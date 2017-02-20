
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger TextWindow::log = Logger("TextWindow");


//=========================================================================================================================
TextWindow::TextWindow(Engine* g)
{//=========================================================================================================================
	this->e = g;

	borderTexture = GLUtils::getTextureFromPNG("data/textbox/border.png");

	scrollPercent = 0;
}


//=========================================================================================================================
void TextWindow::init()
{//=========================================================================================================================

	if (spriteWindowEntity != nullptr)
	{
		delete spriteWindowEntity;
		spriteWindowEntity = nullptr;
	}

	if (textBoxTextureByteArray != nullptr)
	{
		delete[] textBoxTextureByteArray;
		textBoxTextureByteArray = nullptr;
	}

	textBoxTextureByteArray = new u8[getTextManager()->pow2TexWidth * getTextManager()->pow2TexHeight * 4];


	//		for(int i=0;i<getTextManager()->textureWidth*getTextManager()->textureHeight;i++)
	//		{
	//			textBoxTextureByteArray[(i*4)+0]=(byte)0;
	//			textBoxTextureByteArray[(i*4)+1]=(byte)0;
	//			textBoxTextureByteArray[(i*4)+2]=(byte)0;
	//			textBoxTextureByteArray[(i*4)+3]=(byte)0;
	//		}

	clearByteArray();


	textBoxTexture = GLUtils::getTextureFromData("textBox", getTextManager()->pow2TexWidth, getTextManager()->pow2TexHeight, textBoxTextureByteArray);


	// ----------------------------
	// sprite window
	// ----------------------------

	if (spriteWindowTextureByteArray != nullptr)
	{
		delete[] spriteWindowTextureByteArray;
		spriteWindowTextureByteArray = nullptr;
	}

	spriteWindowTextureByteArray = new u8[((64) * (64)) * 4];


	for (int i = 0; i < (64) * (64); i++)
	{
		spriteWindowTextureByteArray[(i * 4) + 0] = 0;
		spriteWindowTextureByteArray[(i * 4) + 1] = 0;
		spriteWindowTextureByteArray[(i * 4) + 2] = 0;
		spriteWindowTextureByteArray[(i * 4) + 3] = 255;
	}

	spriteBoxTexture = GLUtils::getTextureFromData("spriteWindow", 64, 64, spriteWindowTextureByteArray);

}

void TextWindow::render()
{ // =========================================================================================================================


	//render getText window at 25% screen height, let's make "scroll in" a float where 1.0 is height + 16px or whatever

	int screenWidth = (int)(getEngine()->getWidth());
	int screenHeight = (int)(getEngine()->getHeight());
	float scaledTextWindowHeight = screenHeight * 0.15f; //not including borders!

	float widthToHeightRatio = (float)(getTextManager()->width) / (float)(getTextManager()->height);
	float scaledTextWindowWidth = scaledTextWindowHeight * widthToHeightRatio;

	float heightScale = scaledTextWindowHeight / (float)(getTextManager()->height);

	float widthScale = scaledTextWindowWidth / (float)(getTextManager()->width);
	float scaledSpriteWindowWidth = getTextManager()->spriteWindowWidth * widthScale;

	float borderWidth = 10;
	float scaledBorderWidth = borderWidth * widthScale;

	float borderHeight = 16;
	float scaledBorderHeight = borderHeight * heightScale;

	float totalScaledWidth = scaledTextWindowWidth + scaledSpriteWindowWidth + scaledBorderWidth * 3;
	float totalScaledHeight = scaledTextWindowHeight + scaledBorderHeight * 2;

	if (totalScaledWidth > getEngine()->getWidth() * 0.90f)
	{
		//getScale width to 90%
		//getScale height from that
		scaledTextWindowWidth = (float)(getEngine()->getWidth() * 0.75f);
		widthScale = scaledTextWindowWidth / (float)(getTextManager()->width);
		scaledSpriteWindowWidth = getTextManager()->spriteWindowWidth * widthScale;

		//float heightToWidthRatio = (float)(getTextManager()->height) / (float)(getTextManager()->width);
		scaledTextWindowHeight = scaledTextWindowWidth / widthToHeightRatio;
		heightScale = scaledTextWindowHeight / (float)(getTextManager()->height);

		scaledBorderWidth = borderWidth * widthScale;
		scaledBorderHeight = borderHeight * heightScale;
		totalScaledWidth = scaledTextWindowWidth + scaledSpriteWindowWidth + scaledBorderWidth * 3;
		totalScaledHeight = scaledTextWindowHeight + scaledBorderHeight * 2;
	}


	float tx0 = 0.0f;
	float tx1 = 1.0f;
	float ty0 = 0.0f;
	float ty1 = 1.0f;

	float x0 = 0;
	float x1 = 0;
	float y0 = 0;
	float y1 = 0;


	float y = 0;
	//scroll from bottom
	float startScrollPosition = (float)getEngine()->getHeight();
	float finalScrollPosition = getEngine()->getHeight() - totalScaledHeight - 16;

	if (this == getTextManager()->textBox->get(1))
	{
		//scroll from top
		startScrollPosition = (float)0 - totalScaledHeight;
		finalScrollPosition = (float)0 + StatusBar::sizeY + 16;
	}
	y = (startScrollPosition + (finalScrollPosition - startScrollPosition) * scrollPercent) + shakeY;


	float x = ((screenWidth - totalScaledWidth) / 2) + shakeX;


	// -----------------------
	// border
	// ----------------------

	tx0 = 0.0f; // 672 x 160
	tx1 = 672.0f / borderTexture->getTextureWidth();
	ty0 = 0.0f;
	ty1 = 160.0f / borderTexture->getTextureHeight();


	//		x0=(int)((getScreenX)-(getTextManager()->spriteWindowWidth))-16;
	//		x1=(int)(getScreenX)+(getTextManager()->textWindowWidth)+16;
	//		y0=(int)(getScreenY-16);
	//		y1=(int)(getScreenY)+(getTextManager()->textWindowHeight)+16;


	x0 = x;
	x1 = x0 + totalScaledWidth;
	y0 = y;
	y1 = y0 + totalScaledHeight;


	GLUtils::drawTexture(borderTexture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, alpha, GLUtils::FILTER_NEAREST);

	// ------------------
	// getText box itself
	// ------------------

	tx0 = 0.0f;
	tx1 = (float)(textBoxTexture->getImageWidth()) / (float)(textBoxTexture->getTextureWidth());
	ty0 = 0.0f;
	ty1 = (float)(textBoxTexture->getImageHeight()) / (float)(textBoxTexture->getTextureHeight());

	//		x0=(int)(getScreenX);
	//		x1=(int)((getScreenX)+(getTextManager()->textWindowWidth));
	//		y0=(int)(getScreenY);
	//		y1=(int)((getScreenY)+(getTextManager()->textWindowHeight));

	x0 = x + scaledBorderWidth + scaledSpriteWindowWidth + scaledBorderWidth;
	x1 = x0 + scaledTextWindowWidth;
	y0 = y + scaledBorderHeight;
	y1 = y0 + scaledTextWindowHeight;

	GLUtils::drawTexture(textBoxTexture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, alpha, GLUtils::FILTER_LINEAR);

	// -----------------------
	// sprite window
	// ----------------------

	/*
	 * spriteBoxTexture.bind();
	 * tx0 = 0.0f;
	 * tx1 = 1.0f;
	 * ty0 = 0.0f;
	 * ty1 = 1.0f;
	 * x0 = (int)((screen_x)-(64*2));
	 * x1 = (int)(screen_x);
	 * y0 = (int)(screen_y);
	 * y1 = (int)((screen_y)+(G.textManager.size_y));
	 * draw_texture(tx0, tx1, ty0, ty1, x0, x1, y0, y1);
	 */

	// ----------------------
	// sprite window sprite
	// ----------------------

	tx0 = 0.0f;
	tx1 = 1.0f;
	ty0 = 0.0f;
	ty1 = 1.0f;

	//		x0=(int)((getScreenX)-((64*2)));
	//		x1=(int)(getScreenX);
	//		y0=(int)(getScreenY);
	//		y1=(int)((getScreenY)+(64*2));

	x0 = x + scaledBorderWidth;
	x1 = x0 + scaledSpriteWindowWidth;
	y0 = y + scaledBorderHeight;
	y1 = y0 + scaledTextWindowHeight;

	// if(sprite_window_gfx==null)sprite_window_gfx = TM.questionMarkTexture;

	GLUtils::drawTexture(spriteBoxTexture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, alpha, GLUtils::FILTER_NEAREST);


	// ----------------------
	// label underneath sprite window
	// ----------------------
	/*
	 * if(sprite_window_npc==null)
	 * {
	 * sprite_window_npc = G.cameraman;
	 * }
	 * else
	 * {
	 * label = sprite_window_npc.name;
	 * }
	 * if(sprite_window_npc==G.cameraman)
	 * {
	 * label = "???";
	 * }
	 */
	//getTextManager()->ttfFont.drawString(x0+48,y1+10-6,label,Color.white);//TODO


	if (this == getTextManager()->textBox->get(getTextManager()->selectedTextbox))
	{
		tx0 = 0.0f;
		tx1 = 1.0f;
		ty0 = 0.0f;
		ty1 = 1.0f;


		x0 = x + scaledBorderWidth + scaledSpriteWindowWidth + scaledBorderWidth + scaledTextWindowWidth;
		x1 = x0 + 16;
		y0 = y + scaledBorderHeight + scaledTextWindowHeight;
		//if(getTextManager()->buttonIconUpDownToggle)y0-=1;
		y1 = y0 + 16;

		getTextManager()->actionIconScreenSprite->setX(x0 - 36);
		getTextManager()->actionIconScreenSprite->setY(y0 - 20);

		//GLUtils.drawTexture(spriteBoxTexture,tx0,tx1,ty0,ty1,x0,x1,y0,y1,alpha,GLUtils.FILTER_NEAREST);
	}
}

void TextWindow::updateSpriteWindowTexture()
{ // =========================================================================================================================


	u8* oldtex = spriteWindowTexture->getTextureData();
	int size_x = spriteWindowTexture->getTextureWidth();
	int size_y = spriteWindowTexture->getTextureHeight();


	// go through sprite texture data, which should be 32 x 64 or 32 x 32
	// find top pixel by shooting rays down from top to bottom for 0-32
	int top_filled_pixel = size_y;
	for (int x = 0; x < 32; x++)
	{
		for (int y = 0; y < size_y; y++)
		{
			// skip checking y values lower than the previous known top pixel, dont need them
			if (y >= top_filled_pixel)
			{
				break;
			}

			if (oldtex[((size_x * y) + x) * 4 + 0] != static_cast<char>(0) || oldtex[((size_x * y) + x) * 4 + 1] != static_cast<char>(0) || oldtex[((size_x * y) + x) * 4 + 2] != static_cast<char>(0)) // b -  g -  r
			{
				if (y < top_filled_pixel)
				{
					top_filled_pixel = y;
				}
				break;
			}
		}
	}


	// make 64 * 64 pixel box
	u8* newtex = new u8[64 * 64 * 4];

	// fill with transparent
	for (int i = 0; i < 64 * 64 * 4; i++)
	{
		newtex[i] = static_cast<char>(0);
	}


	// take 32 x 32 pixels starting at line *above* top pixel (so there is one empty line), draw them float sized into 64 * 64 box
	// if (top pixel-1) + 32 is more than bottom, break and leave transparent.

	for (int y = top_filled_pixel; y < top_filled_pixel + 31 && y < size_y; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			char r = oldtex[((size_x * y) + x) * 4 + 0];
			char g = oldtex[((size_x * y) + x) * 4 + 1];
			char b = oldtex[((size_x * y) + x) * 4 + 2];
			char a = oldtex[((size_x * y) + x) * 4 + 3];


			for (int xx = 0; xx < 2; xx++)
			{
				for (int yy = 0; yy < 2; yy++)
				{
					int newy = (y + 1) - top_filled_pixel;

					newtex[(((64 * (((newy) * 2) + yy)) + ((x * 2) + xx)) * 4) + 0] = r;
					newtex[(((64 * (((newy) * 2) + yy)) + ((x * 2) + xx)) * 4) + 1] = g;
					newtex[(((64 * (((newy) * 2) + yy)) + ((x * 2) + xx)) * 4) + 2] = b;
					newtex[(((64 * (((newy) * 2) + yy)) + ((x * 2) + xx)) * 4) + 3] = a;
				}
			}
		}
	}


	// go through each pixel
	// if a pixel isn't transparent and isn't completely white (so it ignores already-outlined areas)
	// if the surrounding pixels are transparent, set it to white.
	for (int t = 127 - 32; t >= 0; t -= 16)
	{
		for (int x = 0; x < 64; x++)
		{
			for (int y = 0; y < 64; y++)
			{
				if (newtex[((64 * y) + x) * 4 + 3] != static_cast<char>(0) && (newtex[((64 * y) + x) * 4 + 0] != static_cast<char>(t) || newtex[((64 * y) + x) * 4 + 1] != static_cast<char>(t) || newtex[((64 * y) + x) * 4 + 2] != static_cast<char>(t))) // b -  g -  r
				{
					for (int i = 0; i < 8; i++)
					{
						int xx = 0;
						int yy = 0;

						if (i == 0)
						{
							xx = -1;
							yy = 0;
						}
						if (i == 1)
						{
							xx = 1;
							yy = 0;
						}
						if (i == 2)
						{
							xx = 0;
							yy = -1;
						}
						if (i == 3)
						{
							xx = 0;
							yy = 1;
						}

						if (i == 4)
						{
							xx = -1;
							yy = 1;
						}
						if (i == 5)
						{
							xx = 1;
							yy = -1;
						}
						if (i == 6)
						{
							xx = -1;
							yy = -1;
						}
						if (i == 7)
						{
							xx = 1;
							yy = 1;
						}

						if (y + yy >= 0 && y + yy < 64 && x + xx >= 0 && x + xx < 64)
						{
							if (newtex[((64 * (y + yy)) + (x + xx)) * 4 + 3] == static_cast<char>(0))
							{
								newtex[((64 * (y + yy)) + (x + xx)) * 4 + 0] = static_cast<char>(t);
								newtex[((64 * (y + yy)) + (x + xx)) * 4 + 1] = static_cast<char>(t);
								newtex[((64 * (y + yy)) + (x + xx)) * 4 + 2] = static_cast<char>(t);
								newtex[((64 * (y + yy)) + (x + xx)) * 4 + 3] = static_cast<char>(t);
							}
						}
					}
				}
			}
		}
	}

	// make texture from new 64*64 array

	delete [] spriteWindowTextureByteArray;
	spriteWindowTextureByteArray = newtex;

	spriteBoxTexture->release();
	spriteBoxTexture = GLUtils::getTextureFromData("spriteWindow", 64, 64, spriteWindowTextureByteArray);

	/*
	 * int textureHandle = spriteBoxTexture.getTextureID();
	 * glBindTexture(GL_TEXTURE_2D,textureHandle);
	 * glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	 * glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	 * glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL11.GL_NEAREST);
	 * glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL11.GL_NEAREST);
	 * glTexImage2D(GL_TEXTURE_2D, //type of texture we're creating
	 * 0, //level-of-detail: use 0
	 * GL_RGBA, //texture pixel format
	 * 64, 64, //width and height of texture image (powers of 2)
	 * 0, //width of the border (either 0 or 1, use 0)
	 * GL_RGBA, //image pixel format
	 * GL_UNSIGNED_BYTE, //image pixel data type
	 * spriteWindowTexturePixelsByteBuffer//image pixel data
	 * );
	 */
}

void TextWindow::setSpriteWindow(Entity* entity, BobTexture* texture, const string& newLabel)
{ // =========================================================================================================================

	if (entity != nullptr || texture != nullptr)
	{
		// if no texture is input, just take it from the entity
		if (entity != nullptr && texture == nullptr)
		{
			voicePitch = entity->getVoicePitch();

			if ((dynamic_cast<Player*>(entity) != NULL))
			{
				texture = (static_cast<Player*>(entity))->uniqueTexture;
			}

			if ((dynamic_cast<RandomCharacter*>(entity) != NULL))
			{
				texture = (static_cast<RandomCharacter*>(entity))->uniqueTexture;
			}


			if (texture == nullptr && entity->sprite != nullptr)
			{
				texture = entity->sprite->texture;
			}

			if (texture == nullptr || texture == GLUtils::blankTexture)
			{
				texture = TextManager::questionMarkTexture;
			}


			if (newLabel == "")
			{
				if (entity != nullptr)
				{
					if (entity->sprite != nullptr)
					{
						label = entity->sprite->getDisplayName();
					}
				}
			}
			else
			{
				label = newLabel;
			}
		}

		// if there isn't an entity, stay on camera. this way just putting in a gfx works, but the camera won't try to move
		if (entity == nullptr)
		{
			entity = getCameraman();
			voicePitch = 0;

			if (newLabel != "")
			{
				label = newLabel;
			}
			else
			{
				label = "???";
			}
		}

		// else, follow npc and use gfx for sprite window :)
		spriteWindowEntity = entity; // TODO: each npc should have a voice pitch!!!
		spriteWindowTexture = texture;


		// if(TM.GLOBAL_text_engine_state!=TM.CLOSED)
		// {
		updateSpriteWindowTexture();

		// }
	}
	else
	{
		string e = "Tried to update sprite window with both npc and gfx null.";
		Console::error(e);
		log.error(e);
	}
}

void TextWindow::updateTextureFromByteArray()
{ // =========================================================================================================================

	if (redraw == true)
	{
		// TODO: it might actually be more efficient to overwrite the previous texture, the way i had it before, instead of releasing and recreating.

		textBoxTexture->release();

		textBoxTexture = GLUtils::getTextureFromData("textBox", getTextManager()->pow2TexWidth, getTextManager()->pow2TexHeight, textBoxTextureByteArray);

		redraw = false;
	}
}

void TextWindow::clearByteArray()
{ // =========================================================================================================================
	for (int x = 0; x < getTextManager()->pow2TexWidth; x++)
	{
		for (int y = 0; y < getTextManager()->pow2TexHeight; y++)
		{
			textBoxTextureByteArray[((x + (y * getTextManager()->pow2TexWidth)) * 4) + 0] = 0;
			textBoxTextureByteArray[((x + (y * getTextManager()->pow2TexWidth)) * 4) + 1] = 0;
			textBoxTextureByteArray[((x + (y * getTextManager()->pow2TexWidth)) * 4) + 2] = 0;
			textBoxTextureByteArray[((x + (y * getTextManager()->pow2TexWidth)) * 4) + 3] = 0;

			if (x < getTextManager()->width && y < getTextManager()->height)
			{
				textBoxTextureByteArray[((x + (y * getTextManager()->pow2TexWidth)) * 4) + 3] = 255;
			}
		}
	}
}

int TextWindow::getPixelValue(int letter_index, int y, int x_in_letter, bool blank)
{ // =========================================================================================================================


	if (blank == true)
	{
		return 0;
	}

	int index = BobFont::getFontPixelValueAtIndex((letter_index * getTextManager()->font->blockHeight * getTextManager()->font->blockWidth) + (y * getTextManager()->font->blockWidth) + x_in_letter, getTextManager()->font);

	return index;
}

void TextWindow::setPixel(int index, BobColor* c)
{ // =========================================================================================================================


	textBoxTextureByteArray[index + 0] = static_cast<char>(c->ri());
	textBoxTextureByteArray[index + 1] = static_cast<char>(c->gi());
	textBoxTextureByteArray[index + 2] = static_cast<char>(c->bi());
	textBoxTextureByteArray[index + 3] = static_cast<char>(c->ai()); // was 255
}

u8* BobFont::font_Palette_ByteArray;

void TextWindow::drawColumn(int letter_index, int x_in_letter, bool blank)
{ // =========================================================================================================================


	int y = 0;
	int h = getTextManager()->font->maxCharHeight;

	bool draw2X = true;

	if (h > 12)
	{
		draw2X = false;
	}


	int lineHeight = 12;
	if (draw2X == false)
	{
		lineHeight = 24; // because the font is float, we don't need to draw at 2x
	}


	for (y = 0; y < lineHeight && y < h; y++)
	{
		int index = getPixelValue(letter_index, y, x_in_letter, blank);


		if (index != 0)
		{
			BobColor* pixelColor = getTextManager()->textColor;
			if (index == 0)
			{
				pixelColor = getTextManager()->textBGColor;
			}
			if (index == 1)
			{
				pixelColor = getTextManager()->textColor;
			}
			if (index == 2)
			{
				pixelColor = getTextManager()->textAAColor;
			}
			if (index == 3)
			{
				pixelColor = getTextManager()->textShadowColor;
			}


			if (index > 2)
			{
				// get the gray color from the getText palette
				int byte1 = (int)(BobFont::font_Palette_ByteArray[index * 2 + 0] & 255);
				//int byte2 = (int)(BobFont::font_Palette_ByteArray[index * 2 + 1] & 255);
				//int abgr1555 = (byte2 << 8) + byte1;
				int r = 255 - (int)((((byte1 & 31)) / 32.0f) * 255.0f);


				// int r = 255-(int)((((byte1&0b00011111))/32.0f)*255.0f);
				// Color gray = new Color(b,b,b);


				// now r is the gray value (since r=g=b)

				int a = r; // gray.getRed();
				if (a < 0)
				{
					a = 0;
				}
				pixelColor = new BobColor(pixelColor->ri(), pixelColor->gi(), pixelColor->bi(), a);
			}


			if (index == 1 && y < h * 0.75f)
			{
				int r = (int)(min(255,(int)(pixelColor->ri() + (((float)(h - y) / (float)(h))*255.0f))));
				int g = (int)(min(255,(int)(pixelColor->gi() + (((float)(h - y) / (float)(h))*255.0f))));
				int b = (int)(min(255,(int)(pixelColor->bi() + (((float)(h - y) / (float)(h))*255.0f))));


				pixelColor = new BobColor(r, g, b);
			}


			if (draw2X)
			{
				// draw each pixel 4 times (2x getScale)
				for (int yy = 0; yy < 2; yy++)
				{
					for (int xx = 0; xx < 2; xx++)
					{
						setPixel((getTextManager()->pow2TexWidth * 4 * line * lineHeight * 2) + (((getTextManager()->pow2TexWidth * ((y * 2) + yy)) + ((xInLine * 2) + xx)) * 4), pixelColor);
					}
				}
			}
			else
			{
				setPixel((getTextManager()->pow2TexWidth * 4 * line * lineHeight) + (((getTextManager()->pow2TexWidth * ((y))) + ((xInLine))) * 4), pixelColor);
			}
		}


		// do shadow

		// if this value is 1 and the value of x_in_letter+1 is 0, set x_in_letter+1 to 3
		if (index == 1)
		{
			BobColor* shadowColor = getTextManager()->textShadowColor;

			if (draw2X)
			{
				if (getPixelValue(letter_index, y, x_in_letter + 1, blank) == 0)
				{
					for (int yy = 0; yy < 2; yy++)
					{
						for (int xx = 0; xx < 2; xx++)
						{
							setPixel((getTextManager()->pow2TexWidth * 4 * line * lineHeight) + (((getTextManager()->pow2TexWidth * ((y) + yy)) + (((xInLine + 1)) + xx)) * 4), shadowColor);
						}
					}
				}


				if (getPixelValue(letter_index, y + 1, x_in_letter, blank) == 0)
				{
					for (int yy = 0; yy < 2; yy++)
					{
						for (int xx = 0; xx < 2; xx++)
						{
							setPixel((getTextManager()->pow2TexWidth * 4 * line * lineHeight) + (((getTextManager()->pow2TexWidth * (((y + 1)) + yy)) + (((xInLine)) + xx)) * 4), shadowColor);
						}
					}
				}


				if (getPixelValue(letter_index, y + 1, x_in_letter + 1, blank) == 0)
				{
					for (int yy = 0; yy < 2; yy++)
					{
						for (int xx = 0; xx < 2; xx++)
						{
							setPixel((getTextManager()->pow2TexWidth * 4 * line * lineHeight) + (((getTextManager()->pow2TexWidth * (((y + 1)) + yy)) + (((xInLine + 1)) + xx)) * 4), shadowColor);
						}
					}
				}
			}
			else
			{
				if (getPixelValue(letter_index, y, x_in_letter + 1, blank) == 0)
				{
					for (int yy = 0; yy < 2; yy++)
					{
						for (int xx = 0; xx < 2; xx++)
						{
							setPixel((getTextManager()->pow2TexWidth * 4 * line * lineHeight) + (((getTextManager()->pow2TexWidth * ((y) + yy)) + (((xInLine + 1)) + xx)) * 4), shadowColor);
						}
					}
				}


				if (getPixelValue(letter_index, y + 1, x_in_letter, blank) == 0)
				{
					for (int yy = 0; yy < 2; yy++)
					{
						for (int xx = 0; xx < 2; xx++)
						{
							setPixel((getTextManager()->pow2TexWidth * 4 * line * lineHeight) + (((getTextManager()->pow2TexWidth * (((y + 1)) + yy)) + (((xInLine)) + xx)) * 4), shadowColor);
						}
					}
				}


				if (getPixelValue(letter_index, y + 1, x_in_letter + 1, blank) == 0)
				{
					for (int yy = 0; yy < 2; yy++)
					{
						for (int xx = 0; xx < 2; xx++)
						{
							setPixel((getTextManager()->pow2TexWidth * 4 * line * lineHeight) + (((getTextManager()->pow2TexWidth * (((y + 1)) + yy)) + (((xInLine + 1)) + xx)) * 4), shadowColor);
						}
					}
				}


				// if(TEXT_get_letter_pixel_color(letter_index,y,x_in_letter+1,blank)==0)TEXT_set_pixel((textMan().size_x*4*line*lineHeight)+(((textMan().size_x*((y)))+(((x_in_line+1))))*4),c2);
				// if(TEXT_get_letter_pixel_color(letter_index,y+1,x_in_letter,blank)==0)TEXT_set_pixel((textMan().size_x*4*line*lineHeight)+(((textMan().size_x*(((y+1))))+(((x_in_line))))*4),c2);
				// if(TEXT_get_letter_pixel_color(letter_index,y+1,x_in_letter+1,blank)==0)TEXT_set_pixel((textMan().size_x*4*line*lineHeight)+(((textMan().size_x*(((y+1))))+(((x_in_line+1))))*4),c2);
			}
		}
	}
}

