//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------



#pragma once
#include <string>
#include "bobtypes.h"
#include "GameLogic.h"
#include "GameType.h"
#include "GameSequence.h"
#include <src/Engine/network/GameSave.h>
#include <src/Engine/network/UDPPeerConnection.h>


class Logger;

#include "src/Utility/AssetData.h"
#include "src/Utility/ArrayList.h"
#include "src/Utility/HashMap.h"
#include "src/Utility/audio/Music.h"
#include "src/Utility/ControlsManager.h"
#include "src/Utility/BobMenu.h"
#include "../Engine/Engine.h"
#include "../Engine/nd/NDGameEngine.h"

#include "CustomGameEditor.h"
#include "GameSequenceEditor.h"


#include "Stats/GameStats.h"
#include "Stats/UserStatsForSpecificGameAndDifficulty.h"
#include "Stats/LeaderBoardAndHighScoreBoardEntry.h"
//#include "GameTestMenu.h"

class GameTestMenuControl;
//class Engine;
//class NDGameEngine;
class Logger;
class ControlsManager;
class SpriteManager;
class AudioManager;
class PreloadedSprite;
class BobFont;
class CaptionManager;
class Room;



//=========================================================================================================================
class BobsGame : public NDGameEngine
{//=========================================================================================================================
private:
	typedef NDGameEngine super;
public:
	static Logger log;

protected:
	bool bgShaderFBOTextureToggle = false;

public:

	//static BobsGame* b;
	Music *music = nullptr;
	BobTexture* keyboardTexture = nullptr;
	BobTexture* controllerTexture = nullptr;
	BobTexture* controllerIconTexture = nullptr;
	BobTexture* keyboardIconTexture = nullptr;
	BobTexture* onlineTexture = nullptr;
	BobTexture* networkIconTexture = nullptr;
	BobTexture* gearsTexture = nullptr;
	BobTexture* chartTexture = nullptr;

	static BobTexture* upperLeft;
	static BobTexture* top;
	static BobTexture* upperRight;
	static BobTexture* left;
	static BobTexture* right;
	static BobTexture* lowerLeft;
	static BobTexture* bottom;
	static BobTexture* lowerRight;

	GameLogic* getPlayer1Game();
	PuzzlePlayer* getPlayer1();
	void setBobsGameFBOSize();
	void renderGameIntoFBO(GameLogic* g, bool useColorFilter);
	void drawBobsGameFBO(float x0, float x1, float y0, float y1);
	virtual void render() override;

	BobsGame();
	virtual ~BobsGame();
	virtual void init();



	void initPlayer();
	bool isMultiplayer();
	
	//long long randomSeed = -1;
	//GameType* originalSettings = nullptr;
	long long timeRenderBegan = 0;


	bool isNetworkGame() override;
	void debugKeys();
	void update() override;


	
	int shaderCount = rand() % GLUtils::bgShaderCount;
	void changeBG();
	virtual void shakeSmall() override;
	virtual void shakeHard() override;
	

	static Sprite* bobsGameLogoSmall;

	void initAssets();
	Sprite* getSpriteFromName(const string& name);
	//BobsGame* getThis();

	virtual void updateControls() override;
	virtual void resetPressedButtons() override;
	virtual void setButtonStates() override;


	ArrayList<PuzzlePlayer*> players;
	



	//-----------------
	//menus
	//-----------------

		
	Caption* pressEnterToRestartCaption = nullptr;

	virtual void setupMenus() override;
	virtual bool renderMenus() override;
	virtual bool updateMenus() override;

	bool startScreenMenuShowing = false;
	BobMenu *startScreenMenu = nullptr;
	BobMenu *infoMenu = nullptr;
	BobMenu *patreonMenu = nullptr;
	BobMenu *forumMenu = nullptr;
	int startScreenMenuCursorPosition = 0;
	void startScreenMenuUpdate();
	void startScreenMenuRender();

	BobMenu *gettingGamesFromServerMenu = nullptr;
	void gettingGamesFromServerMenuUpdate();
	void gettingGamesFromServerMenuRender();
	bool gettingGamesFromServerMenuShowing = false;
	long long gettingGamesFromServerDotsTime = 0;
	int gettingGamesFromServerCount = 0;

	string cycleDots(int tries);

	virtual void updateTitleScreenLogo() override;
	virtual void updateTitleMenuLogoTexture() override;
	virtual void titleMenuUpdate() override;
	virtual void titleMenuRender() override;

	//Caption* pressEnterCaption = nullptr;

	virtual void pauseMenuUpdate() override;
	virtual void pauseMenuRender() override;
	long long timeLastChangedSetting = 0;


	void difficultyMenuUpdate();
	void difficultyMenuRender();
	bool difficultyMenuShowing = false;
	BobMenu *difficultyMenu = nullptr;
	int difficultyMenuCursorPosition = 0;


	void controllerMenuUpdate();
	void controllerMenuRender();
	bool controllerMenuShowing = false;
	BobMenu *controllerMenu = nullptr;
	int controllerMenuCursorPosition = 0;
	bool controllerMenuTestingButtons = false;


	void localMultiplayerPlayerJoinMenuUpdate();
	void localMultiplayerPlayerJoinMenuRender();
	bool localMultiplayerPlayerJoinMenuShowing = false;
	BobMenu *localMultiplayerPlayerJoinMenu = nullptr;
	int localMultiplayerPlayerJoinMenuCursorPosition = 0;
	Caption* localMultiplayerPressStartCaption = nullptr;

	void playerDifficultyMiniMenuUpdate(PuzzlePlayer *p);
	void playerDifficultyMiniMenuRender(PuzzlePlayer *p, float x, float y);
	void playerPauseMiniMenuUpdate(PuzzlePlayer *p);
	void playerPauseMiniMenuRender(PuzzlePlayer *p, float x0, float x1, float y0, float y1);


	void loginMenuUpdate();
	void loginMenuRender();
	bool loginMenuShowing = false;
	BobMenu *loginMenu = nullptr;
	int loginMenuCursorPosition = 0;
	bool textStarted = false;
	string userNameOrEmailText = "";
	string userNameText = "";
	string emailText = "";
	string passwordText = "";
	string passwordStarsText = "";
	string confirmPasswordText = "";
	string confirmPasswordStarsText = "";
	bool stayLoggedIn = true;

	Caption* errorLabel = nullptr;
	Caption* statusLabel = nullptr;

	//bool loggedIn = false;

	void createAccountMenuUpdate();
	void createAccountMenuRender();
	bool createAccountMenuShowing = false;
	int lastMX = 0;
	int lastMY = 0;
	BobMenu *createAccountMenu = nullptr;
	int createAccountMenuCursorPosition = 0;
	
	ArrayList<Room*> rooms;
	Room* currentRoom = nullptr;

	void addToRoomsMenu(Room* c, string name, string id);
	void populateRoomsMenu();
	void networkMultiplayerLobbyMenuUpdate();
	void networkMultiplayerLobbyMenuRender();
	void selectGameSequenceOrSingleGameTypeFilterMenuUpdate();
	void selectGameSequenceFilterMenuUpdate();
	void selectSingleGameTypeFilterMenuUpdate();
	bool networkMultiplayerLobbyMenuShowing = false;
	bool selectGameSequenceFilterMenuShowing = false;
	bool selectSingleGameTypeFilterMenuShowing = false;
	bool selectGameSequenceOrSingleGameTypeFilterMenuShowing = false;
	//ArrayList<Caption*> *hostingFriendCaptions = new ArrayList<Caption*>();
	//ArrayList<Caption*> *playingFriendCaptions = new ArrayList<Caption*>();
	//int hostingFriendsCursorPosition = 0;
	BobMenu *networkMultiplayerLobbyMenu = nullptr;
	BobMenu *yourStatsMenu = nullptr;
	BobMenu *leaderBoardMenu = nullptr;
	BobMenu *roomsMenu = nullptr;
	BobMenu *friendsOnlineMenu = nullptr;
	//Caption *onlineFriendsLabel = nullptr;
	int networkMultiplayerLobbyMenuCursorPosition = 0;
	bool selectingHostedGame = false;
	//UDPPeerConnection *hostPeer = nullptr;
	ArrayList<UDPPeerConnection*> *joinedPeers = new ArrayList<UDPPeerConnection*>();
	bool hostStartedGame = false;
	string friendUserName = "";


	void networkMultiplayerPlayerJoinMenuUpdate();
	void networkMultiplayerPlayerJoinMenuRender();
	BobMenu *networkMultiplayerPlayerJoinMenu = nullptr;
	BobMenu *networkMultiplayerJoinedPeersMenu = nullptr;
	BobMenu *networkMultiplayerRoomRulesMenu = nullptr;
	Caption* networkMultiplayerPlayerJoinMenuPressStartCaption = nullptr;
	bool networkMultiplayerPlayerJoinMenuShowing = false;
	bool hosting = false;
	bool joining = false;
	
	bool hidePrivateRooms = false;
	bool hidePublicRooms = false;
	bool hideFreePlayRooms = false;
	bool hideTournamentRooms = false;
	string filterByGameSequenceName = "";
	string filterByGameSequenceUUID = "";
	string filterByGameTypeName = "";
	string filterByGameTypeUUID = "";
	string filterByKeyword = "";
	int filterByMaxPlayers = -1;


	long long lastSentPlayersUpdateTime = 0;
	long long lastSentServerRoomUpdateTime = 0;
	long long updatedJoinedPeersListTime = 0;
	//NETWORK

	long long lastTimeTriedToCloseGame = 0;
	virtual void tryToCloseGame() override;


	CustomGameEditorControl *customGameEditor = nullptr;
	GameSequenceEditorControl *gameSequenceEditor = nullptr;
	GameTestMenuControl *gameTestMenu = nullptr;

	void customGameEditorMenuUpdate();
	void customGameEditorMenuRender();
	BobMenu *customGameEditorMenu = nullptr;
	bool customGameEditorMenuShowing = false;
	int customGameEditorMenuCursorPosition = 0;
    

	void gameSequenceEditorMenuUpdate();
	void gameSequenceEditorMenuRender();
	BobMenu *gameSequenceEditorMenu = nullptr;
	bool gameSequenceEditorMenuShowing = false;
	int gameSequenceEditorMenuCursorPosition = 0;

	void gameTestMenuUpdate();
	void gameTestMenuRender();
	//BobMenu *gameTestMenu = nullptr;
	bool gameTestMenuShowing = false;
	int gameTestMenuCursorPosition = 0;



	void settingsMenuInit(BobMenu* m);
	void settingsMenuLeft(BobMenu* m);
	void settingsMenuRight(BobMenu* m);
	void settingsMenuConfirm(BobMenu* m);
	void globalSettingsMenuUpdate();
	void globalSettingsMenuRender();
	BobMenu *globalSettingsMenu = nullptr;
	bool globalSettingsMenuShowing = false;
	int globalSettingsMenuCursorPosition = 0;

	void statsMenuUpdate();
	void statsMenuRender();
	BobMenu *statsMenu = nullptr;
	BobMenu *whichStatsMiniMenu = nullptr;
	bool whichStatsMiniMenuShowing = false;
	void resetAllStatsMenuVars();
	void whichStatsMiniMenuUpdate();
	bool statsMenuShowing = false;
	int statsMenuCursorPosition = 0;
	string statsMenu_difficultyName = "OVERALL";
	string statsMenu_gameSequenceOrTypeUUID = "OVERALL";
	string statsMenu_gameSequenceOrTypeName = "OVERALL";
	bool statsMenu_totalTimePlayed = true;
	bool statsMenu_totalBlocksCleared = false;
	bool statsMenu_planeswalkerPoints = false;
	bool statsMenu_eloScore = false;
	bool statsMenu_timeLasted = false;
	bool statsMenu_blocksCleared = false;

	void gameSetupMenuUpdate();
	void gameSetupMenuRender();
	BobMenu *gameSetupMenu = nullptr;
	bool gameSetupMenuShowing = false;
	int gameSetupMenuCursorPosition = 0;
	int selectedDifficultyIndex = 0;
	int selectedObjectiveIndex = 0;

	//void selectedGameSequence(string name);
	//void selectedGameType(string name);
	//void selectedDifficulty(string name);
	//void selectedObjective(string name);

	void selectGameSequenceOrSingleGameTypeMenuUpdate();
	void selectGameSequenceOrSingleGameTypeMenuRender();
	BobMenu *selectGameSequenceOrSingleGameTypeMenu = nullptr;
	bool selectGameSequenceOrSingleGameTypeMenuShowing = false;
	int selectGameSequenceOrSingleGameTypeMenuCursorPosition = 0;

	void selectGameSequenceMenuUpdate();
	void selectGameSequenceMenuRender();
	BobMenu *selectGameSequenceMenu = nullptr;
	bool selectGameSequenceMenuShowing = false;
	int selectGameSequenceMenuCursorPosition = 0;

	double wilsonScore(double up, double total, double confidence = 1.644853);
	typedef pair<string, BobColor*> StringColorPair;
	typedef pair<GameType*, StringColorPair> GameTypeStringColorPairPair;
	typedef pair<GameSequence*, StringColorPair> GameSequenceStringColorPairPair;

	void populateUserStatsForSpecificGameAndDifficultyMenu(BobMenu *menu, string gameTypeOrSequenceUUID, string difficultyString);
	void populateLeaderBoardOrHighScoreBoardMenu(BobMenu *menu, string gameTypeOrSequenceUUID, string difficultyString,
		bool totalTimePlayed,
		bool totalBlocksCleared,
		bool planeswalkerPoints,
		bool eloScore,
		bool timeLasted,
		bool blocksCleared
	);

	ArrayList<GameTypeStringColorPairPair> getSortedGameTypes();
	ArrayList<GameSequenceStringColorPairPair> getSortedGameSequences();
	void populateGameTypesMenu(BobMenu *m);
	void populateGameSequencesMenu(BobMenu *m);
	void selectSingleGameTypeMenuUpdate();
	void selectSingleGameTypeMenuRender();
	BobMenu *selectSingleGameTypeMenu = nullptr;
	bool selectSingleGameTypeMenuShowing = false;
	int selectSingleGameTypeMenuCursorPosition = 0;

	bool upRepeatedStarted = false;
	bool upRepeating = false;
	long long upLastTime = 0;

	bool downRepeatedStarted = false;
	bool downRepeating = false;
	long long downLastTime = 0;

	void gameSequenceOptionsMenuUpdate();
	void gameSequenceOptionsMenuRender();
	BobMenu *gameSequenceOptionsMenu = nullptr;
	bool gameSequenceOptionsMenuShowing = false;
	int gameSequenceOptionsMenuCursorPosition = 0;

	void gameObjectiveMenuUpdate();
	void gameObjectiveMenuRender();
	BobMenu *gameObjectiveMenu = nullptr;
	bool gameObjectiveMenuShowing = false;
	int gameObjectiveMenuCursorPosition = 0;

	void multiplayerOptionsMenuUpdate();
	void multiplayerOptionsMenuRender();
	BobMenu *multiplayerOptionsMenu = nullptr;
	bool multiplayerOptionsMenuShowing = false;
	int multiplayerOptionsMenuCursorPosition = 0;

	//bool multiplayer_AllowDifferentDifficulties = true;
	//bool multiplayer_AllowDifferentGameSequences = true;
	//bool multiplayer_GameEndsWhenOnePlayerRemains = true;
	//bool multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel = true;
	//bool multiplayer_DisableVSGarbage = false;
	bool localMultiplayer = false;
	bool networkMultiplayer = false;
	//GameSequence *multiplayer_SelectedGameSequence = nullptr;
	//string multiplayer_SelectedDifficultyName = "Beginner";

	BobMenu* voteMenu = nullptr;
	bool voting = false;
	bool voteUpDown = false;

	bool sentStats = false;

	void playerGameSequenceMiniMenuUpdate(PuzzlePlayer *p);
	void playerGameSequenceMiniMenuRender(PuzzlePlayer *p, float x, float y);






	static ArrayList<BobsGameUserStatsForSpecificGameAndDifficulty*> userStatsPerGameAndDifficulty;
	static ArrayList<BobsGameLeaderBoardAndHighScoreBoard*> topPlayersByTotalTimePlayed;
	static ArrayList<BobsGameLeaderBoardAndHighScoreBoard*> topPlayersByTotalBlocksCleared;
	static ArrayList<BobsGameLeaderBoardAndHighScoreBoard*> topPlayersByPlaneswalkerPoints;
	static ArrayList<BobsGameLeaderBoardAndHighScoreBoard*> topPlayersByEloScore;
	static ArrayList<BobsGameLeaderBoardAndHighScoreBoard*> topGamesByTimeLasted;
	static ArrayList<BobsGameLeaderBoardAndHighScoreBoard*> topGamesByBlocksCleared;




	void sendAllJoinedPeers(string s);
	void sendPeer(UDPPeerConnection *c, string s);
	void sendAllPeers(string s);

	static const string lobbyCommand_STARTGAME;
	static const string lobbyCommand_CANCELGAME;
	static const string lobbyCommand_PEERGAMEJOIN;
	static const string lobbyCommand_PEERGAMELEAVE;
	static const string lobbyCommand_JOINEDPEER;
	static const string lobbyCommand_PLAYERCONFIRM;
	static const string lobbyCommand_PLAYERJOIN;
	static const string lobbyCommand_PLAYERLEAVE;
	static const string lobbyCommand_PLAYERFORFEIT;
	static const string lobbyCommandAllPeers_PLAYING;
	static const string lobbyCommandAllPeers_HOSTING;
	static const string lobbyCommandAllPeers_NOT_HOSTING;

	static const string netCommand_START;
	static const string netCommand_FRAME;
	static const string netCommand_FORFEIT;

	//ArrayList<PuzzlePlayer*>* bobsGameNetworkPlayers = new ArrayList<PuzzlePlayer*>();

	void tellAllPeersOneOfMyPlayersForfeitsGame(PuzzlePlayer *p);
	//void cancelNetworkGame();
	void tellHostPeerIAmJoiningTheirGame();
	void tellAllPeersIAmHosting();
	void tellAllPeersIAmNotHosting();
	void tellAllJoinedPeersThatANewPeerHasJoinedMyHostedGame(UDPPeerConnection *c);
	void tellAllPeersIAmPlayingAGame();
	void tellAllJoinedPeersIHaveCanceledMyHostedGame();
	void tellAllJoinedPeersMyHostedGameHasStarted();
	void tellAllJoinedPeersIHaveLeftTheGame();
	void tellAllJoinedPeersOneOfMyPlayersHasLeftTheLobby(PuzzlePlayer *p);
	void tellAllJoinedPeersOneOfMyPlayersHasJoinedTheLobby(PuzzlePlayer *p);
	void tellPeerThatOtherPeerHasJoined(UDPPeerConnection* peerToTell, UDPPeerConnection* joinedPeer);
	void tellPeerThatIHaveJoined(UDPPeerConnection* peerToTell);
	void tellPeerThatPlayerHasJoined(UDPPeerConnection* peerToTell, PuzzlePlayer *p);
	void tellPeerThatPlayerHasConfirmedAndSendGameSequence(UDPPeerConnection* peerToTell, PuzzlePlayer *p);
	void tellAllPeersThatPlayerHasConfirmedAndSendGameSequence(PuzzlePlayer *p);
	void tellServerIAmHostingOrUpdateRoomStatus(string roomDescription);
	void tellServerIHaveCanceledTheGame(string roomUUID);
	void tellServerIHaveStartedTheGame(string roomUUID);
	void tellServerTheGameHasEnded(string roomUUID, string results);
	static void getUserIDAndRandomSeedAndUUIDFromPlayerIDString(string s, long long &userID, long long &randomSeed, string &uuid);
	virtual bool udpPeerMessageReceived(UDPPeerConnection *c, string s) override;

  
	static ArrayList<GameType*> loadedGameTypes;
	static ArrayList<GameSequence*> loadedGameSequences;
	static ArrayList<Sprite*> loadedSprites;
	void loadGameSequencesFromXML();
	void loadGameTypesFromXML();

	static void saveUnknownGameSequencesAndTypesToXML(GameSequence *gs);
	static void saveGameSequenceToXML(GameSequence *gs, bool downloaded);
	static void saveGameTypeToXML(GameType *gt, bool downloaded);
	static void loadGameSequenceUUIDsToGamesArray(GameSequence *g);
	static GameType* getGameTypeByName(string name);
	static GameType* getGameTypeByUUID(string uuid);
	static GameSequence* getGameSequenceByName(string name);
	static GameSequence* getGameSequenceByUUID(string uuid);


	void increaseVolume();
	void decreaseVolume();

	void updateVersion0ToVersion1();

	void sendGameStatsToServer();
	bool doVoting();

	bool wasAuthorizedWhenSent = false;
	bool gotGamesFromServer = false;
	bool sentServerGamesRequest = false;
	long long lastCheckedGamesFromServerTime = 0;
	void getGameTypesAndSequencesFromServer();
	static void parseIncomingGameTypesAndSequencesFromServer_S(string &s);
	

	//------------------------------------

private:
	static queue<GameType*> _incomingGameTypes;
	static mutex _incomingGameTypes_Mutex;
public:
	static int incomingGameTypesQueueSize_S()
	{
		lock_guard<mutex> lock(_incomingGameTypes_Mutex);
		return (int)_incomingGameTypes.size();
	}
	static GameType* incomingGameTypesQueuePop_S()
	{
		lock_guard<mutex> lock(_incomingGameTypes_Mutex);
		GameType *g = _incomingGameTypes.front();
		_incomingGameTypes.pop();
		return g;
	}
	static void incomingGameTypesQueuePush_S(GameType *p)
	{
		lock_guard<mutex> lock(_incomingGameTypes_Mutex);
		_incomingGameTypes.push(p);
	}
	//------------------------------------

	//------------------------------------

private:
	static queue<GameSequence*> _incomingGameSequences;
	static mutex _incomingGameSequences_Mutex;
public:
	static int incomingGameSequencesQueueSize_S()
	{
		lock_guard<mutex> lock(_incomingGameSequences_Mutex);
		return (int)_incomingGameSequences.size();
	}
	static GameSequence* incomingGameSequencesQueuePop_S()
	{
		lock_guard<mutex> lock(_incomingGameSequences_Mutex);
		GameSequence *g = _incomingGameSequences.front();
		_incomingGameSequences.pop();
		return g;
	}
	static void incomingGameSequencesQueuePush_S(GameSequence *p)
	{
		lock_guard<mutex> lock(_incomingGameSequences_Mutex);
		_incomingGameSequences.push(p);
	}
	//------------------------------------

	//------------------------------------
	private:
		static bool _gotIncomingGamesFromServer;
		static mutex _gotIncomingGamesFromServer_Mutex;
public:
	static void setGotIncomingGamesFromServer_S(bool b)
	{
		lock_guard<mutex> lock(_gotIncomingGamesFromServer_Mutex);
		_gotIncomingGamesFromServer = b;
	}
	static bool getAndResetGotIncomingGamesFromServer_S()
	{
		lock_guard<mutex> lock(_gotIncomingGamesFromServer_Mutex);
		if(_gotIncomingGamesFromServer)
		{
			_gotIncomingGamesFromServer = false;
			return true;
		}
		else
		{
			return false;
		}
	}
	//------------------------------------

	long long lastCheckedGotIncomingGamesFromServerTime = 0;
};



