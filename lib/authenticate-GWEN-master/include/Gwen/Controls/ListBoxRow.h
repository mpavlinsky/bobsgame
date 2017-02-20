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
#include "Gwen/Controls/Layout/TableRow.h"

namespace Gwen
{
namespace Controls
{

// Forward declarations.
class ListBox;

/// \brief This class represents a row in a list box.
class ListBoxRow : public Layout::TableRow
{
    friend class ListBox;

public:
    /// \brief Constructor.
    GWEN_CONTROL(ListBoxRow, Layout::TableRow);

    /// \brief Called when the mouse enters the control.
    virtual void OnMouseEnter() override;

    /// \brief Called when the mouse leaves the control.
    virtual void OnMouseLeave() override;

    /// \brief Called when the left mouse button is pressed.
    virtual void OnMouseClickLeft(int x, int y, bool is_down) override;

    /// \brief Called when the elft mouse button is double clicked.
    virtual void OnMouseDoubleClickLeft(int x, int y) override;

    /// \brief Sets if a row is selected.
    virtual void SetSelected(bool selected) override;

protected:
    /// \brief Draws the UI element.
    virtual void Render(Skin::Base* skin) override;

private:
    /// \brief A helper function to do the selection.
    void _DoSelect();

    /// \brief A helper function to update the text color.
    void _UpdateTextColor();
};

}; // namespace Controls

}; // namespace Gwen
