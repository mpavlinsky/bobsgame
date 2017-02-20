#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger SubPanel::log = Logger("SubPanel");


SubPanel::SubPanel()
{ //=========================================================================================================================


	//   thisDialogLayout = this;
	//
	//
	//   setTheme(GUIManager::subMenuPanelDialogLayoutTheme);
	//
	//   //----------------------
	//   //setup layout inside scrollpane
	//   //----------------------
	//   insideLayout = new DialogLayout();
	//   insideLayout->setTheme(GUIManager::emptyDialogLayoutTheme);
	//   insideLayout->setCanAcceptKeyboardFocus(false);
	//
	//
	//   //----------------------
	//   //setup scrollpane
	//   //----------------------
	//
	//   scrollPane = new ScrollPane(insideLayout);
	//   scrollPane->setTheme(GUIManager::scrollPaneTheme);
	//   scrollPane->setCanAcceptKeyboardFocus(false);
	//   scrollPane->setExpandContentSize(true);
	//
	//
	//   //----------------------
	//   //setup this dialoglayout
	//   //----------------------
	//
	//   add(scrollPane);
	//   setVisible(false);
	//
	//   setCanAcceptKeyboardFocus(false);
	//   setHorizontalGroup(createParallelGroup(scrollPane));
	//
	//   setVerticalGroup(createSequentialGroup(scrollPane));
}

void SubPanel::init()
{ //=========================================================================================================================
	//put anything in here that you want to happen after the subpanel is created and constructed
}

void SubPanel::setVisible(bool b)
{ //=========================================================================================================================
	//DialogLayout::setVisible(b);

	//put anything in here that you want to happen when we switch to the subpanel
}

void SubPanel::layout()
{ //=========================================================================================================================


	//   scrollPane->setMinSize((int)(StuffMenu()->insideScrollPaneLayout->getInnerWidth() * StuffMenu()->subPanelScreenWidthPercent), (int)(StuffMenu()->insideScrollPaneLayout->getInnerHeight() * StuffMenu()->subPanelScreenHeightPercent));
	//   scrollPane->setSize((int)(StuffMenu()->insideScrollPaneLayout->getInnerWidth() * StuffMenu()->subPanelScreenWidthPercent), (int)(StuffMenu()->insideScrollPaneLayout->getInnerHeight() * StuffMenu()->subPanelScreenHeightPercent));
	//   //scrollPane.adjustSize();
	//
	//   scrollPane->updateScrollbarSizes();
	//
	//   DialogLayout::layout();

}

void SubPanel::update()
{ //=========================================================================================================================

	//put anything in here that you want to change every frame
}

void SubPanel::render()
{ //=========================================================================================================================
}
//
//BGClientEngine* SubPanel::getClientEngine()
//{
//	return Main::gameEngine;
//}
//
//EventManager* SubPanel::getEventManager()
//{
//	return getClientEngine()->eventManager;
//}
//
//Clock* SubPanel::getClock()
//{
//	return getClientEngine()->clock;
//}
//
//GUIManager* SubPanel::getGUIManager()
//{
//	return getClientEngine()->guiManager;
//}
//
//StuffMenu* SubPanel::getStuffMenu()
//{
//	return getGUIManager()->stuffMenu;
//}
//
//GameStore* SubPanel::getGameStore()
//{
//	return getGUIManager()->gameStore;
//}
//
//PlayerEditMenu* SubPanel::getPlayerEditMenu()
//{
//	return getGUIManager()->playerEditMenu;
//}
//
//Player* SubPanel::getPlayer()
//{
//	return getClientEngine()->player;
//}
//
//ND* SubPanel::getND()
//{
//	return getClientEngine()->nD;
//}
//
//Wallet* SubPanel::getWallet()
//{
//	return getClientEngine()->wallet;
//}
//
//FriendManager* SubPanel::getFriendManager()
//{
//	return getClientEngine()->friendManager;
//}
//
//StatusBar* SubPanel::getStatusBar()
//{
//	return getClientEngine()->statusBar;
//}
//
//NotificationManager* SubPanel::getNotificationManager()
//{
//	return getStatusBar()->notificationManager;
//}
//
//TCPServerConnection* SubPanel::getServerConnection()
//{
//	return BobNet::tcpServerConnection;
//}
//
//GameSave* SubPanel::getGameSave()
//{
//	return getServerConnection()->getGameSave_S();
//}
//
