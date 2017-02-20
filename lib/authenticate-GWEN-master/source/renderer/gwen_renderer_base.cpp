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
#include "Gwen/renderer/gwen_renderer_base.h"

#include "Gwen/Utility.h"

namespace Gwen
{
namespace Renderer
{

Base::Base()
{
    _offset = Point(0, 0);
    _clipping_region = Rectangle(0, 0, 0, 0);
}

Base::~Base()
{
}

void Base::Initialize()
{
}

void Base::Begin()
{
}

void Base::End()
{
}

void Base::StartClipping()
{
}

void Base::EndClipping()
{
}

void Base::LoadTexture(Texture*)
{
}

void Base::FreeTexture(Texture*)
{
}

void Base::LoadFont(Font*)
{
}

void Base::FreeFont(Font*)
{
}

void Base::Translate(int& x, int& y)
{
    x += _offset._x;
    y += _offset._y;
}

void Base::Translate(Gwen::Rectangle& rectangle)
{
    Translate(rectangle._x, rectangle._y);
}

void Base::SetRenderOffset(const Gwen::Point& offset)
{
    _offset = offset;
}

void Base::AddRenderOffset(const Gwen::Point& offset)
{
    _offset._x += offset._x;
    _offset._y += offset._y;
}

Gwen::Point Base::GetRenderOffset() const
{
    return _offset;
}

void Gwen::Renderer::Base::SetClippingRegion(const Gwen::Rectangle& rectangle)
{
    _clipping_region = rectangle;
}

void Base::AddClippingRegion(const Gwen::Rectangle& rectangle)
{
    Gwen::Rectangle inner_rectangle = rectangle;

    inner_rectangle._x = _offset._x;
    inner_rectangle._y = _offset._y;
    Gwen::Rectangle out = inner_rectangle;

    if (inner_rectangle._x < _clipping_region._x)
    {
        out._width -= (_clipping_region._x - out._x);
        out._x = _clipping_region._x;
    }

    if (inner_rectangle._y < _clipping_region._y)
    {
        out._height -= (_clipping_region._y - out._y);
        out._y = _clipping_region._y;
    }

    if (inner_rectangle._x + inner_rectangle._width > _clipping_region._x + _clipping_region._width)
    {
        out._width = (_clipping_region._x + _clipping_region._width) - out._x;
    }

    if (inner_rectangle._y + inner_rectangle._height > _clipping_region._y + _clipping_region._height)
    {
        out._height = (_clipping_region._y + _clipping_region._height) - out._y;
    }

    _clipping_region = out;
}

Gwen::Rectangle Base::GetClippingRegion() const
{
    return _clipping_region;
}

bool Base::GetClippingRegionVisible() const
{
    if (_clipping_region._width <= 0 || _clipping_region._height <= 0)
    {
        return false;
    }

    return true;
}

void Base::SetDrawColor(const Color&)
{
}

void Base::DrawRectangle(const Gwen::Rectangle&)
{
}

void Base::FillRectangle(const Gwen::Rectangle&)
{
}

void Base::FillShavedCornerRectangle(const Gwen::Rectangle& rectangle, bool slight)
{
    // Draw inside the width and height.
    Gwen::Rectangle inside_rectangle = rectangle;
    inside_rectangle._width -= 1;
    inside_rectangle._height -= 1;

    if (slight)
    {
        FillRectangle(Rectangle(inside_rectangle._x + 1, inside_rectangle._y, inside_rectangle._width - 1, 1));
        FillRectangle(Rectangle(inside_rectangle._x + 1, inside_rectangle._y + inside_rectangle._height, inside_rectangle._width - 1, 1));
        FillRectangle(Rectangle(inside_rectangle._x, inside_rectangle._y + 1, 1, inside_rectangle._height - 1));
        FillRectangle(Rectangle(inside_rectangle._x + inside_rectangle._width, inside_rectangle._y + 1, 1, inside_rectangle._height - 1));
    }
    else
    {
        DrawPixel(inside_rectangle._x + 1, inside_rectangle._y + 1);
        DrawPixel(inside_rectangle._x + inside_rectangle._width - 1, inside_rectangle._y + 1);
        DrawPixel(inside_rectangle._x + 1, inside_rectangle._y + inside_rectangle._height - 1);
        DrawPixel(inside_rectangle._x + inside_rectangle._width - 1, inside_rectangle._y + inside_rectangle._height - 1);
        FillRectangle(Rectangle(inside_rectangle._x + 2, inside_rectangle._y, inside_rectangle._width - 3, 1));
        FillRectangle(Rectangle(inside_rectangle._x + 2, inside_rectangle._y + inside_rectangle._height, inside_rectangle._width - 3, 1));
        FillRectangle(Rectangle(inside_rectangle._x, inside_rectangle._y + 2, 1, inside_rectangle._height - 3));
        FillRectangle(Rectangle(inside_rectangle._x + inside_rectangle._width, inside_rectangle._y + 2, 1, inside_rectangle._height - 3));
    }
}

void Base::DrawPixel(int x, int y)
{
    FillRectangle(Gwen::Rectangle(x, y, 1, 1));
}

void Base::DrawTexture(Texture*, const Gwen::Rectangle&, float, float, float, float)
{
}

Gwen::Color Base::GetPixelColor(Texture*, unsigned int, unsigned int, const Gwen::Color& default_color) const
{
    return default_color;
}

void Base::DrawErrorTexture(const Gwen::Rectangle& rectangle)
{
    SetDrawColor(Colors::RED);
    FillRectangle(rectangle);
}

void Base::DrawText(Font*, const Gwen::Point&, const std::string&)
{
}

Gwen::Point Base::MeasureText(Font*, const std::string&)
{
    return Point();
}

}; // namespace Renderer

}; // namespace Gwen
