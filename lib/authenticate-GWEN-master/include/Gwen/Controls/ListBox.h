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

#include "Gwen/Controls/Layout/Table.h"
#include "Gwen/Controls/Layout/TableRow.h"
#include "Gwen/Controls/ScrollControl.h"

namespace Gwen
{
namespace Controls
{

/// \brief This class represents a list box.
class ListBox : public ScrollControl
{
public:
    /// \brief Constructor.
    GWEN_CONTROL(ListBox, ScrollControl);

    /// \brief Lays out the UI element.
    virtual void Layout(Skin::Base* skin) override;

    /// \brief Adds a row to the list box.
    Layout::TableRow* AddRow(const std::string& label, const std::string& name = "");

    /// \brief Gets the rows from the list box.
    std::vector<Layout::TableRow*> GetRows();

    /// \brief Gets the rows from the list box.
    std::vector<const Layout::TableRow*> GetRows() const;

    /// \brief Removes an item from the list box.
    void RemoveItem(Layout::TableRow* row);

    /// \brief Clears the list box.
    virtual void Clear() override;

    /// \brief Sets the ability to select multiple rows at once.
    virtual void SetAllowMultiSelect(bool multi_select);

    /// \brief Gets the ability to select multiple rows at once.
    virtual bool GetAllowMultiSelect() const;

    /// \brief Unselects all rows.
    virtual void UnselectAll();

    /// \brief Sets the selected row.
    virtual void SetSelectedRow(Gwen::Controls::Base* row, bool clear_others = true);

    /// \brief Sets the selected row.
    virtual void SetSelectedRow(const std::string& string, bool clear_others = true);

    /// \brief Gets the selected row.
    virtual Layout::TableRow* GetSelectedRow();

    /// \brief Gets the selected row.
    virtual const Layout::TableRow* GetSelectedRow() const;

    /// \brief Gets the selected rows.
    virtual const std::list<Layout::TableRow*>& GetSelectedRows();

    /// \brief Gets the name of the selected row.
    virtual std::string GetSelectedRowName() const;

    /// \brief Sets the number of columns.
    void SetColumnCount(int count);

    /// \brief Sets the width for a column.
    void SetColumnWidth(int count, int size);

    /// \brief An event for when a row is selected.
    Gwen::Event::Caller _on_row_selected;

    /// \brief An event for when a row is double clicked with the left mouse button.
    Gwen::Event::Caller _on_row_mouse_double_click_left;

protected:
    /// \brief Updates the scroll bar.
    virtual void _UpdateScrollBar() override;

    /// \brief Draws the UI element.
    virtual void Render(Skin::Base* skin) override;

    /// \brief Called when a row is selected.
    virtual void OnRowSelected(Base* control);

    /// \brief Called when a row is doubled clicked with the left mouse button.
    virtual void OnRowMouseDoubleClickLeft(Base* control);

    /// \brief Called when a key is pressed.
    virtual bool OnKeyDown(bool is_down) override;

    /// \brief Called when a key is released.
    virtual bool OnKeyUp(bool is_down) override;

    /// \brief Is multiselect enabled?
    bool _multi_select;

    /// \brief The internal table control.
    Controls::Layout::Table* _table;

    /// \brief The selected rows.
    std::list<Layout::TableRow*> _selected_rows;
};

}; // namespace Controls

}; // namespace Gwen
