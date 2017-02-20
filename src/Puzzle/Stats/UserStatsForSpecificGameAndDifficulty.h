//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
#include <src/Utility/Logger.h>


//===============================================================================================
//high score collects stats per user for a specific game or sequence at a specific difficulty in order to track their progress and high score
class BobsGameUserStatsForSpecificGameAndDifficulty
{//===============================================================================================
public:

	Logger log = Logger("BobsGameUserStatsForSpecificGameAndDifficulty");

	string userName = "";
	long long userID = -1;

	string isGameTypeOrSequence = "";
	string gameTypeName = "";
	string gameTypeUUID = "";
	string gameSequenceName = "";
	string gameSequenceUUID = "";
	string difficultyName = "";


	int totalGamesPlayed = 0;
	int singlePlayerGamesPlayed = 0;
	int tournamentGamesPlayed = 0;
	int localMultiplayerGamesPlayed = 0;
	int tournamentGamesWon = 0;
	int tournamentGamesLost = 0;
	int singlePlayerGamesCompleted = 0;
	int singlePlayerGamesLost = 0;
	int singlePlayerHighestLevelReached = 0;
	long long totalTimePlayed = 0;
	long long longestGameLength = 0;
	long long averageGameLength = 0;
	double eloScore = 0;
	long long firstTimePlayed = 0;
	long long lastTimePlayed = 0;

	long long planesWalkerPoints = 0;
	long long totalBlocksMade = 0;
	long long totalPiecesMade = 0;
	long long totalBlocksCleared = 0;
	long long totalPiecesPlaced = 0;
	long long totalCombosMade = 0;
	int biggestCombo = 0;



	int mostBlocksCleared = 0;
	string longestTimeStatsUUID = "";
	string mostBlocksClearedStatsUUID = "";






	//===============================================================================================
	BobsGameUserStatsForSpecificGameAndDifficulty()
	{//===============================================================================================


	}




	//===============================================================================================
	string encode()
	{//===============================================================================================

		string gameSaveString =
			"userID:`" + to_string(userID) + "`" +
			",userName:`" + userName + "`";

		gameSaveString += ",isGameTypeOrSequence:`" + isGameTypeOrSequence + "`";
		gameSaveString += ",gameTypeName:`" + gameTypeName + "`";
		gameSaveString += ",gameTypeUUID:`" + gameTypeUUID + "`";
		gameSaveString += ",gameSequenceName:`" + gameSequenceName + "`";
		gameSaveString += ",gameSequenceUUID:`" + gameSequenceUUID + "`";
		gameSaveString += ",difficultyName:`" + difficultyName + "`";


		gameSaveString += ",totalGamesPlayed:" + to_string(totalGamesPlayed);
		gameSaveString += ",singlePlayerGamesPlayed:" + to_string(singlePlayerGamesPlayed);
		gameSaveString += ",tournamentGamesPlayed:" + to_string(tournamentGamesPlayed);
		gameSaveString += ",localMultiplayerGamesPlayed:" + to_string(localMultiplayerGamesPlayed);
		gameSaveString += ",tournamentGamesWon:" + to_string(tournamentGamesWon);
		gameSaveString += ",tournamentGamesLost:" + to_string(tournamentGamesLost);
		gameSaveString += ",singlePlayerGamesCompleted:" + to_string(singlePlayerGamesCompleted);
		gameSaveString += ",singlePlayerGamesLost:" + to_string(singlePlayerGamesLost);
		gameSaveString += ",singlePlayerHighestLevelReached:" + to_string(singlePlayerHighestLevelReached);
		gameSaveString += ",totalTimePlayed:" + to_string(totalTimePlayed);
		gameSaveString += ",longestGameLength:" + to_string(longestGameLength);
		gameSaveString += ",averageGameLength:" + to_string(averageGameLength);
		gameSaveString += ",eloScore:" + to_string(eloScore);
		gameSaveString += ",firstTimePlayed:" + to_string(firstTimePlayed);
		gameSaveString += ",lastTimePlayed:" + to_string(lastTimePlayed);
		gameSaveString += ",planesWalkerPoints:" + to_string(planesWalkerPoints);
		gameSaveString += ",totalBlocksMade:" + to_string(totalBlocksMade);
		gameSaveString += ",totalPiecesMade:" + to_string(totalPiecesMade);
		gameSaveString += ",totalBlocksCleared:" + to_string(totalBlocksCleared);
		gameSaveString += ",totalPiecesPlaced:" + to_string(totalPiecesPlaced);
		gameSaveString += ",totalCombosMade:" + to_string(totalCombosMade);
		gameSaveString += ",biggestCombo:" + to_string(biggestCombo);
		gameSaveString += ",mostBlocksCleared:" + to_string(mostBlocksCleared);
		gameSaveString += ",longestTimeStatsUUID:" + longestTimeStatsUUID;
		gameSaveString += ",mostBlocksClearedStatsUUID:" + mostBlocksClearedStatsUUID;





		gameSaveString += ",";

		return gameSaveString;
	}

	//===============================================================================================
	BobsGameUserStatsForSpecificGameAndDifficulty(string &s)
	{//===============================================================================================

		decode(s);
	}


	//===============================================================================================
	void decode(string &s)
	{//===============================================================================================

	 //		"userID:"+                  	"`"+userID+"`"+
		{
			s = s.substr(s.find('`') + 1);
			string t = s.substr(0, s.find('`'));
			if (t.length()>0)try { userID = stoll(t); }
			catch (exception) {  return; }
			s = s.substr(s.find('`') + 1);

		}

		//		",userName:"+            	"`"+userName+"`"+
		{
			s = s.substr(s.find('`') + 1);
			string t = s.substr(0, s.find('`'));
			if (t.length()>0)userName = t;
			s = s.substr(s.find('`') + 1);

		}

		string t = "";

		s = s.substr(s.find('`') + 1);
		t = s.substr(0, s.find('`'));
		if (t.length()>0)isGameTypeOrSequence = t;
		s = s.substr(s.find('`') + 1);

		s = s.substr(s.find('`') + 1);
		t = s.substr(0, s.find('`'));
		if (t.length()>0)gameTypeName = t;
		s = s.substr(s.find('`') + 1);

		s = s.substr(s.find('`') + 1);
		t = s.substr(0, s.find('`'));
		if (t.length()>0)gameTypeUUID = t;
		s = s.substr(s.find('`') + 1);

		s = s.substr(s.find('`') + 1);
		t = s.substr(0, s.find('`'));
		if (t.length()>0)gameSequenceName = t;
		s = s.substr(s.find('`') + 1);

		s = s.substr(s.find('`') + 1);
		t = s.substr(0, s.find('`'));
		if (t.length()>0)gameSequenceUUID = t;
		s = s.substr(s.find('`') + 1);

		s = s.substr(s.find('`') + 1);
		t = s.substr(0, s.find('`'));
		if (t.length()>0)difficultyName = t;
		s = s.substr(s.find('`') + 1);



		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { totalGamesPlayed = stoi(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);

		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { singlePlayerGamesPlayed = stoi(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);

		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { tournamentGamesPlayed = stoi(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);

		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { localMultiplayerGamesPlayed = stoi(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);

		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { tournamentGamesWon = stoi(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);

		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { tournamentGamesLost = stoi(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);

		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { singlePlayerGamesCompleted = stoi(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);

		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { singlePlayerGamesLost = stoi(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);

		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { singlePlayerHighestLevelReached = stoi(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);


		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { totalTimePlayed = stoll(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);

		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { longestGameLength = stoll(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);

		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { averageGameLength = stoll(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);

		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { eloScore = stod(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);

		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { firstTimePlayed = stoll(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);

		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { lastTimePlayed = stoll(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);


		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { planesWalkerPoints = stoll(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);


		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { totalBlocksMade = stoll(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);


		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { totalPiecesMade = stoll(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);


		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { totalBlocksCleared = stoll(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);


		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { totalPiecesPlaced = stoll(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);


		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { totalCombosMade = stoll(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);


		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { biggestCombo = stoi(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);

		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)try { mostBlocksCleared = stoi(t); }
		catch (exception) {  return; }
		s = s.substr(s.find(',') + 1);

		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)longestTimeStatsUUID = t;
		s = s.substr(s.find(',') + 1);

		s = s.substr(s.find(':') + 1);
		t = s.substr(0, s.find(','));
		if (t.length()>0)mostBlocksClearedStatsUUID = t;
		s = s.substr(s.find(',') + 1);



	}


};
