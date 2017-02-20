#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once


#include "BGClientEngine.h"
#include "../../Utility/FileUtils.h"

Logger BGClientEngine::log = Logger("BGClientEngine");

bool BGClientEngine::debugMode = true;

BGClientEngine::BGClientEngine()
{ //=========================================================================================================================
#ifdef _DEBUG
	log.info("BGClientEngine()");
#endif
}

BGClientEngine::~BGClientEngine()
{ //=========================================================================================================================

#ifdef _DEBUG
	log.info("~BGClientEngine()");
#endif



}

void BGClientEngine::init()
{ //=========================================================================================================================


	super::init();


#ifdef _DEBUG
	log.info("BGClientEngine::init()");
#endif
	

	clock = new Clock(this);

	player = new Player(this);
	normalPlayer = player;

	guiManager = new GUIManager(this);

	statusBar = new StatusBar(this);
	wallet = new Wallet(this);

	friendManager = new FriendManager(this);

	nD = new ND();
	stadiumScreen = new StadiumScreen(this);


	if (Main::previewClientInEditor == false)
	{
		loadPreCachedObjectData();
	}


	guiManager->init();

	statusBar->init();

	wallet->init();


	nD->init();
	//nD.setActivated(true);


	//BobsGame* bobsgame = new BobsGame();// nD);
	//bobsgame.setConnection(null);
	//bobsgame->init();
	//		nDMenu.addGame(ping,"Ping",Color.BLUE);
	//		nDMenu.addGame(ramio,"Ramio",Color.RED);
	//		nDMenu.addGame(bobsgame,"\"bob's game\"",Color.GREEN);
	//nD->setGame(bobsgame);


	friendManager->init();

	//mapManager.changeMap("TOWNYUUDownstairs",30,18);
	//mapManager.changeMap("TOWNVideoRentAdultRoom",10,10);
	//mapManager.changeMap("CITYTheCafe",10,10);
	//mapManager.changeMap("TOWNTacoBurger",53,110);
	//mapManager.changeMap("BLANK",16,16);
	//mapManager.changeMap("TOWNCoffeeShop",53,110);//start nowhere
	//mapManager.changeMap("CITYCityHallEntrance",53,110);
	//mapManager.changeMap("CITYStadiumBackstage",80,140);
	//mapManager.changeMap("TOWNPets4Less",53,110);
	//mapManager.changeMap("TOWNMovieTheatreMensBathroom",53,110);

	cameraman->setTarget(player);


	//can't remember why i did this, to fix gui stuff???
	cameraman->update(); //TODO: fix this so it only updates ONE TICK


	cameraman->setXYToTarget(); //TODO: fix this so it goes to xtarget (camstop tiles) instead of just npc target (player)


	//itemManager.ITEM_get_no_caption(new Item("nD","The indie handheld Game() console. A juggernaut of disposable technology, devised as a vengeful scheme to destroy the traditional Game() industry. Invented by a secretive, notoriously stubborn developer whose first Game() was held back by corrupt, obsolete corporate policy. So cheap and ubiquitous that every kid has two or three- making it a modern societal requirement."));
	//itemManager.ITEM_get_no_caption(new Item("Wallet","This holds your old receipts, slowly rubbing the ink off so the paper can be reused to write down phone numbers- if only you had a pen!"));
	//itemManager.ITEM_get_no_caption(new Item("Keys","These relics of long-antiquated technology give an illusion of security. Easily lost, they weigh down your pants, scratch everything in your pockets, and are generally uncomfortable, noisy metal daggers. Don't ever leave home without them!"));
	//itemManager.ITEM_get_no_caption(new Item("Smartphone","This infinitely helpful device keeps you constantly distracted and tracks your every move for a huge monthly fee. Sometimes you begin to wonder if it is making you more impulsive and helpless, and are fortunately comforted by its glow just as panic sets in. Scientists are pretty sure it doesn't cause brain cancer!"));


	//new EasingTest();

	//cinematicsManager.toggleLetterbox(true);
	//textManager.getText("Yuu normal font <TINY>tiny font <SMALL><GREEN>small font <WHITE><HUGE>huge font <.><SMALL><NORMAL><NEXTLINE>next line <1>top getText box<0>bottom getText box");

	//captionManager.CAPTION_make_caption(Caption.CAPTION_CENTERED_SCREEN,0,Caption.CAPTION_DELETE_WHEN_MAIN_SPRITE_MOVES,"CAPTION_CENTERED_SCREEN",0,Color.white,Color.black,4,1.0f,0);
	//captionManager.CAPTION_make_caption(Caption.CAPTION_CENTERED_OVER_SPRITE,0,-1,"CAPTION_CENTERED_OVER_SPRITE",0,Color.white,Color.black,4,1.0f,0);
	//captionManager.CAPTION_make_caption(Caption.CAPTION_CENTERED_X,0,Caption.CAPTION_DELETE_WHEN_MAIN_SPRITE_MOVES,"CAPTION_CENTERED_X",0,Color.white,Color.black,4,1.0f,0);


	//new Notification("This is the notification area.");
	//new Notification("This is the notification area. Important messages will show up here periodically to let you know about events or whatever.");
}





//The following method was originally marked 'synchronized':
void BGClientEngine::setGameInitializedFromSave_S(bool b)
{
	_isGameInitializedFromSave = b;
}

//The following method was originally marked 'synchronized':
bool BGClientEngine::getGameInitializedFromSave_S()
{
	return _isGameInitializedFromSave;
}


//The following method was originally marked 'synchronized':
void BGClientEngine::setProjectLoadEventID_S(int id)
{ //=========================================================================================================================
	_projectLoadEventID = id;
}

//The following method was originally marked 'synchronized':
int BGClientEngine::getProjectLoadEventID_S()
{ //=========================================================================================================================
	return _projectLoadEventID;
}

bool BGClientEngine::getFinishedLoadEvent()
{
	return finishedLoadEvent;
}

void BGClientEngine::update()
{ //=========================================================================================================================

	
	long long currentTime = System::currentHighResTimer();



	if (Main::introMode == true)
	{
		//getServerConnection()->setGameSave_S(new GameSave());
		getServerConnection()->setInitialGameSaveReceived_S(true);
		setGameInitializedFromSave_S(true);

		guiManager->update();
	}
	else
	{
		if (getServerConnection()->getInitialGameSaveReceived_S() == false)
		{
			return;
		}


		if (isGameInitializedFromSave_nonThreaded == false)
		{
			if (getGameInitializedFromSave_S() == true)
			{
				isGameInitializedFromSave_nonThreaded = true;

				initializeGameFromSave_S();
				setPlayerAppearanceFromGameSave_S();
			}

			return;
		}




		guiManager->update();


		if (gameSaveCompleted_nonThreaded == false)
		{
			if (getGameSave_S().wasPlayerCreatedYet() == false)
			{
				if (guiManager->playerEditMenu->getIsActivated() == false)
				{
					guiManager->playerEditMenu->setActivated(true);
				}
			}
			else
			{
				gameSaveCompleted_nonThreaded = true;
			}

			return;
		}


		if (isLoadEventInitialized_nonThreaded == false)
		{
			long long startTime = lastSentLoadEventRequestTime;
			int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
			if (ticksPassed > 200)
			{
				lastSentLoadEventRequestTime = currentTime;

				if (getProjectLoadEventID_S() == -1)
				{
					sendLoadEventRequest();
				}
				else
				{
					isLoadEventInitialized_nonThreaded = true;

					loadEvent = getEventManager()->getEventByIDCreateIfNotExist(getProjectLoadEventID_S());
					getEventManager()->addToEventQueueIfNotThere(loadEvent); //events update their own network data inside their run function
				}
			}

			return;
		}


		if (finishedLoadEvent == false)
		{
			//wait for load event to finish
			if (getEventManager()->isEventInQueue(loadEvent) == false)
			{
				finishedLoadEvent = true;

				GameSave g = getGameSave_S();


				bool updateGameSave = false;

				//if(g.startingRoom.equals("BLANK"))g.startingRoom = "GENERIC1UpstairsBedroom1";
				if (g.lastKnownRoom == "BLANK")
				{
					g.lastKnownRoom = "GENERIC1UpstairsBedroom1";
					g.lastKnownX = 17 * 8 * 2;
					g.lastKnownY = 12 * 8 * 2;
					getServerConnection()->setGameSave_S(g);
					updateGameSave = true;
				}

				getMapManager()->changeMap(g.lastKnownRoom, g.lastKnownX, g.lastKnownY, updateGameSave); // *** don't changemap in network thread! it blocks
			}
		}
	}


	handleGameEngineOptionKeys();


	Engine::update();


	clock->update();

	friendManager->update();


	//EasingTest.update();

	statusBar->update();

	wallet->update();

	nD->update();
	stadiumScreen->update();
}

void BGClientEngine::cleanup()
{ //=========================================================================================================================

	Engine::cleanup();

	guiManager->cleanup();

	friendManager->cleanup();
}

void BGClientEngine::render()
{ //=========================================================================================================================


	if (nD->getIsScrolledUp() == false)
	{
		Engine::render();
	}


	//GLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	nD->render();
	//stadiumScreen.render();

	//GLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	statusBar->render();

	guiManager->render();

	//GLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}

bool BGClientEngine::areAnyMenusOpen()
{ //=========================================================================================================================


	//   if (getND()->getIsActivated() || getStuffMenu()->getIsActivated() || getPlayerEditMenu()->getIsActivated() || getGameStore()->getIsActivated())
	//   {
	//      return true;
	//   }

	return false;
}

void BGClientEngine::handleGameEngineOptionKeys()
{ //=========================================================================================================================


	if (getControlsManager()->key_F1_Pressed() == true)
	{
		//guiManager->keyboardScreen->toggleActivated();
	}


	if (getControlsManager()->bgClient_OPENND_Pressed() == true && nD->getIsActivated() == false)
	{
		//nD->toggleActivated();
	}


	if (getControlsManager()->bgClient_OPENMENU_Pressed() == true)
	{
		//guiManager->stuffMenu->toggleActivated();
	}


	if (areAnyMenusOpen())
	{
		return;
	}


	//-----------------------------
	// zoom controls
	//------------------------------

	if (getCameraman()->zoomManuallyEnabled)
	{
		if (getControlsManager()->bgClient_ZOOMOUT_Pressed() == true)
		{
			cameraman->zoomOut();
		}

		if (getControlsManager()->bgClient_ZOOMIN_Pressed() == true)
		{
			cameraman->zoomIn();
		}

		if (getControlsManager()->bgClient_ZOOMRESET_Pressed() == true)
		{
			cameraman->resetZoom();
		}

		if (getControlsManager()->bgClient_QUICKZOOMOUT_Pressed() == true)
		{
			cameraman->quickZoomOut();
		}
		else
		{
			if (getControlsManager()->bgClient_QUICKZOOMIN_Pressed() == true)
			{
				cameraman->quickZoomIn();
			}
			else
			{
				cameraman->resetQuickZoom();
			}
		}
	}


	if (debugMode == true)
	{
		if (getControlsManager()->key_H_Pressed() == true)
		{
			hitLayerEnabled = !hitLayerEnabled;
			Console::debug(string("Hit Layer Toggled: ") + StringConverterHelper::toString(hitLayerEnabled), 1000);
		}

		if (getControlsManager()->key_TILDE_Pressed() == true)
		{
			underLayerEnabled = !underLayerEnabled;
			Console::debug(string("Under Layer Toggled: ") + StringConverterHelper::toString(underLayerEnabled), 1000);
		}

		if (getControlsManager()->key_1_Pressed() == true)
		{
			entityLayerEnabled = !entityLayerEnabled;
			Console::debug(string("Entity Layer Toggled: ") + StringConverterHelper::toString(entityLayerEnabled), 1000);
		}

		if (getControlsManager()->key_2_Pressed() == true)
		{
			overLayerEnabled = !overLayerEnabled;
			Console::debug(string("Over Layer Toggled: ") + StringConverterHelper::toString(overLayerEnabled), 1000);
		}

		if (getControlsManager()->key_3_Pressed() == true)
		{
			lightsLayerEnabled = !lightsLayerEnabled;
			Console::debug(string("Lights Layer Toggled: ") + StringConverterHelper::toString(lightsLayerEnabled), 1000);
		}

		if (getControlsManager()->key_4_Pressed() == true)
		{
			GLUtils::useShaders = !GLUtils::useShaders;
			Console::debug(string("Shader Toggled: ") + to_string(GLUtils::useShaders), 1000);
		}

//		if (getControlsManager()->key_5_Pressed() == true)
//		{
//			GLUtils::useFBO = !GLUtils::useFBO;
//			Console::debug(string("FBO Toggled: ") + StringConverterHelper::toString(GLUtils::useFBO), 1000);
//		}

		if (getControlsManager()->key_6_Pressed() == true)
		{
			debugLayerEnabled = !debugLayerEnabled;
			Console::debug(string("Debug Layer Toggled: ") + StringConverterHelper::toString(debugLayerEnabled), 1000);
		}

		if (getControlsManager()->key_NUM2_Pressed() == true)
		{
			getMapManager()->contrast -= 0.1f;
			Console::debug(string("Contrast: ") + to_string(getMapManager()->contrast), 1000);
		}

		if (getControlsManager()->key_NUM3_Pressed() == true)
		{
			getMapManager()->contrast += 0.1f;
			Console::debug(string("Contrast: ") + to_string(getMapManager()->contrast), 1000);
		}

		if (getControlsManager()->key_NUM5_Pressed() == true)
		{
			getMapManager()->brightness -= 0.1f;
			Console::debug(string("Brightness: ") + to_string(getMapManager()->brightness), 1000);
		}

		if (getControlsManager()->key_NUM6_Pressed() == true)
		{
			getMapManager()->brightness += 0.1f;
			Console::debug(string("Brightness: ") + to_string(getMapManager()->brightness), 1000);
		}

		if (getControlsManager()->key_NUM8_Pressed() == true)
		{
			getMapManager()->saturation -= 0.1f;
			Console::debug(string("Saturation: ") + to_string(getMapManager()->saturation), 1000);
		}

		if (getControlsManager()->key_NUM9_Pressed() == true)
		{
			getMapManager()->saturation += 0.1f;
			Console::debug(string("Saturation: ") + to_string(getMapManager()->saturation), 1000);
		}

		if (getControlsManager()->key_NUM1_Pressed() == true)
		{
			getMapManager()->gamma -= 0.1f;
			Console::debug(string("Gamma: ") + to_string(getMapManager()->gamma), 1000);
		}

		if (getControlsManager()->key_NUM4_Pressed() == true)
		{
			getMapManager()->gamma += 0.1f;
			Console::debug(string("Gamma: ") + to_string(getMapManager()->gamma), 1000);
		}

		if (getControlsManager()->key_NUM0_Pressed() == true)
		{
			getMapManager()->saturation = 1.0f;
			getMapManager()->brightness = 1.0f;
			getMapManager()->contrast = 1.0f;
			getMapManager()->gamma = 1.0f;
			Console::debug(string("Saturation: ") + to_string(getMapManager()->saturation) + string(" | Brightness: ") + to_string(getMapManager()->brightness) + string(" | Contrast: ") + to_string(getMapManager()->contrast) + string(" | Gamma: ") + to_string(getMapManager()->gamma), 1000);
		}
	}
}

void BGClientEngine::updateDebugText()
{ //=========================================================================================================================
	Engine::updateDebugText();

	playerMapText->text = string("Player map xy: ") + to_string(player->getX()) + string(",") + to_string(player->getY()) + string(" | Tiles: ") + to_string(player->getX() / 8) + string(",") + to_string(player->getY() / 8);
	playerScreenText->text = string("Player screen xy: ") + to_string(player->getScreenLeft()) + string(",") + to_string(player->getScreenTop()) + string(" Player layer: ") + to_string((int)player->getRenderOrder());
}

void BGClientEngine::loadPreCachedObjectData()
{ //===============================================================================================


	bool debug = false;


	ArrayList<string>* b64List = nullptr;


	try
	{
		b64List = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/PreloadSkillData");
	}
	catch (exception e)//IOException e)
	{
		//e->printStackTrace();
	}
	if (b64List->size() > 0)
	{
		for (int i = 0; i < b64List->size(); i++)
		{
			string s = b64List->get(i);
			if (s.length() > 0)
			{
				SkillData* data = SkillData::fromBase64ZippedJSON(s);
				//Skill* skill =
                new Skill(this, data);
				//getEventManager()->skillList.add(skill);
				if (debug)
				{
					log.debug(string("Preload Skill id:") + to_string(data->getID()) + string(" name:") + data->getName());
				}
			}
		}
	}

	try
	{
		b64List = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/PreloadDialogueData");
	}
	catch (exception e)//IOException e)
	{
		//e->printStackTrace();
	}
	if (b64List->size() > 0)
	{
		for (int i = 0; i < b64List->size(); i++)
		{
			string s = b64List->get(i);
			if (s.length() > 0)
			{
				DialogueData* data = DialogueData::fromBase64ZippedJSON(s);
				//Dialogue* m =
                new Dialogue(this, data);
				//getEventManager()->dialogueList.add(m);
				if (debug)
				{
					log.debug(string("Preload Dialogue id:") + to_string(data->getID()) + string(" name:") + data->getName());
				}
			}
		}
	}

	try
	{
		b64List = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/PreloadFlagData");
	}
	catch (exception e)//IOException e)
	{
		//e->printStackTrace();
	}
	if (b64List->size() > 0)
	{
		for (int i = 0; i < b64List->size(); i++)
		{
			string s = b64List->get(i);
			if (s.length() > 0)
			{
				FlagData* data = FlagData::fromBase64ZippedJSON(s);
				//Flag* m =
                new Flag(this, data);
				//getEventManager()->flagList.add(m);
				if (debug)
				{
					log.debug(string("Preload Flag id:") + to_string(data->getID()) + string(" name:") + data->getName());
				}
			}
		}
	}

	try
	{
		b64List = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/PreloadGameStringData");
	}
	catch (exception e)//IOException e)
	{
		//e->printStackTrace();
	}
	if (b64List->size() > 0)
	{
		for (int i = 0; i < b64List->size(); i++)
		{
			string s = b64List->get(i);
			if (s.length() > 0)
			{
				GameStringData* data = GameStringData::fromBase64ZippedJSON(s);
				//GameString* m =
                new GameString(this, data);
				//getEventManager()->gameStringList.add(m);
				if (debug)
				{
					log.debug(string("Preload GameString id:") + to_string(data->getID()) + string(" name:") + data->getName());
				}
			}
		}
	}

	try
	{
		b64List = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/PreloadEventData");
	}
	catch (exception e)//IOException e)
	{
		//e->printStackTrace();
	}
	if (b64List->size() > 0)
	{
		for (int i = 0; i < b64List->size(); i++)
		{
			string s = b64List->get(i);
			if (s.length() > 0)
			{
				EventData* data = EventData::fromBase64ZippedJSON(s);
				//Event* m =
                new Event(this, data);
				//getEventManager()->eventList.add(m);
				if (debug)
				{
					log.debug(string("Preload Event id:") + to_string(data->getID()) + string(" name:") + data->getName());
				}
			}
		}
	}

	try
	{
		b64List = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/PreloadSpriteData");
	}
	catch (exception e)//IOException e)
	{
		//e->printStackTrace();
	}
	if (b64List->size() > 0)
	{
		for (int i = 0; i < b64List->size(); i++)
		{
			string s = b64List->get(i);

			if (s.length() > 0)
			{
				SpriteData* data = SpriteData::fromBase64ZippedJSON(s);

				if (getSpriteManager()->spriteByIDHashMap.get(data->getID()) == nullptr)
				{
					Sprite* sprite = new Sprite(this);
					sprite->initializeWithSpriteData(data);

					getSpriteManager()->spriteByNameHashMap.put(data->getName(), sprite);
					getSpriteManager()->spriteByIDHashMap.put(data->getID(), sprite);
				}
				else
				{
					log.error(string("Sprite already exists:") + data->getName());
				}

				//System.out.println(spriteData.name);

				if (debug)
				{
					log.debug(string("Preload Sprite id:") + to_string(data->getID()) + string(" name:") + data->getName());
				}
			}
		}
	}


	try
	{
		b64List = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/PreloadSoundData");
	}
	catch (exception e)//IOException e)
	{
		//e->printStackTrace();
	}
	if (b64List->size() > 0)
	{
		for (int i = 0; i < b64List->size(); i++)
		{
			string s = b64List->get(i);

			if (s.length() > 0)
			{
				SoundData* data = SoundData::fromBase64ZippedJSON(s);

				//Sound* m =
                new Sound(this, data);

				//just adding the md5 names for the sounds in sounds.zip to the soundList so they can be immediately accessed without server calls
				//getAudioManager()->soundList.add(m);

				//music will first ask the server

				//System.out.println(data.name);

				if (debug)
				{
					log.debug(string("Preload Sound id:") + to_string(data->getID()) + string(" name:") + data->getName());
				}
			}
		}
	}


	try
	{
		b64List = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/PreloadMusicData");
	}
	catch (exception e)//IOException e)
	{
		//e->printStackTrace();
	}
	if (b64List->size() > 0)
	{
		for (int i = 0; i < b64List->size(); i++)
		{
			string s = b64List->get(i);

			if (s.length() > 0)
			{
				MusicData* data = MusicData::fromBase64ZippedJSON(s);

				//Music* m =
                new Music(this, data);

				//just adding the md5 names for PRELOADED music in music.zip to the musicList so they can be immediately accessed without server calls
				//getAudioManager()->musicList.add(m);

				if (debug)
				{
					log.debug(string("Preload Music id:") + to_string(data->getID()) + string(" name:") + data->getName());
				}
			}
		}
	}

	try
	{
		b64List = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/PreloadMapData");
	}
	catch (exception e)//IOException e)
	{
		//e->printStackTrace();
	}
	if (b64List->size() > 0)
	{
		for (int i = 0; i < b64List->size(); i++)
		{
			string s = b64List->get(i);

			if (s.length() > 0)
			{
				MapData* data = MapData::fromBase64ZippedJSON(s);

				if (getMapManager()->mapByIDHashMap.get(data->getID()) == nullptr)
				{
					Map* m = new Map(this, data);

					getMapManager()->mapList.add(m);
					getMapManager()->mapByNameHashMap.put(data->getName(), m);
					getMapManager()->mapByIDHashMap.put(data->getID(), m);
				}
				else
				{
					log.error(string("Map already exists:") + data->getName());
				}

				if (debug)
				{
					log.debug(string("Preload Map id:") + to_string(data->getID()) + string(" name:") + data->getName());
				}
			}
		}
	}
}

//The following method was originally marked 'synchronized':
void BGClientEngine::initializeGameFromSave_S()
{ //=========================================================================================================================


	{
		//set flags, set dialogueDone values, stats values
		string itemsHeld = getGameSave_S().itemsHeld; //items are just comma separated values
		while (itemsHeld.find(",") != string::npos)
		{
			string dataString = itemsHeld.substr(0, itemsHeld.find(","));

			int itemID = -1;
			try
			{
				itemID = stoi(dataString.substr(0, dataString.find(":")));
			}
			catch (exception e)//NumberFormatException ex)
			{
				//ex->printStackTrace();
				return;
			}
			dataString = dataString.substr(dataString.find(":") + 1);
			bool value = StringConverterHelper::fromString<bool>(dataString.substr(0, dataString.find(":")));
			dataString = dataString.substr(dataString.find(":") + 1);
			long long timeSet = -1;
			try
			{
				timeSet = StringConverterHelper::fromString<long long>(dataString);
			}
			catch (exception e)//NumberFormatException ex)
			{
				//ex->printStackTrace();
				return;
			}


			itemsHeld = itemsHeld.substr(itemsHeld.find(",") + 1);


			Item* f = getEventManager()->getItemByID(itemID);
			f->initHaveItemValue_S(value, timeSet);
		}
	}


	{
		string flagsSet = getGameSave_S().flagsSet; //flags are just comma separated values
		while (flagsSet.find(",") != string::npos)
		{
			//flag looks like id:true:timeSet,id:false:timeSet,
			string dataString = flagsSet.substr(0, flagsSet.find(","));

			int flagID = -1;
			try
			{
				flagID = stoi(dataString.substr(0, dataString.find(":")));
			}
			catch (exception e)//NumberFormatException ex)
			{
				//ex->printStackTrace();
				return;
			}
			dataString = dataString.substr(dataString.find(":") + 1);
			bool value = StringConverterHelper::fromString<bool>(dataString.substr(0, dataString.find(":")));
			dataString = dataString.substr(dataString.find(":") + 1);
			long long timeSet = -1;
			try
			{
				timeSet = StringConverterHelper::fromString<long long>(dataString);
			}
			catch (exception e)//NumberFormatException ex)
			{
				//ex->printStackTrace();
				return;
			}


			flagsSet = flagsSet.substr(flagsSet.find(",") + 1);

			Flag* f = getEventManager()->getFlagByIDCreateIfNotExist(flagID);
			f->initValueFromGameSave_S(value, timeSet);
		}
	}


	{
		string dialoguesDone = getGameSave_S().dialoguesDone; //dialogues are just comma separated values
		while (dialoguesDone.find(",") != string::npos)
		{
			string dataString = dialoguesDone.substr(0, dialoguesDone.find(","));

			int dialogueID = -1;
			try
			{
				dialogueID = stoi(dataString.substr(0, dataString.find(":")));
			}
			catch (exception e)//NumberFormatException ex)
			{
				//ex->printStackTrace();
				return;
			}
			dataString = dataString.substr(dataString.find(":") + 1);
			bool value = StringConverterHelper::fromString<bool>(dataString.substr(0, dataString.find(":")));
			dataString = dataString.substr(dataString.find(":") + 1);
			long long timeSet = -1;
			try
			{
				timeSet = StringConverterHelper::fromString<long long>(dataString);
			}
			catch (exception e)//NumberFormatException ex)
			{
				//ex->printStackTrace();
				return;
			}

			dialoguesDone = dialoguesDone.substr(dialoguesDone.find(",") + 1);

			Dialogue* d = getEventManager()->getDialogueByIDCreateIfNotExist(dialogueID);
			d->initDialogueDoneValueFromGameSave_S(value, timeSet);
		}
	}


	{
		string skillValues = getGameSave_S().skillValues; //skills look like skillID:float:time, so 199:-1.4:time,
		while (skillValues.find(",") != string::npos)
		{
			string dataString = skillValues.substr(0, skillValues.find(","));

			int skillID = -1;
			try
			{
				skillID = stoi(dataString.substr(0, dataString.find(":")));
			}
			catch (exception e)//NumberFormatException ex)
			{
				//ex->printStackTrace();
				return;
			}
			dataString = dataString.substr(dataString.find(":") + 1);
			float value = -1;
			try
			{
				value = stof(dataString.substr(0, dataString.find(":")));
			}
			catch (exception e)//NumberFormatException ex)
			{
				//ex->printStackTrace();
				return;
			}
			dataString = dataString.substr(dataString.find(":") + 1);
			long long timeSet = -1;
			try
			{
				timeSet = StringConverterHelper::fromString<long long>(dataString);
			}
			catch (exception e)//NumberFormatException ex)
			{
				//ex->printStackTrace();
				return;
			}

			skillValues = skillValues.substr(skillValues.find(",") + 1);

			Skill* skill = getEventManager()->getSkillByIDCreateIfNotExist(skillID);
			skill->initValueFromGameSave_S(value, timeSet);
		}
	}

	//mapManager.changeMap("ALPHABobsApartment",18,15);//g.lastKnownRoom, g.lastKnownX/8, g.lastKnownY/8);
	//mapManager.changeMap(g.lastKnownRoom, g.lastKnownX/8, g.lastKnownY/8);


	setGameInitializedFromSave_S(true);
}

//The following method was originally marked 'synchronized':
void BGClientEngine::setPlayerAppearanceFromGameSave_S()
{ //=========================================================================================================================

	GameSave g = getGameSave_S();

	player->setAppearanceFromCharacterAppearanceString(g.characterAppearance);

	player->setCharacterNameAndCaption(getNameColor(g.accountRank), g.characterName, getAccountRankColor(g.accountRank), getAccountRankString(g.accountRank));
}

BobColor* BGClientEngine::getNameColor(int accountType)
{ //=========================================================================================================================
	return getAccountRankColor(accountType);
}

string BGClientEngine::getAccountRankString(int accountRank)
{ //=========================================================================================================================
	string accountRankString = "Free";
	if (accountRank == 0)
	{
		accountRankString = "Free";
	}
	if (accountRank == 1)
	{
		accountRankString = "Premium";
	}
	if (accountRank == 2)
	{
		accountRankString = "nD Dev";
	}
	if (accountRank == 3)
	{
		accountRankString = "Mod";
	}
	if (accountRank == 4)
	{
		accountRankString = "Admin";
	}
	if (accountRank == 5)
	{
		accountRankString = "Champion";
	}
	if (accountRank == 6)
	{
		accountRankString = "Legend";
	}
	if (accountRank == 7)
	{
		accountRankString = "Saint";
	}
	if (accountRank == 8)
	{
		accountRankString = "Prophet";
	}
	if (accountRank == 9)
	{
		accountRankString = "Genius";
	}
	if (accountRank == 10)
	{
		accountRankString = "Uberman";
	}
	if (accountRank == 11)
	{
		accountRankString = "Angel";
	}
	if (accountRank == 12)
	{
		accountRankString = "Christ";
	}
	if (accountRank == 13)
	{
		accountRankString = "God";
	}
	if (accountRank == 14)
	{
		accountRankString = "\"bob\"";
	}

	return accountRankString;
}

BobColor* BGClientEngine::getAccountRankColor(int accountRank)
{ //=========================================================================================================================
	BobColor* accountRankColor = BobColor::white;
	if (accountRank == 0)
	{
		accountRankColor = BobColor::white; //"Free";
	}
	if (accountRank == 1)
	{
		accountRankColor = BobColor::purple; //"Premium";
	}
	if (accountRank == 2)
	{
		accountRankColor = BobColor::blue; //"nD Dev";
	}
	if (accountRank == 3)
	{
		accountRankColor = BobColor::red; //"Mod";
	}
	if (accountRank == 4)
	{
		accountRankColor = BobColor::red; //"Admin";
	}
	if (accountRank == 5)
	{
		accountRankColor = BobColor::red; //"Champion";
	}
	if (accountRank == 6)
	{
		accountRankColor = BobColor::red; //"Legend";
	}
	if (accountRank == 7)
	{
		accountRankColor = BobColor::red; //"Saint";
	}
	if (accountRank == 8)
	{
		accountRankColor = BobColor::red; //"Prophet";
	}
	if (accountRank == 9)
	{
		accountRankColor = BobColor::red; //"Genius";
	}
	if (accountRank == 10)
	{
		accountRankColor = BobColor::red; //"Uberman";
	}
	if (accountRank == 11)
	{
		accountRankColor = BobColor::red; //"Angel";
	}
	if (accountRank == 12)
	{
		accountRankColor = BobColor::red; //"Christ";
	}
	if (accountRank == 13)
	{
		accountRankColor = BobColor::red; //"God";
	}
	if (accountRank == 14)
	{
		accountRankColor = BobColor::green; //"\"bob\"";
	}

	return accountRankColor;
}



void BGClientEngine::setPlayerToTempPlayerWithSprite(Sprite* s)
{ //=========================================================================================================================


	Player* p = new Player(this, s->getName());

	p->update();

	p->setX(player->getX());
	p->setY(player->getY());
	p->setSpawnXPixelsHQ(player->getX());
	p->setSpawnYPixelsHQ(player->getY());


	if (getCurrentMap() != nullptr)
	{
		if (getCurrentMap()->activeEntityList.contains(player))
		{
			getCurrentMap()->activeEntityList.remove(player);
			getCurrentMap()->activeEntityList.add(p);
		}
	}

	if (getCameraman() != nullptr && getCameraman()->targetEntity == player)
	{
		getCameraman()->setTarget(p);
	}

	player = p;
}

void BGClientEngine::setPlayerToNormalPlayer()
{//=========================================================================================================================

	if (getCurrentMap() != nullptr)
	{
		if (getCurrentMap()->activeEntityList.contains(player))
		{
			getCurrentMap()->activeEntityList.remove(player);
			getCurrentMap()->activeEntityList.add(normalPlayer);
		}
	}

	if (getCameraman() != nullptr && getCameraman()->targetEntity == player)
	{
		getCameraman()->setTarget(normalPlayer);
	}

	player = normalPlayer;
}



Clock* BGClientEngine::getClock()
{
	return clock;
}

GUIManager* BGClientEngine::getGUIManager()
{
	return guiManager;
}

StuffMenu* BGClientEngine::getStuffMenu()
{
	return getGUIManager()->stuffMenu;
}

GameStore* BGClientEngine::getGameStore()
{
	return getGUIManager()->gameStore;
}

PlayerEditMenu* BGClientEngine::getPlayerEditMenu()
{
	return getGUIManager()->playerEditMenu;
}

Player* BGClientEngine::getPlayer()
{
	return player;
}

ND* BGClientEngine::getND()
{
	return nD;
}

Wallet* BGClientEngine::getWallet()
{
	return wallet;
}

FriendManager* BGClientEngine::getFriendManager()
{
	return friendManager;
}

StatusBar* BGClientEngine::getStatusBar()
{
	return statusBar;
}

NotificationManager* BGClientEngine::getNotificationManager()
{
	return getStatusBar()->notificationManager;
}





bool BGClientEngine::serverMessageReceived(string e)// ChannelHandlerContext* ctx, MessageEvent* e)
{ //===============================================================================================

	if(super::serverMessageReceived(e))
	{
		return true;
	}
	else
	if (String::startsWith(e, BobNet::Load_Event_Response))
	{
		incomingLoadEventResponse(e);
		return true;
	}
	return false;

}
void BGClientEngine::sendLoadEventRequest()
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(BobNet::Load_Event_Request + BobNet::endline);
}

void BGClientEngine::incomingLoadEventResponse(string s)
{ //=========================================================================================================================

  //Event:id-name:eventData
	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::


	EventData* data = EventData::fromBase64ZippedJSON(s);

	if (data == nullptr)
	{
		log.error("Load Event could not be decompressed.");
	}
	else
	{
		Event* d = getEventManager()->getEventByIDCreateIfNotExist(data->getID());
		d->setData_S(data);

		setProjectLoadEventID_S(data->getID());

		if (data->getID() == -1)
		{
			log.error("Load eventID is -1");
		}
	}
}