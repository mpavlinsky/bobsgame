
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger GlowTileBackground::log = Logger("GlowTileBackground");


GlowTileBackground::GlowTile::GlowTile(GlowTileBackground* outerInstance) : outerInstance(outerInstance)
{
}

GlowTileBackground::GlowTileBackground()
{ //=========================================================================================================================
}

GlowTileBackground::GlowTileBackground(Engine* g)
{ //=========================================================================================================================

	this->e = g;
	init();
}

void GlowTileBackground::init()
{ //=========================================================================================================================

	numActiveTiles = 4;
	scale = 2.0f;
	ticksPerFrame = 30;
	scrollSpeedTicksMultiplier = (1.0f / 50.0f);

	tileFrames = 115;


	cleanup();

	bgScrollTexture = GLUtils::getTextureFromPNG("data/guiBackground/glowTileFramesBG.png");

	//glowTileFramesTexture = new ArrayList<Texture*>();
	for (int i = 0; i < tileFrames; i++)
	{
		glowTileFramesTexture->add(GLUtils::getTextureFromPNG("data/guiBackground/glowTileFrames/" + to_string(i) + ".png"));
	}

	glowTiles->clear();

	for (int i = 0; i < numActiveTiles; i++)
	{
		glowTiles->add(new GlowTile(this));
	}

	glowTiles->get(0)->started = true;
}

void GlowTileBackground::cleanup()
{ //=========================================================================================================================
	if (glowTileFramesTexture->size() > 0 && glowTileFramesTexture->size() > 0)
	{
		for (int i = 0; i < glowTileFramesTexture->size(); i++)
		{
			if (glowTileFramesTexture->get(i) != nullptr)
			{
				glowTileFramesTexture->get(i)->release();				
			}
		}
		glowTileFramesTexture->clear();
	}

	if (bgScrollTexture != nullptr)
	{
		bgScrollTexture->release();
		bgScrollTexture = nullptr;
	}
}

void GlowTileBackground::update()
{ //=========================================================================================================================


	if (glowTileFramesTexture->isEmpty())
	{
		init();
	}

	if (e != nullptr)
	{
		ticksPassed = e->engineTicksPassed();
	}
	else
	{
		ticksPassed = Engine::realWorldTicksPassed();
	}

	float tileWidth = glowTileFramesTexture->get(0)->getImageWidth() * scale;
	float tileHeight = glowTileFramesTexture->get(0)->getImageHeight() * scale;


	int screenWidth = GLUtils::getViewportWidth();
	int screenHeight = GLUtils::getViewportHeight();

	if (e != nullptr)
	{
		screenWidth = (int)(e->getWidth());
		screenHeight = (int)(e->getHeight());
	}

	//------------------------------------------
	//set the bg glow frames
	//------------------------------------------
	for (int i = 0; i < glowTiles->size(); i++)
	{
		GlowTile* tile = glowTiles->get(i);

		tile->ticks += ticksPassed;
		if (tile->ticks > ticksPerFrame)
		{
			tile->ticks = 0;

			//get the next glowtile
			int next = i + 1;
			if (next >= glowTiles->size())
			{
				next = 0;
			}

			GlowTile* nextTile = glowTiles->get(next);

			if (tile->started == false)
			{
				//if next is at frame length, set to started.
				if (nextTile->frame >= (tileFrames) / glowTiles->size())
				{
					tile->started = true;
				}
			}


			if (tile->started == true)
			{
				tile->frame++;
				if (tile->frame >= tileFrames)
				{
					tile->frame = 0;

					//follow the previous tile for snake-like movement.
					if (Math::randLessThan(2) == 0)
					{
						tile->tileX = nextTile->tileX;
						tile->tileY = nextTile->tileY + 1;
					} //down
					else
					{
						tile->tileX = nextTile->tileX + 1;
						tile->tileY = nextTile->tileY;
					} //right


					//wrap around
					if (tile->tileX > screenWidth / tileWidth)
					{
						tile->tileX = 0;
					}
					if (tile->tileX < 0)
					{
						tile->tileX = (int)(screenWidth / tileWidth);
					}

					if (tile->tileY > screenHeight / tileHeight)
					{
						tile->tileY = 0;
					}
					if (tile->tileY < 0)
					{
						tile->tileY = (int)(screenHeight / tileHeight);
					}

					//pick a random tile
					//bg_glow_offset[f][0]=((rand()%13)*32);
					//bg_glow_offset[f][1]=((rand()%11)*32);

					//bg_glow_ticks[f]+=(500+rand()%2000);
				}
			}
		}
	}
	//------------------------------------------

	//------------------------------------------
	//set the bg scrolling
	//------------------------------------------


	bgScrollX -= ticksPassed * scrollSpeedTicksMultiplier;
	bgScrollY -= ticksPassed * scrollSpeedTicksMultiplier;


	if (bgScrollX <= -tileWidth)
	{
		bgScrollX = 0;


		//move the glow offsets when the bg loops
		for (int i = 0; i < glowTiles->size(); i++)
		{
			GlowTile* tile = glowTiles->get(i);
			tile->tileX -= 1;
			if (tile->tileX < 0)
			{
				tile->tileX += (int)(screenWidth / tileWidth);
			}
		}
	}

	if (bgScrollY <= -tileHeight)
	{
		bgScrollY = 0;

		//move the glow offsets when the bg loops
		for (int i = 0; i < glowTiles->size(); i++)
		{
			GlowTile* tile = glowTiles->get(i);
			tile->tileY -= 1;
			if (tile->tileY < 0)
			{
				tile->tileY += (int)(screenHeight / tileHeight);
			}
		}
	}


	//TODO: tiles near bottom of screen are clipped wrong
	//TODO: animation is too fast
	//TODO: fix weird delay on start
}

void GlowTileBackground::render()
{ //=========================================================================================================================

	//------------------------------------------
	//draw background png
	//------------------------------------------

	{
		//starting at bgScrollXY, draw bgScrollTexture until overlaps screen size x and y
		BobTexture* texture = bgScrollTexture;

		int w = texture->getImageWidth();
		int h = texture->getImageHeight();

		int screenWidth = GLUtils::getViewportWidth();
		int screenHeight = GLUtils::getViewportHeight();

		if (e != nullptr)
		{
			screenWidth = e->getWidth();
			screenHeight = e->getHeight();
		}

		//if the screen is bigger than the background scroll image we need to tile it
		int drawX = (int)(((screenWidth - (bgScrollX)) / (w * scale))) + 1;
		int drawY = (int)(((screenHeight - (bgScrollY)) / (h * scale))) + 1;

		for (int y = 0; y < drawY; y++)
		{
			for (int x = 0; x < drawX; x++)
			{
				float x0 = bgScrollX + (x * w * scale);
				float x1 = x0 + w * scale;
				float y0 = bgScrollY + (y * h * scale);
				float y1 = y0 + h * scale;


				GLUtils::drawTexture(texture, x0, x1, y0, y1, 1.0f, filter);
			}
		}
	}

	//------------------------------------------
	//draw background glow
	//------------------------------------------

	for (int i = glowTiles->size() - 1; i >= 0; i--) //from top to bottom
	{
		GlowTile* tile = glowTiles->get(i);


		BobTexture* texture = glowTileFramesTexture->get(tile->frame);
		int w = texture->getImageWidth();
		int h = texture->getImageHeight();

		float tXRatio = (float)(texture->getImageWidth()) / (float)(texture->getTextureWidth());
		float tYRatio = (float)(texture->getImageHeight()) / (float)(texture->getTextureHeight());

		float x0 = bgScrollX + tile->tileX * w * scale;
		float x1 = x0 + w * scale;
		float y0 = bgScrollY + tile->tileY * h * scale;
		float y1 = y0 + h * scale;

		float tx0 = 0.0f * tXRatio;
		float tx1 = 1.0f * tXRatio;
		float ty0 = 0.0f * tYRatio;
		float ty1 = 1.0f * tYRatio;

		GLUtils::drawTexture(texture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, 1.0f, filter);
	}
}

