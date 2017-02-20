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
#include "Gwen/renderer/gwen_font.h"

namespace Gwen
{

namespace Controls
{

// Forward declarations.
class Base;

}; // namespace Controls

namespace Renderer
{

// Forward declarations.
class Base;

}; // namespace Renderer

namespace Skin
{

/// \brief This class represents a base class for a skin.
class Base
{
public:
    /// \brief Constructor.
    explicit Base(Gwen::Renderer::Base* renderer = nullptr);

    /// \brief Destructor.
    virtual ~Base();

    /// \brief Sets the default font.
    virtual void SetDefaultFont(const std::string& face_name = "Arial", float size = 10.0f);

    /// \brief Gets the default font.
    virtual Renderer::Font* GetDefaultFont();

    /// \brief Deallocates a font.
    virtual void ReleaseFont(Renderer::Font* font);

    /// \brief Sets the renderer.
    virtual void SetRender(Gwen::Renderer::Base* renderer);

    /// \brief Gets the renderer.
    virtual Gwen::Renderer::Base* GetRender();


    /// \brief Draws a button.
    virtual void DrawButton(Controls::Base* control, bool is_depressed, bool is_hovered, bool is_disabled) = 0;


    /// \brief Draws a tab button.
    virtual void DrawTabButton(Controls::Base* control, bool is_active, int alignment) = 0;

    /// \brief Draws an active tab button.
    virtual void DrawTabButtonActive(Controls::Base* control, int alignment) = 0;

    /// \brief Draws a tab control.
    virtual void DrawTabControl(Controls::Base* control) = 0;

    /// \brief Draws a tab title bar.
    virtual void DrawTabTitleBar(Controls::Base* control) = 0;


    /// \brief Draws a menu.
    virtual void DrawMenu(Controls::Base* control, bool is_padding_disabled) = 0;

    /// \brief Draws a menu item.
    virtual void DrawMenuItem(Controls::Base* control, bool is_submenu_open, bool is_checked) = 0;

    /// \brief Draws a menu strip.
    virtual void DrawMenuStrip(Controls::Base* control) = 0;

    /// \brief Draws a menu divider.
    virtual void DrawMenuDivider(Controls::Base* control) = 0;

    /// \brief Draws a right menu arrow.
    virtual void DrawMenuRightArrow(Controls::Base* control) = 0;


    /// \brief Draws a shadow.
    virtual void DrawShadow(Controls::Base* control) = 0;


    /// \brief Draws a status bar.
    virtual void DrawStatusBar(Controls::Base* control) = 0;


    /// \brief Draws a check box.
    virtual void DrawCheckBox(Controls::Base* control, bool is_selected) = 0;


    /// \brief Draws a radio button.
    virtual void DrawRadioButton(Controls::Base* control, bool is_selected) = 0;


    /// \brief Draws a keyboard highlight.
    virtual void DrawKeyboardHighlight(Controls::Base* control, const Gwen::Rectangle& rectangle, int offset) = 0;


    /// \brief Draws a text box.
    virtual void DrawTextBox(Controls::Base* control) = 0;


    /// \brief Draws a highlight.
    virtual void DrawHighlight(Controls::Base* control) = 0;


    /// \brief Draws a scroll bar.
    virtual void DrawScrollBar(Controls::Base* control, bool is_horizontal) = 0;

    /// \brief Draws a scroll bar's bar.
    virtual void DrawScrollBarBar(Controls::Base* control, bool is_depressed, bool is_hovered, bool is_horizontal) = 0;

    /// \brief Draws a scroll bar's button.
    virtual void DrawScrollBarButton(Controls::Base* control, int alignment, bool is_depressed, bool is_hovered, bool is_disabled) = 0;


    /// \brief Draws a progress bar.
    virtual void DrawProgressBar(Controls::Base* control, bool is_horizontal, float progress, const Gwen::Padding& bar_padding, const Gwen::Color& color) = 0;


    /// \brief Draws a list box.
    virtual void DrawListBox(Controls::Base* control) = 0;

    /// \brief Draws a list box line.
    virtual void DrawListBoxLine(Controls::Base* control, bool is_selected, bool is_even) = 0;


    /// \brief Draws a slider.
    virtual void DrawSlider(Controls::Base* control, unsigned number_of_notches, unsigned size) = 0;

    /// \brief Draws a slider button.
    virtual void DrawSliderButton(Gwen::Controls::Base* control, bool is_depressed) = 0;

    /// \brief Draws a slider notches.
    virtual void DrawSliderNotches(const Gwen::Rectangle& rectangle, unsigned number_of_notches, unsigned length) = 0;


    /// \brief Draw combo box.
    virtual void DrawComboBox(Controls::Base* control, bool is_down, bool is_open) = 0;

    /// \brief Draw combo box down arrow.
    virtual void DrawComboDownArrow(Controls::Base* control, bool is_hovered, bool is_down, bool is_open, bool is_disabled) = 0;

    /// \brief Draws a tooltip.
    virtual void DrawTooltip(Controls::Base* control) = 0;


    /// \brief The colors for the skin.
    struct
    {
        /// \brief The button colors.
        struct Button_t
        {
            Gwen::Color Normal;
            Gwen::Color Hover;
            Gwen::Color Down;
            Gwen::Color Disabled;
        } Button;

        /// \brief The chat box row colors.
        struct ChatBoxRow_t
        {
            Gwen::Color Normal;
        } ChatBoxRow;

        /// \brief The label colors.
        struct Label_t
        {
            Gwen::Color Text;
        } Label;

        /// \brief The shadowed label colors.
        struct LabelShadowed_t
        {
            Gwen::Color Text;
            Gwen::Color Shadow;
        } LabelShadowed;

        /// \brief The list box row colors.
        struct ListBoxRow_t
        {
            Gwen::Color Normal;
            Gwen::Color Hover;
            Gwen::Color Down;
        } ListBoxRow;

        /// \brief The menu colors.
        struct Menu_t
        {
            Gwen::Color Normal;
            Gwen::Color Hover;
        } Menu;

        /// \brief The progress bar colors.
        struct ProgressBar_t
        {
            Gwen::Color Bar;
            Gwen::Color Text;
        } ProgressBar;

        /// \brief The slider colors.
        struct Slider_t
        {
            Gwen::Color Bar;
            Gwen::Color Notch;
        } Slider;

        /// \brief The tab colors.
        struct Tab_t
        {
            /// \brief The active tab colors.
            struct Active_t
            {
                Gwen::Color Normal;
                Gwen::Color Hover;
                Gwen::Color Down;
                Gwen::Color Disabled;
            } Active;

            /// \brief The inactive tab colors.
            struct Inactive_t
            {
                Gwen::Color Normal;
                Gwen::Color Hover;
                Gwen::Color Down;
                Gwen::Color Disabled;
            } Inactive;

        } Tab;

        /// \brief The text box colors.
        struct TextBox_t
        {
            Gwen::Color Selection;
        } TextBox;

        /// \brief The tooltip text colors.
        struct Tooltip_t
        {
            Gwen::Color Normal;
        } Tooltip;

    } Colors;

protected:
    /// \brief The default font.
    Renderer::Font _default_font;

    /// \brief The renderer.
    Renderer::Base* _render;
};

}; // namespace Skin

}; // namespace Gwen
