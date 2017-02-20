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

#include "Gwen/renderer/gwen_renderer_base.h"

#include "SDL.h"

namespace Gwen
{
namespace Renderer
{

/// \brief This class represents an SDL2 renderer.
class SDL2 : public Renderer::Base
{
public:
    /// \brief Constructor.
    SDL2(SDL_Window* window, SDL_Renderer* renderer);

    /// \brief Destructor.
    virtual ~SDL2() override;

    /// \brief Starts clipping.
    virtual void StartClipping() override;

    /// \brief Ends clipping.
    virtual void EndClipping() override;

    /// \brief Loads a texture.
    virtual void LoadTexture(Texture* texture) override;

    /// \brief Frees a texture.
    virtual void FreeTexture(Texture* texture) override;

    /// \brief Loads a font.
    virtual void LoadFont(Renderer::Font* pFont) override;

    /// \brief Frees a font.
    virtual void FreeFont(Renderer::Font* pFont) override;

    /// \brief Sets the draw color.
    virtual void SetDrawColor(const Gwen::Color& color) override;

    /// \brief Draws a rectangle.
    void DrawRectangle(const Gwen::Rectangle& rectangle) override;

    /// \brief Fills a rectangle.
    virtual void FillRectangle(const Gwen::Rectangle& rectangle) override;

    /// \brief Draws a texture.
    void DrawTexture(Texture* texture, const Gwen::Rectangle& rectangle, float u1 = 0.0f, float v1 = 0.0f, float u2 = 1.0f, float v2 = 1.0f) override;

    /// \brief Gets the color at a specific location on a texture.
    Gwen::Color GetPixelColor(Renderer::Texture* texture, unsigned x, unsigned y, const Gwen::Color& default_color) const override;

    /// \brief Draws text.
    virtual void DrawText(Renderer::Font* font, const Gwen::Point& position, const std::string& text) override;

    /// \brief Measures text.
    virtual Gwen::Point MeasureText(Renderer::Font* pFont, const std::string& text) override;

protected:
    /// \brief The SDL window.
    SDL_Window* _window;

    /// \brief The SDL renderer.
    SDL_Renderer* _renderer;

    /// \brief The draw color.
    SDL_Color _color;
};

}; // namespace Renderer

}; // namespace Gwen
