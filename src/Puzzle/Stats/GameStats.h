//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"

#include <src/Utility/Logger.h>


//===============================================================================================
//game stats logs stats for every single game that every user plays
class BobsGameGameStats
{//===============================================================================================

public:
	Logger log = Logger("BobsGameGameStats");

	string userName = "";
	long long userID = -1;

	string isGameTypeOrSequence = "";

	string gameTypeName = "";
	string gameTypeUUID = "";
	string gameSequenceName = "";
	string gameSequenceUUID = "";

	string gameTypeEndedOnName = "";
	string gameTypeEndedOnUUID = "";
	string difficultyName = "";

	int won = 0;
	int died = 0;
	int lost = 0;
	int complete = 0;
	int isLocalMultiplayer = 0;
	int isNetworkMultiplayer = 0;
	int numPlayers = 1;


	int level = 0;
	long long timeLasted = 0;
	long long timeStarted = 0;
	long long timeEnded = 0;
	int blocksMade = 0;
	int piecesMade = 0;
	int blocksCleared = 0;
	int piecesPlaced = 0;
	int combosMade = 0;
	int biggestCombo = 0;


	int maxPlayers = -1;
	int privateRoom = 0;
	int tournamentRoom = 0;
	long long hostUserID = -1;
	int multiplayer_AllowDifferentDifficulties = 1;
	int multiplayer_AllowDifferentGameSequences = 1;
	int multiplayer_GameEndsWhenOnePlayerRemains = 1;
	int multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel = 1;
	int multiplayer_DisableVSGarbage = 0;


	string allFrameStatesZipped = "";
	string playerIDsCSV = "";//id:`userName`:lost,id:`userName`:won,:

	string statsUUID = "";

	//game type or sequence,
	//sequence options
	//sequence uuid or gametype uuid
	//time started, time finished, time lasted
	//blocks made, pieces made, blocks cleared
	//was multiplayer,
	//number of players
	//multiplayer options,
	//whether won / lost
	//send replay packet as well

	//===============================================================================================
	BobsGameGameStats()
	{//===============================================================================================
		boost::uuids::random_generator generator;
		statsUUID = to_string(generator());
	}

	//===============================================================================================
	string encode()
	{//===============================================================================================
		string s = "";

		s += "`" + userName + "`" + ","
			+ to_string(userID) + ","
			+ isGameTypeOrSequence + ","
			+ "`" + gameTypeName + "`" + ","
			+ gameTypeUUID + ","
			+ "`" + gameSequenceName + "`" + ","
			+ gameSequenceUUID + ","
			+ "`" + gameTypeEndedOnName + "`" + ","
			+ gameTypeEndedOnUUID + ","
			+ difficultyName + ","
			+ to_string(won) + ","
			+ to_string(died) + ","
			+ to_string(lost) + ","
			+ to_string(complete) + ","
			+ to_string(isLocalMultiplayer) + ","
			+ to_string(isNetworkMultiplayer) + ","
			+ to_string(numPlayers) + ","
			+ to_string(level) + ","
			+ to_string(timeLasted) + ","
			+ to_string(timeStarted) + ","
			+ to_string(timeEnded) + ","
			+ to_string(blocksMade) + ","
			+ to_string(piecesMade) + ","
			+ to_string(blocksCleared) + ","
			+ to_string(piecesPlaced) + ","
			+ to_string(combosMade) + ","
			+ to_string(biggestCombo) + ","
			+ to_string(maxPlayers) + ","
			+ to_string(privateRoom) + ","
			+ to_string(tournamentRoom) + ","
			+ to_string(hostUserID) + ","
			+ to_string(multiplayer_AllowDifferentDifficulties) + ","
			+ to_string(multiplayer_AllowDifferentGameSequences) + ","
			+ to_string(multiplayer_GameEndsWhenOnePlayerRemains) + ","
			+ to_string(multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel) + ","
			+ to_string(multiplayer_DisableVSGarbage) + ","
			+ allFrameStatesZipped + ","
			+ statsUUID + ","
			+ playerIDsCSV + ":";


		return s;
	}

	//===============================================================================================
	BobsGameGameStats(string s)
	{//===============================================================================================

		boost::uuids::random_generator generator;
		statsUUID = to_string(generator());

		decode(s);
	}


	//===============================================================================================
	void decode(string s)
	{//===============================================================================================

		s = s.substr(s.find("`") + 1);
		userName = s.substr(0, s.find("`"));
		s = s.substr(s.find("`") + 1);
		s = s.substr(s.find(",") + 1);
		string userIDstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		isGameTypeOrSequence = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		s = s.substr(s.find("`") + 1);
		gameTypeName = s.substr(0, s.find("`"));
		s = s.substr(s.find("`") + 1);
		s = s.substr(s.find(",") + 1);
		gameTypeUUID = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		s = s.substr(s.find("`") + 1);
		gameSequenceName = s.substr(0, s.find("`"));
		s = s.substr(s.find("`") + 1);
		s = s.substr(s.find(",") + 1);
		gameSequenceUUID = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		s = s.substr(s.find("`") + 1);
		gameTypeEndedOnName = s.substr(0, s.find("`"));
		s = s.substr(s.find("`") + 1);
		s = s.substr(s.find(",") + 1);
		gameTypeEndedOnUUID = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		difficultyName = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string wonstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string diedstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string loststring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string completestring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string isLocalMultiplayerstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string isNetworkMultiplayerstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string numPlayersstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string levelstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string timeLastedstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string timeStartedstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string timeEndedstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string blocksMadestring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string piecesMadestring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string blocksClearedstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string piecesPlacedstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string combosMadestring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string biggestCombostring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string maxPlayersstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string privateRoomstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string tournamentRoomstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string hostUserIDstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_AllowDifferentDifficultiesstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_AllowDifferentGameSequencesstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_GameEndsWhenOnePlayerRemainsstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_GameEndsWhenSomeoneCompletesCreditsLevelstring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_DisableVSGarbagestring = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		allFrameStatesZipped = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		statsUUID = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		while (s.substr(0, 1) != ":")//id:`userName`:lost,id:`userName`:won,:
		{
			playerIDsCSV += s.substr(0, s.find("`") + 1);
			s = s.substr(s.find("`") + 1);
			playerIDsCSV += s.substr(0, s.find("`") + 1);
			s = s.substr(s.find("`") + 1);
			playerIDsCSV += s.substr(0, s.find(",") + 1);
			s = s.substr(s.find(",") + 1);
		}


		try
		{
			userID = stoll(userIDstring);
		}
		catch (exception)
		{
			log.error("Could not parse userID");
			return;
		}

		try
		{
			won = stoi(wonstring);
		}
		catch (exception)
		{
			log.error("Could not parse won");
			return;
		}

		try
		{
			died = stoi(diedstring);
		}
		catch (exception)
		{
			log.error("Could not parse died");
			return;
		}

		try
		{
			lost = stoi(loststring);
		}
		catch (exception)
		{
			log.error("Could not parse lost");
			return;
		}

		try
		{
			complete = stoi(completestring);
		}
		catch (exception)
		{
			log.error("Could not parse complete");
			return;
		}

		try
		{
			isLocalMultiplayer = stoi(isLocalMultiplayerstring);
		}
		catch (exception)
		{
			log.error("Could not parse isLocalMultiplayer");
			return;
		}

		try
		{
			isNetworkMultiplayer = stoi(isNetworkMultiplayerstring);
		}
		catch (exception)
		{
			log.error("Could not parse isNetworkMultiplayer");
			return;
		}

		try
		{
			numPlayers = stoi(numPlayersstring);
		}
		catch (exception)
		{
			log.error("Could not parse numPlayers");
			return;
		}

		try
		{
			level = stoi(levelstring);
		}
		catch (exception)
		{
			log.error("Could not parse level");
			return;
		}

		try
		{
			timeLasted = stoll(timeLastedstring);
		}
		catch (exception)
		{
			log.error("Could not parse timeLasted");
			return;
		}

		try
		{
			timeStarted = stoll(timeStartedstring);
		}
		catch (exception)
		{
			log.error("Could not parse timeStarted");
			return;
		}

		try
		{
			timeEnded = stoll(timeEndedstring);
		}
		catch (exception)
		{
			log.error("Could not parse timeEnded");
			return;
		}

		try
		{
			blocksMade = stoi(blocksMadestring);
		}
		catch (exception)
		{
			log.error("Could not parse blocksMade");
			return;
		}

		try
		{
			piecesMade = stoi(piecesMadestring);
		}
		catch (exception)
		{
			log.error("Could not parse piecesMade");
			return;
		}

		try
		{
			blocksCleared = stoi(blocksClearedstring);
		}
		catch (exception)
		{
			log.error("Could not parse blocksCleared");
			return;
		}

		try
		{
			piecesPlaced = stoi(piecesPlacedstring);
		}
		catch (exception)
		{
			log.error("Could not parse piecesPlaced");
			return;
		}

		try
		{
			combosMade = stoi(combosMadestring);
		}
		catch (exception)
		{
			log.error("Could not parse combosMade");
			return;
		}

		try
		{
			biggestCombo = stoi(biggestCombostring);
		}
		catch (exception)
		{
			log.error("Could not parse biggestCombo");
			return;
		}

		try
		{
			maxPlayers = stoi(maxPlayersstring);
		}
		catch (exception)
		{
			log.error("Could not parse maxPlayers");
			return;
		}

		try
		{
			privateRoom = stoi(privateRoomstring);
		}
		catch (exception)
		{
			log.error("Could not parse privateRoom");
			return;
		}

		try
		{
			tournamentRoom = stoi(tournamentRoomstring);
		}
		catch (exception)
		{
			log.error("Could not parse tournamentRoom");
			return;
		}

		try
		{
			hostUserID = stoll(hostUserIDstring);
		}
		catch (exception)
		{
			log.error("Could not parse hostUserID");
			return;
		}

		try
		{
			multiplayer_AllowDifferentDifficulties = stoi(multiplayer_AllowDifferentDifficultiesstring);
		}
		catch (exception)
		{
			log.error("Could not parse multiplayer_AllowDifferentDifficulties");
			return;
		}

		try
		{
			multiplayer_AllowDifferentGameSequences = stoi(multiplayer_AllowDifferentGameSequencesstring);
		}
		catch (exception)
		{
			log.error("Could not parse multiplayer_AllowDifferentGameSequences");
			return;
		}

		try
		{
			multiplayer_GameEndsWhenOnePlayerRemains = stoi(multiplayer_GameEndsWhenOnePlayerRemainsstring);
		}
		catch (exception)
		{
			log.error("Could not parse multiplayer_GameEndsWhenOnePlayerRemains");
			return;
		}

		try
		{
			multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel = stoi(multiplayer_GameEndsWhenSomeoneCompletesCreditsLevelstring);
		}
		catch (exception)
		{
			log.error("Could not parse multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel");
			return;
		}

		try
		{
			multiplayer_DisableVSGarbage = stoi(multiplayer_DisableVSGarbagestring);
		}
		catch (exception)
		{
			log.error("Could not parse multiplayer_DisableVSGarbage");
			return;
		}

	}




};