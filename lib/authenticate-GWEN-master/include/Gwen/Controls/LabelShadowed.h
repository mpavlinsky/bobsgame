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
#include "Gwen/Controls/Text.h"

namespace Gwen
{
namespace Controls
{

/// \brief This class represents a control which contains a shadowed text element.
class LabelShadowed : public Base
{
public:
    /// \brief Constructor.
    GWEN_CONTROL(LabelShadowed, Base);

    /// \brief Destructor.
    virtual ~LabelShadowed() override;

    /// \brief Sets the text.
    virtual void SetText(const std::string& text);

    /// \brief Gets the text.
    virtual std::string GetText() const;

    /// \brief Sets the font.
    virtual void SetFont(std::string name, int size, bool is_bold);

    /// \brief Sets the font.
    virtual void SetFont(Renderer::Font* font);

    /// \brief Gets the font.
    virtual Renderer::Font* GetFont();

    /// \brief Sets the color of the text.
    virtual void SetTextColor(const Gwen::Color& color);

    /// \brief Gets the color of the text.
    virtual Gwen::Color GetTextColor() const;

    /// \brief Sets the color of the text shadow.
    virtual void SetShadowColor(const Gwen::Color& color);

    /// \brief Gets the color of the text shadow.
    virtual Gwen::Color GetShadowColor() const;

    /// \brief Sets the offset of the text shadow.
    virtual void SetShadowOffset(const Gwen::Point& offset);

    /// \brief Gets the offset of the text shadow.
    virtual Gwen::Point GetShadowOffset() const;

    /// \brief Sets the alignment of the text.
    virtual void SetAlignment(int alignment);

    /// \brief Sets the alignment of the text.
    virtual void SetAlignment(const Gwen::Position::Position& alignment);

    /// \brief Gets the alignment of the text.
    virtual Gwen::Position::Position GetAlignment();

    /// \brief Sets the wrap.
    virtual void SetWrap(bool do_wrap);

    /// \brief Gets the wrap.
    virtual bool GetWrap() const;

    /// \brief Sets the text padding.
    virtual void SetTextPadding(const Padding& padding);

    /// \brief Gets the text padding.
    virtual Padding GetTextPadding() const;

    /// \brief Gets the length of the text.
    virtual int GetTextLength() const;

    /// \brief Gets the position of a character.
    Gwen::Rectangle GetCharacterPosition(unsigned character) const;

    /// \brief Gets the closest character to the point.
    int GetClosestCharacter(const Gwen::Point& point) const;

    /// \brief Sizes the control to its contents.
    virtual void SizeToContents();

    /// \brief Called before the control is deleted.
    virtual void PreDelete(Gwen::Skin::Base* skin) override;

    /// \brief Lays out the UI element.
    virtual void PostLayout(Skin::Base* skin) override;

protected:
    /// \brief Called when the bounds change.
    virtual void _OnBoundsChanged(const Gwen::Rectangle& old_bounds) override;

    /// \brief The font.
    Renderer::Font* _font;

    /// \brief The text.
    ControlsInternal::Text* _text;

    /// \brief The shadow offset.
    Gwen::Point _shadow_offset;

    /// \brief The shadow text.
    ControlsInternal::Text* _text_shadow;

    /// \brief The alignment.
    Gwen::Position::Position _alignment;
};

}; // namespace Controls

}; // namespace Gwen
