//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class LoginState : public State
{
public:

	static Logger log;


	//GUI* loginScreenGUI = nullptr;
	LoginScreen* loginScreen = nullptr;


	LoginState();


	virtual void update() override;


	virtual void render() override;


	virtual void cleanup() override;
};

