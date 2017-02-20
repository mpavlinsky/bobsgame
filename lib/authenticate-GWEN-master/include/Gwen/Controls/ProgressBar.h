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

#include "Gwen/Controls/Label.h"
#include "Gwen/skin/gwen_skin_base.h"

namespace Gwen
{
namespace Controls
{

/// \brief This class represents a progress bar.
class ProgressBar : public Label
{
public:
    /// \brief Constructor.
    GWEN_CONTROL(ProgressBar, Label);

    /// \brief Sets the progress bar's value.
    virtual void SetProgress(unsigned progress);

    /// \brief Gets the progress bar's value.
    virtual unsigned GetProgress() const;

    /// \brief Sets the progress bar's maximum value.
    virtual void SetMaximumProgress(unsigned maximum_progress);

    /// \brief Gets the progress bar's maximum value.
    virtual unsigned GetMaximumProgress() const;

    /// \brief Sets the progress bar to vertical.
    virtual void SetVertical();

    /// \brief Sets the progress bar to horizontal.
    virtual void SetHorizontal();

    /// \brief Should the progress bar display its label?
    virtual void SetDisplayLabel(bool display_label, bool as_percentage = true);

    /// \brief Sets the color of the bar.
    virtual void SetColor(const Gwen::Color& color);

protected:
    /// \brief Draws the UI element.
    virtual void Render(Skin::Base* skin) override;

    /// \brief The progress bar color.
    Gwen::Color _color;

    /// \brief The padding between the bounds of the entire widget and the progress bar itself.
    Gwen::Padding _bar_padding;

    /// \brief The progress.
    unsigned _progress;

    /// \brief The maximum progress.
    unsigned _maximum_progress;

    /// \brief Is the progress bar horizontal?
    bool _is_horizontal;

    /// \brief Should the progress bar display its label?
    bool _display_label;

    /// \brief Should the progress bar display its label as a percentage?
    bool _as_percentage;
};

}; // namespace Controls

}; // namespace Gwen
