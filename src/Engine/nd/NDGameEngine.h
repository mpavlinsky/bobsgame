//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




#include "../MiniGameEngine.h"
#include "GameDataLoader.h"

class ND;

class BobTexture;
class Caption;

class NDGameEngine : public MiniGameEngine
{
private:
	typedef MiniGameEngine super;
public:
	static Logger log;

protected:
	ND* nD = nullptr;


public:
	
	NDGameEngine();
	virtual ~NDGameEngine();
	NDGameEngine(ND* nD);
	virtual void init();

	virtual void tryToCloseGame();

};

