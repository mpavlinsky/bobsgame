//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class RamioBrickBlock : public RamioBlock
{
public:

	static Logger log;


	RamioBrickBlock(Engine* g);


	int open = 0;
	int contains = 0;


	virtual void getHit();
};

