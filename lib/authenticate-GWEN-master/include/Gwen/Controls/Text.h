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

namespace Gwen
{
namespace ControlsInternal
{

/// \brief An internal control to draw text.
class Text : public Controls::Base
{
public:
    /// \brief Constructor.
    GWEN_CONTROL(Text, Controls::Base);

    /// \brief Sets the text.
    void SetText(const std::string& text);

    /// \brief Gets the text.
    std::string GetText() const;

    /// \brief Sets the font.
    void SetFont(Renderer::Font* font);

    /// \brief Gets the font.
    Renderer::Font* GetFont();

    /// \brief Sets the color of the text.
    virtual void SetTextColor(const Gwen::Color& color);

    /// \brief Gets the color of the text.
    virtual Gwen::Color GetTextColor() const;

    /// \brief Sets the color override of the text.
    virtual void SetTextColorOverride(const Gwen::Color& color);

    /// \brief Gets the color override of the text.
    virtual Gwen::Color GetTextColorOverride();

    /// \brief Sets the text changed.
    virtual void SetTextChanged(bool has_text_changed);

    /// \brief Sets the text wrap.
    virtual void SetWrap(bool do_wrap);

    /// \brief Gets the text wrap.
    virtual bool GetWrap() const;

    /// \brief Gets the position of the character.
    Gwen::Rectangle GetCharacterPosition(unsigned character);

    /// \brief Picks the closest character to the point.
    int GetClosestCharacter(const Gwen::Point& point);

    /// \brief Gets the length of the text.
    unsigned GetLength() const;

    /// \brief Gets the number of lines.
    virtual unsigned GetLineCount();

    /// \brief Gets a line.
    virtual Text* GetLine(int index);

    /// \brief Gets a line.
    virtual int GetLineFromCharacter(int index);

    /// \brief Gets a character.
    virtual int GetStartCharacterFromLine(int index);

    /// \brief Gets a character.
    virtual int GetEndCharacterFromLine(int index);

    /// \brief Gets a character.
    virtual int GetCharacterPositionOnLine(int index);

    /// \brief Refresh the size.
    void RefreshSize();

    /// \brief Lays out the control.
    void Layout(Skin::Base* skin) override;

protected:
    /// \brief Called when the scale of the control changes.
    virtual void _OnScaleChanged() override;

    /// \brief Draws the UI element.
    void Render(Skin::Base* skin) override;

private:
    /// \brief Refreshes the word wrap.
    virtual void RefreshSizeWrap();

    /// \brief Splits the text into lines.
    void _SplitLines(const std::string& text, std::vector<std::string>& result);

    /// \brief The text.
    std::string _text;

    /// \brief The font.
    Renderer::Font* _font;

    /// \brief The color of the text.
    Gwen::Color _color;

    /// \brief The override color of the text.
    Gwen::Color _color_override;

    /// \brief Wrap the text?
    bool _wrap;

    /// \brief Did the text change?
    bool _changed;

    /// \brief The lines of text.
    std::list<Text*> _lines;
};

}; // namespace ControlsInternal

}; // namespace Gwen
