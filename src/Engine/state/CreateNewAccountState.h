//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class CreateNewAccountState : public State
{
public:

	static Logger log;


	CreateNewAccount* createNewAccount = nullptr;
	//GUI* createNewAccountGUI = nullptr;


	CreateNewAccountState();


	virtual void update() override;


	virtual void render() override;


	virtual void cleanup() override;
};

