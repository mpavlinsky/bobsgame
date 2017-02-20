#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger MenuPanel::log = Logger("MenuPanel");


MenuPanel::MenuPanel()
{ //=========================================================================================================================

	//
	//   setCanAcceptKeyboardFocus(false);
	//
	//
	//   //----------------------
	//   //outside panel, just attached to "nothing"
	//   //----------------------
	//
	//   mainPanelLayout = new DialogLayout();
	//
	//   //if(stuffMenu().lightTheme==true)
	//   //mainPanelLayout.setTheme(GUIManager.lightThemeString);
	//   //else
	//   mainPanelLayout->setTheme(GUIManager::darkThemeString);
	//
	//
	//   //---------------------
	//   //this goes inside the scrollpane which goes inside mainPanelLayout. for the stuff menu we just attach it directly to mainPanelLayout because the submenus have scrollpanes.
	//   //----------------------
	//
	//   insideScrollPaneLayout = new DialogLayout();
	//   insideScrollPaneLayout->setTheme(GUIManager::emptyDialogLayoutTheme);
	//   insideScrollPaneLayout->setCanAcceptKeyboardFocus(false);
}

void MenuPanel::update()
{ //=========================================================================================================================

	if (isActivated == true)
	{
		if (isScrollingDown == false)
		{
			ticksSinceTurnedOff = 0;
			ticksSinceTurnedOn += (int)Engine::realWorldTicksPassed();

			scrollUp();
		}
		else
		{
			if (isScrollingDown == true)
			{
				ticksSinceTurnedOn = 0;
				ticksSinceTurnedOff += (int)Engine::realWorldTicksPassed();

				scrollDown();
			}
		}
	}
}

void MenuPanel::setEnabled(bool b)
{ //=========================================================================================================================
	enabled = b;

	if (b == false)
	{
		if (getIsActivated() == true)
		{
			setActivated(false);
		}
	}
}

bool MenuPanel::getEnabled()
{ //=========================================================================================================================
	return enabled;
}

bool MenuPanel::getIsActivated()
{ //=========================================================================================================================
	return isActivated;
}

bool MenuPanel::getIsScrollingDown()
{ //=========================================================================================================================
	return isScrollingDown;
}

bool MenuPanel::getIsScrolledUp()
{ //=========================================================================================================================
	return isScrolledUp;
}

void MenuPanel::setActivated(bool b)
{ //=========================================================================================================================

	if (b == true && getEnabled() == false)
	{
		return;
	}

	if (b == true)
	{
		isScrollingDown = false;
		isActivated = true;
		ticksSinceTurnedOn = 0;

		screenY = (float)(GLUtils::getViewportHeight());
		//Widget::setVisible(true);
	}
	else
	{
		if (b == false)
		{
			if (isActivated == true)
			{
				isScrolledUp = false;

				if (isScrollingDown == false)
				{
					isScrollingDown = true;
					ticksSinceTurnedOff = 0;
					if (ticksSinceTurnedOn < fadeInTime)
					{
						ticksSinceTurnedOff = (int)(fadeOutTime - ((ticksSinceTurnedOn / fadeInTime) * fadeOutTime));
					}
				}
			}
		}
	}
}

void MenuPanel::toggleActivated()
{ //=========================================================================================================================

	if (isActivated == false)
	{
		setActivated(true);
	}
	else
	{
		if (isActivated == true)
		{
			if (isScrollingDown == true)
			{
				isScrollingDown = false;
			}
			else
			{
				setActivated(false);
			}
		}
	}
}

void MenuPanel::onScrolledUp()
{ //=========================================================================================================================
}

void MenuPanel::scrollUp()
{ //=========================================================================================================================
	if (ticksSinceTurnedOn <= fadeInTime)
	{
		screenY = (float)((GLUtils::getViewportHeight()) - (Easing::easeOutCubic(ticksSinceTurnedOn, 0, GLUtils::getViewportHeight(), fadeInTime)));
		layout();
	}

	//if it's supposed to be scrolled all the way up, make sure it is.
	else
	{
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
}

void MenuPanel::scrollDown()
{ //=========================================================================================================================
	if (ticksSinceTurnedOff <= fadeOutTime)
	{
		screenY = (float)(Easing::easeOutParabolicBounce(ticksSinceTurnedOff, 0, GLUtils::getViewportHeight(), fadeOutTime));
		layout();
	}
	else
	{
		isActivated = false;
		isScrollingDown = false;
		//Widget::setVisible(false);
	}
}

void MenuPanel::layout()
{ //=========================================================================================================================


	//   mainPanelLayout->adjustSize();
	//   mainPanelLayout->setSize((int)(GLUtils::getViewportWidth() * 0.90f), (int)(GLUtils::getViewportHeight() * 0.90f));
	//
	//
	//   // main panel is centered
	//   mainPanelLayout->setPosition((getInnerX() + (getInnerWidth() - mainPanelLayout->getWidth()) / 2), (int)(getScreenY + (getInnerY() + (getInnerHeight() - mainPanelLayout->getHeight()) / 2)));
	//
	//
	//   scrollPane->setMinSize((int)(mainPanelLayout->getWidth() * 0.86f), (int)(mainPanelLayout->getHeight() * 0.86f));
	//   scrollPane->setSize((int)(mainPanelLayout->getWidth() * 0.86f), (int)(mainPanelLayout->getHeight() * 0.86f));
	//
	//
	//   Widget::layout();
}

void MenuPanel::renderBefore()
{ //=========================================================================================================================


	if (isScrollingDown == true)
	{
		return;
	}
	if (isActivated == false)
	{
		return;
	}


	GLUtils::drawFilledRect(0, 0, 0, 0, (float)GLUtils::getViewportWidth(), 0, (float)GLUtils::getViewportHeight(), 0.5f);
}

void MenuPanel::render()
{ //=========================================================================================================================


	if (isScrollingDown == true)
	{
		return;
	}
	if (isActivated == false)
	{
		return;
	}
}


//
//BGClientEngine* MenuPanel::getClientGameEngine()
//{
//	return Main::gameEngine;
//}
//
//Clock* MenuPanel::getClock()
//{
//	if (getClientGameEngine() == nullptr)
//	{
//		return nullptr;
//	}
//	return getClientGameEngine()->clock;
//}
//
//GUIManager* MenuPanel::getGUIManager()
//{
//	if (getClientGameEngine() == nullptr)
//	{
//		return nullptr;
//	}
//	return getClientGameEngine()->guiManager;
//}
//
//StuffMenu* MenuPanel::getStuffMenu()
//{
//	if (getClientGameEngine() == nullptr)
//	{
//		return nullptr;
//	}
//	return getGUIManager()->stuffMenu;
//}
//
//GameStore* MenuPanel::getGameStore()
//{
//	if (getClientGameEngine() == nullptr)
//	{
//		return nullptr;
//	}
//	return getGUIManager()->gameStore;
//}
//
//PlayerEditMenu* MenuPanel::getPlayerEditMenu()
//{
//	if (getClientGameEngine() == nullptr)
//	{
//		return nullptr;
//	}
//	return getGUIManager()->playerEditMenu;
//}
//
//Player* MenuPanel::getPlayer()
//{
//	if (getClientGameEngine() == nullptr)
//	{
//		return nullptr;
//	}
//	return getClientGameEngine()->player;
//}
//
//ND* MenuPanel::getND()
//{
//	if (getClientGameEngine() == nullptr)
//	{
//		return nullptr;
//	}
//	return getClientGameEngine()->nD;
//}
//
//Wallet* MenuPanel::getWallet()
//{
//	if (getClientGameEngine() == nullptr)
//	{
//		return nullptr;
//	}
//	return getClientGameEngine()->wallet;
//}
//
//FriendManager* MenuPanel::getFriendManager()
//{
//	if (getClientGameEngine() == nullptr)
//	{
//		return nullptr;
//	}
//	return getClientGameEngine()->friendManager;
//}
//
//StatusBar* MenuPanel::getStatusBar()
//{
//	if (getClientGameEngine() == nullptr)
//	{
//		return nullptr;
//	}
//	return getClientGameEngine()->statusBar;
//}
//
//NotificationManager* MenuPanel::getNotificationManager()
//{
//	if (getClientGameEngine() == nullptr)
//	{
//		return nullptr;
//	}
//	return getStatusBar()->notificationManager;
//}
//
//TCPServerConnection* MenuPanel::getServerConnection()
//{
//	return BobNet::tcpServerConnection;
//}
//
//GameSave* MenuPanel::getGameSave()
//{
//	return getServerConnection()->getGameSave_S();
//}
//
