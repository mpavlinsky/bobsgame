/*
memory_recycler: A minimal library for doing type-safe bitwise operations.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Leonardo Boquillon, FuDePAN 2015
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt in the root directory or
    copy at http://www.boost.org/LICENSE_1_0.txt)

    MiLi IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#ifndef MEMORY_RECYCLER_H
#define MEMORY_RECYCLER_H

#include <list>
#include <memory>
#include <cstdlib>

NAMESPACE_BEGIN

/**
 * @brief Memory allocator that raise a exception when it can't
 * allocate memory
 * @tparam Type The type to be allocated
 */

template<class Type>
class ThrowMemoryAllocator
{
public:

    /**
     * @brief Allocate one aligned memory block of Type size
     */

    Type* allocate()
    {
        Type* memoryAllocated = static_cast<Type*>(aligned_alloc(alignof(Type), sizeof(Type)));
        if (memoryAllocated == nullptr)
        {
            throw std::bad_alloc();
        } // ELSE: Memory was allocated thus it could continue the normal course. Do nothing.
        return memoryAllocated;
    }

    /**
     * @brief Operator used by unique_ptr to know how delete memory
     * @param usedMemory A pointer to the object we're destroying.
     */
    void operator()(Type* usedMemory)
    {
        free(usedMemory);
    }
};

/**
 * @brief Memory allocator that never raise a exception when it can't
 * allocate memory
 * @tparam Type The type to be allocated
 */

template<class Type>
class NoThrowMemoryAllocator
{
public:
    /**
     * @brief Allocate one aligned memory block of Type size
     */
    Type* allocate() noexcept
    {
        return static_cast<Type*>(aligned_alloc(alignof(Type), sizeof(Type)));
    }

    /**
     * @brief Operator used by unique_ptr to know how delete memory
     * @param usedMemory A pointer to the object we're destroying.
     */
    void operator()(Type* usedMemory)
    {
        free(usedMemory);
    }
};

/**
 * @brief Generic memory recycler. We use this to minimize runtime memory
 * allocations for objects of a given type T.
 * @details We keep two lists of allocated objects: _busy (for objects that are
 * currently in use), and _trash (for objects that were deleted). Every time
 * an object of type T is deleted, Recycler<T>::sendToTrash will place it in the
 * _trash list. Whenever a new T is about to be created, Recycler<T>::allocate
 * will first check if there's an old T in _trash. If there is, we'll use
 * its memory for the new T instead of performing a separate allocation.
 *
 * We use the _busy list to keep track of alive objects. It also allows us to
 * use std::list::splice to move the objects to _trash, thus avoiding the
 * overhead of std::list::push_back.
 *
 * @tparam RecyclableType The type whose memory we want to recycle.
 */

template<class RecyclableType,
         template<typename> class InternalAllocatorPolicy = ThrowMemoryAllocator>
class MemoryRecycler
{
    using Type = RecyclableType;

public:
    struct MemoryPack;

    using InternalAllocator = InternalAllocatorPolicy<MemoryPack>;
    using RecycledObjectInfo = typename std::list<std::unique_ptr<MemoryPack, InternalAllocator>>::iterator;

    /**
     * @brief A wrapper for the recycled object data. It also keeps an iterator
     * that points to it inside the _busy list. We'll use that iterator to avoid
     * traversing _busy whenever we need to access the object.
     */
    struct MemoryPack
    {
        MemoryPack() = delete;

        Type object;
        RecycledObjectInfo recycledObjectInfo;
    };

    using MemoryPackContainer = std::list<std::unique_ptr<MemoryPack, InternalAllocator>>;

    MemoryRecycler() = default;

    /**
     * @brief Checks whether there's an old object already allocated in _trash.
     * If there is, use its memory. Otherwise, allocate a new one.
     * @details This will be called before the object's constructor.
     *
     * @return A pointer to a MemoryPack that wraps the object we're creating.
     */

    MemoryPack* allocate()
    {
        MemoryPack* memory;
        if (!_trash.empty()) /* Objects to be reused */
        {
            auto it = --_trash.end();
            _busy.splice(_busy.end(), _trash, it);
            memory = it->get();
        }
        else /* Need to allocate a new object */
        {
            memory = internalAllocator.allocate();
            _busy.emplace_back(memory, internalAllocator);
            new(&memory->recycledObjectInfo) RecycledObjectInfo(--_busy.end());
        }
        return memory;
    }

    /**
     * @brief Moves an object to the _trash list.
     * @details This will be called before the object's destructor.
     *
     * @param memory A pointer to the object we're destroying.
     */

    void sendToTrash(void* memory)
    {
        MemoryPack* const memoryPack = (static_cast<MemoryPack*>(memory));
        _trash.splice(_trash.end(), _busy, memoryPack->recycledObjectInfo);
    }

private:
    /** @brief Objects that were deleted. */
    MemoryPackContainer _trash;

    /** @brief Objects that are currently in use. */
    MemoryPackContainer _busy;

    /** @brief Instance of allocator used to create new objects */
    InternalAllocator internalAllocator;
};

/**
 * @brief Base class for recyclable objects.
 * @details We use this to implement the CRTP for recyclable classes.
 *
 * A recyclable class T will inherit from RecyclableType<T>, which has a static
 * Recycler<T> member that it uses to manage the recycling of T objects.
 * This way, T::operator new should call RecyclableType<T>::allocateMemory,
 * and T::operator delete should call RecyclableType<T>::deleteMemory.
 *
 * As the Recycler<T> member is static, its destructor will be invoked at
 * program termination.
 *
 * @tparam Derived The class whose objects we're recycling.
 */

template<class Derived>
class RecyclabeType
{
    using InternalRecycler = MemoryRecycler<Derived>;

protected:
    RecyclabeType() = default;

    /**
     * @brief A wrapper for Recycler<T>::allocate.
     * @details This should be called from T::operator new.
     * @return A pointer to the object we're creating.
     */
    static void* allocateMemory()
    {
        typename InternalRecycler::MemoryPack* const memoryPack = _recycler.allocate();
        return &memoryPack->object;
    }

    /**
     * @brief A wrapper for Recycler<T>::sendToTrash.
     * @details This should be called from T::operator delete.
     *
     * @param memory A pointer to the object we're destroying.
     */
    static void deleteMemory(void* memory)
    {
        _recycler.sendToTrash(memory);
    }
private:
    /** @brief A static Recycler<T> instance. */
    static InternalRecycler _recycler;
};

template<class Derived>
typename RecyclabeType<Derived>::InternalRecycler RecyclabeType<Derived>::_recycler;

NAMESPACE_END

#endif