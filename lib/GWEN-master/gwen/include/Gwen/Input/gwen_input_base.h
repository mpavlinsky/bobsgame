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

#include "Gwen/Structures.h"

namespace Gwen
{

namespace Controls
{

// Forward declarations.
class Base;

}; // namespace Controls

namespace Key
{

const unsigned char INVALID = 0;
const unsigned char RETURN = 1;
const unsigned char BACKSPACE = 2;
const unsigned char DEL = 3;
const unsigned char LEFT = 4;
const unsigned char RIGHT = 5;
const unsigned char SHIFT = 6;
const unsigned char TAB = 7;
const unsigned char SPACE = 8;
const unsigned char HOME = 9;
const unsigned char END = 10;
const unsigned char CONTROL = 11;
const unsigned char UP = 12;
const unsigned char DOWN = 13;
const unsigned char ESCAPE = 14;
const unsigned char ALT = 15;
const unsigned char COUNT = 16;

}; // namespace Key

namespace Input
{

/// \brief Removes the focus.
void Blur();

/// \brief Is the key down?
bool IsKeyDown(int key);

/// \brief Is the left mouse button down?
bool IsLeftMouseDown();

/// \brief Is the right mosue button down?
bool IsRightMouseDown();

/// \brief Is a shift key down?
bool IsShiftDown();

/// \brief Is a control key down?
bool IsControlDown();

/// \brief Is the key down?
Gwen::Point GetMousePosition();

/// \brief Handles accelerators.
bool HandleAccelerator(Controls::Base* canvas, char character);

/// \brief Called when the mouse is moved.
void OnMouseMoved(Controls::Base* canvas, int x, int y, int delta_x, int delta_y);

/// \brief Called when the mouse is clicked.
bool OnMouseClicked(Controls::Base* canvas, int button, bool is_down);

/// \brief Called when a key is pressed.
bool OnKeyEvent(Controls::Base* canvas, int key, bool is_down);

/// \brief Called to animate the canvas.
void OnCanvasThink(Controls::Base* canvas);

}; // namespace Input

}; // namespace Gwen
