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
#include "Gwen/skin/gwen_skin_base.h"

namespace Gwen
{
namespace Controls
{

/// \brief This class represents a check box.
class CheckBox : public Button
{
public:
    /// \brief Constructor.
    GWEN_CONTROL(CheckBox, Button);

    /// \brief Sets the checked state.
    virtual void SetChecked(bool is_checked);

    /// \brief Gets the checked state.
    virtual bool GetChecked() const;

    /// \brief Inverts the checked state.
    virtual void Toggle() override;

    /// \brief Called when the control is checked.
    virtual void OnChecked();

    /// \brief Called when the check box is pressed with the left mouse button.
    virtual void OnPressLeft() override;

    /// \brief An event for when the control is checked.
    Gwen::Event::Caller _on_checked;

    /// \brief An event for when the control is unchecked.
    Gwen::Event::Caller _on_unchecked;

    /// \brief An event for when the control's checked state is changed.
    Gwen::Event::Caller _on_check_changed;

protected:
    /// \brief Draws the UI element.
    virtual void Render(Skin::Base* skin) override;

private:
    /// \brief Allows the control to be unchecked.
    virtual bool AllowUncheck() const;

    /// \brief Is the control checked?
    bool _is_checked;
};

}; // namespace Controls

}; // namespace Gwen
