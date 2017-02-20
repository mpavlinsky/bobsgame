//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class Ramio : public NDGameEngine
{
public:

	static Logger log;


	Ramio(ND* nD);


	bool playing = true;
	bool won = false;

	static int timer;
	static int initialTimer;
	static int ticksToAddForMoneyBlock;


	Caption* RAMIO_timercaption = nullptr;

	bool easymode = true;


	int highScore = 142;
	int score = 0;
	bool gotHighScore = false;


	int deadX = 0;
	int deadY = 0;
	bool dead = false;


	bool credits = false;
	bool creditScreenInit = false;
	bool initialized = false;


	long long ticks = 0;


	int winSequenceStep = 0;
	int dieSequenceStep = 0;


	ArrayList<RamioBoba*>* bobas = new ArrayList<RamioBoba*>();
	ArrayList<RamioBrickBlock*>* brickBlocks = new ArrayList<RamioBrickBlock*>();
	ArrayList<RamioMoneyBlock*>* moneyBlocks = new ArrayList<RamioMoneyBlock*>();


	RamioGuy* guy;


	virtual void updateScore();


	virtual bool checkHit(int dir);


	virtual void initGame();


	virtual void doWinSequence();


	virtual void doDeathSequence();


	ConsoleText* ramioText = Console::add("ramioText", BobColor::green);

	virtual void update() override;


	virtual void render() override;
};

