//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
#include "src/Utility/HashMap.h"
#include "src/Utility/ArrayList.h"
#include <mutex>
class Logger;




class ConsoleText;
class BobColor;
class CaptionManager;



//================
//defines
//================


//================
//variables
//================

extern bool error_console_on;



extern DEBUG_overlay_STRUCT* DEBUG_overlays[128];



//================
//prototypes
//================

void ERROR_init_error_console();

void DEBUG_delete_overlay(DEBUG_overlay_STRUCT* overlay);
DEBUG_overlay_STRUCT* DEBUG_make_overlay(string text, float x, float y);
void DEBUG_update_overlay(DEBUG_overlay_STRUCT* overlay, string text, float, float);
void DEBUG_draw_overlays();

void DEBUG_draw_text(float screenX0, float screenY0, string text, BobColor* color);

//void gl_check_errors(int val);
void error_console(string error_string);
void ERROR_set_error(string error_string);
void ERROR_draw_error_console();


class Console
{
public:
	static Logger log;

	static CaptionManager* captionManager;

	static ArrayList<ConsoleText*>* consoleTextList;
	static mutex _consoleTextList_Mutex;

	Console();
	virtual void update();
	static ConsoleText* error(const string& s);
	static ConsoleText* error(const string& s, int ticks);
	static ConsoleText* error(const string& s, BobColor* c);
	static ConsoleText* error(const string& s, BobColor* c, int ticks);
	static ConsoleText* error(const string& s, int x, int y);
	static ConsoleText* error(const string& s, BobColor* c, int x, int y);


	static ConsoleText* debug(const string& s);

	static ConsoleText* debug(const string& s, int ticks);


	static ConsoleText* debug(const string& s, BobColor* c);


	static ConsoleText* debug(const string& s, BobColor* c, int ticks);


	static ConsoleText* debug(const string& s, int x, int y);


	static ConsoleText* debug(const string& s, BobColor* c, int x, int y);


	static ConsoleText* add(const string& s);


	static ConsoleText* add(const string& s, int ticks);


	static ConsoleText* add(const string& s, BobColor* c);


	static ConsoleText* add(const string& s, BobColor* c, int ticks);


	/// <summary>
	/// If x OR y is -1, it is centered on that axis. If both are -1, it is displayed in the console. </summary>
	static ConsoleText* add(const string& s, int x, int y);


	/// <summary>
	/// If x OR y is -1, it is centered on that axis. If both are -1, it is displayed in the console. </summary>
	static ConsoleText* add(const string& s, int x, int y, int ticks);


	/// <summary>
	/// If x OR y is -1, it is centered on that axis. If both are -1, it is displayed in the console. </summary>
	static ConsoleText* add(const string& s, BobColor* c, int x, int y);


	/// <summary>
	/// If x OR y is -1, it is centered on that axis. If both are -1, it is displayed in the console. </summary>
	static ConsoleText* add(const string& s, BobColor* c, int x, int y, int ticks);


	/// <summary>
	/// If x OR y is -1, it is centered on that axis. If both are -1, it is displayed in the console. </summary>
	static ConsoleText* add(const string& s, BobColor* c, int x, int y, int ticks, bool isDebug);



	void render();
};

