#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger NDMenuWheelItem::log = Logger("NDMenuWheelItem");


int NDMenuWheelItem::firstCartY = 0;
int NDMenuWheelItem::wheelItemHeight = 38;
int NDMenuWheelItem::wheelItemLabelOffsetX = 6 / 2;
int NDMenuWheelItem::wheelItemLabelOffsetY = 6 / 2;

NDMenuWheelItem::NDMenuWheelItem(Engine* g, NDGameEngine* game, const string& name, BobColor* color)
{ //=========================================================================================================================
	this->e = g;

	this->game = game;
	this->name = name;
	this->color = color;

	this->caption = new Caption(g, 0, 0, -1, name, BobFont::font_normal_16_outlined_smooth, color, nullptr, new BobColor(0, 0, 0, 0), RenderOrder::ABOVE_TOP, 1.0f, 0);
	this->caption->setAlphaImmediately(1.0f);

	y = (float)firstCartY + (NDMenuWheel::wheelItems->size() - 1) * wheelItemHeight;
	slot = NDMenuWheel::wheelItems->size() - 1;
}

float NDMenuWheelItem::top()
{ //=========================================================================================================================
	return y;
}

float NDMenuWheelItem::middleY()
{ //=========================================================================================================================
	return y + wheelItemHeight / 2.0f;
}

float NDMenuWheelItem::bottom()
{ //=========================================================================================================================
	return y + wheelItemHeight;
}

void NDMenuWheelItem::render(bool isSelected)
{ //=========================================================================================================================
	//------------------------------------------
	//draw item background graphic
	//------------------------------------------
	GLUtils::drawTexture(wheelItemBackgroundTexture, x, y, 1.0f, GLUtils::FILTER_LINEAR);


	//------------------------------------------
	//draw wheel item label
	//------------------------------------------

	float labelX = x + wheelItemLabelOffsetX;
	float labelY = y + wheelItemLabelOffsetY;

	//NDGame.drawTexture(labelTexture,labelX,labelY);

	if (caption != nullptr)
	{
		caption->screenX = x + 40 / 2;
		caption->screenY = y + 20 / 2;
		caption->render();
	}

	//------------------------------------------
	//draw shiny overlay
	//------------------------------------------


	if (isSelected)
	{
		//if(selectedWheelItem==1)NDGame.drawTextureAlpha(labelGlowTexture,labelX,labelY,1.0f-(float)(highlightColor/255.0f));

		GLUtils::drawTexture(wheelItemGlossyOverlayTexture, labelX, labelY, NDMenuWheel::highlightColor, GLUtils::FILTER_LINEAR);
	}
	else
	{
		GLUtils::drawTexture(wheelItemGlossyOverlayTexture, labelX, labelY, 1.0f, GLUtils::FILTER_LINEAR);
	}
}

