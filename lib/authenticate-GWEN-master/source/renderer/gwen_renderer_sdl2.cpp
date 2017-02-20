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
#include "Gwen/renderer/gwen_renderer_sdl2.h"

#include "Gwen/renderer/gwen_renderer_base.h"
#include "Gwen/renderer/gwen_font.h"
#include "Gwen/renderer/gwen_texture.h"
#include "Gwen/Utility.h"

#include "SDL_image.h"
#include "SDL_ttf.h"

namespace Gwen
{
namespace Renderer
{

SDL2::SDL2(SDL_Window* window, SDL_Renderer* renderer) :
    _window(window),
    _renderer(renderer)
{
    assert(_window != nullptr);
    assert(_renderer != nullptr);
    _color = { 255, 255, 255, 255 };
}

SDL2::~SDL2()
{
    // This class does not own these pointers.
    // So, don't delete them here.
    _window = nullptr;
    _renderer = nullptr;
}

void SDL2::StartClipping()
{
    const Gwen::Rectangle& rectangle = GetClippingRegion();
    const SDL_Rect sdl_rectangle = { rectangle._x, rectangle._y, rectangle._width, rectangle._height };
    SDL_RenderSetClipRect(_renderer, &sdl_rectangle);
}

void SDL2::EndClipping()
{
    SDL_RenderSetClipRect(_renderer, nullptr);
}

void SDL2::LoadTexture(Renderer::Texture* texture)
{
    if (!texture)
    {
        return;
    }

    if (texture->_data)
    {
        FreeTexture(texture);
    }

    SDL_Texture* sdl_texure = nullptr;
    if (texture->_readable)
    {
        // The format of a texture cannot be retrieved once it is loaded in SDL2.
        // So, keep the surface to read from.
        SDL_Surface* surface = IMG_Load(texture->_name.c_str());
        sdl_texure = SDL_CreateTextureFromSurface(_renderer, surface);
        texture->_surface = surface;
    }
    else
    {
        sdl_texure = IMG_LoadTexture(_renderer, texture->_name.c_str());
    }

    if (sdl_texure)
    {
        int width = 0;
        int height = 0;
        SDL_QueryTexture(sdl_texure, nullptr, nullptr, &width, &height);

        texture->_data = sdl_texure;
        texture->_width = width;
        texture->_height = height;
        texture->_failed = false;
    }
    else
    {
        texture->_data = nullptr;
        texture->_failed = true;
    }
}

void SDL2::FreeTexture(Renderer::Texture* pTexture)
{
    SDL_DestroyTexture(static_cast<SDL_Texture*>(pTexture->_data));
    pTexture->_data = nullptr;

    if (pTexture->_surface)
    {
        SDL_FreeSurface(static_cast<SDL_Surface*>(pTexture->_surface));
        pTexture->_surface = nullptr;
        pTexture->_readable = false;
    }
}

void SDL2::LoadFont(Renderer::Font* font)
{
    std::string file(font->_face_name);
    if (file.find(".ttf") == std::string::npos)
    {
        file += ".ttf";
    }

    TTF_Font* ttf_font = TTF_OpenFont(file.c_str(), static_cast<int>(font->_size));
    if (!ttf_font)
    {
        printf("Font load error: %s\n", TTF_GetError());
    }
    font->_data = ttf_font;
}

void SDL2::FreeFont(Renderer::Font* font)
{
    if (font->_data)
    {
        TTF_CloseFont(static_cast<TTF_Font*>(font->_data));
        font->_data = nullptr;
    }
}

void SDL2::SetDrawColor(const Gwen::Color& color)
{
    _color.r = color._red;
    _color.g = color._green;
    _color.b = color._blue;
    _color.a = color._alpha;
    SDL_SetRenderDrawColor(_renderer, color._red, color._green, color._blue, color._alpha);
}

void SDL2::DrawRectangle(const Gwen::Rectangle& rectangle)
{
    Gwen::Rectangle inner_rectangle = rectangle;
    Translate(inner_rectangle);

    const SDL_Rect sdl_rectangle = { inner_rectangle._x, inner_rectangle._y, inner_rectangle._width, inner_rectangle._height };
    SDL_RenderDrawRect(_renderer, &sdl_rectangle);
}

void SDL2::FillRectangle(const Gwen::Rectangle& rectangle)
{
    Gwen::Rectangle inner_rectangle = rectangle;
    Translate(inner_rectangle);

    const SDL_Rect sdl_rectangle = { inner_rectangle._x, inner_rectangle._y, inner_rectangle._width, inner_rectangle._height };
    SDL_RenderFillRect(_renderer, &sdl_rectangle);
}

void SDL2::DrawTexture(Renderer::Texture* texture, const Gwen::Rectangle& rectangle, float u1, float v1, float u2, float v2)
{
    SDL_Texture* sdl_texture = static_cast<SDL_Texture*>(texture->_data);
    if (sdl_texture == nullptr)
    {
        return DrawErrorTexture(rectangle);
    }

    Gwen::Rectangle inner_rectangle = rectangle;
    Translate(inner_rectangle);

    const unsigned width = texture->_width;
    const unsigned height = texture->_height;

    const SDL_Rect source =
    {
        static_cast<int>(u1 * width),
        static_cast<int>(v1 * height),
        static_cast<int>((u2 - u1) * width),
        static_cast<int>((v2 - v1) * height)
    };

    const SDL_Rect destination =
    {
        inner_rectangle._x,
        inner_rectangle._y,
        inner_rectangle._width,
        inner_rectangle._height
    };

    SDL_RenderCopy(_renderer, sdl_texture, &source, &destination);
}

Gwen::Color SDL2::GetPixelColor(Renderer::Texture* texture, unsigned x, unsigned y, const Gwen::Color& default_color) const
{
    SDL_Surface* surface = static_cast<SDL_Surface*>(texture->_surface);
    if (!texture->_readable || !surface)
    {
        return default_color;
    }

    if (SDL_MUSTLOCK(surface) != 0)
    {
        SDL_LockSurface(surface);
    }

    const char* memory = static_cast<char*>(surface->pixels) + y * surface->pitch + x * sizeof(Uint32);
    const Uint32 pixel = *reinterpret_cast<const Uint32*>(memory);

    Gwen::Color color = default_color;
    SDL_GetRGBA(pixel, surface->format, &color._red, &color._green, &color._blue, &color._alpha);

    if (SDL_MUSTLOCK(surface) != 0)
    {
        SDL_UnlockSurface(surface);
    }

    return color;
}

void SDL2::DrawText(Renderer::Font* font, const Gwen::Point& position, const std::string& text)
{
    assert(font != nullptr);
    if (font != nullptr)
    {
        TTF_Font* ttf_font = static_cast<TTF_Font*>(font->_data);
        assert(ttf_font != nullptr);
        if (ttf_font != nullptr)
        {
            int x = position._x;
            int y = position._y;
            Translate(x, y);

            SDL_Surface* surface = TTF_RenderUTF8_Blended(ttf_font, text.c_str(), _color);
            assert(surface != nullptr);
            if (surface != nullptr)
            {
                SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
                assert(texture != nullptr);
                if (texture != nullptr)
                {
                    SDL_SetTextureAlphaMod(texture, _color.a);

                    int width = 0;
                    int height = 0;
                    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

                    const SDL_Rect destination_rectangle = { x, y, width, height };
                    SDL_RenderCopy(_renderer, texture, nullptr, &destination_rectangle);
                }

                // Clean up the texture.
                if (texture != nullptr)
                {
                    SDL_DestroyTexture(texture);
                    texture = nullptr;
                }
            }

            // Clean up the surface.
            if (surface != nullptr)
            {
                SDL_FreeSurface(surface);
                surface = nullptr;
            }
        }
    }
}

Gwen::Point SDL2::MeasureText(Renderer::Font* font, const std::string& text)
{
    TTF_Font* ttf_font = static_cast<TTF_Font*>(font->_data);

    // If the font doesn't exist...
    if (!ttf_font)
    {
        FreeFont(font);
        LoadFont(font);
        ttf_font = static_cast<TTF_Font*>(font->_data);
    }

    if (!ttf_font)
    {
        return Gwen::Point(0, 0);
    }

    int width = 0;
    int height = 0;
    TTF_SizeUTF8(ttf_font, text.c_str(), &width, &height);

    return Point(width, height);
}

}; // Renderer

}; // Gwen
