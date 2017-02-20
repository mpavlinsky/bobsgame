
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger BobsGameStadium::log = Logger("BobsGameStadium");

//=========================================================================================================================
BobsGameStadium::BobsGameStadium()
{ //=========================================================================================================================
#ifdef _DEBUG
	log.info("BobsGameStadium()");
#endif
	
}
//=========================================================================================================================
BobsGameStadium::~BobsGameStadium()
{ //=========================================================================================================================
#ifdef _DEBUG
	log.info("~BobsGameStadium()");
#endif

}
//=========================================================================================================================
void BobsGameStadium::init()
{ //=========================================================================================================================

	super::init();


#ifdef _DEBUG
	log.info("BobsGameStadium::init()");
#endif

	name = "bob's game";
}

BobsGameStadium::BobsGameStadium(StadiumScreen* stadiumScreen, Area* area)
{ //=========================================================================================================================

#ifdef _DEBUG
	log.info("BobsGameStadium(StadiumScreen* stadiumScreen, Area* area)");
#endif

	//StadiumGameEngine(stadiumScreen, area);
	this->stadiumScreen = stadiumScreen;
	this->area = area;
	stadiumScreen->setGame(this, area);



}


void BobsGameStadium::shakeSmall()
{ //=========================================================================================================================
	getClientGameEngine()->getCameraman()->popZOOMto = getClientGameEngine()->getCameraman()->getZoom() - 0.1f;
	getClientGameEngine()->getCameraman()->setShakeScreen(300, 2, 2, 30);
	getClientGameEngine()->getCinematicsManager()->fadeColorFromTransparentToAlphaBackToTransparent(200, 255, 255, 255, 0.5f);
}

void BobsGameStadium::shakeHard()
{ //=========================================================================================================================
	getClientGameEngine()->getCameraman()->popZOOMto = getClientGameEngine()->getCameraman()->getZoom() - 0.5f;
	getClientGameEngine()->getCameraman()->setShakeScreen(1000, 5, 5, 30);
	getClientGameEngine()->getCinematicsManager()->fadeColorFromTransparentToAlphaBackToTransparent(200, 255, 255, 255, 0.5f);
}








void BobsGameStadium::titleMenuUpdate()
{ //=========================================================================================================================

	if (titleMenu == nullptr)
	{
		titleMenu = new BobMenu(this,"");
		titleMenu->add("TOURNAMENT MODE");
	}


	if (getControlsManager()->miniGame_CONFIRM_Pressed())
	{
		titleMenuShowing = false;


		if (titleMenu != nullptr)
		{
			delete titleMenu;
			titleMenu = nullptr;
		}
	}
}



void BobsGameStadium::tryToCloseGame()
{ //=========================================================================================================================
	//TODO: upload score to leaderboard
}



