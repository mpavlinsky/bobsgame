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
#include "Gwen/Controls/TextBoxNumeric.h"

#include "Gwen/Utility.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(TextBoxNumeric, TextBox)
{
    SetText("0");
}

float TextBoxNumeric::GetFloat() const
{
    return Gwen::Utility::String::To::Float(GetText());
}

bool TextBoxNumeric::IsTextAllowed(const std::string& text, int position) const
{
    const std::string& current_text = GetText();
    if (text.length() == 0)
    {
        return true;
    }

    for (size_t i = 0; i < text.length(); ++i)
    {
        if (text[i] == '-')
        {
            // It has to be at the start.
            if (i != 0 || position != 0)
            {
                return false;
            }

            // There can only be one.
            if (std::count(current_text.begin(), current_text.end(), '-') > 0)
            {
                return false;
            }

            continue;
        }

        if (text[i] >= '0' && text[i] <= '9')
        {
            continue;
        }

        if (text[i] == '.')
        {
            // Already a fullstop.
            if (std::count(current_text.begin(), current_text.end(), '.') > 0)
            {
                return false;
            }

            continue;
        }

        return false;
    }

    return true;
}

}; // namespace Controls

}; // namespace Gwen
