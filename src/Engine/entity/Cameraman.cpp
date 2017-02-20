

#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once


#include "Cameraman.h"

Logger Cameraman::log = Logger("Cameraman");


ConsoleText* Cameraman::currentSpeedXText = new ConsoleText();
ConsoleText* Cameraman::currentSpeedYText = new ConsoleText();
ConsoleText* Cameraman::targetSpeedXText = new ConsoleText();
ConsoleText* Cameraman::targetSpeedYText = new ConsoleText();

Cameraman::Cameraman(Engine* g)
{ //=========================================================================================================================

	this->e = g;

	EntityData* data = new EntityData(-1, "Camera", "Camera", 0, 0);
	initEntity(data);

	//set target

	//set map x and map y to target x y

	targetEntity = this;

	getData()->setDisableShadow(true);
}

void Cameraman::initCurrentAnimationFromSprite()
{ //=========================================================================================================================

	//super.initCurrentAnimationFromSprite();

	setXYToTarget();
}

//Map* Cameraman::getMap()
//{ //=========================================================================================================================
//
//	return getMapManager()->getCurrentMap();
//}

Map* Cameraman::getCurrentMap()
{ //=========================================================================================================================

	return getMapManager()->getCurrentMap();
}

void Cameraman::render(float alpha)
{ //=========================================================================================================================

	//don't render cameraman
	//super.render();
}

float Cameraman::getX()
{ //=========================================================================================================================

	return (float)(Entity::getX() + (screenShakeX / zoom));
}

float Cameraman::getY()
{ //=========================================================================================================================

	return (float)(Entity::getY() + (screenShakeY / zoom));
}

void Cameraman::setShakeScreen(int ticksDuration, int maxX, int maxY, int ticksPerShake)
{ //=========================================================================================================================

	if (shakeScreenTicksCounter == 0)
	{
		shakeScreenStartTime = System::currentHighResTimer();
	}

	shakeScreenTicksCounter += ticksDuration;

	shakeScreenTicksDuration = shakeScreenTicksCounter;

	screenShakeMaxX = maxX;
	screenShakeMaxY = maxY;

	screenShakeTicksPerShake = ticksPerShake;
}

void Cameraman::updateScreenShake()
{ //=========================================================================================================================
	if (shakeScreenTicksCounter > 0)
	{
		shakeScreenTicksCounter -= (int)getEngine()->engineTicksPassed();
		if (shakeScreenTicksCounter < 0)
		{
			shakeScreenTicksCounter = 0;
		}


		long long startTime = shakeScreenStartTime;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime) * getEngine()->engineSpeed);

		float xOverShakeTime = (float)(Easing::easeInOutCircular(ticksPassed, 0, screenShakeMaxX, shakeScreenTicksDuration));
		float yOverShakeTime = (float)(Easing::easeInOutCircular(ticksPassed, 0, screenShakeMaxY, shakeScreenTicksDuration));

		screenShakeTicksPerShakeXCounter += (int)getEngine()->engineTicksPassed();
		if (screenShakeTicksPerShakeXCounter > screenShakeTicksPerShake)
		{
			screenShakeTicksPerShakeXCounter = 0;
			shakeScreenLeftRightToggle = !shakeScreenLeftRightToggle;
		}

		screenShakeTicksPerShakeYCounter += (int)getEngine()->engineTicksPassed(); //y shakes at half speed
		if (screenShakeTicksPerShakeYCounter > screenShakeTicksPerShake * 2)
		{
			screenShakeTicksPerShakeYCounter = 0;

			shakeScreenUpDownToggle = !shakeScreenUpDownToggle;
		}


		float xThisTime = (float)(Easing::easeInOutCircular(screenShakeTicksPerShakeXCounter, 0, xOverShakeTime, screenShakeTicksPerShake));
		float yThisTime = (float)(Easing::easeInOutCircular(screenShakeTicksPerShakeYCounter, 0, yOverShakeTime, screenShakeTicksPerShake * 2));

		if (shakeScreenLeftRightToggle)
		{
			screenShakeX = xThisTime;
		}
		else
		{
			screenShakeX = 0 - xThisTime;
		}
		if (shakeScreenUpDownToggle)
		{
			screenShakeY = yThisTime;
		}
		else
		{
			screenShakeY = 0 - yThisTime;
		}
	}
	else
	{
		screenShakeX = 0;
		screenShakeY = 0;
	}
}

void Cameraman::update()
{ //=========================================================================================================================

	Entity::update();

	if (getCurrentMap() == nullptr)return;

	int xtarget = getXTarget();
	int ytarget = getYTarget();


	float distX = abs(getX() - xtarget);
	float distY = abs(getY() - ytarget);


	float maxDistX = (float)getEngine()->getWidth();
	float maxDistY = (float)getEngine()->getHeight();


	if (dynamic_cast<BGClientEngine*>(getEngine()) != nullptr)
	{
		float playerSpeedX = ((abs(getPlayer()->forceX * (getPlayer()->pixelsToMoveThisFrame + 1))) / getEngine()->engineTicksPassed()) / 0.01f;
		float playerSpeedY = ((abs(getPlayer()->forceY * (getPlayer()->pixelsToMoveThisFrame + 1))) / getEngine()->engineTicksPassed()) / 0.01f;


		if (getPlayer()->noInput == true)
		{
			snapSpeedX = 0.0f;
			snapSpeedY = 0.0f;
			ticksSinceSnapToPlayer = 0;
			ticksSinceZoomOut = 0;


			standingTicks += (int)getEngine()->engineTicksPassed();
			if (standingTicks > ticksToWaitBeforeZoomingBackIn)
			{
				zoomBackInTicks += (int)getEngine()->engineTicksPassed();

				//zoom back into normal zoom if running zoom is further away
				if (zoomBackInTicks < ticksToZoomBackInFromRunningOrWalking)
				{
					runZOOMto = (float)(ceil((standingTempZoom - (float)(Easing::easeInOutSinusoidal(zoomBackInTicks, 0, standingTempZoom - ZOOMto, ticksToZoomBackInFromRunningOrWalking))) * 1000.0f) / 1000.0f);
				}
				else
				{
					runZOOMto = ZOOMto;
				}
			}


			runningZoomTicks = 0;
			walkingZoomTicks = 0;
		}
		else
		{
			ticksSinceSnapToPlayer += (int)getEngine()->engineTicksPassed();
			ticksSinceZoomOut += (int)getEngine()->engineTicksPassed();
			standingTicks = 0;

			zoomBackInTicks = 0;
			standingTempZoom = runZOOMto;

			if (ticksSinceSnapToPlayer > ticksToWaitBeforeCenteringOnPlayer)
			{
				if (snapSpeedX < playerSpeedX)
				{
					snapSpeedX = (float)(Easing::easeInSinusoidal(ticksSinceSnapToPlayer - ticksToWaitBeforeCenteringOnPlayer, 0, playerSpeedX, ticksToWaitBeforeCenteringOnPlayer + ticksToCenterOnPlayer));
				}

				if (snapSpeedY < playerSpeedY)
				{
					snapSpeedY = (float)(Easing::easeInSinusoidal(ticksSinceSnapToPlayer - ticksToWaitBeforeCenteringOnPlayer, 0, playerSpeedY, ticksToWaitBeforeCenteringOnPlayer + ticksToCenterOnPlayer));
				}
			}

			if (ticksSinceZoomOut > ticksToWaitBeforeZoomingOut)
			{
				if (getPlayer()->running == true)
				{
					runningZoomTicks += (int)getEngine()->engineTicksPassed();
					walkingZoomTicks = 0;

					//zoom out to 1.0f if we are closer in
					if (ZOOMto > runningZoom)
					{
						if (runningZoomTicks <= ticksToZoomOutWhileRunningOrWalking)
						{
							runZOOMto = (float)(floor((runningTempZoom - (float)(Easing::easeInOutSinusoidal(runningZoomTicks, 0, runningTempZoom - runningZoom, ticksToZoomOutWhileRunningOrWalking))) * 1000.0f) / 1000.0f);
						}
						else
						{
							runZOOMto = runningZoom;
						}

						walkingTempZoom = runZOOMto;
					}
				}
				else
				{
					if (getPlayer()->running == false)
					{
						walkingZoomTicks += (int)getEngine()->engineTicksPassed();
						runningZoomTicks = 0;

						if (ZOOMto > walkingZoom)
						{
							if (walkingZoomTicks <= ticksToZoomOutWhileRunningOrWalking)
							{
								runZOOMto = (float)(floor((walkingTempZoom - (float)(Easing::easeInOutSinusoidal(walkingZoomTicks, 0, walkingTempZoom - walkingZoom, ticksToZoomOutWhileRunningOrWalking))) * 1000.0f) / 1000.0f);
							}
							else
							{
								runZOOMto = walkingZoom;
							}

							runningTempZoom = runZOOMto;
						}
					}
				}
			}
			else
			{
				walkingTempZoom = runZOOMto;
				runningTempZoom = runZOOMto;
			}
		}
	}
	else
	{
		runZOOMto = ZOOMto;


		float playerSpeedX = ((abs(targetEntity->getTicksPerPixelMoved() * (targetEntity->pixelsToMoveThisFrame + 1))) / getEngine()->engineTicksPassed()) / 0.01f;
		float playerSpeedY = ((abs(targetEntity->getTicksPerPixelMoved() * (targetEntity->pixelsToMoveThisFrame + 1))) / getEngine()->engineTicksPassed()) / 0.01f;

		if (targetEntity->ticksSinceLastMovement > 0)
		{
			snapSpeedX = 0.0f;
			snapSpeedY = 0.0f;
			ticksSinceSnapToPlayer = 0;
		}
		else
		{
			ticksSinceSnapToPlayer += (int)getEngine()->engineTicksPassed();
			ticksSinceZoomOut += (int)getEngine()->engineTicksPassed();
			standingTicks = 0;

			zoomBackInTicks = 0;
			standingTempZoom = runZOOMto;

			if (ticksSinceSnapToPlayer > ticksToWaitBeforeCenteringOnPlayer)
			{
				if (snapSpeedX < playerSpeedX)
				{
					snapSpeedX = (float)(Easing::easeInSinusoidal(ticksSinceSnapToPlayer - ticksToWaitBeforeCenteringOnPlayer, 0, playerSpeedX, ticksToWaitBeforeCenteringOnPlayer + ticksToCenterOnPlayer));
				}

				if (snapSpeedY < playerSpeedY)
				{
					snapSpeedY = (float)(Easing::easeInSinusoidal(ticksSinceSnapToPlayer - ticksToWaitBeforeCenteringOnPlayer, 0, playerSpeedY, ticksToWaitBeforeCenteringOnPlayer + ticksToCenterOnPlayer));
				}
			}
		}
	}


	float maxSpeed = 100.0f;
	float currentSpeedX = (float)(Easing::easeOutQuintic(distX, snapSpeedX, maxSpeed, maxDistX));
	float currentSpeedY = (float)(Easing::easeOutQuintic(distY, snapSpeedY, maxSpeed, maxDistY));


	currentSpeedXText->text = string("Cam Speed X: ") + to_string(floor(currentSpeedX * getEngine()->engineTicksPassed() * 0.01f * 1000) / 1000);
	currentSpeedYText->text = string("Cam Speed Y: ") + to_string(floor(currentSpeedY * getEngine()->engineTicksPassed() * 0.01f * 1000) / 1000);

	targetSpeedXText->text = string("Player Snap Speed X: ") + to_string(floor(snapSpeedX * getEngine()->engineTicksPassed() * 0.01f * 1000) / 1000);
	targetSpeedYText->text = string("Player Snap Speed Y: ") + to_string(floor(snapSpeedY * getEngine()->engineTicksPassed() * 0.01f * 1000) / 1000);


	float pixelsToMoveX = currentSpeedX * getEngine()->engineTicksPassed() * 0.01f; //currentSpeed*pixelsToMoveThisFrame;//Game().ticksPassed()*0.2f*((float)Math.pow(2.0f, dist));
	float pixelsToMoveY = currentSpeedY * getEngine()->engineTicksPassed() * 0.01f; //currentSpeed*pixelsToMoveThisFrame;//Game().ticksPassed()*0.2f*((float)Math.pow(2.0f, dist));


	if (getCurrentMap()->alpha == 1.0f) //TODO: if current map is done fading in , make this a function
	{
		if (getX() > xtarget)
		{
			setX(getX() - pixelsToMoveX);
			if (getX() < xtarget)
			{
				setX((float)xtarget);
			}
		}
		if (getX() < xtarget)
		{
			setX(getX() + pixelsToMoveX);
			if (getX() > xtarget)
			{
				setX((float)xtarget);
			}
		}
		if (getY() > ytarget)
		{
			setY(getY() - pixelsToMoveY);
			if (getY() < ytarget)
			{
				setY((float)ytarget);
			}
		}
		if (getY() < ytarget)
		{
			setY(getY() + pixelsToMoveY);
			if (getY() > ytarget)
			{
				setY((float)ytarget);
			}
		}
	}

	//setX(xtarget);
	//setY(ytarget);

	updateZoom();

	updateScreenShake();
}

float Cameraman::ZOOMINCREMENT = 0.25f;
float Cameraman::MINZOOM = 0.25f;
float Cameraman::MAXZOOM = 3.0f;

float Cameraman::getZoom()
{
	if (screenShakeMaxY != 0)
	{
		return zoom + ((float)(((float)(screenShakeY) / (float)(screenShakeMaxY)) * (screenShakeMaxY / (getEngine()->getWidth() * zoom)))) * 2;
	}
	return zoom;
}

void Cameraman::setZoomTO(float ZOOMto)
{
	this->ZOOMto = ZOOMto;
}

void Cameraman::setZoomToFitArea(Area* a)
{
	//float screenWidth = (float)getEngine()->getWidth();
	//float areaWidth = (float)a->getWidth();

	//float screenHeight = (float)getEngine()->getHeight();
	//float areaHeight = (float)a->getHeight();

	//TODO:
}

void Cameraman::updateZoom()
{ //=========================================================================================================================

	//float oldZoom = zoom;


	if (quickZOOMto != 0.0f && zoomManuallyEnabled)
	{
		if (zoom != quickZOOMto)
		{
			if (zoom > quickZOOMto)
			{
				zoom -= 0.01f * getEngine()->engineTicksPassed();
				if (zoom < quickZOOMto)
				{
					zoom = quickZOOMto;
				}
			}

			if (zoom < quickZOOMto)
			{
				zoom += 0.01f * getEngine()->engineTicksPassed();
				if (zoom > quickZOOMto)
				{
					zoom = quickZOOMto;
				}
			}
		}
	}
	else
	{
		if (runZOOMto != ZOOMto && autoZoomByPlayerMovementEnabled)
		{
			if (zoom != runZOOMto)
			{
				if (zoom > runZOOMto)
				{
					zoom -= 0.01f * getEngine()->engineTicksPassed();
					if (zoom < runZOOMto)
					{
						zoom = runZOOMto;
					}
				}

				if (zoom < runZOOMto)
				{
					zoom += 0.01f * getEngine()->engineTicksPassed();
					if (zoom > runZOOMto)
					{
						zoom = runZOOMto;
					}
				}
			}
		}
		else
		{
			if (popZOOMto != 0)
			{
				if (zoom != popZOOMto)
				{
					if (zoom > popZOOMto)
					{
						zoom -= 0.00005f * getEngine()->engineTicksPassed();
						if (zoom < popZOOMto)
						{
							zoom = popZOOMto;
						}
					}

					if (zoom < ZOOMto)
					{
						zoom += 0.00005f * getEngine()->engineTicksPassed();
						if (zoom > popZOOMto)
						{
							zoom = popZOOMto;
						}
					}
				}

				if (zoom == popZOOMto)
				{
					popZOOMto = 0.0f;
				}
			}
			else
			{
				if (zoom != ZOOMto)
				{
					if (zoom > ZOOMto)
					{
						zoom -= 0.002f * getEngine()->engineTicksPassed();
						if (zoom < ZOOMto)
						{
							zoom = ZOOMto;
						}
					}

					if (zoom < ZOOMto)
					{
						zoom += 0.002f * getEngine()->engineTicksPassed();
						if (zoom > ZOOMto)
						{
							zoom = ZOOMto;
						}
					}
				}
			}
		}
	}


	//TODO: figure out how to smoothly zoom in without update(1000) hack


	//TODO: shift should lock camera? maybe caps lock


	//TODO: update camera coordinates to smoothly zoom in
	//if(zoom!=oldZoom)
	//{
	//cameraman.getMapXPixelsHQ=cameraman.getMapXPixelsHQ/(zoom-oldZoom);
	//cameraman.getMapYPixelsHQ=cameraman.getMapYPixelsHQ/(zoom-oldZoom);
	//cameraman.update(10000);
	//}

	//TODO: update min zoom to room size? only for big areas, dont want closets zoomed in all the way


	/*if(map().alpha==1.0f)//is finished fading in, make this a function or something
	{
	            
	            
	   //TODO: if we are outside, prefer 640x480?
	   //keep users zoom level, but if camstop layer to edge is smaller than zoom, zoom into that temporarily.
	            
	   //zoom in closer near stores. maybe need fx layer markings for "zoom in"
	            
	   //remember each room's zoom level set by user
	            
	   //if we are inside, prefer 320 x 240, dont allow zooming out further than the room size.
	            
	            
	   int maxCamWidth = cameraman.getMaxCameraBoundaryWidth();
	   int maxCamHeight = cameraman.getMaxCameraBoundaryHeight();
	            
	   if(maxCamWidth<maxCamHeight)
	   //if((float)Display.getWidth()>maxCamWidth*ZOOMto)
	   {
	      ZOOMto=(float)Display.getWidth()/(float)maxCamWidth;
	            
	      //round to nearest 0.25 (higher)
	      //1.77-> 2.0f
	      //1.74-> 1.75
	      ZOOMto=((float)(((((int)(ZOOMto*100))/25)+1)*25))/100.0f;
	      //Math.floor(ZOOMto);
	            
	      if(ZOOMto<MINZOOM)ZOOMto=MINZOOM;
	      if(ZOOMto>MAXZOOM)ZOOMto=MAXZOOM;
	            
	   }
	            
	   if(maxCamHeight<maxCamWidth)
	   //if((float)Display.getHeight()>(float)maxCamHeight*ZOOMto)
	   {
	      ZOOMto=(float)Display.getHeight()/(float)maxCamHeight;
	      ZOOMto=((float)(((((int)(ZOOMto*100))/25)+1)*25))/100.0f;
	            
	      if(ZOOMto<MINZOOM)ZOOMto=MINZOOM;
	      if(ZOOMto>MAXZOOM)ZOOMto=MAXZOOM;
	   }
	}*/
}

void Cameraman::zoomOut()
{ //=========================================================================================================================
	if (ZOOMlock == 0)
	{
		if (ZOOMto > MINZOOM)
		{
			ZOOMto -= ZOOMINCREMENT;
		}
		if (ZOOMto < MINZOOM)
		{
			ZOOMto = MINZOOM;
		}

		runZOOMto = ZOOMto;
	}
}

void Cameraman::zoomIn()
{ //=========================================================================================================================
	if (ZOOMlock == 0)
	{
		if (ZOOMto < MAXZOOM)
		{
			ZOOMto += ZOOMINCREMENT;
		}
		if (ZOOMto > MAXZOOM)
		{
			ZOOMto = MAXZOOM;
		}

		runZOOMto = ZOOMto;
	}
}

void Cameraman::resetZoom()
{ //=========================================================================================================================
	ZOOMto = 2.0f;
	runZOOMto = ZOOMto;
}

void Cameraman::quickZoomOut()
{ //=========================================================================================================================
	//zoom out
	quickZOOMto = 1.0f;

	//TODO: if outside this should be 0.5
}

void Cameraman::quickZoomIn()
{ //=========================================================================================================================
	//zoom in
	quickZOOMto = 3.0f;

	//TODO: do this for conversations
}

void Cameraman::resetQuickZoom()
{ //=========================================================================================================================
	if (quickZOOMto != 0.0f)
	{
		if (quickZOOMto > ZOOMto)
		{
			quickZOOMto -= 0.01f * getEngine()->engineTicksPassed();
			if (quickZOOMto < ZOOMto)
			{
				quickZOOMto = 0.0f;
			}
		}

		if (zoom < ZOOMto)
		{
			quickZOOMto += 0.01f * getEngine()->engineTicksPassed();
			if (quickZOOMto > ZOOMto)
			{
				quickZOOMto = 0.0f;
			}
		}
	}
}

int Cameraman::getXTarget()
{ //=========================================================================================================================
	//=============FIND BOUNDARY TARGETS,CENTER OF THE ROOM IF THE ROOM WILL FIT ONSCREEN,ELSE HALF A SCREEN AWAY FROM THE NEAREST BOUNDARY

	

	int leftbounds = -1;
	int rightbounds = -1;

	int xtarget = -1;

	int SCREEN_WIDTH_TILES = (int)(((getEngine()->getWidth()) / zoom) / tileSize); //width in tiles at current zoom

	int GAME_VIEWPORT_WIDTH_PIXELS = (int)(getEngine()->getWidth() / zoom);

	int mapWidthTiles = getCurrentMap()->getWidthPixelsHQ() / tileSize;


	//TODO: check the fx layer for BOTH left and right/top and bottom of the player (not just the middle), to prevent single tile width camera boundaries from making the camera move for a few frames.
	//prefer the one that is further away

	int playerx = (int)(targetEntity->getX() + (targetEntity->getWidth() / 2.0f));
	int playery = (int)(targetEntity->getY() + (targetEntity->getHeight() / 2.0f));


	for (xtarget = (int)(playerx) / tileSize; xtarget >= 0 && xtarget >= (playerx / tileSize) - (SCREEN_WIDTH_TILES); xtarget--)
	{
		if (getCurrentMap()->getCameraBoundsFXLayerAtXYPixels((float)xtarget * tileSize, (float)playery) == camstop_tile || xtarget == 0)
		{
			leftbounds = (int)((xtarget + 1) * tileSize); //+1 because it's measured by the left edge of the tile: on the right of the tile, the "active" edge is offset by the width of the tile itself
			break;
		}
	}


	for (xtarget = (int)(playerx) / tileSize; xtarget < mapWidthTiles && xtarget <= (playerx / tileSize) + (SCREEN_WIDTH_TILES); xtarget++)
	{
		if (getCurrentMap()->getCameraBoundsFXLayerAtXYPixels((float)xtarget * tileSize, (float)playery) == camstop_tile || xtarget == mapWidthTiles - 1)
		{
			rightbounds = (int)(xtarget * tileSize);
			break;
		}
	}

	xtarget = -1;

	if (leftbounds != -1 || rightbounds != -1)
	{
		if (leftbounds != -1 && rightbounds != -1 && rightbounds - leftbounds <= GAME_VIEWPORT_WIDTH_PIXELS)
		{
			xtarget = (leftbounds + ((rightbounds - leftbounds) / 2));
		}
		else
		{
			if (leftbounds != -1 && playerx <= leftbounds + GAME_VIEWPORT_WIDTH_PIXELS / 2)
			{
				xtarget = (leftbounds + GAME_VIEWPORT_WIDTH_PIXELS / 2);
			}
			else
			{
				if (rightbounds != -1 && playerx >= rightbounds - GAME_VIEWPORT_WIDTH_PIXELS / 2)
				{
					xtarget = (rightbounds - GAME_VIEWPORT_WIDTH_PIXELS / 2);
				}
			}
		}
	}


	lastXTarget = xtarget;
	if (xtarget == -1 || ignoreCameraFXBoundaries == true)
	{
		xtarget = playerx;
	}

	return xtarget;
}

int Cameraman::getYTarget()
{ //=========================================================================================================================

	//=============FIND BOUNDARY TARGETS,CENTER OF THE ROOM IF THE ROOM WILL FIT ONSCREEN,ELSE HALF A SCREEN AWAY FROM THE NEAREST BOUNDARY
	int topbounds = -1;
	int bottombounds = -1;

	int ytarget = -1;

	int statusBarSize = 0;

	if (dynamic_cast<BGClientEngine*>(getEngine()) != NULL)
	// if (getEngine()->getClass().equals(BGClientEngine::typeid))
	{
		//statusBarSize = StatusBar::sizeY;
	}


	int SCREEN_HEIGHT_TILES = (int)(((getEngine()->getHeight()) / zoom) / tileSize);

	int GAME_VIEWPORT_HEIGHT_PIXELS = (int)((int)(getEngine()->getHeight() / zoom) - statusBarSize);

	int mapHeightTiles = getCurrentMap()->getHeightPixelsHQ() / tileSize;


	//TODO: check the fx layer for BOTH left and right/top and bottom of the player (not just the middle), to prevent single tile width camera boundaries from making the camera move for a few frames.
	//prefer the one that is further away

	int playerx = (int)(targetEntity->getX() + (targetEntity->getWidth() / 2.0f));
	int playery = (int)(targetEntity->getY() + (targetEntity->getHeight() / 2.0f));


	for (ytarget = (int)(playery) / tileSize; ytarget >= 0 && ytarget >= (playery / tileSize) - (SCREEN_HEIGHT_TILES); ytarget--)
	{
		if (getCurrentMap()->getCameraBoundsFXLayerAtXYPixels((float)playerx, (float)ytarget * tileSize) == camstop_tile || ytarget == 0)
		{
			topbounds = (int)((ytarget + 1) * tileSize);
			break;
		}
	}

	for (ytarget = (int)(playery) / tileSize; ytarget < mapHeightTiles && ytarget <= (playery / tileSize) + (SCREEN_HEIGHT_TILES); ytarget++)
	{
		if (getCurrentMap()->getCameraBoundsFXLayerAtXYPixels((float)playerx, (float)ytarget * tileSize) == camstop_tile || ytarget == mapHeightTiles - 1)
		{
			bottombounds = (int)(ytarget * tileSize);
			break;
		}
	}

	ytarget = -1;

	if (topbounds != -1 || bottombounds != -1)
	{
		if (topbounds != -1 && bottombounds != -1 && bottombounds - topbounds <= GAME_VIEWPORT_HEIGHT_PIXELS)
		{
			ytarget = (topbounds + ((bottombounds - topbounds) / 2));
		}
		else
		{
			if (topbounds != -1 && playery <= topbounds + GAME_VIEWPORT_HEIGHT_PIXELS / 2)
			{
				ytarget = (topbounds + GAME_VIEWPORT_HEIGHT_PIXELS / 2);
			}
			else
			{
				if (bottombounds != -1 && playery >= bottombounds - GAME_VIEWPORT_HEIGHT_PIXELS / 2)
				{
					ytarget = (bottombounds - GAME_VIEWPORT_HEIGHT_PIXELS / 2);
				}
			}
		}
	}

	lastYTarget = ytarget;

	if (ytarget == -1 || ignoreCameraFXBoundaries == true)
	{
		ytarget = playery;
	}

	//TODO: adjust this based on status bar position
	ytarget -= statusBarSize / 2;

	return ytarget;
}

int Cameraman::getMaxCameraBoundaryWidth()
{ //=========================================================================================================================

	//we want to go from player x to 0, checking for camstop tiles. leftBounds = camstop tile OR 0.
	//this is different from below because it doesn't stop at the edge of the visible screen.

	int leftbounds = -1;
	int rightbounds = -1;

	int xtarget = -1;


	int playerx = (int)(targetEntity->getX() + (targetEntity->getWidth() / 2));
	int playery = (int)(targetEntity->getY() + (targetEntity->getHeight() / 2));

	int mapWidthTiles = getCurrentMap()->getWidthPixelsHQ() / tileSize;
	//int mapHeightTiles = map().heightPixelsHQ2X/tileSize;


	for (xtarget = (int)(playerx / tileSize); xtarget >= 0; xtarget--)
	{
		//TODO: this could actually go by increments of two tiles (or 16 pixels), since every other tile is redundant (get_fx_layer rounds down), since map is hq2x

		if (getCurrentMap()->getCameraBoundsFXLayerAtXYPixels((float)xtarget * tileSize, (float)playery) == camstop_tile)
		{
			leftbounds = (xtarget + 1) * tileSize;
			break;
		}
	}


	for (xtarget = (int)(playerx / tileSize); xtarget < mapWidthTiles; xtarget++)
	{
		int fxtile = getCurrentMap()->getCameraBoundsFXLayerAtXYPixels((float)xtarget * tileSize, (float)playery);
		if (fxtile == camstop_tile)
		{
			rightbounds = xtarget * tileSize;
			break;
		}
	}

	return rightbounds - leftbounds;
}

int Cameraman::getMaxCameraBoundaryHeight()
{ //=========================================================================================================================

	//we want to go from player x to 0, checking for camstop tiles. leftBounds = camstop tile OR 0.
	//this is different from below because it doesn't stop at the edge of the visible screen.

	int topbounds = -1;
	int bottombounds = -1;

	int ytarget = -1;


	int playerx = (int)(targetEntity->getX() + (targetEntity->getWidth() / 2));
	int playery = (int)(targetEntity->getY() + (targetEntity->getHeight() / 2));

	//int mapWidthTiles = map().widthPixelsHQ2X/tileSize;
	int mapHeightTiles = getCurrentMap()->getHeightPixelsHQ() / tileSize;


	for (ytarget = (int)(playery / tileSize); ytarget >= 0; ytarget--)
	{
		if (getCurrentMap()->getCameraBoundsFXLayerAtXYPixels((float)playerx, (float)ytarget * tileSize) == camstop_tile)
		{
			topbounds = (int)((ytarget + 1) * tileSize);
			break;
		}
	}


	for (ytarget = (int)(playery / tileSize); ytarget < mapHeightTiles; ytarget++)
	{
		if (getCurrentMap()->getCameraBoundsFXLayerAtXYPixels((float)playerx, (float)ytarget * tileSize) == camstop_tile)
		{
			bottombounds = (int)(ytarget * tileSize);
			break;
		}
	}

	return bottombounds - topbounds;
}

int Cameraman::getMapWidthBasedOnCameraBoundsFromEdge()
{ //=========================================================================================================================


	return 0;
}

int Cameraman::getMapHeightBasedOnCameraBoundsFromEdge()
{ //=========================================================================================================================


	return 0;
}

void Cameraman::setXYToTarget()
{ //=========================================================================================================================
	setX(targetEntity->getX() + (targetEntity->getWidth() / 2));
	setY(targetEntity->getY() + (targetEntity->getHeight() / 2));
}

void Cameraman::setTarget(Entity* t)
{ //=========================================================================================================================
	if (t == nullptr)
	{
		t = getPlayer();
	}

	if (t == nullptr)
	{
		setDummyTarget();
	}
	else
	{
		targetEntity = t;
	}
}

void Cameraman::setTarget(float mapXPixelsHQ, float mapYPixelsHQ)
{ //=========================================================================================================================
	targetEntity = new Entity(getEngine(), new EntityData(-1, "Null Target", "", (int)mapXPixelsHQ / 2, (int)mapYPixelsHQ / 2));
}

void Cameraman::setTarget(Area* area)
{ //=========================================================================================================================
	targetEntity = new Entity(getEngine(), new EntityData(-1, "Null Target", "", (int)area->middleX() / 2, (int)area->middleY() / 2));
}

void Cameraman::setDummyTarget()
{ //=========================================================================================================================
	targetEntity = this; //new Entity(getEngine(),new EntityData(-1,"Null Target","",getX(),getY()));
}

void Cameraman::setAutoZoomByPlayerMovement(bool b)
{ //=========================================================================================================================
	autoZoomByPlayerMovementEnabled = b;
}

void Cameraman::setPlayerCanZoomManuallyWithKeyboard(bool b)
{ //=========================================================================================================================
	zoomManuallyEnabled = b;
}

