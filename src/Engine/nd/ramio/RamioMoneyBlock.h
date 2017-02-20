//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class RamioMoneyBlock : public RamioBlock
{
public:

	static Logger log;


	RamioMoneyBlock(Engine* g);


	bool open = false;
	bool contains = false;


	virtual void getHit();
};

