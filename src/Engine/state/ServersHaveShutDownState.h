//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class ServersHaveShutDownState : public State
{
public:

	static Logger log;


	ServersHaveShutDownState();


	virtual void update() override;


	virtual void render() override;


	virtual void cleanup() override;
};

