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
#include "Gwen/Controls/gwen_controls_tooltip.h"

#include "Gwen/Controls/Canvas.h"
#include "Gwen/input/gwen_input_base.h"
#include "Gwen/Utility.h"

namespace Gwen
{
namespace Controls
{
namespace Tooltip
{

/// \brief A pointer to the tooltip.
Controls::Base* _tooltip = nullptr;

void Enable(Controls::Base* control)
{
    // Sanity.
    assert(control != nullptr && control->GetTooltip() != nullptr);
    if (control == nullptr || control->GetTooltip() == nullptr)
    {
        return;
    }

    _tooltip = control;
}

void Disable(Controls::Base* control)
{
    if (_tooltip == control)
    {
        _tooltip = nullptr;
    }
}

void Layout(Gwen::Skin::Base* skin)
{
    // Sanity.
    assert(skin != nullptr);
    if (skin == nullptr)
    {
        return;
    }

    if (_tooltip == nullptr)
    {
        return;
    }

    assert(_tooltip->GetTooltip() != nullptr);
    if (_tooltip->GetTooltip() == nullptr)
    {
        Disable(_tooltip);
        return;
    }

    // Layout the tooltip.
    _tooltip->RecurseLayout(skin);
}

void Render(Gwen::Skin::Base* skin)
{
    // Sanity.
    assert(skin != nullptr);
    if (skin == nullptr)
    {
        return;
    }

    if (_tooltip == nullptr)
    {
        return;
    }

    assert(_tooltip->GetTooltip() != nullptr);
    if (_tooltip->GetTooltip() == nullptr)
    {
        Disable(_tooltip);
        return;
    }

    Renderer::Base* render = skin->GetRender();
    assert(render != nullptr);
    if (render != nullptr)
    {
        Point old_offset = render->GetRenderOffset();
        Point mouse_position = Input::GetMousePosition();
        Rectangle bounds = _tooltip->GetTooltip()->GetBounds();

        Rectangle offset = Gwen::Rectangle(mouse_position._x - bounds._width / 2,
                                           mouse_position._y - bounds._height - 10,
                                           bounds._width,
                                           bounds._height);
        offset = Utility::ClampRectangleToRectangle(offset, _tooltip->GetCanvas()->GetBounds());

        // Calculate the offset on screen bounds.
        render->AddRenderOffset(Point(offset._x, offset._y));
        render->EndClipping();

        skin->DrawTooltip(_tooltip->GetTooltip());

        _tooltip->GetTooltip()->DoRender(skin);

        render->SetRenderOffset(old_offset);
    }
}

bool GetTooltipActive()
{
    return _tooltip != nullptr;
}

}; // namespace Tooltip

}; // namespace Controls

}; // namespace Gwen
