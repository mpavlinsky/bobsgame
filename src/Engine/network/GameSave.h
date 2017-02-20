//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class GameSave
{
public:
	static Logger log;


	long long userID = -1;
	string userName = "";
	string emailAddress = "";
	string passwordHash = "";
	int accountVerified = 0;
	string verificationHash = "";
	long long lastPasswordResetTime = 0;
	long long accountCreatedTime = 0;
	long long accountVerifiedTime = 0;
	long long firstLoginTime = 0;
	long long lastLoginTime = 0;
	long long lastSeenTime = 0;
	int timesLoggedIn = 0;
	long long totalTimePlayed = 0;
	string firstIP = "";
	string lastIP = "";

	//public String realName = "";
	//public long birthdayTime = 0;


	string facebookID = "";
	string facebookAccessToken = "";
	string facebookEmail = "";
	//string facebookBirthday = "";
	string facebookFirstName = "";
	string facebookLastName = "";
	string facebookGender = "";
	//string facebookLocale = "";
	//float facebookTimeZone = 0.0f;
	//string facebookUsername = "";
	//string facebookWebsite = "";

	//string googlePlusID = "";
	string postalCode = "";
	string countryName = "";
	string isoCountryCode = "";
	string placeName = "";
	string stateName = "";
	float lat = 0;
	float lon = 0;

	string notes = "";
	string warnings = "";

	string avatarIcon = "";



	string lastKnownRoom = "";
	int lastKnownX = 0;
	int lastKnownY = 0;
	string startingRoom = "";

	long long timePlayed = 0;
	long long pixelsWalked = 0;


	int accountRank = 0;

	float money = 0.0f;
	float moneyPurchased = 0.0f;


	int realWorldTransactions = 0;
	int inGameTransactions = 0;
	int timesTalkedToNPCs = 0;
	int timesTalkedToOtherPlayers = 0;
	string characterAppearance = "";
	string characterName = "";
	string itemsHeld = "";
	string itemsTotalCollected = "";
	string itemsPurchased = "";

	int miniGamesTimesPlayed = 0;
	int miniGamesTimesBattled = 0;
	int miniGamesTimesChallenged = 0;
	int miniGamesTimesChallenger = 0;
	int miniGamesTimesWon = 0;
	int miniGamesTimesLost = 0;
	int miniGamesTimesTied = 0;

	string dialoguesDone = "";
	string flagsSet = "";
	string skillValues = "";





	//GameSave(ResultSet *databaseResultSet);


	GameSave();


	virtual bool wasPlayerCreatedYet();


	virtual string addOrUpdateValueToCommaSeparatedList(string list, string value);


	virtual void* updateGameSaveValue(const string& variableName, const string& value);


	virtual string encodeGameSave();


	virtual void decodeGameSave(string s);


	static string getCountryStringFromCode(const string& countryCode);


	static string getCountryCodeFromCountryString(const string& countryString);
};

