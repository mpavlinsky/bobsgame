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

namespace Gwen
{
namespace Controls
{

/// \brief This class represents a tab strip.
class TabStrip : public Base
{
public:
    /// \brief Constructor.
    GWEN_CONTROL(TabStrip, Base);

    /// \brief Sets the tab position.
    virtual void SetTabPosition(int position);

    /// \brief Can the tab pages be reordered?
    virtual void SetAllowReorder(bool allow_reorder);

    /// \brief Can the tab pages be reordered?
    virtual bool GetAllowReorder();

    /// \brief Should the control clip its children?
    virtual bool GetShouldClip() const override;

    /// \brief Draws the UI element.
    virtual void Layout(Skin::Base* skin) override;

private:
    /// \brief Can the tab pages be reordered?
    bool _allow_reorder;
};

}; // namespace Controls

}; // namespace Gwen
