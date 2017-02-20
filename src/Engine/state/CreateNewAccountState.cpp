#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger CreateNewAccountState::log = Logger("CreateNewAccountState");


CreateNewAccountState::CreateNewAccountState()
{ //=========================================================================================================================


	createNewAccount = new CreateNewAccount();

	//createNewAccountGUI = new GUI(createNewAccount, GLUtils::TWLrenderer);
	//createNewAccountGUI->applyTheme(GLUtils::TWLthemeManager);
}

void CreateNewAccountState::update()
{ //=========================================================================================================================

	createNewAccount->update();
}

void CreateNewAccountState::render()
{ //=========================================================================================================================
	{
		//SlickCallable.leaveSafeBlock();//weird slick texture errors if i dont do this
		createNewAccount->renderBefore();
		//createNewAccountGUI->update();
		createNewAccount->render();
	}
	//SlickCallable.enterSafeBlock();
}

void CreateNewAccountState::cleanup()
{ //=========================================================================================================================
	//createNewAccountGUI->destroy();
}

