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

#include "Gwen/Controls/ScrollBar.h"
#include "Gwen/skin/gwen_skin_base.h"

namespace Gwen
{
namespace Controls
{

/// \brief This class represents a vertical scroll bar.
class VerticalScrollBar : public ControlsInternal::ScrollBar
{
    /// \brief Constructor.
    GWEN_CONTROL(VerticalScrollBar, ControlsInternal::ScrollBar);

    /// \brief Nudges the bar up.
    virtual void NudgeUp(Base* control);

    /// \brief Nudges the bar down.
    virtual void NudgeDown(Base* control);

    /// \brief Sets the size of the bar.
    virtual void SetBarSize(unsigned size) override;

    /// \brief Gets the size of the bar.
    virtual unsigned GetBarSize() const override;

    /// \brief Gets the position of the bar.
    virtual unsigned GetBarPosition() const override;

    /// \brief Gets the size of the buttons.
    virtual unsigned GetButtonSize() const override;

    /// \brief Sets the bar to the top.
    virtual void ScrollToTop() override;

    /// \brief Sets the bar to the bottom.
    virtual void ScrollToBottom() override;

    /// \brief Calculate the amount scrolled.
    virtual unsigned CalculateScrolledAmount() override;

    /// \brief Sets the amount scrolled.
    virtual bool SetScrolledAmount(unsigned amount, bool do_events = true) override;

    /// \brief Called when the bar is moved.
    virtual void OnBarMoved(Controls::Base* control) override;

    /// \brief Called when the left mouse button is pressed.
    virtual void OnMouseClickLeft(int x, int y, bool is_down) override;

    /// \brief Lays out the UI element.
    virtual void Layout(Skin::Base* skin) override;
};

}; // namespace Controls

}; // namespace Gwen
