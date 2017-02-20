/*
circular_buffer: A type-templetized circular buffer.
    This file is part of the MiLi Minimalistic Library.


    Copyright (C) Pablo Oliva, Franco Riberi, FuDePAN 2013
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

#ifndef CIRC_BUFFER_H
#define CIRC_BUFFER_H

#include "generic_exception.h"
#include "exception_policy.h"

NAMESPACE_BEGIN

/** @brief Exceptions for CircularBuffer. */
struct CircularBufferExceptionHierarchy {};
typedef mili::GenericException<CircularBufferExceptionHierarchy> CircularBufferException;

DEFINE_SPECIFIC_EXCEPTION_TEXT(EmptyDequeue, CircularBufferExceptionHierarchy, "Attempt to dequeue an element from an empty buffer.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(FullEnqueue, CircularBufferExceptionHierarchy, "Attempt to enqueue an element on a full buffer.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(ExcessiveDrop, CircularBufferExceptionHierarchy, "Attempt to drop more elements than those contained in the buffer.");

/** @brief The type we want to use for circular buffer. */
typedef unsigned int CircularBufferSizeType;

/**
 * @brief Circular buffer.
 *
 * Takes 5 template parameters:
 * T                    The type that the buffer will contain.
 * Size                 The amount of elements contained by the buffer.
 * DequeueOnEmptyPolicy The action to perform when dequeue() is invoked on an empty buffer. Assertion by default.
 * EnqueueOnFullPolicy  The action to perform when queue() is invoked on a full buffer. Assertion by default.
 * DropTooManyPolicy    The action to perform when drop() is invoked on a buffer that has too few elements to drop. Assertion by default.
 */
template < typename T,
           CircularBufferSizeType Size,
           class DequeueOnEmptyPolicy = AssertionErrorPolicy,
           class EnqueueOnFullPolicy = AssertionErrorPolicy,
           class DropTooManyPolicy = AssertionErrorPolicy >
class CircBuffer
{
public:
    /**
     * @brief Constructor.
     */
    CircBuffer();

    /**
     * @brief Checks if the buffer is full.
     * @return true if the buffer is full, false otherwise.
     */
    bool isFull() const;

    /**
     * @brief  Checks if the buffer is empty.
     * @return true if the buffer is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Resets the buffer
     */
    void flush();

    /**
     * @brief Adds the item k to the buffer. Checks if the buffer is full.
     *
     * @param item      The item we want to add.
     */
    void queue(T item);

    /**
     * @brief Tells how much buffer space is available.
     * @return Space available in the buffer.
     */
    CircularBufferSizeType available() const;

    /**
     * @brief Tells how much buffer space is used.
     *
     * @return Space used in the buffer.
     */
    CircularBufferSizeType used() const;

    /**
     * @brief Tells how large the buffer is.
     *
     * @return Size of the buffer.
     */
    CircularBufferSizeType size() const;

    /**
     * @brief Removes the index pointed to by _read and returns it. Checks if the buffer is empty.
     *
     * @return The removed item.
     */
    T dequeue();

    /**
     * @brief Discards amount elements of the buffer, checks if there are too few elements.
     *
     * @param amount The amount of elements we want to discard.
     */
    void discard(CircularBufferSizeType amount);

    /**
    * @brief Moves as many items as possible from src to this CircBuffer.
    *
    * @param src    The CircBuffer whose elements we want to move here.
    *
    * @return The amount of elements moved.
    */
    template < CircularBufferSizeType SrcSize,
               class SrcDequeueOnEmptyPolicy,
               class SrcEnqueueOnFullPolicy,
               class SrcDropTooManyPolicy >
    CircularBufferSizeType moveFrom(CircBuffer<T, SrcSize, SrcDequeueOnEmptyPolicy, SrcEnqueueOnFullPolicy, SrcDropTooManyPolicy>& src);

private:
    /**
     * @brief Checks if the read index is valid, points it to ParkingLot otherwise.
     */
    void parkReadIndex();

    /**
     * @brief If there are values to read, points the read index to the first of such values; does nothing otherwise.
     */
    void unparkReadIndex();

    /**
     * @brief The write index on the array.
     */
    CircularBufferSizeType _write;

    /**
     * @brief The read index on the array; is equal to ParkingLot when there is no data to read.
     */
    CircularBufferSizeType _read;

    /**
     * @brief The array of elements where we store our values.
     */
    T _buf[Size];

    /**
     * @brief The place where the read index goes when it has no valid data to point to.
     */
    static const CircularBufferSizeType ParkingLot = Size;
};

NAMESPACE_END

#define CIRC_BUFFER_INLINE_H
#include "circular_buffer_inline.h"
#undef CIRC_BUFFER_INLINE_H

#endif

