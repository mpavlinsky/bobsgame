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
#include "Gwen/Controls/RadioButtonController.h"

#include "Gwen/Controls/RadioButton.h"
#include "Gwen/Utility.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(RadioButtonController, Base)
{
    _selected = nullptr;

    SetKeyboardInputEnabled(false);
    SetTabable(false);
}

RadioButtonWithLabel* RadioButtonController::AddItem(const std::string& text, const std::string& name)
{
    RadioButtonWithLabel* radio_button = new RadioButtonWithLabel(this);
    radio_button->SetName(name);
    radio_button->GetLabel()->SetText(text);
    radio_button->GetRadioButton()->_on_checked.Add(this, &RadioButtonController::OnRadioButtonChecked);
    radio_button->SetDock(Position::TOP);
    radio_button->SetMargin(Margin(0, 0, 0, 0));
    radio_button->SetKeyboardInputEnabled(false);
    radio_button->SetTabable(false);

    Invalidate();

    return radio_button;
}

RadioButtonWithLabel* RadioButtonController::GetSelected()
{
    return _selected;
}

void RadioButtonController::OnSelectionChanged()
{
    _on_selection_changed.Call(this);
}

void RadioButtonController::OnRadioButtonChecked(Gwen::Controls::Base* control)
{
    RadioButton* checked_radio_button = dynamic_cast<RadioButton*>(control);

    // Iterate through all other buttons and set them to false.
    for (auto i = _children.begin(); i != _children.end(); ++i)
    {
        RadioButtonWithLabel* radio_button_with_label = dynamic_cast<RadioButtonWithLabel*>(*i);
        if (radio_button_with_label)
        {
            RadioButton* radio_button = radio_button_with_label->GetRadioButton();
            if (radio_button == checked_radio_button)
            {
                _selected = radio_button_with_label;
            }
            else
            {
                radio_button_with_label->GetRadioButton()->SetChecked(false);
            }
        }
    }

    OnSelectionChanged();
}

void RadioButtonController::Render(Skin::Base*)
{
}

}; // namespace Controls

}; // namespace Gwen
