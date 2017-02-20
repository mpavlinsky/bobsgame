//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "Logger.h"


class BobColor;


class BufferedImage
{
public:
	//static Logger log;

	u8* rgbadata;

	BufferedImage();
	BufferedImage(unsigned char* rgbadata, int w, int h);
	BufferedImage(int width, int height, int type);
	void setRGB(int i, int i1, int get_rgb);
	int getRGB(int i, int y);
	unsigned char* getData();
	void setColor(BobColor* bob_color);
	void fillRect(int i, int i1, int i2, int i3);
	static BufferedImage* loadFromPNG(string filename);
	const static int TYPE_INT_ARGB = 0;
	int getWidth();
	int getHeight();
};

