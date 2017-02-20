//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class RandomCharacter : public Character
{
public:
	static Logger log;


	int targetX = -1;
	int targetY = -1;

	string cameFrom = "";
	bool gotThere = false;


	//public Texture shadowTexture = null; // just use the normal hq2x shadow texture in the spriteasset since it doesn't matter.


	bool kid = false;
	bool adult = false;
	bool male = false;
	bool female = false;
	bool car = false;


	RandomCharacter(Engine* g, Map* map, int spawnXPixels1X, int spawnYPixels1X, bool kid, bool adult, bool male, bool female, bool car);


	virtual Map* getCurrentMap();


	//The following method was originally marked 'synchronized':
	virtual u8* getByteBuffer_S();


	//The following method was originally marked 'synchronized':
	virtual void setByteBuffer_S(u8* bb);


	u8* textureByteBuffer_S;

	int eyeSet = -1;
	int skinSet = -1;
	int hairSet = -1;
	int shirtSet = -1;
	int pantsSet = -1;
	int shoeSet = -1;
	int carSet = -1;


	virtual int selectRandomSet(Sprite* s);


	bool createdThread = false;


	virtual void createRandomTexture();


	virtual void update() override;


	virtual string getRandomAreaWarpOrDoorTYPEID();


	virtual string getRandomConnectionTYPEIDFromCurrentPoint();
};

