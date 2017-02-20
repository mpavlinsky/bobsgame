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
#include "Gwen/Controls/TabControl.h"

#include "Gwen/Controls/Canvas.h"
#include "Gwen/Controls/ScrollBarButton.h"
#include "Gwen/Controls/TabControlInnerPanel.h"
#include "Gwen/skin/gwen_skin_base.h"

#include "Gwen/Utility.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(TabControl, Base)
{
    _tab_strip = new TabStrip(this);
    _tab_strip->SetTabPosition(Position::TOP);

    _scroll[0] = new ControlsInternal::ScrollBarButton(this);
    _scroll[0]->SetDirectionLeft();
    _scroll[0]->_on_press_left.Add(this, &TabControl::ScrollPressLeft);
    _scroll[0]->SetSize(14, 14);
    _scroll[1] = new ControlsInternal::ScrollBarButton(this);
    _scroll[1]->SetDirectionRight();
    _scroll[1]->_on_press_left.Add(this, &TabControl::ScrollPressRight);
    _scroll[1]->SetSize(14, 14);

    _inner_panel = new ControlsInternal::TabControlInnerPanel(this);
    _inner_panel->SetDock(Position::FILL);
    _inner_panel->SendToBack();

    _current_button = nullptr;

    _offset = 0;

    SetTabable(false);
}

void TabControl::PostLayout(Skin::Base*)
{
    Gwen::Point tab_size = _tab_strip->ChildrenSize();
    Gwen::Padding tab_padding = _tab_strip->GetPadding();

    // Only enable the scrollers if the tabs are at the top.
    // TODO: This is a limitation we should explore.
    bool is_needed = tab_size._x + tab_padding._left > Width() && _tab_strip->GetDock() == Position::TOP;
    _scroll[0]->SetHidden(!is_needed);
    _scroll[1]->SetHidden(!is_needed);

    if (!is_needed)
    {
        return;
    }

    _offset = Utility::Clamp(_offset, 0, tab_size._x + tab_padding._left - Width());

    _tab_strip->SetMargin(Margin(-_offset, 0, 0, 0));

    _scroll[0]->SetPosition(Width() - 32, 4);
    _scroll[1]->SetPosition(_scroll[0]->Right(), 4);
}

TabButton* TabControl::AddPage(const std::string& text, Base* page)
{
    if (page)
    {
        page->SetParent(this);
    }
    else
    {
        page = new Base(this);
    }

    TabButton* button = new TabButton(_tab_strip);
    button->SetText(text);
    button->SetPage(page);
    button->SetTabable(false);

    AddPage(button);

    return button;
}

void TabControl::AddPage(TabButton* button)
{
    Base* page = button->GetPage();
    page->SetParent(this);
    page->SetHidden(true);
    page->SetMargin(Margin(6, 6, 6, 6));
    page->SetDock(Position::FILL);

    button->SetParent(_tab_strip);
    button->SetDock(Position::LEFT);
    button->SizeToContents();

    if (button->GetTabControl())
    {
        button->_on_press_left.RemoveHandler(button->GetTabControl());
    }

    button->SetTabControl(this);
    button->_on_press_left.Add(this, &TabControl::OnPressedTab);

    if (!_current_button)
    {
        button->OnPressLeft();
    }

    _on_tab_added.Call(this);
    Invalidate();
}

void TabControl::RemovePage(TabButton* button)
{
    // Sanity.
    assert(button != nullptr);
    if (button != nullptr)
    {
        // Hide the button's page.
        Base* page = button->GetPage();
        assert(page != nullptr);
        if (page != nullptr)
        {
            page->SetHidden(true);
        }

        // Update the button.
        button->SetParent(GetCanvas());
        OnRemovedTab(button);
    }
}

void TabControl::OnPressedTab(Base* control)
{
    TabButton* button = dynamic_cast<TabButton*>(control);
    if (!button)
    {
        return;
    }

    Base* page = button->GetPage();
    if (!page)
    {
        return;
    }

    if (_current_button == button)
    {
        return;
    }

    if (_current_button)
    {
        Base* page = _current_button->GetPage();
        if (page)
        {
            page->SetHidden(true);
        }

        _current_button->Redraw();
        _current_button = nullptr;
    }

    _current_button = button;
    page->SetHidden(false);
    _tab_strip->Invalidate();
    Invalidate();
}

void TabControl::OnRemovedTab(TabButton* button)
{
    if (_current_button == button)
    {
        _current_button = nullptr;
    }

    _on_tab_removed.Call(this);
    Invalidate();
}

unsigned TabControl::GetTabCount() const
{
    return _tab_strip->GetChildrenCount();
}

TabButton* TabControl::GetTab(int index)
{
    return dynamic_cast<TabButton*>(_tab_strip->GetChild(index));
}

TabButton* TabControl::GetCurrentButton()
{
    return _current_button;
}

TabStrip* TabControl::GetTabStrip()
{
    return _tab_strip;
}

void TabControl::SetTabStripPosition(int iDock)
{
    _tab_strip->SetTabPosition(iDock);
}

bool TabControl::DoesAllowDrag() const
{
    return _tab_strip->GetAllowReorder();
}

void TabControl::SetAllowReorder(bool allow_reorder)
{
    GetTabStrip()->SetAllowReorder(allow_reorder);
}

void TabControl::ScrollPressLeft(Base*)
{
    // TODO: Investigate changing the offset to bring the next button completely on screen.
    _offset -= 120;

    Invalidate();
}

void TabControl::ScrollPressRight(Base*)
{
    // TODO: Investigate changing the offset to bring the next button completely on screen.
    _offset += 120;

    Invalidate();
}

}; // namespace Controls

}; // namespace Gwen
