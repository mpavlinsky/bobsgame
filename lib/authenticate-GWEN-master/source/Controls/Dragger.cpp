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
#include "Gwen/Controls/Dragger.h"

namespace Gwen
{
namespace ControlsInternal
{

GWEN_CONTROL_CONSTRUCTOR(Dragger, Controls::Base)
{
    _depressed = false;
    _target = nullptr;
    _do_move = true;

    SetMouseInputEnabled(true);
}

bool Dragger::GetDepressed()
{
    return _depressed;
}

void Dragger::SetTarget(Controls::Base* base)
{
    _target = base;
}

void Dragger::SetDoMove(bool do_move)
{
    _do_move = do_move;
}

void Dragger::OnMouseMoved(int x, int y, int delta_x, int delta_y)
{
    if (!_depressed)
    {
        return;
    }

    if (_do_move && _target)
    {
        Gwen::Point point = Gwen::Point(x - _hold_position._x, y - _hold_position._y);

        // Translate to parent.
        if (_target->GetParent())
        {
            point = _target->GetParent()->CanvasPositionToLocal(point);
        }

        _target->MoveTo(point._x, point._y);
    }

    _on_dragged.Call(this);
}

void Dragger::OnMouseClickLeft(int x, int y, bool is_down)
{
    if (is_down)
    {
        if (_target)
        {
            _hold_position = _target->CanvasPositionToLocal(Gwen::Point(x, y));
        }

        _depressed = true;
        Gwen::Controls::_mouse_focus = this;
        _on_drag_start.Call(this);
    }
    else
    {
        _depressed = false;
        Gwen::Controls::_mouse_focus = nullptr;
    }
}

void Dragger::OnMouseDoubleClickLeft(int x, int y)
{
    _on_mouse_double_click_left.Call(this);
}

}; // namespace ControlsInternal

}; // namespace Gwen
