//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class RamioGuy;

class RamioBoba : public Entity
{
public:

	static Logger log;


	RamioBoba(Engine* g);


	bool dead = false;


	virtual bool checkHitLayerBlocksAndOtherBobas(int dir);


	virtual void update() override;


	virtual bool checkStomp(RamioGuy* guy);


	virtual bool checkRunningInto(RamioGuy* guy);
};

