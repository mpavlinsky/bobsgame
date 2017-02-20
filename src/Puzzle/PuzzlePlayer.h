
//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
#include "GameLogic.h"
#include "src/Utility/Color.h"

//=========================================================================================================================
class PuzzlePlayer
{//=========================================================================================================================
public:
	//=========================================================================================================================
	PuzzlePlayer(GameLogic *g)
	{//=========================================================================================================================
		this->gameLogic = g;
		if (g != nullptr)g->player = this;
	}
	//=========================================================================================================================
	~PuzzlePlayer()
	{//=========================================================================================================================
		if (gameLogic != nullptr)delete gameLogic;
		if (menu != nullptr)delete menu;
		if (nameCaption != nullptr)
		{
			nameCaption->setToBeDeletedImmediately();
			nameCaption = nullptr;
		}
		if (gameCaption != nullptr)
		{
			gameCaption->setToBeDeletedImmediately();
			gameCaption = nullptr;
		}
		if (difficultyCaption != nullptr)
		{
			difficultyCaption->setToBeDeletedImmediately();
			difficultyCaption = nullptr;
		}
	}
	//=========================================================================================================================
	string getID()
	{//=========================================================================================================================
		if (peerConnection != nullptr)return to_string(peerConnection->peerUserID) + "." + to_string(gameLogic->randomSeed) + "." + gameLogic->uuid;
		else return to_string(gameLogic->getEngine()->getUserID_S()) + "." + to_string(gameLogic->randomSeed) + "." + gameLogic->uuid;
	}
	//=========================================================================================================================
	bool isNetworkPlayer()
	{//=========================================================================================================================
		if (gameLogic->isNetworkPlayer && peerConnection != nullptr)return true;
		return false;
	}

	GameLogic* gameLogic = nullptr;
	bool confirmed = false;
	BobMenu *menu = nullptr;
	bool selectGameSequenceOrSingleGameTypeMiniMenuShowing = true;
	bool selectGameSequenceMiniMenuShowing = false;
	bool gameSequenceOptionsMiniMenuShowing = false;
	bool selectSingleGameTypeMiniMenuShowing = false;
	bool setGameSequence = false;
	bool setDifficulty = false;

	bool upRepeatedStarted = false;
	bool upRepeating = false;
	long long upLastTime = 0;

	bool downRepeatedStarted = false;
	bool downRepeating = false;
	long long downLastTime = 0;



	bool allowAnalogControls = true;
	bool slamWithY = true;
	bool slamWithR = false;
	bool slamWithUp = true;

	bool useKeyboard = false;
	GameController *gameController = nullptr;

	//BobsGameNetwork *network = nullptr;
	UDPPeerConnection *peerConnection = nullptr;
	Caption* nameCaption = nullptr;
	Caption* gameCaption = nullptr;
	Caption* difficultyCaption = nullptr;






	BobColor *gridBorderColor = new BobColor(255, 255, 255);//TODO: move these to user settings!
	BobColor *gridCheckeredBackgroundColor1 = BobColor::black;
	BobColor *gridCheckeredBackgroundColor2 = new BobColor(8, 8, 8);
	BobColor *screenBackgroundColor = BobColor::black;
	bool gridRule_showWarningForFieldThreeQuartersFilled = true;//TODO: move these to user settings!
















	bool UP_HELD = false;
	bool DOWN_HELD = false;
	bool LEFT_HELD = false;
	bool RIGHT_HELD = false;
	bool ROTATECW_HELD = false;
	bool ROTATECCW_HELD = false;
	bool HOLDRAISE_HELD = false;
	bool SLAM_HELD = false;
	bool PAUSE_HELD = false;
	bool CONFIRM_HELD = false;
	bool CANCEL_HELD = false;
	//bool START_HELD = false;



	bool LAST_UP_HELD = false;
	bool LAST_DOWN_HELD = false;
	bool LAST_LEFT_HELD = false;
	bool LAST_RIGHT_HELD = false;
	bool LAST_ROTATECW_HELD = false;
	bool LAST_ROTATECCW_HELD = false;
	bool LAST_HOLDRAISE_HELD = false;
	bool LAST_SLAM_HELD = false;
	bool LAST_PAUSE_HELD = false;
	bool LAST_CONFIRM_HELD = false;
	bool LAST_CANCEL_HELD = false;
	//bool LAST_START_HELD = false;

private:
	bool UP_PRESSED = false;
	bool DOWN_PRESSED = false;
	bool LEFT_PRESSED = false;
	bool RIGHT_PRESSED = false;
	bool ROTATECW_PRESSED = false;//space or B
	bool ROTATECCW_PRESSED = false;//lshift or a
	bool HOLDRAISE_PRESSED = false;//lctrl or l or r
	bool SLAM_PRESSED = false;//lctrl or l or r
	bool PAUSE_PRESSED = false;
	bool CONFIRM_PRESSED = false;
	bool CANCEL_PRESSED = false;
	//bool START_PRESSED = false;

public:
	bool upPressed() { if (UP_PRESSED) { UP_PRESSED = false; return true; }return false; }
	bool downPressed() { if (DOWN_PRESSED) { DOWN_PRESSED = false; return true; }return false; }
	bool leftPressed() { if (LEFT_PRESSED) { LEFT_PRESSED = false; return true; }return false; }
	bool rightPressed() { if (RIGHT_PRESSED) { RIGHT_PRESSED = false; return true; }return false; }
	bool rotateCWPressed() { if (ROTATECW_PRESSED) { ROTATECW_PRESSED = false; return true; }return false; }
	bool rotateCCWPressed() { if (ROTATECCW_PRESSED) { ROTATECCW_PRESSED = false; return true; }return false; }
	bool holdRaisePressed() { if (HOLDRAISE_PRESSED) { HOLDRAISE_PRESSED = false; return true; }return false; }
	bool slamPressed() { if (SLAM_PRESSED) { SLAM_PRESSED = false; return true; }return false; }
	//Esc or Start
	bool pausePressed() { if (PAUSE_PRESSED) { PAUSE_PRESSED = false; return true; }return false; }
	//Enter or Bottom Button (a)
	bool confirmPressed() { if (CONFIRM_PRESSED) { CONFIRM_PRESSED = false; return true; }return false; }
	//Esc or Right Button (b)
	bool cancelPressed() { if (CANCEL_PRESSED) { CANCEL_PRESSED = false; return true; }return false; }
	//Enter or Start
	//bool startPressed() { if (START_PRESSED) { START_PRESSED = false; return true; }return false; }
	//=========================================================================================================================
	void resetPressedButtons()
	{//=========================================================================================================================

		UP_PRESSED = false;
		DOWN_PRESSED = false;
		LEFT_PRESSED = false;
		RIGHT_PRESSED = false;
		ROTATECW_PRESSED = false;
		ROTATECCW_PRESSED = false;
		HOLDRAISE_PRESSED = false;
		SLAM_PRESSED = false;
		PAUSE_PRESSED = false;
		CONFIRM_PRESSED = false;
		CANCEL_PRESSED = false;
		//START_PRESSED = false;
	}
	//=========================================================================================================================
	void setButtonStates()
	{//=========================================================================================================================
		LAST_UP_HELD = UP_HELD;
		LAST_DOWN_HELD = DOWN_HELD;
		LAST_LEFT_HELD = LEFT_HELD;
		LAST_RIGHT_HELD = RIGHT_HELD;
		LAST_ROTATECW_HELD = ROTATECW_HELD;
		LAST_ROTATECCW_HELD = ROTATECCW_HELD;
		LAST_HOLDRAISE_HELD = HOLDRAISE_HELD;
		LAST_SLAM_HELD = SLAM_HELD;
		LAST_PAUSE_HELD = PAUSE_HELD;
		LAST_CONFIRM_HELD = CONFIRM_HELD;
		LAST_CANCEL_HELD = CANCEL_HELD;



		UP_HELD = false;
		DOWN_HELD = false;
		LEFT_HELD = false;
		RIGHT_HELD = false;
		ROTATECW_HELD = false;
		ROTATECCW_HELD = false;
		HOLDRAISE_HELD = false;
		SLAM_HELD = false;
		PAUSE_HELD = false;
		CONFIRM_HELD = false;
		CANCEL_HELD = false;
		//START_HELD = false;

	}
	//=========================================================================================================================
	void setPressedButtons()
	{//=========================================================================================================================
		if (UP_HELD						&&LAST_UP_HELD == false)			 UP_PRESSED = true;
		if (DOWN_HELD					&&LAST_DOWN_HELD == false)		DOWN_PRESSED = true;
		if (LEFT_HELD					&&LAST_LEFT_HELD == false)		LEFT_PRESSED = true;
		if (RIGHT_HELD					&&LAST_RIGHT_HELD == false)		 RIGHT_PRESSED = true;
		if (ROTATECW_HELD				&&LAST_ROTATECW_HELD == false)			 ROTATECW_PRESSED = true;
		if (ROTATECCW_HELD				&&LAST_ROTATECCW_HELD == false)			 ROTATECCW_PRESSED = true;
		if (HOLDRAISE_HELD				&&LAST_HOLDRAISE_HELD == false)	 HOLDRAISE_PRESSED = true;
		if (SLAM_HELD					&&LAST_SLAM_HELD == false)	 SLAM_PRESSED = true;
		//if (START_HELD					&&LAST_START_HELD == false)	 START_PRESSED = true;
		if (PAUSE_HELD					&&LAST_PAUSE_HELD == false)	 PAUSE_PRESSED = true;
		if (CONFIRM_HELD					&&LAST_CONFIRM_HELD == false)	 CONFIRM_PRESSED = true;
		if (CANCEL_HELD					&&LAST_CANCEL_HELD == false)	 CANCEL_PRESSED = true;
	}

};
