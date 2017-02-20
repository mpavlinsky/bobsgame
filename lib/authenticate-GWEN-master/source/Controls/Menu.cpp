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
#include "Gwen/Controls/Menu.h"

#include "Gwen/Controls/Canvas.h"
#include "Gwen/Controls/MenuDivider.h"
#include "Gwen/input/gwen_input_base.h"
#include "Gwen/skin/gwen_skin_base.h"
#include "Gwen/Utility.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(Menu, ScrollControl)
{
    SetBounds(0, 0, 10, 10);
    SetDeleteOnClose(false);
    SetIconMarginDisabled(false);
    SetPadding(Padding(0, 0, 0, 0));
    _SetScrollBarHidden(true);
}

void Menu::Layout(Skin::Base* skin)
{
    // Call the base class.
    ScrollControl::Layout(skin);

    int children_height = 0;

    for (auto i = _inner_panel->GetChildren().begin(); i != _inner_panel->GetChildren().end(); ++i)
    {
        Base* child = (*i);
        assert(child != nullptr);
        if (child != nullptr)
        {
            children_height += child->Height();
        }
    }

    if (Y() + children_height > GetCanvas()->Height())
    {
        children_height = GetCanvas()->Height() - Y();
    }

    SetSize(Width(), children_height);
}

MenuItem* Menu::AddItem(const std::string& name, const std::string& icon_name, const std::string& accelerator)
{
    MenuItem* item = new MenuItem(this);
    item->SetPadding(Padding(2, 4, 4, 4));
    item->SetText(name);
    item->SetImage(icon_name);
    item->SetAccelerator(accelerator);

    _OnAddItem(item);

    return item;
}

void Menu::AddDivider()
{
    MenuDivider* divider = new MenuDivider(this);
    divider->SetDock(Position::TOP);
    divider->SetMargin(Margin(GetIconMarginDisabled() ? 0 : 24, 0, 4, 0));
}

void Menu::Clear()
{
    for (auto i = _inner_panel->GetChildren().begin(); i != _inner_panel->GetChildren().end(); ++i)
    {
        Base* child = *i;
        assert(child != nullptr);
        if (child != nullptr)
        {
            child->DelayedDelete();
        }
    }
}

void Menu::SetIconMarginDisabled(bool is_disabled)
{
    _disable_icon_margin = is_disabled;
}

bool Menu::GetIconMarginDisabled() const
{
    return _disable_icon_margin;
}

void Menu::SetDeleteOnClose(bool delete_on_close)
{
    _delete_on_close = delete_on_close;
}

bool Menu::GetDeleteOnClose() const
{
    return _delete_on_close;
}

bool Menu::GetHoverOpenMenu() const
{
    return true;
}

bool Menu::GetMenuComponent()
{
    return true;
}

void Menu::Open()
{
    SetHidden(false);
    BringToFront();
}

void Menu::Close()
{
    SetHidden(true);
    if (GetDeleteOnClose())
    {
        DelayedDelete();
    }
}

void Menu::CloseSubMenus()
{
    for (auto i = _inner_panel->GetChildren().begin(); i != _inner_panel->GetChildren().end(); ++i)
    {
        MenuItem* item = dynamic_cast<MenuItem*>(*i);
        if (item != nullptr)
        {
            item->Close();
        }
    }
}

void Menu::CloseMenus()
{
    // Call the base class.
    ScrollControl::CloseMenus();

    Close();
    CloseSubMenus();
}

bool Menu::GetOpen() const
{
    for (auto i = _inner_panel->GetChildren().begin(); i != _inner_panel->GetChildren().end(); ++i)
    {
        MenuItem* item = dynamic_cast<MenuItem*>(*i);
        if (item != nullptr && item->GetOpen())
        {
            return true;
        }
    }

    return false;
}

void Menu::Render(Skin::Base* skin)
{
    skin->DrawMenu(this, GetIconMarginDisabled());
}

void Menu::RenderUnder(Skin::Base* skin)
{
    // Call the base class.
    ScrollControl::RenderUnder(skin);

    skin->DrawShadow(this);
}

void Menu::_OnAddItem(MenuItem* item)
{
    item->SetTextPadding(Padding(GetIconMarginDisabled() ? 0 : 24, 0, 16, 0));
    item->SetDock(Position::TOP);
    item->SizeToContents();
    item->SetAlignment(Position::CENTER_V | Position::LEFT);
    item->_on_hover_enter.Add(this, &Menu::_OnHoverItem);

    const int width = std::max(item->Width() + 10 + 32, Width());
    SetSize(width, Height());
}

void Menu::_OnHoverItem(Gwen::Controls::Base* control)
{
    if (!GetHoverOpenMenu())
    {
        return;
    }

    MenuItem* item = dynamic_cast<MenuItem*>(control);
    if (item != nullptr && !item->GetOpen())
    {
        CloseSubMenus();
        item->Open();
    }
}

}; // namespace Controls

}; // namespace Gwen
