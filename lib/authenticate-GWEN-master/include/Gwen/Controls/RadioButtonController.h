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
#include "Gwen/Controls/RadioButtonWithLabel.h"

namespace Gwen
{
namespace Controls
{

/// \brief This class represents a controller for radio buttons.
class RadioButtonController : public Base
{
public:
    /// \brief Constructor.
    GWEN_CONTROL(RadioButtonController, Base);

    /// \brief Adds a radio button to the controller.
    virtual RadioButtonWithLabel* AddItem(const std::string& text, const std::string& name = "");

    /// \brief Gets the selected radio button.
    virtual RadioButtonWithLabel* GetSelected();

    /// \brief Called when the selection is changed.
    virtual void OnSelectionChanged();

    /// \brief Called when a radio button is checked.
    virtual void OnRadioButtonChecked(Base* control);

    /// \brief An event for when the selection is changed.
    Event::Caller _on_selection_changed;

protected:
    /// \brief Draws the UI element.
    virtual void Render(Skin::Base*) override;

private:
    /// \brief The selected radio button.
    RadioButtonWithLabel* _selected;
};

}; // namespace Controls

}; // namespace Gwen
