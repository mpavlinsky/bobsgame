#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger Ramio::log = Logger("Ramio");


Ramio::Ramio(ND* nD)
{ // =========================================================================================================================


	this->nD = nD;

}

int Ramio::timer = 0;
int Ramio::initialTimer = 0;
int Ramio::ticksToAddForMoneyBlock = 0;

void Ramio::updateScore()
{ // =========================================================================================================================

	//
	//
	// char char_score[15];
	// sprintf(char_score,"%d",RAMIO_score);
	// int score_length=strlen(char_score);
	//
	//
	// int x=0;
	//
	// //if(RAMIO_score==0)
	// for(x=0;x<3;x++)
	// {
	// //RAMIO_set_tile(1,2,8+x-3,2,29*32);
	// //RAMIO_set_tile(1,2,8+x-3,3,29*32);
	// }
	//
	// for(x=0;x<score_length;x++)
	// {
	// //RAMIO_set_tile(1,2,8+x-score_length,2,(char_score[x]-48)+(30*32));
	// //RAMIO_set_tile(1,2,8+x-score_length,3,(char_score[x]-48)+(31*32));
	// }
	//
	// char char_hiscore[15];
	// sprintf(char_hiscore,"%d",RAMIO_high_score);
	// int hiscore_length=strlen(char_hiscore);
	//
	// //if(RAMIO_high_score==0)
	// for(x=0;x<3;x++)
	// {
	// //RAMIO_set_tile(1,2,29+x-3,2,29*32);
	// //RAMIO_set_tile(1,2,29+x-3,3,29*32);
	// }
	//
	// for(x=0;x<hiscore_length;x++)
	// {
	// //RAMIO_set_tile(1,2,29+x-hiscore_length,2,(char_hiscore[x]-48)+(30*32));
	// //RAMIO_set_tile(1,2,29+x-hiscore_length,3,(char_hiscore[x]-48)+(31*32));
	// }
}

bool Ramio::checkHit(int dir)
{ //=========================================================================================================================
	return false;
}

void Ramio::initGame()
{ //=========================================================================================================================


	if (easymode == true)
	{
		timer = 0;
		initialTimer = 1000;
		ticksToAddForMoneyBlock = 200;
	}
	else
	{
		timer = 0;
		initialTimer = 800;
		ticksToAddForMoneyBlock = 140;
	}


	getCaptionManager()->newManagedCaption(Caption::CENTERED_X, 20, 3000, "Alright! It works!", BobFont::font_normal_8, BobColor::white, nullptr, BobColor::clear, RenderOrder::ABOVE_TOP, 0.5f, -1);


	getMapManager()->changeMap("MINIGAMERAMIOramiolevel1", 16, 0);

	guy = new RamioGuy(this);
	getCurrentMap()->activeEntityList.add(guy);

	getCurrentMap()->defaultDisableFloorOffset = true;

	guy->init();

	guy->setX(5 * 8 * 2);
	guy->setY(14 * 8 * 2);


	getCameraman()->setTarget(guy);
	getCameraman()->setXYToTarget();
	getCameraman()->ZOOMto = 0.5f;

	timer = initialTimer;

	initialized = true;
}

void Ramio::doWinSequence()
{ // =========================================================================================================================

	if (winSequenceStep == 0)
	{
		getCaptionManager()->newManagedCaption(Caption::CENTERED_X, 20, 3000, "Yeah! I did it!", BobFont::font_normal_8, BobColor::white, nullptr, BobColor::clear, RenderOrder::ABOVE_TOP, 0.5f, -1);


		getAudioManager()->stopAllMusic();
		getAudioManager()->playSound("ramiowon", 0.25f, 1.0f, 1);
		winSequenceStep = 1;
		ticks = 0;
	}
	else if (winSequenceStep == 1)
	{
		if (ticks > 150)
		{
			winSequenceStep = 2;
		}
	}

	else if (winSequenceStep == 2)
	{
		winSequenceStep = 3;

		// delete sprites

		// CAPTION_delete_caption(RAMIO_timercaption);

		// TODO:glitch, end game

		initialized = false;
		creditScreenInit = true;

		playing = false;
	}
}

void Ramio::doDeathSequence()
{ //=========================================================================================================================


	if (dieSequenceStep == 0)
	{
		int r = Math::randLessThan(5);
		if (r == 0)
		{
			getCaptionManager()->newManagedCaption(Caption::CENTERED_X, 20, 3000, "Let's try this again.", BobFont::font_normal_8, BobColor::white, nullptr, BobColor::clear, RenderOrder::ABOVE_TOP, 0.5f, -1);
		}
		if (r == 1)
		{
			getCaptionManager()->newManagedCaption(Caption::CENTERED_X, 20, 3000, "I was so close!", BobFont::font_normal_8, BobColor::white, nullptr, BobColor::clear, RenderOrder::ABOVE_TOP, 0.5f, -1);
		}
		if (r == 2)
		{
			getCaptionManager()->newManagedCaption(Caption::CENTERED_X, 20, 3000, "Grrr. That was stupid.", BobFont::font_normal_8, BobColor::white, nullptr, BobColor::clear, RenderOrder::ABOVE_TOP, 0.5f, -1);
		}
		if (r == 3)
		{
			getCaptionManager()->newManagedCaption(Caption::CENTERED_X, 20, 3000, "One more try.", BobFont::font_normal_8, BobColor::white, nullptr, BobColor::clear, RenderOrder::ABOVE_TOP, 0.5f, -1);
		}
		if (r == 4)
		{
			getCaptionManager()->newManagedCaption(Caption::CENTERED_X, 20, 3000, "Nooooooooo!", BobFont::font_normal_8, BobColor::white, nullptr, BobColor::clear, RenderOrder::ABOVE_TOP, 0.5f, -1);
		}

		getAudioManager()->stopAllMusic();
		getAudioManager()->playSound("ramiodeath", 0.25f, 1.0f, 1);

		guy->setCurrentAnimationByName("death");
		guy->setAnimateOnceThroughCurrentAnimation();

		dieSequenceStep = 1;
	}
	else if (dieSequenceStep == 1)
	{
		if (ticks > 30)
		{
			dieSequenceStep = 2;
			ticks = 0;
		}
	}
	else if (dieSequenceStep == 2)
	{
		if (ticks > 30)
		{
			dieSequenceStep = 3;
			ticks = 0;
		}
	}
	else if (dieSequenceStep == 3)
	{
		if (ticks > 60)
		{
			dieSequenceStep = 4;
		}
	}
	else if (dieSequenceStep == 4)
	{
		getAudioManager()->playMusic("ramio", 0.5f, 1.0f, true);
		dieSequenceStep = 0;
		// do death animation
		// getCaption probably

		guy->setX(5 * 8 * 2);
		guy->setY(14 * 8 * 2);

		// start over
		dead = false;
		timer = initialTimer;
	}
}

void Ramio::update()
{ // =========================================================================================================================

	//if(guy!=null)Cameraman().setX((float)Math.floor(guy.x()+guy.width()/2));
	//if(guy!=null)Cameraman().setX((float)guy.x()+guy.width()/2);
	NDGameEngine::update();

	if (guy != nullptr)
	{
		getCameraman()->setX(guy->getX());

		//Cameraman().setX((float)Math.floor(((int)(guy.x())/2))*2);//clamp to whole pixels

		//guy.setX((float)Math.floor(((int)(guy.x())/4))*4);
	}

	ticks += engineTicksPassed();

	if (credits == false)
	{
		if (initialized == false)
		{
			initGame();
		}

		ramioText->text = string("GuyX: ") + to_string(guy->getX()) + string(" GuyY: ") + to_string(guy->getY()) + string(" CamX: ") + to_string(getCameraman()->getX()) + string(" CamY: ") + to_string(getCameraman()->getY());

		updateScore();


		//			timer--;
		//			if(timer<=0)
		//			{
		//				dead=true;
		//			}


		// timer
		string timerString = "$";
		timerString += string("") + to_string(((timer / 1000) % 10));
		timerString += string("") + to_string(((timer / 100) % 10));
		timerString += string("") + to_string(((timer / 10) % 10));
		timerString += string("") + to_string((timer % 10));

		if (RAMIO_timercaption == nullptr)
		{
			RAMIO_timercaption = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, 2, -1, timerString, BobFont::font_normal_16_shadow1, BobColor::green, nullptr, BobColor::clear, RenderOrder::ABOVE_TOP, 0.5f);
		}
		else
		{
			RAMIO_timercaption->setText(timerString);
		}

		if (won == true)
		{
			doWinSequence();
		}
		else if (dead == true)
		{
			doDeathSequence();
		}
		else
		{
			//guy.update();
			//Cameraman().update();

			for (int i = 0; i < bobas->size(); i++)
			{
				bobas->get(i)->update();
			}
			for (int i = 0; i < moneyBlocks->size(); i++)
			{
				moneyBlocks->get(i)->update();
			}
			for (int i = 0; i < brickBlocks->size(); i++)
			{
				brickBlocks->get(i)->update();
			}


			// check fell in pit
			//				if(guy.bottom()>=22*8) dead=true;


			// end of level
			//				if((guy.x())/8>=468)
			//				{
			//					won=true;
			//
			//				}
		}
	}
	else
	{
		if (creditScreenInit == false)
		{
			initialized = false;
			creditScreenInit = true;
		}

		if (getControlsManager()->miniGame_CONFIRM_Pressed())
		{
			playing = false;
		}
	}
}

void Ramio::render()
{ // =========================================================================================================================
	NDGameEngine::render();
}

