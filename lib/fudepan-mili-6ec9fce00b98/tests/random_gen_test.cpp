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

TEST(RandomGenTest, rnd)
{
    const float max = 11.0f;
    const float min = 10.0f;

    Randomizer<float> rnd(min, max);

    for (unsigned int i = 0; i < 100; ++i)
    {
        const float r = rnd.get();
        EXPECT_LE(r, max);
        EXPECT_GE(r, min);
    }
}

TEST(RandomGenTest, rndSameSeed)
{
    const unsigned int max = 20u;
    const unsigned int min = 10u;
    const unsigned int seed = 5u;

    Randomizer<unsigned int> randOne(min, max, seed);
    Randomizer<unsigned int> randTwo(min, max, seed);

    for (unsigned int i(0u); i < 100u; ++i)
    {
        EXPECT_EQ(randOne.get(), randTwo.get());
    }
}

TEST(RandomGenTest, getMethod)
{
    const unsigned int max = 100u;
    const unsigned int min = 1u;
    const unsigned int seed = 20u;

    const unsigned int retrievedValue1 = 15u;
    const unsigned int retrievedValue2 = 66u;
    const unsigned int retrievedValue3 = 64u;
    const unsigned int retrievedValue4 = 41u;
    const unsigned int retrievedValue5 = 25u;

    Randomizer<unsigned int> rnd(min, max, seed);

    EXPECT_EQ(rnd.get(), retrievedValue1);
    EXPECT_EQ(rnd.get(), retrievedValue2);
    EXPECT_EQ(rnd.get(), retrievedValue3);
    EXPECT_EQ(rnd.get(), retrievedValue4);
    EXPECT_EQ(rnd.get(), retrievedValue5);
}
