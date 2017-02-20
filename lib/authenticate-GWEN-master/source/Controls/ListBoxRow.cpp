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
#include "Gwen/Controls/ListBoxRow.h"

#include "Gwen/Controls/Layout/TableRow.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(ListBoxRow, Layout::TableRow)
{
    SetColumnCount(1);
    SetHidden(false);
    SetMouseInputEnabled(true);
    SetSelected(false);
}

void ListBoxRow::OnMouseEnter()
{
    // Call the base class function.
    Base::OnMouseEnter();

    _UpdateTextColor();
}

void ListBoxRow::OnMouseLeave()
{
    // Call the base class.
    Base::OnMouseLeave();

    _UpdateTextColor();
}

void ListBoxRow::OnMouseClickLeft(int, int, bool is_down)
{
    if (is_down)
    {
        _DoSelect();
    }
}

void ListBoxRow::OnMouseDoubleClickLeft(int, int)
{
    _DoSelect();
    _on_mouse_double_click_left.Call(this);
}

void ListBoxRow::SetSelected(bool selected)
{
    // Call the base class function.
    TableRow::SetSelected(selected);

    _UpdateTextColor();
}

void ListBoxRow::Render(Skin::Base* skin)
{
    skin->DrawListBoxLine(this, GetSelected(), GetEven());
}

void ListBoxRow::_DoSelect()
{
    SetSelected(true);
    _on_selected.Call(this);
    Redraw();
}

void ListBoxRow::_UpdateTextColor()
{
    //
    // Update the text color.
    //

    if (GetSelected())
    {
        SetTextColor(GetSkin()->Colors.ListBoxRow.Down);
    }
    else if (_hovered_control == this)
    {
        SetTextColor(GetSkin()->Colors.ListBoxRow.Hover);
    }
    else
    {
        SetTextColor(GetSkin()->Colors.ListBoxRow.Normal);
    }
}

}; // namespace Controls

}; // namespace Gwen
