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
#include "Gwen/skin/gwen_skin_base.h"

namespace Gwen
{
namespace ControlsInternal
{

/// \brief An internal control to facilitate dragging.
class Dragger : public Controls::Base
{
public:
    /// \brief Constructor.
    GWEN_CONTROL(Dragger, Controls::Base);

    /// \brief Is the dragger depressed?
    virtual bool GetDepressed();

    /// \brief Sets the target.
    virtual void SetTarget(Controls::Base* base);

    /// \brief Sets if the dragger should move.
    virtual void SetDoMove(bool do_move);

    /// \brief Called when the mouse is moved.
    virtual void OnMouseMoved(int x, int y, int delta_x, int delta_y) override;

    /// \brief Called when the left mouse button is pressed.
    virtual void OnMouseClickLeft(int x, int y, bool is_down) override;

    /// \brief Called when the right mouse button is double clicked.
    virtual void OnMouseDoubleClickLeft(int x, int y) override;

    /// \brief An event for when the control is dragged.
    Gwen::Event::Caller _on_dragged;

    /// \brief An event for when the control starts to drag.
    Gwen::Event::Caller _on_drag_start;

    /// \brief An event for when the control is double clicked with the left mouse button.
    Gwen::Event::Caller _on_mouse_double_click_left;

protected:
    /// \brief Is the control depressed?
    bool _depressed;

    /// \brief Not sure what this is.  Need to look at the source.
    Gwen::Point _hold_position;

    /// \brief The target control.
    Controls::Base* _target;

    /// \brief Should the control move?
    bool _do_move;
};

}; // namespace ControlsInternal

}; // namespace Gwen
