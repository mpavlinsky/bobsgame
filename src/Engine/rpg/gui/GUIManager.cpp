#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger GUIManager::log = Logger("GUIManager");


string GUIManager::lightThemeString = "lightMenu";
string GUIManager::darkThemeString = "darkMenu";
string GUIManager::subMenuPanelDialogLayoutTheme = "subMenuPanelDialogLayout";
string GUIManager::emptyDialogLayoutTheme = "invisibleScrollPaneContentContainerDialogLayout";
string GUIManager::buttonTheme = "oppositeThemeButton";
string GUIManager::checkboxTheme = "checkbox";
string GUIManager::scrollPaneTheme = "themedScrollPane";

GUIManager::GUIManager(BGClientEngine* g)
{ //=========================================================================================================================


	this->e = g;


	//------------------------------
	// login screen
	//------------------------------

	//this has to be run before making the gui, something in the createThemeManager function delays the texture creation or something

	//game.update(1000);//this will start the map cam already scrolled
	//game.render();
	//map().draw(1);
	//glClear(GL_COLOR_BUFFER_BIT);


	stuffMenu = new StuffMenu();
	playerEditMenu = new PlayerEditMenu();
	gameStore = new GameStore();
	keyboardScreen = new KeyboardScreen();
	//
	//   
	//   stuffMenuGUI = new GUI(stuffMenu, GLUtils::TWLrenderer);
	//   stuffMenuGUI->applyTheme(GLUtils::TWLthemeManager);
	//
	//

	//   gameStoreGUI = new GUI(gameStore, GLUtils::TWLrenderer);
	//   gameStoreGUI->applyTheme(GLUtils::TWLthemeManager);
	//
	//   
	//   playerEditGUI = new GUI(playerEditMenu, GLUtils::TWLrenderer);
	//   playerEditGUI->applyTheme(GLUtils::TWLthemeManager);
	//
	//
	//   
	//   keyboardScreenGUI = new GUI(keyboardScreen, GLUtils::TWLrenderer);
	//   keyboardScreenGUI->applyTheme(GLUtils::TWLthemeManager);
}

void GUIManager::init()
{ //=========================================================================================================================

	stuffMenu->init();
	//loadingScreen.init();
	//gameStore->init();
	playerEditMenu->init();
}

void GUIManager::update()
{ //=========================================================================================================================


	//set x, y, timer

	stuffMenu->update();
	gameStore->update();
	playerEditMenu->update();
	keyboardScreen->update();

	for (int i = 0; i < gameChallenges->size(); i++)
	{
		GameChallengeNotificationPanel* g = gameChallenges->get(i);
		g->update();
	}
}

void GUIManager::render()
{ //=========================================================================================================================


	//render
	//
	//
	//   if (stuffMenu->getIsActivated())
	//   {
	//      stuffMenu->renderBefore();
	//      stuffMenuGUI->update();
	//      stuffMenu->render();
	//   }
	//   if (gameStore->getIsActivated())
	//   {
	//      gameStore->renderBefore();
	//      gameStoreGUI->update();
	//      gameStore->render();
	//   }
	//   if (playerEditMenu->getIsActivated())
	//   {
	//      playerEditMenu->renderBefore();
	//      playerEditGUI->update();
	//      playerEditMenu->render();
	//   }
	//   if (keyboardScreen->getIsActivated())
	//   {
	//      keyboardScreen->renderBefore();
	//      keyboardScreenGUI->update();
	//      keyboardScreen->render();
	//   }
	//
	//   for (int i = 0; i < gameChallenges->size(); i++)
	//   {
	//      GameChallengeNotificationPanel* g = gameChallenges[i];
	//      GUI* gui = gameChallengesGUIs[i];
	//      if (g->getIsActivated())
	//      {
	//         g->renderBefore();
	//         gui->update();
	//         g->render();
	//      }
	//   }
}

//The following method was originally marked 'synchronized':
GameChallengeNotificationPanel* GUIManager::makeGameChallengeNotification(FriendCharacter* friend_in, const string& gameName)
{ //=========================================================================================================================
	GameChallengeNotificationPanel* g = new GameChallengeNotificationPanel(friend_in, gameName);
	gameChallenges->add(g);

	//   GUI* gui = new GUI(g, GLUtils::TWLrenderer);
	//   gui->applyTheme(GLUtils::TWLthemeManager);
	//   gameChallengesGUIs.push_back(gui);

	g->setActivated(true);

	return g;
}

void GUIManager::removeGameNotification(GameChallengeNotificationPanel* g)
{ //=========================================================================================================================

	for (int i = 0; i < gameChallenges->size(); i++)
	{
		//      if (gameChallenges[i] == g)
		//      {
		//         gameChallenges.remove(i);
		//         GUI* gui = gameChallengesGUIs.remove(i);
		//
		//         gui->destroy();
		//      }
	}
}

void GUIManager::cleanup()
{ //=========================================================================================================================


	//   //loadingScreenGUI.destroy();
	//   stuffMenuGUI->destroy();
	//
	//   gameStoreGUI->destroy();
	//   playerEditGUI->destroy();
	//   keyboardScreenGUI->destroy();
	//
	//   for (int i = 0; i < gameChallenges->size(); i++)
	//   {
	//      gameChallenges.remove(i);
	//      GUI* gui = gameChallengesGUIs.remove(i);
	//      gui->destroy();
	//   }
}

void GUIManager::setDarkTheme()
{ //=========================================================================================================================

	lightTheme = false;

	getStatusBar()->setDarkTheme();


	//   stuffMenu->mainPanelLayout->setTheme(GUIManager::darkThemeString);
	//   stuffMenu->mainPanelLayout->reapplyTheme();
	//
	//   gameStore->mainPanelLayout->setTheme(GUIManager::darkThemeString);
	//   gameStore->mainPanelLayout->reapplyTheme();
	//
	//   playerEditMenu->mainPanelLayout->setTheme(GUIManager::darkThemeString);
	//   playerEditMenu->mainPanelLayout->reapplyTheme();
	//
	//   keyboardScreen->mainPanelLayout->setTheme(GUIManager::darkThemeString);
	//   keyboardScreen->mainPanelLayout->reapplyTheme();
	//
	//   for (int i = 0; i < gameChallenges->size(); i++)
	//   {
	//      gameChallenges[i]->mainPanelLayout.setTheme(GUIManager::darkThemeString);
	//      gameChallenges[i]->mainPanelLayout.reapplyTheme();
	//   }
}

void GUIManager::setLightTheme()
{ //=========================================================================================================================

	lightTheme = true;

	getStatusBar()->setLightTheme();

	//   stuffMenu->mainPanelLayout->setTheme(GUIManager::lightThemeString);
	//   stuffMenu->mainPanelLayout->reapplyTheme();
	//
	//   gameStore->mainPanelLayout->setTheme(GUIManager::lightThemeString);
	//   gameStore->mainPanelLayout->reapplyTheme();
	//
	//   playerEditMenu->mainPanelLayout->setTheme(GUIManager::lightThemeString);
	//   playerEditMenu->mainPanelLayout->reapplyTheme();
	//
	//   keyboardScreen->mainPanelLayout->setTheme(GUIManager::lightThemeString);
	//   keyboardScreen->mainPanelLayout->reapplyTheme();
	//
	//   for (int i = 0; i < gameChallenges->size(); i++)
	//   {
	//      gameChallenges[i]->mainPanelLayout.setTheme(GUIManager::lightThemeString);
	//      gameChallenges[i]->mainPanelLayout.reapplyTheme();
	//   }
}

void GUIManager::openND()
{ //=========================================================================================================================
	closeAllMenusAndND();
	getND()->setActivated(true);
}

void GUIManager::closeND()
{ //=========================================================================================================================

	if (getND()->getIsActivated() == true)
	{
		getND()->toggleActivated();
	}
}

void GUIManager::openGameStore()
{ //=========================================================================================================================
	closeAllMenusAndND();
}

void GUIManager::openSettingsMenu()
{ //=========================================================================================================================
	openStuffMenu();

	//stuffMenu->openSubMenu(stuffMenu->settingsPanel);
}

void GUIManager::openFriendsMenu()
{ //=========================================================================================================================
	openStuffMenu();

	//stuffMenu->openSubMenu(stuffMenu->friendsPanel);
}

void GUIManager::openStatusMenu()
{ //=========================================================================================================================
	openStuffMenu();

	//stuffMenu->openSubMenu(stuffMenu->statusPanel);
}

void GUIManager::openLogMenu()
{ //=========================================================================================================================
	openStuffMenu();

	//stuffMenu->openSubMenu(stuffMenu->logsPanel);
}

void GUIManager::openItemsMenu()
{ //=========================================================================================================================

	openStuffMenu();

	//stuffMenu->openSubMenu(stuffMenu->itemsPanel);
}

void GUIManager::openStuffMenu()
{ //=========================================================================================================================

	getND()->setActivated(false);
	gameStore->setActivated(false);


	stuffMenu->setActivated(true);
}

void GUIManager::enableAllMenusAndND()
{ //=========================================================================================================================

	keyboardScreen->setEnabled(true);
	getND()->setEnabled(true);
	gameStore->setEnabled(true);
	stuffMenu->setEnabled(true);
}

void GUIManager::disableAllMenusAndND()
{ //=========================================================================================================================

	closeAllMenusAndND();

	keyboardScreen->setEnabled(false);
	getND()->setEnabled(false);
	gameStore->setEnabled(false);
	stuffMenu->setEnabled(false);
}

void GUIManager::closeAllMenusAndND()
{ //=========================================================================================================================

	keyboardScreen->setActivated(false);
	closeND();
	gameStore->setActivated(false);
	stuffMenu->setActivated(false);
}

