#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger StuffMenu::log = Logger("StuffMenu");


StuffMenu::StuffMenu()
{ //=========================================================================================================================

	MenuPanel();


	//setTheme("stuffmenu");


	statusPanel = new StatusPanel();
	itemsPanel = new ItemsPanel();
	messagesPanel = new MessagesPanel();
	friendsPanel = new FriendsPanel();
	logsPanel = new LogsPanel();
	controlsPanel = new ControlsPanel();
	settingsPanel = new SettingsPanel();
	debugInfoPanel = new DebugInfoPanel();

	//
	//   stuffMenuTabs = ArrayList<ToggleButton*>(8);
	//   SimpleIntegerModel* startMenuTabsIntModel = new SimpleIntegerModel(1, stuffMenuTabs->size(), 0);
	//
	//   for (int i = 0; i < stuffMenuTabs->size(); i++)
	//   {
	//      stuffMenuTabs[i] = new ToggleButton(new OptionBooleanModel(startMenuTabsIntModel, i + 1));
	//      stuffMenuTabs[i]->setCanAcceptKeyboardFocus(false);
	//      stuffMenuTabs[i]->setTheme(GUIManager::buttonTheme);
	//   }
	//
	//
	//   stuffMenuTabs[0]->setText("Account Status");
	//   stuffMenuTabs[1]->setText("Items");
	//   stuffMenuTabs[2]->setText("Messages");
	//   stuffMenuTabs[3]->setText("Friends");
	//   stuffMenuTabs[4]->setText("Game Logs");
	//   stuffMenuTabs[5]->setText("Controls");
	//   stuffMenuTabs[6]->setText("Settings");
	//   stuffMenuTabs[7]->setText("Debug Info");
	//
	//
	//   //---------------------------------------------------------
	//   //status
	//   //---------------------------------------------------------
	//   stuffMenuTabs[0]->addCallback([&] ()
	//      {
	//         setAllInvisible();
	//         statusPanel->setVisible(true);
	//      }
	//   );
	//   //---------------------------------------------------------
	//   //stuff
	//   //---------------------------------------------------------
	//   stuffMenuTabs[1]->addCallback([&] ()
	//      {
	//         setAllInvisible();
	//         itemsPanel->setVisible(true);
	//      }
	//   );
	//   //---------------------------------------------------------
	//   //messages
	//   //---------------------------------------------------------
	//   stuffMenuTabs[2]->addCallback([&] ()
	//      {
	//         setAllInvisible();
	//         messagesPanel->setVisible(true);
	//      }
	//   );
	//
	//   //---------------------------------------------------------
	//   //friends
	//   //---------------------------------------------------------
	//   stuffMenuTabs[3]->addCallback([&] ()
	//      {
	//         setAllInvisible();
	//         friendsPanel->setVisible(true);
	//      }
	//   );
	//
	//   //---------------------------------------------------------
	//   //logs
	//   //---------------------------------------------------------
	//   stuffMenuTabs[4]->addCallback([&] ()
	//      {
	//         setAllInvisible();
	//         logsPanel->setVisible(true);
	//      }
	//   );
	//
	//   //---------------------------------------------------------
	//   //controls
	//   //---------------------------------------------------------
	//   stuffMenuTabs[5]->addCallback([&] ()
	//      {
	//         setAllInvisible();
	//         controlsPanel->setVisible(true);
	//      }
	//   );
	//
	//   //---------------------------------------------------------
	//   //settings
	//   //---------------------------------------------------------
	//   stuffMenuTabs[6]->addCallback([&] ()
	//      {
	//         setAllInvisible();
	//         settingsPanel->setVisible(true);
	//      }
	//   );
	//
	//   //---------------------------------------------------------
	//   //debug
	//   //---------------------------------------------------------
	//   stuffMenuTabs[7]->addCallback([&] ()
	//      {
	//         setAllInvisible();
	//         debugInfoPanel->setVisible(true);
	//      }
	//   );
	//
	//
	//   insideScrollPaneLayout->setHorizontalGroup(insideScrollPaneLayout->createParallelGroup().addGroup(insideScrollPaneLayout->createSequentialGroup().addGap().addWidgets(stuffMenuTabs[0], stuffMenuTabs[5], stuffMenuTabs[7]).addGap()).addGroup(insideScrollPaneLayout->createParallelGroup(debugInfoPanel, settingsPanel, controlsPanel, messagesPanel, itemsPanel, logsPanel, statusPanel, friendsPanel)));
	//   //.addGroup(insideScrollPaneLayout.createSequentialGroup().addGap().addWidgets(stuffMenuTabs[0],stuffMenuTabs[1],stuffMenuTabs[2],stuffMenuTabs[3]).addGap())
	//   //.addGroup(insideScrollPaneLayout.createSequentialGroup().addGap().addWidgets(stuffMenuTabs[4],stuffMenuTabs[5],stuffMenuTabs[6],stuffMenuTabs[7]).addGap())
	//
	//   insideScrollPaneLayout->setVerticalGroup(insideScrollPaneLayout->createSequentialGroup().addGroup(insideScrollPaneLayout->createParallelGroup(stuffMenuTabs[0], stuffMenuTabs[5], stuffMenuTabs[7])).addGroup(insideScrollPaneLayout->createParallelGroup(debugInfoPanel, settingsPanel, controlsPanel, messagesPanel, itemsPanel, logsPanel, statusPanel, friendsPanel)));
	//   //.addGroup(insideScrollPaneLayout.createParallelGroup(stuffMenuTabs[0],stuffMenuTabs[1],stuffMenuTabs[2],stuffMenuTabs[3]))
	//   //.addGroup(insideScrollPaneLayout.createParallelGroup(stuffMenuTabs[4],stuffMenuTabs[5],stuffMenuTabs[6],stuffMenuTabs[7]))
	//
	//
	//   //---------------------
	//   //scrollpane
	//   //----------------------
	//
	//   scrollPane = new ScrollPane();
	//
	//   scrollPane->setTheme(GUIManager::scrollPaneTheme);
	//   scrollPane->setCanAcceptKeyboardFocus(false);
	//   scrollPane->setExpandContentSize(true);
	//
	//
	//   //---------------------
	//   //add scrollpane to outside panel
	//   //----------------------
	//
	//   //i don't need it here, i am adding the subpanels directly and they contain their own scrollpane.
	//   //mainPanelLayout.add(scrollPane);
	//
	//
	//   mainPanelLayout->setCanAcceptKeyboardFocus(false);
	//   mainPanelLayout->setHorizontalGroup(mainPanelLayout->createParallelGroup(insideScrollPaneLayout));
	//
	//   mainPanelLayout->setVerticalGroup(mainPanelLayout->createSequentialGroup(insideScrollPaneLayout));
	//
	//
	//   Console::add(mainPanelLayout);
}

void StuffMenu::setActivated(bool b)
{ //=========================================================================================================================

	if (b == true && (getStatusBar()->stuffButton->enabled == false || getEnabled() == false))
	{
		return;
	}

	MenuPanel::setActivated(b);
}

void StuffMenu::setAllInvisible()
{ //=========================================================================================================================
	debugInfoPanel->setVisible(false);
	settingsPanel->setVisible(false);
	controlsPanel->setVisible(false);
	messagesPanel->setVisible(false);
	statusPanel->setVisible(false);
	friendsPanel->setVisible(false);
	logsPanel->setVisible(false);
	itemsPanel->setVisible(false);
}

void StuffMenu::openSubMenu()//SubPanel* subPanel)
{ //=========================================================================================================================
	setAllInvisible();
	//subPanel->setVisible(true);
}

void StuffMenu::init()
{ //=========================================================================================================================
	//super.init();

	debugInfoPanel->init();
	settingsPanel->init();
	controlsPanel->init();
	messagesPanel->init();
	statusPanel->init();
	friendsPanel->init();
	logsPanel->init();
	itemsPanel->init();
}

void StuffMenu::update()
{ //=========================================================================================================================
	MenuPanel::update();

	if (getIsActivated() == false)
	{
		return;
	}

	//   if (debugInfoPanel->isVisible())
	//   {
	//      debugInfoPanel->update();
	//   }
	//   if (settingsPanel->isVisible())
	//   {
	//      settingsPanel->update();
	//   }
	//   if (controlsPanel->isVisible())
	//   {
	//      controlsPanel->update();
	//   }
	//   if (messagesPanel->isVisible())
	//   {
	//      messagesPanel->update();
	//   }
	//   if (statusPanel->isVisible())
	//   {
	//      statusPanel->update();
	//   }
	//   if (friendsPanel->isVisible())
	//   {
	//      friendsPanel->update();
	//   }
	//   if (logsPanel->isVisible())
	//   {
	//      logsPanel->update();
	//   }
	//   if (itemsPanel->isVisible())
	//   {
	//      itemsPanel->update();
	//   }
}

void StuffMenu::render()
{ //=========================================================================================================================

	MenuPanel::render();

	if (getIsActivated() == false)
	{
		return;
	}


	//
	//   //additional rendering calls go here (after gui is drawn)
	//   if (debugInfoPanel->isVisible())
	//   {
	//      debugInfoPanel->render();
	//   }
	//   if (settingsPanel->isVisible())
	//   {
	//      settingsPanel->render();
	//   }
	//   if (controlsPanel->isVisible())
	//   {
	//      controlsPanel->render();
	//   }
	//   if (messagesPanel->isVisible())
	//   {
	//      messagesPanel->render();
	//   }
	//   if (statusPanel->isVisible())
	//   {
	//      statusPanel->render();
	//   }
	//   if (friendsPanel->isVisible())
	//   {
	//      friendsPanel->render();
	//   }
	//   if (logsPanel->isVisible())
	//   {
	//      logsPanel->render();
	//   }
	//   if (itemsPanel->isVisible())
	//   {
	//      itemsPanel->render();
	//   }
}

void StuffMenu::layout()
{ //=========================================================================================================================


	if (getIsActivated() == false)
	{
		return;
	}

	//
	//   if (debugInfoPanel->isVisible())
	//   {
	//      debugInfoPanel->layout();
	//   }
	//   if (settingsPanel->isVisible())
	//   {
	//      settingsPanel->layout();
	//   }
	//   if (controlsPanel->isVisible())
	//   {
	//      controlsPanel->layout();
	//   }
	//   if (messagesPanel->isVisible())
	//   {
	//      messagesPanel->layout();
	//   }
	//   if (statusPanel->isVisible())
	//   {
	//      statusPanel->layout();
	//   }
	//   if (friendsPanel->isVisible())
	//   {
	//      friendsPanel->layout();
	//   }
	//   if (logsPanel->isVisible())
	//   {
	//      logsPanel->layout();
	//   }
	//   if (itemsPanel->isVisible())
	//   {
	//      itemsPanel->layout();
	//   }
	//
	//   insideScrollPaneLayout->setMinSize((int)(mainPanelLayout->getWidth() * 0.80f), (int)(mainPanelLayout->getHeight() * 0.80f));
	//   insideScrollPaneLayout->setSize((int)(mainPanelLayout->getWidth() * 0.80f), (int)(mainPanelLayout->getHeight() * 0.80f));


	MenuPanel::layout();
}

