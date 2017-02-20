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
#include "Gwen/Controls/ComboBox.h"
#include "Gwen/skin/gwen_skin_base.h"

namespace Gwen
{
namespace ControlsInternal
{

/// \brief This class represents a down arrow for the combo box.
class ComboBoxDownArrow : public Controls::Base
{
public:
    /// \brief Constructor.
    GWEN_CONTROL(ComboBoxDownArrow, Controls::Base);

    /// \brief Sets the combo box.
    virtual void SetComboBox(Controls::ComboBox* combo_box);

protected:
    /// \brief Draws the UI element.
    virtual void Render(Skin::Base* skin) override;

    /// \brief A pointer to the combo box.
    Controls::ComboBox* _combo_box;
};

}; // namespace ControlsInternal

}; // namespace Gwen
