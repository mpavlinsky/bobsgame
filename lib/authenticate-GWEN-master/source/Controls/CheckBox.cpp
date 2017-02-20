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
#include "Gwen/Controls/CheckBox.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(CheckBox, Button)
{
    _is_checked = true;

    SetSize(15, 15);
    Toggle();
}

void CheckBox::SetChecked(bool is_checked)
{
    if (_is_checked == is_checked)
    {
        return;
    }

    _is_checked = is_checked;
    OnChecked();
}

bool CheckBox::GetChecked() const
{
    return _is_checked;
}

void CheckBox::Toggle()
{
    SetChecked(!GetChecked());
}

void CheckBox::OnChecked()
{
    if (GetChecked())
    {
        _on_checked.Call(this);
    }
    else
    {
        _on_unchecked.Call(this);
    }

    _on_check_changed.Call(this);
}

void CheckBox::OnPressLeft()
{
    if (IsDisabled())
    {
        return;
    }

    if (GetChecked() && !AllowUncheck())
    {
        return;
    }

    Toggle();

    _on_press_left.Call(this);
}

void CheckBox::Render(Skin::Base* skin)
{
    skin->DrawCheckBox(this, _is_checked);
}

bool CheckBox::AllowUncheck() const
{
    return true;
}

}; // namespace Controls

}; // namespace Gwen
