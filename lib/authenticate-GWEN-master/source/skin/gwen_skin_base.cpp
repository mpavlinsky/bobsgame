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
#include "Gwen/skin/gwen_skin_base.h"

#include "Gwen/Controls/Base.h"

namespace Gwen
{
namespace Skin
{

Base::Base(Gwen::Renderer::Base* renderer)
{
    _default_font._face_name = "Arial";
    _default_font._size = 10.0f;
    _render = renderer;
}

Base::~Base()
{
    ReleaseFont(&_default_font);
}

void Base::SetDefaultFont(const std::string& face_name, float size)
{
    _default_font._face_name = face_name;
    _default_font._size = size;
}

Renderer::Font* Base::GetDefaultFont()
{
    return &_default_font;
}

void Base::ReleaseFont(Renderer::Font* font)
{
    if (!font)
    {
        return;
    }

    if (!_render)
    {
        return;
    }

    _render->FreeFont(font);
}

void Base::SetRender(Gwen::Renderer::Base* renderer)
{
    _render = renderer;
}

Gwen::Renderer::Base* Base::GetRender()
{
    return _render;
}

}; // namesapce Skin

}; // namespace Gwen
