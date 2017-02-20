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

namespace Gwen
{
namespace Controls
{

// Forward declarations.
class TabControl;

/// \brief This class represents a tab button.
class TabButton : public Button
{
public:
    /// \brief Constructor.
    GWEN_CONTROL(TabButton, Button);

    /// \brief Sets the page.
    virtual void SetPage(Base* page);

    /// \brief Gets the page.
    virtual Base* GetPage();

    /// \brief Sets the tab control.
    virtual void SetTabControl(TabControl* control);

    /// \brief Gets the tab control.
    virtual TabControl* GetTabControl();

    /// \brief Is this the active tab button?
    virtual bool GetActive() const;

    /// \brief Called when the left key is pressed.
    virtual bool OnKeyLeft(bool is_down) override;

    /// \brief Called when the right key is pressed.
    virtual bool OnKeyRight(bool is_down) override;

    /// \brief Called when the up key is pressed.
    virtual bool OnKeyUp(bool is_down) override;

    /// \brief Called when the down key is pressed.
    virtual bool OnKeyDown(bool is_down) override;

    /// \brief Updates the control's colors.
    virtual void UpdateColors() override;

    /// \brief Should the control clip its children?
    virtual bool GetShouldClip() const override;

    /// \brief Lays out the UI element.
    virtual void Layout(Skin::Base* skin) override;

protected:
    /// \brief Draws the UI element.
    virtual void Render(Skin::Base* skin) override;

private:
    /// \brief The page.
    Base* _page;

    /// \brief The tab control.
    TabControl* _control;
};

}; // namespace Controls

}; // namespace Gwen
