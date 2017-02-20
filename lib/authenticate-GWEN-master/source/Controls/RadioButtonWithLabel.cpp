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
#include "Gwen/Controls/RadioButtonWithLabel.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(RadioButtonWithLabel, Base)
{
    _radio_button = new RadioButton(this);
    _radio_button->SetDock(Position::LEFT);
    _radio_button->SetMargin(Margin(0, 2, 2, 2));
    _radio_button->SetTabable(false);
    _radio_button->SetKeyboardInputEnabled(false);

    _label = new LabelClickable(this);
    _label->SetAlignment(Position::CENTER_V | Position::LEFT);
    _label->SetText("Radio Button");
    _label->SetDock(Position::FILL);
    _label->_on_press_left.Add(_radio_button, &CheckBox::OnPressLeft);
    _label->SetTabable(false);
    _label->SetKeyboardInputEnabled(false);

    SetSize(200, 20);
}

void RadioButtonWithLabel::Select()
{
    _radio_button->SetChecked(true);
}

RadioButton* RadioButtonWithLabel::GetRadioButton()
{
    return _radio_button;
}

LabelClickable* RadioButtonWithLabel::GetLabel()
{
    return _label;
}

bool RadioButtonWithLabel::OnKeySpace(bool is_down)
{
    if (is_down)
    {
        _radio_button->SetChecked(!_radio_button->GetChecked());
    }

    return true;
}

void RadioButtonWithLabel::RenderFocus(Gwen::Skin::Base* skin)
{
    if (Gwen::Controls::_keyboard_focus != this)
    {
        return;
    }

    if (!IsTabable())
    {
        return;
    }

    skin->DrawKeyboardHighlight(this, GetRenderBounds(), 0);
}

}; // namespace Controls

}; // namespace Gwen
