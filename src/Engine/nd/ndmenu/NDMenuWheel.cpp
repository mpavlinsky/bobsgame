
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger NDMenuWheel::log = Logger("NDMenuWheel");


BobTexture* NDMenuWheelItem::wheelItemBackgroundTexture;
BobTexture* NDMenuWheelItem::wheelItemGlossyOverlayTexture;

NDMenuWheel::NDMenuWheel(Engine* g)
{ //=========================================================================================================================
	this->e = g;
}

ArrayList<NDMenuWheelItem*>* NDMenuWheel::wheelItems = new ArrayList<NDMenuWheelItem*>();
int NDMenuWheel::CLOCKWISE = 0;
int NDMenuWheel::COUNTERCLOCKWISE = 1;
float NDMenuWheel::highlightColor = 0;


void NDMenuWheel::init()
{ //=========================================================================================================================


	//------------------------------------------
	//initialize wheel item labels / highlight values
	//------------------------------------------


	selectedItemColorSpinTexture[0] = GLUtils::getTextureFromPNG("data/nD/menu/wheelItem/selectedItemColorSpin_00.png");
	selectedItemColorSpinTexture[1] = GLUtils::getTextureFromPNG("data/nD/menu/wheelItem/selectedItemColorSpin_01.png");
	selectedItemColorSpinTexture[2] = GLUtils::getTextureFromPNG("data/nD/menu/wheelItem/selectedItemColorSpin_02.png");
	selectedItemColorSpinTexture[3] = GLUtils::getTextureFromPNG("data/nD/menu/wheelItem/selectedItemColorSpin_03.png");
	selectedItemColorSpinTexture[4] = GLUtils::getTextureFromPNG("data/nD/menu/wheelItem/selectedItemColorSpin_04.png");
	selectedItemColorSpinTexture[5] = GLUtils::getTextureFromPNG("data/nD/menu/wheelItem/selectedItemColorSpin_05.png");
	selectedItemColorSpinTexture[6] = GLUtils::getTextureFromPNG("data/nD/menu/wheelItem/selectedItemColorSpin_06.png");
	selectedItemColorSpinTexture[7] = GLUtils::getTextureFromPNG("data/nD/menu/wheelItem/selectedItemColorSpin_07.png");
	selectedItemColorSpinTexture[8] = GLUtils::getTextureFromPNG("data/nD/menu/wheelItem/selectedItemColorSpin_08.png");
	selectedItemColorSpinTexture[9] = GLUtils::getTextureFromPNG("data/nD/menu/wheelItem/selectedItemColorSpin_09.png");
	selectedItemColorSpinTexture[10] = GLUtils::getTextureFromPNG("data/nD/menu/wheelItem/selectedItemColorSpin_10.png");
	selectedItemColorSpinTexture[11] = GLUtils::getTextureFromPNG("data/nD/menu/wheelItem/selectedItemColorSpin_11.png");
	selectedItemColorSpinTexture[12] = GLUtils::getTextureFromPNG("data/nD/menu/wheelItem/selectedItemColorSpin_12.png");
	selectedItemColorSpinTexture[13] = GLUtils::getTextureFromPNG("data/nD/menu/wheelItem/selectedItemColorSpin_13.png");
	selectedItemColorSpinTexture[14] = GLUtils::getTextureFromPNG("data/nD/menu/wheelItem/selectedItemColorSpin_14.png");


	//------------------------------------------
	//load wheel item textures
	//------------------------------------------

	NDMenuWheelItem::wheelItemBackgroundTexture = GLUtils::getTextureFromPNG("data/nD/menu/wheelItem/itemBackground.png");
	NDMenuWheelItem::wheelItemGlossyOverlayTexture = GLUtils::getTextureFromPNG("data/nD/menu/wheelItem/glossyOverlay.png");


	wheelItems->add(new NDMenuWheelItem(getEngine(), nullptr, "GameStore", BobColor::magenta));
	wheelItems->add(new NDMenuWheelItem(getEngine(), nullptr, "Settings", BobColor::green));
}

void NDMenuWheel::addGame(NDGameEngine* game, const string& name, BobColor* color)
{ //=========================================================================================================================

	wheelItems->add(new NDMenuWheelItem(getEngine(), game, name, color));


	//------------------------------------------
	//set up wheel items
	//------------------------------------------

	//			wheelItems.get(0).labelTexture = GLUtils.loadTexture("res/nD/menu/items/gamestore/label_gamestore.png");
	//			wheelItems.get(0).labelGlowTexture = GLUtils.loadTexture("res/nD/menu/items/gamestore/label_gamestore.png");
	//
	//			wheelItems.get(1).labelTexture = GLUtils.loadTexture("res/nD/menu/items/bobsgame/label_bobsgame.png");
	//			wheelItems.get(1).labelGlowTexture = GLUtils.loadTexture("res/nD/menu/items/bobsgame/label_bobsgame_glow.png");
	//
	//			wheelItems.get(2).labelTexture = GLUtils.loadTexture("res/nD/menu/items/settings/label_settings.png");
	//			wheelItems.get(2).labelGlowTexture = GLUtils.loadTexture("res/nD/menu/items/settings/label_settings.png");
	//
	//			wheelItems.get(0).name="Game Store";
	//			wheelItems.get(1).name="\"bob's game\"";
	//			wheelItems.get(2).name="Settings";
	//
	//			wheelItems.get(0).color = Color.red;
	//			wheelItems.get(1).color = Color.green;
	//			wheelItems.get(2).color = Color.yellow;
	//


	//------------------------------------------
	//initialize wheel movement values
	//------------------------------------------

	//int max_wheel_items_onscreen = (getViewportHeight()/cart_label_height)+2;

	//since the middle label will be centered on screen, the topmost label y position will be offset, not zero
	//int first_cart_y = (((getViewportHeight()/2)-(cart_label_height/2))%cart_label_height);

	///populate the wheel starting from the middle, so the first item is always selected.
}

void NDMenuWheel::render()
{ //=========================================================================================================================

	//------------------------------------------
	//draw each wheel item
	//------------------------------------------

	for (int c = 0; c < wheelItems->size(); c++)
	{
		wheelItems->get(c)->render(c == selectedWheelItem);
	}


	NDMenuWheelItem* selected = wheelItems->get(selectedWheelItem);
	//------------------------------------------
	//draw selection box
	//------------------------------------------
	if (selectionColorSpinEnabled == true)
	{
		GLUtils::drawTexture(selectedItemColorSpinTexture[selectionBoxFrame], selected->x, selected->y, 1.0f, GLUtils::FILTER_LINEAR);
	}
}

void NDMenuWheel::renderGameTitleCentered()
{ //=========================================================================================================================
	//NDMenuWheelItem* selected = wheelItems->get(selectedWheelItem);
	//draw game title
	//NDGame.drawTexture(selected.labelTexture,ND.getViewportWidth()/2-selected.labelTexture.getImageWidth()/2,ND.getViewportHeight()/2-selected.labelTexture.getImageHeight()/2);
}

void NDMenuWheel::renderGameTitleCenteredGlow()
{ //=========================================================================================================================
	//NDMenuWheelItem* selected = wheelItems->get(selectedWheelItem);
	//draw game title glow
	//NDGame.drawTextureAlpha(selected.labelGlowTexture,ND.getViewportWidth()/2-selected.labelTexture.getImageWidth()/2,ND.getViewportHeight()/2-selected.labelTexture.getImageHeight()/2,NDMenu.actionFadeCounter/255.0f);
}

void NDMenuWheel::spinWheel(int dir)
{ //=========================================================================================================================

	if (dir == CLOCKWISE)
	{
		//wheelSpinDirection=wheelClockwise;
		selectedWheelItem++;

		if (selectedWheelItem >= wheelItems->size())
		{
			selectedWheelItem = 0;
		}

		wheelSoundQueue++;
	}
	else
	{
		if (dir == COUNTERCLOCKWISE)
		{
			//wheelSpinDirection=wheelCounterClockwise;
			selectedWheelItem--;

			if (selectedWheelItem < 0)
			{
				selectedWheelItem = wheelItems->size() - 1;
			}

			wheelSoundQueue++;
		}
	}
}

void NDMenuWheel::update()
{ //=========================================================================================================================
	//------------------------------------------
	//do wheel sound
	//------------------------------------------

	if (wheelSoundQueue > 0)
	{
		getAudioManager()->playSound("nDMenuWheelSound", 1.0f, 1.0f, wheelSoundQueue - 1);
		wheelSoundQueue = 0;
	}
	if (NDMenu::actionButtonPressed == true)
	{
		NDMenu::actionButtonPressed = false;

		{
			//if(selectedWheelItem==1)
			getAudioManager()->playSound("nDMenuActionPressed", 1.0f, 1.0f, 1);
			NDMenu::actionFadeCountSwitch = 1;
		}
	}


	NDMenuWheelItem* selected = wheelItems->get(selectedWheelItem);


	float screenMiddleY = (float)(GLUtils::getViewportHeight() / 2);
	float wheelMiddleY = selected->middleY();

	//------------------------------------------
	//if the selected wheel item isnt centered on the wheel
	//------------------------------------------
	if (wheelMiddleY != screenMiddleY)
	{
		wheelSpinning = true;

		float distance = 0;

		if (wheelMiddleY <= screenMiddleY)
		{
			distance = screenMiddleY - wheelMiddleY;
		}
		else if (wheelMiddleY > screenMiddleY)
		{
			distance = wheelMiddleY - screenMiddleY;
		}


		float amt = (float)(pow(getEngine()->engineTicksPassed(), distance / 100.0f)); //*(1.0f/10.0f)

		if (wheelMiddleY < screenMiddleY && wheelMiddleY + amt > screenMiddleY)
		{
			amt = screenMiddleY - wheelMiddleY;
		}
		if (wheelMiddleY > screenMiddleY && wheelMiddleY - amt < screenMiddleY)
		{
			amt = wheelMiddleY - screenMiddleY;
		}

		//------------------------------------------
		//move all the items up or down based on the direction the wheel is spinning
		//(this is so you can immediately change direction while the wheel is turning)
		//------------------------------------------

		if (wheelMiddleY > screenMiddleY) //wheelSpinDirection==wheelClockwise)
		{
			wheelSpinDirection = NDMenuWheel::CLOCKWISE;
			for (int c = 0; c < wheelItems->size(); c++)
			{
				wheelItems->get(c)->y -= amt;
			}

			//SWI.y-=wheelTicksPassed*getDistanceToCenter()/300.0f;
			//if(SWI.getMiddleY()<screenMiddleY)SWI.y=screenMiddleY-(wheelItemHeight/2.0f);
		}
		if (wheelMiddleY < screenMiddleY) //wheelSpinDirection==wheelCounterClockwise)
		{
			wheelSpinDirection = NDMenuWheel::COUNTERCLOCKWISE;
			for (int c = 0; c < wheelItems->size(); c++)
			{
				wheelItems->get(c)->y += amt;
			}
			//SWI.y+=wheelTicksPassed*getDistanceToCenter()/300.0f;
			//if(SWI.getMiddleY()>screenMiddleY)SWI.y=screenMiddleY-(wheelItemHeight/2.0f);
		}
		//------------------------------------------


		//if the wheel is going clockwise
		//find the bottom-most wheel item
		//if it is less than getViewportHeight()-cartsizey
		//take the top one, set to bottom most + cart size y
		//or for neat slide effect, move it up until it is above 0-cartsizey
		//then set it to getViewportHeight() and catch up to the bottom-most

		//if the wheel is going counterclockwise
		//find the topmost wheel item
		//if it is more than 0+cartsizey
		//take the bottom one, move it down until it is below getViewportHeight()
		//then set it to 0-cartsize and catch up to the topmost

		//------------------------------------------
		//find topmost and bottommost
		//------------------------------------------


		NDMenuWheelItem* bottomItem = wheelItems->get(0);
		NDMenuWheelItem* topItem = bottomItem;

		for (int c = 0; c < wheelItems->size(); c++)
		{
			//if(c==selectedWheelItem)continue;

			if (wheelItems->get(c)->y > bottomItem->y)
			{
				bottomItem = wheelItems->get(c);
			}
			if (wheelItems->get(c)->y < topItem->y)
			{
				topItem = wheelItems->get(c);
			}
		}
		//------------------------------------------

		//if an item wraps off the screen, wrap it on the other side
		if (wheelSpinDirection == NDMenuWheel::CLOCKWISE)
		{
			if (topItem->bottom() < 0)
			{
				//if there are more items than the screen can fit, append to the bottommost item, else just append to the bottom of the screen
				//if(bottomItem.bottom()>=getViewportHeight())
				{
					topItem->y = bottomItem->bottom();
				}
				{
					//else
					//topItem.y=getViewportHeight()-(1-topItem.bottom());
				}
			}
		}

		if (wheelSpinDirection == NDMenuWheel::COUNTERCLOCKWISE)
		{
			if (bottomItem->top() >= GLUtils::getViewportHeight())
			{
				{
					//if(topItem.top()<0)
					bottomItem->y = topItem->top() - (NDMenuWheelItem::wheelItemHeight);
				}
				{
					//else
					//bottomItem.y=(0-wheelItemHeight)+(bottomItem.top()-(getViewportHeight()-1));
				}
			}
		}
	}
	else
	{
		wheelSpinning = false;
	}


	float overlayFadeSpeedTicksMultiplier = (2.0f / 1000.0f);
	float cartSlideXSpeedTicksMultiplier = (2.0f / 100.0f);


	//------------------------------------------
	//set the alpha value to fade the selected item in and out
	//------------------------------------------

	if (highlightDir == 1)
	{
		highlightColor -= getEngine()->engineTicksPassed() * overlayFadeSpeedTicksMultiplier;
		if (highlightColor <= 0)
		{
			highlightColor = 0;
			highlightDir = 0;
		}
	}
	else
	{
		if (highlightDir == 0)
		{
			highlightColor += getEngine()->engineTicksPassed() * overlayFadeSpeedTicksMultiplier;
			if (highlightColor >= 1.0f)
			{
				highlightColor = 1.0f;
				highlightDir = 1;
			}
		}
	}


	//------------------------------------------
	//slide out cart if we aren't pressing a direction
	//------------------------------------------
	if (NDMenu::directionButtonPressed == true)
	{
		cartSlideX = 0;
	}
	else
	{
		if (cartSlideX < 10)
		{
			cartSlideX += getEngine()->engineTicksPassed() * cartSlideXSpeedTicksMultiplier;
		}
		if (cartSlideX > 10)
		{
			cartSlideX = 10;
		}
	}


	for (int c = 0; c < wheelItems->size(); c++)
	{
		//------------------------------------------
		//set position
		//------------------------------------------

		//tempWheelItemXY.y = wheelItem->get(c).y;//(y%cart_size_y)+((c-1)*cart_size_y);
		wheelItems->get(c)->x = (float)((GLUtils::getViewportWidth() / 2.0f) + 25.0f - (40.0f * (sin((float)(((wheelItems->get(c)->y + 2.0f)) / 66.0f)))));
	}

	//------------------------------------------
	//slide out selected item
	//------------------------------------------
	wheelItems->get(selectedWheelItem)->x -= cartSlideX;


	if (selectionColorSpinEnabled == true)
	{
		long long ticks = (int)getEngine()->engineTicksPassed();
		selectionBoxTicks += ticks;

		if (selectionBoxTicks > 20)
		{
			selectionBoxTicks = 0;

			selectionBoxFrame++;
			if (selectionBoxFrame > 14)
			{
				selectionBoxFrame = 0;
			}
		}
	}
}

