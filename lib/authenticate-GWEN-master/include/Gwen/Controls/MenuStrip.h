/*
 *  GWEN
 *  Copyright (c) 2010 Facepunch Studios
 *  See license in Gwen.h
 */

#pragma once

#include "Gwen/Controls/Menu.h"
#include "Gwen/Controls/MenuItem.h"

namespace Gwen
{
namespace Controls
{

/// \brief This class represents a menu strip.
class MenuStrip : public Menu
{
public:
    /// \brief Constructor.
    GWEN_CONTROL(MenuStrip, Menu);

    /// \brief Lays out the UI element.
    virtual void Layout(Skin::Base* skin) override;

    /// \brief Gets if the menu should open on hover.
    virtual bool GetHoverOpenMenu() const override;

    /// \brief Closes the menu strip.
    virtual void Close() override;

protected:
    /// \brief Draws the UI element.
    virtual void Render(Skin::Base* skin) override;

    /// \brief Draws the UI element.
    virtual void RenderUnder(Skin::Base* skin) override;

    /// \brief Called when an item is added.
    virtual void _OnAddItem(MenuItem* item) override;
};

}; // namespace Controls

}; // namespace Gwen
