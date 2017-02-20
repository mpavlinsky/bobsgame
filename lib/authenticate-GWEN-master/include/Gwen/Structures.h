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

namespace Position
{

enum Position
{
    NONE        = 0,
    LEFT        = (1 << 1),
    RIGHT       = (1 << 2),
    TOP         = (1 << 3),
    BOTTOM      = (1 << 4),
    CENTER_V    = (1 << 5),
    CENTER_H    = (1 << 6),
    FILL        = (1 << 7),
    CENTER      = CENTER_V | CENTER_H,
};

}; // namespace Position

/// \brief This class represents a margin, the space between elements.
struct Margin
{
    /// \brief Constructor.
    explicit Margin(int left = 0, int top = 0, int right = 0, int bottom = 0);

    /// \brief Operator.
    bool operator==(const Margin& margin) const;

    /// \brief Operator.
    bool operator!=(const Margin& margin) const;

    /// \brief Operator.
    Margin operator+(const Margin& left_margin) const;

    /// \brief The top of the margin.
    int _top;

    /// \brief The bottom of the margin.
    int _bottom;

    /// \brief The left of the margin.
    int _left;

    /// \brief The right of the margin.
    int _right;
};

/// \brief This class represents padding, the space within an element.
typedef Margin Padding;

/// \brief This class represents a rectangle.
struct Rectangle
{
    /// \brief Constructor.
    explicit Rectangle();

    /// \brief Constructor.
    explicit Rectangle(int x, int y, int width, int height);

    /// \brief Operator.
    bool operator==(const Rectangle& rectangle) const;

    /// \brief Operator.
    bool operator!=(const Rectangle& rectangle) const;

    /// \brief Operator.
    Rectangle operator+(const Rectangle& rectangle) const;

    /// \brief The X coordinate.
    int _x;

    /// \brief The Y coordinate.
    int _y;

    /// \brief The width.
    int _width;

    /// \brief The height.
    int _height;
};

/// \brief This class represents a point.
struct Point
{
    /// \brief Constructor.
    explicit Point();

    /// \brief Constructor.
    explicit Point(int x, int y);

    /// \brief Operator.
    bool operator==(const Point& point) const;

    /// \brief Operator.
    bool operator!=(const Point& point) const;

    /// \brief Operator.
    void operator+=(const Point& point);

    /// \brief Operator.
    Point operator+(const Point& point) const;

    /// \brief Operator.
    void operator-=(const Point& point);

    /// \brief Operator.
    Point operator-(const Point& point) const;

    /// \brief The X coordinate.
    int _x;

    /// \brief The Y coordinate.
    int _y;
};

/// \brief  This class represents a color.
struct Color
{
    /// \brief Constructor.
    explicit Color(unsigned char red = 0, unsigned char green = 0, unsigned char blue = 0, unsigned char alpha = 0);

    /// \brief Operator.
    bool operator==(const Color& color) const;

    /// \brief Operator.
    bool operator!=(const Color& color) const;

    /// \brief Operator.
    void operator=(const Color& color);

    /// \brief Operator.
    void operator+=(const Color& color);

    /// \brief Operator.
    void operator-=(const Color& color);

    /// \brief Operator.
    void operator*=(float scale);

    /// \brief Operator.
    Color operator*(float scale) const;

    /// \brief Operator.
    Color operator-(const Color& color) const;

    /// \brief Operator.
    Color operator+(const Color& color) const;

    /// \brief The red channel.
    unsigned char _red;

    /// \brief The green channel.
    unsigned char _green;

    /// \brief The blue channel.
    unsigned char _blue;

    /// \brief The alpha channel.
    unsigned char _alpha;
};

namespace Colors
{

const Color BLACK(0, 0, 0, 255);
const Color BLUE(0, 0, 255, 255);
const Color GREEN(0, 255, 0, 255);
const Color GREY(200, 200, 200, 255);
const Color LIGHT_GREY(230, 230, 230, 255);
const Color PINK(255, 65, 199, 255);
const Color RED(255, 0, 0, 255);
const Color WHITE(255, 255, 255, 255);
const Color YELLOW(255, 255, 0, 255);

}; // namespace Colors

}; // namespace Gwen
