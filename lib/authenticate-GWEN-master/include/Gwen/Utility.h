//
// GWEN
// Copyright (c) 2013-2015 James Lammlein
// Copyright (c) 2010 Facepunch Studios
//
// This file is part of GWEN.
//
// MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "Gwen/Structures.h"

#include <ostream>
#include <sstream>

namespace Gwen
{
namespace Utility
{

/// \brief Clamps a value.
template <typename T>
T Clamp(T value, T minimum, T maximum)
{
    return value < minimum ? minimum : (value > maximum ? maximum : value);
}

/// \brief Approaches a value.
template <typename T, typename U>
T Approach(T current, T target, U delta)
{
    if (current < target)
    {
        current += delta;
        if (current > target)
        {
            return target;
        }
    }
    else if (current > target)
    {
        current -= delta;
        if (current < target)
        {
            return target;
        }
    }

    return current;
}

/// \brief Converts a variable to a string.
template <typename T>
std::string ToString(const T& value)
{
    std::ostringstream string_stream;
    string_stream << value;
    return string_stream.str();
}

namespace String
{

/// \brief Splits a string.
void Split(const std::string& string, const std::string& seperator, std::vector<std::string>& output, bool leave_seperators = false);

/// \brief Finds a substring within a string.
bool Wildcard(const std::string& wild_card, const std::string& hay_stack);

/// \brief Converts a string to upper case.
void ToUpper(std::string& string);

/// \brief Removes characters from a string.
void Strip(std::string& string, const std::string& characters);

namespace To
{

/// \brief Converts a string to a boolean.
bool Bool(const std::string& string);

/// \brief Converts a string to an integer.
int Int(const std::string& string);

/// \brief Converts a string to a float.
float Float(const std::string& string);

}; // namespace To

}; // namespace String

/// \brief Clamps two rectangles.
Gwen::Rectangle ClampRectangleToRectangle(Gwen::Rectangle inside, Gwen::Rectangle outside, bool clamp_size = false);

}; // namespace Utility

}; // namespace Gwen
