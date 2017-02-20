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
#include "Gwen/Controls/Base.h"
#include "Gwen/renderer/gwen_texture.h"

namespace Gwen
{
namespace Controls
{

/// \brief This class represents an image panel.
class ImagePanel : public Base
{
public:
    /// \brief Constructor.
    GWEN_CONTROL(ImagePanel, Base);

    /// \brief Destructor.
    virtual ~ImagePanel();

    /// \brief Sets the image name and loads the image.
    virtual void SetImageName(const std::string& name);

    /// \brief Gets the image name.
    virtual std::string GetImageName() const;

    /// \brief Sets the image to stretch.
    virtual void SetStretch(bool stretch);

    /// \brief Gets if the image is stretched.
    virtual bool GetStretch() const;

    /// \brief Sets the UV coordinates.
    virtual void SetUV(float u1, float v1, float u2, float v2);

    /// \brief Sets the draw color.
    virtual void SetDrawColor(const Gwen::Color& color);

    /// \brief Gets the width of the texture.
    virtual unsigned GetTextureWidth();

    /// \brief Gets the height of the texture.
    virtual unsigned GetTextureHeight();

    /// \brief Sizes the control to its contents.
    virtual void SizeToContents();

    /// \brief Did the image panel fail to load?
    virtual bool FailedToLoad();

protected:
    /// \brief Draws the UI element.
    virtual void Render(Skin::Base* skin) override;

    /// \brief The texture.
    Renderer::Texture _texture;

    /// \brief The UV coordinates.
    float _uv[4];

    /// \brief The draw color.
    Gwen::Color _draw_color;

    /// \brief Should the image stretch?
    bool _stretch;
};

}; // namespace Controls

}; // namespace Gwen
