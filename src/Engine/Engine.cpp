#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

Logger Engine::log = Logger("Engine");

//BGClientEngine* Engine::clientGameEngine = nullptr;


//=========================================================================================================================
Engine::Engine()
{ //=========================================================================================================================
#ifdef _DEBUG
	log.info("Engine()");
#endif

}

//=========================================================================================================================
Engine::~Engine()
{ //=========================================================================================================================
#ifdef _DEBUG
	log.info("~Engine()");
#endif
	delete audioManager;
	delete spriteManager;
	delete mapManager;
	delete cinematicsManager;
	delete captionManager;
	delete textManager;
	delete eventManager;
	delete cameraman;
	delete actionManager;
}

//=========================================================================================================================
void Engine::init()
{//=========================================================================================================================

	super::init();

#ifdef _DEBUG
	log.info("Engine::init()");
#endif


	audioManager = new AudioManager(this);
	spriteManager = new SpriteManager(this);
	mapManager = new MapManager(this);
	cinematicsManager = new CinematicsManager(this);
	captionManager = new CaptionManager(this);
	textManager = new TextManager(this);
	eventManager = new EventManager(this);
	cameraman = new Cameraman(this);
	actionManager = new ActionManager(this);

	controlsManager = Main::controlsManager;


	textManager->init();
	cinematicsManager->init();

}

//=========================================================================================================================
void Engine::update()
{ //=========================================================================================================================


	audioManager->update();

	textManager->update();

	captionManager->update();

	spriteManager->update();

	cameraman->update();

	mapManager->update(); //map adjusts itself based on cameraman xy so it must update after entities do


	actionManager->update();
	eventManager->update();
	cinematicsManager->update();


	updateDebugText();
}


//=========================================================================================================================
void Engine::render()
{ //=========================================================================================================================

	super::render();

	getMapManager()->render(); //does entities as well, multi-layered rendering here.

	getSpriteManager()->renderScreenSprites(RenderOrder::ABOVE);

	getCaptionManager()->render(RenderOrder::ABOVE);

	getSpriteManager()->renderScreenSprites(RenderOrder::ABOVE_TOP);

	getCaptionManager()->render(RenderOrder::ABOVE_TOP);

	//if(!Keyboard.isKeyDown(Keyboard.KEY_LBRACKET))GLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	getCinematicsManager()->render(RenderOrder::ABOVE_TOP);
	//if(!Keyboard.isKeyDown(Keyboard.KEY_RBRACKET))GLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	getTextManager()->render();

	getMapManager()->renderEntities(RenderOrder::OVER_TEXT);

	getSpriteManager()->renderScreenSprites(RenderOrder::OVER_TEXT); //screensprites

	getCaptionManager()->render(RenderOrder::OVER_TEXT);

	getMapManager()->renderDebug();

	getSpriteManager()->renderScreenSprites(RenderOrder::OVER_GUI);

	getCaptionManager()->render(RenderOrder::OVER_GUI);
}

void Engine::updateDebugText()
{ //=========================================================================================================================

	//playerSpeedText.getText = "Player speed: " + player.pixelsToMoveThisFrame;
	//cameraSpeedText.getText = "Camera speed: " + cameraman.pixelsToMoveThisFrame;
	zoomText->text = string("Zoom level: ") + to_string(cameraman->getZoom()) + string(" ZoomTO: ") + to_string(cameraman->ZOOMto);

	mapCamText->text = string("Map cam xy: ") + to_string(getCurrentMap()->mapCamX()) + string(",") + to_string(getCurrentMap()->mapCamY());
	mapScreenText->text = string("Map screen xy: ") + to_string(getCurrentMap()->screenX()) + string(",") + to_string(getCurrentMap()->screenY());

	mapSizeText->text = string("Map: ") + string(getCurrentMap()->getName()) + string(" | Size : ") + to_string(getCurrentMap()->getWidthPixelsHQ()) + string(" x ") + to_string(getCurrentMap()->getHeightPixelsHQ()) + string(" PixelsHQ | ") + to_string(getCurrentMap()->getWidthTiles1X()) + string(" x ") + to_string(getCurrentMap()->getHeightTiles1X()) + string(" Tiles 1X ");

	resolutionText->text = string("Window res: ") + to_string(GLUtils::getViewportWidth()) + string(" x ") + to_string(GLUtils::getViewportHeight()) + string(" (") + to_string((int)(GLUtils::getViewportWidth()) / 2 / cameraman->getZoom()) + string(" x ") + to_string((int)(GLUtils::getViewportHeight()) / 2 / cameraman->getZoom()) + string(")");

	textText->text = string("Text: ") + textManager->currentText;
	textOptionText->text = string("Text option: ") + textManager->optionBuffer;


}

void* Engine::getGameObjectByTYPEIDName(const string& typeIDName)
{ //=========================================================================================================================


	//typeIDName always looks like TYPE.id
	//MUSIC.1
	//DIALOGUE.0f
	//STATE.4
	//AREA.15

	//areas, entities, and lights are map-specific and are created when the map loads, and destroyed when the map changes.
	//they always have the same ID when they are created, but they may not exist if the map is not loaded.

	//this function is intended to be called when event parameters are parsed,
	//upon loading new events inside of objects (inside of maps), because objects are referenced by id name inside event strings send from the server,
	//based on the exported IDs from the tools, which indexes everything uniquely.
	//therefore all of the objects that a script references will exist inside the map the event is being called from.
	//these references will break every time the map is loaded and unloaded and the objects are destroyed, so an event must re-parse all the parameters each time the map is loaded.

	int id = -1;
	
	try
	{
		id = stoi(typeIDName.substr(typeIDName.find(".") + 1));
	}
	catch (exception)
	{
		log.error("Could not parse id in typeIDName");
	}
	


	//global objects
	if (String::startsWith(typeIDName, "MAP."))
	{
		return getMapManager()->getMapByIDBlockUntilLoaded(id);
	}
	if (String::startsWith(typeIDName, "SPRITE."))
	{
		return getSpriteManager()->getSpriteAssetByIDOrRequestFromServerIfNotExist(id);
	}
	if (String::startsWith(typeIDName, "DIALOGUE."))
	{
		return getEventManager()->getDialogueByIDCreateIfNotExist(id);
	}
	if (String::startsWith(typeIDName, "EVENT."))
	{
		return getEventManager()->getEventByIDCreateIfNotExist(id);
	}
	if (String::startsWith(typeIDName, "FLAG."))
	{
		return getEventManager()->getFlagByIDCreateIfNotExist(id);
	}
	if (String::startsWith(typeIDName, "SKILL."))
	{
		return getEventManager()->getSkillByIDCreateIfNotExist(id);
	}
	if (String::startsWith(typeIDName, "GAMESTRING."))
	{
		return getEventManager()->getGameStringByIDCreateIfNotExist(id);
	}
	if (String::startsWith(typeIDName, "MUSIC."))
	{
		return getAudioManager()->getMusicByIDCreateIfNotExist(id);
	}
	if (String::startsWith(typeIDName, "SOUND."))
	{
		return getAudioManager()->getSoundByIDCreateIfNotExist(id);
	}


	//map objects (will only exist within the current map)
	if (String::startsWith(typeIDName, "STATE."))
	{
		return getMapManager()->getMapStateByID(id);
	}
	if (String::startsWith(typeIDName, "ENTITY."))
	{
		return getMapManager()->getEntityByID(id);
	}
	if (String::startsWith(typeIDName, "AREA."))
	{
		return getMapManager()->getAreaByID(id);
	}
	if (String::startsWith(typeIDName, "LIGHT."))
	{
		return getMapManager()->getLightByID(id);
	}
	if (String::startsWith(typeIDName, "DOOR."))
	{
		return getMapManager()->getDoorByID(id);
	}


	return nullptr;
}

Cameraman* Engine::getCameraman()
{
	return cameraman;
}

MapManager* Engine::getMapManager()
{
	return mapManager;
}

SpriteManager* Engine::getSpriteManager()
{
	return spriteManager;
}

ActionManager* Engine::getActionManager()
{
	return actionManager;
}

TextManager* Engine::getTextManager()
{
	return textManager;
}

AudioManager* Engine::getAudioManager()
{
	return audioManager;
}

CaptionManager* Engine::getCaptionManager()
{
	return captionManager;
}

EventManager* Engine::getEventManager()
{
	return eventManager;
}

CinematicsManager* Engine::getCinematicsManager()
{
	return cinematicsManager;
}

Map* Engine::getCurrentMap()
{
	Map* m = mapManager->currentMap;
	if (m == nullptr)
	{
		m = new Map(this, new MapData(-1, "none", 0, 0));
	}
	return m;
}


//void Engine::setClientGameEngine(BGClientEngine* clientGameEngine)
//{
//	Engine::clientGameEngine = clientGameEngine;
//	EnginePart::setClientGameEngine(clientGameEngine);
//}


//void Engine::setControlsManager(ControlsManager* controlsManager)
//{
//	controlsManager = controlsManager;
//	
//}

//BGClientEngine* Engine::getClientGameEngine()
//{
//	return clientGameEngine;
//}


float Engine::getWidthRelativeToZoom()
{
	return getWidth() / getCameraman()->getZoom();
}

float Engine::getHeightRelativeToZoom()
{
	return getHeight() / getCameraman()->getZoom();
}



bool Engine::serverMessageReceived(string e)// ChannelHandlerContext* ctx, MessageEvent* e)
{ //===============================================================================================


  //Print out the line received from the server.
  //
  //   try
  //   {
  //      Thread::currentThread().setName("ClientTCP_BobsGameClientHandler");
  //   }
  //   catch (SecurityException ex)
  //   {
  //      ex->printStackTrace();
  //   }



	string s = e;


	if (super::serverMessageReceived(e))
	{
		return true;
	}
	else
	if (String::startsWith(s, BobNet::Sprite_Response))
	{
		incomingSpriteData(s);
		return true;
	}
	else
	if (String::startsWith(s, BobNet::Map_Response))
	{
		incomingMapData(s);
		return true;
	}
	else
	if (String::startsWith(s, BobNet::Dialogue_Response))
	{
		incomingDialogue(s);
		return true;
	}
	else
	if (String::startsWith(s, BobNet::Flag_Response))
	{
		incomingFlag(s);
		return true;
	}
	else
	if (String::startsWith(s, BobNet::Skill_Response))
	{
		incomingSkill(s);
		return true;
	}
	else
	if (String::startsWith(s, BobNet::Event_Response))
	{
		incomingEvent(s);
		return true;
	}
	else
	if (String::startsWith(s, BobNet::GameString_Response))
	{
		incomingGameString(s);
		return true;
	}
	else
	if (String::startsWith(s, BobNet::Music_Response))
	{
		incomingMusic(s);
		return true;
	}
	else
	if (String::startsWith(s, BobNet::Sound_Response))
	{
		incomingSound(s);
		return true;
	}
	return false;


}




void Engine::sendSpriteDataRequestByName(string spriteAssetName)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(BobNet::Sprite_Request_By_Name + spriteAssetName + BobNet::endline);
}

void Engine::sendSpriteDataRequestByID(int id)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(BobNet::Sprite_Request_By_ID + to_string(id) + BobNet::endline);
}

void Engine::incomingSpriteData(string s)
{ //=========================================================================================================================

  //Sprite:id-getSpriteName:spriteData
	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::

	SpriteData* data = SpriteData::fromBase64ZippedJSON(s);


	if (data == nullptr)
	{
		log.error("Sprite could not be decompressed.");
	}
	else
	{
		Sprite* sprite = getSpriteManager()->spriteByNameHashMap.get(data->getName());

		if (sprite == nullptr)
		{
			sprite = new Sprite(this);
		}

		sprite->initializeWithSpriteData(data);

		getSpriteManager()->spriteByNameHashMap.put(sprite->getName(), sprite);
		getSpriteManager()->spriteByIDHashMap.put(sprite->getID(), sprite);
	}
}

void Engine::sendMapDataRequestByName(string mapName)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(BobNet::Map_Request_By_Name + mapName + BobNet::endline);
}

void Engine::sendMapDataRequestByID(int id)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(BobNet::Map_Request_By_ID + to_string(id) + BobNet::endline);
}

void Engine::incomingMapData(string s)
{ //=========================================================================================================================

  //Map:id-name:Base64->GZip->GSON/JSON->MapData[Lights,Entities,Events,States,Areas,Doors,Characters]
	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::

	MapData* data = MapData::fromBase64ZippedJSON(s);

	if (data == nullptr)
	{
		log.error("Map could not be decompressed.");
	}
	else
	{
		if (getMapManager()->mapByNameHashMap.get(data->getName()) == nullptr)
		{
			Map* m = new Map(this, data);
			getMapManager()->mapList.add(m);
			getMapManager()->mapByNameHashMap.put(data->getName(), m);
			getMapManager()->mapByIDHashMap.put(data->getID(), m);
		}
	}
}

void Engine::sendServerObjectRequest(ServerObject* serverObject)
{ //====================================================
  //   if (serverObject->getClass() == Dialogue::typeid)
  //   {
  //      sendDialogueRequest((static_cast<Dialogue*>(serverObject))->id());
  //   }
  //   if (serverObject->getClass() == Flag::typeid)
  //   {
  //      sendFlagRequest((static_cast<Flag*>(serverObject))->id());
  //   }
  //   if (serverObject->getClass() == GameString::typeid)
  //   {
  //      sendGameStringRequest((static_cast<GameString*>(serverObject))->id());
  //   }
  //   if (serverObject->getClass() == Skill::typeid)
  //   {
  //      sendSkillRequest((static_cast<Skill*>(serverObject))->id());
  //   }
  //   if (serverObject->getClass() == Event::typeid)
  //   {
  //      sendEventRequest((static_cast<Event*>(serverObject))->id());
  //   }
  //   if (serverObject->getClass() == Sound::typeid)
  //   {
  //      sendSoundRequest((static_cast<Sound*>(serverObject))->id());
  //   }
  //   if (serverObject->getClass() == Music::typeid)
  //   {
  //      sendMusicRequest((static_cast<Music*>(serverObject))->id());
  //   }
}

void Engine::sendDialogueRequest(int id)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(BobNet::Dialogue_Request + to_string(id) + BobNet::endline);
}

void Engine::incomingDialogue(string s)
{ //=========================================================================================================================

	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::

								   //Dialogue:id-name:base64Blob

	DialogueData* data = DialogueData::fromBase64ZippedJSON(s);

	if (data == nullptr)
	{
		log.error("Dialogue could not be decompressed.");
	}
	else
	{
		Dialogue* d = getEventManager()->getDialogueByIDCreateIfNotExist(data->getID());
		d->setData_S(data);
	}
}


void Engine::sendEventRequest(int id)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(BobNet::Event_Request + to_string(id) + BobNet::endline);
}

void Engine::incomingEvent(string s)
{ //=========================================================================================================================

  //Event:id-name:eventData
	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::


	EventData* data = EventData::fromBase64ZippedJSON(s);

	if (data == nullptr)
	{
		log.error("Event could not be decompressed.");
	}
	else
	{
		Event* d = getEventManager()->getEventByIDCreateIfNotExist(data->getID());
		d->setData_S(data);
	}
}

void Engine::sendGameStringRequest(int id)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(BobNet::GameString_Request + to_string(id) + BobNet::endline);
}

void Engine::incomingGameString(string s)
{ //=========================================================================================================================


  //GameString:id:data
	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::

	GameStringData* data = GameStringData::fromBase64ZippedJSON(s);

	if (data == nullptr)
	{
		log.error("GameString could not be decompressed.");
	}
	else
	{
		GameString* gameString = getEventManager()->getGameStringByIDCreateIfNotExist(data->getID());
		gameString->setData_S(data);
	}
}

void Engine::sendFlagRequest(int id)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(BobNet::Flag_Request + to_string(id) + BobNet::endline);
}

void Engine::incomingFlag(string s)
{ //=========================================================================================================================


  //Flag:id:data
	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::

	FlagData* data = FlagData::fromBase64ZippedJSON(s);

	if (data == nullptr)
	{
		log.error("Flag could not be decompressed.");
	}
	else
	{
		Flag* flag = getEventManager()->getFlagByIDCreateIfNotExist(data->getID());
		flag->setData_S(data);
	}
}

void Engine::sendSkillRequest(int id)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(BobNet::Skill_Request + to_string(id) + BobNet::endline);
}

void Engine::incomingSkill(string s)
{ //=========================================================================================================================


  //Skill:id:data
	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::

	SkillData* data = SkillData::fromBase64ZippedJSON(s);

	if (data == nullptr)
	{
		log.error("Skill could not be decompressed.");
	}
	else
	{
		Skill* skill = getEventManager()->getSkillByIDCreateIfNotExist(data->getID());
		skill->setData_S(data);
	}
}

void Engine::sendMusicRequest(int id)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(BobNet::Music_Request + to_string(id) + BobNet::endline);
}

void Engine::incomingMusic(string s)
{ //=========================================================================================================================

  //Music:id:data
	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::

	MusicData* data = MusicData::fromBase64ZippedJSON(s);

	if (data == nullptr)
	{
		log.error("Music could not be decompressed.");
	}
	else
	{
		Music* music = getAudioManager()->getMusicByIDCreateIfNotExist(data->getID());
		music->setData_S(data);
	}
}

void Engine::sendSoundRequest(int id)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(BobNet::Sound_Request + to_string(id) + BobNet::endline);
}

void Engine::incomingSound(string s)
{ //=========================================================================================================================


  //Sound:id:data
	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::

	SoundData* data = SoundData::fromBase64ZippedJSON(s);

	if (data == nullptr)
	{
		log.error("Sound could not be decompressed.");
	}
	else
	{
		Sound* sound = getAudioManager()->getSoundByIDCreateIfNotExist(data->getID());
		sound->setData_S(data);
	}
}

