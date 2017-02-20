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
#include "Gwen/Controls/ScrollBarButton.h"
#include "Gwen/Controls/TabButton.h"
#include "Gwen/Controls/TabStrip.h"
#include "Gwen/Controls/TabTitleBar.h"

namespace Gwen
{
namespace Controls
{

/// \brief This class represents a tab control.
class TabControl : public Base
{
public:
    /// \brief Constructor.
    GWEN_CONTROL(TabControl, Base);

    /// \brief Lays out the UI element.
    virtual void PostLayout(Skin::Base* skin);

    /// \brief Adds a page to the tab control.
    virtual TabButton* AddPage(const std::string& text, Base* page = nullptr);

    /// \brief Adds a page to the tab control.
    virtual void AddPage(TabButton* button);

    /// \brief Removes a page from the tab control.
    virtual void RemovePage(TabButton* button);

    /// \brief Called when a tab is pressed.
    virtual void OnPressedTab(Base* control);

    /// \brief Called when a tab is removed.
    virtual void OnRemovedTab(TabButton* button);

    /// \brief Gets the number of tabs.
    virtual unsigned GetTabCount() const;

    /// \brief Gets a tab.
    virtual TabButton* GetTab(int index);

    /// \brief Gets the selected tab.
    virtual TabButton* GetCurrentButton();

    /// \brief Gets the tab strip.
    virtual TabStrip* GetTabStrip();

    /// \brief Sets the positio of the tab strip.
    virtual void SetTabStripPosition(int position);

    /// \brief Can the tab control be dragged?
    virtual bool DoesAllowDrag() const;

    /// \brief Can the tab control be reordered?
    virtual void SetAllowReorder(bool allow_reorder);

    /// \brief An event for when a tab is removed.
    Gwen::Event::Caller _on_tab_removed;

    /// \brief An event for when a tab is added.
    Gwen::Event::Caller _on_tab_added;

private:
    /// \brief Called when scrolling to the left.
    virtual void ScrollPressLeft(Base* control);

    /// \brief Called when scrolling to the right.
    virtual void ScrollPressRight(Base* control);

    /// \brief The tab strip.
    TabStrip* _tab_strip;

    /// \brief The tab button.
    TabButton* _current_button;

    /// \brief The scroll bar buttons.
    ControlsInternal::ScrollBarButton* _scroll[2];

    /// \brief The offset.
    int _offset;
};

}; // namespace Controls

}; // namespace Gwen
