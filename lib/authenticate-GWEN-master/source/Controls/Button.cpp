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
#include "Gwen/Controls/Button.h"

#include "Gwen/Controls/ImagePanel.h"
#include "Gwen/skin/gwen_skin_base.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(Button, Label)
{
    _image = nullptr;
    _depressed = false;
    _center = false;
    _toggle_state = false;

    SetAlignment(Position::CENTER);
    SetKeyboardInputEnabled(false);
    SetMouseInputEnabled(true);
    SetSize(100, 20);
    SetTabable(false);
    SetTextPadding(Padding(3, 0, 3, 0));
    SetToggle(false);
}

Button::~Button()
{
    if (_image != nullptr)
    {
        delete _image;
        _image = nullptr;
    }
}

void Button::SetDepressed(bool is_depressed)
{
    if (_depressed == is_depressed)
    {
        return;
    }

    _depressed = is_depressed;
    Redraw();
}

bool Button::GetDepressed() const
{
    return _depressed;
}

void Button::SetToggle(bool is_toggle)
{
    _toggle = is_toggle;
}

bool Button::GetToggle() const
{
    return _toggle;
}

void Button::SetToggleState(bool toggle_state)
{
    if (_toggle_state == toggle_state)
    {
        return;
    }

    _toggle_state = toggle_state;
    _on_toggle.Call(this);

    if (_toggle_state)
    {
        _on_toggle_on.Call(this);
    }
    else
    {
        _on_toggle_off.Call(this);
    }

    Redraw();
}

bool Button::GetToggleState() const
{
    return _toggle_state;
}

void Button::Toggle()
{
    SetToggleState(!GetToggleState());
}

void Button::SetImage(const std::string& name, bool center)
{
    if (name.empty())
    {
        if (_image)
        {
            delete _image;
            _image = nullptr;
        }

        return;
    }

    if (!_image)
    {
        _image = new ImagePanel(this);
    }

    _image->SetImageName(name);
    _image->SizeToContents();
    _image->SetMargin(Margin(2, 0, 2, 0));
    _center = center;

    Padding padding = GetTextPadding();
    padding._left = _image->Right() + 2;
    SetTextPadding(padding);
}

void Button::SetImageAlpha(float alpha)
{
    if (!_image)
    {
        return;
    }

    _image->SetDrawColor(Gwen::Color(255, 255, 255, static_cast<unsigned char>(255.0f * alpha)));
}

void Button::UpdateColors()
{
    if (IsDisabled())
    {
        return SetTextColor(GetSkin()->Colors.Button.Disabled);
    }

    if (GetDepressed() || GetToggleState())
    {
        return SetTextColor(GetSkin()->Colors.Button.Down);
    }

    if (IsHovered())
    {
        return SetTextColor(GetSkin()->Colors.Button.Hover);
    }

    SetTextColor(GetSkin()->Colors.Button.Normal);
}

void Button::OnPressLeft()
{
    if (GetToggle())
    {
        SetToggleState(!GetToggleState());
    }

    _on_press_left.Call(this);
}

void Button::OnPressRight()
{
    _on_press_right.Call(this);
}

void Button::SizeToContents()
{
    Label::SizeToContents();

    if (_image)
    {
        int height = _image->Height() + 4;
        if (Height() < height)
        {
            SetHeight(height);
        }
    }
}

void Button::OnMouseClickLeft(int, int , bool is_down)
{
    if (IsDisabled())
    {
        return;
    }

    if (is_down)
    {
        SetDepressed(true);
        Gwen::Controls::_mouse_focus = this;
        _on_down.Call(this);
    }
    else
    {
        if (IsHovered() && _depressed)
        {
            OnPressLeft();
        }

        SetDepressed(false);
        Gwen::Controls::_mouse_focus = nullptr;
        _on_up.Call(this);
    }
}

void Button::OnMouseClickRight(int, int, bool is_down)
{
    if (IsDisabled())
    {
        return;
    }

    if (is_down)
    {
        SetDepressed(true);
        Gwen::Controls::_mouse_focus = this;
        _on_down.Call(this);
    }
    else
    {
        if (IsHovered() && _depressed)
        {
            OnPressRight();
        }

        SetDepressed(false);
        Gwen::Controls::_mouse_focus = nullptr;
        _on_up.Call(this);
    }
}

void Button::OnMouseDoubleClickLeft(int x, int y)
{
    if (IsDisabled())
    {
        return;
    }

    OnMouseClickLeft(x, y, true);
    _on_mouse_double_click_left.Call(this);
}

void Button::OnMouseDoubleClickRight(int x, int y)
{
    if (IsDisabled())
    {
        return;
    }

    OnMouseClickRight(x, y, true);
    _on_mouse_double_click_right.Call(this);
}

void Button::PostLayout(Skin::Base* skin)
{
    Label::PostLayout(skin);

    if (_image)
    {
        if (_center)
        {
            _image->SetPosition(Position::CENTER, 0, 0);
        }
        else
        {
            _image->SetPosition(static_cast<Gwen::Position::Position>(Position::LEFT | Position::CENTER_V), 0, 0);
        }
    }
}

void Button::Render(Skin::Base* skin)
{
    if (!GetShouldDrawBackground())
    {
        return;
    }

    bool draw_depressed = GetDepressed();
    if (GetToggle())
    {
        draw_depressed = draw_depressed || GetToggleState();
    }

    skin->DrawButton(this, draw_depressed, IsHovered(), IsDisabled());
}

}; // namespace Controls

}; // namespace Gwen
