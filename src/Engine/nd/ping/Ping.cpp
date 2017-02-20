#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger Ping::log = Logger("Ping");


Ping::Ping(ND* nD)
{ // =========================================================================================================================

	this->nD = nD;
}

void Ping::reset()
{ // =========================================================================================================================


	lp->x = (float)10 - (PingPaddle::w / 2);
	lp->y = (float)(GLUtils::getViewportHeight() / 2) - (PingPaddle::h / 2);


	rp->x = (float)GLUtils::getViewportWidth() - 10 - (PingPaddle::w / 2);
	rp->y = (float)(GLUtils::getViewportHeight() / 2) - (PingPaddle::h / 2);


	ball->x = (float)(GLUtils::getViewportWidth() / 2) - (PingBall::w / 2);
	ball->y = (float)(GLUtils::getViewportHeight() / 2) - (PingBall::h / 2);


	framesSincePressedA = 0;
	framesSincePressedB = 0;
	framesSincePressedRight = 0;
	framesSincePressedLeft = 0;
	framesSincePressedDown = 0;
	framesSincePressedR = 0;
	canPressA = true;
	canPressB = true;
	canPressRight = true;
	canPressLeft = true;
	canPressDown = true;
	canPressR = true;
}

void Ping::initGame()
{ // =========================================================================================================================

	if (easyMode == true)
	{
		highScore = 66;
		maxBallSpeed = 9;
	}
	else
	{
		highScore = 333; // 142
		maxBallSpeed = 9;
	}


	background->init();

	reset();


	initialized = true;
}

void Ping::update()
{ // =========================================================================================================================


	if (quit == false)
	{
		if (initialized == false)
		{
			initGame();
		}


		background->update();


		if (dying)
		{
			getAudioManager()->stopAllMusic();
			getAudioManager()->playMusic("tetrid_death", 0.25f, 1.0f, true);

			if (firstDeath == false)
			{
				firstDeath = true;

				// CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Aww.. Yuu sucks. Come on, let's see this.",FONT_NORMAL_ID,WHITE,BLACK,1,1);
			}
			else if (firstDeath == true)
			{
				firstDeath = false;
				// CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Yuu thinks there's some kind of trick?",FONT_NORMAL_ID,WHITE,BLACK,1,1);
			}
		}
		else
		{
			background->update();

			game();
		}
	}
	else
	{
		initialized = false;

		playingPING = false;
	}
}

void Ping::render()
{ // =========================================================================================================================
	background->render();

	lp->render();
	rp->render();
	ball->render();
}

void Ping::game()
{ // =========================================================================================================================


	if ((!getControlsManager()->MINIGAME_UP_HELD) || (framesSincePressedUp >= 0))
	{
		canPressUp = true;
	}
	else
	{
		framesSincePressedUp++;
	}


	if ((!getControlsManager()->MINIGAME_DOWN_HELD) || (framesSincePressedDown >= 0))
	{
		canPressDown = true;
	}
	else
	{
		framesSincePressedDown++;
	}


	if ((getControlsManager()->MINIGAME_UP_HELD) && (canPressUp))
	{
		getAudioManager()->playSound("tick", 0.5f, 1.0f + Math::randLessThanFloat(0.5f), 1);

		if (whichPaddle == LEFT)
		{
			lp->y -= paddleSpeed * (engineTicksPassed() / 10.0f);
			if (lp->y < 8)
			{
				lp->y = 8;
			}
		}
		if (whichPaddle == RIGHT)
		{
			rp->y -= paddleSpeed * (engineTicksPassed() / 10.0f);
			if (rp->top() < 8)
			{
				rp->y = 8;
			}
		}


		canPressUp = false;
		framesSincePressedUp = 0;
	}


	if ((getControlsManager()->MINIGAME_DOWN_HELD) && (canPressDown))
	{
		getAudioManager()->playSound("tick", 0.5f, 1.0f + Math::randLessThanFloat(0.5f), 1);

		if (whichPaddle == LEFT)
		{
			lp->y += paddleSpeed * (engineTicksPassed() / 10.0f);
			if (lp->bottom() >= GLUtils::getViewportHeight())
			{
				lp->y = (float)GLUtils::getViewportHeight() - (PingPaddle::h + 1);
			}
		}
		if (whichPaddle == RIGHT)
		{
			rp->y += paddleSpeed * (engineTicksPassed() / 10.0f);
			if (rp->bottom() >= GLUtils::getViewportHeight())
			{
				rp->y = (float)GLUtils::getViewportHeight() - (PingPaddle::h + 1);
			}
		}


		canPressDown = false;
		framesSincePressedDown = 0;
	}


	// move ball==============================================================================


	// move up or down based on angle
	ball->y += ballDirY * (angle * (engineTicksPassed() / 120.0f));

	// if getHit ceiling, bounce
	if (ball->top() <= 8)
	{
		ballDirY = DOWN;
	}
	if (ball->bottom() > GLUtils::getViewportHeight())
	{
		ballDirY = UP;
	}

	bool hitleft = false;
	bool hitright = false;
	bool hitwall = false;

	if (ballDirX == LEFT)
	{
		whichPaddle = LEFT;
		lp->selected = true;
		rp->selected = false;

		ball->x -= ballSpeed * (engineTicksPassed() / 10.0f);

		if (ball->left() <= lp->right())
		{
			// if it's touching the paddle
			if ((ball->top() >= lp->top() && ball->top() <= lp->bottom()) || (ball->bottom() >= lp->top() && ball->bottom() <= lp->bottom()))
			{
				hitleft = true;
			}
			else
			{
				hitwall = true;
			}
		}
	}
	else if (ballDirX == RIGHT)
	{
		whichPaddle = RIGHT;
		rp->selected = true;
		lp->selected = false;

		ball->x += ballSpeed * (engineTicksPassed() / 10.0f);

		if (ball->right() >= rp->left())
		{
			// if it's touching the paddle
			if ((ball->top() >= rp->top() && ball->top() <= rp->bottom()) || (ball->bottom() >= rp->top() && ball->bottom() <= rp->bottom()))
			{
				hitright = true;
			}
			else
			{
				hitwall = true;
			}
		}
	}

	// handle hits======================================================
	if (hitleft || hitright)
	{
		// play sound

		getAudioManager()->playSound("pingbeep", 0.25f, 1.0f, 1);

		// score
		score++;

		// if(PING_score==3)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"This is so easy.",FONT_NORMAL_ID,WHITE,BLACK,1,1);
		// if(PING_score==15)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Ok, maybe not.",FONT_NORMAL_ID,WHITE,BLACK,1,1);
		// if(PING_score==30)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"There's a rhythm to it.",FONT_NORMAL_ID,WHITE,BLACK,1,1);
		// if(PING_score==40)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"I'm starting to get it.",FONT_NORMAL_ID,WHITE,BLACK,1,1);
		// if(PING_score==50)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Yeah, I can do this.",FONT_NORMAL_ID,WHITE,BLACK,1,1);

		// increase speed
		ballSpeed++;
		if (ballSpeed > maxBallSpeed)
		{
			ballSpeed = maxBallSpeed;
		}

		float pxFromMiddleY = 0;

		if (hitleft)
		{
			// change direction
			ballDirX = RIGHT;
			// if ball touching paddle, bounce depending on angle
			// set angle depending on where touched the paddle.
			// so we should calc based on the middle of the ball vs the middle of the paddle divided into chunks.
			if (ball->middleY() > lp->middleY())
			{
				if (ballDirY == STRAIGHT)
				{
					ballDirY = DOWN; // down
				}
				pxFromMiddleY = ball->middleY() - lp->middleY();
			}

			if (ball->middleY() <= lp->middleY())
			{
				if (ballDirY == STRAIGHT)
				{
					ballDirY = UP; // up
				}
				pxFromMiddleY = lp->middleY() - ball->middleY();
			}
		}

		if (hitright)
		{
			// change direction
			ballDirX = LEFT;

			// if ball touching paddle, bounce depending on angle
			if (ball->middleY() > rp->middleY())
			{
				if (ballDirY == STRAIGHT)
				{
					ballDirY = DOWN; // down
				}
				pxFromMiddleY = ball->middleY() - rp->middleY();
			}

			if (ball->middleY() <= rp->middleY())
			{
				if (ballDirY == STRAIGHT)
				{
					ballDirY = UP; // up
				}
				pxFromMiddleY = rp->middleY() - ball->middleY();
			}
		}


		angle = (pxFromMiddleY / (PingPaddle::h / 2.0f));
	}

	if (hitwall) // reset
	{
		getAudioManager()->playSound("pingbad", 0.25f, 1.0f, 1);

		// reset ball speed, direction, x, y
		ballDirX = LEFT;
		ballDirY = 0;
		angle = 5;
		ballSpeed = 1;

		if (score > highScore)
		{
			highScore = score;
			gotHighScore = true;

			getAudioManager()->playSound("pinghighscore", 0.25f, 1.0f, 1);
		}
		score = 0;

		if (gotHighScore == false)
		{
			// int r=0;
			// r=rand()%5;
			// if(r==0)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Is this even possible?",FONT_NORMAL_ID,WHITE,BLACK,1,1);
			// if(r==1)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"I hate this game.",FONT_NORMAL_ID,WHITE,BLACK,1,1);
			// if(r==2)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"What a dumb game.",FONT_NORMAL_ID,WHITE,BLACK,1,1);
			// if(r==3)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"People liked this?",FONT_NORMAL_ID,WHITE,BLACK,1,1);
			// if(r==4)CAPTION_make_caption(&yuu_ping_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"What's the point of this?",FONT_NORMAL_ID,WHITE,BLACK,1,1);

			reset();
		}
		else
		{
			reset();
			//quit=true;
		}
	}


	updateScore();
}

void Ping::updateScore()
{ // =========================================================================================================================


	// char char_score[15];
	// sprintf(char_score,"%d",PING_score);
	// int score_length=strlen(char_score);
	//
	//
	// int x=0;
	//
	//
	// for(x=0;x<3;x++)
	// {
	// PING_set_tile(1,2,8+x-3,2,29*32);
	// PING_set_tile(1,2,8+x-3,3,29*32);
	// }
	//
	// for(x=0;x<score_length;x++)
	// {
	// PING_set_tile(1,2,8+x-score_length,2,(char_score[x]-48)+(30*32));
	// PING_set_tile(1,2,8+x-score_length,3,(char_score[x]-48)+(31*32));
	// }
	//
	// char char_hiscore[15];
	// sprintf(char_hiscore,"%d",PING_high_score);
	// int hiscore_length=strlen(char_hiscore);
	//
	// //if(PING_high_score==0)
	// for(x=0;x<3;x++)
	// {
	// PING_set_tile(1,2,29+x-3,2,29*32);
	// PING_set_tile(1,2,29+x-3,3,29*32);
	// }
	//
	// for(x=0;x<hiscore_length;x++)
	// {
	// PING_set_tile(1,2,29+x-hiscore_length,2,(char_hiscore[x]-48)+(30*32));
	// PING_set_tile(1,2,29+x-hiscore_length,3,(char_hiscore[x]-48)+(31*32));
	// }
}

