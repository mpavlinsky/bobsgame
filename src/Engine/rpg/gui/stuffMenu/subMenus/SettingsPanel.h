//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class SettingsPanel : public SubPanel
{
public:

	static Logger log;


	//   Label* autoZoomLabel;
	//   ToggleButton*const autoZoomToggleButton = new ToggleButton("");
	//
	//   Label* playerPhysicsLabel;
	//   ToggleButton*const playerPhysicsToggleButton = new ToggleButton("");
	//
	//   Label* cameraPhysicsLabel;
	//   ToggleButton*const cameraPhysicsToggleButton = new ToggleButton("");
	//
	//   Label* playerWalkSpeedLabel;
	//   Scrollbar*const playerWalkSpeedScrollbar = new Scrollbar(Scrollbar::Orientation::HORIZONTAL);
	//   Label*const playerWalkSpeedValueLabel = new Label("Default");
	//
	//
	//   DialogLayout* gameSettingsDialogLayout;
	//
	//
	//   Label* whiteStatusBarToggleButtonLabel;
	//   ToggleButton*const whiteThemeToggleButton = new ToggleButton("");
	//
	//   //	Label grayscaleToggleButtonLabel;
	//   //	final ToggleButton grayscaleToggleButton = new ToggleButton("");
	//
	//   Label* statusBarGlossLabel;
	//   Scrollbar*const statusBarGlossScrollbar = new Scrollbar(Scrollbar::Orientation::HORIZONTAL);
	//   Label*const statusBarGlossValueLabel = new Label("Default");
	//
	//   DialogLayout* guiSettingsDialogLayout;
	//
	//
	//   Label* hq2xToggleButtonLabel;
	//   ToggleButton*const hq2xToggleButton = new ToggleButton("");
	//
	//   Label* fboToggleButtonLabel;
	//   ToggleButton*const fboToggleButton = new ToggleButton("");
	//
	//   Label* shadersToggleButtonLabel;
	//   ToggleButton*const shadersToggleButton = new ToggleButton("");
	//
	//
	//   //	Label gammaScrollbarLabel;
	//   //	final public Scrollbar gammaScrollbar = new Scrollbar(Orientation.HORIZONTAL);
	//   //	final Label gammaScrollbarValueLabel = new Label("Default");
	//   //
	//   //
	//   //	Label contrastScrollbarLabel;
	//   //	final public Scrollbar contrastScrollbar = new Scrollbar(Orientation.HORIZONTAL);
	//   //	final Label contrastScrollbarValueLabel = new Label("Default");
	//   //
	//   //
	//   //	Label brightnessScrollbarLabel;
	//   //	final public Scrollbar brightnessScrollbar = new Scrollbar(Orientation.HORIZONTAL);
	//   //	final Label brightnessScrollbarValueLabel = new Label("Default");
	//   //
	//   //
	//   //	Label saturationScrollbarLabel;
	//   //	final public Scrollbar saturationScrollbar = new Scrollbar(Orientation.HORIZONTAL);
	//   //	final Label saturationScrollbarValueLabel = new Label("Default");
	//
	//
	//   DialogLayout* graphicsSettingsDialogLayout;


	SettingsPanel();


	virtual void initGameSettingsSubPanel();


	virtual void initGUISettingsSubPanel();


	virtual void initGraphicsSettingsSubPanel();


	virtual void layout() override;


	virtual void setVisible(bool b) override;
};

