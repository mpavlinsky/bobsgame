//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;



class Logger;
#include "src/Utility/HashMap.h"



class GameController
{
public:

	SDL_JoystickID id;

	bool UP_HELD = false;
	bool DOWN_HELD = false;
	bool LEFT_HELD = false;
	bool RIGHT_HELD = false;
	bool ANALOGUP_HELD = false;
	bool ANALOGDOWN_HELD = false;
	bool ANALOGLEFT_HELD = false;
	bool ANALOGRIGHT_HELD = false;
	bool A_HELD = false;
	bool B_HELD = false;
	bool X_HELD = false;
	bool Y_HELD = false;
	bool L_HELD = false;
	bool R_HELD = false;
	bool L2_HELD = false;
	bool R2_HELD = false;
	bool START_HELD = false;
	bool SELECT_HELD = false;


	bool LAST_UP_HELD = false;
	bool LAST_DOWN_HELD = false;
	bool LAST_LEFT_HELD = false;
	bool LAST_RIGHT_HELD = false;
	bool LAST_ANALOGUP_HELD = false;
	bool LAST_ANALOGDOWN_HELD = false;
	bool LAST_ANALOGLEFT_HELD = false;
	bool LAST_ANALOGRIGHT_HELD = false;
	bool LAST_A_HELD = false;
	bool LAST_B_HELD = false;
	bool LAST_X_HELD = false;
	bool LAST_Y_HELD = false;
	bool LAST_L_HELD = false;
	bool LAST_R_HELD = false;
	bool LAST_L2_HELD = false;
	bool LAST_R2_HELD = false;
	bool LAST_START_HELD = false;
	bool LAST_SELECT_HELD = false;

private:
	bool UP_PRESSED = false;
	bool DOWN_PRESSED = false;
	bool LEFT_PRESSED = false;
	bool RIGHT_PRESSED = false;
	bool ANALOGUP_PRESSED = false;
	bool ANALOGDOWN_PRESSED = false;
	bool ANALOGLEFT_PRESSED = false;
	bool ANALOGRIGHT_PRESSED = false;
	bool A_PRESSED = false;
	bool B_PRESSED = false;
	bool X_PRESSED = false;
	bool Y_PRESSED = false;
	bool L_PRESSED = false;
	bool R_PRESSED = false;
	bool L2_PRESSED = false;
	bool R2_PRESSED = false;
	bool START_PRESSED = false;
	bool SELECT_PRESSED = false;
public:

public:
	bool up_Pressed() { if (UP_PRESSED) { UP_PRESSED = false; return true; }return false; }
	bool down_Pressed() { if (DOWN_PRESSED) { DOWN_PRESSED = false; return true; }return false; }
	bool left_Pressed() { if (LEFT_PRESSED) { LEFT_PRESSED = false; return true; }return false; }
	bool right_Pressed() { if (RIGHT_PRESSED) { RIGHT_PRESSED = false; return true; }return false; }
	bool analogUp_Pressed() { if (ANALOGUP_PRESSED) { ANALOGUP_PRESSED = false; return true; }return false; }
	bool analogDown_Pressed() { if (ANALOGDOWN_PRESSED) { ANALOGDOWN_PRESSED = false; return true; }return false; }
	bool analogLeft_Pressed() { if (ANALOGLEFT_PRESSED) { ANALOGLEFT_PRESSED = false; return true; }return false; }
	bool analogRight_Pressed() { if (ANALOGRIGHT_PRESSED) { ANALOGRIGHT_PRESSED = false; return true; }return false; }
	bool a_Pressed() { if (A_PRESSED) { A_PRESSED = false; return true; }return false; }
	bool b_Pressed() { if (B_PRESSED) { B_PRESSED = false; return true; }return false; }
	bool x_Pressed() { if (X_PRESSED) { X_PRESSED = false; return true; }return false; }
	bool y_Pressed() { if (Y_PRESSED) { Y_PRESSED = false; return true; }return false; }
	bool l_Pressed() { if (L_PRESSED) { L_PRESSED = false; return true; }return false; }
	bool r_Pressed() { if (R_PRESSED) { R_PRESSED = false; return true; }return false; }
	bool l2_Pressed() { if (L2_PRESSED) { L2_PRESSED = false; return true; }return false; }
	bool r2_Pressed() { if (R2_PRESSED) { R2_PRESSED = false; return true; }return false; }
	bool start_Pressed() { if (START_PRESSED) { START_PRESSED = false; return true; }return false; }
	bool select_Pressed() { if (SELECT_PRESSED) { SELECT_PRESSED = false; return true; }return false; }

	void resetPressedButtons()
	{
		UP_PRESSED = false;
		DOWN_PRESSED = false;
		LEFT_PRESSED = false;
		RIGHT_PRESSED = false;
		ANALOGUP_PRESSED = false;
		ANALOGDOWN_PRESSED = false;
		ANALOGLEFT_PRESSED = false;
		ANALOGRIGHT_PRESSED = false;
		A_PRESSED = false;
		B_PRESSED = false;
		X_PRESSED = false;
		Y_PRESSED = false;
		L_PRESSED = false;
		R_PRESSED = false;
		L2_PRESSED = false;
		R2_PRESSED = false;
		START_PRESSED = false;
		SELECT_PRESSED = false;
	}

	void setButtonStates()
	{
		LAST_UP_HELD = UP_HELD;
		LAST_DOWN_HELD = DOWN_HELD;
		LAST_LEFT_HELD = LEFT_HELD;
		LAST_RIGHT_HELD = RIGHT_HELD;
		LAST_ANALOGUP_HELD = ANALOGUP_HELD;
		LAST_ANALOGDOWN_HELD = ANALOGDOWN_HELD;
		LAST_ANALOGLEFT_HELD = ANALOGLEFT_HELD;
		LAST_ANALOGRIGHT_HELD = ANALOGRIGHT_HELD;
		LAST_A_HELD = A_HELD;
		LAST_B_HELD = B_HELD;
		LAST_X_HELD = X_HELD;
		LAST_Y_HELD = Y_HELD;
		LAST_L_HELD = L_HELD;
		LAST_R_HELD = R_HELD;
		LAST_L2_HELD = L2_HELD;
		LAST_R2_HELD = R2_HELD;
		LAST_START_HELD = START_HELD;
		LAST_SELECT_HELD = SELECT_HELD;
	}

	void setPressedButtons()
	{
		if (UP_HELD			&&LAST_UP_HELD==false)		  UP_PRESSED = true;
		if (DOWN_HELD		 &&LAST_DOWN_HELD == false)	  DOWN_PRESSED = true;
		if (LEFT_HELD		 &&LAST_LEFT_HELD == false)	  LEFT_PRESSED = true;
		if (RIGHT_HELD		 &&LAST_RIGHT_HELD == false)	  RIGHT_PRESSED = true;
		if (ANALOGUP_HELD			&&LAST_ANALOGUP_HELD == false)		  ANALOGUP_PRESSED = true;
		if (ANALOGDOWN_HELD		 &&LAST_ANALOGDOWN_HELD == false)	  ANALOGDOWN_PRESSED = true;
		if (ANALOGLEFT_HELD		 &&LAST_ANALOGLEFT_HELD == false)	  ANALOGLEFT_PRESSED = true;
		if (ANALOGRIGHT_HELD		 &&LAST_ANALOGRIGHT_HELD == false)	  ANALOGRIGHT_PRESSED = true;
		if (A_HELD			&&LAST_A_HELD == false)		  A_PRESSED = true;
		if (B_HELD			&&LAST_B_HELD == false)		  B_PRESSED = true;
		if (X_HELD			&&LAST_X_HELD == false)		  X_PRESSED = true;
		if (Y_HELD			&&LAST_Y_HELD == false)		  Y_PRESSED = true;
		if (L_HELD			&&LAST_L_HELD == false)		  L_PRESSED = true;
		if (R_HELD			&&LAST_R_HELD == false)		  R_PRESSED = true;
		if (L2_HELD			&&LAST_L2_HELD == false)		  L2_PRESSED = true;
		if (R2_HELD			&&LAST_R2_HELD == false)		  R2_PRESSED = true;
		if (START_HELD		 &&LAST_START_HELD == false)	  START_PRESSED = true;
		if (SELECT_HELD		 &&LAST_SELECT_HELD == false)  SELECT_PRESSED = true;

	}
};

class ControlsManager
{
public:
	static Logger log;

	ControlsManager();

	static int numControllers;
	static string controllerNames;

	static int DEADZONE;

	//static SDL_Event event;
	//static HashMap<int,SDL_GameController*> *controllersByJoystickNum;
	static HashMap<SDL_JoystickID, SDL_GameController*> controllersByJoystickID;

	static float MAXZOOM;
	static float MINZOOM;
	static float ZOOMINCREMENT;


	static ArrayList<GameController*> gameControllers;// = new ArrayList<GameController*>();


	//------------------------------------
	//keyboard
	//------------------------------------
public:
	bool KEY_UP_HELD = false;
	bool KEY_DOWN_HELD = false;
	bool KEY_LEFT_HELD = false;
	bool KEY_RIGHT_HELD = false;
	bool KEY_SPACE_HELD = false; //was A
	bool KEY_TAB_HELD = false; //was START
	bool KEY_RETURN_HELD = false; //was SELECT
	bool KEY_H_HELD = false;
	bool KEY_LBRACKET_HELD = false; //was L
	bool KEY_RBRACKET_HELD = false; //was R
	bool KEY_RALT_HELD = false;
	bool KEY_LALT_HELD = false;
	bool KEY_LSHIFT_HELD = false; //was B
	bool KEY_RSHIFT_HELD = false; //quickzoom
	bool KEY_LCTRL_HELD = false;
	bool KEY_RCTRL_HELD = false; //quickzoom
	bool KEY_BACKSPACE_HELD = false; //reset zoom
	bool KEY_ESC_HELD = false;
	bool KEY_F1_HELD = false;
	bool KEY_F2_HELD = false;
	bool KEY_F3_HELD = false;
	bool KEY_F4_HELD = false;
	bool KEY_F5_HELD = false;
	bool KEY_F6_HELD = false;
	bool KEY_F7_HELD = false;
	bool KEY_F8_HELD = false;
	bool KEY_F9_HELD = false;
	bool KEY_F10_HELD = false;
	bool KEY_F11_HELD = false;
	bool KEY_F12_HELD = false;
	bool KEY_PRINTSCREEN_HELD = false;
	bool KEY_PAUSE_HELD = false;
	bool KEY_TILDE_HELD = false;
	bool KEY_1_HELD = false;
	bool KEY_2_HELD = false;
	bool KEY_3_HELD = false;
	bool KEY_4_HELD = false;
	bool KEY_5_HELD = false;
	bool KEY_6_HELD = false;
	bool KEY_7_HELD = false;
	bool KEY_8_HELD = false;
	bool KEY_9_HELD = false;
	bool KEY_0_HELD = false;
	bool KEY_MINUS_HELD = false; //zoom in
	bool KEY_PLUS_HELD = false; //zoom out
	bool KEY_NUM0_HELD = false;
	bool KEY_NUM1_HELD = false;
	bool KEY_NUM2_HELD = false;
	bool KEY_NUM3_HELD = false;
	bool KEY_NUM4_HELD = false;
	bool KEY_NUM5_HELD = false;
	bool KEY_NUM6_HELD = false;
	bool KEY_NUM7_HELD = false;
	bool KEY_NUM8_HELD = false;
	bool KEY_NUM9_HELD = false;


private:
	bool KEY_UP_PRESSED = false;
	bool KEY_DOWN_PRESSED = false;
	bool KEY_LEFT_PRESSED = false;
	bool KEY_RIGHT_PRESSED = false;
	bool KEY_SPACE_PRESSED = false; //was A
	bool KEY_TAB_PRESSED = false; //was START
	bool KEY_RETURN_PRESSED = false; //was SELECT
	bool KEY_H_PRESSED = false;
	bool KEY_LBRACKET_PRESSED = false; //was L
	bool KEY_RBRACKET_PRESSED = false; //was R
	bool KEY_RALT_PRESSED = false;
	bool KEY_LALT_PRESSED = false;
	bool KEY_LSHIFT_PRESSED = false; //was B
	bool KEY_RSHIFT_PRESSED = false; //quickzoom
	bool KEY_LCTRL_PRESSED = false;
	bool KEY_RCTRL_PRESSED = false; //quickzoom
	bool KEY_BACKSPACE_PRESSED = false; //reset zoom
	bool KEY_ESC_PRESSED = false;
	bool KEY_F1_PRESSED = false;
	bool KEY_F2_PRESSED = false;
	bool KEY_F3_PRESSED = false;
	bool KEY_F4_PRESSED = false;
	bool KEY_F5_PRESSED = false;
	bool KEY_F6_PRESSED = false;
	bool KEY_F7_PRESSED = false;
	bool KEY_F8_PRESSED = false;
	bool KEY_F9_PRESSED = false;
	bool KEY_F10_PRESSED = false;
	bool KEY_F11_PRESSED = false;
	bool KEY_F12_PRESSED = false;
	bool KEY_PRINTSCREEN_PRESSED = false;
	bool KEY_PAUSE_PRESSED = false;
	bool KEY_TILDE_PRESSED = false;
	bool KEY_1_PRESSED = false;
	bool KEY_2_PRESSED = false;
	bool KEY_3_PRESSED = false;
	bool KEY_4_PRESSED = false;
	bool KEY_5_PRESSED = false;
	bool KEY_6_PRESSED = false;
	bool KEY_7_PRESSED = false;
	bool KEY_8_PRESSED = false;
	bool KEY_9_PRESSED = false;
	bool KEY_0_PRESSED = false;
	bool KEY_MINUS_PRESSED = false; //zoom in
	bool KEY_PLUS_PRESSED = false; //zoom out
	bool KEY_NUM0_PRESSED = false;
	bool KEY_NUM1_PRESSED = false;
	bool KEY_NUM2_PRESSED = false;
	bool KEY_NUM3_PRESSED = false;
	bool KEY_NUM4_PRESSED = false;
	bool KEY_NUM5_PRESSED = false;
	bool KEY_NUM6_PRESSED = false;
	bool KEY_NUM7_PRESSED = false;
	bool KEY_NUM8_PRESSED = false;
	bool KEY_NUM9_PRESSED = false;
	bool MOUSE_LEFTBUTTON_PRESSED = false;
	int MOUSE_X = 0;
	int MOUSE_Y = 0;
public:

		bool key_UP_Pressed()				{ if (KEY_UP_PRESSED) { KEY_UP_PRESSED = false; return true; }return false; }
		bool key_DOWN_Pressed()			{ if (KEY_DOWN_PRESSED) { KEY_DOWN_PRESSED = false; return true; }return false; }
		bool key_LEFT_Pressed()			{ if (KEY_LEFT_PRESSED) { KEY_LEFT_PRESSED = false; return true; }return false; }
		bool key_RIGHT_Pressed()			{ if (KEY_RIGHT_PRESSED) { KEY_RIGHT_PRESSED = false; return true; }return false; }
		bool key_SPACE_Pressed()			{ if (KEY_SPACE_PRESSED) { KEY_SPACE_PRESSED = false; return true; }return false; }
		bool key_TAB_Pressed()			{ if (KEY_TAB_PRESSED) { KEY_TAB_PRESSED = false; return true; }return false; }
		bool key_RETURN_Pressed()			{ if (KEY_RETURN_PRESSED) { KEY_RETURN_PRESSED = false; return true; }return false; }
		bool key_H_Pressed()				{ if (KEY_H_PRESSED) { KEY_H_PRESSED = false; return true; }return false; }
		bool key_LBRACKET_Pressed()		{ if (KEY_LBRACKET_PRESSED) { KEY_LBRACKET_PRESSED = false; return true; }return false; }
		bool key_RBRACKET_Pressed()		{ if (KEY_RBRACKET_PRESSED) { KEY_RBRACKET_PRESSED = false; return true; }return false; }
		bool key_RALT_Pressed()			{ if (KEY_RALT_PRESSED) { KEY_RALT_PRESSED = false; return true; }return false; }
		bool key_LALT_Pressed()			{ if (KEY_LALT_PRESSED) { KEY_LALT_PRESSED = false; return true; }return false; }
		bool key_LSHIFT_Pressed()			{ if (KEY_LSHIFT_PRESSED) { KEY_LSHIFT_PRESSED = false; return true; }return false; }
		bool key_RSHIFT_Pressed()			{ if (KEY_RSHIFT_PRESSED) { KEY_RSHIFT_PRESSED = false; return true; }return false; }
		bool key_LCTRL_Pressed()			{ if (KEY_LCTRL_PRESSED) { KEY_LCTRL_PRESSED = false; return true; }return false; }
		bool key_RCTRL_Pressed()			{ if (KEY_RCTRL_PRESSED) { KEY_RCTRL_PRESSED = false; return true; }return false; }
		bool key_BACKSPACE_Pressed()		{ if (KEY_BACKSPACE_PRESSED) { KEY_BACKSPACE_PRESSED = false; return true; }return false; }
		bool key_ESC_Pressed()			{ if (KEY_ESC_PRESSED) { KEY_ESC_PRESSED = false; return true; }return false; }
		bool key_F1_Pressed()				{ if (KEY_F1_PRESSED) { KEY_F1_PRESSED = false; return true; }return false; }
		bool key_F2_Pressed()				{ if (KEY_F2_PRESSED) { KEY_F2_PRESSED = false; return true; }return false; }
		bool key_F3_Pressed()				{ if (KEY_F3_PRESSED) { KEY_F3_PRESSED = false; return true; }return false; }
		bool key_F4_Pressed()				{ if (KEY_F4_PRESSED) { KEY_F4_PRESSED = false; return true; }return false; }
		bool key_F5_Pressed()				{ if (KEY_F5_PRESSED) { KEY_F5_PRESSED = false; return true; }return false; }
		bool key_F6_Pressed()				{ if (KEY_F6_PRESSED) { KEY_F6_PRESSED = false; return true; }return false; }
		bool key_F7_Pressed()				{ if (KEY_F7_PRESSED) { KEY_F7_PRESSED = false; return true; }return false; }
		bool key_F8_Pressed()				{ if (KEY_F8_PRESSED) { KEY_F8_PRESSED = false; return true; }return false; }
		bool key_F9_Pressed()				{ if (KEY_F9_PRESSED) { KEY_F9_PRESSED = false; return true; }return false; }
		bool key_F10_Pressed()			{ if (KEY_F10_PRESSED) { KEY_F10_PRESSED = false; return true; }return false; }
		bool key_F11_Pressed()			{ if (KEY_F11_PRESSED) { KEY_F11_PRESSED = false; return true; }return false; }
		bool key_F12_Pressed()			{ if (KEY_F12_PRESSED) { KEY_F12_PRESSED = false; return true; }return false; }
		bool key_PRINTSCREEN_Pressed()	{ if (KEY_PRINTSCREEN_PRESSED) { KEY_PRINTSCREEN_PRESSED = false; return true; }return false; }
		bool key_PAUSE_Pressed()			{ if (KEY_PAUSE_PRESSED) { KEY_PAUSE_PRESSED = false; return true; }return false; }
		bool key_TILDE_Pressed()			{ if (KEY_TILDE_PRESSED) { KEY_TILDE_PRESSED = false; return true; }return false; }
		bool key_1_Pressed()				{ if (KEY_1_PRESSED) { KEY_1_PRESSED = false; return true; }return false; }
		bool key_2_Pressed()				{ if (KEY_2_PRESSED) { KEY_2_PRESSED = false; return true; }return false; }
		bool key_3_Pressed()				{ if (KEY_3_PRESSED) { KEY_3_PRESSED = false; return true; }return false; }
		bool key_4_Pressed()				{ if (KEY_4_PRESSED) { KEY_4_PRESSED = false; return true; }return false; }
		bool key_5_Pressed()				{ if (KEY_5_PRESSED) { KEY_5_PRESSED = false; return true; }return false; }
		bool key_6_Pressed()				{ if (KEY_6_PRESSED) { KEY_6_PRESSED = false; return true; }return false; }
		bool key_7_Pressed()				{ if (KEY_7_PRESSED) { KEY_7_PRESSED = false; return true; }return false; }
		bool key_8_Pressed()				{ if (KEY_8_PRESSED) { KEY_8_PRESSED = false; return true; }return false; }
		bool key_9_Pressed()				{ if (KEY_9_PRESSED) { KEY_9_PRESSED = false; return true; }return false; }
		bool key_0_Pressed()				{ if (KEY_0_PRESSED) { KEY_0_PRESSED = false; return true; }return false; }
		bool key_MINUS_Pressed()			{ if (KEY_MINUS_PRESSED) { KEY_MINUS_PRESSED = false; return true; }return false; }
		bool key_PLUS_Pressed()			{ if (KEY_PLUS_PRESSED) { KEY_PLUS_PRESSED = false; return true; }return false; }
		bool key_NUM0_Pressed()			{ if (KEY_NUM0_PRESSED) { KEY_NUM0_PRESSED = false; return true; }return false; }
		bool key_NUM1_Pressed()			{ if (KEY_NUM1_PRESSED) { KEY_NUM1_PRESSED = false; return true; }return false; }
		bool key_NUM2_Pressed()			{ if (KEY_NUM2_PRESSED) { KEY_NUM2_PRESSED = false; return true; }return false; }
		bool key_NUM3_Pressed()			{ if (KEY_NUM3_PRESSED) { KEY_NUM3_PRESSED = false; return true; }return false; }
		bool key_NUM4_Pressed()			{ if (KEY_NUM4_PRESSED) { KEY_NUM4_PRESSED = false; return true; }return false; }
		bool key_NUM5_Pressed()			{ if (KEY_NUM5_PRESSED) { KEY_NUM5_PRESSED = false; return true; }return false; }
		bool key_NUM6_Pressed()			{ if (KEY_NUM6_PRESSED) { KEY_NUM6_PRESSED = false; return true; }return false; }
		bool key_NUM7_Pressed()			{ if (KEY_NUM7_PRESSED) { KEY_NUM7_PRESSED = false; return true; }return false; }
		bool key_NUM8_Pressed()			{ if (KEY_NUM8_PRESSED) { KEY_NUM8_PRESSED = false; return true; }return false; }
		bool key_NUM9_Pressed()			{ if (KEY_NUM9_PRESSED) { KEY_NUM9_PRESSED = false; return true; }return false; }

		bool mouse_LEFTBUTTON_Pressed()			{ if (MOUSE_LEFTBUTTON_PRESSED) { MOUSE_LEFTBUTTON_PRESSED = false; return true; }return false; }




	bool BGCLIENT_UP_HELD = false;
	bool BGCLIENT_DOWN_HELD = false;
	bool BGCLIENT_LEFT_HELD = false;
	bool BGCLIENT_RIGHT_HELD = false;
	bool BGCLIENT_ACTION_HELD = false;
	bool BGCLIENT_CANCELRUN_HELD = false;
	//bool BGCLIENT_START_HELD = false;
	//bool BGCLIENT_SELECT_HELD = false;
	bool BGCLIENT_OPENND_HELD = false;
	bool BGCLIENT_ZOOMOUT_HELD = false;
	bool BGCLIENT_ZOOMIN_HELD = false;
	bool BGCLIENT_ZOOMRESET_HELD = false;
	bool BGCLIENT_OPENMENU_HELD = false;
	bool BGCLIENT_QUICKZOOMOUT_HELD = false;
	bool BGCLIENT_QUICKZOOMIN_HELD = false;

private:

	bool BGCLIENT_UP_PRESSED = false;
	bool BGCLIENT_DOWN_PRESSED = false;
	bool BGCLIENT_LEFT_PRESSED = false;
	bool BGCLIENT_RIGHT_PRESSED = false;
	bool BGCLIENT_ACTION_PRESSED = false;
	bool BGCLIENT_CANCELRUN_PRESSED = false;

	bool BGCLIENT_OPENND_PRESSED = false;//return
	bool BGCLIENT_ZOOMOUT_PRESSED = false;//minus
	bool BGCLIENT_ZOOMIN_PRESSED = false;//plus (equals)
	bool BGCLIENT_ZOOMRESET_PRESSED = false;//backspace
	bool BGCLIENT_OPENMENU_PRESSED = false;//tab, maybe esc
	bool BGCLIENT_QUICKZOOMOUT_PRESSED = false;//rctrl
	bool BGCLIENT_QUICKZOOMIN_PRESSED = false;//rshift

	//bool BGCLIENT_START_PRESSED = false; 
	//bool BGCLIENT_SELECT_PRESSED = false;

public:

	bool bgClient_UP_Pressed() { if (BGCLIENT_UP_PRESSED) { BGCLIENT_UP_PRESSED = false; return true; }return false; }
	bool bgClient_DOWN_Pressed() { if (BGCLIENT_DOWN_PRESSED) { BGCLIENT_DOWN_PRESSED = false; return true; }return false; }
	bool bgClient_LEFT_Pressed() { if (BGCLIENT_LEFT_PRESSED) { BGCLIENT_LEFT_PRESSED = false; return true; }return false; }
	bool bgClient_RIGHT_Pressed() { if (BGCLIENT_RIGHT_PRESSED) { BGCLIENT_RIGHT_PRESSED = false; return true; }return false; }
	bool bgClient_ACTION_Pressed() { if (BGCLIENT_ACTION_PRESSED) { BGCLIENT_ACTION_PRESSED = false; return true; }return false; }
	bool bgClient_CANCELRUN_Pressed() { if (BGCLIENT_CANCELRUN_PRESSED) { BGCLIENT_CANCELRUN_PRESSED = false; return true; }return false; }
	bool bgClient_OPENND_Pressed() { if (BGCLIENT_OPENND_PRESSED) { BGCLIENT_OPENND_PRESSED = false; return true; }return false; }
	bool bgClient_ZOOMOUT_Pressed() { if (BGCLIENT_ZOOMOUT_PRESSED) { BGCLIENT_ZOOMOUT_PRESSED = false; return true; }return false; }
	bool bgClient_ZOOMIN_Pressed() { if (BGCLIENT_ZOOMIN_PRESSED) { BGCLIENT_ZOOMIN_PRESSED = false; return true; }return false; }
	bool bgClient_ZOOMRESET_Pressed() { if (BGCLIENT_ZOOMRESET_PRESSED) { BGCLIENT_ZOOMRESET_PRESSED = false; return true; }return false; }
	bool bgClient_OPENMENU_Pressed() { if (BGCLIENT_OPENMENU_PRESSED) { BGCLIENT_OPENMENU_PRESSED = false; return true; }return false; }
	bool bgClient_QUICKZOOMOUT_Pressed() { if (BGCLIENT_QUICKZOOMOUT_PRESSED) { BGCLIENT_QUICKZOOMOUT_PRESSED = false; return true; }return false; }
	bool bgClient_QUICKZOOMIN_Pressed() { if (BGCLIENT_QUICKZOOMIN_PRESSED) { BGCLIENT_QUICKZOOMIN_PRESSED = false; return true; }return false; }





	bool MINIGAME_UP_HELD = false;
	bool MINIGAME_DOWN_HELD = false;
	bool MINIGAME_LEFT_HELD = false;
	bool MINIGAME_RIGHT_HELD = false;
	bool MINIGAME_ANALOGUP_HELD = false;
	bool MINIGAME_ANALOGDOWN_HELD = false;
	bool MINIGAME_ANALOGLEFT_HELD = false;
	bool MINIGAME_ANALOGRIGHT_HELD = false;
	//Space bar or B button, //TODO: can be customized to either a or b
	bool MINIGAME_ACTION_HELD = false;
	//Left Shift or A button, //TODO: can be customized to either a or b
	bool MINIGAME_RUN_HELD = false;
	//Return key or Start button
	bool MINIGAME_START_HELD = false;
	//Esc key or Select button
	bool MINIGAME_SELECT_HELD = false;
	bool MINIGAME_L_HELD = false;
	bool MINIGAME_R_HELD = false;
	bool MINIGAME_Y_HELD = false;
	bool MINIGAME_X_HELD = false;
	bool MINIGAME_A_HELD = false;
	bool MINIGAME_B_HELD = false;

private:
	bool MINIGAME_UP_PRESSED = false;
	bool MINIGAME_DOWN_PRESSED = false;
	bool MINIGAME_LEFT_PRESSED = false;
	bool MINIGAME_RIGHT_PRESSED = false;	
	bool MINIGAME_ANALOGUP_PRESSED = false;
	bool MINIGAME_ANALOGDOWN_PRESSED = false;
	bool MINIGAME_ANALOGLEFT_PRESSED = false;
	bool MINIGAME_ANALOGRIGHT_PRESSED = false;

	//Space bar or B button, //TODO: can be customized to either a or b
	//bool MINIGAME_ACTION_PRESSED = false;
	//Left Shift or A button, //TODO: can be customized to either a or b
	//bool MINIGAME_RUN_PRESSED = false;
	//Return key or Start button
	//bool MINIGAME_START_PRESSED = false;
	//Esc key or Select button
	//bool MINIGAME_SELECT_PRESSED = false;


	bool MINIGAME_L_PRESSED = false;//lctrl?
	bool MINIGAME_R_PRESSED = false;
	bool MINIGAME_Y_PRESSED = false;
	bool MINIGAME_X_PRESSED = false;
	bool MINIGAME_A_PRESSED = false;
	bool MINIGAME_B_PRESSED = false;

public:

	bool miniGame_UP_Pressed() { if (MINIGAME_UP_PRESSED) { MINIGAME_UP_PRESSED = false; return true; }return false; }
	bool miniGame_DOWN_Pressed() { if (MINIGAME_DOWN_PRESSED) { MINIGAME_DOWN_PRESSED = false; return true; }return false; }
	bool miniGame_LEFT_Pressed() { if (MINIGAME_LEFT_PRESSED) { MINIGAME_LEFT_PRESSED = false; return true; }return false; }
	bool miniGame_RIGHT_Pressed() { if (MINIGAME_RIGHT_PRESSED) { MINIGAME_RIGHT_PRESSED = false; return true; }return false; }
	bool miniGame_ANALOGUP_Pressed() { if (MINIGAME_ANALOGUP_PRESSED) { MINIGAME_ANALOGUP_PRESSED = false; return true; }return false; }
	bool miniGame_ANALOGDOWN_Pressed() { if (MINIGAME_ANALOGDOWN_PRESSED) { MINIGAME_ANALOGDOWN_PRESSED = false; return true; }return false; }
	bool miniGame_ANALOGLEFT_Pressed() { if (MINIGAME_ANALOGLEFT_PRESSED) { MINIGAME_ANALOGLEFT_PRESSED = false; return true; }return false; }
	bool miniGame_ANALOGRIGHT_Pressed() { if (MINIGAME_ANALOGRIGHT_PRESSED) { MINIGAME_ANALOGRIGHT_PRESSED = false; return true; }return false; }



	bool miniGame_L_Pressed() { if (MINIGAME_L_PRESSED) { MINIGAME_L_PRESSED = false; return true; }return false; }
	bool miniGame_R_Pressed() { if (MINIGAME_R_PRESSED) { MINIGAME_R_PRESSED = false; return true; }return false; }
	bool miniGame_Y_Pressed() { if (MINIGAME_Y_PRESSED) { MINIGAME_Y_PRESSED = false; return true; }return false; }
	bool miniGame_X_Pressed() { if (MINIGAME_X_PRESSED) { MINIGAME_X_PRESSED = false; return true; }return false; }
	bool miniGame_A_Pressed() { if (MINIGAME_A_PRESSED) { MINIGAME_A_PRESSED = false; return true; }return false; }
	bool miniGame_B_Pressed() { if (MINIGAME_B_PRESSED) { MINIGAME_B_PRESSED = false; return true; }return false; }


	//these don't have HOLD equivalents because they dont need them as they are not game keys


	//Enter key or Start button
	bool miniGame_START_Pressed()
	{

		//if (MINIGAME_START_PRESSED) { MINIGAME_START_PRESSED = false; return true; }return false;

		if (key_RETURN_Pressed())return true;

		for (int i = 0; i < gameControllers.size(); i++)
		{
			GameController *g = gameControllers.get(i);
			if (g->start_Pressed())return true;
		}
		return false;
	}

	//Esc key or Select button
	bool miniGame_SELECT_Pressed()
	{
		//if (MINIGAME_SELECT_PRESSED) { MINIGAME_SELECT_PRESSED = false; return true; }return false;

		if (key_ESC_Pressed())return true;

		for (int i = 0; i < gameControllers.size(); i++)
		{
			GameController *g = gameControllers.get(i);
			if (g->select_Pressed())return true;
		}
		return false;
	}

	bool miniGame_ACTION_Pressed()
	{
		//if (MINIGAME_ACTION_PRESSED) { MINIGAME_ACTION_PRESSED = false; return true; }return false;
		if (key_SPACE_Pressed())return true;

		for (int i = 0; i < gameControllers.size(); i++)
		{
			GameController *g = gameControllers.get(i);
			if (g->b_Pressed())return true;
		}
		return false;

	}
	bool miniGame_RUN_Pressed()
	{
		//if (MINIGAME_RUN_PRESSED) { MINIGAME_RUN_PRESSED = false; return true; }return false;

		if (key_LSHIFT_Pressed())return true;

		for (int i = 0; i < gameControllers.size(); i++)
		{
			GameController *g = gameControllers.get(i);
			if (g->a_Pressed())return true;
		}
		return false;
	}


	//Esc key or Start button
	bool miniGame_PAUSE_Pressed()
	{
		//if (MINIGAME_START_PRESSED) { MINIGAME_START_PRESSED = false; return true; }
		//if (KEY_ESC_PRESSED) { KEY_ESC_PRESSED = false; return true; }

		if (key_ESC_Pressed())return true;
		if (miniGame_START_Pressed())return true;
		return false;
	}

	//Enter key, Start button, or Space bar or bottom button (a on xbox, x on playstation, japanese controls are opposite)
	bool miniGame_CONFIRM_Pressed()
	{
		//MINIGAME_START already does this
		//if (KEY_RETURN_PRESSED) { KEY_RETURN_PRESSED = false; return true; }

		//if (KEY_SPACE_PRESSED) { KEY_SPACE_PRESSED = false; return true; }

		//was MINIGAME_ACTION but now that is mapped to b and is inconsistent

		//if (MINIGAME_A_PRESSED) { MINIGAME_A_PRESSED = false; return true; }//TODO: can be customized to either a or b
		//if (MINIGAME_START_PRESSED) { MINIGAME_START_PRESSED = false; return true; }
		
		if (miniGame_ACTION_Pressed())return true;
		if (miniGame_START_Pressed())return true;

		
		return false;
	}





	//LShift key, Esc key, or RunCancel (Left Shift or A button)
	bool miniGame_CANCEL_Pressed()
	{

		if (KEY_ESC_PRESSED) { KEY_ESC_PRESSED = false; return true; }
		//if (KEY_LSHIFT_PRESSED) { KEY_LSHIFT_PRESSED = false; return true; }
		if (MINIGAME_B_PRESSED) { MINIGAME_B_PRESSED = false; return true; }//TODO: can be customized to either a or b

		return false;
	}


//	bool MOUSE_0_PRESSED = false;
//	bool MOUSE_0_HELD = false;
//	bool MOUSE_1_PRESSED = false;
//	bool MOUSE_1_HELD = false;


	char pszGUID[4096];

	string text;

	static void initControllers();
	void resetPressedButtons();
	void setButtonStates();

	static void cleanup();
	int getMouseX();
	int getMouseY();
};

