#include "stdafx.h"
/*
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Hugo Arregui, FuDePAN 2011
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
#include <gmock/gmock.h>
#include "mili/mili.h"

using namespace mili;

TEST(ArithUtilsTest, bchain)
{
    ASSERT_TRUE(bchain(1) < 2 < 3);

    int x(10);
    ASSERT_EQ(x, (5 >= bchain(4) < 10));
}

TEST(ArithUtilsTest, power)
{
    ASSERT_EQ(4, power<2>(2));
}

TEST(ArithUtilsTest, power_negative_base)
{
    ASSERT_EQ(.25, power < -2 > (2));
}

TEST(ArithUtilsTest, cubic_root)
{
    ASSERT_EQ(3, cubic_root(27));
}

TEST(ArithUtilsTest, in_range)
{
    ASSERT_FALSE(in_range(3.141692f, 10.0f, 11.0f));
}

TEST(ArithUtilsTest, implies)
{
    ASSERT_TRUE(implies(true, true));
    ASSERT_FALSE(implies(true, false));
    ASSERT_TRUE(implies(false, true));
    ASSERT_TRUE(implies(false, false));
}

TEST(ArithUtilsTest, is_lossless_sum)
{
    ASSERT_FALSE(is_lossless_sum_bigsmall(1e80, 0.0001));
    ASSERT_FALSE(is_lossless_sum(1e80, 0.0001));
    ASSERT_FALSE(is_lossless_sum(0.0001, 1e80));
}

TEST(ArithUtilsTest, deg2rad)
{
    ASSERT_NEAR(0.f, deg2rad(0.f), 10e-6f);
    ASSERT_NEAR(1.5707963f, deg2rad(90.f), 10e-6f);
    ASSERT_NEAR(float(M_PI), deg2rad(180.f), 10e-6f);
}

TEST(ArithUtilsTest, rad2deg)
{
    ASSERT_NEAR(0.f, rad2deg(0.f), 10e-6f);
    ASSERT_NEAR(90.f, rad2deg(1.5707963f), 10e-6f);
    ASSERT_NEAR(180.f, rad2deg(float(M_PI)), 10e-6f);
}

TEST(ArithUtilsTest, is_near_zero)
{
    // Float. Default tolerance.
    ASSERT_TRUE(is_near_zero(0.000001f));
    ASSERT_FALSE(is_near_zero(0.00001f));
    ASSERT_TRUE(is_near_zero(-0.000001f));
    ASSERT_FALSE(is_near_zero(-0.00001f));
    // Float. Tolerance passed as argument.
    ASSERT_TRUE(is_near_zero(0.0000001f, 10e-7f));
    ASSERT_FALSE(is_near_zero(0.000001f, 10e-7f));

    // Double. Default tolerance.
    ASSERT_TRUE(is_near_zero(0.000001));
    ASSERT_FALSE(is_near_zero(0.00001));
    ASSERT_TRUE(is_near_zero(-0.000001));
    ASSERT_FALSE(is_near_zero(-0.00001));
    // Double. Tolerance passed as argument.
    ASSERT_TRUE(is_near_zero(0.0000001, 10e-7));
    ASSERT_FALSE(is_near_zero(0.000001, 10e-7));
}
