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

#include "Gwen.h"
#include "Gwen/Controls/Layout/Table.h"

#include "Gwen/Controls/Button.h"
#include "Gwen/Controls/Layout/TableRow.h"
#include "Gwen/Utility.h"

namespace Gwen
{
namespace Controls
{
namespace Layout
{

GWEN_CONTROL_CONSTRUCTOR(Table, Base)
{
    _default_row_height = 21;
    _column_count = 1;

    for (int i = 0; i < MAX_COLUMNS; ++i)
    {
        _column_width[i] = 0;
    }

    SetHidden(false);
    SetMouseInputEnabled(true);
}

void Table::SetColumnCount(int count)
{
    if (_column_count == count)
    {
        return;
    }

    for (auto i = _children.begin(); i != _children.end(); ++i)
    {
        TableRow* row = dynamic_cast<TableRow*>(*i);
        if (row != nullptr)
        {
            row->SetColumnCount(count);
        }
    }

    _column_count = count;

    Invalidate();
    InvalidateChildren();
}

void Table::SetColumnWidth(int column, int width)
{
    if (_column_width[column] == width)
    {
        return;
    }

    _column_width[column] = width;

    Invalidate();
    InvalidateChildren();
}

TableRow* Table::AddRow(int dock, bool to_back)
{
    TableRow* row = new TableRow(this);
    AddRow(row, dock, to_back);
    return row;
}

void Table::AddRow(TableRow* row, int dock, bool to_back)
{
    row->SetParent(this, to_back);
    row->SetColumnCount(_column_count);
    row->SetHeight(_default_row_height);
    row->SetDock(dock);

    Invalidate();
    InvalidateChildren();
}

void Table::Remove(TableRow* row)
{
    assert(row);
    if (row)
    {
        row->DelayedDelete();
    }

    Invalidate();
    InvalidateChildren();
}

void Table::Clear()
{
    for (auto child : _children)
    {
        child->DelayedDelete();
    }

    Invalidate();
    InvalidateChildren();
}

TableRow* Table::GetRow(unsigned index)
{
    return dynamic_cast<TableRow*>(GetChild(index));
}

const TableRow* Table::GetRow(unsigned index) const
{
    return dynamic_cast<const TableRow*>(GetChild(index));
}

unsigned Table::GetRowCount() const
{
    return GetChildrenCount();
}

unsigned Table::GetDefaultRowHeight() const
{
    return _default_row_height;
}

bool Table::GetShouldClip() const
{
    return false;
}

void Table::Layout(Skin::Base* skin)
{
    // Call the base class.
    Base::Layout(skin);

    int size_remainder = Width();
    int auto_size_columns = 0;

    for (int i = 0; i < MAX_COLUMNS && i < _column_count; ++i)
    {
        size_remainder -= _column_width[i];

        if (_column_width[i] == 0)
        {
            ++auto_size_columns;
        }
    }

    if (auto_size_columns > 1)
    {
        size_remainder /= auto_size_columns;
    }

    bool even = true;
    for (auto i = _children.begin(); i != _children.end(); ++i)
    {
        TableRow* row = dynamic_cast<TableRow*>(*i);
        if (row != nullptr)
        {
            row->SetEven(even);
            even = !even;

            for (int j = 0; j < MAX_COLUMNS && j < _column_count; ++j)
            {
                if (_column_width[j] == 0)
                {
                    row->SetColumnWidth(j, size_remainder);
                }
                else
                {
                    row->SetColumnWidth(j, _column_width[j]);
                }
            }
        }
    }
}

void Table::PostLayout(Skin::Base*)
{
    SizeToChildren();
}

void Table::SizeToContents()
{
    for (int i = 0; i < MAX_COLUMNS; ++i)
    {
        _column_width[i] = 10;
    }

    for (auto i = _children.begin(); i != _children.end(); ++i)
    {
        TableRow* row = dynamic_cast<TableRow*>(*i);
        if (row != nullptr)
        {
            row->SizeToContents();
            for (int j = 0; j < MAX_COLUMNS; ++j)
            {
                if (row->_columns[j])
                {
                    _column_width[j] = std::max(_column_width[j], row->_columns[j]->Width());
                }
            }
        }
    }

    Invalidate();
    InvalidateChildren();
}

}; // namespace Layout

}; // namespace Controls

}; // namespace Gwen
