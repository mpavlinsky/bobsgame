#include "stdafx.h"
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

    This is a test file
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#define private public
#define protected public

#include "mili/mili.h"

#define RECYCLABLE_OPERATORS_INLINE(TYPE) \
    static void * operator new(std::size_t /*size*/) \
    { \
        return RecyclabeType<TYPE>::allocateMemory(); \
    } \
    static void operator delete(void* memory) \
    { \
        RecyclabeType<TYPE>::deleteMemory(memory); \
    } \

struct RecyclableTest1 : public mili::RecyclabeType<RecyclableTest1>
{
    RECYCLABLE_OPERATORS_INLINE(RecyclableTest1);
};

struct RecyclableTest2 : public mili::RecyclabeType<RecyclableTest2>
{
    RECYCLABLE_OPERATORS_INLINE(RecyclableTest2);
};

TEST(MemoryRecycler, NewTest)
{
    RecyclableTest1* object1 = new RecyclableTest1();
    ASSERT_EQ(object1->_recycler._busy.size(), 1);
    RecyclableTest1* object2 = new RecyclableTest1();
    ASSERT_EQ(object1->_recycler._busy.size(), 2);
    RecyclableTest1* object3 = new RecyclableTest1();
    ASSERT_EQ(object1->_recycler._busy.size(), 3);
    ASSERT_EQ(object1->_recycler._trash.size(), 0);

    delete object1;
    delete object2;
    delete object3;
}

TEST(MemoryRecycler, NewAndDeleteTest)
{
    RecyclableTest2* object1 = new RecyclableTest2();
    RecyclableTest2* object2 = new RecyclableTest2();
    ASSERT_EQ(object1->_recycler._busy.size(), 2);
    ASSERT_EQ(object1->_recycler._trash.size(), 0);
    delete object1;
    ASSERT_EQ(object1->_recycler._busy.size(), 1);
    ASSERT_EQ(object1->_recycler._trash.size(), 1);
    delete object2;
    ASSERT_EQ(object1->_recycler._busy.size(), 0);
    ASSERT_EQ(object1->_recycler._trash.size(), 2);
}