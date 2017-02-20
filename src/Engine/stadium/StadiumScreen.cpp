#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger StadiumScreen::log = Logger("StadiumScreen");


StadiumScreen::StadiumScreen(Engine* g)
{ //=========================================================================================================================
	this->e = g;

	stadiumGameStateManager = new StateManager();
}

void StadiumScreen::update()
{ //=========================================================================================================================


	if (getIsActivated() == false)
	{
		return;
	}

	State* s = stadiumGameStateManager->getState();
	if (s == nullptr)
	{
		return;
	}


	GLUtils::globalDrawScale = GLUtils::FBO_SCALE;
	if (s != nullptr)
	{
		stadiumGameStateManager->update();
	}
	GLUtils::globalDrawScale = 1.0f;
}

void StadiumScreen::setGame(MiniGameEngine* game, Area* area)
{ //=========================================================================================================================

	this->area = area;


	stadiumGameStateManager->setState(game);

	this->setActivated(true);
}

MiniGameEngine* StadiumScreen::getGame()
{ //=========================================================================================================================
	return static_cast<MiniGameEngine*>(stadiumGameStateManager->getState());
}

void StadiumScreen::render()
{ //=========================================================================================================================

	if (getIsActivated() == false)
	{
		return;
	}

	if (area == nullptr)
	{
		return;
	}

	if (stadiumGameStateManager->getState() == nullptr)
	{
		return;
	}

	float x0 = area->screenLeft();
	float x1 = area->screenRight();
	float y0 = area->screenTop();
	float y1 = area->screenBottom();


	//--------------------------
	//set the framebuffer to the nD FBO
	//--------------------------
	GLUtils::bindFBO(GLUtils::preColorFilterFBO);
	//glDrawBuffer(GL_COLOR_ATTACHMENT0);

	GLUtils::setPreColorFilterViewport();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//--------------------------
	//render the game, which should render the map and entities, etc first.
	//--------------------------
	GLUtils::globalDrawScale = GLUtils::FBO_SCALE;
	stadiumGameStateManager->render();
	GLUtils::globalDrawScale = 1.0f;


	//--------------------------
	//set main FBO
	//--------------------------

	GLUtils::bindFBO(GLUtils::postColorFilterFBO); //set the framebuffer object to the MAIN FBO
	GLUtils::drawIntoFBOAttachment(0); //set which framebuffer object to draw into (whatever buffer is set with glBindFramebuffer)

	//--------------------------
	//set main viewport
	//--------------------------
	GLUtils::setPostColorFilterViewport();

	//--------------------------
	//clear the main FBO
	//--------------------------
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClear(GL_COLOR_BUFFER_BIT);


	//--------------------------
	//draw nD FBO texture to main FBO
	//--------------------------


	//draw black background
	//GLUtils.drawFilledRect(8,8,8,x0,x1,y0,y1,1.0f);

	//draw nD screen  (upside down because FBO is flipped)
	//GLUtils.drawTexture(GLUtils.nDFBO_Texture, 0.0f, 1.0f, 1.0f, 0.0f, x0, x1, y0, y1, 1.0f, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);


	//--------------------------
	// draw MAIN FBO texture into SCREEN BUFFER
	//--------------------------

	if (GLUtils::useShaders)
	{
		GLUtils::useShader(GLUtils::colorShader);

		GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameHue", 1.0f);
		GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameSaturation", 1.2f);
		GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameBrightness", 1.0f);
		GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameContrast", 1.2f);
		GLUtils::setShaderVar1f(GLUtils::colorShader, (char*)"gameGamma", 1.0f);
		GLUtils::setShaderVar1i(GLUtils::colorShader, (char*)"Tex0", 0);
	}

	//draw the framebuffer with the lights drawn into it into the screen buffer  (upside down because FBO is flipped)
	//if(!Keyboard.isKeyDown(Keyboard.KEY_SEMICOLON))
	GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); //this fixes the small shadow problems, and also makes the doorknob glow brighter.
	//GLUtils.drawTexture(GLUtils.mainFBO_Texture, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, (int)(GLUtils.getViewportWidth()), 0.0f, (int)(GLUtils.getViewportHeight()), 1.0f, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);

	GLUtils::drawTexture(GLUtils::preColorFilterFBO_Texture_Attachment0, 0.0f, 1.0f, 1.0f, 0.0f, x0, x1, y0, y1, 1.0f, GLUtils::DEFAULT_ND_FBO_FILTER);

	//GLUtils.drawTexture(GLUtils.mainFBO_Texture, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, (int)(GLUtils.getViewportWidth()), 0.0f, (int)(GLUtils.getViewportHeight()), 1.0f, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);
	//if(!Keyboard.isKeyDown(Keyboard.KEY_APOSTROPHE))
	GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	if (GLUtils::useShaders)
	{
		GLUtils::useShader(0);
	}


	//
	//		boolean drawScreenLight = true;
	//
	//		if(GLUtils.useShader)
	//		{
	//			if(drawScreenLight)
	//			{
	//
	//				//--------------------------
	//				// set LIGHTS buffer in MAIN FBO
	//				//--------------------------
	//				//switch to LIGHTS buffer attachment
	//				glDrawBuffer(GL_COLOR_ATTACHMENT1);//draws into lightFBOTextureID
	//				glClear(GL_COLOR_BUFFER_BIT);
	//
	//				//--------------------------
	//				//draw the main FBO texture into the LIGHTS buffer attachment (upside down because FBO is flipped)
	//				//--------------------------
	//				GLUtils.drawTexture(GLUtils.mainFBO_Texture, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, (int)(GLUtils.getViewportWidth()), 0.0f, (int)(GLUtils.getViewportHeight()), 1.0f, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);
	//
	//				//--------------------------
	//				//switch to MAIN buffer attachment in MAIN FBO
	//				//--------------------------
	//				glDrawBuffer(GL_COLOR_ATTACHMENT0);//draws into mainFBOTextureID
	//
	//
	//				//--------------------------
	//				// draw light into MAIN FBO mixing with LIGHT BUFFER TEXTURE (copy of MAIN FBO) to blend nicely
	//				//--------------------------
	//				glUseProgram(GLUtils.lightShader);
	//
	//				//set the LIGHTS FBO texture to texture 0, we drew the main FBO (maps and sprites) into it and we are going to use it to blend
	//				glActiveTexture(GL_TEXTURE0);
	//				glEnable(GL_TEXTURE_2D);
	//				glBindTexture(GL_TEXTURE_2D, GLUtils.mainFBO_lightTexture);
	//
	//
	//				glActiveTexture(GL_TEXTURE1);//switch to texture 1, we are going to bind the light textures to this when we draw them.
	//				glEnable(GL_TEXTURE_2D);
	//
	//
	//				glUniform1i(glGetUniformLocation(GLUtils.lightShader, new StringBuffer("Tex0")), 0);
	//				glUniform1i(glGetUniformLocation(GLUtils.lightShader, new StringBuffer("Tex1")), 1);
	//				glUniform1f(glGetUniformLocation(GLUtils.lightShader, new StringBuffer("width")), Display.getWidth());
	//				glUniform1f(glGetUniformLocation(GLUtils.lightShader, new StringBuffer("height")), Display.getHeight());
	//
	//
	//				float lightOffset = 48*Cameraman().zoom;
	//				//draw screen light
	//				if(light!=null)light.renderLight(x0-lightOffset,x1+lightOffset,y0-lightOffset,y1+lightOffset,lightAlpha);
	//
	//
	//				//disable texture2D on texture unit 1
	//				glActiveTexture(GL_TEXTURE1);
	//				glDisable(GL_TEXTURE_2D);
	//
	//				//switch back to texture unit 0
	//				glActiveTexture(GL_TEXTURE0);
	//				glDisable(GL_TEXTURE_2D);
	//
	//				glUseProgram(0);
	//			}
	//		}

	//
	//		//--------------------------
	//		// switch back to SCREEN BUFFER (has game drawn in it)
	//		//--------------------------
	//
	//		glBindFramebuffer(GL_FRAMEBUFFER, 0);//set the framebuffer back to the screen buffer
	//		glEnable(GL_TEXTURE_2D);
	//
	//		GLUtils.setViewport();
	//
	//		//--------------------------
	//		// draw MAIN FBO texture into SCREEN BUFFER
	//		//--------------------------
	//
	//		if(GLUtils.useShader)
	//		{
	//			glUseProgram(GLUtils.colorShader);
	//
	//			glUniform1f(glGetUniformLocation(GLUtils.colorShader, new StringBuffer("gameHue")), 1.0f);
	//			glUniform1f(glGetUniformLocation(GLUtils.colorShader, new StringBuffer("gameSaturation")), 1.2f);
	//			glUniform1f(glGetUniformLocation(GLUtils.colorShader, new StringBuffer("gameBrightness")), 1.0f);
	//			glUniform1f(glGetUniformLocation(GLUtils.colorShader, new StringBuffer("gameContrast")), 1.2f);
	//			glUniform1f(glGetUniformLocation(GLUtils.colorShader, new StringBuffer("gameGamma")), 1.0f);
	//			glUniform1i(glGetUniformLocation(GLUtils.colorShader, new StringBuffer("Tex0")), 0);
	//		}
	//
	//		//draw the framebuffer with the lights drawn into it into the screen buffer  (upside down because FBO is flipped)
	//		GLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);//this fixes the small shadow problems, and also makes the doorknob glow brighter.
	//		//GLUtils.drawTexture(GLUtils.mainFBO_Texture, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, (int)(GLUtils.getViewportWidth()), 0.0f, (int)(GLUtils.getViewportHeight()), 1.0f, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);
	//		GLUtils.drawTexture(GLUtils.mainFBO_Texture, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, (int)(GLUtils.getViewportWidth()), 0.0f, (int)(GLUtils.getViewportHeight()), 1.0f, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);
	//		GLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//
	//
	//		if(GLUtils.useShader)
	//		{
	//			glUseProgram(0);
	//		}
	//
}

