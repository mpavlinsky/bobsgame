//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class SpriteData : public AssetData
{
	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------
	//
	//
	//
	//	WARNING! EDITING THESE NAMES WILL BREAK JSON DECODING
	//
	//
	//
	//
	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------

private:
	
	string comment = "";

	
	string displayName = "";

	
	int widthPixels1X = 0;
	
	int heightPixels1X = 0;

	
	int frames = 1;

	
	bool isNPC = false; //not used for anything yet

	
	bool isKid = false;
	
	bool isAdult = false;
	
	bool isMale = false;
	
	bool isFemale = false;
	
	bool isCar = false;
	
	bool isAnimal = false;


	
	bool hasShadow = false;
	
	bool isRandom = false;


	//TODO: handle these
	
	bool isDoor = false;
	
	bool isGame = false;
	
	bool isItem = false;

	
	bool forceHQ2X = false;
	
	bool forceMD5Export = false;

	
	int eventID = -1;
	
	string itemGameDescription = "";
	
	float gamePrice = 0.0f;


	
	int utilityOffsetXPixels1X = 0; //used for spawn point, doorknob marking, hands?
	
	int utilityOffsetYPixels1X = 0;


	
	string dataMD5 = "";
	
	string paletteMD5 = "";


	
	ArrayList<SpriteAnimationSequence*>* animationList = new ArrayList<SpriteAnimationSequence*>();


public:

	SpriteData(int id = -1, const string& name = "none", const string& displayName = "", int widthPixels1X = 0, int heightPixels1X = 0, int frames = 1, bool isNPC = false, bool isKid = false, bool isAdult = false, bool isMale = false, bool isFemale = false, bool isCar = false, bool isAnimal = false, bool hasShadow = false, bool isRandom = false, bool isDoor = false, bool isGame = false, bool isItem = false, bool forceHQ2X = false, bool forceClientMD5Export = false, int eventID = -1, const string& itemGameDescription = "", float gamePrice = 0, int utilityOffsetXPixels1X = 0, int utilityOffsetYPixels1X = 0, const string& dataMD5 = "", const string& paletteMD5 = "");


	virtual void addAnimation(const string& frameSequenceName, int frameStart, int hitBoxOffsetLeft1X, int hitBoxOffsetRight1X, int hitBoxOffsetTop1X, int hitBoxOffsetBottom1X);


	static SpriteData* fromBase64ZippedJSON(const string& b64);


	static SpriteData* fromJSON(const string& json);


	virtual string getTYPEIDString();


	virtual string getDisplayName();
	virtual int getWidthPixels1X();
	virtual int getHeightPixels1X();
	virtual int getWidthPixelsHQ();
	virtual int getHeightPixelsHQ();
	virtual int getNumFrames();
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
	virtual int getEventID();
	virtual string getItemGameDescription();
	virtual float getGamePrice();
	virtual int getUtilityOffsetXPixels1X();
	virtual int getUtilityOffsetYPixels1X();
	virtual int getUtilityOffsetXPixelsHQ();
	virtual int getUtilityOffsetYPixelsHQ();
	virtual string getDataMD5();
	virtual string getPaletteMD5();
	virtual ArrayList<SpriteAnimationSequence*>* getAnimationList();
	virtual string getComment();
	virtual bool getForceMD5Export();


	virtual void setComment(const string& s);
	virtual void setWidthPixels1X(int s);
	virtual void setHeightPixels1X(int s);
	virtual void setFrames(int s);
	virtual void setDisplayName(const string& s);
	virtual void setIsNPC(bool s);
	virtual void setIsKid(bool s);
	virtual void setIsAdult(bool s);
	virtual void setIsMale(bool s);
	virtual void setIsFemale(bool s);
	virtual void setIsCar(bool s);
	virtual void setIsAnimal(bool s);
	virtual void setHasShadow(bool s);
	virtual void setIsRandom(bool s);
	virtual void setIsDoor(bool s);
	virtual void setIsGame(bool s);
	virtual void setIsItem(bool s);
	virtual void setForceHQ2X(bool s);
	virtual void setForceMD5Export(bool s);
	virtual void setEventID(int s);
	virtual void setItemGameDescription(const string& s);
	virtual void setGamePrice(float s);
	virtual void setUtilityOffsetXPixels1X(int s);
	virtual void setUtilityOffsetYPixels1X(int s);
	virtual void setDataMD5(const string& s);
	virtual void setPaletteMD5(const string& s);
};

