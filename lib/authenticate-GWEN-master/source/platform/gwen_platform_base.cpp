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
#include "Gwen/platform/gwen_platform_base.h"

#include "Gwen/Macros.h"

namespace Gwen
{
namespace Platform
{

/// \brief A virtual clip board.
static std::string _clipboard;

/// \brief The application start time.
static auto _application_start = std::chrono::system_clock::now().time_since_epoch();

bool SetClipboardText(const std::string& text)
{
    _clipboard = text;
    return true;
}

std::string GetClipboardText()
{
    return _clipboard;
}

Point GetCursorPosition()
{
    return Point();
}

Rectangle GetDesktopSize()
{
    return Rectangle();
}

float GetTimeInSeconds()
{
    auto now = std::chrono::system_clock::now().time_since_epoch();
    long long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();

    milliseconds -= std::chrono::duration_cast<std::chrono::milliseconds>(_application_start).count();

    return static_cast<float>(milliseconds * 0.001f);
}

long long GetTimeInMilliseconds()
{
    auto now = std::chrono::system_clock::now().time_since_epoch();
    long long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();

    milliseconds -= std::chrono::duration_cast<std::chrono::milliseconds>(_application_start).count();

    return milliseconds;
}

}; // namespace Platform

}; // namespace Gwen
