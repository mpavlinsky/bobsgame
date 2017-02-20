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

#pragma once

#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Button.h"
#include "Gwen/Controls/ScrollBar.h"
#include "Gwen/skin/gwen_skin_base.h"

namespace Gwen
{
namespace Controls
{

/// \brief This class represents a scroll control.  It is used a base for more complicated controls
///        such as the list box and chat box.
class ScrollControl : public Base
{
public:
    /// \brief Constructor.
    GWEN_CONTROL(ScrollControl, Base);

    /// \brief Lays out the UI element.
    virtual void Layout(Skin::Base* skin) override;

    /// \brief Sets the clamp to nudge amount.
    virtual void SetClampToNudgeAmount(bool clamp_to_nudge_amount);

    /// \brief Gets the clamp to nudge amount.
    virtual bool GetClampToNudgeAmount() const;

    /// \brief Scrolls the control to the top.
    virtual void ScrollToTop();

    /// \brief Scrolls the control to the bottom.
    virtual void ScrollToBottom();

    /// \brief Clears the scroll control.
    virtual void Clear();

protected:
    /// \brief Are the contents docked?
    virtual bool _GetContentsDocked();

    /// \brief Sets if the scroll control can scroll.
    virtual void _SetScroll(bool can_scroll);

    /// \brief Sets if the scroll bar is hidden.
    virtual void _SetScrollBarHidden(bool is_hidden);

    /// \brief Gets if the scroll bar is hidden.
    virtual bool _GetScrollBarHidden() const;

    /// \brief Updates the scroll bar.
    virtual void _UpdateScrollBar();

    /// \brief Called when the scroll bar moves.
    virtual void _OnScrollBarMoved(Controls::Base* control);

    /// \brief Called when a child's bounds change.
    virtual void _OnChildBoundsChanged(const Gwen::Rectangle& old_child_bounds, Controls::Base* child) override;

    /// \brief Called when the mouse is wheeled.
    virtual bool OnMouseWheeled(int delta) override;

    /// \brief Draws the UI element.
    virtual void Render(Skin::Base* skin) override;

    /// \brief The scroll bar.
    ControlsInternal::ScrollBar* _scroll_bar;
};

}; // namespace Controls

}; // namespace Gwen
