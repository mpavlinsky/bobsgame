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
#include "Gwen/Controls/Label.h"

#include "Gwen/Utility.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(Label, Base)
{
    _font = nullptr;

    _text = new ControlsInternal::Text(this);
    _text->SetFont(GetSkin()->GetDefaultFont());

    SetAlignment(Position::LEFT | Position::TOP);
    SetMouseInputEnabled(false);
    SetSize(200, 20);
}

Label::~Label()
{
    if (_font != nullptr)
    {
        GetSkin()->ReleaseFont(_font);
        delete _font;
        _font = nullptr;
        SetFont(nullptr);
    }

    if (_text != nullptr)
    {
        delete _text;
        _text = nullptr;
    }
}

void Label::SetText(const std::string& text)
{
    _text->SetText(text);
    Redraw();
}

std::string Label::GetText() const
{
    return _text->GetText();
}

void Label::SetFont(std::string name, int size, bool is_bold)
{
    if (_font != nullptr)
    {
        GetSkin()->ReleaseFont(_font);
        delete _font;
        _font = nullptr;
        SetFont(nullptr);
    }

    _font = new Renderer::Font();
    _font->_bold = is_bold;
    _font->_face_name = name;
    _font->_size = static_cast<float>(size);

    SetFont(_font);

    _text->RefreshSize();

    Invalidate();
}

void Label::SetFont(Renderer::Font* font)
{
    _text->SetFont(font);
}

Renderer::Font* Label::GetFont()
{
    return _text->GetFont();
}

void Label::SetTextColor(const Gwen::Color& color)
{
    _text->SetTextColor(color);
}

Gwen::Color Label::GetTextColor() const
{
    return _text->GetTextColor();
}

void Label::SetTextColorOverride(const Gwen::Color& color)
{
    _text->SetTextColorOverride(color);
}

Gwen::Color Label::GetTextColorOverride() const
{
    return _text->GetTextColorOverride();
}

void Label::SetAlignment(int alignment)
{
    SetAlignment(static_cast<Gwen::Position::Position>(alignment));
}

void Label::SetAlignment(const Gwen::Position::Position& alignment)
{
    if (_alignment == alignment)
    {
        return;
    }

    _alignment = alignment;
    Invalidate();
}

Gwen::Position::Position Label::GetAlignment()
{
    return _alignment;
}

void Label::SetWrap(bool do_wrap)
{
    _text->SetWrap(do_wrap);
}

bool Label::GetWrap() const
{
    return _text->GetWrap();
}

void Label::SetTextPadding(const Padding& padding)
{
    _text->SetPadding(padding);

    Invalidate();
}

Padding Label::GetTextPadding() const
{
    return _text->GetPadding();
}

int Label::GetTextLength() const
{
    return _text->GetLength();
}

Gwen::Rectangle Label::GetCharacterPosition(unsigned character) const
{
    return _text->GetCharacterPosition(character);
}

int Label::GetClosestCharacter(const Gwen::Point& point) const
{
    return _text->GetClosestCharacter(point);
}

void Label::SizeToContents()
{
    _text->SetPosition(_padding._left, _padding._top);
    _text->RefreshSize();

    SetSize(_text->Width() + _padding._left + _padding._right,
            _text->Height() + _padding._top + _padding._bottom);
}

void Label::PreDelete(Gwen::Skin::Base* skin)
{
    if (_font)
    {
        skin->ReleaseFont(_font);
        delete _font;
        _font = nullptr;
        SetFont(nullptr);
    }
}

void Label::PostLayout(Skin::Base*)
{
    _text->SetPosition(_alignment, 0, 0);
}

void Label::_OnBoundsChanged(const Gwen::Rectangle& old_bounds)
{
    // Call the base class.
    Base::_OnBoundsChanged(old_bounds);

    if (_text->GetWrap())
    {
        _text->RefreshSize();
        Invalidate();
    }
}

}; // namespace Controls

}; // namespace Gwen
