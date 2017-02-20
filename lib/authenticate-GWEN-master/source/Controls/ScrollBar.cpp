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
#include "Gwen/Controls/ScrollBar.h"

#include "Gwen/Controls/ScrollBarBar.h"
#include "Gwen/Controls/ScrollBarButton.h"

#include "Gwen/Utility.h"

namespace Gwen
{
namespace ControlsInternal
{

GWEN_CONTROL_CONSTRUCTOR(ScrollBar, Controls::Base)
{
    _bar = new ScrollBarBar(this);

    for (int i = 0; i < 2; ++i)
    {
        _scroll_button[i] = new ScrollBarButton(this);
    }

    _depressed = false;
    _clamp_to_nudge_amount = false;
    _alignment = Position::TOP;
    _scrolled_amount = 0;
    _content_size = 0;
    _viewable_content_size = 0;
    _nudge_amount = 0;

    SetAlignment(Position::TOP);
    SetBounds(0, 0, 15, 15);
    SetClampToNudgeAmount(false);
    SetNudgeAmount(20);
}

void ScrollBar::SetClampToNudgeAmount(bool clamp_to_nudge_amount)
{
    _clamp_to_nudge_amount = clamp_to_nudge_amount;
}

bool ScrollBar::GetClampToNudgeAmount() const
{
    return _clamp_to_nudge_amount;
}

void ScrollBar::SetAlignment(int alignment)
{
    SetAlignment(static_cast<Gwen::Position::Position>(alignment));
}

void ScrollBar::SetAlignment(const Gwen::Position::Position& alignment)
{
    _alignment = alignment;
}

void ScrollBar::SetBarHidden(bool is_hidden)
{
    assert(_bar != nullptr);
    if (_bar != nullptr)
    {
        _bar->SetHidden(is_hidden);
    }
}

unsigned ScrollBar::GetButtonSize() const
{
    return 0;
}

void ScrollBar::ScrollToLeft()
{
}

void ScrollBar::ScrollToRight()
{
}

void ScrollBar::ScrollToTop()
{
}

void ScrollBar::ScrollToBottom()
{
}

void ScrollBar::SetNudgeAmount(unsigned nudge_amount)
{
    _nudge_amount = nudge_amount;
}

unsigned ScrollBar::GetNudgeAmount() const
{
    return _nudge_amount;
}

unsigned ScrollBar::CalculateScrolledAmount()
{
    return 0;
}

unsigned ScrollBar::CalculateBarSize()
{
    return 0;
}

bool ScrollBar::SetScrolledAmount(unsigned amount, bool do_events)
{
    amount = Utility::Clamp<unsigned>(amount, 0, _content_size - _viewable_content_size);
    if (_scrolled_amount == amount && !do_events)
    {
        return false;
    }

    _scrolled_amount = amount;

    // Clamp to the nudge amount.
    if (_clamp_to_nudge_amount)
    {
        _scrolled_amount = _ClampToNudgeAmount(_scrolled_amount);
    }

    Invalidate();

    OnBarMoved(this);
    return true;
}

unsigned ScrollBar::GetScrolledAmount() const
{
    return _scrolled_amount;
}

void ScrollBar::SetContentSize(unsigned size)
{
    if (_content_size != size)
    {
        Invalidate();
    }

    _content_size = size;
}

unsigned ScrollBar::GetContentSize() const
{
    return _content_size;
}

void ScrollBar::SetViewableContentSize(unsigned size)
{
    if (_viewable_content_size != size)
    {
        Invalidate();
    }

    _viewable_content_size = size;
}

unsigned ScrollBar::GetViewableContentSize() const
{
    return _viewable_content_size;
}

bool ScrollBar::GetHorizontal() const
{
    return false;
}

bool ScrollBar::GetVertical() const
{
    return !GetHorizontal();
}

unsigned ScrollBar::_ClampToNudgeAmount(unsigned value) const
{
    unsigned result = value;

    unsigned minimum = 0;
    unsigned maximum = _content_size - _viewable_content_size;

    // Make sure the nudge amount is position and the value is not already at the minimum or maximum.
    if (_nudge_amount > 0 && value != minimum && value != maximum)
    {
        if (result % _nudge_amount != 0)
        {
            result = ((result / _nudge_amount) + 1) * _nudge_amount;
        }
        result = Utility::Clamp(result, minimum, maximum);
    }

    return result;
}

void ScrollBar::OnBarMoved(Controls::Base*)
{
    _on_bar_moved.Call(this);
}

void ScrollBar::OnMouseClickLeft(int, int, bool)
{
}

void ScrollBar::Render(Skin::Base* skin)
{
    skin->DrawScrollBar(this, GetHorizontal());
}

}; // namespace ControlsInternal

}; // namespace Gwen
