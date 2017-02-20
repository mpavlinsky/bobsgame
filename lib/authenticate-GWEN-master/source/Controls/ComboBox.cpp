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
#include "Gwen/Controls/ComboBox.h"

#include "Gwen/Controls/Canvas.h"
#include "Gwen/Controls/ComboBoxDownArrow.h"
#include "Gwen/Controls/Menu.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(ComboBox, Button)
{
    _menu = new Menu(this);
    _menu->SetHidden(true);
    _menu->SetIconMarginDisabled(true);
    _menu->SetTabable(false);

    ControlsInternal::ComboBoxDownArrow* down_arrow = new ControlsInternal::ComboBoxDownArrow(this);
    down_arrow->SetComboBox(this);

    _button = down_arrow;
    _selected_item = nullptr;

    SetAlignment(Position::LEFT | Position::CENTER_V);
    SetKeyboardInputEnabled(true);
    SetMargin(Margin(3, 0, 0, 0));
    SetSize(100, 20);
    SetTabable(true);
    SetText("");
    SetTextPadding(Padding(4, 0, 0, 0));
}

MenuItem* ComboBox::AddItem(const std::string& label, const std::string& name)
{
    MenuItem* item = _menu->AddItem(label, "");
    item->SetName(name);
    item->SetTextPadding(Padding(2, 0, 0, 0));
    item->_on_selected.Add(this, &ComboBox::OnItemSelected);

    if (_selected_item == nullptr)
    {
        OnItemSelected(item);
    }

    return item;
}

void ComboBox::Clear()
{
    if (_menu)
    {
        _menu->Clear();
    }
}

void ComboBox::SelectItem(MenuItem* item, bool do_events)
{
    if (_selected_item == item)
    {
        return;
    }

    _selected_item = item;
    SetText(_selected_item->GetText());
    _menu->SetHidden(true);
    Invalidate();

    if (do_events)
    {
        _on_selected.Call(this);
        Focus();
    }
}

void ComboBox::SelectItemByName(const std::string& name, bool do_events)
{
    std::list<Base*>& children = _menu->GetChildren();
    auto begin = children.begin();
    while (begin != children.end())
    {
        MenuItem* child = dynamic_cast<MenuItem*>(*begin);

        if (child->GetName() == name)
        {
            return SelectItem(child, do_events);
        }

        ++begin;
    }
}

Gwen::Controls::Label* ComboBox::GetSelectedItem()
{
    return _selected_item;
}

void ComboBox::UpdateColors()
{
    if (!GetShouldDrawBackground())
    {
        return SetTextColor(GetSkin()->Colors.Button.Normal);
    }

    Button::UpdateColors();
}

void ComboBox::OnItemSelected(Controls::Base* control)
{
    // Convert selected to a menu item
    MenuItem* item = dynamic_cast<MenuItem*>(control);
    if (!item)
    {
        return;
    }

    SelectItem(item);
}

void ComboBox::OnPressLeft()
{
    if (GetOpen())
    {
        return GetCanvas()->CloseMenus();
    }

    GetCanvas()->CloseMenus();
    bool was_menu_hidden = _menu->Hidden();
    if (was_menu_hidden)
    {
        Open();
    }
}

bool ComboBox::OnKeyUp(bool is_down)
{
    if (is_down)
    {
        std::list<Base*>& children = _menu->GetChildren();
        auto i = std::find(children.rbegin(), children.rend(), _selected_item);
        if (i != children.rend() && (++i != children.rend()))
        {
            Base* up_element = *i;
            OnItemSelected(up_element);
        }
    }

    return true;
}

bool ComboBox::OnKeyDown(bool is_down)
{
    if (is_down)
    {
        std::list<Base*>& children = _menu->GetChildren();
        auto i = std::find(children.begin(), children.end(), _selected_item);
        if (i != children.end() && (++i != children.end()))
        {
            Base* down_element = *i;
            OnItemSelected(down_element);
        }
    }

    return true;
}

void ComboBox::OnKeyboardFocus()
{
    SetTextColor(Color(0, 0, 0, 255));
}

void ComboBox::OnLostkeyboardFocus()
{
    SetTextColor(Color(0, 0, 0, 255));
}

void ComboBox::Layout(Skin::Base* skin)
{
    // Call the base class.
    Button::Layout(skin);

    _button->SetPosition(static_cast<Gwen::Position::Position>(Position::RIGHT | Position::CENTER_V), 4, 0);
}


bool ComboBox::GetMenuComponent()
{
    return true;
}

void ComboBox::Open()
{
    if (!_menu)
    {
        return;
    }

    _menu->SetParent(GetCanvas());
    _menu->SetHidden(false);
    _menu->BringToFront();

    Gwen::Point point = LocalPositionToCanvas(Gwen::Point(0, 0));
    _menu->SetBounds(Gwen::Rectangle(point._x, point._y + Height(), Width(), _menu->Height()));
}

void ComboBox::Close()
{
    if (!_menu)
    {
        return;
    }

    _menu->Hide();
}

void ComboBox::CloseMenus()
{
    Close();
}

bool ComboBox::GetOpen()
{
    return _menu && !_menu->Hidden();
}

void ComboBox::Render(Skin::Base* skin)
{
    if (!GetShouldDrawBackground())
    {
        return;
    }

    skin->DrawComboBox(this, GetDepressed(), GetOpen());
}

}; // namespace Controls

}; // namespace Gwen
