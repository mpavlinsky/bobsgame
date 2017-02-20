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

class Mock
{
public:
    MOCK_METHOD1(mocked_set_celsius, void(float));
    MOCK_CONST_METHOD0(mocked_get_celsius, void());
};

class TemperatureSensor
{
private:
    float get_celsius() const
    {
        mock.mocked_get_celsius();
        return _celsius;
    };

    void set_celsius(float val)
    {
        _celsius = val;
        mock.mocked_set_celsius(val);
    }

public:
    PROPERTIES
    {
        PropertyRW<TemperatureSensor, float, &TemperatureSensor::get_celsius, &TemperatureSensor::set_celsius>   celsius;
    };
    Mock mock;
private:
    float _celsius;
};

TEST(Properties, test)
{
    TemperatureSensor s;
    EXPECT_CALL(s.mock, mocked_set_celsius(0));
    s.celsius = 0;
    EXPECT_CALL(s.mock, mocked_get_celsius());
    float f = s.celsius;
    ASSERT_EQ(f, 0);
}
