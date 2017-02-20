#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger RamioGuy::log = Logger("RamioGuy");


RamioGuy::RamioGuy(Engine* g)
{ // =========================================================================================================================
	Entity(g, new EntityData(-1, "ramio", "ramio", 0, 0));
}

bool RamioGuy::jumping = false;

void RamioGuy::init()
{ // =========================================================================================================================
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

void RamioGuy::jump()
{ // =========================================================================================================================


	if (jumping == true)
	{
		jumpDecelCounter++;
	}
	else
	{
		jumpDecelCounter = 0;
	}

	if (getControlsManager()->MINIGAME_ACTION_HELD)
	{
		if (canJump == true)
		{
			jumping = true;
			canJump = false;
			getAudioManager()->playSound("ramiojump", 64, 44100, 0);
		}

		if (jumping == true)
		{
			int max_jump = 3;
			if (rightWalkSpeed == 3 || leftWalkSpeed == 3)
			{
				max_jump = 4;
			}

			if (pixelsJumped < 16 * max_jump + 1)
			{
				if (checkHit(UP) == false)
				{
					if (jumpDecelCounter > (pixelsJumped / jump_decel))
					{
						jumpDecelCounter = 0;
						setY(getY() - 1);
						pixelsJumped++;
					}
				}
				else
				{
					jumping = false;
					pixelsJumped = 0;
					canJump = false;
					wasJumping = true;
				}
			}
			else
			{
				jumping = false;
				pixelsJumped = 0;
				canJump = false;
				wasJumping = true;
			}
		}
	}
	else
	{
		if (jumping == true)
		{
			if (pixelsJumped < (16 * 2) + 1)
			{
				if (checkHit(UP) == false)
				{
					if (jumpDecelCounter > (pixelsJumped / jump_decel))
					{
						jumpDecelCounter = 0;
						setY(getY() - 1);
						pixelsJumped++;
					}
				}
				else
				{
					jumping = false;
					pixelsJumped = 0;
					canJump = false;
					wasJumping = true;
				}
			}
			else
			{
				jumping = false;
				pixelsJumped = 0;
				canJump = false;
				wasJumping = true;
			}
		}
	}
}

void RamioGuy::fall()
{ // =========================================================================================================================


	// gravity
	if (jumping == false)
	{
		if (checkHit(DOWN) == false)
		{
			fallAccelCounter++;
			canJump = false;

			if (fallAccelCounter > (fall_accel / (pixelsFell + 1)))
			{
				setY(getY() + 1);
				pixelsFell++;
				fallAccelCounter = 0;
			}
		}
		else
		{
			if (!getControlsManager()->MINIGAME_ACTION_HELD)
			{
				canJump = true;
			}
			pixelsFell = 0;
			fallAccelCounter = 0;
			wasJumping = false;
		}
	}
}

void RamioGuy::update()
{ // =========================================================================================================================


	Entity::update();


	int direction = -1;


	if (getControlsManager()->MINIGAME_RIGHT_HELD)
	{
		direction = RIGHT;
	}

	if (getControlsManager()->MINIGAME_LEFT_HELD)
	{
		direction = LEFT;
	}


	// ========handle running
	if (getControlsManager()->MINIGAME_RUN_HELD == true)
	{
		running = true;
	}
	else
	{
		running = false;
	}


	if (getControlsManager()->miniGame_ACTION_Pressed())
	{
		forceY = -5.0f;
	}


	forceFactor = 0.17f * pixelsToMoveThisFrame;
	frictionFactor = 0.017f * pixelsToMoveThisFrame;
	gravityFactor = 0.15f * pixelsToMoveThisFrame;


	speedLimit = 2.0f;
	if (running == true)
	{
		speedLimit = 3.0f;
	}


	float gravityLimit = 3.5f;

	if (forceY < gravityLimit)
	{
		forceY += gravityFactor;
		if (forceY > gravityLimit)
		{
			forceY = gravityLimit;
		}
	}


	if (direction == -1)
	{
		// reduce force/apply friction
		if (forceX > 0)
		{
			forceX -= frictionFactor;
			if (forceX < 0)
			{
				forceX = 0.0f;
			}
		}
		else if (forceX < 0)
		{
			forceX += frictionFactor;
			if (forceX > 0)
			{
				forceX = 0.0f;
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
	}
	if (direction == RIGHT)
	{
		forceX += forceFactor;
		if (forceX > speedLimit)
		{
			forceX = speedLimit;
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
	else if (forceX > 0)
	{
		move(RIGHT, forceX * pixelsToMoveThisFrame);
	}


	if (forceY < 0)
	{
		move(UP, -forceY * pixelsToMoveThisFrame);
	}
	else if (forceY > 0)
	{
		move(DOWN, forceY * pixelsToMoveThisFrame);
	}


	// get heart
	// turn into evil reggie
	// throw pizzas

	// sprite type broken brick

	// jump into ? blocks, get stuff

	// jump into bricks, break them

	// skidding is not right.
	// need to be able to run over spaces
	// slows down when hits a block on ceiling. no good

	// if bobas are above a block you getHit, kill them

	// cant jump into a gap in between 2 blocks horizontally

	// DONE======================

	// make sprites
	// walk sprites, animate them
	// stomp on bobs head, delete them
	// run into sprites die

	// fall in pit die

	// sprite type brick 16x16
	// sprite type ? block
	// sprite type dead block

	// timer

	// need level end when enter door at end

	// timer
	// run out of time die
}

bool RamioGuy::checkHit(int dir)
{ // =========================================================================================================================
	bool hitting_wall = true;

	if (getIgnoreHitLayer() == true)
	{
		return false;
	}

	if (dir == UP)
	{
		if (getMap()->getHitLayerValueAtXYPixels(getLeft() + 1, getTop()) == false && getMap()->getHitLayerValueAtXYPixels(getMiddleX(), getTop()) == false && getMap()->getHitLayerValueAtXYPixels(getMiddleX(), getTop()) == false && getMap()->getHitLayerValueAtXYPixels(getRight() - 2, getTop()) == false)
		{
			hitting_wall = false;
		}
	}
	else if (dir == DOWN)
	{
		if (getMap()->getHitLayerValueAtXYPixels(getLeft() + 1, getBottom()) == false && getMap()->getHitLayerValueAtXYPixels(getMiddleX() - 1, getBottom()) == false && getMap()->getHitLayerValueAtXYPixels(getMiddleX(), getBottom()) == false && getMap()->getHitLayerValueAtXYPixels(getRight() - 2, getBottom()) == false)
		{
			hitting_wall = false;
		}
	}
	else if (dir == LEFT)
	{
		if (getMap()->getHitLayerValueAtXYPixels(getLeft(), getTop() + 1) == false && getMap()->getHitLayerValueAtXYPixels(getLeft(), getMiddleY() - 1) == false && getMap()->getHitLayerValueAtXYPixels(getLeft(), getMiddleY()) == false && getMap()->getHitLayerValueAtXYPixels(getLeft(), getBottom() - 1) == false)
		{
			hitting_wall = false;
		}
	}
	else if (dir == RIGHT)
	{
		if (getMap()->getHitLayerValueAtXYPixels(getRight() - 1, getTop() + 1) == false && getMap()->getHitLayerValueAtXYPixels(getRight() - 1, getMiddleY() - 1) == false && getMap()->getHitLayerValueAtXYPixels(getRight() - 1, getMiddleY()) == false && getMap()->getHitLayerValueAtXYPixels(getRight() - 1, getBottom() - 1) == false)
		{
			hitting_wall = false;
		}
	}

	isWalkingIntoWallThisFrame = hitting_wall;

	return hitting_wall;
}

void RamioGuy::move(int direction, float floatPixels)
{ // =========================================================================================================================
	int moveWholePixels = (int)(floor(floatPixels));
	float moveRemainder = (floatPixels - moveWholePixels);

	int xWholePixels = (int)(floor(getX()));
	float xRemainder = (getX() - xWholePixels);

	int yWholePixels = (int)(floor(getY()));
	float yRemainder = (getY() - yWholePixels);


	if (direction == RIGHT) // RIGHT
	{
		//setX(x()+floatPixels);

		for (int i = 0; i < moveWholePixels; i++)
		{
			if (checkHit(RIGHT) == false)
			{
				movePixelInDirection(RIGHT);
			}
		}

		if (xRemainder + moveRemainder >= 1.0f)
		{
			if (checkHit(RIGHT) == false)
			{
				moveRemainder = (xRemainder + moveRemainder) - 1.0f;
				setX(getX() - xRemainder);
				movePixelInDirection(RIGHT);
			}
		}


		if (checkHit(RIGHT) == true)
		{
			setX((float)(floor(getX())));
			forceX = 0;
		}
		else
		{
			setX(getX() + moveRemainder);
		}
	}
	else if (direction == LEFT) // LEFT
	{
		for (int i = 0; i < moveWholePixels; i++)
		{
			if (checkHit(LEFT) == false)
			{
				movePixelInDirection(LEFT);
			}
		}

		if (xRemainder - moveRemainder < 0.0f)
		{
			if (checkHit(LEFT) == false)
			{
				moveRemainder -= xRemainder;
				setX(getX() - xRemainder);
				movePixelInDirection(LEFT);
			}
		}


		if (checkHit(LEFT) == true)
		{
			setX((float)(floor(getX())));
			forceX = 0;
		}
		else
		{
			setX(getX() - moveRemainder);
		}
	}
	else if (direction == UP) // UP
	{
		for (int i = 0; i < moveWholePixels; i++)
		{
			if (checkHit(UP) == false)
			{
				movePixelInDirection(UP);
			}
		}

		if (yRemainder - moveRemainder < 0.0f)
		{
			if (checkHit(UP) == false)
			{
				moveRemainder -= yRemainder;
				setY(getY() - yRemainder);
				movePixelInDirection(UP);
			}
		}
		if (checkHit(UP) == true)
		{
			setY((float)(floor(getY())));
			forceY = 0;
		}
		else
		{
			setY(getY() - moveRemainder);
		}
	}
	else if (direction == DOWN) // DOWN
	{
		for (int i = 0; i < moveWholePixels; i++)
		{
			if (checkHit(DOWN) == false)
			{
				movePixelInDirection(DOWN);
			}
		}

		if (yRemainder + moveRemainder >= 1.0f)
		{
			if (checkHit(DOWN) == false)
			{
				moveRemainder = (yRemainder + moveRemainder) - 1.0f;
				setY(getY() - yRemainder);
				movePixelInDirection(DOWN);
			}
		}


		if (checkHit(DOWN) == true)
		{
			setY((float)(floor(getY())));
		}
		else
		{
			setY(getY() + moveRemainder);
		}
	}
}

void RamioGuy::render(float alpha, BobTexture* texture, BobTexture* shadowTexture)
{ //=========================================================================================================================

	float zoom = getCameraman()->getZoom();

	float tx0 = 0.0f;
	float tx1 = 1.0f;
	float ty0 = 0.0f;
	float ty1 = 1.0f;

	float x0 = 0;
	float x1 = 0;
	float y0 = 0;
	float y1 = 0;


	//------------------
	//now draw actual sprite
	//------------------
	if (texture != nullptr)
	{
		tx0 = 0.0f;
		tx1 = ((float)(sprite->getScreenWidth()) / (float)(texture->getTextureWidth()));
		ty0 = (((float)(sprite->getScreenHeight())) * getFrame()) / (float)(texture->getTextureHeight());
		ty1 = (((float)(sprite->getScreenHeight())) * (getFrame() + 1)) / (float)(texture->getTextureHeight());


		//NOTICE I AM NOT USING THE OFFSET

		x0 = getScreenLeft(); //-offsetX;
		y0 = getScreenTop(); //-offsetY;


		x0 = ((float)(floor(((int)(x0))))); //clamp drawing
		//y0 = ((float)Math.floor(((int)(y0)/2))*2);


		x1 = (float)(x0 + getWidth() * zoom);
		y1 = (float)(y0 + getHeight() * zoom);


		GLUtils::drawTexture(texture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, alpha, GLUtils::FILTER_NEAREST);
	}
}

