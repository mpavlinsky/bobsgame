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
#include "Gwen/Controls/ScrollControl.h"

#include "Gwen/Controls/ScrollBar.h"
#include "Gwen/Controls/VerticalScrollBar.h"
#include "Gwen/Utility.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(ScrollControl, Base)
{
    _scroll_bar = new VerticalScrollBar(this);
    _scroll_bar->SetDock(Position::RIGHT);
    _scroll_bar->_on_bar_moved.Add(this, &ScrollControl::_OnScrollBarMoved);
    _scroll_bar->SetNudgeAmount(21);

    _inner_panel = new Base(this);
    _inner_panel->SetPosition(0, 0);
    _inner_panel->SendToBack();
    _inner_panel->SetMouseInputEnabled(true);

    SetClampToNudgeAmount(false);
    SetMouseInputEnabled(false);
    _SetScrollBarHidden(false);
}

void ScrollControl::Layout(Skin::Base* skin)
{
    // Call the base class function.
    Base::Layout(skin);

    _UpdateScrollBar();
}

void ScrollControl::SetClampToNudgeAmount(bool clamp_to_nudge_amount)
{
    _scroll_bar->SetClampToNudgeAmount(clamp_to_nudge_amount);
}

bool ScrollControl::GetClampToNudgeAmount() const
{
    return _scroll_bar->GetClampToNudgeAmount();
}

void ScrollControl::ScrollToTop()
{
    _UpdateScrollBar();
    _scroll_bar->ScrollToTop();
}

void ScrollControl::ScrollToBottom()
{
    _UpdateScrollBar();
    _scroll_bar->ScrollToBottom();
}

void ScrollControl::Clear()
{
    _inner_panel->RemoveChildren();
}

bool ScrollControl::_GetContentsDocked()
{
    if (!_inner_panel)
    {
        return false;
    }

    for (auto i = _inner_panel->GetChildren().begin(); i != _inner_panel->GetChildren().end(); ++i)
    {
        Base* child = *i;
        if (child->GetDock() == Position::NONE)
        {
            return false;
        }
    }

    return true;
}

void ScrollControl::_SetScroll(bool can_scroll)
{
    _scroll_bar->SetBarHidden(!can_scroll);
    _scroll_bar->SetDisabled(!can_scroll);
}

void ScrollControl::_SetScrollBarHidden(bool is_hidden)
{
    _scroll_bar->SetHidden(is_hidden);
}

bool ScrollControl::_GetScrollBarHidden() const
{
    return _scroll_bar->Hidden();
}

void ScrollControl::_UpdateScrollBar()
{
    if (!_inner_panel)
    {
        return;
    }

    // Get the control's padding.
    const Gwen::Padding& padding = GetPadding();

    // Calculate the control's visible width.
    unsigned width = Width() - padding._left - padding._right;
    unsigned height = Height() - padding._top - padding._bottom;

    // Calculate the scroll bar's width.
    int scroll_bar_width = 0;
    if (!_scroll_bar->Hidden())
    {
        scroll_bar_width = _scroll_bar->Width() - 1;
    }

    // Get the maximum size of all the children.
    unsigned children_height = 0;
    for (auto i = _inner_panel->GetChildren().begin(); i != _inner_panel->GetChildren().end(); ++i)
    {
        Base* child = *i;
        children_height = std::max<int>(children_height, child->Bottom());
    }
    children_height += padding._top + padding._bottom;

    // Update the size of the inner panel.
    _inner_panel->SetSize(width - scroll_bar_width, std::max(height, children_height));

    // Determine whether to display the scroll bar's bar.
    bool can_scroll = height <= children_height;
    _SetScroll(can_scroll);

    // Update the scroll bar's content and viewable size.
    _scroll_bar->SetContentSize(children_height);

    const Gwen::Padding& inner_padding = _inner_panel->GetPadding();
    _scroll_bar->SetViewableContentSize(height - inner_padding._top - inner_padding._bottom);

    // Set the position of the inner panel.
    int position_y = 0;
    if (!_scroll_bar->Hidden())
    {
        position_y = -static_cast<int>(_scroll_bar->GetScrolledAmount());
    }

    _inner_panel->SetPosition(0, position_y);
}

void ScrollControl::_OnScrollBarMoved(Controls::Base*)
{
    Invalidate();
}

void ScrollControl::_OnChildBoundsChanged(const Gwen::Rectangle&, Controls::Base*)
{
    _UpdateScrollBar();
}

bool ScrollControl::OnMouseWheeled(int delta)
{
    if (!_scroll_bar->IsDisabled())
    {
        int scrolled_amount = _scroll_bar->GetScrolledAmount() + (_scroll_bar->GetNudgeAmount() * -delta);
        scrolled_amount = Utility::Clamp<int>(scrolled_amount, 0, _scroll_bar->GetContentSize() - _scroll_bar->GetViewableContentSize());
        if (_scroll_bar->SetScrolledAmount(scrolled_amount))
        {
            return true;
        }
    }

    return false;
}

void ScrollControl::Render(Skin::Base*)
{
}

}; // namespace Controls

}; // namespace Gwen
