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

#include "Gwen/Controls/Dragger.h"
#include "Gwen/skin/gwen_skin_base.h"

namespace Gwen
{
namespace ControlsInternal
{

/// \brief This class represents the center, draggable bar of a scroll bar.
class ScrollBarBar : public Dragger
{
public:
    /// \brief Constructor.
    GWEN_CONTROL(ScrollBarBar, Dragger);

    /// \brief Sets the bar to horizontal.
    virtual void SetHorizontal();

    /// \brief Gets if the bar is horizontal.
    virtual bool GetHorizontal() const;

    /// \brief Sets the bar to vertical.
    virtual void SetVertical();

    /// \brief Gets if the bar is vertical.
    virtual bool GetVertical() const;

    /// \brief Gets if the bar is depressed.
    virtual bool GetDepressed() override;

    /// \brief Moves the control.
    virtual void MoveTo(int x, int y) override;

    /// \brief Called when the mouse is moved.
    virtual void OnMouseMoved(int x, int y, int delta_x, int delta_y) override;

    /// \brief Called when the left mouse button is pressed.
    virtual void OnMouseClickLeft(int x, int y, bool is_down) override;

    /// \brief Lays out the control.
    virtual void Layout(Skin::Base* skin) override;

protected:
    /// \brief Draws the UI element.
    virtual void Render(Skin::Base* skin) override;

    /// \brief Is the bar horizontal?
    bool _horizontal;
};

}; // namespace ControlsInternal

}; // namespace Gwen
