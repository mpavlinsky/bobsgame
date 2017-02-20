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
#include "Gwen/skin/gwen_skin_texturing.h"

#include "Gwen/renderer/gwen_renderer_base.h"
#include "Gwen/renderer/gwen_texture.h"

namespace Gwen
{
namespace Skin
{
namespace Texturing
{

Single::Single()
{
    _texture = nullptr;

    _uv[0] = 0.0f;
    _uv[1] = 0.0f;
    _uv[2] = 0.0f;
    _uv[3] = 0.0f;

    _width = 0;
    _height = 0;
}

void Single::Initialize(Renderer::Texture* texture, int x, int y, unsigned width, unsigned height)
{
    _texture = texture;

    float texw = static_cast<float>(texture->_width);
    float texh = static_cast<float>(texture->_height);

    _uv[0] = x / texw;
    _uv[1] = y / texh;
    _uv[2] = (x + width) / texw;
    _uv[3] = (y + height) / texh;

    _width = width;
    _height = height;
}

void Single::Draw(Gwen::Renderer::Base* render, const Gwen::Rectangle& rectangle, const Gwen::Color& color)
{
    if (!_texture)
    {
        return;
    }

    render->SetDrawColor(color);
    render->DrawTexture(_texture, rectangle, _uv[0], _uv[1], _uv[2], _uv[3]);
}

void Single::DrawCenter(Gwen::Renderer::Base* render, const Gwen::Rectangle& rectangle, const Gwen::Color& color)
{
    if (!_texture)
    {
        return;
    }

    Gwen::Rectangle inner_rectangle = rectangle;
    inner_rectangle._x += (rectangle._width - _width) / 2;
    inner_rectangle._y += (rectangle._height - _height) / 2;
    inner_rectangle._width = _width;
    inner_rectangle._height = _height;

    Draw(render, rectangle, color);
}

Bordered::Bordered()
{
    _texture = nullptr;

    _width = 0;
    _height = 0;
}

void Bordered::Initialize(Renderer::Texture* texture, int x, int y, unsigned width, unsigned height, const Margin& margin)
{
    _texture = texture;
    _margin = margin;
    _width = width;
    _height = height;

    // Calculate the texture coordinates of the sub rectangles.
    _SetSubRectangle(0, x, y, _margin._left, _margin._top);
    _SetSubRectangle(1, x + _margin._left, y, _width - _margin._left - _margin._right, _margin._top);
    _SetSubRectangle(2, (x + _width) - _margin._right, y, _margin._right, _margin._top);
    _SetSubRectangle(3, x, y + _margin._top, _margin._left, _height - _margin._top - _margin._bottom);
    _SetSubRectangle(4, x + _margin._left,  y + _margin._top, _width - _margin._left - _margin._right, _height - _margin._top - _margin._bottom);
    _SetSubRectangle(5, (x + _width) - _margin._right,  y + _margin._top, _margin._right, _height - _margin._top - _margin._bottom);
    _SetSubRectangle(6, x, (y + _height) - _margin._bottom, _margin._left, _margin._bottom);
    _SetSubRectangle(7, x + _margin._left, (y + _height) - _margin._bottom, _width - _margin._left - _margin._right, _margin._bottom);
    _SetSubRectangle(8, (x + _width) - _margin._right, (y + _height) - _margin._bottom, _margin._right, _margin._bottom);
}

void Bordered::Draw(Gwen::Renderer::Base* render, const Gwen::Rectangle& rectangle, const Gwen::Color& color, unsigned sub_rectangle_index)
{
    if (!_texture)
    {
        return;
    }

    render->SetDrawColor(color);

    // Draw which sub rectangles?
    if (sub_rectangle_index & (1 << 0))
    {
        _DrawSubRectangle(render, 0,
                          rectangle._x,
                          rectangle._y,
                          _margin._left,
                          _margin._top);
    }

    if (sub_rectangle_index & (1 << 1))
    {
        _DrawSubRectangle(render, 1,
                          rectangle._x + _margin._left,
                          rectangle._y,
                          rectangle._width - _margin._left - _margin._right,
                          _margin._top);
    }

    if (sub_rectangle_index & (1 << 2))
    {
        _DrawSubRectangle(render, 2,
                          rectangle._x + rectangle._width - _margin._right,
                          rectangle._y,
                          _margin._right,
                          _margin._top);
    }

    if (sub_rectangle_index & (1 << 3))
    {
        _DrawSubRectangle(render, 3,
                          rectangle._x,
                          rectangle._y + _margin._top,
                          _margin._left,
                          rectangle._height - _margin._top - _margin._bottom);
    }

    if (sub_rectangle_index & (1 << 4))
    {
        _DrawSubRectangle(render, 4,
                          rectangle._x + _margin._left,
                          rectangle._y + _margin._top,
                          rectangle._width - _margin._left - _margin._right,
                          rectangle._height - _margin._top - _margin._bottom);
    }

    if (sub_rectangle_index & (1 << 5))
    {
        _DrawSubRectangle(render, 5,
                          rectangle._x + rectangle._width - _margin._right,
                          rectangle._y + _margin._top,
                          _margin._right,
                          rectangle._height - _margin._top - _margin._bottom);
    }

    if (sub_rectangle_index & (1 << 6))
    {
        _DrawSubRectangle(render, 6,
                          rectangle._x,
                          rectangle._y + rectangle._height - _margin._bottom,
                          _margin._left,
                          _margin._bottom);
    }

    if (sub_rectangle_index & (1 << 7))
    {
        _DrawSubRectangle(render, 7,
                          rectangle._x + _margin._left,
                          rectangle._y + rectangle._height - _margin._bottom,
                          rectangle._width - _margin._left - _margin._right,
                          _margin._bottom);
    }

    if (sub_rectangle_index & (1 << 8))
    {
        _DrawSubRectangle(render, 8,
                          rectangle._x + rectangle._width - _margin._right,
                          rectangle._y + rectangle._height - _margin._bottom,
                          _margin._right,
                          _margin._bottom);
    }
}

void Bordered::_SetSubRectangle(unsigned sub_rectangle_index, int x, int y, unsigned width, unsigned height)
{
    _sub_rectangles[sub_rectangle_index]._uv[0] = x / static_cast<float>(_texture->_width);
    _sub_rectangles[sub_rectangle_index]._uv[1] = y / static_cast<float>(_texture->_height);
    _sub_rectangles[sub_rectangle_index]._uv[2] = (x + width) / static_cast<float>(_texture->_width);
    _sub_rectangles[sub_rectangle_index]._uv[3] = (y + height) / static_cast<float>(_texture->_height);
}

void Bordered::_DrawSubRectangle(Renderer::Base* render, unsigned sub_rectangle_index, int x, int y, unsigned w, unsigned h)
{
    render->DrawTexture(_texture,
                        Gwen::Rectangle(x, y, w, h),
                        _sub_rectangles[sub_rectangle_index]._uv[0],
                        _sub_rectangles[sub_rectangle_index]._uv[1],
                        _sub_rectangles[sub_rectangle_index]._uv[2],
                        _sub_rectangles[sub_rectangle_index]._uv[3]);
}

Bordered::SubRectangle::SubRectangle()
{
    _uv[0] = 0.0f;
    _uv[1] = 0.0f;
    _uv[2] = 0.0f;
    _uv[3] = 0.0f;
}

}; // namespace Texturing

}; // namespace Skin

}; // namespace Gwen
