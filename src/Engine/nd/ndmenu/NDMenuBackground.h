//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;





#include "../../state/GlowTileBackground.h"


class NDMenuBackground : public GlowTileBackground
{
public:

	static Logger log;


	NDMenuBackground(Engine* g);


	virtual void init();
};

