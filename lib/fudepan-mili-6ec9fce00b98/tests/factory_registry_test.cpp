#include "stdafx.h"
/*
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Leandro Ramos, FuDePAN 2012
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

    This is a test file.
*/

#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mili/mili.h"

using namespace mili;
using namespace testing;
using std::string;

struct IntOperation
{
    virtual int unaryOperation(const int n) = 0;
    virtual ~IntOperation() {}
};

class PlusOne: public IntOperation
{
    virtual int unaryOperation(const int n)
    {
        return n + 1;
    }
};

REGISTER_FACTORIZABLE_CLASS(IntOperation, PlusOne, string, "PlusOne");

class MinusOne: public IntOperation
{
    virtual int unaryOperation(const int n)
    {
        return n - 1;
    }
};

REGISTER_FACTORIZABLE_CLASS(IntOperation, MinusOne, string, "MinusOne");

class TimesFive: public IntOperation
{
    virtual int unaryOperation(const int n)
    {
        return n * 5;
    }
};

REGISTER_FACTORIZABLE_CLASS(IntOperation, TimesFive, string, "TimesFive");

struct CurriedOperation
{
    const int _fixedArg;
    CurriedOperation(int fixedArg): _fixedArg(fixedArg) {};
    virtual ~CurriedOperation() {};
    virtual int binaryOperation(int x) = 0;
};

struct CurriedAdder : public CurriedOperation
{
    CurriedAdder(int x): CurriedOperation(x) {};
    virtual int binaryOperation(int x)
    {
        return _fixedArg + x;
    };
};
REGISTER_FACTORIZABLE_CLASS_WITH_ARG(CurriedOperation, CurriedAdder, std::string, "CurriedAdder", int);

struct CurriedMultiplication : public CurriedOperation
{
    CurriedMultiplication(int x): CurriedOperation(x) {};
    virtual int binaryOperation(int x)
    {
        return _fixedArg * x;
    };
};
REGISTER_FACTORIZABLE_CLASS_WITH_ARG(CurriedOperation, CurriedMultiplication, std::string, "CurriedMultiplication", int);

TEST(FactoryRegistryTest, ReturnTest)
{
    IntOperation* plusone;
    plusone = FactoryRegistry<IntOperation, string>::new_class("PlusOne");
    ASSERT_NE(static_cast<IntOperation*>(NULL), plusone);
    IntOperation* minusone;
    minusone = FactoryRegistry<IntOperation, string>::new_class("MinusOne");
    ASSERT_NE(static_cast<IntOperation*>(NULL), minusone);
    IntOperation* timesfive;
    timesfive = FactoryRegistry<IntOperation, string>::new_class("TimesFive");
    ASSERT_NE(static_cast<IntOperation*>(NULL), timesfive);
    EXPECT_EQ(4, plusone->unaryOperation(3));
    delete plusone;
    EXPECT_EQ(3, minusone->unaryOperation(4));
    delete minusone;
    EXPECT_EQ(15, timesfive->unaryOperation(3));
    delete timesfive;
}

TEST(FactoryRegistryTest, ReturnTestWithArg)
{
    CurriedOperation* curriedAdder;
    curriedAdder = FactoryRegistry<CurriedOperation, string, int>::new_class("CurriedAdder", 5);
    ASSERT_NE(static_cast<CurriedOperation*>(NULL), curriedAdder);

    CurriedOperation* curriedMultiplication;
    curriedMultiplication = FactoryRegistry<CurriedOperation, string, int>::new_class("CurriedMultiplication", 3);
    ASSERT_NE(static_cast<CurriedOperation*>(NULL), curriedMultiplication);

    EXPECT_EQ(6, curriedAdder->binaryOperation(1));
    delete curriedAdder;
    EXPECT_EQ(12, curriedMultiplication->binaryOperation(4));
    delete curriedMultiplication;
}

TEST(FactoryRegistryTest, NoRegisteredClassTest)
{
    IntOperation* anyone;
    anyone = FactoryRegistry<IntOperation, std::string>::new_class("TimesSeven");
    ASSERT_EQ(static_cast<IntOperation*>(NULL), anyone);
}

TEST(FactoryRegistryTest, NoRegisteredClassTestWithArg)
{
    CurriedOperation* anyone;
    anyone = FactoryRegistry<CurriedOperation, std::string, int>::new_class("CurriedPencet", 4);
    ASSERT_EQ(static_cast<CurriedOperation*>(NULL), anyone);
}


TEST(FactoryRegistryTest, getConstructibleObjectsTest)
{
    mili::Factory<std::string, IntOperation>::KeyIterator it(mili::FactoryRegistry<IntOperation, std::string>::getConstructibleObjectsKeys());
    EXPECT_EQ("MinusOne", *it);
    ++it;
    EXPECT_EQ("PlusOne", *it);
    ++it;
    EXPECT_EQ("TimesFive", *it);
    it++;
    EXPECT_TRUE(it.end());
}
