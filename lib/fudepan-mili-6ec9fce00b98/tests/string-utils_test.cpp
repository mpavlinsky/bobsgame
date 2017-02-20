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
#include <map>
#include "mili/mili.h"

using namespace mili;

TEST(StringUtilsTest, lstring_test)
{
    lstring ls("helLO");
    ls[1] = 'E';

    ASSERT_TRUE(ls[2] == 'L');
    ASSERT_TRUE(ls == "HELLO");

    std::map<lstring, int> m;
    m["Hello"] = 3;
    m["Goodbye"] = 5;
    ASSERT_EQ(3, m["hELLo"]);

    ASSERT_TRUE(begins_with(ls, "HE"));
    ASSERT_TRUE(ends_with(ls, "Ello"));
}

TEST(StringUtilsTest, toupper)
{
    ASSERT_EQ("HELLO WORLD!", toupper("Hello World!"));
}

/** to_string short int */
TEST(StringUtilsTest, to_string_sInt)
{
    ASSERT_EQ("123654", to_string(123654));
}

TEST(StringUtilsTest, to_string_sIntNegative)
{
    ASSERT_EQ("-123654", to_string(-123654));
}

/** to_string unsigned short int */
TEST(StringUtilsTest, to_string_uSInt)
{
    ASSERT_EQ("65535", to_string(65535));
}

/** to_string int */
TEST(StringUtilsTest, to_string_Int)
{
    ASSERT_EQ("2147563", to_string(2147563));
}

TEST(StringUtilsTest, to_string_IntNegative)
{
    ASSERT_EQ("-2147563", to_string(-2147563));
}

/** to_string unsigned int */
TEST(StringUtilsTest, to_string_uInt)
{
    ASSERT_EQ("2147561", to_string(2147561));
}

/** to_string long int */
TEST(StringUtilsTest, to_string_lInt)
{
    ASSERT_EQ("2147999", to_string(2147999));
}

TEST(StringUtilsTest, to_string_lIntNegative)
{
    ASSERT_EQ("-2147999", to_string(-2147999));
}

/** to_string unsigned long int */
TEST(StringUtilsTest, to_string_ulInt)
{
    ASSERT_EQ("2147483647", to_string(2147483647));
}

/** to_string long long int */
TEST(StringUtilsTest, to_string_llInt)
{
    ASSERT_EQ("9223372036854775807", to_string(9223372036854775807));
}

TEST(StringUtilsTest, to_string_llIntNegative)
{
    ASSERT_EQ("-9223372036854775807", to_string(-9223372036854775807));
}

/** to_string unsigned long long int */
TEST(StringUtilsTest, to_string_ullInt)
{
    ASSERT_EQ("9223372036854775805", to_string(9223372036854775805));
}

template <class T>
static void executeUnsignedIntegersBasicTests()
{
    T value;
    EXPECT_FALSE(from_string("-3", value));
    EXPECT_FALSE(from_string("3234.3", value));
    EXPECT_FALSE(from_string("3234SD", value));
    EXPECT_FALSE(from_string("qweqweqw", value));
    EXPECT_FALSE(from_string("", value));

    EXPECT_TRUE(from_string("23424", value));
    EXPECT_EQ(23424, value);
    EXPECT_TRUE(from_string("  786", value));
    EXPECT_EQ(786, value);
    EXPECT_TRUE(from_string("0", value));
    EXPECT_EQ(0, value);

    EXPECT_THROW(value = from_string<T>("-3"), ConversionFailed);
    EXPECT_THROW(value = from_string<T>("3234.3"), ConversionFailed);
    EXPECT_THROW(value = from_string<T>("3234SD"), ConversionFailed);
    EXPECT_THROW(value = from_string<T>("qweqweqw"), ConversionFailed);
    EXPECT_THROW(value = from_string<T>(""), ConversionFailed);

    EXPECT_NO_THROW(value = from_string<T>("23424"));
    EXPECT_EQ(23424, value);
    EXPECT_NO_THROW(value = from_string<T>(" 243"));
    EXPECT_EQ(243, value);
    EXPECT_NO_THROW(value = from_string<T>("0"));
    EXPECT_EQ(0, value);
}

template <class T>
static void executeSignedIntegersBasicTests()
{
    T value;
    EXPECT_FALSE(from_string("", value));
    EXPECT_FALSE(from_string("234DF", value));
    EXPECT_FALSE(from_string("234.435", value));
    EXPECT_FALSE(from_string("qweqwewq", value));
    EXPECT_TRUE(from_string("234", value));
    EXPECT_EQ(234, value);
    EXPECT_TRUE(from_string("-5004", value));
    EXPECT_EQ(-5004, value);
    EXPECT_TRUE(from_string("0", value));
    EXPECT_EQ(0, value);

    EXPECT_THROW(value = from_string<T>(""), ConversionFailed);
    EXPECT_THROW(value = from_string<T>("234DF"), ConversionFailed);
    EXPECT_THROW(value = from_string<T>("234.435"), ConversionFailed);
    EXPECT_THROW(value = from_string<T>("qweqwewq"), ConversionFailed);

    EXPECT_NO_THROW(value = from_string<T>("234"));
    EXPECT_EQ(234, value);
    EXPECT_NO_THROW(value = from_string<T>("-5004"));
    EXPECT_EQ(-5004, value);
    EXPECT_NO_THROW(value = from_string<T>("0"));
    EXPECT_EQ(0, value);
}

template <class T>
static void executeFloatPointBasicTests()
{
    T value;
    EXPECT_FALSE(from_string("6410..671356", value));
    EXPECT_FALSE(from_string("6410.671DD", value));
    EXPECT_FALSE(from_string("-6410.671DD", value));
    EXPECT_FALSE(from_string("", value));
    EXPECT_FALSE(from_string("ADSsaf", value));

    EXPECT_TRUE(from_string("6410.671356", value));
    EXPECT_FLOAT_EQ(6410.671356f, value);

    EXPECT_TRUE(from_string("0.0", value));
    EXPECT_FLOAT_EQ(0.0f, value);

    EXPECT_TRUE(from_string("-45466.45656", value));
    EXPECT_FLOAT_EQ(-45466.45656f, value);

    EXPECT_THROW(value = from_string<T>("6410..671356"), ConversionFailed);
    EXPECT_THROW(value = from_string<T>("6410.671DD"), ConversionFailed);
    EXPECT_THROW(value = from_string<T>("-6410.671DD"), ConversionFailed);
    EXPECT_THROW(value = from_string<T>(""), ConversionFailed);
    EXPECT_THROW(value = from_string<T>("ADSsaf"), ConversionFailed);

    EXPECT_NO_THROW(value = from_string<T>("6410.671356"));
    EXPECT_FLOAT_EQ(6410.671356f, value);

    EXPECT_NO_THROW(value = from_string<T>("0.0"));
    EXPECT_FLOAT_EQ(0.0f, value);

    EXPECT_NO_THROW(value = from_string<T>("-45466.45656"));
    EXPECT_FLOAT_EQ(-45466.45656f, value);
}



// TODO Add test cases to check overflows and underflows.


TEST(StringUtilsTest, from_string_to_unsigned_short_int)
{
    executeUnsignedIntegersBasicTests<unsigned short int>();
}


TEST(StringUtilsTest, from_string_to_short_int)
{
    executeSignedIntegersBasicTests<short int>();
}


TEST(StringUtilsTest, from_string_to_unsigned_int)
{
    executeUnsignedIntegersBasicTests<unsigned int>();
}


TEST(StringUtilsTest, from_string_to_int)
{
    executeSignedIntegersBasicTests<int>();
}


TEST(StringUtilsTest, from_string_to_unsigned_long_int)
{
    executeUnsignedIntegersBasicTests<unsigned long int>();
}


TEST(StringUtilsTest, from_string_to_long_int)
{
    executeSignedIntegersBasicTests<long int>();
}

TEST(StringUtilsTest, from_string_to_unsigned_long_long_int)
{
    executeUnsignedIntegersBasicTests<unsigned long long int>();
}

TEST(StringUtilsTest, from_string_to_long_long_int)
{
    executeSignedIntegersBasicTests<long long int>();
}

TEST(StringUtilsTest, from_string_to_float)
{
    executeFloatPointBasicTests<float>();
}


TEST(StringUtilsTest, from_string_to_double)
{
    executeFloatPointBasicTests<double>();
}


TEST(StringUtilsTest, from_string_long_double)
{
    long double d;
    ASSERT_TRUE(from_string("132048.988654", d));
    from_string("132048.988654", d);
    ASSERT_DOUBLE_EQ(132048.988654, d);
    long double d1;
    from_string("-62.235643", d1);
    ASSERT_DOUBLE_EQ(-62.235643, d1);
}


TEST(StringUtilsTest, ensure_found)
{
    std::string str = "Why?";
    ASSERT_TRUE(ensure_found(str.find_first_of("h", 0)));
    ASSERT_THROW(ensure_found(str.find_first_of(" ", 0)), StringNotFound);
    ASSERT_EQ(str.size(), ensure_found(str.find_first_of(" ", 0), str.size()));
}

TEST(StringUtilsTest, substr)
{
    ASSERT_EQ("llo Wo", substr("Hello World", Pos_(2), Count_(6)));
    ASSERT_EQ("llo W", substr("Hello World", Pos_(2), Pos_(6)));
}