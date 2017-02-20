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
#include "Gwen/skin/gwen_skin_texture.h"

#include "Gwen/Controls/Base.h"

#include "Gwen/skin/gwen_skin_base.h"
#include "Gwen/skin/gwen_skin_texturing.h"

#include "Gwen/renderer/gwen_texture.h"

namespace Gwen
{
namespace Skin
{

TexturedBase::TexturedBase(Gwen::Renderer::Base* renderer) :
    Gwen::Skin::Base(renderer)
{
}

TexturedBase::~TexturedBase()
{
    _texture.Release(_render);
}

void TexturedBase::Initialize(const std::string& texture_name, const std::string& font_name, float font_size)
{
    _default_font._face_name                = font_name;
    _default_font._size                     = font_size;

    _texture.Load(texture_name, GetRender(), true);

    Colors.Button.Normal                    = GetRender()->GetPixelColor(&_texture, 4 + 8 * 0, 508, Color(255, 255, 0));
    Colors.Button.Hover                     = GetRender()->GetPixelColor(&_texture, 4 + 8 * 3, 508, Color(255, 255, 0));
    Colors.Button.Down                      = GetRender()->GetPixelColor(&_texture, 4 + 8 * 3, 508, Color(255, 255, 0));
    Colors.Button.Disabled                  = GetRender()->GetPixelColor(&_texture, 4 + 8 * 0, 508, Color(255, 255, 0));

    Colors.ChatBoxRow.Normal                = GetRender()->GetPixelColor(&_texture, 4 + 8 * 3, 508, Color(255, 255, 0));

    Colors.Label.Text                       = GetRender()->GetPixelColor(&_texture, 4 + 8 * 5, 508, Color(255, 255, 0));

    Colors.LabelShadowed.Text               = GetRender()->GetPixelColor(&_texture, 4 + 8 * 5, 508, Color(255, 255, 0));
    Colors.LabelShadowed.Shadow             = GetRender()->GetPixelColor(&_texture, 4 + 8 * 0, 508, Color(255, 255, 0));

    Colors.ListBoxRow.Normal                = GetRender()->GetPixelColor(&_texture, 4 + 8 * 3, 508, Color(255, 255, 0));
    Colors.ListBoxRow.Hover                 = GetRender()->GetPixelColor(&_texture, 4 + 8 * 3, 508, Color(255, 255, 0));
    Colors.ListBoxRow.Down                  = GetRender()->GetPixelColor(&_texture, 4 + 8 * 3, 508, Color(255, 255, 0));

    Colors.Menu.Normal                      = GetRender()->GetPixelColor(&_texture, 4 + 8 * 3, 508, Color(255, 255, 0));
    Colors.Menu.Hover                       = GetRender()->GetPixelColor(&_texture, 4 + 8 * 3, 508, Color(255, 255, 0));

    Colors.ProgressBar.Bar                  = GetRender()->GetPixelColor(&_texture, 4 + 8 * 2, 500, Color(255, 255, 0));
    Colors.ProgressBar.Text                 = GetRender()->GetPixelColor(&_texture, 4 + 8 * 2, 508, Color(255, 255, 0));

    Colors.Slider.Bar                       = GetRender()->GetPixelColor(&_texture, 4 + 8 * 0, 508, Color(255, 255, 0));
    Colors.Slider.Notch                     = GetRender()->GetPixelColor(&_texture, 4 + 8 * 0, 508, Color(255, 255, 0));

    Colors.Tab.Active.Normal                = GetRender()->GetPixelColor(&_texture, 4 + 8 * 0, 508, Color(255, 255, 0));
    Colors.Tab.Active.Hover                 = GetRender()->GetPixelColor(&_texture, 4 + 8 * 2, 508, Color(255, 255, 0));
    Colors.Tab.Active.Down                  = GetRender()->GetPixelColor(&_texture, 4 + 8 * 0, 508, Color(255, 255, 0));
    Colors.Tab.Active.Disabled              = GetRender()->GetPixelColor(&_texture, 4 + 8 * 0, 508, Color(255, 255, 0));
    Colors.Tab.Inactive.Normal              = GetRender()->GetPixelColor(&_texture, 4 + 8 * 0, 508, Color(255, 255, 0));
    Colors.Tab.Inactive.Hover               = GetRender()->GetPixelColor(&_texture, 4 + 8 * 2, 508, Color(255, 255, 0));
    Colors.Tab.Inactive.Down                = GetRender()->GetPixelColor(&_texture, 4 + 8 * 0, 508, Color(255, 255, 0));
    Colors.Tab.Inactive.Disabled            = GetRender()->GetPixelColor(&_texture, 4 + 8 * 0, 508, Color(255, 255, 0));

    Colors.TextBox.Selection                = GetRender()->GetPixelColor(&_texture, 4 + 8 * 2, 508, Color(255, 255, 0));

    Colors.Tooltip.Normal                   = GetRender()->GetPixelColor(&_texture, 4 + 8 * 19, 500, Color(255, 255, 0));

    Textures.StatusBar.Initialize(&_texture, 128, 288, 127, 31, Margin(8, 8, 8, 8));

    Textures.Shadow.Initialize(&_texture, 448, 0, 31, 31, Margin(8, 8, 8, 8));

    Textures.Tooltip.Initialize(&_texture, 128, 320, 127, 31, Margin(8, 8, 8, 8));

    Textures.CheckBox.Active.Checked.Initialize(&_texture, 448, 32, 15, 15);
    Textures.CheckBox.Active.Normal.Initialize(&_texture, 464, 32, 15, 15);
    Textures.CheckBox.Disabled.Checked.Initialize(&_texture, 448, 48, 15, 15);
    Textures.CheckBox.Disabled.Normal.Initialize(&_texture, 464, 48, 15, 15);

    Textures.RadioButton.Active.Checked.Initialize(&_texture, 448, 64, 15, 15);
    Textures.RadioButton.Active.Normal.Initialize(&_texture, 464, 64, 15, 15);
    Textures.RadioButton.Disabled.Checked.Initialize(&_texture, 448, 80, 15, 15);
    Textures.RadioButton.Disabled.Normal.Initialize(&_texture, 464, 80, 15, 15);

    Textures.TextBox.Normal.Initialize(&_texture, 0, 150, 127, 21, Margin(4, 4, 4, 4));
    Textures.TextBox.Focus.Initialize(&_texture, 0, 172, 127, 21, Margin(4, 4, 4, 4));
    Textures.TextBox.Disabled.Initialize(&_texture, 0, 193, 127, 21, Margin(4, 4, 4, 4));

    Textures.ProgressBar.Back.Initialize(&_texture, 384, 0, 31, 31, Margin(8, 8, 8, 8));

    Textures.ScrollBar.TrackV.Initialize(&_texture, 384, 208, 15, 127, Margin(4, 4, 4, 4));
    Textures.ScrollBar.ButtonV_Normal.Initialize(&_texture, 384 + 16, 208, 15, 127, Margin(4, 4, 4, 4));
    Textures.ScrollBar.ButtonV_Hover.Initialize(&_texture, 384 + 32, 208, 15, 127, Margin(4, 4, 4, 4));
    Textures.ScrollBar.ButtonV_Down.Initialize(&_texture, 384 + 48, 208, 15, 127, Margin(4, 4, 4, 4));
    Textures.ScrollBar.ButtonV_Disabled.Initialize(&_texture, 384 + 64, 208, 15, 127, Margin(4, 4, 4, 4));
    Textures.ScrollBar.TrackH.Initialize(&_texture, 384, 128, 127, 15, Margin(4, 4, 4, 4));
    Textures.ScrollBar.ButtonH_Normal.Initialize(&_texture, 384, 128 + 16, 127, 15, Margin(4, 4, 4, 4));
    Textures.ScrollBar.ButtonH_Hover.Initialize(&_texture, 384, 128 + 32, 127, 15, Margin(4, 4, 4, 4));
    Textures.ScrollBar.ButtonH_Down.Initialize(&_texture, 384, 128 + 48, 127, 15, Margin(4, 4, 4, 4));
    Textures.ScrollBar.ButtonH_Disabled.Initialize(&_texture, 384, 128 + 64, 127, 15, Margin(4, 4, 4, 4));

    for (int i = 0; i < 4; ++i)
    {
        Textures.ScrollBar.Button.Normal[i].Initialize(&_texture, 464 + 0, 208 + i * 16, 15, 15, Margin(2, 2, 2, 2));
        Textures.ScrollBar.Button.Hover[i].Initialize(&_texture, 480, 208 + i * 16, 15, 15, Margin(2, 2, 2, 2));
        Textures.ScrollBar.Button.Down[i].Initialize(&_texture, 464, 272 + i * 16, 15, 15, Margin(2, 2, 2, 2));
        Textures.ScrollBar.Button.Disabled[i].Initialize(&_texture, 480 + 48, 272 + i * 16, 15, 15, Margin(2, 2, 2, 2));
    }

    Textures.Menu.RightArrow.Initialize(&_texture, 464, 112, 15, 15);
    Textures.Menu.Check.Initialize(&_texture, 448, 112, 15, 15);
    Textures.Menu.Strip.Initialize(&_texture, 0, 128, 127, 21, Margin(1, 1, 1, 1));
    Textures.Menu.BackgroundWithMargin.Initialize(&_texture, 128, 128, 127, 63, Margin(24, 8, 8, 8));
    Textures.Menu.Background.Initialize(&_texture, 128, 192, 127, 63, Margin(8, 8, 8, 8));
    Textures.Menu.Hover.Initialize(&_texture, 128, 256, 127, 31, Margin(8, 8, 8, 8));

    Textures.Input.Button.Normal.Initialize(&_texture, 480, 0, 31, 31, Margin(8, 8, 8, 8));
    Textures.Input.Button.Hovered.Initialize(&_texture, 480, 32, 31, 31, Margin(8, 8, 8, 8));
    Textures.Input.Button.Disabled.Initialize(&_texture, 480, 64, 31, 31, Margin(8, 8, 8, 8));
    Textures.Input.Button.Pressed.Initialize(&_texture, 480, 96, 31, 31, Margin(8, 8, 8, 8));

    Textures.Input.ListBox.Background.Initialize(&_texture, 256, 256, 63, 127, Margin(8, 8, 8, 8));
    Textures.Input.ListBox.Hovered.Initialize(&_texture, 320, 320, 31, 31, Margin(8, 8, 8, 8));
    Textures.Input.ListBox.EvenLine.Initialize(&_texture, 352, 256, 31, 31, Margin(8, 8, 8, 8));
    Textures.Input.ListBox.OddLine.Initialize(&_texture, 352, 256, 31, 31, Margin(8, 8, 8, 8));
    Textures.Input.ListBox.EvenLineSelected.Initialize(&_texture, 320, 256, 31, 31, Margin(8, 8, 8, 8));
    Textures.Input.ListBox.OddLineSelected.Initialize(&_texture, 320, 256, 31, 31, Margin(8, 8, 8, 8));

    Textures.Input.ComboBox.Normal.Initialize(&_texture, 384, 336, 127, 31, Margin(8, 8, 32, 8));
    Textures.Input.ComboBox.Hover.Initialize(&_texture, 384, 336 + 32, 127, 31, Margin(8, 8, 32, 8));
    Textures.Input.ComboBox.Down.Initialize(&_texture, 384, 336 + 64, 127, 31, Margin(8, 8, 32, 8));
    Textures.Input.ComboBox.Disabled.Initialize(&_texture, 384, 336 + 96, 127, 31, Margin(8, 8, 32, 8));
    Textures.Input.ComboBox.Button.Normal.Initialize(&_texture, 496, 272, 15, 15);
    Textures.Input.ComboBox.Button.Hover.Initialize(&_texture, 496, 272 + 16, 15, 15);
    Textures.Input.ComboBox.Button.Down.Initialize(&_texture, 496, 272 + 32, 15, 15);
    Textures.Input.ComboBox.Button.Disabled.Initialize(&_texture, 496, 272 + 48, 15, 15);

    Textures.Input.Slider.Horizontal.Normal.Initialize(&_texture, 416, 32, 15, 15);
    Textures.Input.Slider.Horizontal.Hover.Initialize(&_texture, 416, 32 + 16, 15, 15);
    Textures.Input.Slider.Horizontal.Down.Initialize(&_texture, 416, 32 + 32, 15, 15);
    Textures.Input.Slider.Horizontal.Disabled.Initialize(&_texture, 416, 32 + 48, 15, 15);
    Textures.Input.Slider.Vertical.Normal.Initialize(&_texture, 416 + 16, 32, 15, 15);
    Textures.Input.Slider.Vertical.Hover.Initialize(&_texture, 416 + 16, 32 + 16, 15, 15);
    Textures.Input.Slider.Vertical.Down.Initialize(&_texture, 416 + 16, 32 + 32, 15, 15);
    Textures.Input.Slider.Vertical.Disabled.Initialize(&_texture, 416 + 16, 32 + 48, 15, 15);

    Textures.Tab.Bottom.Active.Initialize(&_texture, 0, 416, 63, 31, Margin(8, 8, 8, 8));
    Textures.Tab.Bottom.Inactive.Initialize(&_texture, 128, 416, 63, 31, Margin(8, 8, 8, 8));
    Textures.Tab.Top.Active.Initialize(&_texture, 0, 384, 63, 31, Margin(8, 8, 8, 8));
    Textures.Tab.Top.Inactive.Initialize(&_texture, 128, 384, 63, 31, Margin(8, 8, 8, 8));
    Textures.Tab.Left.Active.Initialize(&_texture, 64, 384, 31, 63, Margin(8, 8, 8, 8));
    Textures.Tab.Left.Inactive.Initialize(&_texture, 64 + 128,  384, 31, 63, Margin(8, 8, 8, 8));
    Textures.Tab.Right.Active.Initialize(&_texture, 96, 384, 31, 63, Margin(8, 8, 8, 8));
    Textures.Tab.Right.Inactive.Initialize(&_texture, 96 + 128, 384, 31, 63, Margin(8, 8, 8, 8));
    Textures.Tab.Control.Initialize(&_texture, 0, 256, 127, 127, Margin(8, 8, 8, 8));
    Textures.Tab.HeaderBar.Initialize(&_texture, 128, 352, 127, 31, Margin(4, 4, 4, 4));
}

void TexturedBase::DrawButton(Controls::Base* control, bool is_depressed, bool is_hovered, bool is_disabled)
{
    if (is_disabled)
    {
        return Textures.Input.Button.Disabled.Draw(GetRender(), control->GetRenderBounds());
    }

    if (is_depressed)
    {
        return Textures.Input.Button.Pressed.Draw(GetRender(), control->GetRenderBounds());
    }

    if (is_hovered)
    {
        return Textures.Input.Button.Hovered.Draw(GetRender(), control->GetRenderBounds());
    }

    Textures.Input.Button.Normal.Draw(GetRender(), control->GetRenderBounds());
}

void TexturedBase::DrawTabButton(Controls::Base* control, bool is_active, int alignment)
{
    if (is_active)
    {
        return DrawTabButtonActive(control, alignment);
    }

    if (alignment == Position::BOTTOM)
    {
        return Textures.Tab.Bottom.Inactive.Draw(GetRender(), control->GetRenderBounds());
    }

    if (alignment == Position::TOP)
    {
        return Textures.Tab.Top.Inactive.Draw(GetRender(), control->GetRenderBounds());
    }

    if (alignment == Position::LEFT)
    {
        return Textures.Tab.Left.Inactive.Draw(GetRender(), control->GetRenderBounds());
    }

    if (alignment == Position::RIGHT)
    {
        return Textures.Tab.Right.Inactive.Draw(GetRender(), control->GetRenderBounds());
    }
}

void TexturedBase::DrawTabButtonActive(Controls::Base* control, int alignment)
{
    if (alignment == Position::BOTTOM)
    {
        return Textures.Tab.Bottom.Active.Draw(GetRender(), control->GetRenderBounds() + Rectangle(0, -8, 0, 8));
    }

    if (alignment == Position::TOP)
    {
        return Textures.Tab.Top.Active.Draw(GetRender(), control->GetRenderBounds() + Rectangle(0, 0, 0, 8));
    }

    if (alignment == Position::LEFT)
    {
        return Textures.Tab.Left.Active.Draw(GetRender(), control->GetRenderBounds() + Rectangle(0, 0, 8, 0));
    }

    if (alignment == Position::RIGHT)
    {
        return Textures.Tab.Right.Active.Draw(GetRender(), control->GetRenderBounds() + Rectangle(-8, 0, 8, 0));
    }
}

void TexturedBase::DrawTabControl(Controls::Base* control)
{
    Textures.Tab.Control.Draw(GetRender(), control->GetRenderBounds());
}

void TexturedBase::DrawTabTitleBar(Controls::Base* control)
{
    Textures.Tab.HeaderBar.Draw(GetRender(), control->GetRenderBounds());
}

void TexturedBase::DrawMenu(Controls::Base* control, bool is_padding_disabled)
{
    if (!is_padding_disabled)
    {
        return Textures.Menu.BackgroundWithMargin.Draw(GetRender(), control->GetRenderBounds());
    }

    Textures.Menu.Background.Draw(GetRender(), control->GetRenderBounds());
}

void TexturedBase::DrawMenuItem(Controls::Base* control, bool is_submenu_open, bool is_checked)
{
    const Gwen::Rectangle& bounds = control->GetRenderBounds();
    if (is_submenu_open || control->IsHovered())
    {
        Textures.Menu.Hover.Draw(GetRender(), bounds);
    }

    if (is_checked)
    {
        Textures.Menu.Check.Draw(GetRender(), Gwen::Rectangle(bounds._x + 4, bounds._y + 3, 15, 15));
    }
}

void TexturedBase::DrawMenuStrip(Gwen::Controls::Base* control)
{
    Textures.Menu.Strip.Draw(GetRender(), control->GetRenderBounds());
}

void TexturedBase::DrawMenuDivider(Controls::Base* control)
{
    Gwen::Rectangle bounds = control->GetRenderBounds();
    GetRender()->SetDrawColor(Gwen::Color(128, 128, 128, 128));
    GetRender()->FillRectangle(bounds);
}

void TexturedBase::DrawMenuRightArrow(Controls::Base* control)
{
    Textures.Menu.RightArrow.Draw(GetRender(), control->GetRenderBounds());
}

void TexturedBase::DrawShadow(Gwen::Controls::Base* control)
{
    Gwen::Rectangle bounds = control->GetRenderBounds();
    bounds._x -= 4;
    bounds._y -= 4;
    bounds._width += 10;
    bounds._height += 10;

    Textures.Shadow.Draw(GetRender(), bounds);
}

void TexturedBase::DrawStatusBar(Controls::Base* control)
{
    Textures.StatusBar.Draw(GetRender(), control->GetRenderBounds());
}

void TexturedBase::DrawCheckBox(Gwen::Controls::Base* control, bool is_selected)
{
    if (is_selected)
    {
        if (control->IsDisabled())
        {
            Textures.CheckBox.Disabled.Checked.Draw(GetRender(), control->GetRenderBounds());
        }
        else
        {
            Textures.CheckBox.Active.Checked.Draw(GetRender(), control->GetRenderBounds());
        }
    }
    else
    {
        if (control->IsDisabled())
        {
            Textures.CheckBox.Disabled.Normal.Draw(GetRender(), control->GetRenderBounds());
        }
        else
        {
            Textures.CheckBox.Active.Normal.Draw(GetRender(), control->GetRenderBounds());
        }
    }
}

void TexturedBase::DrawRadioButton(Gwen::Controls::Base* control, bool is_selected)
{
    if (is_selected)
    {
        if (control->IsDisabled())
        {
            Textures.RadioButton.Disabled.Checked.Draw(GetRender(), control->GetRenderBounds());
        }
        else
        {
            Textures.RadioButton.Active.Checked.Draw(GetRender(), control->GetRenderBounds());
        }
    }
    else
    {
        if (control->IsDisabled())
        {
            Textures.RadioButton.Disabled.Normal.Draw(GetRender(), control->GetRenderBounds());
        }
        else
        {
            Textures.RadioButton.Active.Normal.Draw(GetRender(), control->GetRenderBounds());
        }
    }
}

void TexturedBase::DrawKeyboardHighlight(Gwen::Controls::Base*, const Gwen::Rectangle& rectangle, int offset)
{
    Gwen::Rectangle inner_rectangle = rectangle;
    inner_rectangle._x += offset;
    inner_rectangle._y += offset;
    inner_rectangle._width -= offset * 2;
    inner_rectangle._height -= offset * 2;

    // Draw the top and the bottom.
    bool skip = true;
    for (int i = 0; i < inner_rectangle._width / 2; ++i)
    {
        _render->SetDrawColor(Gwen::Color(0, 0, 0, 255));

        if (!skip)
        {
            GetRender()->DrawPixel(inner_rectangle._x + (i * 2), inner_rectangle._y);
            GetRender()->DrawPixel(inner_rectangle._x + (i * 2), inner_rectangle._y + inner_rectangle._height - 1);
        }
        else
        {
            skip = !skip;
        }
    }

    skip = false;
    for (int i = 0; i < inner_rectangle._height / 2; ++i)
    {
        GetRender()->SetDrawColor(Gwen::Color(0, 0, 0, 255));

        if (!skip)
        {
            GetRender()->DrawPixel(inner_rectangle._x , inner_rectangle._y + i * 2);
            GetRender()->DrawPixel(inner_rectangle._x + inner_rectangle._width - 1, inner_rectangle._y + i * 2);
        }
        else
        {
            skip = !skip;
        }
    }
}

void TexturedBase::DrawTextBox(Gwen::Controls::Base* control)
{
    if (control->IsDisabled())
    {
        return Textures.TextBox.Disabled.Draw(GetRender(), control->GetRenderBounds());
    }

    if (control->HasFocus())
    {
        Textures.TextBox.Focus.Draw(GetRender(), control->GetRenderBounds());
    }
    else
    {
        Textures.TextBox.Normal.Draw(GetRender(), control->GetRenderBounds());
    }
}



void TexturedBase::DrawHighlight(Gwen::Controls::Base* control)
{
    Gwen::Rectangle bounds = control->GetRenderBounds();
    GetRender()->SetDrawColor(Gwen::Color(255, 100, 255, 255));
    GetRender()->FillRectangle(bounds);
}

void TexturedBase::DrawScrollBar(Gwen::Controls::Base* control, bool is_horizontal)
{
    if (is_horizontal)
    {
        Textures.ScrollBar.TrackH.Draw(GetRender(), control->GetRenderBounds());
    }
    else
    {
        Textures.ScrollBar.TrackV.Draw(GetRender(), control->GetRenderBounds());
    }
}

void TexturedBase::DrawScrollBarBar(Controls::Base* control, bool is_depressed, bool is_hovered, bool is_horizontal)
{
    if (!is_horizontal)
    {
        if (control->IsDisabled())
        {
            return Textures.ScrollBar.ButtonV_Disabled.Draw(GetRender(), control->GetRenderBounds());
        }

        if (is_depressed)
        {
            return Textures.ScrollBar.ButtonV_Down.Draw(GetRender(), control->GetRenderBounds());
        }

        if (is_hovered)
        {
            return Textures.ScrollBar.ButtonV_Hover.Draw(GetRender(), control->GetRenderBounds());
        }

        return Textures.ScrollBar.ButtonV_Normal.Draw(GetRender(), control->GetRenderBounds());
    }

    if (control->IsDisabled())
    {
        return Textures.ScrollBar.ButtonH_Disabled.Draw(GetRender(), control->GetRenderBounds());
    }

    if (is_depressed)
    {
        return Textures.ScrollBar.ButtonH_Down.Draw(GetRender(), control->GetRenderBounds());
    }

    if (is_hovered)
    {
        return Textures.ScrollBar.ButtonH_Hover.Draw(GetRender(), control->GetRenderBounds());
    }

    return Textures.ScrollBar.ButtonH_Normal.Draw(GetRender(), control->GetRenderBounds());
}

void TexturedBase::DrawScrollBarButton(Controls::Base* control, int alignment, bool is_depressed, bool is_hovered, bool is_disabled)
{
    int i = 0;
    if (alignment == Position::TOP)
    {
        i = 1;
    }

    if (alignment == Position::RIGHT)
    {
        i = 2;
    }

    if (alignment == Position::BOTTOM)
    {
        i = 3;
    }

    if (is_disabled)
    {
        return Textures.ScrollBar.Button.Disabled[i].Draw(GetRender(), control->GetRenderBounds());
    }

    if (is_depressed)
    {
        return Textures.ScrollBar.Button.Down[i].Draw(GetRender(), control->GetRenderBounds());
    }

    if (is_hovered)
    {
        return Textures.ScrollBar.Button.Hover[i].Draw(GetRender(), control->GetRenderBounds());
    }

    return Textures.ScrollBar.Button.Normal[i].Draw(GetRender(), control->GetRenderBounds());
}

void TexturedBase::DrawProgressBar(Controls::Base* control, bool is_horizontal, float progress, const Gwen::Padding& bar_padding, const Gwen::Color& color)
{
    Gwen::Rectangle bounds = control->GetRenderBounds();

    if (is_horizontal)
    {
        Textures.ProgressBar.Back.Draw(GetRender(), bounds);

        bounds._x = bounds._x + bar_padding._left;
        bounds._y = bounds._y + bar_padding._top;
        bounds._width = bounds._width - bar_padding._left - bar_padding._right;
        bounds._height = bounds._height - bar_padding._top - bar_padding._bottom;

        bounds._width = static_cast<int>(bounds._width * progress);
        if (bounds._width > 0)
        {
            GetRender()->SetDrawColor(color);
            GetRender()->FillRectangle(bounds);
        }
    }
    else
    {
        Textures.ProgressBar.Back.Draw(GetRender(), bounds);

        bounds._x = bounds._x + bar_padding._left;
        bounds._y = bounds._y + bar_padding._top;
        bounds._width = bounds._width - bar_padding._left - bar_padding._right;
        bounds._height = bounds._height - bar_padding._top - bar_padding._bottom;

        int inverse_progress = static_cast<int>(bounds._height * (1.0f - progress));
        bounds._y += inverse_progress;
        bounds._height -= inverse_progress;
        if (bounds._height > 0)
        {
            GetRender()->SetDrawColor(color);
            GetRender()->FillRectangle(bounds);
        }
    }
}

void TexturedBase::DrawListBox(Controls::Base* control)
{
    return Textures.Input.ListBox.Background.Draw(GetRender(), control->GetRenderBounds());
}

void TexturedBase::DrawListBoxLine(Controls::Base* control, bool is_selected, bool is_even)
{
    if (is_selected)
    {
        if (is_even)
        {
            return Textures.Input.ListBox.EvenLineSelected.Draw(GetRender(), control->GetRenderBounds());
        }
        else
        {
            return Textures.Input.ListBox.OddLineSelected.Draw(GetRender(), control->GetRenderBounds());
        }
    }

    if (control->IsHovered())
    {
        return Textures.Input.ListBox.Hovered.Draw(GetRender(), control->GetRenderBounds());
    }

    if (is_even)
    {
        return Textures.Input.ListBox.EvenLine.Draw(GetRender(), control->GetRenderBounds());
    }

    return Textures.Input.ListBox.OddLine.Draw(GetRender(), control->GetRenderBounds());
}

void TexturedBase::DrawSlider(Controls::Base* control, unsigned number_of_notches, unsigned size)
{
    Gwen::Rectangle bounds = control->GetRenderBounds();
    bounds._x += size / 2;
    bounds._width -= size;
    bounds._y += bounds._height / 2 - 1;
    bounds._height = 1;

    DrawSliderNotches(bounds, number_of_notches, size / 2);

    GetRender()->SetDrawColor(Colors.Slider.Bar);
    GetRender()->FillRectangle(bounds);
}

void TexturedBase::DrawSliderButton(Controls::Base* control, bool is_depressed)
{
    if (control->IsDisabled())
    {
        return Textures.Input.Slider.Horizontal.Disabled.DrawCenter(GetRender(), control->GetRenderBounds());
    }

    if (is_depressed)
    {
        return Textures.Input.Slider.Horizontal.Down.DrawCenter(GetRender(), control->GetRenderBounds());
    }

    if (control->IsHovered())
    {
        return Textures.Input.Slider.Horizontal.Hover.DrawCenter(GetRender(), control->GetRenderBounds());
    }

    Textures.Input.Slider.Horizontal.Normal.DrawCenter(GetRender(), control->GetRenderBounds());
}

void TexturedBase::DrawSliderNotches(const Gwen::Rectangle& rectangle, unsigned number_of_notches, unsigned length)
{
    if (number_of_notches > 0 && length > 0)
    {
        GetRender()->SetDrawColor(Colors.Slider.Bar);

        float spacing = static_cast<float>(rectangle._width) / static_cast<float>(number_of_notches);
        for (unsigned i = 0; i < number_of_notches + 1; ++i)
        {
            GetRender()->FillRectangle(Gwen::Rectangle(static_cast<int>(rectangle._x + spacing * i), rectangle._y + length - 2, 1, 5));
        }
    }
}

void TexturedBase::DrawComboBox(Controls::Base* control, bool is_down, bool is_open)
{
    if (control->IsDisabled())
    {
        return Textures.Input.ComboBox.Disabled.Draw(GetRender(), control->GetRenderBounds());
    }

    if (is_down || is_open)
    {
        return Textures.Input.ComboBox.Down.Draw(GetRender(), control->GetRenderBounds());
    }

    if (control->IsHovered())
    {
        return Textures.Input.ComboBox.Hover.Draw(GetRender(), control->GetRenderBounds());
    }

    Textures.Input.ComboBox.Normal.Draw(GetRender(), control->GetRenderBounds());
}

void TexturedBase::DrawComboDownArrow(Gwen::Controls::Base* control, bool is_hovered, bool is_down, bool is_open, bool is_disabled)
{
    if (is_disabled)
    {
        return Textures.Input.ComboBox.Button.Disabled.Draw(GetRender(), control->GetRenderBounds());
    }

    if (is_down || is_open)
    {
        return Textures.Input.ComboBox.Button.Down.Draw(GetRender(), control->GetRenderBounds());
    }

    if (is_hovered)
    {
        return Textures.Input.ComboBox.Button.Hover.Draw(GetRender(), control->GetRenderBounds());
    }

    Textures.Input.ComboBox.Button.Normal.Draw(GetRender(), control->GetRenderBounds());
}

void TexturedBase::DrawTooltip(Controls::Base* control)
{
    return Textures.Tooltip.Draw(GetRender(), control->GetRenderBounds());
}

}; // namespace Skin

}; // namespace Gwen
