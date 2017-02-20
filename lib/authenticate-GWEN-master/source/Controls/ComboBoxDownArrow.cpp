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
#include "Gwen/Controls/ComboBoxDownArrow.h"

namespace Gwen
{
namespace ControlsInternal
{

GWEN_CONTROL_CONSTRUCTOR(ComboBoxDownArrow, Base)
{
    SetMouseInputEnabled(false);
    SetSize(15, 15);
}

void ComboBoxDownArrow::SetComboBox(Controls::ComboBox* combo_box)
{
    _combo_box = combo_box;
}

void ComboBoxDownArrow::Render(Skin::Base* skin)
{
    if (!_combo_box->GetShouldDrawBackground())
    {
        return skin->DrawComboDownArrow(this, false, false, false, _combo_box->IsDisabled());
    }

    skin->DrawComboDownArrow(this, _combo_box->IsHovered(), _combo_box->GetDepressed(), _combo_box->GetOpen(), _combo_box->IsDisabled());
}

}; // namespace ControlsInternal

}; // namespace Gwen
