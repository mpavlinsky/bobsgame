#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger SettingsPanel::log = Logger("SettingsPanel");


SettingsPanel::SettingsPanel()
{ //=========================================================================================================================


	SubPanel();

	initGameSettingsSubPanel();

	initGUISettingsSubPanel();

	initGraphicsSettingsSubPanel();


	//   insideLayout->setHorizontalGroup(insideLayout->createParallelGroup(insideLayout->createParallelGroup(gameSettingsDialogLayout), insideLayout->createParallelGroup(guiSettingsDialogLayout), insideLayout->createParallelGroup(graphicsSettingsDialogLayout)));
	//
	//   insideLayout->setVerticalGroup(insideLayout->createSequentialGroup().addGroup(insideLayout->createParallelGroup(gameSettingsDialogLayout)).addGroup(insideLayout->createParallelGroup(guiSettingsDialogLayout)).addGroup(insideLayout->createParallelGroup(graphicsSettingsDialogLayout)));
}

void SettingsPanel::initGameSettingsSubPanel()
{ //=========================================================================================================================
	//
	//   //-----------------------------
	//   //auto zoom checkbox
	//   //-----------------------------
	//
	//   autoZoomToggleButton->setTheme(GUIManager::checkboxTheme);
	//   autoZoomToggleButton->setCanAcceptKeyboardFocus(false);
	//   autoZoomToggleButton->setActive(true);
	//   autoZoomToggleButton->addCallback([&] ()
	//      {
	//         //TODO
	//      }
	//   );
	//
	//   autoZoomLabel = new Label("Auto Zoom Camera To Fit Room");
	//   autoZoomLabel->setCanAcceptKeyboardFocus(false);
	//   autoZoomLabel->setLabelFor(autoZoomToggleButton);
	//
	//
	//   //-----------------------------
	//   //player physics checkbox
	//   //-----------------------------
	//
	//   playerPhysicsToggleButton->setTheme(GUIManager::checkboxTheme);
	//   playerPhysicsToggleButton->setCanAcceptKeyboardFocus(false);
	//   playerPhysicsToggleButton->setActive(true);
	//   playerPhysicsToggleButton->addCallback([&] ()
	//      {
	//         //TODO
	//      }
	//   );
	//
	//   playerPhysicsLabel = new Label("Player Physics");
	//   playerPhysicsLabel->setCanAcceptKeyboardFocus(false);
	//   playerPhysicsLabel->setLabelFor(playerPhysicsToggleButton);
	//
	//
	//   //-----------------------------
	//   //camera physics checkbox
	//   //-----------------------------
	//
	//   cameraPhysicsToggleButton->setTheme(GUIManager::checkboxTheme);
	//   cameraPhysicsToggleButton->setCanAcceptKeyboardFocus(false);
	//   cameraPhysicsToggleButton->setActive(true);
	//   cameraPhysicsToggleButton->addCallback([&] ()
	//      {
	//         //TODO
	//      }
	//   );
	//
	//   cameraPhysicsLabel = new Label("Camera Physics");
	//   cameraPhysicsLabel->setCanAcceptKeyboardFocus(false);
	//   cameraPhysicsLabel->setLabelFor(cameraPhysicsToggleButton);
	//
	//   //-----------------------------
	//   //player walk speed
	//   //-----------------------------
	//
	//   playerWalkSpeedScrollbar->setTheme("hscrollbar");
	//   playerWalkSpeedScrollbar->setCanAcceptKeyboardFocus(false);
	//
	//   playerWalkSpeedScrollbar->setMinMaxValue(0, 100);
	//   playerWalkSpeedScrollbar->setPageSize(10);
	//   playerWalkSpeedScrollbar->setStepSize(1);
	//
	//
	//   playerWalkSpeedScrollbar->addCallback([&] ()
	//      {
	//         //StatusBar.glossAlpha=((float)statusBarGlossScrollbar.getValue())/100.0f;
	//
	//         //if(statusBarGlossScrollbar.getValue()==100)statusBarGlossValueLabel.setText("Default");
	//         //else statusBarGlossValueLabel.setText(""+(statusBarGlossScrollbar.getValue())+"%");
	//
	//         //TODO
	//      }
	//   );
	//
	//   playerWalkSpeedScrollbar->setValue((int)(100), true);
	//
	//   playerWalkSpeedLabel = new Label("Player Walk Speed: ");
	//   playerWalkSpeedLabel->setCanAcceptKeyboardFocus(false);
	//   playerWalkSpeedLabel->setLabelFor(playerWalkSpeedScrollbar);
	//
	//
	//   //-----------------------------
	//   //group layout
	//   //-----------------------------
	//
	//   gameSettingsDialogLayout = new DialogLayout();
	//   gameSettingsDialogLayout->setCanAcceptKeyboardFocus(false);
	//
	//   gameSettingsDialogLayout->setHorizontalGroup(gameSettingsDialogLayout->createParallelGroup(gameSettingsDialogLayout->createSequentialGroup(gameSettingsDialogLayout->createParallelGroup(autoZoomLabel, playerPhysicsLabel, cameraPhysicsLabel), gameSettingsDialogLayout->createParallelGroup(autoZoomToggleButton, playerPhysicsToggleButton, cameraPhysicsToggleButton)), gameSettingsDialogLayout->createSequentialGroup(gameSettingsDialogLayout->createParallelGroup(playerWalkSpeedLabel), gameSettingsDialogLayout->createParallelGroup(playerWalkSpeedScrollbar), gameSettingsDialogLayout->createParallelGroup(playerWalkSpeedValueLabel))));
	//
	//   gameSettingsDialogLayout->setVerticalGroup(gameSettingsDialogLayout->createSequentialGroup().addGroup(gameSettingsDialogLayout->createParallelGroup(autoZoomLabel, autoZoomToggleButton)).addGroup(gameSettingsDialogLayout->createParallelGroup(playerPhysicsLabel, playerPhysicsToggleButton)).addGroup(gameSettingsDialogLayout->createParallelGroup(cameraPhysicsLabel, cameraPhysicsToggleButton)).addGroup(gameSettingsDialogLayout->createParallelGroup(playerWalkSpeedLabel, playerWalkSpeedScrollbar, playerWalkSpeedValueLabel)));
}

void SettingsPanel::initGUISettingsSubPanel()
{ //=========================================================================================================================

	//
	//   //-----------------------------
	//   //white theme checkbox
	//   //-----------------------------
	//
	//   whiteThemeToggleButton->setTheme(GUIManager::checkboxTheme);
	//   whiteThemeToggleButton->setCanAcceptKeyboardFocus(false);
	//   whiteThemeToggleButton->setActive(false); //guiMan().lightTheme
	//   //whiteStatusBarToggleButton.setTooltipContent("Toggle Light Status Bar");
	//   whiteThemeToggleButton->addCallback([&] ()
	//      {
	//         if (getGUIManager()->lightTheme == true)
	//         {
	//            GUIManager().setDarkTheme();
	//         }
	//         else
	//         {
	//            GUIManager().setLightTheme();
	//         }
	//      }
	//   );
	//
	//   whiteStatusBarToggleButtonLabel = new Label("Toggle Light Theme");
	//   whiteStatusBarToggleButtonLabel->setCanAcceptKeyboardFocus(false);
	//   whiteStatusBarToggleButtonLabel->setLabelFor(whiteThemeToggleButton);
	//
	//   //-----------------------------
	//   //status bar gloss scrollbar
	//   //-----------------------------
	//
	//   statusBarGlossScrollbar->setTheme("hscrollbar");
	//   statusBarGlossScrollbar->setCanAcceptKeyboardFocus(false);
	//
	//   statusBarGlossScrollbar->setMinMaxValue(0, 100);
	//   statusBarGlossScrollbar->setPageSize(10);
	//   statusBarGlossScrollbar->setStepSize(1);
	//
	//
	//   statusBarGlossScrollbar->setValue(100, true);
	//   //statusBarGlossScrollbar.setValue((int)(statusBar().glossAlpha*100), true);
	//
	//   statusBarGlossScrollbar->addCallback([&] ()
	//      {
	//         getStatusBar()->glossAlpha = ((float)(statusBarGlossScrollbar->getValue())) / 100.0f;
	//
	//         if (statusBarGlossScrollbar->getValue() == 100)
	//         {
	//            statusBarGlossValueLabel->setText("Default");
	//         }
	//         else
	//         {
	//            statusBarGlossValueLabel->setText(string("") + (statusBarGlossScrollbar->getValue()) + string("%"));
	//         }
	//      }
	//   );
	//
	//
	//   statusBarGlossLabel = new Label("Status Bar Gloss: ");
	//   statusBarGlossLabel->setCanAcceptKeyboardFocus(false);
	//   statusBarGlossLabel->setLabelFor(statusBarGlossScrollbar);
	//
	//   //-----------------------------
	//   //grayscale checkbox
	//   //-----------------------------
	//
	//   //		grayscaleToggleButton.setTheme(GUIManager.checkboxTheme);
	//   //		grayscaleToggleButton.setCanAcceptKeyboardFocus(false);
	//   //		grayscaleToggleButton.setActive(false);//Main.getGame().grayscale);
	//   //		//grayscaleToggleButton.setTooltipContent("Toggle grayscale");
	//   //		grayscaleToggleButton.addCallback(new Runnable()
	//   //		{
	//   //			public void run()
	//   //			{
	//   //				g.grayscale=!g.grayscale;
	//   //			}
	//   //		});
	//   //
	//   //		grayscaleToggleButtonLabel = new Label("Grayscale");
	//   //		grayscaleToggleButtonLabel.setCanAcceptKeyboardFocus(false);
	//   //		grayscaleToggleButtonLabel.setLabelFor(grayscaleToggleButton);
	//
	//
	//   guiSettingsDialogLayout = new DialogLayout();
	//   guiSettingsDialogLayout->setCanAcceptKeyboardFocus(false);
	//
	//
	//   guiSettingsDialogLayout->setHorizontalGroup(guiSettingsDialogLayout->createParallelGroup(guiSettingsDialogLayout->createSequentialGroup(guiSettingsDialogLayout->createParallelGroup(whiteStatusBarToggleButtonLabel), guiSettingsDialogLayout->createParallelGroup(whiteThemeToggleButton)), guiSettingsDialogLayout->createSequentialGroup(guiSettingsDialogLayout->createParallelGroup(statusBarGlossLabel), guiSettingsDialogLayout->createParallelGroup(statusBarGlossScrollbar), guiSettingsDialogLayout->createParallelGroup(statusBarGlossValueLabel))));
	//
	//   guiSettingsDialogLayout->setVerticalGroup(guiSettingsDialogLayout->createSequentialGroup().addGroup(guiSettingsDialogLayout->createParallelGroup(whiteThemeToggleButton, whiteStatusBarToggleButtonLabel)).addGroup(guiSettingsDialogLayout->createParallelGroup(statusBarGlossLabel, statusBarGlossScrollbar, statusBarGlossValueLabel)));
	//   //.addGroup(guiSettingsDialogLayout.createParallelGroup(grayscaleToggleButtonLabel, grayscaleToggleButton))
	//
}

void SettingsPanel::initGraphicsSettingsSubPanel()
{ //=========================================================================================================================

	//
	//   //-----------------------------
	//   //hq2x checkbox
	//   //-----------------------------
	//
	//   hq2xToggleButton->setTheme(GUIManager::checkboxTheme);
	//   hq2xToggleButton->setCanAcceptKeyboardFocus(false);
	//   hq2xToggleButton->setActive(MapManager::generateHQ2XChunks);
	//
	//   hq2xToggleButton->addCallback([&] ()
	//      {
	//         MapManager::generateHQ2XChunks = !MapManager::generateHQ2XChunks;
	//      }
	//   );
	//
	//   hq2xToggleButtonLabel = new Label("Generate HQ2X Background");
	//   hq2xToggleButtonLabel->setCanAcceptKeyboardFocus(false);
	//   hq2xToggleButtonLabel->setLabelFor(hq2xToggleButton);
	//
	//   //-----------------------------
	//   //fbo checkbox
	//   //-----------------------------
	//
	//   fboToggleButton->setTheme(GUIManager::checkboxTheme);
	//   fboToggleButton->setCanAcceptKeyboardFocus(false);
	//   fboToggleButton->setActive(GLUtils::useFBO);
	//   //fboToggleButton.setTooltipContent("Toggle FBO");
	//   fboToggleButton->addCallback([&] ()
	//      {
	//         GLUtils::useFBO = !GLUtils::useFBO;
	//      }
	//   );
	//
	//   fboToggleButtonLabel = new Label("Use Framebuffer Objects");
	//   fboToggleButtonLabel->setCanAcceptKeyboardFocus(false);
	//   fboToggleButtonLabel->setLabelFor(fboToggleButton);
	//
	//   //-----------------------------
	//   //shaders checkbox
	//   //-----------------------------
	//
	//   shadersToggleButton->setTheme(GUIManager::checkboxTheme);
	//   shadersToggleButton->setCanAcceptKeyboardFocus(false);
	//   shadersToggleButton->setActive(GLUtils::useShaders);
	//   //shadersToggleButton.setTooltipContent("Toggle shaders");
	//   shadersToggleButton->addCallback([&] ()
	//      {
	//         GLUtils::useShaders = !GLUtils::useShaders;
	//      }
	//   );
	//
	//   shadersToggleButtonLabel = new Label("Use Shaders");
	//   shadersToggleButtonLabel->setCanAcceptKeyboardFocus(false);
	//   shadersToggleButtonLabel->setLabelFor(shadersToggleButton);
	//
	//
	//   //
	//   //		//-----------------------------
	//   //		//gamma scrollbar
	//   //		//-----------------------------
	//   //
	//   //		gammaScrollbar.setTheme("hscrollbar");
	//   //		gammaScrollbar.setCanAcceptKeyboardFocus(false);
	//   //		//gammaScrollbar.setTooltipContent("Set Gamma");
	//   //		gammaScrollbar.setMinMaxValue(0, 200);
	//   //		gammaScrollbar.setPageSize(10);
	//   //		gammaScrollbar.setStepSize(1);
	//   //
	//   //		gammaScrollbar.setValue(100);//(int)(Main.getGame().gamma*100), true);
	//   //
	//   //		gammaScrollbar.addCallback(new Runnable()
	//   //		{
	//   //			public void run()
	//   //			{
	//   //				g.gamma=((float)gammaScrollbar.getValue())/100.0f;
	//   //
	//   //				if(gammaScrollbar.getValue()>100)gammaScrollbarValueLabel.setText("+"+(gammaScrollbar.getValue()-100)+"%");
	//   //				else if(gammaScrollbar.getValue()==100)gammaScrollbarValueLabel.setText("Default");
	//   //				else gammaScrollbarValueLabel.setText(""+(gammaScrollbar.getValue()-100)+"%");
	//   //			}
	//   //		});
	//   //
	//   //
	//   //
	//   //		gammaScrollbarLabel = new Label("Gamma: ");
	//   //		gammaScrollbarLabel.setCanAcceptKeyboardFocus(false);
	//   //		gammaScrollbarLabel.setLabelFor(gammaScrollbar);
	//   //
	//   //		//-----------------------------
	//   //		//contrast scrollbar
	//   //		//-----------------------------
	//   //
	//   //		contrastScrollbar.setTheme("hscrollbar");
	//   //		contrastScrollbar.setCanAcceptKeyboardFocus(false);
	//   //		//contrastScrollbar.setTooltipContent("Set Contrast");
	//   //		contrastScrollbar.setMinMaxValue(0, 200);
	//   //		contrastScrollbar.setPageSize(10);
	//   //		contrastScrollbar.setStepSize(1);
	//   //
	//   //		contrastScrollbar.setValue(100);//(int)(Main.getGame().contrast*100), true);
	//   //
	//   //
	//   //		contrastScrollbar.addCallback(new Runnable()
	//   //		{
	//   //			public void run()
	//   //			{
	//   //				g.contrast=((float)contrastScrollbar.getValue())/100.0f;
	//   //
	//   //				if(contrastScrollbar.getValue()>100)contrastScrollbarValueLabel.setText("+"+(contrastScrollbar.getValue()-100)+"%");
	//   //				else if(contrastScrollbar.getValue()==100)contrastScrollbarValueLabel.setText("Default");
	//   //				else contrastScrollbarValueLabel.setText(""+(contrastScrollbar.getValue()-100)+"%");
	//   //			}
	//   //		});
	//   //
	//   //
	//   //
	//   //		contrastScrollbarLabel = new Label("Contrast: ");
	//   //		contrastScrollbarLabel.setCanAcceptKeyboardFocus(false);
	//   //		contrastScrollbarLabel.setLabelFor(contrastScrollbar);
	//   //
	//   //
	//   //		//-----------------------------
	//   //		//brightness scrollbar
	//   //		//-----------------------------
	//   //
	//   //		brightnessScrollbar.setTheme("hscrollbar");
	//   //		brightnessScrollbar.setCanAcceptKeyboardFocus(false);
	//   //		//brightnessScrollbar.setTooltipContent("Set Brightness: ");
	//   //		brightnessScrollbar.setMinMaxValue(0, 200);
	//   //		brightnessScrollbar.setPageSize(10);
	//   //		brightnessScrollbar.setStepSize(1);
	//   //
	//   //		brightnessScrollbar.setValue(100);//(int)(Main.getGame().brightness*100), true);
	//   //
	//   //
	//   //		brightnessScrollbar.addCallback(new Runnable()
	//   //		{
	//   //			public void run()
	//   //			{
	//   //				g.brightness=((float)brightnessScrollbar.getValue())/100.0f;
	//   //
	//   //				if(brightnessScrollbar.getValue()>100)brightnessScrollbarValueLabel.setText("+"+(brightnessScrollbar.getValue()-100)+"%");
	//   //				else if(brightnessScrollbar.getValue()==100)brightnessScrollbarValueLabel.setText("Default");
	//   //				else brightnessScrollbarValueLabel.setText(""+(brightnessScrollbar.getValue()-100)+"%");
	//   //			}
	//   //		});
	//   //
	//   //
	//   //
	//   //		brightnessScrollbarLabel = new Label("Brightness: ");
	//   //		brightnessScrollbarLabel.setCanAcceptKeyboardFocus(false);
	//   //		brightnessScrollbarLabel.setLabelFor(brightnessScrollbar);
	//   //
	//   //
	//   //		//-----------------------------
	//   //		//saturation scrollbar
	//   //		//-----------------------------
	//   //
	//   //		saturationScrollbar.setTheme("hscrollbar");
	//   //		saturationScrollbar.setCanAcceptKeyboardFocus(false);
	//   //		//saturationScrollbar.setTooltipContent("Set Saturation");
	//   //		saturationScrollbar.setMinMaxValue(0, 200);
	//   //		saturationScrollbar.setPageSize(10);
	//   //		saturationScrollbar.setStepSize(1);
	//   //
	//   //
	//   //		saturationScrollbar.setValue(100);//(int)(Main.getGame().saturation*100), true);
	//   //
	//   //		saturationScrollbar.addCallback(new Runnable()
	//   //		{
	//   //			public void run()
	//   //			{
	//   //				g.saturation=((float)saturationScrollbar.getValue())/100.0f;
	//   //
	//   //				if(saturationScrollbar.getValue()>100)saturationScrollbarValueLabel.setText("+"+(saturationScrollbar.getValue()-100)+"%");
	//   //				else if(saturationScrollbar.getValue()==100)saturationScrollbarValueLabel.setText("Default");
	//   //				else saturationScrollbarValueLabel.setText(""+(saturationScrollbar.getValue()-100)+"%");
	//   //			}
	//   //		});
	//   //
	//   //
	//   //
	//   //		saturationScrollbarLabel = new Label("Saturation: ");
	//   //		saturationScrollbarLabel.setCanAcceptKeyboardFocus(false);
	//   //		saturationScrollbarLabel.setLabelFor(saturationScrollbar);
	//   //
	//
	//
	//   graphicsSettingsDialogLayout = new DialogLayout();
	//   //graphicsSettingsDialogLayout.setTheme("dark-paneldialoglayout");
	//   graphicsSettingsDialogLayout->setCanAcceptKeyboardFocus(false);
	//
	//
	//   graphicsSettingsDialogLayout->setHorizontalGroup(graphicsSettingsDialogLayout->createParallelGroup(graphicsSettingsDialogLayout->createSequentialGroup(graphicsSettingsDialogLayout->createParallelGroup(hq2xToggleButtonLabel, fboToggleButtonLabel, shadersToggleButtonLabel), graphicsSettingsDialogLayout->createParallelGroup(hq2xToggleButton, fboToggleButton, shadersToggleButton))));
	//   //						,
	//   //						graphicsSettingsDialogLayout.createSequentialGroup//horizontal row
	//   //						(
	//   //								graphicsSettingsDialogLayout.createParallelGroup//vertical column
	//   //								(
	//   //										gammaScrollbarLabel,contrastScrollbarLabel,brightnessScrollbarLabel,saturationScrollbarLabel
	//   //								),
	//   //
	//   //								graphicsSettingsDialogLayout.createParallelGroup//vertical column
	//   //								(
	//   //										gammaScrollbar,contrastScrollbar,brightnessScrollbar,saturationScrollbar
	//   //								),
	//   //
	//   //								graphicsSettingsDialogLayout.createParallelGroup//vertical column
	//   //								(
	//   //										gammaScrollbarValueLabel,contrastScrollbarValueLabel,brightnessScrollbarValueLabel,saturationScrollbarValueLabel
	//   //								)
	//   //						)
	//
	//   graphicsSettingsDialogLayout->setVerticalGroup(graphicsSettingsDialogLayout->createSequentialGroup().addGroup(graphicsSettingsDialogLayout->createParallelGroup(hq2xToggleButtonLabel, hq2xToggleButton)).addGroup(graphicsSettingsDialogLayout->createParallelGroup(fboToggleButtonLabel, fboToggleButton)).addGroup(graphicsSettingsDialogLayout->createParallelGroup(shadersToggleButtonLabel, shadersToggleButton)));
	//   //.addGroup(graphicsSettingsDialogLayout.createParallelGroup(gammaScrollbarLabel,gammaScrollbar,gammaScrollbarValueLabel))
	//   //.addGroup(graphicsSettingsDialogLayout.createParallelGroup(contrastScrollbarLabel,contrastScrollbar,contrastScrollbarValueLabel))
	//   //.addGroup(graphicsSettingsDialogLayout.createParallelGroup(brightnessScrollbarLabel,brightnessScrollbar,brightnessScrollbarValueLabel))
	//   //.addGroup(graphicsSettingsDialogLayout.createParallelGroup(saturationScrollbarLabel,saturationScrollbar,saturationScrollbarValueLabel))
}

void SettingsPanel::layout()
{ //=========================================================================================================================

	//
	//   playerWalkSpeedScrollbar->setMinSize(400, 20);
	//
	//   statusBarGlossScrollbar->setMinSize(400, 20);
	//   //statusBarGlossScrollbar.setMaxSize(400, 20);
	//
	//
	//   //		gammaScrollbar.setMinSize(400, 20);
	//   //		//gammaScrollbar.setMaxSize(400, 20);
	//   //
	//   //		contrastScrollbar.setMinSize(400, 20);
	//   //		//contrastScrollbar.setMaxSize(400, 20);
	//   //
	//   //		brightnessScrollbar.setMinSize(400, 20);
	//   //		//brightnessScrollbar.setMaxSize(400, 20);
	//   //
	//   //		saturationScrollbar.setMinSize(400, 20);
	//   //		//saturationScrollbar.setMaxSize(400, 20);


	SubPanel::layout();
}

void SettingsPanel::setVisible(bool b)
{ //=========================================================================================================================
	SubPanel::setVisible(b);


	//TODO: sync the button and checkbox states based on Game().contrast, etc.
	//currently they can do out of sync
}

