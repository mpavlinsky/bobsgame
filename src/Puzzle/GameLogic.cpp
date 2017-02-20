#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#include "Room.h"


Logger GameLogic::log = Logger("GameLogic");

int GameLogic::aboveGridBuffer = 4;
//int GameLogic::gameTypeCount = (int)(GameType::LAST);

//===============================================================================================
Engine* GameLogic::getEngine()
{//===============================================================================================
	return e;
}

//===============================================================================================
BobsGame* GameLogic::getBobsGame()
{//===============================================================================================
	return (BobsGame*)getEngine();
}


//=========================================================================================================================
CaptionManager* GameLogic::getCaptionManager()
{//=========================================================================================================================

	return getEngine()->getCaptionManager();
}


//===============================================================================================
GameLogic::GameLogic(Engine* g, long long seed)
{//===============================================================================================

	boost::uuids::random_generator generator;
	uuid = to_string(generator());

	captionTextColor = BobColor::white;
	captionBGColor = BobColor::clear;
	captionFont = BobFont::ttf_oswald_16;

	announcementCaptionTextColor = BobColor::white;
	announcementCaptionBGColor = BobColor::clear;
	announcementCaptionFont = BobFont::ttf_oswald_32;
	resultCaptionFont = BobFont::ttf_oswald_64;
	mediumCaptionFont = BobFont::ttf_oswald_16;



	this->e = g;

	grid = new Grid(this);

	randomSeed = seed;
	initializeRandomGenerator();

	currentGameType = (new GameType());

	grid->reformat(0, 0);

}

//=========================================================================================================================
GameLogic::~GameLogic()
{//=========================================================================================================================

	deleteAllCaptions();

	if (packetProcessThreadStarted)
	{
		setStopThread_S(true);
		packetProcessThread.join();
	}

}




//=========================================================================================================================
void GameLogic::initializeRandomGenerator()
{//=========================================================================================================================

	if (randomSeed == -1)
	{
		random_device randomDevice;//true random number generator, not pseudorandom
		default_random_engine defaultRandomEngine(randomDevice());

		randomSeed = defaultRandomEngine();// static_cast<long long>(rand() * (numeric_limits<long long>::max)());
	}

	if (randomSeed < 0)
	{
		randomSeed *= -1;
	}

	randomGenerator = mt19937((unsigned int)randomSeed);
}


//=========================================================================================================================
void GameLogic::fillGameTypeRandomBag()
{//=========================================================================================================================



	if (currentGameSequence->randomizeSequence)
	{
		ArrayList<GameType*> tempBag;

		for (int i = 0; i < currentGameSequence->gameTypes.size(); i++)
		{
			tempBag.add(currentGameSequence->gameTypes.get(i));
		}

		//tempBag.add(GameType::TETRID);
		//tempBag.add(GameType::DRBOB);

		while (tempBag.size() > 0)
		{
			int i = getRandomIntLessThan(tempBag.size(), "fillGameTypeRandomBag");

			GameType* g = tempBag.get(i);
			gameTypeRandomBag.add(g);

			tempBag.removeAt(i);
		}
	}
	else
	{
		for (int i = 0; i < currentGameSequence->gameTypes.size(); i++)
		{
			gameTypeRandomBag.add(currentGameSequence->gameTypes.get(i));
		}
	}

	//if random bag starts with current gametype, remove it and add it at the end instead.
	//this is a hack to prevent playing the same game twice
	if (gameTypeRandomBag.get(0) == currentGameType)
	{
		gameTypeRandomBag.removeAt(0);
		gameTypeRandomBag.add(currentGameType);
	}

}

//=========================================================================================================================
GameType* GameLogic::getGameTypeFromRandomBag()
{//=========================================================================================================================
	if (gameTypeRandomBag.isEmpty())
	{
		fillGameTypeRandomBag();
	}

	GameType* value = gameTypeRandomBag.get(0);

	gameTypeRandomBag.removeAt(0);

	return value;
}


//=========================================================================================================================
DifficultyType* GameLogic::getCurrentDifficulty()
{//=========================================================================================================================
	return currentGameType->getDifficultyByName(currentGameSequence->currentDifficultyName);
}

//=========================================================================================================================
void GameLogic::setGameType(GameType* gameType)
{//=========================================================================================================================

	previousGameString = currentGameType->name;

	//keep difficulty settings
	//string currentDifficultyName = getCurrentDifficulty()->name;
	currentGameType = (gameType);
	


}

#define INIT 1
//=========================================================================================================================
void GameLogic::initGame()
{//=========================================================================================================================


	//set all variables to initial state, in case when switching games
	//currentGameType = new GameType();

	if(firstInit)
	{
		firstInit = false;

		chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
		timeStarted = (long long)ms.count();
	}

	didInit = true;

	if (dontResetNextPieces == false)
	{
		resetNextPieces(); //set nextPiece to null
	}
	grid->randomBag.clear();


	//log.warn("Number of cells before: "+grid.getNumberOfFilledCells());

	int oldWidth = gridW();
	int oldHeight = gridH();


	
	//if (dontResetNextPieces == false)
	//{
		//clear arrays and reset settings variables



		//{
			setGameType(getGameTypeFromRandomBag());
		//}
	//}

	if (isNetworkPlayer)log.warn(currentGameType->name);
	else log.debug(currentGameType->name);

//	grid->blocks.clear();
//	for (int i = 0; i<grid->getWidth()*grid->getHeight(); i++)
//	{
//		grid->blocks.insert(i, grid->nullBlock);
//	}

	grid->reformat(oldWidth, oldHeight);

	grid->scrollPlayingFieldY = 0;

	//log.warn("Number of cells after reformat: "+grid.getNumberOfFilledCells());

	//force gravity first to fill in any gaps
	manuallyApplyGravityWithoutChainChecking();


	//log.warn("Number of cells after move down: "+grid.getNumberOfFilledCells());


	//go through playing field, change all blocks to acceptable playing field blocks if exist, otherwise normal pieces
	grid->replaceAllBlocksWithNewGameBlocks();


	//log.warn("Number of cells after replace: "+grid.getNumberOfFilledCells());

	//force gravity first to fill in any gaps
	manuallyApplyGravityWithoutChainChecking();

	//log.warn("Number of cells after move down again: "+grid.getNumberOfFilledCells());

	//possibly adding blocks or gaps to playing field i.e. dr






	//TODO: default background colors/animations/border colors for games

	//TODO: graphical meter for all timings and numbers, maybe piece fills up when locking? small meter next to piece for drop delay?

	//TODO: make all options variable and mix game() modes

	//TODO: shooter blocks don't have spawn delay, should move down at a set rate

	//TODO: maximum spawn/line clear delay


	lockDelayTicksCounter = currentGameType->maxLockDelayTicks;
	currentLineDropSpeedTicks = getCurrentDifficulty()->initialLineDropSpeedTicks;
	stopStackRiseTicksCounter = 1000;

	piecesMadeThisGame = 0;
	lastPiecesMadeThisGame = 0;
	blocksClearedThisGame = 0;
	linesClearedThisGame = 0;


	//TODO: 
	//maybe do this, it was commented out and i dont remember why
	//if(ME!=null)ME.deleteAllCaptions();
	//if(THEM!=null)THEM.deleteAllCaptions();



//
//	if (getCurrentGameType()->chainRule_CheckEntireLine)// && getCurrentGameType()->chainRule_AmountPerChain == 0)//TODO: see if this breaks anything!!
//	{
//		getCurrentGameType()->chainRule_AmountPerChain = gridW();
//	}


	if (currentGameType->randomlyFillGrid)
	{
		grid->randomlyFillGridWithPlayingFieldPieces(getCurrentDifficulty()->randomlyFillGridAmount, currentGameType->randomlyFillGridStartY);
	}

	if (currentGameType->randomlyFillStack)
	{
		grid->buildRandomStackRetainingExistingBlocks(getCurrentDifficulty()->randomlyFillStackAmount, currentGameType->randomlyFillStackStartY);
	}

	if (currentGameType->gameMode==GameMode::DROP)
	{
		newRandomPiece();
	}
	else
	if (currentGameType->gameMode == GameMode::STACK)
	{

		if (currentGameType->stackCursorType == CursorType::ONE_BLOCK_PICK_UP)
		{
			PieceType* cursorPiece = new PieceType("cursorPiece", "", nullptr, 1, Piece::get1BlockCursorRotationSet());
			BlockType* cursorBlock = BlockType::emptyBlockType;
			currentPiece = new Piece(this, grid, cursorPiece, cursorBlock);
			currentPiece->xGrid = (grid->getWidth() / 2);
			currentPiece->yGrid = 7 + GameLogic::aboveGridBuffer;
		}


		if (currentGameType->stackCursorType == CursorType::TWO_BLOCK_HORIZONTAL)
		{
			PieceType* cursorPiece = new PieceType("cursorPiece", "", nullptr, 2, Piece::get2BlockHorizontalCursorRotationSet());
			BlockType* cursorBlock = BlockType::emptyBlockType;
			currentPiece = new Piece(this, grid, cursorPiece, cursorBlock);
			currentPiece->xGrid = (grid->getWidth() / 2) - 1;
			currentPiece->yGrid = 7 + GameLogic::aboveGridBuffer;
		}


		if (currentGameType->stackCursorType == CursorType::TWO_BLOCK_VERTICAL)
		{
			PieceType* cursorPiece = new PieceType("cursorPiece", "", nullptr, 2, Piece::get2BlockVerticalCursorRotationSet());
			BlockType* cursorBlock = BlockType::emptyBlockType;
			currentPiece = new Piece(this, grid, cursorPiece, cursorBlock);
			currentPiece->xGrid = (grid->getWidth() / 2) - 1;
			currentPiece->yGrid = 7 + GameLogic::aboveGridBuffer;
		}


		if (currentGameType->stackCursorType == CursorType::THREE_BLOCK_HORIZONTAL)
		{
			PieceType* cursorPiece = new PieceType("cursorPiece", "", nullptr, 2, Piece::get3BlockHorizontalCursorRotationSet());
			BlockType* cursorBlock = BlockType::emptyBlockType;
			currentPiece = new Piece(this, grid, cursorPiece, cursorBlock);
			currentPiece->xGrid = (grid->getWidth() / 2) - 1;
			currentPiece->yGrid = 7 + GameLogic::aboveGridBuffer;
		}
		if (currentGameType->stackCursorType == CursorType::THREE_BLOCK_VERTICAL)
		{
			PieceType* cursorPiece = new PieceType("cursorPiece", "", nullptr, 2, Piece::get3BlockVerticalCursorRotationSet());
			BlockType* cursorBlock = BlockType::emptyBlockType;
			currentPiece = new Piece(this, grid, cursorPiece, cursorBlock);
			currentPiece->xGrid = (grid->getWidth() / 2) - 1;
			currentPiece->yGrid = 7 + GameLogic::aboveGridBuffer;
		}

		if (currentGameType->stackCursorType == CursorType::QUAD_BLOCK_ROTATE)
		{
			PieceType* cursorPiece = new PieceType("cursorPiece", "", nullptr, 4, Piece::get4BlockCursorRotationSet());
			BlockType* cursorBlock = BlockType::emptyBlockType;
			currentPiece = new Piece(this, grid, cursorPiece, cursorBlock);
			currentPiece->xGrid = (grid->getWidth() / 2) - 1;
			currentPiece->yGrid = 7 + GameLogic::aboveGridBuffer;
		}
		
	}


//	if (getCurrentDifficulty() == Difficulty::BEGINNER)
//	{
//		difficultyCaptionText = "Difficulty: Beginner";
//	}
//	else if (getCurrentDifficulty() == Difficulty::EASY)
//	{
//		difficultyCaptionText = "Difficulty: Easy";
//	}
//	else if (getCurrentDifficulty() == Difficulty::NORMAL)
//	{
//		difficultyCaptionText = "Difficulty: Normal";
//	}
//	else if (getCurrentDifficulty() == Difficulty::HARD)
//	{
//		difficultyCaptionText = "Difficulty: Hard";
//	}
//	else if (getCurrentDifficulty() == Difficulty::INSANE)
//	{
//		difficultyCaptionText = "Difficulty: Insane";
//	}
	


	getAudioManager()->stopMusic(playingMusic);
	playingMusic = currentGameType->normalMusic;
	getAudioManager()->playMusic(playingMusic);


	//		Writer output = null;
	//		try
	//		{
	//			output = new BufferedWriter(new FileWriter(new File(System.getProperty("user.home")+"\\Desktop\\output.txt")));
	//
	//			string settingsString = GameType().toJSON();
	//
	//			output.write(settingsString);
	//			output.close();
	//		}
	//		catch (IOException e)
	//		{
	//			e.printStackTrace();
	//		}
}



//=========================================================================================================================
void GameLogic::waitForPressStart()
{//=========================================================================================================================

	if (pressStartCaption == nullptr)
	{
		pressStartCaption = getCaptionManager()->newManagedCaption(0, (GLUtils::getViewportHeight() / 2) - 60, -1, "PRESS START", announcementCaptionFont, BobColor::yellow, BobColor::clear, RenderOrder::ABOVE, 1.0f);
	}
	else
	{
		pressStartCaption->screenX = (int)(grid->getXOnScreenNoShake() + (grid->getWidth() * cellW() / 2)) - pressStartCaption->getWidth() / 2;
		pressStartCaption->flashing = true;
		pressStartCaption->flashingTicksPerFlash = 500;
	}

	if (getControlsManager()->miniGame_CONFIRM_Pressed())
	{
		if (pressStartCaption != nullptr)
		{
			pressStartCaption->setToFadeOutAndBeDeleted();
			pressStartCaption = nullptr;
			//this will be deleted by the caption manager
		}

		waitingForStart = false;
		log.info("waitingForStart=false");
	}
}


//=========================================================================================================================
void GameLogic::waitForReady()
{//=========================================================================================================================
	if (playedReadySound == false)
	{
		getAudioManager()->playSound(currentGameType->readySound, getVolume(), 1.0f);
		playedReadySound = true;


		Caption* c = getCaptionManager()->newManagedCaption(0, (GLUtils::getViewportHeight() / 2) - 30, currentGameType->readyTicksAmount, "READY", announcementCaptionFont, BobColor::red, BobColor::clear, RenderOrder::ABOVE, 2.0f);
		c->screenX = (int)(grid->getXOnScreenNoShake() + (grid->getWidth() * cellW() / 2)) - c->getWidth() / 2;
	}


	readyTicksCounter += getEngine()->engineTicksPassed();
	if (readyTicksCounter > currentGameType->readyTicksAmount)
	{
		readyTicksCounter = 0;
		playedReadySound = true;
		waitingForReady = false;

		getAudioManager()->playSound(currentGameType->goSound, getVolume(), 1.0f);

		Caption* c = getCaptionManager()->newManagedCaption(0, (GLUtils::getViewportHeight() / 2), 1000, "GO!", announcementCaptionFont, BobColor::green, BobColor::clear, RenderOrder::ABOVE, 2.0f);
		c->screenX = (int)(grid->getXOnScreenNoShake() + (grid->getWidth() * cellW() / 2)) - c->getWidth() / 2;
		c->flashing = true;
		c->flashingTicksPerFlash = 80;
	}
}

#define UPDATE 1

//=========================================================================================================================
void GameLogic::update(PuzzlePlayer* p, int gameIndex, int numGames, float forceWidth, float forceHeight)
{//=========================================================================================================================

	float screenWidth = getBobsGame()->getWidth();
	float screenHeight = getBobsGame()->getHeight();
	
	if (forceWidth != 0)
	{
		screenWidth = forceWidth;
		screenHeight = forceHeight;
	}

	//setGridXY(p, gameIndex, numGames);
	{
		int colWidth = 0;
		int rows = 1;
		bool done = false;
		int rowHeight = screenHeight;

		while (!done)
		{
			int numBlocksW = gridW() + 4;
			int numBlocksH = gridH() + 7;
			rowHeight = screenHeight / rows;

			//get window size, divide by numGames, fit game into width with height limited to a maximum
			colWidth = screenWidth / (int)ceil((float)numGames / (float)rows);

			//set the block height based on how many fit in window height
			blockHeight = (rowHeight / numBlocksH);
			//set block width based on how many fit in the game width
			blockWidth = (colWidth / numBlocksW);

			//if the height is less than the width, set the block width to block height, for play fields that are wider than tall like single player
			if (blockHeight < blockWidth)blockWidth = blockHeight;
			//if the width is less than the height, set the height to the width, for narrow play fields like multiplayer
			else if (blockWidth < blockHeight)blockHeight = blockWidth;

			blockWidth -= currentGameType->gridPixelsBetweenColumns;
			blockHeight -= currentGameType->gridPixelsBetweenRows;

			//if the game is shorter than rows+1 on the screen, let's increase the rows of games
			if (numBlocksH*cellH() <= screenHeight / (rows + 1))
			{
				rows++;
			}
			else
			{
				done = true;
			}
		}


		int gamesPerRow = (int)ceil((float)numGames / (float)rows);
		int row = ((int)floor((float)(gameIndex) / (float)gamesPerRow));
		int indexInRow = 0;
		indexInRow = gameIndex - (row*gamesPerRow);

		//center grid in column
		grid->screenX = (float)(indexInRow*colWidth) + ((colWidth / 2 - ((gridW() * cellW()) / 2))); // - cellW()*3;
																									 //offset height by 5 blocks
		grid->screenY = (float)(row*rowHeight) + (5 * cellH()); //getHeight()/2 - (gridH()*cellH())/2;

		playingFieldX0 = (float)(indexInRow*colWidth);
		playingFieldX1 = (float)(indexInRow*colWidth + colWidth);
		playingFieldY0 = (float)(row*rowHeight);
		playingFieldY1 = (float)(row*rowHeight + rowHeight);

		if (p->nameCaption != nullptr)
		{
			p->nameCaption->screenX = grid->getXOnScreenNoShake();
			p->nameCaption->screenY = grid->getYOnScreenNoShake() + gridH()* cellH();
			p->nameCaption->setTextColor(BobColor::white);
		}
		if (p->gameCaption != nullptr)
		{
			p->gameCaption->screenX = grid->getXOnScreenNoShake();
			p->gameCaption->screenY = grid->getYOnScreenNoShake() + gridH()* cellH() + 16;
			p->gameCaption->setTextColor(BobColor::white);
		}
		if (p->difficultyCaption != nullptr)
		{
			p->difficultyCaption->screenX = grid->getXOnScreenNoShake();
			p->difficultyCaption->screenY = grid->getYOnScreenNoShake() + gridH()* cellH() + 16 + 16;
			p->difficultyCaption->setTextColor(BobColor::white);
		}

		captionX = (float)(grid->getXOnScreenNoShake() + (grid->getWidth() + 1) * cellW()) + 4;
	}



	updateCaptionFadeValues();

	if (isNetworkPlayer == false)
	{

		if (testing == false)
		{
			if (waitingForStart)
			{
				waitForPressStart();
				return;
			}

			if (waitingForReady)
			{
				waitForReady();
				return;
			}
		}

		frameState = FrameState();
		frameState.ticksPassed = getEngine()->engineTicksPassed();


		if(p->pausePressed())
		{
			if(numGames==1)
			{
				getBobsGame()->pauseMenuShowing = true;
			}
			else
			{
				pauseMiniMenuShowing = true;
			}
		}

		if(pauseMiniMenuShowing)
		{
			getBobsGame()->playerPauseMiniMenuUpdate(p);

		}
		else
		{
			setControlsState(p);
		}


		//log.debug("New frame");

		if (didInit == false)initGame();
		
		processFrame();
		



		if (getBobsGame()->isNetworkGame() == false)
		{
			if (getBobsGame()->currentRoom->multiplayer_DisableVSGarbage == false)
			{
				if (queuedVSGarbageAmountToSend > 0)
				{
					for (int n = 0; n < getBobsGame()->players.size(); n++)
					{
						PuzzlePlayer *p2 = getBobsGame()->players.get(n);

						GameLogic *g2 = p2->gameLogic;
						if (g2 != this && Math::randLessThan(getBobsGame()->players.size()) == 0)g2->gotVSGarbageFromOtherPlayer(queuedVSGarbageAmountToSend);
					}
					queuedVSGarbageAmountToSend = 0;
				}
			}

		}
		else
		{

			if (getBobsGame()->currentRoom->multiplayer_DisableVSGarbage == false)
			{
				for (int n = 0; n < getBobsGame()->players.size(); n++)
				{
					PuzzlePlayer *p2 = getBobsGame()->players.get(n);
					GameLogic *g2 = p2->gameLogic;
					if (g2 != this)
					{
						if (g2->queuedVSGarbageAmountToSend > 0)// && Math::randLessThan(getBobsGame()->players.size()) == 0)
						{
							gotVSGarbageFromOtherPlayer(g2->queuedVSGarbageAmountToSend);
						}
						g2->queuedVSGarbageAmountToSend = 0;
					}
				}
			}

			string gridString;
			for (int n = 0; n<grid->blocks.size(); n++)
			{
				gridString += to_string(grid->blocks.get(n) != grid->nullBlock);
			}
			frameState.gridString = gridString;
			frameState.randomInt = randomGenerator();



			sendPacketsToOtherPlayers(p);
			//TODO: handle accepting garbage from network players games

			//handle gotGarbage for network players

			//TODO: store "got garbage" in frameState so the actual release of garbage is exactly synced

		}

		framesArray.add(frameState);
	}
	else
	if (isNetworkPlayer == true)
	{

//		if (waitingForPlayer == true)
//		{
//			return;
//		}
		
		//dont remember why this is commented out, maybe i dont need it anymore
		//		{
		//			if(waitingForPlayerCaption==null)
		//			{
		//				waitingForPlayerCaption = getCaptionManager()->newManagedCaption(0,(int)(ScreenHeight/2)-60,-1,"Waiting For Challenger",BobFont.font_normal_8_outlined,Color.darkGray,Color.CLEAR,1.0f,50,false, true);
		//			}
		//			else
		//			{
		//				waitingForPlayerCaption.getScreenX = (int)(grid.getScreenX+(grid.getWidth()*cellW()/2)) - waitingForPlayerCaption.getWidth()/2;
		//				waitingForPlayerCaption.flashing = true;
		//				waitingForPlayerCaption.flashingTicksPerFlash = 10000;
		//			}
		//
		//			return;
		//		}
		//		else
		//		{
		//			if(waitingForPlayerCaption!=null)
		//			{
		//				waitingForPlayerCaption.setToFadeOutAndBeDeleted();
		//				waitingForPlayerCaption = null;
		//			}
		//		}

 

		//updateNetworkGame
		if (incomingFramePacketsSize_S() > 0)
		{
			if (incomingFramePacketsContainsKey_S(lastIncomingFramePacketID))
			{
				ArrayList<FrameState> incomingFrames = incomingFramePacketsGet_S(lastIncomingFramePacketID);
				incomingFramePacketsRemoveAt_S(lastIncomingFramePacketID);

				lastIncomingFramePacketID++;

				while (incomingFrames.size()>0)
				{
					FrameState f = incomingFrames.get(0);
					incomingFrames.removeAt(0);
					framesArray.add(f);
				}

				waitingForNetworkFrames = false;
			}
			else
			{
				log.error("incomingFramePackets contains out of order frame!");
			}
		}

		

		
		//check timeout
		long long currentTime = System::currentHighResTimer();
		long long ticksPassed = (long long)System::getTicksBetweenTimes(checkLastTrafficTime, currentTime);
		if (ticksPassed > 15000)
		{
			checkLastTrafficTime = currentTime;
			ticksPassed = (long long)System::getTicksBetweenTimes(getLastTimeGotIncomingTraffic(), currentTime);
			if (ticksPassed > 15000)
			{
				if (p->peerConnection->getConnectedToPeer_S() == false)
				{
					//TODO: drop connection, match is forfeit, i am winner
					setTheyForfeit(true);
				}
			}

			if (getTheyForfeit() == true)
			{
				//THEM->lose = true;
				//g->win = true;
				died = true;
			}

		}
		

		if (waitingForNetworkFrames == true)
		{
			return;
		}

		if (framesArray.size() > 0)
		{
			int numFrames = framesArray.size();
			int framesToProcess = 1;
			int secondsBehind = (int)floor((float)numFrames * 16.0f / 1000.0f );
			if (secondsBehind >= 1)framesToProcess = 1 + ((int)pow(2,secondsBehind)-1);
			for (int i = 0; i < framesToProcess; i++)//process at least 1 frame and 10% of how far behind we are to catch up
			{
				if (framesArray.size() > 0)
				{
					this->frameState = framesArray.get(0);
					framesArray.removeAt(0);

					//log.warn("New frame");

					if (didInit == false)
					{
						initGame();
					}

					processFrame();

					if (getBobsGame()->currentRoom->multiplayer_DisableVSGarbage == false)
					{
						if (frameState.receivedGarbageAmount > 0) //this should only happen when we are the network side
						{
							gotVSGarbageFromOtherPlayer(frameState.receivedGarbageAmount);
						}
					}

					string gridString;
					for (int n = 0; n<grid->blocks.size(); n++)
					{
						gridString += to_string(grid->blocks.get(n) != grid->nullBlock);
					}
					int r = randomGenerator();
					if(frameState.gridString != gridString || frameState.randomInt != r)log.error("Desync! r: " + to_string(r) + "  frameState.randomInt: " + to_string(frameState.randomInt) + " gridString: "+gridString + " frameState.gridString: "+frameState.gridString );




				}
			}
		}
		else
		waitingForNetworkFrames = true;

	}
}
//=========================================================================================================================
void GameLogic::sendPacketsToOtherPlayers(PuzzlePlayer *p)
{//=========================================================================================================================
	long long currentTime = System::currentHighResTimer();

	//DONE: queue up packets, with id, md5

	//storeNetworkPackets()
	{

		long long ticksPassed = (long long)System::getTicksBetweenTimes(storePacketsTicksCounter, currentTime);
		if (ticksPassed > 200)
		{
			storePacketsTicksCounter = currentTime;

			ArrayList<FrameState> packetToSplit = framesArray;
			framesArray = ArrayList<FrameState>();


			int maxFramesInPacket = 800/16;

			if ((int)packetToSplit.size() > maxFramesInPacket)
			{
				log.debug("Splitting packet");
				//if player 1 has been playing for a while, the network packet will have too many frames in it.
				//so we split it into multiple packets.
				while (packetToSplit.size() > 0)
				{
					ArrayList<FrameState> partialPacket;

					int size = packetToSplit.size();
					for (int i = 0; i < maxFramesInPacket && i < size; i++)
					{
						FrameState frame = packetToSplit.get(0);

						packetToSplit.removeAt(0);
						//Vector<FrameState>::removeAt(packetToSplit.frameStates,0);

						partialPacket.add(frame);
						size--;
					}

					allNetworkPacketsSentUpUntilNow.add(partialPacket);
				}

			}
			else
			if ((int)packetToSplit.size() > 0)
			{
				allNetworkPacketsSentUpUntilNow.add(packetToSplit);
			}
		}
	}

	//queueSendPackets()
	{
		int size = allNetworkPacketsSentUpUntilNow.size();

		for (int j = lastSentPacketID; j < size; j++)
		{

			ArrayList<FrameState> networkPacket = allNetworkPacketsSentUpUntilNow.get(j);

			string b64zip = FrameState::getFrameStatesAsBase64GZippedXML(networkPacket);
			string md5 = FileUtils::getStringMD5(b64zip);

			//log.debug("Packet Size: "+b64zip.length());

			string idAndMD5String = to_string(j) + "," + md5;

			outboundPacketQueueVector.add(idAndMD5String); //just so we have an ordered list we can get(0) from
			outboundPacketQueueHashMap.put(idAndMD5String, b64zip);
		}

		lastSentPacketID = size;
	}



	//send our local players network packets to all peers
	//send_QueuedPacket()
	{
		//send packet 0

		if (outboundPacketQueueVector.size() > 0)
		{
			string idAndMD5String = outboundPacketQueueVector.get(0);
			string b64zip = outboundPacketQueueHashMap.get(idAndMD5String);


			getBobsGame()->sendAllJoinedPeers(BobsGame::netCommand_FRAME + p->getID() + ":" + idAndMD5String + ":" + b64zip);

			//remove id,MD5 from vector queue 	
			//remove id,MD5 from hashmap queue 	
			//if got id, md5, remove packet 0 	
			//if not, send packet 0 again 	
			outboundPacketQueueHashMap.removeAt(idAndMD5String);
			outboundPacketQueueVector.removeAt(0);// idAndMD5String);
		}
	}

	
}




//=========================================================================================================================
void GameLogic::incoming_FramePacket(const string &s)
{ //=========================================================================================================================

	setLastTimeGotIncomingTraffic();

	incomingPacketQueuePush_S(s);

	if(packetProcessThreadStarted == false)
	{
		//log.debug("Creating frame processing thread");
		packetProcessThread = thread(&GameLogic::_packetProcessThreadLoop,this);
		packetProcessThreadStarted = true;
	}

}

//=========================================================================================================================
void GameLogic::_packetProcessThreadLoop(GameLogic *g)
{//=========================================================================================================================

	//log.debug("Started frame processing thread");
	while (g->getStopThread_S()==false)
	{
		this_thread::sleep_for(chrono::milliseconds(100));

		g->_processIncomingPackets();
	}
}

//=========================================================================================================================
void GameLogic::_processIncomingPackets()
{//=========================================================================================================================

	while (incomingPacketQueueSize_S() > 0)
	{
		this_thread::sleep_for(chrono::milliseconds(10));

		string s = incomingPacketQueueFront_S();
		incomingPacketQueuePop_S();

		//packetID,MD5:base64

		//get ID, md5
		if (s.find(":") == -1)
		{
			return;
		}
		string idMD5 = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);
		string frameData = s.substr(0, s.find(":"));

		long long id = -1;
		try
		{
			id = StringConverterHelper::fromString<long long>(idMD5.substr(0, idMD5.find(",")));
		}
		catch (exception)
		{
			log.error("Failed to parse framePacket ID in incoming frame packet");
			return;
		}
		string md5 = idMD5.substr(idMD5.find(",") + 1);

		string compMD5 = FileUtils::getStringMD5(frameData);
		if (md5 != compMD5)
		{
			log.error("Frame Packet MD5 did not match!");
			return;
		}

		//store id, md5 in "got packets" log so we don't add the same frame packet twice, in case our "OK" doesn't make it back and they keep sending it
		if (_gotPacketsLog.contains(idMD5) == false)
		{

			//if not in log, add to log, add frames to queue, send back id, md5 as confirmation
			ArrayList<FrameState> packet = FrameState::getFramesArrayFromBase64GZippedXML(frameData);

			//queue<FrameState> frames = packet.frameStates;

			if (packet.size() > 0)
			{
				//log.info("Added framePacket ID: "+id);
				if (incomingFramePacketsContainsKey_S(id))
				{
					log.error("Incoming framePacket was already inserted into incomingFramePackets");
				}
				else
				{
					incomingFramePacketsPut_S(id, packet);
				}

				_gotPacketsLog.add(idMD5);

			}
		}
	}
}



//=========================================================================================================================
//void GameLogic::incoming_Forfeit(string s)
//{ //=========================================================================================================================
//
//  //randomSeed:
//
//	if (s.find(":") == -1)
//	{
//		return;
//	}
//	long long theirRandomSeed = -1;
//	try
//	{
//		theirRandomSeed = StringConverterHelper::fromString<long long>(s.substr(0, s.find(":")));
//	}
//	catch (exception)
//	{
//		log.error("Failed to parse randomSeed in incoming frame packet");
//		return;
//	}
//	//s = s.substring(s.indexOf(":")+1);
//
//#ifdef _DEBUG
//		log.error(string("incoming_Forfeit: Their Seed: ") + to_string(theirRandomSeed));
//#endif
//	//Game them = games.get(randomSeed);
//	//if(them==null){log.error("Could not find game with seed:" + randomSeed);return;}
//
//	setTheyForfeit(true);
//
//}
//
//void GameLogic::sendForfeit()
//{ //=========================================================================================================================
//	connection->write(netCommand_FORFEIT + to_string(randomSeed) + string(":") + string("-1") + BobNet::endline);
//}




long long GameLogic::getLastTimeGotIncomingTraffic()
{
	return lastIncomingTrafficTime;
}

void GameLogic::setLastTimeGotIncomingTraffic()
{
	this->lastIncomingTrafficTime = System::currentHighResTimer();
}

bool GameLogic::getTheyForfeit()
{
	return theyForfeit;
}

void GameLogic::setTheyForfeit(bool b)
{
	this->theyForfeit = b;
}

//=========================================================================================================================
void GameLogic::setControlsState(PuzzlePlayer *p)
{//=========================================================================================================================

	frameState.ROTATECW_HELD = p->ROTATECW_HELD;
	frameState.HOLDRAISE_HELD = p->HOLDRAISE_HELD;
	frameState.ROTATECCW_HELD = p->ROTATECCW_HELD;
	frameState.UP_HELD = p->UP_HELD;
	frameState.LEFT_HELD = p->LEFT_HELD;
	frameState.DOWN_HELD = p->DOWN_HELD;
	frameState.RIGHT_HELD = p->RIGHT_HELD;
	frameState.SLAM_HELD = p->SLAM_HELD;
}



//=========================================================================================================================
void GameLogic::processFrame()
{//=========================================================================================================================


	updateCaptions();


	if(won || lost || complete || died)
	{
		if (timeEnded == 0)timeEnded = System::currentHighResTimer();
	}

	if (won == true)
	{
		wonSequence();
		return;
	}

	if (lost == true)
	{
		lostSequence();
		return;
	}

	if (complete == true)
	{
		creditsSequence();
		return;
	}

	if (died == true)
	{
		diedSequence();
		return;
	}


	totalTicksPassed += ticks();

	updateSpecialPiecesAndBlocks();


	if (currentGameType->playingFieldGarbageSpawnRule != GarbageSpawnRule::NONE)
	{
		processGarbageRules();
	}

	processQueuedGarbageSentFromOtherPlayer();

	grid->update();

	grid->scrollBackground();

	doExtraStageEffects();


	lockInputCountdownTicks -= ticks();
	if (lockInputCountdownTicks < 0)
	{
		lockInputCountdownTicks = 0;
	}

	lockDelayTicksCounter -= ticks();
	if (lockDelayTicksCounter < 0)
	{
		lockDelayTicksCounter = 0;
	}

	lineDropTicksCounter -= ticks();
	if (lineDropTicksCounter < 0)
	{
		lineDropTicksCounter = 0;
	}

	lineClearDelayTicksCounter -= ticks();
	if (lineClearDelayTicksCounter < 0)
	{
		lineClearDelayTicksCounter = 0;
	}

	spawnDelayTicksCounter -= ticks();
	if (spawnDelayTicksCounter < 0)
	{
		spawnDelayTicksCounter = 0;
	}


	if (currentGameType->gameMode == GameMode::STACK)
	{
		doStackRiseGame();
	}
	else
	if (currentGameType->gameMode == GameMode::DROP)
	{
		doFallingBlockGame();
	}


	moveDownLineTicksCounter += ticks();

	if ((pieceSetAtBottom == true && detectedChain() == false) || forceGravityThisFrame)
	{
		if (checkForChainAgainIfNoBlocksPopping)
		{
			if (grid->areAnyBlocksPopping())
			{
				return;
			}
			else
			{
				checkForChainAgainIfNoBlocksPopping = false;
			}
		}

		bool movedDownBlocks = moveDownBlocksOverBlankSpaces();

		if (movedDownBlocks == true)
		{
			gravityThisFrame = true;
		}

		if (movedDownBlocks == false)
		{
			forceGravityThisFrame = false;

			gravityThisFrame = false;


			checkForChain();


			handleNewChain();


			checkForFastMusic();


			if (detectedChain() == false && checkForChainAgainIfNoBlocksPopping == false)
			{
				currentCombo = 0;
				currentChain = 0;
				comboChainTotal = 0;

				if (currentGameType->gameMode == GameMode::STACK)
				{
					//don't make new piece since they are not "falling block" games
				}
				else
				if (currentGameType->gameMode == GameMode::DROP)
				{
					if (pieceSetAtBottom == true)
					{
						newRandomPiece();
					}
				}

				updateScore(); //must set new game type here while there are no flashing blocks
			}
		}
	}
}




//=========================================================================================================================
void GameLogic::flashScreen()
{//=========================================================================================================================

	flashScreenTicksCounter += ticks();
	if (flashScreenTicksCounter > flashScreenSpeedTicks)
	{
		flashScreenTicksCounter = 0;

		flashScreenOnOffToggle = !flashScreenOnOffToggle;

		if (flashScreenOnOffToggle == true)
		{
			timesToFlashScreenQueue--;
		}
	}
}


//=========================================================================================================================
void GameLogic::flashChainBlocks()
{//=========================================================================================================================

	flashBlocksTicksCounter += ticks();

	if (flashBlocksTicksCounter > flashBlockSpeedTicks)
	{
		flashBlocksTicksCounter = 0;

		if (detectedChain())
		{
			for (int i = 0; i < currentChainBlocks.size(); i++)
			{
				currentChainBlocks.get(i)->flashingToBeRemovedLightDarkToggle = !currentChainBlocks.get(i)->flashingToBeRemovedLightDarkToggle;
			}
		}

		timesToFlashBlocksQueue--;
	}
}

//=========================================================================================================================
void GameLogic::removeFlashedChainBlocks()
{//=========================================================================================================================


	int linesCleared = 0;
	int blocksCleared = 0;

	if (currentChainBlocks.size() > 0)
	{
		for (int i = 0; i < currentChainBlocks.size(); i++)
		{
			Block* b = currentChainBlocks.get(i);

			if (b->overrideAnySpecialBehavior == false)
			{
				if (b->blockType->makePieceTypeWhenCleared_UUID.size()>0)
				{
					PieceType *pt = currentGameType->getPieceTypeByUUID(b->blockType->makePieceTypeWhenCleared_UUID.get(getRandomIntLessThan(b->blockType->makePieceTypeWhenCleared_UUID.size(), "removeFlashedChainBlocks")));
					Piece* p = new Piece(this, grid, pt, BlockType::emptyBlockType);
					nextPieceSpecialBuffer.add(p);

					//DONE: sound "got bomb" "got weight" "got shooter"
					if (p->pieceType->bombPiece)
					{
						makeAnnouncementCaption("BOMB", BobColor::blue);
						getAudioManager()->playSound(currentGameType->gotBombSound, getVolume(), 1.0f);
					}

					if (p->pieceType->weightPiece)
					{
						makeAnnouncementCaption("WEIGHT", BobColor::orange);
						getAudioManager()->playSound(currentGameType->gotWeightSound, getVolume(), 1.0f);
					}

					if (p->pieceType->clearEveryRowPieceIsOnIfAnySingleRowCleared)
					{
						makeAnnouncementCaption("FLASHING CLEAR", BobColor::green);
						getAudioManager()->playSound(currentGameType->flashingClearSound, getVolume(), 1.0f);
					}

					if (p->pieceType->pieceRemovalShooterPiece)
					{
						makeAnnouncementCaption("SUBTRACTOR", BobColor::red);
						getAudioManager()->playSound(currentGameType->gotSubtractorSound, getVolume(), 1.0f);
					}

					if (p->pieceType->pieceShooterPiece)
					{
						makeAnnouncementCaption("ADDER", BobColor::yellow);
						getAudioManager()->playSound(currentGameType->gotAdderSound, getVolume(), 1.0f);
					}
				}

				if (b->blockType->clearEveryOtherLineOnGridWhenCleared)
				{
					makeAnnouncementCaption("SCANLINE CLEAR", BobColor::red);
					getAudioManager()->playSound(currentGameType->scanlineClearSound, getVolume(), 1.0f);

					//add every other line to clear blocks
					for (int y = gridH() - 2; y >= 0; y -= 2)
					{
						for (int x = 0; x < gridW(); x++)
						{
							Block* c = grid->get(x, y);
							if (c != nullptr)
							{
								if (currentChainBlocks.contains(c) == false)
								{
									currentChainBlocks.add(c);
								}
							}
						}
					}

					grid->shakeSmall();
				}
			}
		}


		removeBlocksTicksCounter += ticks();

		while 
		(
			currentChainBlocks.size() > 0 
			&& 
			(
				currentGameType->removingBlocksDelayTicksBetweenEachBlock == 0 
				|| 
				removeBlocksTicksCounter > currentGameType->removingBlocksDelayTicksBetweenEachBlock
			)
		)
		{
			//flash blocks slower, remove one at a time

			removeBlocksTicksCounter = 0;

			Block* a = currentChainBlocks.get(0);
			//we need to pop any boxes touching this one
			ArrayList<Block*> temp = grid->getConnectedBlocksUpDownLeftRight(a);
			if (temp.size() > 0)
			{
				for (int i = 0; i < temp.size(); i++)
				{
					Block* b = temp.get(i);

					if (b->blockType->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_UUID.size()>0)
					{
						b->popping = true;
						b->animationFrame = 0;

						checkForChainAgainIfNoBlocksPopping = true;
					}
				}
			}

			if (currentGameType->chainRule_CheckEntireLine)
			{
				//clear line by line and add score per line
				for (int i = 0; i < currentChainBlocks.size(); i++)
				{
					Block* b = currentChainBlocks.get(i);

					if (b != a && b->yGrid == a->yGrid)
					{
						//currentChainBlocks.Remove(b);
						currentChainBlocks.remove(b);

						grid->remove(b, true, true);

						blocksCleared++;
						blocksClearedThisGame++;
						blocksClearedThisLevel++;
						blocksClearedTotal++;

						i = -1;
					}
				}

				linesCleared++;
				linesClearedThisGame++;
				linesClearedThisLevel++;
				linesClearedTotal++;
			}


			currentChainBlocks.remove(a);

			grid->remove(a, true, true);

			blocksCleared++;
			blocksClearedThisGame++;
			blocksClearedThisLevel++;
			blocksClearedTotal++;
		}
	}

	timesToFlashScreenQueue += linesCleared;

	if (linesCleared == 1)
	{
		getAudioManager()->playSound(currentGameType->singleLineFlashingSound, getVolume(), 1.0f);
	}
	if (linesCleared == 2)
	{
		getAudioManager()->playSound(currentGameType->doubleLineFlashingSound, getVolume(), 1.0f);
	}
	if (linesCleared == 3)
	{
		getAudioManager()->playSound(currentGameType->tripleLineFlashingSound, getVolume(), 1.0f);
	}
	if (linesCleared >= 4)
	{
		getAudioManager()->playSound(currentGameType->quadLineFlashingSound, getVolume(), 1.0f);
		makeAnnouncementCaption("SOSUMI!", BobColor::green);
	}


	if (currentGameType->chainRule_CheckEntireLine)
	{
		lineClearDelayTicksCounter += linesCleared * currentGameType->lineClearDelayTicksAmountPerLine;
	}
	else
	{
		lineClearDelayTicksCounter += blocksCleared * currentGameType->lineClearDelayTicksAmountPerBlock;
	}


	currentChain = currentChainBlocks.size();
}


//=========================================================================================================================
void GameLogic::updateSpecialPiecesAndBlocks()
{//=========================================================================================================================

	if (currentPiece != nullptr)
	{
		currentPiece->update();
	}
	if (holdPiece != nullptr)
	{
		holdPiece->update();
	}

	if (nextPieces.size() > 0)
	{
		for (int i = 0; i < nextPieces.size(); i++)
		{
			nextPieces.get(i)->update();
		}
	}


	if (nextPieceSpecialBuffer.size() > 0)
	{
		for (int i = 0; i < nextPieceSpecialBuffer.size(); i++)
		{
			nextPieceSpecialBuffer.get(i)->update();
		}
	}

	if (fadingOutBlocks.size() > 0)
	{
		for (int i = 0; i < fadingOutBlocks.size(); i++)
		{
			fadingOutBlocks.get(i)->update();
		}
	}
}


//=========================================================================================================================
void GameLogic::addToChainBlocks(ArrayList<Block*> &arr)
{//=========================================================================================================================

	if (arr.size() > 0)
	{

		for (int i = 0; i < arr.size(); i++)
		{
			if (currentChainBlocks.contains(arr.get(i)) == false)
			{
				currentChainBlocks.add(arr.get(i));
			}
		}
	}
}


//=========================================================================================================================
bool GameLogic::detectedChain()
{//=========================================================================================================================
	if (currentChainBlocks.size() > 0 && currentChainBlocks.size() > 0)
	{
		return true;
	}

	return false;
}



//=========================================================================================================================
void GameLogic::checkForChain()
{//=========================================================================================================================


	currentChainBlocks.clear();

	ArrayList<BlockType*> ignoreTypes = currentGameType->getBlockTypesToIgnoreWhenCheckingChain(getCurrentDifficulty());
	ArrayList<BlockType*> mustContainAtLeastOneTypes = currentGameType->getBlockTypesChainMustContain(getCurrentDifficulty());


	//can use this while blocks are falling to detect sticky colors
	//while blocks are falling we can make them visually appear joined if they are the same color and are supposed to glob together
	grid->setColorConnections(ignoreTypes);

	



	int toRow = grid->getHeight();
	if (currentGameType->gameMode == GameMode::STACK)
	{
		toRow = grid->getHeight() - 1; //stack rise games have one visible buffer row that isnt part of the chain
	}

	if (currentGameType->chainRule_CheckEntireLine)
	{
		ArrayList<Block*> chainBlocks = grid->checkLines(ignoreTypes, mustContainAtLeastOneTypes);
		addToChainBlocks(chainBlocks);
	}
	

	if (currentGameType->chainRule_AmountPerChain > 0)
	{
		ArrayList<Block*> chainBlocks;

		for (int y = 0; y < toRow; y++)
		{
			for (int x = 0; x < grid->getWidth(); x++)
			{
				Block* b = grid->get(x, y);

				if (b != nullptr && (ignoreTypes.isEmpty() || ignoreTypes.contains(b->blockType) == false))
				{
					if (currentGameType->chainRule_CheckRow)
					{
						grid->addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowAtLeastAmount(b, chainBlocks, currentGameType->chainRule_AmountPerChain, 0, grid->getWidth(), 0, toRow, ignoreTypes, mustContainAtLeastOneTypes);
					}
					if (currentGameType->chainRule_CheckColumn)
					{
						grid->addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInColumnAtLeastAmount(b, chainBlocks, currentGameType->chainRule_AmountPerChain, 0, grid->getWidth(), 0, toRow, ignoreTypes, mustContainAtLeastOneTypes);
					}
					if (currentGameType->chainRule_CheckDiagonal)
					{
						grid->addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfDiagonalAtLeastAmount(b, chainBlocks, currentGameType->chainRule_AmountPerChain, 0, grid->getWidth(), 0, toRow, ignoreTypes, mustContainAtLeastOneTypes);
					}
				}
			}
		}

		if (currentGameType->chainRule_CheckRecursiveConnections)
		{
			grid->checkRecursiveConnectedRowOrColumn(chainBlocks, currentGameType->chainRule_AmountPerChain, 0, grid->getWidth(), 0, toRow, ignoreTypes, mustContainAtLeastOneTypes);
		}

		addToChainBlocks(chainBlocks);
	}
	

	if (currentGameType->chainRule_CheckTouchingBreakerBlocksChain)
	{
		ArrayList<Block*> chainBlocks = grid->checkBreakerBlocks(toRow, ignoreTypes, mustContainAtLeastOneTypes);//TODO: going to need to refactor this into above, or send in the chainBlocks array to modify, so that you can have coexisting rules for checklines and checkAmountPerChain along with breaker blocks
		addToChainBlocks(chainBlocks);
	}
}


//=========================================================================================================================
void GameLogic::handleNewChain()
{//=========================================================================================================================
	//if flashing blocks, show getCaption
	if (detectedChain())
	{
		int chainMinimum = currentGameType->chainRule_AmountPerChain;
		if (currentGameType->chainRule_CheckEntireLine)chainMinimum = currentGameType->gridWidth;

		if (currentCombo == 0)
		{
			currentCombo = 1;
			currentChain = currentChainBlocks.size();

			makeAnnouncementCaption(string("Chain: ") + to_string(currentChain));


			int bonusAmount = (currentChain - chainMinimum);
			if (currentGameType->chainRule_CheckEntireLine)
			{
				bonusAmount = currentChain / currentGameType->gridWidth;
				if (bonusAmount == 1)
				{
					bonusAmount = 0;
				}
			}

			if (bonusAmount > 0)
			{
				makeAnnouncementCaption(string("Chain Bonus: ") + to_string(bonusAmount), BobColor::green);
				queueVSGarbage(bonusAmount);
			}

			getBobsGame()->changeBG();

			getBobsGame()->shakeSmall();
			grid->shakeSmall();
		}
		else
		{
			currentCombo++;
			currentChain = currentChainBlocks.size();
			comboChainTotal += currentChain;
			totalCombosMade++;

			if (comboChainTotal > biggestComboChain)biggestComboChain = comboChainTotal;

			makeAnnouncementCaption(string("Chain: ") + to_string(currentChain));

			makeAnnouncementCaption(string("") + to_string(currentCombo) + string("X Combo! Total: ") + to_string(comboChainTotal), BobColor::magenta);

			int bonusAmount = (currentChain - chainMinimum);
			if (bonusAmount == 0)
			{
				bonusAmount = 1;
			}

			makeAnnouncementCaption(string("Combo Bonus: ") + to_string(bonusAmount) + string(" X ") + to_string(currentCombo), BobColor::green);

			queueVSGarbage(currentCombo);

			getBobsGame()->shakeHard();
			grid->shakeHard();
		}


		//add any gray blobs touching the chain to the chain
		ArrayList<Block*> addToChain;
		for (int i = 0; i < currentChainBlocks.size(); i++)
		{
			Block* a = currentChainBlocks.get(i);

			ArrayList<Block*> temp = grid->getConnectedBlocksUpDownLeftRight(a);
			if (temp.size() > 0)
			{
				for (int k = 0; k < temp.size(); k++)
				{
					Block* b = temp.get(k);

					if (b->blockType->addToChainIfConnectedUpDownLeftRightToExplodingChainBlocks)
					{
						if (addToChain.contains(b) == false)
						{
							addToChain.add(b);
						}
					}
				}
			}
		}


		for (int i = 0; i < addToChain.size(); i++)
		{
			Block* a = addToChain.get(i);
			if (currentChainBlocks.contains(a) == false)
			{
				currentChainBlocks.add(a);
			}
		}


		for (int i = 0; i < currentChainBlocks.size(); i++)
		{
			Block* a = currentChainBlocks.get(i);
			a->flashingToBeRemoved = true;
		}

		if (currentGameType->gameMode == GameMode::STACK) //TODO: check stop behavior for dama and gemfight
		{
			//stop
			if (currentChainBlocks.size() > 3)
			{
				stopStackRiseTicksCounter += 1000 * currentChainBlocks.size();
			}
		}

		getAudioManager()->playSound(currentGameType->blocksFlashingSound, getVolume(), 1.0f);
		timesToFlashBlocksQueue = timesToFlashBlocks;
	}
}


//=========================================================================================================================
void GameLogic::doStackRiseGame()
{//=========================================================================================================================

	//stack rise game lets you continue manipulating pieces while there is a chain completing, falling block games don't.
	//so notice here it does not return from flashing detected chain blocks, and that it also detects one chain at a time.


	pieceSetAtBottom = true; //we dont use this and it should be true for the check below.

	manualStackRiseTicksCounter += ticks();

	//if not STOP, scroll playingfield up.
	bool stop = false;
	if (stopStackRiseTicksCounter > 0)
	{
		stopStackRiseTicksCounter -= ticks();
		if (stopStackRiseTicksCounter < 0)
		{
			stopStackRiseTicksCounter = 0;
		}
		stopCounterCaptionText = string("Wait: ") + to_string(stopStackRiseTicksCounter);
		stop = true;
	}

	if (timesToFlashBlocksQueue > 0)
	{
		flashChainBlocks();
		stopCounterCaptionText = "Wait: Flash";

		stop = true;
	}
	else
	{
		if (detectedChain())
		{
			removeFlashedChainBlocks();

			stopCounterCaptionText = string("Wait: Pop ") + to_string(currentChainBlocks.size());
			stop = true;
		}
	}


	if (timesToFlashScreenQueue > 0)
	{
		flashScreen();
		stopCounterCaptionText = "Wait: Flash";
		stop = true;
	}

	if (grid->continueSwappingBlocks())
	{
		stopCounterCaptionText = "Wait: Swap";
		stop = true;
	}

	if (stop == false)
	{
		stopCounterCaptionText = "Go!";
		stackRiseTicksCounter += ticks();


		//stackrise 300 was default, was too slow
		//200-300 is a good speed

		//dropspeed is 128-1000

		//dropspeed/10 = 12-100

		//stackrise = minStackRise



		int stackRiseDiff = getCurrentDifficulty()->maxStackRise - getCurrentDifficulty()->minStackRise;


		long long dropSpeedDiff = getCurrentDifficulty()->initialLineDropSpeedTicks - getCurrentDifficulty()->minimumLineDropSpeedTicks;

		long long currentDropSpeedDiff = (currentLineDropSpeedTicks - getCurrentDifficulty()->minimumLineDropSpeedTicks);

		int currentStackRise = getCurrentDifficulty()->minStackRise + (int)(((float)(currentDropSpeedDiff) / (float)(dropSpeedDiff)) * (float)(stackRiseDiff));

		if (stackRiseTicksCounter > currentStackRise/3)//TODO: make better
		{
			stackRiseTicksCounter = 0;


			bool scrolled = grid->scrollUpStack(currentPiece, 1);
			if (scrolled == false)
			{
				died = true;
			}

			if (died)
			{
				stopCounterCaptionText = "Wait: Dead";
				return;
			}
		}
	}

	updateKeyInput();
}


//=========================================================================================================================
void GameLogic::doFallingBlockGame()
{//=========================================================================================================================

	if (timesToFlashBlocksQueue > 0)
	{
		flashChainBlocks();
		return;
	}


	if (detectedChain())
	{
		removeFlashedChainBlocks();
		return;
	}

	if (timesToFlashScreenQueue > 0)
	{
		flashScreen();
	}


	//apply gravity to current piece
	if (pieceSetAtBottom == false)
	{
		if (lineDropTicksCounter == 0 && spawnDelayTicksCounter == 0 && lineClearDelayTicksCounter == 0)
		{
			bool moved = movePiece(MovementType::DOWN);
			if (moved)
			{
				lineDropTicksCounter = currentLineDropSpeedTicks;
			}

			if (died)
			{
				return;
			}

			//if(currentPiece!=null&&currentPiece.y<0&&moved==false){dead=true;return;}
			//if currentPosition<0 and movePiece==false dead
		}

		updateKeyInput();
	}
}


//=========================================================================================================================
void GameLogic::manuallyApplyGravityWithoutChainChecking()
{//=========================================================================================================================
	while (moveDownBlocksOverBlankSpaces())
	{
		moveDownLineTicksCounter = currentGameType->gravityRule_ticksToMoveDownBlocksOverBlankSpaces;
	}
}


//=========================================================================================================================
bool GameLogic::moveDownBlocksOverBlankSpaces()
{//=========================================================================================================================


	ArrayList<BlockType*> ignoreMovingBlockTypes = currentGameType->getBlockTypesToIgnoreWhenMovingDown(getCurrentDifficulty());
	bool movedDownBlocks = true;

	if (moveDownLineTicksCounter >= currentGameType->gravityRule_ticksToMoveDownBlocksOverBlankSpaces || currentGameType->moveDownAllLinesOverBlankSpacesAtOnce)
	{
		moveDownLineTicksCounter = 0;

		do
		{
			if (currentGameType->chainRule_CheckEntireLine) //we only care about totally blank lines
			{
				movedDownBlocks = grid->moveDownLinesAboveBlankLinesOneLine();
			}
			else
			{
				if (currentGameType->gravityRule_onlyMoveDownDisconnectedBlocks)
				{
					movedDownBlocks = grid->moveDownDisconnectedBlocksAboveBlankSpacesOneLine(ignoreMovingBlockTypes);
				}
				else
				{
					movedDownBlocks = grid->moveDownAnyBlocksAboveBlankSpacesOneLine(ignoreMovingBlockTypes);
				}
			}
		}
		while (currentGameType->moveDownAllLinesOverBlankSpacesAtOnce == true && movedDownBlocks == true);
	}

	return movedDownBlocks;
}

//=========================================================================================================================
void GameLogic::pieceMoved()
{//=========================================================================================================================
	lockDelayTicksCounter = currentGameType->maxLockDelayTicks;

	//test one more down
	currentPiece->yGrid++;
	if (grid->doesPieceFit(currentPiece) == false)
	{
		getAudioManager()->playSound(currentGameType->touchBottomSound, getVolume(), getSoundEffectSpeed());
	}
	currentPiece->yGrid--;
}

//=========================================================================================================================
bool GameLogic::movePiece(MovementType move)
{//=========================================================================================================================

	if (currentPiece == nullptr)
	{
		log.error("Tried to move null piece");
		return false;
	}

	if (move == MovementType::ROTATE_COUNTERCLOCKWISE || move == MovementType::ROTATE_CLOCKWISE)
	{
		if (currentPiece->pieceType->pieceShooterPiece)
		{
			//so we can't repeatedly use it
			switchedHoldPieceAlready = true;


			//make new piece, not new block
			//this is so the colors get initialized and the block can be updated by getting arrayOfPiecesInGrid
			Piece* p = new Piece(this, grid, PieceType::emptyPieceType, new BlockType("shotPiece","Square","", nullptr, BobColor::gray, 0, 0));
			Block* b = p->blocks.get(0);

			//set last screenXY to current piece so it appears to shoot, even though it's really just being placed directly into the grid.
			b->lastScreenX = grid->getXInFBO() + currentPiece->xGrid * cellW();
			b->lastScreenY = grid->getYInFBO() + currentPiece->yGrid * cellH();
			b->ticksSinceLastMovement = 0;

			int xGrid = currentPiece->xGrid;
			int yGrid = currentPiece->yGrid;

			while (yGrid < gridH() - 1 && grid->get(xGrid, yGrid + 1) == nullptr)
			{
				yGrid++;
			}

			p->xGrid = xGrid;
			p->yGrid = yGrid;

			if (yGrid != currentPiece->yGrid)
			{
				grid->shakeSmall();

				grid->setPiece(p);
				getAudioManager()->playSound(currentGameType->hardDropClankSound, getVolume(), getSoundEffectSpeed());
				
			}
			else
			{
				//could not shoot piece because the next grid space down is full
				//maybe play thud sound here?
			}

			return false;
		}


		if (currentPiece->pieceType->pieceRemovalShooterPiece)
		{
			//so we can't repeatedly use it
			switchedHoldPieceAlready = true;

			int xGrid = currentPiece->xGrid;
			int yGrid = currentPiece->yGrid;

			while (yGrid < gridH() - 1 && grid->get(xGrid, yGrid) == nullptr)
			{
				yGrid++;
			}

			Block* b = grid->get(xGrid, yGrid);

			if (b != nullptr)
			{
				grid->remove(b, true, true);

				//set last screenXY to current piece so it appears to shoot, even though it's really just being placed directly into the grid.
				b->lastScreenX = grid->getXInFBO() + xGrid * cellW();
				b->lastScreenY = grid->getYInFBO() + yGrid * cellH();
				b->xGrid = xGrid;
				b->yGrid = currentPiece->yGrid;

				getAudioManager()->playSound(currentGameType->hardDropSwishSound, getVolume(), getSoundEffectSpeed());
			}

			return false;
		}
	}


	if (move == MovementType::ROTATE_COUNTERCLOCKWISE)
	{
		currentPiece->rotateCCW();
	}
	if (move == MovementType::ROTATE_CLOCKWISE)
	{
		currentPiece->rotateCW();
	}
	if (move == MovementType::UP)
	{
		currentPiece->yGrid--;
	}
	if (move == MovementType::DOWN || move == MovementType::HARD_DROP)
	{
		currentPiece->yGrid++;
	}
	if (move == MovementType::RIGHT)
	{
		currentPiece->xGrid++;
	}
	if (move == MovementType::LEFT)
	{
		currentPiece->xGrid--;
	}


	if (grid->doesPieceFit(currentPiece))
	{
		pieceMoved();
		return true;
	}
	else
	{
		if (move == MovementType::ROTATE_COUNTERCLOCKWISE || move == MovementType::ROTATE_CLOCKWISE)
		{
			if (currentGameType->pieceClimbingAllowed)
			{
				//try climbing if direction is pressed
				if (getFrameState()->LEFT_HELD)
				{
					int tempY = currentPiece->yGrid;
					currentPiece->xGrid--;

					for (int i = 0; i <= currentPiece->getHeight(); i++)
					{
						currentPiece->yGrid--;
						if (grid->doesPieceFit(currentPiece) == true)
						{
							pieceMoved();
							getAudioManager()->playSound(currentGameType->diagonalWallKickSound, getVolume(), 1.0f);
							canPressLeft = false;
							ticksHoldingLeft = 0;
							return true;
						}
					}

					currentPiece->yGrid = tempY;
					currentPiece->xGrid++;
				}

				//try climbing if direction is pressed
				if (getFrameState()->RIGHT_HELD)
				{
					int tempY = currentPiece->yGrid;
					currentPiece->xGrid++;

					for (int i = 0; i <= currentPiece->getHeight(); i++)
					{
						currentPiece->yGrid--;
						if (grid->doesPieceFit(currentPiece) == true)
						{
							pieceMoved();
							getAudioManager()->playSound(currentGameType->diagonalWallKickSound, getVolume(), 1.0f);
							canPressRight = false;
							ticksHoldingRight = 0;
							return true;
						}
					}

					currentPiece->yGrid = tempY;
					currentPiece->xGrid--;
				}
			}


			// try pushing off the wall

			bool hittingLeft = grid->isHittingLeft(currentPiece);
			bool hittingRight = grid->isHittingRight(currentPiece);

			if (hittingLeft == true)
			{
				//check right 1
				currentPiece->xGrid++;
				if (grid->doesPieceFit(currentPiece) == true)
				{
					pieceMoved();
					getAudioManager()->playSound(currentGameType->wallKickSound, getVolume(), 1.0f);
					return true;
				}
				else
				{
					currentPiece->xGrid--;

					if (currentGameType->twoSpaceWallKickAllowed)
					{
						//check right 2
						currentPiece->xGrid += 2;
						if (grid->doesPieceFit(currentPiece) == true)
						{
							pieceMoved();
							getAudioManager()->playSound(currentGameType->doubleWallKickSound, getVolume(), 1.0f);
							return true;
						}
						else
						{
							currentPiece->xGrid -= 2;
						}
					}

					if (currentGameType->diagonalWallKickAllowed)
					{
						//check down
						currentPiece->yGrid++;
						if (grid->doesPieceFit(currentPiece) == true)
						{
							pieceMoved();
							getAudioManager()->playSound(currentGameType->diagonalWallKickSound, getVolume(), 1.0f);
							return true;
						}
						else
						{
							currentPiece->yGrid--;

							//check downright
							currentPiece->xGrid++;
							currentPiece->yGrid++;
							if (grid->doesPieceFit(currentPiece) == true)
							{
								pieceMoved();
								getAudioManager()->playSound(currentGameType->diagonalWallKickSound, getVolume(), 1.0f);
								return true;
							}
							else
							{
								currentPiece->xGrid--;
								currentPiece->yGrid--;
							}
						}
					}
				}
			}

			if (hittingRight == true)
			{
				//check left 1
				currentPiece->xGrid--;
				if (grid->doesPieceFit(currentPiece) == true)
				{
					pieceMoved();
					getAudioManager()->playSound(currentGameType->wallKickSound, getVolume(), 1.0f);
					return true;
				}
				else
				{
					currentPiece->xGrid++;

					if (currentGameType->twoSpaceWallKickAllowed)
					{
						//check left 2
						currentPiece->xGrid -= 2;
						if (grid->doesPieceFit(currentPiece) == true)
						{
							pieceMoved();
							getAudioManager()->playSound(currentGameType->doubleWallKickSound, getVolume(), 1.0f);
							return true;
						}
						else
						{
							currentPiece->xGrid += 2;
						}
					}

					if (currentGameType->diagonalWallKickAllowed)
					{
						//check down
						currentPiece->yGrid++;
						if (grid->doesPieceFit(currentPiece) == true)
						{
							pieceMoved();
							getAudioManager()->playSound(currentGameType->diagonalWallKickSound, getVolume(), 1.0f);
							return true;
						}
						else
						{
							currentPiece->yGrid--;

							//check downleft
							currentPiece->xGrid--;
							currentPiece->yGrid++;
							if (grid->doesPieceFit(currentPiece) == true)
							{
								pieceMoved();
								getAudioManager()->playSound(currentGameType->diagonalWallKickSound, getVolume(), 1.0f);
								return true;
							}
							else
							{
								currentPiece->xGrid++;
								currentPiece->yGrid--;
							}
						}
					}
				}
			}

			if (currentGameType->floorKickAllowed)
			{
				//check up 1
				currentPiece->yGrid--;
				if (grid->doesPieceFit(currentPiece) == true)
				{
					pieceMoved();
					getAudioManager()->playSound(currentGameType->floorKickSound, getVolume(), 1.0f);
					return true;
				}
				else
				{
					currentPiece->yGrid++;

					if (currentGameType->twoSpaceWallKickAllowed)
					{
						//check up 2
						currentPiece->yGrid -= 2;
						if (grid->doesPieceFit(currentPiece) == true)
						{
							pieceMoved();
							getAudioManager()->playSound(currentGameType->floorKickSound, getVolume(), 1.0f);
							return true;
						}
						else
						{
							currentPiece->yGrid += 2;
						}
					}
				}
			}

			//DONE: handle 180 flip if rotating and piece does not fit
			if (currentGameType->flip180Allowed)
			{
				//rotate in direction again
				if (move == MovementType::ROTATE_COUNTERCLOCKWISE)
				{
					currentPiece->rotateCCW();
				}
				if (move == MovementType::ROTATE_CLOCKWISE)
				{
					currentPiece->rotateCW();
				}

				if (grid->doesPieceFit(currentPiece) == true)
				{
					pieceMoved();
					getAudioManager()->playSound(currentGameType->pieceFlip180Sound, getVolume(), 1.0f);
					return true;
				}
				else
				{
					//check up 1
					currentPiece->yGrid--;
					if (grid->doesPieceFit(currentPiece) == true)
					{
						pieceMoved();
						getAudioManager()->playSound(currentGameType->pieceFlip180Sound, getVolume(), 1.0f);
						return true;
					}
					else
					{
						currentPiece->yGrid++;
					}

					//rotate back
					if (move == MovementType::ROTATE_COUNTERCLOCKWISE)
					{
						currentPiece->rotateCW();
					}
					if (move == MovementType::ROTATE_CLOCKWISE)
					{
						currentPiece->rotateCCW();
					}
				}
			}
		}


		if (move == MovementType::ROTATE_COUNTERCLOCKWISE)
		{
			currentPiece->rotateCW();
		}
		if (move == MovementType::ROTATE_CLOCKWISE)
		{
			currentPiece->rotateCCW();
		}
		if (move == MovementType::UP)
		{
			currentPiece->yGrid++;
		}
		if (move == MovementType::DOWN || move == MovementType::HARD_DROP)
		{
			currentPiece->yGrid--;
		}
		if (move == MovementType::RIGHT)
		{
			currentPiece->xGrid--;
		}
		if (move == MovementType::LEFT)
		{
			currentPiece->xGrid++;
		}


		if (move == MovementType::DOWN || move == MovementType::HARD_DROP)
		{
			if (move == MovementType::HARD_DROP && currentGameType->hardDropPunchThroughToLowestValidGridPosition)
			{
				if (currentPiece != nullptr)
				{
					int lastValidYPosition = currentPiece->yGrid;

					for (int y = lastValidYPosition; y < grid->getHeight(); y++)
					{
						if (grid->doesPieceFit(currentPiece, currentPiece->xGrid, y))
						{
							lastValidYPosition = y;
						}
					}
					currentPiece->yGrid = lastValidYPosition;
				}
			}


			if (lockDelayTicksCounter == 0)
			{
				setPiece();
			}
		}


		return false;
	}
}


//=========================================================================================================================
void GameLogic::setCurrentPieceAtTop()
{//=========================================================================================================================
	currentPiece->xGrid = (grid->getWidth() / 2) - (currentPiece->getWidth() / 2 + currentPiece->getLowestOffsetX());
	if (currentPiece->getWidth() % 2 == 1)
	{
		currentPiece->xGrid -= 1;
	}

	currentPiece->yGrid = -2 + GameLogic::aboveGridBuffer;
	//TODO: make starting y position variable.  why does the long piece start at -1?  must be +1 in the rotation


	if (grid->doesPieceFit(currentPiece) == false)
	{
		died = true;
	}


	spawnDelayTicksCounter = currentGameType->spawnDelayTicksAmountPerPiece;

	lineDropTicksCounter = 0;
}

//=========================================================================================================================
void GameLogic::setPiece()
{//=========================================================================================================================


	if (currentPiece->pieceType->bombPiece)
	{
		//get pieces down, left, right of bomb piece

		//grid.delete all those pieces

		ArrayList<Block*> explodeBlocks;


		int startX = (currentPiece->xGrid - abs(currentPiece->getLowestOffsetX())) - 1;
		int endX = currentPiece->xGrid + currentPiece->getWidth() + 1;

		int startY = (currentPiece->yGrid - abs(currentPiece->getLowestOffsetY())) - 1;
		int endY = currentPiece->yGrid + currentPiece->getHeight() + 1;

		for (int x = startX; x < endX && x < gridW(); x++)
		{
			for (int y = startY; y < endY && y < gridH(); y++)
			{
				Block* b = grid->get(x, y);
				if (b != nullptr && explodeBlocks.contains(b) == false)
				{
					explodeBlocks.add(b);
				}
			}
		}


		for (int i = 0; i < explodeBlocks.size(); i++)
		{
			grid->remove(explodeBlocks.get(i), true, true);
		}

		getAudioManager()->playSound(currentGameType->hardDropClankSound, 1.5f, 0.25f);

		grid->shakeHard();

	}


	if (currentPiece->pieceType->weightPiece)
	{
		//set weight piece blocks lastx,y
		for (int i = 0; i < (int)currentPiece->getNumBlocksInCurrentRotation() && i < currentPiece->blocks.size(); i++)
		{
			Block* b = currentPiece->blocks.get(i);
			b->lastScreenX = grid->getXInFBO() + (currentPiece->xGrid + b->xInPiece) * cellW();
			b->lastScreenY = grid->getYInFBO() + (currentPiece->yGrid + b->yInPiece) * cellH();
			b->ticksSinceLastMovement = 0;
		}


		//grid.delete all blocks underneath weight
		for (int y = currentPiece->yGrid; y < gridH(); y++)
		{
			for (int x = currentPiece->getLowestOffsetX(); x <= currentPiece->getHighestOffsetX(); x++)
			{
				Block* b = grid->get(currentPiece->xGrid + x, y);
				if (b != nullptr)
				{
					grid->remove(b, true, true);
				}
			}
		}


		//set weight piece at bottom
		while (grid->doesPieceFit(currentPiece))
		{
			currentPiece->yGrid++;
		}
		currentPiece->yGrid--;

		getAudioManager()->playSound(currentGameType->hardDropClankSound, getVolume(), 0.5f);

		grid->shakeHard();
	}


	grid->setPiece(currentPiece);


	//make it so all blocks in piece must be less than 0
	//if(currentPiece.yGrid<0+GameLogic.aboveGridBuffer)
	if (currentPiece->yGrid + currentPiece->getHighestOffsetY() < 0 + GameLogic::aboveGridBuffer)
	{
		died = true;
	}


	//TODO: size grid buffer based on largest piece... 
	//OR start grid at 0 on the bottom, and have the grid expand infinitely 
	//as pieces rise above the death line, must also pull back camera to fit grid


	pieceSetAtBottom = true;

	piecesPlacedTotal++;

	currentPiece = nullptr;

	getAudioManager()->playSound(currentGameType->pieceSetSound, getVolume(), getSoundEffectSpeed());
}


//=========================================================================================================================
void GameLogic::newRandomPiece()
{//=========================================================================================================================

	pieceSetAtBottom = false;



	//fill last nextPiece from bag

	while (nextPieces.size() < currentGameType->numberOfNextPiecesToShow)
	{
		if (nextPieceSpecialBuffer.size() > 0)
		{
			nextPieces.add(nextPieceSpecialBuffer.get(0));
			nextPieceSpecialBuffer.removeAt(0);
		}
		else
		{
			nextPieces.add(grid->getRandomPiece());
		}
		createdPiecesCounterForFrequencyPieces++;
	}

	currentPiece = nextPieces.get(0);

	nextPieces.removeAt(0);



	setCurrentPieceAtTop();

	switchedHoldPieceAlready = false;

	piecesMadeThisGame++;
	piecesMadeThisLevel++;
	piecesMadeTotal++;
	blocksMadeTotal += currentPiece->blocks.size();

	if (garbageWaitPieces > 0)
	{
		garbageWaitPieces--;
	}

	getAudioManager()->playSound(getRandomMakePieceSound(), getVolume(), getSoundEffectSpeed());


	ArrayList<Piece*> piecesOnGrid = grid->getArrayOfPiecesOnGrid();
	for (int i = 0; i < piecesOnGrid.size(); i++)
	{
		Piece* p = piecesOnGrid.get(i);
		p->piecesSetSinceThisPieceSet++;

		for (int j = 0; j < (int)p->blocks.size(); j++)
		{
			Block* b = p->blocks.get(j);
			if (b->blockType->counterType)
			{
				if (b->counterCount > -1)
				{
					b->counterCount--;
				}
			}
		}
	}


	//clear lineClearDelay if special piece
	if (currentPiece->pieceType->bombPiece || currentPiece->pieceType->weightPiece || currentPiece->pieceType->pieceShooterPiece || currentPiece->pieceType->pieceRemovalShooterPiece)
	{
		lineClearDelayTicksCounter = 0;
	}


//	//immediately skip bomb, weight, pieceShooter if playing field is empty
//	if (currentPiece->pieceType->bombPiece || currentPiece->pieceType->weightPiece || currentPiece->pieceType->pieceRemovalShooterPiece)
//	{
//		bool bottomEmpty = true;
//		for (int x = 0; x < grid->getWidth(); x++)
//		{
//			if (grid->get(x, grid->getHeight() - 1) != nullptr)
//			{
//				bottomEmpty = false;
//			}
//		}
//
//		if (bottomEmpty)
//		{
//			newRandomPiece();
//		}
//	}


}

//=========================================================================================================================
void GameLogic::gotVSGarbageFromOtherPlayer(int amount)
{//=========================================================================================================================

	frameState.receivedGarbageAmount += amount;


	garbageWaitPieces += 3;
	if (garbageWaitPieces > 4)
	{
		garbageWaitPieces = 4;
	}


	queuedVSGarbageAmountFromOtherPlayer += amount;

	makeAnnouncementCaption(string("Got VS Garbage: ") + to_string(amount));

	if (garbageBlock == nullptr)
	{
		ArrayList<BlockType*> garbageTypes = currentGameType->getGarbageBlockTypes(getCurrentDifficulty());
		Piece* p = new Piece(this, grid, PieceType::emptyPieceType, grid->getRandomBlockType(garbageTypes));//TODO: use garbagePieceTypes with one block
		garbageBlock = p->blocks.get(0);
	}
}

//=========================================================================================================================
void GameLogic::processQueuedGarbageSentFromOtherPlayer()
{//=========================================================================================================================


	if (queuedVSGarbageAmountFromOtherPlayer > 0)
	{
		if (garbageWaitPieces == 0)
		{
			//makeAnnouncementCaption(string("Processed VS Garbage: ") + to_string(queuedGarbageAmountFromOtherPlayer));


			int garbageMultiplier = 2;
			//TODO: if garbageRuleMax, drop one line per garbageAmount
			//garbageRuleMultiplier, divide gridWidth times amount
			//could also drop indiviual garbage instead of lines


			while (queuedVSGarbageAmountFromOtherPlayer/(grid->getWidth()/garbageMultiplier) > 0)
			{
				queuedVSGarbageAmountFromOtherPlayer-= grid->getWidth();
				if (queuedVSGarbageAmountFromOtherPlayer < 0)queuedVSGarbageAmountFromOtherPlayer = 0;

				if (isNetworkPlayer)log.warn("Garbage");
				else log.debug("Garbage");

				if (currentGameType->vsGarbageRule == VSGarbageRule::FALL_FROM_CEILING_IN_EVEN_ROWS)
				{
					makeGarbageRowFromCeiling();
					moveDownBlocksOverBlankSpaces();
				}
				if (currentGameType->vsGarbageRule == VSGarbageRule::RISE_FROM_FLOOR_IN_EVEN_ROWS)
				{
					makeGarbageRowFromFloor();
				}
			}
		}
	}
}


//=========================================================================================================================
void GameLogic::queueVSGarbage(int amount)
{//=========================================================================================================================

	//if queued garbage, send it to the other side and negate it

	//garbage types per game?

	if (getBobsGame()->isMultiplayer())
	{

		if (queuedVSGarbageAmountFromOtherPlayer > 0)
		{
			if (amount >= queuedVSGarbageAmountFromOtherPlayer)
			{
				makeAnnouncementCaption(string("Negated VS Garbage: ") + to_string(queuedVSGarbageAmountFromOtherPlayer));

				amount -= queuedVSGarbageAmountFromOtherPlayer;
				queuedVSGarbageAmountFromOtherPlayer = 0;
			}
			else
			{
				if (amount < queuedVSGarbageAmountFromOtherPlayer)
				{
					makeAnnouncementCaption(string("Negated VS Garbage: ") + to_string(amount));
					queuedVSGarbageAmountFromOtherPlayer -= amount;
					amount = 0;
				}
			}
		}

		if (amount > 0)
		{
			queuedVSGarbageAmountToSend += amount;
			makeAnnouncementCaption(string("Sent VS Garbage: ") + to_string(amount) + string(" Total: ") + to_string(queuedVSGarbageAmountToSend));
		}
	}
}


//=========================================================================================================================
void GameLogic::processGarbageRules()
{//=========================================================================================================================

	bool makeGarbage = false;

	if (currentGameType->playingFieldGarbageSpawnRule == GarbageSpawnRule::TICKS)
	{
		playingFieldGarbageValueCounter += ticks();
		if (playingFieldGarbageValueCounter > getCurrentDifficulty()->playingFieldGarbageSpawnRuleAmount)
		{
			playingFieldGarbageValueCounter = 0;
			makeGarbage = true;
		}
	}
	else
	{
		if (currentGameType->playingFieldGarbageSpawnRule == GarbageSpawnRule::PIECES_MADE)
		{
			if (piecesMadeThisGame >= playingFieldGarbageValueCounter + getCurrentDifficulty()->playingFieldGarbageSpawnRuleAmount)
			{
				playingFieldGarbageValueCounter = piecesMadeThisGame;
				makeGarbage = true;
			}
		}
		else
		{
			if (currentGameType->playingFieldGarbageSpawnRule == GarbageSpawnRule::BLOCKS_CLEARED)
			{
				if (blocksClearedThisGame >= playingFieldGarbageValueCounter + getCurrentDifficulty()->playingFieldGarbageSpawnRuleAmount)
				{
					playingFieldGarbageValueCounter = blocksClearedThisGame;
					makeGarbage = true;
				}
			}
			else
			{
				if (currentGameType->playingFieldGarbageSpawnRule == GarbageSpawnRule::LINES_CLEARED)
				{
					if (linesClearedThisGame >= playingFieldGarbageValueCounter + getCurrentDifficulty()->playingFieldGarbageSpawnRuleAmount)
					{
						playingFieldGarbageValueCounter = linesClearedThisGame;
						makeGarbage = true;
					}
				}
			}
		}
	}

	if (makeGarbage)
	{
		makeGarbageRowFromFloor();
	}
}

//=========================================================================================================================
void GameLogic::makeGarbageRowFromFloor()
{//=========================================================================================================================
	grid->makeGarbageRowFromFloor();
	manuallyApplyGravityWithoutChainChecking();
	//forceGravityThisFrame = true;

	grid->shakeMedium();
}

//=========================================================================================================================
void GameLogic::makeGarbageRowFromCeiling()
{//=========================================================================================================================
	grid->makeGarbageRowFromCeiling();
	//forceGravityThisFrame = true;
	manuallyApplyGravityWithoutChainChecking();

	grid->shakeHard();
}

//=========================================================================================================================
void GameLogic::renderQueuedGarbage()
{//=========================================================================================================================

	// render getCaption with garbageWaitPieces

	if (queuedVSGarbageAmountFromOtherPlayer > 0)
	{
		if (garbageWaitCaption == nullptr)
		{
			garbageWaitCaption = getCaptionManager()->newManagedCaption(0, 0, -1, " ", announcementCaptionFont, BobColor::white, BobColor::clear, RenderOrder::ABOVE, 0.5f);
		}
		garbageWaitCaption->screenX = (float)(grid->getXOnScreenNoShake());
		garbageWaitCaption->screenY = (float)(grid->getYOnScreenNoShake() - (cellH()));
		garbageWaitCaption->flashing = true;
		garbageWaitCaption->flashingTicksPerFlash = 500;
		garbageWaitCaption->setText(string("Wait: ") + to_string(garbageWaitPieces));


		for (int i = 0; i < queuedVSGarbageAmountFromOtherPlayer; i++)
		{
			if (garbageBlock != nullptr)
			{
				garbageBlock->render(grid->getXInFBO() + i * blockWidth, grid->getYInFBO() - blockHeight, 0.5f, 1.0f, false, false);
			}
		}
	}
	else
	{
		if (garbageWaitCaption != nullptr)
		{
			garbageWaitCaption->setToFadeOutAndBeDeleted();
			garbageWaitCaption = nullptr;
		}
	}
}


//=========================================================================================================================
void GameLogic::renderHoldPiece()
{//=========================================================================================================================

	if(currentGameType->gameMode==GameMode::STACK)
	{
		if (holdCaption != nullptr)
		{
			holdCaption->visible = false;
		}
		return;
	}

	float holdBoxX = grid->getXOnScreenNoShake() - 3 * cellW();
	float holdBoxY = grid->getYOnScreenNoShake();
	float holdBoxW = (float)(2 * cellW());
	float holdBoxH = (float)(2 * cellH());

	if (holdCaption != nullptr)
	{
		holdCaption->visible = true;
		holdCaption->screenX = holdBoxX;
		holdCaption->screenY = holdBoxY - captionYSize;
	}


	//draw hold box
	GLUtils::drawFilledRectXYWH(holdBoxX, holdBoxY, holdBoxW, holdBoxH, 1, 1, 1, 1.0f);
	GLUtils::drawFilledRectXYWH(holdBoxX + 1, holdBoxY + 1, holdBoxW - 2, holdBoxH - 2, 0, 0, 0, 1.0f);

	if (holdPiece != nullptr)
	{
		float scale = 0.5f;

		float w = (float)cellW();
		float h = (float)cellH();

		float holdX = (float)(holdBoxX + 1 * w * scale);
		float holdY = (float)(holdBoxY + 1 * h * scale);

		//center in box depending on width
		if (holdPiece->getWidth() == 3)
		{
			holdX -= 0.5f * w * scale;
		}
		if (holdPiece->getWidth() == 4)
		{
			holdX -= 1 * w * scale;
		}


		for (int i = 0; i < (int)holdPiece->getNumBlocksInCurrentRotation() && i < holdPiece->blocks.size(); i++)
		{
			float blockX = (holdPiece->blocks.get(i)->xInPiece - holdPiece->getLowestOffsetX()) * w * scale;
			float blockY = (holdPiece->blocks.get(i)->yInPiece - holdPiece->getLowestOffsetY()) * h * scale;

			float x = holdX + blockX;
			float y = holdY + blockY;
			holdPiece->blocks.get(i)->render(x, y, 1.0f, 0.5f, true, false);
		}
	}
}


//=========================================================================================================================
bool GameLogic::nextPieceEnabled()
{//=========================================================================================================================
	if (extraStage3 == false && extraStage4 == false && currentGameType->nextPieceEnabled == true)
	{
		return true;
	}
	return false;
}


//=========================================================================================================================
void GameLogic::renderNextPiece()
{//=========================================================================================================================

	if (currentGameType->gameMode == GameMode::STACK)
	{
		if (nextCaption != nullptr)
		{
			nextCaption->visible = false;
		}
		return;
	}

	if (nextCaption != nullptr)
	{
		nextCaption->visible = true;
		nextCaption->screenX = grid->getXOnScreenNoShake() + ((grid->getWidth() / 2) * cellW());
		nextCaption->screenY = grid->getYOnScreenNoShake() - 4 * cellH();
	}

	// render nextPiece
	if (nextPieceEnabled())
	{
		if (nextPieces.size() > 0)
		{
			if (nextPieces.isEmpty())
			{
				return;
			}

			float lastPieceX = 0;
			float startPieceX = 0;

			//wait until currentPiece has moved out of the next box before sliding the other pieces over
			if (currentPiece != nullptr && currentPiece->yGrid <= 0 + GameLogic::aboveGridBuffer)
			{
				for (int i = 0; i < (int)currentPiece->getNumBlocksInCurrentRotation() && i < currentPiece->blocks.size(); i++)
				{
					float blockX = (float)(currentPiece->blocks.get(i)->xInPiece*cellW());

					float x = grid->getXInFBONoShake() + ((grid->getWidth() / 2) * cellW()) + blockX;
					if (currentPiece->getWidth() % 2 == 1)
					{
						x -= cellW();
					}

					if (x > lastPieceX)
					{
						lastPieceX = x;
					}
				}
			}


			for (int i = 0; i < nextPieces.size(); i++)
			{
				Piece* nextPiece = nextPieces.get(i);

				startPieceX = lastPieceX + cellW();
				if (startPieceX > playingFieldX1)break;

				for (int b = 0; b < (int)nextPiece->getNumBlocksInCurrentRotation() && b < nextPiece->blocks.size(); b++)
				{
					if (i == 0 && (currentPiece == nullptr || currentPiece->yGrid > 0 + GameLogic::aboveGridBuffer))
					{
						float blockX = (float)(nextPiece->blocks.get(b)->xInPiece*cellW());
						float x = (float)(grid->getXOnScreenNoShake() + ((grid->getWidth() / 2) * cellW()) + blockX);
						if (nextPiece->getWidth() % 2 == 1)
						{
							x -= cellW();
						}


						float blockY = (float)(nextPiece->blocks.get(b)->yInPiece*cellH());

						float y = (float)(grid->getYOnScreenNoShake() - (cellH() * (nextPiece->getHeight())) + blockY);


						nextPiece->blocks.get(b)->render(x, y, 1.0f, 1.0f, true, false);

						if (x > lastPieceX)
						{
							lastPieceX = x;
						}
					}
					else
					{
						float s = 0.75f;

						float blockX = nextPiece->blocks.get(b)->xInPiece*cellW() * s;
						float x = startPieceX + (abs(nextPiece->getLowestOffsetX()) + 1) * cellW() * s + blockX;


						float blockY = nextPiece->blocks.get(b)->yInPiece*cellH() * s;
						float y = grid->getYOnScreenNoShake() - (cellH() * 3) + blockY;


						nextPiece->blocks.get(b)->render(x, y, 1.0f, s, true, false);

						if (x > lastPieceX)
						{
							lastPieceX = x;
						}
					}
				}
			}
		}
	}


}


//=========================================================================================================================
void GameLogic::renderCurrentPiece()
{//=========================================================================================================================
	if (currentPiece != nullptr)
	{
		if (currentGameType->gameMode == GameMode::STACK)
		{
		}
		else
		if (currentGameType->gameMode == GameMode::DROP)
		{
			// render ghost piece
			if (pieceSetAtBottom == false && gravityThisFrame == false)
			{
				grid->renderGhostPiece(currentPiece);
			}
		}


		// render currentPiece
		currentPiece->renderAsCurrentPiece();
	}
}


//=========================================================================================================================
void GameLogic::renderOverlays()
{//=========================================================================================================================


	// flash screen if flashing
	if (timesToFlashScreenQueue > 0)
	{
		if (flashScreenOnOffToggle == true)
		{
			//draw screen flash effect
			GLUtils::drawFilledRectXYWH(0, 0, (float)GLUtils::getViewportWidth(), (float)GLUtils::getViewportHeight(), 1.0f, 1.0f, 1.0f, 0.2f);
		}
	}
}


//=========================================================================================================================
void GameLogic::renderBackground()
{//=========================================================================================================================

	//GameType().gridBorderColor = Color.yellow;
	//GameType().gridBorderColor = Color.getHSBColor(captionColorCycleHueValue,1.0f,1.0f);


	// fill in checkered background
	grid->renderBackground();

	grid->renderBorder();
}


//=========================================================================================================================
void GameLogic::renderBlocks()
{//=========================================================================================================================


	renderQueuedGarbage();

	for (int i = 0; i < fadingOutBlocks.size(); i++)
	{
		fadingOutBlocks.get(i)->renderDisappearing();
	}

	//render blocks
	grid->render();


	renderHoldPiece();

	renderNextPiece();

	renderCurrentPiece();
}


//=========================================================================================================================
void GameLogic::renderForeground()
{//=========================================================================================================================

	grid->renderBlockOutlines();

	if (currentGameType->gameMode == GameMode::STACK)
	{
		grid->renderTransparentOverLastRow();
	}


	renderOverlays();

	
}


//=========================================================================================================================
void GameLogic::doExtraStageEffects()
{//=========================================================================================================================


	if (currentLevel >= getCurrentDifficulty()->extraStage1Level)
	{
		grid->wigglePlayingField();
	}

	//		if(extraStage1)
	//		{
	//			grid.scrollBackground();
	//		}
	//
	//
	//		if(extraStage2)
	//		{
	//			extraStageTicksPassed+=ticks();
	//			if(extraStageTicksPassed>1000)
	//			{
	//				extraStageTicksPassed=0;
	//				grid.setRandomPieceGrayscaleColors(currentPiece,nextPieces);
	//
	//			}
	//
	//			grid.scrollBackground();
	//		}
	//
	//		if(extraStage3)
	//		{
	//			extraStageTicksPassed+=ticks();
	//
	//			if(extraStageTicksPassed>300)
	//			{
	//				extraStageTicksPassed=0;
	//				grid.setRandomBlockColors();
	//
	//			}
	//
	//			grid.shakeForeground();
	//		}
	//
	//		if(extraStage4)
	//		{
	//			extraStageTicksPassed+=ticks();
	//
	//			if(extraStageTicksPassed>200)
	//			{
	//				extraStageTicksPassed=0;
	//				grid.setRandomMatrixBlockColors();
	//
	//
	//			}
	//
	//			grid.scrollBackground();
	//			grid.shakeForeground();
	//		}
}


//=========================================================================================================================
string GameLogic::getRandomMakePieceSound()
{//=========================================================================================================================


	int r = Math::randLessThan(7);//doesn't matter
	if (r == 0)
	{
		return "piece1";
	}
	if (r == 1)
	{
		return "piece2";
	}
	if (r == 2)
	{
		return "piece3";
	}
	if (r == 3)
	{
		return "piece4";
	}
	if (r == 4)
	{
		return "piece5";
	}
	if (r == 5)
	{
		return "piece6";
	}
	return "piece7";
}

//=========================================================================================================================
float GameLogic::getSoundEffectSpeed()
{//=========================================================================================================================
	if (currentGameType->useRandomSoundModulation)
	{
		default_random_engine generator;
		uniform_real_distribution<double> distribution(0.0, 1.0);
		double number = distribution(generator);

		//default_random_engine e1(rd());
		//random = static_cast<long long>(e1() * (numeric_limits<long long>::max)());

		return 0.5f + (float)(number * 1.5f); //don't use our seeded random
	}
	return 1.0f;
}

//=========================================================================================================================
float GameLogic::getVolume()
{//=========================================================================================================================
	if (mute)
	{
		return 0.0f;
	}
	else
	{
		return 1.0f;
	}
}


//=========================================================================================================================
void GameLogic::checkForFastMusic()
{//=========================================================================================================================


	bool anythingAboveThreeQuarters = grid->isAnythingAboveThreeQuarters();

	if (player->gridRule_showWarningForFieldThreeQuartersFilled && (anythingAboveThreeQuarters || extraStage1 || extraStage2 || extraStage3))
	{
		if (playingFastMusic == false)
		{
			playingFastMusic = true;

			if (currentGameType->fastMusic == "" || currentGameType->fastMusic.length() == 0)
			{
				getAudioManager()->stopMusic(playingMusic);
				playingMusic = currentGameType->normalMusic;
				getAudioManager()->playMusic(playingMusic, getVolume(), 1.5f, true);
			}
			else
			{
				getAudioManager()->stopMusic(playingMusic);
				playingMusic = currentGameType->fastMusic;
				getAudioManager()->playMusic(currentGameType->fastMusic, getVolume(), 1.0f, true);
			}

			if (anythingAboveThreeQuarters)
			{
				makeAnnouncementCaption("Uh oh, be careful!");
			}
		}
	}
	else
	{
		if (playingFastMusic == true)
		{
			playingFastMusic = false;

			getAudioManager()->stopMusic(playingMusic);
			playingMusic = currentGameType->normalMusic;
			getAudioManager()->playMusic(playingMusic);
		}
	}

	return;
}


//=========================================================================================================================
void GameLogic::updateKeyInput()
{//=========================================================================================================================


	//DONE: autopress buttons getEnabled per game()
	//DONE: timing for buttons per game()


	if (lockInputCountdownTicks > 0)
	{
		return;
	}


	if (!getFrameState()->ROTATECW_HELD)
	{
		canPressRotateCW = true;
		ticksHoldingRotateCW = 0;
		repeatStartedRotateCW = false;
	}

	if (!getFrameState()->ROTATECCW_HELD)
	{
		canPressRotateCCW = true;
		ticksHoldingRotateCCW = 0;
		repeatStartedRotateCCW = false;
	}

	if (!getFrameState()->RIGHT_HELD)
	{
		canPressRight = true;
		ticksHoldingRight = 0;
		repeatStartedRight = false;
	}

	if (!getFrameState()->LEFT_HELD)
	{
		canPressLeft = true;
		ticksHoldingLeft = 0;
		repeatStartedLeft = false;
	}

	if (!getFrameState()->DOWN_HELD)
	{
		canPressDown = true;
		ticksHoldingDown = 0;
		repeatStartedDown = false;
	}

	if (!getFrameState()->UP_HELD)
	{
		canPressUp = true;
		ticksHoldingUp = 0;
		repeatStartedUp = false;
	}

	if (!getFrameState()->HOLDRAISE_HELD)
	{
		canPressHoldRaise = true;
		ticksHoldingHoldRaise = 0;
		repeatStartedHoldRaise = false;
	}
	if (!getFrameState()->SLAM_HELD)
	{
		canPressSlam = true;
		ticksHoldingSlam = 0;
		repeatStartedSlam = false;
	}

	int repeatDelayRotateCW = 100;
	int repeatDelayRotateCCW = 100;
	int repeatDelayHoldRaise = 100;
	int repeatDelayUp = 100;//if stack game, 50
	int repeatDelayDown = 30;//if stack game, 50
	int repeatDelayLeft = 50;
	int repeatDelayRight = 50;
	int repeatDelaySlam = 100;
	bool repeatEnabledRotateCW = false;
	bool repeatEnabledRotateCCW = false;
	bool repeatEnabledHoldRaise = false;
	bool repeatEnabledUp = false;//if stack game, true
	bool repeatEnabledDown = true;
	bool repeatEnabledLeft = true;
	bool repeatEnabledRight = true;
	bool repeatEnabledSlam = false;
	int repeatStartDelayRotateCW = 150;
	int repeatStartDelayRotateCCW = 150;
	int repeatStartDelayHoldRaise = 150;
	int repeatStartDelayUp = 150;
	int repeatStartDelayDown = 30; //if stack game, 150
	int repeatStartDelayLeft = 150;
	int repeatStartDelayRight = 150;
	int repeatStartDelaySlam = 150;

	if(currentGameType->gameMode==GameMode::STACK)
	{
		repeatDelayUp = 50;
		repeatDelayDown = 50;
		repeatEnabledUp = true;
		repeatStartDelayDown = 150;
	}


	if (getFrameState()->ROTATECW_HELD && ((repeatEnabledRotateCW && repeatStartedRotateCW == false && ticksHoldingRotateCW >= repeatStartDelayRotateCW) || (repeatStartedRotateCW && ticksHoldingRotateCW >= repeatDelayRotateCW)))
	{
		canPressRotateCW = true;
		ticksHoldingRotateCW = 0;
		repeatStartedRotateCW = true;
	}
	else
	{
		ticksHoldingRotateCW += ticks();
	}


	if (getFrameState()->ROTATECCW_HELD && ((repeatEnabledRotateCCW && repeatStartedRotateCCW == false && ticksHoldingRotateCCW >= repeatStartDelayRotateCCW) || (repeatStartedRotateCCW && ticksHoldingRotateCCW >= repeatDelayRotateCCW)))
	{
		canPressRotateCCW = true;
		ticksHoldingRotateCCW = 0;
		repeatStartedRotateCCW = true;
	}
	else
	{
		ticksHoldingRotateCCW += ticks();
	}


	if (getFrameState()->RIGHT_HELD && ((repeatEnabledRight && repeatStartedRight == false && ticksHoldingRight >= repeatStartDelayRight)||(repeatStartedRight && ticksHoldingRight >= repeatDelayRight)))
	{
		canPressRight = true;
		ticksHoldingRight = 0;
		repeatStartedRight = true;
	}
	else
	{
		ticksHoldingRight += ticks();
	}


	if (getFrameState()->LEFT_HELD && ((repeatEnabledLeft && repeatStartedLeft == false && ticksHoldingLeft >= repeatStartDelayLeft) || (repeatStartedLeft && ticksHoldingLeft >= repeatDelayLeft)))
	{
		canPressLeft = true;
		ticksHoldingLeft = 0;
		repeatStartedLeft = true;
	}
	else
	{
		ticksHoldingLeft += ticks();
	}


	if (getFrameState()->DOWN_HELD && ((repeatEnabledDown && repeatStartedDown == false && ticksHoldingDown >= repeatStartDelayDown) || (repeatStartedDown && ticksHoldingDown >= repeatDelayDown)))
	{
		canPressDown = true;
		ticksHoldingDown = 0;
		repeatStartedDown = true;
	}
	else
	{
		ticksHoldingDown += ticks();
	}


	if (getFrameState()->UP_HELD && ((repeatEnabledUp && repeatStartedUp == false && ticksHoldingUp >= repeatStartDelayUp) || (repeatStartedUp && ticksHoldingUp >= repeatDelayUp)))
	{
		canPressUp = true;
		ticksHoldingUp = 0;
		repeatStartedUp = true;
	}
	else
	{
		ticksHoldingUp += ticks();
	}


	if (getFrameState()->HOLDRAISE_HELD && ((repeatEnabledHoldRaise && repeatStartedHoldRaise == false && ticksHoldingHoldRaise >= repeatStartDelayHoldRaise) || (repeatStartedHoldRaise && ticksHoldingHoldRaise >= repeatDelayHoldRaise)))
	{
		canPressHoldRaise = true;
		ticksHoldingHoldRaise = 0;
		repeatStartedHoldRaise = true;
	}
	else
	{
		ticksHoldingHoldRaise += ticks();
	}

	if (getFrameState()->SLAM_HELD && ((repeatEnabledSlam && repeatStartedSlam == false && ticksHoldingSlam >= repeatStartDelaySlam) || (repeatStartedSlam && ticksHoldingSlam >= repeatDelaySlam)))
	{
		canPressSlam = true;
		ticksHoldingSlam = 0;
		repeatStartedSlam = true;
	}
	else
	{
		ticksHoldingSlam += ticks();
	}

	// END CHECK IF KEY WAS ALREADY PRESSED
	// BEGIN ACTUAL KEY CHECK
	if ((getFrameState()->ROTATECW_HELD) && (canPressRotateCW == true))
	{
		if (currentGameType->gameMode == GameMode::STACK)
		{


			if (currentGameType->stackCursorType == CursorType::ONE_BLOCK_PICK_UP)
			{
				getAudioManager()->playSound(currentGameType->rotateSound, getVolume(), getSoundEffectSpeed());
				grid->cursorSwapHoldingBlockWithGrid(currentPiece);
			}

			if (currentGameType->stackCursorType == CursorType::TWO_BLOCK_HORIZONTAL)
			{
				getAudioManager()->playSound(currentGameType->rotateSound, getVolume(), getSoundEffectSpeed());
				grid->cursorSwapBetweenTwoBlocksHorizontal(currentPiece);
			}

			if (currentGameType->stackCursorType == CursorType::TWO_BLOCK_VERTICAL)
			{
				getAudioManager()->playSound(currentGameType->rotateSound, getVolume(), getSoundEffectSpeed());
				grid->cursorSwapBetweenTwoBlocksVertical(currentPiece);
			}

			if (currentGameType->stackCursorType == CursorType::THREE_BLOCK_HORIZONTAL)
			{
				getAudioManager()->playSound(currentGameType->rotateSound, getVolume(), getSoundEffectSpeed());
				grid->cursorSwapBetweenThreeBlocksHorizontal(currentPiece, MovementType::ROTATE_CLOCKWISE);
			}

			if (currentGameType->stackCursorType == CursorType::THREE_BLOCK_VERTICAL)
			{
				getAudioManager()->playSound(currentGameType->rotateSound, getVolume(), getSoundEffectSpeed());
				grid->cursorSwapBetweenThreeBlocksVertical(currentPiece, MovementType::ROTATE_CLOCKWISE);
			}

			if (currentGameType->stackCursorType == CursorType::QUAD_BLOCK_ROTATE)
			{
				getAudioManager()->playSound(currentGameType->rotateSound, getVolume(), getSoundEffectSpeed());
				grid->cursorRotateBlocks(currentPiece, MovementType::ROTATE_CLOCKWISE);
			}
		}

		if (currentGameType->gameMode == GameMode::DROP)
		{
			getAudioManager()->playSound(currentGameType->rotateSound, getVolume(), getSoundEffectSpeed());
			movePiece(MovementType::ROTATE_CLOCKWISE);
		}
			
		
		canPressRotateCW = false;
		ticksHoldingRotateCW = 0;
	}

	if ((getFrameState()->ROTATECCW_HELD) && (canPressRotateCCW == true))
	{
		if (currentGameType->gameMode == GameMode::STACK)
		{


			if (currentGameType->stackCursorType == CursorType::ONE_BLOCK_PICK_UP)
			{
				getAudioManager()->playSound(currentGameType->rotateSound, getVolume(), getSoundEffectSpeed());
				grid->cursorSwapHoldingBlockWithGrid(currentPiece);
			}

			if (currentGameType->stackCursorType == CursorType::TWO_BLOCK_HORIZONTAL)
			{
				getAudioManager()->playSound(currentGameType->rotateSound, getVolume(), getSoundEffectSpeed());
				grid->cursorSwapBetweenTwoBlocksHorizontal(currentPiece);
			}

			if (currentGameType->stackCursorType == CursorType::TWO_BLOCK_VERTICAL)
			{
				getAudioManager()->playSound(currentGameType->rotateSound, getVolume(), getSoundEffectSpeed());
				grid->cursorSwapBetweenTwoBlocksVertical(currentPiece);
			}

			if (currentGameType->stackCursorType == CursorType::THREE_BLOCK_HORIZONTAL)
			{
				getAudioManager()->playSound(currentGameType->rotateSound, getVolume(), getSoundEffectSpeed());
				grid->cursorSwapBetweenThreeBlocksHorizontal(currentPiece, MovementType::ROTATE_COUNTERCLOCKWISE);
			}

			if (currentGameType->stackCursorType == CursorType::THREE_BLOCK_VERTICAL)
			{
				getAudioManager()->playSound(currentGameType->rotateSound, getVolume(), getSoundEffectSpeed());
				grid->cursorSwapBetweenThreeBlocksVertical(currentPiece, MovementType::ROTATE_COUNTERCLOCKWISE);
			}

			if (currentGameType->stackCursorType == CursorType::QUAD_BLOCK_ROTATE)
			{
				getAudioManager()->playSound(currentGameType->rotateSound, getVolume(), getSoundEffectSpeed());
				grid->cursorRotateBlocks(currentPiece, MovementType::ROTATE_COUNTERCLOCKWISE);
			}
		}

		if (currentGameType->gameMode == GameMode::DROP)
		{
			getAudioManager()->playSound(currentGameType->rotateSound, getVolume(), getSoundEffectSpeed());
			movePiece(MovementType::ROTATE_COUNTERCLOCKWISE);
		}

		canPressRotateCCW = false;
		ticksHoldingRotateCCW = 0;
	}

	if ((getFrameState()->RIGHT_HELD) && (canPressRight == true) && !getFrameState()->LEFT_HELD)
	{
		if (currentGameType->gameMode == GameMode::STACK)
		{
			getAudioManager()->playSound(currentGameType->moveRightSound, getVolume(), getSoundEffectSpeed());
			if (currentPiece->xGrid < grid->getWidth() - currentPiece->getWidth())
			{
				currentPiece->xGrid++;
			}
		}
		else
			if (currentGameType->gameMode == GameMode::DROP)
		{
			getAudioManager()->playSound(currentGameType->moveRightSound, getVolume(), getSoundEffectSpeed());
			movePiece(MovementType::RIGHT);
		}

		canPressRight = false;
		ticksHoldingRight = 0;
	}


	if ((getFrameState()->LEFT_HELD) && (canPressLeft == true) && !getFrameState()->RIGHT_HELD)
	{
		if (currentGameType->gameMode == GameMode::STACK)
		{
			getAudioManager()->playSound(currentGameType->moveLeftSound, getVolume(), getSoundEffectSpeed());
			if (currentPiece->xGrid > 0)
			{
				currentPiece->xGrid--;
			}
		}
		else
			if (currentGameType->gameMode == GameMode::DROP)
		{
			getAudioManager()->playSound(currentGameType->moveLeftSound, getVolume(), getSoundEffectSpeed());
			movePiece(MovementType::LEFT);
		}

		canPressLeft = false;
		ticksHoldingLeft = 0;
	}


	if ((getFrameState()->DOWN_HELD) && (canPressDown == true) && !getFrameState()->UP_HELD)
	{
		if (currentGameType->gameMode == GameMode::STACK)
		{
			getAudioManager()->playSound(currentGameType->moveDownSound, getVolume(), getSoundEffectSpeed());
			if (currentPiece->yGrid < grid->getHeight() - (1 + currentPiece->getHeight()))
			{
				currentPiece->yGrid++;
			}
		}
		else
			if (currentGameType->gameMode == GameMode::DROP)
		{
			if (pieceSetAtBottom == false)
			{
				getAudioManager()->playSound(currentGameType->moveDownSound, getVolume(), getSoundEffectSpeed());

				movePiece(MovementType::DOWN);

				if (getFrameState()->dropLockType == DropLockType::SOFT_DROP_INSTANT_LOCK)
				{
					lockDelayTicksCounter = 0;
				}
			}
		}

		canPressDown = false;
		ticksHoldingDown = 0;
	}


	if ((getFrameState()->UP_HELD) && (canPressUp == true && !getFrameState()->DOWN_HELD))
	{
		if (currentGameType->gameMode == GameMode::STACK)
		{
			getAudioManager()->playSound(currentGameType->moveUpSound, getVolume(), getSoundEffectSpeed());
			if (currentPiece->yGrid > 1 + GameLogic::aboveGridBuffer)
			{
				currentPiece->yGrid--;
			}
		}
		else
			if (currentGameType->gameMode == GameMode::DROP)
		{

		}

		canPressUp = false;
		ticksHoldingUp = 0;
	}

	if ((getFrameState()->SLAM_HELD) && (canPressSlam == true))
	{
		if (currentGameType->gameMode == GameMode::STACK)
		{

		}
		else
			if (currentGameType->gameMode == GameMode::DROP)
		{
			if (pieceSetAtBottom == false)
			{
				getAudioManager()->playSound(currentGameType->hardDropSwishSound, getVolume(), 2.0f);

				if (currentPiece != nullptr)
				{
					currentPiece->setBlocksSlamming();
				}


				while (movePiece(MovementType::HARD_DROP) == true)
				{
					if (getFrameState()->dropLockType == DropLockType::HARD_DROP_INSTANT_LOCK)
					{
						lockDelayTicksCounter = 0;
					}
				}


				grid->shakeSmall();

				getAudioManager()->playSound(currentGameType->hardDropClankSound, getVolume(), 0.5f);
			}
		}

		canPressSlam = false;
		ticksHoldingSlam = 0;
	}


	if ((getFrameState()->HOLDRAISE_HELD) && (canPressHoldRaise == true))
	{
		if (currentGameType->gameMode == GameMode::STACK)
		{
		}
		else
			if (currentGameType->gameMode == GameMode::DROP)
		{
			if (currentGameType->holdPieceEnabled == true)
			{
				if (holdPiece != nullptr || switchedHoldPieceAlready)
				{
					if (switchedHoldPieceAlready == false)
					{
						switchedHoldPieceAlready = true;
						Piece* tempPiece = holdPiece;
						holdPiece = currentPiece;
						currentPiece = tempPiece;

						if (currentGameType->resetHoldPieceRotation)
						{
							holdPiece->setRotation(0);
						}

						setCurrentPieceAtTop();

						getAudioManager()->playSound(currentGameType->switchHoldPieceSound, getVolume(), 1.0f);
					}
					else
					{
						getAudioManager()->playSound(currentGameType->cantHoldPieceSound, getVolume(), 1.0f);
					}
				}
				else
				{
					if (currentPiece != nullptr)
					{
						holdPiece = currentPiece;

						if (currentGameType->resetHoldPieceRotation)
						{
							holdPiece->setRotation(0);
						}

						getAudioManager()->playSound(currentGameType->switchHoldPieceSound, getVolume(), getSoundEffectSpeed());
						newRandomPiece();
					}
				}
			}
		}

		canPressHoldRaise = false;
		ticksHoldingHoldRaise = 0;
	}


	if (currentGameType->gameMode == GameMode::STACK)
	{
		if (getFrameState()->HOLDRAISE_HELD)
		{
			if (manualStackRiseTicksCounter > 30/4)//TODO: make better
			{
				manualStackRiseTicksCounter = 0;

				manualStackRiseSoundToggle++;
				if (manualStackRiseSoundToggle > 3)
				{
					manualStackRiseSoundToggle = 0;
					getAudioManager()->playSound(currentGameType->stackRiseSound, getVolume(), 1.0f);
				}
				grid->scrollUpStack(currentPiece, 1);
			}
		}
	}



}


//=========================================================================================================================
void GameLogic::wonSequence()
{//=========================================================================================================================


	if (startedWinSequence == false)
	{
		startedWinSequence = true;

		getAudioManager()->playSound(currentGameType->winSound, getVolume(), 1.0f);

		getAudioManager()->stopMusic(playingMusic);
		playingMusic = currentGameType->winMusic;
		getAudioManager()->playMusic(playingMusic);

		if (winCaption == nullptr)
		{
			winCaption = getCaptionManager()->newManagedCaption(0, (GLUtils::getViewportHeight() / 2) - 60, -1, "WIN", resultCaptionFont, BobColor::green, BobColor::clear, RenderOrder::OVER_TEXT, 1.0f);
			winCaption->screenX = (int)(grid->getXOnScreenNoShake() + (grid->getWidth() * cellW() / 2)) - winCaption->getWidth() / 2;
			winCaption->flashing = true;
			winCaption->flashingTicksPerFlash = 500;
		}
	}

	updateSpecialPiecesAndBlocks();
}


//=========================================================================================================================
void GameLogic::lostSequence()
{//=========================================================================================================================


	if (startedLoseSequence == false)
	{
		startedLoseSequence = true;

		getAudioManager()->playSound(currentGameType->loseSound, getVolume(), 1.0f);

		getAudioManager()->stopMusic(playingMusic);
		playingMusic = currentGameType->loseMusic;
		getAudioManager()->playMusic(playingMusic);

		if (loseCaption == nullptr)
		{
			loseCaption = getCaptionManager()->newManagedCaption(0, (GLUtils::getViewportHeight() / 2) - 60, -1, "LOSE", resultCaptionFont, BobColor::red, BobColor::clear, RenderOrder::OVER_TEXT, 1.0f);
			loseCaption->screenX = (int)(grid->getXOnScreenNoShake() + (grid->getWidth() * cellW() / 2)) - loseCaption->getWidth() / 2;
			loseCaption->flashing = true;
			loseCaption->flashingTicksPerFlash = 500;
		}
	}

	updateSpecialPiecesAndBlocks();
}


//=========================================================================================================================
void GameLogic::diedSequence()
{//=========================================================================================================================


	if (startedDeathSequence == false)
	{
		startedDeathSequence = true;

		getAudioManager()->playSound(currentGameType->deadSound, getVolume(), 1.0f);


		getAudioManager()->stopMusic(playingMusic);
		playingMusic = currentGameType->deadMusic;
		getAudioManager()->playMusic(playingMusic);

		if (firstDeath == false)
		{
			firstDeath = true;

			if (deadCaption == nullptr)
			{
				deadCaption = getCaptionManager()->newManagedCaption(0, (GLUtils::getViewportHeight() / 2) - 60, -1, "NEVER GIVE UP", resultCaptionFont, BobColor::red, BobColor::clear, RenderOrder::OVER_TEXT, 1.0f);
				deadCaption->screenX = (int)(grid->getXOnScreenNoShake() + (grid->getWidth() * cellW() / 2)) - deadCaption->getWidth() / 2;
				deadCaption->flashing = true;
				deadCaption->flashingTicksPerFlash = 500;
			}
		}
		else
		{
			if (firstDeath == true)
			{
				firstDeath = false;

				if (deadCaption == nullptr)
				{
					deadCaption = getCaptionManager()->newManagedCaption(0, (GLUtils::getViewportHeight() / 2) - 60, -1, "NEVER GIVE UP", resultCaptionFont, BobColor::red, BobColor::clear, RenderOrder::OVER_TEXT, 1.0f);
					deadCaption->screenX = (int)(grid->getXOnScreenNoShake() + (grid->getWidth() * cellW() / 2)) - deadCaption->getWidth() / 2;
					deadCaption->flashing = true;
					deadCaption->flashingTicksPerFlash = 500;
				}
			}
		}
	}


	updateSpecialPiecesAndBlocks();

	grid->doDeathSequence();
}


//=========================================================================================================================
void GameLogic::creditsSequence()
{//=========================================================================================================================

	if (creditScreenInitialized == false)
	{
		creditScreenInitialized = true;


		getAudioManager()->stopMusic(playingMusic);

		playingMusic = currentGameType->creditsMusic;
		getAudioManager()->playMusic(playingMusic);

		if (creditsCaption == nullptr)
		{
			creditsCaption = getCaptionManager()->newManagedCaption(0, (GLUtils::getViewportHeight() / 2) - 60, -1, "COMPLETE", resultCaptionFont, BobColor::purple, BobColor::clear, RenderOrder::OVER_TEXT, 1.0f);
			creditsCaption->screenX = (int)(grid->getXOnScreenNoShake() + (grid->getWidth() * cellW() / 2)) - creditsCaption->getWidth() / 2;
			creditsCaption->flashing = true;
			creditsCaption->flashingTicksPerFlash = 500;
		}
	}
}




//=========================================================================================================================
void GameLogic::makeAnnouncementCaption(const string& text)
{//=========================================================================================================================
	makeAnnouncementCaption(text, nullptr);
}


//=========================================================================================================================
void GameLogic::makeAnnouncementCaption(const string& text, BobColor* color)
{//=========================================================================================================================

	if (color == nullptr)
	{
		color = announcementCaptionTextColor;
	}

	Caption* c = getCaptionManager()->newManagedCaption(0, 0, -1, text, announcementCaptionFont, color, announcementCaptionBGColor, RenderOrder::ABOVE_TOP, announcementCaptionScale);
	//c->drawAbove = true;
	announcementCaptions->add(c);
}


//=========================================================================================================================
void GameLogic::makeRandomLevelUpCaption()
{//=========================================================================================================================
	int z = 0;
	z = Math::randLessThan(5);//doesn't matter
	if (z == 0)
	{
		makeAnnouncementCaption("Nice! Keep going!");
	}
	if (z == 1)
	{
		makeAnnouncementCaption("Not bad! Can you keep it up?");
	}
	if (z == 2)
	{
		makeAnnouncementCaption("So far so good!");
	}
	if (z == 3)
	{
		makeAnnouncementCaption("You'll make it at this rate!");
	}
	if (z == 4)
	{
		makeAnnouncementCaption("You can do it, come on!");
	}
}


//=========================================================================================================================
void GameLogic::updateCaptionFadeValues()
{//=========================================================================================================================


	if (captionColorCycleHueInOutToggle == true)
	{
		captionColorCycleHueValue += 0.001f * getEngine()->engineTicksPassed();
		if (captionColorCycleHueValue > 1.0f)
		{
			captionColorCycleHueValue = 1.0f;
			captionColorCycleHueInOutToggle = false;
		}
	}
	else
	{
		captionColorCycleHueValue -= 0.001f * getEngine()->engineTicksPassed();
		if (captionColorCycleHueValue < 0.0f)
		{
			captionColorCycleHueValue = 0.0f;
			captionColorCycleHueInOutToggle = true;
		}
	}
}


//=========================================================================================================================
Caption* GameLogic::makeInfoCaption(const string& text)
{//=========================================================================================================================


	Caption* c = getCaptionManager()->newManagedCaption(0, (int)++captionY * captionYSize, -1, string("" + text), captionFont, captionTextColor, captionBGColor, RenderOrder::ABOVE, captionScale);
	if (infoCaptions->contains(c) == false)
	{
		infoCaptions->add(c);
	}
	return c;
}


//=========================================================================================================================
void GameLogic::deleteAllCaptions()
{//=========================================================================================================================


	if (totalTicksPassedCaption != nullptr)
	{
		totalTicksPassedCaption->setToBeDeletedImmediately();
	}
	if (creditsCaption != nullptr)
	{
		creditsCaption->setToBeDeletedImmediately();
	}
	if (deadCaption != nullptr)
	{
		deadCaption->setToBeDeletedImmediately();
	}
	if (winCaption != nullptr)
	{
		winCaption->setToBeDeletedImmediately();
	}
	if (loseCaption != nullptr)
	{
		loseCaption->setToBeDeletedImmediately();
	}
	if (pressStartCaption != nullptr)
	{
		pressStartCaption->setToBeDeletedImmediately();
	}
	if (waitingForPlayerCaption != nullptr)
	{
		waitingForPlayerCaption->setToBeDeletedImmediately();
	}
	if (garbageWaitCaption != nullptr)
	{
		garbageWaitCaption->setToBeDeletedImmediately();
	}
	if (nextCaption != nullptr)
	{
		nextCaption->setToBeDeletedImmediately();
	}
	if (holdCaption != nullptr)
	{
		holdCaption->setToBeDeletedImmediately();
	}

	for (int i = 0; i < infoCaptions->size(); i++)
	{
		Caption* c = infoCaptions->get(i);
		if (c != nullptr)
		{
			c->setToBeDeletedImmediately();
		}
	}


	for (int i = 0; i < announcementCaptions->size(); i++)
	{
		Caption* c = announcementCaptions->get(i);
		if (c != nullptr)
		{
			c->setToBeDeletedImmediately();
		}
	}
}


//=========================================================================================================================
void GameLogic::updateInfoCaptionsXY()
{//=========================================================================================================================


	int counterY = -1;
	float gridY = grid->getYInFBO();

	if (infoCaptions->size() > 0)captionYSize = (int)infoCaptions->get(0)->getHeight();

	for (int i = 0; i < infoCaptions->size(); i++)
	{
		Caption* c = infoCaptions->get(i);

		if (c != nullptr)
		{

			if (getBobsGame()->isMultiplayer())c->visible = false;

			c->screenX = captionX;
			c->screenY = gridY + (++counterY * captionYSize);
			
		}
	}
}


//=========================================================================================================================
void GameLogic::updateCaptions()
{//=========================================================================================================================


	captionY = -1;


	if (levelCaption == nullptr)
	{
		levelCaption = makeInfoCaption("levelCaption");
	}


	if (gameTypeCaption == nullptr)
	{
		gameTypeCaption = makeInfoCaption("gameTypeCaption");
	}

	if (rulesCaption == nullptr)
	{
		rulesCaption = makeInfoCaption("rulesCaption");
	}


	if (difficultyCaption == nullptr)
	{
		difficultyCaption = makeInfoCaption("difficultyCaption");
	}



	if (linesClearedThisGameCaption == nullptr)
	{
		linesClearedThisGameCaption = makeInfoCaption("linesClearedThisGameCaption");
	}
	if (blocksClearedThisGameCaption == nullptr)
	{
		blocksClearedThisGameCaption = makeInfoCaption("blocksClearedThisGameCaption");
	}
	if (piecesMadeThisGameCaption == nullptr)
	{
		piecesMadeThisGameCaption = makeInfoCaption("piecesMadeThisGameCaption");
	}
	if (totalLinesClearedCaption == nullptr)
	{
		totalLinesClearedCaption = makeInfoCaption("totalLinesClearedCaption");
	}
	if (totalBlocksClearedCaption == nullptr)
	{
		totalBlocksClearedCaption = makeInfoCaption("totalBlocksClearedCaption");
	}
	if (totalPiecesMadeCaption == nullptr)
	{
		totalPiecesMadeCaption = makeInfoCaption("totalPiecesMadeCaption");
	}






	if (currentChainCaption == nullptr)
	{
		currentChainCaption = makeInfoCaption("currentChainCaption");
	}
	if (currentComboCaption == nullptr)
	{
		currentComboCaption = makeInfoCaption("currentComboCaption");
	}
	if (comboChainTotalCaption == nullptr)
	{
		comboChainTotalCaption = makeInfoCaption("comboChainTotalCaption");
	}


	if (lineDropTicksCaption == nullptr)
	{
		lineDropTicksCaption = makeInfoCaption("lineDropTicksCaption");
	}
	if (lockDelayCaption == nullptr)
	{
		lockDelayCaption = makeInfoCaption("lockDelayCaption");
	}
	if (spawnDelayCaption == nullptr)
	{
		spawnDelayCaption = makeInfoCaption("spawnDelayCaption");
	}
	if (lineClearDelayCaption == nullptr)
	{
		lineClearDelayCaption = makeInfoCaption("lineClearDelayCaption");
	}

	if (gravityCaption == nullptr)
	{
		gravityCaption = makeInfoCaption("gravityCaption");
	}
	
	if (currentGameType->gameMode == GameMode::STACK)
	{
		if (stopCounterCaption == nullptr)
		{
			stopCounterCaption = makeInfoCaption("stopCounterCaption");
		}
	}




#ifdef _DEBUG

	if (blocksInGridCaption == nullptr)
	{
		blocksInGridCaption = makeInfoCaption("blocksInGridCaption");
	}
	if (xCaption == nullptr)
	{
		xCaption = makeInfoCaption("xCaption");
	}
	if (yCaption == nullptr)
	{
		yCaption = makeInfoCaption("yCaption");
	}
	if (rotationCaption == nullptr)
	{
		rotationCaption = makeInfoCaption("rotationCaption");
	}
	if (seedCaption == nullptr)
	{
		seedCaption = makeInfoCaption("seedCaption");
	}
	if (bgCaption == nullptr)
	{
		bgCaption = makeInfoCaption("bgCaption");
	}
#endif






	if (totalTicksPassedCaption == nullptr)
	{
		totalTicksPassedCaption = getCaptionManager()->newManagedCaption(0, 0, -1, "00:00:000", announcementCaptionFont, captionTextColor, BobColor::clear, RenderOrder::ABOVE_TOP, captionScale);
		timeCaptionStandardizedWidth = (int)(totalTicksPassedCaption->getWidth());
	}

	if (holdCaption == nullptr)
	{
		holdCaption = getCaptionManager()->newManagedCaption(0, 0, -1, "HOLD", mediumCaptionFont, captionTextColor, BobColor::clear, RenderOrder::ABOVE, captionScale);
	}
	if (nextCaption == nullptr)
	{
		nextCaption = getCaptionManager()->newManagedCaption(0, 0, -1, "NEXT", mediumCaptionFont, captionTextColor, BobColor::clear, RenderOrder::ABOVE, captionScale);
	}


	updateInfoCaptionsXY();

#ifdef _DEBUG
	if (currentPiece != nullptr)
	{
		xCaption->setText(string("X: ") + to_string(currentPiece->xGrid));
		yCaption->setText(string("Y: ") + to_string(currentPiece->yGrid));

		rotationCaption->setText(string("Rotation: ") + to_string(currentPiece->currentRotation));
	}

	blocksInGridCaption->setText(string("Blocks In Grid: ") + to_string(grid->getNumberOfFilledCells()));
	seedCaption->setText(string("Seed: ") + to_string(randomSeed));
	bgCaption->setText(string("Shader: ") + to_string(getBobsGame()->shaderCount));
#endif

	if (stopCounterCaption != nullptr)
	{
		stopCounterCaption->setText(stopCounterCaptionText);
	}


	if (currentLevel == getCurrentDifficulty()->extraStage1Level)
	{
		levelCaptionText = "Level: EX1";
	}
	else if (currentLevel == getCurrentDifficulty()->extraStage2Level)
	{
		levelCaptionText = "Level: EX2";
	}
	else if (currentLevel == getCurrentDifficulty()->extraStage3Level)
	{
		levelCaptionText = "Level: EX3";
	}
	else if (currentLevel == getCurrentDifficulty()->extraStage4Level)
	{
		levelCaptionText = "Level: EX4";
	}
	else
	{
		levelCaptionText = string("Level: ") + to_string(currentLevel);
	}


	levelCaption->setText(levelCaptionText);
	gameTypeCaption->setText("Game: "+currentGameType->name);
	rulesCaption->setText("Rules: "+currentGameType->rules);
	difficultyCaption->setText("Difficulty: "+ getCurrentDifficulty()->name);

	gravityCaption->setText(string("Gravity: ") + to_string(16.7f / (float)(currentLineDropSpeedTicks)) + string("G"));//::Format("%.3f",
	lockDelayCaption->setText(string("Lock Delay: ") + to_string(lockDelayTicksCounter));
	lineDropTicksCaption->setText(string("Line Drop Ticks: ") + to_string(lineDropTicksCounter));
	spawnDelayCaption->setText(string("Spawn Delay Ticks: ") + to_string(spawnDelayTicksCounter));
	lineClearDelayCaption->setText(string("Line Clear Delay Ticks: ") + to_string(lineClearDelayTicksCounter));

	linesClearedThisGameCaption->setText(string("Lines This Game: ") + to_string(linesClearedThisGame));
	blocksClearedThisGameCaption->setText(string("Blocks This Game: ") + to_string(blocksClearedThisGame));
	piecesMadeThisGameCaption->setText(string("Pieces Made This Game: ") + to_string(piecesMadeThisGame));

	totalLinesClearedCaption->setText(string("Lines Total: ") + to_string(linesClearedTotal));
	totalBlocksClearedCaption->setText(string("Blocks Total: ") + to_string(blocksClearedTotal));
	totalPiecesMadeCaption->setText(string("Pieces Made Total: ") + to_string(piecesMadeTotal));

	currentChainCaption->setText(string("Current Chain: ") + to_string(currentChain));
	currentComboCaption->setText(string("Current Combo: ") + to_string(currentCombo));
	comboChainTotalCaption->setText(string("Combo Chain Total: ") + to_string(comboChainTotal));



	ostringstream oss1;
	string ms = "000";
	oss1 << setfill('0') << setw(3) << (totalTicksPassed % 1000);
	ms = oss1.str();
	
	ostringstream oss2;
	string seconds = "00";
	oss2 << setfill('0') << setw(2) << ((totalTicksPassed / 1000) % 60);
	seconds = oss2.str();

	ostringstream oss3;
	string minutes = "00";
	oss3 << setfill('0') << setw(2) << ((totalTicksPassed / 1000 / 60) % 60);
	minutes = oss3.str();

	totalTicksPassedCaption->setText(minutes + string(":") + seconds + string(":") + ms);

	totalTicksPassedCaption->screenX = grid->getXOnScreenNoShake() + (grid->getWidth() * blockWidth) / 2 - timeCaptionStandardizedWidth / 2;
	totalTicksPassedCaption->screenY = playingFieldY1 - 40;// grid->screenY + grid->getHeight() * blockHeight + 20;

	levelCaption->setTextColor(new BobColor(captionColorCycleHueValue, 0.5f, 1.0f, 1.0f, true));


	if (announcementCaptions->size() > 15)
	{
		Caption* c = announcementCaptions->get(0);
		c->setToFadeOutAndBeDeleted();
		announcementCaptions->removeAt(0);
	}


	//defaults for original font
	//		float centerStartScale = 3.25f;
	//		float centerStepDownScale = 0.25f;
	//		float centerMinScale = 2.0f;
	//		float sideMinScale = 1.0f;

	float centerStartScale = 1.25f;
	float centerStepDownScale = 0.25f;
	float centerMinScale = 0.5f;
	float sideMinScale = 0.5f;


	for (int i = 0; i < announcementCaptions->size(); i++)
	{
		Caption* c = announcementCaptions->get(i);


		int stayInCenterTicks = 1000;
		int transitionTime = 200;

		if (c->ticksAge < stayInCenterTicks)
		{
			c->setAlphaTo(1.0f);
			c->flashing = true;
			c->flashingTicksPerFlash = 500;

			c->scale = centerStartScale - (announcementCaptions->size() - i) * centerStepDownScale;
			if (c->scale < centerMinScale)
			{
				c->scale = centerMinScale;
			}

			c->screenX = (int)(grid->getXOnScreenNoShake() + (grid->getWidth() * cellW() / 2)) - c->getWidth() / 2;
			c->screenY = (int)(grid->getYOnScreenNoShake() + (grid->getHeight() * cellH() / 2)) - (c->getHeight() * (announcementCaptions->size() - i) + 10);
		}
		else
		{
			if (getBobsGame()->isMultiplayer())c->visible = false;

			//if(c.ticksAge<stayInCenterTicks+transitionTime)

			c->scale = sideMinScale;

			float xFrom = (grid->getXOnScreenNoShake() + (grid->getWidth() * cellW() / 2)) - c->getWidth() / 2;
			float yFrom = (grid->getYOnScreenNoShake() + (grid->getHeight() * cellH() / 2)) - c->getHeight() / 2;
			float xTo = (grid->getXOnScreenNoShake() - (cellW() * 1.5f) - c->getWidth());
			float yTo = (grid->getYOnScreenNoShake() + (cellH() * 2)) + c->getHeight() * i;

			float xDiff = xFrom - xTo;
			float yDiff = yFrom - yTo;

			c->setAlphaTo(1.0f);
			c->flashing = false;
			c->flashingTicksPerFlash = 0;

			float xMod = ((float)(c->ticksAge - stayInCenterTicks) / (float)(transitionTime));
			float yMod = ((float)(c->ticksAge - stayInCenterTicks) / (float)(transitionTime));

			if (xMod > 1.0f)
			{
				xMod = 1.0f;
			}
			if (yMod > 1.0f)
			{
				yMod = 1.0f;
			}


			c->screenX = xFrom - xMod * xDiff;
			c->screenY = yFrom - yMod * yDiff;
		}


		if (c->getBeingDeletedWhenFadeOutStatus() == true && c->getAlpha() == 0.0f)
		{
			//announcementCaptions.RemoveAt(i);
			announcementCaptions->removeAt(i);
			i = -1;
			continue;
		}
	}
}


//=========================================================================================================================
void GameLogic::resetNextPieces()
{//=========================================================================================================================

	//destroy all cube objects
	if (currentPiece != nullptr)
	{
	}
	if (holdPiece != nullptr)
	{
	}
	if (nextPieces.size() > 0)
	{
		for (int x = 0; x < nextPieces.size(); x++)
		{
			//Piece* p = nextPieces->get(x);
		}
	}
	if (nextPieceSpecialBuffer.size() > 0)
	{
		for (int x = 0; x < nextPieceSpecialBuffer.size(); x++)
		{
			//Piece* p = nextPieceSpecialBuffer->get(x);
		}
	}

	currentPiece = nullptr;
	holdPiece = nullptr;


	nextPieces.clear();//MEMORY
	nextPieceSpecialBuffer.clear();//MEMORY
}

#define CHANGEGAME 1
//=========================================================================================================================
void GameLogic::changeGame()
{//=========================================================================================================================


	//TODO: play sound, delay, fix captions to show scoring type, etc


	int piecesMade = piecesMadeThisGame;
	long long dropSpeed = currentLineDropSpeedTicks;


	

	didInit = false;
	initGame();

	currentLineDropSpeedTicks = dropSpeed;
	piecesMadeThisGame = piecesMade;
	lastPiecesMadeThisGame = piecesMade;


	//log.warn("Number of cells after init: "+grid.getNumberOfFilledCells());

	//forceBlockGravity = true;

	lockInputCountdownTicks = 500;
}


//=========================================================================================================================
void GameLogic::updateScore()
{//=========================================================================================================================

	

	if (piecesMadeThisGame > lastPiecesMadeThisGame)
	{
		lastPiecesMadeThisGame = piecesMadeThisGame;

		if (currentLineDropSpeedTicks > getCurrentDifficulty()->minimumLineDropSpeedTicks)
		{
			currentLineDropSpeedTicks = (long long)(currentLineDropSpeedTicks * 0.98f);
		}
		if (currentLineDropSpeedTicks < getCurrentDifficulty()->minimumLineDropSpeedTicks)
		{
			currentLineDropSpeedTicks = getCurrentDifficulty()->minimumLineDropSpeedTicks;
		}

	}



	if (currentGameType->scoreType == ScoreType::LINES_CLEARED)
	{
		if (currentGameType->scoreTypeAmountPerLevelGained > 0)
		{
			if (linesClearedThisLevel / currentGameType->scoreTypeAmountPerLevelGained >= 1)
			{
				currentLevel++;
			}
		}
	}
	else
		if (currentGameType->scoreType == ScoreType::BLOCKS_CLEARED)
		{
			if (currentGameType->scoreTypeAmountPerLevelGained > 0)
			{
				if (blocksClearedThisLevel / currentGameType->scoreTypeAmountPerLevelGained >= 1)
				{
					currentLevel++;
				}
			}
		}
		else
			if (currentGameType->scoreType == ScoreType::PIECES_MADE)
			{
				if (currentGameType->scoreTypeAmountPerLevelGained > 0)
				{
					if (piecesMadeThisLevel / currentGameType->scoreTypeAmountPerLevelGained >= 1)
					{
						currentLevel++;
					}
				}
			}
	
		
//	if (totalTicksPassed > lastTicksPassed + 6000)
//	{
//		lastTicksPassed = totalTicksPassed;
//		currentLevel++;
//	}


	if (currentLevel != lastKnownLevel)
	{

		linesClearedThisLevel = 0;
		piecesMadeThisLevel = 0;
		blocksClearedThisLevel = 0;

		lastKnownLevel = currentLevel;

		if (currentGameSequence->gameTypes.size() > 1)
		{
			changeGame();
		}

		timesToFlashScreenQueue = flashScreenTimesPerLevel;


		if (currentLevel > 0)
		{
			if (currentLevel < getCurrentDifficulty()->extraStage1Level)
			{
				makeAnnouncementCaption("Level up!");
			}

			//makeRandomLevelUpCaption();

			grid->setRandomWholePieceColors(false, currentPiece, nextPieces);

			getAudioManager()->playSound(currentGameType->levelUpSound, getVolume(), 1.0f);
		}


		if (currentGameSequence->endlessMode == false)
		{
			if (currentLevel == getCurrentDifficulty()->extraStage1Level && extraStage1 == false)
			{
				extraStage1 = true;
				makeAnnouncementCaption("Wow, it's the special stage!", BobColor::yellow);

				getAudioManager()->playSound(currentGameType->extraStage1Sound, getVolume(), 1.0f);
			}


			if (currentLevel == getCurrentDifficulty()->extraStage2Level && extraStage2 == false)
			{
				extraStage2 = true;
				makeAnnouncementCaption("Whoa, I've never gotten this far!", BobColor::orange);

				getAudioManager()->playSound(currentGameType->extraStage2Sound, getVolume(), 1.0f);
			}


			if (currentLevel == getCurrentDifficulty()->extraStage3Level && extraStage3 == false)
			{
				extraStage3 = true;
				makeAnnouncementCaption("Don't stop the party!", BobColor::red);//"Amazing!"

				getAudioManager()->playSound(currentGameType->extraStage3Sound, getVolume(), 1.0f);
			}


			if (currentLevel == getCurrentDifficulty()->extraStage4Level && extraStage4 == false)
			{
				extraStage4 = true;
				makeAnnouncementCaption("What is going on?!", BobColor::magenta);

				getAudioManager()->playSound(currentGameType->extraStage4Sound, getVolume(), 1.0f);
			}


			if (currentLevel > getCurrentDifficulty()->creditsLevel)
			{
				complete = true;
				makeAnnouncementCaption("You did it!!!", BobColor::blue);

				getAudioManager()->playSound(currentGameType->creditsSound, getVolume(), 1.0f);
			}
		}
	}
}


//=========================================================================================================================
ControlsManager* GameLogic::getControlsManager()
{//=========================================================================================================================
	return getEngine()->getControlsManager();
}


//=========================================================================================================================
AudioManager* GameLogic::getAudioManager()
{//=========================================================================================================================
	return getEngine()->getAudioManager();
}



//
////=========================================================================================================================
//GameType* GameLogic::currentGameType
//{//=========================================================================================================================
//	return currentGameType;
//}
//
//
////=========================================================================================================================
//void GameLogic::setCurrentGameType(GameType* settings)
//{//=========================================================================================================================
//	this->currentGameType = settings;
//}


//=========================================================================================================================
int GameLogic::getRandomIntLessThan(int i, string whereCalledFrom)
{//=========================================================================================================================
	if (i <= 0)return 0;

	int n = randomGenerator() % i;

	//if(isNetworkPlayer)log.warn("NETWORK Random: " + to_string(n) + " / "+to_string(i)+" | " + whereCalledFrom);
	//if(!isNetworkPlayer)log.debug("LOCAL Random: " + to_string(n) + " / "+to_string(i)+" | " + whereCalledFrom);

	return n;
	//return randomGenerator() % i;
	// return randomGenerator.nextInt(i);
}


//=========================================================================================================================
int GameLogic::cellW()
{//=========================================================================================================================
	return blockWidth + currentGameType->gridPixelsBetweenColumns;
}


//=========================================================================================================================
int GameLogic::cellH()
{//=========================================================================================================================
	return blockHeight + currentGameType->gridPixelsBetweenRows;
}


//=========================================================================================================================
int GameLogic::gridW()
{//=========================================================================================================================
	return currentGameType->gridWidth;
}


//=========================================================================================================================
int GameLogic::gridH()
{//=========================================================================================================================
	return currentGameType->gridHeight + GameLogic::aboveGridBuffer;
}


//=========================================================================================================================
long long GameLogic::ticks()
{//=========================================================================================================================
	return frameState.ticksPassed;
}


//=========================================================================================================================
FrameState* GameLogic::getFrameState()
{//=========================================================================================================================
	return &(frameState);
}



