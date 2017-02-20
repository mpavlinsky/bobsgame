//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class TextWindow : public EnginePart
{ // =========================================================================================================================


public:
	static Logger log;


	BobTexture* textBoxTexture;
	BobTexture* spriteBoxTexture;
	BobTexture* borderTexture;


	float scrollPercent = 0;

	u8* textBoxTextureByteArray = nullptr;
	//u8* textBoxTexturePixelsByteBuffer;

	u8* spriteWindowTextureByteArray = nullptr;
	//u8* spriteWindowTexturePixelsByteBuffer;


	float voicePitch = 0;
	string label = "";

	int xInLine = 0;
	int line = 0;

	Entity* spriteWindowEntity = nullptr;

	BobTexture* spriteWindowTexture = nullptr;

	bool redraw = false;

	float alpha = 1.0f;


	int shakeTicksXTotal = 0;
	//public int shakeTicksLeft=0;
	int shakeTicksLeftRightCounter = 0;
	float shakeX = 0;
	int shakeMaxX = 2;
	bool shakeLeftRightToggle = false;


	int shakeTicksYTotal = 0;
	//public int shakeTicksLeft=0;
	int shakeTicksUpDownCounter = 0;
	float shakeY = 0;
	int shakeMaxY = 2;
	bool shakeUpDownToggle = false;

	TextWindow(Engine* g);


	virtual void init();


	virtual void render();


	virtual void updateSpriteWindowTexture();


	virtual void setSpriteWindow(Entity* entity, BobTexture* texture, const string& newLabel);


	virtual void updateTextureFromByteArray();


	virtual void clearByteArray();


	virtual int getPixelValue(int letter_index, int y, int x_in_letter, bool blank);


	virtual void setPixel(int index, BobColor* c);


	virtual void drawColumn(int letter_index, int x_in_letter, bool blank);
};

