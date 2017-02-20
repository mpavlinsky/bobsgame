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
#include "Gwen/Controls/Base.h"

#include "Gwen/Animation.h"
#include "Gwen/renderer/gwen_renderer_base.h"

#include "Gwen/Controls/Canvas.h"
#include "Gwen/Controls/gwen_controls_tooltip.h"
#include "Gwen/Controls/Label.h"

#include "Gwen/platform/gwen_platform_base.h"
#include "Gwen/skin/gwen_skin_base.h"

#include "Gwen/Utility.h"

namespace Gwen
{
namespace Controls
{

/// \brief A global pointer to the hovered control.
Base* _hovered_control = nullptr;

/// \brief A global pointer to the control with keyboard focus.
Base* _keyboard_focus = nullptr;

/// \brief A global pointer to the control with mouse focus.
Base* _mouse_focus = nullptr;

Base::Base(Base* parent, const std::string& name) :
    _parent(nullptr),
    _actual_parent(nullptr),
    _inner_panel(nullptr),
    _tooltip(nullptr),
    _skin(nullptr),
    _bounds(0, 0, 10, 10),
    _render_bounds(0, 0, 10, 10),
    _inner_bounds(0, 0, 10, 10),
    _padding(0, 0, 0, 0),
    _margin(0, 0, 0, 0),
    _dock(0),
    _restrict_to_parent(false),
    _disabled(false),
    _hidden(false),
    _mouse_input_enabled(false),
    _keyboard_input_enabled(false),
    _draw_background(false),
    _tabable(false),
    _needs_layout(true)
{
    SetKeyboardInputEnabled(false);
    SetHidden(false);
    SetMouseInputEnabled(true);
    SetName(name);
    SetParent(parent);
    SetRestrictToParent(false);
    SetShouldDrawBackground(true);
    SetTabable(false);
    SetTooltip(nullptr);

    Invalidate();
}

Base::~Base()
{
    Canvas* canvas = GetCanvas();
    if (canvas)
    {
        canvas->_PreDeleteCanvas(this);
    }

    auto i = _children.begin();
    while (i != _children.end())
    {
        Base* child = *i;
        i = _children.erase(i);
        delete child;
    }
    _children.clear();

    for (auto i = _accelerators.begin(); i != _accelerators.end(); ++i)
    {
        delete i->second;
    }
    _accelerators.clear();

    SetParent(nullptr);

    if (Gwen::Controls::_hovered_control == this)
    {
        Gwen::Controls::_hovered_control = nullptr;
    }

    if (Gwen::Controls::_keyboard_focus == this)
    {
        Gwen::Controls::_keyboard_focus = nullptr;
    }

    if (Gwen::Controls::_mouse_focus == this)
    {
        Gwen::Controls::_mouse_focus = nullptr;
    }

    Tooltip::Disable(this);
    Animation::Cancel(this);
}

void Base::PreDelete(Gwen::Skin::Base*)
{
}

void Base::DelayedDelete()
{
    Canvas* canvas = GetCanvas();
    canvas->AddDelayedDelete(this);
}

void Base::SetParent(Controls::Base* parent, bool to_back)
{
    if (_parent == parent)
    {
        return;
    }

    if (_parent)
    {
        _parent->RemoveChild(this);
    }

    _parent = parent;
    _actual_parent = nullptr;

    if (_parent)
    {
        _parent->AddChild(this, to_back);
    }
}

Base* Base::GetParent() const
{
    return _parent;
}

Canvas* Base::GetCanvas()
{
    Base* canvas = _parent;
    if (!canvas)
    {
        return nullptr;
    }
    return canvas->GetCanvas();
}

void Base::AddChild(Controls::Base* child, bool to_back)
{
    // If there's an inner panel, add the child to the inner panel.
    if (_inner_panel)
    {
        _inner_panel->AddChild(child, to_back);
        return;
    }

    // Determine which side of the list to add the child.
    if (to_back)
    {
        _children.push_back(child);
    }
    else
    {
        _children.push_front(child);
    }

    _OnChildAdded(child);
    child->_actual_parent = this;
}

void Base::RemoveChild(Base* child)
{
    // If we removed our innerpanel, remove our pointer to it.
    if (_inner_panel == child)
    {
        _inner_panel = nullptr;
    }

    if (_inner_panel)
    {
        _inner_panel->RemoveChild(child);
    }

    _children.remove(child);
    _OnChildRemoved(child);
}

void Base::RemoveChildren()
{
    while (_children.size() > 0)
    {
        RemoveChild(*_children.begin());
    }
}

bool Base::IsChild(Controls::Base* child) const
{
    for (auto i = _children.begin(); i != _children.end(); ++i)
    {
        if (child == (*i))
        {
            return true;
        }
    }

    return false;
}

std::list<Base*>& Base::GetChildren()
{
    if (_inner_panel)
    {
        return _inner_panel->GetChildren();
    }
    return _children;
}

unsigned Base::GetChildrenCount() const
{
    return static_cast<unsigned>(_children.size());
}

Controls::Base* Base::GetChild(unsigned int index)
{
    if (index >= GetChildrenCount())
    {
        return nullptr;
    }

    for (auto i = _children.begin(); i != _children.end(); ++i)
    {
        if (index == 0)
        {
            return *i;
        }

        --index;
    }

    // Should never happen.
    return nullptr;
}

const Base* Base::GetChild(unsigned index) const
{
    if (index >= GetChildrenCount())
    {
        return nullptr;
    }

    for (auto i = _children.begin(); i != _children.end(); ++i)
    {
        if (index == 0)
        {
            return *i;
        }

        --index;
    }

    // Should never happen.
    return nullptr;
}

Gwen::Point Base::ChildrenSize() const
{
    Gwen::Point size;

    for (auto i = _children.begin(); i != _children.end(); ++i)
    {
        Base* child = *i;
        if (child->Hidden())
        {
            continue;
        }

        size._x = std::max(size._x, child->Right());
        size._y = std::max(size._y, child->Bottom());
    }

    return size;
}

bool Base::SizeToChildren(bool size_width, bool size_height)
{
    Gwen::Point size = ChildrenSize();
    size._y += GetPadding()._bottom;
    size._x += GetPadding()._right;
    return SetSize(size_width ? size._x : Width(), size_height ? size._y : Height());
}

Base* Base::FindChildByName(const std::string& name, bool recursive)
{
    for (auto i = _children.begin(); i != _children.end(); ++i)
    {
        Base* child = *i;
        if (!child->GetName().empty() && child->GetName() == name)
        {
            return child;
        }

        if (recursive)
        {
            Controls::Base* sub_child = child->FindChildByName(name, true);
            if (sub_child)
            {
                return sub_child;
            }
        }
    }

    return nullptr;
}

void Base::SetName(const std::string& name)
{
    _name = name;
}

std::string Base::GetName() const
{
    return _name;
}

void Base::Think()
{
}

void Base::SendToBack()
{
    if (!_actual_parent)
    {
        return;
    }

    if (_actual_parent->_children.front() == this)
    {
        return;
    }

    _actual_parent->_children.remove(this);
    _actual_parent->_children.push_front(this);

    Invalidate();

    Redraw();
}

void Base::BringToFront()
{
    if (!_actual_parent)
    {
        return;
    }

    if (_actual_parent->_children.back() == this)
    {
        return;
    }

    _actual_parent->_children.remove(this);
    _actual_parent->_children.push_back(this);

    Invalidate();

    Redraw();
}

Gwen::Point Base::LocalPositionToCanvas(const Gwen::Point& position)
{
    if (_parent)
    {
        int x = position._x + X();
        int y = position._y + Y();

        // If our parent has an innerpanel and we're a child of it,
        // add its offset onto us.
        if (_parent->_inner_panel && _parent->_inner_panel->IsChild(this))
        {
            x += _parent->_inner_panel->X();
            y += _parent->_inner_panel->Y();
        }

        return _parent->LocalPositionToCanvas(Gwen::Point(x, y));
    }

    return position;
}

Gwen::Point Base::CanvasPositionToLocal(const Gwen::Point& position)
{
    if (_parent)
    {
        int x = position._x - X();
        int y = position._y - Y();

        // If our parent has an innerpanel and we're a child of it,
        // add its offset onto us.
        if (_parent->_inner_panel && _parent->_inner_panel->IsChild(this))
        {
            x -= _parent->_inner_panel->X();
            y -= _parent->_inner_panel->Y();
        }

        return _parent->CanvasPositionToLocal(Gwen::Point(x, y));
    }

    return position;
}

void Base::SetDock(int dock)
{
    if (_dock == dock)
    {
        return;
    }

    _dock = dock;

    Invalidate();
}

int Base::GetDock() const
{
    return _dock;
}

void Base::SetRestrictToParent(bool restrict_to_parent)
{
    _restrict_to_parent = restrict_to_parent;
}

bool Base::GetRestrictToParent() const
{
    return _restrict_to_parent;
}

int Base::X() const
{
    return _bounds._x;
}

int Base::Y() const
{
    return _bounds._y;
}

int Base::Width() const
{
    return _bounds._width;
}

int Base::Height() const
{
    return _bounds._height;
}

int Base::Bottom() const
{
    return _bounds._y + _bounds._height + _margin._bottom;
}

int Base::Right() const
{
    return _bounds._x + _bounds._width + _margin._right;
}

Margin Base::GetMargin() const
{
    return _margin;
}

Padding Base::GetPadding() const
{
    return _padding;
}

void Base::SetPosition(int x, int y)
{
    SetBounds(x, y, Width(), Height());
}

void Base::SetPosition(const Point& point)
{
    return SetPosition(point._x, point._y);
}

void Base::SetPosition(const Gwen::Position::Position& alignment, int x_padding, int y_padding)
{
    const Rectangle& bounds = GetParent()->GetInnerBounds();
    const Margin& margin = GetMargin();
    int x = X();
    int y = Y();

    if (alignment & Position::LEFT)
    {
        x = bounds._x + x_padding + margin._left;
    }

    if (alignment & Position::RIGHT)
    {
        x = bounds._x + (bounds._width - Width() - x_padding - margin._right);
    }

    if (alignment & Position::CENTER_H)
    {
        x = bounds._x + (bounds._width - Width()) / 2;
    }

    if (alignment & Position::TOP)
    {
        y = bounds._y + y_padding;
    }

    if (alignment & Position::BOTTOM)
    {
        y = bounds._y + (bounds._height - Height() - y_padding);
    }

    if (alignment & Position::CENTER_V)
    {
        y = bounds._y + (bounds._height - Height()) / 2 + y_padding;
    }

    SetPosition(x, y);
}

Point Base::GetPosition() const
{
    return Point(X(), Y());
}

void Base::SetWidth(int width)
{
    SetSize(width, Height());
}

void Base::SetHeight(int height)
{
    SetSize(Width(), height);
}

bool Base::SetSize(int width, int height)
{
    return SetBounds(X(), Y(), width, height);
}

bool Base::SetSize(const Point& point)
{
    return SetSize(point._x, point._y);
}

Point Base::GetSize() const
{
    return Point(Width(), Height());
}

bool Base::SetBounds(const Gwen::Rectangle& bounds)
{
    bool result = false;

    if (_bounds != bounds)
    {
        const Gwen::Rectangle oldBounds = GetBounds();
        _bounds = bounds;
        _OnBoundsChanged(oldBounds);

        result = true;
    }

    return result;
}

bool Base::SetBounds(int x, int y, int width, int height)
{
    return SetBounds(Rectangle(x, y, width, height));
}

bool Base::SetPadding(const Padding& padding)
{
    if (_padding == padding)
    {
        return false;
    }

    _padding = padding;

    Invalidate();

    return true;
}

bool Base::SetMargin(const Margin& margin)
{
    if (_margin == margin)
    {
        return false;
    }

    _margin = margin;

    Invalidate();

    return true;
}

void Base::MoveBy(int x, int y)
{
    MoveTo(X() + x, Y() + y);
}

void Base::MoveTo(int x, int y)
{
    if (_restrict_to_parent && GetParent())
    {
        Base* parent = GetParent();
        if (x - GetPadding()._left < parent->GetMargin()._left)
        {
            x = parent->GetMargin()._left + GetPadding()._left;
        }

        if (y - GetPadding()._top < parent->GetMargin()._top)
        {
            y = parent->GetMargin()._top + GetPadding()._top;
        }

        if (x + Width() + GetPadding()._right > parent->Width() - parent->GetMargin()._right)
        {
            x = parent->Width() - parent->GetMargin()._right - Width() - GetPadding()._right;
        }

        if (y + Height() + GetPadding()._bottom > parent->Height() - parent->GetMargin()._bottom)
        {
            y = parent->Height() - parent->GetMargin()._bottom - Height() - GetPadding()._bottom;
        }
    }

    SetBounds(x, y, Width(), Height());
}

Gwen::Rectangle Base::GetBounds() const
{
    return _bounds;
}

std::vector<Base*> Base::GetControlsAt(int x, int y)
{
    std::vector<Base*> result;

    //
    // Recursively add any child controls.
    //

    // For each child...
    for (auto i = _children.rbegin(); i != _children.rend(); ++i)
    {
        // Get the child.
        Base* child = *i;

        // Get the child's children.
        std::vector<Base*> children = child->GetControlsAt(x - child->X(), y - child->Y());
        if (!children.empty())
        {
            // Store the result.
            result.insert(result.end(), children.begin(), children.end());
        }
    }

    // If the mouse is over this control...
    if (x >= 0 && y >= 0 && x < Width() && y < Height())
    {
        // Add this control.
        result.push_back(this);
    }

    return result;
}

Gwen::Rectangle Base::GetInnerBounds() const
{
    return _inner_bounds;
}

Gwen::Rectangle Base::GetRenderBounds() const
{
    return _render_bounds;
}

void Base::DoRender(Gwen::Skin::Base* skin)
{
    assert(skin != nullptr);
    if (skin != nullptr)
    {
        RenderRecursive(skin, GetBounds());
    }
}

void Base::RenderRecursive(Gwen::Skin::Base* skin, const Gwen::Rectangle& clipping_rectangle)
{
    Gwen::Renderer::Base* render = skin->GetRender();
    Gwen::Point old_offset = render->GetRenderOffset();
    render->AddRenderOffset(Point(clipping_rectangle._x, clipping_rectangle._y));

    RenderUnder(skin);

    Gwen::Rectangle old_region = render->GetClippingRegion();
    if (GetShouldClip())
    {
        render->AddClippingRegion(clipping_rectangle);

        if (!render->GetClippingRegionVisible())
        {
            render->SetRenderOffset(old_offset);
            render->SetClippingRegion(old_region);
            return;
        }
    }

    // Render this control and its children controls.
    render->StartClipping();

    Render(skin);
    if (!_children.empty())
    {
        for (auto i = _children.begin(); i != _children.end(); ++i)
        {
            Base* child = *i;
            if (child->Hidden())
            {
                continue;
            }
            child->DoRender(skin);
        }
    }

    render->EndClipping();

    // Render overlay/focus.
    render->SetClippingRegion(old_region);
    render->StartClipping();
    {
        RenderOver(skin);
        RenderFocus(skin);
    }
    render->EndClipping();
    render->SetRenderOffset(old_offset);

}

bool Base::GetShouldClip() const
{
    return true;
}

void Base::SetHidden(bool is_hidden)
{
    if (_hidden == is_hidden)
    {
        return;
    }

    _hidden = is_hidden;

    // If this control is hidden...
    if (_hidden)
    {
        Tooltip::Disable(this);
        Tooltip::Disable(GetParent());
    }

    // Get the mouse position.
    Gwen::Point mouse_position = Gwen::Input::GetMousePosition();
    Gwen::Input::OnMouseMoved(GetCanvas(), mouse_position._x, mouse_position._y, 0, 0);

    // If this control is not hidden and is the hovered control...
    if (!_hidden && _hovered_control == this)
    {
        // Update the tooltip.
        if (GetTooltip() != nullptr)
        {
            Tooltip::Enable(this);
        }
        else if (GetParent() != nullptr && GetParent()->GetTooltip() != nullptr)
        {
            Tooltip::Enable(GetParent());
        }
    }

    Invalidate();
    Redraw();
}

bool Base::Hidden() const
{
    return _hidden;
}

bool Base::Visible() const
{
    if (Hidden())
    {
        return false;
    }

    if (GetParent())
    {
        return GetParent()->Visible();
    }

    return true;
}

void Base::Hide()
{
    SetHidden(true);
}

void Base::Show()
{
    SetHidden(false);
}

void Base::SetSkin(Skin::Base* skin, bool recursive)
{
    if (_skin == skin)
    {
        return;
    }
    _skin = skin;

    Invalidate();
    Redraw();
    _OnSkinChanged(skin);

    if (recursive)
    {
        for (auto i = _children.begin(); i != _children.end(); ++i)
        {
            (*i)->SetSkin(skin, true);
        }
    }
}

Skin::Base* Base::GetSkin(void)
{
    if (_skin)
    {
        return _skin;
    }

    if (_parent)
    {
        return _parent->GetSkin();
    }

    assert(false);
    return nullptr;
}

void Base::SetShouldDrawBackground(bool should_draw_background)
{
    _draw_background = should_draw_background;
}

bool Base::GetShouldDrawBackground() const
{
    return _draw_background;
}

void Base::OnMouseEnter()
{
    _on_hover_enter.Call(this);

    if (Visible())
    {
        if (GetTooltip() != nullptr)
        {
            Tooltip::Enable(this);
        }
        else if (GetParent() != nullptr && GetParent()->GetTooltip() != nullptr)
        {
            Tooltip::Enable(GetParent());
        }
    }

    Redraw();
}

void Base::OnMouseLeave()
{
    _on_hover_leave.Call(this);

    Tooltip::Disable(this);
    Tooltip::Disable(GetParent());

    Redraw();
}

void Base::OnMouseMoved(int, int, int, int)
{
}

bool Base::OnMouseWheeled(int wheel)
{
    if (_actual_parent)
    {
        return _actual_parent->OnMouseWheeled(wheel);
    }

    return false;
}

void Base::OnMouseClickLeft(int, int, bool)
{
}

void Base::OnMouseClickRight(int, int, bool)
{
}

void Base::OnMouseDoubleClickLeft(int x, int y)
{
    OnMouseClickLeft(x, y, true);
}

void Base::OnMouseDoubleClickRight(int x, int y)
{
    OnMouseClickRight(x, y, true);
}

void Base::OnKeyboardFocus()
{
}

void Base::OnLostkeyboardFocus()
{
}

void Base::SetMouseInputEnabled(bool mouse_input_enabled)
{
    _mouse_input_enabled = mouse_input_enabled;
}

bool Base::GetMouseInputEnabled() const
{
    return _mouse_input_enabled;
}

void Base::SetKeyboardInputEnabled(bool keyboard_input_enabled)
{
    _keyboard_input_enabled = keyboard_input_enabled;
}

bool Base::GetKeyboardInputEnabled() const
{
    return _keyboard_input_enabled;
}

bool Base::OnCharacter(char)
{
    return false;
}

bool Base::OnKeyPress(int key, bool is_down)
{
    bool handled = false;

    switch (key)
    {
    case Key::TAB:
        handled = OnKeyTab(is_down);
        break;

    case Key::SPACE:
        handled = OnKeySpace(is_down);
        break;

    case Key::HOME:
        handled = OnKeyHome(is_down);
        break;

    case Key::END:
        handled = OnKeyEnd(is_down);
        break;

    case Key::RETURN:
        handled = OnKeyReturn(is_down);
        break;

    case Key::BACKSPACE:
        handled = OnKeyBackspace(is_down);
        break;

    case Key::DELETE:
        handled = OnKeyDelete(is_down);
        break;

    case Key::RIGHT:
        handled = OnKeyRight(is_down);
        break;

    case Key::LEFT:
        handled = OnKeyLeft(is_down);
        break;

    case Key::UP:
        handled = OnKeyUp(is_down);
        break;

    case Key::DOWN:
        handled = OnKeyDown(is_down);
        break;

    case Key::ESCAPE:
        handled = OnKeyEscape(is_down);
        break;

    default:
        break;
    };

    if (!handled && GetParent())
    {
        GetParent()->OnKeyPress(key, is_down);
    }

    return handled;
}

bool Base::OnKeyRelease(int key)
{
    return OnKeyPress(key, false);
}

void Base::OnCut(Base*)
{
}

void Base::OnCopy(Base*)
{
}

void Base::OnPaste(Base*)
{
}

void Base::OnSelectAll(Base*)
{
}

bool Base::OnKeyTab(bool bDown)
{
    if (!bDown)
        return true;

    if (GetCanvas()->_next_tab)
    {
        GetCanvas()->_next_tab->Focus();
        Redraw();
    }

    return true;
}

bool Base::OnKeySpace(bool)
{
    return false;
}

bool Base::OnKeyReturn(bool)
{
    return false;
}

bool Base::OnKeyBackspace(bool)
{
    return false;
}

bool Base::OnKeyDelete(bool)
{
    return false;
}

bool Base::OnKeyHome(bool)
{
    return false;
}

bool Base::OnKeyEnd(bool)
{
    return false;
}

bool Base::OnKeyLeft(bool)
{
    return false;
}

bool Base::OnKeyRight(bool)
{
    return false;
}

bool Base::OnKeyUp(bool)
{
    return false;
}

bool Base::OnKeyDown(bool)
{
    return false;
}

bool Base::OnKeyEscape(bool)
{
    return false;
}

bool Base::IsHovered()
{
    return Gwen::Controls::_hovered_control == this;
}

bool Base::HasFocus()
{
    return Gwen::Controls::_keyboard_focus == this;
}

void Base::Focus()
{
    if (Gwen::Controls::_keyboard_focus == this)
    {
        return;
    }

    if (Gwen::Controls::_keyboard_focus)
    {
        Gwen::Controls::_keyboard_focus->OnLostkeyboardFocus();
    }

    Gwen::Controls::_keyboard_focus = this;
    OnKeyboardFocus();
    Redraw();
}

void Base::Blur()
{
    if (Gwen::Controls::_keyboard_focus != this)
    {
        return;
    }

    Gwen::Controls::_keyboard_focus = nullptr;
    OnLostkeyboardFocus();
    Redraw();
}

void Base::SetDisabled(bool disabled)
{
    if (_disabled == disabled)
    {
        return;
    }

    _disabled = disabled;

    Redraw();
}

bool Base::IsDisabled() const
{
    return _disabled;
}

void Base::Redraw()
{
    UpdateColors();
    if (_parent)
    {
        _parent->Redraw();
    }
}

void Base::UpdateColors()
{
}

void Base::SetTooltip(const std::string& text)
{
    Label* tooltip = nullptr;

    // Only create a tooltip if there's text.
    if (!text.empty())
    {
        tooltip = new Label(this);
        tooltip->SetText(text);
        tooltip->SetTextColorOverride(GetSkin()->Colors.Tooltip.Normal);
        tooltip->SetPadding(Padding(6, 4, 6, 4));
        tooltip->SizeToContents();
    }

    SetTooltip(tooltip);
}

void Base::SetTooltip(Base* tooltip)
{
    // Clean up the old tooltip.
    if (_tooltip != nullptr)
    {
        // Handle the case where a tooltip was removed from the hovered control.
        if (Gwen::Controls::_hovered_control == this)
        {
            Tooltip::Disable(this);
            Tooltip::Disable(GetParent());
        }

        delete _tooltip;
        _tooltip = nullptr;
    }

    // Store the new tooltip.
    _tooltip = tooltip;

    // Configure the new tooltip.
    if (_tooltip)
    {
        _tooltip->SetParent(this);
        _tooltip->SetHidden(true);
    }

    // Handle the case where a tooltip was added from the hovered control.
    if (Gwen::Controls::_hovered_control == this)
    {
        if (Visible())
        {
            if (GetTooltip() != nullptr)
            {
                Tooltip::Enable(this);
            }
            else if (GetParent() != nullptr && GetParent()->GetTooltip() != nullptr)
            {
                Tooltip::Enable(GetParent());
            }
        }
    }
}

Base* Base::GetTooltip()
{
    return _tooltip;
}

bool Base::GetMenuComponent()
{
    if (!_parent)
    {
        return false;
    }

    return _parent->GetMenuComponent();
}

void Base::CloseMenus()
{
    for (auto i = _children.begin(); i != _children.end(); ++i)
    {
        (*i)->CloseMenus();
    }
}

void Base::SetTabable(bool isTabable)
{
    _tabable = isTabable;
}

bool Base::IsTabable() const
{
    return _tabable;
}

bool Base::GetAcceleratorOnlyOnFocus() const
{
    return false;
}

bool Base::HandleAccelerator(const std::string& accelerator)
{
    if (Gwen::Controls::_keyboard_focus == this || !GetAcceleratorOnlyOnFocus())
    {
        auto i = _accelerators.find(accelerator);
        if (i != _accelerators.end())
        {
            i->second->Call(this);
            return true;
        }
    }

    for (auto i = _children.begin(); i != _children.end(); ++i)
    {
        if ((*i)->HandleAccelerator(accelerator))
        {
            return true;
        }
    }

    return false;
}

void Base::Invalidate()
{
    _needs_layout = true;
    if (_inner_panel != nullptr)
    {
        _inner_panel->_needs_layout = true;
    }

    if (_parent)
    {
        _parent->Invalidate();
    }
}

void Base::InvalidateChildren()
{
    for (auto i = _children.begin(); i != _children.end(); ++i)
    {
        (*i)->_needs_layout = true;
        (*i)->InvalidateChildren();
    }

    if (_inner_panel)
    {
        _inner_panel->_needs_layout = true;
        for (auto i = _inner_panel->_children.begin(); i != _inner_panel->_children.end(); ++i)
        {
            (*i)->_needs_layout = true;
            (*i)->InvalidateChildren();
        }
    }
}

void Base::RecurseLayout(Gwen::Skin::Base* skin)
{
    assert(skin != nullptr);
    if (skin != nullptr &&
        _needs_layout)
    {
        _needs_layout = false;

        Layout(skin);

        bool bounds_changed = false;
        Gwen::Rectangle bounds = GetRenderBounds();

        // Adjust the bounds for padding.
        bounds._x += _padding._left;
        bounds._width -= _padding._left + _padding._right;
        bounds._y += _padding._top;
        bounds._height -= _padding._top + _padding._bottom;

        // For each child...
        std::vector<Base*> children_fill;
        for (auto i = _children.begin(); i != _children.end(); ++i)
        {
            Base* child = *i;
            assert(child != nullptr);
            if (child != nullptr)
            {
                int dock = child->GetDock();
                if (dock & Position::FILL)
                {
                    children_fill.push_back(child);
                }
                else
                {
                    if (dock & Position::LEFT)
                    {
                        const Margin& margin = child->GetMargin();
                        bounds_changed |= child->SetBounds(bounds._x + margin._left,
                                                           bounds._y + margin._top,
                                                           child->Width(),
                                                           bounds._height - margin._top - margin._bottom);
                        int width = margin._left + margin._right + child->Width();
                        bounds._x += width;
                        bounds._width -= width;
                    }
                    else if (dock & Position::RIGHT)
                    {
                        const Margin& margin = child->GetMargin();
                        bounds_changed |= child->SetBounds(bounds._x + bounds._width - child->Width() - margin._right,
                                                           bounds._y + margin._top,
                                                           child->Width(),
                                                           bounds._height - margin._top - margin._bottom);
                        int width = margin._left + margin._right + child->Width();
                        bounds._width -= width;
                    }

                    if (dock & Position::TOP)
                    {
                        const Margin& margin = child->GetMargin();
                        bounds_changed |= child->SetBounds(bounds._x + margin._left,
                                                           bounds._y + margin._top,
                                                           bounds._width - margin._left - margin._right,
                                                           child->Height());
                        int height = margin._top + margin._bottom + child->Height();
                        bounds._y += height;
                        bounds._height -= height;
                    }
                    else if (dock & Position::BOTTOM)
                    {
                        const Margin& margin = child->GetMargin();
                        bounds_changed |= child->SetBounds(bounds._x + margin._left,
                                                           bounds._y + bounds._height - child->Height() - margin._bottom,
                                                           bounds._width - margin._left - margin._right,
                                                           child->Height());
                        int height = child->Height() + margin._bottom + margin._top;
                        bounds._height -= height;
                    }

                    child->RecurseLayout(skin);
                }
            }
        }

        // Store the inner bounds.
        if (_inner_bounds != bounds)
        {
            _inner_bounds = bounds;
            bounds_changed = true;
        }

        // Fill uses the left over space.  So, do that now.
        for (auto i = children_fill.begin(); i != children_fill.end(); ++i)
        {
            Base* child = *i;
            assert(child != nullptr);
            if (child != nullptr)
            {
                int dock = child->GetDock();
                assert(dock & Position::FILL);
                if (dock & Position::FILL)
                {
                    const Margin& margin = child->GetMargin();
                    child->SetBounds(bounds._x + margin._left,
                                     bounds._y + margin._top,
                                     bounds._width - margin._left - margin._right,
                                     bounds._height - margin._top - margin._bottom);
                    child->RecurseLayout(skin);
                }
            }
        }

        if (_inner_panel != nullptr)
        {
            _inner_panel->RecurseLayout(skin);
        }

        PostLayout(skin);

        // Update the tabbing.
        if (IsTabable() && !IsDisabled())
        {
            if (!GetCanvas()->_first_tab)
            {
                GetCanvas()->_first_tab = this;
            }

            if (!GetCanvas()->_next_tab)
            {
                GetCanvas()->_next_tab = this;
            }
        }

        // Update the keyboard focus.
        if (Gwen::Controls::_keyboard_focus == this)
        {
            GetCanvas()->_next_tab = nullptr;
        }

        // If the bounds of the control changed...
        if (bounds_changed)
        {
            // Update the layout again.
            Invalidate();
            InvalidateChildren();
            RecurseLayout(skin);
        }
    }
}

void Base::Layout(Gwen::Skin::Base*)
{
}

void Base::PostLayout(Gwen::Skin::Base*)
{
}

void Base::Render(Gwen::Skin::Base*)
{
}

void Base::RenderUnder(Gwen::Skin::Base*)
{
}

void Base::RenderOver(Gwen::Skin::Base*)
{
}

void Base::RenderFocus(Gwen::Skin::Base* skin)
{
    if (Gwen::Controls::_keyboard_focus != this)
    {
        return;
    }

    if (!IsTabable())
    {
        return;
    }

    skin->DrawKeyboardHighlight(this, GetRenderBounds(), 3);
}

void Base::UpdateRenderBounds()
{
    _render_bounds._x = 0;
    _render_bounds._y = 0;
    _render_bounds._width = _bounds._width;
    _render_bounds._height = _bounds._height;
}

void Base::_OnChildAdded(Base*)
{
    Invalidate();
}

void Base::_OnChildRemoved(Base*)
{
    Invalidate();
}

void Base::_OnBoundsChanged(const Gwen::Rectangle& old_bounds)
{
    if (_bounds != old_bounds)
    {
        Base* parent = GetParent();
        if (parent != nullptr)
        {
            parent->_OnChildBoundsChanged(old_bounds, this);
        }

        UpdateRenderBounds();
        Redraw();
    }
}

void Base::_OnChildBoundsChanged(const Gwen::Rectangle&, Base*)
{
}

void Base::_OnScaleChanged()
{
    for (auto i = _children.begin(); i != _children.end(); ++i)
    {
        (*i)->_OnScaleChanged();
    }
}

void Base::_OnSkinChanged(Skin::Base*)
{
}

}; // namespace Controls

}; // namespace Gwen
