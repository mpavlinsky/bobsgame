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
#include "Gwen/Controls/Label.h"

namespace Gwen
{
namespace Controls
{
namespace Layout
{

// Forward declarations.
class Table;

/// \brief The maximum number of columns in a table.
const unsigned MAX_COLUMNS = 16;

/// \brief This class represents a row in a table.
class TableRow : public Base
{
    friend class Table;

public:
    /// \brief Constructor.
    GWEN_CONTROL(TableRow, Base);

    /// \brief Sets the user data.
    virtual void SetUserData(void* user_data);

    /// \brief Gets the user data.
    virtual void* GetUserData() const;

    /// \brief Sets the number of columns.
    void SetColumnCount(int count);

    /// \brief Sets the width for a column.
    void SetColumnWidth(int column, int width);

    /// \brief Cleans up table rows.
    virtual void DelayedDelete() override;

    /// \brief Sets a cell's text.
    void SetCellText(int cell, const std::string& text);

    /// \brief Gets a cell's text.
    std::string GetCellText(int cell);

    /// \brief Sets the text's color.
    void SetTextColor(const Gwen::Color& color);

    /// \brief Sets if a row is selected.
    virtual void SetSelected(bool selected);

    /// \brief Gets if a row is selected.
    virtual bool GetSelected() const;

    /// \brief Sets if a row is even.
    virtual void SetEven(bool even);

    /// \brief Gets if a row is even.
    virtual bool GetEven();

    /// \brief Sizes the control to its contents.
    void SizeToContents();

    /// \brief An event for when the row is double clicked with the left mouse button.
    Gwen::Event::Caller _on_mouse_double_click_left;

    /// \brief An event for when the row is selected.
    Gwen::Event::Caller _on_selected;

private:
    /// \brief A pointer for user data.
    void* _user_data;

    /// \brief Is this row selected?
    bool _selected;

    /// \brief Is this row even?
    bool _even;

    /// \brief The number of columns.
    int _column_count;

    /// \brief The columns.
    Label* _columns[MAX_COLUMNS];
};

}; // namespace Layout

}; // namespace Controls

}; // namespace Gwen
