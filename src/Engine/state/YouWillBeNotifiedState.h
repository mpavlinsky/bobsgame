//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class YouWillBeNotifiedState : public State
{
public:

	static Logger log;

	YouWillBeNotifiedState();


	virtual void update() override;


	virtual void render() override;


	virtual void cleanup() override;
};

