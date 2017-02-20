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

#include "Gwen/Events.h"
#include "Gwen/Macros.h"
#include "Gwen/renderer/gwen_renderer_base.h"
#include "Gwen/skin/gwen_skin_base.h"
#include "Gwen/Structures.h"

#include "Gwen/Utility.h"

#include <map>
#include <list>

namespace Gwen
{

namespace Skin
{

class Base;

}; // namespace Skin

namespace Controls
{

class Base;
class Canvas;

/// \brief A global pointer to the hovered control.
extern Base* _hovered_control;

/// \brief A global pointer to the control with keyboard focus.
extern Base* _keyboard_focus;

/// \brief A global pointer to the control with mouse focus.
extern Base* _mouse_focus;

/// \brief This class represents a base class for all UI controls.
class Base : public Event::Handler
{
public:
    /// \brief Constructor.
    explicit Base(Base* parent, const std::string& name = "");

    /// \brief Destructor.
    virtual ~Base() override;

    /// \brief Called before the control is deleted.
    virtual void PreDelete(Gwen::Skin::Base*);

    /// \brief Deletes the control.
    virtual void DelayedDelete();

    /// \brief Sets the parent control.  Adds this control as a child control of the parent control.  Adds this control to the front
    ///        or back of the parent control's child control list.  Defaults to the back.
    virtual void SetParent(Controls::Base* parent, bool to_back = true);

    /// \brief Gets the parent control.
    virtual Base* GetParent() const;

    /// \brief Gets the canvas.
    virtual Canvas* GetCanvas();

    /// \brief Adds a child control to the front or back of the list.  Defaults to the back.
    virtual void AddChild(Base* child, bool to_back = true);

    /// \brief Removes a child control.
    virtual void RemoveChild(Base* child);

    /// \brief Deletes the children.
    virtual void RemoveChildren();

    /// \brief Is the control a child?
    virtual bool IsChild(Base* child) const;

    /// \brief Gets the children.
    virtual std::list<Base*>& GetChildren();

    /// \brief Gets the number of children.
    virtual unsigned GetChildrenCount() const;

    /// \brief Gets a child.
    virtual Base* GetChild(unsigned index);

    /// \brief Gets a child.
    virtual const Base* GetChild(unsigned index) const;

    /// \brief The size of the children.
    virtual Gwen::Point ChildrenSize() const;

    /// \brief Sizes the control to the size of its children.
    virtual bool SizeToChildren(bool size_width = true, bool size_height = true);

    /// \brief Finds a child control by its name.
    virtual Base* FindChildByName(const std::string& name, bool recursive = false);

    /// \brief Finds a child control by its name.
    template <class T>
    T* FindChild(const std::string& name, bool recursive = false)
    {
        return dynamic_cast<T*>(FindChildByName(name, recursive));
    }

    /// \brief Sets the name.
    virtual void SetName(const std::string& name);

    /// \brief Gets the name.
    virtual std::string GetName() const;

    /// \brief Animates the control.
    virtual void Think();

    /// \brief Sends the control to the back.
    virtual void SendToBack();

    /// \brief Brings the control to the front.
    virtual void BringToFront();

    /// \brief Converts to canvas space.
    virtual Gwen::Point LocalPositionToCanvas(const Gwen::Point& position);

    /// \brief Converts to local space.
    virtual Gwen::Point CanvasPositionToLocal(const Gwen::Point& position);

    /// \brief Sets the dock.
    virtual void SetDock(int dock);

    /// \brief Gets the dock.
    virtual int GetDock() const;

    /// \brief Sets restrict to parent.
    virtual void SetRestrictToParent(bool restrict_to_parent);

    /// \brief Gets restrict to parent.
    virtual bool GetRestrictToParent() const;

    /// \brief Gets the X coordinate.
    virtual int X() const;

    /// \brief Gets the Y coordinate.
    virtual int Y() const;

    /// \brief Gets the width.
    virtual int Width() const;

    /// \brief Gets the height.
    virtual int Height() const;

    /// \brief Gets the bottom boundary.
    virtual int Bottom() const;

    /// \brief Gets the right boundary.
    virtual int Right() const;

    /// \brief Gets the margin.
    virtual Margin GetMargin() const;

    /// \brief Gets the padding.
    virtual Padding GetPadding() const;

    /// \brief Sets the position.
    virtual void SetPosition(int x, int y);

    /// \brief Sets the position.
    virtual void SetPosition(const Point& point);

    /// \brief Sets the position
    virtual void SetPosition(const Gwen::Position::Position& alignment, int x_padding, int y_padding);

    /// \brief Gets the position.
    virtual Point GetPosition() const;

    /// \brief Sets the width.
    virtual void SetWidth(int width);

    /// \brief Sets the height.
    virtual void SetHeight(int height);

    /// \brief Sets the size.
    virtual bool SetSize(int width, int height);

    /// \brief Sets the size.
    virtual bool SetSize(const Point& point);

    /// \brief Gets the size.
    virtual Point GetSize() const;

    /// \brief Sets the bounds.
    virtual bool SetBounds(int x, int y, int width, int height);

    /// \brief Sets the bounds.
    virtual bool SetBounds(const Gwen::Rectangle& bounds);

    /// \brief Sets the padding; the space within an element.
    virtual bool SetPadding(const Padding& padding);

    /// \brief Sets the margin, the space between elements.
    virtual bool SetMargin(const Margin& margin);

    /// \brief Moves the control.
    virtual void MoveTo(int x, int y);

    /// \brief Moves the control.
    virtual void MoveBy(int x, int y);

    /// \brief Gets the bounds.
    virtual Gwen::Rectangle GetBounds() const;

    /// \brief Gets The controls at the position.
    virtual std::vector<Base*> GetControlsAt(int x, int y);

    /// \brief Gets the inner bounds, the bounds after a layout.
    virtual Gwen::Rectangle GetInnerBounds() const;

    /// \brief Gets the render bounds, the bounds translated to point (0, 0).
    virtual Gwen::Rectangle GetRenderBounds() const;

    /// \brief Draws the UI element.
    virtual void DoRender(Gwen::Skin::Base* skin);

    /// \brief Draws the UI element.
    virtual void RenderRecursive(Gwen::Skin::Base* skin, const Gwen::Rectangle& clipping_rectangle);

    /// \brief Should the control clip its children?
    virtual bool GetShouldClip() const;

    /// \brief Sets if the UI element is visible.
    virtual void SetHidden(bool is_hidden);

    /// \brief Gets if the UI element is hidden.
    virtual bool Hidden() const;

    /// \brief Gets if the UI element is visible.
    virtual bool Visible() const;

    /// \brief Hides the UI element.
    virtual void Hide();

    /// \brief Shows the UI element.
    virtual void Show();

    /// \brief Sets the skin.
    virtual void SetSkin(Skin::Base* skin, bool recursive = false);

    /// \brief Gets the skin.
    virtual Gwen::Skin::Base* GetSkin(void);

    /// \brief Sets should draw background.
    virtual void SetShouldDrawBackground(bool should_draw_background);

    /// \brief Gets should draw background.
    virtual bool GetShouldDrawBackground() const;

    /// \brief Called when the mouse enters the control.
    virtual void OnMouseEnter();

    /// \brief Called when the mouse leaves the control.
    virtual void OnMouseLeave();

    /// \brief Called when the mouse is moved.
    virtual void OnMouseMoved(int x, int y, int delta_x, int delta_y);

    /// \brief Called when the mouse is wheeled.
    virtual bool OnMouseWheeled(int delta);

    /// \brief Called when the left mouse button is pressed.
    virtual void OnMouseClickLeft(int x, int y, bool is_down);

    /// \brief Called when the right mouse button is pressed.
    virtual void OnMouseClickRight(int x, int y, bool is_down);

    /// \brief Called when the left mouse button is double clicked.
    virtual void OnMouseDoubleClickLeft(int x, int y);

    /// \brief Called when the right mouse button is double clicked.
    virtual void OnMouseDoubleClickRight(int x, int y);

    /// \brief Called when the control gains keyboard focus.
    virtual void OnKeyboardFocus();

    /// \brief Called when the control loses keyboard focus.
    virtual void OnLostkeyboardFocus();

    /// \brief Sets mouse input enabled.
    virtual void SetMouseInputEnabled(bool mouse_input_enabled);

    /// \brief Gets mouse input enabled.
    virtual bool GetMouseInputEnabled() const;

    /// \brief Gets keyboard input enabled.
    virtual void SetKeyboardInputEnabled(bool keyboard_input_enabled);

    /// \brief Sets keyboard input enabled.
    virtual bool GetKeyboardInputEnabled() const;

    /// \brief Called when a character key is pressed.
    virtual bool OnCharacter(char character);

    /// \brief Called when a key is pressed.
    virtual bool OnKeyPress(int key, bool is_down = true);

    /// \brief Called when a key is released.
    virtual bool OnKeyRelease(int key);

    /// \brief Called when the cut accelerator is pressed.
    virtual void OnCut(Base* control);

    /// \brief Called when the copy accelerator is pressed.
    virtual void OnCopy(Base* control);

    /// \brief Called when the paste accelerator is pressed.
    virtual void OnPaste(Base* control);

    /// \brief Called when the select all accelerator is pressed.
    virtual void OnSelectAll(Base* control);

    /// \brief Called when the tab key is pressed.
    virtual bool OnKeyTab(bool is_down);

    /// \brief Called when the space key is pressed.
    virtual bool OnKeySpace(bool is_down);

    /// \brief Called when the return key is pressed.
    virtual bool OnKeyReturn(bool is_down);

    /// \brief Called when the back space key is pressed.
    virtual bool OnKeyBackspace(bool is_down);

    /// \brief Called when the delete key is pressed.
    virtual bool OnKeyDelete(bool is_down);

    /// \brief Called when the home key is pressed.
    virtual bool OnKeyHome(bool is_down);

    /// \brief Called when the end key is pressed.
    virtual bool OnKeyEnd(bool is_down);

    /// \brief Called when the left key is pressed.
    virtual bool OnKeyLeft(bool is_down);

    /// \brief Called when the right key is pressed.
    virtual bool OnKeyRight(bool is_down);

    /// \brief Called when the up key is pressed.
    virtual bool OnKeyUp(bool is_down);

    /// \brief Called when the down key is pressed.
    virtual bool OnKeyDown(bool is_down);

    /// \brief Called when the escape key is pressed.
    virtual bool OnKeyEscape(bool is_down);

    /// \brief Is the mouse over this control?
    virtual bool IsHovered();

    /// \brief Does this control have focus?
    virtual bool HasFocus();

    /// \brief Focus this control.
    virtual void Focus();

    /// \brief Drop the focus.
    virtual void Blur();

    /// \brief Sets if the control is disabled.
    virtual void SetDisabled(bool disabled);

    /// \brief Is the control disabled?
    virtual bool IsDisabled() const;

    /// \brief Redraws the control.
    virtual void Redraw();

    /// \brief Updates the control's colors.
    virtual void UpdateColors();

    /// \brief Sets the tooltip.
    virtual void SetTooltip(const std::string& text);

    /// \brief Sets the tooltip.
    virtual void SetTooltip(Base* tooltip);

    /// \brief Gets the tooltip.
    virtual Base* GetTooltip();

    /// \brief Is this control a menu control?
    virtual bool GetMenuComponent();

    /// \brief Closes all menu controls.
    virtual void CloseMenus();

    /// \brief Sets tabable.
    virtual void SetTabable(bool isTabable);

    /// \brief Is this control tabable?
    virtual bool IsTabable() const;

    /// \brief Only handle accelerators when the control has focus.
    virtual bool GetAcceleratorOnlyOnFocus() const;

    /// \brief Handle the accelerator.
    virtual bool HandleAccelerator(const std::string& accelerator);

    /// \brief Adds an accelerator.
    template <typename T>
    void AddAccelerator(const std::string& accelerator, T function, Event::Handler* handler = nullptr)
    {
        if (handler == nullptr)
        {
            handler = this;
        }

        // Create the event.
        Event::Caller* caller = new Event::Caller();
        caller->Add(handler, function);

        // Create the key for the map.
        std::string accelerator_name = accelerator;
        Gwen::Utility::String::ToUpper(accelerator_name);
        Gwen::Utility::String::Strip(accelerator_name, " ");

        // Remove the old event if it is present.
        if (_accelerators.find(accelerator_name) != _accelerators.end())
        {
            delete _accelerators[accelerator_name];
            _accelerators[accelerator_name] = nullptr;
            _accelerators.erase(accelerator_name);
        }

        // Store the accelerator.
        _accelerators[accelerator_name] = caller;
    }

    /// \brief Flags the control for redraw.
    virtual void Invalidate();

    /// \briefs Flags the children for redraw.
    virtual void InvalidateChildren();

    /// \brief Lays out the control.
    virtual void Layout(Gwen::Skin::Base* skin);

    /// \brief Lays out the control.
    virtual void RecurseLayout(Gwen::Skin::Base* skin);

    /// \brief Lays out the control.
    virtual void PostLayout(Gwen::Skin::Base* skin);

    /// \brief An event for when the mouse enters the control.
    Gwen::Event::Caller _on_hover_enter;

    /// \brief An event for when the mouse leaves the control.
    Gwen::Event::Caller _on_hover_leave;

protected:
    /// \brief Draws the UI element.
    virtual void Render(Gwen::Skin::Base* skin);

    /// \brief Draws the UI element.
    virtual void RenderUnder(Gwen::Skin::Base* skin);

    /// \brief Draws the UI element.
    virtual void RenderOver(Gwen::Skin::Base* skin);

    /// \brief Draws the UI element.
    virtual void RenderFocus(Gwen::Skin::Base* skin);

    /// \brief Update the render bounds.
    virtual void UpdateRenderBounds();

    /// \brief Called when a child control is added.
    virtual void _OnChildAdded(Base* child);

    /// \brief Called when a child control is removed.
    virtual void _OnChildRemoved(Base* child);

    /// \brief Called when the bounds change.
    virtual void _OnBoundsChanged(const Gwen::Rectangle& old_bounds);

    /// \brief Called when a child's bounds change.
    virtual void _OnChildBoundsChanged(const Gwen::Rectangle& old_child_bounds, Base* child);

    /// \brief Called when the scale of the control changes.
    virtual void _OnScaleChanged();

    /// \brief Called when the skin is changed.
    virtual void _OnSkinChanged(Gwen::Skin::Base* skin);

    /// \brief The parent.
    Base* _parent;

    /// \brief The actual parent.  This is used with controls requiring the inner panel.
    Base* _actual_parent;

    /// \brief The inner panel.
    Base* _inner_panel;

    /// \brief The tooltip.
    Base* _tooltip;

    /// \brief The children.
    std::list<Base*> _children;

    /// \brief The accelerators.
    std::map<std::string, Event::Caller*> _accelerators;

    /// \brief The skin.
    Skin::Base* _skin;

    /// \brief The bounds.
    Gwen::Rectangle _bounds;

    /// \brief The render bounds.
    Gwen::Rectangle _render_bounds;

    /// \brief The inner bounds.
    Gwen::Rectangle _inner_bounds;

    /// \brief The padding.
    Padding _padding;

    /// \brief The margin.
    Margin _margin;

    /// \brief The name.
    std::string _name;

    /// \brief The dock.
    int _dock;

    /// \brief Should the position be restricted to the control's parent.
    bool _restrict_to_parent;

    /// \brief Is the control disabled?
    bool _disabled;

    /// \brief Is the control hidden?
    bool _hidden;

    /// \brief Is mouse input enabled?
    bool _mouse_input_enabled;

    /// \brief Is keyboard input enabled?
    bool _keyboard_input_enabled;

    /// \brief Should the background be drawn?
    bool _draw_background;

    /// \brief Is this control tabable?
    bool _tabable;

    /// \brief Does the lay out need updated.
    bool _needs_layout;
};

}; // namespace Controls

}; // namespace Gwen
