//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;



class LightData;
class Light;


class ImageData
{
};

class BufferedImageData : public ImageData
{
private:
	Light* outerInstance = nullptr;


	int width = 0;
	int height = 0;

	u8* byteArray;
	u8* byteBuffer;

	int texWidth = 0;
	int texHeight = 0;


public:
	BufferedImageData(Light* outerInstance, BufferedImage* bufferedImage);

	/// <seealso cref= org.newdawn.slick.opengl.ImageData#getDepth() </seealso>
	int getDepth();

	/// <seealso cref= org.newdawn.slick.opengl.ImageData#getHeight() </seealso>
	int getHeight();

	/// <seealso cref= org.newdawn.slick.opengl.ImageData#getImageBufferData() </seealso>
	u8* getImageBufferData();

	/// <seealso cref= org.newdawn.slick.opengl.ImageData#getTexHeight() </seealso>
	int getTexHeight();

	/// <seealso cref= org.newdawn.slick.opengl.ImageData#getTexWidth() </seealso>
	int getTexWidth();

	/// <seealso cref= org.newdawn.slick.opengl.ImageData#getWidth() </seealso>
	int getWidth();
};


class Light : public Entity
{
public:
	static Logger log;


	static int NOT_DRAWN;
	static int DRAWING;
	static int OVERLAPS_SOMETHING;
	static int DRAWN;


	BobTexture* texture = nullptr;


	int sortingState = 0;


	//private LightData data;

	//TO DO: handle these

	//public int id = -1;
	//public String stateName = "";


	bool isScreenLight = false;


	/// <summary>
	/// This constructor is specifically for creating lights not bound to the map, but to the screen instead. The mapX and mapY coords will be used as screen coords.
	/// </summary>
	Light(Engine* g, const string& name, int mapXPixels1X, int mapYPixels1X, int widthPixels1X, int heightPixels1X, int red, int green, int blue, int alpha, int radiusPixels1X, float blendFalloff, float decayExponent, int focusRadius1X, bool isDayLight, bool isNightLight);


	Light(Engine* g, LightData* lightAsset);


	bool flickerOnOffToggle = true;
	int onTicks = 0;
	int offTicks = 0;
	long long ticksCounter = 0;
	bool toggleOnOffToggle = true;

	bool drawLightThisFrame = true;


	virtual void update() override;	
	void initLight(LightData* lightAsset);
	void toggle();
	void setOnOff(bool b);
	void setFlicker(bool b);
	//The following method was originally marked 'synchronized':
	void setLightTexturePNGFileExists_S(bool exists);
	//The following method was originally marked 'synchronized':
	bool getLightTexturePNGFileExists_S();
	string getFileName();
	bool checkEdgeAgainstHitLayerAndOtherLightsInDirection(int dir);
	void bounceAroundRoom();
	bool isOnScreen();
	virtual void renderDebugBoxes() override;
	virtual void render(float alpha) override;
	bool renderLight();
	bool renderLight(float screenX0, float screenX1, float screenY0, float screenY1, float alpha);
	void createLightTexturePNG(const string& fileName);
public:
	virtual float getLeft() override;
	virtual float getRight() override;
	virtual float getTop() override;
	virtual float getBottom() override;
	virtual float getScreenLeft() override;
	virtual float screenRight();
	virtual float getScreenTop() override;
	virtual float screenBottom();
	virtual float screenMiddleX();
	virtual float screenMiddleY();
	virtual float getHitBoxFromLeft() final override;
	virtual float getHitBoxFromRight() final override;
	virtual float getHitBoxFromTop() final override;
	virtual float getHitBoxFromBottom() final override;

	//virtual EntityData* getData() override;
	virtual LightData* getLightData();


	virtual float getWidth() override;
	virtual float getHeight() override;


	virtual int getRadiusPixelsHQ();
	virtual int focusRadiusPixelsHQ();
	virtual int toggleXPixelsHQ();
	virtual int toggleYPixelsHQ();

	virtual int redColorByte();
	virtual int greenColorByte();
	virtual int blueColorByte();
	virtual int alphaColorByte();

	virtual int r();
	virtual int g();
	virtual int b();
	virtual int a();

	virtual float blendFalloff();
	virtual float decayExponent();
	virtual bool isDayLight();
	virtual bool isNightLight();
	virtual bool flickers();
	virtual bool changesColor();
	virtual bool toggleable();
	virtual int flickerOnTicks();
	virtual int flickerOffTicks();
	virtual bool flickerRandomUpToOnTicks();
	virtual bool flickerRandomUpToOffTicks();

	//public String getTYPEIDString(){return getData().getTYPEIDString();}


	//set

	virtual void setWidthPixels(int s);
	virtual void setHeightPixels(int s);
	virtual void setRadiusPixels(int s);
	virtual void setFocusRadiusPixels(int s);
	virtual void setToggleXPixels(int s);
	virtual void setToggleYPixels(int s);

	virtual void setRedColorByte(int s);
	virtual void setGreenColorByte(int s);
	virtual void setBlueColorByte(int s);
	virtual void setAlphaColorByte(int s);


	virtual void setBlendFalloff(float s);
	virtual void setDecayExponent(float s);
	virtual void setIsDayLight(bool s);
	virtual void setIsNightLight(bool s);
	virtual void setFlickers(bool s);
	virtual void setChangesColor(bool s);
	virtual void setToggleable(bool s);
	virtual void setFlickerOnTicks(int s);
	virtual void setFlickerOffTicks(int s);
	virtual void setFlickerRandomUpToOnTicks(bool s);
	virtual void setFlickerRandomUpToOffTicks(bool s);
};

