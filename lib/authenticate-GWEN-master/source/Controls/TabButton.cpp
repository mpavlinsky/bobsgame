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
#include "Gwen/Controls/TabButton.h"

#include "Gwen/Controls/Highlight.h"
#include "Gwen/Controls/TabControl.h"
#include "Gwen/skin/gwen_skin_base.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(TabButton, Button)
{
    _page = nullptr;
    _control = nullptr;

    SetAlignment(Position::TOP | Position::LEFT);
    SetTextPadding(Padding(8, 0, 8, 0));
}

void TabButton::SetPage(Base* page)
{
    _page = page;
}

Base* TabButton::GetPage()
{
    return _page;
}

void TabButton::SetTabControl(TabControl* control)
{
    if (_control == control)
    {
        return;
    }

    if (_control)
    {
        _control->OnRemovedTab(this);
    }

    _control = control;
}

TabControl* TabButton::GetTabControl()
{
    return _control;
}

bool TabButton::GetActive() const
{
    return _page && _page->Visible();
}

bool TabButton::OnKeyLeft(bool is_down)
{
    if (is_down)
    {
        auto i = std::find(_parent->GetChildren().rbegin(), _parent->GetChildren().rend(), this);
        if (i != _parent->GetChildren().rend() && (++i != _parent->GetChildren().rend()))
        {
            Base* next_tab = *i;
            GetTabControl()->OnPressedTab(next_tab);
            Gwen::Controls::_keyboard_focus = next_tab;
        }
    }

    return true;
}

bool TabButton::OnKeyRight(bool is_down)
{
    if (is_down)
    {
        auto i = std::find(_parent->GetChildren().begin(), _parent->GetChildren().end(), this);
        if (i != _parent->GetChildren().end() && (++i != _parent->GetChildren().end()))
        {
            Base* next_tab = *i;
            GetTabControl()->OnPressedTab(next_tab);
            Gwen::Controls::_keyboard_focus = next_tab;
        }
    }

    return true;
}

bool TabButton::OnKeyUp(bool is_down)
{
    return OnKeyLeft(is_down);
}

bool TabButton::OnKeyDown(bool is_down)
{
    return OnKeyRight(is_down);
}

void TabButton::UpdateColors()
{
    if (!GetActive())
    {
        if (IsDisabled())
        {
            return SetTextColor(GetSkin()->Colors.Tab.Inactive.Disabled);
        }

        if (GetDepressed())
        {
            return SetTextColor(GetSkin()->Colors.Tab.Inactive.Down);
        }

        if (IsHovered())
        {
            return SetTextColor(GetSkin()->Colors.Tab.Inactive.Hover);
        }

        return SetTextColor(GetSkin()->Colors.Tab.Inactive.Normal);
    }

    if (IsDisabled())
    {
        return SetTextColor(GetSkin()->Colors.Tab.Active.Disabled);
    }

    if (GetDepressed())
    {
        return SetTextColor(GetSkin()->Colors.Tab.Active.Down);
    }

    if (IsHovered())
    {
        return SetTextColor(GetSkin()->Colors.Tab.Active.Hover);
    }

    SetTextColor(GetSkin()->Colors.Tab.Active.Normal);
}

bool TabButton::GetShouldClip() const
{
    return false;
}

void TabButton::Layout(Skin::Base* skin)
{
    // Call the base class.
    Button::Layout(skin);

    int parent_dock = _control->GetTabStrip()->GetDock();
    if (parent_dock == Position::BOTTOM)
    {
        SetPadding(Padding(3, 1, 5, 4));
    }
    else if (parent_dock == Position::TOP)
    {
        SetPadding(Padding(3, 3, 5, 2));
    }
    else
    {
        SetPadding(Padding(3, 2, 5, 2));
    }
}

void TabButton::Render(Skin::Base* skin)
{
    skin->DrawTabButton(this, GetActive(), _control->GetTabStrip()->GetDock());
}

}; // namespace Controls

}; // namespace Gwen
