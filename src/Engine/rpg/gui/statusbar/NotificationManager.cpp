
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger NotificationManager::log = Logger("NotificationManager");


BobTexture* NotificationManager::loadingBarTexture = nullptr;
BobTexture* NotificationManager::loadingBarBackgroundTexture = nullptr;

NotificationManager::NotificationManager(BGClientEngine* g)
{ //=========================================================================================================================


	this->e = g;

	loadingBarTexture = GLUtils::getTextureFromPNG("data/statusbar/loadingBar.png");
	loadingBarBackgroundTexture = GLUtils::getTextureFromPNG("data/statusbar/loadingBarBackground.png");


	//TODO: manage multiple notifications, cycle through them, keep them in a dropdown log

	//TODO: have status bar movable to bottom
}

void NotificationManager::init()
{ //=========================================================================================================================
}

void NotificationManager::update()
{ //=========================================================================================================================


	for (int i = 0; i < notificationList->size(); i++)
	{
		notificationList->get(i)->update();
	}
}

void NotificationManager::render(int layer)
{ //=========================================================================================================================
	for (int i = 0; i < notificationList->size(); i++)
	{
		notificationList->get(i)->render(layer);
	}
}

void NotificationManager::add(Notification* n)
{ //=========================================================================================================================


	notificationList->add(n);
}

void NotificationManager::remove(Notification* n)
{ //=========================================================================================================================

	notificationList->remove(n);
}

