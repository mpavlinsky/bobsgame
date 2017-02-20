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
#include "Gwen/Controls/ImagePanel.h"

#include "Gwen/renderer/gwen_renderer_base.h"
#include "Gwen/Controls/Base.h"
#include "Gwen/renderer/gwen_texture.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(ImagePanel, Base)
{
    _draw_color = Colors::WHITE;

    SetMouseInputEnabled(false);
    SetStretch(true);
    SetUV(0.0f, 0.0f, 1.0f, 1.0f);
}

ImagePanel::~ImagePanel()
{
    _texture.Release(GetSkin()->GetRender());
}

void ImagePanel::SetImageName(const std::string& name)
{
    _texture.Load(name, GetSkin()->GetRender());
}

std::string ImagePanel::GetImageName() const
{
    return _texture._name;
}

void ImagePanel::SetStretch(bool stretch)
{
    _stretch = stretch;
}

bool ImagePanel::GetStretch() const
{
    return _stretch;
}

void ImagePanel::SetUV(float u1, float v1, float u2, float v2)
{
    _uv[0] = u1;
    _uv[1] = v1;
    _uv[2] = u2;
    _uv[3] = v2;
}

void ImagePanel::SetDrawColor(const Gwen::Color& color)
{
    _draw_color = color;
}

unsigned ImagePanel::GetTextureWidth()
{
    return _texture._width;
}

unsigned ImagePanel::GetTextureHeight()
{
    return _texture._height;
}

void ImagePanel::SizeToContents()
{
    SetSize(_texture._width, _texture._height);
}

bool ImagePanel::FailedToLoad()
{
    return _texture.FailedToLoad();
}

void ImagePanel::Render(Skin::Base* skin)
{
    skin->GetRender()->SetDrawColor(_draw_color);

    if (_stretch)
    {
        skin->GetRender()->DrawTexture(&_texture, GetRenderBounds(), _uv[0], _uv[1], _uv[2], _uv[3]);
    }
    else
    {
        skin->GetRender()->DrawTexture(&_texture, Gwen::Rectangle(0, 0, _texture._width, _texture._height), _uv[0], _uv[1], _uv[2], _uv[3]);
    }
}

}; // namespace Controls

}; // namespace Gwen
