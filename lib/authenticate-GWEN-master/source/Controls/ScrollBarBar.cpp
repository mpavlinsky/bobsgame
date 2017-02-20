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
#include "Gwen/Controls/ScrollBarBar.h"

#include "Gwen/Controls/ScrollBar.h"

namespace Gwen
{
namespace ControlsInternal
{

GWEN_CONTROL_CONSTRUCTOR(ScrollBarBar, Dragger)
{
    SetRestrictToParent(true);
    SetTarget(this);
}

void ScrollBarBar::SetHorizontal()
{
    _horizontal = true;
}

bool ScrollBarBar::GetHorizontal() const
{
    return _horizontal;
}

void ScrollBarBar::SetVertical()
{
    _horizontal = false;
}

bool ScrollBarBar::GetVertical() const
{
    return !GetHorizontal();
}

bool ScrollBarBar::GetDepressed()
{
    return _depressed;
}

void ScrollBarBar::MoveTo(int x, int y)
{
    // Call the base class.
    ControlsInternal::Dragger::MoveTo(x, y);
}

void ScrollBarBar::OnMouseMoved(int x, int y, int delta_x, int delta_y)
{
    // Call the base class.
    ControlsInternal::Dragger::OnMouseMoved(x, y, delta_x, delta_y);

    if (!_depressed)
    {
        return;
    }

    Invalidate();
}

void ScrollBarBar::OnMouseClickLeft(int x, int y, bool is_down)
{
    // Call the base class.
    ControlsInternal::Dragger::OnMouseClickLeft(x, y, is_down);

    Invalidate();
}

void ScrollBarBar::Layout(Skin::Base*)
{
    if (!GetParent())
    {
        return;
    }

    MoveTo(X(), Y());
}

void ScrollBarBar::Render(Skin::Base* skin)
{
    // Call the base class.
    ControlsInternal::Dragger::Render(skin);
    skin->DrawScrollBarBar(this, _depressed, IsHovered(), GetHorizontal());
}

}; // namespace ControlsInternal

}; // namespace Gwen
