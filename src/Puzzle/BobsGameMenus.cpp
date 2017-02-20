#include "stdafx.h"

#include "src/Utility/audio/AudioManager.h"

#include "stdlib.h"

#include "Room.h"

//=========================================================================================================================
void BobsGame::setupMenus()
{//=========================================================================================================================

	super::setupMenus();

	numTitleMenuTextureFrames = 25;//91; //139;//with quotes

}

bool BobsGame::updateMenus()
{ //=========================================================================================================================

	//titleMenuShowing = false;
	//customGameEditorMenuShowing = true;
	//gameSequenceEditorMenuShowing = true;
	//globalSettingsMenuShowing = true;
	//gameSetupMenuShowing = true;

	bool updatedMenu = false;

	if (super::updateMenus() == true)updatedMenu = true;

	if (startScreenMenuShowing)
	{
		startScreenMenuUpdate();
		updatedMenu = true;
	}
	if (gettingGamesFromServerMenuShowing)
	{
		gettingGamesFromServerMenuUpdate();
		updatedMenu = true;
	}

	if (controllerMenuShowing)
	{
		controllerMenuUpdate();
		updatedMenu = true;
	}

	if (localMultiplayerPlayerJoinMenuShowing)
	{
		localMultiplayerPlayerJoinMenuUpdate();
		updatedMenu = true;
	}

	if (loginMenuShowing)
	{
		loginMenuUpdate();
		updatedMenu = true;
	}

	if (createAccountMenuShowing)
	{
		createAccountMenuUpdate();
		updatedMenu = true;
	}

	if (networkMultiplayerLobbyMenuShowing)
	{
		networkMultiplayerLobbyMenuUpdate();
		updatedMenu = true;
	}

	if (networkMultiplayerPlayerJoinMenuShowing)
	{
		networkMultiplayerPlayerJoinMenuUpdate();
		updatedMenu = true;
	}

	if (customGameEditorMenuShowing)
	{
		customGameEditorMenuUpdate();
		updatedMenu = true;
	}

	if (gameSequenceEditorMenuShowing)
	{
		gameSequenceEditorMenuUpdate();
		updatedMenu = true;
	}

	if (gameTestMenuShowing)
	{
		gameTestMenuUpdate();
		updatedMenu = true;
	}

	if (globalSettingsMenuShowing)
	{
		globalSettingsMenuUpdate();
		updatedMenu = true;
	}

	if (gameSetupMenuShowing)
	{
		gameSetupMenuUpdate();
		updatedMenu = true;
	}

	if (statsMenuShowing)
	{
		statsMenuUpdate();
		updatedMenu = true;
	}

//	if (selectGameSequenceOrSingleGameTypeMenuShowing)
//	{
//		selectGameSequenceOrSingleGameTypeMenuUpdate();
//		updatedMenu = true;
//	}
//
//	if (selectGameSequenceMenuShowing)
//	{
//		selectGameSequenceMenuUpdate();
//		updatedMenu = true;
//	}
//
//	if (selectSingleGameTypeMenuShowing)
//	{
//		selectSingleGameTypeMenuUpdate();
//		updatedMenu = true;
//	}
//
//	if (difficultyMenuShowing)
//	{
//		difficultyMenuUpdate();
//		updatedMenu = true;
//	}
//
//	if (gameSequenceOptionsMenuShowing)
//	{
//		gameSequenceOptionsMenuUpdate();
//		updatedMenu = true;
//	}
//
//	if (gameObjectiveMenuShowing)
//	{
//		gameObjectiveMenuUpdate();
//		updatedMenu = true;
//	}

	if (multiplayerOptionsMenuShowing)
	{
		multiplayerOptionsMenuUpdate();
		updatedMenu = true;
	}


//	if (gameSetupMenuShowing)
//	{
//		gameSetupMenuUpdate();
//		updatedMenu = true;
//	}

	if(updatedMenu == false)unloadTitleMenuTextures();
	return updatedMenu;
}

bool BobsGame::renderMenus()
{//=========================================================================================================================

	bool renderedMenu = false;

	if (super::renderMenus() == true)renderedMenu = true;


	if (startScreenMenuShowing)
	{
		startScreenMenuRender();
		renderedMenu = true;
	}

	if (gettingGamesFromServerMenuShowing)
	{
		gettingGamesFromServerMenuRender();
		renderedMenu = true;
	}

	if (controllerMenuShowing)
	{
		controllerMenuRender();
		renderedMenu = true;
	}

	if (localMultiplayerPlayerJoinMenuShowing)
	{
		localMultiplayerPlayerJoinMenuRender();
		renderedMenu = true;
	}

	if (loginMenuShowing)
	{
		loginMenuRender();
		renderedMenu = true;
	}

	if (createAccountMenuShowing)
	{
		createAccountMenuRender();
		renderedMenu = true;
	}

	if (networkMultiplayerLobbyMenuShowing)
	{
		networkMultiplayerLobbyMenuRender();
		renderedMenu = true;
	}

	if (networkMultiplayerPlayerJoinMenuShowing)
	{
		networkMultiplayerPlayerJoinMenuRender();
		renderedMenu = true;
	}

	if (customGameEditorMenuShowing)
	{
		customGameEditorMenuRender();
		renderedMenu = true;
	}

	if (gameSequenceEditorMenuShowing)
	{
		gameSequenceEditorMenuRender();
		renderedMenu = true;
	}

	if (gameTestMenuShowing)
	{
		gameTestMenuRender();
		renderedMenu = true;
	}

	if (globalSettingsMenuShowing)
	{
		globalSettingsMenuRender();
		renderedMenu = true;
	}

	if (gameSetupMenuShowing)
	{
		gameSetupMenuRender();
		renderedMenu = true;
	}

	if (statsMenuShowing)
	{
		statsMenuRender();
		renderedMenu = true;
	}

//	if (selectGameSequenceOrSingleGameTypeMenuShowing)
//	{
//		selectGameSequenceOrSingleGameTypeMenuRender();
//		renderedMenu = true;
//	}
//
//	if (selectGameSequenceMenuShowing)
//	{
//		selectGameSequenceMenuRender();
//		renderedMenu = true;
//	}
//
//	if (selectSingleGameTypeMenuShowing)
//	{
//		selectSingleGameTypeMenuRender();
//		renderedMenu = true;
//	}
//
//	if (difficultyMenuShowing)
//	{
//		difficultyMenuRender();
//		renderedMenu = true;
//	}
//
//	if (gameSequenceOptionsMenuShowing)
//	{
//		gameSequenceOptionsMenuRender();
//		renderedMenu = true;
//	}
//
//	if (gameObjectiveMenuShowing)
//	{
//		gameObjectiveMenuRender();
//		renderedMenu = true;
//	}


	if (multiplayerOptionsMenuShowing)
	{
		multiplayerOptionsMenuRender();
		renderedMenu = true;
	}
//	if (gameSetupMenuShowing)
//	{
//		gameSetupMenuRender();
//		renderedMenu = true;
//	}
	return renderedMenu;

}


//=========================================================================================================================
void BobsGame::updateTitleMenuLogoTexture()
{//=========================================================================================================================

//	if(titleScreenTexture!= nullptr)
//	{
//		titleScreenTexture->release();
//		titleScreenTexture= nullptr;
//	}

//	string numString = ""+to_string(currentTitleScreenTextureFrame);
//	int len = numString.length();
//	for(int n=0;n<2-len;n++)numString = "0"+numString;//pad to 2 zeros

	//titleScreenTexture = GLUtils::getTextureFromPNG("data/guiBackground/logo/"+numString+".png");

	if(titleMenuTextures==nullptr)titleMenuTextures = new ArrayList<BobTexture*>();// [numTileScreenTextureFrames];
	if(titleMenuTextures->size()==0)
	{
		for (int i = 0; i<numTitleMenuTextureFrames; i++)
		{
			string numString = "" + to_string(i);
			int len = (int)numString.length();
			for (int n = 0; n<2 - len; n++)numString = "0" + numString;//pad to 2 zeros

			titleMenuTextures->add(GLUtils::getTextureFromPNG("data/guiBackground/logo/" + numString + ".png"));
		}
	}
}


void BobsGame::titleMenuUpdate()
{ //=========================================================================================================================


	if (titleMenu == nullptr)
	{
		titleMenu = new BobMenu(this, "");
		titleMenu->spacing = 1.2f;

		titleMenu->addInfo("Connecting to server...","Login");
		titleMenu->add("Play Offline");
		titleMenu->add("Exit Game");

		titleMenu->cursorPosition = titleMenuCursorPosition;
	}

	bool leaveMenu = false;

	if (getServerConnection()->getConnectedToServer_S())
	{
		if(FileUtils::readSessionTokenFromCache()!="")
		{
			titleMenu->getMenuItemByID("Login")->setText("Logging in...");
			titleMenu->getMenuItemByID("Login")->info = true;
		}
		else
		{
			titleMenu->getMenuItemByID("Login")->setText("Login Or Create Account");
			titleMenu->getMenuItemByID("Login")->info = false;
		}

		if (getServerConnection()->getAuthorizedOnServer_S())
		{
			leaveMenu = true;
			startScreenMenuShowing = true;
		}
	}

	if (getControlsManager()->miniGame_UP_Pressed())
	{
		titleMenu->up();
	}

	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		titleMenu->down();
	}

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();

	if (confirm || clicked)
	{

		if (titleMenu->isSelectedID("Login", clicked, mx, my))
		{
			loginMenuShowing = true;
			leaveMenu = true;
		}

		if (titleMenu->isSelectedID("Play Offline", clicked, mx, my))
		{
			startScreenMenuShowing = true;
			leaveMenu = true;
		}

		if (titleMenu->isSelectedID("Exit Game", clicked, mx, my))
		{
			Main::quit = true;
		}
	}

	if (leaveMenu)
	{
		titleMenuShowing = false;

		if (titleMenu != nullptr)
		{
			titleMenuCursorPosition = titleMenu->cursorPosition;
			delete titleMenu;
			titleMenu = nullptr;
		}
	}
}


void BobsGame::titleMenuRender()
{ //=========================================================================================================================

	GLUtils::drawFilledRect(255, 255, 255, 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);


	BobTexture *t = nullptr;

	if (titleMenuTextures != nullptr && titleMenuTextures->size()>0)t = titleMenuTextures->get(currentTitleMenuTextureFrame);
	if (titleMenuTexture != nullptr)t = titleMenuTexture;

	if (titleMenu == nullptr)return;

	if (t != nullptr)
	{
		titleMenu->setGraphic(t, getWidth() / 3*2, getHeight() / 7);
		titleMenu->render();
	}

}


void BobsGame::startScreenMenuUpdate()
{ //=========================================================================================================================

	titleMenuFrameTicks += super::engineTicksPassed();
	if (titleMenuFrameTicks > 20)
	{
		titleMenuFrameTicks = 0;
		currentTitleMenuTextureFrame++;
		if (currentTitleMenuTextureFrame >= numTitleMenuTextureFrames)
		{
			currentTitleMenuTextureFrame = 0;
		}

		updateTitleMenuLogoTexture();
	}

	if (startScreenMenu == nullptr)
	{
		startScreenMenu = new BobMenu(this, "");
		startScreenMenu->spacing = 1.2f;
		//pressEnterCaption = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, y-60, -1, "Press Enter to begin", BobFont::ttf_oswald_24, infoColor, clearColor, RenderOrder::OVER_GUI);
		//pressEnterCaption->flashing = true;
		//pressEnterCaption->flashingTicksPerFlash = 3000;

		startScreenMenu->add("Single Player");
		startScreenMenu->add("Local Multiplayer");
		startScreenMenu->add("Online Multiplayer","", BobMenu::disabledMenuColor);
		startScreenMenu->add("Stats And Leaderboards","Stats", BobMenu::disabledMenuColor);
		startScreenMenu->add("Vote On New Games", "", BobMenu::disabledMenuColor);
		startScreenMenu->add("Custom Game Editor");
		startScreenMenu->add("Game Sequence Creator");
		startScreenMenu->add("Global Settings");
		startScreenMenu->add("Controller Test");
		//startScreenMenu->add("Report Bug");
		//startScreenMenu->add("Support On Patreon", "Donate");
		startScreenMenu->add("Exit Game");

		startScreenMenu->cursorPosition = startScreenMenuCursorPosition;
	}


	if (infoMenu == nullptr)
	{
		infoMenu = new BobMenu(this, "");
		infoMenu->center = false;
		infoMenu->font = BobFont::ttf_oswald_10;
		infoMenu->addInfo("Build " + Main::version + " " + __TIMESTAMP__);// +" - Support this game: ", "Build Number");
		infoMenu->addInfo("This game is actively developed by one person for free and will have bugs.  I rely on your feedback.");
		infoMenu->addInfo("Please report problems or crashes to bugs@bobsgame.com or ", "Open Forum");
		infoMenu->addInfo("If there are no games the server might be overloaded, wait a bit or restart a few times.");
		infoMenu->addInfo("Currently working on: Android/iOS ports.");
	}



//	if (patreonMenu == nullptr)
//	{
//		patreonMenu = new BobMenu(this, "");
//		patreonMenu->center = false;
//		patreonMenu->font = BobFont::ttf_oswald_10;
//		patreonMenu->addInfo("https://patreon.com/bobsgame", "Patreon", BobColor::lightBlue);
//	}



	if (forumMenu == nullptr)
	{
		forumMenu = new BobMenu(this, "");
		forumMenu->center = false;
		forumMenu->font = BobFont::ttf_oswald_10;
		forumMenu->addInfo("https://bobsgame.com/forum", "Open Forum",BobColor::lightBlue);
	}

	if(getServerConnection()->getConnectedToServer_S())
	{
		startScreenMenu->getMenuItemByID("Online Multiplayer")->setColor(BobMenu::menuColor);
		startScreenMenu->getMenuItemByID("Online Multiplayer")->info = false;

		startScreenMenu->getMenuItemByID("Stats")->setColor(BobMenu::menuColor);
		startScreenMenu->getMenuItemByID("Stats")->info = false;

		startScreenMenu->getMenuItemByID("Vote On New Games")->setColor(BobMenu::menuColor);
		startScreenMenu->getMenuItemByID("Vote On New Games")->info = false;
	}
	else
	{
		startScreenMenu->getMenuItemByID("Online Multiplayer")->info = true;
		startScreenMenu->getMenuItemByID("Vote On New Games")->info = true;
	}

	if (getControlsManager()->miniGame_UP_Pressed())
	{
		startScreenMenu->up();
	}

	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		startScreenMenu->down();
	}

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{

		bool leaveMenu = false;

		if (startScreenMenu->isSelectedID("Single Player", clicked, mx, my))
		{
			localMultiplayer = false;
			networkMultiplayer = false;
			gameSetupMenuShowing = true;
			leaveMenu = true;
		}
		if (startScreenMenu->isSelectedID("Local Multiplayer", clicked, mx, my))
		{
			localMultiplayer = true;
			networkMultiplayer = false;
			multiplayerOptionsMenuShowing = true;
			leaveMenu = true;
		}

		if (startScreenMenu->isSelectedID("Online Multiplayer", clicked, mx, my))
		{
			if (getServerConnection()->getConnectedToServer_S())
			{
				localMultiplayer = false;
				networkMultiplayer = true;
				loginMenuShowing = true;
				leaveMenu = true;
			}
		}

		if (startScreenMenu->isSelectedID("Stats", clicked, mx, my))
		{
			if (getServerConnection()->getConnectedToServer_S())
			{
				statsMenuShowing = true;
				leaveMenu = true;
			}
		}

		if (startScreenMenu->isSelectedID("Vote On New Games", clicked, mx, my))
		{
			if (getServerConnection()->getConnectedToServer_S())
			{
				gameTestMenuShowing = true;
				leaveMenu = true;
			}
		}

		if (startScreenMenu->isSelectedID("Custom Game Editor", clicked, mx, my))
		{
			customGameEditorMenuShowing = true;
			leaveMenu = true;
		}

		if (startScreenMenu->isSelectedID("Game Sequence Creator", clicked, mx, my))
		{
			gameSequenceEditorMenuShowing = true;
			leaveMenu = true;
		}

		if (startScreenMenu->isSelectedID("Global Settings", clicked, mx, my))
		{
			globalSettingsMenuShowing = true;
			leaveMenu = true;
		}

		if (startScreenMenu->isSelectedID("Controller Test", clicked, mx, my))
		{
			controllerMenuShowing = true;
			leaveMenu = true;
		}

		if (startScreenMenu->isSelectedID("Exit Game", clicked, mx, my))
		{
			Main::quit = true;
		}

		if (confirm == false && clicked == true)
		{
			if (patreonMenu!=nullptr && patreonMenu->isSelectedID("Patreon", clicked, mx, my))
			{
				Main::openURL("https://www.patreon.com/bobsgame");
			}

			if (forumMenu!=nullptr && forumMenu->isSelectedID("Open Forum", clicked, mx, my))
			{
				Main::openURL("https://www.bobsgame.com/forum");
			}
		}

		if (leaveMenu)
		{
			startScreenMenuShowing = false;

			if(startScreenMenu!=nullptr)
			{
				startScreenMenuCursorPosition = startScreenMenu->cursorPosition;
				delete startScreenMenu;
				startScreenMenu = nullptr;
			}
			if (infoMenu != nullptr)
			{
				delete infoMenu;
				infoMenu = nullptr;
			}
			if (patreonMenu != nullptr)
			{
				delete patreonMenu;
				patreonMenu = nullptr;
			}
			if (forumMenu != nullptr)
			{
				delete forumMenu;
				forumMenu = nullptr;
			}
		}
	}
}


void BobsGame::startScreenMenuRender()
{ //=========================================================================================================================

	GLUtils::drawFilledRect(255,255,255, 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);


	BobTexture *t = nullptr;

	if (titleMenuTextures != nullptr && titleMenuTextures->size()>0)t = titleMenuTextures->get(currentTitleMenuTextureFrame);
	if (titleMenuTexture != nullptr)t = titleMenuTexture;
	
	if (startScreenMenu == nullptr)return;

	if (t != nullptr)
	{
		startScreenMenu->setGraphic(t, getWidth()/3*2, getHeight() / 7);
		startScreenMenu->render();
	}

	infoMenu->render(0, 6);// getHeight() - (infoMenu->getAmountOfMenuItems() * 20), 10);

	if(patreonMenu!=nullptr)
	{
		Caption *c = infoMenu->getMenuItemByID("Build Number")->caption;
		int x = c->screenX + c->getWidth();
		int y = c->screenY;
		patreonMenu->render(y, x);
	}

	if(forumMenu!=nullptr)
	{
		Caption *c = infoMenu->getMenuItemByID("Open Forum")->caption;
		int x = x = c->screenX + c->getWidth();
		int y = y = c->screenY;
		forumMenu->render(y, x);
	}
}

void BobsGame::gettingGamesFromServerMenuUpdate()
{ //=========================================================================================================================

	titleMenuFrameTicks += super::engineTicksPassed();
	if (titleMenuFrameTicks > 20)
	{
		titleMenuFrameTicks = 0;
		currentTitleMenuTextureFrame++;
		if (currentTitleMenuTextureFrame >= numTitleMenuTextureFrames)
		{
			currentTitleMenuTextureFrame = 0;
		}

		updateTitleMenuLogoTexture();
	}

	if (gettingGamesFromServerMenu == nullptr)
	{
		gettingGamesFromServerMenu = new BobMenu(this, "");
		gettingGamesFromServerMenu->spacing = 1.2f;
		gettingGamesFromServerMenu->addInfo("Downloading games from server...","Downloading");
	}

	long long currentTime = System::currentHighResTimer();
	long long startTime = gettingGamesFromServerDotsTime;
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	if (ticksPassed > 300)
	{
		gettingGamesFromServerDotsTime = currentTime;
		gettingGamesFromServerCount++;
		gettingGamesFromServerMenu->getCaptionByID("Downloading")->setText("Downloading games from server" + cycleDots(gettingGamesFromServerCount));
	}
	
	
}


void BobsGame::gettingGamesFromServerMenuRender()
{ //=========================================================================================================================

	GLUtils::drawFilledRect(255,255,255, 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);


	BobTexture *t = nullptr;

	if (titleMenuTextures != nullptr && titleMenuTextures->size()>0)t = titleMenuTextures->get(currentTitleMenuTextureFrame);
	if (titleMenuTexture != nullptr)t = titleMenuTexture;
	
	if (gettingGamesFromServerMenu == nullptr)return;

	if (t != nullptr)
	{
		gettingGamesFromServerMenu->setGraphic(t, getWidth()/3*2, getHeight() / 7);
		gettingGamesFromServerMenu->render();
	}

}


void BobsGame::decreaseVolume()
{//=========================================================================================================================
	if (globalSettings->musicVolume > 0)globalSettings->musicVolume -= 1;
	if (globalSettings->musicVolume < 0)globalSettings->musicVolume = 0;
	music->setVolume(((float)globalSettings->musicVolume / 100.0f));
}


void BobsGame::increaseVolume()
{//=========================================================================================================================
	if (globalSettings->musicVolume < 100)globalSettings->musicVolume += 1;
	if (globalSettings->musicVolume > 100)globalSettings->musicVolume = 100;
	music->setVolume(((float)globalSettings->musicVolume / 100.0f));
}


//=========================================================================================================================
void BobsGame::pauseMenuUpdate()
{//=========================================================================================================================

	if(pauseMenu == nullptr)
	{
		pauseMenu = new BobMenu(this,"Paused");

		pauseMenu->add("Back To Game", "Back To Game");
		settingsMenuInit(pauseMenu);
		pauseMenu->add("Quit Game And Return To Title Screen","Quit Game And Return To Title Screen");

		pauseMenu->cursorPosition = pauseMenuCursorPosition;
	}
	

	if(getControlsManager()->miniGame_UP_Pressed())
	{
		pauseMenu->up();
	}

	if(getControlsManager()->miniGame_DOWN_Pressed())
	{
		pauseMenu->down();
	}

	

	if (getControlsManager()->MINIGAME_LEFT_HELD)
	{
		settingsMenuLeft(pauseMenu);
	}
	if (getControlsManager()->MINIGAME_RIGHT_HELD)
	{
		settingsMenuRight(pauseMenu);
	}


	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{

		if (pauseMenu->isSelectedID("Defaults", clicked, mx, my))
		{
			settingsMenuConfirm(pauseMenu);
		}

		if(pauseMenu->isSelectedID("Back To Game", clicked, mx, my))
		{
			leaveMenu = true;
		}

		if (pauseMenu->isSelectedID("Quit Game And Return To Title Screen", clicked, mx, my))
		{
			leaveMenu = true;
			startScreenMenuShowing = true;
			initPlayer();
		}

	}

	if (getControlsManager()->miniGame_CANCEL_Pressed())
	{
		leaveMenu = true;
	}

	if(leaveMenu)
	{
		pauseMenuShowing = false;

		if (pauseMenu != nullptr)
		{
			pauseMenuCursorPosition = pauseMenu->cursorPosition;
			delete pauseMenu;
			pauseMenu = nullptr;
		}
	}
}


//=========================================================================================================================
void BobsGame::pauseMenuRender()
{//=========================================================================================================================

//	if (pauseMenu != nullptr)
//	{
//		if(
//			pauseMenu->isSelectedID("Brightness") == false &&
//			pauseMenu->isSelectedID("Contrast") == false &&
//			pauseMenu->isSelectedID("Saturation") == false
//		)
//		{
//			GLUtils::drawFilledRect(255, 255, 255, 0, (float)getWidth(), 0, (float)getHeight(), 0.7f);
//		}
//	}

	BobTexture* t = keyboardTexture;

	if (pauseMenu == nullptr)return;

	if (t != nullptr)
	{
		pauseMenu->setGraphic(t, getWidth() / 8 * 5, getHeight() / 8);
	}

	pauseMenu->render(0, 0, getHeight(), true, nullptr, nullptr, true);
}



//=========================================================================================================================
void BobsGame::controllerMenuUpdate()
{//=========================================================================================================================

	if (controllerMenu == nullptr)
	{

		//Game controllers are automatically detected.
		//Test your buttons here, press Esc to stop.
		//If your controller was not detected, you can create a new mapping for it.
		//This will be saved to disk and loaded automatically.

		//Test controls
		//Testing... Press Esc to stop.
		//Create custom mapping

		controllerMenu = new BobMenu(this, "Controller Test");
		controllerMenu->addInfo("Game controllers should be automatically detected.");
		controllerMenu->addInfo("If your controller does not work, try downloading x360ce.");
		controllerMenu->addInfo("If it still does not work, please report to bugs@bobsgame.com");
		controllerMenu->addInfo(" ");
		controllerMenu->add("Test detected button mapping");
		controllerMenu->add("Return to Title Screen");
		controllerMenu->addInfo(" ", "Testing Caption");
		controllerMenu->addInfo(" ", "Button Press Caption");

		controllerMenu->cursorPosition = controllerMenuCursorPosition;
	}
	


	if(controllerMenuTestingButtons)
	{
		controllerMenu->getMenuItemByID("Testing Caption")->setColor(BobColor::lightGreen);
		controllerMenu->getMenuItemByID("Testing Caption")->setText("Testing buttons... Press Esc key or hold Start and Select on controller to stop");

		BobMenu::MenuItem *m = controllerMenu->getMenuItemByID("Button Press Caption");
		Caption *c = controllerMenu->getCaptionByID("Button Press Caption");

		for (int i = 0; i < getControlsManager()->gameControllers.size(); i++)
		{
			GameController *g = getControlsManager()->gameControllers.get(i);

			m->setColor(BobColor::lightRed);

			if (g->up_Pressed())c->setText("Controller "+to_string(i)+" Up Pressed");
			if (g->down_Pressed())c->setText("Controller " + to_string(i) + " Down Pressed");
			if (g->left_Pressed())c->setText("Controller " + to_string(i) + " Left Pressed");
			if (g->right_Pressed())c->setText("Controller " + to_string(i) + " Right Pressed");
			if (g->b_Pressed())c->setText("Controller " + to_string(i) + " B Pressed");
			if (g->a_Pressed())c->setText("Controller " + to_string(i) + " A Pressed");
			if (g->x_Pressed())c->setText("Controller " + to_string(i) + " X Pressed");
			if (g->y_Pressed())c->setText("Controller " + to_string(i) + " Y Pressed");
			if (g->start_Pressed())c->setText("Controller " + to_string(i) + " Start Pressed");
			if (g->select_Pressed())c->setText("Controller " + to_string(i) + " Select Pressed");
			if (g->l_Pressed())c->setText("Controller " + to_string(i) + " L Pressed");
			if (g->r_Pressed())c->setText("Controller " + to_string(i) + " R Pressed");
		}

		if (getControlsManager()->key_ESC_Pressed() || (getControlsManager()->MINIGAME_START_HELD && getControlsManager()->MINIGAME_SELECT_HELD))
			controllerMenuTestingButtons = false;

	}
	else
	{
		controllerMenu->getMenuItemByID("Testing Caption")->setText(" ");
		controllerMenu->getMenuItemByID("Button Press Caption")->setText(" ");

		if (getControlsManager()->miniGame_UP_Pressed())
		{
			controllerMenu->up();
		}

		if (getControlsManager()->miniGame_DOWN_Pressed())
		{
			controllerMenu->down();
		}


		bool leaveMenu = false;

		bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
		bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
		int mx = getControlsManager()->getMouseX();
		int my = getControlsManager()->getMouseY();

		if (confirm || clicked)
		{

			if (controllerMenu->isSelectedID("Test detected button mapping", clicked, mx, my))
			{
				//testing
				controllerMenuTestingButtons = true;
			}
			if (controllerMenu->isSelectedID("Return to Title Screen", clicked, mx, my))
			{
				startScreenMenuShowing = true;
				leaveMenu = true;
			}
		}

		if(getControlsManager()->miniGame_CANCEL_Pressed())
		{
			startScreenMenuShowing = true;
			leaveMenu = true;
		}

		if(leaveMenu)
		{
			controllerMenuShowing = false;

			if (controllerMenu != nullptr)
			{
				controllerMenuCursorPosition = controllerMenu->cursorPosition;
				delete controllerMenu;
				controllerMenu = nullptr;
			}
		}
	}
}


//=========================================================================================================================
void BobsGame::controllerMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(BobMenu::bgColor->ri(), BobMenu::bgColor->gi(), BobMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	BobTexture* t = controllerTexture;

	if (controllerMenu == nullptr)return;

	if (t != nullptr)
	{
		controllerMenu->setGraphic(t, getWidth() / 3 * 1, getHeight() / 8);
	}

	controllerMenu->render();
}



//=========================================================================================================================
void BobsGame::playerPauseMiniMenuUpdate(PuzzlePlayer *p)
{//=========================================================================================================================

	if (p != nullptr)
	{
		if (p->menu == nullptr)
		{
			p->menu = new BobMenu(this, "");

			p->menu->add("Back To Game", "Back To Game", BobColor::white);
			settingsMenuInit(p->menu);
			p->menu->add("Forfeit", "Forfeit", BobColor::white);
		}

		if (p->upPressed())
		{
			p->menu->up();
		}

		if (p->downPressed())
		{
			p->menu->down();
		}

		if (p->LEFT_HELD)
		{
			settingsMenuLeft(p->menu);
		}
		if (p->RIGHT_HELD)
		{
			settingsMenuRight(p->menu);
		}

		bool leaveMenu = false;
		//bool deletePlayer = false;


		if (p->confirmPressed())
		{

			if (p->menu->isSelectedID("Defaults"))
			{
				settingsMenuConfirm(p->menu);
			}

			if (p->menu->isSelectedID("Back To Game"))
			{
				leaveMenu = true;
			}


			if (p->menu->isSelectedID("Forfeit"))
			{
				//if (isMultiplayer())
				{
					if (isNetworkGame())
					{
						tellAllPeersOneOfMyPlayersForfeitsGame(p);
					}

					p->gameLogic->died = true;
					//players.remove(p);
					//deletePlayer = true;

					bool allLocalPlayersDead = true;
					for (int i = 0; i < players.size(); i++)
					{
						PuzzlePlayer *o = players.get(i);
						if (o->isNetworkPlayer() == false && o->gameLogic->died==false)allLocalPlayersDead = false;
					}

					if (allLocalPlayersDead)
					{
						if (isNetworkGame())
						{

							if (hosting)
							{
								//send to all friends disconnected
								tellAllPeersIAmNotHosting();	
							}

							tellAllJoinedPeersIHaveLeftTheGame();

							BobNet::myStatus = BobNet::status_AVAILABLE;
							joinedPeers->clear();
							networkMultiplayerLobbyMenuShowing = true;
						}
						else
						{
							localMultiplayerPlayerJoinMenuShowing = true;
						}

						
						initPlayer();
					}
					leaveMenu = true;
				}
			}
		}

		if (p->cancelPressed())
		{
			leaveMenu = true;
		}

		if (leaveMenu)
		{
			if (p->menu != nullptr)
			{
				delete p->menu;
				p->menu = nullptr;
			}
			p->gameLogic->pauseMiniMenuShowing = false;

//			if(deletePlayer)
//			{
//				delete p;
//				return false;
//			}
//			return true;
		}
	}
	//return true;
}

//=========================================================================================================================
void BobsGame::playerPauseMiniMenuRender(PuzzlePlayer *p, float x0, float x1, float y0, float y1)
{//=========================================================================================================================

	//GLUtils::drawFilledRect(255,255,255, x0,x1,y0,y1, 0.7f);

	if (p->menu != nullptr)
	{
		p->menu->render((int)(y0+((y1-y0)/2)), (int)(x0 + ((x1 - x0) / 2)),getHeight(),true,nullptr,nullptr,true);
	}
}

//=========================================================================================================================
void BobsGame::loginMenuUpdate()
{//=========================================================================================================================


	//log in
	//save login
	//create account

	int y = (int)(getHeight() / 4 * 3);

	if (statusLabel == nullptr)statusLabel = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, y, -1, " ", BobFont::ttf_oswald_16, BobMenu::statusColor, BobMenu::clearColor, RenderOrder::OVER_GUI);
	if (errorLabel == nullptr)errorLabel = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, y, -1, " ", BobFont::ttf_oswald_16, BobMenu::errorColor, BobMenu::clearColor, RenderOrder::OVER_GUI);


	if (loginMenu == nullptr)
	{
		loginMenu = new BobMenu(this, "Login");
		//loginMenu->center = false;
		loginMenu->add("Username or Email: " + userNameOrEmailText,"Username or Email", BobMenu::statusColor);
		loginMenu->add("Password: " + passwordStarsText, "Password", BobMenu::statusColor);
		loginMenu->add("Stay logged in: Yes", "Stay logged in");
		loginMenu->add("Log in");
		loginMenu->add("Create new account");
		loginMenu->add("Forgot password");
		loginMenu->add("Return to title screen");

		loginMenu->cursorPosition = loginMenuCursorPosition;
	}

	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();

	if (mx != lastMX || my != lastMY)
	{
		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
		lastMX = mx;
		lastMY = my;
	}

	if (getControlsManager()->miniGame_UP_Pressed())
	{
		loginMenu->up();

		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
	}

	if (getControlsManager()->miniGame_DOWN_Pressed() || getControlsManager()->key_TAB_Pressed())
	{
		loginMenu->down();

		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
	}

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();

	if (confirm || clicked || (getControlsManager()->miniGame_LEFT_Pressed() || getControlsManager()->miniGame_RIGHT_Pressed()))
	{
		if (loginMenu->isSelectedID("Stay logged in", clicked, mx, my))
		{
			stayLoggedIn = !stayLoggedIn;

			if (stayLoggedIn)loginMenu->getMenuItemByID("Stay logged in")->setText("Stay logged in: Yes");
			else loginMenu->getMenuItemByID("Stay logged in")->setText("Stay logged in: No");

		}
	}

	if (loginMenu->isSelectedID("Username or Email"))
	{
		if (!textStarted) { SDL_StartTextInput(); getControlsManager()->text = userNameOrEmailText; textStarted = true;}
		userNameOrEmailText = getControlsManager()->text;
		loginMenu->getMenuItemByID("Username or Email")->setText("Username or Email: " + userNameOrEmailText);
	}

	if (loginMenu->isSelectedID("Password"))
	{
		if (!textStarted) { SDL_StartTextInput(); getControlsManager()->text = passwordText; textStarted = true; }
		passwordText = getControlsManager()->text;
		passwordStarsText = "";
		for (int i = 0; i < (int)passwordText.length(); i++)passwordStarsText += "*";
		loginMenu->getMenuItemByID("Password")->setText("Password: " + passwordStarsText);
	}

	bool leaveMenu = false;


	if (confirm || clicked)
	{

		if (loginMenu->isSelectedID("Log in", clicked, mx, my) || loginMenu->isSelectedID("Password", clicked, mx, my))
		{
			getServerConnection()->doLogin(statusLabel, errorLabel,userNameOrEmailText,passwordText,stayLoggedIn);
		}

		if (loginMenu->isSelectedID("Create new account", clicked, mx, my))
		{
			leaveMenu = true;
			createAccountMenuShowing = true;
		}

		if (loginMenu->isSelectedID("Forgot password", clicked, mx, my))
		{
			getServerConnection()->doForgotPassword(statusLabel,errorLabel,userNameOrEmailText);
		}

		if (loginMenu->isSelectedID("Return to title screen", clicked, mx, my))
		{
			//back to title screen
			leaveMenu = true;
			titleMenuShowing = true;
		}

	}


	if (getServerConnection()->getAuthorizedOnServer_S())
	{
		leaveMenu = true;
		if (networkMultiplayer)networkMultiplayerLobbyMenuShowing = true;
		else startScreenMenuShowing = true;
	}

	if (getControlsManager()->key_ESC_Pressed() || getControlsManager()->miniGame_SELECT_Pressed())
	{
		leaveMenu = true;
		startScreenMenuShowing = true;
	}

	if (leaveMenu)
	{
		loginMenuShowing = false;

		if (loginMenu != nullptr)
		{
			loginMenuCursorPosition = loginMenu->cursorPosition;
			delete loginMenu;
			loginMenu = nullptr;
		}

		if (statusLabel != nullptr)
		{
			statusLabel->setToBeDeletedImmediately();
			statusLabel = nullptr;
		}

		if (errorLabel != nullptr)
		{
			errorLabel->setToBeDeletedImmediately();
			errorLabel = nullptr;
		}
	}

}



//=========================================================================================================================
void BobsGame::loginMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(BobMenu::bgColor->ri(), BobMenu::bgColor->gi(), BobMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	BobTexture* t = onlineTexture;

	if (loginMenu == nullptr)return;

	if (t != nullptr)
	{
		loginMenu->setGraphic(t, getWidth() / 8 * 4, 100);
	}


	if (statusLabel != nullptr && errorLabel != nullptr)
	{
		errorLabel->screenY = (float)(getHeight() / 4 * 3);
		statusLabel->screenY = (float)((getHeight() / 4 * 3) + 24);
	}

	loginMenu->render();
}


//=========================================================================================================================
void BobsGame::createAccountMenuUpdate()
{//=========================================================================================================================

	if (createAccountMenu == nullptr)
	{
		int y = (int)(getHeight() / 4 * 3);

		if (statusLabel == nullptr)statusLabel = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, y, -1, " ", BobFont::ttf_oswald_16, BobMenu::statusColor, BobMenu::clearColor, RenderOrder::OVER_GUI);
		if (errorLabel == nullptr)errorLabel = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, y, -1, " ", BobFont::ttf_oswald_16, BobMenu::errorColor, BobMenu::clearColor, RenderOrder::OVER_GUI);

		if (userNameOrEmailText.length()>0)
		{
			if (userNameOrEmailText.find("@") != string::npos)
				emailText = userNameOrEmailText;
			else
				userNameText = userNameOrEmailText;
		}

		createAccountMenu = new BobMenu(this, "Create Account");
		//createAccountMenu->center = false;
		createAccountMenu->add("Username: " + userNameText, "Username");
		createAccountMenu->add("Email: " + emailText, "Email");
		createAccountMenu->add("Password: " + passwordStarsText, "Password");
		createAccountMenu->add("Confirm: " + confirmPasswordStarsText, "Confirm");
		createAccountMenu->add("Create account");
		createAccountMenu->add("Return to login screen");
	}
	
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();

	if(mx!=lastMX || my !=lastMY)
	{
		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
		lastMX = mx;
		lastMY = my;
	}

	if (getControlsManager()->miniGame_UP_Pressed())
	{
		createAccountMenu->up();

		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
	}

	if (getControlsManager()->miniGame_DOWN_Pressed() || getControlsManager()->key_TAB_Pressed())
	{
		createAccountMenu->down();

		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
	}


	if (createAccountMenu->isSelectedID("Username"))
	{
		if (!textStarted) { SDL_StartTextInput(); getControlsManager()->text = userNameText; textStarted = true; }
		userNameText = getControlsManager()->text;
		createAccountMenu->getMenuItemByID("Username")->setText("Username: " + userNameText);
	}

	if (createAccountMenu->isSelectedID("Email"))
	{
		if (!textStarted) { SDL_StartTextInput(); getControlsManager()->text = emailText; textStarted = true; }
		emailText = getControlsManager()->text;
		createAccountMenu->getMenuItemByID("Email")->setText("Email: " + emailText);
	}

	if (createAccountMenu->isSelectedID("Password"))
	{
		if (!textStarted) { SDL_StartTextInput(); getControlsManager()->text = passwordText; textStarted = true; }
		passwordText = getControlsManager()->text;
		passwordStarsText = "";
		for (int i = 0; i < (int)passwordText.length(); i++)passwordStarsText += "*";
		createAccountMenu->getMenuItemByID("Password")->setText("Password: " + passwordStarsText);
	}

	if (createAccountMenu->isSelectedID("Confirm"))
	{
		if (!textStarted) { SDL_StartTextInput(); getControlsManager()->text = confirmPasswordText; textStarted = true; }
		confirmPasswordText = getControlsManager()->text;
		confirmPasswordStarsText = "";
		for (int i = 0; i < (int)confirmPasswordText.length(); i++)confirmPasswordStarsText += "*";
		createAccountMenu->getMenuItemByID("Confirm")->setText("Confirm: " + confirmPasswordStarsText);
	}

	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();

	if (confirm || clicked)
	{
		if (createAccountMenu->isSelectedID("Create account", clicked, mx, my))
		{
			if(getServerConnection()->doCreateAccount(statusLabel,errorLabel,userNameText,emailText,passwordText,confirmPasswordText)==true)
			{
				leaveMenu = true;
				loginMenuShowing = true;
			}
		}

		if (createAccountMenu->isSelectedID("Return to login screen", clicked, mx, my))
		{
			//back to title screen
			leaveMenu = true;
			loginMenuShowing = true;
		}
	}


	if (getControlsManager()->key_ESC_Pressed() || getControlsManager()->miniGame_SELECT_Pressed())
	{
		leaveMenu = true;
		loginMenuShowing = true;
	}

	if (leaveMenu)
	{
		createAccountMenuShowing = false;

		if(createAccountMenu != nullptr)
		{
			delete createAccountMenu;
			createAccountMenu = nullptr;
		}

		if (statusLabel != nullptr)
		{
			statusLabel->setToBeDeletedImmediately();
			statusLabel = nullptr;
		}

		if (errorLabel != nullptr)
		{
			errorLabel->setToBeDeletedImmediately();
			errorLabel = nullptr;
		}
	}

}



//=========================================================================================================================
void BobsGame::createAccountMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(BobMenu::bgColor->ri(), BobMenu::bgColor->gi(), BobMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	BobTexture* t = onlineTexture;

	if (createAccountMenu == nullptr)return;

	if (t != nullptr)
	{
		createAccountMenu->setGraphic(t, getWidth() / 8 * 4, 20);
	}

	if (statusLabel != nullptr && errorLabel != nullptr)
	{
		errorLabel->screenY = (float)(getHeight() / 4 * 3);
		statusLabel->screenY = (float)((getHeight() / 4 * 3) + 24);
	}

	createAccountMenu->render();

}


//=========================================================================================================================
void BobsGame::settingsMenuInit(BobMenu* m)
{//=========================================================================================================================
	m->add("Music Volume: " + to_string((int)(music->getVolume() * 100)) + "%", "Music Volume");
	m->add("Brightness: " + to_string((int)(globalSettings->brightness * 100)) + "%", "Brightness");
	m->add("Contrast: " + to_string((int)(globalSettings->contrast * 100)) + "%", "Contrast");
	m->add("Saturation: " + to_string((int)(globalSettings->saturation * 100)) + "%", "Saturation");
	//m->add("Hue Shift: " + to_string((int)(globalSettings->hue * 100)) + "%", "Hue Shift");
	m->add("Defaults");
}

//=========================================================================================================================
void BobsGame::settingsMenuLeft(BobMenu* m)
{//=========================================================================================================================
	if (m->isSelectedID("Music Volume"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			decreaseVolume();
			m->getMenuItemByID("Music Volume")->setText("Music Volume: " + to_string((int)(music->getVolume() * 100)) + "%");
		}
	}

	if (m->isSelectedID("Brightness"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			if (globalSettings->brightness > 0)globalSettings->brightness -= 0.01f;
			if (globalSettings->brightness < 0)globalSettings->brightness = 0;
			m->getMenuItemByID("Brightness")->setText("Brightness: " + to_string((int)(globalSettings->brightness * 100)) + "%");
		}
	}

	if (m->isSelectedID("Contrast"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			if (globalSettings->contrast > 0)globalSettings->contrast -= 0.01f;
			if (globalSettings->contrast < 0)globalSettings->contrast = 0;
			m->getMenuItemByID("Contrast")->setText("Contrast: " + to_string((int)(globalSettings->contrast * 100)) + "%");
		}
	}

	if (m->isSelectedID("Saturation"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			if (globalSettings->saturation > 0)globalSettings->saturation -= 0.01f;
			if (globalSettings->saturation < 0)globalSettings->saturation = 0;
			m->getMenuItemByID("Saturation")->setText("Saturation: " + to_string((int)(globalSettings->saturation * 100)) + "%");
		}
	}
//
//	if (m->isSelectedID("Hue Shift"))
//	{
//		long long startTime = timeLastChangedSetting;
//		long long currentTime = System::currentHighResTimer();
//		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
//
//		if (ticksPassed > 15)
//		{
//			timeLastChangedSetting = currentTime;
//			if (globalSettings->hue > 0)globalSettings->hue -= 0.01f;
//			if (globalSettings->hue < 0)globalSettings->hue = 0;
//			m->getMenuItemByID("Hue Shift")->setText("Hue Shift: " + to_string((int)(globalSettings->hue * 100)) + "%");
//		}
//	}
}


//=========================================================================================================================
void BobsGame::settingsMenuRight(BobMenu* m)
{//=========================================================================================================================
	if (m->isSelectedID("Music Volume"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			increaseVolume();
			m->getMenuItemByID("Music Volume")->setText("Music Volume: " + to_string((int)(music->getVolume() * 100)) + "%");
		}
	}
	if (m->isSelectedID("Brightness"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			if (globalSettings->brightness < 2)globalSettings->brightness += 0.01f;
			if (globalSettings->brightness > 2)globalSettings->brightness = 2;
			m->getMenuItemByID("Brightness")->setText("Brightness: " + to_string((int)(globalSettings->brightness * 100)) + "%");
		}
	}

	if (m->isSelectedID("Contrast"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			if (globalSettings->contrast < 2)globalSettings->contrast += 0.01f;
			if (globalSettings->contrast > 2)globalSettings->contrast = 2;
			m->getMenuItemByID("Contrast")->setText("Contrast: " + to_string((int)(globalSettings->contrast * 100)) + "%");
		}
	}

	if (m->isSelectedID("Saturation"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			if (globalSettings->saturation < 2)globalSettings->saturation += 0.01f;
			if (globalSettings->saturation > 2)globalSettings->saturation = 2;
			m->getMenuItemByID("Saturation")->setText("Saturation: " + to_string((int)(globalSettings->saturation * 100)) + "%");
		}
	}
//
//	if (m->isSelectedID("Hue Shift"))
//	{
//		long long startTime = timeLastChangedSetting;
//		long long currentTime = System::currentHighResTimer();
//		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
//
//		if (ticksPassed > 15)
//		{
//			timeLastChangedSetting = currentTime;
//			if (globalSettings->hue < 2)globalSettings->hue += 0.01f;
//			if (globalSettings->hue > 2)globalSettings->hue = 2;
//			m->getCaptionByID("Hue Shift")->replaceText("Hue Shift: " + to_string((int)(globalSettings->hue * 100)) + "%");
//		}
//	}
}

//=========================================================================================================================
void BobsGame::settingsMenuConfirm(BobMenu* m)
{//=========================================================================================================================

		globalSettings->musicVolume = 50;
		music->setVolume(((float)globalSettings->musicVolume / 100.0f));
		globalSettings->hue = 1.5f;
		globalSettings->saturation = 1.2f;
		globalSettings->brightness = 1.0f;
		globalSettings->contrast = 1.2f;
		globalSettings->gamma = 1.0f;
		m->getMenuItemByID("Music Volume")->setText("Music Volume: " + to_string((int)(music->getVolume() * 100)) + "%");
		m->getMenuItemByID("Brightness")->setText("Brightness: " + to_string((int)(globalSettings->brightness * 100)) + "%");
		m->getMenuItemByID("Contrast")->setText("Contrast: " + to_string((int)(globalSettings->contrast * 100)) + "%");
		m->getMenuItemByID("Saturation")->setText("Saturation: " + to_string((int)(globalSettings->saturation * 100)) + "%");
	
}

//=========================================================================================================================
void BobsGame::globalSettingsMenuUpdate()
{//=========================================================================================================================

	if (globalSettingsMenu == nullptr)
	{
		globalSettingsMenu = new BobMenu(this, "Global Settings");

		settingsMenuInit(globalSettingsMenu);
		globalSettingsMenu->add("Back To Title Screen", "Back To Title Screen");

		globalSettingsMenu->cursorPosition = globalSettingsMenuCursorPosition;
	}


	if (getControlsManager()->miniGame_UP_Pressed())
	{
		globalSettingsMenu->up();
	}

	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		globalSettingsMenu->down();
	}

	if (getControlsManager()->MINIGAME_LEFT_HELD)
	{
		settingsMenuLeft(globalSettingsMenu);
	}
	if (getControlsManager()->MINIGAME_RIGHT_HELD)
	{
		settingsMenuRight(globalSettingsMenu);
	}


	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{
		if (globalSettingsMenu->isSelectedID("Defaults", clicked, mx, my))
		{
			settingsMenuConfirm(globalSettingsMenu);
		}
		if (globalSettingsMenu->isSelectedID("Back To Title Screen", clicked, mx, my))
		{
			leaveMenu = true;
		}

	}

	if (getControlsManager()->miniGame_CANCEL_Pressed())
	{
		leaveMenu = true;
	}

	if (leaveMenu)
	{
		globalSettingsMenuShowing = false;
		startScreenMenuShowing = true;

		if (globalSettingsMenu != nullptr)
		{
			globalSettingsMenuCursorPosition = globalSettingsMenu->cursorPosition;
			delete globalSettingsMenu;
			globalSettingsMenu = nullptr;
		}


	}
}


//=========================================================================================================================
void BobsGame::globalSettingsMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(BobMenu::bgColor->ri(), BobMenu::bgColor->gi(), BobMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	BobTexture* t = gearsTexture;

	if (globalSettingsMenu == nullptr)return;

	if (t != nullptr)
	{
		globalSettingsMenu->setGraphic(t, getWidth() / 3, getHeight() / 8);
	}

	globalSettingsMenu->render();
}

//=========================================================================================================================
void BobsGame::resetAllStatsMenuVars()
{//=========================================================================================================================
	statsMenu_totalTimePlayed = false;
	statsMenu_totalBlocksCleared = false;
	statsMenu_planeswalkerPoints = false;
	statsMenu_eloScore = false;
	statsMenu_timeLasted = false;
	statsMenu_blocksCleared = false;
}
//=========================================================================================================================
void BobsGame::whichStatsMiniMenuUpdate()
{//=========================================================================================================================
	
	//populate leaderBoardMiniMenu
	if (whichStatsMiniMenu == nullptr)
	{
		whichStatsMiniMenu = new BobMenu(this, "");
		whichStatsMiniMenu->center = false;
		whichStatsMiniMenu->font = BobFont::ttf_oswald_12;

		whichStatsMiniMenu->add("Top Players By Total Time Played", "totalTimePlayed");
		whichStatsMiniMenu->add("Top Players By Total Blocks Cleared", "totalBlocksCleared");
		whichStatsMiniMenu->add("Top Players By Planeswalker Points", "planeswalkerPoints");
		whichStatsMiniMenu->add("Top Players By Elo Score", "eloScore");
		whichStatsMiniMenu->add("Top Games By Time Lasted", "timeLasted");
		whichStatsMiniMenu->add("Top Games By Blocks Cleared", "blocksCleared");
	}


	if (getControlsManager()->miniGame_UP_Pressed())
	{
		whichStatsMiniMenu->up();
	}

	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		whichStatsMiniMenu->down();
	}

	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{

		if (whichStatsMiniMenu->isSelectedID("totalTimePlayed")) 
		{
			resetAllStatsMenuVars();
			statsMenu_totalTimePlayed = true; 
		}
		if (whichStatsMiniMenu->isSelectedID("totalBlocksCleared"))
		{
			resetAllStatsMenuVars();
			statsMenu_totalBlocksCleared = true;
		}
		if (whichStatsMiniMenu->isSelectedID("planeswalkerPoints"))
		{
			resetAllStatsMenuVars();
			statsMenu_planeswalkerPoints = true;
		}
		if (whichStatsMiniMenu->isSelectedID("eloScore"))
		{
			resetAllStatsMenuVars();
			statsMenu_eloScore = true;
		}
		if (whichStatsMiniMenu->isSelectedID("timeLasted"))
		{
			resetAllStatsMenuVars();
			statsMenu_timeLasted = true;
		}
		if (whichStatsMiniMenu->isSelectedID("blocksCleared"))
		{
			resetAllStatsMenuVars();
			statsMenu_blocksCleared = true;
		}

		leaveMenu = true;
	}

	//	if (getControlsManager()->miniGame_CANCEL_Pressed())
	//	{
	//		selectGameSequenceOrSingleGameTypeMenuShowing = true;
	//		leaveMenu = true;
	//	}

	if (leaveMenu)
	{
		whichStatsMiniMenuShowing = false;

		if (whichStatsMiniMenu != nullptr)
		{
			delete whichStatsMiniMenu;
			whichStatsMiniMenu = nullptr;
		}
	}

}



//=========================================================================================================================
void BobsGame::statsMenuUpdate()
{//=========================================================================================================================

	if (statsMenu == nullptr)
	{
		statsMenu = new BobMenu(this, "Stats And Leaderboards");

		statsMenu->add("Leaderboard Type", "Stats Type");
		statsMenu->add("All Games", "Game");
		statsMenu->add("All Difficulties", "Difficulty");
		statsMenu->addInfo(" ");
		statsMenu->add("Back To Title Screen", "Back To Title Screen");


		statsMenu->cursorPosition = statsMenuCursorPosition;
	}


	bool leaveMenu = false;


	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();

	if (whichStatsMiniMenuShowing)
	{
		whichStatsMiniMenuUpdate();
	}
	else
	if (selectGameSequenceOrSingleGameTypeMenuShowing)
	{
		selectGameSequenceOrSingleGameTypeMenuUpdate();
	}
	else
		if (selectGameSequenceMenuShowing)
		{
			selectGameSequenceMenuUpdate();
		}
		else
			if (selectSingleGameTypeMenuShowing)
			{
				selectSingleGameTypeMenuUpdate();
			}
			else
				if (gameSequenceOptionsMenuShowing)
				{
					gameSequenceOptionsMenuUpdate();
				}
				else
					if (gameObjectiveMenuShowing)
					{
						gameObjectiveMenuUpdate();
					}
					else
						if (difficultyMenuShowing)
						{
							difficultyMenuUpdate();
						}
						else
						{
							if (getControlsManager()->miniGame_UP_Pressed())
							{
								statsMenu->up();
							}

							if (getControlsManager()->miniGame_DOWN_Pressed())
							{
								statsMenu->down();
							}


							bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
							bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();

							if (confirm || clicked)
							{

								if (statsMenu->isSelectedID("Back To Title Screen", clicked, mx, my))
								{
									leaveMenu = true;
								}
								if (statsMenu->isSelectedID("Stats Type", clicked, mx, my))
								{
									whichStatsMiniMenuShowing = true;
								}

								if (statsMenu->isSelectedID("Game", clicked, mx, my))
								{
									selectGameSequenceOrSingleGameTypeMenuShowing = true;
								}

								if (statsMenu->isSelectedID("Difficulty", clicked, mx, my))
								{
									difficultyMenuShowing = true;
								}

							}
						}

	if (yourStatsMenu == nullptr)
	{
		yourStatsMenu = new BobMenu(this, "");
		yourStatsMenu->center = false;
		yourStatsMenu->font = BobFont::ttf_oswald_10;


		populateUserStatsForSpecificGameAndDifficultyMenu(yourStatsMenu, "OVERALL", "OVERALL");

	}

	if (leaderBoardMenu == nullptr)
	{
		leaderBoardMenu = new BobMenu(this, "");
		leaderBoardMenu->center = false;
		leaderBoardMenu->font = BobFont::ttf_oswald_10;

		populateLeaderBoardOrHighScoreBoardMenu(leaderBoardMenu, "OVERALL", "OVERALL", false, false, false, true, false, false);
	}


	long long currentTime = System::currentHighResTimer();
	long long startTime = updateStatsTime;
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	if (ticksPassed > 200)
	{
		updateStatsTime = currentTime;
	
		yourStatsMenu->clear();
		leaderBoardMenu->clear();


		populateUserStatsForSpecificGameAndDifficultyMenu(yourStatsMenu, statsMenu_gameSequenceOrTypeUUID, statsMenu_difficultyName);

		populateLeaderBoardOrHighScoreBoardMenu(leaderBoardMenu, statsMenu_gameSequenceOrTypeUUID, statsMenu_difficultyName,
				statsMenu_totalTimePlayed, statsMenu_totalBlocksCleared, statsMenu_planeswalkerPoints, statsMenu_eloScore, statsMenu_timeLasted, statsMenu_blocksCleared);

		yourStatsMenu->setAllCaptionsToFullAlpha();
		leaderBoardMenu->setAllCaptionsToFullAlpha();
	}






	if (getControlsManager()->miniGame_CANCEL_Pressed())
	{
		leaveMenu = true;
	}

	if (leaveMenu)
	{
		statsMenuShowing = false;
		startScreenMenuShowing = true;

		if (statsMenu != nullptr)
		{
			statsMenuCursorPosition = statsMenu->cursorPosition;
			delete statsMenu;
			statsMenu = nullptr;
		}
		if (yourStatsMenu != nullptr)
		{
			delete yourStatsMenu;
			yourStatsMenu = nullptr;
		}
		if (leaderBoardMenu != nullptr)
		{
			delete leaderBoardMenu;
			leaderBoardMenu = nullptr;
		}

	}
}


//=========================================================================================================================
void BobsGame::statsMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(BobMenu::bgColor->ri(), BobMenu::bgColor->gi(), BobMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	BobTexture* t = chartTexture;

	if (statsMenu == nullptr)return;

	if (t != nullptr)
	{
		statsMenu->setGraphic(t, getWidth() / 4, getHeight() / 10);
	}

	
	int startHeight = 0;
	int bottomHeight = 0;
	int leftX = 0;
	int rightX = 0;
	statsMenu->render(0, getWidth() / 6 * 1, getHeight(), true, &startHeight, &bottomHeight, false, &leftX, &rightX);
	yourStatsMenu->render(startHeight, rightX + 80, getHeight(), false, nullptr, nullptr, false, nullptr, &rightX);
	leaderBoardMenu->render(startHeight, rightX + 80, getHeight(), false);


	if (whichStatsMiniMenuShowing && whichStatsMiniMenu != nullptr)
	{
		Caption *c = statsMenu->getCaptionByID("Stats Type");
		whichStatsMiniMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, GLUtils::getViewportHeight(), true, nullptr, nullptr, true);
	}

	if (selectGameSequenceOrSingleGameTypeMenuShowing && selectGameSequenceOrSingleGameTypeMenu != nullptr)
	{
		Caption *c = statsMenu->getCaptionByID("Game");
		selectGameSequenceOrSingleGameTypeMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, GLUtils::getViewportHeight(), true, nullptr, nullptr, true);
	}

	if (selectGameSequenceMenuShowing && selectGameSequenceMenu != nullptr)
	{
		Caption *c = statsMenu->getCaptionByID("Game");
		selectGameSequenceMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, GLUtils::getViewportHeight(), true, nullptr, nullptr, true);
	}

	if (selectSingleGameTypeMenuShowing && selectSingleGameTypeMenu != nullptr)
	{
		Caption *c = statsMenu->getCaptionByID("Game");
		selectSingleGameTypeMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, GLUtils::getViewportHeight(), true, nullptr, nullptr, true);
	}


	if (difficultyMenuShowing && difficultyMenu != nullptr)
	{
		Caption *c = statsMenu->getCaptionByID("Difficulty");
		difficultyMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, GLUtils::getViewportHeight(), true, nullptr, nullptr, true);
	}


}



//
//void selectedGameSequence(BobsGame *b, string name)
//{
//	//get game sequence by name
//	//set current game sequence
//}
//
//void selectedGameType(BobsGame *b, string name)
//{
//	//select game type by name
//	//create new game sequence with only that one game type
//	//set current game sequence
//}
//
//void selectedDifficulty(BobsGame *b, string name)
//{
//	//set current difficulty type
//}
//
//void selectedObjective(BobsGame *b, string name)
//{
//	if(name=="End At Credits Level")
//	{
//		
//	}
//
//	if(name == "Endless")
//	{
//		
//	}
//}
//


//enum class StartWithOption
//{
//	FIRST_GAME,
//	RANDOM,
//};
//
//enum class PlayOrderOption
//{
//	RANDOM_BAG,
//	TOTALLY_RANDOM,
//	IN_ORDER,
//};





enum class GameObjective
{
	PLAY_TO_CREDITS_LEVEL,
	ENDLESS,
	LAST,
};

//=========================================================================================================================
void BobsGame::gameSetupMenuUpdate()
{//=========================================================================================================================


	if (gameSetupMenu == nullptr)
	{
		gameSetupMenu = new BobMenu(this, "Setup Game Options");

		gameSetupMenu->add("Select Game Sequence Or Single Game Type...", "Select Game");
		gameSetupMenu->add("Difficulty: Beginner", "Difficulty");
		gameSetupMenu->add("Objective: Play To Credits Level", "Objective");
		gameSetupMenu->addInfo(" ", " ");
		gameSetupMenu->add("Start Game", "Start Game");
		gameSetupMenu->addInfo(" ", " ");
		gameSetupMenu->add("Back To Title Screen", "Back To Title Screen");

		gameSetupMenu->cursorPosition = gameSetupMenuCursorPosition;

	}


	{
		string selectedDifficultyName = "";
		if (localMultiplayer || networkMultiplayer)
		{
			if (currentRoom == nullptr)currentRoom = new Room();

			if (currentRoom->multiplayer_SelectedDifficultyName != "")
			{
				selectedDifficultyName = currentRoom->multiplayer_SelectedDifficultyName;
			}
		}
		else
		{
			if (getPlayer1Game()->currentGameSequence != nullptr)
				selectedDifficultyName = getPlayer1Game()->currentGameSequence->currentDifficultyName;
		}

		if (selectedDifficultyName != "")
		{

			GameType gt;
			for (int i = 0; i < gt.difficultyTypes.size(); i++)
			{
				string difficultyName = gt.difficultyTypes.get(i)->name;
				if (selectedDifficultyName == difficultyName)selectedDifficultyIndex = i;
			}

			if (getPlayer1Game()->currentGameSequence != nullptr)
				getPlayer1Game()->currentGameSequence->currentDifficultyName = selectedDifficultyName;

			Caption *c = gameSetupMenu->getCaptionByID("Difficulty");
			if (c != nullptr)c->setText("Difficulty: " + selectedDifficultyName);
		}
	}



	{
		GameSequence *selectedGameSequence = nullptr;
		if (localMultiplayer || networkMultiplayer)
		{
			selectedGameSequence = currentRoom->multiplayer_SelectedGameSequence;
		}
		else
		{
			selectedGameSequence = getPlayer1Game()->currentGameSequence;
		}

		if(selectedGameSequence == nullptr)
		{
			selectedGameSequence = getGameSequenceByName("bob's game");
			if (selectedGameSequence == nullptr)
			{
				selectedGameSequence = new GameSequence();
				selectedGameSequence->gameTypes.add(new GameType());
			}
			currentRoom->multiplayer_SelectedGameSequence = selectedGameSequence;
			getPlayer1Game()->currentGameSequence = selectedGameSequence;
		}

		{
			Caption *c = gameSetupMenu->getCaptionByID("Select Game");
			if (c != nullptr)
			{
				if (selectedGameSequence->gameTypes.size() > 1)c->setText("Game Sequence: " + selectedGameSequence->name);
				if (selectedGameSequence->gameTypes.size() == 1)c->setText("Game Type: " + selectedGameSequence->name);
			}
		}

		gameSetupMenu->getMenuItemByID("Start Game")->setColor(BobMenu::menuColor);
		gameSetupMenu->getMenuItemByID("Start Game")->info = false;
		
	}

	{
		string objectiveString = "";
		if (selectedObjectiveIndex == (int)GameObjective::PLAY_TO_CREDITS_LEVEL)
		{
			objectiveString = "Play To Credits Level";
		}
		if (selectedObjectiveIndex == (int)GameObjective::ENDLESS)
		{
			objectiveString = "Endless";
		}
		Caption *c = gameSetupMenu->getCaptionByID("Objective");
		if (c != nullptr)c->setText("Objective: " + objectiveString);
	}

	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();




	if (selectGameSequenceOrSingleGameTypeMenuShowing)
	{
		selectGameSequenceOrSingleGameTypeMenuUpdate();
	}
	else
	if (selectGameSequenceMenuShowing)
	{
		selectGameSequenceMenuUpdate();
	}
	else
	if (selectSingleGameTypeMenuShowing)
	{
		selectSingleGameTypeMenuUpdate();
	}
	else
	if (gameSequenceOptionsMenuShowing)
	{
		gameSequenceOptionsMenuUpdate();
	}
	else
	if (gameObjectiveMenuShowing)
	{
		gameObjectiveMenuUpdate();
	}
	else
	if (difficultyMenuShowing)
	{
		difficultyMenuUpdate();
	}
	else
	{
		if (getControlsManager()->miniGame_UP_Pressed())
		{
			gameSetupMenu->up();
		}

		if (getControlsManager()->miniGame_DOWN_Pressed())
		{
			gameSetupMenu->down();
		}

		bool left = getControlsManager()->miniGame_LEFT_Pressed();
		bool right = getControlsManager()->miniGame_RIGHT_Pressed();
		
		if (left || right)
		{
			if (gameSetupMenu->isSelectedID("Difficulty"))
			{
				GameType gt;
				if (left)
				{
					selectedDifficultyIndex--;
					if (selectedDifficultyIndex < 0)selectedDifficultyIndex = gt.difficultyTypes.size() - 1;
				}
				if (right)
				{
					selectedDifficultyIndex++;
					if (selectedDifficultyIndex >= gt.difficultyTypes.size())selectedDifficultyIndex = 0;
				}

				DifficultyType *d = gt.difficultyTypes.get(selectedDifficultyIndex);
				string difficultyName = d->name;
				currentRoom->multiplayer_SelectedDifficultyName = difficultyName;
				if (getPlayer1Game()->currentGameSequence != nullptr)
					getPlayer1Game()->currentGameSequence->currentDifficultyName = difficultyName;
			}

			if (gameSetupMenu->isSelectedID("Objective"))
			{
				if (left)
				{
					selectedObjectiveIndex--;
					if (selectedObjectiveIndex < 0)selectedObjectiveIndex = (int)GameObjective::LAST - 1;
				}
				if (right)
				{
					selectedObjectiveIndex++;
					if (selectedObjectiveIndex >= (int)GameObjective::LAST)selectedObjectiveIndex = 0;
				}

				if (selectedObjectiveIndex == (int)GameObjective::PLAY_TO_CREDITS_LEVEL)
				{
					if (getPlayer1Game()->currentGameSequence != nullptr)getPlayer1Game()->currentGameSequence->endlessMode = false;
					if (currentRoom->multiplayer_SelectedGameSequence != nullptr)currentRoom->multiplayer_SelectedGameSequence->endlessMode = false;
				}
				if (selectedObjectiveIndex == (int)GameObjective::ENDLESS)
				{
					if (getPlayer1Game()->currentGameSequence != nullptr)getPlayer1Game()->currentGameSequence->endlessMode = true;
					if (currentRoom->multiplayer_SelectedGameSequence != nullptr)currentRoom->multiplayer_SelectedGameSequence->endlessMode = true;
				}

				string objectiveString = "";
				if (selectedObjectiveIndex == (int)GameObjective::PLAY_TO_CREDITS_LEVEL)
				{
					objectiveString = "Play To Credits Level";
				}
				if (selectedObjectiveIndex == (int)GameObjective::ENDLESS)
				{
					objectiveString = "Endless";
				}
				Caption *c = gameSetupMenu->getCaptionByID("Objective");
				if (c != nullptr)c->setText("Objective: " + objectiveString);

			}
		}

		bool leaveMenu = false;

		bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
		bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();

		if (confirm || clicked)
		{

			if (gameSetupMenu->isSelectedID("Select Game", clicked, mx, my))
			{
				selectGameSequenceOrSingleGameTypeMenuShowing = true;
			}

			if (gameSetupMenu->isSelectedID("Difficulty", clicked, mx, my))
			{
				difficultyMenuShowing = true;
			}

			if (gameSetupMenu->isSelectedID("Objective", clicked, mx, my))
			{
				gameObjectiveMenuShowing = true;
			}

			if (gameSetupMenu->isSelectedID("Start Game", clicked, mx, my))
			{

				if(getPlayer1Game()->currentGameSequence == nullptr)getPlayer1Game()->currentGameSequence = currentRoom->multiplayer_SelectedGameSequence;

				GameType gt;
				DifficultyType *d = gt.difficultyTypes.get(selectedDifficultyIndex);
				string difficultyName = d->name;
				currentRoom->multiplayer_SelectedDifficultyName = difficultyName;
				if (getPlayer1Game()->currentGameSequence != nullptr)
					getPlayer1Game()->currentGameSequence->currentDifficultyName = difficultyName;


				if (selectedObjectiveIndex == (int)GameObjective::PLAY_TO_CREDITS_LEVEL)
				{
					if (getPlayer1Game()->currentGameSequence != nullptr)getPlayer1Game()->currentGameSequence->endlessMode = false;
					if (currentRoom->multiplayer_SelectedGameSequence != nullptr)currentRoom->multiplayer_SelectedGameSequence->endlessMode = false;
				}
				if (selectedObjectiveIndex == (int)GameObjective::ENDLESS)
				{
					if (getPlayer1Game()->currentGameSequence != nullptr)getPlayer1Game()->currentGameSequence->endlessMode = true;
					if (currentRoom->multiplayer_SelectedGameSequence != nullptr)currentRoom->multiplayer_SelectedGameSequence->endlessMode = true;
				}

				//if game type selected, else gray out
				leaveMenu = true;
			}

			if (gameSetupMenu->isSelectedID("Back To Title Screen", clicked, mx, my))
			{
				startScreenMenuShowing = true;

				leaveMenu = true;
			}
		}

		if (getControlsManager()->miniGame_CANCEL_Pressed())
		{

			startScreenMenuShowing = true;
			
			leaveMenu = true;
		}

		if (leaveMenu)
		{
			gameSetupMenuShowing = false;

			if (gameSetupMenu != nullptr)
			{
				gameSetupMenuCursorPosition = gameSetupMenu->cursorPosition;
				delete gameSetupMenu;
				gameSetupMenu = nullptr;
			}


		}
	}
}


//=========================================================================================================================
void BobsGame::gameSetupMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(BobMenu::bgColor->ri(), BobMenu::bgColor->gi(), BobMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	BobTexture* t = keyboardTexture;

	if (gameSetupMenu == nullptr)return;

	if (t != nullptr)
	{
		gameSetupMenu->setGraphic(t, getWidth() / 8 * 6, getHeight() / 8);
	}

	gameSetupMenu->render();


	if(selectGameSequenceOrSingleGameTypeMenuShowing && selectGameSequenceOrSingleGameTypeMenu != nullptr)
	{
		Caption *c = gameSetupMenu->getCaptionByID("Select Game");
		selectGameSequenceOrSingleGameTypeMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, GLUtils::getViewportHeight(), true, nullptr, nullptr, true);
	}

	if (selectGameSequenceMenuShowing && selectGameSequenceMenu != nullptr)
	{
		Caption *c = gameSetupMenu->getCaptionByID("Select Game");
		selectGameSequenceMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, GLUtils::getViewportHeight(), true, nullptr, nullptr, true);
	}
		
	if (selectSingleGameTypeMenuShowing && selectSingleGameTypeMenu != nullptr)
	{
		Caption *c = gameSetupMenu->getCaptionByID("Select Game");
		selectSingleGameTypeMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, GLUtils::getViewportHeight(), true, nullptr, nullptr, true);
	}
			
	if (gameSequenceOptionsMenuShowing && gameSequenceOptionsMenu != nullptr)
	{
		Caption *c = gameSetupMenu->getCaptionByID("Select Game");
		gameSequenceOptionsMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, GLUtils::getViewportHeight(), true, nullptr, nullptr, true);
	}

	if (difficultyMenuShowing && difficultyMenu!=nullptr)
	{
		Caption *c = gameSetupMenu->getCaptionByID("Difficulty");
		difficultyMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, GLUtils::getViewportHeight(), true, nullptr, nullptr, true);
	}

	if (gameObjectiveMenuShowing && gameObjectiveMenu != nullptr)
	{
		Caption *c = gameSetupMenu->getCaptionByID("Objective");
		gameObjectiveMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, GLUtils::getViewportHeight(), true, nullptr, nullptr, true);
	}
}


//=========================================================================================================================
void BobsGame::selectGameSequenceOrSingleGameTypeMenuUpdate()
{//=========================================================================================================================



	//TODO: store default difficulty in GlobalSettings


	if (selectGameSequenceOrSingleGameTypeMenu == nullptr)
	{
		selectGameSequenceOrSingleGameTypeMenu = new BobMenu(this, "");

		if(localMultiplayer || networkMultiplayer)
		{
			selectGameSequenceOrSingleGameTypeMenu->add("Allow Different Game Sequences Or Types");
		}

		if (statsMenuShowing)
		{
			selectGameSequenceOrSingleGameTypeMenu->add("Any Game Type Or Sequence", "Allow Different Game Sequences Or Types");
			selectGameSequenceOrSingleGameTypeMenu->add("Select Game Sequence", "Play Game Sequence");
			selectGameSequenceOrSingleGameTypeMenu->add("Select Single Game Type", "Play Single Game Type");
		}
		else
		{
			selectGameSequenceOrSingleGameTypeMenu->add("Play Game Sequence", "Play Game Sequence");
			selectGameSequenceOrSingleGameTypeMenu->add("Play Single Game Type", "Play Single Game Type");
		}
		
		selectGameSequenceOrSingleGameTypeMenu->cursorPosition = selectGameSequenceOrSingleGameTypeMenuCursorPosition;
	}



	if (getControlsManager()->miniGame_UP_Pressed())
	{
		selectGameSequenceOrSingleGameTypeMenu->up();
	}

	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		selectGameSequenceOrSingleGameTypeMenu->down();
	}

	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{

		if (selectGameSequenceOrSingleGameTypeMenu->isSelectedID("Allow Different Game Sequences Or Types", clicked, mx, my))
		{
			if (localMultiplayer || networkMultiplayer)
			{
				currentRoom->multiplayer_AllowDifferentGameSequences = true;
			}

			if(statsMenuShowing)
			{
				statsMenu_gameSequenceOrTypeUUID = "OVERALL";
			}
		}

		if (selectGameSequenceOrSingleGameTypeMenu->isSelectedID("Play Game Sequence", clicked, mx, my))
		{
			if (statsMenuShowing == false)
			{
				currentRoom->multiplayer_AllowDifferentGameSequences = false;
			}
			selectGameSequenceMenuShowing = true;
		}

		if (selectGameSequenceOrSingleGameTypeMenu->isSelectedID("Play Single Game Type", clicked, mx, my))
		{
			if (statsMenuShowing == false)
			{
				currentRoom->multiplayer_AllowDifferentGameSequences = false;
			}
			selectSingleGameTypeMenuShowing = true;
		}

		leaveMenu = true;
	}

//	if (getControlsManager()->miniGame_CANCEL_Pressed())
//	{
//		if(localMultiplayer || networkMultiplayer)
//		{
//			multiplayerOptionsMenuShowing = true;
//		}
//		else
//		{
//			titleMenuShowing = true;
//		}
//		leaveMenu = true;
//	}

	if (leaveMenu)
	{
		selectGameSequenceOrSingleGameTypeMenuShowing = false;

		if (selectGameSequenceOrSingleGameTypeMenu != nullptr)
		{
			selectGameSequenceOrSingleGameTypeMenuCursorPosition = selectGameSequenceOrSingleGameTypeMenu->cursorPosition;
			delete selectGameSequenceOrSingleGameTypeMenu;
			selectGameSequenceOrSingleGameTypeMenu = nullptr;
		}
	}

}


//=========================================================================================================================
void BobsGame::selectGameSequenceOrSingleGameTypeMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(BobMenu::bgColor->ri(), BobMenu::bgColor->gi(), BobMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	BobTexture* t = keyboardTexture;

	if (selectGameSequenceOrSingleGameTypeMenu == nullptr)return;

	if (t != nullptr)
	{
		selectGameSequenceOrSingleGameTypeMenu->setGraphic(t, getWidth() / 3 * 2, getHeight() / 10);
	}

	selectGameSequenceOrSingleGameTypeMenu->render(getHeight()/2);
}



//=========================================================================================================================
void BobsGame::selectGameSequenceMenuUpdate()
{//=========================================================================================================================

	if (selectGameSequenceMenu == nullptr)
	{
		selectGameSequenceMenu = new BobMenu(this, "");
		selectGameSequenceMenu->center = false;

		populateGameSequencesMenu(selectGameSequenceMenu);


		selectGameSequenceMenu->cursorPosition = selectGameSequenceMenuCursorPosition;
	}

	if (getControlsManager()->miniGame_UP_Pressed())
	{
		selectGameSequenceMenu->up();
	}

	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		selectGameSequenceMenu->down();
	}

	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{
		for (int i = 0; i<loadedGameSequences.size(); i++)
		{
			GameSequence *g = loadedGameSequences.get(i);
			if (selectGameSequenceMenu->isSelectedID(g->uuid, clicked, mx, my))
			{
				if(statsMenuShowing)
				{
					statsMenu_gameSequenceOrTypeUUID = g->uuid;
				}
				else
				{
					currentRoom->multiplayer_SelectedGameSequence = g;
					getPlayer1Game()->currentGameSequence = g;

					gameSequenceOptionsMenuShowing = true;
				}
			}
		}

		leaveMenu = true;
	}

//	if (getControlsManager()->miniGame_CANCEL_Pressed())
//	{
//		selectGameSequenceOrSingleGameTypeMenuShowing = true;
//		leaveMenu = true;
//	}

	if (leaveMenu)
	{
		selectGameSequenceMenuShowing = false;

		if (selectGameSequenceMenu != nullptr)
		{
			selectGameSequenceMenuCursorPosition = selectGameSequenceMenu->cursorPosition;
			delete selectGameSequenceMenu;
			selectGameSequenceMenu = nullptr;
		}
	}

}


//=========================================================================================================================
void BobsGame::selectGameSequenceMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(BobMenu::bgColor->ri(), BobMenu::bgColor->gi(), BobMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	BobTexture* t = keyboardTexture;

	if (selectGameSequenceMenu == nullptr)return;

	if (t != nullptr)
	{
		selectGameSequenceMenu->setGraphic(t, getWidth() / 3 * 2, getHeight() / 10);
	}

	selectGameSequenceMenu->render(getHeight()/2);
}



//=========================================================================================================================
void BobsGame::gameSequenceOptionsMenuUpdate()
{//=========================================================================================================================

	const string RANDOMIZE_SEQUENCE = "Randomize Sequence";
	const string PLAY_THROUGH_SEQUENCE_IN_ORDER = "Play Through Sequence In Order";

	if (gameSequenceOptionsMenu == nullptr)
	{
		gameSequenceOptionsMenu = new BobMenu(this,"");

		gameSequenceOptionsMenu->add(RANDOMIZE_SEQUENCE);
		gameSequenceOptionsMenu->add(PLAY_THROUGH_SEQUENCE_IN_ORDER);
		
		gameSequenceOptionsMenu->cursorPosition = gameSequenceOptionsMenuCursorPosition;
	}



	if (getControlsManager()->miniGame_UP_Pressed())
	{
		gameSequenceOptionsMenu->up();
	}

	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		gameSequenceOptionsMenu->down();
	}

	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{

		if (gameSequenceOptionsMenu->isSelectedID(RANDOMIZE_SEQUENCE, clicked, mx, my))
		{
			if(getPlayer1Game()->currentGameSequence!=nullptr)getPlayer1Game()->currentGameSequence->randomizeSequence = true;
			if (currentRoom->multiplayer_SelectedGameSequence != nullptr)currentRoom->multiplayer_SelectedGameSequence->randomizeSequence = true;
		}

		if (gameSequenceOptionsMenu->isSelectedID(PLAY_THROUGH_SEQUENCE_IN_ORDER, clicked, mx, my))
		{
			if (getPlayer1Game()->currentGameSequence != nullptr)getPlayer1Game()->currentGameSequence->randomizeSequence = false;
			if (currentRoom->multiplayer_SelectedGameSequence != nullptr)currentRoom->multiplayer_SelectedGameSequence->randomizeSequence = false;
		}

		//gameObjectiveMenuShowing = true;


		leaveMenu = true;
	}

//	if (getControlsManager()->miniGame_CANCEL_Pressed())
//	{
//		selectGameSequenceMenuShowing = true;
//		leaveMenu = true;
//	}

	if (leaveMenu)
	{
		gameSequenceOptionsMenuShowing = false;

		if (gameSequenceOptionsMenu != nullptr)
		{
			gameSequenceOptionsMenuCursorPosition = gameSequenceOptionsMenu->cursorPosition;
			delete gameSequenceOptionsMenu;
			gameSequenceOptionsMenu = nullptr;
		}
	}

}


//=========================================================================================================================
void BobsGame::gameSequenceOptionsMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(BobMenu::bgColor->ri(), BobMenu::bgColor->gi(), BobMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	BobTexture* t = keyboardTexture;

	if (gameSequenceOptionsMenu == nullptr)return;

	if (t != nullptr)
	{
		gameSequenceOptionsMenu->setGraphic(t, getWidth() / 3 * 2, getHeight() / 10);
	}

	gameSequenceOptionsMenu->render();
}



//=========================================================================================================================
/// <summary>
/// Calculates the Wilson Score based on the total votes and upvotes
/// </summary>
/// <param name="up">Number of upvotes</param>
/// <param name="total">Total number of votes</param>
/// <param name="confidence">Confidence used in calculation, default 1.644853 (95%)</param>
double BobsGame::wilsonScore(double up, double total, double confidence)
{//=========================================================================================================================
	/** Based on http://www.evanmiller.org/how-not-to-sort-by-average-rating.html **/
	if (total <= 0 || total < up)
		return 0;

	double phat = up / total;
	double z2 = confidence * confidence;

	return (phat + z2 / (2 * total) - confidence * sqrt((phat * (1 - phat) + z2 / (4 * total)) / total)) / (1 + z2 / total);
}

//=========================================================================================================================
ArrayList<pair<GameType*,pair<string,BobColor*>>> BobsGame::getSortedGameTypes()
{//=========================================================================================================================
	
	ArrayList<pair<GameType*, pair<string, BobColor*>>> gamesStringColor;

	for (int i = 0; i<loadedGameTypes.size(); i++)
	{
		GameType *g = loadedGameTypes.get(i);
		if (g->builtInType)
		{
			string name = g->name;
			BobColor *color = BobColor::darkGreen;
			pair<string, BobColor*> stringColorPair = pair<string, BobColor*>(name,color);
			pair<GameType*, pair<string, BobColor*>> gameTypeStringColorPairPair = pair<GameType*, pair<string, BobColor*>>(g, stringColorPair);
			gamesStringColor.add(gameTypeStringColorPairPair);
		}
	}
	for (int i = 0; i<loadedGameTypes.size(); i++)
	{
		GameType *g = loadedGameTypes.get(i);
		if (g->builtInType == false && g->downloaded == false)
		{
			string name = g->creatorUserName + " - " + g->name;
			BobColor *color = BobColor::darkPurple;
			pair<string, BobColor*> stringColorPair = pair<string, BobColor*>(name, color);
			pair<GameType*, pair<string, BobColor*>> gameTypeStringColorPairPair = pair<GameType*, pair<string, BobColor*>>(g, stringColorPair);
			gamesStringColor.add(gameTypeStringColorPairPair);
		}
	}

	ArrayList<GameType*> downloadedGames;
	for (int i = 0; i<loadedGameTypes.size(); i++)
	{
		GameType *g = loadedGameTypes.get(i);
		if (g->builtInType == false && g->downloaded == true)
		{
			downloadedGames.add(g);
		}
	}

	multimap<double, GameType*> games;
	for (int i = 0; i < downloadedGames.size(); i++)
	{
		GameType *g = downloadedGames.get(i);

		double up = (double)(g->upVotes);
		double total = (double)(g->upVotes + g->downVotes);
		double score = wilsonScore(up, total);

		games.insert(std::pair<double, GameType*>(score, g));
	}

	long long currentSecondsSinceEpoch = (long long)time(nullptr);

	multimap<double, GameType*>::iterator pos;
	for (pos = games.begin(); pos != games.end(); ++pos)
	{
		GameType *g = pos->second;

		long long secondsSinceEpoch = g->dateCreated / 1000;
		long long secondsExisted = currentSecondsSinceEpoch - secondsSinceEpoch;
		int daysExisted = (int)(secondsExisted / 60 / 60 / 24);

		string name = g->creatorUserName + " - " + g->name + " (" + to_string(g->upVotes) + "/" + to_string(g->downVotes) + ") " + to_string(daysExisted) + "days";

		BobColor *color = BobColor::black;
		pair<string, BobColor*> stringColorPair = pair<string, BobColor*>(name, color);
		pair<GameType*, pair<string, BobColor*>> gameTypeStringColorPairPair = pair<GameType*, pair<string, BobColor*>>(g, stringColorPair);
		gamesStringColor.add(gameTypeStringColorPairPair);
	}

	return gamesStringColor;

}

//=========================================================================================================================
ArrayList<pair<GameSequence*, pair<string, BobColor*>>> BobsGame::getSortedGameSequences()
{//=========================================================================================================================

	ArrayList<pair<GameSequence*, pair<string, BobColor*>>> gamesStringColor;

	for (int i = 0; i<loadedGameSequences.size(); i++)
	{
		GameSequence *g = loadedGameSequences.get(i);
		if (g->builtInType)
		{
			string name = g->name;
			BobColor *color = BobColor::darkGreen;
			pair<string, BobColor*> stringColorPair = pair<string, BobColor*>(name, color);
			pair<GameSequence*, pair<string, BobColor*>> gameSequenceStringColorPairPair = pair<GameSequence*, pair<string, BobColor*>>(g, stringColorPair);
			gamesStringColor.add(gameSequenceStringColorPairPair);
		}
	}
	for (int i = 0; i<loadedGameSequences.size(); i++)
	{
		GameSequence *g = loadedGameSequences.get(i);
		if (g->builtInType == false && g->downloaded == false)
		{
			string name = g->creatorUserName + " - " + g->name;
			BobColor *color = BobColor::darkPurple;
			pair<string, BobColor*> stringColorPair = pair<string, BobColor*>(name, color);
			pair<GameSequence*, pair<string, BobColor*>> gameSequenceStringColorPairPair = pair<GameSequence*, pair<string, BobColor*>>(g, stringColorPair);
			gamesStringColor.add(gameSequenceStringColorPairPair);
		}
	}

	ArrayList<GameSequence*> downloadedGames;
	for (int i = 0; i<loadedGameSequences.size(); i++)
	{
		GameSequence *g = loadedGameSequences.get(i);
		if (g->builtInType == false && g->downloaded == true)
		{
			downloadedGames.add(g);
		}
	}

	multimap<double, GameSequence*> games;
	for (int i = 0; i < downloadedGames.size(); i++)
	{
		GameSequence *g = downloadedGames.get(i);

		double up = (double)(g->upVotes);
		double total = (double)(g->upVotes + g->downVotes);
		double score = wilsonScore(up, total);

		games.insert(std::pair<double, GameSequence*>(score, g));
	}

	long long currentSecondsSinceEpoch = (long long)time(nullptr);

	multimap<double, GameSequence*>::iterator pos;
	for (pos = games.begin(); pos != games.end(); ++pos)
	{
		GameSequence *g = pos->second;

		long long secondsSinceEpoch = g->dateCreated / 1000;
		long long secondsExisted = currentSecondsSinceEpoch - secondsSinceEpoch;
		int daysExisted = (int)(secondsExisted / 60 / 60 / 24);

		string name = g->creatorUserName + " - " + g->name + " (" + to_string(g->upVotes) + "/" + to_string(g->downVotes) + ") " + to_string(daysExisted) + "days";

		BobColor *color = BobColor::black;
		pair<string, BobColor*> stringColorPair = pair<string, BobColor*>(name, color);
		pair<GameSequence*, pair<string, BobColor*>> gameSequenceStringColorPairPair = pair<GameSequence*, pair<string, BobColor*>>(g, stringColorPair);
		gamesStringColor.add(gameSequenceStringColorPairPair);
	}

	return gamesStringColor;

}
//=========================================================================================================================
void BobsGame::populateGameTypesMenu(BobMenu *menu)
{//=========================================================================================================================
	

	//need to sort and color
	//make built in games green maybe
	//make usermade by me under those, make blue
	//make downloaded ones have user info, sorted by some voodoo metric of upvotes / timeexisted
	//use smaller font
	//username - game name - upvotes/downvotes

	ArrayList<pair<GameType*, pair<string, BobColor*>>> gamesStringColor = getSortedGameTypes();
	for (int i = 0; i < gamesStringColor.size(); i++)
	{
		pair<GameType*, pair<string, BobColor*>> gameTypeStringColorPairPair = gamesStringColor.get(i);
		GameType *g = gameTypeStringColorPairPair.first;
		pair<string, BobColor*> stringColorPair = gameTypeStringColorPairPair.second;
		string name = stringColorPair.first;
		BobColor *color = stringColorPair.second;

		BobMenu::MenuItem *m = menu->add(name, g->uuid);
		m->setColor(color);

	}
	//TODO:maybe show preview of game running really fast ???
}

//=========================================================================================================================
void BobsGame::populateGameSequencesMenu(BobMenu *menu)
{//=========================================================================================================================

	ArrayList<pair<GameSequence*, pair<string, BobColor*>>> gamesStringColor = getSortedGameSequences();
	for (int i = 0; i < gamesStringColor.size(); i++)
	{
		pair<GameSequence*, pair<string, BobColor*>> gameSequenceStringColorPairPair = gamesStringColor.get(i);
		GameSequence *g = gameSequenceStringColorPairPair.first;
		pair<string, BobColor*> stringColorPair = gameSequenceStringColorPairPair.second;
		string name = stringColorPair.first;
		BobColor *color = stringColorPair.second;

		BobMenu::MenuItem *m = menu->add(name, g->uuid);
		m->setColor(color);

	}
}



//=========================================================================================================================
string getNiceTime(long ms)
{//=========================================================================================================================
	int sec = ms / 1000;
	int min = sec / 60;
	int hrs = min / 60;

	string niceTime = "";
	if (hrs > 0 && hrs < 10)niceTime += "0"+to_string(hrs) + "h ";
	if (hrs > 0 && hrs >= 10)niceTime += to_string(hrs) + "h ";

	if (min > 0 && min < 10)niceTime += "0" + to_string(min) + "m ";
	if (min > 0 && min >= 10)niceTime += to_string(min) + "m ";

	if (sec > 0 && sec < 10)niceTime += "0" + to_string(sec) + "s ";
	if (sec > 0 && sec >= 10)niceTime += to_string(sec) + "s ";
	return niceTime;
}

string getDateFromEpochTime(long ms)
{
	std::time_t result = ms;
	string s = std::asctime(std::localtime(&result));
	std::string::size_type i = s.find("\n");
	if (i != std::string::npos)
		s.erase(i, s.length());
	return s;
}

//=========================================================================================================================
//gameTypeOrSequenceString or difficulty string can be "OVERALL"
void BobsGame::populateUserStatsForSpecificGameAndDifficultyMenu(BobMenu *menu, string gameTypeOrSequenceUUID, string difficultyString)
{//=========================================================================================================================

	BobsGameUserStatsForSpecificGameAndDifficulty *stats = nullptr;
	for(int i=0;i<userStatsPerGameAndDifficulty.size();i++)
	{
		BobsGameUserStatsForSpecificGameAndDifficulty *s = userStatsPerGameAndDifficulty.get(i);
		if (s->gameTypeUUID == gameTypeOrSequenceUUID || s->gameSequenceUUID == gameTypeOrSequenceUUID || s->isGameTypeOrSequence == gameTypeOrSequenceUUID)
		{
			if (s->difficultyName == difficultyString)
			{
				stats = s;
				break;
			}
		}
	}
	bool deleteStats = false;
	if (stats == nullptr)
	{
		stats = new BobsGameUserStatsForSpecificGameAndDifficulty(); 
		deleteStats = true;
	}


	string gameName = "";
	if (gameTypeOrSequenceUUID == "OVERALL")
	{
		gameName = "All Games";
	}
	else
	{
		GameType* gt = getGameTypeByUUID(gameTypeOrSequenceUUID);
		GameSequence *gs = getGameSequenceByUUID(gameTypeOrSequenceUUID);
		if (gt != nullptr)gameName = gt->name;
		if (gs != nullptr)gameName = gs->name;
	}

	string difficultyName = "";
	if (difficultyString == "OVERALL")
	{
		difficultyName = "All Difficulties";
	}
	else
	{
		difficultyName = difficultyString;
	}

	menu->add("Your Stats");
	menu->add(gameName);
	menu->add(difficultyName);
	menu->addInfo(" ");
	menu->add("Total Games Played: " + to_string(stats->totalGamesPlayed));
	menu->add("Single Player Games Played: " + to_string(stats->singlePlayerGamesPlayed));
	menu->add("Single Player Games Completed: " + to_string(stats->singlePlayerGamesCompleted));
	menu->add("Single Player Games Failed: " + to_string(stats->singlePlayerGamesLost));
	menu->add("Local Multiplayer Games Played: " + to_string(stats->localMultiplayerGamesPlayed));
	menu->add("Tournament Games Played: " + to_string(stats->tournamentGamesPlayed));
	menu->add("Tournament Games Won: " + to_string(stats->tournamentGamesWon));
	menu->add("Tournament Games Lost: " + to_string(stats->tournamentGamesLost));
	menu->add("Longest Game Length: " + getNiceTime(stats->longestGameLength));
	menu->add("Average Game Length: " + getNiceTime(stats->averageGameLength));
	menu->add("Total Time Played: " + getNiceTime(stats->totalTimePlayed));
	menu->add("First Time Played: " + getDateFromEpochTime(stats->firstTimePlayed));
	menu->add("Last Time Played: " + getDateFromEpochTime(stats->lastTimePlayed));
	menu->add("Most Blocks Cleared: " + to_string(stats->mostBlocksCleared));
	menu->add("Total Blocks Made: " + to_string(stats->totalBlocksMade));
	menu->add("Total Blocks Cleared: " + to_string(stats->totalBlocksCleared));
	menu->add("Total Pieces Made: " + to_string(stats->totalPiecesMade));
	menu->add("Total Pieces Placed: " + to_string(stats->totalPiecesPlaced));
	menu->add("Total Combos Made: " + to_string(stats->totalCombosMade));
	menu->add("Biggest Combo: " + to_string(stats->biggestCombo));
	menu->add("Elo Score: " + to_string(stats->eloScore));
	menu->add("Planeswalker Score: " + to_string(stats->planesWalkerPoints));


	if (deleteStats)delete stats;
}

/*

static ArrayList<BobsGameUserStatsForSpecificGameAndDifficulty*> userStatsPerGameAndDifficulty;
static ArrayList<BobsGameLeaderBoardAndHighScoreBoard*> topPlayersByTotalTimePlayed;
static ArrayList<BobsGameLeaderBoardAndHighScoreBoard*> topPlayersByTotalBlocksCleared;
static ArrayList<BobsGameLeaderBoardAndHighScoreBoard*> topPlayersByPlaneswalkerPoints;
static ArrayList<BobsGameLeaderBoardAndHighScoreBoard*> topPlayersByEloScore;

//TODO: could do highest level reached
//TODO: could do biggest combo
static ArrayList<BobsGameLeaderBoardAndHighScoreBoard*> topGamesByTimeLasted;
static ArrayList<BobsGameLeaderBoardAndHighScoreBoard*> topGamesByBlocksCleared;
*/

//=========================================================================================================================
void BobsGame::populateLeaderBoardOrHighScoreBoardMenu(BobMenu *menu, string gameTypeOrSequenceUUID, string difficultyString, 
	bool totalTimePlayed,
	bool totalBlocksCleared,
	bool planeswalkerPoints,
	bool eloScore,
	bool timeLasted,
	bool blocksCleared
)
{//=========================================================================================================================

	BobsGameLeaderBoardAndHighScoreBoard *stats = nullptr;

	ArrayList<BobsGameLeaderBoardAndHighScoreBoard*> &board = topPlayersByTotalTimePlayed;

	if (totalTimePlayed)board = topPlayersByTotalTimePlayed;
	if (totalBlocksCleared)board = topPlayersByTotalBlocksCleared;
	if (planeswalkerPoints)board = topPlayersByPlaneswalkerPoints;
	if (eloScore)board = topPlayersByEloScore;
	if (timeLasted)board = topGamesByTimeLasted;
	if (blocksCleared)board = topGamesByBlocksCleared;

	for (int i = 0; i<board.size(); i++)
	{
		BobsGameLeaderBoardAndHighScoreBoard *s = board.get(i);
		if (s->gameTypeUUID == gameTypeOrSequenceUUID || s->gameSequenceUUID == gameTypeOrSequenceUUID || s->isGameTypeOrSequence == gameTypeOrSequenceUUID)
		{
			if (s->difficultyName == difficultyString)
			{
				stats = s;
				break;
			}
		}
	}
	bool deleteStats = false;
	if (stats == nullptr)
	{
		stats = new BobsGameLeaderBoardAndHighScoreBoard();
		deleteStats = true;
	}


	string gameName = "";
	if (gameTypeOrSequenceUUID == "OVERALL")
	{
		gameName = "All Games";
	}
	else
	{
		GameType* gt = getGameTypeByUUID(gameTypeOrSequenceUUID);
		GameSequence *gs = getGameSequenceByUUID(gameTypeOrSequenceUUID);
		if (gt != nullptr)gameName = gt->name;
		if (gs != nullptr)gameName = gs->name;
	}

	string difficultyName = "";
	if (difficultyString == "OVERALL")
	{
		difficultyName = "All Difficulties";
	}
	else
	{
		difficultyName = difficultyString;
	}

	/*
	
		class BobsGameLeaderBoardAndHighScoreBoardEntry
	{
	public:
		string userName = "";
		long userID = -1;

		//elo score should handle most of this
		int totalGamesPlayed = 0;
		int singlePlayerGamesPlayed = 0;
		int tournamentGamesPlayed = 0;
		int localMultiplayerGamesPlayed = 0;
		int tournamentGamesWon = 0;
		int tournamentGamesLost = 0;
		int singlePlayerGamesCompleted = 0;
		int singlePlayerGamesLost = 0;
		int singlePlayerHighestLevelReached = 0;
		long totalTimePlayed = 0;
		long longestGameLength = 0;
		long firstTimePlayed = 0;
		long lastTimePlayed = 0;
		long timeRecordSet = 0;
		double eloScore = 0;
		long planesWalkerPoints = 0;
		long totalBlocksCleared = 0;
		int biggestCombo = 0;
		int mostBlocksClearedInOneGame = 0;
		string statsUUID = "";
	};

	ArrayList<BobsGameLeaderBoardAndHighScoreBoardEntry*> entries;
	*/

	string titleName = "";

	if (totalTimePlayed)titleName = "Top Players (Total Time Played)";
	if (totalBlocksCleared)titleName = "Top Players (Total Blocks Cleared)";
	if (planeswalkerPoints)titleName = "Top Players (Planeswalker Points)";
	if (eloScore)titleName = "Top Players (Elo Score)";
	if (timeLasted)titleName = "Top Games (Time Lasted)";
	if (blocksCleared)titleName = "Top Games (Total Time Played)";

	menu->add(titleName);
	menu->add(gameName);
	menu->add(difficultyName);
	menu->addInfo(" ");

	for (int i = 0; i < stats->entries.size(); i++)
	{
		BobsGameLeaderBoardAndHighScoreBoard::BobsGameLeaderBoardAndHighScoreBoardEntry* e = stats->entries.get(i);
		string s = to_string(i)+") " + e->userName + " | ";

		if (totalTimePlayed)
		{
			menu->add(s+"Total Time Played: " + getNiceTime(e->totalTimePlayed));
		}
		if (totalBlocksCleared)
		{
			menu->add(s + "Total Blocks Cleared: " + to_string(e->totalBlocksCleared));
		}

		if (planeswalkerPoints)
		{
			menu->add(s + "Planeswalker Score: " + to_string(e->planesWalkerPoints));
		}

		if (eloScore)
		{
			menu->add(s + "Elo Score: " + to_string(e->eloScore));
		}

		if (timeLasted)
		{
			menu->add(s + "Longest Game Length: " + getNiceTime(e->longestGameLength));
		}

		if (blocksCleared)
		{
			menu->add(s + "Most Blocks Cleared: " + to_string(e->mostBlocksClearedInOneGame));
		}

//		menu->add("Total Games Played: " + to_string(e->totalGamesPlayed));
//		menu->add("Single Player Games Played: " + to_string(e->singlePlayerGamesPlayed));
//		menu->add("Single Player Games Completed: " + to_string(e->singlePlayerGamesCompleted));
//		menu->add("Single Player Games Failed: " + to_string(e->singlePlayerGamesLost));
//		menu->add("Local Multiplayer Games Played: " + to_string(e->localMultiplayerGamesPlayed));
//		menu->add("Tournament Games Played: " + to_string(e->tournamentGamesPlayed));
//		menu->add("Tournament Games Won: " + to_string(e->tournamentGamesWon));
//		menu->add("Tournament Games Lost: " + to_string(e->tournamentGamesLost));
//		menu->add("First Time Played: " + getDateFromEpochTime(e->firstTimePlayed));
//		menu->add("Time Record Set: " + getDateFromEpochTime(e->timeRecordSet));
//		menu->add("Biggest Combo: " + to_string(e->biggestCombo));
		
		
		menu->addInfo(" ");
	}

	if (deleteStats)delete stats;

}



//=========================================================================================================================
void BobsGame::selectSingleGameTypeMenuUpdate()
{//=========================================================================================================================

	if (selectSingleGameTypeMenu == nullptr)
	{
		selectSingleGameTypeMenu = new BobMenu(this, "");
		selectSingleGameTypeMenu->center = false;
		selectSingleGameTypeMenu->font = BobFont::ttf_oswald_12;


		populateGameTypesMenu(selectSingleGameTypeMenu);
		

		selectSingleGameTypeMenu->cursorPosition = selectSingleGameTypeMenuCursorPosition;
	}

	//make key repeat work
	if (getControlsManager()->MINIGAME_UP_HELD)
	{
		long long currentTime = System::currentHighResTimer();

		if(upRepeatedStarted==false)
		{
			selectSingleGameTypeMenu->up();
			upRepeatedStarted = true;
			upLastTime = currentTime;
		}
		else
		{
			
			long long startTime = upLastTime;
			int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

			if (upRepeating == false)
			{
				if (ticksPassed > 300)
				{
					upLastTime = currentTime;
					selectSingleGameTypeMenu->up();
					upRepeating = true;
				}
			}
			else
			{
				if (ticksPassed > 30)
				{
					upLastTime = currentTime;
					selectSingleGameTypeMenu->up();
				}
			}
		}
	}
	else
	{
		upRepeating = false;
		upRepeatedStarted = false;
	}

	if (getControlsManager()->MINIGAME_DOWN_HELD)
	{
		long long currentTime = System::currentHighResTimer();

		if (downRepeatedStarted == false)
		{
			selectSingleGameTypeMenu->down();
			downRepeatedStarted = true;
			downLastTime = currentTime;
		}
		else
		{
			long long startTime = downLastTime;
			int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

			if (downRepeating == false)
			{
				if (ticksPassed > 300)
				{
					downLastTime = currentTime;
					selectSingleGameTypeMenu->down();
					downRepeating = true;
				}
			}
			else
			{
				if (ticksPassed > 30)
				{
					downLastTime = currentTime;
					selectSingleGameTypeMenu->down();
				}
			}
		}
	}
	else
	{
		downRepeating = false;
		downRepeatedStarted = false;
	}

	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{

		for (int i = 0; i<loadedGameTypes.size(); i++)
		{
			GameType *g = loadedGameTypes.get(i);
			if (selectSingleGameTypeMenu->isSelectedID(g->uuid, clicked, mx, my))
			{

				if(statsMenuShowing)
				{
					statsMenu_gameSequenceOrTypeUUID = g->uuid;
				}
				else
				{

					currentRoom->multiplayer_SelectedGameSequence = new GameSequence();
					currentRoom->multiplayer_SelectedGameSequence->gameTypes.add(g);
					currentRoom->multiplayer_SelectedGameSequence->name = g->name;

					getPlayer1Game()->currentGameSequence = currentRoom->multiplayer_SelectedGameSequence;
				}
			}
		}


		//gameObjectiveMenuShowing = true;
		

		leaveMenu = true;
	}

//	if (getControlsManager()->miniGame_CANCEL_Pressed())
//	{
//		selectGameSequenceOrSingleGameTypeMenuShowing = true;
//		leaveMenu = true;
//	}

	if (leaveMenu)
	{
		selectSingleGameTypeMenuShowing = false;

		if (selectSingleGameTypeMenu != nullptr)
		{
			selectSingleGameTypeMenuCursorPosition = selectSingleGameTypeMenu->cursorPosition;
			delete selectSingleGameTypeMenu;
			selectSingleGameTypeMenu = nullptr;
		}
	}

}


//=========================================================================================================================
void BobsGame::selectSingleGameTypeMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(BobMenu::bgColor->ri(), BobMenu::bgColor->gi(), BobMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	BobTexture* t = keyboardTexture;

	if (selectSingleGameTypeMenu == nullptr)return;

	if (t != nullptr)
	{
		selectSingleGameTypeMenu->setGraphic(t, getWidth() / 3 * 2, getHeight() / 10);
	}

	selectSingleGameTypeMenu->render();
}





//=========================================================================================================================
void BobsGame::gameObjectiveMenuUpdate()
{//=========================================================================================================================

	const string PLAY_TO_CREDITS_LEVEL = "Play To Credits Level";
	const string ENDLESS = "Endless";

	if (gameObjectiveMenu == nullptr)
	{
		gameObjectiveMenu = new BobMenu(this, "");


		gameObjectiveMenu->add(PLAY_TO_CREDITS_LEVEL);
		gameObjectiveMenu->add(ENDLESS);
		

		gameObjectiveMenu->cursorPosition = gameObjectiveMenuCursorPosition;
	}



	if (getControlsManager()->miniGame_UP_Pressed())
	{
		gameObjectiveMenu->up();
	}

	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		gameObjectiveMenu->down();
	}

	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{


		if (gameObjectiveMenu->isSelectedID(PLAY_TO_CREDITS_LEVEL, clicked, mx, my))
		{
			selectedObjectiveIndex = (int)GameObjective::PLAY_TO_CREDITS_LEVEL;
			if(getPlayer1Game()->currentGameSequence!=nullptr)getPlayer1Game()->currentGameSequence->endlessMode = false;
			if(currentRoom->multiplayer_SelectedGameSequence!=nullptr)currentRoom->multiplayer_SelectedGameSequence->endlessMode = false;

		}

		if (gameObjectiveMenu->isSelectedID(ENDLESS, clicked, mx, my))
		{
			selectedObjectiveIndex = (int)GameObjective::ENDLESS;
			if (getPlayer1Game()->currentGameSequence != nullptr)getPlayer1Game()->currentGameSequence->endlessMode = true;
			if (currentRoom->multiplayer_SelectedGameSequence != nullptr)currentRoom->multiplayer_SelectedGameSequence->endlessMode = true;

		}


//		if (localMultiplayer || networkMultiplayer)
//		{
//			if (multiplayer_AllowDifferentDifficulties == false)
//			{
//				difficultyMenuShowing = true;
//			}
//			else
//				if (localMultiplayer)
//				{
//					localMultiplayerPlayerJoinMenuShowing = true;
//				}
//				else
//					if (networkMultiplayer)
//					{
//						networkMultiplayerPlayerJoinMenuShowing = true;
//					}
//		}
//		else
//		{
//			difficultyMenuShowing = true;
//		}

		leaveMenu = true;
	}

//	if (getControlsManager()->miniGame_CANCEL_Pressed())
//	{
//		if(localMultiplayer || networkMultiplayer)
//		{
//			multiplayerOptionsMenuShowing = true;
//		}
//		else
//		{
//			selectGameSequenceOrSingleGameTypeMenuShowing = true;
//		}
//		leaveMenu = true;
//	}

	if (leaveMenu)
	{
		gameObjectiveMenuShowing = false;

		if (gameObjectiveMenu != nullptr)
		{
			gameObjectiveMenuCursorPosition = gameObjectiveMenu->cursorPosition;
			delete gameObjectiveMenu;
			gameObjectiveMenu = nullptr;
		}
	}

}


//=========================================================================================================================
void BobsGame::gameObjectiveMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(BobMenu::bgColor->ri(), BobMenu::bgColor->gi(), BobMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	BobTexture* t = keyboardTexture;

	if (gameObjectiveMenu == nullptr)return;

	if (t != nullptr)
	{
		gameObjectiveMenu->setGraphic(t, getWidth() / 3 * 2, getHeight() / 10);
	}

	gameObjectiveMenu->render(getHeight()/2);
}



//=========================================================================================================================
void BobsGame::difficultyMenuUpdate()
{//=========================================================================================================================

	GameType gt;


	if (difficultyMenu == nullptr)
	{
		difficultyMenu = new BobMenu(this, "");
		difficultyMenu->center = false;

		if (localMultiplayer || networkMultiplayer)
		{
			difficultyMenu->add("Allow Different Difficulties");
		}

		if(statsMenuShowing)
		{
			difficultyMenu->add("All Difficulties", "Allow Different Difficulties");
		}

		for (int i = 0; i<gt.difficultyTypes.size(); i++)
		{
			difficultyMenu->add(gt.difficultyTypes.get(i)->name);
		}

		difficultyMenu->cursorPosition = difficultyMenuCursorPosition;
	}



	if (getControlsManager()->miniGame_UP_Pressed())
	{
		difficultyMenu->up();
	}

	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		difficultyMenu->down();
	}

	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{

		if (difficultyMenu->isSelectedID("Allow Different Difficulties", clicked, mx, my))
		{
			if (localMultiplayer || networkMultiplayer)
			{
				currentRoom->multiplayer_AllowDifferentDifficulties = true;
			}

			if(statsMenuShowing)
			{
				statsMenu_difficultyName = "OVERALL";
			}
		}

		for (int i = 0; i<gt.difficultyTypes.size(); i++)
		{

			string difficultyName = gt.difficultyTypes.get(i)->name;
			if (difficultyMenu->isSelectedID(difficultyName, clicked, mx, my))
			{

				if (statsMenuShowing == false)
				{
					currentRoom->multiplayer_AllowDifferentDifficulties = false;
					currentRoom->multiplayer_SelectedDifficultyName = difficultyName;

					if (getPlayer1Game()->currentGameSequence != nullptr)
						getPlayer1Game()->currentGameSequence->currentDifficultyName = currentRoom->multiplayer_SelectedDifficultyName;
				}
				else
				{
					statsMenu_difficultyName = difficultyName;
				}

			}
		}

//		if (localMultiplayer)
//		{
//			localMultiplayerPlayerJoinMenuShowing = true;
//		}
//		else
//			if (networkMultiplayer)
//			{
//				networkMultiplayerPlayerJoinMenuShowing = true;
//			}
//			else
//			{
//				//start single player game	
//			}

		leaveMenu = true;
	}

//	if (getControlsManager()->miniGame_CANCEL_Pressed())
//	{
//		if (localMultiplayer || networkMultiplayer)
//		{
//			multiplayerOptionsMenuShowing = true;
//		}
//		else
//		{
//			selectGameSequenceOrSingleGameTypeMenuShowing = true;
//		}
//		leaveMenu = true;
//	}

	if (leaveMenu)
	{
		difficultyMenuShowing = false;

		if (difficultyMenu != nullptr)
		{
			difficultyMenuCursorPosition = difficultyMenu->cursorPosition;
			delete difficultyMenu;
			difficultyMenu = nullptr;
		}
	}

}


//=========================================================================================================================
void BobsGame::difficultyMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(BobMenu::bgColor->ri(), BobMenu::bgColor->gi(), BobMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	BobTexture* t = keyboardTexture;

	if (difficultyMenu == nullptr)return;

	if (t != nullptr)
	{
		difficultyMenu->setGraphic(t, getWidth() / 3 * 2, getHeight() / 10);
	}

	difficultyMenu->render(getHeight() / 2);
}



//=========================================================================================================================
void BobsGame::multiplayerOptionsMenuUpdate()
{//=========================================================================================================================


	//const string ALLOW_DIFFERENT_GAME_SEQUENCES_OR_TYPES = "Game Sequence: Allow Different Game Sequences Or Types";
	//const string ALLOW_DIFFERENT_DIFFICULTIES = "Difficulty: Allow Different Difficulties";
	//const string GAME_ENDS_WHEN_ALL_OPPONENTS_LOSE = "Game Ends When All Opponents Lose";
	//const string GAME_ENDS_WHEN_SOMEONE_COMPLETES_CREDITS_LEVEL = "Game Ends When Someone Completes Credits Level";
	//const string DISABLE_VS_GARBAGE = "Disable Sending VS Garbage";
	//const string CONTINUE = "Continue";

	if (multiplayerOptionsMenu == nullptr)
	{


		if(networkMultiplayer)
		{
			multiplayerOptionsMenu = new BobMenu(this, "Set Network Multiplayer Room Options");
			multiplayerOptionsMenu->center = false;
			multiplayerOptionsMenu->add("Visibility: Public", "Public Or Private");
			multiplayerOptionsMenu->add("Score Mode: Free Play", "Free Play Or Tournament");
			multiplayerOptionsMenu->add("Max Players: Unlimited", "Max Players");
			multiplayerOptionsMenu->addInfo(" ", " ");

		}
		else
		{
			multiplayerOptionsMenu = new BobMenu(this, "Set Local Multiplayer Options");
			multiplayerOptionsMenu->center = false;
		}

		multiplayerOptionsMenu->add("Game Sequence: Allow Different Game Sequences Or Types", "Select Game");
		multiplayerOptionsMenu->add("Difficulty: Allow Different Difficulties", "Difficulty");
		multiplayerOptionsMenu->add("End Rule: Game Ends When One Player Remains", "End Rule");
		multiplayerOptionsMenu->add("Finish Rule: Race To Credits Level", "Finish Rule");
		multiplayerOptionsMenu->add("Garbage Rule: Enable VS Garbage", "Garbage Rule");
		multiplayerOptionsMenu->addInfo(" "," ");
		multiplayerOptionsMenu->add("Continue");
		multiplayerOptionsMenu->addInfo(" ", " ");
		if(networkMultiplayer)multiplayerOptionsMenu->add("Back To Network Multiplayer Lobby");
		else multiplayerOptionsMenu->add("Back To Title Screen");
		

		multiplayerOptionsMenu->cursorPosition = multiplayerOptionsMenuCursorPosition;
	}


	if(currentRoom==nullptr)
	{
		currentRoom = new Room();

	}
	if(currentRoom->multiplayer_SelectedGameSequence == nullptr)
	{
		currentRoom->multiplayer_SelectedGameSequence = new GameSequence();
		currentRoom->multiplayer_SelectedGameSequence->gameTypes.add(new GameType());
	}


	if(currentRoom->multiplayer_AllowDifferentGameSequences)
	{
		multiplayerOptionsMenu->getMenuItemByID("Select Game")->setText("Game Sequence: Allow Different Game Sequences Or Types");
	}
	else
	if (currentRoom->multiplayer_SelectedGameSequence != nullptr)
	{
		{
			Caption *c = multiplayerOptionsMenu->getCaptionByID("Select Game");
			if (c != nullptr)
			{
				if (currentRoom->multiplayer_SelectedGameSequence->gameTypes.size() > 1)c->setText("Game Sequence: " + currentRoom->multiplayer_SelectedGameSequence->name);
				if (currentRoom->multiplayer_SelectedGameSequence->gameTypes.size() == 1)c->setText("Game Type: " + currentRoom->multiplayer_SelectedGameSequence->name);
			}
		}
	}


	if (currentRoom->multiplayer_AllowDifferentDifficulties)
	{
		Caption *c = multiplayerOptionsMenu->getCaptionByID("Difficulty");
		if (c != nullptr)c->setText("Difficulty: Allow Different Difficulties");
	}
	else
	if (currentRoom->multiplayer_SelectedDifficultyName != "")
	{

		GameType gt;
		for (int i = 0; i < gt.difficultyTypes.size(); i++)
		{
			string difficultyName = gt.difficultyTypes.get(i)->name;
			if (currentRoom->multiplayer_SelectedDifficultyName == difficultyName)selectedDifficultyIndex = i + 1;
		}

		DifficultyType *d = gt.difficultyTypes.get(selectedDifficultyIndex - 1);
		string difficultyName = d->name;
		currentRoom->multiplayer_SelectedDifficultyName = difficultyName;
		if (getPlayer1Game()->currentGameSequence != nullptr)
			getPlayer1Game()->currentGameSequence->currentDifficultyName = difficultyName;

		Caption *c = multiplayerOptionsMenu->getCaptionByID("Difficulty");
		if (c != nullptr)c->setText("Difficulty: " + difficultyName);
	}


	if (networkMultiplayer)
	{
		if (currentRoom->privateRoom)multiplayerOptionsMenu->getMenuItemByID("Public Or Private")->setText("Visibility: Private (Friends Only)");
		else multiplayerOptionsMenu->getMenuItemByID("Public Or Private")->setText("Visibility: Public");

		if (currentRoom->tournamentRoom)multiplayerOptionsMenu->getMenuItemByID("Free Play Or Tournament")->setText("Score Mode: Tournament (Counts Towards Ranking)");
		else multiplayerOptionsMenu->getMenuItemByID("Free Play Or Tournament")->setText("Score Mode: Free Play");

		if (currentRoom->maxPlayers < 2)multiplayerOptionsMenu->getMenuItemByID("Max Players")->setText("Max Players: Unlimited");
		else multiplayerOptionsMenu->getMenuItemByID("Max Players")->setText("Max Players: " + to_string(currentRoom->maxPlayers));
	}

	if (currentRoom->multiplayer_DisableVSGarbage)multiplayerOptionsMenu->getMenuItemByID("Garbage Rule")->setText("Garbage Rule: Disable VS Garbage");
	else multiplayerOptionsMenu->getMenuItemByID("Garbage Rule")->setText("Garbage Rule: VS Garbage Allowed");


	if (currentRoom->multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel)multiplayerOptionsMenu->getMenuItemByID("Finish Rule")->setText("Finish Rule: Race To Credits Level");
	else multiplayerOptionsMenu->getMenuItemByID("Finish Rule")->setText("Finish Rule: Endless Mode");


	if (currentRoom->multiplayer_GameEndsWhenOnePlayerRemains)multiplayerOptionsMenu->getMenuItemByID("End Rule")->setText("End Rule: Game Ends When One Player Remains");
	else multiplayerOptionsMenu->getMenuItemByID("End Rule")->setText("End Rule: Continue Until All Players Lose");




	if (selectGameSequenceOrSingleGameTypeMenuShowing)
	{
		selectGameSequenceOrSingleGameTypeMenuUpdate();
	}
	else
	if (selectGameSequenceMenuShowing)
	{
		selectGameSequenceMenuUpdate();
	}
	else
	if (selectSingleGameTypeMenuShowing)
	{
		selectSingleGameTypeMenuUpdate();
	}
	else
	if (gameSequenceOptionsMenuShowing)
	{
		gameSequenceOptionsMenuUpdate();
	}
	else
	if (difficultyMenuShowing)
	{
		difficultyMenuUpdate();
	}
	else
	{

		if (getControlsManager()->miniGame_UP_Pressed())
		{
			multiplayerOptionsMenu->up();
		}

		if (getControlsManager()->miniGame_DOWN_Pressed())
		{
			multiplayerOptionsMenu->down();
		}

		bool leaveMenu = false;


		bool left = getControlsManager()->miniGame_LEFT_Pressed();
		bool right = getControlsManager()->miniGame_RIGHT_Pressed();
		
		if(left || right)
		{
			
			if (multiplayerOptionsMenu->isSelectedID("Difficulty"))
			{
				GameType gt;
				if (left)
				{
					selectedDifficultyIndex--;
					if (selectedDifficultyIndex < 0)selectedDifficultyIndex = gt.difficultyTypes.size();//-1
				}
				if (right)
				{
					selectedDifficultyIndex++;
					if (selectedDifficultyIndex > gt.difficultyTypes.size())selectedDifficultyIndex = 0;
				}

				if (selectedDifficultyIndex > 0)
				{
					currentRoom->multiplayer_AllowDifferentDifficulties = false;
					DifficultyType *d = gt.difficultyTypes.get(selectedDifficultyIndex - 1);
					string difficultyName = d->name;
					currentRoom->multiplayer_SelectedDifficultyName = difficultyName;
					if (getPlayer1Game()->currentGameSequence != nullptr)
						getPlayer1Game()->currentGameSequence->currentDifficultyName = difficultyName;
				}
				else
				{
					currentRoom->multiplayer_AllowDifferentDifficulties = true;
				}
			}

		}

		bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
		bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
		int mx = getControlsManager()->getMouseX();
		int my = getControlsManager()->getMouseY();
		if (confirm || left || right || clicked)
		{

			if (multiplayerOptionsMenu->isSelectedID("End Rule", clicked, mx, my))
			{
				currentRoom->multiplayer_GameEndsWhenOnePlayerRemains = !currentRoom->multiplayer_GameEndsWhenOnePlayerRemains;
			}

			if (multiplayerOptionsMenu->isSelectedID("Finish Rule", clicked, mx, my))
			{
				currentRoom->multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel = !currentRoom->multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel;
			}

			if (multiplayerOptionsMenu->isSelectedID("Garbage Rule", clicked, mx, my))
			{
				currentRoom->multiplayer_DisableVSGarbage = !currentRoom->multiplayer_DisableVSGarbage;
			}

			if (multiplayerOptionsMenu->isSelectedID("Public Or Private", clicked, mx, my))
			{
				currentRoom->privateRoom = !currentRoom->privateRoom;
			}

			if (multiplayerOptionsMenu->isSelectedID("Free Play Or Tournament", clicked, mx, my))
			{
				currentRoom->tournamentRoom = !currentRoom->tournamentRoom;
			}

			if (multiplayerOptionsMenu->isSelectedID("Max Players", clicked, mx, my))
			{
				currentRoom->maxPlayers = -1;
			}

		}

		if(left)
		{
			if (multiplayerOptionsMenu->isSelectedID("Max Players"))
			{
				long long startTime = timeLastChangedSetting;
				long long currentTime = System::currentHighResTimer();
				int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

				if (ticksPassed > 15)
				{
					timeLastChangedSetting = currentTime;
					if (currentRoom->maxPlayers > -1) currentRoom->maxPlayers--;
					if (currentRoom->maxPlayers < 2)currentRoom->maxPlayers = -1;
				}
			}
		}

		if(right)
		{
			if (multiplayerOptionsMenu->isSelectedID("Max Players"))
			{
				long long startTime = timeLastChangedSetting;
				long long currentTime = System::currentHighResTimer();
				int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

				if (ticksPassed > 15)
				{
					timeLastChangedSetting = currentTime;
					if (currentRoom->maxPlayers < 1)currentRoom->maxPlayers = 1;
					currentRoom->maxPlayers++;
				}
			}
		}

		if (confirm || clicked)
		{

			if (multiplayerOptionsMenu->isSelectedID("Select Game", clicked, mx, my))
			{
				selectGameSequenceOrSingleGameTypeMenuShowing = true;
			}

			if (multiplayerOptionsMenu->isSelectedID("Difficulty", clicked, mx, my))
			{
				difficultyMenuShowing = true;
			}

			if (multiplayerOptionsMenu->isSelectedID("Continue", clicked, mx, my))
			{

				if (localMultiplayer)
				{
					localMultiplayerPlayerJoinMenuShowing = true;
				}
				else
					if (networkMultiplayer)
					{
						networkMultiplayerPlayerJoinMenuShowing = true;
					}


				leaveMenu = true;
			}

			if (multiplayerOptionsMenu->isSelectedID("Back To Title Screen", clicked, mx, my))
			{
				startScreenMenuShowing = true;

				leaveMenu = true;
			}

			if (multiplayerOptionsMenu->isSelectedID("Back To Network Multiplayer Lobby", clicked, mx, my))
			{
				networkMultiplayerLobbyMenuShowing = true;

				leaveMenu = true;
			}
		}


		if (getControlsManager()->miniGame_CANCEL_Pressed())
		{
			if(networkMultiplayer)networkMultiplayerLobbyMenuShowing = true;
			else startScreenMenuShowing = true;

			leaveMenu = true;
		}

		if (leaveMenu)
		{
			multiplayerOptionsMenuShowing = false;

			if (multiplayerOptionsMenu != nullptr)
			{
				multiplayerOptionsMenuCursorPosition = multiplayerOptionsMenu->cursorPosition;
				delete multiplayerOptionsMenu;
				multiplayerOptionsMenu = nullptr;
			}
		}
	}

}


//=========================================================================================================================
void BobsGame::multiplayerOptionsMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(BobMenu::bgColor->ri(), BobMenu::bgColor->gi(), BobMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	BobTexture* t = onlineTexture;

	if (multiplayerOptionsMenu == nullptr)return;

	if (t != nullptr)
	{
		multiplayerOptionsMenu->setGraphic(t, getWidth() / 3 * 2, getHeight() / 8);
	}

	multiplayerOptionsMenu->render(getHeight() / 2, getWidth() / 2 - 50);


	if (selectGameSequenceOrSingleGameTypeMenuShowing && selectGameSequenceOrSingleGameTypeMenu != nullptr)
	{
		Caption *c = multiplayerOptionsMenu->getCaptionByID("Select Game");
		selectGameSequenceOrSingleGameTypeMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, GLUtils::getViewportHeight(), true, nullptr, nullptr, true);
	}

	if (selectGameSequenceMenuShowing && selectGameSequenceMenu != nullptr)
	{
		Caption *c = multiplayerOptionsMenu->getCaptionByID("Select Game");
		selectGameSequenceMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, GLUtils::getViewportHeight(), true, nullptr, nullptr, true);
	}

	if (selectSingleGameTypeMenuShowing && selectSingleGameTypeMenu != nullptr)
	{
		Caption *c = multiplayerOptionsMenu->getCaptionByID("Select Game");
		selectSingleGameTypeMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, GLUtils::getViewportHeight(), true, nullptr, nullptr, true);
	}

	if (gameSequenceOptionsMenuShowing && gameSequenceOptionsMenu != nullptr)
	{
		Caption *c = multiplayerOptionsMenu->getCaptionByID("Select Game");
		gameSequenceOptionsMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, GLUtils::getViewportHeight(), true, nullptr, nullptr, true);
	}

	if (difficultyMenuShowing && difficultyMenu != nullptr)
	{
		Caption *c = multiplayerOptionsMenu->getCaptionByID("Difficulty");
		difficultyMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, GLUtils::getViewportHeight(), true, nullptr, nullptr, true);
	}

}






//=========================================================================================================================
void BobsGame::localMultiplayerPlayerJoinMenuUpdate()
{//=========================================================================================================================

	if (localMultiplayerPlayerJoinMenu == nullptr)
	{
		localMultiplayerPlayerJoinMenu = new BobMenu(this, "Local Multiplayer Host/Join Menu");
		localMultiplayerPlayerJoinMenu->addInfo("Press the Space key or A on your controller to join");
		localMultiplayerPlayerJoinMenu->addInfo("Press Esc or Select on your controller to return to Title Screen");


		players.deleteAll();
//		while (players.size()>0)
//		{
//			PuzzlePlayer *p = players.get(players.size() - 1);
//			players.removeAt(players.size() - 1);
//			delete p;
//		}
	}

	bool leaveMenu = false;

	//select player, show icon for gamepad or keyboard
	//show mini difficulty menu
	//if press a, ready
	//if both ready, game start

	bool ready = true;
	for (int i = 0; i<players.size(); i++)
	{
		PuzzlePlayer *p = players.get(i);
		if (p->confirmed == false)
		{
			ready = false;
			

			if (p->setGameSequence == false)
			{
				if (currentRoom->multiplayer_AllowDifferentGameSequences)
				{
					playerGameSequenceMiniMenuUpdate(p);
				}
				else
				{
					p->gameLogic->currentGameSequence = currentRoom->multiplayer_SelectedGameSequence;
					p->setGameSequence = true;
				}
			}
			else
			if (p->setDifficulty == false)
			{
				if (currentRoom->multiplayer_AllowDifferentDifficulties)
				{
					playerDifficultyMiniMenuUpdate(p);
				}
				else
				{
					p->gameLogic->currentGameSequence->currentDifficultyName = currentRoom->multiplayer_SelectedDifficultyName;
					p->setDifficulty = true;
				}
			}
			else
			if(p->confirmed==false)
			{
				p->confirmed = true;

				p->gameCaption = getCaptionManager()->newManagedCaption(0, 0, -1, p->gameLogic->currentGameSequence->name, BobFont::ttf_oswald_12, BobMenu::menuColor, BobMenu::clearColor, RenderOrder::OVER_GUI);
				p->difficultyCaption = getCaptionManager()->newManagedCaption(0, 0, -1, p->gameLogic->currentGameSequence->currentDifficultyName, BobFont::ttf_oswald_12, BobMenu::menuColor, BobMenu::clearColor, RenderOrder::OVER_GUI);
			}

			
		}
	}

	if (players.size() > 1)
	{
		if (ready)
		{
			if (localMultiplayerPressStartCaption == nullptr) 
			{
				localMultiplayerPressStartCaption = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, (int)(getHeight() - 50), -1, "Press the Enter key or Start on your controller to start game", BobFont::ttf_oswald_16, BobMenu::menuColor, BobMenu::clearColor, RenderOrder::OVER_GUI);
				localMultiplayerPressStartCaption->flashing = true;
				localMultiplayerPressStartCaption->flashingTicksPerFlash = 1000;
			}

			if (getControlsManager()->miniGame_START_Pressed())
			{
				//start the game!

				leaveMenu = true;
			}
		}
	}

	if (players.size() <= 1 || ready == false)
	{
		if (localMultiplayerPressStartCaption != nullptr)
		{
			localMultiplayerPressStartCaption->setToBeDeletedImmediately();
			localMultiplayerPressStartCaption = nullptr;
		}
	}

	//int maxPlayers = 4;
	if (getControlsManager()->key_SPACE_Pressed())
	{
		//if (players.size() < maxPlayers)
		{
			bool alreadyInUse = false;
			for (int i = 0; i < players.size(); i++)
			{
				PuzzlePlayer *p = players.get(i);
				if (p->useKeyboard)alreadyInUse = true;
			}
			if (!alreadyInUse)
			{
				PuzzlePlayer *p = new PuzzlePlayer(new GameLogic(this, -1));
				p->useKeyboard = true;
				players.add(p);
				p->nameCaption = getCaptionManager()->newManagedCaption(0, 0, -1, "Local (Keyboard)", BobFont::ttf_oswald_12, BobMenu::menuColor, BobMenu::clearColor, RenderOrder::OVER_GUI);
			}
		}
	}
	if (getControlsManager()->key_LSHIFT_Pressed())
	{
		for (int i = 0; i < players.size(); i++)
		{
			PuzzlePlayer *p = players.get(i);
			if (p->useKeyboard)
			{
				players.removeAt(i);
				delete p;
				i = 0;
			}
		}
	}


	for (int controllerNum = 0; controllerNum < getControlsManager()->gameControllers.size(); controllerNum++)
	{
		GameController *g = getControlsManager()->gameControllers.get(controllerNum);

		if (g->a_Pressed())
		{
			//if (players.size() < maxPlayers)
			{
				bool alreadyInUse = false;
				for (int i = 0; i < players.size(); i++)
				{
					PuzzlePlayer *p = players.get(i);
					if (p->gameController == g)alreadyInUse = true;
				}

				if (!alreadyInUse)
				{
					PuzzlePlayer *p = new PuzzlePlayer(new GameLogic(this, -1));
					p->gameController = g;
					players.add(p);
					p->nameCaption = getCaptionManager()->newManagedCaption(0, 0, -1, "Local (Controller " + to_string(controllerNum) + ")", BobFont::ttf_oswald_12, BobMenu::menuColor, BobMenu::clearColor, RenderOrder::OVER_GUI);
				}
			}
		}

		if (g->b_Pressed())
		{
			for (int i = 0; i < players.size(); i++)
			{
				PuzzlePlayer *p = players.get(i);
				if (p->gameController == g)
				{
					players.removeAt(i);
					delete p;
					i = 0;
				}
			}
		}
	}


	if (getControlsManager()->key_ESC_Pressed() || getControlsManager()->miniGame_SELECT_Pressed())
	{
		leaveMenu = true;
		startScreenMenuShowing = true;

		initPlayer();
	}

	if (leaveMenu)
	{
		localMultiplayerPlayerJoinMenuShowing = false;

		if (localMultiplayerPlayerJoinMenu != nullptr)
		{
			delete localMultiplayerPlayerJoinMenu;
			localMultiplayerPlayerJoinMenu = nullptr;
		}

		if (localMultiplayerPressStartCaption != nullptr)
		{
			localMultiplayerPressStartCaption->setToBeDeletedImmediately();
			localMultiplayerPressStartCaption = nullptr;
		}
	}

}


//=========================================================================================================================
void BobsGame::localMultiplayerPlayerJoinMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(BobMenu::bgColor->ri(), BobMenu::bgColor->gi(), BobMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	BobTexture* kt = keyboardIconTexture;
	BobTexture* gt = controllerIconTexture;


	for (int i = 0; i < players.size(); i++)
	{
		PuzzlePlayer *p = players.get(i);

		BobTexture *t = nullptr;

		if (p->useKeyboard)t = kt;
		else
			if (p->gameController != nullptr)t = gt;

		float sx0 = 0;
		float sx1 = 0;
		float sy0 = 0;
		float sy1 = 0;

		if (t != nullptr)
		{
			int slot = players.size();
			if (slot < 2)slot = 2;

			float tx0 = 0;
			float tx1 = (float)(t->getImageWidth()) / (float)(t->getTextureWidth());
			float ty0 = 0;
			float ty1 = (float)((float)(t->getImageHeight()) / (float)(t->getTextureHeight()));

			float ratio = (float)(getWidth() / slot / 6 * 2) / (float)(t->getImageWidth());

			sx0 = (float)((int)(getWidth() / slot*i + getWidth() / slot / 6 * 2));
			sx1 = sx0 + (int)((getWidth() / slot) / 6 * 2);
			sy0 = (float)((int)(getHeight() / 6 * 1));
			sy1 = sy0 + (float)((int)(t->getImageHeight() * ratio));

			GLUtils::drawTexture(t, tx0, tx1, ty0, ty1, sx0, sx1, sy0, sy1, 1.0f, GLUtils::FILTER_NEAREST);
		}

		float x = (float)((int)sx0);
		float y = (float)((int)sy1 + 6);
		if (p->confirmed == false)
		{
			playerDifficultyMiniMenuRender(p, x, y);
		}
		else
		{
			//draw greencheck mark or green box or something?
			GLUtils::drawFilledRect(0, 255, 0, sx0, sx1, sy0, sy1, 0.2f);

			if (p->gameCaption != nullptr)
			{
				p->gameCaption->screenX = sx0;
				p->gameCaption->screenY = sy1 + 4;
				//p->gameCaption->render();
			}
			if (p->difficultyCaption != nullptr)
			{
				p->difficultyCaption->screenX = sx0;
				p->difficultyCaption->screenY = sy1 + 4 + 16;
				//p->difficultyCaption->render();
			}
		}

		//need to render friend name and player number
		if (p->nameCaption != nullptr)
		{
			p->nameCaption->screenX = sx0;
			p->nameCaption->screenY = sy1 - 12;
			//p->nameCaption->render();
		}
	}

	if (localMultiplayerPlayerJoinMenu == nullptr)return;

	localMultiplayerPlayerJoinMenu->render(getHeight() / 4 * 3);

}



//=========================================================================================================================
void BobsGame::playerDifficultyMiniMenuUpdate(PuzzlePlayer *p)
{//=========================================================================================================================

	if (p != nullptr)
	{

		

		if (p->menu == nullptr)
		{
			p->menu = new BobMenu(this, "");
			p->menu->center = false;
			p->menu->font = BobFont::ttf_oswald_12;
			GameType g;

			for (int i = 0; i<g.difficultyTypes.size(); i++)
			{
				p->menu->add(g.difficultyTypes.get(i)->name);
			}
		}

		{
			bool up = false;
			bool down = false;
			bool a = false;
			if (p->useKeyboard)
			{
				if (getControlsManager()->key_UP_Pressed())up = true;
				if (getControlsManager()->key_DOWN_Pressed())down = true;
				if (getControlsManager()->key_SPACE_Pressed())a = true;
			}
			else
			{
				GameController *g = p->gameController;
				if (g != nullptr)
				{
					if (g->up_Pressed())up = true;
					if (g->down_Pressed())down = true;
					if (g->a_Pressed())a = true;
				}
			}

			if (up)
			{
				p->menu->up();
			}

			if (down)
			{
				p->menu->down();
			}

			if (a)
			{
				GameLogic *game = p->gameLogic;
				GameType g;

				for (int i = 0; i<g.difficultyTypes.size(); i++)
				{
					string difficultyName = g.difficultyTypes.get(i)->name;

					if (p->menu->isSelectedID(difficultyName))
					{
						game->currentGameSequence->currentDifficultyName = difficultyName;
						p->setDifficulty = true;
					}
				}

				if (p->menu != nullptr)
				{
					delete p->menu;
					p->menu = nullptr;
				}
			
				
			}
		}
	}

}

//=========================================================================================================================
void BobsGame::playerDifficultyMiniMenuRender(PuzzlePlayer *p, float x, float y)
{//=========================================================================================================================

	if (p->menu != nullptr)
	{
		p->menu->render((int)y, (int)x);
	}
}

//=========================================================================================================================
void BobsGame::playerGameSequenceMiniMenuUpdate(PuzzlePlayer *p)
{//=========================================================================================================================


	const string PLAY_GAME_SEQUENCE = "Play Game Sequence";
	const string PLAY_SINGLE_GAME_TYPE = "Play Single Game Type";


	const string RANDOMIZE_SEQUENCE = "Randomize Sequence";
	const string PLAY_THROUGH_SEQUENCE_IN_ORDER = "Play Through Sequence In Order";


	if (p != nullptr)
	{
		if (p->menu == nullptr)
		{
			p->menu = new BobMenu(this, "");
			p->menu->center = false;
			p->menu->font = BobFont::ttf_oswald_12;

			if (p->selectGameSequenceOrSingleGameTypeMiniMenuShowing)
			{
				p->menu->add(PLAY_GAME_SEQUENCE);
				p->menu->add(PLAY_SINGLE_GAME_TYPE);
			}

			if(p->selectGameSequenceMiniMenuShowing)
			{
				populateGameSequencesMenu(p->menu);
			}

			if (p->gameSequenceOptionsMiniMenuShowing)
			{
				p->menu->add(RANDOMIZE_SEQUENCE);
				p->menu->add(PLAY_THROUGH_SEQUENCE_IN_ORDER);
			}

			if(p->selectSingleGameTypeMiniMenuShowing)
			{
				populateGameTypesMenu(p->menu);
			}
		}

		{
			bool up = false;
			bool down = false;
			bool a = false;
			if (p->useKeyboard)
			{
				if (getControlsManager()->KEY_UP_HELD)up = true;
				if (getControlsManager()->KEY_DOWN_HELD)down = true;
				if (getControlsManager()->key_SPACE_Pressed())a = true;
			}
			else
			{
				GameController *g = p->gameController;
				if (g != nullptr)
				{
					if (g->UP_HELD)up = true;
					if (g->DOWN_HELD)down = true;
					if (g->a_Pressed())a = true;
				}
			}

			if (up)
			{
				long long currentTime = System::currentHighResTimer();

				if (p->upRepeatedStarted == false)
				{
					p->menu->up();
					p->upRepeatedStarted = true;
					p->upLastTime = currentTime;
				}
				else
				{

					long long startTime = p->upLastTime;
					int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

					if (p->upRepeating == false)
					{
						if (ticksPassed > 300)
						{
							p->upLastTime = currentTime;
							p->menu->up();
							p->upRepeating = true;
						}
					}
					else
					{
						if (ticksPassed > 30)
						{
							p->upLastTime = currentTime;
							p->menu->up();
						}
					}
				}
			}
			else
			{
				p->upRepeating = false;
				p->upRepeatedStarted = false;
			}

			if (down)
			{
				long long currentTime = System::currentHighResTimer();

				if (p->downRepeatedStarted == false)
				{
					p->menu->down();
					p->downRepeatedStarted = true;
					p->downLastTime = currentTime;
				}
				else
				{
					long long startTime = p->downLastTime;
					int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

					if (p->downRepeating == false)
					{
						if (ticksPassed > 300)
						{
							p->downLastTime = currentTime;
							p->menu->down();
							p->downRepeating = true;
						}
					}
					else
					{
						if (ticksPassed > 30)
						{
							p->downLastTime = currentTime;
							p->menu->down();
						}
					}
				}
			}
			else
			{
				p->downRepeating = false;
				p->downRepeatedStarted = false;
			}

			if (a)
			{
				GameLogic *game = p->gameLogic;

				if (p->selectGameSequenceOrSingleGameTypeMiniMenuShowing)
				{
					if (p->menu->isSelectedID(PLAY_GAME_SEQUENCE))
					{
						p->selectGameSequenceMiniMenuShowing = true;
					}
					if (p->menu->isSelectedID(PLAY_SINGLE_GAME_TYPE))
					{
						p->selectSingleGameTypeMiniMenuShowing = true;
					}

					p->selectGameSequenceOrSingleGameTypeMiniMenuShowing = false;
				}
				else
				if(p->selectGameSequenceMiniMenuShowing)
				{
					for (int i = 0; i<loadedGameSequences.size(); i++)
					{

						GameSequence *gs = loadedGameSequences.get(i);
						if (p->menu->isSelectedID(gs->uuid))
						{
							game->currentGameSequence = gs;
							p->gameSequenceOptionsMiniMenuShowing = true;
						}
					}

					p->selectGameSequenceMiniMenuShowing = false;

				}
				else
				if(p->gameSequenceOptionsMiniMenuShowing)
				{
					if (p->menu->isSelectedID(RANDOMIZE_SEQUENCE))
					{
						game->currentGameSequence->randomizeSequence = true;
					}

					if (p->menu->isSelectedID(PLAY_THROUGH_SEQUENCE_IN_ORDER))
					{
						game->currentGameSequence->randomizeSequence = false;
					}

					p->setGameSequence = true;
					p->gameSequenceOptionsMiniMenuShowing = false;


				}
				else
				if(p->selectSingleGameTypeMiniMenuShowing)
				{


					for (int i = 0; i<loadedGameTypes.size(); i++)
					{
						GameType *g = loadedGameTypes.get(i);
						if (p->menu->isSelectedID(g->uuid))
						{
							game->currentGameSequence = new GameSequence();
							game->currentGameSequence->gameTypes.add(g);
							game->currentGameSequence->name = g->name;
						}
					}

					p->setGameSequence = true;
					p->selectSingleGameTypeMiniMenuShowing = false;

				}

				if (p->menu != nullptr)
				{
					delete p->menu;
					p->menu = nullptr;
				}
				
			}
		}
	}

}

//=========================================================================================================================
void BobsGame::playerGameSequenceMiniMenuRender(PuzzlePlayer *p, float x, float y)
{//=========================================================================================================================

	if (p->menu != nullptr)
	{
		p->menu->render((int)y, (int)x);
	}
}

