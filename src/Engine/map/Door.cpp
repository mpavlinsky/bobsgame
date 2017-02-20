#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger Door::log = Logger("Door");


Door::Door(Engine* g, DoorData* doorAsset)
{ //=========================================================================================================================

	this->e = g;

	initEntity(doorAsset);

	this->data = doorAsset;


	if (getEventID() != -1)
	{
		Event* e = getEventManager()->getEventByIDCreateIfNotExist(getEventID());
		e->door = this;
	}
}

bool Door::isOpen()
{
	return open;
}

void Door::setOpenManually(bool b)
{
	if (b == true)
	{
		this->open = true;
		this->stayOpen = true;

		resetAnimationTimer();
		setNonWalkable(false);
	}
	else
	{
		//update will do the closing animation

		this->stayOpen = false;

		resetAnimationTimer();
		setNonWalkable(true);
	}
}

void Door::setOpenAnimation(bool b)
{
	if (b == true)
	{
		this->open = true;
	}
	else
	{
		//update will do the closing animation
	}
}

void Door::update()
{ //=========================================================================================================================


	Entity::update();


	//getPreload connecting map

	long long startTime = lastRequestedMapDataTime;
	long long currentTime = System::currentHighResTimer();
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	if (ticksPassed > 5000)
	{
		lastRequestedMapDataTime = currentTime;

		if (destinationMapName().length() > 0)
		{
			getMapManager()->requestMapDataIfNotLoadedYet(destinationMapName());
		}
	}


	//super.update() will load and initialize the spriteAsset doorData.
	if (sprite == nullptr)
	{
		return;
	}


	if (sprite != nullptr)
	{
		this->doorknobX = sprite->getUtilityOffsetXPixelsHQ();
		this->doorknobY = sprite->getUtilityOffsetYPixelsHQ();
	}


	//DONE: handle door opening animation

	if (open == true)
	{
		//if we aren't at the last frame, increment the frames until the last frame, starting at the current frame.

		if (haveTicksPassedSinceLastAnimated_ResetIfTrue(80))
		{
			if (getFrame() < getSpriteLastFrame())
			{
				incrementAnimationFrameInAllFrames();
			}
			else
			{
				if (stayOpen == false)
				{
					open = false;
				}
			}
		}
	}

	if (open == false)
	{
		//if we aren't at the first frame, decrement the frames until the first frame, starting at the current frame.

		if (haveTicksPassedSinceLastAnimated_ResetIfTrue(80))
		{
			if (getFrame() > 0)
			{
				setFrame(getFrame() - 1);
			}
		}
	}


	if (getMap() == getEngine()->getCurrentMap())
	{
		//handle random spawn point
		if (randomNPCSpawnPoint() && getMap()->randomSpawnEnabled)
		{
			//TODO: make this within screen bounds AND AMOUNT, two screens over?
			if (getMap()->isXYWithinScreenByAmt(getMiddleX(), getMiddleY(), 128) == true)
			{
				ticksSinceSpawnTry += getEngine()->engineTicksPassed();

				if (ticksSinceSpawnTry >= randomSpawnDelay())
				{
					ticksSinceSpawnTry = 0;

					if (Math::random() < randomSpawnChance()) // this is correct.
					{
						//TODO: don't spawn if there are too many randoms, have map limit?


						ArrayList<string>* targetTYPEIDList = new ArrayList<string>();

						//if this door has connections, set target to one of this door's connections
						if (getConnectionTYPEIDList()->size() > 0)
						{
							for (int i = 0; i < getConnectionTYPEIDList()->size(); i++)
							{
								targetTYPEIDList->add(getConnectionTYPEIDList()->get(i));
							}
						}
						else
						{
							targetTYPEIDList = getMap()->getListOfRandomPointsOfInterestTYPEIDs();
						}


						if (targetTYPEIDList->size() > 0)
						{
							//don't spawn if all the possible random points are full

							while (targetTYPEIDList->size() > 0)
							{
								int i = Math::randLessThan(targetTYPEIDList->size());

								//don't count this door
								if (targetTYPEIDList->get(i) == string("DOOR.") + getName())
								{
									targetTYPEIDList->removeAt(i);
									continue;
								}

								bool canMakeRandom = false;

								//if there is another exit, keep pumping out randoms, they will go there.
								if (String::startsWith(targetTYPEIDList->get(i), "DOOR."))
								{
									canMakeRandom = true;
								}
								else
								{
									//else we should check to make sure there is a random point of interest to go to, otherwise he will have nowhere to go and just stand there.
									Area* a = getMap()->getAreaOrWarpAreaByTYPEID(targetTYPEIDList->get(i));

									if (a != nullptr)
									{
										if (getMap()->findOpenSpaceInArea(a, 32, 32) == nullptr)
										//entMan().isAnyoneStandingInArea(a)==true
										//||
										//entMan().isAnyoneTryingToGoToArea(a)==true
										//||
										{
											targetTYPEIDList->removeAt(i);
											continue;
										}
										else
										{
											canMakeRandom = true;
										}
									}
									else
									{
										targetTYPEIDList->removeAt(i);
										//this is a serious error, prints out on System.err in getAreaOrWarpAreaByName
									}
								}

								if (canMakeRandom == true)
								{
									RandomCharacter* r = new RandomCharacter(getEngine(), getMap(), (int)(arrivalXPixelsHQ() + 8) / 2, (int)(arrivalYPixelsHQ() + 8) / 2, randomSpawnKids(), randomSpawnAdults(), randomSpawnMales(), randomSpawnFemales(), false);
									r->currentAreaTYPEIDTarget = targetTYPEIDList->get(i);
									r->cameFrom = string("DOOR.") + getName();
									targetTYPEIDList->clear();
									open = true;
								}
							}
						}
					}
				}
			}
		}
	}
}

void Door::enter()
{ //=========================================================================================================================

	//go through mapMan().doorList and find door.mapAsset=destinationMapAsset and door.entityNameIdentifier=destinationDoorName, get arrival x and arrival y

	//if(open==false&&spriteAsset.frames>1)setDoorAnim("opening");


	if (destinationTYPEIDString() == "" || destinationTYPEIDString().length() == 0 || destinationTYPEIDString() == string("DOOR.") + to_string(getID()))
	{
		//if action held

		if (getControlsManager()->BGCLIENT_ACTION_HELD)
		{
			if (openingButtonHeld == false)
			{
				openingButtonHeld = true;

				if (open == false)
				{
					setOpenManually(true);
				}
				else
				{
					setOpenManually(false);
				}
			}
		}
		else
		{
			openingButtonHeld = false;
		}
	}
	else
	{
		Map* map = getMapManager()->getMapByNameBlockUntilLoaded(destinationMapName());


		for (int i = 0; i < (int)map->doorList.size(); i++)
		{
			Door* d = map->doorList.get(i);

			if (d->getName() == destinationDoorName())
			{
				open = true;

				getMapManager()->doorEntered = this;
				getMapManager()->doorExited = d;

				d->open = true;

				//TODO: do I want the other door open?
				//TODO: do I want this door to be open immediately?
				//TODO: do I want them in sync?
				//TODO: test these combinations
				setFrame(getSpriteLastFrame()); //set to open frame.
				resetAnimationTimer();

				getMapManager()->changeMap(destinationMapName(), (int)(d->arrivalXPixelsHQ()) + 8, (int)(d->arrivalYPixelsHQ()) + 8);
				return;
			}
		}
	}
}

void Door::renderActionIcon()
{ //=========================================================================================================================

	if (open)
	{
		return;
	}

	if (showActionIcon == false)
	{
		return;
	}

	//get distance from player

	BobTexture* actionTexture = getSpriteManager()->actionTexture;

	if (actionTexture == nullptr)
	{
		return;
	}

	float doorAlpha = 1.0f;

	if (this->isEntityHitBoxTouchingMyHitBoxByAmount(getPlayer(), 256) == false)
	{
		return;
	}

	doorAlpha = (256.0f - this->getDistanceFromEntity(getPlayer())) / 256.0f;
	if (doorAlpha > 1.0f)
	{
		doorAlpha = 1.0f;
	}


	float tx0 = 0.0f;
	float tx1 = 32.0f / ((float)(actionTexture->getTextureWidth()));
	float ty0 = (float)(32.0f * getSpriteManager()->actionTextureFrame) / ((float)(actionTexture->getTextureHeight()));
	float ty1 = (float)(32.0f * (getSpriteManager()->actionTextureFrame + 1)) / ((float)(actionTexture->getTextureHeight()));


	float zoom = getCameraman()->getZoom();

	float x0 = getScreenLeft() - (16.0f * zoom) + (doorknobX * zoom);
	float x1 = getScreenLeft() + (16.0f * zoom) + (doorknobX * zoom);
	float y0 = getScreenTop() - (16.0f * zoom) + (doorknobY * zoom);
	float y1 = getScreenTop() + (16.0f * zoom) + (doorknobY * zoom);

	GLUtils::drawTexture(actionTexture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, doorAlpha, GLUtils::FILTER_LINEAR);
}

void Door::renderDebugBoxes()
{ //=========================================================================================================================
	float zoom = getCameraman()->getZoom();

	float screenRight = getScreenLeft() + (getWidth() * zoom);
	float screenBottom = getScreenTop() + (getHeight() * zoom);


	//outline
	GLUtils::drawBox(getScreenLeft(), screenRight - 1, getScreenTop(), screenBottom - 1, 0, 255, 0); //-1 so the box is inside one pixel

	//hitbox
	GLUtils::drawBox(getScreenLeft() + (getHitBoxFromLeft() * zoom), (screenRight - (getHitBoxFromRight() * zoom)) - 1, getScreenTop() + (getHitBoxFromTop() * zoom), (screenBottom - (getHitBoxFromBottom() * zoom)) - 1, 255, 0, 0);


	{
		//arrival point
		float ax = getMap()->getScreenX((float)arrivalXPixelsHQ(), 16);
		float ay = getMap()->getScreenY((float)arrivalYPixelsHQ(), 16);

		GLUtils::drawBox(ax, ax + (16 * zoom) - 1, ay, ay + (16 * zoom) - 1, 200, 0, 255);

		GLUtils::drawLine(getScreenLeft() + (getWidth() / 2) * zoom, getScreenTop() + (getHeight() / 2) * zoom, ax + (8 * zoom), ay + (8 * zoom), 255, 255, 255);
	}


	for (int i = 0; i < getConnectionTYPEIDList()->size(); i++)
	{
		//draw connections to doors
		if (String::startsWith(getConnectionTYPEIDList()->get(i), "DOOR."))
		{
			//go through doorlist
			for (int d = 0; d < (int)getMap()->doorList.size(); d++)
			{
				Door* door = getMap()->doorList.get(d);
				if (door->getMap() == getMap())
				{
					if (getConnectionTYPEIDList()->get(i) == string("DOOR.") + door->getName())
					{
						float dx = door->getScreenLeft() + (door->getWidth() / 2) * zoom;
						float dy = door->getScreenTop() + (door->getHeight()) * zoom;

						GLUtils::drawArrowLine(getScreenLeft() + (getWidth() / 2) * zoom, getScreenTop() + (getHeight() / 2) * zoom, dx, dy, 0, 255, 0);
					}
				}
			}
		}
		else
		{
			//draw connections to areas
			//go through area hashlist
			//         java::util::Iterator<Area*> aEnum = getMap()->currentState->areaByNameHashtable.elements();
			//         //areas
			//         while (aEnum->hasMoreElements())
			//         {
			//            Area* a = aEnum->nextElement();

			ArrayList<Area*> *areas = getMap()->currentState->areaByNameHashtable.getAllValues();
			for (int i = 0; i<areas->size(); i++)
			{
				Area* a = areas->get(i);

				if (getConnectionTYPEIDList()->get(i) == a->getName())
				{
					float ax = a->screenLeft() + (a->getWidth() / 2) * zoom;
					float ay = a->screenTop() + (a->getHeight() / 2) * zoom;

					GLUtils::drawArrowLine(getScreenLeft() + (getWidth() / 2) * zoom, getScreenTop() + (getHeight() / 2) * zoom, ax, ay, 0, 255, 0);
				}
			}

			//if not found, go through warparea list
			for (int j = 0; j < (int)getMap()->warpAreaList.size(); j++)
			{
				Area* a = getMap()->warpAreaList.get(j);

				if (getConnectionTYPEIDList()->get(i) == a->getName())
				{
					float ax = a->screenLeft() + (a->getWidth() / 2) * zoom;
					float ay = a->screenTop() + (a->getHeight() / 2) * zoom;

					GLUtils::drawArrowLine(getScreenLeft() + (getWidth() / 2) * zoom, getScreenTop() + (getHeight() / 2) * zoom, ax, ay, 0, 255, 0);
				}
			}
		}
	}
}

void Door::renderDebugInfo()
{ //=========================================================================================================================


	float x = (getScreenLeft());
	float y = (getScreenTop());


	int strings = -1;


	GLUtils::drawOutlinedString(string("entityID: ") + getName(), x, y - 18, BobColor::yellow);


	GLUtils::drawOutlinedString(string("assetName: ") + sprite->getName(), x, y - 9, BobColor::white);


	GLUtils::drawOutlinedString(string("getDestinationTYPEIDString: ") + destinationTYPEIDString(), x, y + (++strings * 9), new BobColor(200, 0, 255));

	if (destinationTYPEIDString() == string("DOOR.") + to_string(getID()) || destinationTYPEIDString() == "" || destinationTYPEIDString() == "none" || destinationTYPEIDString() == "self")
	{
		GLUtils::drawOutlinedString("Has no destination!", x, y + (++strings * 9), BobColor::red);
	}
	//else
	GLUtils::drawOutlinedString(string("Goes to: ") + destinationMapName() + string(".") + destinationDoorName(), x, y + (++strings * 9), new BobColor(200, 0, 255));


	if (randomNPCSpawnPoint())
	{
		GLUtils::drawOutlinedString(string("Random Spawn Point | Chance: ") + to_string(randomSpawnChance()), x, y + (++strings * 9), BobColor::magenta);
	}

	if (randomNPCSpawnPoint())
	{
		GLUtils::drawOutlinedString(string("Spawn Delay: ") + to_string(randomSpawnDelay()), x, y + (++strings * 9), BobColor::white);
	}

	if (randomNPCSpawnPoint())
	{
		string allowedTypes = "";
		if (randomSpawnKids())
		{
			allowedTypes = allowedTypes + string(" Kids");
		}
		if (randomSpawnAdults())
		{
			allowedTypes = allowedTypes + string(" Adults");
		}
		if (randomSpawnMales())
		{
			allowedTypes = allowedTypes + string(" Males");
		}
		if (randomSpawnFemales())
		{
			allowedTypes = allowedTypes + string(" Females");
		}
		GLUtils::drawOutlinedString(string("Spawn Types: ") + allowedTypes, x, y + (++strings * 9), BobColor::magenta);
	}

	if (randomPointOfInterestOrExit())
	{
		GLUtils::drawOutlinedString("Random Exit (Point Of Interest)", x, y + (++strings * 9), BobColor::white);
	}


	/*
	               
	               
	int getArrivalXPixelsHQ=0;
	int getArrivalYPixelsHQ=0;
	               
	boolean isRandomNPCSpawnPoint;
	float getRandomSpawnChance;
	boolean randomExit;
	int getRandomSpawnDelay;
	boolean getRandomSpawnKids;
	boolean getRandomSpawnAdults;
	boolean getRandomSpawnMales;
	boolean getRandomSpawnFemales;
	               
	               
	ArrayList<String> getBehaviorList = new ArrayList<String>();
	ArrayList<String> connectionList = new ArrayList<String>();
	               
	               */
}

EntityData* Door::getData()
{
	return data;
}

DoorData* Door::getDoorData()
{
	return ((DoorData*)getData());
}

float Door::arrivalXPixelsHQ()
{
	return getDoorData()->getArrivalXPixelsHQ();
}

float Door::arrivalYPixelsHQ()
{
	return getDoorData()->getArrivalYPixelsHQ();
}

string Door::destinationTYPEIDString()
{
	if (getDoorData()->getDestinationTYPEIDString() == "" || getDoorData()->getDestinationTYPEIDString().length() == 0)
	{
		getDoorData()->setDestinationTYPEIDString(getTYPEIDString());
	}
	return getDoorData()->getDestinationTYPEIDString();
}

string Door::destinationMapName()
{
	return getDoorData()->getDestinationMapName();
}

string Door::destinationDoorName()
{
	return getDoorData()->getDestinationDoorName();
}

bool Door::randomPointOfInterestOrExit()
{
	return getDoorData()->getRandomPointOfInterestOrExit();
}

bool Door::randomNPCSpawnPoint()
{
	return getDoorData()->getRandomNPCSpawnPoint();
}

float Door::randomSpawnChance()
{
	return getDoorData()->getRandomSpawnChance();
}

int Door::randomSpawnDelay()
{
	return getDoorData()->getRandomSpawnDelay();
}

bool Door::randomSpawnKids()
{
	return getDoorData()->getRandomSpawnKids();
}

bool Door::randomSpawnAdults()
{
	return getDoorData()->getRandomSpawnAdults();
}

bool Door::randomSpawnMales()
{
	return getDoorData()->getRandomSpawnMales();
}

bool Door::randomSpawnFemales()
{
	return getDoorData()->getRandomSpawnFemales();
}

void Door::setDestinationTYPEIDString(const string& typeID)
{
	getDoorData()->setDestinationTYPEIDString(typeID);
}

void Door::setRandomPointOfInterestOrExit(bool s)
{
	getDoorData()->setRandomPointOfInterestOrExit(s);
}

void Door::setRandomNPCSpawnPoint(bool s)
{
	getDoorData()->setRandomNPCSpawnPoint(s);
}

void Door::setRandomSpawnChance(float s)
{
	getDoorData()->setRandomSpawnChance(s);
}

void Door::setRandomSpawnDelay(int s)
{
	getDoorData()->setRandomSpawnDelay(s);
}

void Door::setRandomSpawnKids(bool s)
{
	getDoorData()->setRandomSpawnKids(s);
}

void Door::setRandomSpawnAdults(bool s)
{
	getDoorData()->setRandomSpawnAdults(s);
}

void Door::setRandomSpawnMales(bool s)
{
	getDoorData()->setRandomSpawnMales(s);
}

void Door::setRandomSpawnFemales(bool s)
{
	getDoorData()->setRandomSpawnFemales(s);
}

void Door::setArrivalXPixels(int s)
{
	getDoorData()->setArrivalXPixels1X(s);
}

void Door::setArrivalYPixels(int s)
{
	getDoorData()->setArrivalYPixels1X(s);
}

