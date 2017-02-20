

#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger ND::log = Logger("ND");



ND::ND()
{ //=========================================================================================================================
	//MenuPanel();

	texture = GLUtils::getTextureFromPNG("data/nD/nD.png");

	widthTextureAspectRatio = ((float)(texture->getTextureWidth()) / (float)(texture->getImageWidth()));
	heightTextureAspectRatio = ((float)(texture->getTextureHeight()) / (float)(texture->getImageHeight()));
	widthToHeightRatio = ((float)(texture->getTextureWidth()) / (float)(texture->getTextureHeight()));


	nDGameStateManager = new StateManager();
}

void ND::init()
{ //=========================================================================================================================

	fadeInTime = 1500.0f; //override MenuPanel defaults, since we are zooming in, not scrolling in.
	fadeOutTime = 500.0f;
}

void ND::update()
{ //=========================================================================================================================


	targetWidth = GLUtils::getViewportWidth() * 2.00f;


	MenuPanel::update();


	State* s = nDGameStateManager->getState();

	if (isActivated == true)
	{
		GLUtils::globalDrawScale = GLUtils::FBO_SCALE;
		if (s != nullptr)
		{
			nDGameStateManager->update();
		}
		GLUtils::globalDrawScale = 1.0f;
	}

	if (s != nullptr)
	{
		if (lightFadeInOutToggle == true)
		{
			if (lightAlpha < lightMaxAlpha)
			{
				lightAlpha += s->engineTicksPassed() * (lightFadeSpeedMult);

				if (lightAlpha >= lightMaxAlpha)
				{
					lightAlpha = lightMaxAlpha;
					lightFadeInOutToggle = false;
				}
			}
		}
		else
		{
			if (lightAlpha >= lightMinAlpha)
			{
				lightAlpha -= s->engineTicksPassed() * (lightFadeSpeedMult);

				if (lightAlpha < lightMinAlpha)
				{
					lightAlpha = lightMinAlpha;
					lightFadeInOutToggle = true;
				}
			}
		}


		if (isScrolledUp == true)
		{
			fadeOutMeshTicks += s->engineTicksPassed();

			if (fadeOutMeshTicks > fadeOutMeshTicksSpeed)
			{
				fadeOutMeshTicks = 0;
				fadeMesh = false;
			}

			if (fadeMesh)
			{
				drawMeshAlpha = 0.1f + (0.5f - (0.5f * ((float)(fadeOutMeshTicks) / (float)(fadeOutMeshTicksSpeed))));
			}
			else
			{
				drawMeshAlpha = 0.1f;
			}
		}
	}


	ndZoomText->text = string("nD zoom: ") + to_string(nDZoom);
}

void ND::setGame(NDGameEngine* game)
{ //=========================================================================================================================

	light = new Light(game, "nDScreenLight", 0, 0, GLUtils::getViewportWidth(), GLUtils::getViewportHeight(), 240, 240, 255, 60, 32, 2.0f, 1.0f, 0, true, true);


	nDGameStateManager->setState(game);
}

NDGameEngine* ND::getGame()
{ //=========================================================================================================================
	return static_cast<NDGameEngine*>(nDGameStateManager->getState());
}

void ND::toggleActivated()
{ //=========================================================================================================================

	if (isActivated == false)
	{
		setActivated(true);
	}
	else
	{
		if (isActivated == true)
		{
			if (isScrollingDown == true)
			{
				isScrollingDown = false;
			}
			else
			{
				//ask the game to close instead of directly closing!

				if (getGame() != nullptr)
				{
					getGame()->tryToCloseGame();
				}
				else
				{
					setActivated(false);
				}
			}
		}
	}
}

void ND::setActivated(bool b)
{ //=========================================================================================================================

	if (b == true && getEnabled() == false)
	{
		return;
	}


	if (getClientGameEngine() != nullptr)
	{
		if (b == true)
		{
			BobNet::myStatus = BobNet::status_PLAYING_GAME;
		}
		else
		{
			BobNet::myStatus = BobNet::status_AVAILABLE;
		}
	}


	MenuPanel::setActivated(b);
}

void ND::onScrolledUp()
{ //=========================================================================================================================
}

void ND::scrollUp()
{ //=========================================================================================================================

	if (widthThisFrame != targetWidth)
	{
		if (ticksSinceTurnedOn <= fadeInTime)
		{
			widthThisFrame = (float)(Easing::easeOutParabolicBounce(ticksSinceTurnedOn, 0.0f, targetWidth, fadeInTime));
		}
		else
		{
			widthThisFrame = targetWidth;
		}

		float zWidth = widthTextureAspectRatio * widthThisFrame;
		//float zHeight = (widthTextureAspectRatio / widthToHeightRatio) * widthThisFrame;

		nDDrawAlpha = (widthThisFrame * 2.0f) / targetWidth;
		if (nDDrawAlpha > 1.0f)
		{
			nDDrawAlpha = 1.0f;
		}

		nDZoom = zWidth / texture->getTextureWidth();
	}
	else
	{
		if (isScrolledUp == false)
		{
			onScrolledUp();
			isScrolledUp = true;
		}
	}
}

void ND::scrollDown()
{ //=========================================================================================================================

	if (widthThisFrame > 0)
	{
		fadeMesh = true;
		fadeOutMeshTicks = 0;
		drawMeshAlpha = 1.0f;

		widthThisFrame = targetWidth - (float)(Easing::easeInBackSlingshot(ticksSinceTurnedOff, 0.0f, targetWidth, fadeOutTime));

		float zWidth = widthTextureAspectRatio * (widthThisFrame);
		//float zHeight = (widthTextureAspectRatio / widthToHeightRatio) * (widthThisFrame);

		nDDrawAlpha = (widthThisFrame * 2.0f) / targetWidth;
		if (nDDrawAlpha > 1.0f)
		{
			nDDrawAlpha = 1.0f;
		}

		nDZoom = zWidth / texture->getTextureWidth();
	}
	else
	{
		isActivated = false;
		isScrollingDown = false;
	}
}



void ND::render()
{ //=========================================================================================================================

	if (isActivated == false)
	{
		return;
	}


	if (texture == nullptr)
	{
		return;
	}


	float tx0 = 0.0f;
	float tx1 = 1.0f;
	float ty0 = 0.0f;
	float ty1 = 1.0f;

	float x0 = 0;
	float x1 = 0;
	float y0 = 0;
	float y1 = 0;


	//calculate width and height based on zoom

	float zWidth = (float)(texture->getImageWidth()) * widthTextureAspectRatio * nDZoom;
	float zHeight = (float)(texture->getImageHeight()) * heightTextureAspectRatio * nDZoom;

	//calculate screen x and y by centering based on width and height
	float screenX = (GLUtils::getViewportWidth() - (zWidth / widthTextureAspectRatio)) / 2.0f;
	float screenY = (GLUtils::getViewportHeight() - (zHeight / heightTextureAspectRatio)) / 2.0f;


	x0 = screenX;
	x1 = screenX + (zWidth);
	y0 = screenY;
	y1 = screenY + (zHeight);


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
	nDGameStateManager->render();
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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//--------------------------
	//draw nD console background to main FBO
	//--------------------------
	GLUtils::drawTexture(texture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, nDDrawAlpha, GLUtils::FILTER_LINEAR);


	//--------------------------
	//draw nD FBO texture to main FBO
	//--------------------------

	float screenScale = (640.0f / (float)(GLUtils::getViewportWidth())) * (float)(GLUtils::FBO_SCALE);
	//302x258
	float inScreenX = (((float)(texture->getImageWidth()) - GLUtils::getViewportWidth() * screenScale) / 2) * nDZoom;
	float inScreenY = (((float)(texture->getImageHeight()) - GLUtils::getViewportHeight() * screenScale) / 2) * nDZoom;
	float inScreenWidth = GLUtils::getViewportWidth() * screenScale * nDZoom;
	float inScreenHeight = GLUtils::getViewportHeight() * screenScale * nDZoom;


	float nDScreenOnScreenX0 = screenX + inScreenX;
	float nDScreenOnScreenX1 = screenX + inScreenX + inScreenWidth;

	float nDScreenOnScreenY0 = screenY + inScreenY;
	float nDScreenOnScreenY1 = screenY + inScreenY + inScreenHeight;


	//draw black background
	GLUtils::drawFilledRect(8, 8, 8, nDScreenOnScreenX0, nDScreenOnScreenX1, nDScreenOnScreenY0, nDScreenOnScreenY1, 1.0f);

	//draw nD screen  (upside down because FBO is flipped)
	GLUtils::drawTexture(GLUtils::preColorFilterFBO_Texture_Attachment0, 0.0f, 1.0f, 1.0f, 0.0f, nDScreenOnScreenX0, nDScreenOnScreenX1, nDScreenOnScreenY0, nDScreenOnScreenY1, 1.0f, GLUtils::DEFAULT_ND_FBO_FILTER);


	//--------------------------
	// draw pixel mesh to main FBO
	//--------------------------

	//TODO: make glowing power lights, maybe slight glow on screen, maybe slight pixel filter on screen


	{
		//if(fadeMesh)

		//draw pixel mesh
		int meshDiv = GLUtils::getViewportWidth() / 320;

		for (int x = 0; x < GLUtils::getViewportWidth() / meshDiv; x++)
		{
			GLUtils::drawLine(nDScreenOnScreenX0 + (x * meshDiv * screenScale * nDZoom), nDScreenOnScreenY0, nDScreenOnScreenX0 + (x * meshDiv * screenScale * nDZoom), nDScreenOnScreenY1, 0.1f, 0.1f, 0.1f, drawMeshAlpha);
		}
		for (int y = 0; y < GLUtils::getViewportHeight() / meshDiv; y++)
		{
			GLUtils::drawLine(nDScreenOnScreenX0, nDScreenOnScreenY0 + (y * meshDiv * screenScale * nDZoom), nDScreenOnScreenX1, nDScreenOnScreenY0 + (y * meshDiv * screenScale * nDZoom), 0.1f, 0.1f, 0.1f, drawMeshAlpha);
		}
	}


	bool drawScreenLight = true;

	if (GLUtils::useShaders)
	{
		if (drawScreenLight)
		{
			//--------------------------
			// set LIGHTS buffer in MAIN FBO
			//--------------------------
			//switch to LIGHTS buffer attachment
			GLUtils::drawIntoFBOAttachment(1); //draws into lightFBOTextureID
			glClear(GL_COLOR_BUFFER_BIT);

			//--------------------------
			//draw the main FBO texture into the LIGHTS buffer attachment (upside down because FBO is flipped)
			//--------------------------
			GLUtils::drawTexture(GLUtils::postColorFilterFBO_Texture_Attachment0, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, (float)GLUtils::getViewportWidth(), 0.0f, (float)GLUtils::getViewportHeight(), 1.0f, GLUtils::DEFAULT_ND_FBO_FILTER);

			//--------------------------
			//switch to MAIN buffer attachment in MAIN FBO
			//--------------------------
			GLUtils::drawIntoFBOAttachment(0); //draws into mainFBOTextureID


			//--------------------------
			// draw light into MAIN FBO mixing with LIGHT BUFFER TEXTURE (copy of MAIN FBO) to blend nicely
			//--------------------------
			GLUtils::useShader(GLUtils::lightShader);

			//set the LIGHTS FBO texture to texture 0, we drew the main FBO (maps and sprites) into it and we are going to use it to blend
			glActiveTexture(GL_TEXTURE0);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, GLUtils::postColorFilterFBO_Texture_Attachment1_PreLighting);


			glActiveTexture(GL_TEXTURE1); //switch to texture 1, we are going to bind the light textures to this when we draw them.
			glEnable(GL_TEXTURE_2D);


			GLUtils::setShaderVar1i(GLUtils::lightShader, (char*)"Tex0", 0);
			GLUtils::setShaderVar1i(GLUtils::lightShader, (char*)"Tex1", 1);
			GLUtils::setShaderVar1f(GLUtils::lightShader, (char*)"width", (float)GLUtils::getViewportWidth());
			GLUtils::setShaderVar1f(GLUtils::lightShader, (char*)"height", (float)GLUtils::getViewportHeight());


			float lightOffset = 48 * nDZoom;
			//draw screen light
			if (light != nullptr)
			{
				light->renderLight(nDScreenOnScreenX0 - lightOffset, nDScreenOnScreenX1 + lightOffset, nDScreenOnScreenY0 - lightOffset, nDScreenOnScreenY1 + lightOffset, lightAlpha);
			}


			//disable texture2D on texture unit 1
			glActiveTexture(GL_TEXTURE1);
			glDisable(GL_TEXTURE_2D);

			//switch back to texture unit 0
			glActiveTexture(GL_TEXTURE0);
			glDisable(GL_TEXTURE_2D);

			GLUtils::useShader(0);
		}
	}


	//--------------------------
	// switch back to SCREEN BUFFER (has game drawn in it)
	//--------------------------

	GLUtils::bindFBO(0); //set the framebuffer back to the screen buffer
	glEnable(GL_TEXTURE_2D);

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
	GLUtils::setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); //this fixes the small shadow problems, and also makes the doorknob glow brighter.
	GLUtils::drawTexture(GLUtils::postColorFilterFBO_Texture_Attachment0, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, (float)GLUtils::getViewportWidth(), 0.0f, (float)GLUtils::getViewportHeight(), 1.0f, GLUtils::DEFAULT_ND_FBO_FILTER);
	GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	if (GLUtils::useShaders)
	{
		GLUtils::useShader(0);
	}

	//--------------------------
	// draw shine overlay over screen
	//--------------------------


	//DONE: make shiny screen overlay that moves when scrolling up
	//draw shine over screen
	float endShineRemovedSize = 1.0f;
	float shineSize = ((widthThisFrame / targetWidth) * ((inScreenHeight) * endShineRemovedSize));

	float shineOffset = 2 * nDZoom; //2 (adjusted) pixels closer to bezel
	GLUtils::drawFilledRect(255, 255, 255, nDScreenOnScreenX0 - shineOffset, nDScreenOnScreenX1 + shineOffset, nDScreenOnScreenY0 - shineOffset, (nDScreenOnScreenY0 - shineOffset) + (inScreenHeight - shineSize), 0.3f);
}

void ND::layout()
{ //=========================================================================================================================

	//we are overriding MenuPanel but it isnt really a widget, we're just using the same convenience functions.
	//so do nothing here.
}

