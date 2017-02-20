#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger StatusBarButton::log = Logger("StatusBarButton");


StatusBarButton::StatusBarButton()
{ //=========================================================================================================================
}

StatusBarButton::StatusBarButton(BGClientEngine* g)
{ //=========================================================================================================================
	this->e = g;
}

void StatusBarButton::init()
{ //=========================================================================================================================
}

void StatusBarButton::setOffsets()
{ //=========================================================================================================================
}

void StatusBarButton::clicked()
{ //=========================================================================================================================
}

bool StatusBarButton::isAssociatedMenuActive()
{ //=========================================================================================================================
	return false;
}

void StatusBarButton::update()
{ //=========================================================================================================================

	if (enabled == false)
	{
		return;
	}

	setOffsets();


	if (getControlsManager()->getMouseX() > clickX0 && getControlsManager()->getMouseX() < clickX1 && getControlsManager()->getMouseY() > (GLUtils::getViewportHeight() - StatusBar::sizeY))
	{
		glow = true;
		glowAlpha = 1.0f;

//		if (getControlsManager()->MOUSE_0_HELD == true)
//		{
//			pressedOffsetY = 2;
//		}
//		else
//		{
//			pressedOffsetY = 0;
//		}
//
//		if (getControlsManager()->MOUSE_0_PRESSED == true)
//		{
//			clicked();
//		}
	}
	else if (isAssociatedMenuActive() == true)
	{
		glow = true;
	}
	else
	{
		glow = false;
	}


	if (pulse == true)
	{
		glow = true;

		pulseTicks += (int)getEngine()->engineTicksPassed();

		if (pulseTicks > lastPulseTicks + 1000)
		{
			lastPulseTicks = pulseTicks;

			pulseInOut = !pulseInOut;
		}

		if (pulseInOut == true)
		{
			glowAlpha += ((float)(getEngine()->engineTicksPassed()) / 1000.0f);
			if (glowAlpha > 1.0f)
			{
				glowAlpha = 1.0f;
			}
		}
		else
		{
			glowAlpha -= ((float)(getEngine()->engineTicksPassed()) / 1000.0f);
			if (glowAlpha < 0.0f)
			{
				glowAlpha = 0.0f;
			}
		}
	}
	else
	{
		glowAlpha = 1.0f;
	}
}

void StatusBarButton::setEnabled(bool b)
{ //=========================================================================================================================
	enabled = b;
}

void StatusBarButton::render(int layer)
{ //=========================================================================================================================


	if (enabled == false)
	{
		return;
	}

	if (texture == nullptr)
	{
		return;
	}


	if (layer == 0)
	{
		if (glow)
		{
			GLUtils::drawTexture(StatusBar::glowTexture, (float)glowX0, (float)glowX1, (float)glowY0, (float)glowY1, glowAlpha, GLUtils::FILTER_LINEAR);
		}


		GLUtils::drawTexture(texture, (float)offsetX0, (float)offsetX1, (float)offsetY0 + pressedOffsetY, (float)(StatusBar::sizeY - offsetY1) + pressedOffsetY, 1.0f, GLUtils::FILTER_LINEAR);


		if (glow)
		{
			GLUtils::drawTexture(StatusBar::glowTexture, (float)glowX0, (float)glowX1, (float)glowY0, (float)glowY1, 0.2f, GLUtils::FILTER_LINEAR);
		}
	}

	if (layer == 1)
	{
		GLUtils::drawTexture(StatusBar::dividerTexture, (float)dividerX, (float)dividerX + 3, 0, (float)StatusBar::sizeY - 1, 1.0f, GLUtils::FILTER_LINEAR);
	}
}

