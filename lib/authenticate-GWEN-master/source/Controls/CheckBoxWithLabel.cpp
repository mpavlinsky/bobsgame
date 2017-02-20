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
#include "Gwen/Controls/CheckBoxWithLabel.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(CheckBoxWithLabel, Base)
{
    _checkbox = new CheckBox(this);
    _checkbox->SetDock(Position::LEFT);
    _checkbox->SetMargin(Margin(0, 2, 2, 2));
    _checkbox->SetTabable(false);

    _label = new LabelClickable(this);
    _label->SetDock(Position::FILL);
    _label->_on_press_left.Add(_checkbox, &CheckBox::OnPressLeft);
    _label->SetTabable(false);

    SetSize(200, 20);
    SetTabable(false);
}

CheckBox* CheckBoxWithLabel::GetCheckbox()
{
    return _checkbox;
}

LabelClickable* CheckBoxWithLabel::GetLabel()
{
    return _label;
}

bool CheckBoxWithLabel::OnKeySpace(bool is_down)
{
    if (!is_down)
    {
        _checkbox->SetChecked(!_checkbox->GetChecked());
    }

    return true;
}

}; // namespace Controls

}; // namespace Gwen
