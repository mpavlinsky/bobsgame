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
#include "Gwen/Controls/ProgressBar.h"

#include "Gwen/Animation.h"
#include "Gwen/Controls/ScrollControl.h"
#include "Gwen/Utility.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(ProgressBar, Label)
{
    _bar_padding = Gwen::Padding(2, 2, 2, 2);
    _progress = 0;
    _maximum_progress = 100;
    _display_label = true;
    _as_percentage = true;

    SetAlignment(Position::CENTER);
    SetBounds(Rectangle(0, 0, 128, 32));
    SetHorizontal();
    SetMouseInputEnabled(true);
    SetTextPadding(Padding(3, 0, 3, 0));

    Gwen::Skin::Base* skin = GetSkin();
    assert(skin != nullptr);
    if (skin != nullptr)
    {
        SetColor(skin->Colors.ProgressBar.Bar);
        SetTextColor(skin->Colors.ProgressBar.Text);
    }
}

void ProgressBar::SetProgress(unsigned progress)
{
    if (progress > _maximum_progress)
    {
        progress = _maximum_progress;
    }

    _progress = progress;

    if (_display_label)
    {
        if (_as_percentage)
        {
            int value = static_cast<int>(static_cast<float>(_progress) / static_cast<float>(_maximum_progress) * 100.0f);
            SetText(Utility::ToString(value) + " %");
        }
        else
        {
            SetText(Utility::ToString(_progress) + "/" + Utility::ToString(_maximum_progress));
        }
    }
}

unsigned ProgressBar::GetProgress() const
{
    return _progress;
}

void ProgressBar::SetMaximumProgress(unsigned maximum_progress)
{
    _maximum_progress = maximum_progress;

    // Reset the progress incase the maximum progress is now less than the progress.
    SetProgress(_progress);
}

unsigned ProgressBar::GetMaximumProgress() const
{
    return _maximum_progress;
}

void ProgressBar::SetVertical()
{
    _is_horizontal = false;
}

void ProgressBar::SetHorizontal()
{
    _is_horizontal = true;
}

void ProgressBar::SetDisplayLabel(bool display_label, bool as_percentage)
{
    _display_label = display_label;
    _as_percentage = as_percentage;
}

void ProgressBar::SetColor(const Gwen::Color& color)
{
    _color = color;
}

void ProgressBar::Render(Skin::Base* skin)
{
    float progress = static_cast<float>(_progress) / static_cast<float>(_maximum_progress);
    skin->DrawProgressBar(this, _is_horizontal, progress, _bar_padding, _color);
}

}; // namespace Controls

}; // namespace Gwen
