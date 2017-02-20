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
#include "Gwen/Controls/MenuItem.h"

#include "Gwen/Controls/Menu.h"
#include "Gwen/Controls/MenuItemRightArrow.h"
#include "Gwen/Controls/Canvas.h"
#include "Gwen/skin/gwen_skin_base.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(MenuItem, Button)
{
    _menu = nullptr;
    _submenu_arrow = nullptr;
    _accelerator = nullptr;

    SetCheckable(false);
    SetChecked(false);
    SetOnStrip(false);
    SetTabable(false);
    SetToggle(true);

    Gwen::Skin::Base* skin = GetSkin();
    assert(skin != nullptr);
    if (skin != nullptr)
    {
        SetTextColor(skin->Colors.Menu.Normal);
    }
}

void MenuItem::Layout(Skin::Base* skin)
{
    // Call the base class.
    Button::Layout(skin);

    if (_submenu_arrow)
    {
        _submenu_arrow->SetPosition(static_cast<Gwen::Position::Position>(Position::LEFT | Position::CENTER_V), 128, 0);
    }
}

void MenuItem::SetOnStrip(bool on_strip)
{
    _on_strip = on_strip;
}

bool MenuItem::GetOnStrip() const
{
    return _on_strip;
}

void MenuItem::SetCheckable(bool checkable)
{
    _checkable = checkable;
}

bool MenuItem::GetCheckable() const
{
    return _checkable;
}

void MenuItem::SetChecked(bool checked)
{
    if (checked == _checked)
    {
        return;
    }

    _checked = checked;
    _on_check_changed.Call(this);

    if (checked)
    {
        _on_checked.Call(this);
    }
    else
    {
        _on_unchecked.Call(this);
    }
}

bool MenuItem::GetChecked() const
{
    return _checked;
}

Menu* MenuItem::GetMenu()
{
    if (!_menu)
    {
        _menu = new Menu(GetCanvas());
        _menu->SetHidden(true);

        if (!_on_strip)
        {
            _submenu_arrow = new ControlsInternal::MenuItemRightArrow(this);
            _submenu_arrow->SetSize(15, 15);
        }

        Invalidate();
    }

    return _menu;
}

void MenuItem::UpdateColors()
{
    if (GetDepressed() || _hovered_control == this || GetOpen())
    {
        SetTextColor(GetSkin()->Colors.Menu.Hover);
    }
    else
    {
        SetTextColor(GetSkin()->Colors.Menu.Normal);
    }
}

void MenuItem::OnPressLeft()
{
    // Do the menu item logic before the base class.
    if (_menu)
    {
        Toggle();
    }
    else if (!_on_strip)
    {
        SetChecked(!GetChecked());
        _on_selected.Call(this);
        GetCanvas()->CloseMenus();
    }

    // Call the base class.
    Button::OnPressLeft();
}

void MenuItem::SizeToContents()
{
    // Call the base class.
    Button::SizeToContents();

    if (_accelerator)
    {
        _accelerator->SizeToContents();
        SetWidth(Width() + _accelerator->Width());
    }
}

void MenuItem::SetAccelerator(const std::string& accelerator)
{
    // Create the accelerator label.
    if (_accelerator)
    {
        _accelerator->DelayedDelete();
        _accelerator = nullptr;
    }

    if (accelerator.empty())
    {
        return;
    }

    _accelerator = new Controls::Label(this);
    _accelerator->SetDock(Position::RIGHT);
    _accelerator->SetAlignment(Position::RIGHT | Position::CENTER_V);
    _accelerator->SetText(accelerator);
    _accelerator->SetMargin(Margin(0, 0, 16, 0));

    // Add an accelerator to handle the left mouse button press event.
    AddAccelerator(accelerator, &Button::OnPressLeft);
}

bool MenuItem::GetMenuComponent()
{
    return true;
}

void MenuItem::Open()
{
    // Sanity.
    if (!_menu)
    {
        return;
    }

    // Open the menu.
    _menu->Open();

    // Update the position.
    Gwen::Point point = LocalPositionToCanvas(Gwen::Point(0, 0));

    // Strip menus open downwards.
    if (_on_strip)
    {
        _menu->SetPosition(point._x, point._y + Height() + 1);
    }
    // Submenus open sideways.
    else
    {
        _menu->SetPosition(point._x + Width(), point._y);
    }

    // Update the text color of the menu item.
    UpdateColors();
}

void MenuItem::Close()
{
    // Sanity.
    if (!_menu)
    {
        return;
    }

    // Close the menu.
    _menu->CloseMenus();

    // Update the text color of the menu item.
    UpdateColors();
}

void MenuItem::Toggle()
{
    if (GetOpen())
    {
        Close();
    }
    else
    {
        Open();
    }
}

bool MenuItem::GetOpen() const
{
    if (!_menu)
    {
        return false;
    }

    return !_menu->Hidden();
}

void MenuItem::CloseMenus()
{
    Close();
}

void MenuItem::Render(Skin::Base* skin)
{
    skin->DrawMenuItem(this, GetOpen(), _checkable ? _checked : false);

    if (_accelerator)
    {
        _accelerator->SetTextColorOverride(GetTextColor());
    }
}

}; // namespace Controls

}; // namespace Gwen
