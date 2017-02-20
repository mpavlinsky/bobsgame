#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger GameChallengeNotificationPanel::log = Logger("GameChallengeNotificationPanel");


GameChallengeNotificationPanel::GameChallengeNotificationPanel(FriendCharacter* friend_in, const string& gameName)
{ //=========================================================================================================================

	MenuPanel();

	this->notificationCreatedTime = System::currentHighResTimer();

	this->friendCharacter = friend_in;
	this->gameName = gameName;

	//
	//   notificationPanel = new DialogLayout();
	//   notificationPanel->setTheme("darkLayout");
	//
	//
	//   Label* notificationPanelLabel = new Label("Game Challenge!");
	//   notificationPanelLabel->setCanAcceptKeyboardFocus(false);
	//   notificationPanelLabel->setTheme("bigLabel");
	//
	//   Label* challengeTextLabel = new Label(string("") + friend->name() + string(" has challenged you to play ") + gameName);
	//   challengeTextLabel->setCanAcceptKeyboardFocus(false);
	//
	//   timeLeftLabel = new Label("");
	//   timeLeftLabel->setCanAcceptKeyboardFocus(false);
	//
	//   //---------------------------------------------------------
	//   //yes
	//   //---------------------------------------------------------
	//   yesButton = new Button("Yes");
	//   yesButton->setCanAcceptKeyboardFocus(false);
	//   yesButton->addCallback([&] ()
	//      {
	//         doYes();
	//      }
	//   );
	//
	//
	//   //---------------------------------------------------------
	//   //no
	//   //---------------------------------------------------------
	//   noButton = new Button("No");
	//   noButton->setCanAcceptKeyboardFocus(false);
	//   noButton->addCallback([&] ()
	//      {
	//         doNo();
	//      }
	//   );
	//
	//
	//   notificationPanel->setHorizontalGroup(notificationPanel->createParallelGroup(notificationPanel->createParallelGroup().addMinGap(200), notificationPanel->createSequentialGroup(notificationPanel->createParallelGroup().addMinGap(20), notificationPanel->createParallelGroup(notificationPanel->createSequentialGroup().addGap().addWidget(notificationPanelLabel).addGap(), notificationPanel->createSequentialGroup().addGap().addWidget(timeLeftLabel).addGap(), notificationPanel->createSequentialGroup().addGap().addWidget(challengeTextLabel).addGap(), notificationPanel->createSequentialGroup().addGap().addWidget(noButton).addGap().addWidget(yesButton).addGap()), notificationPanel->createParallelGroup().addMinGap(20))));
	//
	//
	//   notificationPanel->setVerticalGroup(notificationPanel->createSequentialGroup(notificationPanel->createSequentialGroup().addMinGap(20), notificationPanel->createParallelGroup(notificationPanelLabel), notificationPanel->createSequentialGroup().addMinGap(20), notificationPanel->createParallelGroup(challengeTextLabel), notificationPanel->createParallelGroup(timeLeftLabel), notificationPanel->createSequentialGroup().addMinGap(20), notificationPanel->createParallelGroup(noButton, yesButton), notificationPanel->createSequentialGroup().addMinGap(50)));
	//
	//
	//   //		//---------------------------------------------------------
	//   //		//layout
	//   //		//---------------------------------------------------------
	//   //
	//   //		insideScrollPaneLayout.setHorizontalGroup
	//   //		(
	//   //				insideScrollPaneLayout.createParallelGroup
	//   //				(
	//   //						insideScrollPaneLayout.createSequentialGroup().addGap().addWidget(notificationPanel).addGap()
	//   //				)
	//   //		);
	//   //
	//   //		insideScrollPaneLayout.setVerticalGroup
	//   //		(
	//   //				insideScrollPaneLayout.createSequentialGroup
	//   //				(
	//   //						insideScrollPaneLayout.createSequentialGroup().addGap()
	//   //						,
	//   //						insideScrollPaneLayout.createParallelGroup().addWidget(notificationPanel)
	//   //						,
	//   //						insideScrollPaneLayout.createSequentialGroup().addGap()
	//   //				)
	//   //		);
	//   //
	//   //
	//   //
	//   //
	//   //
	//   //		//---------------------
	//   //		//scrollpane
	//   //		//----------------------
	//   //
	//   //		scrollPane = new ScrollPane(insideScrollPaneLayout);
	//   //
	//   //		scrollPane.setTheme(GUIManager.scrollPaneTheme);
	//   //		scrollPane.setCanAcceptKeyboardFocus(false);
	//   //		scrollPane.setExpandContentSize(true);
	//   //
	//   //
	//   //		//---------------------
	//   //		//add scrollpane to outside panel
	//   //		//----------------------
	//   //
	//   //		//mainPanelLayout.add(scrollPane);
	//   //
	//   //
	//   mainPanelLayout->setCanAcceptKeyboardFocus(false);
	//   mainPanelLayout->setHorizontalGroup(mainPanelLayout->createParallelGroup(notificationPanel));
	//
	//   mainPanelLayout->setVerticalGroup(mainPanelLayout->createSequentialGroup(notificationPanel));
	//
	//
	//   add(mainPanelLayout);
	//
	//
	//   notificationPanel->adjustSize();


	setActivated(true);
}

void GameChallengeNotificationPanel::update()
{ //=========================================================================================================================
	MenuPanel::update();


	long long startTime = notificationCreatedTime;
	long long currentTime = System::currentHighResTimer();
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

	if (ticksPassed > 20000)
	{
		setActivated(false);

		//getGUIManager()->removeGameNotification(this);
	}

	//long long startTime = notificationCreatedTime;
	//long long currentTime = System::currentHighResTimer();
	//int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	//timeLeftLabel->setText(string("Time Left: ") + to_string((20000 - (currentTime - notificationCreatedTime)) / 1000));
}

void GameChallengeNotificationPanel::onScrolledUp()
{ //=========================================================================================================================
}

void GameChallengeNotificationPanel::scrollUp()
{ //=========================================================================================================================

	if (isScrolledUp == false)
	{
		onScrolledUp();
		isScrolledUp = true;

		if (screenY != 0)
		{
			screenY = 0;
			layout();
		}
	}
}

void GameChallengeNotificationPanel::scrollDown()
{ //=========================================================================================================================


	isActivated = false;
	isScrollingDown = false;
	//MenuPanel::setVisible(false);
}

void GameChallengeNotificationPanel::layout()
{ //=========================================================================================================================

	//   mainPanelLayout->adjustSize();
	//
	//   // main panel is centered
	//   mainPanelLayout->setPosition(0, 20);
	//   //(getInnerX() + (getInnerWidth() - mainPanelLayout.getWidth()) / 2),
	//   //(int)(getScreenY+(getInnerY() + (getInnerHeight() - mainPanelLayout.getHeight()) / 2)));
	//
	//
	//   notificationPanel->adjustSize();
	//   //notificationPanel.setPosition(0,20);
	//   //insideScrollPaneLayout.getInnerX() + (insideScrollPaneLayout.getInnerWidth() - notificationPanel.getWidth()) / 2,
	//   //insideScrollPaneLayout.getInnerY() + (insideScrollPaneLayout.getInnerHeight() - notificationPanel.getHeight()) / 2);
	//
	//   //super.layout();
}

void GameChallengeNotificationPanel::setButtonsVisible(bool b)
{ //=========================================================================================================================

	//   yesButton->setVisible(b);
	//   noButton->setVisible(b);
}

void GameChallengeNotificationPanel::doNo()
{ //=========================================================================================================================

	//GUI* gui = getGUI();
	//if (gui != nullptr)
	{
		//if click yes, open nD, initialize game with this connection
		//TODO: get game by challenge name


		friendCharacter->setOutgoingGameChallengeResponse(NDGameEngine::gameChallengeResponse_DECLINE);

		//Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
		delete friendCharacter->gameChallengeNotification;

		setActivated(false);

		//getGUIManager()->removeGameNotification(this);
	}
}

void GameChallengeNotificationPanel::doYes()
{ //=========================================================================================================================

	//GUI* gui = getGUI();
	//if (gui != nullptr)
	{
		friendCharacter->setOutgoingGameChallengeResponse(NDGameEngine::gameChallengeResponse_ACCEPT);


		//getND()->getGame()->setConnection(friendCharacter->connection);

		friendCharacter->setGameToForwardPacketsTo(getND()->getGame());


		//getGUIManager()->openND();

		//Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
		delete friendCharacter->gameChallengeNotification;

		setActivated(false);

		//getGUIManager()->removeGameNotification(this);
	}
}

void GameChallengeNotificationPanel::renderBefore()
{ //=========================================================================================================================


	if (getIsScrollingDown() == true)
	{
		return;
	}
	if (getIsActivated() == false)
	{
		return;
	}
	//additional rendering calls go here (after gui is drawn)
}

void GameChallengeNotificationPanel::render()
{ //=========================================================================================================================


	if (getIsScrollingDown() == true)
	{
		return;
	}
	if (getIsActivated() == false)
	{
		return;
	}

	//additional rendering calls go here (after gui is drawn)
}

