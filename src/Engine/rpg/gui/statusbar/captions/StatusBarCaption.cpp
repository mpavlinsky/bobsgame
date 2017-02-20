#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once



Logger StatusBarCaption::log = Logger("StatusBarCaption");


StatusBarCaption::StatusBarCaption()
{ //=========================================================================================================================
}

StatusBarCaption::StatusBarCaption(BGClientEngine* g)
{ //=========================================================================================================================
	this->e = g;
}

void StatusBarCaption::setEnabled(bool b)
{ //=========================================================================================================================
	enabled = b;
}

void StatusBarCaption::init()
{ //=========================================================================================================================
}

void StatusBarCaption::update()
{ //=========================================================================================================================
}

void StatusBarCaption::render(int layer)
{ //=========================================================================================================================


	if (enabled == false)
	{
		return;
	}

	if (layer == 0)
	{
		if (caption != nullptr)
		{
			caption->render();
		}
		if (light != nullptr)
		{
			light->renderLight();
		}
	}
}

void StatusBarCaption::updateCaption(const string& s)
{ //=========================================================================================================================

	if (caption == nullptr)
	{
		caption = new Caption(getEngine(), 0, 2, -1, s, BobFont::font_small_16_outlined_smooth, currentFGColor, currentAAColor, currentBGColor, RenderOrder::OVER_TEXT, 1.0f, 0);
	}
	else
	{
		if (s.compare(caption->text) != 0)
		{
			caption->setText(s);
		}
	}
}

void StatusBarCaption::setColors(BobColor* fg, BobColor* aa, BobColor* bg)
{ //=========================================================================================================================

	currentFGColor = fg;
	currentAAColor = aa;
	currentBGColor = bg;


	if (caption != nullptr)
	{
		caption->setTextColor(fg, aa, bg);
	}
}

void StatusBarCaption::setDefaultColor()
{ //=========================================================================================================================
	setColors(defaultFGColor, defaultAAColor, defaultBGColor);
}

