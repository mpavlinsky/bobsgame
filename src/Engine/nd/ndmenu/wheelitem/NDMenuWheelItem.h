//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class NDMenuWheelItem : public EnginePart
{
public:

	static Logger log;


	static BobTexture* wheelItemBackgroundTexture;
	static BobTexture* wheelItemGlossyOverlayTexture;

	static int firstCartY; //((getViewportHeight()/2)-(wheelItemHeight/2));

	static int wheelItemHeight; //40;//37;//48;//cart_SURFACE->h; //size of cart image
	static int wheelItemLabelOffsetX; //where the label "container" starts inside the cart png
	static int wheelItemLabelOffsetY; //13;//where the label "container" starts inside the cart png


	float x = 0;
	float y = 0;

	//public Texture labelTexture = null;
	//public Texture labelGlowTexture = null;

	int slot = 0;
	string name = "";

	NDGameEngine* game;

	BobColor* color = BobColor::black;


	Caption* caption;


	NDMenuWheelItem(Engine* g, NDGameEngine* game, const string& name, BobColor* color);


	virtual float top();

	virtual float middleY();

	virtual float bottom();

	virtual void render(bool isSelected);
};

