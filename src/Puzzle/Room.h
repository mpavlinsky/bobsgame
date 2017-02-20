//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------



#pragma once
#include <string>
#include "bobtypes.h"
#include <src/Engine/network/UDPPeerConnection.h>
#include "GameSequence.h"
#include "BobsGame.h"

//=========================================================================================================================
class Room
{//=========================================================================================================================
public:


	UDPPeerConnection *hostPeer = nullptr;

	int currentNumPlayers = 0;
	int maxPlayers = -1;
	bool privateRoom = false;
	bool tournamentRoom = false;
	string uuid = "";
	long long hostUserID = -1;
	bool multiplayer_AllowDifferentDifficulties = true;
	bool multiplayer_AllowDifferentGameSequences = true;
	bool multiplayer_GameEndsWhenOnePlayerRemains = true;
	bool multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel = true;
	bool multiplayer_DisableVSGarbage = false;
	string gameSequenceOrTypeName = "";
	string gameSequenceUUID = "";
	string gameTypeUUID = "";
	//bool isSingleGameType = false;
	//bool isGameSequence = false;
	GameSequence *multiplayer_SelectedGameSequence = nullptr;
	string multiplayer_SelectedDifficultyName = "Beginner";

	//=========================================================================================================================
	Room()
	{//=========================================================================================================================
		boost::uuids::random_generator generator;
		uuid = to_string(generator());
	}
	//=========================================================================================================================
	string getRoomDescription()
	{//=========================================================================================================================
		string visibility = "Public";
		if (privateRoom)visibility = "Private";

		string scoreMode = "Free Play";
		if (tournamentRoom)scoreMode = "Tournament";

		string game = "Any Game";

		if (multiplayer_AllowDifferentGameSequences == false && multiplayer_SelectedGameSequence != nullptr)
			game = multiplayer_SelectedGameSequence->name;

		string difficulty = "Any Difficulty";
		if (multiplayer_AllowDifferentDifficulties == false)
			difficulty = multiplayer_SelectedDifficultyName;

		string garbage = "";
		if (multiplayer_DisableVSGarbage)
			garbage = "No Garbage";

		string endWhenLose = "Ends When All Lost";
		if (multiplayer_GameEndsWhenOnePlayerRemains)endWhenLose = "End On 1 Player Left";

		string endOnCredits = "Endless Mode";
		if (multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel)endOnCredits = "Race To Credits";


		string roomDescription = game;
		if (visibility != "")roomDescription += " | " + visibility;
		if (scoreMode != "")roomDescription += " | " + scoreMode;
		if (difficulty != "")roomDescription += " | " + difficulty;
		//if (garbage != "")roomDescription += " | " + garbage;
		//if (endWhenLose != "")roomDescription += " | " + endWhenLose;
		//if (endOnCredits != "")roomDescription += " | " + endOnCredits;


		string playersString = to_string(currentNumPlayers);
		if (maxPlayers > 1)playersString += "/" + to_string(maxPlayers) + " players";
		else playersString += " players";

		roomDescription += " | " + playersString;
		return roomDescription;
	}

	//=========================================================================================================================
	string encodeRoomData(long long hostUserID, int numPlayers, bool includeXMLGameSequence)
	{//=========================================================================================================================

	 //hostUserID,roomUUID,`gameSequenceOrTypeName`,isGameSequenceOrType,gameSequenceOrTypeUUID,usersInRoom,maxUsers,private,tournament,multiplayerOptions,
		string s =
			to_string(hostUserID) +
			"," + uuid;


		s += ",`" + multiplayer_SelectedGameSequence->name + "`";

		if (multiplayer_SelectedGameSequence->gameTypes.size() == 1)
		{
			s += ",GameType," + multiplayer_SelectedGameSequence->gameTypes.get(0)->uuid;
		}
		else
		{
			s += ",GameSequence," + multiplayer_SelectedGameSequence->uuid;
		}


		s +=

			"," + to_string(numPlayers) +
			"," + to_string(maxPlayers) +
			"," + to_string((int)privateRoom) +
			"," + to_string((int)tournamentRoom) +
			"," + to_string((int)multiplayer_AllowDifferentDifficulties) +
			"," + to_string((int)multiplayer_AllowDifferentGameSequences) +
			"," + to_string((int)multiplayer_GameEndsWhenOnePlayerRemains) +
			"," + to_string((int)multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel) +
			"," + to_string((int)multiplayer_DisableVSGarbage) +
			",";


		if (includeXMLGameSequence)
		{
			if (multiplayer_SelectedGameSequence != nullptr)
			{
				NetworkGameSequence ngs = NetworkGameSequence(*(multiplayer_SelectedGameSequence));
				s += ":" + ngs.toBase64GZippedXML();
			}
		}
		return s;
	}


	//=========================================================================================================================
	static Room* decodeRoomData(string s, bool decodeGameSequenceXML)
	{//=========================================================================================================================


		string hostUserIDString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string roomUUID = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		s = s.substr(s.find("`") + 1);
		string gameSequenceOrTypeName = s.substr(0, s.find("`"));
		s = s.substr(s.find("`") + 1);
		s = s.substr(s.find(",") + 1);
		string isGameSequenceOrType = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string gameSequenceOrTypeUUID = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string playersString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string maxPlayersString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string privateRoomString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string tournamentRoomString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_AllowDifferentDifficultiesString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_AllowDifferentGameSequencesString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_GameEndsWhenAllOpponentsLoseString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_GameEndsWhenSomeoneCompletesCreditsLevelString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_DisableVSGarbageString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);

		string multiplayer_SelectedGameSequenceString = "";
		if (decodeGameSequenceXML)
		{
			s = s.substr(s.find(":") + 1);
			multiplayer_SelectedGameSequenceString = s.substr(0, s.find(":"));
			if (multiplayer_SelectedGameSequenceString.length() < 10)multiplayer_SelectedGameSequenceString = "";
		}


		Room *newRoom = new Room();




		int hostUserID = -1;
		try
		{
			hostUserID = stoi(hostUserIDString);
		}
		catch (exception)
		{
			BobsGame::log.error("hostUserID could not be parsed");
			return nullptr;
		}
		newRoom->hostUserID = hostUserID;

		newRoom->uuid = roomUUID;

		newRoom->gameSequenceOrTypeName = gameSequenceOrTypeName;

		if (isGameSequenceOrType == "GameType")
		{
			//newRoom->isSingleGameType = true;
			newRoom->gameTypeUUID = gameSequenceOrTypeUUID;
		}
		else
		{
			//newRoom->isGameSequence = true;
			newRoom->gameSequenceUUID = gameSequenceOrTypeUUID;
		}

		int numPlayers = -1;
		try
		{
			numPlayers = stoi(playersString);
		}
		catch (exception)
		{
			BobsGame::log.error("numPlayers could not be parsed");
			return nullptr;
		}
		newRoom->currentNumPlayers = numPlayers;

		try
		{
			newRoom->maxPlayers = stoi(maxPlayersString);
		}
		catch (exception)
		{
			BobsGame::log.error("Could not parse maxPlayers");
			return nullptr;
		}

		try
		{
			newRoom->privateRoom = 0 != stoi(privateRoomString);
		}
		catch (exception)
		{
			BobsGame::log.error("Could not parse privateRoom");
			return nullptr;
		}

		try
		{
			newRoom->tournamentRoom = 0 != stoi(tournamentRoomString);
		}
		catch (exception)
		{
			BobsGame::log.error("Could not parse tournamentRoom");
			return nullptr;
		}

		try
		{
			newRoom->multiplayer_AllowDifferentDifficulties = 0 != stoi(multiplayer_AllowDifferentDifficultiesString);
		}
		catch (exception)
		{
			BobsGame::log.error("Could not parse multiplayer_AllowDifferentDifficulties");
			return nullptr;
		}

		try
		{
			newRoom->multiplayer_AllowDifferentGameSequences = 0 != stoi(multiplayer_AllowDifferentGameSequencesString);
		}
		catch (exception)
		{
			BobsGame::log.error("Could not parse multiplayer_AllowDifferentGameSequences");
			return nullptr;
		}

		try
		{
			newRoom->multiplayer_GameEndsWhenOnePlayerRemains = 0 != stoi(multiplayer_GameEndsWhenAllOpponentsLoseString);
		}
		catch (exception)
		{
			BobsGame::log.error("Could not parse multiplayer_GameEndsWhenAllOpponentsLose");
			return nullptr;
		}

		try
		{
			newRoom->multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel = 0 != stoi(multiplayer_GameEndsWhenSomeoneCompletesCreditsLevelString);
		}
		catch (exception)
		{
			BobsGame::log.error("Could not parse multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel");
			return nullptr;
		}

		try
		{
			newRoom->multiplayer_DisableVSGarbage = 0 != stoi(multiplayer_DisableVSGarbageString);
		}
		catch (exception)
		{
			BobsGame::log.error("Could not parse multiplayer_DisableVSGarbage");
			return nullptr;
		}

		if (decodeGameSequenceXML)
		{
			if (multiplayer_SelectedGameSequenceString.length() > 0)
			{
				NetworkGameSequence *gs = NetworkGameSequence::fromBase64GZippedXML(multiplayer_SelectedGameSequenceString);

				if (gs == nullptr)
				{
					BobsGame::log.error("Could not parse received GameSequence");
					return nullptr;
				}

				BobsGame::saveUnknownGameSequencesAndTypesToXML(gs);

				newRoom->multiplayer_SelectedGameSequence = gs;
				if (gs->gameTypes.size() == 1)
				{
					//newRoom->isSingleGameType = true;
					newRoom->gameTypeUUID = gs->gameTypes.get(0)->uuid;
				}
				else
				{
					//newRoom->isGameSequence = true;
					newRoom->gameSequenceUUID = gs->uuid;
				}
			}
			else
			{
				newRoom->multiplayer_SelectedGameSequence = nullptr;
			}
		}

		return newRoom;
	}





};

