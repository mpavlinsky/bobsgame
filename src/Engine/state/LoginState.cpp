#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger LoginState::log = Logger("LoginState");


LoginState::LoginState()
{ //=========================================================================================================================

	loginScreen = new LoginScreen();
	//
	//   loginScreenGUI = new GUI(loginScreen, GLUtils::TWLrenderer);
	//   loginScreenGUI->applyTheme(GLUtils::TWLthemeManager);
}

void LoginState::update()
{ //=========================================================================================================================
	loginScreen->update();
}

void LoginState::render()
{ //=========================================================================================================================


	{
		//SlickCallable.leaveSafeBlock();//weird slick texture errors if i dont do this
		loginScreen->renderBefore();
		//loginScreenGUI->update();
		loginScreen->render();
	}
	//SlickCallable.enterSafeBlock();
}

void LoginState::cleanup()
{ //=========================================================================================================================
	//loginScreenGUI->destroy();
}

