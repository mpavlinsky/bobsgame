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
#include "Gwen/Controls/Label.h"

namespace Gwen
{
namespace Controls
{

/// \brief A control which contains a writable text element.
class TextBox : public Base
{
    /// \brief Constructor.
    GWEN_CONTROL(TextBox, Base);

    /// \brief Sets the size of the text box.
    virtual bool SetSize(int width, int height) override;

    /// \brief Sets the size of the text box.
    virtual bool SetSize(const Point& point) override;

    /// \brief Sets the text box as editable.
    virtual void SetEditable(bool editable);

    /// \brief Sets the text box to select all on focus.
    virtual void SetSelectAllOnFocus(bool select_all_on_focus);

    /// \brief Sets the maximum text length.
    virtual void SetMaximumTextLength(unsigned length);

    /// \brief Sets the text.
    virtual void SetText(const std::string& text);

    /// \brief Inserts text.
    virtual void InsertText(const std::string& text);

    /// \brief Deletes text.
    virtual void DeleteText(int start, int length);

    /// \brief Gets the text.
    virtual std::string GetText() const;

    /// \brief Sets the beginning position of the cursor.
    virtual void SetCursorBeginPosition(int begin);

    /// \brief Sets the end position of the cursor.
    virtual void SetCursorEndPosition(int end);

    /// \brief Makes the cursor visible.
    virtual void MakeCursorVisible();

    /// \brief Moves the cursor to the beginning.
    virtual void MoveCursorToBegin();

    /// \brief Moves the cursor to the end.
    virtual void MoveCursorToEnd();

    /// \brief Refreshes the bounds of the cursor.
    virtual void RefreshCursorBounds();

    /// \brief Updates the cursor color.
    virtual void UpdateCursorColor();

    /// \brief Gets the selection.
    virtual std::string GetSelection() const;

    /// \brief Erases the selection.
    virtual void EraseSelection();

    /// \brief Is there a selection?
    virtual bool HasSelection() const;

    /// \brief Only handle accelerators when the control has focus.
    virtual bool GetAcceleratorOnlyOnFocus() const override;

    /// \brief Called when the control gains keyboard focus.
    virtual void OnKeyboardFocus() override;

    /// \brief Called when a character key is pressed.
    virtual bool OnCharacter(char character) override;

    /// \brief Called when the return key is pressed.
    virtual bool OnKeyReturn(bool is_down) override;

    /// \brief Called when the back space key is pressed.
    virtual bool OnKeyBackspace(bool is_down) override;

    /// \brief Called when the delete key is pressed.
    virtual bool OnKeyDelete(bool is_down) override;

    /// \brief Called when the home key is pressed.
    virtual bool OnKeyHome(bool is_down) override;

    /// \brief Called when the end key is pressed.
    virtual bool OnKeyEnd(bool is_down) override;

    /// \brief Called when the left key is pressed.
    virtual bool OnKeyLeft(bool is_down) override;

    /// \brief Called when the right key is pressed.
    virtual bool OnKeyRight(bool is_down) override;

    /// \brief Called when the cut accelerator is pressed.
    virtual void OnCut(Gwen::Controls::Base* control) override;

    /// \brief Called when the copy accelerator is pressed.
    virtual void OnCopy(Gwen::Controls::Base* control) override;

    /// \brief Called when the paste accelerator is pressed.
    virtual void OnPaste(Gwen::Controls::Base* control) override;

    /// \brief Called when the select all accelerator is pressed.
    virtual void OnSelectAll(Gwen::Controls::Base* control) override;

    /// \brief Called when the mouse enters the control.
    virtual void OnMouseEnter() override;

    /// \brief Called when the mouse is moved.
    virtual void OnMouseMoved(int x, int y, int delta_x, int delta_y) override;

    /// \brief Called when the left mouse button is pressed.
    virtual void OnMouseClickLeft(int x, int y, bool is_down) override;

    /// \brief Called when the left mouse button is double clicked.
    virtual void OnMouseDoubleClickLeft(int x, int y) override;

    /// \brief Lays out the UI element.
    virtual void Layout(Gwen::Skin::Base* skin) override;

    /// \brief Lays out the UI element.
    virtual void PostLayout(Gwen::Skin::Base* skin) override;

    /// \brief An event for when the text is changed.
    Event::Caller _on_text_changed;

    /// \brief An event for when return is pressed.
    Event::Caller _on_return_pressed;

protected:
    /// \brief Called when the text is changed.
    virtual void OnTextChanged();

    /// \brief Is text allowed in this text box?
    virtual bool IsTextAllowed(const std::string& text, int position) const;

    /// \brief Draws the UI element.
    virtual void Render(Gwen::Skin::Base* skin) override;

    /// \brief Draws the UI element.
    virtual void RenderFocus(Gwen::Skin::Base* skin) override;

    /// \brief The lable.
    Label* _label;

    /// \brief Is the text box editable?
    bool _editable;

    /// \brief Should the text box select all on focus?
    bool _select_all_on_focus;

    /// \brief The maximum length of the text.
    unsigned _maximum_text_length;

    /// \brief The cursor begin position.
    int _cursor_begin;

    /// \brief The cursor end position.
    int _cursor_end;

    /// \brief The selection bounds.
    Gwen::Rectangle _selection_bounds;

    /// \brief The cursor bounds.
    Gwen::Rectangle _cursor_bounds;

    /// \brief The next time to change the cursor's color.
    float _next_cursor_color_change;

    /// \brief The cursor's color.
    Gwen::Color _cursor_color;
};

}; // namespace Controls

}; // namespace Gwen
