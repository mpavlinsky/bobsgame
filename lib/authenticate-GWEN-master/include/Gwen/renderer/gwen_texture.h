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

namespace Gwen
{
namespace Renderer
{

// Forward declarations.
class Base;

/// \brief This structure represents a texture.
class Texture
{
public:
    /// \brief Constructor.
    Texture();

    /// \brief Loads the texture.
    void Load(const std::string& name, Renderer::Base* render, bool need_readable = false);

    /// \brief Releases the texture.
    void Release(Renderer::Base* render);

    /// \brief Did the texture fail to load?
    bool FailedToLoad() const;

    /// \brief The name.
    std::string _name;

    /// \brief A pointer to the SDL texture.
    void* _data;

    /// \brief Did the texture fail to load?
    bool _failed;

    /// \brief The width.
    int _width;

    /// \brief The width.
    int _height;

    /// \brief Is the texture readable?
    bool _readable;

    /// \brief A pointer to the SDL surface.
    void* _surface;
};

}; // namespace Renderer

}; // namespace Gwen
