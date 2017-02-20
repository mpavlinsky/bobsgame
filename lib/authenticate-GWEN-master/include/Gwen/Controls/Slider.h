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
#include "Gwen/Controls/SliderBar.h"
#include "Gwen/skin/gwen_skin_base.h"

namespace Gwen
{
namespace ControlsInternal
{

/// \brief This class represents a slider.
class Slider : public Controls::Base
{
    /// \brief Constructor.
    GWEN_CONTROL(Slider, Controls::Base);

    /// \brief Lays out the UI element.
    virtual void Layout(Skin::Base* skin) override;

    /// \brief Clamps the value to the notches.
    virtual void SetClampToNotches(bool clamp);

    /// \brief Sets the notch count.
    virtual void SetNotchCount(unsigned count);

    /// \brief Gets the notch count.
    virtual unsigned GetNotchCount() const;

    /// \brief Sets the minimum.
    virtual void SetMinimum(float minimum);

    /// \brief Gets the minimum.
    virtual float GetMinimum() const;

    /// \brief Sets the maximum.
    virtual void SetMaximum(float maximum);

    /// \brief Gets the maximum.
    virtual float GetMaximum() const;

    /// \brief Sets the value of the slider.
    virtual void SetValue(float value, bool force_update = true);

    /// \brief Gets the value of the slider.
    virtual float GetValue();

    /// \brief Calculates the value of the slider.
    virtual float CalculateValue();

    /// \brief Called when the slider is moved.
    virtual void OnMoved(Controls::Base* control);

    /// \brief Called when the left key is pressed.
    virtual bool OnKeyLeft(bool is_down) override;

    /// \brief Called when the right key is pressed.
    virtual bool OnKeyRight(bool is_down) override;

    /// \brief Called when the up key is pressed.
    virtual bool OnKeyUp(bool is_down) override;

    /// \brief Called when the down key is pressed.
    virtual bool OnKeyDown(bool is_down) override;

    /// \brief An event for when the value of the slider changed.
    Gwen::Event::Caller onValueChanged;

protected:
    /// \brief Sets the value.
    virtual void _SetValueInternal(float value);

    /// \brief Updates the position of the slider from the value.
    virtual void UpdateBarFromValue() = 0;

    /// \brief Draws the UI element.
    virtual void Render(Skin::Base* skin) override = 0;

    /// \brief Draws the UI element.
    virtual void RenderFocus(Gwen::Skin::Base* skin) override;

    /// \brief Called when the bounds change.
    virtual void _OnBoundsChanged(const Gwen::Rectangle& old_bounds) override;

    /// \brief The slider bar control.
    SliderBar* _bar;

    /// \brief Clamps the value to the notches.
    bool _clamp_to_notches;

    /// \brief The number of notches.
    unsigned _number_of_notches;

    /// \brief The value.
    float _value;

    /// \brief The minimum value.
    float _minimum;

    /// \brief The maximum value.
    float _maximum;
};

}; // namespace ControlsInternal

}; // namespace Gwen
