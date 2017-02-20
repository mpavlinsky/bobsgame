//
// GWEN
// Copyright (c) 2013-2015 James Lammlein
// Copyright (c) 2011 BQ
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

#include "Gwen/Gwen.h"
#include "Gwen/Input/gwen_input_sdl2.h"

#include "SDL.h"

namespace Gwen
{
namespace Input
{

GwenSDL2::GwenSDL2()
{
    _canvas = nullptr;
}

void GwenSDL2::Initialize(Controls::Canvas* canvas)
{
    _canvas = canvas;
}

bool GwenSDL2::ProcessEvent(const SDL_Event& the_event)
{
    if (!_canvas)
    {
        return false;
    }

    switch (the_event.type)
    {
    case SDL_KEYUP:
    case SDL_KEYDOWN:
        {
            SDL_KeyboardEvent keyboard_event = the_event.key;
            SDL_Scancode scancode = keyboard_event.keysym.scancode;

            int key = Gwen::Key::INVALID;
            switch (scancode)
            {
            case SDL_SCANCODE_RETURN:
            case SDL_SCANCODE_KP_ENTER:
                key = Gwen::Key::RETURN;
                break;
            case SDL_SCANCODE_BACKSPACE:
                key = Gwen::Key::BACKSPACE;
                break;
            case SDL_SCANCODE_DELETE:
                key = Gwen::Key::DEL;
                break;
            case SDL_SCANCODE_LEFT:
                key = Gwen::Key::LEFT;
                break;
            case SDL_SCANCODE_RIGHT:
                key = Gwen::Key::RIGHT;
                break;
            case SDL_SCANCODE_LSHIFT:
                key = Gwen::Key::SHIFT;
                break;
            case SDL_SCANCODE_RSHIFT:
                key = Gwen::Key::SHIFT;
                break;
            case SDL_SCANCODE_TAB:
                key = Gwen::Key::TAB;
                break;
            case SDL_SCANCODE_SPACE:
                key = Gwen::Key::SPACE;
                break;
            case SDL_SCANCODE_HOME:
                key = Gwen::Key::HOME;
                break;
            case SDL_SCANCODE_END:
                key = Gwen::Key::END;
                break;
            case SDL_SCANCODE_LCTRL:
                key = Gwen::Key::CONTROL;
                break;
            case SDL_SCANCODE_RCTRL:
                key = Gwen::Key::CONTROL;
                break;
            case SDL_SCANCODE_UP:
                key = Gwen::Key::UP;
                break;
            case SDL_SCANCODE_DOWN:
                key = Gwen::Key::DOWN;
                break;
            case SDL_SCANCODE_ESCAPE:
                key = Gwen::Key::ESCAPE;
                break;
            case SDL_SCANCODE_LALT:
                key = Gwen::Key::ALT;
                break;
            case SDL_SCANCODE_RALT:
                key = Gwen::Key::ALT;
                break;

            //
            // Notes:
            //
            // Historically, all accelerators were handled with
            // SDL_TEXTINPUT events.  However, if the "control" key is down,
            // no text events are generated for character keys.  This prevented
            // accelerators containing the "control" key from working with SDL2.
            //
            // The following is a temporary work around for some common accelerators.
            // It is not a very robust solution.  However, it allows some
            // basic functionality for now.
            //

            case SDL_SCANCODE_A:
                return _ProcessAccelerator('a', keyboard_event);
                break;
            case SDL_SCANCODE_C:
                return _ProcessAccelerator('c', keyboard_event);
                break;
            case SDL_SCANCODE_S:
                return _ProcessAccelerator('s', keyboard_event);
                break;
            case SDL_SCANCODE_V:
                return _ProcessAccelerator('v', keyboard_event);
                break;
            case SDL_SCANCODE_X:
                return _ProcessAccelerator('x', keyboard_event);
                break;
            case SDL_SCANCODE_Z:
                return _ProcessAccelerator('z', keyboard_event);
                break;
            default:
                return false;
            };

            return _canvas->InputKey(key, keyboard_event.state != 0);
        };
    case SDL_TEXTINPUT:
        {
            // TODO: This will probably need fixing for UTF-8.
            char character = the_event.text.text[0];
            return _canvas->InputCharacter(character);
        };
    case SDL_MOUSEMOTION:
        {
            SDL_MouseMotionEvent mouse_motion_event = the_event.motion;
            return _canvas->InputMouseMoved(mouse_motion_event.x, mouse_motion_event.y, mouse_motion_event.xrel, mouse_motion_event.yrel);
        };
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        {
            SDL_MouseButtonEvent mouse_button_event = the_event.button;

            int button = -1;
            switch (mouse_button_event.button)
            {
            case SDL_BUTTON_LEFT:
                button = 0;
                break;
            case SDL_BUTTON_MIDDLE:
                button = 2;
                break;
            case SDL_BUTTON_RIGHT:
                button = 1;
                break;
            default:
                return false;
            };

            return _canvas->InputMouseButton(button, mouse_button_event.state != 0);
        };
    case SDL_MOUSEWHEEL:
        {
            SDL_MouseWheelEvent mouse_wheel_event = the_event.wheel;
            return _canvas->InputMouseWheel(mouse_wheel_event.y);
        };
    default:
        {
            return false;
        };
    }
}

bool GwenSDL2::_ProcessAccelerator(char character, const SDL_KeyboardEvent& keyboard_event)
{
    bool result = false;

    if (_canvas != nullptr && keyboard_event.state != 0)
    {
        //result = _canvas->InputAccelerator(character);
    }

    return result;
}

}; // namespace Input

}; // namespace Gwen
