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
#include "Gwen/Controls/Button.h"
#include "Gwen/skin/gwen_skin_base.h"

namespace Gwen
{
namespace Controls
{

// Forward declarations.
class Menu;

/// \brief This class represents a menu item.
class MenuItem : public Button
{
public:
    /// \brief constructor.
    GWEN_CONTROL(MenuItem, Button);

    /// \brief Lays out the UI element.
    virtual void Layout(Skin::Base* skin) override;

    /// \brief Sets if the menu item is on the strip.
    virtual void SetOnStrip(bool on_strip);

    /// \brief Gets if the menu item is on the strip.
    virtual bool GetOnStrip() const;

    /// \brief Sets if the menu item is checkable.
    virtual void SetCheckable(bool checkable);

    /// \brief Sets if the menu item is checkable.
    virtual bool GetCheckable() const;

    /// \brief Sets if the menu item is checked.
    virtual void SetChecked(bool checked);

    /// \brief Gets if the menu item is checked.
    virtual bool GetChecked() const;

    /// \brief Gets the menu.
    virtual Menu* GetMenu();

    /// \brief Updates the menu item's colors.
    virtual void UpdateColors() override;

    /// \brief Called when the button is pressed with the left mouse button.
    virtual void OnPressLeft() override;

    /// \brief Sizes the control to its contents.
    virtual void SizeToContents() override;

    /// \brief Sets the accelerator.
    virtual void SetAccelerator(const std::string& accelerator);

    /// \brief Is this control a menu component?
    virtual bool GetMenuComponent() override;

    /// \brief Opens the menu.
    virtual void Open();

    /// \brief Closes the menu.
    virtual void Close();

    /// \brief Toggles the menu.
    virtual void Toggle() override;

    /// \brief Is the menu open?
    virtual bool GetOpen() const;

    /// \brief Closes all menu controls.
    virtual void CloseMenus() override;

    /// \brief An event for when the menu item is selected.
    Gwen::Event::Caller _on_selected;

    /// \brief An event for when the menu item is checked.
    Gwen::Event::Caller _on_checked;

    /// \brief An event for when the menu item is unchecked.
    Gwen::Event::Caller _on_unchecked;

    /// \brief An event for when the menu item's check status is changed.
    Gwen::Event::Caller _on_check_changed;

protected:
    /// \brief Draws the UI element.
    virtual void Render(Skin::Base* skin) override;

private:
    /// \brief The menu.
    Menu* _menu;

    /// \brief The accelerator.
    Label* _accelerator;

    /// \brief The sub menu arrow.
    Controls::Base* _submenu_arrow;

    /// \brief Is the menu on the menu strip?
    bool _on_strip;

    /// \brief Is the menu checkable?
    bool _checkable;

    /// \brief Is the menu checked?
    bool _checked;
};

}; // namespace Controls

}; // namespace Gwen
