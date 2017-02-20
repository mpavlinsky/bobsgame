#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger Character::log = Logger("Character");


Character::Character()
{ //=========================================================================================================================
}


//Character::Character(Engine* g)
//{ //=========================================================================================================================
//   this->e = g;
//
//}

Character::Character(Engine* g, EntityData* data)
{ //=========================================================================================================================


	this->e = g;

	initEntity(data);

	initCharacter();
}

void Character::initCharacter()
{
	clipShadow = true;

	//setScale(1.25f);
	setAnimateThroughAllFrames(false);
	setAnimateThroughCurrentAnimation(false);

	setLoopAnimation(false);
	setRandomFrames(false);

	setTicksBetweenFrames(0); //set in shouldAnimate() based on walking speed.
	setTicksBetweenAnimationLoop(0); //should always be 0 for chars
	setRandomUpToTicksBetweenAnimationLoop(false); //should always be false for chars

	setAnimationDisabled(false);

	setIsNPC(true);
	setVoicePitch(1.0f);
}

/**
This is specifically for something, not sure what
*/
Character::Character(Engine* g, string name, Sprite* sprite, Area* a)
{ //=========================================================================================================================
	this->e = g;

	EntityData* data = new EntityData(-1, name, sprite->getName(), (int)a->middleX() / 2, (int)a->middleY() / 2, 0, false, true, 255, 1.25f, 8);

	initEntity(data);


	getCurrentMap()->currentState->characterList.add(this);
	getCurrentMap()->currentState->characterByNameHashtable.put(name, this);
}

void Character::initCurrentAnimationFromSprite()
{ //=========================================================================================================================

	Entity::initCurrentAnimationFromSprite();


	if (getCurrentAnimationName() == "Up")
	{
		setAnimationByDirection(UP);
		movementDirection = UP;
	}
	if (getCurrentAnimationName() == "Down")
	{
		setAnimationByDirection(DOWN);
		movementDirection = DOWN;
	}
	if (getCurrentAnimationName() == "Left")
	{
		setAnimationByDirection(LEFT);
		movementDirection = LEFT;
	}
	if (getCurrentAnimationName() == "Right")
	{
		setAnimationByDirection(RIGHT);
		movementDirection = RIGHT;
	}


	setX((float)(((float)(getData()->getSpawnXPixelsHQ())) - ((getScale() - 1.0f) * getWidth() / 2.0f))); //this ADJUSTS the actual placement of the npcs by getScale, since in the editor they dont line up nicely without moving them per-pixel.

	setY(getData()->getSpawnYPixelsHQ());
}

void Character::render(float alpha)
{ //=========================================================================================================================
	if (draw == false)
	{
		return;
	}


	if (uniqueTexture == nullptr)
	{
		Entity::render(alpha);
	}
	else
	{
		Entity::render(alpha, uniqueTexture, sprite->shadowTexture);
	}
}

void Character::update()
{ //=========================================================================================================================

	Entity::update();

	if (sprite == nullptr)
	{
		return;
	}


	//process behaviors
	//for(int i=0;i<getBehaviorList->size();i++)
	{
		{
			//if(getBehaviorList.get(i).equals("walkToPointsRandomly"))
			//if we have a current area

			if (currentAreaTYPEIDTarget.length() > 0)
			{
				//find current area
				if (String::startsWith(currentAreaTYPEIDTarget, "DOOR.") == false)
				{
					//get current area x and y
					Area* a = getMap()->getAreaOrWarpAreaByTYPEID(currentAreaTYPEIDTarget);

					if (a == nullptr)
					{
						currentAreaTYPEIDTarget = "";
						return;
					}
					//walk towards x and y
					//boolean there = walk_to_xy_nohit( a.getMapXPixelsHQ + a.getWidthPixelsHQ/2, a.getMapYPixelsHQ + a.getHeightPixelsHQ/2);

					int there = 0;
					if (getMap()->getIsOutside() == false && getMap()->getWidthTiles1X() < 100 && getMap()->getHeightTiles1X() < 100)
					{
						there = walkToXYWithPathFinding(a->middleX(), a->middleY());
					}
					//else there=walkToXYNoHitAvoidOthersPushMain(a.getMiddleX(),a.getMiddleY());
					else if (walkToXYNoCheckHit(a->middleX(), a->middleY()))
					{
						there = 1;
					}

					//boolean there = in_range_of_area_xyxy_in_direction_by_amount(a.getMapXPixelsHQ, a.getMapYPixelsHQ, a.getMapXPixelsHQ + a.getWidthPixelsHQ, a.getMapYPixelsHQ + a.getHeightPixelsHQ, anim_dir, 0);
					//if we are there, pick a new point
					if (there == 1)
					{
						//check area for variables: stay here, wait x ms, face direction

						if (a->standSpawnDirection() != -1)
						{
							if (a->standSpawnDirection() == 0)
							{
								setAnimationByDirection(UP);
							}
							if (a->standSpawnDirection() == 1)
							{
								setAnimationByDirection(DOWN);
							}
							if (a->standSpawnDirection() == 2)
							{
								setAnimationByDirection(LEFT);
							}
							if (a->standSpawnDirection() == 3)
							{
								setAnimationByDirection(RIGHT);
							}
						}

						if (ticksToStand > 0)
						{
							ticksToStand -= (int)getEngine()->engineTicksPassed();
						}
						else
						{
							currentAreaTYPEIDTarget = "";

							if (getConnectionTYPEIDList()->size() > 0)
							{
								currentAreaTYPEIDTarget = getConnectionTYPEIDList()->get(Math::randLessThan(getConnectionTYPEIDList()->size()));
							}
						}
					}
					else
					{
						//set standing ticks to current ticks
						if (a->waitHereTicks() > 0)
						{
							ticksToStand = a->waitHereTicks();
						}
						else
						{
							ticksToStand = 0;
						}
					}
				}
			}
			else
			{
				currentAreaTYPEIDTarget = "";
				//else pick a new point
				if (getConnectionTYPEIDList()->size() > 0)
				{
					currentAreaTYPEIDTarget = getConnectionTYPEIDList()->get(Math::randLessThan(getConnectionTYPEIDList()->size()));
				}
			}
		}
	}


	//this is done here regardless of controls so that external movements still trigger animation and sound, i.e. cutscenes
	//don't need to do this for player, randomcharacter, cameraman.

	//if(this instanceof Character) //this will let through Player, RandomCharacter, etc, but NOT Entity
	//if (this->getClass().equals(Character::typeid)) //this will ONLY do Character
	if (dynamic_cast<Character*>(this) != NULL)
	{
		//log.debug(""+getName());
		checkIfMoved();

		doCharacterAnimation();
	}
}

void Character::setAnimationByDirection(int dir)
{ //===========================================================================================================================

	//need to figure out is sprite has 8 directions or just 4. allow movement and animation in all 8

	//DONE: if animation doesnt exist keep it the same. (logs error)

	if (canDoCharacterMovementOrStandingAnimation())
	{
		string sequenceName = "";
		if (dir == UP)
		{
			sequenceName = "Up";
		}
		if (dir == DOWN)
		{
			sequenceName = "Down";
		}
		if (dir == LEFT)
		{
			sequenceName = "Left";
		}
		if (dir == RIGHT)
		{
			sequenceName = "Right";
		}

		if (sprite->getNumberOfAnimations() > 4)
		{
			if (dir == UPLEFT)
			{
				sequenceName = "UpLeft";
			}
			if (dir == UPRIGHT)
			{
				sequenceName = "UpRight";
			}
			if (dir == DOWNLEFT)
			{
				sequenceName = "DownLeft";
			}
			if (dir == DOWNRIGHT)
			{
				sequenceName = "DownRight";
			}
		}

		if (sequenceName.length() > 0)
		{
			int offset = getCurrentFrameOffsetInCurrentAnimation();

			setCurrentAnimationByName(sequenceName);

			setFrameOffsetInCurrentAnimation(offset);
		}

		animationDirection = dir;
	}
}

bool Character::canDoCharacterMovementOrStandingAnimation()
{ //=========================================================================================================================
	if (disableMovementAnimationForAllEntities == true || getMovementAnimationDisabled() == true || getAnimatingThroughAllFrames() == true || getAnimatingThroughCurrentAnimation() == true)
	//||
	//getLoopAnimation()==true
	{
		return false;
	}
	return true;
}

void Character::doCharacterAnimation()
{ //=========================================================================================================================


	if (getAnimatingThroughCurrentAnimation() || getAnimatingThroughAllFrames())
	{
		return;
	}


	int nextAnimDirection = animationDirection;


	if (sprite->getNumberOfAnimations() < 8)
	{
		nextAnimDirection = movementDirection;
	}


	if (sprite->getNumberOfAnimations() >= 8)
	{
		if (movementDirection != animationDirection)
		{
			if (movementDirection == UP)
			{
				if (animationDirection == UP)
				{
					nextAnimDirection = UP;
				}
				else if (animationDirection == DOWN)
				{
					if (Math::randLessThan(2) == 0)
					{
						nextAnimDirection = DOWNLEFT;
					}
					else
					{
						nextAnimDirection = DOWNRIGHT;
					}
				}
				else if (animationDirection == LEFT)
				{
					nextAnimDirection = UPLEFT;
				}
				else if (animationDirection == RIGHT)
				{
					nextAnimDirection = UPRIGHT;
				}
				else if (animationDirection == UPLEFT)
				{
					nextAnimDirection = UP;
				}
				else if (animationDirection == UPRIGHT)
				{
					nextAnimDirection = UP;
				}
				else if (animationDirection == DOWNLEFT)
				{
					nextAnimDirection = LEFT;
				}
				else if (animationDirection == DOWNRIGHT)
				{
					nextAnimDirection = RIGHT;
				}
			}
			else if (movementDirection == DOWN)
			{
				if (animationDirection == UP)
				{
					if (Math::randLessThan(2) == 0)
					{
						nextAnimDirection = UPLEFT;
					}
					else
					{
						nextAnimDirection = UPRIGHT;
					}
				}
				else if (animationDirection == DOWN)
				{
					nextAnimDirection = DOWN;
				}
				else if (animationDirection == LEFT)
				{
					nextAnimDirection = DOWNLEFT;
				}
				else if (animationDirection == RIGHT)
				{
					nextAnimDirection = DOWNRIGHT;
				}
				else if (animationDirection == UPLEFT)
				{
					nextAnimDirection = LEFT;
				}
				else if (animationDirection == UPRIGHT)
				{
					nextAnimDirection = RIGHT;
				}
				else if (animationDirection == DOWNLEFT)
				{
					nextAnimDirection = DOWN;
				}
				else if (animationDirection == DOWNRIGHT)
				{
					nextAnimDirection = DOWN;
				}
			}
			else if (movementDirection == LEFT)
			{
				if (animationDirection == UP)
				{
					nextAnimDirection = UPLEFT;
				}
				else if (animationDirection == DOWN)
				{
					nextAnimDirection = DOWNLEFT;
				}
				else if (animationDirection == LEFT)
				{
					nextAnimDirection = LEFT;
				}
				else if (animationDirection == RIGHT)
				{
					if (Math::randLessThan(2) == 0)
					{
						nextAnimDirection = UPRIGHT;
					}
					else
					{
						nextAnimDirection = DOWNRIGHT;
					}
				}
				else if (animationDirection == UPLEFT)
				{
					nextAnimDirection = LEFT;
				}
				else if (animationDirection == UPRIGHT)
				{
					nextAnimDirection = UP;
				}
				else if (animationDirection == DOWNLEFT)
				{
					nextAnimDirection = LEFT;
				}
				else if (animationDirection == DOWNRIGHT)
				{
					nextAnimDirection = DOWN;
				}
			}
			else if (movementDirection == RIGHT)
			{
				if (animationDirection == UP)
				{
					nextAnimDirection = UPRIGHT;
				}
				else if (animationDirection == DOWN)
				{
					nextAnimDirection = DOWNRIGHT;
				}
				else if (animationDirection == LEFT)
				{
					if (Math::randLessThan(2) == 0)
					{
						nextAnimDirection = DOWNLEFT;
					}
					else
					{
						nextAnimDirection = UPLEFT;
					}
				}
				else if (animationDirection == RIGHT)
				{
					nextAnimDirection = RIGHT;
				}
				else if (animationDirection == UPLEFT)
				{
					nextAnimDirection = UP;
				}
				else if (animationDirection == UPRIGHT)
				{
					nextAnimDirection = RIGHT;
				}
				else if (animationDirection == DOWNLEFT)
				{
					nextAnimDirection = DOWN;
				}
				else if (animationDirection == DOWNRIGHT)
				{
					nextAnimDirection = RIGHT;
				}
			}
			else if (movementDirection == UPLEFT)
			{
				if (animationDirection == UP)
				{
					nextAnimDirection = UPLEFT;
				}
				else if (animationDirection == DOWN)
				{
					nextAnimDirection = DOWNLEFT;
				}
				else if (animationDirection == LEFT)
				{
					nextAnimDirection = UPLEFT;
				}
				else if (animationDirection == RIGHT)
				{
					nextAnimDirection = UPRIGHT;
				}
				else if (animationDirection == UPLEFT)
				{
					nextAnimDirection = UPLEFT;
				}
				else if (animationDirection == UPRIGHT)
				{
					nextAnimDirection = UP;
				}
				else if (animationDirection == DOWNLEFT)
				{
					nextAnimDirection = LEFT;
				}
				else if (animationDirection == DOWNRIGHT)
				{
					if (Math::randLessThan(2) == 0)
					{
						nextAnimDirection = DOWN;
					}
					else
					{
						nextAnimDirection = RIGHT;
					}
				}
			}
			else if (movementDirection == UPRIGHT)
			{
				if (animationDirection == UP)
				{
					nextAnimDirection = UPRIGHT;
				}
				else if (animationDirection == DOWN)
				{
					nextAnimDirection = DOWNRIGHT;
				}
				else if (animationDirection == LEFT)
				{
					nextAnimDirection = UPLEFT;
				}
				else if (animationDirection == RIGHT)
				{
					nextAnimDirection = UPRIGHT;
				}
				else if (animationDirection == UPLEFT)
				{
					nextAnimDirection = UP;
				}
				else if (animationDirection == UPRIGHT)
				{
					nextAnimDirection = UPRIGHT;
				}
				else if (animationDirection == DOWNLEFT)
				{
					if (Math::randLessThan(2) == 0)
					{
						nextAnimDirection = LEFT;
					}
					else
					{
						nextAnimDirection = DOWN;
					}
				}
				else if (animationDirection == DOWNRIGHT)
				{
					nextAnimDirection = RIGHT;
				}
			}
			else if (movementDirection == DOWNLEFT)
			{
				if (animationDirection == UP)
				{
					nextAnimDirection = UPLEFT;
				}
				else if (animationDirection == DOWN)
				{
					nextAnimDirection = DOWNLEFT;
				}
				else if (animationDirection == LEFT)
				{
					nextAnimDirection = DOWNLEFT;
				}
				else if (animationDirection == RIGHT)
				{
					nextAnimDirection = DOWNRIGHT;
				}
				else if (animationDirection == UPLEFT)
				{
					nextAnimDirection = LEFT;
				}
				else if (animationDirection == UPRIGHT)
				{
					if (Math::randLessThan(2) == 0)
					{
						nextAnimDirection = UP;
					}
					else
					{
						nextAnimDirection = RIGHT;
					}
				}
				else if (animationDirection == DOWNLEFT)
				{
					nextAnimDirection = DOWNLEFT;
				}
				else if (animationDirection == DOWNRIGHT)
				{
					nextAnimDirection = DOWN;
				}
			}
			else if (movementDirection == DOWNRIGHT)
			{
				if (animationDirection == UP)
				{
					nextAnimDirection = UPRIGHT;
				}
				else if (animationDirection == DOWN)
				{
					nextAnimDirection = DOWNRIGHT;
				}
				else if (animationDirection == LEFT)
				{
					nextAnimDirection = DOWNLEFT;
				}
				else if (animationDirection == RIGHT)
				{
					nextAnimDirection = DOWNRIGHT;
				}
				else if (animationDirection == UPLEFT)
				{
					if (Math::randLessThan(2) == 0)
					{
						nextAnimDirection = UP;
					}
					else
					{
						nextAnimDirection = LEFT;
					}
				}
				else if (animationDirection == UPRIGHT)
				{
					nextAnimDirection = RIGHT;
				}
				else if (animationDirection == DOWNLEFT)
				{
					nextAnimDirection = DOWN;
				}
				else if (animationDirection == DOWNRIGHT)
				{
					nextAnimDirection = DOWNRIGHT;
				}
			}
		}
	}


	if (animationDirection != nextAnimDirection)
	{
		//TODO: maybe figure out how many directions player needs to turn in order to get to walking direction,
		//i.e. turn faster if they have to fully turn around, in order to make a full 180 degree turn look less dumb


		//animate 8-direction characters by rotating them in between diagonal directions with a timing delay
		//EDIT: I will have 4-direction characters have a slight delay as well.
		if (haveTicksPassedSinceLastAnimated_ResetIfTrue(rotationAnimationSpeedTicks) == true)
		{
			//notice the direction isn't set until after the delay
			setAnimationByDirection(nextAnimDirection);

			if (canDoCharacterMovementOrStandingAnimation())
			{
				incrementAnimationFrameInCurrentAnimation();
			}
		}
	}
	else
	{
		if (standing == false)
		{
			//TODO: handle running animation
			if (running == true)
			{
				//set animation to running
				//if(PLAYER_npc->gfx==GFX_KID_yuu)PLAYER_npc->gfx=GFX_KID_yuurunning;
				//else if(PLAYER_npc->gfx==GFX_KID_youngyuu)PLAYER_npc->gfx=GFX_KID_youngyuurunning;
			}
			else
			{
				if (running == false)
				{
					//set animation to walking
					//if(PLAYER_npc->gfx==GFX_KID_yuurunning)PLAYER_npc->gfx=GFX_KID_yuu;
					//else if(PLAYER_npc->gfx==GFX_KID_youngyuurunning)PLAYER_npc->gfx=GFX_KID_youngyuu;
				}
			}

			if (canDoCharacterMovementOrStandingAnimation())
			{
				//doMovementAnimation();
				//=========================================================================================================================
				//public void doMovementAnimation()
				{ //=========================================================================================================================


					int movementTicksBetweenFrames = 0;

					if (getTicksPerPixelMoved() >= ticksPerPixel_NORMAL) //slower than normal
					{
						movementTicksBetweenFrames = (int)(getTicksPerPixelMoved() * (8.0f));
					}
					else
					{
						movementTicksBetweenFrames = (int)(getTicksPerPixelMoved() * (10.0f));
					}

					if (haveTicksPassedSinceLastAnimated_ResetIfTrue(movementTicksBetweenFrames) == true)
					{
						incrementAnimationFrameInCurrentAnimation();
					}
				}
			}
		}
		else
		{
			if (standing == true)
			{
				//TODO: set animation back to walking

				//doStandingAnimation();
				//=========================================================================================================================
				//public void doStandingAnimation()
				{ //=========================================================================================================================


					if (haveTicksPassedSinceLastAnimated_ResetIfTrue(standingTicksBetweenFrames) == true)
					{
						bool standRightAway = false;
						if (standingTicksBetweenFrames == 0)
						{
							standRightAway = true;
						}

						//randomize ticks between standing frames
						standingTicksBetweenFrames = 200 + Math::randUpToIncluding(600);


						bool jittered = false;

						//if standing, jitter a pixel or two. this is added in Entity.screenXY() and does not affect real position
						if (Math::randLessThan(6) == 0)
						{
							jittered = true;
							if (standJitterX != 0)
							{
								standJitterX = 0;
							}
							else
							{
								if (Math::randLessThan(2) == 0)
								{
									standJitterX++;
								}
								else
								{
									standJitterX--;
								}
							}
						}
						else
						{
							if (Math::randLessThan(6) == 1)
							{
								jittered = true;
								if (standJitterY != 0)
								{
									standJitterY = 0;
								}
								else
								{
									if (Math::randLessThan(2) == 0)
									{
										standJitterY++;
									}
									else
									{
										standJitterY--;
									}
								}
							}
						}

						if (jittered || standRightAway)
						{
							if (canDoCharacterMovementOrStandingAnimation())
							{
								//NOTICE: this is hardcoded for characters. sequence is frames-1, (frames/2)-1
								if (getCurrentFrameOffsetInCurrentAnimation() == 0)
								{
									//(frames/2)-1
									setFrameOffsetInCurrentAnimation((getCurrentAnimationNumberOfFrames() / 2) - 1);
								}
								else
								{
									//frames-1
									setFrameOffsetInCurrentAnimation(getCurrentAnimationNumberOfFrames() - 1);
								}

								incrementAnimationFrameInCurrentAnimation();
							}
						}
					}
				}
			}
		}
	}
}

void Character::checkIfMoved()
{ //=========================================================================================================================

	//if player is moving
	if (lastMapX != floor(getX()) || lastMapY != floor(getY()))
	{
		lastMapX = (float)(floor(getX()));
		lastMapY = (float)(floor(getY()));

		ticksSinceMoved = 0;

		moved = true;

		standing = false;


		if (draw == true)
		{
			//if we've moved a pixel we want to set the background priority
			//setPriorityFromFXLayer();


			if (getDisableShadow() == false && sprite != nullptr && sprite->getHasShadow() == true && clipShadow == true)
			{
				setShadowClip();
			}
		}
	}
	else
	{
		ticksSinceMoved += (int)getEngine()->engineTicksPassed();
		//TODO: put anything here that i want to happen immediately when the sprite stops moving

		moved = false;

		if (ticksSinceMoved > 100)
		{
			standing = true; //this also takes a little bit of time to animate to standing position
		}
		else
		{
			standingTicksBetweenFrames = 0;
		}
	}


	if (standing == false)
	{
		standJitterX = 0;
		standJitterY = 0;
	}
}

//=========================================================================================================================
void Character::dontLookAtEntity(Entity* e)
{ //=========================================================================================================================


	if (this != getPlayer())
	{
		float amt1 = (getMiddleX()) - (e->getMiddleX());
		float amt2 = (getMiddleY()) - (e->getMiddleY());
		if (amt1 < 0)
		{
			amt1 = amt1 * -1;
		}
		if (amt2 < 0)
		{
			amt2 = amt2 * -1;
		}

		if (amt2 >= amt1)
		{
			if (getMiddleY() < e->getMiddleY())
			{
				setAnimationByDirection(UP);
			}
			if (getMiddleY() > e->getMiddleY())
			{
				setAnimationByDirection(DOWN);
			}
		}
		else
		{
			if (getMiddleX() > e->getMiddleX())
			{
				setAnimationByDirection(RIGHT);
			}
			if (getMiddleX() < e->getMiddleX())
			{
				setAnimationByDirection(LEFT);
			}
		}
	}
	else
	{
		if (getMiddleX() <= e->getMiddleX())
		{
			setAnimationByDirection(LEFT);
		} //hitBoxLeft()
		if (getMiddleX() >= e->getMiddleX())
		{
			setAnimationByDirection(RIGHT);
		} //hitBoxRight()
		if (getMiddleY() <= e->getMiddleY())
		{
			setAnimationByDirection(UP);
		} //up
		if (getMiddleY() >= e->getMiddleY())
		{
			setAnimationByDirection(DOWN);
		} //down
		if (getMiddleX() <= e->getMiddleX() && getMiddleY() <= e->getMiddleY())
		{
			setAnimationByDirection(UPLEFT);
		}
		if (getMiddleX() >= e->getMiddleX() && getMiddleY() <= e->getMiddleY())
		{
			setAnimationByDirection(UPRIGHT);
		}
		if (getMiddleY() >= e->getMiddleY() && getMiddleX() <= e->getMiddleX())
		{
			setAnimationByDirection(DOWNLEFT);
		}
		if (getMiddleY() >= e->getMiddleY() && getMiddleX() >= e->getMiddleX())
		{
			setAnimationByDirection(DOWNRIGHT);
		}
	}
}

//=========================================================================================================================
void Character::lookAtEntity(Entity* e)
{ //=========================================================================================================================


	if (this != getPlayer())
	{
		float amt1 = (getMiddleX()) - (e->getMiddleX());
		float amt2 = (getMiddleY()) - (e->getMiddleY());
		if (amt1 < 0)
		{
			amt1 = amt1 * -1;
		}
		if (amt2 < 0)
		{
			amt2 = amt2 * -1;
		}

		if (amt2 >= amt1)
		{
			if (getMiddleY() < e->getMiddleY())
			{
				setAnimationByDirection(DOWN);
			}
			if (getMiddleY() > e->getMiddleY())
			{
				setAnimationByDirection(UP);
			}
		}
		else
		{
			if (getMiddleX() > e->getMiddleX())
			{
				setAnimationByDirection(LEFT);
			}
			if (getMiddleX() < e->getMiddleX())
			{
				setAnimationByDirection(RIGHT);
			}
		}
	}
	else
	{
		if (getMiddleX() <= e->getMiddleX())
		{
			setAnimationByDirection(RIGHT);
		}
		if (getMiddleX() >= e->getMiddleX())
		{
			setAnimationByDirection(LEFT);
		}
		if (getMiddleY() <= e->getMiddleY())
		{
			setAnimationByDirection(DOWN);
		}
		if (getMiddleY() >= e->getMiddleY())
		{
			setAnimationByDirection(UP);
		}
		if (getMiddleX() <= e->getMiddleX() && getMiddleY() <= e->getMiddleY())
		{
			setAnimationByDirection(DOWNRIGHT);
		}
		if (getMiddleX() >= e->getMiddleX() && getMiddleY() <= e->getMiddleY())
		{
			setAnimationByDirection(DOWNLEFT);
		}
		if (getMiddleY() >= e->getMiddleY() && getMiddleX() <= e->getMiddleX())
		{
			setAnimationByDirection(UPRIGHT);
		}
		if (getMiddleY() >= e->getMiddleY() && getMiddleX() >= e->getMiddleX())
		{
			setAnimationByDirection(UPLEFT);
		}
	}
}

//=========================================================================================================================
void Character::lookAtEntityButNotOppositeWalkingDirection(Entity* stared_at_entity)
{ //=========================================================================================================================

	float amt1 = (getMiddleX()) - (stared_at_entity->getMiddleX());
	float amt2 = (getMiddleY()) - (stared_at_entity->getMiddleY());
	if (amt1 < 0)
	{
		amt1 = amt1 * -1;
	}
	if (amt2 < 0)
	{
		amt2 = amt2 * -1;
	}

	if (amt2 >= amt1)
	{
		if (getMiddleY() < stared_at_entity->getMiddleY())
		{
			if (movementDirection != UP)
			{
				setAnimationByDirection(DOWN);
			}
		}
		if (getMiddleY() > stared_at_entity->getMiddleY())
		{
			if (movementDirection != DOWN)
			{
				setAnimationByDirection(UP);
			}
		}
	}
	else
	{
		if (getMiddleX() > stared_at_entity->getMiddleX())
		{
			if (movementDirection != RIGHT)
			{
				setAnimationByDirection(LEFT);
			}
		}
		if (getMiddleX() < stared_at_entity->getMiddleX())
		{
			if (movementDirection != LEFT)
			{
				setAnimationByDirection(RIGHT);
			}
		}
	}
}

//=========================================================================================================================
void Character::setAppearanceFromCharacterAppearanceString(string s)
{ //=========================================================================================================================


	if (s.length() > 0)
	{
		int genderIndex = -1;
		int archetypeIndex = -1;
		int hairColorIndex = -1;
		int skinColorIndex = -1;
		int eyeColorIndex = -1;
		int shirtColorIndex = -1;
		int pantsColorIndex = -1;
		int shoeColorIndex = -1;


		try
		{
			genderIndex = stoi(s.substr(0, s.find(",")));
		}
		catch (exception ex)
		{
			return;
		}
		s = s.substr(s.find(",") + 1);
		try
		{
			archetypeIndex = stoi(s.substr(0, s.find(",")));
		}
		catch (exception ex)
		{
			return;
		}
		s = s.substr(s.find(",") + 1);
		try
		{
			hairColorIndex = stoi(s.substr(0, s.find(",")));
		}
		catch (exception ex)
		{
			return;
		}
		s = s.substr(s.find(",") + 1);
		try
		{
			skinColorIndex = stoi(s.substr(0, s.find(",")));
		}
		catch (exception ex)
		{
			return;
		}
		s = s.substr(s.find(",") + 1);
		try
		{
			eyeColorIndex = stoi(s.substr(0, s.find(",")));
		}
		catch (exception ex)
		{
			return;
		}
		s = s.substr(s.find(",") + 1);
		try
		{
			shirtColorIndex = stoi(s.substr(0, s.find(",")));
		}
		catch (exception ex)
		{
			return;
		}
		s = s.substr(s.find(",") + 1);
		try
		{
			pantsColorIndex = stoi(s.substr(0, s.find(",")));
		}
		catch (exception ex)
		{
			return;
		}
		s = s.substr(s.find(",") + 1);
		try
		{
			shoeColorIndex = stoi(s);
		}
		catch (exception ex)
		{
			return;
		}

		generateUniqueTexture(genderIndex, archetypeIndex, shoeColorIndex, shirtColorIndex, pantsColorIndex, skinColorIndex, eyeColorIndex, hairColorIndex);
	}
}

//=========================================================================================================================
void Character::generateUniqueTexture(int genderIndex, int archetypeIndex, int shoeColorIndex, int shirtColorIndex, int pantsColorIndex, int skinColorIndex, int eyeColorIndex, int hairColorIndex)
{ //=========================================================================================================================

	getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMcarColors")->loadTextures();
	getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMeyeColors")->loadTextures();
	getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMskinColors")->loadTextures();
	getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMhairColors")->loadTextures();
	getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMshirtColors")->loadTextures();
	getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMpantsColors")->loadTextures();
	getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMshoeColors")->loadTextures();


	Sprite* sprite = nullptr;


	if (genderIndex == 0) //male
	{
		isMale = true;
		isFemale = false;

		if (archetypeIndex == 0)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("popularboy");
		}
		if (archetypeIndex == 1)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("hipsterboy");
		}
		if (archetypeIndex == 2)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("gothboy");
		}
		if (archetypeIndex == 3)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("toughboy");
		}
		if (archetypeIndex == 4)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("athleticboy");
		}
		if (archetypeIndex == 5)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("nerdyboy");
		}
		if (archetypeIndex == 6)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("pudgyboy");
		}
		if (archetypeIndex == 7)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("punkboy");
		}
		if (archetypeIndex == 8)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("skaterboy");
		}
		if (archetypeIndex == 9)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("thugboy");
		}
		if (archetypeIndex == 10)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("pimpleboy");
		}
		if (archetypeIndex == 11)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyBuzzedHairLongSleeve");
		}
		if (archetypeIndex == 12)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyBuzzedHairShortSleeve");
		}
		if (archetypeIndex == 13)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyBuzzedHairLongSleeveShorts");
		}
		if (archetypeIndex == 14)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyBuzzedHairShortSleeveShorts");
		}
		if (archetypeIndex == 15)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyMessyHairLongSleeve");
		}
		if (archetypeIndex == 16)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyMessyHairShortSleeve");
		}
		if (archetypeIndex == 17)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyMessyHairLongSleeveShorts");
		}
		if (archetypeIndex == 18)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyMessyHairShortSleeveShorts");
		}
		if (archetypeIndex == 19)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyNormalHairLongSleeve");
		}
		if (archetypeIndex == 20)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyNormalHairShortSleeve");
		}
		if (archetypeIndex == 21)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyNormalHairLongSleeveShorts");
		}
		if (archetypeIndex == 22)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyNormalHairShortSleeveShorts");
		}
		if (archetypeIndex == 23)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyShortHairLongSleeve");
		}
		if (archetypeIndex == 24)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyShortHairShortSleeve");
		}
		if (archetypeIndex == 25)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyShortHairLongSleeveShorts");
		}
		if (archetypeIndex == 26)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMBoyShortHairShortSleeveShorts");
		}
	}


	if (genderIndex == 1) //female
	{
		isMale = false;
		isFemale = true;

		if (archetypeIndex == 0)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("populargirl");
		}
		if (archetypeIndex == 1)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("hipstergirl");
		}
		if (archetypeIndex == 2)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("gothgirl");
		}
		if (archetypeIndex == 3)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("toughgirl");
		}
		if (archetypeIndex == 4)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("athleticgirl");
		}
		if (archetypeIndex == 5)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("nerdygirl");
		}
		if (archetypeIndex == 6)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("pudgygirl");
		}
		if (archetypeIndex == 7)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("punkgirl");
		}
		if (archetypeIndex == 8)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("skatergirl");
		}
		if (archetypeIndex == 9)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("thuggirl");
		}
		if (archetypeIndex == 10)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("pimplegirl");
		}
		if (archetypeIndex == 11)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlLongHairSkirt");
		}
		if (archetypeIndex == 12)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlLongHairSkirtHalter");
		}
		if (archetypeIndex == 13)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlLongHairJeans");
		}
		if (archetypeIndex == 14)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlLongHairJeansHalter");
		}
		if (archetypeIndex == 15)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlLongHairShortsHalter");
		}
		if (archetypeIndex == 16)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlPonytailSkirt");
		}
		if (archetypeIndex == 17)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlPonytailSkirtHalter");
		}
		if (archetypeIndex == 18)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlPonytailJeans");
		}
		if (archetypeIndex == 19)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlPonytailJeansHalter");
		}
		if (archetypeIndex == 20)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlPonytailShortsHalter");
		}
		if (archetypeIndex == 21)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlShortHairSkirt");
		}
		if (archetypeIndex == 22)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlShortHairSkirtHalter");
		}
		if (archetypeIndex == 23)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlShortHairJeans");
		}
		if (archetypeIndex == 24)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlShortHairJeansHalter");
		}
		if (archetypeIndex == 25)
		{
			sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMGirlShortHairShortsHalter");
		}
	}


	if (sprite != nullptr)
	{
		if (sprite->texture == nullptr)
		{
			sprite->loadTextures();
		}
	}


	this->sprite = sprite;

	setCurrentAnimationBySpriteFrame(getFrame());


	if (uniqueTexture != nullptr)
	{
		uniqueTexture->release();
	}

	int eyeSet = eyeColorIndex + 1;
	int skinSet = skinColorIndex + 1;
	int hairSet = hairColorIndex + 1;
	int shirtSet = shirtColorIndex + 1;
	int pantsSet = pantsColorIndex + 1;
	int shoeSet = shoeColorIndex + 1;

	u8* bb = sprite->createRandomSpriteTextureByteBuffer_S(eyeSet, skinSet, hairSet, shirtSet, pantsSet, shoeSet, -1);

	uniqueTexture = GLUtils::getTextureFromData(string("random") + to_string(Math::randLessThan(500)), sprite->getScreenWidth(), sprite->getScreenHeight() * sprite->getNumFrames(), bb);


	if (this->sprite != nullptr)
	{
		shadowClipPerPixel = new float[sprite->getScreenWidth()];
		for (int i = 0; i < sprite->getScreenWidth(); i++)
		{
			shadowClipPerPixel[i] = 1.0f;
		}
	}
}


//=========================================================================================================================
void Character::setShowName(bool b)
{ //=========================================================================================================================

	showName = b;

	if (getName() != "" && getName().length() > 0)
	{
		setCharacterNameAndCaption(nameColor, getName(), accountTypeNameColor, accountTypeName);
	}
	else
	{
		if (sprite != nullptr && sprite->getDisplayName() != "" && sprite->getDisplayName().length() > 0)
		{
			setCharacterNameAndCaption(nameColor, sprite->getDisplayName(), accountTypeNameColor, accountTypeName);
		}
	}
}

//=========================================================================================================================
void Character::setShowAccountType(bool b)
{ //=========================================================================================================================

	showAccountType = b;

	if (accountTypeName != "")
	{
		if (accountTypeName.length() > 0)
		{
			setCharacterNameAndCaption(nameColor, getName(), accountTypeNameColor, accountTypeName);
		}
	}
}

//=========================================================================================================================
void Character::setCharacterNameAndCaption(BobColor* nameColor, const string& name, BobColor* accountTypeNameColor, const string& accountTypeName)
{ //=========================================================================================================================

	this->nameColor = nameColor;
	this->setName(name);
	this->accountTypeNameColor = accountTypeNameColor;
	this->accountTypeName = accountTypeName;

	if (showName == true)
	{
		if (nameCaption == nullptr)
		{
			if (name != "" && name.length() > 0)
			{
				nameCaption = getCaptionManager()->newManagedCaption(Caption::CENTERED_OVER_ENTITY, 0, -1, name, BobFont::font_normal_16_outlined_smooth, nameColor);
			}
			nameCaption->setEntity(this);
		}
		else
		{
			nameCaption->setText(name);
		}
	}
	else
	{
		if (nameCaption != nullptr)
		{
			nameCaption->setToFadeOutAndBeDeleted();
			nameCaption = nullptr;
		}
	}


	if (showAccountType == true)
	{
		if (accountTypeCaption == nullptr)
		{
			if (accountTypeName != "" && accountTypeName.length() > 0)
			{
				accountTypeCaption = getCaptionManager()->newManagedCaption(Caption::CENTERED_OVER_ENTITY, 0, -1, accountTypeName, BobFont::font_normal_8_outlined, accountTypeNameColor);
			}
			nameCaption->setEntity(this);
		}
		else
		{
			accountTypeCaption->setText(accountTypeName);
		}
	}
	else
	{
		if (accountTypeCaption != nullptr)
		{
			accountTypeCaption->setToFadeOutAndBeDeleted();
			accountTypeCaption = nullptr;
		}
	}
}

//=========================================================================================================================
ArrayList<Entity*>* Character::getOnScreenNonCharacterEntitiesWithinRangeAmount(int amt)
{ //=========================================================================================================================


	ArrayList<Entity*>* list = new ArrayList<Entity*>();

	for (int s = 0; s < (int)getMap()->zList.size(); s++) //NOTICE THIS IS USING ZLIST
	{
		Entity* e = getMap()->zList.get(s);

		if (dynamic_cast<Character*>(e) != NULL || dynamic_cast<RandomCharacter*>(e) != NULL || e->getNonWalkable() == false)
		{
			continue;
		}

		if (e == this)
		{
			continue;
		}


		if (getRight() + amt >= e->getLeft() && getLeft() - amt <= e->getRight() && getBottom() + amt >= e->getTop() && getTop() - amt <= e->getBottom())
		{
			list->add(e);
		}
	}

	return list;
}

//=========================================================================================================================
bool Character::checkTouchingAnyEntityInEntityList(ArrayList<Entity*>* list, float x, float y)
{ //=========================================================================================================================

	if (getEngine()->hitLayerEnabled == false)
	{
		return false;
	}

	for (int s = 0; s < list->size(); s++)
	{
		Entity* e = list->get(s);

		if (dynamic_cast<Character*>(e) != NULL || dynamic_cast<RandomCharacter*>(e) != NULL || e->getNonWalkable() == false)
		{
			continue;
		}

		if (e == this)
		{
			continue;
		}


		if (x >= e->getLeft() && x <= e->getRight() && y >= e->getTop() && y <= e->getBottom())
		{
			return true;
		}
	}

	return false;
}

//=========================================================================================================================
bool Character::checkHitLayerAndTouchingAnyEntityInEntityList(ArrayList<Entity*>* list, float x, float y)
{ //=========================================================================================================================
	if (getMap()->getHitLayerValueAtXYPixels(x, y) == false && checkTouchingAnyEntityInEntityList(list, x, y) == false)
	{
		return false;
	}

	return true;
}

//=========================================================================================================================
bool Character::checkTouchingAnyOnScreenNonCharacterNonWalkableEntities(float x, float y)
{ //=========================================================================================================================

	if (getEngine()->hitLayerEnabled == false)
	{
		return false;
	}

	for (int s = 0; s < (int)getMap()->zList.size(); s++) //NOTICE THIS IS USING ZLIST
	{
		Entity* e = getMap()->zList.get(s);


		if (dynamic_cast<Character*>(e) != NULL || dynamic_cast<RandomCharacter*>(e) != NULL || e->getNonWalkable() == false)
		{
			continue;
		}

		if (e == this)
		{
			continue;
		}


		if (x >= e->getLeft() && x <= e->getRight() && y >= e->getTop() && y <= e->getBottom())
		{
			return true;
		}
	}

	return false;
}

//=========================================================================================================================
void Character::setShadowClip()
{ //=========================================================================================================================
	//check from current tile downwards for any getHit detection
	//if it runs into getHit detection before the shadow length, clip the shadow to % of shadow start to the start of that getHit block / total shadow length


	if (shadowClipPerPixel == nullptr)
	{
		shadowClipPerPixel = new float[sprite->getScreenWidth()];
		for (int i = 0; i < sprite->getScreenWidth(); i++)
		{
			shadowClipPerPixel[i] = 1.0f;
		}
	}

	//float left = getLeft()+2;
	//float right = getRight()-2;
	float bottom = (getY() + (getHeight() * getShadowStart()));
	//float middle = getMiddleX();


	float shadowLength = ((float)(getHeight()) * shadowSize);


	//TODO: add option to put back whole sprite clipping on/off, this is resource intensive.

	//DONE: have function that returns a list of sprites this sprite might be touching. then run through that list, much faster than even just onscreen sprites.
	//also, could render all shadows first, and then sprites, wouldn't have to check against other sprites at all. just run through zlist twice on render.

	//DONE: only do this for onscreen sprites.

	//REALIZATION: i should never have to clip against other entities, ever. your shadow will always be on the ground, and any entities in front of you will always be rendered AFTER your shadow.


	//ArrayList<Entity> list = get_ONSCREEN_entities_besides_characters_within_amt(32);

	for (int x = 0; x < sprite->getScreenWidth(); x++)
	{
		int clip = 0;

		for (int y = 0; y < shadowLength; y++)
		{
			if (getMap()->getHitLayerValueAtXYPixels(getX() + (x * getScale()), bottom + y) == true)
			{
				//check_shadow_clip_hit_layer_xy_and_non_walkable_entities_besides_characters(getX()+(x*getScale),bottom+y)==true
				clip = y;
				y = (int)(shadowLength);
				break;
			}
		}


		if (clip > 0)
		{
			shadowClipPerPixel[x] = ((float)(clip) / (float)(shadowLength));
		}
		else
		{
			shadowClipPerPixel[x] = 1.0f;
		}
	}


	//DONE: i could possibly do this for each horizontal pixel of the shadow and make it totally perfect, definitely do this.
}

//=========================================================================================================================
int Character::walkToXYWithPathFinding(float x, float y)
{ //=========================================================================================================================


	float myX = getRoundedMiddleX();
	float myY = getRoundedMiddleY();


	if (x == -1)
	{
		x = myX;
	}
	if (y == -1)
	{
		y = myY;
	}

	x = round(x);
	y = round(y);


	int there_yet = 0;

	if (finalPathX == x && finalPathY == y)
	{
		return 1;
	}


	//TODO: need to pathfind based on all covered getHit tiles of this sprite.

	//TODO: need to check for characters that are sitting down. otherwise walks through them.

	//TODO: need to send in entire area, try to center self in target area, or just reach closest edge.


	/*
	 * if(myX==x&&myY==y)
	 * {
	 * there_yet=true;
	 * pathPosition=0;
	 * pathfinder=null;
	 * }
	 * else
	 * if(myX>=x-8&&myX<=x+8&&myY>=y-8&&myY<=y+8) //if we're within a tile, just walk straight there.
	 * {
	 * if(walk_to_xy_nohit(x, y))
	 * {
	 * there_yet = true;
	 * pathPosition=0;
	 * pathfinder=null;
	 * }
	 * }
	 * else
	 */


	{
		//if i don't have a pathfinder, make one.


		//walk from path point to path point until i reach my dest.


		if (getMap()->utilityLayersLoaded == false)
		{
			return 0;
		}

		if (pathfinder == nullptr)
		{
			pathfinder = new PathFinder(this, getMiddleX(), getMiddleY(), (float)x, (float)y, getMap()->getWidthTiles1X(), getMap()->getHeightTiles1X());
		}

		if (pathfinder != nullptr)
		{
			if (pathfinder->path != nullptr)
			{
				if (pathPosition < (int)pathfinder->path->pathTiles->size() - 1)
				{
					int pathX = pathfinder->path->getTileXForPathIndex(pathPosition) * 8 * 2 + 8; //+8 for center of tile
					int pathY = pathfinder->path->getTileYForPathIndex(pathPosition) * 8 * 2 + 8;

					//skip tiles that are in a row, starting from the NEXT position
					for (int i = pathPosition + 1; i < (int)pathfinder->path->pathTiles->size(); i++)
					{
						if (pathfinder->path->getTileXForPathIndex(i) * 8 * 2 + 8 == pathX && (i + 1 < (int)pathfinder->path->pathTiles->size()) && pathfinder->path->getTileXForPathIndex(i + 1) * 8 * 2 + 8 == pathX)
						{
							pathfinder->path->pathTiles->erase(pathfinder->path->pathTiles->begin() + i);
						}
						else
						{
							break;
						}
					}

					//skip tiles that are in a column, starting from the NEXT position
					for (int i = pathPosition + 1; i < (int)pathfinder->path->pathTiles->size(); i++)
					{
						if (pathfinder->path->getTileYForPathIndex(i) * 8 * 2 + 8 == pathY && (i + 1 < (int)pathfinder->path->pathTiles->size()) && pathfinder->path->getTileYForPathIndex(i + 1) * 8 * 2 + 8 == pathY)
						{
							pathfinder->path->pathTiles->erase(pathfinder->path->pathTiles->begin() + i);
						}
						else
						{
							break;
						}
					}


					//avoid_nearest_entity(16);

					if (walkToXYNoCheckHit((float)pathX, (float)pathY))
					{
						pathPosition++;
					}
				}
				else if (walkToXYNoCheckHit(x, y)) //for the last step, just walk straight to the destination
				{
					there_yet = 1;
					pathPosition = 0;
					delete pathfinder;
					pathfinder = nullptr;

					finalPathX = x; //we are as close as we can be.
					finalPathY = y;
				}
			}
			else
			{
				pathFindWaitTicks += (int)getEngine()->engineTicksPassed();

				//doStandingAnimation();//should be handled by checkIfMoved and doCharacterAnimation now

				if (pathFindWaitTicks > 500)
				{
					pathFindWaitTicks = 0;

					pathTried++;

					pathPosition = 0;

					delete pathfinder;
					pathfinder = nullptr;

					if (pathTried > 3)
					{
						finalPathX = getMiddleX();
						finalPathY = getMiddleY();

						pathTried = 0;
						return -1;
					}
				}
			}
		}
	}


	//figure out size of hitbox of this sprite in tiles

	//go through map in chunks of this size, staggered by individual tiles


	return there_yet;
}

void Character::checkHitBoxAndWalkDirection(int dir)
{ //=========================================================================================================================

	if (ifCanMoveAPixelThisFrameSubtractAndReturnTrue() == true)
	{
		checkHitBoxAndMovePixelInDirection(dir);

		if (pixelsToWalk > 0 && isWalkingIntoPlayerThisFrame == false)
		{
			pixelsToWalk--;
		}
	}
}

void Character::walkDirectionNoCheckHit(int direction)
{ //=========================================================================================================================

	if (ifCanMoveAPixelThisFrameSubtractAndReturnTrue() == true)
	{
		if (direction == UP)
		{
			setY(getY() - 1);
		}
		if (direction == DOWN)
		{
			setY(getY() + 1);
		}
		if (direction == LEFT)
		{
			setX(getX() - 1);
		}
		if (direction == RIGHT)
		{
			setX(getX() + 1);
		}

		if (pixelsToWalk > 0)
		{
			pixelsToWalk--;
		}

		movementDirection = direction;
	}
}

void Character::walkRandomlyAroundRoomAndStop()
{ //=========================================================================================================================

	if (pixelsToWalk == 0)
	{
		movementDirection = Math::randLessThan(4);
		pixelsToWalk = (Math::randLessThan(100)) + 10;
		//setTicksPerPixelMoved((Math::randLessThan(ticksPerPixel_FASTEST-ticksPerPixel_SLOWEST))+ticksPerPixel_SLOWEST);
	}
	if (pixelsToWalk == 1)
	{
		//setTicksPerPixelMoved((Math::randLessThan(ticksPerPixel_FASTEST-ticksPerPixel_SLOWEST))+ticksPerPixel_SLOWEST);
	}

	if (ifCanMoveAPixelThisFrameSubtractAndReturnTrue() == true)
	{
		checkHitBoxAndMovePixelInDirection(movementDirection);

		if (isWalkingIntoWallThisFrame == true)
		{
			pixelsToWalk = 0;
		}

		if (pixelsToWalk > 0 && isWalkingIntoPlayerThisFrame == false)
		{
			pixelsToWalk--;
		}
	}
}

void Character::walkRandomlyAroundRoom()
{ //=========================================================================================================================

	if (pixelsToWalk == 0)
	{
		movementDirection = Math::randLessThan(4);
		pixelsToWalk = (Math::randLessThan(100)) + 10;
		//setTicksPerPixelMoved((Math::randLessThan(ticksPerPixel_FASTEST-ticksPerPixel_SLOWEST))+ticksPerPixel_SLOWEST);
	}
	checkHitBoxAndWalkDirection(movementDirection);
}

int Character::walkRandomlyWithinXYXY(float x1, float y1, float x2, float y2)
{ //=========================================================================================================================


	if (pixelsToWalk == 0)
	{
		movementDirection = Math::randLessThan(4);

		if ((x2 - x1) > (y2 - y1))
		{
			pixelsToWalk = Math::randLessThan((int)(x2 - x1));
		}
		else
		{
			pixelsToWalk = Math::randLessThan((int)(y2 - y1));
		}
		//setTicksPerPixelMoved((Math::randLessThan(ticksPerPixel_FASTEST-ticksPerPixel_SLOWEST))+ticksPerPixel_SLOWEST);
	}

	int can_walk = 0;


	if (movementDirection == UP && getTop() > y1)
	{
		can_walk = 1;
	}
	if (movementDirection == DOWN && getBottom() < y2)
	{
		can_walk = 1;
	}
	if (movementDirection == LEFT && getLeft() > x1)
	{
		can_walk = 1;
	}
	if (movementDirection == RIGHT && getRight() < x2)
	{
		can_walk = 1;
	}


	if (can_walk == 1)
	{
		walkDirectionAvoidOtherEntities(movementDirection);
	}
	else
	{
		pixelsToWalk = 0;
	}

	if (pixelsToWalk == 0)
	{
		return 1;
	}
	return 0;
}

void Character::twitchAroundRoom()
{ //=========================================================================================================================

	if (pixelsToWalk == 0 || pixelsToWalk > 5)
	{
		movementDirection = Math::randLessThan(4);
		pixelsToWalk = (Math::randLessThan(5)) + 1;
		setTicksPerPixelMoved((float)ticksPerPixel_FAST);
	}

	setIgnoreHitPlayer(true);

	if (ifCanMoveAPixelThisFrameSubtractAndReturnTrue() == true)
	{
		checkHitBoxAndMovePixelInDirection(movementDirection);
		if (isWalkingIntoWallThisFrame == true)
		{
			pixelsToWalk = 0;
		}
		if (pixelsToWalk > 0 && isWalkingIntoPlayerThisFrame == false)
		{
			pixelsToWalk--;
		}
	}

	setIgnoreHitPlayer(false);
}

Character* Character::findNearestCharacter()
{ //=========================================================================================================================

	Character* nearest = nullptr;

	int shortestdist = 65535;


	for (int n = 0; n < (int)getMap()->activeEntityList.size(); n++)
	{
		Entity* currentEntity = getMap()->activeEntityList.get(n);


		if (this != currentEntity &&
			(
				(dynamic_cast<Character*>(currentEntity) != NULL) ||
				(dynamic_cast<Player*>(currentEntity) != NULL) ||
				(dynamic_cast<RandomCharacter*>(currentEntity) != NULL)
			)
		)
		{
			float x = getMiddleX() - (currentEntity->getMiddleX());
			float y = getMiddleY() - (currentEntity->getMiddleY());

			x = abs(x);
			y = abs(y);

			int dist = (int)(sqrt((x * x) + (y * y)));

			if (dist < shortestdist)
			{
				shortestdist = dist;
				nearest = static_cast<Character*>(currentEntity);
			}
		}
	}

	return nearest;
}

int Character::walkToXYLRToUD(float x, float y)
{ //=========================================================================================================================

	//setTicksPerPixelMoved(speed);
	int there_yet = 0;


	if (getMiddleX() < x)
	{
		checkHitBoxAndWalkDirection(RIGHT);
		there_yet = 0;
	}
	else if (getMiddleX() > x)
	{
		checkHitBoxAndWalkDirection(LEFT);
		there_yet = 0;
	}
	else if (getMiddleY() < y)
	{
		checkHitBoxAndWalkDirection(DOWN);
		there_yet = 0;
	}
	else if (getMiddleY() > y)
	{
		checkHitBoxAndWalkDirection(UP);
		there_yet = 0;
	}
	else
	{
		there_yet = 1;
	}

	if (isWalkingIntoWallThisFrame == true)
	{
		if (getMiddleY() < y)
		{
			checkHitBoxAndMovePixelInDirection(DOWN);
			there_yet = 0;
		}
		else if (getMiddleY() > y)
		{
			checkHitBoxAndMovePixelInDirection(UP);
			there_yet = 0;
		}
		else if (getMiddleX() < x)
		{
			checkHitBoxAndMovePixelInDirection(RIGHT);
			there_yet = 0;
		}
		else if (getMiddleX() > x)
		{
			checkHitBoxAndMovePixelInDirection(LEFT);
			there_yet = 0;
		}
	}

	return there_yet;
}

int Character::walkToXYUDToLR(float toX, float toY)
{ //=========================================================================================================================

	//setTicksPerPixelMoved(speed);

	int there_yet = 0;


	if (getMiddleY() < toY)
	{
		checkHitBoxAndWalkDirection(DOWN);
		there_yet = 0;
	}
	else if (getMiddleY() > toY)
	{
		checkHitBoxAndWalkDirection(UP);
		there_yet = 0;
	}
	else if (getMiddleX() < toX)
	{
		checkHitBoxAndWalkDirection(RIGHT);
		there_yet = 0;
	}
	else if (getMiddleX() > toX)
	{
		checkHitBoxAndWalkDirection(LEFT);
		there_yet = 0;
	}
	else
	{
		there_yet = 1;
	}

	if (isWalkingIntoWallThisFrame == true)
	{
		if (getMiddleX() < toX)
		{
			checkHitBoxAndMovePixelInDirection(RIGHT);
			there_yet = 0;
		}
		else if (getMiddleX() > toX)
		{
			checkHitBoxAndMovePixelInDirection(LEFT);
			there_yet = 0;
		}
		else if (getMiddleY() < toY)
		{
			checkHitBoxAndMovePixelInDirection(DOWN);
			there_yet = 0;
		}
		else if (getMiddleY() > toY)
		{
			checkHitBoxAndMovePixelInDirection(UP);
			there_yet = 0;
		}
	}


	return there_yet;
}

bool Character::walkToXYNoCheckHit(float toX, float toY)
{ //=========================================================================================================================

	//this was created for randomcharacters and overrode the old walktoXYNoCheckHit but i moved it into character

	if (toX == -1)
	{
		toX = getRoundedMiddleX();
	}
	if (toY == -1)
	{
		toY = getRoundedMiddleY();
	}

	toX = round(toX);
	toY = round(toY);


	bool there = false;

	if (getRoundedMiddleX() == toX && getRoundedMiddleY() == toY)
	{
		there = true;
	}
	else
	{
		float xDist = abs(getRoundedMiddleX() - toX);
		float yDist = abs(getRoundedMiddleY() - toY);


		int horizontalMovementDir = -1;
		int verticalMovementDir = -1;

		if (getRoundedMiddleX() > toX)
		{
			setX(getX() - pixelsToMoveThisFrame);

			//if i went past it, go exactly to targetX
			if (getRoundedMiddleX() < toX)
			{
				setX(toX - getMiddleOffsetX());
			}

			horizontalMovementDir = LEFT;
		}

		if (getRoundedMiddleX() < toX)
		{
			setX(getX() + pixelsToMoveThisFrame);

			//if i went past it, go exactly to targetX
			if (getRoundedMiddleX() > toX)
			{
				setX(toX - getMiddleOffsetX());
			}

			horizontalMovementDir = RIGHT;
		}


		if (getRoundedMiddleY() > toY)
		{
			setY(getY() - pixelsToMoveThisFrame);

			if (getRoundedMiddleY() < toY)
			{
				setY(toY - getMiddleOffsetY());
			}

			verticalMovementDir = UP;
		}
		if (getRoundedMiddleY() < toY)
		{
			setY(getY() + pixelsToMoveThisFrame);

			if (getRoundedMiddleY() > toY)
			{
				setY(toY - getMiddleOffsetY());
			}

			verticalMovementDir = DOWN;
		}

		if (horizontalMovementDir == LEFT && verticalMovementDir == UP)
		{
			movementDirection = UPLEFT;
		}
		if (horizontalMovementDir == RIGHT && verticalMovementDir == UP)
		{
			movementDirection = UPRIGHT;
		}
		if (horizontalMovementDir == LEFT && verticalMovementDir == DOWN)
		{
			movementDirection = DOWNLEFT;
		}
		if (horizontalMovementDir == RIGHT && verticalMovementDir == DOWN)
		{
			movementDirection = DOWNRIGHT;
		}
		if (horizontalMovementDir == RIGHT && verticalMovementDir == -1)
		{
			movementDirection = RIGHT;
		}
		if (horizontalMovementDir == LEFT && verticalMovementDir == -1)
		{
			movementDirection = LEFT;
		}
		if (horizontalMovementDir == -1 && verticalMovementDir == UP)
		{
			movementDirection = UP;
		}
		if (horizontalMovementDir == -1 && verticalMovementDir == DOWN)
		{
			movementDirection = DOWN;
		}

		if (sprite->getNumberOfAnimations() == 4)
		{
			if (movementDirection == UPLEFT)
			{
				if (xDist > yDist)
				{
					movementDirection = LEFT;
				}
				else
				{
					movementDirection = UP;
				}
			}
			if (movementDirection == UPRIGHT)
			{
				if (xDist > yDist)
				{
					movementDirection = RIGHT;
				}
				else
				{
					movementDirection = UP;
				}
			}
			if (movementDirection == DOWNLEFT)
			{
				if (xDist > yDist)
				{
					movementDirection = LEFT;
				}
				else
				{
					movementDirection = DOWN;
				}
			}
			if (movementDirection == DOWNRIGHT)
			{
				if (xDist > yDist)
				{
					movementDirection = RIGHT;
				}
				else
				{
					movementDirection = DOWN;
				}
			}
		}

		if (pixelsToWalk > 0)
		{
			pixelsToWalk--;
		}


		if (getRoundedMiddleX() == toX && getRoundedMiddleY() == toY)
		{
			there = true;
		}
	}

	return there;
}

bool Character::walkToXYNoCheckHitOLD(float x, float y)
{ //=========================================================================================================================

	setIgnoreHitPlayer(false);


	if (x == -1)
	{
		x = getRoundedMiddleX();
	}
	if (y == -1)
	{
		y = getRoundedMiddleY();
	}

	x = round(x);
	y = round(y);


	bool there_yet = false;

	if (getRoundedMiddleX() == x && getRoundedMiddleY() == y)
	{
		there_yet = true;

		yPixelCounter = 0;
		xPixelCounter = 0;

		//stand();
	}
	else
	{
		int newAnimDir = -1;

		{
			//while(can_walk()==true&&(myX!=x||myY!=y))


			float xdistance = abs(getRoundedMiddleX() - x);
			float ydistance = abs(getRoundedMiddleY() - y);


			if (xdistance >= ydistance)
			{
				if (getRoundedMiddleX() > x)
				{
					setX(getX() - pixelsToMoveThisFrame);

					if (getRoundedMiddleX() < x)
					{
						setX(x - (getMiddleX() - getX()));
					}

					movementDirection = LEFT;
					if (ydistance <= xdistance)
					{
						newAnimDir = LEFT;
					}
				}
				if (getRoundedMiddleX() < x)
				{
					setX(getX() + pixelsToMoveThisFrame);
					if (getRoundedMiddleX() > x)
					{
						setX(x - (getMiddleX() - getX()));
					}
					movementDirection = RIGHT;
					if (ydistance <= xdistance)
					{
						newAnimDir = RIGHT;
					}
				}
			}
			else if (ydistance >= xdistance)
			{
				if (getRoundedMiddleY() > y)
				{
					setY(getY() - pixelsToMoveThisFrame);
					if (getRoundedMiddleY() < y)
					{
						setY(y - (getMiddleY() - getY()));
					}
					movementDirection = UP;
					if (ydistance > xdistance && abs(ydistance - xdistance) > 2)
					{
						newAnimDir = UP;
					}
				}
				if (getRoundedMiddleY() < y)
				{
					setY(getY() + pixelsToMoveThisFrame);
					if (getRoundedMiddleY() > y)
					{
						setY(y - (getMiddleY() - getY()));
					}
					movementDirection = DOWN;
					if (ydistance > xdistance && abs(ydistance - xdistance) > 2)
					{
						newAnimDir = DOWN;
					}
				}
			}


			if (pixelsToWalk > 0)
			{
				pixelsToWalk--;
			}
		}

		if (getRoundedMiddleX() == x && getRoundedMiddleY() == y)
		{
			there_yet = true;
		}
	}
	return there_yet;
}

bool Character::walkToXYUntilHitWall(float x, float y)
{ //=========================================================================================================================

	setIgnoreHitPlayer(false);


	if (x == -1)
	{
		x = getRoundedMiddleX();
	}
	if (y == -1)
	{
		y = getRoundedMiddleY();
	}

	x = round(x);
	y = round(y);


	bool there_yet = false;

	if (getRoundedMiddleX() == x && getRoundedMiddleY() == y)
	{
		there_yet = true;

		yPixelCounter = 0;
		xPixelCounter = 0;

		//stand();
	}
	else
	{
		int newAnimDir = -1;

		{
			//while(can_walk()==true&&(myX!=x||myY!=y))


			float xdistance = abs(getRoundedMiddleX() - x);
			float ydistance = abs(getRoundedMiddleY() - y);


			int moved = 0;

			if (xdistance >= ydistance)
			{
				//setting movementDirection here is useless.
				if (getRoundedMiddleX() > x)
				{
					while (pixelsToMoveThisFrame > 1.0f)
					{
						pixelsToMoveThisFrame -= 1.0f;
						if (checkHitBoxAndMovePixelInDirection(LEFT))
						{
							moved++;
						}
					}

					setX(getX() - pixelsToMoveThisFrame);
					if (getRoundedMiddleX() < x)
					{
						setX(x - (getMiddleX() - getX())); //if we overshot the goal, rewind.
					}


					movementDirection = LEFT;
					if (ydistance <= xdistance)
					{
						newAnimDir = LEFT;
					}
				}


				if (getRoundedMiddleX() < x)
				{
					while (pixelsToMoveThisFrame > 1.0f)
					{
						pixelsToMoveThisFrame -= 1.0f;
						if (checkHitBoxAndMovePixelInDirection(RIGHT))
						{
							moved++;
						}
					}

					setX(getX() + pixelsToMoveThisFrame);
					if (getRoundedMiddleX() > x)
					{
						setX(x - (getMiddleX() - getX()));
					}

					movementDirection = RIGHT;
					if (ydistance <= xdistance)
					{
						newAnimDir = RIGHT;
					}
				}
			}
			else if (ydistance >= xdistance)
			{
				if (getRoundedMiddleY() > y)
				{
					while (pixelsToMoveThisFrame > 1.0f)
					{
						pixelsToMoveThisFrame -= 1.0f;
						if (checkHitBoxAndMovePixelInDirection(UP))
						{
							moved++;
						}
					}

					setY(getY() - pixelsToMoveThisFrame);
					if (getRoundedMiddleY() < y)
					{
						setY(y - (getMiddleY() - getY()));
					}

					movementDirection = UP;
					if (ydistance > xdistance && abs(ydistance - xdistance) > 2)
					{
						newAnimDir = UP;
					}
				}


				if (getRoundedMiddleY() < y)
				{
					while (pixelsToMoveThisFrame > 1.0f)
					{
						pixelsToMoveThisFrame -= 1.0f;
						if (checkHitBoxAndMovePixelInDirection(DOWN))
						{
							moved++;
						}
					}

					setY(getY() + pixelsToMoveThisFrame);
					if (getRoundedMiddleY() > y)
					{
						setY(y - (getMiddleY() - getY()));
					}

					movementDirection = DOWN;
					if (ydistance > xdistance && abs(ydistance - xdistance) > 2)
					{
						newAnimDir = DOWN;
					}
				}
			}


			if (pixelsToWalk > 0)
			{
				pixelsToWalk--;
			}
		}

		if (getRoundedMiddleX() == x && getRoundedMiddleY() == y)
		{
			there_yet = true;
		}

		if (moved == false)
		{
			there_yet = true;
		}
	}
	return there_yet;
}

int Character::walkToXYWithBasicHitCheck(float x, float y)
{ //=========================================================================================================================

	setIgnoreHitPlayer(true);


	if (x == -1)
	{
		x = getMiddleX();
	}
	if (y == -1)
	{
		y = getMiddleY();
	}

	int there_yet = 0;
	int direction = 0;

	if (ifCanMoveAPixelThisFrameSubtractAndReturnTrue() == true)
	{
		//WALK PERFECT DIAGONAL

		float ydistance = 0;
		float xdistance = 0;
		if (getMiddleY() > y)
		{
			ydistance = getMiddleY() - y;
		}
		if (getMiddleY() < y)
		{
			ydistance = y - getMiddleY();
		}

		if (getMiddleX() > x)
		{
			xdistance = getMiddleX() - x;
		}
		if (getMiddleX() < x)
		{
			xdistance = x - getMiddleX();
		}


		float x_to_y_ratio = 0;
		if (ydistance != 0)
		{
			x_to_y_ratio = xdistance / ydistance;
		}
		float y_to_x_ratio = 0;
		if (xdistance != 0)
		{
			y_to_x_ratio = ydistance / xdistance;
		}


		if (xdistance >= ydistance || y_to_x_ratio < yPixelCounter)
		{
			if (getMiddleX() > x)
			{
				mapX--;
				if (isWalkingIntoWallThisFrame == false && ydistance <= xdistance)
				{
					direction = LEFT;
				}
			}
			if (getMiddleX() < x)
			{
				mapX++;
				if (isWalkingIntoWallThisFrame == false && ydistance <= xdistance)
				{
					direction = RIGHT;
				}
			}
			xPixelCounter++;
			yPixelCounter = 0;
		}

		if (ydistance >= xdistance || x_to_y_ratio < xPixelCounter)
		{
			if (getMiddleY() > y)
			{
				mapY--;
				if (ydistance > xdistance)
				{
					direction = UP;
				}
			}
			if (getMiddleY() < y)
			{
				mapY++;
				if (ydistance > xdistance)
				{
					direction = DOWN;
				}
			}
			yPixelCounter++;
			xPixelCounter = 0;
		}


		if (pixelsToWalk > 0 && isWalkingIntoPlayerThisFrame == false)
		{
			pixelsToWalk--;
		}
	}

	if (getMiddleX() == x && getMiddleY() == y)
	{
		there_yet = 1;

		yPixelCounter = 0;
		xPixelCounter = 0;
	}

	return there_yet;
}

int Character::walkToXYNoHitAvoidOthersPushMain(float x, float y)
{ //=========================================================================================================================

	if (getPlayer() == nullptr)
	{
		log.error("Player null in walk_to_xy_nohit_avoidothers_pushmain()");
		return 0;
	}


	setIgnoreHitPlayer(true);


	int there_yet = 0;

	float myX = getRoundedMiddleX();
	float myY = getRoundedMiddleY();

	x = round(x);
	y = round(y);

	if (x == -1)
	{
		x = myX;
	}
	if (y == -1)
	{
		y = myY;
	}

	if (myX == x && myY == y)
	{
		there_yet = 1;
	}
	else
	{
		if (ifCanMoveAPixelThisFrameSubtractAndReturnTrue() == true)
		{
			Character* nearestentity = findNearestCharacter();


			int collide = 0;
			int hitPlayer = 0;

			//WALK PERFECT DIAGONAL
			float xdistance = abs(myX - x);
			float ydistance = abs(myY - y);


			float x_to_y_ratio = 0;
			if (ydistance != 0)
			{
				x_to_y_ratio = xdistance / ydistance;
			}

			float y_to_x_ratio = 0;
			if (xdistance != 0)
			{
				y_to_x_ratio = ydistance / xdistance;
			}


			if (ydistance >= xdistance || x_to_y_ratio < xPixelCounter) //walk the greater distance first, up/down vs hitBoxLeft()/hitBoxRight()
			{
				if (myY < y) //walking down
				{
					if (isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity, 12) == true)
					{
						if (nearestentity == getPlayer())
						{
							hitPlayer = 1;
						}
						//else
						if ((animationDirection == UP && nearestentity->getMiddleY() <= getMiddleY()) || (animationDirection == DOWN && nearestentity->getMiddleY() >= getMiddleY()))
						{
							if (animationDirection != nearestentity->animationDirection || getTicksPerPixelMoved() <= nearestentity->getTicksPerPixelMoved())
							{
								if (myX < nearestentity->getMiddleX())
								{
									setX(getX() - 1);
									collide = 1;
								}
								else
								{
									setX(getX() + 1);
									collide = 1;
								}
							}
						}
					}
					{
						//else
						mapY++;
						yPixelCounter++;
						xPixelCounter = 0;
						standing_cycles = 0;
					}
				}
				if (myY > y)
				{
					if (isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity, 13) == true)
					{
						if (nearestentity == getPlayer())
						{
							hitPlayer = 1;
						}
						//else
						if ((animationDirection == UP && nearestentity->getMiddleY() <= getMiddleY()) || (animationDirection == DOWN && nearestentity->getMiddleY() >= getMiddleY()))
						{
							if (animationDirection != nearestentity->animationDirection || getTicksPerPixelMoved() <= nearestentity->getTicksPerPixelMoved())
							{
								//if(standing_cycles==0&&nearestentity->standing_cycles==0)
								if (myX <= nearestentity->getMiddleX())
								{
									setX(getX() - 1);
									collide = 1;
								} //else walk hitBoxLeft() if slightly hitBoxLeft()
								else
								{
									setX(getX() + 1);
									collide = 1;
								} //else walk hitBoxRight()
							}
						}
					}
					{
						//else
						mapY--;
						yPixelCounter++;
						xPixelCounter = 0;
						standing_cycles = 0;
					}
				}
			}

			if (xdistance >= ydistance || y_to_x_ratio < yPixelCounter)
			{
				if (myX < x)
				{
					if (isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity, 12) == true)
					{
						if (nearestentity == getPlayer())
						{
							hitPlayer = 1;
						}
						//else
						if ((animationDirection == LEFT && nearestentity->getMiddleX() <= getMiddleX()) || (animationDirection == RIGHT && nearestentity->getMiddleX() >= getMiddleX()))
						{
							if (animationDirection != nearestentity->animationDirection || getTicksPerPixelMoved() <= nearestentity->getTicksPerPixelMoved())
							{
								//if(standing_cycles==0&&nearestentity->standing_cycles==0)
								if (getMiddleY() < nearestentity->getMiddleY())
								{
									setY(getY() - 1);
									collide = 1;
								} //else walk up if slightly above
								else
								{
									setY(getY() + 1);
									collide = 1;
								} //else walk down
							}
						}
					}
					{
						//else

						mapX++;
						xPixelCounter++;
						yPixelCounter = 0;
						standing_cycles = 0;
					}
				}


				if (myX > x)
				{
					if (isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity, 13) == true)
					{
						if (nearestentity == getPlayer())
						{
							hitPlayer = 1;
						}
						//else
						if ((animationDirection == LEFT && nearestentity->getMiddleX() <= getMiddleX()) || (animationDirection == RIGHT && nearestentity->getMiddleX() >= getMiddleX()))
						{
							if (animationDirection != nearestentity->animationDirection || getTicksPerPixelMoved() <= nearestentity->getTicksPerPixelMoved())
							{
								//if(standing_cycles==0&&nearestentity->standing_cycles==0)
								if (getMiddleY() <= nearestentity->getMiddleY())
								{
									setY(getY() - 1);
									collide = 1;
								} //else walk up if slightly above
								else
								{
									setY(getY() + 1);
									collide = 1;
								} //else walk down
							}
						}
					}
					{
						//else
						mapX--;
						xPixelCounter++;
						yPixelCounter = 0;
						standing_cycles = 0;
					}
				}
			}

			if (collide == 1)
			{
				if (nearestentity->animationDirection == animationDirection && nearestentity->getTicksPerPixelMoved() == getTicksPerPixelMoved())
				{
					//walking_speed+=GLOBALSPEED*1;
				}
			}

			if (hitPlayer == 1)
			{
				float nx = getMiddleX();
				float ny = getMiddleY();
				float sx = nearestentity->getMiddleX();
				float sy = nearestentity->getMiddleY();

				int wd = nearestentity->movementDirection;

				if (nx > sx && ny < sy)
				{
					wd = (DOWNLEFT);
				}
				else if (nx < sx && ny < sy)
				{
					wd = (DOWNRIGHT);
				}
				else if (ny > sy && nx > sx)
				{
					wd = (UPLEFT);
				}
				else if (ny > sy && nx < sx)
				{
					wd = (UPRIGHT);
				}
				else if (nx > sx)
				{
					wd = (LEFT);
				}
				else if (nx < sx)
				{
					wd = (RIGHT);
				}
				else if (ny > sy)
				{
					wd = (UP);
				}
				else if (ny < sy)
				{
					wd = (DOWN);
				}

				//nearestentity->ms=nearestentity->walking_speed*2;
				//PLAYER_check_hit_move_pixel_animate(wd);
				//nearestentity->animateInDirection(wd);
			}

			if (pixelsToWalk > 0 && isWalkingIntoPlayerThisFrame == false)
			{
				pixelsToWalk--;
			}
		}
	}
	return there_yet;
}

int Character::walkToXYStopForOtherEntitiesWithinAmt(float x, float y, int amt)
{ //=========================================================================================================================

	setIgnoreHitPlayer(true);
	//setTicksPerPixelMoved(speed);

	int there_yet = 0;


	if (x == -1)
	{
		x = getMiddleX();
	}
	if (y == -1)
	{
		y = getMiddleY();
	}

	if (getMiddleX() == x && getMiddleY() == y)
	{
		there_yet = 1;
	}
	else
	{
		if (ifCanMoveAPixelThisFrameSubtractAndReturnTrue() == true)
		{
			Entity* n = findNearestEntity();

			/*
			 * if(nearest_entity!=null)
			 * {
			 * if(standing_cycles!=0)
			 * {
			 * nearestentity=(NPC*)nearest_entity;
			 * standing_cycles--;
			 * }
			 * else
			 * {
			 * nearest_entity=(struct NPC*)nearestentity;
			 * standing_cycles=FileUtils::r(10);
			 * }
			 * }
			 * else
			 * {
			 * nearest_entity=(struct NPC*)nearestentity;
			 * nearestentity=(NPC*)nearest_entity;
			 * }
			 */


			//WALK PERFECT DIAGONAL

			float ydistance = 0;
			float xdistance = 0;
			if (getMiddleY() > y)
			{
				ydistance = getMiddleY() - y;
			}
			if (getMiddleY() < y)
			{
				ydistance = y - getMiddleY();
			}

			if (getMiddleX() > x)
			{
				xdistance = getMiddleX() - x;
			}
			if (getMiddleX() < x)
			{
				xdistance = x - getMiddleX();
			}


			float x_to_y_ratio = 0;
			if (ydistance != 0)
			{
				x_to_y_ratio = xdistance / ydistance;
			}

			float y_to_x_ratio = 0;
			if (xdistance != 0)
			{
				y_to_x_ratio = ydistance / xdistance;
			}


			if (ydistance >= xdistance || x_to_y_ratio < xPixelCounter) //walk the greater distance first, up/down vs hitBoxLeft()/hitBoxRight()
			{
				if (getMiddleY() < y) //walking down
				{
					if (!(((getLeft() >= n->getLeft() && getLeft() <= n->getRight()) || (getRight() >= n->getLeft() && getRight() <= n->getRight()) || (n->getLeft() >= getLeft() && n->getLeft() <= getRight()) || (n->getRight() >= getLeft() && n->getRight() <= getRight())) && (getBottom() <= n->getTop()) && (getBottom() >= n->getTop() - amt)))
					{
						mapY++;
						yPixelCounter++;
						xPixelCounter = 0;
						standing_cycles = 0;
					}
				}

				if (getMiddleY() > y) //walking up
				{
					if (!(((getLeft() >= n->getLeft() && getLeft() <= n->getRight()) || (getRight() >= n->getLeft() && getRight() <= n->getRight()) || (n->getLeft() >= getLeft() && n->getLeft() <= getRight()) || (n->getRight() >= getLeft() && n->getRight() <= getRight())) && (getTop() >= n->getBottom()) && (getTop() <= n->getBottom() + amt)))
					{
						mapY--;
						yPixelCounter++;
						xPixelCounter = 0;
						standing_cycles = 0;
					}
				}
			}


			if (xdistance >= ydistance || y_to_x_ratio < yPixelCounter)
			{
				if (getMiddleX() < x) //moving hitBoxRight()
				{
					if (!(((getTop() >= n->getTop() && getTop() <= n->getBottom()) || (getBottom() >= n->getTop() && getBottom() <= n->getBottom())) && (getRight() <= n->getLeft()) && (getRight() >= n->getLeft() - amt)))
					{
						mapX++;
						xPixelCounter++;
						yPixelCounter = 0;
						standing_cycles = 0;
					}
				}


				if (getMiddleX() > x)
				{
					if (!(((getTop() >= n->getTop() && getTop() <= n->getBottom()) || (getBottom() >= n->getTop() && getBottom() <= n->getBottom())) && (getLeft() >= n->getRight()) && (getLeft() <= n->getRight() + amt)))
					{
						mapX--;
						xPixelCounter++;
						yPixelCounter = 0;
						standing_cycles = 0;
					}
				}
			}


			if (pixelsToWalk > 0 && isWalkingIntoPlayerThisFrame == false)
			{
				pixelsToWalk--;
			}
		}
	}
	return there_yet;
}

void Character::walkDirectionAvoidOtherEntities(int direction)
{ //=========================================================================================================================

	if (ifCanMoveAPixelThisFrameSubtractAndReturnTrue() == true)
	{
		Entity* n = findNearestEntity();

		if (direction == DOWN)
		{
			if (isEntityHitBoxTouchingMyHitBoxByAmount(n, 8 + Math::randLessThan(6)) == true)
			{
				if (getMiddleX() <= n->getMiddleX())
				{
					setX(getX() - Math::randLessThan(2));
				}
				else
				{
					setX(getX() + Math::randLessThan(2));
				}
			}
			else
			{
				checkHitBoxAndMovePixelInDirection(DOWN);
			}
			direction = DOWN;
		}

		if (direction == UP)
		{
			if (isEntityHitBoxTouchingMyHitBoxByAmount(n, 8 + Math::randLessThan(6)) == true)
			{
				if (getMiddleX() < n->getMiddleX())
				{
					setX(getX() - Math::randLessThan(2)); //else walk hitBoxLeft() if slightly hitBoxLeft()
				}
				else
				{
					setX(getX() + Math::randLessThan(2)); //else walk hitBoxRight()
				}
			}
			else
			{
				checkHitBoxAndMovePixelInDirection(UP);
			}
			direction = UP;
		}

		if (direction == RIGHT)
		{
			if (isEntityHitBoxTouchingMyHitBoxByAmount(n, 8 + Math::randLessThan(6)) == true)
			{
				if (getMiddleY() <= n->getMiddleY())
				{
					setY(getY() - Math::randLessThan(2)); //else walk up if slightly above
				}
				else
				{
					setY(getY() + Math::randLessThan(2)); //else walk down
				}
			}
			else
			{
				checkHitBoxAndMovePixelInDirection(RIGHT);
			}
			direction = RIGHT;
		}

		if (direction == LEFT)
		{
			if (isEntityHitBoxTouchingMyHitBoxByAmount(n, 8 + Math::randLessThan(6)) == true)
			{
				if (getMiddleY() < n->getMiddleY())
				{
					setY(getY() - Math::randLessThan(2)); //else walk up if slightly above
				}
				else
				{
					setY(getY() + Math::randLessThan(2)); //else walk down
				}
			}
			else
			{
				checkHitBoxAndMovePixelInDirection(LEFT);
			}
			direction = LEFT;
		}


		if (pixelsToWalk > 0 && isWalkingIntoPlayerThisFrame == false)
		{
			pixelsToWalk--;
		}

		movementDirection = direction;
	}
}

bool Character::walkToXYIntelligentHitPushOthers(float x, float y)
{ //=========================================================================================================================

	if (getPlayer() == nullptr)
	{
		log.error("Player null in walk_to_xy_intelligenthit_pushothers()");
		return false;
	}


	setIgnoreHitPlayer(true);

	bool there_yet = false;


	if (x == -1)
	{
		x = getMiddleX();
	}
	if (y == -1)
	{
		y = getMiddleY();
	}


	if (getMiddleX() == x && getMiddleY() == y)
	{
		there_yet = true;
	}
	else
	{
		if (ifCanMoveAPixelThisFrameSubtractAndReturnTrue() == true)
		{
			float xdistance = getMiddleX() - x;
			float ydistance = getMiddleY() - y;

			if (xdistance < 0)
			{
				xdistance *= -1;
			}
			if (ydistance < 0)
			{
				ydistance *= -1;
			}

			int direction = 0;


			Entity* n = findNearestEntity();


			if (ydistance >= xdistance) //walk the greater distance first, up/down vs hitBoxLeft()/hitBoxRight()
			{
				if (getMiddleY() < y)
				{
					if (isEntityHitBoxTouchingMyHitBoxByAmount(n, 7) == true)
					{
						if (n == getPlayer())
						{
							if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN) == false)
							{
								getPlayer()->mapY++;
							}

							if (getMiddleX() < getPlayer()->getMiddleX())
							{
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT) == false)
								{
									getPlayer()->mapX++;
								}
							}
							else
							{
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT) == false)
								{
									getPlayer()->mapX--;
								}
							}
						}
						else
						{
							n->checkHitBoxAndMovePixelInDirection(DOWN);

							if (getMiddleX() <= n->getMiddleX())
							{
								n->checkHitBoxAndMovePixelInDirection(RIGHT);
							}
							else
							{
								n->checkHitBoxAndMovePixelInDirection(LEFT);
							}
						}
						direction = DOWN;
					}


					if (checkHitBoxAndMovePixelInDirection(DOWN) == false || isEntityHitBoxTouchingMyHitBoxByAmount(n, 7) == true)
					{
						if (movementDirection != LEFT && movementDirection != RIGHT)
						{
							if (Math::randLessThan(2) == 0)
							{
								movementDirection = LEFT;
							}
							else
							{
								movementDirection = RIGHT;
							}
						}
					}
					else
					{
						movementDirection = 4;
						direction = DOWN;
					}
				}

				///======
				///======
				///======
				///======


				if (getMiddleY() > y)
				{
					if (isEntityHitBoxTouchingMyHitBoxByAmount(n, 7) == true)
					{
						if (n == getPlayer())
						{
							if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP) == false)
							{
								getPlayer()->mapY--;
							}

							if (getMiddleX() < getPlayer()->getMiddleX())
							{
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT) == false)
								{
									getPlayer()->mapX++;
								}
							}
							else
							{
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT) == false)
								{
									getPlayer()->mapX--;
								}
							}
						}
						else
						{
							n->checkHitBoxAndMovePixelInDirection(UP);

							if (getMiddleX() < n->getMiddleX())
							{
								n->checkHitBoxAndMovePixelInDirection(RIGHT);
							}
							else
							{
								n->checkHitBoxAndMovePixelInDirection(LEFT);
							}
						}

						direction = UP;
					}

					{
						if (checkHitBoxAndMovePixelInDirection(UP) == false || isEntityHitBoxTouchingMyHitBoxByAmount(n, 7) == true)
						{
							if (movementDirection != LEFT && movementDirection != RIGHT)
							{
								if (Math::randLessThan(2) == 0)
								{
									movementDirection = LEFT;
								}
								else
								{
									movementDirection = RIGHT;
								}
							}
						}
						else
						{
							movementDirection = 4;
							direction = UP;
						}
					}
				}
			}
			///===========================================
			if (xdistance > ydistance)
			{
				if (getMiddleX() < x)
				{
					if (isEntityHitBoxTouchingMyHitBoxByAmount(n, 7) == true)
					{
						if (n == getPlayer())
						{
							if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT) == false)
							{
								n->mapX++;
							}

							if (getMiddleY() > getPlayer()->getMiddleY())
							{
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP) == false)
								{
									n->mapY--;
								}
							}
							else
							{
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN) == false)
								{
									n->mapY++;
								}
							}
						}
						else
						{
							n->checkHitBoxAndMovePixelInDirection(RIGHT);

							if (getMiddleY() >= n->getMiddleY())
							{
								n->checkHitBoxAndMovePixelInDirection(UP);
							}
							else
							{
								n->checkHitBoxAndMovePixelInDirection(DOWN);
							}
						}

						direction = RIGHT;
					}

					{
						if (checkHitBoxAndMovePixelInDirection(RIGHT) == false || isEntityHitBoxTouchingMyHitBoxByAmount(n, 7) == true)
						{
							if (movementDirection != UP && movementDirection != DOWN)
							{
								if (Math::randLessThan(2) == 0)
								{
									movementDirection = UP;
								}
								else
								{
									movementDirection = DOWN;
								}
							}
						}
						else
						{
							movementDirection = 4;
							direction = RIGHT;
						}
					}
				}

				if (getMiddleX() > x)
				{
					if (isEntityHitBoxTouchingMyHitBoxByAmount(n, 7) == true)
					{
						if (n == getPlayer())
						{
							//push main sprite hitBoxLeft()
							if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT) == false)
							{
								n->mapX--;
							}

							if (getMiddleY() >= n->getMiddleY())
							{ //push main sprite up
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP) == false)
								{
									n->mapY--;
								}
							}
							else
							{ //push main sprite down
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN) == false)
								{
									n->mapY++;
								}
							}
						}
						else
						{
							n->checkHitBoxAndMovePixelInDirection(LEFT);

							if (getMiddleY() > n->getMiddleY())
							{
								n->checkHitBoxAndMovePixelInDirection(UP);
							}
							else
							{
								n->checkHitBoxAndMovePixelInDirection(DOWN);
							}
						}

						direction = LEFT;
					}

					{
						if (checkHitBoxAndMovePixelInDirection(LEFT) == false || isEntityHitBoxTouchingMyHitBoxByAmount(n, 7) == true)
						{
							if (movementDirection != UP && movementDirection != DOWN)
							{
								if (Math::randLessThan(2) == 0)
								{
									movementDirection = UP;
								}
								else
								{
									movementDirection = DOWN;
								}
							}
						}
						else
						{
							movementDirection = 4;
							direction = LEFT;
						}
					}
				}
			}

			if (movementDirection == UP)
			{
				if (checkHitBoxAndMovePixelInDirection(UP) == false || isEntityHitBoxTouchingMyHitBoxByAmount(n, 10 + Math::randLessThan(6)) == true)
				{
					movementDirection = 4;
				}
				else
				{
					direction = UP;
				}
			}
			else if (movementDirection == DOWN)
			{
				if (checkHitBoxAndMovePixelInDirection(DOWN) == false || isEntityHitBoxTouchingMyHitBoxByAmount(n, 10 + Math::randLessThan(6)) == true)
				{
					movementDirection = 4;
				}
				else
				{
					direction = DOWN;
				}
			}
			else if (movementDirection == LEFT)
			{
				if (checkHitBoxAndMovePixelInDirection(LEFT) == false || isEntityHitBoxTouchingMyHitBoxByAmount(n, 10 + Math::randLessThan(6)) == true)
				{
					movementDirection = 4;
				}
				else
				{
					direction = LEFT;
				}
			}
			else if (movementDirection == RIGHT)
			{
				if (checkHitBoxAndMovePixelInDirection(RIGHT) == false || isEntityHitBoxTouchingMyHitBoxByAmount(n, 10 + Math::randLessThan(6)) == true)
				{
					movementDirection = 4;
				}
				else
				{
					direction = RIGHT;
				}
			}


			if (pixelsToWalk > 0 && isWalkingIntoPlayerThisFrame == false)
			{
				pixelsToWalk--;
			}
		}
	}
	return there_yet;
}

bool Character::walkToXYIntelligentHitAvoidOthers(float x, float y)
{ //=========================================================================================================================

	setIgnoreHitPlayer(true);
	//setTicksPerPixelMoved(speed);

	bool there_yet = false;
	int avoided = 0;


	if (x == -1)
	{
		x = getMiddleX();
	}
	if (y == -1)
	{
		y = getMiddleY();
	}

	if (getMiddleX() == x && getMiddleY() == y)
	{
		there_yet = true;
	}
	else
	{
		if (ifCanMoveAPixelThisFrameSubtractAndReturnTrue() == true)
		{
			float xdistance = getMiddleX() - x;
			float ydistance = getMiddleY() - y;

			if (xdistance < 0)
			{
				xdistance *= -1;
			}
			if (ydistance < 0)
			{
				ydistance *= -1;
			}

			int direction = 0;
			Entity* nearestentity = findNearestEntity();

			if (ydistance >= xdistance) //walk the greater distance first, up/down vs hitBoxLeft()/hitBoxRight()
			{
				if (getMiddleY() < y)
				{
					if (isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity, 10 + Math::randLessThan(6)) == true)
					{
						{
							avoided = Math::randLessThan(2);
							if (getMiddleX() <= nearestentity->getMiddleX())
							{
								if (avoided == 1)
								{
									checkHitBoxAndMovePixelInDirection(LEFT);
								}
								movementDirection = 4;
							}
							else
							{
								if (avoided == 1)
								{
									checkHitBoxAndMovePixelInDirection(RIGHT);
								}
								movementDirection = 4;
							}
						}
						direction = DOWN;
					}

					if (avoided == 0)
					{
						if (checkHitBoxAndMovePixelInDirection(DOWN) == false)
						{
							if (movementDirection != LEFT && movementDirection != RIGHT)
							{
								if (Math::randLessThan(2) == 0)
								{
									movementDirection = LEFT;
								}
								else
								{
									movementDirection = RIGHT;
								}
							}
						}
						else
						{
							movementDirection = 4;
							direction = DOWN;
						}
					}
				}
				avoided = 0;
				if (getMiddleY() > y)
				{
					if (isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity, 10 + Math::randLessThan(6)) == true)
					{
						{
							avoided = Math::randLessThan(2);
							if (getMiddleX() < nearestentity->getMiddleX())
							{
								if (avoided == 1)
								{
									checkHitBoxAndMovePixelInDirection(LEFT); //else walk hitBoxLeft() if slightly hitBoxLeft()
								}
								movementDirection = 4;
							}
							else
							{
								if (avoided == 1)
								{
									checkHitBoxAndMovePixelInDirection(RIGHT); //else walk hitBoxRight()
								}
								movementDirection = 4;
							}
						}
						direction = UP;
					}

					if (avoided == 0)
					{
						if (checkHitBoxAndMovePixelInDirection(UP) == false)
						{
							if (movementDirection != LEFT && movementDirection != RIGHT)
							{
								if (Math::randLessThan(2) == 0)
								{
									movementDirection = LEFT;
								}
								else
								{
									movementDirection = RIGHT;
								}
							}
						}
						else
						{
							movementDirection = 4;
							direction = UP;
						}
					}
				}
				avoided = 0;
			}

			if (xdistance > ydistance)
			{
				if (getMiddleX() < x)
				{
					if (isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity, 10 + Math::randLessThan(6)) == true)
					{
						{
							avoided = Math::randLessThan(2);
							if (getMiddleY() <= nearestentity->getMiddleY())
							{
								if (avoided == 1)
								{
									checkHitBoxAndMovePixelInDirection(UP); //else walk up if slightly above
								}
								movementDirection = 4;
							}
							else
							{
								if (avoided == 1)
								{
									checkHitBoxAndMovePixelInDirection(DOWN); //else walk down
								}
								movementDirection = 4;
							}
						}
						direction = RIGHT;
					}

					if (avoided == 0)
					{
						if (checkHitBoxAndMovePixelInDirection(RIGHT) == false)
						{
							if (movementDirection != UP && movementDirection != DOWN)
							{
								if (Math::randLessThan(2) == 0)
								{
									movementDirection = UP;
								}
								else
								{
									movementDirection = DOWN;
								}
							}
						}
						else
						{
							movementDirection = 4;
							direction = RIGHT;
						}
					}
				}
				avoided = 0;
				if (getMiddleX() > x)
				{
					if (isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity, 10 + Math::randLessThan(6)) == true)
					{
						{
							avoided = Math::randLessThan(2);
							if (getMiddleY() < nearestentity->getMiddleY())
							{
								if (avoided == 1)
								{
									checkHitBoxAndMovePixelInDirection(UP); //else walk up if slightly above
								}
								movementDirection = 4;
							}
							else
							{
								if (avoided == 1)
								{
									checkHitBoxAndMovePixelInDirection(DOWN); //else walk down
								}
								movementDirection = 4;
							}
						}
						direction = LEFT;
					}

					if (avoided == 0)
					{
						if (checkHitBoxAndMovePixelInDirection(LEFT) == false)
						{
							if (movementDirection != UP && movementDirection != DOWN)
							{
								if (Math::randLessThan(2) == 0)
								{
									movementDirection = UP;
								}
								else
								{
									movementDirection = DOWN;
								}
							}
						}
						else
						{
							movementDirection = 4;
							direction = LEFT;
						}
					}
				}
			}

			if (movementDirection == UP)
			{
				if (checkHitBoxAndMovePixelInDirection(UP) == false || isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity, 10 + Math::randLessThan(6)) == true)
				{
					movementDirection = 4;
				}
				else
				{
					direction = UP;
				}
			}
			else if (movementDirection == DOWN)
			{
				if (checkHitBoxAndMovePixelInDirection(DOWN) == false || isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity, 10 + Math::randLessThan(6)) == true)
				{
					movementDirection = 4;
				}
				else
				{
					direction = DOWN;
				}
			}
			else if (movementDirection == LEFT)
			{
				if (checkHitBoxAndMovePixelInDirection(LEFT) == false || isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity, 10 + Math::randLessThan(6)) == true)
				{
					movementDirection = 4;
				}
				else
				{
					direction = LEFT;
				}
			}
			else if (movementDirection == RIGHT)
			{
				if (checkHitBoxAndMovePixelInDirection(RIGHT) == false || isEntityHitBoxTouchingMyHitBoxByAmount(nearestentity, 10 + Math::randLessThan(6)) == true)
				{
					movementDirection = 4;
				}
				else
				{
					direction = RIGHT;
				}
			}


			if (pixelsToWalk > 0 && isWalkingIntoPlayerThisFrame == false)
			{
				pixelsToWalk--;
			}
		}
	}
	return there_yet;
}

int Character::walk_to_xy_intelligenthit_stopforothers_pushmain(float x, float y)
{ //=========================================================================================================================


	if (getPlayer() == nullptr)
	{
		log.error("Player null in walk_to_xy_intelligenthit_stopforothers_pushmain()");
		return 0;
	}


	setIgnoreHitPlayer(true);
	//setTicksPerPixelMoved(speed);


	if (x == -1)
	{
		x = getMiddleX();
	}
	if (y == -1)
	{
		y = getMiddleY();
	}

	int there_yet = 0;
	int noanim = 0;

	if (getMiddleX() == x && getMiddleY() == y)
	{
		there_yet = 1;
	}
	else
	{
		if (ifCanMoveAPixelThisFrameSubtractAndReturnTrue() == true)
		{
			float xdistance = getMiddleX() - x;
			float ydistance = getMiddleY() - y;

			if (xdistance < 0)
			{
				xdistance *= -1;
			}
			if (ydistance < 0)
			{
				ydistance *= -1;
			}

			int direction = 0;

			Entity* n = findNearestEntity();

			if (ydistance >= xdistance) //walk the greater distance first, up/down vs hitBoxLeft()/hitBoxRight()
			{
				if (getMiddleY() < y)
				{
					if (isHitBoxTouchingEntityInDirectionByAmount(n, DOWN, 5) == true && (getX() != n->getX() || getY() != n->getY()))
					{
						if (n == getPlayer())
						{
							//push main sprite down
							if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN) == false)
							{
								n->mapY++;
							}

							if (getMiddleX() < n->getMiddleX())
							{ //push main sprite hitBoxRight()
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT) == false)
								{
									n->mapX++;
								}
							}
							else
							{ //push main sprite hitBoxLeft()
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT) == false)
								{
									n->mapX--;
								}
							}
						}

						noanim = 1;
						movementDirection = 4;
						direction = DOWN;
					}
					else if (checkHitBoxAndMovePixelInDirection(DOWN) == false)
					{
						if (movementDirection != LEFT && movementDirection != RIGHT)
						{
							if (Math::randLessThan(2) == 0)
							{
								movementDirection = LEFT;
							}
							else
							{
								movementDirection = RIGHT;
							}
						}
					}
					else
					{
						movementDirection = 4;
						direction = DOWN;
					}
				}
				if (getMiddleY() > y)
				{
					if (isHitBoxTouchingEntityInDirectionByAmount(n, UP, 5) == true && (getX() != n->getX() || getY() != n->getY()))
					{
						if (n == getPlayer())
						{
							//push main sprite up
							if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP) == false)
							{
								n->mapY--;
							}

							if (getMiddleX() <= n->getMiddleX())
							{ //push main sprite hitBoxRight()
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT) == false)
								{
									n->mapX++;
								}
							}
							else
							{ //push main sprite hitBoxLeft()
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT) == false)
								{
									n->mapX--;
								}
							}
						}
						noanim = 1;
						movementDirection = 4;
						direction = UP;
					}
					else if (checkHitBoxAndMovePixelInDirection(UP) == false)
					{
						if (movementDirection != LEFT && movementDirection != RIGHT)
						{
							if (Math::randLessThan(2) == 0)
							{
								movementDirection = LEFT;
							}
							else
							{
								movementDirection = RIGHT;
							}
						}
					}
					else
					{
						movementDirection = 4;
						direction = UP;
					}
				}
			}

			if (xdistance >= ydistance)
			{
				if (getMiddleX() < x)
				{
					if (isHitBoxTouchingEntityInDirectionByAmount(n, RIGHT, 5) == true && (getX() != n->getX() || getY() != n->getY()))
					{
						if (n == getPlayer())
						{
							//push main sprite hitBoxRight()
							if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT) == false)
							{
								n->mapX++;
							}

							if (getMiddleY() > n->getMiddleY())
							{ //push main sprite up
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP) == false)
								{
									n->mapY--;
								}
							}
							else
							{ //push main sprite down
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN) == false)
								{
									n->mapY++;
								}
							}
						}
						noanim = 1;
						movementDirection = 4;
						direction = RIGHT;
					}
					else if (checkHitBoxAndMovePixelInDirection(RIGHT) == false)
					{
						if (movementDirection != UP && movementDirection != DOWN)
						{
							if (Math::randLessThan(2) == 0)
							{
								movementDirection = UP;
							}
							else
							{
								movementDirection = DOWN;
							}
						}
					}
					else
					{
						movementDirection = 4;
						direction = RIGHT;
					}
				}
				if (getMiddleX() > x)
				{
					if (isHitBoxTouchingEntityInDirectionByAmount(n, LEFT, 5) == true && (getX() != n->getX() || getY() != n->getY()))
					{
						if (n == getPlayer())
						{
							//push main sprite hitBoxLeft()
							if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT) == false)
							{
								n->mapX--;
							}

							if (getMiddleY() >= n->getMiddleY())
							{ //push main sprite up
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP) == false)
								{
									n->mapY--;
								}
							}
							else
							{ //push main sprite down
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN) == false)
								{
									n->mapY++;
								}
							}
						}
						noanim = 1;
						movementDirection = 4;
						direction = LEFT;
					}
					else if (checkHitBoxAndMovePixelInDirection(LEFT) == false)
					{
						if (movementDirection != UP && movementDirection != DOWN)
						{
							if (Math::randLessThan(2) == 0)
							{
								movementDirection = UP;
							}
							else
							{
								movementDirection = DOWN;
							}
						}
					}
					else
					{
						movementDirection = 4;
						direction = LEFT;
					}
				}
			}

			if (movementDirection == UP)
			{
				if (checkHitBoxAndMovePixelInDirection(UP) == false || isEntityHitBoxTouchingMyHitBoxByAmount(n, 10 + Math::randLessThan(6)) == true)
				{
					movementDirection = 4;
				}
				else
				{
					direction = UP;
				}
			}
			else if (movementDirection == DOWN)
			{
				if (checkHitBoxAndMovePixelInDirection(DOWN) == false || isEntityHitBoxTouchingMyHitBoxByAmount(n, 10 + Math::randLessThan(6)) == true)
				{
					movementDirection = 4;
				}
				else
				{
					direction = DOWN;
				}
			}
			else if (movementDirection == LEFT)
			{
				if (checkHitBoxAndMovePixelInDirection(LEFT) == false || isEntityHitBoxTouchingMyHitBoxByAmount(n, 10 + Math::randLessThan(6)) == true)
				{
					movementDirection = 4;
				}
				else
				{
					direction = LEFT;
				}
			}
			else if (movementDirection == RIGHT)
			{
				if (checkHitBoxAndMovePixelInDirection(RIGHT) == false || isEntityHitBoxTouchingMyHitBoxByAmount(n, 10 + Math::randLessThan(6)) == true)
				{
					movementDirection = 4;
				}
				else
				{
					direction = RIGHT;
				}
			}
		}
	}
	return there_yet;
}

void Character::walkStraightFromPointToPoint(float x1, float y1, float x2, float y2)
{ //=========================================================================================================================


	if (movementDirection > 1)
	{
		movementDirection = 0; //this will simply be used as a movement switch in this function //no its not appropriate but fuck it
	}
	int there_yet = 0;
	if (movementDirection == 0)
	{
		there_yet = walkToXYWithBasicHitCheck(x1, y1);
		if (there_yet == 1)
		{
			movementDirection++;
		}
	}
	if (movementDirection == 1)
	{
		there_yet = walkToXYWithBasicHitCheck(x2, y2);
		if (there_yet == 1)
		{
			movementDirection = 0;
		}
	}
}

void Character::walkStraightFromPointToPointAndStop(float x1, float y1, float x2, float y2)
{ //=========================================================================================================================

	if (movementDirection > 1)
	{
		movementDirection = 0; //this will simply be used as a movement switch in this function //no its not appropriate but fuck it
	}


	int there_yet = 0;
	if (movementDirection == 0)
	{
		there_yet = walkToXYWithBasicHitCheck(x1, y1);
		if (there_yet == 1)
		{
			movementDirection++;
		}
	}
	if (movementDirection == 1)
	{
		there_yet = walkToXYWithBasicHitCheck(x2, y2);
		if (there_yet == 1)
		{
			movementDirection = 0;
		}
	}
}

void Character::walkAwayFromPoint(float x, float y)
{ //=========================================================================================================================

	setIgnoreHitPlayer(true);
	//setTicksPerPixelMoved(speed);
	if (ifCanMoveAPixelThisFrameSubtractAndReturnTrue() == true)
	{
		if (getMiddleY() > y)
		{
			checkHitBoxAndMovePixelInDirection(DOWN);
		}
		if (getMiddleY() < y)
		{
			checkHitBoxAndMovePixelInDirection(UP);
		}
		if (getMiddleX() > x)
		{
			checkHitBoxAndMovePixelInDirection(RIGHT);
		}
		if (getMiddleX() < x)
		{
			checkHitBoxAndMovePixelInDirection(LEFT);
		}

		if (pixelsToWalk > 0 && isWalkingIntoPlayerThisFrame == false)
		{
			pixelsToWalk--;
		}
	}
}

int Character::walkDistance(int direction)
{ //=========================================================================================================================

	int there_yet = 0;

	if (pixelsToWalk > 0)
	{
		movementDirection = direction;
		//setTicksPerPixelMoved(speed);
		checkHitBoxAndWalkDirection(movementDirection);
	}
	else
	{
		there_yet = 1;
	}

	return there_yet;
}

int Character::avoidEntity(Entity* e, int amt)
{ //=========================================================================================================================

	int outside_area = 0;


	//if( getRight()>e.getLeft()-amt &&
	//getLeft()<e.getRight()+amt &&
	//getBottom()>e.getTop()-amt &&
	//getTop()<e.getBottom()+amt

	if (getMiddleX() > e->getMiddleX() - amt && getMiddleX() < e->getMiddleX() + amt && getMiddleY() > e->getMiddleY() - amt && getMiddleY() < e->getMiddleY() + amt)
	{
		outside_area = 0;
		float temp_speed = getTicksPerPixelMoved();
		setTicksPerPixelMoved(1);
		setIgnoreHitPlayer(true);

		if (getMiddleX() <= e->getMiddleX())
		{
			movementDirection = LEFT;
		} //move hitBoxLeft()
		if (getMiddleX() >= e->getMiddleX())
		{
			movementDirection = RIGHT;
		} //move hitBoxRight()

		if (getMiddleY() <= e->getMiddleY())
		{
			movementDirection = UP;
		} //move up
		if (getMiddleY() >= e->getMiddleY())
		{
			movementDirection = DOWN;
		} //move down

		if (ifCanMoveAPixelThisFrameSubtractAndReturnTrue() == true)
		{
			if (getMiddleX() <= e->getMiddleX())
			{
				checkMiddlePixelHitAndMovePixelInDirection(LEFT);
			} //move hitBoxLeft()

			if (getMiddleX() >= e->getMiddleX())
			{
				checkMiddlePixelHitAndMovePixelInDirection(RIGHT);
			} //move hitBoxRight()


			if (getMiddleY() <= e->getMiddleY())
			{
				checkMiddlePixelHitAndMovePixelInDirection(UP);
			} //move up

			if (getMiddleY() >= e->getMiddleY())
			{
				checkMiddlePixelHitAndMovePixelInDirection(DOWN);
			} //move down
		}

		setIgnoreHitPlayer(false);
		setTicksPerPixelMoved(temp_speed);
	}
	else
	{
		outside_area = 1;
	}

	return outside_area;
}

int Character::avoidNearestEntity(int avoid_amt)
{ //=========================================================================================================================

	Entity* nearestentity = findNearestEntity();

	return avoidEntity(nearestentity, avoid_amt);
}

int Character::avoidNearestCharacter(int avoid_amt)
{ //=========================================================================================================================

	Character* nearestentity = findNearestCharacter();

	return avoidEntity(nearestentity, avoid_amt);
}

void Character::pushableCrowdBehavior()
{ //=========================================================================================================================


	Entity* nearestentity = findNearestEntity();

	if (avoidEntity(nearestentity, 4) == 1) //based on entity avoid nearest entity,send in all the entitys you want to be in the crowd
	{
		//avoiding.. hehe i could just leave this out
	}
}

int Character::walk_to_xy_intelligenthit_avoidothers_pushmain(float x, float y)
{ //=========================================================================================================================


	if (getPlayer() == nullptr)
	{
		log.error("Player null in walk_to_xy_intelligenthit_avoidothers_pushmain()");
		return 0;
	}


	setIgnoreHitPlayer(true);
	//setTicksPerPixelMoved(speed);


	int there_yet = 0;
	int avoided = 0;
	int facing_direction = 0;
	int already_walked = 0;


	if (x == -1)
	{
		x = getMiddleX();
	}
	if (y == -1)
	{
		y = getMiddleY();
	}

	//if already there return 1, animate standing

	if (getMiddleX() == x && getMiddleY() == y)
	{
		there_yet = 1;
	}

	else

	{
		if (ifCanMoveAPixelThisFrameSubtractAndReturnTrue() == true)
		{
			//if time to walk

			//calc distance x and y
			float xdistance = getMiddleX() - x;
			float ydistance = getMiddleY() - y;

			if (xdistance < 0)
			{
				xdistance *= -1;
			}
			if (ydistance < 0)
			{
				ydistance *= -1;
			}


			//find nearest entity
			Entity* e = findNearestEntity();


			if (ydistance >= xdistance) //walk the greater distance first, up/down vs hitBoxLeft()/hitBoxRight()
			{
				///walking down
				if (getMiddleY() < y)
				{
					if (isEntityHitBoxTouchingMyHitBoxByAmount(e, 10) == true)
					{
						if (e == getPlayer())
						{
							//push main sprite down
							if ((getMiddleY() < getPlayer()->getMiddleY()) && getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN) == false)
							{
								e->mapY++;
							}

							if (getMiddleX() < getPlayer()->getMiddleX())
							{ //push main sprite hitBoxRight()
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT) == false)
								{
									e->mapX++;
								}
							}

							else

							{ //push main sprite hitBoxLeft()
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT) == false)
								{
									e->mapX--;
								}
							}
						}


						{
							avoided = Math::randLessThan(2);
							if (getMiddleX() <= e->getMiddleX())
							{
								if (avoided == 1)
								{
									checkHitBoxAndMovePixelInDirection(LEFT);
								}
								already_walked = 1;
							}
							else
							{
								if (avoided == 1)
								{
									checkHitBoxAndMovePixelInDirection(RIGHT);
								}
								already_walked = 1;
							}
						}


						facing_direction = DOWN;
					}


					if (avoided == 0)
					{
						if (checkHitBoxAndMovePixelInDirection(DOWN) == false)
						{
							if (movementDirection != LEFT && movementDirection != RIGHT)
							{
								if (getMiddleX() >= x)
								{
									movementDirection = LEFT;
								}
								else
								{
									movementDirection = RIGHT;
								}
							}
						}
						else
						{
							already_walked = 1;
							facing_direction = DOWN;
						}
					}
				}


				avoided = 0;

				///walking up
				if (getMiddleY() > y)
				{
					if (isEntityHitBoxTouchingMyHitBoxByAmount(e, 10) == true)
					{
						if (e == getPlayer())
						{
							//push main sprite up
							if ((getMiddleY() > getPlayer()->getMiddleY()) && getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP) == false)
							{
								e->mapY--;
							}

							if (getMiddleX() <= getPlayer()->getMiddleX())
							{ //push main sprite hitBoxRight()
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT) == false)
								{
									e->mapX++;
								}
							}
							else
							{ //push main sprite hitBoxLeft()
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT) == false)
								{
									e->mapX--;
								}
							}
						}

						{
							avoided = Math::randLessThan(2);

							if (getMiddleX() < e->getMiddleX())
							{
								if (avoided == 1)
								{
									checkHitBoxAndMovePixelInDirection(LEFT); //else walk hitBoxLeft() if slightly hitBoxLeft()
								}
								already_walked = 1;
							}
							else
							{
								if (avoided == 1)
								{
									checkHitBoxAndMovePixelInDirection(RIGHT); //else walk hitBoxRight()
								}
								already_walked = 1;
							}
						}
						facing_direction = UP;
					}

					if (avoided == 0)
					{
						if (checkHitBoxAndMovePixelInDirection(UP) == false)
						{
							if (movementDirection != LEFT && movementDirection != RIGHT)
							{
								if (getMiddleX() >= x)
								{
									movementDirection = LEFT;
								}
								else
								{
									movementDirection = RIGHT;
								}
							}
						}
						else
						{
							already_walked = 1;
							facing_direction = UP;
						}
					}
				}
				avoided = 0;
			}


			//if walk hitBoxRight()/hitBoxLeft() first
			if (xdistance > ydistance)
			{
				///walking hitBoxRight()
				if (getMiddleX() < x)
				{
					if (isEntityHitBoxTouchingMyHitBoxByAmount(e, 10) == true)
					{
						if (e == getPlayer())
						{
							//push main sprite hitBoxRight()
							if ((getMiddleX() < getPlayer()->getMiddleX()) && getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(RIGHT) == false)
							{
								e->mapX++;
							}

							if (getMiddleY() > getPlayer()->getMiddleY())
							{ //push main sprite up
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP) == false)
								{
									e->mapY--;
								}
							}
							else
							{ //push main sprite down
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN) == false)
								{
									e->mapY++;
								}
							}
						}

						{
							avoided = Math::randLessThan(2);

							if (getMiddleY() <= e->getMiddleY())
							{
								if (avoided == 1)
								{
									checkHitBoxAndMovePixelInDirection(UP); //else walk up if slightly above
								}
								already_walked = 1;
							}
							else
							{
								if (avoided == 1)
								{
									checkHitBoxAndMovePixelInDirection(DOWN); //else walk down
								}
								already_walked = 1;
							}
						}
						facing_direction = RIGHT;
					}

					if (avoided == 0)
					{
						if (checkHitBoxAndMovePixelInDirection(RIGHT) == false)
						{
							if (movementDirection != UP && movementDirection != DOWN)
							{
								if (getMiddleY() >= y)
								{
									movementDirection = UP;
								}
								else
								{
									movementDirection = DOWN;
								}
							}
						}
						else
						{
							already_walked = 1;
							facing_direction = RIGHT;
						}
					}
				}


				avoided = 0;


				///walking hitBoxLeft()
				if (getMiddleX() > x)
				{
					if (isEntityHitBoxTouchingMyHitBoxByAmount(e, 10) == true)
					{
						if (e == getPlayer())
						{
							//push main sprite hitBoxLeft()
							if ((getMiddleX() > getPlayer()->getMiddleX()) && getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(LEFT) == false)
							{
								e->mapX--;
							}

							if (getMiddleY() >= getPlayer()->getMiddleY())
							{ //push main sprite up
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(UP) == false)
								{
									e->mapY--;
								}
							}
							else
							{ //push main sprite down
								if (getPlayer()->checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(DOWN) == false)
								{
									e->mapY++;
								}
							}
						}

						{
							avoided = Math::randLessThan(2);
							if (getMiddleY() < e->getMiddleY())
							{
								if (avoided == 1)
								{
									checkHitBoxAndMovePixelInDirection(UP); //else walk up if slightly above
								}
								already_walked = 1;
							}
							else
							{
								if (avoided == 1)
								{
									checkHitBoxAndMovePixelInDirection(DOWN); //else walk down
								}
								already_walked = 1;
							}
						}
						facing_direction = LEFT;
					}

					if (avoided == 0)
					{
						if (checkHitBoxAndMovePixelInDirection(LEFT) == false)
						{
							if (movementDirection != UP && movementDirection != DOWN)
							{
								if (getMiddleY() >= y)
								{
									movementDirection = UP;
								}
								else
								{
									movementDirection = DOWN;
								}
							}
						}
						else
						{
							already_walked = 1;
							facing_direction = LEFT;
						}
					}
				}
			}


			if (already_walked == 0)
			{
				if (movementDirection == UP)
				{
					if (checkHitBoxAndMovePixelInDirection(UP) == false || (isEntityHitBoxTouchingMyHitBoxByAmount(e, 10 + Math::randLessThan(6)) == true && getMiddleY() > e->getMiddleY()))
					{
						movementDirection = 4;
					}
					else
					{
						facing_direction = UP;
					}
				}
				else if (movementDirection == DOWN)
				{
					if (checkHitBoxAndMovePixelInDirection(DOWN) == false || (isEntityHitBoxTouchingMyHitBoxByAmount(e, 10 + Math::randLessThan(6)) == true && getMiddleY() < e->getMiddleY()))
					{
						movementDirection = 4;
					}
					else
					{
						facing_direction = DOWN;
					}
				}
				else if (movementDirection == LEFT)
				{
					if (checkHitBoxAndMovePixelInDirection(LEFT) == false || (isEntityHitBoxTouchingMyHitBoxByAmount(e, 10 + Math::randLessThan(6)) == true && getMiddleX() > e->getMiddleX()))
					{
						movementDirection = 4;
					}
					else
					{
						facing_direction = LEFT;
					}
				}
				else if (movementDirection == RIGHT)
				{
					if (checkHitBoxAndMovePixelInDirection(RIGHT) == false || (isEntityHitBoxTouchingMyHitBoxByAmount(e, 10 + Math::randLessThan(6)) == true && getMiddleX() < e->getMiddleX()))
					{
						movementDirection = 4;
					}
					else
					{
						facing_direction = RIGHT;
					}
				}
			}

			if (pixelsToWalk > 0 && isWalkingIntoPlayerThisFrame == false)
			{
				pixelsToWalk--;
			}
		}
	}
	return there_yet;
}

void Character::renderDebugBoxes()
{ //=========================================================================================================================
	Entity::renderDebugBoxes();

	//float zoom = getCameraman()->getZoom();

	if (pathfinder != nullptr)
	{
		if (pathfinder->path != nullptr)
		{
			for (int i = 0; i < (int)pathfinder->path->pathTiles->size(); i++)
			{
				GLUtils::drawBox(getMap()->getScreenX((float)pathfinder->path->getTileXForPathIndex(i) * 8 * 2, 16), getMap()->getScreenX((float)pathfinder->path->getTileXForPathIndex(i) * 8 * 2 + 16, 16), getMap()->getScreenY((float)pathfinder->path->getTileYForPathIndex(i) * 8 * 2, 16), getMap()->getScreenY((float)pathfinder->path->getTileYForPathIndex(i) * 8 * 2 + 16, 16), 255, 255, 255);
			}
		}
	}
}

