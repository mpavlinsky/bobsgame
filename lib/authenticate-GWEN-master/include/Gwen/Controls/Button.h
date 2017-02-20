/*
 *  GWEN
 *  Copyright (c) 2010 Facepunch Studios
 *  See license in Gwen.h
 */

#pragma once

#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Label.h"

namespace Gwen
{
namespace Controls
{

// Forward declarations.
class ImagePanel;

/// \brief This class represents a button.
class Button : public Label
{
public:
    /// \brief Constructor.
    GWEN_CONTROL(Button, Label);

    /// \brief Destructor.
    virtual ~Button() override;

    /// \brief Sets depressed.
    virtual void SetDepressed(bool is_depressed);

    /// \brief Gets depressed.
    virtual bool GetDepressed() const;

    /// \brief Sets toggle.
    virtual void SetToggle(bool is_toggle);

    /// \brief Gets toggle.
    virtual bool GetToggle() const;

    /// \brief Sets toggle state.
    virtual void SetToggleState(bool toggle_state);

    /// \brief Gets toggle state.
    virtual bool GetToggleState() const;

    /// \brief Inverts the toggle state.
    virtual void Toggle();

    /// \brief Sets the image.
    virtual void SetImage(const std::string& name, bool center = false);

    /// \brief Sets the image's alpha channel.  Expects a value between 0.0f - 1.0f.
    virtual void SetImageAlpha(float alpha);

    /// \brief Updates the button's colors.
    virtual void UpdateColors() override;

    /// \brief Called when the button is pressed with the left mouse button.
    virtual void OnPressLeft();

    /// \brief Called when the button is pressed with the right mouse button.
    virtual void OnPressRight();

    /// \brief Sizes the button to its contents.
    virtual void SizeToContents() override;

    /// \brief Called when the left mouse button is pressed.
    virtual void OnMouseClickLeft(int x, int y, bool is_down) override;

    /// \brief Called when the right mouse button is pressed.
    virtual void OnMouseClickRight(int x, int y, bool is_down) override;

    /// \brief Called when the left mouse button is double clicked.
    virtual void OnMouseDoubleClickLeft(int x, int y) override;

    /// \brief Called when the right mouse button is double clicked.
    virtual void OnMouseDoubleClickRight(int x, int y) override;

    /// \brief Lays out the control.
    virtual void PostLayout(Skin::Base* skin) override;

    /// \brief An event for when the button is pressed with the left mouse button.
    Gwen::Event::Caller _on_press_left;

    /// \brief An event for when the button is pressed with the right mouse button.
    Gwen::Event::Caller _on_press_right;

    /// \brief An event for when the button is up.
    Gwen::Event::Caller _on_up;

    /// \brief An event for when the button is down.
    Gwen::Event::Caller _on_down;

    /// \brief An event for when the button is double clicked with the left mouse button.
    Gwen::Event::Caller _on_mouse_double_click_left;

    /// \brief An event for when the button is double clicked with the right mouse button.
    Gwen::Event::Caller _on_mouse_double_click_right;

    /// \brief An event for when the button is toggled.
    Gwen::Event::Caller _on_toggle;

    /// \brief An event for when the button is toggled on.
    Gwen::Event::Caller _on_toggle_on;

    /// \brief An event for when the button is toggled off.
    Gwen::Event::Caller _on_toggle_off;

protected:
    /// \brief Draws the UI element.
    virtual void Render(Skin::Base* skin) override;

    /// \brief An optional image.
    ImagePanel* _image;

    /// \brief Center the image?
    bool _center;

    /// \brief Is the button currently pressed?
    bool _depressed;

    /// \brief Is this a toggle button?
    bool _toggle;

    /// \brief Is the button currently toggled?
    bool _toggle_state;
};

}; // namespace Controls

}; // namespace Gwen
