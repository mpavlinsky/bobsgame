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

#include "Gwen.h"
#include "Gwen/Utility.h"

#include "Gwen/Controls/Base.h"

namespace Gwen
{
namespace Utility
{

void String::Split(const std::string& string, const std::string& seperator, std::vector<std::string>& output, bool leave_seperators)
{
    size_t offset = 0;
    size_t length = string.length();
    size_t seperator_length = seperator.length();
    size_t i = string.find(seperator, 0);

    while (i != std::string::npos)
    {
        output.push_back(string.substr(offset, i - offset));
        offset = i + seperator_length;
        i = string.find(seperator, offset);

        if (leave_seperators)
        {
            offset -= seperator_length;
        }
    }

    output.push_back(string.substr(offset, length - offset));
}

bool String::Wildcard(const std::string& wild_card, const std::string& hay_stack)
{
    if (wild_card == "*")
    {
        return true;
    }

    size_t position = wild_card.find("*", 0);
    if (position == std::string::npos)
    {
        return wild_card == hay_stack;
    }

    // The first half matches.
    if (position > 0 && wild_card.substr(0, position) != hay_stack.substr(0, position))
    {
        return false;
    }

    // The second half matches.
    if (position != wild_card.length() - 1)
    {
        std::string end = wild_card.substr(position + 1, wild_card.length());
        if (end != hay_stack.substr(hay_stack.length() - end.length(), hay_stack.length()))
        {
            return false;
        }
    }

    return true;
}

void String::ToUpper(std::string& string)
{
    transform(string.begin(), string.end(), string.begin(), toupper);
}

void String::Strip(std::string& string, const std::string& characters)
{
    std::string source = string;
    string = "";

    for (unsigned int i = 0; i < source.length(); ++i)
    {
        if (characters.find(source[i]) != std::string::npos)
        {
            continue;
        }

        string += source[i];
    }
}

bool String::To::Bool(const std::string& string)
{
    if (string.size() == 0)
    {
        return false;
    }

    if (string[0] == 'T' || string[0] == 't' || string[0] == 'y' || string[0] == 'Y')
    {
        return true;
    }

    if (string[0] == 'F' || string[0] == 'f' || string[0] == 'n' || string[0] == 'N')
    {
        return false;
    }

    if (string[0] == '0')
    {
        return false;
    }

    return true;
}

int String::To::Int(const std::string& string)
{
    if (string == "")
    {
        return 0;
    }

    return atoi(string.c_str());
}

float String::To::Float(const std::string& string)
{
    if (string == "")
    {
        return 0.0f;
    }

    return static_cast<float>(atof(string.c_str()));
}

Gwen::Rectangle ClampRectangleToRectangle(Gwen::Rectangle inside, Gwen::Rectangle outside, bool clamp_size)
{
    if (inside._x < outside._x)
    {
        inside._x = outside._x;
    }

    if (inside._y  < outside._y)
    {
        inside._y = outside._y;
    }

    if (inside._x + inside._width > outside._x + outside._width)
    {
        if (clamp_size)
        {
            inside._width = outside._width;
        }
        else
        {
            inside._x = outside._x + outside._width - inside._width;
        }
    }

    if (inside._y + inside._height > outside._y + outside._height)
    {
        if (clamp_size)
        {
            inside._height = outside._height;
        }
        else
        {
            inside._y = outside._width + outside._height - inside._height;
        }
    }

    return inside;
}

}; // namespace Utility

}; // namespace Gwen
