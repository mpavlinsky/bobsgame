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
#include "Gwen/Controls/HorizontalSlider.h"

#include "Gwen/Controls/Slider.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(HorizontalSlider, ControlsInternal::Slider)
{
}

void HorizontalSlider::Layout(Skin::Base*)
{
    _bar->SetSize(15, Height());
}

float HorizontalSlider::CalculateValue()
{
    return static_cast<float>(_bar->X()) / static_cast<float>(Width() - _bar->Width());
}

void HorizontalSlider::UpdateBarFromValue()
{
    _bar->MoveTo(static_cast<int>((Width() - _bar->Width()) * _value), _bar->Y());
}

void HorizontalSlider::Render(Skin::Base* skin)
{
    skin->DrawSlider(this, _number_of_notches, _bar->Width());
}

void HorizontalSlider::OnMouseClickLeft(int x, int y, bool is_down)
{
    // Convert the mosue coordinates.
    Gwen::Point point = Gwen::Point(x, y);
    point = CanvasPositionToLocal(point);

    _bar->MoveTo(point._x - _bar->Width() / 2, _bar->Y());
    _bar->OnMouseClickLeft(x, y, is_down);

    OnMoved(_bar);
}

void HorizontalSlider::_OnBoundsChanged(const Gwen::Rectangle& old_bounds)
{
    // Call the base class.
    Slider::_OnBoundsChanged(old_bounds);

    UpdateBarFromValue();
}

}; // namespace Controls

}; // namespace Gwen
