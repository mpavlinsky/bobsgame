//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;





#include "wheelitem/NDMenuWheelItem.h"


class NDMenuWheel : public EnginePart
{
public:

	static Logger log;


	NDMenuWheel(Engine* g);


	static ArrayList<NDMenuWheelItem*>* wheelItems;


	int selectedWheelItem = 0;
	int wheelSpinDirection = 0; //2;

	int wheelSoundQueue = 0;


	static int CLOCKWISE;
	static int COUNTERCLOCKWISE;


	BobTexture* selectedItemColorSpinTexture[15];


	float cartSlideX = 0;

	int selectionBoxFrame = 0;
	long long selectionBoxTicks = 0;


	long long highlightTicks = 0;
	static float highlightColor;
	int highlightDir = 0;


	bool selectionColorSpinEnabled = true;


	bool wheelSpinning = false;


	virtual void init();


	virtual void addGame(NDGameEngine* game, const string& name, BobColor* color);


	virtual void render();


	virtual void renderGameTitleCentered();

	virtual void renderGameTitleCenteredGlow();


	virtual void spinWheel(int dir);


	virtual void update();
};

