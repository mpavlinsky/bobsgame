#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger ActionManager::log = Logger("ActionManager");


int ActionManager::ACTIONCAPTIONTYPE_NONE = 0;
int ActionManager::ACTIONCAPTIONTYPE_TILE = 1;
int ActionManager::ACTIONCAPTIONTYPE_XY = 2;
int ActionManager::ACTIONCAPTIONTYPE_XYXY = 3;
int ActionManager::ACTIONCAPTIONTYPE_NPC = 4;
int ActionManager::ACTIONCAPTIONTYPE_AREA = 5;

ActionManager::Coords::Coords(ActionManager* outerInstance, int x, int y) : outerInstance(outerInstance)
{
	this->x = x;
	this->y = y;
}

ActionManager::ActionManager(Engine* g)
{ //=========================================================================================================================


	this->e = g;


	//make getText icon texture

	//send into new sprite

	//DONE: new Entity(texture filename) should add itself to the entity manager automatically.. G.entityManager.add(this)

	//new Caption() should do this too


	if (actionIconScreenSprite == nullptr)
	{
		actionIconScreenSprite = new ScreenSprite(g, "button", "actionIcon"); //HARDWARE_create_sprite(TEXT_button_icon_GFX,0,1,1.0f,actionx-8,actiony+1,255);
		actionIconScreenSprite->draw = false;

		actionIconScreenSprite->setAnimateLoopThroughAllFrames();
		actionIconScreenSprite->setRandomUpToTicksBetweenAnimationLoop(false);
		actionIconScreenSprite->setTicksBetweenFrames(60);
		actionIconScreenSprite->setTicksBetweenAnimationLoop(0);
	}
}



void ActionManager::deleteIfNoAction()
{ //=========================================================================================================================

	//if(PLAYER_check_action_dont_run(facing_direction)==0)
	if (actionCaption != nullptr)
	{
		if (actionCaption->actionCaptionType == ACTIONCAPTIONTYPE_TILE) //only delete action tile captions
		{
			actionCaption->setToFadeOutAndBeDeleted();
			actionCaption = nullptr;
			actionIconScreenSprite->draw = false;
		}
	}
}

bool ActionManager::xy(int x, int y, const string& label)
{ //=========================================================================================================================

	return checkAll(x, y, x + 1, y + 1, label, ACTIONCAPTIONTYPE_XY, nullptr, nullptr);
}

bool ActionManager::area(Area* a, const string& label)
{ //=========================================================================================================================

	return checkAll(0, 0, 0, 0, label, ACTIONCAPTIONTYPE_AREA, nullptr, a);
}

bool ActionManager::xyxy(int x, int y, int x2, int y2, const string& label)
{ //=========================================================================================================================

	return checkAll(x, y, x2, y2, label, ACTIONCAPTIONTYPE_XYXY, nullptr, nullptr);
}

bool ActionManager::entity(Entity* e, const string& label)
{ //=========================================================================================================================

	return checkAll(0, 0, 0, 0, label, ACTIONCAPTIONTYPE_NPC, e, nullptr);
}

bool ActionManager::checkAll(int x, int y, int x2, int y2, const string& label, int type, Entity* e, Area* a)
{ //=========================================================================================================================


	if (getPlayer() == nullptr)
	{
		return false;
	}

	bool inRange = false;


	if (type == ACTIONCAPTIONTYPE_AREA)
	{
		x = (int)(a->getLeft());
		y = (int)(a->getTop());
		x2 = (int)(a->getRight());
		y2 = (int)(a->getBottom());

		if (getPlayer()->isAreaBoundaryTouchingMyHitBox(a) == true && getTextManager()->textEngineState == 0 && getPlayer()->GLOBAL_main_sprite_actions_off == 0)
		{
			inRange = true;
		}
	}
	else
	{
		if (type == ACTIONCAPTIONTYPE_NPC)
		{
			x = (int)(a->getLeft());
			y = (int)(a->getTop());
			x2 = (int)(a->getRight());
			y2 = (int)(a->getBottom());

			if (getPlayer()->isEntityHitBoxTouchingMyHitBox(e) == true && getTextManager()->textEngineState == 0 && getPlayer()->GLOBAL_main_sprite_actions_off == 0)
			{
				inRange = true;
			}
		}
		else
		{
			if (
				getPlayer()->isHitBoxTouchingXYXYInDirectionByAmount((float)x, (float)y, (float)x2, (float)y2, getPlayer()->animationDirection, 7) == true &&
				getTextManager()->textEngineState == 0 &&
				getPlayer()->GLOBAL_main_sprite_actions_off == 0
			)
			{
				inRange = true;
			}
		}
	}


	actionsThisFrame->add(new Coords(this, x + (x2 - x), y + (y2 - y)));


	if (inRange)
	{
		if (label != "" && label == "" == false)
		{
			if (actionCaption != nullptr)
			{
				replaceCaptionText(label);

				actionCaption->actionCaptionType = type;
				actionCaption->actionRangeX = x;
				actionCaption->actionRangeY = y;
				actionCaption->entity = e;
				actionCaption->area = a;
			}
			else
			{ //doesnt exist,make new one over sprites head
				makeCaption(label);

				actionCaption->actionCaptionType = type;
				actionCaption->actionRangeX = x;
				actionCaption->actionRangeY = y;
				actionCaption->entity = e;
				actionCaption->area = a;
			}


			if (actionCaption != nullptr && getControlsManager()->bgClient_ACTION_Pressed() == true && label.compare(actionCaption->text) == 0 && ((actionCaption->actionCaptionType == ACTIONCAPTIONTYPE_XYXY && actionCaption->actionRangeX == x && actionCaption->actionRangeY == y) || (actionCaption->actionCaptionType == ACTIONCAPTIONTYPE_XY && actionCaption->actionRangeX == x && actionCaption->actionRangeY == y) || (actionCaption->actionCaptionType == ACTIONCAPTIONTYPE_NPC && actionCaption->entity == e) || (actionCaption->actionCaptionType == ACTIONCAPTIONTYPE_AREA && actionCaption->area == a)))
			{
				deleteCaptionWithBlipSound();
				return true;
			}
		}
		else
		{
			if (getControlsManager()->bgClient_ACTION_Pressed() == true)
			{
				return true;
			}
		}
	}
	else //else delete action icon and getCaption
	{
		if (label != "" && label == "" == false)
		{
			if (actionCaption != nullptr && label.compare(actionCaption->text) == 0 && ((actionCaption->actionCaptionType == ACTIONCAPTIONTYPE_XYXY && actionCaption->actionRangeX == x && actionCaption->actionRangeY == y) || (actionCaption->actionCaptionType == ACTIONCAPTIONTYPE_XY && actionCaption->actionRangeX == x && actionCaption->actionRangeY == y) || (actionCaption->actionCaptionType == ACTIONCAPTIONTYPE_NPC && actionCaption->entity == e) || (actionCaption->actionCaptionType == ACTIONCAPTIONTYPE_AREA && actionCaption->area == a)))
			{
				deleteCaptionNoSound();
			}
		}
	}

	return false;
}

void ActionManager::deleteCaptionNoSound()
{ //=========================================================================================================================

	if (actionCaption != nullptr)
	{
		actionCaption->setToFadeOutAndBeDeleted();
		actionCaption = nullptr;
		actionIconScreenSprite->draw = false;
	}
}

void ActionManager::deleteCaptionWithBlipSound()
{ //=========================================================================================================================
	getAudioManager()->playSound("blip", 0.25f, 1.6f, 1);

	deleteCaptionNoSound();
}

void ActionManager::makeCaption(const string& label)
{ //=========================================================================================================================

	/*
	int px = (int)(ACTION_caption.caption_width*2*ACTION_caption.getScale);
	int actionx=((player().screen_x+player().size_x/2)-((px+8)/2))+8;//centered over player sprite
	if(actionx+px>Display.getWidth())actionx=Display.getWidth()-px;//dont go past right
	if(actionx-8<0)actionx=0+8;//dont go past left
	int actiony=player().screen_y-16;
	*/


	actionCaption = getCaptionManager()->newManagedCaption(Caption::CENTERED_OVER_ENTITY, 0, -1, label, BobFont::font_small_16_outlined_smooth, BobColor::white, nullptr, BobColor::clear, RenderOrder::ABOVE_TOP, 1.0f, 0);


	actionIconScreenSprite->screenXPixelsHQ = actionCaption->screenX - (actionIconScreenSprite->getWidth() + 4); //move action icon sprite
	actionIconScreenSprite->screenYPixelsHQ = actionCaption->screenY - 8;

	actionIconScreenSprite->draw = true;
}

void ActionManager::replaceCaptionText(const string& label)
{ //=========================================================================================================================

	if (label.compare(actionCaption->text) != 0) //        if action icon exists,check new label against old label
	{
		actionCaption->setText(label);
		//move action icon sprite
	}
	else
	{
		actionIconScreenSprite->screenXPixelsHQ = actionCaption->screenX - (actionIconScreenSprite->getWidth() + 4); //move action icon sprite
		actionIconScreenSprite->screenYPixelsHQ = actionCaption->screenY - 8;
	}
}

void ActionManager::update()
{ //=========================================================================================================================
	actionsThisFrame->clear();
}

