//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class LoggedOutState : public State
{
public:

	static Logger log;

	LoggedOutState();


	virtual void update() override;


	virtual void render() override;


	virtual void cleanup() override;
};

