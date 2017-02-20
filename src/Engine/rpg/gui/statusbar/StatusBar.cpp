
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger StatusBar::log = Logger("StatusBar");


BobTexture* StatusBar::blackBackgroundTexture = nullptr;
BobTexture* StatusBar::blackForegroundTexture = nullptr;
BobTexture* StatusBar::whiteBackgroundTexture = nullptr;
BobTexture* StatusBar::whiteForegroundTexture = nullptr;
BobTexture* StatusBar::backgroundTexture = nullptr;
BobTexture* StatusBar::foregroundTexture = nullptr;
BobTexture* StatusBar::glowTexture = nullptr;
BobTexture* StatusBar::dividerTexture = nullptr;
int StatusBar::sizeY = 26;
float StatusBar::glossAlpha = 1.0f;
bool StatusBar::useLightTheme = false;

StatusBar::StatusBar(BGClientEngine* g)
{ //=========================================================================================================================

	this->e = g;

	clockCaption = new ClockCaption(g);
	dayCaption = new DayCaption(g);
	moneyCaption = new MoneyCaption(g);
	ndButton = new NDButton(g);
	gameStoreButton = new GameStoreButton(g);
	stuffButton = new StuffButton(g);

	notificationManager = new NotificationManager(g);


	blackBackgroundTexture = GLUtils::getTextureFromPNG("data/statusbar/blackbarbackground.png");
	blackForegroundTexture = GLUtils::getTextureFromPNG("data/statusbar/blackbarforeground.png");

	whiteBackgroundTexture = GLUtils::getTextureFromPNG("data/statusbar/whitebarbackground.png");
	whiteForegroundTexture = GLUtils::getTextureFromPNG("data/statusbar/whitebarforeground.png");

	backgroundTexture = blackBackgroundTexture;
	foregroundTexture = blackForegroundTexture;


	glowTexture = GLUtils::getTextureFromPNG("data/statusbar/greenDot.png");
	dividerTexture = GLUtils::getTextureFromPNG("data/statusbar/dividerLine.png");
}

void StatusBar::init()
{ //=========================================================================================================================

	clockCaption->init();
	dayCaption->init();
	moneyCaption->init();
	ndButton->init();
	gameStoreButton->init();
	stuffButton->init();

	notificationManager->init();
}

void StatusBar::update()
{ //=========================================================================================================================
	clockCaption->update();
	dayCaption->update();
	moneyCaption->update();

	ndButton->update();
	gameStoreButton->update();
	stuffButton->update();

	notificationManager->update();
}

void StatusBar::setLightTheme()
{ //=========================================================================================================================

	if (useLightTheme == false)
	{
		useLightTheme = true;
		backgroundTexture = whiteBackgroundTexture;
		foregroundTexture = whiteForegroundTexture;


		clockCaption->setColors(new BobColor(200, 0, 0), BobColor::lightRed, nullptr);
		dayCaption->setColors(BobColor::black, BobColor::lighterGray, nullptr);
		moneyCaption->setColors(BobColor::green, BobColor::darkerGreen, nullptr);
	}
}

void StatusBar::setDarkTheme()
{ //=========================================================================================================================
	if (useLightTheme == true)
	{
		useLightTheme = false;
		backgroundTexture = blackBackgroundTexture;
		foregroundTexture = blackForegroundTexture;


		clockCaption->setColors(BobColor::red, BobColor::darkerRed, nullptr);
		dayCaption->setColors(BobColor::white, BobColor::darkerGray, nullptr);
		moneyCaption->setColors(BobColor::green, BobColor::darkerGreen, nullptr);
	}
}

void StatusBar::setEnabled(bool b)
{ //=========================================================================================================================
	enabled = b;
}

void StatusBar::render()
{ //=========================================================================================================================


	if (enabled == false)
	{
		return;
	}


	render(0);

	clockCaption->render(0); //getText, lights
	dayCaption->render(0);
	moneyCaption->render(0);


	ndButton->render(0); //button graphics
	gameStoreButton->render(0);
	stuffButton->render(0);

	notificationManager->render(0); //notification string

	render(1); //status bar gloss


	clockCaption->render(1); //nothing
	dayCaption->render(1); //nothing
	moneyCaption->render(1); //divider


	ndButton->render(1); //dividers
	gameStoreButton->render(1);
	stuffButton->render(1);


	notificationManager->render(1); //nothing yet
}

void StatusBar::render(int layer)
{ //=========================================================================================================================

	if (enabled == false)
	{
		return;
	}

	BobTexture* texture = nullptr;
	if (layer == 0)
	{
		texture = backgroundTexture;
	}
	if (layer == 1)
	{
		texture = foregroundTexture;
	}

	float alpha = 1.0f;
	if (layer == 1)
	{
		alpha = glossAlpha;
	}


	GLUtils::drawTexture(texture, 0, (float)GLUtils::getViewportWidth(), -6, (float)sizeY + 6, alpha, GLUtils::FILTER_FBO_NEAREST_NO_MIPMAPPING);
}

