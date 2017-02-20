/*
container_utils: A minimal library with generic STL container utilities.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Gutson & Ezequiel S. Velez, FuDePAN 2009-2010
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

#ifndef CONTAINER_UTILS_H
#define CONTAINER_UTILS_H

// Supported containers for mili::find() and mili::contains():
#include <map>
#include <vector>
#include <list>
#include <set>
#include <new>
#include <queue>
#include <string>

#if MILI_CXX_VERSION == MILI_CXX_VERSION_CXX0X
#include <unordered_map>
#include <unordered_set>
#endif

#include <algorithm>
#include <exception>
#include "platform_detection.h"
#include "ranker.h"
#include "generic_exception.h"

NAMESPACE_BEGIN

struct ElementNotFound : std::exception {};

/* Definition of find functions throwing exceptions (const and no const);
   only available if exceptions are allowed.*/
#ifdef MILI_EXCEPTIONS_COMPILER_ENABLED
template <class T, class Alloc, class T2>
inline T& find(std::list<T, Alloc>& cont, const T2& element)
{
    const typename std::list<T, Alloc>::iterator it = find(cont.begin(), cont.end(), element);
    assert_throw<ElementNotFound>(it != cont.end());
    return *it;
}

template <class T, class Alloc, class T2>
inline const T& find(const std::list<T, Alloc>& cont, const T2& element)
{
    const typename std::list<T, Alloc>::const_iterator it = find(cont.begin(), cont.end(), element);
    assert_throw<ElementNotFound>(it != cont.end());
    return *it;
}

template <class T, class Alloc, class T2>
inline T& find(std::vector<T, Alloc>& cont, const T2& element)
{
    const typename std::vector<T, Alloc>::iterator it = find(cont.begin(), cont.end(), element);
    assert_throw<ElementNotFound>(it != cont.end());
    return *it;
}

template <class T, class Alloc, class T2>
inline const T& find(const std::vector<T, Alloc>& cont, const T2& element)
{
    const typename std::vector<T, Alloc>::const_iterator it = find(cont.begin(), cont.end(), element);
    assert_throw<ElementNotFound>(it != cont.end());
    return *it;
}

/*In the templates we use another class (for example Key2) for the parameter element because
 if we didnt do this the function wouldnt match with this template, for example when passing strings.*/

/*This returns a reference to const because the set iterator is always a const reference*/
template <class T, class Comp, class Alloc, class Key2>
inline const T& find(std::set<T, Comp, Alloc>& s, const Key2& key)
{
    const typename std::set<T, Comp, Alloc>::const_iterator it = s.find(key);
    assert_throw<ElementNotFound>(it != s.end());
    return *it;
}

template <class T, class Comp, class Alloc, class Key2>
inline const T& find(const std::set<T, Comp, Alloc>& s, const Key2& key)
{
    const typename std::set<T, Comp, Alloc>::const_iterator it = s.find(key);
    assert_throw<ElementNotFound>(it != s.end());
    return *it;
}

template <class Key, class T, class Comp, class Alloc, class Key2>
inline T& find(std::map<Key, T, Comp, Alloc>& m, const Key2& key)
{
    const typename std::map<Key, T, Comp, Alloc>::iterator it = m.find(key);
    assert_throw<ElementNotFound>(it != m.end());
    return it->second;
}

template <class Key, class T, class Comp, class Alloc, class Key2>
inline const T& find(const std::map<Key, T, Comp, Alloc>& m, const Key2& key)
{
    const typename std::map<Key, T, Comp, Alloc>::const_iterator it = m.find(key);
    assert_throw<ElementNotFound>(it != m.end());
    return it->second;
}

/*Support for C++11's unordered_maps & unordered_sets*/
#if MILI_CXX_VERSION == MILI_CXX_VERSION_CXX0X
template <class Key, class T, class Hash, class Pred, class Alloc, class Key2>
inline T& find(std::unordered_map<Key, T, Hash, Pred, Alloc>& m, const Key2& key)
{
    const auto it = m.find(key);
    assert_throw<ElementNotFound>(it != m.end());
    return it->second;
}

template <class Key, class T, class Hash, class Pred, class Alloc, class Key2>
inline const T& find(const std::unordered_map<Key, T, Hash, Pred, Alloc>& m, const Key2& key)
{
    const auto it = m.find(key);
    assert_throw<ElementNotFound>(it != m.end());
    return it->second;
}

/*This also returns a reference to const because the unordered set iterator is always a const reference*/
template <class T, class Hash, class Pred, class Alloc, class Key2>
inline const T& find(std::unordered_set<T, Hash, Pred, Alloc>& s, const Key2& key)
{
    const auto it = s.find(key);
    assert_throw<ElementNotFound>(it != s.end());
    return *it;
}

template <class T, class Hash, class Pred, class Alloc, class Key2>
inline const T& find(const std::unordered_set<T, Hash, Pred, Alloc>& s, const Key2& key)
{
    const auto it = s.find(key);
    assert_throw<ElementNotFound>(it != s.end());
    return *it;
}
#endif // MILI_CXX_VERSION == MILI_CXX_VERSION_CXX0X
#endif // MILI_EXCEPTIONS_COMPILER_ENABLED

/* find, nothrow versions */
template <class T, class Alloc, class T2>
inline T* find(std::list<T, Alloc>& cont, const T2& element, const std::nothrow_t&)
{
    const typename std::list<T, Alloc>::iterator it = find(cont.begin(), cont.end(), element);
    if (it == cont.end())
        return NULL;
    else
        return &(*it);
}

template <class T, class Alloc, class T2>
inline const T* find(const std::list<T, Alloc>& cont, const T2& element, const std::nothrow_t&)
{
    const typename std::list<T, Alloc>::const_iterator it = find(cont.begin(), cont.end(), element);
    if (it == cont.end())
        return NULL;
    else
        return &(*it);
}

template <class T, class Alloc, class T2>
inline T* find(std::vector<T, Alloc>& cont, const T2& element, const std::nothrow_t&)
{
    const typename std::vector<T, Alloc>::iterator it = find(cont.begin(), cont.end(), element);
    if (it == cont.end())
        return NULL;
    else
        return &(*it);
}

template <class T, class Alloc, class T2>
inline const T* find(const std::vector<T, Alloc>& cont, const T2& element, const std::nothrow_t&)
{
    const typename std::vector<T, Alloc>::const_iterator it = find(cont.begin(), cont.end(), element);
    if (it == cont.end())
        return NULL;
    else
        return &(*it);
}

template <class T, class Comp, class Alloc, class Key2>
inline const T* find(std::set<T, Comp, Alloc>& s, const Key2& key, const std::nothrow_t&)
{
    const typename std::set<T, Comp, Alloc>::const_iterator it = s.find(key);
    if (it == s.end())
        return NULL;
    else
        return &(*it);
}

template <class T, class Comp, class Alloc, class Key2>
inline const T* find(const std::set<T, Comp, Alloc>& s, const Key2& key, const std::nothrow_t&)
{
    const typename std::set<T, Comp, Alloc>::const_iterator it = s.find(key);
    if (it == s.end())
        return NULL;
    else
        return &(*it);
}


template <class Key, class T, class Comp, class Alloc, class Key2>
inline T* find(std::map<Key, T, Comp, Alloc>& m, const Key2& key, const std::nothrow_t&)
{
    const typename std::map<Key, T, Comp, Alloc>::iterator it = m.find(key);
    if (it == m.end())
        return NULL;
    else
        return &(it->second);
}

template <class Key, class T, class Comp, class Alloc, class Key2>
inline const T* find(const std::map<Key, T, Comp, Alloc>& m, const Key2& key, const std::nothrow_t&)
{
    const typename std::map<Key, T, Comp, Alloc>::const_iterator it = m.find(key);
    if (it == m.end())
        return NULL;
    else
        return &(it->second);
}

#if MILI_CXX_VERSION == MILI_CXX_VERSION_CXX0X
template <class Key, class T, class Hash, class Pred, class Alloc, class Key2>
inline T* find(std::unordered_map<Key, T, Hash, Pred, Alloc>& m, const Key2& key, const std::nothrow_t&) noexcept
{
    const auto it = m.find(key);
    if (it == m.end())
        return NULL;
    else
        return &(it->second);
}

template <class Key, class T, class Hash, class Pred, class Alloc, class Key2>
inline const T* find(const std::unordered_map<Key, T, Hash, Pred, Alloc>& m, const Key2& key, const std::nothrow_t&) noexcept
{
    const auto it = m.find(key);
    if (it == m.end())
        return NULL;
    else
        return &(it->second);
}

/* this also returns a reference to a const beacuse the unordered_set iterator is always a reference to a const*/
template <class T, class Hash, class Pred, class Alloc, class Key2>
inline const T* find(std::unordered_set<T, Hash, Pred, Alloc>& s, const Key2& key, const std::nothrow_t&) noexcept
{
    const auto it = s.find(key);
    if (it == s.end())
        return nullptr;
    else
        return &(*it);
}

template <class T, class Hash, class Pred, class Alloc, class Key2>
inline const T* find(const std::unordered_set<T, Hash, Pred, Alloc>& s, const Key2& key, const std::nothrow_t&) noexcept
{
    const auto it = s.find(key);
    if (it == s.end())
        return nullptr;
    else
        return &(*it);
}
#endif

/* contains specializations */
template <class T, class Alloc, class T2>
inline bool contains(const std::vector<T, Alloc>& v, const T2& element)
{
    return find(v.begin(), v.end(), element) != v.end();
}

template <class T, class Alloc, class T2>
inline bool contains(const std::list<T, Alloc>& l, const T2& element)
{
    return find(l.begin(), l.end(), element) != l.end();
}

template <class Key, class T, class Comp, class Alloc, class Key2>
inline bool contains(const std::map<Key, T, Comp, Alloc>& m, const Key2& key)
{
    return m.count(key) > 0;
}

template <class Key, class Comp, class Alloc, class T2>
inline bool contains(const std::set<Key, Comp, Alloc>& s, const T2& key)
{
    return s.count(key) > 0;
}

#if MILI_CXX_VERSION == MILI_CXX_VERSION_CXX0X
template <class Key, class T, class Hash, class Pred, class Alloc, class Key2>
inline bool contains(const std::unordered_map<Key, T, Hash, Pred, Alloc>& m, const Key2& key)
{
    return m.count(key) > 0;
}

template <class T, class Hash, class Pred, class Alloc, class Key2>
inline bool contains(const std::unordered_set<T, Hash, Pred, Alloc>& s, const Key2& key)
{
    return s.count(key) > 0;
}
#endif

template <class str>
inline bool contains(const std::string& l, const str& element)
{
    const std::string::size_type found = l.find(element);
    return found != std::string::npos;
}

// ------------ Insertion Utilities

/*this works for sets*/
template <class T, class Compare, class Alloc, class T2>
inline void insert_into(std::set<T, Compare, Alloc>& cont, const T2& element)
{
    cont.insert(element);
}
/*this works for unordered sets*/
#if MILI_CXX_VERSION == MILI_CXX_VERSION_CXX0X
template <class Key, class Hash, class Pred, class Alloc, class Key2>
inline void insert_into(std::unordered_set<Key, Hash, Pred, Alloc>& cont, const Key2& element)
{
    cont.insert(element);
}
#endif

/* This works for lists */
template<class ElementType, class Alloc, class ElementType2>
inline void insert_into(std::list<ElementType, Alloc>& cont, const ElementType2& element)
{
    cont.push_back(element);
}

/* This works for vector */
template<class ElementType, class Alloc, class ElementType2>
inline void insert_into(std::vector<ElementType, Alloc>& cont, const ElementType2& element)
{
    cont.push_back(element);
}

/*this works for deque*/
template<class ElementType, class Alloc, class ElementType2>
inline void insert_into(std::deque<ElementType, Alloc>& cont, const ElementType2& element)
{
    cont.push_back(element);
}

/* This works for Ranker */
template <class T, SameValueBehavior Behavior, class Comp, class T2>
inline void insert_into(Ranker<T, Behavior, Comp>& cont, const T2& element)
{
    cont.insert(element);
}

/* This works for Queue */
template <class T, class Container, class T2>
inline void insert_into(std::queue<T, Container>& cont, const T2& element)
{
    cont.push(element);
}


//------------ Remove first Utilities

/* This works for vectors*/
template <class T, class Alloc, class T2>
inline bool remove_first_from(std::vector<T, Alloc>& cont, const T2& element)
{
    const typename std::vector<T, Alloc>::iterator it = find(cont.begin(), cont.end(), element);
    const bool result(it != cont.end());
    if (result) cont.erase(it);
    return result;
}

/* This works for lists*/
template <class T, class Alloc, class T2>
inline bool remove_first_from(std::list<T, Alloc>& cont, const T2& element)
{
    const typename std::list<T, Alloc>::iterator it = find(cont.begin(), cont.end(), element);
    const bool result(it != cont.end());
    if (result) cont.erase(it);
    return result;
}

/* This works for sets*/
template<class ElementType, class Comp, class Alloc, class ElementType2>
inline bool remove_first_from(std::set<ElementType, Comp, Alloc>& cont, const ElementType2& element)
{
    return (cont.erase(element) > 0);
}

/* This works for Maps */
template <class Key, class T, class Comp, class Alloc, class ElementType>
inline bool remove_first_from(std::map<Key, T, Comp, Alloc>& m, const ElementType& element)
{
    typename std::map<Key, T, Comp, Alloc>::iterator it = m.begin();
    bool result(false);
    while (it != m.end() && !result)
    {
        if (it->second == element)
        {
            m.erase(it);
            result = true;
        }
        else
        {
            ++it;
        }
    }
    return result;
}

#if MILI_CXX_VERSION == MILI_CXX_VERSION_CXX0X
/*this works for USet*/
template<class T, class Hash, class Pred, class Alloc, class T2>
inline bool remove_first_from(std::unordered_set<T, Hash, Pred, Alloc>& cont, const T2& element)
{
    return (cont.erase(element) > 0);
}

/* This works for UMaps */
template <class Key, class T, class Hash, class Pred, class Alloc, class T2>
inline bool remove_first_from(std::unordered_map<Key, T, Hash, Pred, Alloc>& m, const T2& element)
{
    auto it = m.begin();
    bool result(false);
    while (it != m.end() && !result)
    {
        if (it->second == element)
        {
            m.erase(it);
            result = true;
        }
        else
        {
            ++it;
        }
    }
    return result;
}
#endif

/* This works for Ranker */
template <class T, SameValueBehavior Behavior, class Comp, class T2>
inline bool remove_first_from(Ranker<T, Behavior, Comp>& cont, const T2& element)
{
    const typename Ranker<T, Behavior, Comp>::const_iterator it = find(cont.begin(), cont.end(), element);
    const bool result(it != cont.end());
    if (result) cont.remove_first(element);
    return result;
}

//------------ Remove all Utilities

/* This works for vectors */
template <class T, class Alloc, class T2 >
inline bool remove_all_from(std::vector<T, Alloc>& cont, const T2& element)
{
    typename std::vector<T, Alloc>::iterator it = cont.begin();
    bool result(false);
    while (it != cont.end())
    {
        if (*it == element)
        {
            it = cont.erase(it);
            result = true;
        }
        else
        {
            ++it;
        }
    }
    return result;
}

/*This is for lists*/
template <class T, class Alloc, class T2 >
inline bool remove_all_from(std::list<T, Alloc>& cont, const T2& element)
{
    typename std::list<T, Alloc>::iterator it = cont.begin();
    bool result(false);
    while (it != cont.end())
    {
        if (*it == element)
        {
            it = cont.erase(it);
            result = true;
        }
        else
        {
            ++it;
        }
    }
    return result;
}

/* This works for Sets */
template<class ElementType, class Comp, class Alloc, class ElementType2>
inline bool remove_all_from(std::set<ElementType, Comp, Alloc>& cont, const ElementType2& element)
{
    return remove_first_from(cont, element);
}

/* This works for Maps */
template <class Key, class T, class Comp, class Alloc, class ElementType>
inline bool remove_all_from(std::map<Key, T, Comp, Alloc>& m, const ElementType& element)
{
    typename std::map<Key, T, Comp, Alloc>::iterator it = m.begin();
    bool result(false);
    while (it != m.end())
    {
        if (it->second == element)
        {
            typename std::map<Key, T, Comp, Alloc>::iterator it_temp(it);
            ++it_temp;
            m.erase(it);
            it = it_temp;
            result = true;
        }
        else
        {
            ++it;
        }
    }
    return result;
}

#if MILI_CXX_VERSION == MILI_CXX_VERSION_CXX0X
/* This works for USets */
template<class T, class Hash, class Pred, class Alloc, class T2>
inline bool remove_all_from(std::unordered_set<T, Hash, Pred, Alloc>& cont, const T2& element)
{
    return remove_first_from(cont, element);
}

/* This works for UMaps */
template <class Key, class T, class Hash, class Pred, class Alloc, class T2>
inline bool remove_all_from(std::unordered_map<Key, T, Hash, Pred, Alloc>& m, const T2& element)
{
    auto it = m.begin();
    bool result(false);
    while (it != m.end())
    {
        if (it->second == element)
        {
            it = m.erase(it);
            result = true;
        }
        else
        {
            ++it;
        }
    }
    return result;
}
#endif

/* This works for Ranker */
template <class T, SameValueBehavior Behavior, class Comp, class T2>
inline bool remove_all_from(Ranker<T, Behavior, Comp>& cont, const T2& element)
{
    const typename Ranker<T, Behavior, Comp>::const_iterator it = find(cont.begin(), cont.end(), element);
    const bool result(it != cont.end());
    if (result) cont.remove_all(element);
    return result;
}

// Generic container
template <class T>
struct ContainerAdapter
{
    virtual void insert(const T& element) = 0;
    virtual void clear() = 0;
    virtual ~ContainerAdapter() {}
};

template <class T, class Impl>
class ContainerAdapterImpl : public ContainerAdapter<T>
{
    Impl& container;
    virtual void insert(const T& element)
    {
        insert_into(container, element);
    }

    virtual void clear()
    {
        container.clear();
    }
public:
    ContainerAdapterImpl(Impl& cont)
        : container(cont)
    {}
};

template <class Impl>
inline ContainerAdapterImpl<typename Impl::value_type, Impl> containerAdapter(Impl& container)
{
    return ContainerAdapterImpl<typename Impl::value_type, Impl>(container);
}

// CopyContainer -----------------------------
template <class C1, class C2>
static inline void copy_container(const C1& c1, C2& c2)
{
    std::copy(c1.begin(), c1.end(), std::back_insert_iterator<C2> (c2));
}

// TODO: Add more containers.

// Autonomous iterators ----------------------
template <class Container, class Iterator, class Parent>
class AutonomousIteratorBase
{
protected:
    Iterator _current;
    Container& _cont;

    AutonomousIteratorBase(Container& cont, const Iterator& current)
        : _current(current), _cont(cont)
    {}

    AutonomousIteratorBase(Container& cont)
        : _current(cont.begin()), _cont(cont)
    {}

    AutonomousIteratorBase(const AutonomousIteratorBase<Container, Iterator, Parent>& other)
        : _current(other._current), _cont(other._cont)
    {}

    Parent& ThisRef()
    {
        return static_cast<Parent&>(*this);
    }

    const Parent& ThisRef() const
    {
        return static_cast<const Parent&>(*this);
    }
public:
    typedef typename Container::value_type value_type;
    typedef typename Container::reference reference;

    Parent& operator ++()
    {
        ++_current;
        return ThisRef();
    }

    Parent operator ++(int)
    {
        const Parent ret(ThisRef());
        ++(*this);
        return ret;
    }

    Parent& operator --()
    {
        --_current;
        return ThisRef();
    }

    Parent operator --(int)
    {
        const Parent ret(ThisRef());
        --(*this);
        return ret;
    }

    bool operator == (const AutonomousIteratorBase<Container, Iterator, Parent>& other) const
    {
        return _current == other._current;
    }

    typename Container::const_reference operator*() const
    {
        return *_current;
    }

    typename Container::const_iterator& operator->()
    {
        return _current;
    }

    const typename Container::const_iterator& operator->() const
    {
        return _current;
    }

    bool end() const
    {
        return _current == _cont.end();
    }
};

template <class Container>
class AutonomousIterator : public AutonomousIteratorBase<Container, typename Container::iterator, AutonomousIterator<Container> >
{
    typedef AutonomousIteratorBase<Container, typename Container::iterator, AutonomousIterator<Container> > Base;
public:
    AutonomousIterator(const AutonomousIterator<Container>& other)
        : Base(other)
    {}

    AutonomousIterator(Container& cont)
        : Base(cont)
    {}

    AutonomousIterator(Container& cont, typename Container::iterator it)
        : Base(cont, it)
    {}

    typename Container::reference operator*()
    {
        return *this->_current;
    }

    typename Container::iterator& operator->()
    {
        return this->_current;
    }
};

template <class Container>
class CAutonomousIterator : public AutonomousIteratorBase<const Container, typename Container::const_iterator, CAutonomousIterator<Container> >
{
    typedef AutonomousIteratorBase<const Container, typename Container::const_iterator, CAutonomousIterator<Container> > Base;
public:
    CAutonomousIterator(const CAutonomousIterator<Container>& other)
        : Base(other)
    {}

    CAutonomousIterator(const Container& cont)
        : Base(cont)
    {}

    CAutonomousIterator(const Container& cont, typename Container::const_iterator it)
        : Base(cont, it)
    {}
};

NAMESPACE_END

#endif
