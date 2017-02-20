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
namespace Renderer
{

// Forward declarations.
class Font;
class Texture;

/// \brief Derive this class to implement a renderer.
class Base
{
protected:
    /// \brief Constructor.
    Base();

public:
    /// \brief Destructor.
    virtual ~Base();

    /// \brief Initializes the renderer.
    virtual void Initialize();

    /// \brief Begins drawing a frame.
    virtual void Begin();

    /// \brief Ends drawing a frame.
    virtual void End();

    /// \brief Starts clipping.
    virtual void StartClipping();

    /// \brief Ends clipping.
    virtual void EndClipping();

    /// \brief Loads a texture.
    virtual void LoadTexture(Texture* texture);

    /// \brief Frees a texture.
    virtual void FreeTexture(Texture* texture);

    /// \brief Loads a font.
    virtual void LoadFont(Font* font);

    /// \brief Frees a font.
    virtual void FreeFont(Font* font);

    /// \brief Translates the renderer.
    virtual void Translate(int& x, int& y);

    /// \brief Translates the renderer.
    virtual void Translate(Gwen::Rectangle& rectangle);

    // \brief Sets the offset.
    virtual void SetRenderOffset(const Gwen::Point& offset);

    // \brief Adds to the offset.
    virtual void AddRenderOffset(const Gwen::Point& offset);

    // \brief Gets the offset.
    virtual Gwen::Point GetRenderOffset() const;

    /// \brief Sets the clipping region.
    virtual void SetClippingRegion(const Gwen::Rectangle& rectangle);

    /// \brief Adds to the clipping region.
    virtual void AddClippingRegion(const Gwen::Rectangle& rectangle);

    /// \brief Gets the clipping region.
    virtual Gwen::Rectangle GetClippingRegion() const;

    /// \brief Is the clipping region visible?
    virtual bool GetClippingRegionVisible() const;

    /// \brief Sets the draw color.
    virtual void SetDrawColor(const Color& color);

    /// \brief Draws a rectangle.
    virtual void DrawRectangle(const Gwen::Rectangle& rectangle);

    /// \brief Fills a rectangle.
    virtual void FillRectangle(const Gwen::Rectangle& rectangle);

    /// \brief Draws a rectable with rounded corners.
    virtual void FillShavedCornerRectangle(const Gwen::Rectangle& rectangle, bool slight = false);

    /// \brief Draws a pixel.
    virtual void DrawPixel(int x, int y);

    /// \brief Draws a texture.
    virtual void DrawTexture(Texture* texture, const Gwen::Rectangle& rectangle, float u1, float v1, float u2, float v2);

    /// \brief Draws a sample image.
    virtual void DrawErrorTexture(const Gwen::Rectangle& rectangle);

    /// \brief Gets the color at a specific location on a texture.
    virtual Gwen::Color GetPixelColor(Texture* texture, unsigned x, unsigned y, const Gwen::Color& default_color = Gwen::Color(255, 255, 255, 255)) const;

    /// \brief Draws text.
    virtual void DrawText(Font* font, const Gwen::Point& position, const std::string& text);

    /// \brief Measures text.
    virtual Gwen::Point MeasureText(Font* font, const std::string& text);

private:
    /// \brief The offset.
    Gwen::Point _offset;

    /// \brief The clipping region.
    Gwen::Rectangle _clipping_region;
};

}; // namespace Renderer

}; // namespace Gwen
