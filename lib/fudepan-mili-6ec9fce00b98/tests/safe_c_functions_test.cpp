#include "stdafx.h"
/*
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Lucas Besso, FuDePAN 2013
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

#include <gtest/gtest.h>
#include <string>
#include "mili/mili.h"


struct Values
{
    int val1;
    float val2;
    bool val3;
    double val4;
};


TEST(Safe_C_Functions_Test, copyValues)
{
    Values values;
    values.val1 = -525;
    values.val2 = 34.5f;
    values.val3 = true;
    values.val4 = 4.5;

    Values valuesCpy;
    mili::safecpy(&valuesCpy, &values, sizeof(Values));

    EXPECT_EQ(-525, valuesCpy.val1);
    ASSERT_FLOAT_EQ(34.5f, valuesCpy.val2);
    EXPECT_TRUE(valuesCpy.val3);
    ASSERT_DOUBLE_EQ(4.5, valuesCpy.val4);
}


TEST(Safe_C_Functions_Test, copyChars)
{
    typedef char MyBuffer[6];

    const char* const hello = "hello";

    MyBuffer buf;
    mili::safecpy(buf, hello, 6);

    EXPECT_STREQ(hello, buf);
}
