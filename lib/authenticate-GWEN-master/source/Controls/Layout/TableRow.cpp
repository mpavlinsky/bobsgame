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
#include "Gwen/Controls/Layout/TableRow.h"

#include "Gwen/Controls/Label.h"
#include "Gwen/Utility.h"

namespace Gwen
{
namespace Controls
{
namespace Layout
{

GWEN_CONTROL_CONSTRUCTOR(TableRow, Base)
{
    for (int i = 0; i < MAX_COLUMNS; ++i)
    {
        _columns[i] = nullptr;
    }

    _column_count = 0;

    SetEven(false);
    SetHidden(false);
    SetMouseInputEnabled(true);
    SetSelected(false);
    SetUserData(nullptr);
}

void TableRow::SetUserData(void* user_data)
{
    _user_data = user_data;
}

void* TableRow::GetUserData() const
{
    return _user_data;
}

void TableRow::SetColumnCount(int count)
{
    if (count == _column_count)
    {
        return;
    }

    if (count >= MAX_COLUMNS)
    {
        _column_count = MAX_COLUMNS;
    }

    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        if (i < count)
        {
            if (!_columns[i])
            {
                _columns[i] = new Label(this);
                _columns[i]->SetDock(Position::LEFT);
                _columns[i]->SetPadding(Padding(3, 3, 3, 3));
            }
        }
        else if (_columns[i])
        {
            _columns[i]->DelayedDelete();
            _columns[i] = nullptr;
        }

        _column_count = count;
    }
}

void TableRow::SetColumnWidth(int column, int width)
{
    if (!_columns[column])
    {
        return;
    }

    if (_columns[column]->Width() == width)
    {
        return;
    }

    _columns[column]->SetWidth(width);
}

void TableRow::DelayedDelete()
{
    for (int i = 0; i < MAX_COLUMNS; ++i)
    {
        if (_columns[i] != nullptr)
        {
            _columns[i]->DelayedDelete();
            _columns[i] = nullptr;
        }
    }

    Base::DelayedDelete();
}

void TableRow::SetCellText(int cell, const std::string& text)
{
    if (!_columns[cell])
    {
        return;
    }

    _columns[cell]->SetText(text);
}

std::string TableRow::GetCellText(int cell)
{
    if (!_columns[cell])
    {
        return "";
    }

    return _columns[cell]->GetText();
}

void TableRow::SetTextColor(const Gwen::Color& color)
{
    for (int i = 0; i < _column_count; ++i)
    {
        if (!_columns[i])
        {
            continue;
        }

        _columns[i]->SetTextColor(color);
    }
}

void TableRow::SetSelected(bool selected)
{
    _selected = selected;
}

bool TableRow::GetSelected() const
{
    return _selected;
}

void TableRow::SetEven(bool even)
{
    _even = even;
}

bool TableRow::GetEven()
{
    return _even;
}

void TableRow::SizeToContents()
{
    int height = 0;

    for (int i = 0; i < _column_count; ++i)
    {
        if (_columns[i] != nullptr)
        {
            // Note: More than one child here because the label has a child built into it.
            if (_columns[i]->GetChildrenCount() > 1)
            {
                _columns[i]->SizeToChildren();
            }
            else
            {
                _columns[i]->SizeToContents();
            }

            height = std::max(height, _columns[i]->Height());
        }
    }

    SetHeight(height);
}

}; // namespace Layout

}; // namespace Controls

}; // namespace Gwen
