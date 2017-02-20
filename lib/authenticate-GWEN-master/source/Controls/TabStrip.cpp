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
#include "Gwen/Controls/TabStrip.h"

#include "Gwen/Controls/TabButton.h"
#include "Gwen/skin/gwen_skin_base.h"
#include "Gwen/Utility.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(TabStrip, Base)
{
    _allow_reorder = false;
}

void TabStrip::SetTabPosition(int position)
{
    SetDock(position);

    if (_dock == Position::TOP)
    {
        SetPadding(Padding(5, 0, 0, 0));
    }

    if (_dock == Position::LEFT)
    {
        SetPadding(Padding(0, 5, 0, 0));
    }

    if (_dock == Position::RIGHT)
    {
        SetPadding(Padding(0, 5, 0, 0));
    }

    if (_dock == Position::BOTTOM)
    {
        SetPadding(Padding(5, 0, 0, 0));
    }

    InvalidateChildren();
}

void TabStrip::SetAllowReorder(bool allow_reorder)
{
    _allow_reorder = allow_reorder;
}

bool TabStrip::GetAllowReorder()
{
    return _allow_reorder;
}

bool TabStrip::GetShouldClip() const
{
    return false;
}

void TabStrip::Layout(Skin::Base* skin)
{
    // Call the base class.
    Base::Layout(skin);

    Gwen::Point size_new = Gwen::Point(0, 0);

    int number = 0;
    for (auto i = _children.begin(); i != _children.end(); ++i)
    {
        TabButton* button = dynamic_cast<TabButton*>(*i);
        if (button != nullptr)
        {
            // Update the button's size.
            button->SizeToContents();

            // Update the size of the largest tab.
            Gwen::Point size = button->GetSize();
            size_new._x = std::max(size_new._x, size._x);
            size_new._y = std::max(size_new._y, size._y);

            int not_first = number > 0 ? -1 : 0;

            Margin margin;
            if (_dock == Position::TOP)
            {
                margin._left = not_first;
                button->SetDock(Position::LEFT);
            }

            if (_dock == Position::LEFT)
            {
                margin._top = not_first;
                button->SetDock(Position::TOP);
            }

            if (_dock == Position::RIGHT)
            {
                margin._right = not_first;
                button->SetDock(Position::TOP);
            }

            if (_dock == Position::BOTTOM)
            {
                margin._left = not_first;
                button->SetDock(Position::LEFT);
            }
            button->SetMargin(margin);

            ++number;
        }
    }

    // Verify the new size based on the docking value.
    if (_dock == Position::TOP || _dock == Position::BOTTOM)
    {
        size_new._x = Width();
    }

    if (_dock == Position::LEFT || _dock == Position::RIGHT)
    {
        size_new._y = Height();
    }

    // Update the size.
    SetSize(size_new);
}

}; // namespace Controls

}; // namespace Gwen
