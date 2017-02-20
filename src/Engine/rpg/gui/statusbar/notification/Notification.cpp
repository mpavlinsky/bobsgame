#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger Notification::log = Logger("Notification");


Notification::Notification(BGClientEngine* g, const string& s)
{ //=========================================================================================================================

	this->e = g;

	notificationString = s;


	/*
	 *
	 *
	 *
	 * notifications when entering area: "loading area" with progress bar.
	 *
	 * new game available in game store!
	 *
	 *
	 *
	 * your friend is online!
	 *
	 *
	 *
	 *
	*/

	if (caption == nullptr)
	{
		caption = new Caption(g, 0, 5, -1, notificationString, BobFont::font_normal_11_shadow1, BobColor::purple, BobColor::white, BobColor::clear, RenderOrder::OVER_GUI, 1.0f, GLUtils::getViewportWidth());
		caption->setAlphaImmediately(1.0f);
	}


	fadeIn = true;


	getStatusBar()->notificationManager->add(this);
}

void Notification::update()
{ //=========================================================================================================================


	if (caption == nullptr)
	{
		caption = new Caption(getEngine(), 0, 5, -1, notificationString, BobFont::font_normal_11_shadow1, BobColor::purple, BobColor::white, BobColor::clear, RenderOrder::OVER_GUI, 1.0f, GLUtils::getViewportWidth());
		caption->setAlphaImmediately(1.0f);
	}


	if (fadeIn == true)
	{
		if (alpha < 1.0f)
		{
			alpha += getEngine()->engineTicksPassed() * 0.001f;
		}
		if (alpha > 1.0f)
		{
			alpha = 1.0f;
		}
	}


	if (fadeOut == true)
	{
		fadeIn = false;

		if (alpha > 0.0f)
		{
			alpha -= getEngine()->engineTicksPassed() * 0.001f;
		}
		if (alpha < 0.0f)
		{
			alpha = 0.0f;
		}

		if (alpha == 0.0f)
		{
			getStatusBar()->notificationManager->remove(this);


			if (caption->texture != nullptr)
			{
				caption->texture->release();
				caption->texture = nullptr;
			}

			delete caption;
			caption = nullptr;

			return;
		}
	}


	float maxWidth = (GLUtils::getViewportWidth() - caption->screenX) - (GLUtils::getViewportWidth() - (getStatusBar()->moneyCaption->dividerX));

	if (scrolling == false && maxWidth < caption->texture->getImageWidth())
	{
		scrolling = true;
		scrollX = maxWidth;
		caption->screenX = (float)getStatusBar()->stuffButton->dividerX + 3; //we want to scroll right up to the divider
	}
	//else scrolling=false;

	if (scrolling == true)
	{
		scrollX -= getEngine()->engineTicksPassed() * 0.08f;
		if (scrollX < 0 - caption->texture->getImageWidth())
		{
			scrollX = maxWidth;
		}
	}
	else
	{
		caption->screenX = (float)getStatusBar()->stuffButton->dividerX + 3 + 10; //we want to stay 10 pixels away from the divider
	}


	if (hasProgressBar == true)
	{
		//progress+=Game().ticksPassed()*0.0f001;
		if (progress < 0.0f)
		{
			progress = 0.0f;
		}
		if (progress > 1.0f)
		{
			progress = 1.0f;
		}


		progressTicks += (int)getEngine()->engineTicksPassed();

		if (lastProgressTicks + 5 < progressTicks && progress < 1.0f)
		{
			lastProgressTicks = progressTicks;
			//progressBarFrame++;
			//if(progressBarFrame>15)progressBarFrame=0;
		}
	}
}

void Notification::render(int layer)
{ //=========================================================================================================================

	if (layer == 0)
	{
		float screenX = (float)getStatusBar()->stuffButton->dividerX + 3;
		float maxWidth = (GLUtils::getViewportWidth() - screenX) - (GLUtils::getViewportWidth() - (getStatusBar()->moneyCaption->dividerX));


		if (hasProgressBar == true)
		{
			//render progress bar


			/*
			Texture bg = NotificationManager.loadingBarBackgroundTexture;
			float bgw = bg.getImageWidth();
			float bgh = bg.getImageHeight();
			float bgtx1 = bgw/(float)bg.getTextureWidth();
			float bgty1 = bgh/(float)bg.getTextureHeight();
			GL.drawTexture(bg,0,bgtx1,0,bgty1,getScreenX,getScreenX+maxWidth,0,25,1.0f,1);*/


			BobTexture* fg = NotificationManager::loadingBarTexture;
			int fgImageWidth = fg->getImageWidth();
			int fgTextureWidth = fg->getTextureWidth();
			int fgImageHeight = fg->getImageHeight();
			int fgTextureHeight = fg->getTextureHeight();
			int fgFrameHeight = fgImageHeight; ///16.0f;

			float fgtx0 = 0;
			float fgtx1 = (progress * fgImageWidth) / fgTextureWidth;

			float fgty0 = (float)(progressBarFrame * fgFrameHeight) / fgTextureHeight;
			float fgty1 = (float)((progressBarFrame + 1) * fgFrameHeight) / fgTextureHeight;

			float fgx1 = progress * maxWidth;

			GLUtils::drawTexture(fg, fgtx0, fgtx1, fgty0, fgty1, screenX, screenX + fgx1, 0, 25, alpha * 0.75f, 1);
		}


		if (caption != nullptr)
		{
			float tx0 = 0.0f;
			float tx1 = (float)(caption->texture->getImageWidth()) / (float)(caption->texture->getTextureWidth());
			float ty0 = 0.0f;
			float ty1 = (float)(caption->texture->getImageHeight()) / (float)(caption->texture->getTextureHeight());

			float x0 = (caption->screenX);
			float x1 = (caption->screenX + caption->texture->getImageWidth());
			float y0 = (caption->screenY);
			float y1 = (caption->screenY + caption->texture->getImageHeight());


			//notifications scrolling back and forth


			if (scrolling == true)
			{
				//figure out where x0 should be based on scrollX

				if (scrollX < 0)
				{
					//x0 is 0, set x texture clip

					x0 = caption->screenX;
					tx0 = (0 - scrollX) / (float)(caption->texture->getTextureWidth());

					//if the rest will fit
					if (scrollX + caption->texture->getImageWidth() < maxWidth)
					{
						tx1 = (float)(caption->texture->getImageWidth()) / (float)(caption->texture->getTextureWidth());
						x1 = caption->screenX + scrollX + caption->texture->getImageWidth();
					}
					else
					{
						//clip x1 and tx1

						tx1 = ((0 - scrollX) + maxWidth) / (float)(caption->texture->getTextureWidth());
						x1 = caption->screenX + maxWidth;
					}
				}
				else
				{
					x0 = caption->screenX + scrollX;
					tx0 = 0.0f;

					//if it is scrolling off the end
					if (scrollX + caption->texture->getImageWidth() > maxWidth)
					{
						//clip it
						x1 = x0 + (maxWidth - scrollX);
						tx1 = (maxWidth - scrollX) / (float)(caption->texture->getTextureWidth());
					}
					else
					{
						//draw the whole thing
						x1 = x0 + caption->texture->getImageWidth();
						tx1 = (float)(caption->texture->getImageWidth()) / (float)(caption->texture->getTextureWidth());
					}
				}
			}
			else
			{
				x0 = (caption->screenX);
				x1 = (caption->screenX + caption->texture->getImageWidth());
				y0 = (caption->screenY);
				y1 = (caption->screenY + caption->texture->getImageHeight());
			}


			GLUtils::drawTexture(caption->texture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, alpha, GLUtils::FILTER_FBO_NEAREST_NO_MIPMAPPING);
		}
	}
}

Notification* Notification::fadeOutAndDelete()
{
	fadeOut = true;


	return nullptr;
}

