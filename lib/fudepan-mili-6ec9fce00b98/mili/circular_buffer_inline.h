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

NAMESPACE_BEGIN

#ifndef CIRC_BUFFER_INLINE_H
#error Internal header file, DO NOT include this.
#endif

#include <cassert>

template < typename T,
           CircularBufferSizeType Size,
           class DequeueOnEmptyPolicy,
           class EnqueueOnFullPolicy,
           class DropTooManyPolicy >
inline bool CircBuffer<T, Size, DequeueOnEmptyPolicy, EnqueueOnFullPolicy, DropTooManyPolicy>
::isFull() const
{
    return (_read == _write);
}

template < typename T,
           CircularBufferSizeType Size,
           class DequeueOnEmptyPolicy,
           class EnqueueOnFullPolicy,
           class DropTooManyPolicy >
inline void CircBuffer<T, Size, DequeueOnEmptyPolicy, EnqueueOnFullPolicy, DropTooManyPolicy>
::flush()
{
    _read = Size;
}

template < typename T,
           CircularBufferSizeType Size,
           class DequeueOnEmptyPolicy,
           class EnqueueOnFullPolicy,
           class DropTooManyPolicy >
inline void CircBuffer<T, Size, DequeueOnEmptyPolicy, EnqueueOnFullPolicy, DropTooManyPolicy>
::parkReadIndex()
{
    if (isFull())
    {
        flush();
    }
}

template < typename T,
           CircularBufferSizeType Size,
           class DequeueOnEmptyPolicy,
           class EnqueueOnFullPolicy,
           class DropTooManyPolicy >
inline bool CircBuffer<T, Size, DequeueOnEmptyPolicy, EnqueueOnFullPolicy, DropTooManyPolicy>
::isEmpty() const
{
    return (_read == Size);
}

template < typename T,
           CircularBufferSizeType Size,
           class DequeueOnEmptyPolicy,
           class EnqueueOnFullPolicy,
           class DropTooManyPolicy >
inline void CircBuffer<T, Size, DequeueOnEmptyPolicy, EnqueueOnFullPolicy, DropTooManyPolicy>
::unparkReadIndex()
{
    if (isEmpty())
    {
        _read = _write;
    }
}

template < typename T,
           CircularBufferSizeType Size,
           class DequeueOnEmptyPolicy,
           class EnqueueOnFullPolicy,
           class DropTooManyPolicy >
inline CircBuffer<T, Size, DequeueOnEmptyPolicy, EnqueueOnFullPolicy, DropTooManyPolicy>
::CircBuffer()
    : _write(0u), _read(Size)
{}

template < typename T,
           CircularBufferSizeType Size,
           class DequeueOnEmptyPolicy,
           class EnqueueOnFullPolicy,
           class DropTooManyPolicy >
inline void CircBuffer<T, Size, DequeueOnEmptyPolicy, EnqueueOnFullPolicy, DropTooManyPolicy>
::queue(const T item)
{
    EnqueueOnFullPolicy::checkPredicate(!isFull());
    _buf[_write] = item;
    unparkReadIndex();
    ++_write;
    _write %= Size;
}

template < typename T,
           CircularBufferSizeType Size,
           class DequeueOnEmptyPolicy,
           class EnqueueOnFullPolicy,
           class DropTooManyPolicy >
inline CircularBufferSizeType CircBuffer<T, Size, DequeueOnEmptyPolicy, EnqueueOnFullPolicy, DropTooManyPolicy>
::available() const
{
    CircularBufferSizeType result;
    if (isEmpty())
    {
        result = Size;
    }
    else    // if isFull() we should return 0, but the formula below delivers exactly that.
    {
        result = (Size - _write + _read) % Size;
    }
    return result;
}

template < typename T,
           CircularBufferSizeType Size,
           class DequeueOnEmptyPolicy,
           class EnqueueOnFullPolicy,
           class DropTooManyPolicy >
inline T CircBuffer<T, Size, DequeueOnEmptyPolicy, EnqueueOnFullPolicy, DropTooManyPolicy>
::dequeue()
{
    DequeueOnEmptyPolicy::checkPredicate(!isEmpty());
    const T result = _buf[_read];
    ++_read;
    _read %= Size;
    parkReadIndex();
    return result;
}

template < typename T,
           CircularBufferSizeType Size,
           class DequeueOnEmptyPolicy,
           class EnqueueOnFullPolicy,
           class DropTooManyPolicy >
template < CircularBufferSizeType SrcSize,
           class SrcDequeueOnEmptyPolicy,
           class SrcEnqueueOnFullPolicy,
           class SrcDropTooManyPolicy >
inline CircularBufferSizeType CircBuffer<T, Size, DequeueOnEmptyPolicy, EnqueueOnFullPolicy, DropTooManyPolicy>
::moveFrom(CircBuffer<T, SrcSize, SrcDequeueOnEmptyPolicy, SrcEnqueueOnFullPolicy, SrcDropTooManyPolicy>& src)
{
    CircularBufferSizeType result = 0u;

    while (!src.isEmpty() && !isFull())
    {
        queue(src.dequeue());
        ++result;
    }
    return result;
}

template < typename T,
           CircularBufferSizeType Size,
           class DequeueOnEmptyPolicy,
           class EnqueueOnFullPolicy,
           class DropTooManyPolicy >
inline CircularBufferSizeType CircBuffer<T, Size, DequeueOnEmptyPolicy, EnqueueOnFullPolicy, DropTooManyPolicy>
::used() const
{
    return Size - available();
}

template < typename T,
           CircularBufferSizeType Size,
           class DequeueOnEmptyPolicy,
           class EnqueueOnFullPolicy,
           class DropTooManyPolicy >
inline CircularBufferSizeType CircBuffer<T, Size, DequeueOnEmptyPolicy, EnqueueOnFullPolicy, DropTooManyPolicy>
::size() const
{
    return Size;
}

template < typename T,
           CircularBufferSizeType Size,
           class DequeueOnEmptyPolicy,
           class EnqueueOnFullPolicy,
           class DropTooManyPolicy >
inline void CircBuffer<T, Size, DequeueOnEmptyPolicy, EnqueueOnFullPolicy, DropTooManyPolicy>
::discard(CircularBufferSizeType amount)
{
    DropTooManyPolicy::checkPredicate(amount <= used());
    _read = (_read + amount) % Size;
    parkReadIndex();
}

NAMESPACE_END
