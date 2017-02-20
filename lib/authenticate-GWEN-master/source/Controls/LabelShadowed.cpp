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
#include "Gwen/Controls/LabelShadowed.h"

#include "Gwen/Utility.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(LabelShadowed, Base)
{
    _font = nullptr;

    _shadow_offset = Gwen::Point(0, 0);

    _text_shadow = new ControlsInternal::Text(this);
    _text_shadow->SetFont(GetSkin()->GetDefaultFont());

    _text = new ControlsInternal::Text(this);
    _text->SetFont(GetSkin()->GetDefaultFont());

    SetAlignment(Position::LEFT | Position::TOP);
    SetMouseInputEnabled(false);
    SetSize(200, 20);

    SetTextColor(GetSkin()->Colors.LabelShadowed.Text);
    SetShadowColor(GetSkin()->Colors.LabelShadowed.Shadow);
    SetShadowOffset(Gwen::Point(1, 1));
}

LabelShadowed::~LabelShadowed()
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

    if (_text_shadow != nullptr)
    {
        delete _text_shadow;
        _text_shadow = nullptr;
    }
}

void LabelShadowed::SetText(const std::string& text)
{
    _text->SetText(text);
    _text_shadow->SetText(text);
    Redraw();
}

std::string LabelShadowed::GetText() const
{
    return _text->GetText();
}

void LabelShadowed::SetFont(std::string name, int size, bool is_bold)
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
    _text_shadow->RefreshSize();

    Invalidate();
}

void LabelShadowed::SetFont(Renderer::Font* font)
{
    _text->SetFont(font);
    _text_shadow->SetFont(font);
}

Renderer::Font* LabelShadowed::GetFont()
{
    return _text->GetFont();
}

void LabelShadowed::SetTextColor(const Gwen::Color& color)
{
    _text->SetTextColor(color);
}

Gwen::Color LabelShadowed::GetTextColor() const
{
    return _text->GetTextColor();
}

void LabelShadowed::SetShadowColor(const Gwen::Color& color)
{
    _text_shadow->SetTextColor(color);
}

Gwen::Color LabelShadowed::GetShadowColor() const
{
    return _text_shadow->GetTextColor();
}

void LabelShadowed::SetShadowOffset(const Gwen::Point& offset)
{
    if (_shadow_offset == offset)
    {
        return;
    }

    _shadow_offset = offset;
    Invalidate();
}

Gwen::Point LabelShadowed::GetShadowOffset() const
{
    return _text_shadow->GetPosition();
}

void LabelShadowed::SetAlignment(int alignment)
{
    SetAlignment(static_cast<Gwen::Position::Position>(alignment));
}

void LabelShadowed::SetAlignment(const Gwen::Position::Position& alignment)
{
    if (_alignment == alignment)
    {
        return;
    }

    _alignment = alignment;
    Invalidate();
}

Gwen::Position::Position LabelShadowed::GetAlignment()
{
    return _alignment;
}

void LabelShadowed::SetWrap(bool do_wrap)
{
    _text->SetWrap(do_wrap);
    _text_shadow->SetWrap(do_wrap);
}

bool LabelShadowed::GetWrap() const
{
    return _text->GetWrap();
}

void LabelShadowed::SetTextPadding(const Padding& padding)
{
    _text->SetPadding(padding);
    _text_shadow->SetPadding(padding);

    Invalidate();
}

Padding LabelShadowed::GetTextPadding() const
{
    return _text->GetPadding();
}

int LabelShadowed::GetTextLength() const
{
    return _text->GetLength();
}

Gwen::Rectangle LabelShadowed::GetCharacterPosition(unsigned character) const
{
    return _text->GetCharacterPosition(character);
}

int LabelShadowed::GetClosestCharacter(const Gwen::Point& point) const
{
    return _text->GetClosestCharacter(point);
}

void LabelShadowed::SizeToContents()
{
    _text->SetPosition(_padding._left, _padding._top);
    _text->RefreshSize();

    _text_shadow->SetPosition(_padding._left + _shadow_offset._x,
                              _padding._top + _shadow_offset._y);
    _text_shadow->RefreshSize();

    SetSize(_text->Width() + _padding._left + _padding._right,
            _text->Height() + _padding._top + _padding._bottom);
}

void LabelShadowed::PreDelete(Gwen::Skin::Base* skin)
{
    if (_font)
    {
        skin->ReleaseFont(_font);
        delete _font;
        _font = nullptr;
        SetFont(nullptr);
    }
}

void LabelShadowed::PostLayout(Skin::Base*)
{
    _text->SetPosition(_alignment, 0, 0);
    _text_shadow->SetPosition(_alignment, 0, 0);

    Gwen::Point position = _text_shadow->GetPosition();
    _text_shadow->SetPosition(position._x + _shadow_offset._x,
                              position._y + _shadow_offset._y);
}

void LabelShadowed::_OnBoundsChanged(const Gwen::Rectangle& old_bounds)
{
    // Call the base class.
    Base::_OnBoundsChanged(old_bounds);

    if (_text->GetWrap())
    {
        _text->RefreshSize();
        Invalidate();
    }

    if (_text_shadow->GetWrap())
    {
        _text_shadow->RefreshSize();
        Invalidate();
    }
}

}; // namespace Controls

}; // namespace Gwen
