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

#include "Gwen/Controls/MenuItem.h"
#include "Gwen/Controls/ScrollControl.h"

namespace Gwen
{
namespace Controls
{

// Forward declarations.
class MenuStrip;

/// \brief This class represents a menu.
class Menu : public ScrollControl
{
    friend class MenuStrip;

public:
    /// \brief constructor.
    GWEN_CONTROL(Menu, ScrollControl);

    /// \brief Lays out the UI element.
    virtual void Layout(Skin::Base* skin) override;

    /// \brief Adds an item to the menu.
    virtual MenuItem* AddItem(const std::string& name, const std::string& icon_name = "", const std::string& accelerator = "");

    /// \brief Adds a divider to the menu.
    virtual void AddDivider();

    /// \brief Clears the menu.
    virtual void Clear() override;

    /// \brief Sets if the icon margin is disabled.
    virtual void SetIconMarginDisabled(bool is_disabled);

    /// \brief Gets if the icon margin is disabled.
    virtual bool GetIconMarginDisabled() const;

    /// \brief Sets if the menu should delete on close.
    virtual void SetDeleteOnClose(bool delete_on_close);

    /// \brief Gets if the menu should delete on close.
    virtual bool GetDeleteOnClose() const;

    /// \brief Gets if the menu should open on hover.
    virtual bool GetHoverOpenMenu() const;

    /// \brief Is this control a menu component?
    virtual bool GetMenuComponent() override;

    /// \brief Opens the menu.
    virtual void Open();

    /// \brief Closes the menu.
    virtual void Close();

    /// \brief Closes the sub menus.
    virtual void CloseSubMenus();

    /// \brief Closes all menu controls.
    virtual void CloseMenus() override;

    /// \brief Is the menu open?
    virtual bool GetOpen() const;

protected:
    /// \brief Draws the UI element.
    virtual void Render(Skin::Base* skin) override;

    /// \brief Draws the UI element.
    virtual void RenderUnder(Skin::Base* skin) override;

    /// \brief Called when an item is added.
    virtual void _OnAddItem(MenuItem* item);

    /// \brief Called when an item is hovered.
    virtual void _OnHoverItem(Gwen::Controls::Base* control);

    /// \brief Is the icon margin disabled?
    bool _disable_icon_margin;

    /// \brief Should the menu delete when closed?
    bool _delete_on_close;
};

}; // namespace Controls

}; // namespace Gwen
