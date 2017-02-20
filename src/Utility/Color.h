//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "Logger.h"


int HARDWARE_RGB(int r, int g, int b);
void HARDWARE_create_brightened_palette(int* pal, int* newpal, int bright);


void adjust_color(int* pr, int* pg, int* pb);



class BobColor
{
	//various color utilities lifted from other libraries

public:

	//this is only because boost serialize was referencing other colors with exact data and it was breaking deserialization
	//string uuid = "";


	string name = "";
	int r = 0;
	int g = 0;
	int b = 0;
	int a = 0;

	template <typename Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
//		if (version > 0)
//		{
//			ar & BOOST_SERIALIZATION_NVP(uuid);
//		}
			ar & BOOST_SERIALIZATION_NVP(name);
			ar & BOOST_SERIALIZATION_NVP(r);
			ar & BOOST_SERIALIZATION_NVP(g);
			ar & BOOST_SERIALIZATION_NVP(b);
			ar & BOOST_SERIALIZATION_NVP(a);
	}

	

public:

	bool operator==(const BobColor& rhs) const
	{
		return
			r == rhs.r
			&& g == rhs.g
			&& b == rhs.b
			&& a == rhs.a
			&& name == rhs.name
			;
	}
	bool operator!=(const BobColor& rhs) const
	{
		return
			(*this == rhs) == false
			;
	}

//	BobColor& BobColor::operator=(const BobColor rhs)
//	{
//		//don't copy uuid
//
//		this->name = rhs.name;
//		this->r = rhs.r;
//		this->g = rhs.g;
//		this->b = rhs.b;
//		this->a = rhs.a;
//		
//		return *this;
//	}

	static BobColor* getColorByName(string name);
	static Logger log;

	static ArrayList<BobColor*> colors;

	static BobColor* clear;
	static BobColor* transparent;
	static BobColor* black;

	static BobColor* darkerGray;
	static BobColor* darkGray;
	static BobColor* gray;
	static BobColor* lightGray;
	static BobColor* lighterGray;

	static BobColor* white;

	static BobColor* cyan; //, lightCyan, darkCyan);
	static BobColor* lightCyan; //new Color(150,255,255);
	static BobColor* lighterCyan; //new Color(150,255,255);
	static BobColor* darkCyan; //new Color(0,220,220);
	static BobColor* darkerCyan; //new Color(0,180,180);
	static BobColor* magenta; //, lightMagenta, darkMagenta);
	static BobColor* lightMagenta; //new Color(255,120,127);
	static BobColor* lighterMagenta; //new Color(255,120,127);
	static BobColor* darkMagenta; //new Color(150,0,75);
	static BobColor* darkerMagenta; //new Color(127,0,64);
	static BobColor* yellow; //, lightYellow, darkYellow);
	static BobColor* lightYellow; //new Color(255,255,127);
	static BobColor* lighterYellow; //new Color(255,255,127);
	static BobColor* darkYellow; //new Color(200,200,0);
	static BobColor* darkerYellow; //new Color(127,127,0);
	static BobColor* orange; //, lightOrange, darkOrange);
	static BobColor* lightOrange; //new Color(255, 190, 110);
	static BobColor* lighterOrange; //new Color(255, 190, 110);
	static BobColor* darkOrange; //new Color(220, 115, 0);
	static BobColor* darkerOrange; //new Color(150, 90, 0);
	static BobColor* red; //, lightRed, darkRed);
	static BobColor* lightRed; //new Color(255,127,127);
	static BobColor* lighterRed; //new Color(255,127,127);
	static BobColor* darkRed; //new Color(127,0,0);
	static BobColor* darkerRed; //new Color(64,0,0);
	static BobColor* pink; //, lightPink, darkPink);
	static BobColor* lightPink; //new Color(255, 127, 255);
	static BobColor* lighterPink; //new Color(255, 127, 255);
	static BobColor* darkPink; //new Color(127, 0, 127);
	static BobColor* darkerPink; //new Color(64, 0, 64);
	static BobColor* purple; //, lightPurple, darkPurple);
	static BobColor* darkPurple; //new Color(63,0,127);
	static BobColor* darkerPurple; //new Color(63,0,127);
	static BobColor* lightPurple; //new Color(159,63,255);
	static BobColor* lighterPurple; //new Color(159,63,255);
	static BobColor* blue; //, lightBlue, darkBlue);
	static BobColor* lightBlue; //new Color(150,150,255);
	static BobColor* lighterBlue; //new Color(150,150,255);
	static BobColor* darkBlue; //new Color(0,0,150);
	static BobColor* darkerBlue; //new Color(0,0,64);
	static BobColor* green;
	static BobColor* lighterGreen;
	static BobColor* lightGreen;
	static BobColor* darkGreen;
	static BobColor* darkerGreen;
	static BobColor* aqua;
	static BobColor* lighterAqua;
	static BobColor* lightAqua;
	static BobColor* darkAqua;
	static BobColor* darkerAqua;
	static BobColor* turquoise;
	static BobColor* lighterTurquoise;
	static BobColor* lightTurquoise;
	static BobColor* darkTurquoise;
	static BobColor* darkerTurquoise;
	static BobColor* olive;
	static BobColor* lighterOlive;
	static BobColor* lightOlive;
	static BobColor* darkOlive;
	static BobColor* darkerOlive;
	static BobColor* burgandy;
	static BobColor* lighterBurgandy;
	static BobColor* lightBurgandy;
	static BobColor* darkBurgandy;
	static BobColor* darkerBurgandy;
	static BobColor* wine;


	static void initPresetColors();
	static bool colorsInitialized;// = false;

	BobColor();
	//BobColor(BobColor* c);
	//BobColor(const BobColor &c);
	BobColor(BobColor c, int ai);
	BobColor(BobColor c, float af);
	//BobColor(BobColor c, float af);
	BobColor(float rf, float gf, float bf);
	BobColor(float rf, float gf, float bf, float af);
	BobColor(int ri, int gi, int bi);
	BobColor(int ri, int gi, int bi, int ai);
	BobColor(float hf, float sf, float bf, float af, bool hsbOverload);
	BobColor(int rgb);
	float rf();
	float gf();
	float bf();
	float af();
	int ri();
	int gi();
	int bi();
	int ai();
	static float* RGBtoHSB(int r, int g, int b);
	static int HSBtoRGB(float hue, float saturation, float brightness);
	void darker();
	void darker(float scale);
	void lighter();
	void lighter(float scale);

	// void *multiply(Color *c);
	//Color *addToCopy(Color *c);
	//Color *scaleCopy(float value);


	static int rgbatoABGRInt(char r, char g, char b, char a);
	//static int HexToDec(const string &hexst);
	static int DecToRed(int dec);
	static int DecToGreen(int dec);
	static int DecToBlue(int dec);
	int getRGB();
};

BOOST_CLASS_VERSION(BobColor, 1)
BOOST_CLASS_TRACKING(BobColor, boost::serialization::track_never)