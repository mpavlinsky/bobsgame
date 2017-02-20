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
#include "Gwen/Controls/TextBox.h"

#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Controls/TextBoxThink.h"
#include "Gwen/input/gwen_input_base.h"
#include "Gwen/platform/gwen_platform_base.h"
#include "Gwen/skin/gwen_skin_base.h"
#include "Gwen/Utility.h"

namespace Gwen
{
namespace Controls
{

GWEN_CONTROL_CONSTRUCTOR(TextBox, Base)
{
    _label = new Label(this);
    _label->SetAlignment(Position::LEFT | Position::CENTER_V);
    _label->SetKeyboardInputEnabled(false);
    _label->SetMouseInputEnabled(false);
    _label->SetTabable(false);

    _editable = true;
    _select_all_on_focus = false;

    _maximum_text_length = 2056;

    _cursor_begin = 0;
    _cursor_end = 0;

    _next_cursor_color_change = 0.0f;

    SetKeyboardInputEnabled(true);
    SetMouseInputEnabled(true);
    SetPadding(Gwen::Padding(4, 4, 5, 4));
    SetSize(200, 20);
    SetTabable(true);

    AddAccelerator("Ctrl + X", &TextBox::OnCut);
    AddAccelerator("Ctrl + C", &TextBox::OnCopy);
    AddAccelerator("Ctrl + V", &TextBox::OnPaste);
    AddAccelerator("Ctrl + A", &TextBox::OnSelectAll);

    Animation::Add(this, new ControlsInternal::TextBoxThink());
}

bool TextBox::SetSize(int width, int height)
{
    _label->SetSize(width, height);
    return Base::SetSize(width, height);
}

bool TextBox::SetSize(const Point& point)
{
    _label->SetSize(point);
    return Base::SetSize(point);
}

void TextBox::SetEditable(bool editable)
{
    _editable = editable;
}

void TextBox::SetSelectAllOnFocus(bool select_all_on_focus)
{
    _select_all_on_focus = select_all_on_focus;
    if (_select_all_on_focus)
    {
        OnSelectAll(this);
    }
}

void TextBox::SetMaximumTextLength(unsigned length)
{
    _maximum_text_length = length;
}

void TextBox::SetText(const std::string& text)
{
    // Update the label with the text.
    _label->SetText(text);
    _label->SizeToContents();
    OnTextChanged();
}

void TextBox::InsertText(const std::string& text)
{
    // Is the control editable?
    if (!_editable)
    {
        return;
    }

    // Is there a selection?
    if (HasSelection())
    {
        EraseSelection();
    }

    // Sanity.
    if (_cursor_begin > _label->GetTextLength())
    {
        _cursor_begin = _label->GetTextLength();
    }

    // Sanity.
    if (!IsTextAllowed(text, _cursor_begin))
    {
        return;
    }

    // Get the text.
    std::string current_text = _label->GetText();

    // Clamp the text.
    std::string new_text = text;
    unsigned text_size = current_text.size() + new_text.size();
    if (text_size > _maximum_text_length)
    {
        unsigned over_flow = text_size - _maximum_text_length;
        new_text.erase(new_text.end() - over_flow, new_text.end());
    }

    // Add the new text.
    current_text.insert(_cursor_begin, new_text);

    // Store the text.
    int cursor_begin = _cursor_begin;
    SetText(current_text);

    // Update the cursor.
    _cursor_begin = cursor_begin + static_cast<int>(new_text.size());
    _cursor_end = _cursor_begin;

    RefreshCursorBounds();
}

void TextBox::DeleteText(int start, int length)
{
    if (!_editable)
    {
        return;
    }

    std::string current_text = _label->GetText();
    current_text.erase(start, length);

    SetText(current_text);

    if (_cursor_begin > start)
    {
        SetCursorBeginPosition(_cursor_begin - length);
    }

    SetCursorEndPosition(_cursor_begin);
}

std::string TextBox::GetText() const
{
    return _label->GetText();
}

void TextBox::SetCursorBeginPosition(int begin)
{
    if (_cursor_begin == begin)
    {
        return;
    }

    _cursor_begin = begin;
    RefreshCursorBounds();
}

void TextBox::SetCursorEndPosition(int end)
{
    if (_cursor_end == end)
    {
        return;
    }

    _cursor_end = end;
    RefreshCursorBounds();
}

void TextBox::MakeCursorVisible()
{
    int cursor_begin = _label->GetCharacterPosition(_cursor_begin)._x;
    int cursor_end = _label->GetCharacterPosition(_cursor_end)._x;

    // Make sure the start is actually less than the end.
    if (cursor_begin > cursor_end)
    {
        int swapper = cursor_begin;
        cursor_begin = cursor_end;
        cursor_end = swapper;
    }

    // Horizontal cases...
    int x = 0;
    if (HasSelection())
    {
        // There's a selection and part of the selection is past the right edge.
        if (cursor_end > Width() - GetPadding()._left - GetPadding()._right)
        {
            // Calculate how much of the selection is offscreen.
            int offset = Width() - GetPadding()._right - cursor_end;

            // Apply the offset.
            if (cursor_begin + offset >= GetPadding()._left)
            {
                x = offset;
            }
            // Applying the offset will move part of the selection past the left edge.
            else
            {
                // There's enough text to fill the entire text box before the start of the selection.
                if (cursor_begin > Width() - GetPadding()._left - GetPadding()._right)
                {
                    x = GetPadding()._left - cursor_begin;
                }
                // Default to the start of the text.
                else
                {
                    x = GetPadding()._left;
                }
            }
        }
        // Default to the start of the text.
        else
        {
            x = GetPadding()._left;
        }
    }
    else
    {
        // There's no selection and the cursor is located near the right edge.
        if (cursor_begin > Width() - GetPadding()._left - GetPadding()._right)
        {
            x = Width() - GetPadding()._right - cursor_begin;
        }
        // There's no selection and the cursor is located near the left edge.
        else
        {
            x = GetPadding()._left;
        }
    }

    // Vertical cases are all based off of alignment.
    int y = 0;
    if (_label->GetAlignment() & Position::TOP)
    {
        y = GetPadding()._top;
    }
    else if (_label->GetAlignment() & Position::BOTTOM)
    {
        y = Height() - _label->Height() - GetPadding()._bottom;
    }
    else
    {
        y = (Height() - _label->Height()) / 2;
    }

    _label->SetPosition(x, y);
}

void TextBox::MoveCursorToBegin()
{
    _cursor_begin = 0;
    _cursor_end = 0;
    RefreshCursorBounds();
}

void TextBox::MoveCursorToEnd()
{
    _cursor_begin = _label->GetTextLength();
    _cursor_end = _label->GetTextLength();
    RefreshCursorBounds();
}

void TextBox::RefreshCursorBounds()
{
    _next_cursor_color_change = Gwen::Platform::GetTimeInSeconds() + 0.5f;
    _cursor_color = Gwen::Color(30, 30, 30, 255);

    MakeCursorVisible();

    Gwen::Rectangle position = _label->GetCharacterPosition(_cursor_begin);
    position._x += _label->X();

    Gwen::Rectangle end = _label->GetCharacterPosition(_cursor_end);
    end._x += _label->X();

    _selection_bounds._x = std::min(position._x, end._x);
    _selection_bounds._y = GetPadding()._top;
    _selection_bounds._width = std::max(position._x, end._x) - _selection_bounds._x;
    _selection_bounds._height = Height() - GetPadding()._top - GetPadding()._bottom;

    _cursor_bounds._x = position._x;
    _cursor_bounds._y = GetPadding()._top;
    _cursor_bounds._width = 1;
    _cursor_bounds._height = Height() - GetPadding()._top - GetPadding()._bottom;

    Redraw();
}

void TextBox::UpdateCursorColor()
{
    if (_next_cursor_color_change > Gwen::Platform::GetTimeInSeconds())
    {
        return;
    }

    if (!HasFocus())
    {
        _next_cursor_color_change = Gwen::Platform::GetTimeInSeconds() + 0.5f;
        return;
    }

    Gwen::Color cursor_color = Gwen::Color(241, 241, 241, 255);
    if (_cursor_color == cursor_color)
    {
        cursor_color = Gwen::Color(30, 30, 30, 255);
    }

    _next_cursor_color_change = Gwen::Platform::GetTimeInSeconds() + 0.5f;
    _cursor_color = cursor_color;
    Redraw();
}

std::string TextBox::GetSelection() const
{
    if (!HasSelection())
    {
        return "";
    }

    int start = std::min(_cursor_begin, _cursor_end);
    int end = std::max(_cursor_begin, _cursor_end);

    const std::string& current_text = _label->GetText();
    return current_text.substr(start, end - start);
}

void TextBox::EraseSelection()
{
    int start = std::min(_cursor_begin, _cursor_end);
    int end = std::max(_cursor_begin, _cursor_end);
    DeleteText(start, end - start);

    // Update the cursor position.
    _cursor_begin = start;
    _cursor_end = start;
}

bool TextBox::HasSelection() const
{
    return _cursor_begin != _cursor_end;
}

bool TextBox::GetAcceleratorOnlyOnFocus() const
{
    return true;
}

void TextBox::OnKeyboardFocus()
{
    if (_select_all_on_focus)
    {
        OnSelectAll(this);
    }
    else if (HasSelection())
    {
        SetCursorEndPosition(_cursor_begin);
    }
}

bool TextBox::OnCharacter(char character)
{
    if (character == '\t')
    {
        return false;
    }

    std::string text;
    text += character;
    InsertText(text);
    return true;
}

bool TextBox::OnKeyReturn(bool is_down)
{
    if (!is_down)
    {
        return true;
    }

    _on_return_pressed.Call(this);
    return true;
}

bool TextBox::OnKeyBackspace(bool is_down)
{
    if (!is_down)
    {
        return true;
    }

    if (HasSelection())
    {
        EraseSelection();
        return true;
    }

    if (_cursor_begin == 0)
    {
        return true;
    }

    DeleteText(_cursor_begin - 1, 1);
    return true;
}

bool TextBox::OnKeyDelete(bool is_down)
{
    if (!is_down)
    {
        return true;
    }

    if (HasSelection())
    {
        EraseSelection();
        return true;
    }

    if (_cursor_begin >= _label->GetTextLength())
    {
        return true;
    }

    DeleteText(_cursor_begin, 1);
    return true;
}

bool TextBox::OnKeyHome(bool is_down)
{
    if (!is_down)
    {
        return true;
    }

    _cursor_begin = 0;

    if (!Gwen::Input::IsShiftDown())
    {
        _cursor_end = _cursor_begin;
    }

    RefreshCursorBounds();
    return true;
}

bool TextBox::OnKeyEnd(bool is_down)
{
    if (!is_down)
    {
        return true;
    }

    _cursor_begin = _label->GetTextLength();

    if (!Gwen::Input::IsShiftDown())
    {
        _cursor_end = _cursor_begin;
    }

    RefreshCursorBounds();
    return true;
}

bool TextBox::OnKeyLeft(bool is_down)
{
    if (!is_down)
    {
        return true;
    }

    if (_cursor_begin > 0)
    {
        --_cursor_begin;
    }

    if (!Gwen::Input::IsShiftDown())
    {
        _cursor_end = _cursor_begin;
    }

    RefreshCursorBounds();
    return true;
}

bool TextBox::OnKeyRight(bool is_down)
{
    if (!is_down)
    {
        return true;
    }

    if (_cursor_begin < _label->GetTextLength())
    {
        ++_cursor_begin;
    }

    if (!Gwen::Input::IsShiftDown())
    {
        _cursor_end = _cursor_begin;
    }

    RefreshCursorBounds();
    return true;
}

void TextBox::OnCut(Gwen::Controls::Base*)
{
    if (!HasSelection())
    {
        return;
    }

    Platform::SetClipboardText(GetSelection());
    EraseSelection();
}

void TextBox::OnCopy(Gwen::Controls::Base*)
{
    if (!HasSelection())
    {
        return;
    }

    Platform::SetClipboardText(GetSelection());
}

void TextBox::OnPaste(Gwen::Controls::Base*)
{
    InsertText(Platform::GetClipboardText());
}

void TextBox::OnSelectAll(Gwen::Controls::Base*)
{
    _cursor_end = 0;
    _cursor_begin = _label->GetTextLength();
    RefreshCursorBounds();
}

void TextBox::OnMouseEnter()
{
    // Grab the focus.
    Focus();

    // Call the base function.
    Base::OnMouseEnter();
}

void TextBox::OnMouseMoved(int x, int y, int, int)
{
    if (Gwen::Controls::_mouse_focus != this)
    {
        return;
    }

    int position = _label->GetClosestCharacter(Gwen::Point(x, y));
    SetCursorBeginPosition(position);
}

void TextBox::OnMouseClickLeft(int x, int y, bool down)
{
    int position = _label->GetClosestCharacter(Gwen::Point(x, y));
    if (down)
    {
        SetCursorBeginPosition(position);
        SetCursorEndPosition(position);
        Gwen::Controls::_mouse_focus = this;
    }
    else
    {
        if (Gwen::Controls::_mouse_focus == this)
        {
            SetCursorBeginPosition(position);
            Gwen::Controls::_mouse_focus = nullptr;
        }
    }
}

void TextBox::OnMouseDoubleClickLeft(int, int)
{
    OnSelectAll(this);
}

void TextBox::Layout(Gwen::Skin::Base* skin)
{
    RefreshCursorBounds();
}

void TextBox::PostLayout(Gwen::Skin::Base*)
{
}

void TextBox::OnTextChanged()
{
    if (_select_all_on_focus)
    {
        OnSelectAll(this);
    }

    if (_cursor_begin > _label->GetTextLength())
    {
        SetCursorBeginPosition(_label->GetTextLength());
    }

    if (_cursor_end > _label->GetTextLength())
    {
        SetCursorEndPosition(_label->GetTextLength());
    }

    _on_text_changed.Call(this);
}

bool TextBox::IsTextAllowed(const std::string&, int) const
{
    return true;
}

void TextBox::Render(Gwen::Skin::Base* skin)
{
    if (GetShouldDrawBackground())
    {
        skin->DrawTextBox(this);
    }

    // Update the clipping region for the children.
    Gwen::Point point = LocalPositionToCanvas(Gwen::Point(0, 0));
    Gwen::Padding padding = GetPadding();

    Gwen::Rectangle bounds = GetBounds();
    bounds._x = point._x + padding._left - _cursor_bounds._width;
    bounds._y = point._y + padding._top;
    bounds._width -= padding._left + padding._right - _cursor_bounds._width * 2;
    bounds._height -= padding._top + padding._bottom;

    // Store the new clipping region.
    skin->GetRender()->SetClippingRegion(bounds);
    skin->GetRender()->StartClipping();

    if (HasFocus())
    {
        // If selected...
        if (_cursor_begin != _cursor_end)
        {
            // Draw selection.
            skin->GetRender()->SetDrawColor(GetSkin()->Colors.TextBox.Selection);
            skin->GetRender()->FillRectangle(_selection_bounds);
        }

        // Draw caret.
        skin->GetRender()->SetDrawColor(_cursor_color);
        skin->GetRender()->FillRectangle(_cursor_bounds);
    }
}

void TextBox::RenderFocus(Gwen::Skin::Base* skin)
{
}

}; // namespace Controls

}; // namespace Gwen
