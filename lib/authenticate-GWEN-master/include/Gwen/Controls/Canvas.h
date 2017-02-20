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
#include "Gwen/input/gwen_input_base.h"

#include <set>

namespace Gwen
{
namespace Controls
{

/// \brief This class represents a canvas.
class Canvas : public Base
{
    friend class Controls::Base;

public:
    /// \brief Constructor.
    Canvas(Skin::Base* skin);

    /// \brief Destructor.
    virtual ~Canvas() override;

    /// \brief Gets the canvas.
    virtual Canvas* GetCanvas() override;

    /// \brief Call this to fully initialize the canvas.
    void Initialize();

    /// \brief Draws the canvas.
    using Base::Render;
    void Render();

    /// \brief Adds a delayed delete.
    void AddDelayedDelete(Base* control);

    /// \brief Processes any delayed deletes.
    void ProcessDelayedDeletes();

    /// \brief Call to move the mouse.
    bool InputMouseMoved(int x, int y, int delta_x, int delta_y);

    /// \brief Call to update a mouse button.
    bool InputMouseButton(int button, bool is_down);

    /// \brief Call to update the mouse wheel.
    bool InputMouseWheel(int wheel);

    /// \brief Call to update a key.
    bool InputKey(int key, bool is_down);

    /// \brief Call to update an accelerator.
    bool InputAccelerator(char character);

    /// \brief Call to update a character.
    bool InputCharacter(char character);

    /// \brief Sets the background color.
    void SetBackgroundColor(const Gwen::Color& color);

    /// \brief The first tab.
    Base* _first_tab;

    /// \brief The next tab.
    Base* _next_tab;

protected:
    /// \brief Predeletes a control from the canvas.
    void _PreDeleteCanvas(Base* control);

    /// \brief Called when the bounds change.
    virtual void _OnBoundsChanged(const Gwen::Rectangle& old_bounds) override;

    /// \brief A helper function to process input.
    void _Think();

    /// \brief A flag for processing delayed deletes.
    bool _processing_delayed_deletes;

    /// \brief The controls to delete.
    std::vector<Base*> _controls_delete;

    /// \brief The background color.
    Gwen::Color _background_color;
};

}; // namespace Controls

}; // namespace Gwen
