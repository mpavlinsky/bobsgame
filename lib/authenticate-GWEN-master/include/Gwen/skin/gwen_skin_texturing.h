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
#include "Gwen/renderer/gwen_texture.h"

namespace Gwen
{
namespace Skin
{
namespace Texturing
{

/// \brief This class draws a single textured rectangle.
class Single
{
public:
    /// \brief Constructor.
    Single();

    /// \brief Initializes the rectangle.
    void Initialize(Renderer::Texture* texture, int x, int y, unsigned width, unsigned height);

    /// \brief Draws the rectangle.
    void Draw(Renderer::Base* render, const Gwen::Rectangle& rectangle, const Gwen::Color& color = Gwen::Colors::WHITE);

    /// \brief Draws the rectangle.
    void DrawCenter(Renderer::Base* render, const Gwen::Rectangle& rectangle, const Gwen::Color& color = Gwen::Colors::WHITE);

private:
    /// \brief The texture.
    Renderer::Texture* _texture;

    /// \brief The texture coordinates.
    float _uv[4];

    /// \brief The width.
    unsigned _width;

    /// \brief The height.
    unsigned _height;
};

/// \brief This class draws a textured rectangle consisting of the following areas:
///        |  0  |  1  |  2  |
///        |  3  |  4  |  5  |
///        |  6  |  7  |  8  |
class Bordered
{
public:
    /// \brief Constructor.
    Bordered();

    /// \brief Initializes the rectangle.
    void Initialize(Renderer::Texture* texture, int x, int y, unsigned width, unsigned height, const Margin& margin);

    /// \brief Draws a rectangle.
    void Draw(Renderer::Base* render, const Gwen::Rectangle& rectangle, const Gwen::Color& color = Gwen::Colors::WHITE, unsigned sub_rectangle_index = ~0);

private:
    /// \brief A helper function to set up a sub rectangle.
    void _SetSubRectangle(unsigned sub_rectangle_index, int x, int y, unsigned width, unsigned height);

    /// \brief A helper function to draw a sub rectangle.
    void _DrawSubRectangle(Renderer::Base* render, unsigned sub_rectangle_index, int x, int y, unsigned w, unsigned h);

    /// \brief The texture.
    Renderer::Texture* _texture;

    /// \brief A helper structure representing a sub rectangle.
    struct SubRectangle
    {
        /// \brief Constructor.
        SubRectangle();

        /// \brief The texture coordinates.
        float _uv[4];
    };

    /// \brief The sub rectangles.
    SubRectangle _sub_rectangles[9];

    /// \brief The margin.
    Margin _margin;

    /// \brief The width.
    unsigned _width;

    /// \brief The height.
    unsigned _height;
};

}; // namespace Texturing

}; // namespace Skin

}; // namespace Gwen
