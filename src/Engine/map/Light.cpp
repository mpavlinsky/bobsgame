
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger Light::log = Logger("Light");


int Light::NOT_DRAWN = 0;
int Light::DRAWING = 1;
int Light::OVERLAPS_SOMETHING = 2;
int Light::DRAWN = 3;

Light::Light(Engine* g, const string& name, int mapXPixels1X, int mapYPixels1X, int widthPixels1X, int heightPixels1X, int red, int green, int blue, int alpha, int radiusPixels1X, float blendFalloff, float decayExponent, int focusRadius1X, bool isDayLight, bool isNightLight)
{ //=========================================================================================================================


	this->e = g;
	LightData* data = new LightData(-1, "", "", name, mapXPixels1X, mapYPixels1X, widthPixels1X, heightPixels1X, red, green, blue, alpha, radiusPixels1X, blendFalloff, decayExponent, focusRadius1X, isDayLight, isNightLight, false, false, false, -1, -1, 0, 0, false, false);
	initEntity(data);
	initLight(data);


	isScreenLight = true;


	if (getLightTexturePNGFileExists_S() == false)
	{
		BobFile* textureFile = new BobFile(FileUtils::appDataPath + string("l") + "/" + getFileName());
		if (textureFile->exists())
		{
			setLightTexturePNGFileExists_S(true);
		}
		else
		{
			createLightTexturePNG(FileUtils::appDataPath + string("l") + "/" + getFileName());

			setLightTexturePNGFileExists_S(true);
		}
	}

	if (getLightTexturePNGFileExists_S() == true)
	{
		BobFile* textureFile = nullptr;

		textureFile = new BobFile(FileUtils::appDataPath + string("l") + "/" + getFileName());


		if (textureFile->exists() == false)
		{
			//(exception())->printStackTrace();
		}


		BobTexture* t = nullptr;

		if (getMapManager()->lightTextureHashMap.containsKey(getFileName()))
		{
			t = getMapManager()->lightTextureHashMap.get(getFileName());

		}

		if (t == nullptr)
		{
			//t = GLUtils::getTextureFromPNG(FileUtils::cacheDir + string("l") + "/" + getFileName());

			//				if(t==null || t==GLUtils.boxTexture)
			//				{
			//
			//					log.error("Light graphic could not be created. Retrying...");
			//
			//					createLightTexturePNG(FileUtils.cacheDir+"l"+FileUtils.slash+getFileName());
			//
			//					try
			//					{
			//						Thread.sleep(500);
			//					}
			//					catch(InterruptedException e)
			//					{
			//						e.printStackTrace();
			//					}
			//
			//					t = GLUtils.loadTexture(FileUtils.cacheDir+"l"+FileUtils.slash+getFileName());
			//
			//				}

			getMapManager()->lightTextureHashMap.put(getFileName(), t);
		}


		texture = t;
	}
}

Light::Light(Engine* g, LightData* lightAsset)
{ //=========================================================================================================================
	this->e = g;

	initEntity(lightAsset);
	initLight(lightAsset);
}

void Light::initLight(LightData* lightAsset)
{
	this->data = lightAsset;


	if (lightAsset->getFlickerRandomUpToOnTicks())
	{
		onTicks = 16 + Math::randUpToIncluding(lightAsset->getFlickerOnTicks()) + Math::randUpToIncluding(500);
	}
	else
	{
		onTicks = 16 + lightAsset->getFlickerOnTicks() + Math::randUpToIncluding(500);
	}
	if (lightAsset->getFlickerRandomUpToOffTicks())
	{
		offTicks = 16 + Math::randUpToIncluding(lightAsset->getFlickerOffTicks()) + Math::randUpToIncluding(500);
	}
	else
	{
		offTicks = 16 + lightAsset->getFlickerOffTicks() + Math::randUpToIncluding(500);
	}


	movementDirection = (Math::randLessThan(8));
}

void Light::update()
{ //===============================================================================================

	setTicksPerPixelMoved(1);

	updateTimers();


	if (getName().find("mover") != string::npos)
	{
		bounceAroundRoom();
	}


	if (flickers())
	{
		ticksCounter += getEngine()->engineTicksPassed();

		if (flickerOnOffToggle == true)
		{
			if (ticksCounter >= onTicks)
			{
				ticksCounter = 0;
				flickerOnOffToggle = false;

				if (flickerRandomUpToOnTicks())
				{
					onTicks = 16 + Math::randUpToIncluding(flickerOnTicks());
				}
				else
				{
					onTicks = 16 + flickerOnTicks() + 60 + Math::randUpToIncluding(50);
				}
			}
		}
		else
		{
			if (flickerOnOffToggle == false)
			{
				if (ticksCounter >= offTicks)
				{
					ticksCounter = 0;
					flickerOnOffToggle = true;

					if (flickerRandomUpToOffTicks())
					{
						offTicks = 16 + Math::randUpToIncluding(flickerOffTicks());
					}
					else
					{
						offTicks = 16 + flickerOffTicks();
					}
				}
			}
		}
	}


	if (toggleable())
	{
		//if player is in toggle area and press action, set "toggleOnOffToggle" to false
		if (getPlayer()->getRight() >= toggleXPixelsHQ() && getPlayer()->getLeft() < toggleXPixelsHQ() + 16 && getPlayer()->getBottom() >= toggleYPixelsHQ() && getPlayer()->getTop() < toggleYPixelsHQ() + 16)
		{
			if (getControlsManager()->bgClient_ACTION_Pressed())
			{
				toggle();
			}
		}
	}

	if ((toggleOnOffToggle == false) || (flickers() == true && flickerOnOffToggle == false))
	{
		drawLightThisFrame = false;
	}
	else
	{
		drawLightThisFrame = true;
	}

	if (getMapManager()->isNightTime() && isNightLight() == false)
	{
		drawLightThisFrame = false;
	}

	if (getMapManager()->isDayTime() && isDayLight() == false)
	{
		drawLightThisFrame = false;
	}
}

void Light::toggle()
{ //===============================================================================================
	toggleOnOffToggle = !toggleOnOffToggle;
}

void Light::setOnOff(bool b)
{ //===============================================================================================
	toggleOnOffToggle = b;
}

void Light::setFlicker(bool b)
{ //===============================================================================================
	setFlickers(b);
}

//The following method was originally marked 'synchronized':
void Light::setLightTexturePNGFileExists_S(bool exists)
{ //===============================================================================================
	//set hashmap for this filename, boolean exists
	BobBool* temp = new BobBool();
	temp->value = exists;
	getMapManager()->lightTextureFileExistsHashtable.put(getFileName(), temp);
}

//The following method was originally marked 'synchronized':
bool Light::getLightTexturePNGFileExists_S()
{ //===============================================================================================
	//first check the hashmap for the filename. if it exists, do nothing.
	bool existsInHashtable = false;

	//this is an array because Hashtables only accept objects

	if (getMapManager()->lightTextureFileExistsHashtable.containsKey(getFileName()))
	{
		BobBool* fileExistsArray = getMapManager()->lightTextureFileExistsHashtable.get(getFileName());
		if (fileExistsArray != nullptr)
		{
			existsInHashtable = fileExistsArray->value;
		}
	}

	return existsInHashtable;

}

string Light::getFileName()
{ //===============================================================================================

	return string("") + to_string(getWidth() / 2) + string("_") + to_string(getHeight() / 2) + string("_") + to_string(getRadiusPixelsHQ() / 2) + string("_") + to_string(focusRadiusPixelsHQ() / 2) + string("_") + to_string(decayExponent()) + string("_") + to_string(blendFalloff()) + string("_") + to_string(r()) + string("_") + to_string(g()) + string("_") + to_string(b()) + string("_") + to_string(a());
}

bool Light::checkEdgeAgainstHitLayerAndOtherLightsInDirection(int dir)
{ //=========================================================================================================================


	float myRight = getMiddleX() + getRadiusPixelsHQ() / 2;
	float myLeft = getMiddleX() - getRadiusPixelsHQ() / 2;

	float myTop = getMiddleY() - getRadiusPixelsHQ() / 2;
	float myBottom = getMiddleY() + getRadiusPixelsHQ() / 2;


	for (int i = 0; i < (int)getMap()->currentState->lightList.size(); i++)
	{
		Light* l = getMap()->currentState->lightList.get(i);
		if (l != this && l->getName() == getName() == false && l->getName().find("mover") != string::npos)
		{
			int r = 8 + Math::randLessThan(16);


			float theirRight = l->getMiddleX() + l->getRadiusPixelsHQ() / 2;
			float theirLeft = l->getMiddleX() - l->getRadiusPixelsHQ() / 2;
			float theirTop = l->getMiddleY() - l->getRadiusPixelsHQ() / 2;
			float theirBottom = l->getMiddleY() + l->getRadiusPixelsHQ() / 2;


			if (dir == UP)
			{
				if (getMiddleX() < theirRight && getMiddleX() > theirLeft && myBottom > theirTop && myTop - r <= theirBottom)
				{
					return true;
				}
			}
			else
			{
				if (dir == DOWN)
				{
					if (getMiddleX() < theirRight && getMiddleX() > theirLeft && myTop < theirBottom && myBottom + r >= theirTop)
					{
						return true;
					}
				}
				else
				{
					if (dir == LEFT)
					{
						if (myRight > theirLeft && myLeft - r <= theirRight && getMiddleY() < theirBottom && getMiddleY() > theirTop)
						{
							return true;
						}
					}
					else
					{
						if (dir == RIGHT)
						{
							if (myLeft < theirRight && myRight + r >= theirLeft && getMiddleY() < theirBottom && getMiddleY() > theirTop)
							{
								return true;
							}
						}
					}
				}
			}
		}
	}


	if (dir == UP)
	{
		if (getMap()->getHitLayerValueAtXYPixels(getMiddleX(), myTop - 1) == true)
		{
			return true;
		}
		//if(getMap()->getHitLayerValueAtXYPixels(getLeft(),getTop()-1)==true)return true;
		//if(getMap()->getHitLayerValueAtXYPixels(getRight(),getTop()-1)==true)return true;
	}
	else
	{
		if (dir == DOWN)
		{
			if (getMap()->getHitLayerValueAtXYPixels(getMiddleX(), myBottom + 1) == true)
			{
				return true;
			}
			//if(getMap()->getHitLayerValueAtXYPixels(getLeft(),getBottom()+1)==true)return true;
			//if(getMap()->getHitLayerValueAtXYPixels(getRight(),getBottom()+1)==true)return true;
		}
		else
		{
			if (dir == LEFT)
			{
				if (getMap()->getHitLayerValueAtXYPixels(myLeft - 1, getMiddleY()) == true)
				{
					return true;
				}
				//if(getMap()->getHitLayerValueAtXYPixels(getLeft()-1,getTop())==true)return true;
				//if(getMap()->getHitLayerValueAtXYPixels(getLeft()-1,getBottom())==true)return true;
			}
			else
			{
				if (dir == RIGHT)
				{
					if (getMap()->getHitLayerValueAtXYPixels(myRight + 1, getMiddleY()) == true)
					{
						return true;
					}
					//if(getMap()->getHitLayerValueAtXYPixels(getRight()+1,getTop())==true)return true;
					//if(getMap()->getHitLayerValueAtXYPixels(getRight()+1,getBottom())==true)return true;
				}
			}
		}
	}


	return false;
}

void Light::bounceAroundRoom()
{ //=========================================================================================================================


	while (pixelsToMoveThisFrame > 1)
	{
		if (ifCanMoveAPixelThisFrameSubtractAndReturnTrue() == true)
		{
			if (movementDirection == UPLEFT)
			{
				if (checkEdgeAgainstHitLayerAndOtherLightsInDirection(UP) == false)
				{
					movePixelInDirection(UP);
				}
				else
				{
					movementDirection = (Math::randLessThan(8));
				}

				if (checkEdgeAgainstHitLayerAndOtherLightsInDirection(LEFT) == false)
				{
					movePixelInDirection(LEFT);
				}
				else
				{
					movementDirection = (Math::randLessThan(8));
				}
			}
			else
			{
				if (movementDirection == UPRIGHT)
				{
					if (checkEdgeAgainstHitLayerAndOtherLightsInDirection(UP) == false)
					{
						movePixelInDirection(UP);
					}
					else
					{
						movementDirection = (Math::randLessThan(8));
					}

					if (checkEdgeAgainstHitLayerAndOtherLightsInDirection(RIGHT) == false)
					{
						movePixelInDirection(RIGHT);
					}
					else
					{
						movementDirection = (Math::randLessThan(8));
					}
				}
				else
				{
					if (movementDirection == DOWNLEFT)
					{
						if (checkEdgeAgainstHitLayerAndOtherLightsInDirection(DOWN) == false)
						{
							movePixelInDirection(DOWN);
						}
						else
						{
							movementDirection = (Math::randLessThan(8));
						}

						if (checkEdgeAgainstHitLayerAndOtherLightsInDirection(LEFT) == false)
						{
							movePixelInDirection(LEFT);
						}
						else
						{
							movementDirection = (Math::randLessThan(8));
						}
					}
					else
					{
						if (movementDirection == DOWNRIGHT)
						{
							if (checkEdgeAgainstHitLayerAndOtherLightsInDirection(DOWN) == false)
							{
								movePixelInDirection(DOWN);
							}
							else
							{
								movementDirection = (Math::randLessThan(8));
							}

							if (checkEdgeAgainstHitLayerAndOtherLightsInDirection(RIGHT) == false)
							{
								movePixelInDirection(RIGHT);
							}
							else
							{
								movementDirection = (Math::randLessThan(8));
							}
						}
						else
						{
							if (checkEdgeAgainstHitLayerAndOtherLightsInDirection(movementDirection) == false)
							{
								movePixelInDirection(movementDirection);
							}
							else
							{
								movementDirection = (Math::randLessThan(8));
							}
						}
					}
				}
			}
		}
	}
}

bool Light::isOnScreen()
{ //=========================================================================================================================


	//float zoom = getCameraman()->getZoom();

	float left = getScreenLeft();
	//float middleX = screenMiddleX();
	float right = screenRight();

	float top = getScreenTop();
	//float middleY = screenMiddleY();
	float bottom = screenBottom();


	if (left >= getEngine()->getWidth())
	{
		return false;
	}
	if (right < 0)
	{
		return false;
	}

	if (top >= getEngine()->getHeight())
	{
		return false;
	}
	if (bottom < 0)
	{
		return false;
	}

	return true;
}

void Light::renderDebugBoxes()
{ //=========================================================================================================================

	if (isScreenLight == true)
	{
		return;
	}

	float zoom = getCameraman()->getZoom();

	float screenX = getMap()->screenX() * zoom + getX() * zoom;
	float screenY = getMap()->screenY() * zoom + getY() * zoom;

	//inner width, height
	GLUtils::drawBox(screenX, screenX + getWidth() * zoom, screenY, screenY + getHeight() * zoom, 0, 0, 0);


	//radius
	GLUtils::drawBox(getScreenLeft(), screenRight(), getScreenTop(), screenBottom(), 150, 150, 0);

	if (toggleable())
	{
		//toggle point
		float ax = getMap()->getScreenX((float)toggleXPixelsHQ(), 16);
		float ay = getMap()->getScreenY((float)toggleYPixelsHQ(), 16);

		GLUtils::drawBox(ax, ax + (16 * zoom) - 1, ay, ay + (16 * zoom) - 1, 0, 0, 255);

		GLUtils::drawLine(screenMiddleX(), screenMiddleY(), ax + (8 * zoom), ay + (8 * zoom), 255, 255, 255);
	}
}

void Light::render(float alpha)
{ //=========================================================================================================================
	//don't render as entity
}

bool Light::renderLight()
{ //=========================================================================================================================

	return renderLight(getScreenLeft(), screenRight(), getScreenTop(), screenBottom(), 1.0f);
}

bool Light::renderLight(float screenX0, float screenX1, float screenY0, float screenY1, float alpha)
{ //=========================================================================================================================


	if (getEngine()->lightsLayerEnabled == false)
	{
		return false;
	}

	if (drawLightThisFrame == false)
	{
		return false;
	}

	if (texture == nullptr)
	{
		return false;
	}


	float left = screenX0;
	float right = screenX1;
	float middleX = screenX0 + ((screenX1 - screenX0) / 2);


	float top = screenY0;
	float bottom = screenY1;
	float middleY = screenY0 + ((screenY1 - screenY0) / 2);


	if (left >= getEngine()->getWidth())
	{
		return false;
	}
	if (right < 0)
	{
		return false;
	}

	if (top >= getEngine()->getHeight())
	{
		return false;
	}
	if (bottom < 0)
	{
		return false;
	}

	float totalWidth = (getWidth() / 2) / 2 + (getRadiusPixelsHQ() / 2);
	float totalHeight = (getHeight() / 2) / 2 + (getRadiusPixelsHQ() / 2);

	float tx0 = 0.0f;
	float tx1 = ((float)(totalWidth)) / ((float)(texture->getTextureWidth()));
	float ty0 = 0.0f;
	float ty1 = ((float)(totalHeight)) / ((float)(texture->getTextureHeight()));


	float x0;
	float x1;
	float y0;
	float y1;


	glBindTexture(GL_TEXTURE_2D, texture->getTextureID());

	//lower right quadrant (default)

	x0 = middleX;
	x1 = right;

	y0 = middleY;
	y1 = bottom;


	//GL.drawTexture(l.texture,l.red, l.green, l.blue, tx0, tx1, ty0, ty1, x0, x1, y0, y1, 1.0f, GLUtils.FILTER_LINEAR);
	GLUtils::drawTexture(tx0, tx1, ty0, ty1, x0, x1, y0, y1, alpha, GLUtils::FILTER_LINEAR);


	//lower left

	x0 = left;
	x1 = middleX;

	y0 = middleY;
	y1 = bottom;

	//GL.drawTexture(l.texture,l.red, l.green, l.blue, tx1, tx0, ty0, ty1, x0, x1, y0, y1, 1.0f, GLUtils.FILTER_LINEAR);
	GLUtils::drawTexture(tx1, tx0, ty0, ty1, x0, x1, y0, y1, alpha, GLUtils::FILTER_LINEAR);


	//upper left quadrant (default)

	x0 = left;
	x1 = middleX;

	y0 = top;
	y1 = middleY;

	//GL.drawTexture(l.texture,l.red, l.green, l.blue, tx1, tx0, ty1, ty0, x0, x1, y0, y1, 1.0f, GLUtils.FILTER_LINEAR);
	GLUtils::drawTexture(tx1, tx0, ty1, ty0, x0, x1, y0, y1, alpha, GLUtils::FILTER_LINEAR);


	//upper right quadrant

	x0 = middleX;
	x1 = right;

	y0 = top;
	y1 = middleY;

	//GL.drawTexture(l.texture,l.red, l.green, l.blue, tx0, tx1, ty1, ty0, x0, x1, y0, y1, 1.0f, GLUtils.FILTER_LINEAR);
	GLUtils::drawTexture(tx0, tx1, ty1, ty0, x0, x1, y0, y1, alpha, GLUtils::FILTER_LINEAR);

	return true;
}

void Light::createLightTexturePNG(const string& fileName)
{ //===============================================================================================

	//Thread.yield();

	int maxBrightness = a();

	int lightBoxWidth = (int)(getWidth() / 2);
	int lightBoxHeight = (int)(getHeight() / 2);

	int maxRadius = (int)(getRadiusPixelsHQ() / 2);

	//int red = 255;
	//int green = 255;
	//int blue = 255;

	//decay exponent 1.0f = even decay from max to 0
	//decay exponent 0.5 = decays 0.5 as fast until 0.5, then decays 1.5 to radius
	//decay exponent 1.5 = decays 1.5 as fast until 0.5, then decays 0.5 to radius
	//decay exponent 1.7 = decays 1.7 as fast until 0.7, then decays 0.3 to radius
	//decay exponent 0.1 = decays 0.1 as fast until 0.9, then decays 1.9 to radius
	//decay at 1.5 until decayRadius, then decay from there to edge normally
	//we want to multiply by decayexponent until decayradius, then from decayradius to radius we want to multiply by inverse

	// O-----)----)
	//   150%  50%

	//instead i'll just use it as an exponent :P

	//float getDecayExponent = getDecayExponent;
	float focusRadius = (float)(focusRadiusPixelsHQ() / 2);

	//int lightBoxX = maxRadius;
	//int lightBoxY = maxRadius;

	int centerX = 0; //lightBoxX+lightBoxWidth/2;
	int centerY = 0; //lightBoxY+lightBoxHeight/2;

	BufferedImage* lightImage = new BufferedImage(maxRadius + lightBoxWidth / 2, maxRadius + lightBoxHeight / 2, BufferedImage::TYPE_INT_ARGB);

	//Graphics* lightImageGraphics = lightImage->getGraphics();

	float distanceFromBoxEdgeToXY = 0;
	float totalDistanceFromCenterToXY = 0;

	//get the angle of the corner of the light box
	float cornerAngle = (float)(atan((float)(lightBoxWidth / 2) / (float)(lightBoxHeight / 2)));

	float maxDistFromBox = (float)maxRadius;

	//float maxDistFromCenter = maxRadius+lightBoxWidth/2;
	//if(lightBoxWidth>lightBoxHeight)maxDistFromCenter = maxRadius+lightBoxHeight/2;


	//if focusradius!=0
	//fade into focusradius from center, fade out

	if (focusRadius != 0)
	{
		int xFromCenter = 0;
		int yFromCenter = 0;

		for (xFromCenter = 0; xFromCenter < maxRadius + lightBoxWidth / 2; xFromCenter++)
		{
			for (yFromCenter = 0; yFromCenter < maxRadius + lightBoxHeight / 2; yFromCenter++)
			{
				if (xFromCenter == 0)
				{
					totalDistanceFromCenterToXY = (float)yFromCenter;
				}
				else if (yFromCenter == 0)
				{
					totalDistanceFromCenterToXY = (float)xFromCenter;
				}
				else
				{
					totalDistanceFromCenterToXY = (float)hypot(yFromCenter, xFromCenter);
				}

				float distanceFromFocusRadius = abs(focusRadius - totalDistanceFromCenterToXY);

				int alpha = 0;

				//if x<=focusRadius && y<=focusRadius, calculate color distance from center to xy/center to focusdistance
				//else calculate color on distance from focusradius
				if (totalDistanceFromCenterToXY <= focusRadius)
				{
					if (totalDistanceFromCenterToXY <= focusRadius / 2)
					{
						//fade from maxBrightness to maxBrightness/2 based on distance to focusRadius/2
						alpha = (int)((maxBrightness / 3.0f) - (((totalDistanceFromCenterToXY / focusRadius) * (maxBrightness / 3.0f))) + (2.0f * (maxBrightness / 3.0f)));
						if (alpha > 255)
						{
							alpha = 255;
						}
						if (alpha < 0)
						{
							alpha = 0;
						}
					}
					else
					{
						alpha = (int)(((totalDistanceFromCenterToXY / focusRadius) * (maxBrightness / 3.0f)) + (2.0f * (maxBrightness / 3.0f)));
						if (alpha > 255)
						{
							alpha = 255;
						}
						if (alpha < 0)
						{
							alpha = 0;
						}
					}
				}
				else
				{
					alpha = maxBrightness - (int)(pow((distanceFromFocusRadius / (maxRadius - focusRadius)), 1.0f / decayExponent()) * (float)(maxBrightness));
					if (alpha > 255)
					{
						alpha = 255;
					}
					if (alpha < 0)
					{
						alpha = 0;
					}
				}

				lightImage->setColor(new BobColor(r(), g(), b(), alpha));
				//set pixel
				lightImage->fillRect((centerX + xFromCenter), (centerY + yFromCenter), 1, 1);
				//lightImageGraphics.fillRect(((centerX-1)-xFromCenter),(centerY+yFromCenter),1,1);
				//lightImageGraphics.fillRect((centerX+xFromCenter),((centerY-1)-yFromCenter),1,1);
				//lightImageGraphics.fillRect(((centerX-1)-xFromCenter),((centerY-1)-yFromCenter),1,1);
			}
		}
	}
	else
	{
		lightImage->setColor(new BobColor(r(), g(), b(), maxBrightness));
		//lightImageGraphics.fillRect(lightBoxX, lightBoxY, lightBoxWidth, lightBoxHeight);
		lightImage->fillRect(centerX, centerY, lightBoxWidth / 2, lightBoxHeight / 2);

		int xFromCenter = 0;
		int yFromCenter = 0;

		for (xFromCenter = 1; xFromCenter < maxRadius + lightBoxWidth / 2; xFromCenter++)
		{
			for (yFromCenter = 1; yFromCenter < maxRadius + lightBoxHeight / 2; yFromCenter++)
			{
				if (xFromCenter >= lightBoxWidth / 2 || yFromCenter >= lightBoxHeight / 2)
				{
					//get angle from center of box to x,y

					float angle;
					float distanceFromCenterToBoxEdge;
					float adjacent = 0;


					//if the angle of xy is greater than this, have to use adjacent boxwidth
					//if it's exactly the angle, it doesnt matter which
					angle = (float)(atan((float)(xFromCenter) / (float)(yFromCenter)));
					if (angle < cornerAngle)
					{
						adjacent = (float)lightBoxHeight / 2;

						//get hypotenuse of angle, box width
						//adjacent/hypotenuse = cos(alpha)
						//adjacent = cos(alpha)*hypot
						//adjacent/cos(alpha) = hypot
						distanceFromCenterToBoxEdge = adjacent / (float)(cos(angle));

						totalDistanceFromCenterToXY = (float)(hypot(yFromCenter, xFromCenter));
						//dist to x,y - hypotenuse length = dist from edge of box to x,y
						distanceFromBoxEdgeToXY = (totalDistanceFromCenterToXY - (distanceFromCenterToBoxEdge));
					}
					//else adjacent boxheight
					else
					{
						angle = (float)(atan((float)(yFromCenter) / (float)(xFromCenter)));

						adjacent = (float)lightBoxWidth / 2;

						//get hypotenuse of angle, box width
						//adjacent/hypotenuse = cos(alpha)
						//adjacent = cos(alpha)*hypot
						//adjacent/cos(alpha) = hypot
						distanceFromCenterToBoxEdge = adjacent / (float)(cos(angle));

						totalDistanceFromCenterToXY = (float)(hypot(xFromCenter, yFromCenter));
						//dist to x,y - hypotenuse length = dist from edge of box to x,y
						distanceFromBoxEdgeToXY = (totalDistanceFromCenterToXY - (distanceFromCenterToBoxEdge));
					}


					//log.debug("X: "+xFromCenter+" | Y: "+yFromCenter);
					//log.debug("Angle from center to x,y (radians): "+angle+" | Degrees: "+Math.toDegrees(angle));
					//log.debug("Distance to edge of box from center: "+distanceToEdgeFromCenter);

					if (distanceFromBoxEdgeToXY <= maxDistFromBox)
					{
						//int alpha = maxBrightness-(int)((((d/maxDistFromBox)*maxRadius)/(float)maxRadius)*(float)maxBrightness);

						int alpha = maxBrightness - (int)(pow((distanceFromBoxEdgeToXY / maxDistFromBox), 1.0f / decayExponent()) * (float)(maxBrightness));


						if (alpha > 255 || alpha < 0)
						{
							lightImage->setColor(new BobColor(255, 0, 255, 255));
						}
						else
						{
							//set color
							lightImage->setColor(new BobColor(r(), g(), b(), alpha));
						}
						//set pixel
						lightImage->fillRect((centerX + xFromCenter), (centerY + yFromCenter), 1, 1);
						//lightImageGraphics.fillRect(((centerX-1)-xFromCenter),(centerY+yFromCenter),1,1);
						//lightImageGraphics.fillRect((centerX+xFromCenter),((centerY-1)-yFromCenter),1,1);
						//lightImageGraphics.fillRect(((centerX-1)-xFromCenter),((centerY-1)-yFromCenter),1,1);
					}
				}
			}
		}

		yFromCenter = 0;
		for (xFromCenter = (lightBoxWidth / 2); xFromCenter < maxRadius + lightBoxWidth / 2; xFromCenter++)
		{
			distanceFromBoxEdgeToXY = (float)(xFromCenter - (lightBoxWidth / 2));

			totalDistanceFromCenterToXY = (float)xFromCenter;

			//int alpha = maxBrightness-(int)((((distanceFromBoxEdgeToXY/maxDistFromBox)*maxRadius)/(float)maxRadius)*(float)maxBrightness);
			int alpha = maxBrightness - (int)(pow((distanceFromBoxEdgeToXY / maxDistFromBox), 1.0f / decayExponent()) * (float)(maxBrightness));

			if (alpha > 255)
			{
				lightImage->setColor(new BobColor(255, 0, 255, 255));
			}
			else
			{
				lightImage->setColor(new BobColor(r(), g(), b(), alpha));
			}
			lightImage->fillRect((centerX + xFromCenter), (centerY + yFromCenter), 1, 1);
			//lightImageGraphics.fillRect(((centerX-1)-xFromCenter),(centerY+yFromCenter),1,1);
			//lightImageGraphics.fillRect((centerX+xFromCenter),((centerY-1)+yFromCenter),1,1);
			//lightImageGraphics.fillRect(((centerX-1)-xFromCenter),((centerY-1)+yFromCenter),1,1);
		}

		xFromCenter = 0;
		for (yFromCenter = (lightBoxHeight / 2); yFromCenter < maxRadius + lightBoxHeight / 2; yFromCenter++)
		{
			distanceFromBoxEdgeToXY = (float)(yFromCenter - (lightBoxHeight / 2));
			if (distanceFromBoxEdgeToXY > maxDistFromBox)
			{
				distanceFromBoxEdgeToXY = maxDistFromBox;
			}

			totalDistanceFromCenterToXY = (float)yFromCenter;

			//int alpha = maxBrightness-(int)((((distanceFromBoxEdgeToXY/maxDistFromBox)*maxRadius)/(float)maxRadius)*(float)maxBrightness);
			int alpha = maxBrightness - (int)(pow((distanceFromBoxEdgeToXY / maxDistFromBox), 1.0f / decayExponent()) * (float)(maxBrightness));


			if (alpha > 255)
			{
				lightImage->setColor(new BobColor(255, 0, 255, 255));
			}
			else
			{
				lightImage->setColor(new BobColor(r(), g(), b(), alpha));
			}
			lightImage->fillRect((centerX + xFromCenter), (centerY + yFromCenter), 1, 1);
			//lightImageGraphics.fillRect((centerX+xFromCenter),((centerY-1)-yFromCenter),1,1);
			//lightImageGraphics.fillRect(((centerX-1)+xFromCenter),(centerY+yFromCenter),1,1);
			//lightImageGraphics.fillRect(((centerX-1)+xFromCenter),((centerY-1)-yFromCenter),1,1);
		}
	}

	//lightImageGraphics->dispose();
	//Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//delete lightImageGraphics;


	/*
	try
	{
	   texture = TextureLoader.get().getTexture((ImageData)new BufferedImageData(lightImage),GL_NEAREST);
	}
	catch (IOException e)
	{
	   e.printStackTrace();
	}
	*/

	FileUtils::saveImage(fileName, lightImage);

	//lightImage->flush();
	//Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	delete lightImage;

	//System.runFinalization();
	//System.gc();

	//fill alpha native bytebuffer with lightImage.getRGB
	//create alpha texture id
	//send the bytebuffer into the texture

	//set texture to texture id


	//light->get(i).bufferedImage = lightImage;

	//now save the light to the cache, flush the lightimage, and load it as alpha texture.
	//then figure out how to blend it with alpha shader
}

BufferedImageData::BufferedImageData(Light* outerInstance, BufferedImage* bufferedImage) : outerInstance(outerInstance)
{
	this->width = bufferedImage->getWidth();
	this->height = bufferedImage->getHeight();

	this->texWidth = Math::getClosestPowerOfTwo(width);
	this->texHeight = Math::getClosestPowerOfTwo(height);

	byteArray = new u8(texWidth * texHeight * 4);

	//direct method, uses ram outside of the JVM
	//byteBuffer = ByteBuffer::allocateDirect(byteArray->size());
	//byteBuffer->order(ByteOrder::nativeOrder());

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int argb = bufferedImage->getRGB(x, y);
			int alpha = (argb >> 24) % 256;
			int red = (argb >> 16) % 256;
			int green = (argb >> 8) % 256;
			int blue = (argb) % 256;

			int i = (y * texWidth) + x;

			byteArray[(i * 4) + 0] = static_cast<char>(red);
			byteArray[(i * 4) + 1] = static_cast<char>(green);
			byteArray[(i * 4) + 2] = static_cast<char>(blue);
			byteArray[(i * 4) + 3] = static_cast<char>(alpha);
		}
	}

	//byteBuffer->put(byteArray);
	//byteBuffer.flip();
	//byteBuffer->rewind();
}

//int Light::BufferedImageData::getDepth()
//{
//   return 32;
//}
//
//int Light::BufferedImageData::getHeight()
//{
//   return height;
//}
//
//u8* Light::BufferedImageData::getImageBufferData()
//{
//   return byteBuffer;
//}
//
//int Light::BufferedImageData::getTexHeight()
//{
//   return texHeight;
//}
//
//int Light::BufferedImageData::getTexWidth()
//{
//   return texWidth;
//}
//
//int Light::BufferedImageData::getWidth()
//{
//   return width;
//}

float Light::getLeft()
{ //===============================================================================================
	return getX() - getRadiusPixelsHQ();
}

float Light::getRight()
{ //===============================================================================================
	return getX() + getWidth() + getRadiusPixelsHQ();
}

float Light::getTop()
{ //===============================================================================================
	return getY() - getRadiusPixelsHQ();
}

float Light::getBottom()
{ //===============================================================================================
	return getY() + getHeight() + getRadiusPixelsHQ();
}

float Light::getScreenLeft()
{ //===============================================================================================
	if (isScreenLight == true)
	{
		return getLeft();
	}

	float zoom = getCameraman()->getZoom();

	return (getMap()->screenX() * zoom + getX() * zoom - getRadiusPixelsHQ() * zoom);
}

float Light::screenRight()
{ //===============================================================================================
	if (isScreenLight == true)
	{
		return getRight();
	}

	float zoom = getCameraman()->getZoom();

	return (getMap()->screenX() * zoom + getX() * zoom + ((getWidth()) * zoom) + getRadiusPixelsHQ() * zoom);
}

float Light::getScreenTop()
{ //===============================================================================================
	if (isScreenLight == true)
	{
		return getTop();
	}

	float zoom = getCameraman()->getZoom();

	return (getMap()->screenY() * zoom + getY() * zoom - getRadiusPixelsHQ() * zoom);
}

float Light::screenBottom()
{ //===============================================================================================
	if (isScreenLight == true)
	{
		return getBottom();
	}

	float zoom = getCameraman()->getZoom();

	return (getMap()->screenY() * zoom + getY() * zoom + ((getHeight()) * zoom) + getRadiusPixelsHQ() * zoom);
}

float Light::screenMiddleX()
{ //===============================================================================================
	if (isScreenLight == true)
	{
		return getX() + ((getWidth() / 2));
	}

	float zoom = getCameraman()->getZoom();

	return (getMap()->screenX() * zoom + getX() * zoom + ((getWidth() / 2) * zoom));
}

float Light::screenMiddleY()
{ //===============================================================================================
	if (isScreenLight == true)
	{
		return getY() + ((getHeight() / 2));
	}

	float zoom = getCameraman()->getZoom();

	return (getMap()->screenY() * zoom + getY() * zoom + ((getHeight() / 2) * zoom));
}

float Light::getHitBoxFromLeft()
{ //=========================================================================================================================
	return 0;
}

float Light::getHitBoxFromRight()
{ //=========================================================================================================================
	return 0;
}

float Light::getHitBoxFromTop()
{ //=========================================================================================================================
	return 0;
}

float Light::getHitBoxFromBottom()
{ //=========================================================================================================================
	return 0;
}

LightData* Light::getLightData()
{
	return static_cast<LightData*>(data);
}

float Light::getWidth()
{
	return (float)getLightData()->getWidthPixelsHQ();
}

float Light::getHeight()
{
	return (float)getLightData()->getHeightPixelsHQ();
}

int Light::getRadiusPixelsHQ()
{
	return getLightData()->getRadiusPixelsHQ();
}

int Light::focusRadiusPixelsHQ()
{
	return getLightData()->getFocusRadiusPixelsHQ();
}

int Light::toggleXPixelsHQ()
{
	return getLightData()->getToggleXPixelsHQ();
}

int Light::toggleYPixelsHQ()
{
	return getLightData()->getToggleYPixelsHQ();
}

int Light::redColorByte()
{
	return getLightData()->getRedColorByte();
}

int Light::greenColorByte()
{
	return getLightData()->getGreenColorByte();
}

int Light::blueColorByte()
{
	return getLightData()->getBlueColorByte();
}

int Light::alphaColorByte()
{
	return getLightData()->getAlphaColorByte();
}

int Light::r()
{
	return getLightData()->getRedColorByte();
}

int Light::g()
{
	return getLightData()->getGreenColorByte();
}

int Light::b()
{
	return getLightData()->getBlueColorByte();
}

int Light::a()
{
	return getLightData()->getAlphaColorByte();
}

float Light::blendFalloff()
{
	return getLightData()->getBlendFalloff();
}

float Light::decayExponent()
{
	return getLightData()->getDecayExponent();
}

bool Light::isDayLight()
{
	return getLightData()->getIsDayLight();
}

bool Light::isNightLight()
{
	return getLightData()->getIsNightLight();
}

bool Light::flickers()
{
	return getLightData()->getFlickers();
}

bool Light::changesColor()
{
	return getLightData()->getChangesColor();
}

bool Light::toggleable()
{
	return getLightData()->getToggleable();
}

int Light::flickerOnTicks()
{
	return getLightData()->getFlickerOnTicks();
}

int Light::flickerOffTicks()
{
	return getLightData()->getFlickerOffTicks();
}

bool Light::flickerRandomUpToOnTicks()
{
	return getLightData()->getFlickerRandomUpToOnTicks();
}

bool Light::flickerRandomUpToOffTicks()
{
	return getLightData()->getFlickerRandomUpToOffTicks();
}

void Light::setWidthPixels(int s)
{
	getLightData()->setWidthPixels1X(s);
}

void Light::setHeightPixels(int s)
{
	getLightData()->setHeightPixels1X(s);
}

void Light::setRadiusPixels(int s)
{
	getLightData()->setRadiusPixels1X(s);
}

void Light::setFocusRadiusPixels(int s)
{
	getLightData()->setFocusRadiusPixels1X(s);
}

void Light::setToggleXPixels(int s)
{
	getLightData()->setToggleXPixels1X(s);
}

void Light::setToggleYPixels(int s)
{
	getLightData()->setToggleYPixels1X(s);
}

void Light::setRedColorByte(int s)
{
	getLightData()->setRedColorByte(s);
}

void Light::setGreenColorByte(int s)
{
	getLightData()->setGreenColorByte(s);
}

void Light::setBlueColorByte(int s)
{
	getLightData()->setBlueColorByte(s);
}

void Light::setAlphaColorByte(int s)
{
	getLightData()->setAlphaColorByte(s);
}

void Light::setBlendFalloff(float s)
{
	getLightData()->setBlendFalloff(s);
}

void Light::setDecayExponent(float s)
{
	getLightData()->setDecayExponent(s);
}

void Light::setIsDayLight(bool s)
{
	getLightData()->setIsDayLight(s);
}

void Light::setIsNightLight(bool s)
{
	getLightData()->setIsNightLight(s);
}

void Light::setFlickers(bool s)
{
	getLightData()->setFlickers(s);
}

void Light::setChangesColor(bool s)
{
	getLightData()->setChangesColor(s);
}

void Light::setToggleable(bool s)
{
	getLightData()->setToggleable(s);
}

void Light::setFlickerOnTicks(int s)
{
	getLightData()->setFlickerOnTicks(s);
}

void Light::setFlickerOffTicks(int s)
{
	getLightData()->setFlickerOffTicks(s);
}

void Light::setFlickerRandomUpToOnTicks(bool s)
{
	getLightData()->setFlickerRandomUpToOnTicks(s);
}

void Light::setFlickerRandomUpToOffTicks(bool s)
{
	getLightData()->setFlickerRandomUpToOffTicks(s);
}

