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
namespace Layout
{

/// \brief This class represents an internal control to layout UI elements in a table.
class Table : public Base
{
public:
    /// \brief Constructor.
    GWEN_CONTROL(Table, Base);

    /// \brief Sets the number of columns.
    void SetColumnCount(int count);

    /// \brief Sets the width for a column.
    void SetColumnWidth(int column, int width);

    /// \brief Adds a row to the front or back of the table.  Defaults to the back.
    TableRow* AddRow(int dock, bool to_back = true);

    /// \brief Adds a row to the front or back of the table.  Defaults to the back.
    void AddRow(TableRow* row, int dock, bool to_back = true);

    /// \brief Removes a row.
    void Remove(TableRow* row);

    /// \brief Removes all rows.
    void Clear();

    /// \brief Gets a row.
    TableRow* GetRow(unsigned index);

    /// \brief Gets a row.
    const TableRow* GetRow(unsigned index) const;

    /// \briefs Gets the number of rows.
    unsigned GetRowCount() const;

    /// \brief Gets the default row height in pixels.
    unsigned GetDefaultRowHeight() const;

    /// \brief Should the control clip its children?
    virtual bool GetShouldClip() const override;

    /// \brief Lays out the UI element.
    virtual void Layout(Skin::Base* skin) override;

    /// \brief Lays out the UI element.
    virtual void PostLayout(Skin::Base* skin) override;

    /// \brief Sizes the control to its contents.
    void SizeToContents();

private:
    /// \brief The default row height in pixels.
    unsigned _default_row_height;

    /// \brief The number of columns.
    int _column_count;

    /// \brief The width of each column.
    int _column_width[MAX_COLUMNS];
};

}; // namespace Layout

}; // namespace Controls

}; // namespace Gwen
