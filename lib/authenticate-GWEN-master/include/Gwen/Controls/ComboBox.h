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
#include "Gwen/Controls/Menu.h"
#include "Gwen/Controls/MenuItem.h"
#include "Gwen/skin/gwen_skin_base.h"

namespace Gwen
{
namespace Controls
{

/// \brief This class represents a combo box.
class ComboBox : public Button
{
public:
    /// \brief Constructor.
    GWEN_CONTROL(ComboBox, Button);

    /// \briefs Adds an item.
    virtual MenuItem* AddItem(const std::string& label, const std::string& name = "");

    /// \briefs Clears the combo box.
    virtual void Clear();

    /// \brief Selects an item.
    virtual void SelectItem(MenuItem* item, bool do_events = true);

    /// \brief Selects an item by its name.
    virtual void SelectItemByName(const std::string& name, bool do_events = true);

    /// \brief Gets the selected item.
    virtual Gwen::Controls::Label* GetSelectedItem();

    /// \brief Updates the combo box's colors.
    virtual void UpdateColors() override;

    /// \brief Called when an item is selected
    virtual void OnItemSelected(Controls::Base* control);

    /// \brief Called when the button is pressed with the left mouse button.
    virtual void OnPressLeft() override;

    /// \brief Called when the up key is pressed.
    virtual bool OnKeyUp(bool is_down) override;

    /// \brief Called when the down key is pressed.
    virtual bool OnKeyDown(bool is_down) override;

    /// \brief Called when the control gains keyboard focus.
    virtual void OnKeyboardFocus() override;

    /// \brief Called when the control loses keyboard focus.
    virtual void OnLostkeyboardFocus() override;

    /// \brief Lays out the UI element.
    virtual void Layout(Skin::Base* skin) override;

    /// \brief Is this control a menu component?
    virtual bool GetMenuComponent() override;

    /// \brief Opens the combo box.
    virtual void Open();

    /// \brief Closes the combo box.
    virtual void Close();

    /// \brief Closes all menu controls.
    virtual void CloseMenus() override;

    /// \brief Is the combo box open?
    virtual bool GetOpen();

    /// \brief An event for when an item is selected.
    Gwen::Event::Caller _on_selected;

protected:
    /// \brief Draws the UI element.
    virtual void Render(Skin::Base* skin) override;

    /// \brief The menu.
    Menu* _menu;

    /// \brief The selected item.
    MenuItem* _selected_item;

    /// \brief The button.
    Controls::Base* _button;
};

}; // namespace Controls

}; // namespace Gwen
