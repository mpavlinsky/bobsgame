#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger MapManager::log = Logger("MapManager");


bool MapManager::useThreads = false;
bool MapManager::generateHQ2XChunks = false;
bool MapManager::loadTexturesOnDemand = true;

MapManager::MapManager(Engine* g)
{ //=========================================================================================================================
	this->e = g;
	//mapByNameHashMap = new HashMap<string, Map*>();
	//mapByIDHashMap = new HashMap<int, Map*>();
	//lightTextureHashMap = new HashMap<string, BobTexture*>();
	//lightTextureFileExistsHashtable = new HashMap<string, BobBool*>();
}


MapManager::~MapManager()
{//=========================================================================================================================

	//Iterator<Map> maps = Game().mapByNameHashMap.values().iterator();


	{
		//while(maps.hasNext())

		try
		{
			//Map m = maps.next();


			if (MapManager::useThreads)
			{
				//            if (Map::generatePNGExecutorService != nullptr)
				//            {
				//               Map::generatePNGExecutorService->shutdownNow(); //.awaitTermination(30, TimeUnit.SECONDS);
				//            }
				//            if (Map::generateLightPNGExecutorService != nullptr)
				//            {
				//               Map::generateLightPNGExecutorService->shutdownNow(); //.awaitTermination(30, TimeUnit.SECONDS);
				//            }
				//            if (Sprite::generatePNGExecutorService != nullptr)
				//            {
				//               Sprite::generatePNGExecutorService->shutdownNow(); //.awaitTermination(30, TimeUnit.SECONDS);
				//            }
				//if(m->generateHQ2XPNGExecutorService!=null)m->generateHQ2XPNGExecutorService.shutdownNow();//awaitTermination(30, TimeUnit.SECONDS);
			}
		}
		catch (exception e)
		{
			//e.printStackTrace();
		}
	}

}


void MapManager::update()
{ //=========================================================================================================================
	if (currentMap != nullptr)
	{
		//should setscreen for entities AFTER map adjusts itself
		fadeOutAndReleaseLastMap();

		currentMap->update();

		//these can be in any order, since they only rely on map_cam_xy which is set in updateLogic
		currentMap->updateLastKnownScreenXYBasedOnCamera(); //this is 0-map_cam_xy
	}
}



void MapManager::render()
{ //=========================================================================================================================

	if (currentMap == nullptr)
	{
		return;
	}


	if (dynamic_cast<BGClientEngine*>(getEngine()) != nullptr)//GLUtils::useFBO && 
	{
		GLUtils::bindFBO(GLUtils::postColorFilterFBO); //set the framebuffer object to the MAIN FBO

		GLUtils::drawIntoFBOAttachment(0); //set which framebuffer object to draw into (whatever buffer is set with glBindFramebufferEXT)

		//clear the main FBO
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//TODO: set all these to 0,0,0,1
		glClear(GL_COLOR_BUFFER_BIT);

		//DONE: need to resize the fbo texture when the screen size changes

		//DONE: also need to send the fbo size into the lights shader, it is currently hardcoded


		renderLastMap();

		currentMap->render(RenderOrder::GROUND);
		currentMap->renderEntities(RenderOrder::GROUND);
		getCaptionManager()->render(RenderOrder::GROUND);


		GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		getCinematicsManager()->render(RenderOrder::GROUND);
		GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//GLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE);
		currentMap->render(RenderOrder::ABOVE);
		currentMap->renderEntities(RenderOrder::ABOVE);
		currentMap->renderEntities(RenderOrder::ABOVE_TOP); //birds? //TODO should have something OVER lights as well!
		//GLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		//if(!Keyboard.isKeyDown(Keyboard.KEY_COMMA))
		GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		getCinematicsManager()->render(RenderOrder::ABOVE); //screen overlay under lights
		//if(!Keyboard.isKeyDown(Keyboard.KEY_PERIOD))
		GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//getGameEngine()->stadiumScreen->render();

		//			if(Keyboard.isKeyDown(Keyboard.KEY_LBRACKET))GLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		//			else
		//			GLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (GLUtils::useShaders)
		{
			//DONE: this is reading from the FBO texture while writing to the FBO which may be undefined.
			//i may need to use "ping pong" rendering:
			//attach to TEMP FBO
			//draw mainFBO texture into TEMP FBO
			//attach to mainFBO
			//bind TEMP FBO texture into shader
			//draw as many lights as i can that don't overlap, screen blended with the TEMP FBO texture
			//repeat.
			//i may also be able to keep the FBO as one object and just switch textures

			bool flip = true;

			for (int i = 0; i < (int)currentMap->sortedLightsLayers.size(); i++)
			{
				ArrayList<Light*>* thisLayer = currentMap->sortedLightsLayers.get(i);


				if (flip == true)
				{
					//flip FBO attachment buffers


					//switch to LIGHTS buffer attachment
					GLUtils::drawIntoFBOAttachment(1); //draws into postColorFilterFBO_Texture_Attachment1_PreLighting
					glClear(GL_COLOR_BUFFER_BIT);

					//draw the main FBO texture into the LIGHTS buffer attachment
					GLUtils::drawTexture(GLUtils::postColorFilterFBO_Texture_Attachment0, 0, 1, 1, 0, 0, (float)(GLUtils::getViewportWidth()), 0, (float)(GLUtils::getViewportHeight()), 1.0f, GLUtils::FILTER_FBO_NEAREST_NO_MIPMAPPING);

					//switch to MAIN buffer attachment
					GLUtils::drawIntoFBOAttachment(0); //draws into postColorFilterFBO_Texture_Attachment0
				}

				GLUtils::useShader(GLUtils::lightShader);

				//set the LIGHTS FBO texture to texture 0, we drew the main FBO (maps and sprites) into it and we are going to use it to blend
				glActiveTexture(GL_TEXTURE0);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, GLUtils::postColorFilterFBO_Texture_Attachment1_PreLighting);


				glActiveTexture(GL_TEXTURE1); //switch to texture 1, we are going to bind the light textures to this when we draw them.
				glEnable(GL_TEXTURE_2D);
				//each light texture will be bound to texture1 as they are drawn


				//then we set the shader vars, we will blend texture0 with texture1
				GLUtils::setShaderVar1i(GLUtils::lightShader, (char*)"Tex0", 0);//this is the full map and sprites
				GLUtils::setShaderVar1i(GLUtils::lightShader, (char*)"Tex1", 1);//this is each light
				GLUtils::setShaderVar1f(GLUtils::lightShader, (char*)"width", (float)GLUtils::getViewportWidth());
				GLUtils::setShaderVar1f(GLUtils::lightShader, (char*)"height", (float)GLUtils::getViewportHeight());


				flip = false;

				//now we render the lights, we bind the light texture to texture unit 1 and draw them into the main FBO,
				//blending with texture unit 1 which is the lights FBO with maps and sprites drawn in it.

				//we will draw/blend all the lights that don't overlap into the mainFBO texture
				//then we will draw that blended layer back to the lightsFBO so we can blend another layer on top of it without ugly blending artifacts.
				//this is "ping pong" rendering technique.
				for (int n = 0; n < thisLayer->size(); n++)
				{
					Light* l = thisLayer->get(n);
					if (l->getName().find("mover") != string::npos == false) //skip mover lights, draw them afterwards.
					{
						if (l->renderLight() == true)
						{
							flip = true;
						}
					}
				}

				//disable texture2D on texture unit 1
				glActiveTexture(GL_TEXTURE1);
				glDisable(GL_TEXTURE_2D);

				//switch back to texture unit 0
				glActiveTexture(GL_TEXTURE0);
				

				GLUtils::useShader(0);
			}


			if (currentMap != nullptr)
			{
				if (currentMap->currentState != nullptr)
				{
					//draw mover lights after finished drawing blended lights.
					for (int i = 0; i < (int)currentMap->currentState->lightList.size(); i++)
					{
						Light* l = currentMap->currentState->lightList.get(i);
						if (l->getName().find("mover") != string::npos)
						{
							l->renderLight();
						}
					}
				}
			}


			GLUtils::bindFBO(0); //set the framebuffer back to the screen buffer
			GLUtils::setRealWindowViewport();
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//TODO: set all these to 0,0,0,1


			setEffectsShaderEffects();

			setTextureRotation();


			//draw the framebuffer with the lights drawn into it into the screen buffer
			//if(!Keyboard.isKeyDown(Keyboard.KEY_SLASH))
			GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); //this fixes the small shadow problems, and also makes the doorknob glow brighter.
			GLUtils::drawTexture(GLUtils::postColorFilterFBO_Texture_Attachment0, 0, 1, 1, 0, 0, (float)(GLUtils::getRealWindowWidth()), 0, (float)(GLUtils::getRealWindowHeight()), 1.0f, GLUtils::FILTER_FBO_NEAREST_NO_MIPMAPPING);
			GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


			//set back to normal rendering
			//if(useColorShader)
			GLUtils::useShader(0);
		}
		else //not using shaders
		{
			GLUtils::bindFBO(0); //set the framebuffer back to the screen buffer
			GLUtils::setRealWindowViewport();
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//TODO: set all these to 0,0,0,1

			//draw mainFBO (which contains all the map layers drawn into it) to the screen buffer
			GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			GLUtils::drawTexture(GLUtils::postColorFilterFBO_Texture_Attachment0, 0, 1, 1, 0, 0, (float)(GLUtils::getRealWindowWidth()), 0, (float)(GLUtils::getRealWindowHeight()), 1.0f, GLUtils::FILTER_FBO_NEAREST_NO_MIPMAPPING);
			GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//set the framebuffer object back to mainFBO
			GLUtils::bindFBO(GLUtils::postColorFilterFBO); //set the framebuffer object to the MAIN FBO
			//clear the lights FBO
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//TODO: set all these to 0,0,0,1
			glClear(GL_COLOR_BUFFER_BIT);

			//draw the lights into mainFBO
			currentMap->renderAllLightsUnsorted();

			//set the framebuffer back to the screen buffer
			GLUtils::bindFBO(0);
			GLUtils::setRealWindowViewport();

			setFBOEffects();
			setTextureRotation();

			//draw mainFBO (which now contains lights) into the screen buffer
			GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			GLUtils::drawTexture(GLUtils::postColorFilterFBO_Texture_Attachment0, 0, 1, 1, 0, 0, (float)(GLUtils::getRealWindowWidth()), 0, (float)(GLUtils::getRealWindowHeight()), 1.0f, GLUtils::FILTER_FBO_NEAREST_NO_MIPMAPPING);
			GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
	}
	else //not using FBO
	{
		setNonFBOEffects();
		setTextureRotation();

		renderLastMap();


		currentMap->render(RenderOrder::GROUND);
		currentMap->renderEntities(RenderOrder::GROUND);
		getCinematicsManager()->render(RenderOrder::GROUND);
		getCaptionManager()->render(RenderOrder::GROUND);
		currentMap->render(RenderOrder::ABOVE);
		currentMap->renderEntities(RenderOrder::ABOVE);
		currentMap->renderEntities(RenderOrder::ABOVE_TOP);
		getCinematicsManager()->render(RenderOrder::ABOVE);

		//getGameEngine()->stadiumScreen::render();


		currentMap->renderAllLightsUnsorted();
	}


	//mapManager.currentMap->drawMiniMap();
}

void MapManager::renderLastMap()
{ //=========================================================================================================================

	if (lastMap != nullptr)
	{
		lastMap->render(RenderOrder::GROUND, true);
		lastMap->renderEntities(RenderOrder::GROUND);


		//			for(int i=0;i<lastMap.doorList.size();i++)
		//			{
		//				Door d = lastMap.doorList.get(i);
		//
		//				{
		//					if(d!=doorEntered)
		//					{
		//						d.render(lastMap.alpha);
		//					}
		//				}
		//
		//			}

		lastMap->render(RenderOrder::ABOVE, true);
		lastMap->renderEntities(RenderOrder::ABOVE);
		lastMap->renderEntities(RenderOrder::ABOVE_TOP);
	}
}

void MapManager::renderEntities(RenderOrder layer)
{ //=========================================================================================================================

	if (currentMap != nullptr)
	{
		currentMap->renderEntities(layer);
	}
}

void MapManager::setFBOEffects()
{ //=========================================================================================================================

	//TODO: hacks for stuff like grayscale, etc. without using shaders.
}

void MapManager::setNonFBOEffects()
{ //=========================================================================================================================
	//TODO: figure out what doesnt have FBO support. maybe use PBO instead??
}

void MapManager::setEffectsShaderEffects()
{ //=========================================================================================================================
	bool useColorShader = false; //TODO: optimise this, it is too slow for release.
	//maybe use screen filters instead or overlays or something, there has got to be a better way.
	//maybe there is a gl function for making textures grayscale
	//also there were slick/lwjgl/?? utilities for setting things like hue


	//TODO: have cinematic stuff control this.

	if (useColorShader)
	{
		GLUtils::useShader(GLUtils::colorShader);

		GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameHue", hue);
		GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameSaturation", saturation);
		GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameBrightness", brightness);
		GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameContrast", contrast);
		GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameGamma", gamma);
		if (grayscale == true)
		{
			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameSaturation", 0.0f);
		}
		GLUtils::setShaderVar1i(GLUtils::colorShader, (char*)"Tex0", 0);
	}
}

void MapManager::setTextureRotation()
{ //=========================================================================================================================
	if (drawAngle != 0.0f)
	{
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		glTranslated(0.5f, 0.5f, 0.0f);
		glRotated(drawAngle, 0.0f, 0.0f, 1.0f);
		glTranslated(-0.5f, -0.5f, 0.0f);
		glMatrixMode(GL_MODELVIEW);
	}
}

void MapManager::rotateMap(int rotateDegrees)
{ //=========================================================================================================================
	drawAngle = rotateDegrees / 360.0f;
}

void MapManager::renderDebug()
{ //=========================================================================================================================

	//org.newdawn.slick.Color.white.bind();
	//glEnable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_2D);

	if (getEngine()->debugLayerEnabled == true)
	{
		currentMap->renderChunkBoxes();
		currentMap->renderHitLayer();
		currentMap->renderLightBoxes();

		currentMap->renderEntities(RenderOrder::SPRITE_DEBUG_OUTLINES); //-1 = debug boxes
		getSpriteManager()->renderScreenSprites(RenderOrder::SPRITE_DEBUG_OUTLINES); //-1 = debug boxes
		currentMap->renderAreaDebugBoxes();
		currentMap->renderWarpAreaDebugBoxes();


		//org.newdawn.slick.Color.white.bind();

		//debug captions
		//SlickCallable.leaveSafeBlock();//weird slick texture errors if i dont do this
		{
			currentMap->renderAreaDebugInfo();
			currentMap->renderWarpAreaDebugInfo();
			currentMap->renderEntities(RenderOrder::SPRITE_DEBUG_INFO); //-2 = debug info
			getSpriteManager()->renderScreenSprites(RenderOrder::SPRITE_DEBUG_INFO); //-2 = debug info
		}
		//SlickCallable.enterSafeBlock();
	}
}

bool MapManager::isDayTime()
{ //=========================================================================================================================

	//TODO: hook these up to clock

	return true;
}

bool MapManager::isNightTime()
{ //=========================================================================================================================
	//TODO
	return false;
}

bool MapManager::isRaining()
{ //=========================================================================================================================
	// TODO
	return false;
}

bool MapManager::isSnowing()
{ //=========================================================================================================================
	// TODO
	return false;
}

bool MapManager::isWindy()
{ //=========================================================================================================================
	// TODO
	return false;
}

bool MapManager::isFoggy()
{ //=========================================================================================================================
	// TODO
	return false;
}

float MapManager::lastMapCameraOffsetX = 0;
float MapManager::lastMapCameraOffsetY = 0;
float MapManager::lastMapScreenX = 0;
float MapManager::lastMapScreenY = 0;

void MapManager::fadeOutAndReleaseLastMap()
{ //=========================================================================================================================
	if (lastMap != nullptr)
	{
		if (lastMap->generatingAreaNotification != nullptr)
		{
			lastMap->generatingAreaNotification = lastMap->generatingAreaNotification->fadeOutAndDelete();
		}

		lastMap->lastKnownScreenX = lastMapScreenX + lastMapCameraOffsetX - getCameraman()->getX();
		lastMap->lastKnownScreenY = lastMapScreenY + lastMapCameraOffsetY - getCameraman()->getY();

		if (currentMap->alpha == 1.0f) //when current map is completely opaque
		{
			lastMap->fadeOut();

			if (lastMap->alpha == 0.0f)
			{
				lastMap->clearActiveEntityList();
				lastMap->releaseAllTextures(); //TODO: this is what's causing the blip going from outside to inside i bet. test this!
				//TODO: could also try keeping the outside textures in memory if they will fit.
				lastMap = nullptr;
			}
		}
	}
}

void MapManager::setTransitionOffsets()
{ //=========================================================================================================================


	float cameraOffsetX = 0;
	float cameraOffsetY = 0;

	if (doorEntered != nullptr)
	{
		//get camera offset to lastDoor+height
		cameraOffsetX = (doorEntered->getX() + doorEntered->getHitBoxFromLeft()) - getCameraman()->getX();
		cameraOffsetY = (doorEntered->getY() + doorEntered->getHitBoxFromTop()) - getCameraman()->getY();
	}

	if (warpEntered != nullptr)
	{
		//get camera offset to lastDoor+height
		cameraOffsetX = (warpEntered->getX()) - getCameraman()->getX();
		cameraOffsetY = (warpEntered->getY()) - getCameraman()->getY();
	}


	if (doorExited != nullptr)
	{
		//fade in door
		//doorExited.alpha=0.0f; //TODO: notice that i disabled this, it looks nicer to have the door stay opaque now with animations.

		getCameraman()->setX((doorExited->getX() + doorExited->getHitBoxFromLeft()) - cameraOffsetX);
		getCameraman()->setY((doorExited->getY() + doorExited->getHitBoxFromTop()) - cameraOffsetY);
	}
	else
	{
		if (warpExited != nullptr)
		{
			getCameraman()->setX((warpExited->getX()) - cameraOffsetX);
			getCameraman()->setY((warpExited->getY()) - cameraOffsetY);
		}
		else
		{
			getCameraman()->setXYToTarget();
		}
	}

	doorExited = nullptr;
	doorEntered = nullptr;
	warpEntered = nullptr;
	warpExited = nullptr;

	if (lastMap != nullptr)
	{
		//so the last map can track along the current map as the camera normalizes
		lastMapScreenX = lastMap->lastKnownScreenX;
		lastMapScreenY = lastMap->lastKnownScreenY;
	}

	lastMapCameraOffsetX = getCameraman()->getX();
	lastMapCameraOffsetY = getCameraman()->getY();
}

void MapManager::changeMap(const string& mapName, int mapXPixelsHQ, int mapYPixelsHQ)
{ //=========================================================================================================================
	changeMap(mapName, mapXPixelsHQ, mapYPixelsHQ, true);
}

void MapManager::changeMap(const string& mapName, int mapXPixelsHQ, int mapYPixelsHQ, bool updateGameSave)
{ //=========================================================================================================================

	for (int i = 0; i < 1; i++)
	{
		//System.runFinalization();
		//System.gc();
	}

	if (currentMap != nullptr)
	{
		//currentMap->unload();//this is exported by tools, lights, areas, entities are unloaded here per-map in overridden function.

		getEventManager()->unloadCurrentMapEvents(); //this just clears the event queue and resets the execution order of event commands.
	}

	lastMap = currentMap;


	Map* m = getMapByNameBlockUntilLoaded(mapName);
	if (m == nullptr)
	{
		log.error(string("Could not load map: ") + mapName);
		return;
	}

	currentMap = m;
	currentMap->alpha = 0.0f;
	currentMap->currentState = nullptr;
	currentMap->addedEntitiesAndCharactersFromCurrentStateToActiveEntityList = false;
	currentMap->eventsAllLoadedFromServer = false;

	setTransitionOffsets();


	if (dynamic_cast<BGClientEngine*>(getEngine()) != nullptr)
	{
		if (lastMap != nullptr)
		{
			lastMap->activeEntityList.remove(getPlayer()); //DONE: each map should just render its own entities, so we can fade out the last map's entities along with the map.
		}
		//so we should actually clear the entities after the last map is faded out.
		//remove the entitymanager entirely.

		getPlayer()->setFeetAtMapXY((float)mapXPixelsHQ, (float)mapYPixelsHQ);


		if (getClientGameEngine()->getFinishedLoadEvent())
		{
			if (mapName == "BLANK" == false && updateGameSave == true)
			{
				//TODO: make sure we are allowed in this room before doing this! otherwise we will be stuck.
				getServerConnection()->addQueuedGameSaveUpdateRequest_S(string("lastKnownRoom:`") + mapName + string("`,lastKnownX:`") + to_string(mapXPixelsHQ) + string("`,lastKnownY:`") + to_string(mapYPixelsHQ) + string("`"));
			}
		}
	}


	//currentMap->load();//this is exported by tools, lights, areas, entities are created here per-map in overridden function.
}

void MapManager::changeMap(Map* m, int mapXTiles1X, int mapYTiles1X)
{ //=========================================================================================================================
	changeMap(m->getName(), mapXTiles1X * 2 * 8, mapYTiles1X * 2 * 8);
}

void MapManager::changeMap(Map* m, Door* door)
{ //=========================================================================================================================
	changeMap(m->getName(), (int)door->arrivalXPixelsHQ(), (int)door->arrivalYPixelsHQ());
}

void MapManager::changeMap(Map* m, Area* area)
{ //=========================================================================================================================
	changeMap(m->getName(), (int)(area->middleX()), (int)(area->middleY()));
}

void MapManager::changeMap(Map* m, WarpArea* area)
{ //=========================================================================================================================
	changeMap(m->getName(), (int)area->arrivalXPixelsHQ(), (int)area->arrivalYPixelsHQ());
}

void MapManager::changeMap(const string& mapName, const string& areaName)
{ //=========================================================================================================================
	Map* m = getMapByNameBlockUntilLoaded(mapName);
	Area* a = m->getAreaOrWarpAreaByName(areaName);
	changeMap(m, a);
}

Map* MapManager::getMapByIDBlockUntilLoaded(int id)
{ //=========================================================================================================================

	if (id == -1)
	{
		log.warn(string("getMapByID: ") + to_string(id));
		return getCurrentMap();
	}


	
	Map* m = nullptr;

	if (mapByIDHashMap.containsKey(id))
	{
		m = mapByIDHashMap.get(id);
	}

	if (m == nullptr)
	{
		log.warn("Map did not exist in mapByIDHashMap. Blocking until loaded from network. This should never happen, we should preemptively load map data for connecting doors.");


		getEngine()->sendMapDataRequestByID(id);


		int tries = 0;

		while (m == nullptr)
		{
			tries++;
			if (tries > 5)
			{
				log.warn("Map did not load in more than 5 seconds. Resending request.");

				tries = 0;
				getEngine()->sendMapDataRequestByID(id);
			}

			Main::delay(1000);



			m = mapByIDHashMap.get(id);
		}

		log.warn("Map finished loading from network.");
	}

	return m;
}

Map* MapManager::getMapByNameBlockUntilLoaded(const string& name)
{ //=========================================================================================================================

	if (name == "" || name == "none" || name == "null" || name.length() == 0)
	{
		log.warn(string("getMapByName: ") + name);
		return getCurrentMap();
	}


	Map* m = nullptr;
	
	if (mapByNameHashMap.containsKey(name))
	{
		m = mapByNameHashMap.get(name);
	}

	if (m == nullptr)
	{
		log.warn(string("Map NAME: \"") + name + string("\" did not exist in mapNameHashMap. Blocking until loaded from network. This should never happen, we should preemptively load map data for connecting doors."));


		getEngine()->sendMapDataRequestByName(name);


		int tries = 0;

		while (m == nullptr)
		{
			tries++;
			if (tries > 5)
			{
				log.warn(string("Map NAME: \"") + name + string("\" did not load in more than 5 seconds. Resending request."));

				tries = 0;
				getEngine()->sendMapDataRequestByName(name);
			}

			Main::delay(1000);


			if (mapByNameHashMap.containsKey(name))
			{
				m = mapByNameHashMap.get(name);
			}
		}

		log.warn(string("Map NAME: \"") + name + string("\" finished loading from network."));
	}

	return m;
}

void MapManager::requestMapDataIfNotLoadedYet(const string& name)
{ //=========================================================================================================================


	if (name == "" || name == "none" || name == "null" || name.length() == 0)
	{
		log.warn(string("requestMapDataIfNotLoadedYet: ") + name);
		return;
	}



	Map* m = nullptr;

	if (mapByNameHashMap.containsKey(name))
	{
		m = mapByNameHashMap.get(name);
	}
	if (m == nullptr)
	{
		getEngine()->sendMapDataRequestByName(name);
	}
}

MapState* MapManager::getMapStateByID(int id)
{ //=========================================================================================================================


	//first check the current map.
	MapState* s = getCurrentMap()->getMapStateByID(id);

	if (s != nullptr)
	{
		return s;
	}


	//TODO check the other maps if we can't find this ID, this should never happen.

	return nullptr;
}

Area* MapManager::getAreaByID(int id)
{ //=========================================================================================================================

	// first check the current state of the current map
	if (currentMap != nullptr)
	{
		Area* a = currentMap->getAreaOrWarpAreaByTYPEID(string("AREA.") + to_string(id));
		if (a != nullptr)
		{
			return a;
		}
	}

	//TODO: then check all states of current map

	//then check all states of all maps
	for (int i = 0; i < mapList.size(); i++)
	{
		Map* m = mapList.get(i);
		for (int k = 0; k < (int)m->stateList.size(); k++)
		{
			MapState* s = m->stateList.get(k);
			for (int l = 0; l < (int)s->areaList.size(); l++)
			{
				Area* a = s->areaList.get(l);
				if (a->getID() == id)
				{
					return a;
				}
			}
		}

		for (int n = 0; n < (int)m->warpAreaList.size(); n++)
		{
			if (m->warpAreaList.get(n)->getID() == id)
			{
				return m->warpAreaList.get(n);
			}
		}
	}

	return nullptr;
}

Entity* MapManager::getEntityByID(int id)
{ //=========================================================================================================================
	//TODO: first check the current state of the current map

	//TODO: then check all states of current map

	//then check all states of all maps
	for (int i = 0; i < mapList.size(); i++)
	{
		Map* m = mapList.get(i);
		for (int k = 0; k < (int)m->stateList.size(); k++)
		{
			MapState* s = m->stateList.get(k);
			for (int l = 0; l < (int)s->entityList.size(); l++)
			{
				Entity* a = s->entityList.get(l);
				if (a->getID() == id)
				{
					return a;
				}
			}

			for (int l = 0; l < (int)s->characterList.size(); l++)
			{
				Entity* a = s->characterList.get(l);
				if (a->getID() == id)
				{
					return a;
				}
			}

			for (int l = 0; l < (int)s->lightList.size(); l++)
			{
				Entity* a = s->lightList.get(l);
				if (a->getID() == id)
				{
					return a;
				}
			}
		}

		for (int n = 0; n < (int)m->doorList.size(); n++)
		{
			if (m->doorList.get(n)->getID() == id)
			{
				return m->doorList.get(n);
			}
		}

		for (int n = 0; n < (int)m->activeEntityList.size(); n++)
		{
			if (m->activeEntityList.get(n)->getID() == id)
			{
				return m->activeEntityList.get(n);
			}
		}
	}

	for (int n = 0; n < (int)getSpriteManager()->screenSpriteList.size(); n++)
	{
		if (getSpriteManager()->screenSpriteList.get(n)->getID() == id)
		{
			return getSpriteManager()->screenSpriteList.get(n);
		}
	}

	return nullptr;
}

Light* MapManager::getLightByID(int id)
{ //=========================================================================================================================
	//TODO: first check the current state of the current map

	//TODO: then check all states of current map

	//then check all states of all maps
	for (int i = 0; i < mapList.size(); i++)
	{
		Map* m = mapList.get(i);
		for (int k = 0; k < (int)m->stateList.size(); k++)
		{
			MapState* s = m->stateList.get(k);
			for (int l = 0; l < (int)s->lightList.size(); l++)
			{
				Light* a = s->lightList.get(l);
				if (a->getID() == id)
				{
					return a;
				}
			}
		}
	}

	return nullptr;
}

Door* MapManager::getDoorByID(int id)
{ //=========================================================================================================================

	//TODO: first check current map

	//then check all maps
	for (int i = 0; i < mapList.size(); i++)
	{
		Map* m = mapList.get(i);

		for (int l = 0; l < (int)m->doorList.size(); l++)
		{
			Door* a = m->doorList.get(l);
			if (a->getID() == id)
			{
				return a;
			}
		}
	}

	return nullptr;
}

