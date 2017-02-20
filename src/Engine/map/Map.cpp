
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger Map::log = Logger("Map");


//java::util::concurrent::ExecutorService* Map::generatePNGExecutorService = nullptr;
//java::util::concurrent::ExecutorService* Map::generateLightPNGExecutorService = nullptr;


//=========================================================================================================================
Map::Map()
{//=========================================================================================================================

	//chunkTexture = new HashMap<int, BobTexture*>();
}


//=========================================================================================================================
Map::Map(Engine* g, MapData* mapData)
{ //=========================================================================================================================

	//chunkTexture = new HashMap<int, BobTexture*>();

	initMap(g, mapData);

}


//=========================================================================================================================
void Map::initMap(Engine* g, MapData* mapData)
{
	e = g;

	data = mapData;


	//determine number of chunks horizontal and vertical

	//TODO: make this proper with modulus, if the split is even there will be one extra chunk
	chunksWidth = (mapData->getWidthTiles1X() / chunkSizeTiles1X) + 1;
	chunksHeight = (mapData->getHeightTiles1X() / chunkSizeTiles1X) + 1;

	//   if (chunkTexture.isEmpty())
	//   {
	//      chunkTexture = new ArrayList<Texture*>(chunksWidth * chunksHeight * 2); // *2 for over/under layer
	//      for (int i = 0; i < chunksWidth * chunksHeight * 2; i++)
	//      {
	//         //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//         delete chunkTexture.get(i);
	//      }
	//   }

	if (chunkPNGFileExists == nullptr)
	{
		chunkPNGFileExists = new bool[(chunksWidth * chunksHeight * 2)];
		for (int i = 0; i < chunksWidth * chunksHeight * 2; i++)
		{
			chunkPNGFileExists[i] = false;
		}
	}

	if (hq2xChunkPNGFileExists == nullptr)
	{
		hq2xChunkPNGFileExists = new bool[(chunksWidth * chunksHeight * 2)];
		for (int i = 0; i < chunksWidth * chunksHeight * 2; i++)
		{
			hq2xChunkPNGFileExists[i] = false;
		}
	}

	if (usingHQ2XTexture == nullptr)
	{
		usingHQ2XTexture = new bool[(chunksWidth * chunksHeight * 2)];
		for (int i = 0; i < chunksWidth * chunksHeight * 2; i++)
		{
			usingHQ2XTexture[i] = false;
		}
	}


	//need to run through mapData structure and create entities, events, lights, areas, doors, states, warpareas


	for (int i = 0; i < (int)mapData->getEventDataList()->size(); i++)
	{
		//create event, add to eventList
		EventData* eventData = mapData->getEventDataList()->get(i);


		Event* event = nullptr;

		for (int k = 0; k < (int)getEventManager()->eventList.size(); k++)
		{
			if (getEventManager()->eventList.get(k)->getID() == eventData->getID())
			{
				event = getEventManager()->eventList.get(k);
			}
		}

		if (event == nullptr)
		{
			event = new Event(getEngine(), eventData);
		}

		mapEventIDList.add(event->getID());
	}


	for (int i = 0; i < (int)mapData->getDoorDataList()->size(); i++)
	{
		//create door, add to doorList,

		DoorData* doorData = mapData->getDoorDataList()->get(i);
		Door* door = new Door(getEngine(), doorData);


		//TODO: in door update, send command to load door connecting map, it will return as a network thread, create the map object, block that thread until it is loaded.
		//also check and make sure it is sending event update

		doorList.add(door);
	}


	for (int i = 0; i < (int)mapData->getStateDataList()->size(); i++)
	{
		MapStateData* mapStateData = mapData->getStateDataList()->get(i);


		//create state, add to state list.
		MapState* mapState = new MapState(mapStateData);

		stateList.add(mapState);


		for (int n = 0; n < (int)mapStateData->getAreaDataList()->size(); n++)
		{
			AreaData* areaData = mapStateData->getAreaDataList()->get(n);

			if (areaData->getIsWarpArea())
			{
				//create warparea, add to warpAreaList
				WarpArea* warpArea = new WarpArea(getEngine(), areaData);

				//TODO: in door update, send command to load door connecting map, it will return as a network thread, create the map object, block that thread until it is loaded.
				//also check and make sure it is sending event update

				warpAreaList.add(warpArea);
				//note that warp areas DON'T get added to the currentMap.areaHashmap.
				//i go through each map and search for the appropriate warparea in that list
			}
			else
			{
				Area* area = new Area(getEngine(), areaData);
				mapState->areaByNameHashtable.put(area->getName(), area);
				mapState->areaByTYPEIDHashtable.put(area->getTYPEIDString(), area);
				mapState->areaList.add(area);
			}
		}


		for (int n = 0; n < (int)mapStateData->getLightDataList()->size(); n++)
		{
			LightData* lightData = mapStateData->getLightDataList()->get(n);
			Light* light = new Light(getEngine(), lightData);


			mapState->lightList.add(light);
			mapState->lightByNameHashtable.put(light->getName(), light);
		}


		for (int n = 0; n < (int)mapStateData->getEntityDataList()->size(); n++)
		{
			EntityData* entityData = mapStateData->getEntityDataList()->get(n);

			if (entityData->getIsNPC())
			{
				Character* character = new Character(getEngine(), entityData);

				mapState->characterList.add(character);
				mapState->characterByNameHashtable.put(character->getName(), character);
			}
			else
			{
				Entity* entity = new Entity(getEngine(), entityData);

				mapState->entityList.add(entity);
				mapState->entityByNameHashtable.put(entity->getName(), entity);
			}
		}
	}


	//get load event, run it to determine which state to load. (done in update)
}


//=========================================================================================================================
Entity* Map::getEntityByName(const string& name)
{ //=========================================================================================================================
	Entity* e = currentState->entityByNameHashtable.get(name);

	if (e == nullptr)
	{
		e = getCharacterByName(name);
	}

	if (e == nullptr)
	{
		for (int i = 0; i < activeEntityList.size(); i++)
		{
			if (activeEntityList.get(i)->getName() == name)
			{
				e = activeEntityList.get(i);
			}
		}
	}

	if (e == nullptr)
	{
		for (int i = 0; i < (int)getSpriteManager()->screenSpriteList.size(); i++)
		{
			if (getSpriteManager()->screenSpriteList.get(i)->getName().compare(name) == 0)
			{
				e = getSpriteManager()->screenSpriteList.get(i);
			}
		}
	}

	if (e == nullptr)
	{
		e = getLightByName(name);
	}

	return e;
}


//=========================================================================================================================
Character* Map::getCharacterByName(const string& name)
{ //=========================================================================================================================
	return currentState->characterByNameHashtable.get(name);
}


//=========================================================================================================================
Light* Map::getLightByName(const string& name)
{ //=========================================================================================================================

	//log.debug("getLightByName: "+name);

	return currentState->lightByNameHashtable.get(name);
}


//=========================================================================================================================
Area* Map::getAreaOrWarpAreaByName(string name)
{ //=========================================================================================================================


	//log.debug("getAreaOrWarpAreaByName: "+name);

	if (String::startsWith(name, "AREA."))
	{
		name = name.substr(name.find(".") + 1);
	}


	Area* a = nullptr;
	if (currentState != nullptr)
	{
		a = currentState->areaByNameHashtable.get(name);
	}

	if (a == nullptr)
	{
		for (int i = 0; i < stateList.size(); i++)
		{
			MapState* s = stateList.get(i);
			a = s->areaByNameHashtable.get(name);
			if (a != nullptr)
			{
				break;
			}
		}
	}

	if (a == nullptr)
	{
		for (int i = 0; i < warpAreaList.size(); i++)
		{
			if (warpAreaList.get(i)->getName() == name)
			{
				a = warpAreaList.get(i);
			}
		}
	}

	if (a == nullptr)
	{
		log.error(string("Could not find Area/WarpArea: getAreaOrWarpAreaByName() Name:") + name);
	}


	return a;
}

Area* Map::getAreaOrWarpAreaByTYPEID(string typeID)
{ //=========================================================================================================================


	//log.debug("getAreaOrWarpAreaByName: "+name);

	if (String::startsWith(typeID, "AREA.") == false)
	{
		typeID = string("AREA.") + typeID;
	}


	Area* a = nullptr;
	if (currentState != nullptr)
	{
		a = currentState->areaByTYPEIDHashtable.get(typeID);
	}

	if (a == nullptr)
	{
		for (int i = 0; i < warpAreaList.size(); i++)
		{
			if (warpAreaList.get(i)->getTYPEIDString() == typeID)
			{
				a = warpAreaList.get(i);
			}
		}
	}

	if (a == nullptr)
	{
		for (int i = 0; i < stateList.size(); i++)
		{
			MapState* s = stateList.get(i);
			a = s->areaByTYPEIDHashtable.get(typeID);
			if (a != nullptr)
			{
				break;
			}
		}
	}


	if (a == nullptr)
	{
		log.debug(string("Could not find Area/WarpArea: getAreaOrWarpAreaByTYPEID() TypeID:") + typeID);
	}


	return a;
}

Door* Map::getDoorByTYPEID(const string& typeID_in)
{ //=========================================================================================================================

	string typeID = typeID_in;
	//log.debug("getDoorByName: "+name);

	if (String::startsWith(typeID, "DOOR.") == false)
	{
		typeID = string("DOOR.") + typeID;
	}

	//doors
	//for(int n=0;n<MapAssetIndex.mapList.size();n++)
	{
		//MapAsset m = MapAssetIndex.mapList.get(n);

		for (int i = 0; i < doorList.size(); i++)
		{
			Door* d = doorList.get(i);

			if (typeID == d->getTYPEIDString())
			{
				return d;
			}
		}
	}

	log.error(string("Could not find Door: getDoorByTYPEID() TypeID:") + typeID);

	return nullptr;
}

Door* Map::getDoorByName(const string& name_in)
{ //=========================================================================================================================

	string name = name_in;

	//log.debug("getDoorByName: "+name);

	if (String::startsWith(name, "DOOR."))
	{
		name = name.substr(name.find(".") + 1);
	}

	//doors
	//for(int n=0;n<MapAssetIndex.mapList.size();n++)
	{
		//MapAsset m = MapAssetIndex.mapList.get(n);

		for (int i = 0; i < doorList.size(); i++)
		{
			Door* d = doorList.get(i);

			if (name == d->getName())
			{
				return d;
			}
		}
	}

	log.error(string("Could not find Door: getDoorByName(): ") + name);

	return nullptr;
}

MapState* Map::getMapStateByName(const string& name)
{ //=========================================================================================================================
	for (int i = 0; i < stateList.size(); i++)
	{
		MapState* mapState = stateList.get(i);

		if (name == mapState->getName())
		{
			return mapState;
		}
	}


	//we didn't find it. make a new one. throw an error.
	log.error(string("Could not find Map State:") + name + string(". This should never happen."));

	//MapState s = new MapState(-1,name);
	//stateList.add(s);


	return nullptr;
}

MapState* Map::getMapStateByID(int id)
{ //=========================================================================================================================
	//this should look through the current map mapStateList first
	for (int i = 0; i < stateList.size(); i++)
	{
		MapState* s = stateList.get(i);
		if (s->getID() == id)
		{
			return s;
		}
	}


	log.error(string("Could not find State ID:") + to_string(id) + string(" in currentMap stateList. This should never happen."));
	//then it should look through every map mapStateList, since state ID is guaranteed to be unique.

	//MapState s = new MapState(id,"????");
	//stateList.add(s);


	return nullptr;
}

ArrayList<string>* Map::getListOfRandomPointsOfInterestTYPEIDs()
{ //=========================================================================================================================

	ArrayList<string>* areaTYPEIDList = new ArrayList<string>();


	//areas
	//   java::util::Iterator<Area*> aEnum = currentState->areaByNameHashtable.elements();
	//   while (aEnum->hasMoreElements())
	//   {
	//      Area* a = aEnum->nextElement();

	ArrayList<Area*> *areas = currentState->areaByNameHashtable.getAllValues();
	for (int i = 0; i<areas->size(); i++)
	{
		Area* a = areas->get(i);


		if (a->randomPointOfInterestOrExit())
		{
			areaTYPEIDList->add(a->getTYPEIDString());
		}
	}


	//warpareas
	for (int i = 0; i < warpAreaList.size(); i++)
	{
		Area* a = warpAreaList.get(i);
		if (a->randomPointOfInterestOrExit())
		{
			areaTYPEIDList->add(a->getTYPEIDString());
		}
	}


	//doors
	for (int i = 0; i < doorList.size(); i++)
	{
		Door* d = doorList.get(i);
		if (d->randomPointOfInterestOrExit())
		{
			areaTYPEIDList->add(d->getTYPEIDString()); //"DOOR."+d.getTYPEIDString());
		}
	}


	return areaTYPEIDList;
}

void Map::fadeIn()
{ //=========================================================================================================================
	if (alpha < 1.0f)
	{
		alpha += 0.002f * getEngine()->engineTicksPassed();
	}
	if (alpha > 1.0f)
	{
		alpha = 1.0f;
	}
}

void Map::fadeOut()
{ //=========================================================================================================================
	if (alpha > 0.0f)
	{
		alpha -= 0.003f * getEngine()->engineTicksPassed();
	}
	if (alpha < 0.0f)
	{
		alpha = 0.0f;
	}
}

void Map::loadMapState(MapState* s)
{ //===============================================================================================
	currentState = s;
}

void Map::update()
{ //=========================================================================================================================

	
	long long currentTime = System::currentHighResTimer();


	//this should always be true now that we are loading the mapData from the server.
	//the mapData contains the full data for the actual map Events so they are ready at load.

	//area, entity, door events, however, are simply held as eventID in those objects and they will load themselves after map is running.
	if (eventsAllLoadedFromServer == false)
	{
		long long startTime = lastLoadEventRequestTime;
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
		if (ticksPassed > 200)
		{
			lastLoadEventRequestTime = currentTime;
			//load all events

			bool eventsAllLoadedThisTime = false;

			if (mapEventIDList.size() > 0)
			{
				eventsAllLoadedThisTime = true;
				for (int i = 0; i < mapEventIDList.size(); i++)
				{
					int eventID = mapEventIDList.get(i);
					Event* event = getEventManager()->getEventByIDCreateIfNotExist(eventID);
					event->map = this;
					if (event->getInitialized_S() == false)
					{
						eventsAllLoadedThisTime = false;
					}
				}
			}

			if (eventsAllLoadedThisTime == true)
			{
				eventsAllLoadedFromServer = true;
			}
		}

		if (eventsAllLoadedFromServer == false)
		{
			return;
		}
	}


	//run load event to determine which map state to load.
	//DONE: need to choose a MapState here.
	//this is decided by the DEFAULT map Event, which should be loaded and run exactly once before the map loads.
	//so we need to go through currentMap's event list, find event type -1, and run that- before the map actually starts running. how to do that?
	//m.currentState = m.stateList.get(0);


	if (currentState == nullptr)
	{

		long long startTime = lastLoadEventRequestTime;
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
		if (ticksPassed > 200)
		{
			lastLoadEventRequestTime = currentTime;
			for (int i = 0; i < mapEventIDList.size(); i++)
			{
				Event* event = getEventManager()->getEventByIDCreateIfNotExist(mapEventIDList.get(i));
				event->map = this;
				if (event->type() == EventData::TYPE_MAP_RUN_ONCE_BEFORE_LOAD)
				{
					getEventManager()->addToEventQueueIfNotThere(event);
				}
			}
		}
		return;
	}


	fadeIn();


	if (utilityLayersLoaded == false)
	{
		utilityLayersLoaded = true;
		loadUtilityLayers();
	}


	if (startedMissingLightPNGThreads == false)
	{
		startedMissingLightPNGThreads = true;
		startThreadsForMissingLightPNGs();
	}
	else
	{
		if (allLightsLoadedAsTextures == false)
		{
			allLightsLoadedAsTextures = loadLightTexturesFromCachePNGs();
		}
	}


	if (sortedLightsLayers.isEmpty())
	{
		sortLightLayers();
	}


	//load map entities into entitymanager
	if (addedEntitiesAndCharactersFromCurrentStateToActiveEntityList == false)
	{
		addEntitiesAndCharactersFromCurrentStateToActiveEntityList();
		addedEntitiesAndCharactersFromCurrentStateToActiveEntityList = true;
	}


	//don't hammer eventList
	long long startTime = lastLoadEventRequestTime;
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	if (ticksPassed > 200)
	{
		lastLoadEventRequestTime = currentTime;
		//run all events, **this will also run post-load events for this map, which stop executing after one loop.
		for (int i = 0; i < mapEventIDList.size(); i++)
		{
			Event* event = getEventManager()->getEventByIDCreateIfNotExist(mapEventIDList.get(i));
			event->map = this;
			if (event->type() != EventData::TYPE_MAP_DONT_RUN_UNTIL_CALLED && event->type() != EventData::TYPE_MAP_RUN_ONCE_BEFORE_LOAD)
			{
				getEventManager()->addToEventQueueIfNotThere(event);
			}
		}
	}


	updateEntities();
	updateDoors();

	updateAreas();
	updateWarpAreas();

	//run();

	updateLights();

	zOrderEntities();


	if (startedMissingChunkPNGThreads == false)
	{
		startedMissingChunkPNGThreads = true;
		startThreadsForMissingChunkPNGs();
	}
	else
	{
		if (allChunkPNGsLoadedAsTextures == false || MapManager::loadTexturesOnDemand == true)
		{
			allChunkPNGsLoadedAsTextures = loadChunkTexturesFromCachePNGs();
		}
	}


	//else
	/*
	if(miniMapGenerated==false)
	{
	   miniMapGenerated=true;
	            
	   drawMiniMapIntoFBO();
	            
	}
	else
	*/

	if (MapManager::loadTexturesOnDemand == true && startedMissingChunkPNGThreads == true)
	{
		if (MapManager::generateHQ2XChunks == true)
		{
			if (startedMissingHQ2XChunkPNGThreads == false)
			{
				startedMissingHQ2XChunkPNGThreads = true;
				startThreadsForMissingHQ2XChunkPNGs();
			}
		}
	}


	if (allChunkPNGsLoadedAsTextures == true)
	{
		if (MapManager::generateHQ2XChunks == true)
		{
			//check here to see if we already loaded all hq2x textures while loading regular textures, no need to start threads if we have.
			//i don't really have to do this, but why start a thread pool if we don't have to?
			if (allHQ2XChunkPNGsLoadedAsTextures == false)
			{
				bool tempAllHQ2XChunkPNGsLoaded = true;

				for (int chunkY = 0; chunkY < chunksHeight; chunkY++)
				{
					for (int chunkX = 0; chunkX < chunksWidth; chunkX++)
					{
						for (int chunkLayer = 0; chunkLayer < 2; chunkLayer++)
						{
							int chunkIndex = (chunksWidth * chunksHeight * chunkLayer) + ((chunkY * chunksWidth) + chunkX);

							if (usingHQ2XTexture[chunkIndex] == false)
							{
								tempAllHQ2XChunkPNGsLoaded = false;
							}
						}
					}
				}
				if (tempAllHQ2XChunkPNGsLoaded == true)
				{
					allHQ2XChunkPNGsLoadedAsTextures = true;
				}
			}


			//if we still havent loaded them all, they must not exist.
			//start the threads to create them and load them as the threads finish
			if (allHQ2XChunkPNGsLoadedAsTextures == false)
			{
				if (startedMissingHQ2XChunkPNGThreads == false)
				{
					//TODO: manage cpu usage of threads, make sure they don't lower the framerate, even on slow computers.

					startedMissingHQ2XChunkPNGThreads = true;
					startThreadsForMissingHQ2XChunkPNGs();
				}
				else
				{
					allHQ2XChunkPNGsLoadedAsTextures = loadHQ2XTexturesFromCachePNGs();
				}
			}
		}
	}

	//nice percentage progress of chunk/light/hq2x PNG generation and chunk texture loading
	updateLoadingStatus();


	/*if(
	      MapManager.useThreads==true&&
	      generatePNGExecutorService!=null&&
	      startedMissingLightPNGThreads==true&&
	      startedMissingChunkPNGThreads==true&&
	      startedMissingHQ2XChunkPNGThreads==true
	)
	{
	   if(generatePNGExecutorService.isShutdown()==false)
	   {
	      generatePNGExecutorService.shutdown();
	      log.debug("generatePNGExecutorService Shut Down");
	   }
	}*/
}

void Map::updateLoadingStatus()
{ //=========================================================================================================================
	if (maxHq2xChunkPNGThreadsCreated > 0)
	{
		if (hq2xChunkPNGThreadsDebugText == nullptr)
		{
			hq2xChunkPNGThreadsDebugText = Console::debug("hq2xChunkPNGThreadsDebugText");
		}


		{
			float percent = ((float)(maxHq2xChunkPNGThreadsCreated - hq2xChunkPNGThreadsCreated) / (float)(maxHq2xChunkPNGThreadsCreated)) * 100.0f;
			hq2xChunkPNGThreadsDebugText->text = string("HQ2X Chunk PNG Threads: ") + to_string(maxHq2xChunkPNGThreadsCreated - hq2xChunkPNGThreadsCreated) + string(" / ") + to_string(maxHq2xChunkPNGThreadsCreated) + string(" ( ") + to_string(percent) + string(" % )");
		}

		if (hq2xChunkPNGThreadsCreated == 0)
		{
			maxHq2xChunkPNGThreadsCreated = 0;
			hq2xChunkPNGThreadsDebugText->ticks = 1000;
			hq2xChunkPNGThreadsDebugText = nullptr;
		}
	}


	if (maxChunkPNGThreadsCreated > 0)
	{
		if (chunkPNGThreadsDebugText == nullptr)
		{
			chunkPNGThreadsDebugText = Console::debug("chunkPNGThreadsDebugText");
		}


		{
			float percent = ((float)(maxChunkPNGThreadsCreated - chunkPNGThreadsCreated) / (float)(maxChunkPNGThreadsCreated)) * 100.0f;
			chunkPNGThreadsDebugText->text = string("1X Chunk PNG Threads: ") + to_string(maxChunkPNGThreadsCreated - chunkPNGThreadsCreated) + string(" / ") + to_string(maxChunkPNGThreadsCreated) + string(" ( ") + to_string(percent) + string(" % )");
		}

		if (chunkPNGThreadsCreated == 0)
		{
			maxChunkPNGThreadsCreated = 0;
			chunkPNGThreadsDebugText->ticks = 1000;
			chunkPNGThreadsDebugText = nullptr;
		}
	}


	if (maxLightPNGThreadsCreated > 0)
	{
		if (lightPNGThreadsDebugText == nullptr)
		{
			lightPNGThreadsDebugText = Console::debug("lightPNGThreadsDebugText");
		}


		{
			float percent = ((float)(maxLightPNGThreadsCreated - lightPNGThreadsCreated) / (float)(maxLightPNGThreadsCreated)) * 100.0f;
			lightPNGThreadsDebugText->text = string("Light PNG Threads: ") + to_string(maxLightPNGThreadsCreated - lightPNGThreadsCreated) + string(" / ") + to_string(maxLightPNGThreadsCreated) + string(" ( ") + to_string(percent) + string(" % )");
		}

		if (lightPNGThreadsCreated == 0)
		{
			maxLightPNGThreadsCreated = 0;
			lightPNGThreadsDebugText->ticks = 1000;
			lightPNGThreadsDebugText = nullptr;
		}
	}


	if (chunkTexturesLoaded > 0 && MapManager::loadTexturesOnDemand == false)
	{
		int totalChunkTextures = (chunksWidth * chunksHeight * 2);

		if (texturesLoadedDebugText == nullptr)
		{
			texturesLoadedDebugText = Console::debug("texturesLoadedDebugText");
		}

		if (generatingAreaNotification == nullptr)
		{
			generatingAreaNotification = new Notification((static_cast<BGClientEngine*>(getEngine())), "Loading Area...");
		}


		{
			float percent = ((float)(chunkTexturesLoaded) / (float)(totalChunkTextures)) * 100.0f;
			texturesLoadedDebugText->text = string("Textures Loaded: ") + to_string(chunkTexturesLoaded) + string(" / ") + to_string(totalChunkTextures) + string(" ( ") + to_string(percent) + string(" % )");
			generatingAreaNotification->progress = percent / 100.0f;
		}

		if (chunkTexturesLoaded == totalChunkTextures)
		{
			chunkTexturesLoaded = 0;
			texturesLoadedDebugText->ticks = 1000;
			texturesLoadedDebugText = nullptr;

			if (generatingAreaNotification != nullptr)
			{
				generatingAreaNotification = generatingAreaNotification->fadeOutAndDelete();
			}
		}
	}

	if (MapManager::loadTexturesOnDemand == true)
	{
		if (generatingAreaNotification != nullptr)
		{
			generatingAreaNotification = generatingAreaNotification->fadeOutAndDelete();
		}
	}
}

void Map::updateEntities()
{ //=========================================================================================================================

	//for all entities update
	for (int n = 0; n < activeEntityList.size(); n++)
	{
		Entity* e = activeEntityList.get(n);

		e->update();
	}
}

void Map::updateDoors()
{ //=========================================================================================================================

	for (int n = 0; n < doorList.size(); n++)
	{
		Door* e = doorList.get(n);

		e->update();
	}
}

void Map::updateAreas()
{ //=========================================================================================================================

	if (currentState == nullptr)
	{
		return;
	}

	//		Enumeration<Area> aEnum = currentState.areaHashtable.elements();
	//		while(aEnum.hasMoreElements())
	//		{
	//			Area a = aEnum.nextElement();
	//			a.update();
	//		}

	for (int i = 0; i < (int)currentState->areaList.size(); i++)
	{
		Area* a = currentState->areaList.get(i);
		a->update();
	}
}

void Map::updateWarpAreas()
{ //=========================================================================================================================
	for (int i = 0; i < warpAreaList.size(); i++)
	{
		{
			//if(warpAreaList.get(i).mapAsset==currentMap)
			warpAreaList.get(i)->update();
		}
	}
}

void Map::updateLights()
{ //=========================================================================================================================

	for (int i = 0; i < (int)currentState->lightList.size(); i++)
	{
		currentState->lightList.get(i)->update();
	}
}

void Map::zOrderEntities()
{ //=========================================================================================================================


	drawList.clear();


	for (int i = 0; i < activeEntityList.size(); i++)
	{
		Entity* e = activeEntityList.get(i);

		//decide which ones need rendering
		//add to new linked list of on-screen entities to z-order
		if (e->shouldDraw())
		{
			if (drawList.contains(e) == false)
			{
				drawList.add(e);
			}
		}
	}

	for (int i = 0; i < doorList.size(); i++)
	{
		Door* e = doorList.get(i);

		//decide which ones need rendering
		//add to new linked list of on-screen entities to z-order
		if (e->shouldDraw())
		{
			if (drawList.contains(e) == false)
			{
				drawList.add(e);
			}
		}
	}

	if (getCurrentMap() != nullptr && getCurrentMap() == this)
	{
		if (getClientGameEngine() != nullptr && getClientGameEngine()->playerExistsInMap == false)
		{
			if (getPlayer() != nullptr && getPlayer()->shouldDraw())
			{
				if ((drawList.contains(getPlayer())) == false)
				{
					drawList.add(getPlayer());
				}
			}
		}
	}


	if (dynamic_cast<BGClientEngine*>(getEngine()) != nullptr)
	{
		//add friends, they are not added to any entityList
		for (int i = 0; i < (int)getClientGameEngine()->friendManager->friendCharacters->size(); i++)
		{
			FriendCharacter* f = getFriendManager()->friendCharacters->get(i);

			if (f->mapName == getName())
			{
				if (f->shouldDraw())
				{
					if (drawList.contains(f) == false)
					{
						drawList.add(f);
					}
				}
			}
		}
	}


	//z-order all entities

	//now we want to make a new list of all the on-screen entities, z-ordered starting at the top of the screen and working to the bottom
	//for each entity in the drawList, find the topmost one and add it to the new list, then remove it from the drawList


	zList.clear();

	while (drawList.size() != 0)
	{
		Entity* highestOnScreenEntity = nullptr;

		for (int n = 0; n < drawList.size(); n++)
		{
			Entity* e = drawList.get(n);

			//store topmost entity on screen
			//check for non-zordering entities, entities always on top, entities always on bottom here.


			if (e->getAlwaysOnBottom())
			{
				highestOnScreenEntity = e;
				break;
			}

			if (highestOnScreenEntity == nullptr || (e->getAlwaysOnTop() == false && (e->getMiddleY() < highestOnScreenEntity->getMiddleY() || (highestOnScreenEntity->getAboveWhenEqual() && (int)(floor(highestOnScreenEntity->getBottom())) == (int)(floor(e->getBottom()))))))
			{
				highestOnScreenEntity = e;
			}
		}

		drawList.remove(highestOnScreenEntity);
		zList.add(highestOnScreenEntity);
	}


	//		log.debug("---------------------");
	//
	//		for(int i=0;i<zList.size();i++)
	//		{
	//			Entity e = zList.get(i);
	//			log.debug(e.getSpriteName());
	//		}


	//TODO: if any part of the feet are under a tile on the above layer, dont draw the shadow
}

void Map::sortLightLayers()
{ //=========================================================================================================================


	//TODO: redo this algorithm so splarka doesn't get pissy
	//even though it was sent without a license written in javascript and i ported, rewrote, and optimised it :P


	//for all lights
	//if light is not drawn

	for (int i = 0; i < (int)currentState->lightList.size(); i++)
	{
		Light* l = currentState->lightList.get(i);
		//if light is not drawn
		if (l->sortingState != Light::DRAWN)
		{
			ArrayList<Light*>* thisLayerList = new ArrayList<Light*>();

			//light is drawing
			l->sortingState = Light::DRAWING;

			//for all lights from this light to the end
			for (int a = i + 1; a < (int)currentState->lightList.size(); a++)
			{
				Light* compareLight = currentState->lightList.get(a);

				//if that light isn't already drawn
				if (compareLight->sortingState != Light::DRAWN)
				{
					//for all lights
					for (int b = 0; b < (int)currentState->lightList.size(); b++)
					{
						Light* overlapLight = currentState->lightList.get(b);

						//if this light isn't
						if (a != b && overlapLight->sortingState == Light::DRAWING)
						{
							float left1 = compareLight->getLeft();
							float right1 = compareLight->getRight();
							float top1 = compareLight->getTop();
							float bottom1 = compareLight->getBottom();

							float left2 = overlapLight->getLeft();
							float right2 = overlapLight->getRight();
							float top2 = overlapLight->getTop();
							float bottom2 = overlapLight->getBottom();

							if ((left1 < right2) && (right1 > left2) && (top1 < bottom2) && (bottom1 > top2))
							{
								compareLight->sortingState = Light::OVERLAPS_SOMETHING;
							}
						}
					}
					if (compareLight->sortingState != Light::OVERLAPS_SOMETHING)
					{
						compareLight->sortingState = Light::DRAWING;
					}
					else
					{
						compareLight->sortingState = Light::NOT_DRAWN;
					}
				}
			}


			for (int d = 0; d < (int)currentState->lightList.size(); d++)
			{
				Light* drawLight = currentState->lightList.get(d);
				if (drawLight->sortingState == Light::DRAWING)
				{
					thisLayerList->add(drawLight);

					//draw light
					drawLight->sortingState = Light::DRAWN;
				}
			}

			//log.debug("Light layer "+layer);
			//layer++;
			sortedLightsLayers.add(thisLayerList);
		}
	}
}

void Map::render(RenderOrder renderOrder)
{ //=========================================================================================================================
	render(renderOrder, defaultDisableClip, defaultDisableFloorOffset);
}

void Map::render(RenderOrder renderOrder, bool disableClip)
{ //=========================================================================================================================
	render(renderOrder, disableClip, defaultDisableFloorOffset);
}

void Map::render(RenderOrder renderOrder, bool disableClip, bool disableFloorOffset)
{ //=========================================================================================================================

	if (renderOrder == RenderOrder::GROUND && getEngine()->underLayerEnabled == false)
	{
		return;
	}
	if (renderOrder == RenderOrder::ABOVE && getEngine()->overLayerEnabled == false)
	{
		return;
	}

	//only allow above or ground
	if (renderOrder != RenderOrder::GROUND && renderOrder != RenderOrder::ABOVE)
	{
		return;
	}


	int layerIndex = 0;
	if (renderOrder == RenderOrder::GROUND)
	{
		layerIndex = 0;
	}
	if (renderOrder == RenderOrder::ABOVE)
	{
		layerIndex = 1;
	}


	BobTexture* texture = nullptr;

	float sw = (float)getEngine()->getWidth();
	float sh = (float)getEngine()->getHeight();

	float zoom = getCameraman()->getZoom();

	int filter = GLUtils::FILTER_LINEAR;
	if (zoom == 1.0f || zoom >= 1.5f || zoom == 0.5f)
	{
		filter = GLUtils::FILTER_NEAREST;
	}


	float tx0 = 0.0f;
	float tx1 = 1.0f;
	float ty0 = 0.0f;
	float ty1 = 1.0f;


	float x0 = 0;
	float x1 = 0;
	float y0 = 0;
	float y1 = 0;


	//for each texture chunk starting at screen-chunksize*zoom
	//if texture isn't null, draw it at the correct place.


	//start at screen - chunksize

	int startChunkX = ((int)(floor(((mapCamX()) / (chunkSizePixelsHQ2X)))));
	int startChunkY = ((int)(floor(((mapCamY()) / (chunkSizePixelsHQ2X)))));

	if (startChunkX < 0)
	{
		startChunkX = 0;
	}
	if (startChunkY < 0)
	{
		startChunkY = 0;
	}

	int screenChunkWidth = ((int)(floor(sw / (chunkSizePixelsHQ2X * zoom)))) + 1;
	int screenChunkHeight = ((int)(floor(sh / (chunkSizePixelsHQ2X * zoom)))) + 1;


	//for drawing the lastMap, we can't clip based on the camera so we have to draw the whole thing.
	if (disableClip == true)
	{
		startChunkX = 0;
		startChunkY = 0;
		screenChunkWidth = chunksWidth;
		screenChunkHeight = chunksHeight;
	}

	for (int chunkY = startChunkY; chunkY <= startChunkY + screenChunkHeight && chunkY < chunksHeight; chunkY++)
	{
		for (int chunkX = startChunkX; chunkX <= startChunkX + screenChunkWidth && chunkX < chunksWidth; chunkX++)
		{
			//old way, floor and ceil was good but had small line artifacts when zooming
			//if i make them all floor, the line artifacts are worse, same if i make ceil round
			//if i remove the floor and ceil, the grass is "shimmery" and vertical lines are clippy

			//float chunkMapScreenX = (float) Math.floor(map_screen_x*drawScale+(chunkX * chunkSizePixelsHQ2X*drawScale));
			//float chunkMapScreenY = (float) Math.floor(map_screen_y*drawScale+(chunkY * chunkSizePixelsHQ2X*drawScale));
			//float chunkMapScreenX2 = (float) Math.ceil(chunkMapScreenX+chunkSizePixelsHQ2X*drawScale);
			//float chunkMapScreenY2 = (float) Math.ceil(chunkMapScreenY+chunkSizePixelsHQ2X*drawScale);

			//this seems to work the best:
			//i am only flooring the map screen coords, then using that as an offset for all the other values.
			//this has no lines in between zoom levels
			float chunkMapScreenX = (float)(floor(screenX() * zoom)) + (chunkX * chunkSizePixelsHQ2X * zoom);
			float chunkMapScreenY = (float)(floor(screenY() * zoom)) + (chunkY * chunkSizePixelsHQ2X * zoom);

			if (disableFloorOffset)
			{
				chunkMapScreenX = (float)(screenX() * zoom) + (chunkX * chunkSizePixelsHQ2X * zoom);
				chunkMapScreenY = (float)(screenY() * zoom) + (chunkY * chunkSizePixelsHQ2X * zoom);
			}

			float chunkMapScreenX2 = (float)(chunkMapScreenX + chunkSizePixelsHQ2X * zoom);
			float chunkMapScreenY2 = (float)(chunkMapScreenY + chunkSizePixelsHQ2X * zoom);


			if (chunkMapScreenX >= sw || chunkMapScreenX2 < 0 || chunkMapScreenY >= sh || chunkMapScreenY2 < 0) //off the top - off the bottom
			{
				continue;
			}

			x0 = (chunkMapScreenX);
			y0 = (chunkMapScreenY);

			x1 = (chunkMapScreenX2);
			y1 = (chunkMapScreenY2);


			int chunkIndex = (chunksWidth * chunksHeight * layerIndex) + ((chunksWidth * chunkY) + chunkX);

			texture = getChunkTexture(chunkIndex);

			if (texture != nullptr && texture != GLUtils::blankTexture)
			{
				GLUtils::drawTexture(texture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, alpha, filter);
			}
		}
	}


	//OLD WAY, SINGLE ROOM GRAPHICS

	//this only renders the clip that needs it


	/*
	      //if the map is offscreen, don't draw anything
	
	      if((map_screen_x*G.zoom)+(tw*G.zoom)<0)return;
	      if((map_screen_y*G.zoom)+(th*G.zoom)<0)return;
	
	      if((map_screen_x*G.zoom)>=sw)return;//this could still be on the screen :\
	      if((map_screen_y*G.zoom)>=sh)return;
	
	
	      if((map_screen_x*G.zoom)<0)
	      {
	         //tx0 is greater than 0
	         tx0 = (float)(0-(map_screen_x*G.zoom))/(float)(tw*G.zoom);
	         //x0 is 0
	         x0=0;
	      }
	
	      if(map_screen_x*G.zoom>=0)
	      {
	         //tx0 is 0
	         tx0=0.0f;
	         //x0 is map_cam_x/sw
	         x0=(int)(map_screen_x*G.zoom);
	      }
	
	      //if map extends off screen to the right
	      if((map_screen_x*G.zoom)+(tw*G.zoom)>=sw)
	      {
	         tx1=(float)(sw-(map_screen_x*G.zoom))/(float)(tw*G.zoom);
	
	         x1=sw;
	      }
	      else
	      {
	         tx1 = 1.0f;
	         x1 = (int)(map_screen_x*G.zoom)+(int)(tw*G.zoom);
	      }
	
	
	
	
	      if((map_screen_y*G.zoom)<0)
	      {
	         //ty0 is greater than 0
	         ty0 = (float)(0-(map_screen_y*G.zoom))/(float)(th*G.zoom);
	         //y0 is 0
	         y0=0;
	      }
	
	      if((map_screen_y*G.zoom)>=0)
	      {
	         //ty0 is 0
	         ty0=0.0f;
	         //y0 is map_cam_y
	         y0=(int)(map_screen_y*G.zoom);
	      }
	
	      //if map extends off screen to the bottom
	      if((map_screen_y*G.zoom)+(th*G.zoom)>=sh)
	      {
	         ty1=(float)(sh-(map_screen_y*G.zoom))/(float)(th*G.zoom);
	         y1=sh;
	      }
	      else
	      {
	         ty1 = 1.0f;
	         y1 = (int)(map_screen_y*G.zoom)+(int)(th*G.zoom);
	      }
	
	
	      */


	//this renders the whole thing and lets the card clip it
	/*
	float tx0 = 0.0f;// = (float)cam_x/(float)tw;
	float tx1 = 1.0f;//(float)(cam_x+ssx)/(float)tw;
	            
	float ty0 = 0.0f;
	float ty1 = 1.0f;
	            
	            
	int x0 = (int)(map_screen_x*G.zoom);
	int x1 = (int)((map_screen_x*G.zoom)+(tw*G.zoom));
	int y0 = (int)(map_screen_y*G.zoom);
	int y1 = (int)((map_screen_y*G.zoom)+(th*G.zoom));
	            
	            
	            
	            
	GL.drawTexture(texture,tx0,tx1,ty0,ty1,x0,x1,y0,y1,1.0f,0);
	            
	*/

	/*
	texture.bind();
	            
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	            
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	            
	            
	glBegin(GL_QUADS);
	            
	   //TL (0,0)
	   glTexCoord2f(tx0,ty0);
	   glVertex2i(x0,y0);
	            
	   //TR (1,0)
	   glTexCoord2f(tx1,ty0);
	   glVertex2i(x1,y0);
	            
	   //BR (1,1)
	   glTexCoord2f(tx1,ty1);
	   glVertex2i(x1,y1);
	            
	   //BL (0,1)
	   glTexCoord2f(tx0,ty1);
	   glVertex2i(x0,y1);
	            
	glEnd();
	*/
}

void Map::renderEntities(RenderOrder layer)
{ //=========================================================================================================================

	if (layer == RenderOrder::GROUND)
	{
		renderAreaActionIcons();
	}

	if (getEngine()->entityLayerEnabled)
	{
		//for all entities, render as needed, in proper order

		for (int n = 0; n < zList.size(); n++)
		{
			Entity* e = zList.get(n);


			if (layer == RenderOrder::SPRITE_DEBUG_OUTLINES)
			{
				e->renderDebugBoxes();
			}
			else if (layer == RenderOrder::SPRITE_DEBUG_INFO)
			{
				e->renderDebugInfo();
			}
			else if (e->getRenderOrder() == layer)
			{
				e->render(alpha);
			}
		}
	}
}

void Map::renderAllLightsUnsorted()
{ //=========================================================================================================================

	if (getEngine()->lightsLayerEnabled == false)
	{
		return;
	}

	if (currentState != nullptr)
	{
		for (int i = 0; i < (int)currentState->lightList.size(); i++)
		{
			Light* l = currentState->lightList.get(i);
			l->renderLight();
		}
	}
}

void Map::renderAreaActionIcons()
{ //=========================================================================================================================


	//TODO: go through all events currently running. each event will know whether it needs an action icon or not.

	if (currentState == nullptr)
	{
		return;
	}

	//areas
	//   java::util::Iterator<Area*> aEnum = currentState->areaByNameHashtable.elements();
	//   while (aEnum->hasMoreElements())
	//   {
	//      Area* a = aEnum->nextElement();

	ArrayList<Area*> *areas = currentState->areaByNameHashtable.getAllValues();
	for (int i = 0; i<areas->size(); i++)
	{
		Area* a = areas->get(i);

		//if(a.isAnAction)
		a->renderActionIcon();
	}


	//warpareas
	for (int i = 0; i < warpAreaList.size(); i++)
	{
		Area* a = warpAreaList.get(i);
		//if(a.isAnAction)
		a->renderActionIcon();
	}
}

void Map::renderChunkBoxes()
{ //=========================================================================================================================


	//for each tile on screen
	//go through getHit detection


	//glcolor
	//glbegin

	//gl add quads

	//gl end
	glColor4f(1.0f, 0.5f, 0.0f, 0.4f);
	glBegin(GL_LINES);

	float sw = (float)getEngine()->getWidth();
	float sh = (float)getEngine()->getHeight();

	float zoom = getCameraman()->getZoom();

	int startChunkX = ((int)(floor(((mapCamX()) / (chunkSizePixelsHQ2X)))));
	int startChunkY = ((int)(floor(((mapCamY()) / (chunkSizePixelsHQ2X)))));

	if (startChunkX < 0)
	{
		startChunkX = 0;
	}
	if (startChunkY < 0)
	{
		startChunkY = 0;
	}

	int screenChunkWidth = ((int)(floor(sw / (chunkSizePixelsHQ2X * zoom)))) + 1;
	int screenChunkHeight = ((int)(floor(sh / (chunkSizePixelsHQ2X * zoom)))) + 1;


	for (int chunkY = startChunkY; chunkY <= startChunkY + screenChunkHeight && chunkY < chunksHeight; chunkY++)
	{
		for (int chunkX = startChunkX; chunkX <= startChunkX + screenChunkWidth && chunkX < chunksWidth; chunkX++)
		{
			float chunkMapScreenX = (float)(floor(screenX() * zoom + (chunkX * chunkSizePixelsHQ2X * zoom)));
			float chunkMapScreenY = (float)(floor(screenY() * zoom + (chunkY * chunkSizePixelsHQ2X * zoom)));
			float chunkMapScreenX2 = (float)(ceil(chunkMapScreenX + chunkSizePixelsHQ2X * zoom));
			float chunkMapScreenY2 = (float)(ceil(chunkMapScreenY + chunkSizePixelsHQ2X * zoom));


			//left
			glVertex2f(chunkMapScreenX, chunkMapScreenY);
			glVertex2f(chunkMapScreenX, chunkMapScreenY2);

			//right
			glVertex2f(chunkMapScreenX2, chunkMapScreenY);
			glVertex2f(chunkMapScreenX2, chunkMapScreenY2);

			//top
			glVertex2f(chunkMapScreenX, chunkMapScreenY);
			glVertex2f(chunkMapScreenX2, chunkMapScreenY);

			//bottom
			glVertex2f(chunkMapScreenX, chunkMapScreenY2);
			glVertex2f(chunkMapScreenX2, chunkMapScreenY2);
		}
	}


	glEnd();
}

void Map::renderHitLayer()
{ //=========================================================================================================================
	glColor4f(1.0f, 0.0f, 0.0f, 0.4f);
	glBegin(GL_QUADS);

	float sw = (float)getEngine()->getWidth();
	float sh = (float)getEngine()->getHeight();

	float zoom = getCameraman()->getZoom();

	int startTileX = ((int)(floor(((mapCamX()) / (16)))));
	int startTileY = ((int)(floor(((mapCamY()) / (16)))));

	if (startTileX < 0)
	{
		startTileX = 0;
	}
	if (startTileY < 0)
	{
		startTileY = 0;
	}

	int screenTileWidth = ((int)(floor(sw / (16 * zoom)))) + 1;
	int screenTileHeight = ((int)(floor(sh / (16 * zoom)))) + 1;


	for (int tileY = startTileY; tileY <= startTileY + screenTileHeight && tileY < getHeightTiles1X(); tileY++)
	{
		for (int tileX = startTileX; tileX <= startTileX + screenTileWidth && tileX < getWidthTiles1X(); tileX++)
		{
			if (getHitLayerValueAtXYPixels((float)(tileX) * 16, (float)(tileY) * 16) == false)
			{
				continue;
			}

			float tileMapScreenX = (float)(floor(screenX() * zoom + (tileX * 16 * zoom)));
			float tileMapScreenY = (float)(floor(screenY() * zoom + (tileY * 16 * zoom)));
			float tileMapScreenX2 = (float)(ceil(tileMapScreenX + 16 * zoom));
			float tileMapScreenY2 = (float)(ceil(tileMapScreenY + 16 * zoom));


			glVertex2f(tileMapScreenX, tileMapScreenY);
			glVertex2f(tileMapScreenX, tileMapScreenY2);
			glVertex2f(tileMapScreenX2, tileMapScreenY2);
			glVertex2f(tileMapScreenX2, tileMapScreenY);
		}
	}


	glEnd();
}

void Map::renderLightBoxes()
{ //===============================================================================================
	//light boxes
	for (int i = 0; i < sortedLightsLayers.size(); i++)
	{
		ArrayList<Light*>* thisLayer = sortedLightsLayers.get(i);
		for (int n = 0; n < thisLayer->size(); n++)
		{
			thisLayer->get(n)->renderDebugBoxes();
		}
	}
}

void Map::renderAreaDebugBoxes()
{ //===============================================================================================

	if (currentState == nullptr)
	{
		return;
	}

	//   java::util::Iterator<Area*> aEnum = currentState->areaByNameHashtable.elements();
	//   //areas
	//   while (aEnum->hasMoreElements())
	//   {
	//      Area* a = aEnum->nextElement();

	ArrayList<Area*> *areas = currentState->areaByNameHashtable.getAllValues();
	for (int i = 0; i<areas->size(); i++)
	{
		Area* a = areas->get(i);



		a->renderDebugBoxes();
		//a.renderDebugInfo();
	}
}

void Map::renderAreaDebugInfo()
{ //===============================================================================================

	if (currentState == nullptr)
	{
		return;
	}

	//TODO: make these a manager in mapmanager
	//   java::util::Iterator<Area*> aEnum = currentState->areaByNameHashtable.elements();
	//   //areas
	//   while (aEnum->hasMoreElements())
	//   {
	//      Area* a = aEnum->nextElement();

	ArrayList<Area*> *areas = currentState->areaByNameHashtable.getAllValues();
	for (int i = 0; i<areas->size(); i++)
	{
		Area* a = areas->get(i);


		//a.renderDebugBoxes();
		a->renderDebugInfo();
	}
}

void Map::renderWarpAreaDebugBoxes()
{ //=========================================================================================================================

	for (int i = 0; i < warpAreaList.size(); i++)
	{
		{
			//if(warpAreaList.get(i).mapAsset==currentMap)
			warpAreaList.get(i)->renderDebugBoxes();
		}
	}
}

void Map::renderWarpAreaDebugInfo()
{ //=========================================================================================================================

	for (int i = 0; i < warpAreaList.size(); i++)
	{
		{
			//if(warpAreaList.get(i).mapAsset==currentMap)
			warpAreaList.get(i)->renderDebugInfo();
		}
	}
}

void Map::loadUtilityLayers()
{ //=========================================================================================================================


	/*public String getGroundShaderMD5 = null;
	public String getCameraBoundsMD5 = null;
	public String getHitBoundsMD5 = null;
	public String getLightMaskMD5 = null;*/

	//-----------------------------------
	//load hitlayer
	//-----------------------------------
	//hitLayer = BufferUtils.createIntBuffer((mapWidth/8) * (mapHeight/8));

	if (hitLayer == nullptr)
	{
		hitLayer = FileUtils::loadIntFileFromCacheOrDownloadIfNotExist(string("") + getHitBoundsMD5());
		/*hitLayer = new byte[getWidthTiles1X * getHeightTiles1X];
		         
		BufferedInputStream hitBin = new BufferedInputStream(FileUtils::getResourceAsStream(""+CacheManager.cacheDir+getHitBoundsMD5));
		         
		try
		{
		   hitBin.read(hitLayer);
		   hitBin.close();
		}
		catch (IOException e)
		{
		   e.printStackTrace();
		}*/
	}


	//-----------------------------------
	//load fx layer
	//-----------------------------------
	if (cameraLayer == nullptr)
	{
		cameraLayer = FileUtils::loadIntFileFromCacheOrDownloadIfNotExist(string("") + getCameraBoundsMD5());

		//			FileUtils.downloadSmallFileToCacheIfNotExist(""+getCameraBoundsMD5());
		//
		//
		//			cameraLayer = new byte[getWidthTiles1X() * getHeightTiles1X()];
		//			BufferedInputStream fxBin = new BufferedInputStream(FileUtils::getResourceAsStream(""+FileUtils.cacheDir+getCameraBoundsMD5()));
		//
		//			//TODO: in map editor, output this as byte array instead of int array, then i don't have to skip every other byte here
		//			try
		//			{
		//				int data=fxBin.read();
		//				int notdata=fxBin.read();
		//				int i=0;
		//
		//				while(data!=-1||notdata!=-1)
		//				{
		//					cameraLayer->get(i)=(byte)data;
		//					i++;
		//					data=fxBin.read();
		//					notdata=fxBin.read();
		//				}
		//
		//				fxBin.close();
		//			}
		//			catch (IOException e)
		//			{
		//				e.printStackTrace();
		//			}
	}


	//-----------------------------------
	//load ground shader layer
	//-----------------------------------

	if (groundShaderLayer == nullptr)
	{
		groundShaderLayer = FileUtils::loadIntFileFromCacheOrDownloadIfNotExist(string("") + getGroundShaderMD5());

		/*groundShaderLayer = new int[getWidthTiles1X * getHeightTiles1X];
		BufferedInputStream shaderBin = new BufferedInputStream(FileUtils::getResourceAsStream(""+CacheManager.cacheDir+getGroundShaderMD5));
		         
		try
		{
		   int sbyte1=shaderBin.read();
		   int sbyte2=shaderBin.read();
		   int i=0;
		         
		   while(sbyte1!=-1||sbyte2!=-1)
		   {
		         
		      int ubyte1 = sbyte1 & 0xFF;
		      int ubyte2 = sbyte2 & 0xFF;
		         
		      int result = (ubyte2<<8) + ubyte1;
		         
		      groundShaderLayer->get(i)=result;
		      i++;
		      sbyte1=shaderBin.read();
		      sbyte2=shaderBin.read();
		   }
		         
		   shaderBin.close();
		}
		catch (IOException e)
		{
		   e.printStackTrace();
		}*/
	}


	//-----------------------------------
	//load light mask layer
	//-----------------------------------
	if (groundShaderLayer == nullptr)
	{
		groundShaderLayer = FileUtils::loadIntFileFromCacheOrDownloadIfNotExist(string("") + getLightMaskMD5());

		/*lightMaskLayer = new int[getWidthTiles1X * getHeightTiles1X];
		BufferedInputStream lightMaskBin = new BufferedInputStream(FileUtils::getResourceAsStream(""+CacheManager.cacheDir+getLightMaskMD5));
		         
		try
		{
		   int sbyte1=lightMaskBin.read();
		   int sbyte2=lightMaskBin.read();
		   int i=0;
		         
		   while(sbyte1!=-1||sbyte2!=-1)
		   {
		         
		      int ubyte1 = sbyte1 & 0xFF;
		      int ubyte2 = sbyte2 & 0xFF;
		         
		      int result = (ubyte2<<8) + ubyte1;
		         
		      lightMaskLayer->get(i)=result;
		      i++;
		      sbyte1=lightMaskBin.read();
		      sbyte2=lightMaskBin.read();
		   }
		         
		   lightMaskBin.close();
		}
		catch (IOException e)
		{
		   e.printStackTrace();
		}*/
	}
}

void Map::saveDataToCache(int* intArrayAllLayers, int* tiles, u8* pal)
{ //=========================================================================================================================

	//I should just save each layer as the MD5 in the cache folder
	//then set the appropriate md5 name in data

	for (int l = 0; l < MapData::layers; l++)
	{
		if (MapData::isTileLayer(l))
		{
			int index = (getWidthTiles1X() * getHeightTiles1X() * l);
			int* layer = new int(getWidthTiles1X() * getHeightTiles1X());
			for (int i = 0; i < getWidthTiles1X() * getHeightTiles1X(); i++)
			{
				layer[i] = intArrayAllLayers[index + i];
			}

			//save to cache folder as md5 name
			u8* byteArray = FileUtils::getByteArrayFromIntArray(layer);
			string md5FileName = FileUtils::getByteArrayMD5Checksum(byteArray);
			FileUtils::saveByteArrayToCache(byteArray, md5FileName);

			//set layermd5 name to md5
			if (l == MapData::MAP_GROUND_LAYER)
			{
				setGroundLayerMD5(md5FileName);
			}
			if (l == MapData::MAP_GROUND_DETAIL_LAYER)
			{
				setGroundObjectsMD5(md5FileName);
			}
			if (l == MapData::MAP_GROUND_SHADOW_LAYER)
			{
				setGroundShadowMD5(md5FileName);
			}
			if (l == MapData::MAP_OBJECT_LAYER)
			{
				setObjectsMD5(md5FileName);
			}
			if (l == MapData::MAP_OBJECT_DETAIL_LAYER)
			{
				setObjects2MD5(md5FileName);
			}
			if (l == MapData::MAP_OBJECT_SHADOW_LAYER)
			{
				setObjectShadowMD5(md5FileName);
			}
			if (l == MapData::MAP_ABOVE_LAYER)
			{
				setAboveMD5(md5FileName);
			}
			if (l == MapData::MAP_ABOVE_DETAIL_LAYER)
			{
				setAbove2MD5(md5FileName);
			}
			if (l == MapData::MAP_SPRITE_SHADOW_LAYER)
			{
				setSpriteShadowMD5(md5FileName);
			}
			if (l == MapData::MAP_SHADER_LAYER)
			{
				setGroundShaderMD5(md5FileName);
			}
			if (l == MapData::MAP_LIGHT_MASK_LAYER)
			{
				setLightMaskMD5(md5FileName);
			}
			if (l == MapData::MAP_CAMERA_BOUNDS_LAYER)
			{
				setCameraBoundsMD5(md5FileName);
			}
			if (l == MapData::MAP_HIT_LAYER)
			{
				setHitBoundsMD5(md5FileName);
			}
		}
	}
	//save tiles
	u8* byteArray = FileUtils::getByteArrayFromIntArray(tiles);
	string md5FileName = FileUtils::getByteArrayMD5Checksum(byteArray);
	FileUtils::saveByteArrayToCache(byteArray, md5FileName);
	setTilesMD5(md5FileName);

	//save pal
	byteArray = pal;
	md5FileName = FileUtils::getByteArrayMD5Checksum(byteArray);
	FileUtils::saveByteArrayToCache(byteArray, md5FileName);
	setPaletteMD5(md5FileName);
}

void Map::unloadArea(const string& s)
{ //=========================================================================================================================

	//public Hashtable<String, Area> areaHashtable = new Hashtable<String, Area>();

	Area* a = currentState->areaByNameHashtable.get(s);
	currentState->areaByNameHashtable.removeAt(s);
	currentState->areaByTYPEIDHashtable.removeAt(a->getTYPEIDString());
	currentState->areaList.remove(a);
}

void Map::unloadLight(const string& s)
{ //=========================================================================================================================
	//public ArrayList<Light> lightList = new ArrayList<Light>();
	//public Hashtable<String,Light> lightHashtable = new Hashtable<String,Light>();


	for (int i = 0; i < (int)currentState->lightList.size(); i++)
	{
		if (currentState->lightList.get(i)->getName() == s)
		{
			currentState->lightList.removeAt(i);
			i--;
			if (i < 0)
			{
				i = 0;
			}
		}
	}

	currentState->lightByNameHashtable.removeAt(s);

	for (int i = 0; i < sortedLightsLayers.size(); i++)
	{
		for (int j = 0; j < (int)sortedLightsLayers.get(i)->size(); j++)
		{
			if (sortedLightsLayers.get(i)->get(j)->getName() == s)
			{
				sortedLightsLayers.get(i)->removeAt(j);
				j--;
				if (j < 0)
				{
					j = 0;
				}
			}
		}
	}
}

void Map::unloadMapEntity(const string& s)
{ //=========================================================================================================================


	//public ArrayList<MapSprite> entityList = new ArrayList<MapSprite>();
	//public Hashtable<String, MapSprite> entityHashtable = new Hashtable<String, MapSprite>();

	for (int i = 0; i < (int)currentState->entityList.size(); i++)
	{
		if (currentState->entityList.get(i)->getName() == s)
		{
			currentState->entityList.removeAt(i);
			i--;
			if (i < 0)
			{
				i = 0;
			}
		}
	}

	currentState->entityByNameHashtable.removeAt(s);
}

void Map::releaseAllTextures()
{ //=========================================================================================================================
	//go through all chunkTexture[] and release each texture in video memory and set to null
	//then reset all arrays

	//don't reset started threads!!!
	//don't reset these, they will keep going into the next map, which is still useful. they contruct the PNG from raw data which will be loaded later.
	//startedThreads = false;
	//startedHQ2XThreads = false;
	//startedLightThreads=false;


	chunkTexturesLoaded = 0;

	//DO reset these, since we unload these textures.
	allChunkPNGsLoadedAsTextures = false;
	allHQ2XChunkPNGsLoadedAsTextures = false;

	//DO reset this, because we haven't necessarily loaded every light texture yet.
	allLightsLoadedAsTextures = false;


	//unload the utility layers
	delete hitLayer;
	delete cameraLayer;
	delete groundShaderLayer;
	delete lightMaskLayer;

	//   hitLayer = new int[];
	//   cameraLayer= new int[];
	//   groundShaderLayer = new int[];
	//   lightMaskLayer= new int[];

	//we need to reload the utility layers
	utilityLayersLoaded = false;



	
	ArrayList<BobTexture*>* chunks = chunkTexture.getAllValues();
	{
		for (int i = 0; i < chunks->size(); i++)
		{
			BobTexture *t = chunks->get(i);

			if (t != nullptr)
			{
				//don't release the blank texture
				if (t != GLUtils::blankTexture)
				{
					t->release();
				}
			}
		}
	}
	chunkTexture.clear();


	sortedLightsLayers.clear();


	/*if(chunkFileExists!=null)
	{
	   for(int i=0;i<chunksWidth*chunksHeight*2;i++)chunkFileExists->get(i)=false;
	}
	            
	if(HQ2XChunkFileExists!=null)
	{
	   for(int i=0;i<chunksWidth*chunksHeight*2;i++)HQ2XChunkFileExists->get(i)=false;
	}*/

	if (usingHQ2XTexture != nullptr)
	{
		for (int i = 0; i < chunksWidth * chunksHeight * 2; i++)
		{
			usingHQ2XTexture[i] = false;
		}
	}

	delete tilesetIntArray;
	delete paletteRGBByteArray;

	//   tilesetIntArray = new int[];
	//   paletteRGBByteArray= new u8[];

	//System.gc();
}

float Map::mapCamX()
{ //=========================================================================================================================
	//centers the camera x and y on the screen and sets map cam to the upper left corner
	if (this == getCurrentMap())
	{
		return getCameraman()->getX() - (getEngine()->getWidthRelativeToZoom() / 2.0f); // divided by 2.0f because it is getting from the center to the upper left
	}
	else
	{
		return 0 - lastKnownScreenX;
	}
}

float Map::mapCamY()
{ //=========================================================================================================================
	if (this == getCurrentMap())
	{
		return getCameraman()->getY() - (getEngine()->getHeightRelativeToZoom() / 2.0f);
	}
	else
	{
		return 0 - lastKnownScreenY;
	}
}

float Map::getScreenX(float mapX, float width)
{ //=========================================================================================================================

	float zoom = getCameraman()->getZoom();

	//flooring these fixes all the sprite jitter
	float left = (float)(floor(mapX));
	float right = (float)(floor(mapX + width));

	float mapCameraXPixelsHQ = mapCamX();
	float screenleft = mapCameraXPixelsHQ;
	float screenright = mapCameraXPixelsHQ + getEngine()->getWidthRelativeToZoom();

	float screenXPixelsHQ = left - screenleft;

	//if overlapping left side of screen
	if (right >= screenleft && left < screenleft)
	{
		screenXPixelsHQ = 0.0f - (screenleft - left);
	}

	//if onscreen and not overlapping the left side
	if (left >= screenleft && left < screenright)
	{
		screenXPixelsHQ = left - screenleft;
	}


	return screenXPixelsHQ * zoom;
}

float Map::getScreenY(float mapY, float height)
{ //=========================================================================================================================

	float zoom = getCameraman()->getZoom();

	//flooring these fixes all the sprite jitter
	float top = (float)(floor(mapY));
	float bottom = (float)(floor(mapY + height));

	float mapCameraYPixelsHQ = mapCamY();
	float screentop = mapCameraYPixelsHQ;
	float screenbottom = mapCameraYPixelsHQ + getEngine()->getHeightRelativeToZoom();

	float screenYPixelsHQ = top - screentop;

	//if overlapping top side of screen
	if (bottom >= screentop && top < screentop)
	{
		screenYPixelsHQ = 0.0f - (screentop - top);
	}

	//if onscreen and not overlapping the top side
	if (top >= screentop && top < screenbottom)
	{
		screenYPixelsHQ = top - screentop;
	}


	return screenYPixelsHQ * zoom;
}

float Map::screenX()
{
	if (this == getCurrentMap())
	{
		return 0 - mapCamX();
	}
	else
	{
		return lastKnownScreenX;
	}
}

float Map::screenY()
{
	if (this == getCurrentMap())
	{
		return 0 - mapCamY();
	}
	else
	{
		return lastKnownScreenY;
	}
}

void Map::updateLastKnownScreenXYBasedOnCamera()
{ //=========================================================================================================================

	//set map screen x and y

	//if map_cam_x is -400, map_screen_x should be 400

	lastKnownScreenX = 0 - mapCamX();
	lastKnownScreenY = 0 - mapCamY();

	//TODO: can't get rid of these with functions because drawing the last map depends on them not being updated, and instead drawn with an offset.
	//figure out a way to fix this
}


//
//	
//	/**
//	 *
//	 * checks both getHit layer and any mapsprites that aren't characters
//	 *
//	 */
//	public boolean checkHitLayerAndHitSpritesXY(float x, float y)
//	{
//
//		boolean getHit = getHitLayerValueAtXYPixels(x,y);
//
//		if(getHit==false)
//		{
//			//go through all mapsprites, check if map characters
//			for(int i=0;i<activeEntityList.size();i++)
//			{
//				Entity m = activeEntityList.get(i);
//				if(m.getNonWalkable()==true
//						&&x<m.getRight()
//						&&x>m.getLeft()
//						&&y<m.getBottom()
//						&&y>m.getTop()
//				)return true;
//
//			}
//		}
//		return getHit;
//
//	}


bool Map::getHitLayerValueAtXYTile1X(int xTile1X, int yTile1X)
{ //=========================================================================================================================
	return getHitLayerValueAtXYPixels((float)xTile1X * 8 * 2, (float)yTile1X * 8 * 2);
}

bool Map::getHitLayerValueAtXYPixels(float mapXPixelsHQ, float mapYPixelsHQ)
{ //=========================================================================================================================

	if (getEngine()->hitLayerEnabled == false)
	{
		return false;
	}

	if (utilityLayersLoaded == false)
	{
		return true;
	}

	//return "getHit wall" if value is outside of the map
	if (mapYPixelsHQ >= getHeightPixelsHQ() || mapXPixelsHQ >= getWidthPixelsHQ() || mapYPixelsHQ < 0 || mapXPixelsHQ < 0)
	{
		return true;
	}


	int tilex = (((int)(floor(mapXPixelsHQ))) / 8) / 2;
	int tiley = (((int)(floor(mapYPixelsHQ))) / 8) / 2; // divided by 2 because map is getScale 2x. map_x and map_y are 2x as well, giving "subpixel" precision for maps i guess
	//NOTE: will have to float all the tile xy values for movement and placement if i keep it this way

	int tilew = (getWidthPixelsHQ() / 2) / 8; //also divided by 2, see above
	int index = (tiley * tilew) + tilex;


	if (hitLayer[index] == 0)
	{
		return false;
	}
	return true;
}

int Map::getCameraBoundsFXLayerAtXYTile1X(int xTile1X, int yTile1X)
{ //=========================================================================================================================
	return getCameraBoundsFXLayerAtXYPixels((float)xTile1X * 8 * 2, (float)yTile1X * 8 * 2);
}

int Map::getCameraBoundsFXLayerAtXYPixels(float mapXPixelsHQ, float mapYPixelsHQ)
{ //=========================================================================================================================

	if (utilityLayersLoaded == false)
	{
		return 0;
	}

	//return 0 if value is outside of the map
	if (mapYPixelsHQ >= getHeightPixelsHQ() || mapXPixelsHQ >= getWidthPixelsHQ() || mapYPixelsHQ < 0 || mapXPixelsHQ < 0)
	{
		return 0;
	}


	int tilex = ((((int)(floor(mapXPixelsHQ)))) / 8) / 2;
	int tiley = (((int)(floor(mapYPixelsHQ))) / 8) / 2;

	int tilew = (getWidthPixelsHQ() / 2) / 8;
	int index = (tiley * tilew) + tilex;

	return cameraLayer[index];
}

bool Map::isXYWithinScreenByAmt(float x, float y, int amt)
{ //=========================================================================================================================

	float displayWidth = getEngine()->getWidthRelativeToZoom();
	float displayHeight = getEngine()->getHeightRelativeToZoom();

	if (x == -1)
	{
		x = (mapCamX()) + displayWidth / 2;
	}
	if (y == -1)
	{
		y = (mapCamY()) + displayHeight / 2;
	}

	if ((x + amt >= mapCamX() || x >= mapCamX()) && (x - amt <= mapCamX() + displayWidth || x <= mapCamX() + displayWidth) && (y + amt >= mapCamY() || y >= mapCamY()) && (y - amt <= mapCamY() + displayHeight || y <= mapCamY() + displayHeight))
	{
		return true;
	}

	return false;
}

bool Map::isXYXYWithinScreenByAmount(float x, float y, float x2, float y2, float amt)
{ //=========================================================================================================================

	float displayWidth = getEngine()->getWidthRelativeToZoom();
	float displayHeight = getEngine()->getHeightRelativeToZoom();

	if (x == -1)
	{
		x = (mapCamX()) + displayWidth / 2;
	}
	if (y == -1)
	{
		y = (mapCamY()) + displayHeight / 2;
	}
	if (x2 == -1)
	{
		x2 = (mapCamX()) + displayWidth / 2;
	}
	if (y2 == -1)
	{
		y2 = (mapCamY()) + displayHeight / 2;
	}

	if (((mapCamX() >= x && mapCamX() <= x2) || (mapCamX() + displayWidth >= x && mapCamX() + displayWidth <= x2) || (x >= mapCamX() && x <= mapCamX() + displayWidth) || (x2 >= mapCamX() && x2 <= mapCamX() + displayWidth)) && ((mapCamY() >= y && mapCamY() <= y2) || (mapCamY() + displayHeight >= y && mapCamY() + displayHeight <= y2) || (y >= mapCamY() && y <= mapCamY() + displayHeight) || (y2 >= mapCamY() && y2 <= mapCamY() + displayHeight)))
	{
		return true;
	}

	return false;
}

bool Map::isXYWithinScreen(float x, float y)
{ //=========================================================================================================================

	return isXYWithinScreenByAmt(x, y, 0);
}


//
//	
//	public void setTextureMD5Names(String getGroundLayerMD5,String getGroundObjectsMD5,String getGroundShadowMD5,String getObjectsMD5,String getObjects2MD5,String getObjectShadowMD5,String getAboveMD5,String getAbove2MD5,String getSpriteShadowMD5,String getGroundShaderMD5,String getCameraBoundsMD5,String getHitBoundsMD5,String getLightMaskMD5,String paletteMD5,String getTilesMD5)
//	{
//
//
//		//name = object.name;
//		this.getGroundLayerMD5 = getGroundLayerMD5;
//		this.getGroundObjectsMD5 = getGroundObjectsMD5;
//		this.getGroundShadowMD5 = getGroundShadowMD5;
//		this.getObjectsMD5 = getObjectsMD5;
//		this.getObjects2MD5 = getObjects2MD5;
//		this.getObjectShadowMD5 = getObjectShadowMD5;
//		this.getAboveMD5 = getAboveMD5;
//		this.getAbove2MD5 = getAbove2MD5;
//		this.getSpriteShadowMD5 = getSpriteShadowMD5;
//		this.getGroundShaderMD5 = getGroundShaderMD5;
//		this.getCameraBoundsMD5 = getCameraBoundsMD5;
//		this.getHitBoundsMD5 = getHitBoundsMD5;
//		this.getLightMaskMD5 = getLightMaskMD5;
//		this.paletteMD5 = paletteMD5;
//		this.getTilesMD5 = getTilesMD5;
//
//	}


//The following method was originally marked 'synchronized':
BobTexture* Map::getChunkTexture(int index)
{ //=========================================================================================================================
	return chunkTexture.get(index);
}

//The following method was originally marked 'synchronized':
void Map::setChunkTexture(int index, BobTexture* t)
{ //=========================================================================================================================
	chunkTexture.put(index, t);
}

//The following method was originally marked 'synchronized':
void Map::releaseChunkTexture(int index)
{ //=========================================================================================================================
	chunkTexture.get(index)->release();
	chunkTexture.put(index, nullptr);
}

//The following method was originally marked 'synchronized':
bool Map::getChunkPNGFileExists(int index)
{ //=========================================================================================================================
	return chunkPNGFileExists[index];
}

//The following method was originally marked 'synchronized':
void Map::setChunkPNGFileExists_S(int index, bool done)
{ //=========================================================================================================================
	chunkPNGFileExists[index] = done;
}

//The following method was originally marked 'synchronized':
bool Map::getHQ2XChunkPNGFileExists(int index)
{ //=========================================================================================================================
	return hq2xChunkPNGFileExists[index];
}

//The following method was originally marked 'synchronized':
void Map::setHQ2XChunkFileExists_S(int index, bool done)
{ //=========================================================================================================================
	hq2xChunkPNGFileExists[index] = done;
}

//The following method was originally marked 'synchronized':
void Map::incrementChunkTexturesLoaded()
{ //=========================================================================================================================
	chunkTexturesLoaded++;
}

//The following method was originally marked 'synchronized':
void Map::decrementChunkTexturesLoaded()
{ //=========================================================================================================================
	chunkTexturesLoaded--;
}

bool Map::loadChunkTexturesFromCachePNGs()
{ //=========================================================================================================================

	bool tempAllChunksLoaded = true;

	//for each texture that needs to be on-screen, spiraling clockwise from CAMERA TARGET POSITION

	//get chunkX and Y based on player location

	int startChunkX = (int)(getCameraman()->getX()) / chunkSizePixelsHQ2X;
	int startChunkY = (int)(getCameraman()->getY()) / chunkSizePixelsHQ2X;
	if (startChunkX < 0 || startChunkX >= chunksWidth)
	{
		startChunkX = 0;
	}
	if (startChunkY < 0 || startChunkY >= chunksHeight)
	{
		startChunkY = 0;
	}
	int chunkX = startChunkX;
	int chunkY = startChunkY;
	int dir_UP = 0;
	int dir_DOWN = 1;
	int dir_LEFT = 2;
	int dir_RIGHT = 3;
	int dir = dir_RIGHT;
	int movementsUntilChangeDirection = 1;
	int movementsThisDirection = 0;
	int directionChangesUntilIncreaseMovements = 0; //when this is equal to 2, increase movementsUntilChangeDirection


	int sw = (int)(getEngine()->getWidthRelativeToZoom());
	int sh = (int)(getEngine()->getHeightRelativeToZoom());

	int camX = ((int)(floor(((mapCamX())))));
	int camY = ((int)(floor(((mapCamY())))));

	while (movementsUntilChangeDirection < chunksWidth * 2 || movementsUntilChangeDirection < chunksHeight * 2)
	{
		if (MapManager::loadTexturesOnDemand == false || (((chunkX + 1) * chunkSizePixelsHQ2X) - 1 >= camX && chunkX * chunkSizePixelsHQ2X < camX + (sw) && ((chunkY + 1) * chunkSizePixelsHQ2X) - 1 >= camY && chunkY * chunkSizePixelsHQ2X < camY + (sh)))
		{
			if (chunkX >= 0 && chunkX < chunksWidth && chunkY >= 0 && chunkY < chunksHeight)
			{
				for (int chunkLayer = 0; chunkLayer < 2; chunkLayer++)
				{
					int chunkIndex = (chunksWidth * chunksHeight * chunkLayer) + ((chunkY * chunksWidth) + chunkX);

					//check if tile has texture already in gpu
					if (getChunkTexture(chunkIndex) == nullptr)
					{
						tempAllChunksLoaded = false;

						//if it doesnt have a texture, need to load the texture
						//check for existence of texture in groundMD5

						if (getChunkPNGFileExists(chunkIndex) == true || (MapManager::generateHQ2XChunks == true && getHQ2XChunkPNGFileExists(chunkIndex) == true))
						{
							BobFile* textureFile = nullptr;

							if (MapManager::generateHQ2XChunks == true && getHQ2XChunkPNGFileExists(chunkIndex) == true)
							{
								textureFile = new BobFile(FileUtils::appDataPath + string("_") + getGroundLayerMD5() + "/" + string("2x") + "/" + to_string(chunkIndex));
								usingHQ2XTexture[chunkIndex] = true;
							}
							else
							{
								textureFile = new BobFile(FileUtils::appDataPath + string("_") + getGroundLayerMD5() + "/" + to_string(chunkIndex));
							}

							if (textureFile->exists() == false)
							{
								//(exception())->printStackTrace();
								continue;
							}

							//if it exists:

							//if it is 0 bytes, just point texture to blank tile

							if (textureFile->length() < 1)
							{
								setChunkTexture(chunkIndex, GLUtils::blankTexture);
							}
							else
							{
								//************
								//there is no reason to do this, single threaded deferred loading one chunk per frame is fast enough
								//************
								//DONTNEEDTODO: create new thread for loading textures
								//however, this isn't possible with lwjgl without some hacks, so what CAN we do?
								//let's see why it gives the error it does...

								setChunkTexture(chunkIndex, GLUtils::getTextureFromPNG(textureFile->getAbsolutePath()));
							}

							incrementChunkTexturesLoaded();
						}
					}
				}

				if (tempAllChunksLoaded == false)
				{
					break;
				}
			}
		}
		else
		{
			//unload texture
			if (chunkX >= 0 && chunkX < chunksWidth && chunkY >= 0 && chunkY < chunksHeight)
			{
				for (int chunkLayer = 0; chunkLayer < 2; chunkLayer++)
				{
					int chunkIndex = (chunksWidth * chunksHeight * chunkLayer) + ((chunkY * chunksWidth) + chunkX);

					if (getChunkTexture(chunkIndex) != nullptr && getChunkTexture(chunkIndex) != GLUtils::blankTexture) //fix WHITE TILE bug?
					{
						releaseChunkTexture(chunkIndex);


						decrementChunkTexturesLoaded();
					}
				}
			}
		}

		if (movementsThisDirection < movementsUntilChangeDirection)
		{
			if (dir == dir_RIGHT)
			{
				chunkX++;
			}
			else if (dir == dir_LEFT)
			{
				chunkX--;
			}
			else if (dir == dir_DOWN)
			{
				chunkY++;
			}
			else if (dir == dir_UP)
			{
				chunkY--;
			}

			movementsThisDirection++;
		}
		else
		{
			movementsThisDirection = 0;

			if (dir == dir_RIGHT)
			{
				dir = dir_DOWN;
			}
			else if (dir == dir_LEFT)
			{
				dir = dir_UP;
			}
			else if (dir == dir_DOWN)
			{
				dir = dir_LEFT;
			}
			else if (dir == dir_UP)
			{
				dir = dir_RIGHT;
			}

			directionChangesUntilIncreaseMovements++;

			if (directionChangesUntilIncreaseMovements >= 2)
			{
				directionChangesUntilIncreaseMovements = 0;
				movementsUntilChangeDirection++;
			}

			if (dir == dir_RIGHT)
			{
				chunkX++;
			}
			else if (dir == dir_LEFT)
			{
				chunkX--;
			}
			else if (dir == dir_DOWN)
			{
				chunkY++;
			}
			else if (dir == dir_UP)
			{
				chunkY--;
			}

			movementsThisDirection++;
		}
	}

	return false;
	//return tempAllChunksLoaded;
}

bool Map::loadLightTexturesFromCachePNGs()
{ //=========================================================================================================================

	bool tempAllLightTexturesLoaded = true;


	for (int i = 0; i < (int)currentState->lightList.size(); i++)
	{
		{
			//if(lightList.get(i).mapAsset==this)
			Light* l = currentState->lightList.get(i);

			//check if tile has texture already in gpu
			if (l->texture == nullptr)
			{
				//see if it's in the hashmap loaded already from a different map
				l->texture = getMapManager()->lightTextureHashMap.get(l->getFileName());


				if (l->texture == nullptr)
				{
					tempAllLightTexturesLoaded = false;

					//if it doesnt have a texture, need to load the texture
					//check for existence of texture

					//check our PNG file hashmap which was filled when we started threads for missing textures.
					if (l->getLightTexturePNGFileExists_S() == true)
					{
						//floatcheck it exists, this should never be false.
						BobFile* textureFile = new BobFile(FileUtils::appDataPath + "l" + "/" + l->getFileName());
						if (textureFile->exists() == false)
						{
							//(exception())->printStackTrace();
							continue;
						}


						BobTexture* t = GLUtils::getTextureFromPNG(FileUtils::appDataPath + "l" + "/" + l->getFileName());
						getMapManager()->lightTextureHashMap.put(l->getFileName(), t);

						l->texture = t;
					}
				}
			}
		}

		if (tempAllLightTexturesLoaded == false)
		{
			break; //only load one per frame
		}
	}

	return tempAllLightTexturesLoaded;
}

bool Map::loadHQ2XTexturesFromCachePNGs()
{ //=========================================================================================================================

	//run through all chunks
	//this can be linear (not spiral) because this is only called when they are being created by threads (in a spiral) so it will update in a spiral anyway.
	//it's actually probably slightly less efficient to use a spiral since it has to cover a lot of blank space outside the map

	bool tempAllHQ2XChunksLoaded = true;

	for (int chunkY = 0; chunkY < chunksHeight; chunkY++)
	{
		for (int chunkX = 0; chunkX < chunksWidth; chunkX++)
		{
			for (int chunkLayer = 0; chunkLayer < 2; chunkLayer++)
			{
				int chunkIndex = (chunksWidth * chunksHeight * chunkLayer) + ((chunkY * chunksWidth) + chunkX);

				if (usingHQ2XTexture[chunkIndex] == false)
				{
					tempAllHQ2XChunksLoaded = false;

					if (getHQ2XChunkPNGFileExists(chunkIndex) == true)
					{
						BobFile* textureFile = nullptr;

						if (getHQ2XChunkPNGFileExists(chunkIndex) == true)
						{
							textureFile = new BobFile(FileUtils::appDataPath + string("_") + getGroundLayerMD5() + "/" + string("2x") + "/" + to_string(chunkIndex));
						}

						if (textureFile->exists() == false)
						{
							//(exception())->printStackTrace();
							continue;
						}

						BobTexture* t = getChunkTexture(chunkIndex);

						if (t != nullptr)
						{
							//remove previous texture from GPU.
							if (t != GLUtils::blankTexture)
							{
								t->release();
								t = nullptr;
							}
							setChunkTexture(chunkIndex, nullptr);
						}

						//set to new texture

						if (textureFile->length() < 1)
						{
							setChunkTexture(chunkIndex, GLUtils::blankTexture);
						}
						else
						{
							//DONE: create new thread: load it as a texture, set TileTexture to this texture, delete ByteBuffer
							setChunkTexture(chunkIndex, GLUtils::getTextureFromPNG(textureFile->getAbsolutePath()));
						}

						usingHQ2XTexture[chunkIndex] = true;
					}
				}
			}
		}
	}

	return tempAllHQ2XChunksLoaded;
}

//The following method was originally marked 'synchronized':
void Map::incrementChunkPNGThreadsCreated()
{ //=========================================================================================================================
	chunkPNGThreadsCreated++;
	if (chunkPNGThreadsCreated > maxChunkPNGThreadsCreated)
	{
		maxChunkPNGThreadsCreated = chunkPNGThreadsCreated;
	}
}

//The following method was originally marked 'synchronized':
void Map::decrementChunkPNGThreadsCreated_S()
{ //=========================================================================================================================
	chunkPNGThreadsCreated--;
}

void Map::startThreadsForMissingChunkPNGs()
{ //=========================================================================================================================


	//does cache/groundMD5/ exist?
	//if not, make it.
	FileUtils::makeDir(FileUtils::appDataPath + string("_") + getGroundLayerMD5());
	FileUtils::makeDir(FileUtils::appDataPath + string("_") + getGroundLayerMD5() + "/" + string("1x_padded") + "/");
	FileUtils::makeDir(FileUtils::appDataPath + string("_") + getGroundLayerMD5() + "/" + string("2x") + "/");


	//   if (MapManager::useThreads == true && generatePNGExecutorService == nullptr)
	//   {
	//      generatePNGExecutorService = Executors::newFixedThreadPool(3);
	//   }
	//   //if(MapManager.useThreads==true)generatePNGExecutorService = Executors.newFixedThreadPool(3);


	//for each texture that needs to be on-screen, spiraling clockwise from CAMERA TARGET POSITION

	//get chunkX and Y based on player location

	int startChunkX = (int)(getCameraman()->getX()) / chunkSizePixelsHQ2X;
	int startChunkY = (int)(getCameraman()->getY()) / chunkSizePixelsHQ2X;

	if (startChunkX < 0 || startChunkX >= chunksWidth)
	{
		startChunkX = 0;
	}
	if (startChunkY < 0 || startChunkY >= chunksHeight)
	{
		startChunkY = 0;
	}

	int chunkX = startChunkX;
	int chunkY = startChunkY;

	int dir_UP = 0;
	int dir_DOWN = 1;
	int dir_LEFT = 2;
	int dir_RIGHT = 3;

	int dir = dir_RIGHT;


	int movementsUntilChangeDirection = 1;
	int movementsThisDirection = 0;
	int directionChangesUntilIncreaseMovements = 0; //when this is equal to 2, increase movementsUntilChangeDirection

	while (movementsUntilChangeDirection < chunksWidth * 2 || movementsUntilChangeDirection < chunksHeight * 2)
	{
		if (chunkX >= 0 && chunkX < chunksWidth && chunkY >= 0 && chunkY < chunksHeight)
		{
			for (int chunkLayer = 0; chunkLayer < 2; chunkLayer++)
			{
				int chunkIndex = (chunksWidth * chunksHeight * chunkLayer) + ((chunkY * chunksWidth) + chunkX);


				//check for existence of texture in groundMD5
				BobFile* textureFile = new BobFile(FileUtils::appDataPath + string("_") + getGroundLayerMD5() + "/" + to_string(chunkIndex));
				BobFile* hq2xTextureFile = new BobFile(FileUtils::appDataPath + string("_") + getGroundLayerMD5() + "/" + string("2x") + "/" + to_string(chunkIndex));


				if (hq2xTextureFile->exists())
				{
					setHQ2XChunkFileExists_S(chunkIndex, true);
				}

				if (textureFile->exists())
				{
					setChunkPNGFileExists_S(chunkIndex, true);
				}
				else
				{
					//if it doesnt exist
					//load tileset and palette into memory if it is not already loaded into mem from another tile

					if (tilesetIntArray == nullptr)
					{
						tilesetIntArray = FileUtils::loadIntFileFromCacheOrDownloadIfNotExist(string("") + getTilesMD5());
					}

					if (paletteRGBByteArray == nullptr)
					{
						paletteRGBByteArray = FileUtils::loadByteFileFromCacheOrDownloadIfNotExist(string("") + getPaletteMD5());
					}


					//create new thread:
					int threadChunkLayer = chunkLayer;
					int threadChunkX = chunkX;
					int threadChunkY = chunkY;
					int threadChunkIndex = chunkIndex;
					int* threadTilesetIntArray = tilesetIntArray; //we send in a final pointer to this because it is set to null when the map is unloaded, but the threads may still be creating map tile pngs and will release this pointer when they die.
					u8* threadPaletteRGBByteArray = paletteRGBByteArray;


					if (MapManager::useThreads == true)
					{
						incrementChunkPNGThreadsCreated();
						//
						//                  generatePNGExecutorService->execute([&] ()
						//                     {
						//                        try
						//                        {
						//                           Thread::currentThread().setName("MapAsset_startThreadsForMissingChunkPNGs");
						//                        }
						//                        catch (SecurityException e)
						//                        {
						//                           e->printStackTrace();
						//                        }
						//
						//
						//                        createChunkTexturePNG_S(threadChunkLayer, threadChunkX, threadChunkY, threadChunkIndex, threadTilesetIntArray, threadPaletteRGBByteArray);
						//                        setChunkPNGFileExists_S(threadChunkIndex, true);
						//                        decrementChunkPNGThreadsCreated_S();
						//                     }
						//
						//
						//                  );
					}
					else
					{
						//do it linearly, waiting for all chunks to finish before continuing
						createChunkTexturePNG_S(threadChunkLayer, threadChunkX, threadChunkY, threadChunkIndex, threadTilesetIntArray, threadPaletteRGBByteArray);
						setChunkPNGFileExists_S(threadChunkIndex, true);
					}
				}
			}
		}

		if (movementsThisDirection < movementsUntilChangeDirection)
		{
			if (dir == dir_RIGHT)
			{
				chunkX++;
			}
			else if (dir == dir_LEFT)
			{
				chunkX--;
			}
			else if (dir == dir_DOWN)
			{
				chunkY++;
			}
			else if (dir == dir_UP)
			{
				chunkY--;
			}

			movementsThisDirection++;
		}
		else
		{
			movementsThisDirection = 0;

			if (dir == dir_RIGHT)
			{
				dir = dir_DOWN;
			}
			else if (dir == dir_LEFT)
			{
				dir = dir_UP;
			}
			else if (dir == dir_DOWN)
			{
				dir = dir_LEFT;
			}
			else if (dir == dir_UP)
			{
				dir = dir_RIGHT;
			}

			directionChangesUntilIncreaseMovements++;

			if (directionChangesUntilIncreaseMovements >= 2)
			{
				directionChangesUntilIncreaseMovements = 0;
				movementsUntilChangeDirection++;
			}

			if (dir == dir_RIGHT)
			{
				chunkX++;
			}
			else if (dir == dir_LEFT)
			{
				chunkX--;
			}
			else if (dir == dir_DOWN)
			{
				chunkY++;
			}
			else if (dir == dir_UP)
			{
				chunkY--;
			}

			movementsThisDirection++;
		}
	}


	//unload tileset and palette if they were loaded

	delete tilesetIntArray;
	delete paletteRGBByteArray;

	tilesetIntArray = nullptr;
	paletteRGBByteArray = nullptr;


	//if(MapManager.useThreads==true)generatePNGExecutorService.shutdown();
}

//The following method was originally marked 'synchronized':
void Map::incrementLightPNGThreadsCreated()
{ //=========================================================================================================================
	lightPNGThreadsCreated++;
	if (lightPNGThreadsCreated > maxLightPNGThreadsCreated)
	{
		maxLightPNGThreadsCreated = lightPNGThreadsCreated;
	}
}

//The following method was originally marked 'synchronized':
void Map::decrementLightPNGThreadsCreated_S()
{ //=========================================================================================================================
	lightPNGThreadsCreated--;
}

void Map::startThreadsForMissingLightPNGs()
{ //=========================================================================================================================


	//does cache/groundMD5/ exist?
	//if not, make it.
	FileUtils::makeDir(FileUtils::appDataPath + string("l") + "/");


	//   //if(MapManager.useThreads==true&&generatePNGExecutorService==null)generatePNGExecutorService = Executors.newFixedThreadPool(3);
	//   if (MapManager::useThreads == true && generateLightPNGExecutorService == nullptr)
	//   {
	//      generateLightPNGExecutorService = Executors::newFixedThreadPool(3);
	//   }


	//go through all the lights in lightList
	//for all the lights see if there is a texture generated for it, stored in the light object itself
	//if there isn't, generate the light as a bufferedImage, create a texture for it, and set it in the light object

	for (int i = 0; i < (int)currentState->lightList.size(); i++)
	{
		{
			//if(lightList.get(i).mapAsset==this)
			Light* l = currentState->lightList.get(i);


			//don't create a thread to generate a texture that is already being made.
			//this prevents collisions where a thread is overwriting a png that already exists while it is being loaded as a texture
			bool c = false;
			for (int j = 0; j < i; j++)
			{
				if (currentState->lightList.get(j)->getFileName() == l->getFileName())
				{
					c = true;
					break;
				}
			}
			if (c)
			{
				continue;
			}


			if (l->getLightTexturePNGFileExists_S() == false)
			{
				//check for existence of texture in cache folder
				BobFile* textureFile = new BobFile(FileUtils::appDataPath + string("l") + "/" + l->getFileName());
				if (textureFile->exists())
				{
					l->setLightTexturePNGFileExists_S(true);
				}
				else
				{
					if (MapManager::useThreads == true)
					{
						Light* const threadLight = currentState->lightList.get(i);
						const string threadLightFilename = threadLight->getFileName();

						incrementLightPNGThreadsCreated();
						//
						//                  generateLightPNGExecutorService->execute([&] ()
						//                     {
						//                        try
						//                        {
						//                           Thread::currentThread().setName("MapAsset_startThreadsForMissingLightPNGs");
						//                        }
						//                        catch (SecurityException e)
						//                        {
						//                           e->printStackTrace();
						//                        }
						//
						//                        threadLight->createLightTexturePNG(FileUtils::cacheDir + string("l") + "/" + threadLightFilename);
						//                        threadLight->setLightTexturePNGFileExists_S(true);
						//
						//                        decrementLightPNGThreadsCreated_S();
						//                     }
						//
						//
						//                  );
					}
					else
					{
						//do it linearly, waiting for all to finish before continuing
						l->createLightTexturePNG(FileUtils::appDataPath + string("l") + "/" + l->getFileName());

						l->setLightTexturePNGFileExists_S(true);
					}
				}
			}
		}
	}

	//if(MapManager.useThreads==true)generateLightPNGExecutorService.shutdown();
}

//The following method was originally marked 'synchronized':
void Map::incrementHQ2XChunkPNGThreadsCreated()
{ //=========================================================================================================================
	hq2xChunkPNGThreadsCreated++;
	if (hq2xChunkPNGThreadsCreated > maxHq2xChunkPNGThreadsCreated)
	{
		maxHq2xChunkPNGThreadsCreated = hq2xChunkPNGThreadsCreated;
	}
}

//The following method was originally marked 'synchronized':
void Map::decrementHQ2XChunkPNGThreadsCreated()
{ //=========================================================================================================================
	hq2xChunkPNGThreadsCreated--;
}

void Map::startThreadsForMissingHQ2XChunkPNGs()
{ //=========================================================================================================================

	//for each chunk, starting at player position

	//does cache/groundMD5/ exist?
	//if not, make it.
	FileUtils::makeDir(FileUtils::appDataPath + string("_") + getGroundLayerMD5());
	FileUtils::makeDir(FileUtils::appDataPath + string("_") + getGroundLayerMD5() + "/" + string("1x_padded") + "/");
	FileUtils::makeDir(FileUtils::appDataPath + string("_") + getGroundLayerMD5() + "/" + string("2x") + "/");


	//   if (MapManager::useThreads == true && generatePNGExecutorService == nullptr)
	//   {
	//      generatePNGExecutorService = Executors::newFixedThreadPool(3);
	//   }
	//   //if(MapManager.useThreads==true)generateHQ2XPNGExecutorService = Executors.newFixedThreadPool(3);


	int startChunkX = (int)(getCameraman()->getX()) / chunkSizePixelsHQ2X;
	int startChunkY = (int)(getCameraman()->getY()) / chunkSizePixelsHQ2X;

	if (startChunkX < 0 || startChunkX >= chunksWidth)
	{
		startChunkX = 0;
	}
	if (startChunkY < 0 || startChunkY >= chunksHeight)
	{
		startChunkY = 0;
	}

	int chunkX = startChunkX;
	int chunkY = startChunkY;

	int dir_UP = 0;
	int dir_DOWN = 1;
	int dir_LEFT = 2;
	int dir_RIGHT = 3;

	int dir = dir_RIGHT;


	int movementsUntilChangeDirection = 1;
	int movementsThisDirection = 0;
	int directionChangesUntilIncreaseMovements = 0; //when this is equal to 2, increase movementsUntilChangeDirection


	while (movementsUntilChangeDirection < chunksWidth * 2 || movementsUntilChangeDirection < chunksHeight * 2)
	{
		if (chunkX >= 0 && chunkX < chunksWidth && chunkY >= 0 && chunkY < chunksHeight)
		{
			//check hq2x exists only from bottom layer, since we generate both at the same time.
			int chunkLayer = 0;

			int chunkIndex = (chunksWidth * chunksHeight * chunkLayer) + ((chunkY * chunksWidth) + chunkX);
			int chunkIndexOverLayer = (chunksWidth * chunksHeight * 1) + ((chunkY * chunksWidth) + chunkX);

			//check for existence of texture in groundMD5
			BobFile* hq2xTextureFile = new BobFile(FileUtils::appDataPath + string("_") + getGroundLayerMD5() + "/" + string("2x") + "/" + to_string(chunkIndex));

			if (hq2xTextureFile->exists())
			{
				setHQ2XChunkFileExists_S(chunkIndex, true);
				setHQ2XChunkFileExists_S(chunkIndexOverLayer, true);
			}
			else
			{
				//create new thread:
				const int threadChunkX = chunkX;
				const int threadChunkY = chunkY;
				const int threadChunkIndex = chunkIndex;
				const int threadChunkIndexOverLayer = chunkIndexOverLayer;

				if (MapManager::useThreads == true)
				{
					incrementHQ2XChunkPNGThreadsCreated();
					//
					//               generatePNGExecutorService->execute([&] ()
					//                  {
					//                     try
					//                     {
					//                        Thread::currentThread().setName("MapAsset_startThreadsForMissingHQ2XChunkPNGs");
					//                     }
					//                     catch (SecurityException e)
					//                     {
					//                        e->printStackTrace();
					//                     }
					//
					//
					//                     createHQ2XTexturePNG_THREAD(threadChunkX, threadChunkY);
					//                     setHQ2XChunkFileExists_S(threadChunkIndex, true);
					//                     setHQ2XChunkFileExists_S(threadChunkIndexOverLayer, true);
					//
					//                     decrementHQ2XChunkPNGThreadsCreated();
					//                  }
					//
					//               );
				}
				else
				{
					//do it linearly, waiting for all chunks to finish before continuing
					createHQ2XTexturePNG_THREAD(threadChunkX, threadChunkY);
					setHQ2XChunkFileExists_S(threadChunkIndex, true);
					setHQ2XChunkFileExists_S(threadChunkIndexOverLayer, true);
				}
			}
		}


		if (movementsThisDirection < movementsUntilChangeDirection)
		{
			if (dir == dir_RIGHT)
			{
				chunkX++;
			}
			else if (dir == dir_LEFT)
			{
				chunkX--;
			}
			else if (dir == dir_DOWN)
			{
				chunkY++;
			}
			else if (dir == dir_UP)
			{
				chunkY--;
			}

			movementsThisDirection++;
		}
		else
		{
			movementsThisDirection = 0;

			if (dir == dir_RIGHT)
			{
				dir = dir_DOWN;
			}
			else if (dir == dir_LEFT)
			{
				dir = dir_UP;
			}
			else if (dir == dir_DOWN)
			{
				dir = dir_LEFT;
			}
			else if (dir == dir_UP)
			{
				dir = dir_RIGHT;
			}


			directionChangesUntilIncreaseMovements++;

			if (directionChangesUntilIncreaseMovements >= 2)
			{
				directionChangesUntilIncreaseMovements = 0;
				movementsUntilChangeDirection++;
			}


			if (dir == dir_RIGHT)
			{
				chunkX++;
			}
			else if (dir == dir_LEFT)
			{
				chunkX--;
			}
			else if (dir == dir_DOWN)
			{
				chunkY++;
			}
			else if (dir == dir_UP)
			{
				chunkY--;
			}

			movementsThisDirection++;
		}
	}


	//if(MapManager.useThreads==true)generateHQ2XPNGExecutorService.shutdown();
}

void Map::createChunkTexturePNG_S(int chunkLayer, int chunkX, int chunkY, int chunkIndex, int* tilesetIntArray, u8* paletteRGBByteArray)
{ //=========================================================================================================================

	//Thread.yield();

	//create chunkImage
	BufferedImage* chunkImage = new BufferedImage(chunkSizeTiles1X * 8, chunkSizeTiles1X * 8, BufferedImage::TYPE_INT_ARGB);
	BufferedImage* chunkImageBorder = new BufferedImage(chunkSizeTiles1X * 8 + 2, chunkSizeTiles1X * 8 + 2, BufferedImage::TYPE_INT_ARGB);


	//***************************************
	//if i don't init the graphics, the buffered image output has a random alpha jitter for a reason i can't figure out...
	//it actually looks nice, but i wanted to figure out what the heck was doing it!
	//NOPE this isn't why!
	//***************************************

	/*Graphics G = chunkImage.getGraphics();
	G.setColor(new Color(0,0,0,0));
	G.fillRect(0, 0, chunkImage.getWidth(), chunkImage.getHeight());
	G.dispose();
	G = chunkImageBorder.getGraphics();
	G.setColor(new Color(0,0,0,0));
	G.fillRect(0, 0, chunkImageBorder.getWidth(), chunkImageBorder.getHeight());
	G.dispose();*/

	int* layerChunkBuffer = new int[((chunkSizeTiles1X + 2) * (chunkSizeTiles1X + 2))];

	string layerFileName = "";

	bool blank = true;

	if (chunkLayer == 0)
	{
		blank = false;

		for (int l = 0; l < 6; l++)
		{
			bool shadowLayer = false;

			if (l == 0)
			{
				layerFileName = getGroundLayerMD5();
			}
			if (l == 1)
			{
				layerFileName = getGroundObjectsMD5();
			}
			if (l == 2)
			{
				layerFileName = getGroundShadowMD5();
				shadowLayer = true;
			}
			if (l == 3)
			{
				layerFileName = getObjectsMD5();
			}
			if (l == 4)
			{
				layerFileName = getObjects2MD5();
			}
			if (l == 5)
			{
				layerFileName = getObjectShadowMD5();
				shadowLayer = true;
			}

			drawTileLayerIntoBufferedImage(layerFileName, chunkImage, chunkImageBorder, chunkX, chunkY, layerChunkBuffer, shadowLayer, tilesetIntArray, paletteRGBByteArray);
		}
	}
	else
	{
		if (chunkLayer == 1)
		{
			for (int l = 0; l < 3; l++)
			{
				bool shadowLayer = false;

				if (l == 0)
				{
					layerFileName = getAboveMD5();
				}
				if (l == 1)
				{
					layerFileName = getAbove2MD5();
				}
				if (l == 2)
				{
					layerFileName = getSpriteShadowMD5();
					shadowLayer = true;
				}

				bool changedImage = drawTileLayerIntoBufferedImage(layerFileName, chunkImage, chunkImageBorder, chunkX, chunkY, layerChunkBuffer, shadowLayer, tilesetIntArray, paletteRGBByteArray);
				if (changedImage == true)
				{
					blank = false;
				}
			}
		}
	}


	if (blank == true)
	{
		//log.debug("Made blank file: "+chunkLayer+"_"+chunkIndex);

		//save 0 byte placeholder, this will always load blank texture
		BobFile* f = new BobFile(string("") + FileUtils::appDataPath + string("_") + getGroundLayerMD5() + "/" + to_string(chunkIndex));
		BobFile* f2 = new BobFile(string("") + FileUtils::appDataPath + string("_") + getGroundLayerMD5() + "/" + string("1x_padded") + "/" + to_string(chunkIndex));

		try
		{
			f->createNewFile();
			f2->createNewFile();
		}
		catch (exception e)//IOException e)
		{
			//e->printStackTrace();
		}
	}
	else
	{
		//save this as png in folder groundMD5/0_0_0
		FileUtils::saveImage(string("") + FileUtils::appDataPath + string("_") + getGroundLayerMD5() + "/" + to_string(chunkIndex), chunkImage);
		FileUtils::saveImage(string("") + FileUtils::appDataPath + string("_") + getGroundLayerMD5() + "/" + string("1x_padded") + "/" + to_string(chunkIndex), chunkImageBorder);
	}
}

bool Map::drawTileLayerIntoBufferedImage(const string& layerFileName, BufferedImage* chunkImage, BufferedImage* chunkImageBorder, int chunkX, int chunkY, int* layerChunkBuffer, bool shadowLayer, int* tilesetIntArray, u8* paletteRGBByteArray)
{ //=========================================================================================================================


	bool isBlank = true;

	//open layer as file, load chunk into memory, with 1 tile border, filling with 0 if it is on the map edge
	RandomAccessFile* raf = nullptr;
	try
	{
		raf = new RandomAccessFile(string("") + FileUtils::appDataPath + layerFileName, "r");
	}
	catch (exception e)//FileNotFoundException e)
	{
		//e->printStackTrace();
	}

	bool groundLayer = false;
	if (layerFileName == getGroundLayerMD5())
	{
		groundLayer = true;
	}


	//*********
	//IMPORTANT: need to generate chunk sizes that are exactly the size of a power of two.
	//*********


	//at 512, actual chunks will be 256x256, or 32 x 32 tiles
	//but this has a 2 tile border around all sides, so actual tile chunk is 30 x 30
	//we want to get as close to 512x512 as we can for power of two textures, no wasted space


	//NO: can i hq2x as a shader in gpu memory? probably not, don't need to.

	//DONE: need framebuffer, need shader support


	//so:  here we want to load chunkSize + 2 tiles, so 34 x 34


	//so instead let's take 34x34 chunk to begin with, 272x272
	//then we generate a 258x258 png from this, with 1 pixel around border
	//then we save this as BOTH a 256x256 png and a 258x258 png

	//when loading textures into gpu for texture, use the 256x256 png

	//when loading into memory for hq2x, use the 258x258
	//hq2x this, producing 516x516
	//remove 2 from borders, producing 512x512
	//save this as nice clean 512x512 even DXT


	try
	{
		int startY = (chunkY * (chunkSizeTiles1X));
		int startX = (chunkX * (chunkSizeTiles1X));

		//startY - 1 because of border.
		for (int y = startY - 1; y < (startY + chunkSizeTiles1X) + 1; y++)
		{
			//if y is actually negative, fill it with 0 because it's off the map
			if (y >= getHeightTiles1X() || y < 0)
			{
				//fill with 0
			}
			else
			{
				if (chunkX == 0)
				{
					//seek to 0
					raf->seek(static_cast<long long>(((y * getWidthTiles1X()) + (startX)) * 4)); //*4 for bytes -> int4

					//for -1 to +1
					//if x is -1, fill with 0

					for (int x = startX - 1; x < (startX + chunkSizeTiles1X) + 1; x++)
					{
						if (x >= getWidthTiles1X() || x < 0)
						{
							layerChunkBuffer[(((y + 1) - startY) * (chunkSizeTiles1X + 2)) + ((x + 1) - startX)] = 0;
						}
						else
						{
							int result = raf->readInt();

							//								int byte1 = raf.read() & 0xFF;
							//								int byte2 = raf.read() & 0xFF;
							//
							//								int result = (byte2<<8) + byte1;

							if (result != 0)
							{
								isBlank = false;
							}

							layerChunkBuffer[(((y + 1) - startY) * (chunkSizeTiles1X + 2)) + ((x + 1) - startX)] = result;
						}
					}
				}
				else
				{
					//seek to -1
					raf->seek(static_cast<long long>(((y * getWidthTiles1X()) + (startX - 1)) * 4));

					//for 0 to +2

					for (int x = (startX); x < (startX + chunkSizeTiles1X) + 2; x++)
					{
						if (x >= getWidthTiles1X() || x < 0)
						{
							layerChunkBuffer[(((y + 1) - startY) * (chunkSizeTiles1X + 2)) + (x - startX)] = 0;
						}
						else
						{
							int result = raf->readInt();

							//								int byte1 = raf.read() & 0xFF;
							//								int byte2 = raf.read() & 0xFF;
							//
							//								int result = (byte2<<8) + byte1;

							if (result != 0)
							{
								isBlank = false;
							}

							layerChunkBuffer[(((y + 1) - startY) * (chunkSizeTiles1X + 2)) + (x - startX)] = result;
						}
					}
				}
			}
		}
	}
	catch (exception e)//IOException e)
	{
		//e->printStackTrace();
	}

	try
	{
		if (raf != nullptr)
		{
			raf->close();
		}
	}
	catch (exception e)//IOException e)
	{
		//e->printStackTrace();
	}


	if (isBlank == true)
	{
		return false;
	}


	for (int ty = 0; ty < (chunkSizeTiles1X + 2); ty++)
	{
		for (int tx = 0; tx < (chunkSizeTiles1X + 2); tx++)
		{
			int tile = layerChunkBuffer[(ty * (chunkSizeTiles1X + 2)) + tx];

			//skip black tiles on the ground layer
			if (groundLayer == true && tile == 1)
			{
				continue;
			}

			for (int py = 0; py < 8; py++)
			{
				for (int px = 0; px < 8; px++)
				{
					//skip all but one pixel of border
					if (tx == 0 && px < 7)
					{
						continue;
					}
					if (tx == chunkSizeTiles1X + 1 && px > 0)
					{
						continue;
					}
					if (ty == 0 && py < 7)
					{
						continue;
					}
					if (ty == chunkSizeTiles1X + 1 && py > 0)
					{
						continue;
					}


					int tilesetIndex = ((tile * 64) + (py * 8 + px)); //*2;

					int paletteIndex = tilesetIntArray[tilesetIndex];

					//					int byte1 = tileset[tilesetIndex] & 0xFF;
					//					int byte2 = tileset[tilesetIndex+1] & 0xFF;
					//
					//					int paletteIndex = (byte2<<8)+byte1;

					if (paletteIndex != 0)
					{
						int paletteR = paletteRGBByteArray[(paletteIndex * 3) + (0)] & 0xFF;
						int paletteG = paletteRGBByteArray[(paletteIndex * 3) + (1)] & 0xFF;
						int paletteB = paletteRGBByteArray[(paletteIndex * 3) + (2)] & 0xFF;

						BobColor* c = new BobColor(paletteR, paletteG, paletteB);

						if (shadowLayer) //shadow layer
						{
							int oldPixel = chunkImageBorder->getRGB(((tx - 1) * 8 + px) + 1, ((ty - 1) * 8 + py) + 1);
							BobColor* oldColor = new BobColor(oldPixel);// , true);

							int alpha = 255;
							if (oldColor->getRGB() == 0)
							{
								alpha = 150;
							}

							float shadowAlpha = 150.0f;
							int blendedRed = (int)((shadowAlpha / 255.0f) * paletteR + (1.0f - (shadowAlpha / 255.0f)) * oldColor->ri());
							int blendedGreen = (int)((shadowAlpha / 255.0f) * paletteG + (1.0f - (shadowAlpha / 255.0f)) * oldColor->gi());
							int blendedBlue = (int)((shadowAlpha / 255.0f) * paletteB + (1.0f - (shadowAlpha / 255.0f)) * oldColor->bi());

							c = new BobColor(blendedRed, blendedGreen, blendedBlue, alpha);
						}


						chunkImageBorder->setRGB(((tx - 1) * 8 + px) + 1, ((ty - 1) * 8 + py) + 1, c->getRGB());

						if (tx > 0 && tx < chunkSizeTiles1X + 1 && ty > 0 && ty < chunkSizeTiles1X + 1)
						{
							chunkImage->setRGB((tx - 1) * 8 + px, (ty - 1) * 8 + py, c->getRGB());
						}
					}
				}
			}
		}
	}

	return true;
}

void Map::createHQ2XTexturePNG_THREAD(int chunkX, int chunkY)
{ //=========================================================================================================================


	//Thread.currentThread().setPriority(Thread.MIN_PRIORITY);
	//Thread.yield();

	//load 1x png under and over into bitmap arrays


	int clear = (new BobColor(0, 0, 0, 0))->getRGB();
	//int black = (new Color(0, 0, 0, 255))->getRGB();


	int underChunkIndex = (chunksWidth * chunksHeight * 0) + ((chunkY * chunksWidth) + chunkX);
	int overChunkIndex = (chunksWidth * chunksHeight * 1) + ((chunkY * chunksWidth) + chunkX);

	BobFile* underLayerTextureFile = new BobFile(FileUtils::appDataPath + string("_") + getGroundLayerMD5() + "/" + string("1x_padded") + "/" + to_string(underChunkIndex));
	BobFile* overLayerTextureFile = new BobFile(FileUtils::appDataPath + string("_") + getGroundLayerMD5() + "/" + string("1x_padded") + "/" + to_string(overChunkIndex));


	//TODO: handle if 1x file doesn't exist, make it again from md5!

	//TODO: check 1, 1x, hq2x file for being over 0 bytes, the correct width and height... if it isn't, delete it and remake it
	//nice fix for broken cache files


	BufferedImage* bottom = nullptr;
	BufferedImage* top = nullptr;


	//handle 0 byte files!
	if (underLayerTextureFile->length() < 1) //it is actually a completely isEmpty image, it was all 0 tiles
	{
		bottom = new BufferedImage(chunkSizePixels1X + 2, chunkSizePixels1X + 2, BufferedImage::TYPE_INT_ARGB);


		//thought this would fix the hq2x grain glitch, but it was from hq2x being static.
		//dont need to initialize isEmpty graphics
		/*Graphics G = bottom.getGraphics();
		G.setColor(new Color(0,0,0,0));
		G.fillRect(0,0,bottom.getWidth(), bottom.getHeight());
		G.dispose();
		G = null;*/
	}
	else
	{
		try
		{
			bottom = FileUtils::readBufferedImageFromFile(underLayerTextureFile);
		}
		catch (exception e)//IOException e)
		{
			log.error(string("Cannot read PNG file: ") + underLayerTextureFile->getName() + string(" "));// +e->getMessage());
		}
	}


	if (overLayerTextureFile->length() < 1)
	{
		top = new BufferedImage(chunkSizePixels1X + 2, chunkSizePixels1X + 2, BufferedImage::TYPE_INT_ARGB);
		/*Graphics G = top.getGraphics();
		G.setColor(new Color(0,0,0,0));
		G.fillRect(0,0,top.getWidth(), top.getHeight());
		G.dispose();
		G = null;*/
	}
	else
	{
		try
		{
			top = FileUtils::readBufferedImageFromFile(overLayerTextureFile);
		}
		catch (exception e)//IOException e)
		{
			log.error(string("Cannot read PNG file: ") + overLayerTextureFile->getName() + string(" "));// +e->getMessage());
		}
	}


	//create bottom + top image

	BufferedImage* bottomAndTop = new BufferedImage(chunkSizePixels1X + 2, chunkSizePixels1X + 2, BufferedImage::TYPE_INT_ARGB);

	//draw bottom, then top into bottomAndTop

	//draw bottom into bottomAndTop
	for (int y = 0; y < bottom->getHeight(); y++)
	{
		for (int x = 0; x < bottom->getWidth(); x++)
		{
			bottomAndTop->setRGB(x, y, bottom->getRGB(x, y));
		}
	}

	//draw top into bottomAndTop
	for (int y = 0; y < top->getHeight(); y++)
	{
		for (int x = 0; x < top->getWidth(); x++)
		{
			if (top->getRGB(x, y) != clear)
			{
				bottomAndTop->setRGB(x, y, top->getRGB(x, y));
			}
		}
	}

	//----------------------
	//TOP LAYER
	//----------------------

	//hq2x bottom+top
	BufferedImage* hq2xBottomAndTop = (new HQ2X())->hq2x(bottomAndTop);
	//setHQ2XAlphaFromOriginal(hq2xBottomAndTop,bottomAndTop); //(shouldnt be transparent here)

	//dont need bottomandtop

	delete bottomAndTop;
	bottomAndTop = nullptr;

	BufferedImage* hq2xBottomAndTopCopy = new BufferedImage(hq2xBottomAndTop->getWidth(), hq2xBottomAndTop->getHeight(), BufferedImage::TYPE_INT_ARGB);
	for (int y = 0; y < hq2xBottomAndTop->getHeight(); y++)
	{
		for (int x = 0; x < hq2xBottomAndTop->getWidth(); x++)
		{
			//copy x,y into x-2,y-2
			hq2xBottomAndTopCopy->setRGB(x, y, hq2xBottomAndTop->getRGB(x, y));
		}
	}


	//Masking 1x top layer from HQ2X bottom+top
	//go through top layer
	//for each transparent pixel set 2x (x+xx y+yy) transparent on hq2x bottom+top
	for (int y = 0; y < top->getHeight(); y++)
	{
		for (int x = 0; x < top->getWidth(); x++)
		{
			//copy alpha pixels from top, including clear and transparent shadows
			//TODO: fix this in editor as well when outputting hq2x
			if (((top->getRGB(x, y) >> 24) & 0xff) < 255)
			{
				for (int xx = 0; xx < 2; xx++)
				{
					for (int yy = 0; yy < 2; yy++)
					{
						hq2xBottomAndTop->setRGB((x * 2) + xx, ((y * 2) + yy), top->getRGB(x, y));
					}
				}
			}


			//could do better antialiasing around edges here. since we're masking out the bottom layer, some of the edges on the top layer have gray pixels.
			//i could go through the top image, find clear pixels surrounded with black, and set the in-between pixel on the hq2x image with black alpha 127

			//this is kind of broken for negligible benefit, not worth working on at the moment

			/*if(top.getRGB(x, y)==clear)
			{
			   if(
			      (x<top.getWidth()-1&&x>0&&y<top.getHeight()-1&&y>0)
			      )
			   {
			      if(top.getRGB(x+1, y)!=clear&&top.getRGB(x, y-1)!=clear)//right up
			      {
			         hq2xBottomAndTop.setRGB((x*2)+1, ((y*2)+0), new Color(0,255,0,127).getRGB());
			         hq2xBottomAndTop.setRGB((x*2)+0, ((y*2)+0), new Color(0,255,0,127).getRGB());
			         hq2xBottomAndTop.setRGB((x*2)+1, ((y*2)+1), new Color(0,255,0,127).getRGB());
			      }
			   
			      if(top.getRGB(x+1, y)!=clear&&top.getRGB(x, y+1)!=clear)//right down
			      {
			         hq2xBottomAndTop.setRGB((x*2)+1, ((y*2)+1), new Color(0,255,0,127).getRGB());
			         hq2xBottomAndTop.setRGB((x*2)+0, ((y*2)+1), new Color(0,255,0,127).getRGB());
			         hq2xBottomAndTop.setRGB((x*2)+1, ((y*2)+0), new Color(0,255,0,127).getRGB());
			      }
			   
			      if(top.getRGB(x-1, y)!=clear&&top.getRGB(x, y-1)!=clear)//left up
			      {
			         hq2xBottomAndTop.setRGB((x*2)+0, ((y*2)+0), new Color(0,255,0,127).getRGB());
			         hq2xBottomAndTop.setRGB((x*2)+1, ((y*2)+0), new Color(0,255,0,127).getRGB());
			         hq2xBottomAndTop.setRGB((x*2)+0, ((y*2)+1), new Color(0,255,0,127).getRGB());
			      }
			   
			      if(top.getRGB(x-1, y)!=clear&&top.getRGB(x, y+1)!=clear)//left down
			      {
			         hq2xBottomAndTop.setRGB((x*2)+0, ((y*2)+1), new Color(0,255,0,127).getRGB());
			         hq2xBottomAndTop.setRGB((x*2)+0, ((y*2)+0), new Color(0,255,0,127).getRGB());
			         hq2xBottomAndTop.setRGB((x*2)+1, ((y*2)+1), new Color(0,255,0,127).getRGB());
			      }
			   }
			   
			}*/
		}
	}


	//could antialias black edges here. ****this algorithm doesn't really work because all the edges are already interpolated with the background color.
	//antialiasBufferedImage(hq2xBottomAndTop);

	//----------------------
	//output hq2x top layer fully
	//----------------------

	//Outputting full HQ2X top layer

	//make temp image size-4

	BufferedImage* temp = new BufferedImage(hq2xBottomAndTop->getWidth() - 4, hq2xBottomAndTop->getHeight() - 4, BufferedImage::TYPE_INT_ARGB);
	for (int y = 2; y < hq2xBottomAndTop->getHeight() - 2; y++)
	{
		for (int x = 2; x < hq2xBottomAndTop->getWidth() - 2; x++)
		{
			//copy x,y into x-2,y-2
			temp->setRGB(x - 2, y - 2, hq2xBottomAndTop->getRGB(x, y));
		}
	}

	//save temp as hq2x_top
	FileUtils::saveImage(FileUtils::appDataPath + string("_") + getGroundLayerMD5() + "/" + string("2x") + "/" + to_string(overChunkIndex), temp);

	//don't need temp
	delete temp;
	temp = nullptr;

	//dont need hq2xBottomAndTop
	delete hq2xBottomAndTop;
	hq2xBottomAndTop = nullptr;


	//----------------------
	//BOTTOM LAYER
	//----------------------

	//hq2x bottom+top again

	hq2xBottomAndTop = hq2xBottomAndTopCopy; //new HQ2X().HQ2X(bottomAndTop); //it is probably better to just copy the image above before i modify it


	//put back any transparent pixels from bottom (borders around map)
	setHQ2XAlphaFromOriginal(hq2xBottomAndTop, bottom);

	//hq2x bottom
	BufferedImage* hq2xBottom = (new HQ2X())->hq2x(bottom);


	//dont need bottom
	delete bottom;
	bottom = nullptr;


	//Masking HQ2X bottom layer into HQ2X bottom+top layer
	//go through top layer
	//for each NON-transparent pixel 2x (x+xx y+yy ) take pixel from hq2x bottom, copy into hq2x bottom_top
	for (int y = 0; y < top->getHeight(); y++)
	{
		for (int x = 0; x < top->getWidth(); x++)
		{
			if (top->getRGB(x, y) != clear)
			{
				for (int xx = 0; xx < 2; xx++)
				{
					for (int yy = 0; yy < 2; yy++)
					{
						hq2xBottomAndTop->setRGB((x * 2) + xx, ((y * 2) + yy), hq2xBottom->getRGB((x * 2) + xx, ((y * 2) + yy)));
					}
				}
			}
		}
	}


	//dont need top
	delete top;
	top = nullptr;

	//dont need hq2xBottom
	delete hq2xBottom;
	hq2xBottom = nullptr;


	//----------------------
	//output hq2x bottom layer full
	//----------------------

	temp = new BufferedImage(hq2xBottomAndTop->getWidth() - 4, hq2xBottomAndTop->getHeight() - 4, BufferedImage::TYPE_INT_ARGB);
	for (int y = 2; y < hq2xBottomAndTop->getHeight() - 2; y++)
	{
		for (int x = 2; x < hq2xBottomAndTop->getWidth() - 2; x++)
		{
			//copy x,y into x-2,y-2
			temp->setRGB(x - 2, y - 2, hq2xBottomAndTop->getRGB(x, y));
		}
	}

	//Outputting full HQ2X bottom layer
	//save as hq2x bottom
	FileUtils::saveImage(FileUtils::appDataPath + string("_") + getGroundLayerMD5() + "/" + string("2x") + "/" + to_string(underChunkIndex), temp);

	//don't need temp
	delete temp;
	temp = nullptr;

	//dont need hq2xBottomAndTop
	delete hq2xBottomAndTop;
	hq2xBottomAndTop = nullptr;

	delete hq2xBottomAndTopCopy;
	hq2xBottomAndTopCopy = nullptr;


	//DONE: set chunkTexture to hq2x chunk

	//need to do this in main thread, can't release textures in a secondary thread.
	//set a thing textureIsHQ2X, allHQ2XLoaded

	//Texture t = getChunkTexture(underChunkIndex);
	//setChunkTexture(underChunkIndex,null);
	//t.release();
	//t=null;


	//t = getChunkTexture(overChunkIndex);
	//setChunkTexture(overChunkIndex,null);
	//t.release();
	//t=null;


	//delete 1x pngs top and bottom
	underLayerTextureFile->deleteFile();
	overLayerTextureFile->deleteFile();

	delete underLayerTextureFile;
	underLayerTextureFile = nullptr;
	delete overLayerTextureFile;
	overLayerTextureFile = nullptr;
}

void Map::antialiasBufferedImage(BufferedImage* bufferedImage)
{ //===============================================================================================

	//go through hq2x image
	//if pixel is transparent, and the pixel right and down, down and left, left and up, or up and right are black, this one is black

	//have to make a copy otherwise the algorithm becomes recursive
	BufferedImage* copy = new BufferedImage(bufferedImage->getWidth(), bufferedImage->getHeight(), BufferedImage::TYPE_INT_ARGB);
	for (int y = 0; y < bufferedImage->getHeight(); y++)
	{
		for (int x = 0; x < bufferedImage->getWidth(); x++)
		{
			copy->setRGB(x, y, bufferedImage->getRGB(x, y));
		}
	}

	int clear = (new BobColor(0, 0, 0, 0))->getRGB();

	for (int y = 0; y < bufferedImage->getHeight(); y++)
	{
		for (int x = 0; x < bufferedImage->getWidth(); x++)
		{
			if (copy->getRGB(x, y) == clear)
			{
				int black = 0;

				//check right and down
				if (x + 1 < bufferedImage->getWidth() && y + 1 < bufferedImage->getHeight())
				{
					if (copy->getRGB(x + 1, y) != clear && copy->getRGB(x, y + 1) != clear)
					{
						black = 1;
					}
				}

				//check right and up
				if (x + 1 < bufferedImage->getWidth() && y - 1 >= 0)
				{
					if (copy->getRGB(x + 1, y) != clear && copy->getRGB(x, y - 1) != clear)
					{
						black = 1;
					}
				}


				//check left and down
				if (x - 1 >= 0 && y + 1 < bufferedImage->getHeight())
				{
					if (copy->getRGB(x - 1, y) != clear && copy->getRGB(x, y + 1) != clear)
					{
						black = 1;
					}
				}

				//check left and up
				if (x - 1 >= 0 && y - 1 >= 0)
				{
					if (copy->getRGB(x - 1, y) != clear && copy->getRGB(x, y - 1) != clear)
					{
						black = 1;
					}
				}

				if (black == 1)
				{
					bufferedImage->setRGB(x, y, (new BobColor(0, 0, 0, 127))->getRGB());
				}
			}
		}
	}
}

void Map::setHQ2XAlphaFromOriginal(BufferedImage* hq2xBufferedImage, BufferedImage* bufferedImage)
{ //===============================================================================================
	//now go through original image again. take each transparent pixel and set the hq2x one with it at 2x
	for (int y = 0; y < bufferedImage->getHeight(); y++)
	{
		for (int x = 0; x < bufferedImage->getWidth(); x++)
		{
			if (bufferedImage->getRGB(x, y) == 0)
			{
				for (int xx = 0; xx < 2; xx++)
				{
					for (int yy = 0; yy < 2; yy++)
					{
						hq2xBufferedImage->setRGB((x * 2) + xx, ((y * 2) + yy), (new BobColor(0, 0, 0, 0))->getRGB());
					}
				}
			}
		}
	}
}

void Map::addEntitiesAndCharactersFromCurrentStateToActiveEntityList()
{ //=========================================================================================================================


	for (int n = 0; n < (int)currentState->entityList.size(); n++)
	{
		Entity* ms = currentState->entityList.get(n);
		activeEntityList.add(ms);
	}

	for (int n = 0; n < (int)currentState->characterList.size(); n++)
	{
		Character* ms = currentState->characterList.get(n);
		activeEntityList.add(ms);
	}

	if (getPlayer() != nullptr && getClientGameEngine()->playerExistsInMap)
	{
		activeEntityList.add(getPlayer());
	}
}

void Map::clearActiveEntityList()
{ //=========================================================================================================================

	//have to release unique textures on random entities
	for (int i = 0; i < activeEntityList.size(); i++)
	{
		Entity* e = activeEntityList.get(i);
		if ((dynamic_cast<RandomCharacter*>(e) != NULL))
		{
			RandomCharacter* r = static_cast<RandomCharacter*>(e);
			if (r->uniqueTexture != nullptr)
			{
				r->uniqueTexture->release();
				r->uniqueTexture = nullptr;
			}
		}
	}

	activeEntityList.clear();
	//if(getPlayer()!=null)entityList.add(getPlayer());
	//entityList.add(getCameraman());
}

bool Map::isAnyoneOverlappingXY(float x, float y)
{ //=========================================================================================================================
	for (int i = 0; i < activeEntityList.size(); i++)
	{
		//find any characters
		Entity* e = activeEntityList.get(i);

		if (x > e->getLeft() && x < e->getRight() && y > e->getTop() && y < e->getBottom())
		{
			return true;
		}
	}

	return false;
}

bool Map::isAnyoneOverlappingXYXY(float x, float y, float x2, float y2)
{ //=========================================================================================================================
	for (int i = 0; i < activeEntityList.size(); i++)
	{
		//find any characters
		Entity* e = activeEntityList.get(i);

		if (x < e->getRight() && x2 > e->getLeft() && y < e->getBottom() && y2 > e->getTop())
		{
			return true;
		}
	}

	return false;
}

bool Map::isAnyRandomCharacterTryingToGoToXY(float x, float y)
{ //=========================================================================================================================
	for (int i = 0; i < activeEntityList.size(); i++)
	{
		//find any characters
		Entity* e = activeEntityList.get(i);

		if ((dynamic_cast<RandomCharacter*>(e) != NULL))
		{
			RandomCharacter* c = static_cast<RandomCharacter*>(e);

			if (x == c->targetX && y == c->targetY)
			{
				return true;
			}
		}
	}

	return false;
}

int* Map::findOpenSpaceInArea(Area* a, int w, int h)
{ //=========================================================================================================================

	ArrayList<int*>* coords = new ArrayList<int*>();

	for (int x = 1; x < a->getWidth() / 8; x++)
	{
		for (int y = 1; y < a->getHeight() / 8; y++)
		{
			int* xy = new int[2];
			xy[0] = x;
			xy[1] = y;
			coords->add(xy);
		}
	}

	while (coords->size() > 0)
	{
		int i = Math::randLessThan(coords->size());
		int* xy = coords->get(i);
		int x = xy[0];
		int y = xy[1];

		if (isAnyoneOverlappingXYXY((float)a->getX() + (x * 8 - w / 2), (float)a->getY() + (y * 8 - h / 2), (float)a->getX() + (x * 8 + w / 2), (float)a->getY() + (y * 8 + h / 2)) == false && isAnyRandomCharacterTryingToGoToXY(a->getX() + a->getWidth() / 2, a->getY() + a->getHeight() / 2) == false)
		{
			//TODO: could also check all the other random characters targetX and targetY to make sure nobody is TRYING to go here


			int* finalcoords = new int[2];
			finalcoords[0] = (int)(a->getX() + x * 8);
			finalcoords[1] = (int)(a->getY() + y * 8);

			return finalcoords;
		}
		else
		{
			coords->removeAt(i);
		}
	}
	return nullptr;
}

bool Map::isAnyCharacterTouchingArea(Area* a)
{ //=========================================================================================================================

	//go through all entities, if somebody is standing here, don't go there.

	if (a != nullptr) //DEBUG HERE
	{
		for (int i = 0; i < activeEntityList.size(); i++)
		{
			Entity* e = activeEntityList.get(i);

			if (
				(
					(
						(
							(dynamic_cast<Character*>(e) != NULL)
							||
							(dynamic_cast<RandomCharacter*>(e) != NULL)
						)
					)
					||
					(dynamic_cast<Player*>(e) != NULL)
				)
				&&
				a->isEntityHitBoxTouchingMyBoundary(e)
			)
			//&&
			//m.getNonWalkable==true
			{
				return true;
			}
		}
	}

	return false;
}

bool Map::isAnyEntityTouchingArea(Area* a)
{ //=========================================================================================================================

	//go through all entities, if somebody is standing here, don't go there.

	if (a != nullptr) //DEBUG HERE
	{
		for (int i = 0; i < activeEntityList.size(); i++)
		{
			Entity* e = activeEntityList.get(i);

			if (a->isEntityHitBoxTouchingMyBoundary(e))
			{
				return true;
			}
		}
	}

	return false;
}

ArrayList<Entity*>* Map::getAllEntitiesTouchingArea(Area* a)
{ //=========================================================================================================================

	ArrayList<Entity*>* entitiesInArea = new ArrayList<Entity*>();


	for (int i = 0; i < activeEntityList.size(); i++)
	{
		Entity* e = activeEntityList.get(i);

		if (a->isEntityHitBoxTouchingMyBoundary(e))
		{
			entitiesInArea->add(e);
		}
	}


	return entitiesInArea;
}

ArrayList<Entity*>* Map::getAllEntitiesPlayerIsTouching()
{ //=========================================================================================================================

	ArrayList<Entity*>* entitiesTouching = new ArrayList<Entity*>();


	for (int i = 0; i < activeEntityList.size(); i++)
	{
		Entity* e = activeEntityList.get(i);

		if (getPlayer()->isEntityHitBoxTouchingMyHitBox(e))
		{
			entitiesTouching->add(e);
		}
	}


	return entitiesTouching;
}

bool Map::isAnyoneTryingToGoToArea(Area* a)
{ //=========================================================================================================================
	if (a != nullptr) //DEBUG HERE
	{
		for (int i = 0; i < activeEntityList.size(); i++)
		{
			if (activeEntityList.get(i)->currentAreaTYPEIDTarget == a->getName())
			{
				return true;
			}
		}
	}
	return false;
}

bool Map::isAnyEntityUsingSpriteAsset(Sprite* s)
{ //=========================================================================================================================

	for (int i = 0; i < activeEntityList.size(); i++)
	{
		if (activeEntityList.get(i)->sprite == s)
		{
			return true;
		}
	}


	return false;
}

ArrayList<Entity*>* Map::getAllEntitiesUsingSpriteAsset(Sprite* s)
{ //=========================================================================================================================

	ArrayList<Entity*>* entitiesUsingSprite = new ArrayList<Entity*>();

	for (int i = 0; i < activeEntityList.size(); i++)
	{
		Entity* e = activeEntityList.get(i);

		if (e->sprite == s)
		{
			entitiesUsingSprite->add(e);
		}
	}


	return entitiesUsingSprite;
}

Entity* Map::createEntity(Map* map, const string& spriteName, Sprite* spriteAsset, float mapX, float mapY)
{ //=========================================================================================================================


	EntityData* entityData = new EntityData(-1, spriteName, spriteAsset->getName(), (int)(mapX / 2), (int)(mapY / 2));

	Entity* e = new Entity(getEngine(), entityData);

	getCurrentMap()->currentState->entityList.add(e);
	getCurrentMap()->currentState->entityByNameHashtable.put(e->getName(),e);

	return e;
}

Entity* Map::createEntityFeetAtXY(Map* map, const string& spriteName, Sprite* sprite, float mapX, float mapY)
{ //=========================================================================================================================

	// use hitbox center instead of arbitrary offset
	SpriteAnimationSequence* a = sprite->getFirstAnimation();
	int hitBoxYCenter = (a->hitBoxFromTopPixels1X * 2) + (((sprite->getScreenHeight() - (a->hitBoxFromTopPixels1X * 2)) - (a->hitBoxFromBottomPixels1X * 2)) / 2);

	return createEntity(map, spriteName, sprite, mapX - (sprite->getScreenWidth() / 2), mapY - (hitBoxYCenter));
}

Entity* Map::createEntityIfWithinRangeElseDelete_MUST_USE_RETURNVAL(Map* map, Entity* e, const string& spriteName, Sprite* sprite, float mapX, float mapY, int amt)
{ //=========================================================================================================================

	if (map->isXYWithinScreenByAmt(mapX + sprite->getScreenWidth() / 2, mapY + sprite->getScreenHeight() / 2, amt) == true)
	{
		if (e == nullptr)
		{
			return createEntity(map, spriteName, sprite, mapX, mapY);
		}
		else
		{
			return e;
		}
	}
	else
	{
		if (e != nullptr)
		{
			e->deleteFromMapEntityListAndReleaseTexture();
			delete e;
			e = nullptr;
		}
		return nullptr;
	}
}

Entity* Map::createEntityAtArea(Map* map, const string& spriteName, Sprite* spriteAsset, Area* a)
{ //=========================================================================================================================
	float x = a->middleX();
	float y = a->middleY();

	return createEntityFeetAtXY(map, spriteName, spriteAsset, x, y);
}

MapData* Map::getData()
{
	return data;
}

int Map::getID()
{
	return data->getID();
}

string Map::getName()
{
	return data->getName();
}

string Map::getMapNote()
{
	return data->getMapNote();
}

int Map::getWidthTiles1X()
{
	return data->getWidthTiles1X();
}

int Map::getHeightTiles1X()
{
	return data->getHeightTiles1X();
}

int Map::getWidthPixelsHQ()
{
	return data->getWidthPixelsHQ();
}

int Map::getHeightPixelsHQ()
{
	return data->getHeightPixelsHQ();
}

int Map::getMaxRandoms()
{
	return data->getMaxRandoms();
}

bool Map::getIsOutside()
{
	return data->getIsOutside();
}

string Map::getTYPEIDString()
{
	return data->getTYPEIDString();
}

string Map::getGroundLayerMD5()
{
	return getData()->getGroundLayerMD5();
}

string Map::getGroundObjectsMD5()
{
	return getData()->getGroundObjectsMD5();
}

string Map::getGroundShadowMD5()
{
	return getData()->getGroundShadowMD5();
}

string Map::getObjectsMD5()
{
	return getData()->getObjectsMD5();
}

string Map::getObjects2MD5()
{
	return getData()->getObjects2MD5();
}

string Map::getObjectShadowMD5()
{
	return getData()->getObjectShadowMD5();
}

string Map::getAboveMD5()
{
	return getData()->getAboveMD5();
}

string Map::getAbove2MD5()
{
	return getData()->getAbove2MD5();
}

string Map::getSpriteShadowMD5()
{
	return getData()->getSpriteShadowMD5();
}

string Map::getGroundShaderMD5()
{
	return getData()->getGroundShaderMD5();
}

string Map::getCameraBoundsMD5()
{
	return getData()->getCameraBoundsMD5();
}

string Map::getHitBoundsMD5()
{
	return getData()->getHitBoundsMD5();
}

string Map::getLightMaskMD5()
{
	return getData()->getLightMaskMD5();
}

string Map::getPaletteMD5()
{
	return getData()->getPaletteMD5();
}

string Map::getTilesMD5()
{
	return getData()->getTilesMD5();
}

void Map::setGroundLayerMD5(const string& s)
{
	getData()->setGroundLayerMD5(s);
}

void Map::setGroundObjectsMD5(const string& s)
{
	getData()->setGroundObjectsMD5(s);
}

void Map::setGroundShadowMD5(const string& s)
{
	getData()->setGroundShadowMD5(s);
}

void Map::setObjectsMD5(const string& s)
{
	getData()->setObjectsMD5(s);
}

void Map::setObjects2MD5(const string& s)
{
	getData()->setObjects2MD5(s);
}

void Map::setObjectShadowMD5(const string& s)
{
	getData()->setObjectShadowMD5(s);
}

void Map::setAboveMD5(const string& s)
{
	getData()->setAboveMD5(s);
}

void Map::setAbove2MD5(const string& s)
{
	getData()->setAbove2MD5(s);
}

void Map::setSpriteShadowMD5(const string& s)
{
	getData()->setSpriteShadowMD5(s);
}

void Map::setGroundShaderMD5(const string& s)
{
	getData()->setGroundShaderMD5(s);
}

void Map::setCameraBoundsMD5(const string& s)
{
	getData()->setCameraBoundsMD5(s);
}

void Map::setHitBoundsMD5(const string& s)
{
	getData()->setHitBoundsMD5(s);
}

void Map::setLightMaskMD5(const string& s)
{
	getData()->setLightMaskMD5(s);
}

void Map::setPaletteMD5(const string& s)
{
	getData()->setPaletteMD5(s);
}

void Map::setTilesMD5(const string& s)
{
	getData()->setTilesMD5(s);
}

