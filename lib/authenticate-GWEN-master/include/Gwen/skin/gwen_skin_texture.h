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
#include "Gwen/skin/gwen_skin_base.h"
#include "Gwen/skin/gwen_skin_texturing.h"
#include "Gwen/renderer/gwen_texture.h"

namespace Gwen
{
namespace Skin
{

/// \brief A skin using a texture.
class TexturedBase : public Skin::Base
{
public:
    /// \brief Constructor.
    TexturedBase(Renderer::Base* renderer);

    /// \brief Destructor.
    virtual ~TexturedBase() override;

    /// \brief Initializes the skin.
    virtual void Initialize(const std::string& texture_name, const std::string& font_name, float font_size);


    /// \brief Draws a button.
    virtual void DrawButton(Controls::Base* control, bool is_depressed, bool is_hovered, bool is_disabled) override;


    /// \brief Draws a tab button.
    virtual void DrawTabButton(Controls::Base* control, bool is_active, int alignment) override;

    /// \brief Draws an active tab button.
    virtual void DrawTabButtonActive(Controls::Base* control, int alignment) override;

    /// \brief Draws a tab control.
    virtual void DrawTabControl(Controls::Base* control) override;

    /// \brief Draws a tab title bar.
    virtual void DrawTabTitleBar(Controls::Base* control) override;


    /// \brief Draws a menu.
    virtual void DrawMenu(Controls::Base* control, bool is_padding_disabled) override;

    /// \brief Draws a menu item.
    virtual void DrawMenuItem(Controls::Base* control, bool is_submenu_open, bool is_checked) override;

    /// \brief Draws a menu strip.
    virtual void DrawMenuStrip(Controls::Base* control) override;

    /// \brief Draws a menu divider.
    virtual void DrawMenuDivider(Controls::Base* control) override;

    /// \brief Draws a right menu arrow.
    virtual void DrawMenuRightArrow(Controls::Base* control) override;


    /// \brief Draws a shadow.
    virtual void DrawShadow(Controls::Base* control) override;


    /// \brief Draws a status bar.
    virtual void DrawStatusBar(Controls::Base* control) override;


    /// \brief Draws a check box.
    virtual void DrawCheckBox(Controls::Base* control, bool is_selected) override;


    /// \brief Draws a radio button.
    virtual void DrawRadioButton(Controls::Base* control, bool is_selected) override;


    /// \brief Draws a keyboard highlight.
    virtual void DrawKeyboardHighlight(Controls::Base* control, const Gwen::Rectangle& rectangle, int offset) override;


    /// \brief Draws a text box.
    virtual void DrawTextBox(Controls::Base* control) override;


    /// \brief Draws a highlight.
    virtual void DrawHighlight(Controls::Base* control) override;


    /// \brief Draws a scroll bar.
    virtual void DrawScrollBar(Controls::Base* control, bool is_horizontal) override;

    /// \brief Draws a scroll bar's bar.
    virtual void DrawScrollBarBar(Controls::Base* control, bool is_depressed, bool is_hovered, bool is_horizontal) override;

    /// \brief Draws a scroll bar's button.
    virtual void DrawScrollBarButton(Controls::Base* control, int alignment, bool is_depressed, bool is_hovered, bool is_disabled) override;


    /// \brief Draws a progress bar.
    virtual void DrawProgressBar(Controls::Base* control, bool is_horizontal, float progress, const Gwen::Padding& bar_padding, const Gwen::Color& color) override;


    /// \brief Draws a list box.
    virtual void DrawListBox(Controls::Base* control) override;

    /// \brief Draws a list box line.
    virtual void DrawListBoxLine(Controls::Base* control, bool is_selected, bool is_even) override;


    /// \brief Draws a slider.
    virtual void DrawSlider(Controls::Base* control, unsigned number_of_notches, unsigned size) override;

    /// \brief Draws a slider button.
    virtual void DrawSliderButton(Gwen::Controls::Base* control, bool is_depressed) override;

    /// \brief Draws a slider notches.
    virtual void DrawSliderNotches(const Gwen::Rectangle& rectangle, unsigned number_of_notches, unsigned length) override;


    /// \brief Draw combo box.
    virtual void DrawComboBox(Controls::Base* control, bool is_down, bool is_open) override;

    /// \brief Draw combo box down arrow.
    virtual void DrawComboDownArrow(Controls::Base* control, bool is_hovered, bool is_down, bool is_open, bool is_disabled) override;

    /// \brief Draws a tooltip.
    virtual void DrawTooltip(Controls::Base* control) override;

protected:
    /// \brief The textures for the skin.
    struct Textures_t
    {
        /// \brief The status bar texture.
        Texturing::Bordered StatusBar;

        /// \brief The shadow texture.
        Texturing::Bordered Shadow;

        /// \brief The tooltip texture.
        Texturing::Bordered Tooltip;

        /// \brief The check box textures.
        struct CheckBox_t
        {
            /// \brief The active check box textures.
            struct Active_t
            {
                Texturing::Single Normal;
                Texturing::Single Checked;
            } Active;

            /// \brief The disabled check box textures.
            struct Disabled_t
            {
                Texturing::Single Normal;
                Texturing::Single Checked;
            } Disabled;
        } CheckBox;

        /// \brief The radio button textures.
        struct RadioButton_t
        {
            /// \brief The active radio button textures.
            struct Active_t
            {
                Texturing::Single Normal;
                Texturing::Single Checked;
            } Active;

            /// \brief The disabled radio button textures.
            struct Disabled_t
            {
                Texturing::Single Normal;
                Texturing::Single Checked;
            } Disabled;
        } RadioButton;

        /// \brief The text box textures.
        struct TextBox_t
        {
            Texturing::Bordered Normal;
            Texturing::Bordered Focus;
            Texturing::Bordered Disabled;
        } TextBox;

        /// \brief The progress bar textures.
        struct ProgressBar_t
        {
            Texturing::Bordered Back;
        } ProgressBar;

        /// \brief The scroll bar textures.
        struct ScrollBar_t
        {
            Texturing::Bordered TrackV;
            Texturing::Bordered ButtonV_Normal;
            Texturing::Bordered ButtonV_Hover;
            Texturing::Bordered ButtonV_Down;
            Texturing::Bordered ButtonV_Disabled;
            Texturing::Bordered TrackH;
            Texturing::Bordered ButtonH_Normal;
            Texturing::Bordered ButtonH_Hover;
            Texturing::Bordered ButtonH_Down;
            Texturing::Bordered ButtonH_Disabled;

            /// \brief The scroll bar button textures.
            struct Button_t
            {
                Texturing::Bordered Normal[4];
                Texturing::Bordered Hover[4];
                Texturing::Bordered Down[4];
                Texturing::Bordered Disabled[4];
            } Button;
        } ScrollBar;

        /// \brief The menu textures.
        struct Menu_t
        {
            Texturing::Single RightArrow;
            Texturing::Single Check;

            Texturing::Bordered Strip;
            Texturing::Bordered Background;
            Texturing::Bordered BackgroundWithMargin;
            Texturing::Bordered Hover;

        } Menu;

        /// \brief The input textures.
        struct Input_t
        {
            /// \brief The button textures.
            struct Button_t
            {
                Texturing::Bordered Normal;
                Texturing::Bordered Hovered;
                Texturing::Bordered Disabled;
                Texturing::Bordered Pressed;
            } Button;

            /// \brief The list box textures.
            struct ListBox_t
            {
                Texturing::Bordered Background;
                Texturing::Bordered Hovered;
                Texturing::Bordered EvenLine;
                Texturing::Bordered OddLine;
                Texturing::Bordered EvenLineSelected;
                Texturing::Bordered OddLineSelected;
            } ListBox;

            /// \brief The combo box textures.
            struct ComboBox_t
            {
                Texturing::Bordered Normal;
                Texturing::Bordered Hover;
                Texturing::Bordered Down;
                Texturing::Bordered Disabled;

                /// \brief The combo box button textures.
                struct Button_t
                {
                    Texturing::Single Normal;
                    Texturing::Single Hover;
                    Texturing::Single Down;
                    Texturing::Single Disabled;
                } Button;
            } ComboBox;

            /// \brief The slider textures.
            struct Slider_t
            {
                /// \brief The horizontal slider textures.
                struct Horizontal_t
                {
                    Texturing::Single Normal;
                    Texturing::Single Hover;
                    Texturing::Single Down;
                    Texturing::Single Disabled;
                } Horizontal;

                /// \brief The vertical slider textures.
                struct V_t
                {
                    Texturing::Single Normal;
                    Texturing::Single Hover;
                    Texturing::Single Down;
                    Texturing::Single Disabled;
                } Vertical;
            } Slider;
        } Input;

        /// \brief The tab control textures.
        struct Tab_t
        {
            /// \brief The bottom tab control textures.
            struct Bottom_t
            {
                Texturing::Bordered Active;
                Texturing::Bordered Inactive;
            } Bottom;

            /// \brief The top tab control textures.
            struct Top_t
            {
                Texturing::Bordered Active;
                Texturing::Bordered Inactive;
            } Top;

            /// \brief The left tab control textures.
            struct Left_t
            {
                Texturing::Bordered Active;
                Texturing::Bordered Inactive;
            } Left;

            /// \brief The right tab control textures.
            struct Right_t
            {
                Texturing::Bordered Active;
                Texturing::Bordered Inactive;
            } Right;

            /// \brief The tab control textures.
            Texturing::Bordered Control;

            /// \brief The tab control header bar textures.
            Texturing::Bordered HeaderBar;
        } Tab;
    } Textures;

    /// \brief The texture.
    Renderer::Texture _texture;
};

}; // namespace Skin

}; // namespace Gwen
