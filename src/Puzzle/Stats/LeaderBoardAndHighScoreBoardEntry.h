//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------



#pragma once
#include "bobtypes.h"
#include <src/Utility/Logger.h>
#include <src/Utility/ArrayList.h>

//class LeaderBoardScore
//{
//public:
//	double newEloScoreForThisGameAndDifficulty = 0;
//	long newPlaneswalkerPointsForThisGameAndDifficulty = 0;
//
//	//this can't be done unless i tally all the elo scores for each userHighScore entry for a game
//	//double newEloScoreForThisGame = 0;
//	//long newPlaneswalkerPointsForThisGame = 0;
//
//	double newEloScoreForThisDifficulty = 0;
//	long newPlaneswalkerPointsForThisDifficulty = 0;
//
//	double newEloScoreOverall = 0;
//	long newPlaneswalkerPointsOverall = 0;
//
//
//	long totalTimePlayedThisGameAndDifficulty = 0;
//	long totalBlocksClearedThisGameAndDifficulty = 0;
//
//	//long totalTimePlayedThisGame = 0;
//	//long totalBlocksClearedThisGame = 0;
//
//	long totalTimePlayedThisDifficulty = 0;
//	long totalBlocksClearedThisDifficulty = 0;
//
//	long totalTimePlayedOverall = 0;
//	long totalBlocksClearedOverall = 0;
//
//
//	int mostBlocksClearedThisGameAndDifficulty = 0;
//	long longestTimeLastedThisGameAndDifficulty = 0;
//};

//===============================================================================================
//leaderboard shows the top 10 users ranked by elo score or planeswalkerpoints
//high score board shows the top 10 scores by time lasted or some other metric, blocks made, blocks cleared?
//TODO:might have to add timeSpentSpinningAtBottom and subtract that
class BobsGameLeaderBoardAndHighScoreBoard
{//===============================================================================================

public:

	Logger log = Logger("BobsGameLeaderBoardAndHighScoreBoard");


	string isGameTypeOrSequence = "";
	string gameTypeName = "";
	string gameTypeUUID = "";
	string gameSequenceName = "";
	string gameSequenceUUID = "";
	string difficultyName = "";


	class BobsGameLeaderBoardAndHighScoreBoardEntry
	{
	public:
		string userName = "";
		long userID = -1;

		//elo score should handle most of this
		int totalGamesPlayed = 0;
		int singlePlayerGamesPlayed = 0;
		int tournamentGamesPlayed = 0;
		int localMultiplayerGamesPlayed = 0;
		int tournamentGamesWon = 0;
		int tournamentGamesLost = 0;
		int singlePlayerGamesCompleted = 0;
		int singlePlayerGamesLost = 0;
		int singlePlayerHighestLevelReached = 0;
		long totalTimePlayed = 0;
		long longestGameLength = 0;
		long firstTimePlayed = 0;
		long lastTimePlayed = 0;
		long timeRecordSet = 0;
		double eloScore = 0;
		long planesWalkerPoints = 0;
		long totalBlocksCleared = 0;
		int biggestCombo = 0;
		int mostBlocksClearedInOneGame = 0;
		string statsUUID = "";


	};

	ArrayList<BobsGameLeaderBoardAndHighScoreBoardEntry*> entries;

	int maxEntries = 10;







	//===============================================================================================
	BobsGameLeaderBoardAndHighScoreBoard()
	{//===============================================================================================

		for (int i = 0; i<maxEntries; i++)
		{
			entries.add(new BobsGameLeaderBoardAndHighScoreBoardEntry());
		}

	}
//
//	//===============================================================================================
//	static BobsGameLeaderBoardAndHighScoreBoard getFromDBOrCreateNewIfNotExist(Connection databaseConnection, string databaseName, BobsGameGameStats game, bool anyGame, bool anyDifficulty)
//	{//===============================================================================================
//
//		BobsGameLeaderBoardAndHighScoreBoard stats = nullptr;
//		{
//
//			string gameTypeOrSequenceQuerystring = "";
//			string uuid = "";
//			if (game.isGameTypeOrSequence.equals("GameType"))
//			{
//				gameTypeOrSequenceQuerystring = "gameTypeUUID = ?";
//				uuid = game.gameTypeUUID;
//			}
//
//			if (game.isGameTypeOrSequence.equals("GameSequence"))
//			{
//				gameTypeOrSequenceQuerystring = "gameSequenceUUID = ?";
//				uuid = game.gameSequenceUUID;
//			}
//
//			if (anyGame)
//			{
//				gameTypeOrSequenceQuerystring = "isGameTypeOrSequence = ?";
//				uuid = "OVERALL";
//			}
//
//			string difficultyName = game.difficultyName;
//			if (anyDifficulty)
//			{
//				difficultyName = "OVERALL";
//			}
//
//			ResultSet resultSet = nullptr;
//			PreparedStatement ps = nullptr;
//
//			try
//			{
//				ps = databaseConnection.prepareStatement(
//					"SELECT " +
//					"* " +
//					"FROM " + databaseName + " WHERE " + gameTypeOrSequenceQuerystring + " AND difficultyName = ?");
//
//
//				int n = 0;
//				ps.setstring(++n, uuid);
//				ps.setstring(++n, difficultyName);
//				resultSet = ps.executeQuery();
//
//				if (resultSet.next())
//				{
//					stats = new BobsGameLeaderBoardAndHighScoreBoard(resultSet);
//				}
//
//				resultSet.close();
//				ps.close();
//
//			}
//			catch (Exception ex) { log.error("DB ERROR: " + ex.getMessage());  return nullptr; }
//		}
//
//		//create it if it doesnt exist
//		if (stats == nullptr)
//		{
//			stats = new BobsGameLeaderBoardAndHighScoreBoard();
//			stats.isGameTypeOrSequence = game.isGameTypeOrSequence;
//			stats.gameTypeUUID = game.gameTypeUUID;
//			stats.gameTypeName = game.gameTypeName;
//			stats.gameSequenceUUID = game.gameSequenceUUID;
//			stats.gameSequenceName = game.gameSequenceName;
//			stats.difficultyName = game.difficultyName;
//
//			if (anyGame)
//			{
//				stats.isGameTypeOrSequence = "OVERALL";
//				stats.gameTypeUUID = "OVERALL";
//				stats.gameTypeName = "OVERALL";
//				stats.gameSequenceUUID = "OVERALL";
//				stats.gameSequenceName = "OVERALL";
//			}
//
//			if (anyDifficulty)
//			{
//				stats.difficultyName = "OVERALL";
//			}
//
//			stats.initDB(databaseConnection, databaseName);
//		}
//
//		return stats;
//	}
//
//
//	//===============================================================================================
//	static ArrayList<BobsGameLeaderBoardAndHighScoreBoard> getAllLeaderBoardsAndHighScoreBoardsFromDB(Connection databaseConnection, string databaseName)
//	{//===============================================================================================
//
//		ArrayList<BobsGameLeaderBoardAndHighScoreBoard> leaderBoards = new ArrayList<BobsGameLeaderBoardAndHighScoreBoard>();
//
//		ResultSet resultSet = nullptr;
//		PreparedStatement ps = nullptr;
//
//
//		//bobsGameLeaderBoardsByTotalTimePlayed
//		//bobsGameLeaderBoardsByTotalBlocksCleared
//		//bobsGameLeaderBoardsByPlaneswalkerPoints
//		//bobsGameLeaderBoardsByEloScore
//
//		//bobsGameHighScoreBoardsByTimeLasted
//		//bobsGameHighScoreBoardsByBlocksCleared
//
//		try
//		{
//			ps = databaseConnection.prepareStatement(
//				"SELECT " +
//				"* " +
//				"FROM " + databaseName);
//
//
//			resultSet = ps.executeQuery();
//
//			while (resultSet.next())
//			{
//				leaderBoards.add(new BobsGameLeaderBoardAndHighScoreBoard(resultSet));
//			}
//
//			resultSet.close();
//			ps.close();
//
//
//		}
//		catch (Exception ex) { log.error("DB ERROR: " + ex.getMessage());  return nullptr; }
//
//
//		return leaderBoards;
//	}
//
//	//===============================================================================================
//	static void updateLeaderBoardsAndHighScoreBoards(Connection databaseConnection, BobsGameGameStats game, LeaderBoardScore score, BobsGameOverallUserStats userStats, BobsGameUserStatsForSpecificGameAndDifficulty gameStats)
//	{//===============================================================================================
//	 //leaderboard by game and difficulty elo score
//	 //leaderboard by game and difficulty planeswalker
//	 //leaderboard by game and difficulty total time played
//	 //leaderboard by game and difficulty total blocks cleared
//
//	 //leaderboard by game elo score
//	 //leaderboard by game planeswalker
//	 //leaderboard by game total time played
//	 //leaderboard by game total blocks cleared
//
//	 //leaderboard by difficulty elo score
//	 //leaderboard by difficulty planeswalker
//	 //leaderboard by difficulty total time played
//	 //leaderboard by difficulty total blocks cleared
//
//	 //leaderboard by elo score
//	 //leaderboard by planeswalker
//	 //leaderboard by total time played
//	 //leaderboard by total blocks cleared
//
//	 //high score board by game and difficulty blocks cleared
//	 //high score board by game and difficulty time lasted
//
//	 //high score board by game blocks cleared
//	 //high score board by game time lasted
//
//	 //high score board by difficulty blocks cleared
//	 //high score board by difficulty time lasted
//
//	 //high score board by blocks cleared
//	 //high score board by time lasted
//
//
//	 //databases:
//	 //bobsGameLeaderBoardsByTotalTimePlayed
//	 //bobsGameLeaderBoardsByTotalBlocksCleared
//	 //bobsGameLeaderBoardsByPlaneswalkerPoints
//	 //bobsGameLeaderBoardsByEloScore
//
//	 //bobsGameHighScoreBoardsByTimeLasted
//	 //bobsGameHighScoreBoardsByBlocksCleared
//
//
//
//	 //TODO: //could also do leaderboards based on:
//	 //		int totalGamesPlayed = 0;
//	 //		int singlePlayerGamesPlayed = 0;
//	 //		int tournamentGamesPlayed = 0;
//	 //		int localMultiplayerGamesPlayed = 0;
//	 //		int tournamentGamesWon = 0;
//	 //		int tournamentGamesLost = 0;
//	 //		int singlePlayerGamesCompleted = 0;
//	 //		int singlePlayerGamesLost = 0;
//	 //		int singlePlayerHighestLevelReached = 0;
//	 //		int biggestCombo = 0;
//
//		BobsGameLeaderBoardAndHighScoreBoard stats = nullptr;
//		bool needToUpdate = false;
//
//		bool anyGame = false;
//		bool anyDifficulty = false;
//		bool compareEloScore = false;
//		bool comparePlaneswalkerPoints = false;
//		bool compareBlocksCleared = false;
//		bool compareTimeLasted = false;
//		bool compareTotalBlocksCleared = false;
//		bool compareTotalTimePlayed = false;
//
//
//		//leaderboard by game and difficulty elo score
//		anyGame = false;
//		anyDifficulty = false;
//		compareEloScore = true;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = false;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameLeaderBoardsByEloScore", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameLeaderBoardsByEloScore");
//
//		//leaderboard by game and difficulty planeswalker
//		anyGame = false;
//		anyDifficulty = false;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = true;
//		compareBlocksCleared = false;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameLeaderBoardsByPlaneswalkerPoints", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameLeaderBoardsByPlaneswalkerPoints");
//
//
//		//leaderboard by game and difficulty total time played
//		anyGame = false;
//		anyDifficulty = false;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = false;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = true;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameLeaderBoardsByTotalTimePlayed", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameLeaderBoardsByTotalTimePlayed");
//
//
//		//leaderboard by game and difficulty total blocks cleared
//		anyGame = false;
//		anyDifficulty = false;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = false;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = true;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameLeaderBoardsByTotalBlocksCleared", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameLeaderBoardsByTotalBlocksCleared");
//
//
//		//leaderboard by game elo score
//		anyGame = false;
//		anyDifficulty = true;
//		compareEloScore = true;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = false;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameLeaderBoardsByEloScore", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameLeaderBoardsByEloScore");
//
//		//leaderboard by game planeswalker
//		anyGame = false;
//		anyDifficulty = true;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = true;
//		compareBlocksCleared = false;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameLeaderBoardsByPlaneswalkerPoints", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameLeaderBoardsByPlaneswalkerPoints");
//
//
//		//leaderboard by game total time played
//		anyGame = false;
//		anyDifficulty = true;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = false;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = true;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameLeaderBoardsByTotalTimePlayed", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameLeaderBoardsByTotalTimePlayed");
//
//
//		//leaderboard by game total blocks cleared
//		anyGame = false;
//		anyDifficulty = true;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = false;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = true;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameLeaderBoardsByTotalBlocksCleared", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameLeaderBoardsByTotalBlocksCleared");
//
//
//		//leaderboard by difficulty elo score
//		anyGame = true;
//		anyDifficulty = false;
//		compareEloScore = true;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = false;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameLeaderBoardsByEloScore", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameLeaderBoardsByEloScore");
//
//		//leaderboard by difficulty planeswalker
//		anyGame = true;
//		anyDifficulty = false;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = true;
//		compareBlocksCleared = false;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameLeaderBoardsByPlaneswalkerPoints", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameLeaderBoardsByPlaneswalkerPoints");
//
//
//		//leaderboard by difficulty total time played
//		anyGame = true;
//		anyDifficulty = false;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = false;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = true;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameLeaderBoardsByTotalTimePlayed", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameLeaderBoardsByTotalTimePlayed");
//
//
//		//leaderboard by difficulty total blocks cleared
//		anyGame = true;
//		anyDifficulty = false;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = false;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = true;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameLeaderBoardsByTotalBlocksCleared", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameLeaderBoardsByTotalBlocksCleared");
//
//
//		//leaderboard by elo score
//		anyGame = true;
//		anyDifficulty = true;
//		compareEloScore = true;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = false;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameLeaderBoardsByEloScore", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameLeaderBoardsByEloScore");
//
//		//leaderboard by planeswalker
//		anyGame = true;
//		anyDifficulty = true;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = true;
//		compareBlocksCleared = false;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameLeaderBoardsByPlaneswalkerPoints", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameLeaderBoardsByPlaneswalkerPoints");
//
//
//		//leaderboard by total time played
//		anyGame = true;
//		anyDifficulty = true;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = false;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = true;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameLeaderBoardsByTotalTimePlayed", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameLeaderBoardsByTotalTimePlayed");
//
//
//		//leaderboard by total blocks cleared
//		anyGame = true;
//		anyDifficulty = true;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = false;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = true;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameLeaderBoardsByTotalBlocksCleared", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameLeaderBoardsByTotalBlocksCleared");
//
//
//
//
//
//		//now get highScoreBoard by blocksCleared for this game and difficulty, create it if it doesnt exist
//		//go through top 10 and see if our score is better than any there, if so put it there
//
//
//		//high score board by game and difficulty blocks cleared
//		//high score board by game and difficulty time lasted
//
//		//high score board by game blocks cleared
//		//high score board by game time lasted
//
//		//high score board by difficulty blocks cleared
//		//high score board by difficulty time lasted
//
//		//high score board by blocks cleared
//		//high score board by time lasted
//
//		//high score board by game and difficulty blocks cleared
//		anyGame = false;
//		anyDifficulty = false;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = true;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameHighScoreBoardsByBlocksCleared", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameHighScoreBoardsByBlocksCleared");
//
//		//high score board by game and difficulty time lasted
//		anyGame = false;
//		anyDifficulty = false;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = false;
//		compareTimeLasted = true;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameHighScoreBoardsByTimeLasted", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameHighScoreBoardsByTimeLasted");
//
//
//
//		//high score board by game blocks cleared
//		anyGame = false;
//		anyDifficulty = true;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = true;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameHighScoreBoardsByBlocksCleared", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameHighScoreBoardsByBlocksCleared");
//
//		//high score board by game time lasted
//		anyGame = false;
//		anyDifficulty = true;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = false;
//		compareTimeLasted = true;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameHighScoreBoardsByTimeLasted", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameHighScoreBoardsByTimeLasted");
//
//		//high score board by difficulty blocks cleared
//		anyGame = true;
//		anyDifficulty = false;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = true;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameHighScoreBoardsByBlocksCleared", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameHighScoreBoardsByBlocksCleared");
//
//		//high score board by difficulty time lasted
//		anyGame = true;
//		anyDifficulty = false;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = false;
//		compareTimeLasted = true;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameHighScoreBoardsByTimeLasted", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameHighScoreBoardsByTimeLasted");
//
//
//
//		//high score board by blocks cleared
//		anyGame = true;
//		anyDifficulty = true;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = true;
//		compareTimeLasted = false;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameHighScoreBoardsByBlocksCleared", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameHighScoreBoardsByBlocksCleared");
//
//		//high score board by time lasted
//		anyGame = true;
//		anyDifficulty = true;
//		compareEloScore = false;
//		comparePlaneswalkerPoints = false;
//		compareBlocksCleared = false;
//		compareTimeLasted = true;
//		compareTotalBlocksCleared = false;
//		compareTotalTimePlayed = false;
//		stats = BobsGameLeaderBoardAndHighScoreBoard.getFromDBOrCreateNewIfNotExist(databaseConnection, "bobsGameHighScoreBoardsByTimeLasted", game, anyGame, anyDifficulty);
//		needToUpdate = stats.updateFromGameStatsIfNecessary(databaseConnection, game, userStats, gameStats, score, compareEloScore, anyGame, anyDifficulty, comparePlaneswalkerPoints, compareBlocksCleared, compareTimeLasted, compareTotalBlocksCleared, compareTotalTimePlayed);
//		if (needToUpdate)stats.updateDB(databaseConnection, game.userID, "bobsGameHighScoreBoardsByTimeLasted");
//
//
//
//
//	}
//
//
//
//	//===============================================================================================
//	private bool updateFromGameStatsIfNecessary(Connection databaseConnection, BobsGameGameStats game, BobsGameOverallUserStats userStats, BobsGameUserStatsForSpecificGameAndDifficulty gameStats, LeaderBoardScore score, bool anyGame, bool anyDifficulty, bool compareEloScore, bool comparePlaneswalkerPoints, bool compareBlocksCleared, bool compareTimeLasted, bool compareTotalBlocksCleared, bool compareTotalTimePlayed)
//	{//===============================================================================================
//
//
//
//	 //bool compareEloScore
//	 //bool comparePlaneswalkerPoints
//	 //bool compareBlocksCleared
//	 //bool compareTimeLasted
//	 //bool compareTotalBlocksCleared
//	 //bool compareTotalTimePlayed
//
//		for (int i = 0; i<maxEntries; i++)
//		{
//
//			BobsGameLeaderBoardAndHighScoreBoardEntry diffStats = entries.get(i);
//
//
//
//
//
//			//			double newEloScoreForThisGameAndDifficulty = 0;
//			//			long newPlaneswalkerPointsForThisGameAndDifficulty = 0;
//			//
//			//			//this can't be done unless i tally all the elo scores for each userHighScore entry for a game
//			//			//double newEloScoreForThisGame = 0;
//			//			//long newPlaneswalkerPointsForThisGame = 0;
//			//
//			//			double newEloScoreForThisDifficulty = 0;
//			//			long newPlaneswalkerPointsForThisDifficulty = 0;
//			//
//			//			double newEloScoreOverall = 0;
//			//			long newPlaneswalkerPointsOverall = 0;
//			//
//			//			long totalTimePlayedThisGameAndDifficulty = 0;
//			//			long totalBlocksClearedThisGameAndDifficulty = 0;
//			//
//			//			//long totalTimePlayedThisGame = 0;
//			//			//long totalBlocksClearedThisGame = 0;
//			//
//			//			long totalTimePlayedThisDifficulty = 0;
//			//			long totalBlocksClearedThisDifficulty = 0;
//			//
//			//			long totalTimePlayedOverall = 0;
//			//			long totalBlocksClearedOverall = 0;
//			//
//			//			long mostBlocksClearedThisGameAndDifficulty = 0;
//			//			long longestTimeLastedThisGameAndDifficulty = 0;
//
//
//			BobsGameLeaderBoardAndHighScoreBoardEntry newStats = new BobsGameLeaderBoardAndHighScoreBoardEntry();
//			newStats.userName = game.userName;
//			newStats.userID = game.userID;
//			newStats.statsUUID = game.statsUUID;
//			newStats.timeRecordSet = System.currentTimeMillis();
//
//
//			if (anyGame)
//			{
//				BobsGameUserStatsPerDifficulty stats = nullptr;
//
//				if (game.difficultyName == "Beginner")stats = userStats.bgStats_BEGINNER;
//				if (game.difficultyName == "Easy")stats = userStats.bgStats_EASY;
//				if (game.difficultyName == "Normal")stats = userStats.bgStats_NORMAL;
//				if (game.difficultyName == "Hard")stats = userStats.bgStats_HARD;
//				if (game.difficultyName == "Insane")stats = userStats.bgStats_INSANE;
//
//				//use userStats.difficulty
//				if (anyDifficulty)
//				{
//					//use userStats.overall
//					stats = userStats.bgStats_OVERALL;
//				}
//
//
//
//				newStats.totalGamesPlayed = stats.totalGamesPlayed;
//				newStats.singlePlayerGamesPlayed = stats.singlePlayerGamesPlayed;
//				newStats.tournamentGamesPlayed = stats.tournamentGamesPlayed;
//				newStats.localMultiplayerGamesPlayed = stats.localMultiplayerGamesPlayed;
//				newStats.tournamentGamesWon = stats.tournamentGamesWon;
//				newStats.tournamentGamesLost = stats.tournamentGamesLost;
//				newStats.singlePlayerGamesCompleted = stats.singlePlayerGamesCompleted;
//				newStats.singlePlayerGamesLost = stats.singlePlayerGamesLost;
//				newStats.singlePlayerHighestLevelReached = stats.singlePlayerHighestLevelReached;
//				newStats.totalTimePlayed = stats.totalTimePlayed;
//				newStats.longestGameLength = stats.longestGameLength;
//				newStats.firstTimePlayed = stats.firstTimePlayed;
//				//newStats.lastTimePlayed = 0;
//				//newStats.timeRecordSet = stats.timeRecordSet;
//				newStats.eloScore = stats.eloScore;
//				newStats.planesWalkerPoints = stats.planesWalkerPoints;
//				newStats.totalBlocksCleared = stats.totalBlocksCleared;
//				newStats.biggestCombo = stats.biggestCombo;
//				newStats.mostBlocksClearedInOneGame = stats.mostBlocksCleared;
//				//newStats.statsUUID = stats.statsUUID;
//
//			}
//			else
//			{
//				//use gameStats
//				BobsGameUserStatsForSpecificGameAndDifficulty stats = gameStats;
//
//				newStats.totalGamesPlayed = stats.totalGamesPlayed;
//				newStats.singlePlayerGamesPlayed = stats.singlePlayerGamesPlayed;
//				newStats.tournamentGamesPlayed = stats.tournamentGamesPlayed;
//				newStats.localMultiplayerGamesPlayed = stats.localMultiplayerGamesPlayed;
//				newStats.tournamentGamesWon = stats.tournamentGamesWon;
//				newStats.tournamentGamesLost = stats.tournamentGamesLost;
//				newStats.singlePlayerGamesCompleted = stats.singlePlayerGamesCompleted;
//				newStats.singlePlayerGamesLost = stats.singlePlayerGamesLost;
//				newStats.singlePlayerHighestLevelReached = stats.singlePlayerHighestLevelReached;
//				newStats.totalTimePlayed = stats.totalTimePlayed;
//				newStats.longestGameLength = stats.longestGameLength;
//				newStats.firstTimePlayed = stats.firstTimePlayed;
//				//newStats.lastTimePlayed = 0;
//				//newStats.timeRecordSet = stats.timeRecordSet;
//				newStats.eloScore = stats.eloScore;
//				newStats.planesWalkerPoints = stats.planesWalkerPoints;
//				newStats.totalBlocksCleared = stats.totalBlocksCleared;
//				newStats.biggestCombo = stats.biggestCombo;
//				newStats.mostBlocksClearedInOneGame = stats.mostBlocksCleared;
//				//newStats.statsUUID = stats.statsUUID;
//			}
//
//
//
//
//			bool replaceScore = false;
//			if (compareEloScore)
//			{
//				if (anyGame == false && anyDifficulty == false && score.newEloScoreForThisGameAndDifficulty>diffStats.eloScore)
//				{
//					replaceScore = true;
//
//					newStats.eloScore = score.newEloScoreForThisGameAndDifficulty;
//				}
//
//				//				if(anyGame == false && anyDifficulty == true && score.newEloScoreForThisGame>diffStats.eloScore)
//				//				{
//				//					replaceScore = true;
//				//				}
//
//				if (anyGame == true && anyDifficulty == false && score.newEloScoreForThisDifficulty>diffStats.eloScore)
//				{
//					replaceScore = true;
//
//					newStats.eloScore = score.newEloScoreForThisDifficulty;
//				}
//
//				if (anyGame == true && anyDifficulty == true && score.newEloScoreOverall>diffStats.eloScore)
//				{
//					replaceScore = true;
//
//					newStats.eloScore = score.newEloScoreOverall;
//				}
//
//			}
//			if (comparePlaneswalkerPoints)
//			{
//				if (anyGame == false && anyDifficulty == false && score.newPlaneswalkerPointsForThisGameAndDifficulty>diffStats.planesWalkerPoints)
//				{
//					replaceScore = true;
//
//					newStats.planesWalkerPoints = score.newPlaneswalkerPointsForThisGameAndDifficulty;
//
//				}
//
//				//				if(anyGame == false && anyDifficulty == true && score.newPlaneswalkerPointsForThisGame>diffStats.planesWalkerPoints)
//				//				{
//				//					replaceScore = true;
//				//				}
//
//				if (anyGame == true && anyDifficulty == false && score.newPlaneswalkerPointsForThisDifficulty>diffStats.planesWalkerPoints)
//				{
//					replaceScore = true;
//
//					newStats.planesWalkerPoints = score.newPlaneswalkerPointsForThisDifficulty;
//				}
//
//				if (anyGame == true && anyDifficulty == true && score.newPlaneswalkerPointsOverall>diffStats.planesWalkerPoints)
//				{
//					replaceScore = true;
//
//					newStats.planesWalkerPoints = score.newPlaneswalkerPointsOverall;
//				}
//			}
//
//			if (compareBlocksCleared)
//			{
//				if (anyGame == false && anyDifficulty == false && score.mostBlocksClearedThisGameAndDifficulty>diffStats.mostBlocksClearedInOneGame)
//				{
//					replaceScore = true;
//
//					newStats.mostBlocksClearedInOneGame = score.mostBlocksClearedThisGameAndDifficulty;
//				}
//
//			}
//
//			if (compareTimeLasted)
//			{
//				if (anyGame == false && anyDifficulty == false && score.longestTimeLastedThisGameAndDifficulty>diffStats.longestGameLength)
//				{
//					replaceScore = true;
//
//					newStats.longestGameLength = score.longestTimeLastedThisGameAndDifficulty;
//
//				}
//			}
//
//			if (compareTotalBlocksCleared)
//			{
//				if (anyGame == false && anyDifficulty == false && score.totalBlocksClearedThisGameAndDifficulty>diffStats.totalBlocksCleared)
//				{
//					replaceScore = true;
//
//					newStats.totalBlocksCleared = score.totalBlocksClearedThisGameAndDifficulty;
//
//				}
//
//				//				if(anyGame == false && anyDifficulty == true && score.totalBlocksClearedThisGame>diffStats.totalBlocksCleared)
//				//				{
//				//					replaceScore = true;
//				//				}
//
//				if (anyGame == true && anyDifficulty == false && score.totalBlocksClearedThisDifficulty>diffStats.totalBlocksCleared)
//				{
//					replaceScore = true;
//
//					newStats.totalBlocksCleared = score.totalBlocksClearedThisDifficulty;
//				}
//
//				if (anyGame == true && anyDifficulty == true && score.totalBlocksClearedOverall>diffStats.totalBlocksCleared)
//				{
//					replaceScore = true;
//
//					newStats.totalBlocksCleared = score.totalBlocksClearedOverall;
//				}
//			}
//
//			if (compareTotalTimePlayed)
//			{
//				if (anyGame == false && anyDifficulty == false && score.totalTimePlayedThisGameAndDifficulty>diffStats.totalTimePlayed)
//				{
//					replaceScore = true;
//
//					newStats.totalTimePlayed = score.totalTimePlayedThisGameAndDifficulty;
//
//				}
//
//				//				if(anyGame == false && anyDifficulty == true && score.totalTimePlayedThisGame>diffStats.totalTimePlayed)
//				//				{
//				//					replaceScore = true;
//				//				}
//
//				if (anyGame == true && anyDifficulty == false && score.totalTimePlayedThisDifficulty>diffStats.totalTimePlayed)
//				{
//					replaceScore = true;
//
//					newStats.totalTimePlayed = score.totalTimePlayedThisGameAndDifficulty;
//				}
//
//				if (anyGame == true && anyDifficulty == true && score.totalTimePlayedOverall>diffStats.totalTimePlayed)
//				{
//					replaceScore = true;
//
//					newStats.totalTimePlayed = score.totalTimePlayedOverall;
//				}
//			}
//
//
//			if (replaceScore)
//			{
//				entries.add(i, newStats);
//				while (entries.size()>maxEntries)entries.remove(entries.size() - 1);
//				return true;
//			}
//
//		}
//
//
//
//
//		return false;
//
//	}
//
//
//
//
//	//===============================================================================================
//	BobsGameLeaderBoardAndHighScoreBoard(ResultSet databaseResultSet)
//	{//===============================================================================================
//
//
//		for (int i = 0; i<maxEntries; i++)
//		{
//			entries.add(new BobsGameLeaderBoardAndHighScoreBoardEntry());
//		}
//
//
//		try
//		{
//
//			isGameTypeOrSequence = databaseResultSet.getstring("isGameTypeOrSequence");
//			gameTypeName = databaseResultSet.getstring("gameTypeName");
//			gameTypeUUID = databaseResultSet.getstring("gameTypeUUID");
//			gameSequenceName = databaseResultSet.getstring("gameSequenceName");
//			gameSequenceUUID = databaseResultSet.getstring("gameSequenceUUID");
//			difficultyName = databaseResultSet.getstring("difficultyName");
//
//
//			if (isGameTypeOrSequence == nullptr)isGameTypeOrSequence = "";
//			if (gameTypeName == nullptr)gameTypeName = "";
//			if (gameTypeUUID == nullptr)gameTypeUUID = "";
//			if (gameSequenceName == nullptr)gameSequenceName = "";
//			if (gameSequenceUUID == nullptr)gameSequenceUUID = "";
//			if (difficultyName == nullptr)difficultyName = "";
//
//			for (int i = 0; i<maxEntries; i++)
//			{
//				string diff = "_" + i;
//				BobsGameLeaderBoardAndHighScoreBoardEntry s = entries.get(i);
//
//
//				s.userName = databaseResultSet.getstring("userName" + diff);
//				s.userID = databaseResultSet.getLong("userID" + diff);
//				s.totalGamesPlayed = databaseResultSet.getInt("totalGamesPlayed" + diff);
//				s.singlePlayerGamesPlayed = databaseResultSet.getInt("singlePlayerGamesPlayed" + diff);
//				s.tournamentGamesPlayed = databaseResultSet.getInt("tournamentGamesPlayed" + diff);
//				s.localMultiplayerGamesPlayed = databaseResultSet.getInt("localMultiplayerGamesPlayed" + diff);
//				s.tournamentGamesWon = databaseResultSet.getInt("tournamentGamesWon" + diff);
//				s.tournamentGamesLost = databaseResultSet.getInt("tournamentGamesLost" + diff);
//				s.singlePlayerGamesCompleted = databaseResultSet.getInt("singlePlayerGamesCompleted" + diff);
//				s.singlePlayerGamesLost = databaseResultSet.getInt("singlePlayerGamesLost" + diff);
//				s.singlePlayerHighestLevelReached = databaseResultSet.getInt("singlePlayerHighestLevelReached" + diff);
//				s.totalTimePlayed = databaseResultSet.getLong("totalTimePlayed" + diff);
//				s.longestGameLength = databaseResultSet.getLong("longestGameLength" + diff);
//				s.firstTimePlayed = databaseResultSet.getLong("firstTimePlayed" + diff);
//				//s.lastTimePlayed = databaseResultSet.getLong("lastTimePlayed"+diff);
//				s.timeRecordSet = databaseResultSet.getLong("timeRecordSet" + diff);
//				s.eloScore = databaseResultSet.getDouble("eloScore" + diff);
//				s.planesWalkerPoints = databaseResultSet.getLong("planesWalkerPoints" + diff);
//				s.totalBlocksCleared = databaseResultSet.getLong("totalBlocksCleared" + diff);
//				s.biggestCombo = databaseResultSet.getInt("biggestCombo" + diff);
//				s.mostBlocksClearedInOneGame = databaseResultSet.getInt("mostBlocksClearedInOneGame" + diff);
//				s.statsUUID = databaseResultSet.getstring("statsUUID");
//
//				if (s.statsUUID == nullptr)s.statsUUID = "";
//
//
//
//			}
//		}
//		catch (Exception ex)
//		{
//			log.error("DB ERROR:" + ex.getMessage());
//		}
//	}


	//===============================================================================================
	string encode()
	{//===============================================================================================

		string gameSavestring = "";


		gameSavestring += ",isGameTypeOrSequence:`" + isGameTypeOrSequence + "`";
		gameSavestring += ",gameTypeName:`" + gameTypeName + "`";
		gameSavestring += ",gameTypeUUID:`" + gameTypeUUID + "`";
		gameSavestring += ",gameSequenceName:`" + gameSequenceName + "`";
		gameSavestring += ",gameSequenceUUID:`" + gameSequenceUUID + "`";
		gameSavestring += ",difficultyName:`" + difficultyName + "`";

		for (int i = 0; i<maxEntries; i++)
		{
			string diff = "_" + to_string(i);
			BobsGameLeaderBoardAndHighScoreBoardEntry *s = entries.get(i);


			gameSavestring += ",userName:`" + s->userName + "`";
			gameSavestring += ",userID:`" + to_string(s->userID) + "`";
			gameSavestring += ",totalGamesPlayed" + diff + ":" + to_string(s->totalGamesPlayed);
			gameSavestring += ",singlePlayerGamesPlayed" + diff + ":" + to_string(s->singlePlayerGamesPlayed);
			gameSavestring += ",tournamentGamesPlayed" + diff + ":" + to_string(s->tournamentGamesPlayed);
			gameSavestring += ",localMultiplayerGamesPlayed" + diff + ":" + to_string(s->localMultiplayerGamesPlayed);
			gameSavestring += ",tournamentGamesWon" + diff + ":" + to_string(s->tournamentGamesWon);
			gameSavestring += ",tournamentGamesLost" + diff + ":" + to_string(s->tournamentGamesLost);
			gameSavestring += ",singlePlayerGamesCompleted" + diff + ":" + to_string(s->singlePlayerGamesCompleted);
			gameSavestring += ",singlePlayerGamesLost" + diff + ":" + to_string(s->singlePlayerGamesLost);
			gameSavestring += ",singlePlayerHighestLevelReached" + diff + ":" + to_string(s->singlePlayerHighestLevelReached);
			gameSavestring += ",totalTimePlayed" + diff + ":" + to_string(s->totalTimePlayed);
			gameSavestring += ",longestGameLength" + diff + ":" + to_string(s->longestGameLength);
			gameSavestring += ",firstTimePlayed" + diff + ":" + to_string(s->firstTimePlayed);
			gameSavestring += ",lastTimePlayed"+diff+":"+to_string(s->lastTimePlayed);
			gameSavestring += ",timeRecordSet" + diff + ":" + to_string(s->timeRecordSet);
			gameSavestring += ",eloScore" + diff + ":" + to_string(s->eloScore);
			gameSavestring += ",planesWalkerPoints" + diff + ":" + to_string(s->planesWalkerPoints);
			gameSavestring += ",totalBlocksCleared" + diff + ":" + to_string(s->totalBlocksCleared);
			gameSavestring += ",biggestCombo" + diff + ":" + to_string(s->biggestCombo);
			gameSavestring += ",mostBlocksClearedInOneGame" + diff + ":" + to_string(s->mostBlocksClearedInOneGame);
			gameSavestring += ",statsUUID" + diff + ":" + s->statsUUID;



		}

		gameSavestring += ",";

		return gameSavestring;
	}

	//===============================================================================================
	BobsGameLeaderBoardAndHighScoreBoard(string &s)
	{//===============================================================================================

		for (int i = 0; i<maxEntries; i++)
		{
			entries.add(new BobsGameLeaderBoardAndHighScoreBoardEntry());
		}

		decode(s);
	}


	//===============================================================================================
	void decode(string &s)
	{//===============================================================================================

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

		for (int i = 0; i<maxEntries; i++)
		{
			string diff = "_" + to_string(i);
			BobsGameLeaderBoardAndHighScoreBoardEntry *stats = entries.get(i);


			s = s.substr(s.find('`') + 1);
			t = s.substr(0, s.find('`'));
			if (t.length()>0)stats->userName = t;
			s = s.substr(s.find('`') + 1);


			s = s.substr(s.find('`') + 1);
			t = s.substr(0, s.find('`'));
			if (t.length()>0)try { stats->userID = stol(t); }
			catch (exception) {  return; }
			s = s.substr(s.find('`') + 1);


			s = s.substr(s.find(':') + 1);
			t = s.substr(0, s.find(','));
			if (t.length()>0)try { stats->totalGamesPlayed = stoi(t); }
			catch (exception) {  return; }
			s = s.substr(s.find(',') + 1);


			s = s.substr(s.find(':') + 1);
			t = s.substr(0, s.find(','));
			if (t.length()>0)try { stats->singlePlayerGamesPlayed = stoi(t); }
			catch (exception) {  return; }
			s = s.substr(s.find(',') + 1);


			s = s.substr(s.find(':') + 1);
			t = s.substr(0, s.find(','));
			if (t.length()>0)try { stats->tournamentGamesPlayed = stoi(t); }
			catch (exception) {  return; }
			s = s.substr(s.find(',') + 1);


			s = s.substr(s.find(':') + 1);
			t = s.substr(0, s.find(','));
			if (t.length()>0)try { stats->localMultiplayerGamesPlayed = stoi(t); }
			catch (exception) {  return; }
			s = s.substr(s.find(',') + 1);


			s = s.substr(s.find(':') + 1);
			t = s.substr(0, s.find(','));
			if (t.length()>0)try { stats->tournamentGamesWon = stoi(t); }
			catch (exception) {  return; }
			s = s.substr(s.find(',') + 1);


			s = s.substr(s.find(':') + 1);
			t = s.substr(0, s.find(','));
			if (t.length()>0)try { stats->tournamentGamesLost = stoi(t); }
			catch (exception) {  return; }
			s = s.substr(s.find(',') + 1);


			s = s.substr(s.find(':') + 1);
			t = s.substr(0, s.find(','));
			if (t.length()>0)try { stats->singlePlayerGamesCompleted = stoi(t); }
			catch (exception) {  return; }
			s = s.substr(s.find(',') + 1);


			s = s.substr(s.find(':') + 1);
			t = s.substr(0, s.find(','));
			if (t.length()>0)try { stats->singlePlayerGamesLost = stoi(t); }
			catch (exception) {  return; }
			s = s.substr(s.find(',') + 1);


			s = s.substr(s.find(':') + 1);
			t = s.substr(0, s.find(','));
			if (t.length()>0)try { stats->singlePlayerHighestLevelReached = stoi(t); }
			catch (exception) {  return; }
			s = s.substr(s.find(',') + 1);



			s = s.substr(s.find(':') + 1);
			t = s.substr(0, s.find(','));
			if (t.length()>0)try { stats->totalTimePlayed = stol(t); }
			catch (exception) {  return; }
			s = s.substr(s.find(',') + 1);


			s = s.substr(s.find(':') + 1);
			t = s.substr(0, s.find(','));
			if (t.length()>0)try { stats->longestGameLength = stol(t); }
			catch (exception) {  return; }
			s = s.substr(s.find(',') + 1);


			s = s.substr(s.find(':') + 1);
			t = s.substr(0, s.find(','));
			if (t.length()>0)try { stats->firstTimePlayed = stol(t); }
			catch (exception) {  return; }
			s = s.substr(s.find(',') + 1);

			s = s.substr(s.find(':')+1);
			t = s.substr(0, s.find(','));
			if(t.length()>0)try{stats->lastTimePlayed = stol(t);}catch(exception){return;}
			s = s.substr(s.find(',')+1);

			s = s.substr(s.find(':') + 1);
			t = s.substr(0, s.find(','));
			if (t.length()>0)try { stats->timeRecordSet = stol(t); }
			catch (exception) {  return; }
			s = s.substr(s.find(',') + 1);



			s = s.substr(s.find(':') + 1);
			t = s.substr(0, s.find(','));
			if (t.length()>0)try { stats->eloScore = stod(t); }
			catch (exception) {  return; }
			s = s.substr(s.find(',') + 1);


			s = s.substr(s.find(':') + 1);
			t = s.substr(0, s.find(','));
			if (t.length()>0)try { stats->planesWalkerPoints = stol(t); }
			catch (exception) {  return; }
			s = s.substr(s.find(',') + 1);


			s = s.substr(s.find(':') + 1);
			t = s.substr(0, s.find(','));
			if (t.length()>0)try { stats->totalBlocksCleared = stol(t); }
			catch (exception) {  return; }
			s = s.substr(s.find(',') + 1);

			s = s.substr(s.find(':') + 1);
			t = s.substr(0, s.find(','));
			if (t.length()>0)try { stats->biggestCombo = stoi(t); }
			catch (exception) {  return; }
			s = s.substr(s.find(',') + 1);

			s = s.substr(s.find(':') + 1);
			t = s.substr(0, s.find(','));
			if (t.length()>0)try { stats->mostBlocksClearedInOneGame = stoi(t); }
			catch (exception) {  return; }
			s = s.substr(s.find(',') + 1);


			s = s.substr(s.find(':') + 1);
			t = s.substr(0, s.find(','));
			if (t.length()>0)stats->statsUUID = t;
			s = s.substr(s.find(',') + 1);

		}
	}
//
//
//	//===============================================================================================
//	void initDB(Connection databaseConnection, string databaseName)
//	{//===============================================================================================
//
//
//		if (databaseConnection == nullptr) { log.error("DB ERROR: Could not open DB connection!"); return; }
//
//		PreparedStatement ps = nullptr;
//
//		string query =
//
//			"INSERT INTO " + databaseName + " SET "; //bobsGameEloScoreLeaderBoards or bobsGameMostBlocksClearedHighScoreBoards
//
//		query += "isGameTypeOrSequence = ? ";
//		query += "gameTypeName = ? ";
//		query += "gameTypeUUID = ? ";
//		query += "gameSequenceName = ? ";
//		query += "gameSequenceUUID = ? ";
//		query += "difficultyName = ? ";
//
//		for (int i = 0; i<maxEntries; i++)
//		{
//			string diffName = "_" + i;
//			BobsGameLeaderBoardAndHighScoreBoardEntry diffStats = entries.get(i);
//
//
//			query += "" + diffStats.userName + diffName + " = ? ";
//			query += "" + diffStats.userID + diffName + " = ? ";
//			query += "" + diffStats.totalGamesPlayed + diffName + " = ? ";
//			query += "" + diffStats.singlePlayerGamesPlayed + diffName + " = ? ";
//			query += "" + diffStats.tournamentGamesPlayed + diffName + " = ? ";
//			query += "" + diffStats.localMultiplayerGamesPlayed + diffName + " = ? ";
//			query += "" + diffStats.tournamentGamesWon + diffName + " = ? ";
//			query += "" + diffStats.tournamentGamesLost + diffName + " = ? ";
//			query += "" + diffStats.singlePlayerGamesCompleted + diffName + " = ? ";
//			query += "" + diffStats.singlePlayerGamesLost + diffName + " = ? ";
//			query += "" + diffStats.singlePlayerHighestLevelReached + diffName + " = ? ";
//			query += "" + diffStats.totalTimePlayed + diffName + " = ? ";
//			query += "" + diffStats.longestGameLength + diffName + " = ? ";
//			query += "" + diffStats.firstTimePlayed + diffName + " = ? ";
//			//query += ""+diffStats.lastTimePlayed+diffName+" = ? ";
//			query += "" + diffStats.timeRecordSet + diffName + " = ? ";
//			query += "" + diffStats.eloScore + diffName + " = ? ";
//			query += "" + diffStats.planesWalkerPoints + diffName + " = ? ";
//			query += "" + diffStats.totalBlocksCleared + diffName + " = ? ";
//			query += "" + diffStats.biggestCombo + diffName + " = ? ";
//			query += "" + diffStats.mostBlocksClearedInOneGame + diffName + " = ? ";
//			query += "" + diffStats.statsUUID + diffName + " = ? ";
//
//		}
//
//		try
//		{
//			ps = databaseConnection.prepareStatement(query);
//
//			int n = 0;
//
//
//			ps.setstring(n++, isGameTypeOrSequence);
//			ps.setstring(n++, gameTypeName);
//			ps.setstring(n++, gameTypeUUID);
//			ps.setstring(n++, gameSequenceName);
//			ps.setstring(n++, gameSequenceUUID);
//			ps.setstring(n++, difficultyName);
//
//
//			for (int i = 0; i<maxEntries; i++)
//			{
//
//				BobsGameLeaderBoardAndHighScoreBoardEntry diffStats = entries.get(i);
//
//
//				ps.setstring(++n, diffStats.userName);
//				ps.setLong(++n, diffStats.userID);
//				ps.setInt(++n, diffStats.totalGamesPlayed);
//				ps.setInt(++n, diffStats.singlePlayerGamesPlayed);
//				ps.setInt(++n, diffStats.tournamentGamesPlayed);
//				ps.setInt(++n, diffStats.localMultiplayerGamesPlayed);
//				ps.setInt(++n, diffStats.tournamentGamesWon);
//				ps.setInt(++n, diffStats.tournamentGamesLost);
//				ps.setInt(++n, diffStats.singlePlayerGamesCompleted);
//				ps.setInt(++n, diffStats.singlePlayerGamesLost);
//				ps.setInt(++n, diffStats.singlePlayerHighestLevelReached);
//				ps.setLong(++n, diffStats.totalTimePlayed);
//				ps.setLong(++n, diffStats.longestGameLength);
//				ps.setLong(++n, diffStats.firstTimePlayed);
//				//ps.setLong(++n, diffStats.lastTimePlayed);
//				ps.setLong(++n, diffStats.timeRecordSet);
//				ps.setDouble(++n, diffStats.eloScore);
//				ps.setLong(++n, diffStats.planesWalkerPoints);
//				ps.setLong(++n, diffStats.totalBlocksCleared);
//				ps.setInt(++n, diffStats.biggestCombo);
//				ps.setInt(++n, diffStats.mostBlocksClearedInOneGame);
//				ps.setstring(++n, diffStats.statsUUID);
//
//			}
//
//
//			ps.executeUpdate();
//
//			ps.close();
//
//		}
//		catch (Exception ex) { System.err.println("DB ERROR: " + ex.getMessage()); }
//
//
//
//	}
//
//	//===============================================================================================
//	void updateDB(Connection databaseConnection, long userID, string databaseName)
//	{//===============================================================================================
//
//		if (databaseConnection == nullptr) { log.error("DB ERROR: Could not open DB connection!"); return; }
//
//		string query = "";
//		query += "UPDATE " + databaseName + " SET "; //bobsGameEloScoreLeaderBoards or bobsGameMostBlocksClearedHighScoreBoards
//
//		string gameTypeOrSequenceQuerystring = "";
//		string uuid = "";
//		if (isGameTypeOrSequence.equals("GameType"))
//		{
//			gameTypeOrSequenceQuerystring = "gameTypeUUID = ?";
//			uuid = gameTypeUUID;
//		}
//
//		if (isGameTypeOrSequence.equals("GameSequence"))
//		{
//			gameTypeOrSequenceQuerystring = "gameSequenceUUID = ?";
//			uuid = gameSequenceUUID;
//		}
//
//		if (isGameTypeOrSequence.equals("OVERALL"))
//		{
//			gameTypeOrSequenceQuerystring = "isGameTypeOrSequence = ?";
//			uuid = "OVERALL";
//		}
//
//		if (difficultyName.equals("OVERALL"))
//		{
//			difficultyName = "OVERALL";
//		}
//
//		for (int i = 0; i<maxEntries; i++)
//		{
//			string diffName = "_" + i;
//			BobsGameLeaderBoardAndHighScoreBoardEntry diffStats = entries.get(i);
//
//
//
//
//			query += "" + diffStats.userName + diffName + " = ? ";
//			query += "" + diffStats.userID + diffName + " = ? ";
//			query += "" + diffStats.totalGamesPlayed + diffName + " = ? ";
//			query += "" + diffStats.singlePlayerGamesPlayed + diffName + " = ? ";
//			query += "" + diffStats.tournamentGamesPlayed + diffName + " = ? ";
//			query += "" + diffStats.localMultiplayerGamesPlayed + diffName + " = ? ";
//			query += "" + diffStats.tournamentGamesWon + diffName + " = ? ";
//			query += "" + diffStats.tournamentGamesLost + diffName + " = ? ";
//			query += "" + diffStats.singlePlayerGamesCompleted + diffName + " = ? ";
//			query += "" + diffStats.singlePlayerGamesLost + diffName + " = ? ";
//			query += "" + diffStats.singlePlayerHighestLevelReached + diffName + " = ? ";
//			query += "" + diffStats.totalTimePlayed + diffName + " = ? ";
//			query += "" + diffStats.longestGameLength + diffName + " = ? ";
//			query += "" + diffStats.firstTimePlayed + diffName + " = ? ";
//			//query += ""+diffStats.lastTimePlayed+diffName+" = ? ";
//			query += "" + diffStats.timeRecordSet + diffName + " = ? ";
//			query += "" + diffStats.eloScore + diffName + " = ? ";
//			query += "" + diffStats.planesWalkerPoints + diffName + " = ? ";
//			query += "" + diffStats.totalBlocksCleared + diffName + " = ? ";
//			query += "" + diffStats.biggestCombo + diffName + " = ? ";
//			query += "" + diffStats.mostBlocksClearedInOneGame + diffName + " = ? ";
//			query += "" + diffStats.statsUUID + diffName + " = ? ";
//
//		}
//
//		query += "WHERE " + gameTypeOrSequenceQuerystring + " AND difficultyName = ?";
//
//		{
//
//
//			try
//			{
//				PreparedStatement ps = databaseConnection.prepareStatement(query);
//
//
//				int n = 0;
//				for (int i = 0; i<maxEntries; i++)
//				{
//
//					BobsGameLeaderBoardAndHighScoreBoardEntry diffStats = entries.get(i);
//
//
//					ps.setstring(++n, diffStats.userName);
//					ps.setLong(++n, diffStats.userID);
//					ps.setInt(++n, diffStats.totalGamesPlayed);
//					ps.setInt(++n, diffStats.singlePlayerGamesPlayed);
//					ps.setInt(++n, diffStats.tournamentGamesPlayed);
//					ps.setInt(++n, diffStats.localMultiplayerGamesPlayed);
//					ps.setInt(++n, diffStats.tournamentGamesWon);
//					ps.setInt(++n, diffStats.tournamentGamesLost);
//					ps.setInt(++n, diffStats.singlePlayerGamesCompleted);
//					ps.setInt(++n, diffStats.singlePlayerGamesLost);
//					ps.setInt(++n, diffStats.singlePlayerHighestLevelReached);
//					ps.setLong(++n, diffStats.totalTimePlayed);
//					ps.setLong(++n, diffStats.longestGameLength);
//					ps.setLong(++n, diffStats.firstTimePlayed);
//					//ps.setLong(++n, diffStats.lastTimePlayed);
//					ps.setLong(++n, diffStats.timeRecordSet);
//					ps.setDouble(++n, diffStats.eloScore);
//					ps.setLong(++n, diffStats.planesWalkerPoints);
//					ps.setLong(++n, diffStats.totalBlocksCleared);
//					ps.setInt(++n, diffStats.biggestCombo);
//					ps.setInt(++n, diffStats.mostBlocksClearedInOneGame);
//					ps.setstring(++n, diffStats.statsUUID);
//
//				}
//
//				ps.setstring(++n, uuid);
//				ps.setstring(++n, difficultyName);
//				ps.executeUpdate();
//
//				ps.close();
//			}
//			catch (Exception ex) { log.error("DB ERROR: " + ex.getMessage());  }
//
//		}
//	}

};