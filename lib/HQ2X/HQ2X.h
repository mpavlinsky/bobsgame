#pragma once

#include "src/Utility/BufferedImage.h"

class HQ2X
{
private:
	static bool lutsOk;
	static unsigned char* LUT16to32;
	static unsigned char* RGBtoYUV;
	int YUV1 = 0, YUV2 = 0;
	const int Ymask = 0x00FF0000;
	const int Umask = 0x0000FF00;
	const int Vmask = 0x000000FF;
	const int trY = 0x00300000;
	const int trU = 0x00000700;
	const int trV = 0x00000006;

	int Interp1(int c1, int c2);

	int Interp2(int c1, int c2, int c3);

	//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
	//ORIGINAL LINE: @SuppressWarnings("unused") private int Interp5(int c1, int c2)
	int Interp5(int c1, int c2);

	int Interp6(int c1, int c2, int c3);

	int Interp7(int c1, int c2, int c3);

	int Interp9(int c1, int c2, int c3);

	int Interp10(int c1, int c2, int c3);

	bool Diff(int w1, int w2);

	void hq2x_32(unsigned char* in, unsigned char* out, int Xres, int Yres);


	void InitLUTs();

	int RGB8888toRGB565(int rgb);


public:
	virtual BufferedImage* hq2x(BufferedImage* image);// unsigned char* in, int w, int h);


	//virtual unsigned char* hq2x(unsigned char* rgbIntArray, int w, int h);
};

