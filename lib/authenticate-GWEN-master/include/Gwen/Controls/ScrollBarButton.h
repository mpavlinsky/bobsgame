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

#include "Gwen/Controls/Button.h"

namespace Gwen
{
namespace ControlsInternal
{

/// \brief This internal class represents a button on a scroll bar.
class ScrollBarButton : public Controls::Button
{
public:
    /// \brief Constructor.
    GWEN_CONTROL(ScrollBarButton, Controls::Button);

    /// \brief Sets the button direction to up.
    virtual void SetDirectionUp();

    /// \brief Sets the button direction to down.
    virtual void SetDirectionDown();

    /// \brief Sets the button direction to left.
    virtual void SetDirectionLeft();

    /// \brief Sets the button direction to right.
    virtual void SetDirectionRight();

protected:
    /// \brief Draws the UI element.
    virtual void Render(Skin::Base* skin) override;

    /// \brief The direction of the button.
    int _direction;
};

}; // namespace ControlsInternal

}; // namespace Gwen
