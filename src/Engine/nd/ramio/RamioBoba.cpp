#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger RamioBoba::log = Logger("RamioBoba");


RamioBoba::RamioBoba(Engine* g)
{ //=========================================================================================================================
	this->e = g;
}

bool RamioBoba::checkHitLayerBlocksAndOtherBobas(int dir)
{
	return false;
}

void RamioBoba::update()
{ //=========================================================================================================================


	if (dead == false)
	{
		//check down
		if (checkHitLayerBlocksAndOtherBobas(DOWN) == false)
		{
			incY();
		}


		if (movementDirection == LEFT)
		{
			//check getHit
			if (checkHitLayerBlocksAndOtherBobas(LEFT) == false)
			{
				//move left
				decX();
			}
			else
			{
				movementDirection = RIGHT;
			}
		}

		if (movementDirection == RIGHT)
		{
			//heck getHit
			if (checkHitLayerBlocksAndOtherBobas(RIGHT) == false)
			{
				//move right
				incX();
			}
			else
			{
				movementDirection = LEFT;
			}
		}
	}


	if (dead == true)
	{
		//set animation to "dead"
		if (getCurrentAnimationName() == "dead" == false)
		{
			setCurrentAnimationByName("dead");
			setAnimateOnceThroughCurrentAnimation();


			//TODO: make setCurrentAnimation
		}
	}
}

bool RamioBoba::checkStomp(RamioGuy* guy)
{
	// int r=rand()%5;
	// if(r==0)CAPTION_make_caption(&yuu_ramio_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Squish!",FONT_NORMAL_ID,WHITE,BLACK,1,1);
	// if(r==1)CAPTION_make_caption(&yuu_ramio_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Take that!",FONT_NORMAL_ID,WHITE,BLACK,1,1);
	// if(r==2)CAPTION_make_caption(&yuu_ramio_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Poor guy.",FONT_NORMAL_ID,WHITE,BLACK,1,1);

	dead = true;
	// play sound
	getAudioManager()->playSound("ramiosplat", 64, 44100, 0);
	// bounce
	RamioGuy::jumping = true;


	return false;
}

bool RamioBoba::checkRunningInto(RamioGuy* guy)
{
	// TODO
	return false;
}

