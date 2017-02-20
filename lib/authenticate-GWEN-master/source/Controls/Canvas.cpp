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
#include "Gwen/Controls/Canvas.h"

#include "Gwen/Animation.h"

#include "Gwen/Controls/gwen_controls_tooltip.h"
#include "Gwen/Controls/Menu.h"

#include "Gwen/skin/gwen_skin_base.h"

namespace Gwen
{
namespace Controls
{

Canvas::Canvas(Gwen::Skin::Base* skin) :
    Base(nullptr),
    _first_tab(nullptr),
    _next_tab(nullptr),
    _processing_delayed_deletes(false)
{
    SetBackgroundColor(Color(0, 0, 0, 0));
    SetBounds(0, 0, 10000, 10000);

    if (skin)
    {
        SetSkin(skin);
    }
}

Canvas::~Canvas()
{
    auto i = _children.begin();
    while (i != _children.end())
    {
        Base* child = *i;
        i = _children.erase(i);
        delete child;
    }
}

Canvas* Canvas::GetCanvas()
{
    return this;
}

void Canvas::Initialize()
{
}

void Canvas::Render()
{
    _Think();

    Gwen::Renderer::Base* render = _skin->GetRender();
    render->Begin();

    // Update the bounds and offets.
    render->SetClippingRegion(GetBounds());
    render->SetRenderOffset(Gwen::Point(0, 0));

    // Draw the background.
    render->SetDrawColor(_background_color);
    render->FillRectangle(GetRenderBounds());

    // Draw the controls.
    DoRender(_skin);

    // Draw the tooltip.
    Tooltip::Render(_skin);

    render->End();
}

void Canvas::AddDelayedDelete(Base* control)
{
    auto control_iterator = std::find(_controls_delete.begin(), _controls_delete.end(), control);
    if (control_iterator == _controls_delete.end())
    {
        _controls_delete.push_back(control);
    }
}

void Canvas::ProcessDelayedDeletes()
{
    _processing_delayed_deletes = true;

    for (unsigned i = 0; i < _controls_delete.size(); ++i)
    {
        Base* control = _controls_delete.at(i);
        assert(control != nullptr);
        if (control != nullptr)
        {
            control->PreDelete(GetSkin());
            delete control;
        }
    }
    _controls_delete.clear();

    _processing_delayed_deletes = false;
}

bool Canvas::InputMouseMoved(int x, int y, int delta_x, int delta_y)
{
    if (Hidden())
    {
        return false;
    }

    if (Tooltip::GetTooltipActive())
    {
        Redraw();
    }

    Gwen::Input::OnMouseMoved(this, x, y, delta_x, delta_y);

    if (!Controls::_hovered_control)
    {
        return false;
    }

    if (Controls::_hovered_control == this)
    {
        return false;
    }

    if (Controls::_hovered_control->GetCanvas() != this)
    {
        return false;
    }

    Controls::_hovered_control->OnMouseMoved(x, y, delta_x, delta_y);
    return true;
}

bool Canvas::InputMouseButton(int button, bool is_down)
{
    if (Hidden())
    {
        return false;
    }

    return Gwen::Input::OnMouseClicked(this, button, is_down);
}

bool Canvas::InputMouseWheel(int wheel)
{
    if (Hidden())
    {
        return false;
    }

    if (!Controls::_hovered_control)
    {
        return false;
    }

    if (Controls::_hovered_control == this)
    {
        return false;
    }

    if (Controls::_hovered_control->GetCanvas() != this)
    {
        return false;
    }

    return Controls::_hovered_control->OnMouseWheeled(wheel);
}

bool Canvas::InputKey(int key, bool is_down)
{
    if (Hidden())
    {
        return false;
    }

    if (key <= Gwen::Key::INVALID)
    {
        return false;
    }

    if (key >= Gwen::Key::COUNT)
    {
        return false;
    }

    return Gwen::Input::OnKeyEvent(this, key, is_down);
}

bool Canvas::InputAccelerator(char character)
{
    if (Hidden())
    {
        return false;
    }

    if (!iswprint(character))
    {
        return false;
    }

    // Handle any accelerators.
    if (Input::HandleAccelerator(this, character))
    {
        return true;
    }

    return false;
}

bool Canvas::InputCharacter(char character)
{
    if (Hidden())
    {
        return false;
    }

    if (!iswprint(character))
    {
        return false;
    }

    // Handle any characters.
    if (!Controls::_keyboard_focus)
    {
        return false;
    }

    if (Controls::_keyboard_focus->GetCanvas() != this)
    {
        return false;
    }

    if (!Controls::_keyboard_focus->Visible())
    {
        return false;
    }

    if (Input::IsControlDown())
    {
        return false;
    }

    return _keyboard_focus->OnCharacter(character);
}

void Canvas::SetBackgroundColor(const Gwen::Color& color)
{
    _background_color = color;
}

void Canvas::_PreDeleteCanvas(Base* control)
{
    if (!_processing_delayed_deletes)
    {
        auto control_iterator = std::find(_controls_delete.begin(), _controls_delete.end(), control);
        if (control_iterator != _controls_delete.end())
        {
            _controls_delete.erase(control_iterator);
        }
    }
}

void Canvas::_OnBoundsChanged(const Gwen::Rectangle& old_bounds)
{
    // Call the base class.
    Base::_OnBoundsChanged(old_bounds);

    InvalidateChildren();
}

void Canvas::_Think()
{
    ProcessDelayedDeletes();

    // Update the input.
    Gwen::Input::OnCanvasThink(this);

    // Update the animation.
    Animation::Think();

    // Sanity.
    if (Hidden())
    {
        return;
    }

    // Reset the tabbing.
    _next_tab = nullptr;
    _first_tab = nullptr;

    // Update the layouts.
    RecurseLayout(_skin);
    Tooltip::Layout(_skin);

    // If there's no next tab, cycle to the start.
    if (_next_tab == nullptr)
    {
        _next_tab = _first_tab;
    }
}

}; // namespace Controls

}; // namespace Gwen
