#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once



Logger MiniGameEngine::log = Logger("MiniGameEngine");

//=========================================================================================================================
MiniGameEngine::MiniGameEngine()
{//=========================================================================================================================
#ifdef _DEBUG
	log.info("MiniGameEngine()");
#endif

}
//=========================================================================================================================
MiniGameEngine::~MiniGameEngine()
{//=========================================================================================================================
#ifdef _DEBUG
	log.info("~MiniGameEngine()");
#endif

	delete gameDataLoader;
}
//=========================================================================================================================
void MiniGameEngine::init()
{//=========================================================================================================================

	super::init();

#ifdef _DEBUG
	log.info("MiniGameEngine::init()");
#endif


	setupMenus();

	this->gameDataLoader = new GameDataLoader(this);

}


string MiniGameEngine::getGameName()
{ //=========================================================================================================================
	return name;
}



void MiniGameEngine::shakeSmall()
{ //=========================================================================================================================
	//getGameEngine()->getCameraman()->setShakeScreen(300,10,10,60);
}

void MiniGameEngine::shakeHard()
{ //=========================================================================================================================
	//getGameEngine()->getCameraman()->setShakeScreen(600,20,20,60);
}

//void MiniGameEngine::update()
//{
//	//	frameThrottleTicks += MiniGameEngine::engineTicksPassed();
//	//	if (throttle30fps && frameThrottleTicks < 33)
//	//	{
//	//		return;
//	//	}
//	//	ticksPassed = frameThrottleTicks;
//	//	frameThrottleTicks = 0;
//	Engine::update();
//}

void MiniGameEngine::setupMenus()
{ //=========================================================================================================================
  //override
	titleMenuShowing = true;
}


bool MiniGameEngine::updateMenus()
{ //=========================================================================================================================

	bool updatedMenu = false;

  //skip the title screen if we were initialized with a connection, either we are in the simulator or got a friend request

	if (connection != nullptr)
	{
		titleMenuShowing = false;
		multiplayerScreenShowing = false;
	}

	BobMenu::update(super::engineTicksPassed());


	if (titleMenuShowing)
	{
		updateTitleScreenLogo();

		titleMenuUpdate();
		updatedMenu = true;
	}


	if (multiplayerScreenShowing)
	{
		multiplayerScreenUpdate();
		updatedMenu = true;
	}


	if (waitingForFriendScreenShowing)
	{
		waitingForFriendScreenUpdate();
		updatedMenu = true;
	}

	return updatedMenu;
}

bool MiniGameEngine::renderMenus()
{ //=========================================================================================================================
	
	bool renderedMenu = false;

	if (connection != nullptr)
	{
		titleMenuShowing = false;
		multiplayerScreenShowing = false;
	}

	if (titleMenuShowing)
	{
		titleMenuRender();
		renderedMenu = true;
	}

	if (multiplayerScreenShowing)
	{
		multiplayerScreenRender();
		renderedMenu = true;
	}
	

	if (waitingForFriendScreenShowing)
	{
		waitingForFriendScreenRender();
		renderedMenu = true;
	}

	return renderedMenu;
}

//=========================================================================================================================
void MiniGameEngine::updateTitleScreenLogo()
{//=========================================================================================================================

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
}

void MiniGameEngine::updateTitleMenuLogoTexture()
{ //=========================================================================================================================
  //override
}

void MiniGameEngine::unloadTitleMenuTextures()
{//=========================================================================================================================
	if(titleMenuTextures!= nullptr && titleMenuTextures->size()>0)
	{
		for(int i=0;i<numTitleMenuTextureFrames;i++)titleMenuTextures->get(i)->release();
		titleMenuTextures->clear();
	}

	if (titleMenuTexture != nullptr)
	{
		titleMenuTexture->release();
		titleMenuTexture = nullptr;
	}

	//	if (cursorTexture != nullptr)
	//	{
	//		cursorTexture->release();
	//		cursorTexture = nullptr;
	//
	//	}
}





void MiniGameEngine::titleMenuUpdate()
{ //=========================================================================================================================

	if (titleMenu == nullptr)
	{
		titleMenu = new BobMenu(this,"");

		//pressEnterCaption = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, y-60, -1, "Press Enter to begin", BobFont::ttf_oswald_24, infoColor, clearColor, RenderOrder::OVER_GUI);
		//pressEnterCaption->flashing = true;
		//pressEnterCaption->flashingTicksPerFlash = 3000;

		titleMenu->add("Single Player");
		titleMenu->add("Online Multiplayer");
		titleMenu->add("Exit Game");

	}


	if (getServerConnection()->getConnectedToServer_S())
	{
		titleMenu->getMenuItemByID("Online Multiplayer")->setColor(BobColor::white);
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

		bool leaveMenu = false;

		if (titleMenu->isSelectedID("Single Player", clicked, mx, my))
		{
			leaveMenu = true;
		}

		if (titleMenu->isSelectedID("Online Multiplayer", clicked, mx, my))
		{
			if (getServerConnection()->getConnectedToServer_S())
			{
				multiplayerScreenShowing = true;
				leaveMenu = true;
			}
		}

		if (titleMenu->isSelectedID("Exit Game", clicked, mx, my))
		{
			Main::quit = true;
		}

		if (leaveMenu)
		{
			titleMenuShowing = false;

			if (titleMenu != nullptr)
			{
				delete titleMenu;
				titleMenu = nullptr;
			}
		}
	}

}

void MiniGameEngine::titleMenuRender()
{ //=========================================================================================================================

	BobTexture *t = nullptr;

	if (titleMenuTextures != nullptr && titleMenuTextures->size()>0)t = titleMenuTextures->get(currentTitleMenuTextureFrame);
	if (titleMenuTexture != nullptr)t = titleMenuTexture;

	if (t != nullptr)
	{
		titleMenu->setGraphic(t, getWidth() / 2, getHeight() / 4);
	}

	titleMenu->render();
}


//=========================================================================================================================
void MiniGameEngine::pauseMenuUpdate()
{//=========================================================================================================================

	if (pauseMenu == nullptr)
	{
		pauseMenu = new BobMenu(this,"Pause");

		pauseMenu->add("Back To Game");
		pauseMenu->add("Quit Game And Return To Title Screen");
	}

	if (getControlsManager()->miniGame_UP_Pressed())
	{
		pauseMenu->up();
	}

	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		pauseMenu->down();
	}


	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{

		if (pauseMenu->isSelectedID("Back To Game", clicked, mx, my))
		{
			leaveMenu = true;
		}

		if (pauseMenu->isSelectedID("Quit Game And Return To Title Screen", clicked, mx, my))
		{
			leaveMenu = true;
			titleMenuShowing = true;

		}

	}

	if (getControlsManager()->miniGame_CANCEL_Pressed())
	{
		leaveMenu = true;
	}

	if (leaveMenu)
	{
		pauseMenuShowing = false;

		if (pauseMenu != nullptr)
		{
			delete pauseMenu;
			pauseMenu = nullptr;
		}
	}

}


//=========================================================================================================================
void MiniGameEngine::pauseMenuRender()
{//=========================================================================================================================


	GLUtils::drawFilledRect(0,0,0, 0, (float)getWidth(), 0, (float)getHeight(), 0.7f);


	pauseMenu->render();
}



#pragma region NETWORK


void MiniGameEngine::multiplayerScreenUpdate()
{ //=========================================================================================================================


	if (onlineFriendCaptions->isEmpty())
	{
		//onlineFriendCaptions = new ArrayList<Caption*>();

		for (int i = 0; i < onlineFriends.size(); i++)
		{
			UDPPeerConnection* f = onlineFriends.get(i);
			int y = (onlineFriendCaptions->size() + 1) * 20;

			Caption* c = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, y, -1, f->getFriendData_S().characterName, BobFont::ttf_16, BobColor::white, BobColor::clear, RenderOrder::OVER_GUI);
			onlineFriendCaptions->add(c);
		}


		int y = (onlineFriendCaptions->size() + 1) * 20;
		Caption* c = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, y, -1, "Cancel", BobFont::ttf_16, BobColor::white, BobColor::clear, RenderOrder::OVER_GUI);
		onlineFriendCaptions->add(c);
	}


	if (getControlsManager()->miniGame_UP_Pressed())
	{
		multiplayerScreenCursorPosition--;
		if (multiplayerScreenCursorPosition < 0)
		{
			multiplayerScreenCursorPosition = onlineFriendCaptions->size() - 1;
		}
	}


	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		multiplayerScreenCursorPosition++;
		if (multiplayerScreenCursorPosition > onlineFriendCaptions->size() - 1)
		{
			multiplayerScreenCursorPosition = 0;
		}
	}

	bool leaveMenu = false;

	if (getControlsManager()->miniGame_CONFIRM_Pressed())
	{
		
		leaveMenu = true;

		if (multiplayerScreenCursorPosition == onlineFriendCaptions->size() - 1)
		{
			titleMenuShowing = true;
		}
		else
		{
			UDPPeerConnection* f = onlineFriends.get(multiplayerScreenCursorPosition);
			this->connection = f;
			BobNet::addEngineToForwardMessagesTo(this);

			waitingForFriendScreenShowing = true;
			setIncomingGameChallengeResponse(gameChallengeResponse_NONE);
		}
	}

	if (getControlsManager()->miniGame_CANCEL_Pressed())
	{
		leaveMenu = true;
		titleMenuShowing = true;
	}

	if(leaveMenu)
	{
		multiplayerScreenShowing = false;
		if (onlineFriendCaptions->size() > 0)
		{
			for (int i = 0; i < onlineFriendCaptions->size(); i++)
			{
				onlineFriendCaptions->get(i)->setToBeDeletedImmediately();
			}
		}

		onlineFriendCaptions->clear();
		//onlineFriends->clear();
	}

	//TODO: adjust captions y to center to middle of screen
}

void MiniGameEngine::multiplayerScreenRender()
{ //=========================================================================================================================

	super::render(); //captions

	BobTexture* t = BobMenu::cursorTexture;

	if (t != nullptr && onlineFriendCaptions->size() > 0)
	{
		float tx0 = 0;
		float tx1 = 1;

		float ty0 = 0;
		float ty1 = 1;


		float sx0 = onlineFriendCaptions->get(multiplayerScreenCursorPosition)->screenX - 16;
		if (BobMenu::cursorInOutToggle)
		{
			sx0 += 2;
		}
		float sx1 = sx0 + 16;

		float sy0 = onlineFriendCaptions->get(multiplayerScreenCursorPosition)->screenY + 2;
		float sy1 = sy0 + 16;


		GLUtils::drawTexture(t, tx0, tx1, ty0, ty1, sx0, sx1, sy0, sy1, 1.0f, GLUtils::FILTER_NEAREST);
	}
}


void MiniGameEngine::waitingForFriendScreenUpdate()
{ //=========================================================================================================================


  //we send the friendUDPConnection a "play game request"
  //it pops up a dialog
  //if they accept it, it opens their nD.
  //if they decline it or it times out we go back to the title screen


	long long currentTime = System::currentHighResTimer();



	if (gameChallengeRequestSentTime == -1)
	{
		gameChallengeRequestSentTime = currentTime;
	}


	if (connection != nullptr)
	{
		if (connection->getConnectedToPeer_S())
		{

			long long startTime = nonThreaded_SendGameChallengeRequestSentTime;
			int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

			if (ticksPassed > 2000)
			{
				nonThreaded_SendGameChallengeRequestSentTime = currentTime;

				//send "play game request"

				//log.debug("Game_Challenge_Request:bobsgame");
				connection->writeReliable_S(BobNet::Game_Challenge_Request + getGameName() + BobNet::endline);
			}
		}
	}


	if (waitingForFriendCaptions->isEmpty())
	{
		//waitingForFriendCaptions = new ArrayList<Caption*>();

		int y = (waitingForFriendCaptions->size() + 1) * 20;
		Caption* c = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, y, -1, "Sending game request...", BobFont::ttf_16, BobColor::white, BobColor::clear, RenderOrder::OVER_GUI);
		waitingForFriendCaptions->add(c);


		y = (waitingForFriendCaptions->size() + 1) * 20;
		c = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, y, -1, "Cancel", BobFont::ttf_16, BobColor::white, BobColor::clear, RenderOrder::OVER_GUI);
		waitingForFriendCaptions->add(c);
	}

	{
		long long startTime = gameChallengeRequestSentTime;
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (getControlsManager()->miniGame_CANCEL_Pressed() || ticksPassed > 15000)
		{
			gameChallengeRequestSentTime = -1;

			if (ticksPassed > 15000)
			{
				getCaptionManager()->newManagedCaption(Caption::CENTERED_SCREEN, 0, 3000, "Timed out.", BobFont::ttf_16, BobColor::white, BobColor::clear, RenderOrder::OVER_GUI);
			}


			if (waitingForFriendCaptions->size() > 0)
			{
				for (int i = 0; i < waitingForFriendCaptions->size(); i++)
				{
					waitingForFriendCaptions->get(i)->setToBeDeletedImmediately();
				}
			}

			this->connection = nullptr;

			//delete this->friendCharacter;
			//this->friendCharacter = nullptr;

			waitingForFriendCaptions->clear();

			titleMenuShowing = true;
			waitingForFriendScreenShowing = false;
		}
	}

	{
		long long startTime = nonThreaded_CheckForGameChallengeResponseCounter;
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 300)
		{
			nonThreaded_CheckForGameChallengeResponseCounter = currentTime;

			//threaded game challenge response

			//if it is declined, go back to title screen
			//make temp getCaption for 5 seconds in middle of screen
			int response = getIncomingGameChallengeResponse();


			if (response != gameChallengeResponse_NONE)
			{
				if (response == gameChallengeResponse_ACCEPT)
				{
					waitingForFriendScreenShowing = false;

					getCaptionManager()->newManagedCaption(Caption::CENTERED_SCREEN, 0, 5000, "Challenge Accepted!", BobFont::ttf_16, BobColor::green, BobColor::clear, RenderOrder::OVER_GUI);
				}


				if (response == gameChallengeResponse_DECLINE)
				{
					titleMenuShowing = true;
					waitingForFriendScreenShowing = false;

					getCaptionManager()->newManagedCaption(Caption::CENTERED_SCREEN, 0, 5000, "Challenge Declined", BobFont::ttf_16, BobColor::red, BobColor::clear, RenderOrder::OVER_GUI);

					this->connection = nullptr;
					//Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
					//delete this->friendCharacter;
				}


				gameChallengeRequestSentTime = -1;

				setIncomingGameChallengeResponse(gameChallengeResponse_NONE);

				if (waitingForFriendCaptions->size() > 0)
				{
					for (int i = 0; i < waitingForFriendCaptions->size(); i++)
					{
						waitingForFriendCaptions->get(i)->setToBeDeletedImmediately();
					}
				}

				waitingForFriendCaptions->clear();
			}
		}
	}
}
void MiniGameEngine::waitingForFriendScreenRender()
{ //=========================================================================================================================

	super::render(); //captions

	BobTexture* t = BobMenu::cursorTexture;

	if (t != nullptr && waitingForFriendCaptions->size() > 0)
	{
		float tx0 = 0;
		float tx1 = 1;

		float ty0 = 0;
		float ty1 = 1;


		float sx0 = waitingForFriendCaptions->get(1)->screenX - 16;
		if (BobMenu::cursorInOutToggle)
		{
			sx0 += 2;
		}
		float sx1 = sx0 + 16;

		float sy0 = waitingForFriendCaptions->get(1)->screenY + 2;
		float sy1 = sy0 + 16;


		GLUtils::drawTexture(t, tx0, tx1, ty0, ty1, sx0, sx1, sy0, sy1, 1.0f, GLUtils::FILTER_NEAREST);
	}
}



bool MiniGameEngine::isNetworkGame()
{ //=========================================================================================================================
	return connection!=nullptr;
}


void MiniGameEngine::tryToCloseGame()
{ //=========================================================================================================================


	//override this!
}



//
//void MiniGameEngine::setConnection(UDPConnection* connection)
//{ //=========================================================================================================================
//
//	this->connection = connection;
//	//this.multiplayer = true;
//}
bool MiniGameEngine::udpPeerMessageReceived(UDPPeerConnection *c, string e)// ChannelHandlerContext* ctx, MessageEvent* e)
{ //=========================================================================================================================

	string s = e;// static_cast<string>(e->getMessage());

				 //log.debug(s);


	if (s.find(":") == string::npos)
	{
		return false;
	}
	string command = s.substr(0, s.find(":") + 1);
	s = s.substr(s.find(":") + 1);


	if (command == BobNet::Game_Challenge_Response)
	{
		incoming_GameChallengeResponse(s);
		return true;
	}

	return false;
}

void MiniGameEngine::incoming_GameChallengeResponse(const string& s)
{ //=========================================================================================================================
  //responseString

	if (String::startsWith(s, "Decline"))
	{
		setIncomingGameChallengeResponse(gameChallengeResponse_DECLINE);
	}
	if (String::startsWith(s, "Accept"))
	{
		setIncomingGameChallengeResponse(gameChallengeResponse_ACCEPT);
	}
}

int MiniGameEngine::gameChallengeResponse_NONE = 0;
int MiniGameEngine::gameChallengeResponse_ACCEPT = 1;
int MiniGameEngine::gameChallengeResponse_DECLINE = 2;

//The following method was originally marked 'synchronized':
int MiniGameEngine::getIncomingGameChallengeResponse()
{
	return _incomingGameChallengeResponse;
}

//The following method was originally marked 'synchronized':
void MiniGameEngine::setIncomingGameChallengeResponse(int s)
{
	_incomingGameChallengeResponse = s;
}


#pragma endregion NETWORK