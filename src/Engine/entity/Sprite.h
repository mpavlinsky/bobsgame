//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;

#include "../../Utility/gl/GLUtils.h"
#include "../EnginePart.h"

class SpriteAnimationSequence;
class SpriteData;
class BobTexture;
//class TextureRegion;



class Sprite : public EnginePart
{
public:
	static Logger log;

	//static ExecutorService *generatePNGExecutorService;

	int* indexDataIntArray = nullptr;
	u8* paletteRGBByteArray = nullptr;

	BobTexture* texture = nullptr;
	BobTexture* shadowTexture = nullptr;

	//ArrayList<TextureRegion*>* frameTextureRegionList = new ArrayList<TextureRegion*>();

	bool useHQ2X = false;

protected:
	SpriteData* data = nullptr;

	bool _isInitialized = false;

private:
	long long lastCheckedSpriteTextureTime = 0;
	bool spriteTextureInitialized = false;

public:
	long long lastSentDataRequestTime = 0;

	bool threadCreated = false;
	bool checkedIfExist = false;
	bool hasDataMD5 = false; //non-threaded boolean check to avoid locking on synchronized function

	bool _texturePNGExists = false;



	Sprite();
	Sprite(Engine* g);
	void preloadFromFile(string name);
	//The following method was originally marked 'synchronized':
	virtual void initializeWithSpriteData(SpriteData* spriteData);
	virtual void sendDataRequest(const string& getSpriteName);
	virtual void sendDataRequest(int id);

	//The following method was originally marked 'synchronized':
	virtual bool getInitialized_S();
protected:
	//The following method was originally marked 'synchronized':
	virtual void setInitialized_S(bool i);
public:
	virtual void drawFrame(const string& animationName, float x0, float x1, float y0, float y1, float r = 1, float g = 1, float b = 1, float a = 1, int filter = GLUtils::FILTER_NEAREST);
	virtual void drawFrameXYWH(const string& animationName, float x, float y, float w, float h, float r = 1, float g = 1, float b = 1, float a = 1, int filter = GLUtils::FILTER_NEAREST);
	virtual void drawFrame(int frame, float x0, float x1, float y0, float y1, float a = 1, int filter = GLUtils::FILTER_NEAREST);
	virtual void drawFrame(BobTexture* texture, int frame, float x0, float x1, float y0, float y1, float a = 1, int filter = GLUtils::FILTER_NEAREST);
	virtual void drawFrame(int frame, float x0, float x1, float y0, float y1, float r = 1, float g = 1, float b = 1, float a = 1, int filter = GLUtils::FILTER_NEAREST);
	virtual void drawFrame(BobTexture* texture, int frame, float x0, float x1, float y0, float y1, float r = 1, float g = 1, float b = 1, float a = 1, int filter = GLUtils::FILTER_NEAREST);
	void draw(float tx0, float tx1, float ty0, float ty1, float x0, float x1, float y0, float y1, float r = 1, float g = 1, float b = 1, float a = 1, int filter = GLUtils::FILTER_NEAREST);



public:
	virtual void update();
	//	long lastTimeRequestedDataMD5s=0;
	//
	//	
	//	public void requestDataMD5sFromServer()
	//	{
	//
	//long long startTime = lastTimeRequestedDataMD5s;
	//long long currentTime = System::currentHighResTimer();
	//int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	//		if(ticksPassed>3000)
	//		{
	//			lastTimeRequestedDataMD5s = time;
	//
	//			//send a request to the server
	//			Main.clientTCP.sendSpriteDataRequestByName(getName());
	//			//when server sends back response, in BGClient, look up sprite asset by identifier, set textureMD5Names and build texture!!
	//		}
	//	}

	virtual void loadTextures();
	virtual u8* getReplacementRGBFromSet(int r, int g, int b, Sprite* s, int set);
	//The following method was originally marked 'synchronized':
	virtual u8* createRandomSpriteTextureByteBuffer_S(int eyeSet, int skinSet, int hairSet, int shirtSet, int pantsSet, int shoeSet, int carSet);
	//The following method was originally marked 'synchronized':
	virtual void createSpriteTexturePNG_S();
	//The following method was originally marked 'synchronized':
	virtual void createSpriteShadowTexturePNG_S();
	//The following method was originally marked 'synchronized':
	virtual void releaseSpriteTexture_S();

	


	//	public static int spriteTexturesLoaded = 0;
	//	public static int spriteThreadsCreated = 0;
	//	public static int maxSpriteThreadsCreated = 0;


	//The following method was originally marked 'synchronized':
	virtual bool getSpritePNGFileExists_S();

	//The following method was originally marked 'synchronized':
	virtual void setSpritePNGFileExists_S(bool done);


	//	
	//	public void incrementSpriteTexturesLoaded()
	//	{
	//		spriteTexturesLoaded++;
	//	}
	//	
	//	public void decrementSpriteTexturesLoaded()
	//	{
	//		spriteTexturesLoaded--;
	//	}

	//	
	//	public synchronized void incrementSpritePNGThreadsCreated_S()
	//	{
	//		spriteThreadsCreated++;
	//		if(spriteThreadsCreated>maxSpriteThreadsCreated)maxSpriteThreadsCreated=spriteThreadsCreated;
	//	}
	//
	//	
	//	public synchronized void decrementSpritePNGThreadsCreated_S()
	//	{
	//		spriteThreadsCreated--;
	//	}

	virtual int getNumberOfAnimations();
	virtual SpriteAnimationSequence* getFirstAnimation();
	virtual SpriteAnimationSequence* getAnimationByName(const string& name);
	virtual SpriteAnimationSequence* getAnimationByFrame(int frame);
	virtual SpriteAnimationSequence* getAnimationByIndex(int index);
	virtual int getAnimationNumFramesByIndex(int index);
	virtual int getAnimationNumFramesByName(const string& name);
	virtual int getAnimationNumFramesByFrame(int frame);
	virtual int getAnimationNumFramesByAnimation(SpriteAnimationSequence* a);
	virtual int getAnimationIndexByName(const string& name);
	virtual int getAnimationIndexByAnimation(SpriteAnimationSequence* a);
	virtual int getAnimationIndexByFrame(int frame);
	virtual string getAnimationNameByIndex(int index);
	virtual string getAnimationNameByFrame(int frame);
	virtual void antialiasBufferedImage(BufferedImage* bufferedImage);
	virtual void setHQ2XAlphaFromOriginal(BufferedImage* hq2xBufferedImage, BufferedImage* bufferedImage);


	

	virtual SpriteData* getData();

	virtual int getID();
	virtual string getName();
	virtual string getTYPEIDString();
	virtual string getDataMD5();
	virtual string getPaletteMD5();

	virtual string getComment();

	virtual int getImageWidth();
	virtual int getImageHeight();	
	virtual int getScreenWidth();
	virtual int getScreenHeight();
	virtual int getNumFrames();
	virtual string getDisplayName();
	virtual bool getIsNPC();
	virtual bool getIsKid();
	virtual bool getIsAdult();
	virtual bool getIsMale();
	virtual bool getIsFemale();
	virtual bool getIsCar();
	virtual bool getIsAnimal();
	virtual bool getHasShadow();
	virtual bool getIsRandom();
	virtual bool getIsDoor();
	virtual bool getIsGame();
	virtual bool getIsItem();
	virtual bool getForceHQ2X();
	virtual bool getForceMD5Export();
	virtual int getEventID();
	virtual string getItemGameDescription();
	virtual float getGamePrice();
	virtual int getUtilityOffsetXPixelsHQ();
	virtual int getUtilityOffsetYPixelsHQ();
	virtual ArrayList<SpriteAnimationSequence*>* getAnimationList();


	//	public void setName(String s){getData().setName(s);}
	//	public void setComment(String s){getData().setComment(s);}
	//	public void setID(int s){getData().setID(s);}
	//	public void setWidthPixels(int s){getData().setWidthPixels1X(s);}
	//	public void setHeightPixels(int s){getData().setHeightPixels1X(s);}
	//	public void setFrames(int s){getData().setFrames(s);}
	//	public void setDisplayName(String s){getData().setDisplayName(s);}
	//	public void setIsNPC(boolean s){getData().setIsNPC(s);}
	//	public void setIsKid(boolean s){getData().setIsKid(s);}
	//	public void setIsAdult(boolean s){getData().setIsAdult(s);}
	//	public void setIsMale(boolean s){getData().setIsMale(s);}
	//	public void setIsFemale(boolean s){getData().setIsFemale(s);}
	//	public void setIsCar(boolean s){getData().setIsCar(s);}
	//	public void setIsAnimal(boolean s){getData().setIsAnimal(s);}
	//	public void setHasShadow(boolean s){getData().setHasShadow(s);}
	//	public void setIsRandom(boolean s){getData().setIsRandom(s);}
	//	public void setIsDoor(boolean s){getData().setIsDoor(s);}
	//	public void setIsGame(boolean s){getData().setIsGame(s);}
	//	public void setIsItem(boolean s){getData().setIsItem(s);}
	//	public void setForceHQ2X(boolean s){getData().setForceHQ2X(s);}
	//	public void setForceMD5Export(boolean s){getData().setForceMD5Export(s);}
	//	public void setEventID(int s){getData().setEventID(s);}
	//	public void setItemGameDescription(String s){getData().setItemGameDescription(s);}
	//	public void setGamePrice(float s){getData().setGamePrice(s);}
	//	public void setUtilityOffsetXPixels1X(int s){getData().setUtilityOffsetXPixels1X(s);}
	//	public void setUtilityOffsetYPixels1X(int s){getData().setUtilityOffsetYPixels1X(s);}

};

