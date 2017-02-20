#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger GameSave::log = Logger("GameSave");


GameSave::GameSave()//ResultSet* databaseResultSet)
{ //===============================================================================================

	//   try
	//   {
	//      userID = databaseResultSet->getInt("userID");
	//      emailAddress = databaseResultSet->getString("emailAddress");
	//      passwordHash = databaseResultSet->getString("passwordHash");
	//
	//      accountVerified = databaseResultSet->getInt("accountVerified");
	//      verificationHash = databaseResultSet->getString("verificationHash");
	//      lastPasswordResetTime = databaseResultSet->getLong("lastPasswordResetTime");
	//      accountCreatedTime = databaseResultSet->getLong("accountCreatedTime");
	//      accountVerifiedTime = databaseResultSet->getLong("accountVerifiedTime");
	//
	//      firstLoginTime = databaseResultSet->getLong("firstLoginTime");
	//      lastLoginTime = databaseResultSet->getLong("lastLoginTime");
	//      lastSeenTime = databaseResultSet->getLong("lastSeenTime");
	//      timesLoggedIn = databaseResultSet->getInt("timesLoggedIn");
	//      totalTimePlayed = databaseResultSet->getLong("totalTimePlayed");
	//      firstIP = databaseResultSet->getString("firstIP");
	//      lastIP = databaseResultSet->getString("lastIP");
	//
	//      //realName = databaseResultSet.getString("realName");
	//      //birthdayTime = databaseResultSet.getInt("birthdayTime");
	//
	//      facebookID = databaseResultSet->getString("facebookID");
	//      facebookAccessToken = databaseResultSet->getString("facebookAccessToken");
	//      facebookEmail = databaseResultSet->getString("facebookEmail");
	//      facebookBirthday = databaseResultSet->getString("facebookBirthday");
	//      facebookFirstName = databaseResultSet->getString("facebookFirstName");
	//      facebookLastName = databaseResultSet->getString("facebookLastName");
	//      facebookGender = databaseResultSet->getString("facebookGender");
	//      facebookLocale = databaseResultSet->getString("facebookLocale");
	//      facebookTimeZone = databaseResultSet->getFloat("facebookTimeZone");
	//      facebookUsername = databaseResultSet->getString("facebookUsername");
	//      facebookWebsite = databaseResultSet->getString("facebookWebsite");
	//
	//      googlePlusID = databaseResultSet->getString("googlePlusID");
	//
	//
	//      postalCode = databaseResultSet->getString("postalCode");
	//      countryName = databaseResultSet->getString("countryName");
	//      isoCountryCode = databaseResultSet->getString("isoCountryCode");
	//      placeName = databaseResultSet->getString("placeName");
	//      stateName = databaseResultSet->getString("stateName");
	//      lat = databaseResultSet->getFloat("lat");
	//      lon = databaseResultSet->getFloat("lon");
	//
	//
	//      notes = databaseResultSet->getString("notes");
	//      warnings = databaseResultSet->getString("warnings");
	//
	//      avatarIcon = databaseResultSet->getString("avatarIcon");
	//
	//      lastKnownRoom = databaseResultSet->getString("lastKnownRoom");
	//      lastKnownX = databaseResultSet->getInt("lastKnownX");
	//      lastKnownY = databaseResultSet->getInt("lastKnownY");
	//      startingRoom = databaseResultSet->getString("startingRoom");
	//      timePlayed = databaseResultSet->getLong("timePlayed");
	//      pixelsWalked = databaseResultSet->getLong("pixelsWalked");
	//
	//
	//      accountType = databaseResultSet->getInt("accountType");
	//
	//      money = databaseResultSet->getInt("money");
	//      moneyPurchased = databaseResultSet->getInt("moneyPurchased");
	//
	//      realWorldTransactions = databaseResultSet->getInt("realWorldTransactions");
	//      inGameTransactions = databaseResultSet->getInt("inGameTransactions");
	//
	//      timesTalkedToNPCs = databaseResultSet->getInt("timesTalkedToNPCs");
	//      timesTalkedToOtherPlayers = databaseResultSet->getInt("timesTalkedToOtherPlayers");
	//      characterAppearance = databaseResultSet->getString("characterAppearance");
	//      characterName = databaseResultSet->getString("characterName");
	//      itemsHeld = databaseResultSet->getString("itemsHeld");
	//
	//      itemsTotalCollected = databaseResultSet->getString("itemsTotalCollected");
	//      itemsPurchased = databaseResultSet->getString("itemsPurchased");
	//
	//      miniGamesTimesPlayed = databaseResultSet->getInt("miniGamesTimesPlayed");
	//      miniGamesTimesBattled = databaseResultSet->getInt("miniGamesTimesBattled");
	//
	//      miniGamesTimesChallenged = databaseResultSet->getInt("miniGamesTimesChallenged");
	//      miniGamesTimesChallenger = databaseResultSet->getInt("miniGamesTimesChallenger");
	//      miniGamesTimesWon = databaseResultSet->getInt("miniGamesTimesWon");
	//      miniGamesTimesLost = databaseResultSet->getInt("miniGamesTimesLost");
	//      miniGamesTimesTied = databaseResultSet->getInt("miniGamesTimesTied");
	//
	//      dialoguesDone = databaseResultSet->getString("dialoguesDone");
	//      flagsSet = databaseResultSet->getString("flagsSet");
	//      skillValues = databaseResultSet->getString("skillValues");
	//   }
	//   catch (exception& ex)
	//   {
	//      log.error(string("DB ERROR:") + ex.what());
	//   }
}

//GameSave::GameSave()
//{ //===============================================================================================
//}

bool GameSave::wasPlayerCreatedYet()
{ //===============================================================================================


	//if(realName.length()==0)return false;
	if (postalCode.length() == 0)
	{
		return false;
	}

	//public String avatarIcon = "";

	//public String characterAppearance = "";
	//public String characterName = "";


	return true;
}

string GameSave::addOrUpdateValueToCommaSeparatedList(string list, string value)
{ //===============================================================================================

	//value looks like id:thing:time
	//131:3.2:time
	//12:-1.6:time
	//-234:false:time

	//list looks like id:thing:time,id:thing:time,

	string id = value.substr(0, value.find(":"));


	if (list.find(id + string(":")) != string::npos)
	{
		//remove the old value by looking up the id
		log.debug(string("original list:") + list);
		string before = "";
		if (list.find(id + string(":")) > 0)
		{
			before = list.substr(0, list.find(id + string(":")));
		}


		string after = list.substr(list.find(id + string(":")));
		after = after.substr(after.find(",") + 1);

		log.debug(string("before:") + before);
		log.debug(string("after:") + after);
		list = before + after + value + string(","); //tack it on the end, order doesn't matter.
		log.debug(string("resulting list:") + list);
	}
	else
	{
		log.debug(string("original list:") + list);
		list = list + value + string(",");
		log.debug(string("resulting list:") + list);
	}

	return list;
}

void* GameSave::updateGameSaveValue(const string& variableName, const string& value)
{ //===============================================================================================


	log.debug(string("variableName:") + variableName);
	log.debug(string("value:") + value);

	if (variableName.length() == 0)
	{
		return nullptr;
	}
	if (value.length() == 0)
	{
		return nullptr;
	}


	//if(variableName.equals("userID"))						{try{userID = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return new Integer(userID);}

	//if(variableName.equals("emailAddress"))				{emailAddress = new String(value); return emailAddress;}
	//else if(variableName.equals("passwordHash"))				{passwordHash = new String(value); return passwordHash;}
	//else if(variableName.equals("accountVerified"))			{try{accountVerified = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return new Integer(accountVerified);}
	//else if(variableName.equals("verificationHash"))			{verificationHash = new String(value); return verificationHash;}
	//else if(variableName.equals("lastPasswordResetTime"))		{try{lastPasswordResetTime = Long.parseLong(value);}catch(NumberFormatException ex){return null;} return new Long(lastPasswordResetTime);}
	//else if(variableName.equals("accountCreatedTime"))			{try{accountCreatedTime = Long.parseLong(value);}catch(NumberFormatException ex){return null;} return new Long(accountCreatedTime);}
	//else if(variableName.equals("accountVerifiedTime"))		{try{accountVerifiedTime = Long.parseLong(value);}catch(NumberFormatException ex){return null;} return new Long(accountVerifiedTime);}
	//else if(variableName.equals("firstLoginTime"))				{try{firstLoginTime = Long.parseLong(value);}catch(NumberFormatException ex){return null;} return new Long(firstLoginTime);}
	//else if(variableName.equals("lastLoginTime"))					{try{lastLoginTime 	= Long.parseLong(value);}catch(NumberFormatException ex){return null;} return new Long(lastLoginTime);}
	//else if(variableName.equals("lastSeenTime"))					{try{lastSeenTime 	= Long.parseLong(value);}catch(NumberFormatException ex){return null;} return new Long(lastSeenTime);}
	//else if(variableName.equals("timesLoggedIn"))				{try{timesLoggedIn = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return new Integer(timesLoggedIn);}
	//else if(variableName.equals("firstIP"))					{firstIP = new String(value); return firstIP;}
	//else if(variableName.equals("lastIP"))						{lastIP = new String(value); return lastIP;}
	//if(variableName.equals("realName"))					{realName 	= new String(value); return realName;}
	//else if(variableName.equals("birthdayTime"))				{try{birthdayTime = Long.parseLong(value);}catch(NumberFormatException ex){return null;} return new Long(birthdayTime);}
	//else if(variableName.equals("facebookID"))					{facebookID 	= new String(value); return facebookID;}
	//else if(variableName.equals("facebookAccessToken"))		{facebookAccessToken 	= new String(value); return facebookAccessToken;}

	//else if(variableName.equals("facebookEmail"))			{facebookEmail 	= new String(value); return facebookEmail;}
	//else if(variableName.equals("facebookBirthday"))		{facebookBirthday 	= new String(value); return facebookBirthday;}
	//else if(variableName.equals("facebookFirstName"))		{facebookFirstName 	= new String(value); return facebookFirstName;}
	//else if(variableName.equals("facebookLastName"))		{facebookLastName 	= new String(value); return facebookLastName;}
	//else if(variableName.equals("facebookGender"))			{facebookGender 	= new String(value); return facebookGender;}
	//else if(variableName.equals("facebookLocale"))			{facebookLocale 	= new String(value); return facebookLocale;}
	//else if(variableName.equals("facebookTimeZone"))		{try{facebookTimeZone = Float.parseFloat(value);}catch(NumberFormatException ex){return null;} return new Float(facebookTimeZone);}
	//else if(variableName.equals("facebookUsername"))		{facebookUsername 	= new String(value); return facebookUsername;}
	//else if(variableName.equals("facebookWebsite"))			{facebookWebsite 	= new String(value); return facebookWebsite;}


	//else if(variableName.equals("googlePlusID"))				{googlePlusID 	= new String(value); return googlePlusID;}


	if (variableName == "postalCode")
	{
		postalCode = string(value);
		return &postalCode;
	}
	else if (variableName == "countryName")
	{
		countryName = string(value);
		return &countryName;
	}
	else if (variableName == "isoCountryCode")
	{
		isoCountryCode = string(value);
		return &isoCountryCode;
	}
	else if (variableName == "placeName")
	{
		placeName = string(value);
		return &placeName;
	}
	else if (variableName == "stateName")
	{
		stateName = string(value);
		return &stateName;
	}
	else if (variableName == "lat")
	{
		try
		{
			lat = stof(value);
		}
		catch (exception ex)//NumberFormatException ex)
		{
			log.error("Could not parse lat");
			return nullptr;
		}
		return &lat;
	}
	else if (variableName == "lon")
	{
		try
		{
			lon = stof(value);
		}
		catch (exception ex)//NumberFormatException ex)
		{
			log.error("Could not parse lon");
			return nullptr;
		}
		return &lon;
	}


	else if (variableName == "notes")
	{
		notes = string(value);
		return &notes;
	}
	else if (variableName == "warnings")
	{
		warnings = string(value);
		return &warnings;
	}

	else if (variableName == "avatarIcon")
	{
		avatarIcon = string(value);
		return &avatarIcon;
	}

	else if (variableName == "lastKnownRoom")
	{
		lastKnownRoom = string(value);
		return &lastKnownRoom;
	}
	else if (variableName == "lastKnownX")
	{
		try
		{
			lastKnownX = stoi(value);
		}
		catch (exception ex)//NumberFormatException ex)
		{
			log.error("Could not parse lastKnownX");
			return nullptr;
		}
		return &lastKnownX;
	}
	else if (variableName == "lastKnownY")
	{
		try
		{
			lastKnownY = stoi(value);
		}
		catch (exception ex)//NumberFormatException ex)
		{
			log.error("Could not parse lastKnownY");
			return nullptr;
		}
		return &lastKnownY;
	}
	else if (variableName == "startingRoom")
	{
		startingRoom = string(value);
		return &startingRoom;
	}
	else if (variableName == "timePlayed")
	{
		try
		{
			timePlayed = StringConverterHelper::fromString<long long>(value);
		}
		catch (exception ex)//NumberFormatException ex)
		{
			log.error("Could not parse timePlayed");
			return nullptr;
		}
		return &timePlayed;
	}
	else if (variableName == "pixelsWalked")
	{
		try
		{
			pixelsWalked = StringConverterHelper::fromString<long long>(value);
		}
		catch (exception ex)//NumberFormatException ex)
		{
			log.error("Could not parse pixelsWalked");
			return nullptr;
		}
		return &pixelsWalked;
	}


	//else if(variableName.equals("accountType"))				{try{accountType = Integer.parseInt(value);}catch(NumberFormatException ex){return null;} return new Integer(money);}
	//else if(variableName.equals("money"))						{try{money = Float.parseFloat(value);}catch(NumberFormatException ex){return null;} return new Float(money);}
	//else if(variableName.equals("moneyPurchased"))			{try{moneyPurchased = Float.parseFloat(value);}catch(NumberFormatException ex){return null;} return new Float(moneyPurchased);}
	else if (variableName == "realWorldTransactions")
	{
		try
		{
			realWorldTransactions = stoi(value);
		}
		catch (exception ex)//NumberFormatException ex)
		{
			log.error("Could not parse realWorldTransactions");
			return nullptr;
		}
		return &realWorldTransactions;
	}
	else if (variableName == "inGameTransactions")
	{
		try
		{
			inGameTransactions = stoi(value);
		}
		catch (exception ex)//NumberFormatException ex)
		{
			log.error("Could not parse inGameTransactions");
			return nullptr;
		}
		return &inGameTransactions;
	}
	else if (variableName == "timesTalkedToNPCs")
	{
		try
		{
			timesTalkedToNPCs = stoi(value);
		}
		catch (exception ex)//NumberFormatException ex)
		{
			log.error("Could not parse timesTalkedToNPCs");
			return nullptr;
		}
		return &timesTalkedToNPCs;
	}
	else if (variableName == "timesTalkedToOtherPlayers")
	{
		try
		{
			timesTalkedToOtherPlayers = stoi(value);
		}
		catch (exception ex)//NumberFormatException ex)
		{
			log.error("Could not parse timesTalkedToOtherPlayers");
			return nullptr;
		}
		return &timesTalkedToOtherPlayers;
	}
	else if (variableName == "characterAppearance")
	{
		characterAppearance = string(value);
		return &characterAppearance;
	}
	else if (variableName == "characterName")
	{
		characterName = string(value);
		return &characterName;
	}
	else if (variableName == "itemsHeld")
	{
		itemsHeld = addOrUpdateValueToCommaSeparatedList(itemsHeld, value);
		return &itemsHeld;
	}
	else if (variableName == "itemsTotalCollected")
	{
		itemsTotalCollected = string(value);
		return &itemsTotalCollected;
	}
	else if (variableName == "itemsPurchased")
	{
		itemsPurchased = string(value);
		return &itemsPurchased;
	}

	else if (variableName == "miniGamesTimesPlayed")
	{
		try
		{
			miniGamesTimesPlayed = stoi(value);
		}
		catch (exception ex)//NumberFormatException ex)
		{
			log.error("Could not parse miniGamesTimesPlayed");
			return nullptr;
		}
		return &miniGamesTimesPlayed;
	}
	else if (variableName == "miniGamesTimesBattled")
	{
		try
		{
			miniGamesTimesBattled = stoi(value);
		}
		catch (exception ex)//NumberFormatException ex)
		{
			log.error("Could not parse miniGamesTimesBattled");
			return nullptr;
		}
		return &miniGamesTimesBattled;
	}
	else if (variableName == "miniGamesTimesChallenged")
	{
		try
		{
			miniGamesTimesChallenged = stoi(value);
		}
		catch (exception ex)//NumberFormatException ex)
		{
			log.error("Could not parse miniGamesTimesChallenged");
			return nullptr;
		}
		return &miniGamesTimesChallenged;
	}
	else if (variableName == "miniGamesTimesChallenger")
	{
		try
		{
			miniGamesTimesChallenger = stoi(value);
		}
		catch (exception ex)//NumberFormatException ex)
		{
			log.error("Could not parse miniGamesTimesChallenger");
			return nullptr;
		}
		return &miniGamesTimesChallenger;
	}
	else if (variableName == "miniGamesTimesWon")
	{
		try
		{
			miniGamesTimesWon = stoi(value);
		}
		catch (exception ex)//NumberFormatException ex)
		{
			log.error("Could not parse miniGamesTimesWon");
			return nullptr;
		}
		return &miniGamesTimesWon;
	}
	else if (variableName == "miniGamesTimesLost")
	{
		try
		{
			miniGamesTimesLost = stoi(value);
		}
		catch (exception ex)//NumberFormatException ex)
		{
			log.error("Could not parse miniGamesTimesLost");
			return nullptr;
		}
		return &miniGamesTimesLost;
	}
	else if (variableName == "miniGamesTimesTied")
	{
		try
		{
			miniGamesTimesTied = stoi(value);
		}
		catch (exception ex)//NumberFormatException ex)
		{
			log.error("Could not parse miniGamesTimesTied");
			return nullptr;
		}
		return &miniGamesTimesTied;
	}
	else if (variableName == "dialoguesDone")
	{
		dialoguesDone = addOrUpdateValueToCommaSeparatedList(dialoguesDone, value);
		return &dialoguesDone;
	}
	else if (variableName == "flagsSet")
	{
		flagsSet = addOrUpdateValueToCommaSeparatedList(flagsSet, value);
		return &flagsSet;
	}
	else if (variableName == "skillValues")
	{
		skillValues = addOrUpdateValueToCommaSeparatedList(skillValues, value);
		return &skillValues;
	}


	return nullptr;
}

string GameSave::encodeGameSave()
{ //===============================================================================================

	string gameSaveString =
		string("userID:") +
		string("`") +
		to_string(userID) +
		string("`") +
		string(",userName:") +
		string("`") +
		(userName)+
		string("`") +
		string(",emailAddress:") +
		string("`") +
		(emailAddress) +
		string("`") +
		string(",accountCreatedTime:") +
		string("`") +
		to_string(accountCreatedTime) +
		string("`") +
		string(",lastLoginTime:") +
		string("`") +
		to_string(lastLoginTime) +
		string("`") +
		string(",timesLoggedIn:") +
		string("`") +
		to_string(timesLoggedIn) +
		string("`") +
		string(",totalTimePlayed:") +
		string("`") +
		to_string(totalTimePlayed) +
		string("`") +
		string(",lastIP:") +
		string("`") +
		(lastIP) +
		string("`") +
		string(",facebookID:") +
		string("`") +
		(facebookID) +
		string("`") +
		string(",facebookAccessToken:") +
		string("`") +
		(facebookAccessToken) +
		string("`") +
		string(",facebookEmail:") +
		string("`") +
		(facebookEmail) +
		string("`") +
//		string(",facebookBirthday:") +
//		string("`") +
//		(facebookBirthday) +
//		string("`") +
		string(",facebookFirstName:") +
		string("`") +
		(facebookFirstName) +
		string("`") +
		string(",facebookLastName:") +
		string("`") +
		(facebookLastName) +
		string("`") +
		string(",facebookGender:") +
		string("`") +
		(facebookGender) +
		string("`") +
//		string(",facebookLocale:") +
//		string("`") +
//		(facebookLocale) +
//		string("`") +
//		string(",facebookTimeZone:") +
//		string("`") +
//		to_string(facebookTimeZone) +
//		string("`") +
//		string(",facebookUsername:") +
//		string("`") +
//		(facebookUsername) +
//		string("`") +
//		string(",facebookWebsite:") +
//		string("`") +
//		(facebookWebsite) +
//		string("`") +
//		string(",googlePlusID:") +
//		string("`") +
//		(googlePlusID) +
//		string("`") +
		string(",postalCode:") +
		string("`") +
		(postalCode) +
		string("`") +
		string(",countryName:") +
		string("`") +
		(countryName) +
		string("`") +
		string(",isoCountryCode:") +
		string("`") +
		(isoCountryCode) +
		string("`") +
		string(",placeName:") +
		string("`") +
		(placeName) +
		string("`") +
		string(",stateName:") +
		string("`") +
		(stateName) +
		string("`") +
		string(",lat:") +
		string("`") +
		to_string(lat) +
		string("`") +
		string(",lon:") +
		string("`") +
		to_string(lon) +
		string("`") +
		string(",notes:") +
		string("`") +
		(notes) +
		string("`") +
		string(",warnings:") +
		string("`") +
		(warnings) +
		string("`") +
		string(",avatarIcon:") +
		string("`") +
		(avatarIcon) +
		string("`") +
		string(",lastKnownRoom:") +
		string("`") +
		(lastKnownRoom) +
		string("`") +
		string(",lastKnownX:") +
		string("`") +
		to_string(lastKnownX) +
		string("`") +
		string(",lastKnownY:") +
		string("`") +
		to_string(lastKnownY) +
		string("`") +
		string(",startingRoom:") +
		string("`") +
		(startingRoom) +
		string("`") +
		string(",timePlayed:") +
		string("`") +
		to_string(timePlayed) +
		string("`") +
		string(",pixelsWalked:") +
		string("`") +
		to_string(pixelsWalked) +
		string("`") +
		string(",accountRank:") +
		string("`") +
		to_string(accountRank) +
		string("`") +
		string(",money:") +
		string("`") +
		to_string(money) +
		string("`") +
		string(",characterAppearance:") +
		string("`") +
		(characterAppearance) +
		string("`") +
		string(",characterName:") +
		string("`") +
		(characterName) +
		string("`") +
		string(",itemsHeld:") +
		string("`") +
		(itemsHeld) +
		string("`") +
		string(",dialoguesDone:") +
		string("`") +
		(dialoguesDone) +
		string("`") +
		string(",flagsSet:") +
		string("`") +
		(flagsSet) +
		string("`") +
		string(",skillValues:") +
		string("`") +
		(skillValues) +
		string("`");



		gameSaveString += ",";


	//",passwordHash:"+            		"`"+passwordHash+"`"+
	//",accountVerified:"+         	 	"`"+accountVerified+"`"+
	//",verificationHash:"+          	"`"+verificationHash+"`"+
	//",lastPasswordResetTime:"+    	"`"+lastPasswordResetTime+"`"+
	//",accountVerifiedTime:"+    		"`"+accountVerifiedTime+"`"+
	//",firstLoginTime:"+               "`"+firstLoginTime+"`"+
	//",lastSeenTime:"+                 "`"+lastSeenTime+"`"+
	//",firstIP:"+                 		"`"+firstIP+"`"+
	//",realName:"+                		"`"+realName+"`"+
	//",birthdayTime:"+               	"`"+birthdayTime+"`"+
	//",moneyPurchased:"+ 				"`"+moneyPurchased+"`"+
	//",realWorldTransactions:"+   		"`"+realWorldTransactions+"`"+
	//",inGameTransactions:"+      		"`"+inGameTransactions+"`"+
	//",timesTalkedToNPCs:"+       		"`"+timesTalkedToNPCs+"`"+
	//",timesTalkedToOtherPlayers:"+	"`"+timesTalkedToOtherPlayers+"`"+


	return gameSaveString;
}

void GameSave::decodeGameSave(string s)
{ //===============================================================================================

	bool debug = false;

	{
		//		"userID:"+                  	"`"+userID+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				long long tempUserID = stoll(t);
				if(userID!=-1 && tempUserID!=userID)
				{
					log.error("userID did not match incoming userID in GameSave!");
				}
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse userID");
				
			}
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("userID:") + to_string(userID));
		}
	}

	{
		//		",userName:"+            	"`"+userName+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			userName = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("userName:") + userName);
		}
	}

	{
		//		",emailAddress:"+            	"`"+emailAddress+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			emailAddress = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("emailAddress:") + emailAddress);
		}
	}

	{
		//		",accountCreatedTime:"+          "`"+accountCreatedTime+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				accountCreatedTime = StringConverterHelper::fromString<long long>(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse accountCreatedTime");
				
			}
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("accountCreated:") + to_string(accountCreatedTime));
		}
	}

	{
		//		",lastLoginTime:"+                  "`"+lastLoginTime+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				lastLoginTime = StringConverterHelper::fromString<long long>(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse lastLoginTime");
				
			}
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("lastLoginTime:") + to_string(lastLoginTime));
		}
	}

	{
		//		",timesLoggedIn:"+           	"`"+timesLoggedIn+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				timesLoggedIn = stoi(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse timesLoggedIn");
				
			}
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("timesLoggedIn:") + to_string(timesLoggedIn));
		}
	}


	{
		//		",totalTimePlayed:"+           	"`"+totalTimePlayed+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				totalTimePlayed = StringConverterHelper::fromString<long long>(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse totalTimePlayed");
				
			}
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("totalTimePlayed:") + to_string(totalTimePlayed));
		}
	}


	{
		//		",lastIP:"+                  	"`"+lastIP+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			lastIP = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("lastIP:") + lastIP);
		}
	}

	////		",realName:"+                	"`"+realName+"`"+
	//		{
	//			s = s.substring(s.indexOf('`')+1);
	//			String t = s.substring(0, s.indexOf('`'));
	//			if(t.length()>0)realName = t;
	//			s = s.substring(s.indexOf('`')+1);
	//			if(debug)log.debug("realName:"+realName);
	//		}
	//
	////		",birthdayTime:"+                "`"+birthdayTime+"`"+
	//		{
	//			s = s.substring(s.indexOf('`')+1);
	//			String t = s.substring(0, s.indexOf('`'));
	//			if(t.length()>0)try{birthdayTime = Long.parseLong(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
	//			s = s.substring(s.indexOf('`')+1);
	//			if(debug)log.debug("birthdayTime:"+birthdayTime);
	//		}

	{
		//		",facebookID:"+              	"`"+facebookID+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			facebookID = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("facebookID:") + facebookID);
		}
	}

	{
		//		",facebookAccessToken:"+              	"`"+facebookAccessToken+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			facebookAccessToken = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("facebookAccessToken:") + facebookAccessToken);
		}
	}

	{
		//		",facebookEmail:"+              	"`"+facebookEmail+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			facebookEmail = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("facebookEmail:") + facebookEmail);
		}
	}
//	{
//		//		",facebookBirthday:"+              	"`"+facebookBirthday+"`"+
//		s = s.substr(s.find('`') + 1);
//		string t = s.substr(0, s.find('`'));
//		if (t.length() > 0)
//		{
//			facebookBirthday = t;
//		}
//		s = s.substr(s.find('`') + 1);
//		if (debug)
//		{
//			log.debug(string("facebookBirthday:") + facebookBirthday);
//		}
//	}
	{
		//		",facebookFirstName:"+              	"`"+facebookFirstName+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			facebookFirstName = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("facebookFirstName:") + facebookFirstName);
		}
	}
	{
		//		",facebookLastName:"+              	"`"+facebookLastName+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			facebookLastName = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("facebookLastName:") + facebookLastName);
		}
	}
	{
		//		",facebookGender:"+              	"`"+facebookGender+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			facebookGender = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("facebookGender:") + facebookGender);
		}
	}
//	{
//		//		",facebookLocale:"+              	"`"+facebookLocale+"`"+
//		s = s.substr(s.find('`') + 1);
//		string t = s.substr(0, s.find('`'));
//		if (t.length() > 0)
//		{
//			facebookLocale = t;
//		}
//		s = s.substr(s.find('`') + 1);
//		if (debug)
//		{
//			log.debug(string("facebookLocale:") + facebookLocale);
//		}
//	}
//	{
//		//		",facebookTimeZone:"+              	"`"+facebookTimeZone+"`"+
//		s = s.substr(s.find('`') + 1);
//		string t = s.substr(0, s.find('`'));
//		if (t.length() > 0)
//		{
//			try
//			{
//				facebookTimeZone = stof(t);
//			}
//			catch (exception ex)//NumberFormatException ex)
//			{
//				log.error("Could not parse facebookTimeZone");
//				
//			}
//		}
//		s = s.substr(s.find('`') + 1);
//		if (debug)
//		{
//			log.debug(string("facebookTimeZone:") + to_string(facebookTimeZone));
//		}
//	}
//	{
//		//		",facebookUsername:"+              	"`"+facebookUsername+"`"+
//		s = s.substr(s.find('`') + 1);
//		string t = s.substr(0, s.find('`'));
//		if (t.length() > 0)
//		{
//			facebookUsername = t;
//		}
//		s = s.substr(s.find('`') + 1);
//		if (debug)
//		{
//			log.debug(string("facebookUsername:") + facebookUsername);
//		}
//	}
//	{
//		//		",facebookWebsite:"+              	"`"+facebookWebsite+"`"+
//		s = s.substr(s.find('`') + 1);
//		string t = s.substr(0, s.find('`'));
//		if (t.length() > 0)
//		{
//			facebookWebsite = t;
//		}
//		s = s.substr(s.find('`') + 1);
//		if (debug)
//		{
//			log.debug(string("facebookWebsite:") + facebookWebsite);
//		}
//	}
//
//	{
//		//		",googlePlusID:"+            	"`"+googlePlusID+"`"+
//		s = s.substr(s.find('`') + 1);
//		string t = s.substr(0, s.find('`'));
//		if (t.length() > 0)
//		{
//			googlePlusID = t;
//		}
//		s = s.substr(s.find('`') + 1);
//		if (debug)
//		{
//			log.debug(string("googlePlusID:") + googlePlusID);
//		}
//	}

	{
		//		",postalCode:"+                 "`"+postalCode+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			postalCode = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("postalCode:") + postalCode);
		}
	}

	{
		//		",countryName:"+                 "`"+countryName+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			countryName = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("countryName:") + countryName);
		}
	}

	{
		//		",isoCountryCode:"+                 "`"+isoCountryCode+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			isoCountryCode = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("isoCountryCode:") + isoCountryCode);
		}
	}

	{
		//		",placeName:"+                 	"`"+placeName+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			placeName = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("placeName:") + placeName);
		}
	}

	{
		//		",stateName:"+                 	"`"+stateName+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			stateName = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("stateName:") + stateName);
		}
	}

	{
		//		",lat:"+                		"`"+lat+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				lat = stof(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse lat");
			}
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("lat:") + to_string(lat));
		}
	}
	{
		//		",lon:"+                		"`"+lon+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				lon = stof(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse lon");
			}
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("lon:") + to_string(lon));
		}
	}

	//		",timeZone:"+                	"`"+timeZone+"`"+
	//		{
	//			s = s.substring(s.indexOf('`')+1);
	//			String t = s.substring(0, s.indexOf('`'));
	//			if(t.length()>0)try{timeZone = Integer.parseInt(t);}catch(NumberFormatException ex){ex.printStackTrace();return;}
	//			s = s.substring(s.indexOf('`')+1);
	//			if(debug)log.debug("timeZone:"+timeZone);
	//		}

	{
		//		",notes:"+                   	"`"+notes+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			notes = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("notes:") + notes);
		}
	}

	{
		//		",warnings:"+                	"`"+warnings+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			warnings = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("warnings:") + warnings);
		}
	}

	{
		//		",avatarIcon:"+              	"`"+avatarIcon+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			avatarIcon = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("avatarIcon:") + avatarIcon);
		}
	}

	{
		//		",lastKnownRoom:"+           	"`"+lastKnownRoom+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			lastKnownRoom = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("lastKnownRoom:") + lastKnownRoom);
		}
	}

	{
		//		",lastKnownX:"+              	"`"+lastKnownX+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				lastKnownX = stoi(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse lastKnownX");
			}
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("lastKnownX:") + to_string(lastKnownX));
		}
	}

	{
		//		",lastKnownY:"+              	"`"+lastKnownY+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				lastKnownY = stoi(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse lastKnownY");
			}
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("lastKnownY:") + to_string(lastKnownY));
		}
	}

	{
		//		",startingRoom:"+            	"`"+startingRoom+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			startingRoom = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("startingRoom:") + startingRoom);
		}
	}

	{
		//		",timePlayed:"+              	"`"+timePlayed+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				timePlayed = StringConverterHelper::fromString<long long>(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse timePlayed");
			}
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("timePlayed:") + to_string(timePlayed));
		}
	}

	{
		//		",pixelsWalked:"+            	"`"+pixelsWalked+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				pixelsWalked = StringConverterHelper::fromString<long long>(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse pixelsWalked");
			}
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("pixelsWalked:") + to_string(pixelsWalked));
		}
	}


	{
		//		",accountRank:"+          	"`"+accountRank+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				accountRank = stoi(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse accountRank");
			}
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("accountRank:") + to_string(accountRank));
		}
	}

	{ //money
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				money = stof(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse money");
			}
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("money:") + to_string(money));
		}
	}

	{
		//		",characterAppearance:"+     	"`"+characterAppearance+"`"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			characterAppearance = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("characterAppearance:") + characterAppearance);
		}
	}

	{
		//		",characterName:"+           	"`"+characterName+"`"
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			characterName = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("characterName:") + characterName);
		}
	}
	{ //itemsHeld
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			itemsHeld = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("itemsHeld:") + itemsHeld);
		}
	}
	{ //dialoguesDone
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			dialoguesDone = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("dialoguesDone:") + dialoguesDone);
		}
	}
	{ //flagsSet
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			flagsSet = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("flagsSet:") + flagsSet);
		}
	}
	{ //skillValues
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			skillValues = t;
		}
		s = s.substr(s.find('`') + 1);
		if (debug)
		{
			log.debug(string("skillValues:") + skillValues);
		}
	}



}

string GameSave::getCountryStringFromCode(const string& countryCode)
{
	string countryString = "United States";

	if (countryCode == "AD")
	{
		countryString = "Andorra";
	}
	if (countryCode == "AE")
	{
		countryString = "United Arab Emirates";
	}
	if (countryCode == "AF")
	{
		countryString = "Afghanistan";
	}
	if (countryCode == "AG")
	{
		countryString = "Antigua and Barbuda";
	}
	if (countryCode == "AI")
	{
		countryString = "Anguilla";
	}
	if (countryCode == "AL")
	{
		countryString = "Albania";
	}
	if (countryCode == "AM")
	{
		countryString = "Armenia";
	}
	if (countryCode == "AO")
	{
		countryString = "Angola";
	}
	if (countryCode == "AQ")
	{
		countryString = "Antarctica";
	}
	if (countryCode == "AR")
	{
		countryString = "Argentina";
	}
	if (countryCode == "AS")
	{
		countryString = "American Samoa";
	}
	if (countryCode == "AT")
	{
		countryString = "Austria";
	}
	if (countryCode == "AU")
	{
		countryString = "Australia";
	}
	if (countryCode == "AW")
	{
		countryString = "Aruba";
	}
	if (countryCode == "AX")
	{
		countryString = "Aland Islands";
	}
	if (countryCode == "AZ")
	{
		countryString = "Azerbaijan";
	}
	if (countryCode == "BA")
	{
		countryString = "Bosnia and Herzegovina";
	}
	if (countryCode == "BB")
	{
		countryString = "Barbados";
	}
	if (countryCode == "BD")
	{
		countryString = "Bangladesh";
	}
	if (countryCode == "BE")
	{
		countryString = "Belgium";
	}
	if (countryCode == "BF")
	{
		countryString = "Burkina Faso";
	}
	if (countryCode == "BG")
	{
		countryString = "Bulgaria";
	}
	if (countryCode == "BH")
	{
		countryString = "Bahrain";
	}
	if (countryCode == "BI")
	{
		countryString = "Burundi";
	}
	if (countryCode == "BJ")
	{
		countryString = "Benin";
	}
	if (countryCode == "BL")
	{
		countryString = "Saint Barthelemy";
	}
	if (countryCode == "BM")
	{
		countryString = "Bermuda";
	}
	if (countryCode == "BN")
	{
		countryString = "Brunei";
	}
	if (countryCode == "BO")
	{
		countryString = "Bolivia";
	}
	if (countryCode == "BQ")
	{
		countryString = "Bonaire- Saint Eustatius and Saba";
	}
	if (countryCode == "BR")
	{
		countryString = "Brazil";
	}
	if (countryCode == "BS")
	{
		countryString = "Bahamas";
	}
	if (countryCode == "BT")
	{
		countryString = "Bhutan";
	}
	if (countryCode == "BV")
	{
		countryString = "Bouvet Island";
	}
	if (countryCode == "BW")
	{
		countryString = "Botswana";
	}
	if (countryCode == "BY")
	{
		countryString = "Belarus";
	}
	if (countryCode == "BZ")
	{
		countryString = "Belize";
	}
	if (countryCode == "CA")
	{
		countryString = "Canada";
	}
	if (countryCode == "CC")
	{
		countryString = "Cocos Islands";
	}
	if (countryCode == "CD")
	{
		countryString = "Democratic Republic of the Congo";
	}
	if (countryCode == "CF")
	{
		countryString = "Central African Republic";
	}
	if (countryCode == "CG")
	{
		countryString = "Republic of the Congo";
	}
	if (countryCode == "CH")
	{
		countryString = "Switzerland";
	}
	if (countryCode == "CI")
	{
		countryString = "Ivory Coast";
	}
	if (countryCode == "CK")
	{
		countryString = "Cook Islands";
	}
	if (countryCode == "CL")
	{
		countryString = "Chile";
	}
	if (countryCode == "CM")
	{
		countryString = "Cameroon";
	}
	if (countryCode == "CN")
	{
		countryString = "China";
	}
	if (countryCode == "CO")
	{
		countryString = "Colombia";
	}
	if (countryCode == "CR")
	{
		countryString = "Costa Rica";
	}
	if (countryCode == "CU")
	{
		countryString = "Cuba";
	}
	if (countryCode == "CV")
	{
		countryString = "Cape Verde";
	}
	if (countryCode == "CW")
	{
		countryString = "Curacao";
	}
	if (countryCode == "CX")
	{
		countryString = "Christmas Island";
	}
	if (countryCode == "CY")
	{
		countryString = "Cyprus";
	}
	if (countryCode == "CZ")
	{
		countryString = "Czech Republic";
	}
	if (countryCode == "DE")
	{
		countryString = "Germany";
	}
	if (countryCode == "DJ")
	{
		countryString = "Djibouti";
	}
	if (countryCode == "DK")
	{
		countryString = "Denmark";
	}
	if (countryCode == "DM")
	{
		countryString = "Dominica";
	}
	if (countryCode == "DO")
	{
		countryString = "Dominican Republic";
	}
	if (countryCode == "DZ")
	{
		countryString = "Algeria";
	}
	if (countryCode == "EC")
	{
		countryString = "Ecuador";
	}
	if (countryCode == "EE")
	{
		countryString = "Estonia";
	}
	if (countryCode == "EG")
	{
		countryString = "Egypt";
	}
	if (countryCode == "EH")
	{
		countryString = "Western Sahara";
	}
	if (countryCode == "ER")
	{
		countryString = "Eritrea";
	}
	if (countryCode == "ES")
	{
		countryString = "Spain";
	}
	if (countryCode == "ET")
	{
		countryString = "Ethiopia";
	}
	if (countryCode == "FI")
	{
		countryString = "Finland";
	}
	if (countryCode == "FJ")
	{
		countryString = "Fiji";
	}
	if (countryCode == "FK")
	{
		countryString = "Falkland Islands";
	}
	if (countryCode == "FM")
	{
		countryString = "Micronesia";
	}
	if (countryCode == "FO")
	{
		countryString = "Faroe Islands";
	}
	if (countryCode == "FR")
	{
		countryString = "France";
	}
	if (countryCode == "GA")
	{
		countryString = "Gabon";
	}
	if (countryCode == "GB")
	{
		countryString = "United Kingdom";
	}
	if (countryCode == "GD")
	{
		countryString = "Grenada";
	}
	if (countryCode == "GE")
	{
		countryString = "Georgia";
	}
	if (countryCode == "GF")
	{
		countryString = "French Guiana";
	}
	if (countryCode == "GG")
	{
		countryString = "Guernsey";
	}
	if (countryCode == "GH")
	{
		countryString = "Ghana";
	}
	if (countryCode == "GI")
	{
		countryString = "Gibraltar";
	}
	if (countryCode == "GL")
	{
		countryString = "Greenland";
	}
	if (countryCode == "GM")
	{
		countryString = "Gambia";
	}
	if (countryCode == "GN")
	{
		countryString = "Guinea";
	}
	if (countryCode == "GP")
	{
		countryString = "Guadeloupe";
	}
	if (countryCode == "GQ")
	{
		countryString = "Equatorial Guinea";
	}
	if (countryCode == "GR")
	{
		countryString = "Greece";
	}
	if (countryCode == "GS")
	{
		countryString = "South Georgia and the South Sandwich Islands";
	}
	if (countryCode == "GT")
	{
		countryString = "Guatemala";
	}
	if (countryCode == "GU")
	{
		countryString = "Guam";
	}
	if (countryCode == "GW")
	{
		countryString = "Guinea-Bissau";
	}
	if (countryCode == "GY")
	{
		countryString = "Guyana";
	}
	if (countryCode == "HK")
	{
		countryString = "Hong Kong";
	}
	if (countryCode == "HM")
	{
		countryString = "Heard Island and McDonald Islands";
	}
	if (countryCode == "HN")
	{
		countryString = "Honduras";
	}
	if (countryCode == "HR")
	{
		countryString = "Croatia";
	}
	if (countryCode == "HT")
	{
		countryString = "Haiti";
	}
	if (countryCode == "HU")
	{
		countryString = "Hungary";
	}
	if (countryCode == "ID")
	{
		countryString = "Indonesia";
	}
	if (countryCode == "IE")
	{
		countryString = "Ireland";
	}
	if (countryCode == "IL")
	{
		countryString = "Israel";
	}
	if (countryCode == "IM")
	{
		countryString = "Isle of Man";
	}
	if (countryCode == "IN")
	{
		countryString = "India";
	}
	if (countryCode == "IO")
	{
		countryString = "British Indian Ocean Territory";
	}
	if (countryCode == "IQ")
	{
		countryString = "Iraq";
	}
	if (countryCode == "IR")
	{
		countryString = "Iran";
	}
	if (countryCode == "IS")
	{
		countryString = "Iceland";
	}
	if (countryCode == "IT")
	{
		countryString = "Italy";
	}
	if (countryCode == "JE")
	{
		countryString = "Jersey";
	}
	if (countryCode == "JM")
	{
		countryString = "Jamaica";
	}
	if (countryCode == "JO")
	{
		countryString = "Jordan";
	}
	if (countryCode == "JP")
	{
		countryString = "Japan";
	}
	if (countryCode == "KE")
	{
		countryString = "Kenya";
	}
	if (countryCode == "KG")
	{
		countryString = "Kyrgyzstan";
	}
	if (countryCode == "KH")
	{
		countryString = "Cambodia";
	}
	if (countryCode == "KI")
	{
		countryString = "Kiribati";
	}
	if (countryCode == "KM")
	{
		countryString = "Comoros";
	}
	if (countryCode == "KN")
	{
		countryString = "Saint Kitts and Nevis";
	}
	if (countryCode == "KP")
	{
		countryString = "North Korea";
	}
	if (countryCode == "KR")
	{
		countryString = "South Korea";
	}
	if (countryCode == "XK")
	{
		countryString = "Kosovo";
	}
	if (countryCode == "KW")
	{
		countryString = "Kuwait";
	}
	if (countryCode == "KY")
	{
		countryString = "Cayman Islands";
	}
	if (countryCode == "KZ")
	{
		countryString = "Kazakhstan";
	}
	if (countryCode == "LA")
	{
		countryString = "Laos";
	}
	if (countryCode == "LB")
	{
		countryString = "Lebanon";
	}
	if (countryCode == "LC")
	{
		countryString = "Saint Lucia";
	}
	if (countryCode == "LI")
	{
		countryString = "Liechtenstein";
	}
	if (countryCode == "LK")
	{
		countryString = "Sri Lanka";
	}
	if (countryCode == "LR")
	{
		countryString = "Liberia";
	}
	if (countryCode == "LS")
	{
		countryString = "Lesotho";
	}
	if (countryCode == "LT")
	{
		countryString = "Lithuania";
	}
	if (countryCode == "LU")
	{
		countryString = "Luxembourg";
	}
	if (countryCode == "LV")
	{
		countryString = "Latvia";
	}
	if (countryCode == "LY")
	{
		countryString = "Libya";
	}
	if (countryCode == "MA")
	{
		countryString = "Morocco";
	}
	if (countryCode == "MC")
	{
		countryString = "Monaco";
	}
	if (countryCode == "MD")
	{
		countryString = "Moldova";
	}
	if (countryCode == "ME")
	{
		countryString = "Montenegro";
	}
	if (countryCode == "MF")
	{
		countryString = "Saint Martin";
	}
	if (countryCode == "MG")
	{
		countryString = "Madagascar";
	}
	if (countryCode == "MH")
	{
		countryString = "Marshall Islands";
	}
	if (countryCode == "MK")
	{
		countryString = "Macedonia";
	}
	if (countryCode == "ML")
	{
		countryString = "Mali";
	}
	if (countryCode == "MM")
	{
		countryString = "Myanmar";
	}
	if (countryCode == "MN")
	{
		countryString = "Mongolia";
	}
	if (countryCode == "MO")
	{
		countryString = "Macao";
	}
	if (countryCode == "MP")
	{
		countryString = "Northern Mariana Islands";
	}
	if (countryCode == "MQ")
	{
		countryString = "Martinique";
	}
	if (countryCode == "MR")
	{
		countryString = "Mauritania";
	}
	if (countryCode == "MS")
	{
		countryString = "Montserrat";
	}
	if (countryCode == "MT")
	{
		countryString = "Malta";
	}
	if (countryCode == "MU")
	{
		countryString = "Mauritius";
	}
	if (countryCode == "MV")
	{
		countryString = "Maldives";
	}
	if (countryCode == "MW")
	{
		countryString = "Malawi";
	}
	if (countryCode == "MX")
	{
		countryString = "Mexico";
	}
	if (countryCode == "MY")
	{
		countryString = "Malaysia";
	}
	if (countryCode == "MZ")
	{
		countryString = "Mozambique";
	}
	if (countryCode == "NA")
	{
		countryString = "Namibia";
	}
	if (countryCode == "NC")
	{
		countryString = "New Caledonia";
	}
	if (countryCode == "NE")
	{
		countryString = "Niger";
	}
	if (countryCode == "NF")
	{
		countryString = "Norfolk Island";
	}
	if (countryCode == "NG")
	{
		countryString = "Nigeria";
	}
	if (countryCode == "NI")
	{
		countryString = "Nicaragua";
	}
	if (countryCode == "NL")
	{
		countryString = "Netherlands";
	}
	if (countryCode == "NO")
	{
		countryString = "Norway";
	}
	if (countryCode == "NP")
	{
		countryString = "Nepal";
	}
	if (countryCode == "NR")
	{
		countryString = "Nauru";
	}
	if (countryCode == "NU")
	{
		countryString = "Niue";
	}
	if (countryCode == "NZ")
	{
		countryString = "New Zealand";
	}
	if (countryCode == "OM")
	{
		countryString = "Oman";
	}
	if (countryCode == "PA")
	{
		countryString = "Panama";
	}
	if (countryCode == "PE")
	{
		countryString = "Peru";
	}
	if (countryCode == "PF")
	{
		countryString = "French Polynesia";
	}
	if (countryCode == "PG")
	{
		countryString = "Papua New Guinea";
	}
	if (countryCode == "PH")
	{
		countryString = "Philippines";
	}
	if (countryCode == "PK")
	{
		countryString = "Pakistan";
	}
	if (countryCode == "PL")
	{
		countryString = "Poland";
	}
	if (countryCode == "PM")
	{
		countryString = "Saint Pierre and Miquelon";
	}
	if (countryCode == "PN")
	{
		countryString = "Pitcairn";
	}
	if (countryCode == "PR")
	{
		countryString = "Puerto Rico";
	}
	if (countryCode == "PS")
	{
		countryString = "Palestinian Territory";
	}
	if (countryCode == "PT")
	{
		countryString = "Portugal";
	}
	if (countryCode == "PW")
	{
		countryString = "Palau";
	}
	if (countryCode == "PY")
	{
		countryString = "Paraguay";
	}
	if (countryCode == "QA")
	{
		countryString = "Qatar";
	}
	if (countryCode == "RE")
	{
		countryString = "Reunion";
	}
	if (countryCode == "RO")
	{
		countryString = "Romania";
	}
	if (countryCode == "RS")
	{
		countryString = "Serbia";
	}
	if (countryCode == "RU")
	{
		countryString = "Russia";
	}
	if (countryCode == "RW")
	{
		countryString = "Rwanda";
	}
	if (countryCode == "SA")
	{
		countryString = "Saudi Arabia";
	}
	if (countryCode == "SB")
	{
		countryString = "Solomon Islands";
	}
	if (countryCode == "SC")
	{
		countryString = "Seychelles";
	}
	if (countryCode == "SD")
	{
		countryString = "Sudan";
	}
	if (countryCode == "SS")
	{
		countryString = "South Sudan";
	}
	if (countryCode == "SE")
	{
		countryString = "Sweden";
	}
	if (countryCode == "SG")
	{
		countryString = "Singapore";
	}
	if (countryCode == "SH")
	{
		countryString = "Saint Helena";
	}
	if (countryCode == "SI")
	{
		countryString = "Slovenia";
	}
	if (countryCode == "SJ")
	{
		countryString = "Svalbard and Jan Mayen";
	}
	if (countryCode == "SK")
	{
		countryString = "Slovakia";
	}
	if (countryCode == "SL")
	{
		countryString = "Sierra Leone";
	}
	if (countryCode == "SM")
	{
		countryString = "San Marino";
	}
	if (countryCode == "SN")
	{
		countryString = "Senegal";
	}
	if (countryCode == "SO")
	{
		countryString = "Somalia";
	}
	if (countryCode == "SR")
	{
		countryString = "Suriname";
	}
	if (countryCode == "ST")
	{
		countryString = "Sao Tome and Principe";
	}
	if (countryCode == "SV")
	{
		countryString = "El Salvador";
	}
	if (countryCode == "SX")
	{
		countryString = "Sint Maarten";
	}
	if (countryCode == "SY")
	{
		countryString = "Syria";
	}
	if (countryCode == "SZ")
	{
		countryString = "Swaziland";
	}
	if (countryCode == "TC")
	{
		countryString = "Turks and Caicos Islands";
	}
	if (countryCode == "TD")
	{
		countryString = "Chad";
	}
	if (countryCode == "TF")
	{
		countryString = "French Southern Territories";
	}
	if (countryCode == "TG")
	{
		countryString = "Togo";
	}
	if (countryCode == "TH")
	{
		countryString = "Thailand";
	}
	if (countryCode == "TJ")
	{
		countryString = "Tajikistan";
	}
	if (countryCode == "TK")
	{
		countryString = "Tokelau";
	}
	if (countryCode == "TL")
	{
		countryString = "East Timor";
	}
	if (countryCode == "TM")
	{
		countryString = "Turkmenistan";
	}
	if (countryCode == "TN")
	{
		countryString = "Tunisia";
	}
	if (countryCode == "TO")
	{
		countryString = "Tonga";
	}
	if (countryCode == "TR")
	{
		countryString = "Turkey";
	}
	if (countryCode == "TT")
	{
		countryString = "Trinidad and Tobago";
	}
	if (countryCode == "TV")
	{
		countryString = "Tuvalu";
	}
	if (countryCode == "TW")
	{
		countryString = "Taiwan";
	}
	if (countryCode == "TZ")
	{
		countryString = "Tanzania";
	}
	if (countryCode == "UA")
	{
		countryString = "Ukraine";
	}
	if (countryCode == "UG")
	{
		countryString = "Uganda";
	}
	if (countryCode == "UM")
	{
		countryString = "United States Minor Outlying Islands";
	}
	if (countryCode == "US")
	{
		countryString = "United States";
	}
	if (countryCode == "UY")
	{
		countryString = "Uruguay";
	}
	if (countryCode == "UZ")
	{
		countryString = "Uzbekistan";
	}
	if (countryCode == "VA")
	{
		countryString = "Vatican";
	}
	if (countryCode == "VC")
	{
		countryString = "Saint Vincent and the Grenadines";
	}
	if (countryCode == "VE")
	{
		countryString = "Venezuela";
	}
	if (countryCode == "VG")
	{
		countryString = "British Virgin Islands";
	}
	if (countryCode == "VI")
	{
		countryString = "U.S. Virgin Islands";
	}
	if (countryCode == "VN")
	{
		countryString = "Vietnam";
	}
	if (countryCode == "VU")
	{
		countryString = "Vanuatu";
	}
	if (countryCode == "WF")
	{
		countryString = "Wallis and Futuna";
	}
	if (countryCode == "WS")
	{
		countryString = "Samoa";
	}
	if (countryCode == "YE")
	{
		countryString = "Yemen";
	}
	if (countryCode == "YT")
	{
		countryString = "Mayotte";
	}
	if (countryCode == "ZA")
	{
		countryString = "South Africa";
	}
	if (countryCode == "ZM")
	{
		countryString = "Zambia";
	}
	if (countryCode == "ZW")
	{
		countryString = "Zimbabwe";
	}
	if (countryCode == "CS")
	{
		countryString = "Serbia and Montenegro";
	}
	if (countryCode == "AN")
	{
		countryString = "Netherlands Antilles";
	}

	return countryString;
}

string GameSave::getCountryCodeFromCountryString(const string& countryString)
{
	string countryCode = "US";

	if (countryString == "Andorra")
	{
		countryCode = "AD";
	}
	if (countryString == "United Arab Emirates")
	{
		countryCode = "AE";
	}
	if (countryString == "Afghanistan")
	{
		countryCode = "AF";
	}
	if (countryString == "Antigua and Barbuda")
	{
		countryCode = "AG";
	}
	if (countryString == "Anguilla")
	{
		countryCode = "AI";
	}
	if (countryString == "Albania")
	{
		countryCode = "AL";
	}
	if (countryString == "Armenia")
	{
		countryCode = "AM";
	}
	if (countryString == "Angola")
	{
		countryCode = "AO";
	}
	if (countryString == "Antarctica")
	{
		countryCode = "AQ";
	}
	if (countryString == "Argentina")
	{
		countryCode = "AR";
	}
	if (countryString == "American Samoa")
	{
		countryCode = "AS";
	}
	if (countryString == "Austria")
	{
		countryCode = "AT";
	}
	if (countryString == "Australia")
	{
		countryCode = "AU";
	}
	if (countryString == "Aruba")
	{
		countryCode = "AW";
	}
	if (countryString == "Aland Islands")
	{
		countryCode = "AX";
	}
	if (countryString == "Azerbaijan")
	{
		countryCode = "AZ";
	}
	if (countryString == "Bosnia and Herzegovina")
	{
		countryCode = "BA";
	}
	if (countryString == "Barbados")
	{
		countryCode = "BB";
	}
	if (countryString == "Bangladesh")
	{
		countryCode = "BD";
	}
	if (countryString == "Belgium")
	{
		countryCode = "BE";
	}
	if (countryString == "Burkina Faso")
	{
		countryCode = "BF";
	}
	if (countryString == "Bulgaria")
	{
		countryCode = "BG";
	}
	if (countryString == "Bahrain")
	{
		countryCode = "BH";
	}
	if (countryString == "Burundi")
	{
		countryCode = "BI";
	}
	if (countryString == "Benin")
	{
		countryCode = "BJ";
	}
	if (countryString == "Saint Barthelemy")
	{
		countryCode = "BL";
	}
	if (countryString == "Bermuda")
	{
		countryCode = "BM";
	}
	if (countryString == "Brunei")
	{
		countryCode = "BN";
	}
	if (countryString == "Bolivia")
	{
		countryCode = "BO";
	}
	if (countryString == "Bonaire- Saint Eustatius and Saba")
	{
		countryCode = "BQ";
	}
	if (countryString == "Brazil")
	{
		countryCode = "BR";
	}
	if (countryString == "Bahamas")
	{
		countryCode = "BS";
	}
	if (countryString == "Bhutan")
	{
		countryCode = "BT";
	}
	if (countryString == "Bouvet Island")
	{
		countryCode = "BV";
	}
	if (countryString == "Botswana")
	{
		countryCode = "BW";
	}
	if (countryString == "Belarus")
	{
		countryCode = "BY";
	}
	if (countryString == "Belize")
	{
		countryCode = "BZ";
	}
	if (countryString == "Canada")
	{
		countryCode = "CA";
	}
	if (countryString == "Cocos Islands")
	{
		countryCode = "CC";
	}
	if (countryString == "Democratic Republic of the Congo")
	{
		countryCode = "CD";
	}
	if (countryString == "Central African Republic")
	{
		countryCode = "CF";
	}
	if (countryString == "Republic of the Congo")
	{
		countryCode = "CG";
	}
	if (countryString == "Switzerland")
	{
		countryCode = "CH";
	}
	if (countryString == "Ivory Coast")
	{
		countryCode = "CI";
	}
	if (countryString == "Cook Islands")
	{
		countryCode = "CK";
	}
	if (countryString == "Chile")
	{
		countryCode = "CL";
	}
	if (countryString == "Cameroon")
	{
		countryCode = "CM";
	}
	if (countryString == "China")
	{
		countryCode = "CN";
	}
	if (countryString == "Colombia")
	{
		countryCode = "CO";
	}
	if (countryString == "Costa Rica")
	{
		countryCode = "CR";
	}
	if (countryString == "Cuba")
	{
		countryCode = "CU";
	}
	if (countryString == "Cape Verde")
	{
		countryCode = "CV";
	}
	if (countryString == "Curacao")
	{
		countryCode = "CW";
	}
	if (countryString == "Christmas Island")
	{
		countryCode = "CX";
	}
	if (countryString == "Cyprus")
	{
		countryCode = "CY";
	}
	if (countryString == "Czech Republic")
	{
		countryCode = "CZ";
	}
	if (countryString == "Germany")
	{
		countryCode = "DE";
	}
	if (countryString == "Djibouti")
	{
		countryCode = "DJ";
	}
	if (countryString == "Denmark")
	{
		countryCode = "DK";
	}
	if (countryString == "Dominica")
	{
		countryCode = "DM";
	}
	if (countryString == "Dominican Republic")
	{
		countryCode = "DO";
	}
	if (countryString == "Algeria")
	{
		countryCode = "DZ";
	}
	if (countryString == "Ecuador")
	{
		countryCode = "EC";
	}
	if (countryString == "Estonia")
	{
		countryCode = "EE";
	}
	if (countryString == "Egypt")
	{
		countryCode = "EG";
	}
	if (countryString == "Western Sahara")
	{
		countryCode = "EH";
	}
	if (countryString == "Eritrea")
	{
		countryCode = "ER";
	}
	if (countryString == "Spain")
	{
		countryCode = "ES";
	}
	if (countryString == "Ethiopia")
	{
		countryCode = "ET";
	}
	if (countryString == "Finland")
	{
		countryCode = "FI";
	}
	if (countryString == "Fiji")
	{
		countryCode = "FJ";
	}
	if (countryString == "Falkland Islands")
	{
		countryCode = "FK";
	}
	if (countryString == "Micronesia")
	{
		countryCode = "FM";
	}
	if (countryString == "Faroe Islands")
	{
		countryCode = "FO";
	}
	if (countryString == "France")
	{
		countryCode = "FR";
	}
	if (countryString == "Gabon")
	{
		countryCode = "GA";
	}
	if (countryString == "United Kingdom")
	{
		countryCode = "GB";
	}
	if (countryString == "Grenada")
	{
		countryCode = "GD";
	}
	if (countryString == "Georgia")
	{
		countryCode = "GE";
	}
	if (countryString == "French Guiana")
	{
		countryCode = "GF";
	}
	if (countryString == "Guernsey")
	{
		countryCode = "GG";
	}
	if (countryString == "Ghana")
	{
		countryCode = "GH";
	}
	if (countryString == "Gibraltar")
	{
		countryCode = "GI";
	}
	if (countryString == "Greenland")
	{
		countryCode = "GL";
	}
	if (countryString == "Gambia")
	{
		countryCode = "GM";
	}
	if (countryString == "Guinea")
	{
		countryCode = "GN";
	}
	if (countryString == "Guadeloupe")
	{
		countryCode = "GP";
	}
	if (countryString == "Equatorial Guinea")
	{
		countryCode = "GQ";
	}
	if (countryString == "Greece")
	{
		countryCode = "GR";
	}
	if (countryString == "South Georgia and the South Sandwich Islands")
	{
		countryCode = "GS";
	}
	if (countryString == "Guatemala")
	{
		countryCode = "GT";
	}
	if (countryString == "Guam")
	{
		countryCode = "GU";
	}
	if (countryString == "Guinea-Bissau")
	{
		countryCode = "GW";
	}
	if (countryString == "Guyana")
	{
		countryCode = "GY";
	}
	if (countryString == "Hong Kong")
	{
		countryCode = "HK";
	}
	if (countryString == "Heard Island and McDonald Islands")
	{
		countryCode = "HM";
	}
	if (countryString == "Honduras")
	{
		countryCode = "HN";
	}
	if (countryString == "Croatia")
	{
		countryCode = "HR";
	}
	if (countryString == "Haiti")
	{
		countryCode = "HT";
	}
	if (countryString == "Hungary")
	{
		countryCode = "HU";
	}
	if (countryString == "Indonesia")
	{
		countryCode = "ID";
	}
	if (countryString == "Ireland")
	{
		countryCode = "IE";
	}
	if (countryString == "Israel")
	{
		countryCode = "IL";
	}
	if (countryString == "Isle of Man")
	{
		countryCode = "IM";
	}
	if (countryString == "India")
	{
		countryCode = "IN";
	}
	if (countryString == "British Indian Ocean Territory")
	{
		countryCode = "IO";
	}
	if (countryString == "Iraq")
	{
		countryCode = "IQ";
	}
	if (countryString == "Iran")
	{
		countryCode = "IR";
	}
	if (countryString == "Iceland")
	{
		countryCode = "IS";
	}
	if (countryString == "Italy")
	{
		countryCode = "IT";
	}
	if (countryString == "Jersey")
	{
		countryCode = "JE";
	}
	if (countryString == "Jamaica")
	{
		countryCode = "JM";
	}
	if (countryString == "Jordan")
	{
		countryCode = "JO";
	}
	if (countryString == "Japan")
	{
		countryCode = "JP";
	}
	if (countryString == "Kenya")
	{
		countryCode = "KE";
	}
	if (countryString == "Kyrgyzstan")
	{
		countryCode = "KG";
	}
	if (countryString == "Cambodia")
	{
		countryCode = "KH";
	}
	if (countryString == "Kiribati")
	{
		countryCode = "KI";
	}
	if (countryString == "Comoros")
	{
		countryCode = "KM";
	}
	if (countryString == "Saint Kitts and Nevis")
	{
		countryCode = "KN";
	}
	if (countryString == "North Korea")
	{
		countryCode = "KP";
	}
	if (countryString == "South Korea")
	{
		countryCode = "KR";
	}
	if (countryString == "Kosovo")
	{
		countryCode = "XK";
	}
	if (countryString == "Kuwait")
	{
		countryCode = "KW";
	}
	if (countryString == "Cayman Islands")
	{
		countryCode = "KY";
	}
	if (countryString == "Kazakhstan")
	{
		countryCode = "KZ";
	}
	if (countryString == "Laos")
	{
		countryCode = "LA";
	}
	if (countryString == "Lebanon")
	{
		countryCode = "LB";
	}
	if (countryString == "Saint Lucia")
	{
		countryCode = "LC";
	}
	if (countryString == "Liechtenstein")
	{
		countryCode = "LI";
	}
	if (countryString == "Sri Lanka")
	{
		countryCode = "LK";
	}
	if (countryString == "Liberia")
	{
		countryCode = "LR";
	}
	if (countryString == "Lesotho")
	{
		countryCode = "LS";
	}
	if (countryString == "Lithuania")
	{
		countryCode = "LT";
	}
	if (countryString == "Luxembourg")
	{
		countryCode = "LU";
	}
	if (countryString == "Latvia")
	{
		countryCode = "LV";
	}
	if (countryString == "Libya")
	{
		countryCode = "LY";
	}
	if (countryString == "Morocco")
	{
		countryCode = "MA";
	}
	if (countryString == "Monaco")
	{
		countryCode = "MC";
	}
	if (countryString == "Moldova")
	{
		countryCode = "MD";
	}
	if (countryString == "Montenegro")
	{
		countryCode = "ME";
	}
	if (countryString == "Saint Martin")
	{
		countryCode = "MF";
	}
	if (countryString == "Madagascar")
	{
		countryCode = "MG";
	}
	if (countryString == "Marshall Islands")
	{
		countryCode = "MH";
	}
	if (countryString == "Macedonia")
	{
		countryCode = "MK";
	}
	if (countryString == "Mali")
	{
		countryCode = "ML";
	}
	if (countryString == "Myanmar")
	{
		countryCode = "MM";
	}
	if (countryString == "Mongolia")
	{
		countryCode = "MN";
	}
	if (countryString == "Macao")
	{
		countryCode = "MO";
	}
	if (countryString == "Northern Mariana Islands")
	{
		countryCode = "MP";
	}
	if (countryString == "Martinique")
	{
		countryCode = "MQ";
	}
	if (countryString == "Mauritania")
	{
		countryCode = "MR";
	}
	if (countryString == "Montserrat")
	{
		countryCode = "MS";
	}
	if (countryString == "Malta")
	{
		countryCode = "MT";
	}
	if (countryString == "Mauritius")
	{
		countryCode = "MU";
	}
	if (countryString == "Maldives")
	{
		countryCode = "MV";
	}
	if (countryString == "Malawi")
	{
		countryCode = "MW";
	}
	if (countryString == "Mexico")
	{
		countryCode = "MX";
	}
	if (countryString == "Malaysia")
	{
		countryCode = "MY";
	}
	if (countryString == "Mozambique")
	{
		countryCode = "MZ";
	}
	if (countryString == "Namibia")
	{
		countryCode = "NA";
	}
	if (countryString == "New Caledonia")
	{
		countryCode = "NC";
	}
	if (countryString == "Niger")
	{
		countryCode = "NE";
	}
	if (countryString == "Norfolk Island")
	{
		countryCode = "NF";
	}
	if (countryString == "Nigeria")
	{
		countryCode = "NG";
	}
	if (countryString == "Nicaragua")
	{
		countryCode = "NI";
	}
	if (countryString == "Netherlands")
	{
		countryCode = "NL";
	}
	if (countryString == "Norway")
	{
		countryCode = "NO";
	}
	if (countryString == "Nepal")
	{
		countryCode = "NP";
	}
	if (countryString == "Nauru")
	{
		countryCode = "NR";
	}
	if (countryString == "Niue")
	{
		countryCode = "NU";
	}
	if (countryString == "New Zealand")
	{
		countryCode = "NZ";
	}
	if (countryString == "Oman")
	{
		countryCode = "OM";
	}
	if (countryString == "Panama")
	{
		countryCode = "PA";
	}
	if (countryString == "Peru")
	{
		countryCode = "PE";
	}
	if (countryString == "French Polynesia")
	{
		countryCode = "PF";
	}
	if (countryString == "Papua New Guinea")
	{
		countryCode = "PG";
	}
	if (countryString == "Philippines")
	{
		countryCode = "PH";
	}
	if (countryString == "Pakistan")
	{
		countryCode = "PK";
	}
	if (countryString == "Poland")
	{
		countryCode = "PL";
	}
	if (countryString == "Saint Pierre and Miquelon")
	{
		countryCode = "PM";
	}
	if (countryString == "Pitcairn")
	{
		countryCode = "PN";
	}
	if (countryString == "Puerto Rico")
	{
		countryCode = "PR";
	}
	if (countryString == "Palestinian Territory")
	{
		countryCode = "PS";
	}
	if (countryString == "Portugal")
	{
		countryCode = "PT";
	}
	if (countryString == "Palau")
	{
		countryCode = "PW";
	}
	if (countryString == "Paraguay")
	{
		countryCode = "PY";
	}
	if (countryString == "Qatar")
	{
		countryCode = "QA";
	}
	if (countryString == "Reunion")
	{
		countryCode = "RE";
	}
	if (countryString == "Romania")
	{
		countryCode = "RO";
	}
	if (countryString == "Serbia")
	{
		countryCode = "RS";
	}
	if (countryString == "Russia")
	{
		countryCode = "RU";
	}
	if (countryString == "Rwanda")
	{
		countryCode = "RW";
	}
	if (countryString == "Saudi Arabia")
	{
		countryCode = "SA";
	}
	if (countryString == "Solomon Islands")
	{
		countryCode = "SB";
	}
	if (countryString == "Seychelles")
	{
		countryCode = "SC";
	}
	if (countryString == "Sudan")
	{
		countryCode = "SD";
	}
	if (countryString == "South Sudan")
	{
		countryCode = "SS";
	}
	if (countryString == "Sweden")
	{
		countryCode = "SE";
	}
	if (countryString == "Singapore")
	{
		countryCode = "SG";
	}
	if (countryString == "Saint Helena")
	{
		countryCode = "SH";
	}
	if (countryString == "Slovenia")
	{
		countryCode = "SI";
	}
	if (countryString == "Svalbard and Jan Mayen")
	{
		countryCode = "SJ";
	}
	if (countryString == "Slovakia")
	{
		countryCode = "SK";
	}
	if (countryString == "Sierra Leone")
	{
		countryCode = "SL";
	}
	if (countryString == "San Marino")
	{
		countryCode = "SM";
	}
	if (countryString == "Senegal")
	{
		countryCode = "SN";
	}
	if (countryString == "Somalia")
	{
		countryCode = "SO";
	}
	if (countryString == "Suriname")
	{
		countryCode = "SR";
	}
	if (countryString == "Sao Tome and Principe")
	{
		countryCode = "ST";
	}
	if (countryString == "El Salvador")
	{
		countryCode = "SV";
	}
	if (countryString == "Sint Maarten")
	{
		countryCode = "SX";
	}
	if (countryString == "Syria")
	{
		countryCode = "SY";
	}
	if (countryString == "Swaziland")
	{
		countryCode = "SZ";
	}
	if (countryString == "Turks and Caicos Islands")
	{
		countryCode = "TC";
	}
	if (countryString == "Chad")
	{
		countryCode = "TD";
	}
	if (countryString == "French Southern Territories")
	{
		countryCode = "TF";
	}
	if (countryString == "Togo")
	{
		countryCode = "TG";
	}
	if (countryString == "Thailand")
	{
		countryCode = "TH";
	}
	if (countryString == "Tajikistan")
	{
		countryCode = "TJ";
	}
	if (countryString == "Tokelau")
	{
		countryCode = "TK";
	}
	if (countryString == "East Timor")
	{
		countryCode = "TL";
	}
	if (countryString == "Turkmenistan")
	{
		countryCode = "TM";
	}
	if (countryString == "Tunisia")
	{
		countryCode = "TN";
	}
	if (countryString == "Tonga")
	{
		countryCode = "TO";
	}
	if (countryString == "Turkey")
	{
		countryCode = "TR";
	}
	if (countryString == "Trinidad and Tobago")
	{
		countryCode = "TT";
	}
	if (countryString == "Tuvalu")
	{
		countryCode = "TV";
	}
	if (countryString == "Taiwan")
	{
		countryCode = "TW";
	}
	if (countryString == "Tanzania")
	{
		countryCode = "TZ";
	}
	if (countryString == "Ukraine")
	{
		countryCode = "UA";
	}
	if (countryString == "Uganda")
	{
		countryCode = "UG";
	}
	if (countryString == "United States Minor Outlying Islands")
	{
		countryCode = "UM";
	}
	if (countryString == "United States")
	{
		countryCode = "US";
	}
	if (countryString == "Uruguay")
	{
		countryCode = "UY";
	}
	if (countryString == "Uzbekistan")
	{
		countryCode = "UZ";
	}
	if (countryString == "Vatican")
	{
		countryCode = "VA";
	}
	if (countryString == "Saint Vincent and the Grenadines")
	{
		countryCode = "VC";
	}
	if (countryString == "Venezuela")
	{
		countryCode = "VE";
	}
	if (countryString == "British Virgin Islands")
	{
		countryCode = "VG";
	}
	if (countryString == "U.S. Virgin Islands")
	{
		countryCode = "VI";
	}
	if (countryString == "Vietnam")
	{
		countryCode = "VN";
	}
	if (countryString == "Vanuatu")
	{
		countryCode = "VU";
	}
	if (countryString == "Wallis and Futuna")
	{
		countryCode = "WF";
	}
	if (countryString == "Samoa")
	{
		countryCode = "WS";
	}
	if (countryString == "Yemen")
	{
		countryCode = "YE";
	}
	if (countryString == "Mayotte")
	{
		countryCode = "YT";
	}
	if (countryString == "South Africa")
	{
		countryCode = "ZA";
	}
	if (countryString == "Zambia")
	{
		countryCode = "ZM";
	}
	if (countryString == "Zimbabwe")
	{
		countryCode = "ZW";
	}
	if (countryString == "Serbia and Montenegro")
	{
		countryCode = "CS";
	}
	if (countryString == "Netherlands Antilles")
	{
		countryCode = "AN";
	}

	return countryCode;
}

