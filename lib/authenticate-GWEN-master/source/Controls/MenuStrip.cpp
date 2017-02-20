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
#include "Gwen/Controls/MenuStrip.h"

#include "Gwen/skin/gwen_skin_base.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(MenuStrip, Menu)
{
    _inner_panel->SetPadding(Padding(5, 0, 0, 0));

    SetDock(Position::TOP);
    SetBounds(0, 0, 200, 22);
}

void MenuStrip::Layout(Skin::Base* skin)
{
    // Intentionally blank.
}

bool MenuStrip::GetHoverOpenMenu() const
{
    return GetOpen();
}

void MenuStrip::Close()
{
    // Intentionally blank.
}

void MenuStrip::Render(Skin::Base* skin)
{
    skin->DrawMenuStrip(this);
}

void MenuStrip::RenderUnder(Skin::Base*)
{
    // Intentionally blank.
}

void MenuStrip::_OnAddItem(MenuItem* item)
{
    item->SetDock(Position::LEFT);
    item->SetPadding(Padding(10, 0, 10, 0));
    item->SetTextPadding(Padding(5, 0, 5, 0));
    item->SizeToContents();
    item->SetOnStrip(true);
    item->_on_hover_enter.Add(this, &Menu::_OnHoverItem);
}

}; // namespace Controls

}; // namespace Gwen
