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
#include "Gwen/Controls/Slider.h"

#include "Gwen/Controls/SliderBar.h"

#include "Gwen/Utility.h"

namespace Gwen
{
namespace ControlsInternal
{

GWEN_CONTROL_CONSTRUCTOR(Slider, Base)
{
    _bar = new ControlsInternal::SliderBar(this);
    _bar->SetWidth(15);
    _bar->_on_dragged.Add(this, &Slider::OnMoved);

    _minimum = 0.0f;
    _maximum = 1.0f;

    _clamp_to_notches = false;
    _number_of_notches = 5;

    _value = 0.0f;

    SetBounds(Rectangle(0, 0, 128, 16));
    SetTabable(true);
}

void Slider::Layout(Skin::Base* skin)
{
    // Call the base class.
    Base::Layout(skin);
}

void Slider::SetClampToNotches(bool clamp)
{
    _clamp_to_notches = clamp;
}

void Slider::SetNotchCount(unsigned count)
{
    _number_of_notches = count;
}

unsigned Slider::GetNotchCount() const
{
    return _number_of_notches;
}

void Slider::SetMinimum(float minimum)
{
    _minimum = minimum;
}

float Slider::GetMinimum() const
{
    return _minimum;
}

void Slider::SetMaximum(float maximum)
{
    _maximum = maximum;
}

float Slider::GetMaximum() const
{
    return _maximum;
}

void Slider::SetValue(float value, bool)
{
    value = Utility::Clamp(value, _minimum, _maximum);
    value = (value - _minimum) / (_maximum - _minimum);

    _SetValueInternal(value);

    Redraw();
}

float Slider::GetValue()
{
    return _minimum + (_value * (_maximum - _minimum));
}

float Slider::CalculateValue()
{
    return 0.0f;
}

void Slider::OnMoved(Controls::Base*)
{
    _SetValueInternal(CalculateValue());
}

bool Slider::OnKeyLeft(bool is_down)
{
    if (is_down)
    {
        SetValue(GetValue() - 1.0f, true);
    }

    return true;
}

bool Slider::OnKeyRight(bool is_down)
{
    if (is_down)
    {
        SetValue(GetValue() + 1.0f, true);
    }

    return true;
}

bool Slider::OnKeyUp(bool is_down)
{
    if (is_down)
    {
        SetValue(GetValue() + 1.0f, true);
    }

    return true;
}

bool Slider::OnKeyDown(bool is_down)
{
    if (is_down)
    {
        SetValue(GetValue() - 1.0f, true);
    }

    return true;
}

void Slider::_SetValueInternal(float value)
{
    if (_clamp_to_notches)
    {
        value = floorf(value * static_cast<float>(_number_of_notches) + 0.5f);
        value /= static_cast<float>(_number_of_notches);
    }

    if (_value != value)
    {
        _value = value;
        onValueChanged.Call(this);
    }

    UpdateBarFromValue();
}

void Slider::RenderFocus(Gwen::Skin::Base* skin)
{
    if (Gwen::Controls::_keyboard_focus != this)
    {
        return;
    }

    if (!IsTabable())
    {
        return;
    }

    skin->DrawKeyboardHighlight(this, GetRenderBounds(), 0);
}

void Slider::_OnBoundsChanged(const Gwen::Rectangle& old_bounds)
{
    // Call the base class.
    Base::_OnBoundsChanged(old_bounds);
}

}; // namespace ControlsInternal

}; // namespace Gwen
