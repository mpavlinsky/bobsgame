#include "stdafx.h"
//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#include <fstream>
#include <iostream>
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/Delegate.h"
#include "Poco/Zip/Decompress.h"
#include "Poco/Process.h"
#include "Poco/DirectoryIterator.h"
using Poco::DirectoryIterator;
using Poco::File;
using Poco::Process;
using Poco::Path;


Logger BobsGame::log = Logger("BobsGame");
//BobsGame* BobsGame::b = nullptr;

BobTexture* BobsGame::upperLeft = nullptr;
BobTexture* BobsGame::top = nullptr;
BobTexture* BobsGame::upperRight = nullptr;
BobTexture* BobsGame::left = nullptr;
BobTexture* BobsGame::right = nullptr;
BobTexture* BobsGame::lowerLeft = nullptr;
BobTexture* BobsGame::bottom = nullptr;
BobTexture* BobsGame::lowerRight = nullptr;

bool BobsGame::_gotIncomingGamesFromServer = false;
mutex BobsGame::_gotIncomingGamesFromServer_Mutex;
queue<GameType*>BobsGame::_incomingGameTypes;
mutex BobsGame::_incomingGameTypes_Mutex;
queue<GameSequence*>BobsGame::_incomingGameSequences;
mutex BobsGame::_incomingGameSequences_Mutex;
ArrayList<GameType*> BobsGame::loadedGameTypes;
ArrayList<GameSequence*> BobsGame::loadedGameSequences;
ArrayList<Sprite*> BobsGame::loadedSprites;



ArrayList<BobsGameUserStatsForSpecificGameAndDifficulty*> BobsGame::userStatsPerGameAndDifficulty;
ArrayList<BobsGameLeaderBoardAndHighScoreBoard*> BobsGame::topPlayersByTotalTimePlayed;
ArrayList<BobsGameLeaderBoardAndHighScoreBoard*> BobsGame::topPlayersByTotalBlocksCleared;
ArrayList<BobsGameLeaderBoardAndHighScoreBoard*> BobsGame::topPlayersByPlaneswalkerPoints;
ArrayList<BobsGameLeaderBoardAndHighScoreBoard*> BobsGame::topPlayersByEloScore;
ArrayList<BobsGameLeaderBoardAndHighScoreBoard*> BobsGame::topGamesByTimeLasted;
ArrayList<BobsGameLeaderBoardAndHighScoreBoard*> BobsGame::topGamesByBlocksCleared;

#include "Room.h"

//=========================================================================================================================
BobsGame::BobsGame()
{//=========================================================================================================================

#ifdef _DEBUG
	log.info("BobsGame()");
#endif

	//constructors are called from the base class up, so State->Engine->GameEngine->BobsGame

}

//=========================================================================================================================
BobsGame::~BobsGame()
{//=========================================================================================================================
#ifdef _DEBUG
	log.info("~BobsGame()");
#endif

	for (int i = 0; i<players.size(); i++)
	{
		PuzzlePlayer *p = players.get(i);

		if (p->gameLogic != nullptr)
		{
			p->gameLogic->deleteAllCaptions();
		}
		delete p->gameLogic;
		p->gameLogic = nullptr;
		delete p;

	}

	players.clear();

	saveGlobalSettingsToXML();

}

//=========================================================================================================================
void BobsGame::init()
{//=========================================================================================================================

	super::init();

#ifdef _DEBUG
	log.info("BobsGame::init()");
#endif


	//the reason why i have an init function is because i can control the order of the subclass/superclass calling
	//in the regular constructor, it calls the base class first, so it will always be called State->Engine->GameEngine->BobsGame
	//but by using the init function I can call them specifically in any order that I want

  //oh it is also so that i can call init code from multiple constructors, oops


	log.info("Init Assets");
	initAssets();


	//TODO: load music files

	//TODO: load sprite text files regardless of names


	loadGlobalSettingsFromXML();
	loadGameTypesFromXML();
	loadGameSequencesFromXML();

	updateVersion0ToVersion1();



	log.info("Init Player");
	initPlayer();

	//	games.put(randomSeed,ME);
	//	player2 = new Game(this);
	//	player2.controlledByNetwork = true;
	//	games.add(player2);

}


//=========================================================================================================================
void BobsGame::initPlayer()
{//=========================================================================================================================
	for (int i = 0; i<players.size(); i++)
	{
		PuzzlePlayer *p = players.get(i);

		if (p->gameLogic != nullptr)
		{
			p->gameLogic->deleteAllCaptions();
		}
		delete p->gameLogic;
		p->gameLogic = nullptr;
		delete p;

		//for simulator connection
		//if(friend==null&&connection!=null)BobsGame::setConnection(connection);

		//		nD.setGame(bobsgame);
		//		this.nD = null;
		//
		//		if(isNetworkGame())
		//		{
		//			if(connection!=null)setConnection(null);
		//			if(friend!=null)
		//			{
		//				friend.setGameToForwardPacketsTo(null);
		//				friend = null;
		//			}
		//		}

	}
	players.clear();

	PuzzlePlayer *p = new PuzzlePlayer(new GameLogic(this, -1));
	
	p->useKeyboard = true;
	if (getControlsManager()->gameControllers.size() > 0)p->gameController = getControlsManager()->gameControllers.get(0);
	players.add(p);

	if (currentRoom == nullptr)currentRoom = new Room();

	//randomSeed = p->game->randomSeed;
	//originalSettings = p->game->getCurrentGameType();
}


//=========================================================================================================================
bool BobsGame::isMultiplayer()
{//=========================================================================================================================
	if (networkMultiplayer)return true;
	if (localMultiplayer)return true;
	if (players.size() > 1)return true;
	return false;
}




//=========================================================================================================================
bool BobsGame::isNetworkGame()
{//=========================================================================================================================
	for (int i = 0; i < players.size(); i++)
	{
		if (players.get(i)->isNetworkPlayer())return true;
	}
	if (networkMultiplayer)return true;
	return false;
}



//=========================================================================================================================
void BobsGame::initAssets()
{//=========================================================================================================================

	log.info("Loading icons");
	keyboardTexture = GLUtils::getTextureFromPNG("data/theme/keyboard.png");
	controllerTexture = GLUtils::getTextureFromPNG("data/theme/controller.png");
	controllerIconTexture = GLUtils::getTextureFromPNG("data/theme/controllerIcon.png");
	keyboardIconTexture = GLUtils::getTextureFromPNG("data/theme/keyboardIcon.png");
	onlineTexture = GLUtils::getTextureFromPNG("data/theme/online.png");
	networkIconTexture = GLUtils::getTextureFromPNG("data/theme/networkIcon.png");
	gearsTexture = GLUtils::getTextureFromPNG("data/theme/gears.png");
	chartTexture = GLUtils::getTextureFromPNG("data/theme/chart.png");

	log.info("Loading frame");
	upperLeft = GLUtils::getTextureFromPNG("data/frame/frame1-ul.png");
	top = GLUtils::getTextureFromPNG("data/frame/frame1-u.png");
	upperRight = GLUtils::getTextureFromPNG("data/frame/frame1-ur.png");
	left = GLUtils::getTextureFromPNG("data/frame/frame1-l.png");
	right = GLUtils::getTextureFromPNG("data/frame/frame1-r.png");
	lowerLeft = GLUtils::getTextureFromPNG("data/frame/frame1-dl.png");
	bottom = GLUtils::getTextureFromPNG("data/frame/frame1-d.png");
	lowerRight = GLUtils::getTextureFromPNG("data/frame/frame1-dr.png");

	log.info("Loading sprites");





	//load all txt files from sprites folder
	string spriteFolderString = Main::getPath() + "data/sprite/";
	Path spriteFolderPath(spriteFolderString);
	File spriteFolderPathDir(spriteFolderPath);
	if (spriteFolderPathDir.exists() == false)spriteFolderPathDir.createDirectories();
	vector<string> files;
	spriteFolderPathDir.list(files);
	vector<string>::iterator it = files.begin();
	for (; it != files.end(); ++it)
	{
		//cout << *it << endl;
		string name = *it;
		if (name.find(".txt") != string::npos)
		{
			string nameWithoutExtension = name.substr(0, name.find(".txt"));
			loadedSprites.add(spriteManager->preloadSpriteFromFile(nameWithoutExtension));
		}
	}



	//spriteManager.preloadSpriteFromFile("bobsGameLogoSmall");



	//TODO load sounds/index.txt
	//for each line, load ogg file


	ArrayList<string>* stringList = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/sounds/index.txt");


	if (stringList->size() > 0)
	{
		for (int i = 0; i < stringList->size(); i++)
		{
			string s = stringList->get(i);

			if (s.length() > 0)
			{
				//Sound *sound =
                new Sound(this, "data/sounds/" + s);
				//sound.byteData = dataFile.readBytes();
			}
		}
	}
	music = new Music(this, "data/music/slick_v10.ogg");


}



//=========================================================================================================================
Sprite* BobsGame::getSpriteFromName(const string& name)
{//=========================================================================================================================


	return spriteManager->getSpriteByName(name);

}

//=========================================================================================================================
GameLogic* BobsGame::getPlayer1Game()
{//=========================================================================================================================
	return players.get(0)->gameLogic;
}
//=========================================================================================================================
PuzzlePlayer* BobsGame::getPlayer1()
{//=========================================================================================================================
	return players.get(0);
}
//=========================================================================================================================
void BobsGame::setBobsGameFBOSize()
{//=========================================================================================================================
	//let's size the game FBO to the board size, which means sizing the bloom FBO and others

	//calculate the needed board size
	//if FBOs are not that size, resize the FBOs, that also means rendering the game into that size

	//draw each game to an FBO, then draw it to the main screen

	//make this into a function so that i can apply it to the custom game preview

	//ok, so when i calculate the playing field size, let's do that here instead of inside the game itself, and then set the internal size within the game
	//then we can do things like if(preview) use this size, if(singleplayer) fullscreen, if multiplayer do this size

	float w = getPlayer1Game()->playingFieldX1 - getPlayer1Game()->playingFieldX0;
	float h = getPlayer1Game()->playingFieldY1 - getPlayer1Game()->playingFieldY0;

	if (GLUtils::bobsGameFBO_Width != w || GLUtils::bobsGameFBO_Height != h)
	{
		GLUtils::resizeBobsGameFBO(w, h);
	}
}

//=========================================================================================================================
void BobsGame::renderGameIntoFBO(GameLogic* g, bool useColorFilter)
{//=========================================================================================================================


	GLUtils::bindFBO(GLUtils::bobsGame_mainGameFBO);
	GLUtils::drawIntoFBOAttachment(0); //draw to mainGameFBO texture
	GLUtils::setBobsGameMainFBOFilterViewport();


	//clear the main game FBO since we used it to draw the previous game
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	g->renderBackground();//draw the background into the main fbo


	//render the playing field blocks to a FBO
	//draw the FBO to the screen with blur shader and 50% alpha
	//draw the FBO to the screen
	if (GLUtils::useShaders)
	{
		GLUtils::drawIntoFBOAttachment(1); // draw to bloom mask texture
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//this is correct
		glClear(GL_COLOR_BUFFER_BIT);
	}


	g->renderBlocks(); //draw blocks into bloom mask texture


	if (GLUtils::useShaders)
	{

		GLUtils::bindFBO(GLUtils::bobsGame_bloomFBO);
		//GLUtils::drawIntoFBOAttachment(0);
		GLUtils::setBloomViewport();


		glDisable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glDepthMask(false);


		GLUtils::drawIntoFBOAttachment(1);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//this is correct
		glClear(GL_COLOR_BUFFER_BIT);//clear both ping pong textures


		GLUtils::drawIntoFBOAttachment(0); //draw to bloom FBO texture 0
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//this is correct
		glClear(GL_COLOR_BUFFER_BIT);



		GLUtils::useShader(GLUtils::bloomMaskShader);

		glBindTexture(GL_TEXTURE_2D, GLUtils::bobsGame_mainGameFBO_Texture_Attachment1_BloomMask);//has the blocks in it
		GLUtils::setShaderVar1i(GLUtils::bloomMaskShader, (char*)"u_texture0", 0);
		float threshold = 0.1f;
		GLUtils::setShaderVar2f(GLUtils::bloomMaskShader, (char*)"treshold", threshold, 1.0f / (1.0f - threshold));

		GLUtils::drawTexture(GLUtils::bobsGame_mainGameFBO_Texture_Attachment1_BloomMask, 0, 1, 0, 1, -1, 1, -1, 1, 1.0f, GLUtils::DEFAULT_BLOOM_FBO_FILTER);//draw the blocks into ping pong 0

		GLUtils::useShader(0);



		int blurPasses = g->currentGameType->bloomTimes;
		for (int n = 0; n < blurPasses; n++)//blur the blocks
		{
			// horizontal
			GLUtils::drawIntoFBOAttachment(1);
			{
				GLUtils::useShader(GLUtils::gaussianShader);
				{
					GLUtils::setShaderVar2f(GLUtils::gaussianShader, (char*)"size", GLUtils::bobsGameFBO_Width*GLUtils::BLOOM_FBO_SCALE, GLUtils::bobsGameFBO_Height*GLUtils::BLOOM_FBO_SCALE);
					GLUtils::setShaderVar2f(GLUtils::gaussianShader, (char*)"dir", 1.0f, 0.0f);
					GLUtils::drawTexture(GLUtils::bobsGame_bloomFBO_PingPongBlur_Texture_Attachment0, 0, 1, 0, 1, -1, 1, -1, 1, 1.0f, GLUtils::DEFAULT_BLOOM_FBO_FILTER);
				}
				GLUtils::useShader(0);
			}

			// vertical
			GLUtils::drawIntoFBOAttachment(0);
			{
				GLUtils::useShader(GLUtils::gaussianShader);
				{
					GLUtils::setShaderVar2f(GLUtils::gaussianShader, (char*)"size", GLUtils::bobsGameFBO_Width*GLUtils::BLOOM_FBO_SCALE, GLUtils::bobsGameFBO_Height*GLUtils::BLOOM_FBO_SCALE);
					GLUtils::setShaderVar2f(GLUtils::gaussianShader, (char*)"dir", 0.0f, 1.0f);
					GLUtils::drawTexture(GLUtils::bobsGame_bloomFBO_PingPongBlur_Texture_Attachment1, 0, 1, 0, 1, -1, 1, -1, 1, 1, GLUtils::DEFAULT_BLOOM_FBO_FILTER);

				}
				GLUtils::useShader(0);
			}
		}



		GLUtils::bindFBO(GLUtils::bobsGame_mainGameFBO);
		GLUtils::drawIntoFBOAttachment(0); //draw to mainFBO texture 0, has the playing field
		GLUtils::setBobsGameMainFBOFilterViewport();


		glEnable(GL_BLEND);
		GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);


		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, GLUtils::bobsGame_bloomFBO_PingPongBlur_Texture_Attachment0);//has blurred blocks in it

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, GLUtils::bobsGame_mainGameFBO_Texture_Attachment1_BloomMask);//has original blocks in it


		float bloomIntensity = g->currentGameType->bloomIntensity;


//		float w = g->playingFieldX1 - g->playingFieldX0;
//		float h = g->playingFieldY1 - g->playingFieldY0;
//		log.debug(to_string(w));
//		log.debug(to_string(h));
//		log.debug(to_string(GLUtils::bobsGameFBO_Width));
//		log.debug(to_string(GLUtils::bobsGameFBO_Height));

		GLUtils::useShader(GLUtils::bloomShader);//draw the blurred and original blocks with bloom on top of shaders and playing field
		{
			GLUtils::setShaderVar1f(GLUtils::bloomShader, (char*)"OriginalIntensity", 0.8f);
			GLUtils::setShaderVar1f(GLUtils::bloomShader, (char*)"BloomIntensity", bloomIntensity);
			GLUtils::setShaderVar1i(GLUtils::bloomShader, (char*)"u_texture0", 0);//original blocks
			GLUtils::setShaderVar1i(GLUtils::bloomShader, (char*)"u_texture1", 1);//blurred blocks
			GLUtils::drawTexture(GLUtils::bobsGame_mainGameFBO_Texture_Attachment1_BloomMask, 0.0f, 1.0f, 1.0f, 0.0f, 0, GLUtils::bobsGameFBO_Width, 0, GLUtils::bobsGameFBO_Height, 1.0f, GLUtils::DEFAULT_BLOOM_FBO_FILTER);
		}
		GLUtils::useShader(0);


		//disable texture2D on texture unit 1
		glActiveTexture(GL_TEXTURE1);
		glDisable(GL_TEXTURE_2D);

		//switch back to texture unit 0
		glActiveTexture(GL_TEXTURE0);
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);


		GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}

	g->renderForeground();


	if (useColorFilter)
	{
		//let's now draw the main fbo into the mask fbo with the color shader, then back to the main fbo
		GLUtils::bindFBO(GLUtils::bobsGame_mainGameFBO);
		GLUtils::drawIntoFBOAttachment(1);
		GLUtils::setBobsGameMainFBOFilterViewport();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		GLUtils::drawTexture(GLUtils::bobsGame_mainGameFBO_Texture_Attachment0, 0.0f, 1.0f, 1.0f, 0.0f, 0, GLUtils::bobsGameFBO_Width, 0, GLUtils::bobsGameFBO_Height, 1.0f, GLUtils::DEFAULT_ND_FBO_FILTER);
		GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		GLUtils::drawIntoFBOAttachment(0);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (GLUtils::useShaders)
		{
			GLUtils::useShader(GLUtils::colorShader);

			GlobalSettings gs;

			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameHue", gs.hue);//ignore global settings and use default so custom games dont use user settings and are more accurate
			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameSaturation", gs.saturation);
			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameBrightness", gs.brightness);
			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameContrast", gs.contrast);
			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameGamma", gs.gamma);
			GLUtils::setShaderVar1i(GLUtils::colorShader, (char*)"Tex0", 0);
		}
		GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		GLUtils::drawTexture(GLUtils::bobsGame_mainGameFBO_Texture_Attachment1_BloomMask, 0.0f, 1.0f, 1.0f, 0.0f, 0, GLUtils::bobsGameFBO_Width, 0, GLUtils::bobsGameFBO_Height, 1.0f, GLUtils::DEFAULT_ND_FBO_FILTER);
		GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (GLUtils::useShaders)
		{
			GLUtils::useShader(0);
		}

		GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}


}

//=========================================================================================================================
void BobsGame::drawBobsGameFBO(float x0, float x1, float y0, float y1)
{//=========================================================================================================================

	GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	//GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLUtils::drawTexture(GLUtils::bobsGame_mainGameFBO_Texture_Attachment0, 0.0f, 1.0f, 1.0f, 0.0f, x0, x1, y0, y1, 1.0f, GLUtils::DEFAULT_ND_FBO_FILTER);

	GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//int clearToggle = 0;
//
//#ifdef _DEBUG
//if (Main::getMain()->controlsManager->key_NUM1_Pressed())
//{
//	clearToggle++;
//	if (clearToggle > 4)clearToggle = 0;
//	log.debug("ClearToggle: " + to_string(clearToggle));
//}
//
//if (clearToggle == 0)
//{
//
//}
//if (clearToggle == 1)
//{
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//	glClear(GL_COLOR_BUFFER_BIT);
//}
//if (clearToggle == 2)
//{
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT);
//}
//if (clearToggle == 3)
//{
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}
//if (clearToggle == 4)
//{
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}
//
//#endif
//=========================================================================================================================
void BobsGame::render()
{//=========================================================================================================================



	GLUtils::bindFBO(GLUtils::preColorFilterFBO);
	GLUtils::drawIntoFBOAttachment(0); //draw to nD FBO screen texture
	GLUtils::setPreColorFilterViewport();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//this is correct
	glClear(GL_COLOR_BUFFER_BIT);


	if (renderMenus() == true)
	{

		//render game captions
//		{
//			//super::render();
//			captionManager->render(RenderOrder::ABOVE);
//			captionManager->render(RenderOrder::ABOVE_TOP);
//			captionManager->render(RenderOrder::OVER_TEXT);
			captionManager->render(RenderOrder::OVER_GUI);
//		}

		//--------------------------
		// draw MAIN FBO texture into SCREEN BUFFER
		//--------------------------
		GLUtils::bindFBO(0); //set the framebuffer back to the screen buffer
		GLUtils::setRealWindowViewport();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//this is correct
		glClear(GL_COLOR_BUFFER_BIT);


		GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		GLUtils::drawTexture(GLUtils::preColorFilterFBO_Texture_Attachment0, 0, 1, 1, 0, 0, (float)(GLUtils::getRealWindowWidth()), 0, (float)(GLUtils::getRealWindowHeight()), 1.0f, GLUtils::DEFAULT_ND_FBO_FILTER);
		GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}
	else
	{

		if (GLUtils::useShaders)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glEnable(GL_DEPTH_TEST);


			bgShaderFBOTextureToggle = !bgShaderFBOTextureToggle;

			GLUtils::bindFBO(GLUtils::bobsGame_bgShaderFBO);
			if (bgShaderFBOTextureToggle)
			{
				GLUtils::drawIntoFBOAttachment(0);
			}
			else
			{
				GLUtils::drawIntoFBOAttachment(1);
			}


			GLUtils::setShaderViewport();
			float tempDrawScale = GLUtils::globalDrawScale;
			GLUtils::globalDrawScale = 1.0f;


			glActiveTexture(GL_TEXTURE1);
			glEnable(GL_TEXTURE_2D);

			if (bgShaderFBOTextureToggle)
			{
				glBindTexture(GL_TEXTURE_2D, GLUtils::bobsGame_bgShaderFBO_Texture_Attachment1);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, GLUtils::bobsGame_bgShaderFBO_Texture_Attachment0);
			}

			glActiveTexture(GL_TEXTURE0);
			glEnable(GL_TEXTURE_2D);


			//clear the shader bg
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//this is correct
			glClear(GL_COLOR_BUFFER_BIT);



			long long startTime = timeRenderBegan;
			long long currentTime = System::currentHighResTimer();
			int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

			float time = (float)(ticksPassed / 2000.0f);


			int shaderInt = GLUtils::bgShaders.get(shaderCount)->value();

			GLUtils::useShader(shaderInt);
			GLUtils::setShaderVar2f(shaderInt, (char*)"resolution", (float)GLUtils::getViewportWidth()*GLUtils::SHADER_FBO_SCALE, (float)GLUtils::getViewportHeight()*GLUtils::SHADER_FBO_SCALE);
			GLUtils::setShaderVar2f(shaderInt, (char*)"mouse", 0.5f, 0.5f);
			GLUtils::setShaderVar1f(shaderInt, (char*)"time", time);
			GLUtils::setShaderVar1i(shaderInt, (char*)"tex0", 0);
			GLUtils::setShaderVar1i(shaderInt, (char*)"backbuffer", 1);
			GLUtils::setShaderVar1i(shaderInt, (char*)"bb", 1);
			//GLUtils.setShaderVar1i(GLUtils.fractalShader, "tex1"), 1);

			GLUtils::drawFilledRect(255, 255, 255, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f);

			GLUtils::useShader(0);


			glDisable(GL_DEPTH_TEST);

			//disable texture2D on texture unit 1
			glActiveTexture(GL_TEXTURE1);
			glDisable(GL_TEXTURE_2D);

			//switch back to texture unit 0
			glActiveTexture(GL_TEXTURE0);
			glDisable(GL_TEXTURE_2D);


			GLUtils::bindFBO(GLUtils::preColorFilterFBO);
			GLUtils::drawIntoFBOAttachment(0); //draw to nD FBO screen texture
			GLUtils::setPreColorFilterViewport();
			GLUtils::globalDrawScale = tempDrawScale;

			//clear the preColor FBO
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);


			if (bgShaderFBOTextureToggle)
			{
				GLUtils::drawTexture(GLUtils::bobsGame_bgShaderFBO_Texture_Attachment0, 0.0f, 1.0f, 1.0f, 0.0f, 0, (float)getWidth(), 0, (float)getHeight(), 1.0f, GLUtils::DEFAULT_SHADER_FBO_FILTER);
			}
			else
			{
				GLUtils::drawTexture(GLUtils::bobsGame_bgShaderFBO_Texture_Attachment1, 0.0f, 1.0f, 1.0f, 0.0f, 0, (float)getWidth(), 0, (float)getHeight(), 1.0f, GLUtils::DEFAULT_SHADER_FBO_FILTER);
			}

			//draw transparent black to darken background
			GLUtils::drawFilledRect(0, 0, 0, 0, (float)getWidth(), 0, (float)getHeight(), 0.3f);
		}


		setBobsGameFBOSize();


		for (int i = 0; i < players.size(); i++)
		{

			PuzzlePlayer *p = players.get(i);
			GameLogic *g = p->gameLogic;

			//render into mainGameFBO
			renderGameIntoFBO(g, false);

			//draw the mainGameFBO to the preColorFilterFBO in the correct place with correct size
			GLUtils::bindFBO(GLUtils::preColorFilterFBO);
			GLUtils::drawIntoFBOAttachment(0);
			GLUtils::setPreColorFilterViewport();

			drawBobsGameFBO(g->playingFieldX0, g->playingFieldX1, g->playingFieldY0, g->playingFieldY1);
		}


		//--------------------------
		//set main FBO
		//--------------------------

		GLUtils::bindFBO(GLUtils::postColorFilterFBO); //set the framebuffer object to the MAIN FBO
		GLUtils::drawIntoFBOAttachment(0); //set which framebuffer object to draw into (whatever buffer is set with glBindFramebuffer)

		//--------------------------
		//set main viewport
		//--------------------------
		GLUtils::setPostColorFilterViewport();

		//--------------------------
		// draw ND FBO texture into MAIN FBO
		//--------------------------

		if (GLUtils::useShaders)
		{
			GLUtils::useShader(GLUtils::colorShader);

			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameHue", globalSettings->hue);
			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameSaturation", globalSettings->saturation);
			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameBrightness", globalSettings->brightness);
			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameContrast", globalSettings->contrast);
			GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameGamma", globalSettings->gamma);
			GLUtils::setShaderVar1i(GLUtils::colorShader, (char*)"Tex0", 0);
		}


		GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		GLUtils::drawTexture(GLUtils::preColorFilterFBO_Texture_Attachment0, 0.0f, 1.0f, 1.0f, 0.0f, 0, (float)(GLUtils::getViewportWidth()), 0, (float)(GLUtils::getViewportHeight()), 1.0f, GLUtils::DEFAULT_ND_FBO_FILTER);
		GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		if (GLUtils::useShaders)
		{
			GLUtils::useShader(0);
		}

		//render game captions
		{
			//super::render();
			captionManager->render(RenderOrder::ABOVE);
			captionManager->render(RenderOrder::ABOVE_TOP);
			captionManager->render(RenderOrder::OVER_TEXT);
			captionManager->render(RenderOrder::OVER_GUI);
		}

		for (int i = 0; i < players.size(); i++)
		{
			PuzzlePlayer *p = players.get(i);

			if (p->gameLogic->pauseMiniMenuShowing)playerPauseMiniMenuRender(p, p->gameLogic->playingFieldX0, p->gameLogic->playingFieldX1, p->gameLogic->playingFieldY0, p->gameLogic->playingFieldY1);;
		}


		if (pauseMenuShowing == true)
		{
			pauseMenuRender();
		}

		if(voteMenu!=nullptr)
		{
			voteMenu->render(GLUtils::getViewportHeight()/2);
		}

		//--------------------------
		// draw MAIN FBO texture into SCREEN BUFFER
		//--------------------------
		GLUtils::bindFBO(0); //set the framebuffer back to the screen buffer
		GLUtils::setRealWindowViewport();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); //this fixes the small shadow problems, and also makes the doorknob glow brighter.
		GLUtils::drawTexture(GLUtils::postColorFilterFBO_Texture_Attachment0, 0, 1, 1, 0, 0, (float)(GLUtils::getRealWindowWidth()), 0, (float)(GLUtils::getRealWindowHeight()), 1.0f, GLUtils::DEFAULT_ND_FBO_FILTER);
		GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}

}


//=========================================================================================================================
void BobsGame::debugKeys()
{//=========================================================================================================================



	if (getControlsManager()->key_F1_Pressed())
	{
		shaderCount++;
		if (shaderCount >= GLUtils::bgShaderCount)shaderCount = 0;
		log.info("Shader: " + to_string(shaderCount));
		Console::add(string("Shader: ") + to_string(shaderCount), 10000);

		getPlayer1Game()->updateCaptions();
	}

#ifdef _DEBUG
	if (getControlsManager()->key_F2_Pressed())
	{
		getPlayer1Game()->changeGame();
		getPlayer1Game()->updateCaptions();
	}

	if (getControlsManager()->key_1_Pressed() == true)
	{
		globalSettings->hue -= 0.1f;
		Console::debug(string("Hue: ") + to_string(globalSettings->hue), 1000);
	}

	if (getControlsManager()->key_2_Pressed() == true)
	{
		globalSettings->hue += 0.1f;
		Console::debug(string("Hue: ") + to_string(globalSettings->hue), 1000);
	}

	if (getControlsManager()->key_3_Pressed() == true)
	{
		globalSettings->contrast -= 0.1f;
		Console::debug(string("Contrast: ") + to_string(globalSettings->contrast), 1000);
	}

	if (getControlsManager()->key_4_Pressed() == true)
	{
		globalSettings->contrast += 0.1f;
		Console::debug(string("Contrast: ") + to_string(globalSettings->contrast), 1000);
	}

	if (getControlsManager()->key_5_Pressed() == true)
	{
		globalSettings->
			brightness -= 0.1f;
		Console::debug(string("Brightness: ") + to_string(globalSettings->brightness), 1000);
	}

	if (getControlsManager()->key_6_Pressed() == true)
	{
		globalSettings->brightness += 0.1f;
		Console::debug(string("Brightness: ") + to_string(globalSettings->brightness), 1000);
	}

	if (getControlsManager()->key_7_Pressed() == true)
	{
		globalSettings->saturation -= 0.1f;
		Console::debug(string("Saturation: ") + to_string(globalSettings->saturation), 1000);
	}

	if (getControlsManager()->key_8_Pressed() == true)
	{
		globalSettings->saturation += 0.1f;
		Console::debug(string("Saturation: ") + to_string(globalSettings->saturation), 1000);
	}

	if (getControlsManager()->key_9_Pressed() == true)
	{
		globalSettings->gamma -= 0.1f;
		Console::debug(string("Gamma: ") + to_string(globalSettings->gamma), 1000);
	}

	if (getControlsManager()->key_0_Pressed() == true)
	{
		globalSettings->gamma += 0.1f;
		Console::debug(string("Gamma: ") + to_string(globalSettings->gamma), 1000);
	}

	if (getControlsManager()->key_BACKSPACE_Pressed() == true)
	{
		globalSettings->hue = 1.5f;
		globalSettings->saturation = 1.2f;
		globalSettings->brightness = 1.0f;
		globalSettings->contrast = 1.2f;
		globalSettings->gamma = 1.0f;
		Console::debug(string("Hue: ") + to_string(globalSettings->hue) + string(" | Saturation: ") + to_string(globalSettings->saturation) + string(" | Brightness: ") + to_string(globalSettings->brightness) + string(" | Contrast: ") + to_string(globalSettings->contrast) + string(" | Gamma: ") + to_string(globalSettings->gamma), 1000);
	}

#endif

}




//=========================================================================================================================
void BobsGame::update()
{//=========================================================================================================================

	if(music->isPlaying()==false)
	{
		music->play();
	}




	debugKeys();

	//super::update();
	{
		captionManager->update();
		audioManager->update();
		spriteManager->update();
	}


	getGameTypesAndSequencesFromServer();



	if (updateMenus() == true)
	{
		return;
	}



	if(pauseMenuShowing==true)
	{
		pauseMenuUpdate();

		return;
	}



	for (int i = 0; i < players.size(); i++)
	{
		PuzzlePlayer *p = players.get(i);

		GameLogic *g = p->gameLogic;


		//actual game update
		g->update(p,i,players.size());





		//				if (g->lose || g->win)
		//				{
		//					if (currentTime - winOrLoseTime > 5000)
		//					{
		//						if (getControlsManager().BUTTON_SPACE_PRESSED)
		//						{
		//							newGame();
		//						}
		//					}
		//				}
		//				else
		//				{
		//					winOrLoseTime = currentTime;
		//				}

	}

	bool gameOver = false;


	if (players.size() == 1 && players.get(0)->gameLogic->complete)
	{
		gameOver = true;
	}

	bool allPlayersDead = true;
	for (int i = 0; i < players.size(); i++)
	{
		PuzzlePlayer *p = players.get(i);
		if (p->gameLogic->died == false)
		{
			allPlayersDead = false;
		}
	}
	if (allPlayersDead)
	{
		gameOver = true;
	}


	if (currentRoom->multiplayer_GameEndsWhenOnePlayerRemains)
	{
		int alivePlayers = 0;
		for (int i = 0; i < players.size(); i++)
		{
			PuzzlePlayer *p = players.get(i);
			if (p->gameLogic->died == false)
			{
				alivePlayers++;
			}
		}

		if (alivePlayers == 1)
		{
			for (int i = 0; i < players.size(); i++)
			{
				PuzzlePlayer *p = players.get(i);
				if (p->gameLogic->died == false)
				{
					p->gameLogic->won = true;
				}
			}
			gameOver = true;
		}
	}


	if (currentRoom->multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel)
	{

		bool someoneWon = false;
		for (int i = 0; i < players.size(); i++)
		{
			PuzzlePlayer *p = players.get(i);
			if (p->gameLogic->complete == true)
			{
				someoneWon = true;
			}
		}

		if (someoneWon)
		{
			for (int i = 0; i < players.size(); i++)
			{
				PuzzlePlayer *p = players.get(i);
				if (p->gameLogic->complete == false)
				{
					p->gameLogic->lost = true;
				}
			}
			gameOver = true;
		}
	}


	if(gameOver)
	{

		sendGameStatsToServer();

		//if single game, check youVoted=="none"
		//if sequence, check
		//if connected to server, make menu to vote up or down
		//has to be single player game because its tied to account


		if(doVoting()==false)
		{

			//if connected to server and authorized
			//if game sequence only has one game type
			//ask to rate game

			if (pressEnterToRestartCaption == nullptr)
			{
				string text = "Press Enter or Start to restart";

				if (isNetworkGame() || players.size() > 1)
				{
					text = "Press Enter or Start to return to lobby";
				}

				pressEnterToRestartCaption = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, getHeight() - 100, -1, text, BobFont::ttf_24, BobColor::white);
				pressEnterToRestartCaption->flashing = true;
				pressEnterToRestartCaption->flashingTicksPerFlash = 2000;
			}

			if (getControlsManager()->miniGame_START_Pressed())
			{
				sentStats = false;

				if (players.size() == 1)
				{
					GameSequence *gs = getPlayer1Game()->currentGameSequence;
					initPlayer();
					getPlayer1Game()->currentGameSequence = gs;
				}
				else
				{
					initPlayer();

					if (isNetworkGame())
					{
						networkMultiplayerLobbyMenuShowing = true;
					}
					else
					{
						localMultiplayerPlayerJoinMenuShowing = true;
					}
				}

				if (pressEnterToRestartCaption != nullptr)
				{
					pressEnterToRestartCaption->setToBeDeletedImmediately();
					pressEnterToRestartCaption = nullptr;
				}
			}
		}
	}
}

#include <chrono>

//=========================================================================================================================
void BobsGame::sendGameStatsToServer()
{//=========================================================================================================================

	if (sentStats)return;

	if (getServerConnection()->getConnectedToServer_S() == false)return;

	if (getServerConnection()->getAuthorizedOnServer_S() == false)return;


	{
		
		//if (players.size() == 1 || currentRoom->tournamentRoom)
		{

			//do stats
			//user stats
			//tell server all game information
			//even include local multiplayer why not
			//include it in "games played" and "time played"

			for (int i = 0; i < players.size(); i++)
			{
				PuzzlePlayer *p = players.get(i);
				if (p->isNetworkPlayer() == false)
				{

					GameLogic *g = p->gameLogic;

					BobsGameGameStats s;
					s.userName = g->getEngine()->getUserName_S();
					s.userID = g->getEngine()->getUserID_S();

					if (g->currentGameSequence->gameTypes.size() == 1)
					{
						s.isGameTypeOrSequence = "GameType";
						s.gameTypeName = g->currentGameSequence->gameTypes.get(0)->name;
						s.gameTypeUUID = g->currentGameSequence->gameTypes.get(0)->uuid;
					}
					else
					{
						s.isGameTypeOrSequence = "GameSequence";
						s.gameSequenceName = g->currentGameSequence->name;
						s.gameSequenceUUID = g->currentGameSequence->uuid;
					}

					s.gameTypeEndedOnName = g->currentGameType->name;
					s.gameTypeEndedOnUUID = g->currentGameType->uuid;
					s.difficultyName = g->currentGameSequence->currentDifficultyName;
					s.won = g->won;
					s.lost = g->lost;
					s.died = g->died;
					s.complete = g->complete;
					s.isLocalMultiplayer = localMultiplayer;
					s.isNetworkMultiplayer = networkMultiplayer;
					s.numPlayers = players.size();
					s.level = g->currentLevel;
					s.timeLasted = g->totalTicksPassed;
					s.timeStarted = g->timeStarted;
					if(g->timeEnded==0)
					{
						chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
						g->timeEnded = (long long)ms.count();
					}
					s.timeEnded = g->timeEnded;
					s.blocksMade = g->blocksMadeTotal;
					s.piecesMade = g->piecesMadeTotal;
					s.blocksCleared = g->blocksClearedTotal;
					s.piecesPlaced = g->piecesPlacedTotal;
					s.combosMade = g->totalCombosMade;
					s.biggestCombo = g->biggestComboChain;
					s.maxPlayers = currentRoom->maxPlayers;
					s.privateRoom = currentRoom->privateRoom;
					s.tournamentRoom = currentRoom->tournamentRoom;
					s.hostUserID = currentRoom->hostUserID;
					s.multiplayer_AllowDifferentDifficulties = currentRoom->multiplayer_AllowDifferentDifficulties;
					s.multiplayer_AllowDifferentGameSequences = currentRoom->multiplayer_AllowDifferentGameSequences;
					s.multiplayer_GameEndsWhenOnePlayerRemains = currentRoom->multiplayer_GameEndsWhenOnePlayerRemains;
					s.multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel = currentRoom->multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel;
					s.multiplayer_DisableVSGarbage = currentRoom->multiplayer_DisableVSGarbage;

					s.allFrameStatesZipped = FrameState::getFrameStatesAsBase64GZippedXML(g->framesArray);

					for (int n = 0; n < players.size(); n++)
					{
						PuzzlePlayer *pp = players.get(n);
						long long playerUserID = -1;
						if (pp->isNetworkPlayer() && pp->peerConnection != nullptr)
							playerUserID = pp->peerConnection->peerUserID;
						else playerUserID = g->getEngine()->getUserID_S();

						string playerUserName = "Local Player";
						if (pp->isNetworkPlayer() && pp->peerConnection != nullptr)
							playerUserName = pp->peerConnection->getUserName();

						if(players.size()==1)playerUserName = g->getEngine()->getUserName_S();

						string statusString = "";
						if (pp->gameLogic->won)statusString = "won";
						if (pp->gameLogic->died)statusString = "died";
						if (pp->gameLogic->lost)statusString = "lost";
						s.playerIDsCSV += to_string(playerUserID) + ":" +"`"+playerUserName+"`"+":"+ statusString + ",";//id:`userName`:lost,id:`userName`:won,:
					}

					string statsString = s.encode();

					BobsGameGameStats *d = new BobsGameGameStats(statsString);
					//d->decode(statsString);
					//log.info(statsString);

					getServerConnection()->sendBobsGameGameStats_S(statsString);

				}
			}

			sentStats = true;

		}
	}


}


//=========================================================================================================================
bool BobsGame::doVoting()
{//=========================================================================================================================

	if (getServerConnection()->getConnectedToServer_S() == false)return false;

	if (getServerConnection()->getAuthorizedOnServer_S() == false)return false;

	if (players.size() > 1)return false;


	if (voting == false)
	{
		GameSequence *gs = getPlayer1Game()->currentGameSequence;
		if (gs->gameTypes.size() == 1)
		{
			GameType *g = gs->gameTypes.get(0);
			if (g->downloaded==true && g->yourVote == "none")
			{
				if (voteMenu == nullptr)
				{
					voteMenu = new BobMenu(this, "Vote");
					voteMenu->addInfo("Please vote on this game:");
					voteMenu->add("Up");
					voteMenu->add("Down");
				}

			}
			else return false;

		}
		else
		{
			if (gs->downloaded == true && gs->yourVote == "none")
			{
				if (voteMenu == nullptr)
				{
					voteMenu = new BobMenu(this, "Vote");
					voteMenu->addInfo("Please vote on this sequence:");
					voteMenu->add("Up");
					voteMenu->add("Down");
				}

			}
			else return false;
		}

		if (voteMenu != nullptr)
		{
			if (getControlsManager()->miniGame_UP_Pressed())
			{
				voteMenu->up();
			}

			if (getControlsManager()->miniGame_DOWN_Pressed())
			{
				voteMenu->down();
			}

			bool leaveMenu = false;

			bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
			bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
			int mx = getControlsManager()->getMouseX();
			int my = getControlsManager()->getMouseY();
			if (confirm || clicked)
			{

				if (voteMenu->isSelectedID("Up", clicked, mx, my))
				{
					voting = true;
					voteUpDown = true;
				}
				if (voteMenu->isSelectedID("Down", clicked, mx, my))
				{
					voting = true;
					voteUpDown = false;
				}
				leaveMenu = true;
			}

			if (leaveMenu)
			{
				if (voteMenu != nullptr)
				{
					delete voteMenu;
					voteMenu = nullptr;
				}
			}
		}
	}

	if (voting)
	{
		voting = false;

		string vote = "up";
		if (voteUpDown == false)vote = "down";

		if (getPlayer1Game()->currentGameSequence->gameTypes.size() == 1)
		{
			string uuid = getPlayer1Game()->currentGameSequence->gameTypes.get(0)->uuid;
			getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(BobNet::Bobs_Game_GameTypesAndSequences_Vote_Request + "GameType:" + uuid + ":" + vote + ":" + BobNet::endline);
		}
		else
		{
			string uuid = getPlayer1Game()->currentGameSequence->uuid;
			getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(BobNet::Bobs_Game_GameTypesAndSequences_Vote_Request + "GameSequence:" + uuid + ":" + vote + ":" + BobNet::endline);
		}

		if (getPlayer1Game()->currentGameSequence->gameTypes.size() == 1)
		{
			if (voteUpDown)getPlayer1Game()->currentGameSequence->gameTypes.get(0)->yourVote = "up";
			else getPlayer1Game()->currentGameSequence->gameTypes.get(0)->yourVote = "down";
		}
		else
		{
			if (voteUpDown)getPlayer1Game()->currentGameSequence->yourVote = "up";
			else getPlayer1Game()->currentGameSequence->yourVote = "down";
		}

		return true;
	}

	return false;





}

//=========================================================================================================================
void BobsGame::tryToCloseGame()
{//=========================================================================================================================
//
//	if (isNetworkGame())
//	{
//
//		long long startTime = lastTimeTriedToCloseGame;
//		long long currentTime = System::currentHighResTimer();
//		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
//		if (ticksPassed < 5000)
//		{
//			//send "quit" message
//			//TODO: add "lose" to records
//
//			sendForfeit();
//
//		}
//		else
//		{
//			//warn that network game will be forfeit
//			//if try to close again within 5 seconds, close.
//
//			lastTimeTriedToCloseGame = currentTime;
//
//			getCaptionManager()->newManagedCaption(Caption::CENTERED_SCREEN,0,5000,"Network game is in progress! Match will be forfeit. Try again within 5 seconds to confirm.",BobFont::ttf_oswald_16,Color::red);
//		}
//	}
//	else
//	{
//		//nD.setActivated(false);
//	}
}



//=========================================================================================================================
void BobsGame::changeBG()
{//=========================================================================================================================

	//shaderCount++;
	//if(shaderCount>=LWJGLUtils.bgShaderCount)shaderCount=0;

	shaderCount = Math::randLessThan(GLUtils::bgShaderCount);
	//log.debug("Shader: " + to_string(shaderCount));
	//CaptionManager().newManagedCaption(0,0,1000,""+shaderCount,BobFont.font_normal_16_outlined_smooth,BobColor.white,BobColor.black,2.0f);

}



//
////=========================================================================================================================
//BobsGame* BobsGame::getThis()
//{//=========================================================================================================================
//
//	return b;
//
//}
//



void BobsGame::updateControls()
{
	resetPressedButtons();
	setButtonStates();

}

void BobsGame::resetPressedButtons()
{//=========================================================================================================================

	for (int i = 0; i < players.size(); i++)
	{
		PuzzlePlayer *p = players.get(i);
		p->resetPressedButtons();
	}



	getControlsManager()->resetPressedButtons();
}

void BobsGame::setButtonStates()
{//=========================================================================================================================
	for (int i = 0; i < players.size(); i++)
	{
		PuzzlePlayer *p = players.get(i);
		p->setButtonStates();
	}


	getControlsManager()->setButtonStates();



	//puzzlegame

//	if (players.size() == 1)
//	{
//
//		//use MINIGAME controls
//
//		PuzzlePlayer *p = players.get(0);
//
//		if (getControlsManager()->MINIGAME_UP_HELD == true)p->UP_HELD = true;
//		if (getControlsManager()->MINIGAME_DOWN_HELD == true)p->DOWN_HELD = true;
//		if (getControlsManager()->MINIGAME_LEFT_HELD == true)p->LEFT_HELD = true;
//		if (getControlsManager()->MINIGAME_RIGHT_HELD == true)p->RIGHT_HELD = true;
//
//		if (p->allowAnalogControls)
//		{
//			if (getControlsManager()->MINIGAME_ANALOGUP_HELD == true)p->UP_HELD = true;
//			if (getControlsManager()->MINIGAME_ANALOGDOWN_HELD == true)p->DOWN_HELD = true;
//			if (getControlsManager()->MINIGAME_ANALOGLEFT_HELD == true)p->LEFT_HELD = true;
//			if (getControlsManager()->MINIGAME_ANALOGRIGHT_HELD == true)p->RIGHT_HELD = true;
//		}
//		if (getControlsManager()->MINIGAME_RUN_HELD == true)p->ROTATECCW_HELD = true;
//		if (getControlsManager()->MINIGAME_ACTION_HELD == true)p->ROTATECW_HELD = true;
//		if (getControlsManager()->MINIGAME_L_HELD == true)p->HOLDRAISE_HELD = true;
//
//		if (getControlsManager()->miniGame_PAUSE_Pressed() == true)p->PAUSE_PRESSED = true;//doesn't really matter for single player
//		if (getControlsManager()->miniGame_CONFIRM_Pressed() == true)p->CONFIRM_PRESSED = true;//doesn't really matter for single player
//		if (getControlsManager()->miniGame_CANCEL_Pressed() == true)p->CANCEL_PRESSED = true;//doesn't really matter for single player
//
//		if (p->slamWithR)
//		{
//			if (getControlsManager()->MINIGAME_R_HELD == true)p->SLAM_HELD = true;
//		}
//		else
//		{
//			if (getControlsManager()->MINIGAME_R_HELD == true)p->HOLDRAISE_HELD = true;
//		}
//
//		if (p->slamWithY)
//		{
//			if (getControlsManager()->MINIGAME_Y_HELD == true)p->SLAM_HELD = true;
//		}
//
//		if (p->slamWithUp)
//		{
//			if (getControlsManager()->MINIGAME_UP_HELD == true)p->SLAM_HELD = true;
//		}
//		p->setPressedButtons();
//
//	}
//	else
//	if (players.size() > 1)
//	{
	PuzzlePlayer *p;// = players.get(0);

		for (int i = 0; i < players.size();i++)
		{
			p = players.get(i);

			if (p->useKeyboard)
			{
				if (getControlsManager()->KEY_UP_HELD == true)p->UP_HELD = true;
				if (getControlsManager()->KEY_DOWN_HELD == true)p->DOWN_HELD = true;
				if (getControlsManager()->KEY_LEFT_HELD == true)p->LEFT_HELD = true;
				if (getControlsManager()->KEY_RIGHT_HELD == true)p->RIGHT_HELD = true;
				if (getControlsManager()->KEY_SPACE_HELD == true)p->ROTATECW_HELD = true;
				if (getControlsManager()->KEY_LSHIFT_HELD == true)p->ROTATECCW_HELD = true;
				if (getControlsManager()->KEY_LCTRL_HELD == true)p->HOLDRAISE_HELD = true;


				//if (getControlsManager()->KEY_RETURN_HELD == true)p->START_HELD = true;

				if (getControlsManager()->KEY_ESC_HELD == true)p->PAUSE_HELD = true;

				if (getControlsManager()->KEY_RETURN_HELD == true)p->CONFIRM_HELD = true;
				if (getControlsManager()->KEY_SPACE_HELD == true)p->CONFIRM_HELD = true;

				//if (getControlsManager()->KEY_ESC_HELD == true)p->CANCEL_HELD = true;
				if (getControlsManager()->KEY_LSHIFT_HELD == true)p->CANCEL_HELD = true;


				if (p->slamWithUp)
				{
					if (getControlsManager()->KEY_UP_HELD == true)p->SLAM_HELD = true;
				}

				if (p->slamWithR)
				{
					if (getControlsManager()->KEY_LALT_HELD == true)p->SLAM_HELD = true;
				}
				else
				{
					if (getControlsManager()->KEY_LALT_HELD == true)p->HOLDRAISE_HELD = true;
				}
			}

			if (p->gameController!=nullptr)
			{
				GameController *g = p->gameController;

				if (g->UP_HELD == true)p->UP_HELD = true;
				if (g->DOWN_HELD == true)p->DOWN_HELD = true;
				if (g->LEFT_HELD == true)p->LEFT_HELD = true;
				if (g->RIGHT_HELD == true)p->RIGHT_HELD = true;

				if (p->allowAnalogControls)
				{
					if (g->ANALOGUP_HELD == true)p->UP_HELD = true;
					if (g->ANALOGDOWN_HELD == true)p->DOWN_HELD = true;
					if (g->ANALOGLEFT_HELD == true)p->LEFT_HELD = true;
					if (g->ANALOGRIGHT_HELD == true)p->RIGHT_HELD = true;
				}

				if (g->B_HELD == true)p->ROTATECW_HELD = true;
				if (g->A_HELD == true)p->ROTATECCW_HELD = true;
				if (g->L_HELD == true)p->HOLDRAISE_HELD = true;

				if (g->START_HELD == true)p->PAUSE_HELD = true;
				//if (g->START_HELD == true)p->START_HELD = true;
				//if (g->START_HELD == true)p->CONFIRM_HELD = true;
				if (g->A_HELD == true)p->CONFIRM_HELD = true;
				if (g->B_HELD == true)p->CANCEL_HELD = true;

				if (p->slamWithR)
				{
					if (g->R_HELD == true)p->SLAM_HELD = true;
				}
				else
				{
					if (g->R_HELD == true)p->HOLDRAISE_HELD = true;
				}

				if (p->slamWithY)
				{
					if (g->Y_HELD == true)p->SLAM_HELD = true;
				}

				if (p->slamWithUp)
				{
					if (g->UP_HELD == true)p->SLAM_HELD = true;
				}
			}

			p->setPressedButtons();

		}
	}
//}

//=========================================================================================================================
void BobsGame::shakeSmall()
{ //=========================================================================================================================
	//getGameEngine()->getCameraman()->setShakeScreen(300,10,10,60);

}

//=========================================================================================================================
void BobsGame::shakeHard()
{ //=========================================================================================================================
	//getGameEngine()->getCameraman()->setShakeScreen(600,20,20,60);
}

//void BobsGameStadium::shakeSmall()
//{ //=========================================================================================================================
//	getClientGameEngine()->getCameraman()->popZOOMto = getClientGameEngine()->getCameraman()->getZoom() - 0.1f;
//	getClientGameEngine()->getCameraman()->setShakeScreen(300, 2, 2, 30);
//	getClientGameEngine()->getCinematicsManager()->fadeColorFromTransparentToAlphaBackToTransparent(200, 255, 255, 255, 0.5f);
//}
//
//void BobsGameStadium::shakeHard()
//{ //=========================================================================================================================
//	getClientGameEngine()->getCameraman()->popZOOMto = getClientGameEngine()->getCameraman()->getZoom() - 0.5f;
//	getClientGameEngine()->getCameraman()->setShakeScreen(1000, 5, 5, 30);
//	getClientGameEngine()->getCinematicsManager()->fadeColorFromTransparentToAlphaBackToTransparent(200, 255, 255, 255, 0.5f);
//}



//=========================================================================================================================
void BobsGame::loadGameTypesFromXML()
{//=========================================================================================================================
	string userDataPathString = FileUtils::appDataPath + "gameTypes/";
	string builtInDataPathString = Main::getPath() + "data/gameTypes/";
	string downloadedDataPathString = FileUtils::appDataPath + "downloadedGameTypes/";

	Path userDataPath(userDataPathString);
	Path builtInDataPath(builtInDataPathString);
	Path downloadedDataPath(downloadedDataPathString);
	//make sure both directories exist, make them if they don't

	File userDataPathDir(userDataPath);
	File builtInDataPathDir(builtInDataPath);
	File downloadedDataPathDir(downloadedDataPath);

	if (userDataPathDir.exists() == false)userDataPathDir.createDirectories();
	if (builtInDataPathDir.exists() == false)builtInDataPathDir.createDirectories();
	if (downloadedDataPathDir.exists() == false)downloadedDataPathDir.createDirectories();

	loadedGameTypes.clear();


	bool found = false;

	//show all files in dir
	for (int i = 0; i<3; i++)
	{
		vector<string> files;
		if (i == 0)builtInDataPathDir.list(files);
		if (i == 1)userDataPathDir.list(files);
		if (i == 2)downloadedDataPathDir.list(files);
		vector<string>::iterator it = files.begin();
		for (; it != files.end(); ++it)
		{
			//cout << *it << endl;
			string name = *it;
			if (name.find(".xml") != string::npos)
			{
				if(i==0)found = true;

				string fullPathName;
				if (i == 0)fullPathName = builtInDataPathString + name;
				if (i == 1)fullPathName = userDataPathString + name;
				if (i == 2)fullPathName = downloadedDataPathString + name;

				ifstream t(fullPathName);
				string str;

				t.seekg(0, ios::end);
				str.reserve((size_t)t.tellg());
				t.seekg(0, ios::beg);

				str.assign((istreambuf_iterator<char>(t)),
					istreambuf_iterator<char>());

				stringstream ss;
				ss << str;
				boost::archive::xml_iarchive ia(ss);

				GameType gt;
				try
				{
					ia >> BOOST_SERIALIZATION_NVP(gt);
					GameType *s = new GameType();
					*s = gt;

					if(i==0)s->builtInType = true;
					if(i==1) { s->builtInType = false; s->creatorUserName = "(You)"; }
					if(i==2)s->downloaded = true;


					loadedGameTypes.add(s);
				}
				catch(exception)
				{
					log.error("Could not load GameType: " + name);
				}
			}
		}

	}


}


//=========================================================================================================================
void BobsGame::loadGameSequencesFromXML()
{//=========================================================================================================================
	string userDataPathString = FileUtils::appDataPath + "gameSequences/";
	string builtInDataPathString = Main::getPath() + "data/gameSequences/";
	string downloadedDataPathString = FileUtils::appDataPath + "downloadedGameSequences/";

	Path userDataPath(userDataPathString);
	Path builtInDataPath(builtInDataPathString);
	Path downloadedDataPath(downloadedDataPathString);
	//make sure both directories exist, make them if they don't

	File userDataPathDir(userDataPath);
	File builtInDataPathDir(builtInDataPath);
	File downloadedDataPathDir(downloadedDataPath);

	if (userDataPathDir.exists() == false)userDataPathDir.createDirectories();
	if (builtInDataPathDir.exists() == false)builtInDataPathDir.createDirectories();
	if (downloadedDataPathDir.exists() == false)downloadedDataPathDir.createDirectories();


	loadedGameSequences.clear();

	bool found = false;

	//show all files in dir
	for(int i=0;i<3;i++)
	{
		vector<string> files;
		if(i==0)builtInDataPathDir.list(files);
		if(i==1)userDataPathDir.list(files);
		if(i==2)downloadedDataPathDir.list(files);
		vector<string>::iterator it = files.begin();
		for (; it != files.end(); ++it)
		{
			//cout << *it << endl;
			string name = *it;
			if (name.find(".xml") != string::npos)
			{
				if(i==0)found = true;

				string fullPathName;
				if (i == 0)fullPathName = builtInDataPathString + name;
				if (i == 1)fullPathName = userDataPathString + name;
				if (i == 2)fullPathName = downloadedDataPathString + name;

				ifstream t(fullPathName);
				string str;

				t.seekg(0, ios::end);
				str.reserve((size_t)t.tellg());
				t.seekg(0, ios::beg);

				str.assign((istreambuf_iterator<char>(t)),
					istreambuf_iterator<char>());

				stringstream ss;
				ss << str;

				boost::archive::xml_iarchive ia(ss);

				GameSequence gs;
				try
				{
					ia >> BOOST_SERIALIZATION_NVP(gs);

					GameSequence *s = new GameSequence();
					*s = gs;

					if (i == 0)s->builtInType = true;
					if (i == 1) { s->builtInType = false; s->creatorUserName = "(You)"; }
					if (i == 2)s->downloaded = true;

					loadedGameSequences.add(s);
				}
				catch(exception)
				{
					log.error("Could not load GameSequence: " + name);
				}

			}
		}
	}



	{

		//initialize actual games from game names in game sequences, this should be improved using game IDs so it can download missing games and sequences can be shared



		for(int i=0;i<loadedGameSequences.size();i++)
		{
			GameSequence *g = loadedGameSequences.get(i);

			loadGameSequenceUUIDsToGamesArray(g);
		}

	}

}

//=========================================================================================================================
void BobsGame::loadGameSequenceUUIDsToGamesArray(GameSequence *g)
{//=========================================================================================================================

	g->gameTypes.clear();

	for (int n = 0; n<g->importExport_gameUUIDs.size(); n++)
	{
		string uuid = g->importExport_gameUUIDs.get(n);
		GameType *s = getGameTypeByUUID(uuid);

		if (s != nullptr)
		{
			g->gameTypes.add(s);
		}
		else
		{
			log.debug("Could not load game UUID: " + uuid);
		}

	}
}
//=========================================================================================================================
GameType* BobsGame::getGameTypeByName(string name)
{//=========================================================================================================================
	GameType *bt = nullptr;
	for (int i = 0; i<loadedGameTypes.size(); i++)
	{
		GameType *b = loadedGameTypes.get(i);
		if (b->name == name)
		{
			bt = b;
		}
	}
	return bt;
}
//=========================================================================================================================
GameType* BobsGame::getGameTypeByUUID(string uuid)
{//=========================================================================================================================
	GameType *bt = nullptr;
	for (int i = 0; i<loadedGameTypes.size(); i++)
	{
		GameType *b = loadedGameTypes.get(i);
		if (b->uuid == uuid)
		{
			bt = b;
		}
	}
	return bt;
}
//=========================================================================================================================
GameSequence* BobsGame::getGameSequenceByName(string name)
{//=========================================================================================================================
	GameSequence *bt = nullptr;
	for (int i = 0; i<loadedGameSequences.size(); i++)
	{
		GameSequence *b = loadedGameSequences.get(i);
		if (b->name == name)
		{
			bt = b;
		}
	}
	return bt;
}
//=========================================================================================================================
GameSequence* BobsGame::getGameSequenceByUUID(string uuid)
{//=========================================================================================================================
	GameSequence *bt = nullptr;
	for (int i = 0; i<loadedGameSequences.size(); i++)
	{
		GameSequence *b = loadedGameSequences.get(i);
		if (b->uuid == uuid)
		{
			bt = b;
		}
	}
	return bt;
}
//=========================================================================================================================
void BobsGame::loadGlobalSettingsFromXML()
{//=========================================================================================================================
	string userDataPathString = FileUtils::appDataPath + "";
	Path userDataPath(userDataPathString);
	File userDataPathDir(userDataPath);
	if (userDataPathDir.exists() == false)userDataPathDir.createDirectories();


	string filename = "globalSettings.xml";
	File f = File(userDataPathString + filename);
	if(f.exists())
	{
		ifstream t(userDataPathString + filename);
		string str;

		t.seekg(0, ios::end);
		str.reserve((size_t)t.tellg());
		t.seekg(0, ios::beg);

		str.assign((istreambuf_iterator<char>(t)),
			istreambuf_iterator<char>());

		stringstream ss;
		ss << str;

		boost::archive::xml_iarchive ia(ss);
		GlobalSettings gs;
		try
		{
			ia >> BOOST_SERIALIZATION_NVP(gs);
		}
		catch(exception)
		{
			gs = GlobalSettings();
			log.error("Could not unserialize GlobalSettings");
		}

		GlobalSettings *s = new GlobalSettings();
		*s = gs;
		globalSettings = s;
	}
	else
	{
		globalSettings = new GlobalSettings();
	}



	music->setVolume((((float)globalSettings->musicVolume) / 100.0f));

}


//=========================================================================================================================
void BobsGame::saveGlobalSettingsToXML()
{//=========================================================================================================================

	string userDataPathString = FileUtils::appDataPath + "";
	Path userDataPath(userDataPathString);
	File userDataPathDir(userDataPath);
	if (userDataPathDir.exists() == false)userDataPathDir.createDirectories();


	string filename = "globalSettings.xml";

	Path filePath(userDataPathString + filename);
	File file(filePath);

	if (file.exists())
	{
		file.remove();
	}

	{
		std::stringstream ss;
		boost::archive::xml_oarchive oarchive(ss);

		GlobalSettings s;
		s = *globalSettings;
		oarchive << BOOST_SERIALIZATION_NVP(s);

		ofstream outputFile;
		outputFile.open(userDataPathString + filename, ofstream::out);
		outputFile << ss.str() << endl;
		outputFile.close();
	}

}

//=========================================================================================================================
void BobsGame::saveUnknownGameSequencesAndTypesToXML(GameSequence *gs)
{//=========================================================================================================================

	//save game sequence locally and each game type locally!
	//go through each game sequence and each game type and ignore if the uuid doesn't exist
	if (gs->creatorUserID != -1 && gs->dateCreated != -1 && getGameSequenceByUUID(gs->uuid) == nullptr)
	{
		loadedGameSequences.add(gs);
		saveGameSequenceToXML(gs, true);
	}
	for (int i = 0; i < gs->gameTypes.size(); i++)
	{
		GameType *g = gs->gameTypes.get(i);
		if (g->creatorUserID != -1 && g->dateCreated != -1 && getGameTypeByUUID(g->uuid) == nullptr)
		{

			loadedGameTypes.add(g);
			saveGameTypeToXML(g, true);
		}
	}
}

//=========================================================================================================================
void BobsGame::saveGameSequenceToXML(GameSequence *gs, bool downloaded)
{//=========================================================================================================================

	string userDataPathString = FileUtils::appDataPath + "gameSequences/";
	if(downloaded)userDataPathString = FileUtils::appDataPath + "downloadedGameSequences/";
	Path userDataPath(userDataPathString);
	File userDataPathDir(userDataPath);
	if (userDataPathDir.exists() == false)userDataPathDir.createDirectories();

	//if type exists, do we overwrite?
	//let's rename the old file to .000

	//TODO: we should have some kind of server based versioning using username-gamename
	string filename = gs->uuid + ".xml";

	filename = FileUtils::removeIllegalFilenameChars(filename);

	Path filePath(userDataPathString + filename);
	File file(filePath);
	int version = 0;

	if (file.exists())
	{
		while (file.exists())
		{
			file = File(userDataPathString + gs->uuid + "." + to_string(version));
			version++;
		}
		file = File(filePath);
		file.renameTo(userDataPathString + gs->uuid + "." + to_string(version));
	}


	{
		GameSequence g;
		g = *gs;

		std::stringstream ss;
		boost::archive::xml_oarchive oarchive(ss);
		oarchive << BOOST_SERIALIZATION_NVP(g);

		ofstream outputFile;
		outputFile.open(userDataPathString + filename, ofstream::out);
		outputFile << ss.str() << endl;
		outputFile.close();
	}
}

//=========================================================================================================================
void BobsGame::saveGameTypeToXML(GameType *gs, bool downloaded)
{//=========================================================================================================================
	string userDataPathString = FileUtils::appDataPath + "gameTypes/";
	if (downloaded)userDataPathString = FileUtils::appDataPath + "downloadedGameTypes/";
	Path userDataPath(userDataPathString);
	File userDataPathDir(userDataPath);
	if (userDataPathDir.exists() == false)userDataPathDir.createDirectories();


	//if type exists, do we overwrite?
	//let's rename the old file to .000

	//TODO: we should have some kind of server based versioning using username-gamename
	string filename = gs->uuid + ".xml";

	filename = FileUtils::removeIllegalFilenameChars(filename);

	//Path filePath();
	File file(userDataPathString + filename);
	int version = 0;

	if (file.exists())
	{
		while (file.exists())
		{
			file = File(userDataPathString + gs->uuid + "." + to_string(version));
			version++;
		}
		file = File(userDataPathString + filename);
		file.renameTo(userDataPathString + gs->uuid + "." + to_string(version));
	}


	{

		GameType g;
		g = *gs;
		if (downloaded)g.downloaded = true;

		std::stringstream ss;
		boost::archive::xml_oarchive oarchive(ss);
		oarchive << BOOST_SERIALIZATION_NVP(g);

		ofstream outputFile;
		outputFile.open(userDataPathString + filename, ofstream::out);
		outputFile << ss.str() << endl;
		outputFile.close();
	}
}


//=========================================================================================================================
void BobsGame::getGameTypesAndSequencesFromServer()
{//=========================================================================================================================
	

	
	
	if (getServerConnection()->getConnectedToServer_S())
	{
		//if (getServerConnection()->getAuthorizedOnServer_S())
		{
			if (gotGamesFromServer == false)
			{
				if (getServerConnection()->getAuthorizedOnServer_S() || sentServerGamesRequest)gettingGamesFromServerMenuShowing = true;

				long long currentTime = System::currentHighResTimer();
				long long startTime = lastCheckedGamesFromServerTime;
				int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
				if (ticksPassed > 2000)
				{
					lastCheckedGamesFromServerTime = currentTime;
					if (sentServerGamesRequest == false)
					{
						getServerConnection()->sendBobsGameGameTypesAndSequencesDownloadRequest_S();
						sentServerGamesRequest = true;

						wasAuthorizedWhenSent = getServerConnection()->getAuthorizedOnServer_S();
						
					}
					else
					{
						if (getServerConnection()->getAndResetBobsGameGameTypesAndSequencesDownloadResponseReceived_S())
						{
							gotGamesFromServer = true;
						}
					}
				}
			}
			else
			{


				long long currentTime = System::currentHighResTimer();
				long long startTime = lastCheckedGotIncomingGamesFromServerTime;
				int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
				if (ticksPassed > 1000)
				{
					lastCheckedGotIncomingGamesFromServerTime = currentTime;

					//if wasnt authed when got games but now we are authed get games again so votes are correct
					if (wasAuthorizedWhenSent == false && getServerConnection()->getAuthorizedOnServer_S() == true)
					{
						gotGamesFromServer = false;
						sentServerGamesRequest = false;
					}


					if (getAndResetGotIncomingGamesFromServer_S() == true)
					{

						//load threadsafe games into normal loadedGameTypes array in update and save all to xml

						while (incomingGameTypesQueueSize_S() > 0)
						{
							GameType *g = incomingGameTypesQueuePop_S();

							GameType *existing = getGameTypeByUUID(g->uuid);
							if (existing != nullptr)
							{
								if (existing->downloaded == true)
									loadedGameTypes.remove(existing);
							}

							if (existing == nullptr || existing->downloaded == true)//dont replace usermade game with downloaded version
							{
								loadedGameTypes.add(g);
								saveGameTypeToXML(g, true);
							}
						}

						while (incomingGameSequencesQueueSize_S()>0)
						{
							GameSequence *g = incomingGameSequencesQueuePop_S();

							GameSequence* existing = getGameSequenceByUUID(g->uuid);
							if (existing != nullptr)
							{
								if (existing->downloaded == true)
									loadedGameSequences.remove(existing);
							}
							if (existing == nullptr || existing->downloaded == true)
							{
								loadedGameSequences.add(g);
								saveGameSequenceToXML(g, true);
							}
						}

						for (int i = 0; i<loadedGameSequences.size(); i++)
						{
							GameSequence *g = loadedGameSequences.get(i);

							loadGameSequenceUUIDsToGamesArray(g);
						}

						setGotIncomingGamesFromServer_S(false);
						gettingGamesFromServerMenuShowing = false;

						if (gettingGamesFromServerMenu != nullptr)
						{
							delete gettingGamesFromServerMenu;
							gettingGamesFromServerMenu = nullptr;
						}
					}
				}
			}
		}
	}

}


//=========================================================================================================================
void BobsGame::parseIncomingGameTypesAndSequencesFromServer_S(string& s)
{//=========================================================================================================================


	//GameType:MD5:XML:userid:username:name:uuid:datecreated:lastmodified:howmanytimesupdated:upvotes:downvotes:haveyouvoted
	//					GameSequence:MD5

	while(s.length()>0)
	{
		string md5String;
		string zippedXMLString;
		string userIDString;
		string userNameString;
		string gameNameString;
		string uuidString;
		string dateCreatedString;
		string lastModifiedString;
		string howManyTimesUpdatedString;
		string upVotesString;
		string downVotesString;
		string yourVoteString;

		bool gameType = false;
		bool gameSequence = false;

		if(String::startsWith(s,"GameType:"))
		{
			gameType = true;
		}
		else
		if (String::startsWith(s, "GameSequence:"))
		{
			gameSequence = true;
		}
		else
		{
			log.error("Could not parse Game string from server: " + s);
			return;
		}

		s = s.substr(s.find(":") + 1);
		md5String = s.substr(0,s.find(":"));
		s = s.substr(s.find(":") + 1);
		zippedXMLString = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);
		userIDString = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);
		s = s.substr(s.find("`") + 1);
		userNameString = s.substr(0, s.find("`:"));
		s = s.substr(s.find("`") + 1);
		s = s.substr(s.find(":") + 1);
		s = s.substr(s.find("`") + 1);
		gameNameString = s.substr(0, s.find("`:"));
		s = s.substr(s.find("`") + 1);
		s = s.substr(s.find(":") + 1);
		uuidString = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);
		dateCreatedString = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);
		lastModifiedString = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);
		howManyTimesUpdatedString = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);
		upVotesString = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);
		downVotesString = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);
		yourVoteString = s.substr(0, s.find(":"));
		s = s.substr(s.find(":") + 1);

		long long userID = -1;
		try
		{
			userID = stoll(userIDString);
		}
		catch (exception)
		{
			log.error("userID could not be parsed");
			return;
		}

		long long dateCreated = -1;
		try
		{
			dateCreated = stoll(dateCreatedString);
		}
		catch (exception)
		{
			log.error("dateCreated could not be parsed");
			return;
		}

		long long lastModified = -1;
		try
		{
			lastModified = stoll(lastModifiedString);
		}
		catch (exception)
		{
			log.error("lastModified could not be parsed");
			return;
		}



		long long howManyTimesUpdated = -1;
		try
		{
			howManyTimesUpdated = stoll(howManyTimesUpdatedString);
		}
		catch (exception)
		{
			log.error("howManyTimesUpdated could not be parsed");
			return;
		}



		long long upVotes = -1;
		try
		{
			upVotes = stoll(upVotesString);
		}
		catch (exception)
		{
			log.error("upVotes could not be parsed");
			return;
		}



		long long downVotes = -1;
		try
		{
			downVotes = stoll(downVotesString);
		}
		catch (exception)
		{
			log.error("downVotes could not be parsed");
			return;
		}



		//check xml string with md5
		string compMD5 = FileUtils::getStringMD5(zippedXMLString);
		if (md5String == compMD5 == false)
		{
			log.error("GameType MD5 did not match in "+ gameNameString);
			continue;
		}

		//unzip to xml
		string xmlString = FileUtils::unzipBase64StringToString(zippedXMLString);

		if (xmlString == "" || xmlString.length() == 0)
		{
			log.error("Could not unzip GameType in "+ gameNameString);
			continue;
		}

		if(gameType)
		{
			//unserialize, add to threadsafe gameTypeArray

			stringstream ss;
			ss << xmlString;

			boost::archive::xml_iarchive ia(ss);
			GameType gs;
			try
			{
				ia >> BOOST_SERIALIZATION_NVP(gs);
				GameType *g = new GameType();
				*g = gs;

				g->creatorUserID = userID;
				g->creatorUserName = userNameString;
				g->dateCreated = dateCreated;
				g->lastModified = lastModified;
				g->howManyTimesUpdated = howManyTimesUpdated;
				g->upVotes = upVotes;
				g->downVotes = downVotes;
				g->yourVote = yourVoteString;

				incomingGameTypesQueuePush_S(g);
			}
			catch (exception)
			{
				log.error("Could not load GameType from server:"+gameNameString+" "+uuidString);
			}
		}

		if(gameSequence)
		{
			stringstream ss;
			ss << xmlString;

			boost::archive::xml_iarchive ia(ss);
			GameSequence gs;
			try
			{
				ia >> BOOST_SERIALIZATION_NVP(gs);

				GameSequence *g = new GameSequence();
				*g = gs;

				g->creatorUserID = userID;
				g->creatorUserName = userNameString;
				g->dateCreated = dateCreated;
				g->lastModified = lastModified;
				g->howManyTimesUpdated = howManyTimesUpdated;
				g->upVotes = upVotes;
				g->downVotes = downVotes;
				g->yourVote = yourVoteString;

				incomingGameSequencesQueuePush_S(g);
			}
			catch(exception)
			{
				log.error("Could not load GameSequence from server:" + gameNameString + " " + uuidString);
			}
		}

		//set threadsafe loaded games from server flag
		//load threadsafe games into normal loadedGameTypes array in update and save all to xml

		setGotIncomingGamesFromServer_S(true);

	}

}

//=========================================================================================================================
void BobsGame::updateVersion0ToVersion1()
{//=========================================================================================================================


 //after load, if makePieceTypeWhenCleared>0 but UUID==0 get piece types by name and add uuids
 //search and replace using makePieceTypeWhenCleared with UUID everywhere

 //BlockType::makePieceTypeWhenCleared
 //BlockType::ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType
 //BlockType::whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut
 //TurnFromBlockTypeToType::fromType
 //TurnFromBlockTypeToType::toType
 //PieceType::overrideBlockTypes

//search and replace with UUID
//TurnFromBlockTypeToType::fromType
//TurnFromBlockTypeToType::toType
//PieceType::overrideBlockTypes
//GameType::getBlockTypeByName
//GameType::getPieceTypeByName


	//fix for loading version 0 game types before moved to using uuid
	bool resave = false;
	for (int i = 0; i<loadedGameTypes.size(); i++)
	{
		GameType *g = loadedGameTypes.get(i);

		for (int n = 0; n < g->pieceTypes.size(); n++)
		{
			PieceType *p = g->pieceTypes.get(n);
			if (p->uuid == "")
			{
				boost::uuids::random_generator generator;
				p->uuid = to_string(generator());
			}
		}
		for (int n = 0; n < g->blockTypes.size(); n++)
		{
			BlockType *b = g->blockTypes.get(n);
			if (b->uuid == "")
			{
				boost::uuids::random_generator generator;
				b->uuid = to_string(generator());
			}
		}
		for (int n = 0; n<g->pieceTypes.size(); n++)
		{
			PieceType *p = g->pieceTypes.get(n);
			for (int x = 0; x<p->overrideBlockTypes_DEPRECATED.size(); x++)//should not have anything in it if it is > version 0
			{
				resave = true;
				BlockType *b = p->overrideBlockTypes_DEPRECATED.get(x);//wrong block, instantiated by serialize
				BlockType *correctBlock = g->getBlockTypeByName(b->name);
				if (correctBlock != nullptr)
				{
					if (correctBlock->uuid == "")
					{
						boost::uuids::random_generator generator;
						correctBlock->uuid = to_string(generator());
					}
					p->overrideBlockTypes_UUID.add(correctBlock->uuid);
				}
			}
		}
		for (int n = 0; n < g->blockTypes.size(); n++)
		{
			BlockType *b = g->blockTypes.get(n);

			for (int x = 0; x<b->makePieceTypeWhenCleared_DEPRECATED.size(); x++)
			{
				resave = true;
				PieceType *p = b->makePieceTypeWhenCleared_DEPRECATED.get(x);
				PieceType *correctPiece = g->getPieceTypeByName(p->name);
				if (correctPiece != nullptr)
				{
					if (correctPiece->uuid == "")
					{
						boost::uuids::random_generator generator;
						correctPiece->uuid = to_string(generator());
					}
					b->makePieceTypeWhenCleared_UUID.add(correctPiece->uuid);
				}
			}
			for (int x = 0; x<b->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_DEPRECATED.size(); x++)//should not have anything in it if it is > version 0
			{
				resave = true;
				BlockType *bb = b->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_DEPRECATED.get(x);//wrong block, instantiated by serialize
				BlockType *correctBlock = g->getBlockTypeByName(bb->name);
				if (correctBlock != nullptr)
				{
					if (correctBlock->uuid == "")
					{
						boost::uuids::random_generator generator;
						correctBlock->uuid = to_string(generator());
					}
					b->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_UUID.add(correctBlock->uuid);
				}
			}
			for (int x = 0; x < b->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.size(); x++)
			{
				TurnFromBlockTypeToType* t = b->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.get(x);
				if (t->fromType_DEPRECATED != "")
				{
					BlockType *correctBlock = g->getBlockTypeByName(t->fromType_DEPRECATED);
					if (correctBlock != nullptr)
					{
						if (correctBlock->uuid == "")
						{
							boost::uuids::random_generator generator;
							correctBlock->uuid = to_string(generator());
						}
						t->fromType_UUID = correctBlock->uuid;
					}
				}
				if (t->toType_DEPRECATED != "")
				{
					BlockType *correctBlock = g->getBlockTypeByName(t->toType_DEPRECATED);
					if (correctBlock != nullptr)
					{
						if (correctBlock->uuid == "")
						{
							boost::uuids::random_generator generator;
							correctBlock->uuid = to_string(generator());
						}
						t->toType_UUID = correctBlock->uuid;
					}
				}
			}
		}

		for(int n=0;n<g->difficultyTypes.size();n++)
		{
			DifficultyType *d = g->difficultyTypes.get(n);

			for (int x = 0; x < d->pieceTypesToDisallow_DEPRECATED.size(); x++)
			{
				resave = true;
				PieceType *p = d->pieceTypesToDisallow_DEPRECATED.get(x);
				PieceType *correctPiece = g->getPieceTypeByName(p->name);
				if (correctPiece != nullptr)
				{
					if (correctPiece->uuid == "")
					{
						boost::uuids::random_generator generator;
						correctPiece->uuid = to_string(generator());
					}
					d->pieceTypesToDisallow_UUID.add(correctPiece->uuid);
				}
			}
			for (int x = 0; x<d->blockTypesToDisallow_DEPRECATED.size(); x++)//should not have anything in it if it is > version 0
			{
				resave = true;
				BlockType *bb = d->blockTypesToDisallow_DEPRECATED.get(x);//wrong block, instantiated by serialize
				BlockType *correctBlock = g->getBlockTypeByName(bb->name);
				if (correctBlock != nullptr)
				{
					if (correctBlock->uuid == "")
					{
						boost::uuids::random_generator generator;
						correctBlock->uuid = to_string(generator());
					}
					d->blockTypesToDisallow_UUID.add(correctBlock->uuid);
				}
			}
		}


	}
	if (resave)
	{
		for (int i = 0; i < loadedGameTypes.size(); i++)
		{
			GameType *g = loadedGameTypes.get(i);
			if (g->builtInType == false)saveGameTypeToXML(g,g->downloaded);
		}
	}
}