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
#include "Gwen/input/gwen_input_base.h"

#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Canvas.h"
#include "Gwen/platform/gwen_platform_base.h"

namespace Gwen
{
namespace Input
{

/// \brief A helper structure to store key data.
struct KeyData
{
    /// \brief Constructor.
    KeyData()
    {
        for (int i = 0; i < Gwen::Key::COUNT; ++i)
        {
            _state[i] = false;
            _next_repeat[i] = 0;
        }

        _target = nullptr;
        _left_mouse_down = false;
        _right_mouse_down = false;
    }

    /// \brief The key state.
    bool _state[Gwen::Key::COUNT];

    /// \brief The time of the next repeat.
    float _next_repeat[Gwen::Key::COUNT];

    /// \brief The target control.
    Controls::Base* _target;

    /// \brief Is the left mouse down?
    bool _left_mouse_down;

    /// \brief Is the right mouse down?
    bool _right_mouse_down;
};

/// \brief The double click speed.
const float DOUBLE_CLICK_SPEED = 0.5f;

/// \brief The maximum number of mouse buttons.
const unsigned MAX_MOUSE_BUTTONS = 5;

/// \brief The key repeat rate.
const float KEY_REPEAT_RATE = 0.03f;

/// \brief The key repeat delay.
const float KEY_REPEAT_DELAY = 0.3f;

/// \brief The last key's data.
static KeyData _key_data;

/// \brief The mouse position.
static Gwen::Point _mouse_position;

/// \brief The last click time.
static float _last_click_time[MAX_MOUSE_BUTTONS];

/// \brief The last click position.
static Gwen::Point _last_click_position;

/// \brief A helper function to update the hovered control.
static void _UpdateHoveredControl(Controls::Base* canvas)
{
    Controls::Base* hovered = nullptr;

    // Calculate the hovered controls.
    std::vector<Controls::Base*> hovered_controls = canvas->GetControlsAt(_mouse_position._x, _mouse_position._y);

    if (!hovered_controls.empty())
    {
        // Try to set the first visible, mouse enabled control as the hovered control.
        for (auto control : hovered_controls)
        {
            if (control->Visible() && control->GetMouseInputEnabled())
            {
                hovered = control;
                break;
            }
        }

        // If the hovered controls are hidden and not mouse enabled...
        if (hovered == nullptr)
        {
            // Set the first control as the hovered control.
            hovered = *hovered_controls.begin();
        }
    }

    if (hovered != Gwen::Controls::_hovered_control)
    {
        if (Gwen::Controls::_hovered_control)
        {
            Controls::Base* old_hovered = Gwen::Controls::_hovered_control;
            Gwen::Controls::_hovered_control = nullptr;
            old_hovered->OnMouseLeave();
        }

        Gwen::Controls::_hovered_control = hovered;
        if (Gwen::Controls::_hovered_control)
        {
            Gwen::Controls::_hovered_control->OnMouseEnter();
        }
    }
}

/// \brief A helper function to find the keyboard focus.
static bool FindKeyboardFocus(Controls::Base* control)
{
    if (!control)
    {
        return false;
    }

    if (control->GetKeyboardInputEnabled())
    {
        for (auto i = control->GetChildren().begin(); i != control->GetChildren().end(); ++i)
        {
            Controls::Base* child = *i;
            if (child == Gwen::Controls::_keyboard_focus)
            {
                return false;
            }
        }

        control->Focus();
        return true;
    }

    return FindKeyboardFocus(control->GetParent());
}

void Blur()
{
    if (Gwen::Controls::_keyboard_focus)
    {
        Gwen::Controls::_keyboard_focus->Blur();
    }
}

bool IsKeyDown(int key)
{
    return _key_data._state[key];
}

bool IsLeftMouseDown()
{
    return _key_data._left_mouse_down;
}

bool IsRightMouseDown()
{
    return _key_data._right_mouse_down;
}

bool IsShiftDown()
{
    return IsKeyDown(Gwen::Key::SHIFT);
}

bool IsControlDown()
{
    return IsKeyDown(Gwen::Key::CONTROL);
}

Gwen::Point GetMousePosition()
{
    return _mouse_position;
}

bool HandleAccelerator(Controls::Base* canvas, char character)
{
    // Build the accelerator search string.
    std::string accelerator_string;
    if (Gwen::Input::IsControlDown())
    {
        accelerator_string += "CTRL+";
    }

    if (Gwen::Input::IsShiftDown())
    {
        accelerator_string += "SHIFT+";
    }

    character = toupper(character);
    accelerator_string += character;

    if (Gwen::Controls::_keyboard_focus && Gwen::Controls::_keyboard_focus->HandleAccelerator(accelerator_string))
    {
        return true;
    }

    if (Gwen::Controls::_mouse_focus && Gwen::Controls::_mouse_focus->HandleAccelerator(accelerator_string))
    {
        return true;
    }

    if (canvas->HandleAccelerator(accelerator_string))
    {
        return true;
    }

    return false;
}

void OnMouseMoved(Controls::Base* canvas, int x, int y, int delta_x, int delta_y)
{
    _mouse_position._x = x;
    _mouse_position._y = y;

    Gwen::Controls::Base* target = Gwen::Controls::_mouse_focus;
    if (target && target->GetCanvas() != canvas)
    {
        target = nullptr;
    }

    if (target && !target->Visible())
    {
        target = nullptr;
    }

    if (target)
    {
        target->OnMouseMoved(x, y, delta_x, delta_y);
    }

    _UpdateHoveredControl(canvas);
}

bool OnMouseClicked(Controls::Base* canvas, int button, bool is_down)
{
    // If we click on a control that isn't a menu, close all the open menus.
    if (is_down && (!Gwen::Controls::_hovered_control || !Gwen::Controls::_hovered_control->GetMenuComponent()))
    {
        canvas->CloseMenus();
    }

    Gwen::Controls::Base* target = Gwen::Controls::_mouse_focus;
    if (!target)
    {
        target = Gwen::Controls::_hovered_control;
    }

    if (target && target->GetCanvas() != canvas)
    {
        target = nullptr;
    }

    if (target && !target->Visible())
    {
        target = nullptr;
    }

    if (!target)
    {
        return false;
    }

    // Sanity.
    if (button >= MAX_MOUSE_BUTTONS)
    {
        return false;
    }

    if (button == 0)
    {
        _key_data._left_mouse_down = is_down;
    }
    else if (button == 1)
    {
        _key_data._right_mouse_down = is_down;
    }

    bool is_double_click = false;
    if (is_down &&
        _last_click_position._x == _mouse_position._x &&
        _last_click_position._y == _mouse_position._y &&
        (Gwen::Platform::GetTimeInSeconds() - _last_click_time[button]) < DOUBLE_CLICK_SPEED)
    {
        is_double_click = true;
    }

    if (is_down && !is_double_click)
    {
        _last_click_time[button] = Gwen::Platform::GetTimeInSeconds();
        _last_click_position = _mouse_position;
    }

    if (is_down)
    {
        if (!FindKeyboardFocus(target))
        {
            if (Gwen::Controls::_keyboard_focus)
            {
                Gwen::Controls::_keyboard_focus->Blur();
            }
        }
    }

    switch (button)
    {
    case 0:
        if (is_double_click)
        {
            target->OnMouseDoubleClickLeft(_mouse_position._x, _mouse_position._y);
        }
        else
        {
            target->OnMouseClickLeft(_mouse_position._x, _mouse_position._y, is_down);
        }

        return true;

    case 1:
        if (is_double_click)
        {
            target->OnMouseDoubleClickRight(_mouse_position._x, _mouse_position._y);
        }
        else
        {
            target->OnMouseClickRight(_mouse_position._x, _mouse_position._y, is_down);
        }

        return true;
    }

    return false;
}

bool OnKeyEvent(Controls::Base* canvas, int key, bool is_down)
{
    Gwen::Controls::Base* target = Gwen::Controls::_keyboard_focus;
    if (target && target->GetCanvas() != canvas)
    {
        target = nullptr;
    }

    if (target && !target->Visible())
    {
        target = nullptr;
    }

    if (is_down)
    {
        if (!_key_data._state[key])
        {
            _key_data._state[key] = true;
            _key_data._next_repeat[key] = Gwen::Platform::GetTimeInSeconds() + KEY_REPEAT_DELAY;
            _key_data._target = target;

            if (target)
            {
                return target->OnKeyPress(key);
            }
        }
    }
    else
    {
        if (_key_data._state[key])
        {
            _key_data._state[key] = false;

            if (target)
            {
                return target->OnKeyRelease(key);
            }
        }
    }

    return false;
}

void OnCanvasThink(Controls::Base* canvas)
{
    Gwen::Point mouse_position = Gwen::Input::GetMousePosition();
    Gwen::Input::OnMouseMoved(canvas, mouse_position._x, mouse_position._y, 0, 0);

    if (Gwen::Controls::_mouse_focus &&
        (!Gwen::Controls::_mouse_focus->Visible() || !Gwen::Controls::_mouse_focus->GetMouseInputEnabled()))
    {
        Gwen::Controls::_mouse_focus = nullptr;
    }

    if (Gwen::Controls::_keyboard_focus &&
        (!Gwen::Controls::_keyboard_focus->Visible() || !Gwen::Controls::_keyboard_focus->GetKeyboardInputEnabled()))
    {
        Gwen::Controls::_keyboard_focus = nullptr;
    }

    if (!Gwen::Controls::_hovered_control ||
        !Gwen::Controls::_hovered_control->Visible())
    {
        _UpdateHoveredControl(canvas);
    }

    if (!Gwen::Controls::_keyboard_focus)
    {
        return;
    }

    if (Gwen::Controls::_keyboard_focus->GetCanvas() != canvas)
    {
        return;
    }

    // Simulate key repeats.
    float time = Gwen::Platform::GetTimeInSeconds();
    for (int i = 0; i < Gwen::Key::COUNT; ++i)
    {
        if (_key_data._state[i] && _key_data._target != Gwen::Controls::_keyboard_focus)
        {
            _key_data._state[i] = false;
            continue;
        }

        if (_key_data._state[i] && time > _key_data._next_repeat[i])
        {
            _key_data._next_repeat[i] = Gwen::Platform::GetTimeInSeconds() + KEY_REPEAT_RATE;
            if (Gwen::Controls::_keyboard_focus)
            {
                Gwen::Controls::_keyboard_focus->OnKeyPress(i);
            }
        }
    }
}

}; // namespace Input

}; // namespace Gwen
