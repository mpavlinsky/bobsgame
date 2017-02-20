#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger Player::log = Logger("Player");


Player::Player(Engine* g, const string& spriteName)
{ //=========================================================================================================================

	this->e = g;

	EntityData* data = new EntityData(-1, "Player", spriteName, 0, 0);
	initEntity(data);
	initCharacter();
	initPlayer();
}

void Player::initPlayer()
{
	setTicksPerPixelMoved(5);
	setScale(1.25f);
	rotationAnimationSpeedTicks = 100; //80;
}

Player::Player(Engine* g)
{ //=========================================================================================================================

	this->e = g;
	EntityData* data = new EntityData(-1, "Player", "", 0, 0);
	initEntity(data);
	initCharacter();
	initPlayer();
}

void Player::update()
{ //=========================================================================================================================

	if (getClientGameEngine()->playerExistsInMap == false)
	{
		return;
	}

	Character::update();


	handlePlayerControls();

	//this is done here regardless of controls so that external movements still trigger animation and sound, i.e. cutscenes
	checkIfMoved();

	setSpeed();

	doPlayerSound();

	handleAreas();


	doCharacterAnimation();
}

void Player::render(float f)
{ //=========================================================================================================================
	if (getClientGameEngine()->playerExistsInMap == false)
	{
		return;
	}
	Character::render(f);
}

void Player::setAutoPilot(bool b)
{ //=========================================================================================================================
	autopilotActive = b;
}

bool Player::isAutoPilotOn()
{ //=========================================================================================================================
	return autopilotActive;
}

void Player::handleAreas()
{ //=========================================================================================================================


	//go through all areas on this map
	if (getMap()->currentState == nullptr)
	{
		return;
	}

	//   java::util::Iterator<Area*> aEnum = getMap()->currentState->areaByNameHashtable.elements();
	//   //areas
	//   while (aEnum->hasMoreElements())
	//   {
	//      Area* a = aEnum->nextElement();

	ArrayList<Area*> *areas = getMap()->currentState->areaByNameHashtable.getAllValues();
	for (int i=0;i<areas->size();i++)
	{
		Area* a = areas->get(i);

		if (a->isXYXYTouchingMyBoundary(getLeft(), getTop(), getRight(), getBottom()))
		{
			if (a->playerFaceDirection())
			{
				if (a->standSpawnDirection() != -1)
				{
					if (a->standSpawnDirection() == 0)
					{
						movementDirection = UP;
					}
					if (a->standSpawnDirection() == 1)
					{
						movementDirection = DOWN;
					}
					if (a->standSpawnDirection() == 2)
					{
						movementDirection = LEFT;
					}
					if (a->standSpawnDirection() == 3)
					{
						movementDirection = RIGHT;
					}
				}
			}


			if (a->autoPilot() && a->connectionTYPEIDList()->size() > 0)
			{
				autopilotActive = true;
			}
		}
	}


	if (isAutoPilotOn() == true)
	{
		if (autopilotCaption == nullptr)
		{
			autopilotCaption = getCaptionManager()->newManagedCaption(Caption::CENTERED_OVER_ENTITY, 0, -1, "Autopilot", BobFont::font_normal_11_outlined, BobColor::red);
		}
	}
	else
	{
		if (autopilotCaption != nullptr)
		{
			autopilotCaption->setToFadeOutAndBeDeleted();
			autopilotCaption = nullptr;
		}
	}
}

void Player::doPlayerSound()
{ //=========================================================================================================================
	if (moved == true)
	{
		lastPlayedFootstepSoundTicksCounter += getEngine()->engineTicksPassed();

		if (lastPlayedFootstepSoundTicksCounter > getTicksPerPixelMoved() * 60)
		{
			lastPlayedFootstepSoundTicksCounter = 0;

			getAudioManager()->playSound("footstep", 1.0f, Math::randMinMaxFloat(0.5f, 1.0f), 1);
		}
	}
	else
	{
		if (moved == false)
		{
			if (standing == true)
			{
				//TODO: stop playing footsteps?
			}
		}
	}
}

void Player::setSpeed()
{ //=========================================================================================================================

	//============here we are automatically making main sprite stand after half a second, and also turning off footstep sound.

	if (getClientGameEngine() != nullptr && getClientGameEngine()->controlsEnabled == false)
	{
		return;
	}


	//if player is moving
	if (moved == true)
	{
		//set running speed if running (animation is done in animation)
		if (running == true)
		{
			//walking_speed=YUU_RUNNING_SPEED;
			//if(cameraman->walking_speed>PLAYER_npc->walking_speed)cameraman->walking_speed=PLAYER_npc->walking_speed;

			//TODO: increase all of these speeds logarithmically
			setTicksPerPixelMoved(3);
			getCameraman()->setTicksPerPixelMoved(getTicksPerPixelMoved() - 1); //TODO: should have the cameraman speed change set in the cameraman, probably
		}
		else
		{
			if (running == false)
			{
				//accelerate to max walking speed (from standing speed) if enough time has passed
				/*
				      
				   static int last_vbl=0;
				   if(last_vbl!=vbl_var)
				   {
				      last_vbl=vbl_var;
				      //if(vbl_var%5==0&&
				         if(PLAYER_npc->walking_speed>YUU_WALKING_SPEED)PLAYER_npc->walking_speed-=SPEED_ACCEL_INCREMENT_AMOUNT;
				   }
				      
				//TODO: also slow down if speed is still running speed
				 */


				setTicksPerPixelMoved(5);
				getCameraman()->setTicksPerPixelMoved(6);
			}
		}
	}
	else
	{
		if (standing == true)
		{
			//TODO: set standing speed
			//PLAYER_npc->walking_speed=YUU_STANDING_SPEED;
		}
	}
}

void Player::handlePlayerControls()
{ //=========================================================================================================================


	if (getClientGameEngine() != nullptr && (getClientGameEngine()->controlsEnabled == false || getClientGameEngine()->areAnyMenusOpen()))
	{
		noInput = true;
		running = false;
		forceX = 0;
		forceY = 0;
		return;
	}

	//TODO: move all the input stuff into the controlsManager and have it send in a direction pressed

	//FileUtils::distance(0, 0, 1, 1);


	//int temp_map_x = map_x;
	//int temp_map_y = map_y;

	noInput = false;

	int direction = -1;


	if (getControlsManager()->BGCLIENT_RIGHT_HELD == true && getControlsManager()->BGCLIENT_DOWN_HELD == true)
	{
		direction = DOWNRIGHT;
	}
	else
	{
		if (getControlsManager()->BGCLIENT_RIGHT_HELD == true && getControlsManager()->BGCLIENT_UP_HELD == true)
		{
			direction = UPRIGHT;
		}
		else
		{
			if (getControlsManager()->BGCLIENT_LEFT_HELD == true && getControlsManager()->BGCLIENT_DOWN_HELD == true)
			{
				direction = DOWNLEFT;
			}
			else
			{
				if (getControlsManager()->BGCLIENT_LEFT_HELD == true && getControlsManager()->BGCLIENT_UP_HELD == true)
				{
					direction = UPLEFT;
				}
				else
				{
					if (getControlsManager()->BGCLIENT_RIGHT_HELD == true)
					{
						direction = RIGHT;
					}
					else
					{
						if (getControlsManager()->BGCLIENT_LEFT_HELD == true)
						{
							direction = LEFT;
						}
						else
						{
							if (getControlsManager()->BGCLIENT_UP_HELD == true)
							{
								direction = UP;
							}
							else
							{
								if (getControlsManager()->BGCLIENT_DOWN_HELD == true)
								{
									direction = DOWN;
								}
								else
								{
									noInput = true;
								}
							}
						}
					}
				}
			}
		}
	}


	//========handle running
	if (getControlsManager()->BGCLIENT_CANCELRUN_HELD == true)
	{
		running = true;
	}
	else
	{
		running = false;
	}


	forceFactor = 0.1f * pixelsToMoveThisFrame;
	//frictionFactor = 0.0f2f*pixelsToMoveThisFrame;
	frictionFactor = 0.04f * pixelsToMoveThisFrame;


	if (direction == -1)
	{
		//reduce force/apply friction
		if (forceX > 0)
		{
			forceX -= frictionFactor;
			if (forceX < 0)
			{
				forceX = 0.0f;
			}
		}
		if (forceX < 0)
		{
			forceX += frictionFactor;
			if (forceX > 0)
			{
				forceX = 0.0f;
			}
		}

		if (forceY > 0)
		{
			forceY -= frictionFactor;
			if (forceY < 0)
			{
				forceY = 0.0f;
			}
		}
		if (forceY < 0)
		{
			forceY += frictionFactor;
			if (forceY > 0)
			{
				forceY = 0.0f;
			}
		}
	}

	if (direction == LEFT)
	{
		forceX -= forceFactor;
		if (forceX < -speedLimit)
		{
			forceX = -speedLimit;
		}

		//reduce force/apply friction
		if (forceY > 0)
		{
			forceY -= frictionFactor;
			if (forceY < 0)
			{
				forceY = 0.0f;
			}
		}
		if (forceY < 0)
		{
			forceY += frictionFactor;
			if (forceY > 0)
			{
				forceY = 0.0f;
			}
		}
	}
	if (direction == RIGHT)
	{
		forceX += forceFactor;
		if (forceX > speedLimit)
		{
			forceX = speedLimit;
		}

		if (forceY > 0)
		{
			forceY -= frictionFactor;
			if (forceY < 0)
			{
				forceY = 0.0f;
			}
		}
		if (forceY < 0)
		{
			forceY += frictionFactor;
			if (forceY > 0)
			{
				forceY = 0.0f;
			}
		}
	}

	if (direction == UP)
	{
		forceY -= forceFactor;
		if (forceY < -speedLimit)
		{
			forceY = -speedLimit;
		}

		if (forceX > 0)
		{
			forceX -= frictionFactor;
			if (forceX < 0)
			{
				forceX = 0.0f;
			}
		}
		if (forceX < 0)
		{
			forceX += frictionFactor;
			if (forceX > 0)
			{
				forceX = 0.0f;
			}
		}
	}
	if (direction == DOWN)
	{
		forceY += forceFactor;
		if (forceY > speedLimit)
		{
			forceY = speedLimit;
		}

		if (forceX > 0)
		{
			forceX -= frictionFactor;
			if (forceX < 0)
			{
				forceX = 0.0f;
			}
		}
		if (forceX < 0)
		{
			forceX += frictionFactor;
			if (forceX > 0)
			{
				forceX = 0.0f;
			}
		}
	}

	if (direction == UPLEFT)
	{
		forceX -= forceFactor;
		if (forceX < -speedLimit)
		{
			forceX = -speedLimit;
		}

		forceY -= forceFactor;
		if (forceY < -speedLimit)
		{
			forceY = -speedLimit;
		}
	}
	if (direction == UPRIGHT)
	{
		forceX += forceFactor;
		if (forceX > speedLimit)
		{
			forceX = speedLimit;
		}

		forceY -= forceFactor;
		if (forceY < -speedLimit)
		{
			forceY = -speedLimit;
		}
	}
	if (direction == DOWNLEFT)
	{
		forceX -= forceFactor;
		if (forceX < -speedLimit)
		{
			forceX = -speedLimit;
		}


		forceY += forceFactor;
		if (forceY > speedLimit)
		{
			forceY = speedLimit;
		}
	}
	if (direction == DOWNRIGHT)
	{
		forceX += forceFactor;
		if (forceX > speedLimit)
		{
			forceX = speedLimit;
		}

		forceY += forceFactor;
		if (forceY > speedLimit)
		{
			forceY = speedLimit;
		}
	}


	if (direction != -1)
	{
		movementDirection = direction;
	}


	if (forceX < 0)
	{
		move(LEFT, -forceX * pixelsToMoveThisFrame);
	}
	if (forceX > 0)
	{
		move(RIGHT, forceX * pixelsToMoveThisFrame);
	}
	if (forceY < 0)
	{
		move(UP, -forceY * pixelsToMoveThisFrame);
	}
	if (forceY > 0)
	{
		move(DOWN, forceY * pixelsToMoveThisFrame);
	}
}

bool Player::checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(int direction)
{ //=========================================================================================================================

	//this checks one pixel forward in a particular direction, not the current position


	bool hit_wall = true;

	if (direction == UP)
	{
		if (checkXYAgainstHitLayerAndNonWalkableEntities(getLeft() + 1, getTop() - 1) == false && checkXYAgainstHitLayerAndNonWalkableEntities(getMiddleX() - 1, getTop() - 1) == false && checkXYAgainstHitLayerAndNonWalkableEntities(getMiddleX(), getTop() - 1) == false && checkXYAgainstHitLayerAndNonWalkableEntities(getRight() - 3, getTop() - 1) == false)
		{
			hit_wall = false;
		}
	}
	else
	{
		if (direction == DOWN)
		{
			if (checkXYAgainstHitLayerAndNonWalkableEntities(getLeft() + 1, getBottom() + 1) == false && checkXYAgainstHitLayerAndNonWalkableEntities(getMiddleX() - 1, getBottom() + 1) == false && checkXYAgainstHitLayerAndNonWalkableEntities(getMiddleX(), getBottom() + 1) == false && checkXYAgainstHitLayerAndNonWalkableEntities(getRight() - 3, getBottom() + 1) == false)
			{
				hit_wall = false;
			}
		}
		else
		{
			if (direction == LEFT)
			{
				if (checkXYAgainstHitLayerAndNonWalkableEntities(getLeft(), getBottom() - 1) == false && checkXYAgainstHitLayerAndNonWalkableEntities(getLeft(), getTop() + 2) == false)
				{
					//TODO: should check middle for hitBoxLeft() and hitBoxRight() too, in case the player NPC is ever big enough to "straddle" a block. actually, i should check every %8 (%16 now i guess)
					hit_wall = false;
				}
			}
			else
			{
				if (direction == RIGHT)
				{
					if (checkXYAgainstHitLayerAndNonWalkableEntities(getRight() - 1, getBottom() - 1) == false && checkXYAgainstHitLayerAndNonWalkableEntities(getRight() - 1, getTop() + 2) == false)
					{
						hit_wall = false;
					}
				}
			}
		}
	}
	return hit_wall;
}

void Player::move(int direction, float pixels)
{ //=========================================================================================================================


	//if(direction>3)pixelsToMoveThisFrame/=Math.sqrt(2);//0.75f;//only move half speed on diagonals

	{
		//for(int p=0;p<pixelsToMoveThisFrame;p++)

		//int success=1;

		/*if(direction==UPRIGHT)//UPRIGHT
		{
		   int canGoUp=0;
		   int canGoRight=0;
		         
		         
		   if(check_hit_direction(RIGHT)==0)canGoRight=1;
		   if(check_hit_direction(UP)==0)canGoUp=1;
		         
		   //if(canGoUp==1&&canGoRight==1)move_pixel(UPRIGHT);
		   //else if(canGoUp==1)move_pixel(UP);
		   //else if(canGoRight==1)move_pixel(RIGHT);
		         
		   if(canGoUp==1)move_pixel(UP);
		   if(canGoRight==1)move_pixel(RIGHT);
		         
		}
		else
		if(direction==DOWNLEFT)//DOWNLEFT
		{
		   int canGoDown=0;
		   int canGoLeft=0;
		         
		   if(check_hit_direction(LEFT)==0)canGoLeft=1;
		   if(check_hit_direction(DOWN)==0)canGoDown=1;
		         
		   //if(canGoDown==1&&canGoLeft==1)move_pixel(DOWNLEFT);
		   //else if(canGoDown==1)move_pixel(DOWN);
		   //else if(canGoLeft==1)move_pixel(LEFT);
		         
		   if(canGoDown==1)move_pixel(DOWN);
		   if(canGoLeft==1)move_pixel(LEFT);
		         
		}
		else
		if(direction==DOWNRIGHT)//DOWNRIGHT
		{
		   int canGoDown=0;
		   int canGoRight=0;
		         
		   if(check_hit_direction(RIGHT)==0)canGoRight=1;
		   if(check_hit_direction(DOWN)==0)canGoDown=1;
		         
		   //if(canGoDown==1&&canGoRight==1)move_pixel(DOWNRIGHT);
		   //else if(canGoDown==1)move_pixel(DOWN);
		   //else if(canGoRight==1)move_pixel(RIGHT);
		         
		   if(canGoDown==1)move_pixel(DOWN);
		   if(canGoRight==1)move_pixel(RIGHT);
		         
		         
		}
		else
		if(direction==UPLEFT)//UPLEFT
		{
		   int canGoUp=0;
		   int canGoLeft=0;
		         
		   if(check_hit_direction(LEFT)==0)canGoLeft=1;
		   if(check_hit_direction(UP)==0)canGoUp=1;
		         
		   //if(canGoUp==1&&canGoLeft==1)move_pixel(UPLEFT);
		   //else if(canGoUp==1)move_pixel(UP);
		   //else if(canGoLeft==1)move_pixel(LEFT);
		         
		   if(canGoUp==1)move_pixel(UP);
		   if(canGoLeft==1)move_pixel(LEFT);
		         
		         
		         
		}
		else*/


		int wholePixels = (int)(pixels);
		float pixelRemainder = (pixels - wholePixels);

		int mapXWholePixels = (int)(getX());
		float mapXRemainder = (getX() - mapXWholePixels);

		int mapYWholePixels = (int)(getY());
		float mapYRemainder = (getY() - mapYWholePixels);


		if (direction == RIGHT) //RIGHT
		{
			for (int i = 0; i < (int)(pixels); i++)
			{
				if (checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT) == false)
				{
					movePixelInDirection(RIGHT);
				}
			}

			if (mapXRemainder + pixelRemainder >= 1.0f)
			{
				if (checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT) == false)
				{
					setX(getX() + pixelRemainder);
				}
			}
			else
			{
				setX(getX() + pixelRemainder);
			}
		}
		else
		{
			if (direction == LEFT) //LEFT
			{
				for (int i = 0; i < (int)(pixels); i++)
				{
					if (checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT) == false)
					{
						movePixelInDirection(LEFT);
					}
				}

				if (mapXRemainder - pixelRemainder < 0.0f)
				{
					if (checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT) == false)
					{
						setX(getX() - pixelRemainder);
					}
				}
				else
				{
					setX(getX() - pixelRemainder);
				}
			}
			else
			{
				if (direction == UP) //UP
				{
					for (int i = 0; i < (int)(pixels); i++)
					{
						if (checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP) == false)
						{
							movePixelInDirection(UP);
						}
					}

					if (mapYRemainder - pixelRemainder < 0.0f)
					{
						if (checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP) == false)
						{
							setY(getY() - pixelRemainder);
						}
					}
					else
					{
						setY(getY() - pixelRemainder);
					}
				}
				else
				{
					if (direction == DOWN) //DOWN
					{
						for (int i = 0; i < (int)(pixels); i++)
						{
							if (checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN) == false)
							{
								movePixelInDirection(DOWN);
							}
						}

						if (mapYRemainder + pixelRemainder >= 1.0f)
						{
							if (checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN) == false)
							{
								setY(getY() + pixelRemainder);
							}
						}
						else
						{
							setY(getY() + pixelRemainder);
						}
					}
				}
			}
		}


		//else return 0;
	}


	//return success;
}

