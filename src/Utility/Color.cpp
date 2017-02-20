#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once



Logger BobColor::log = Logger("Color");
bool BobColor::colorsInitialized = false;


ArrayList<BobColor*> BobColor::colors;

BobColor* BobColor::clear = new BobColor(0, 0, 0, 0);
BobColor* BobColor::transparent = clear;
BobColor* BobColor::black = new BobColor(0, 0, 0);
BobColor* BobColor::darkerGray = new BobColor(0.2f, 0.2f, 0.2f);
BobColor* BobColor::darkGray = new BobColor(0.35f, 0.35f, 0.35f);
BobColor* BobColor::gray = new BobColor(0.5f, 0.5f, 0.5f);
BobColor* BobColor::lightGray = new BobColor(0.65f, 0.65f, 0.65f);
BobColor* BobColor::lighterGray = new BobColor(0.8f, 0.8f, 0.8f);
BobColor* BobColor::white = new BobColor(1.0f, 1.0f, 1.0f);

BobColor* BobColor::cyan = new BobColor(0, 255, 255);
BobColor* BobColor::lightCyan = new BobColor(0, 255, 255); //cyan->lighter();
BobColor* BobColor::lighterCyan = new BobColor(0, 255, 255); //cyan->lighter();
BobColor* BobColor::darkCyan = new BobColor(0, 255, 255); //cyan->darker();
BobColor* BobColor::darkerCyan = new BobColor(0, 255, 255); //cyan->darker()->darker();

BobColor* BobColor::magenta = new BobColor(255, 0, 127);
BobColor* BobColor::lightMagenta = new BobColor(255, 0, 127); //magenta->lighter();
BobColor* BobColor::lighterMagenta = new BobColor(255, 0, 127); //magenta->lighter();
BobColor* BobColor::darkMagenta = new BobColor(255, 0, 127); //magenta->darker();
BobColor* BobColor::darkerMagenta = new BobColor(255, 0, 127); //magenta->darker()->darker();

BobColor* BobColor::yellow = new BobColor(255, 255, 0);
BobColor* BobColor::lightYellow = new BobColor(255, 255, 0); //yellow->lighter();
BobColor* BobColor::lighterYellow = new BobColor(255, 255, 0); //yellow->lighter();
BobColor* BobColor::darkYellow = new BobColor(255, 255, 0); //yellow->darker();
BobColor* BobColor::darkerYellow = new BobColor(255, 255, 0); //yellow->darker()->darker();

BobColor* BobColor::orange = new BobColor(255, 140, 0);
BobColor* BobColor::lightOrange = new BobColor(255, 140, 0); //orange->lighter();
BobColor* BobColor::lighterOrange = new BobColor(255, 140, 0); //orange->lighter();
BobColor* BobColor::darkOrange = new BobColor(255, 140, 0); //orange->darker();
BobColor* BobColor::darkerOrange = new BobColor(255, 140, 0); //orange->darker()->darker();

BobColor* BobColor::red = new BobColor(255, 0, 0);
BobColor* BobColor::lightRed = new BobColor(255, 0, 0); //red->lighter();
BobColor* BobColor::lighterRed = new BobColor(255, 0, 0); //red->lighter();
BobColor* BobColor::darkRed = new BobColor(255, 0, 0); //red->darker();
BobColor* BobColor::darkerRed = new BobColor(255, 0, 0); //red->darker()->darker();

BobColor* BobColor::pink = new BobColor(255, 0, 255);
BobColor* BobColor::lightPink = new BobColor(255, 0, 255); //pink->lighter();
BobColor* BobColor::lighterPink = new BobColor(255, 0, 255); //pink->lighter();
BobColor* BobColor::darkPink = new BobColor(255, 0, 255); //pink->darker();
BobColor* BobColor::darkerPink = new BobColor(255, 0, 255); //pink->darker()->darker();

BobColor* BobColor::purple = new BobColor(127, 0, 255);
BobColor* BobColor::lightPurple = new BobColor(127, 0, 255); //purple->lighter();
BobColor* BobColor::lighterPurple = new BobColor(127, 0, 255); //purple->lighter();
BobColor* BobColor::darkPurple = new BobColor(127, 0, 255); //purple->darker();
BobColor* BobColor::darkerPurple = new BobColor(127, 0, 255); //purple->darker()->darker();


BobColor* BobColor::blue = new BobColor(0, 0, 255);
BobColor* BobColor::lighterBlue = new BobColor(0, 0, 255); //blue->lighter();
BobColor* BobColor::lightBlue = new BobColor(0, 0, 255); //blue->lighter();
BobColor* BobColor::darkBlue = new BobColor(0, 0, 255); //blue->darker();
BobColor* BobColor::darkerBlue = new BobColor(0, 0, 255); //blue->darker()->darker();

BobColor* BobColor::green = new BobColor(0, 255, 0);
BobColor* BobColor::lighterGreen = new BobColor(0, 255, 0); //green->lighter()->lighter();
BobColor* BobColor::lightGreen = new BobColor(0, 255, 0); //green->lighter();
BobColor* BobColor::darkGreen = new BobColor(0, 255, 0); //green->darker();
BobColor* BobColor::darkerGreen = new BobColor(0, 255, 0); //green->darker()->darker();

BobColor* BobColor::aqua = new BobColor(0, 150, 255);
BobColor* BobColor::lighterAqua = new BobColor(0, 150, 255); //aqua->lighter()->lighter();
BobColor* BobColor::lightAqua = new BobColor(0, 150, 255); //aqua->lighter();
BobColor* BobColor::darkAqua = new BobColor(0, 150, 255); //aqua->darker();
BobColor* BobColor::darkerAqua = new BobColor(0, 150, 255); //aqua->darker()->darker();

BobColor* BobColor::turquoise = new BobColor(0, 255, 150);
BobColor* BobColor::lighterTurquoise = new BobColor(0, 255, 150); //turquoise->lighter()->lighter();
BobColor* BobColor::lightTurquoise = new BobColor(0, 255, 150); //turquoise->lighter();
BobColor* BobColor::darkTurquoise = new BobColor(0, 255, 150); //turquoise->darker();
BobColor* BobColor::darkerTurquoise = new BobColor(0, 255, 150); //turquoise->darker()->darker();

BobColor* BobColor::olive = new BobColor(64, 72, 0);
BobColor* BobColor::darkerOlive = new BobColor(64, 72, 0);
BobColor* BobColor::darkOlive = new BobColor(64, 72, 0);
BobColor* BobColor::lighterOlive = new BobColor(64, 72, 0);
BobColor* BobColor::lightOlive = new BobColor(64, 72, 0);

BobColor* BobColor::burgandy = new BobColor(220, 70, 0);
BobColor* BobColor::darkerBurgandy = new BobColor(220, 70, 0);
BobColor* BobColor::darkBurgandy = new BobColor(220, 70, 0);
BobColor* BobColor::lighterBurgandy = new BobColor(220, 70, 0);
BobColor* BobColor::lightBurgandy = new BobColor(220, 70, 0);


BobColor* BobColor::wine = new BobColor(200, 80, 0);



//==========================================================================================================================
int HARDWARE_RGB(int r, int g, int b)
{//==========================================================================================================================
	return ((1 << 15) + (r) + ((g) << 5) + ((b) << 10));
}


//==========================================================================================================================
void RGBToHSL(float r, float g, float b, float* h, float* s, float* l)
{//==========================================================================================================================


	//float fmin = min(min(r, g), b);    //Min. value of RGB
	//float fmax = max(max(r, g), b);    //Max. value of RGB
	float fmin = r;
	if (g < fmin)fmin = g;
	if (b < fmin)fmin = b;

	float fmax = r;
	if (g > fmax)fmax = g;
	if (b > fmax)fmax = b;

	float delta = fmax - fmin; //Delta RGB value

	*l = (fmax + fmin) / 2.0f; // Luminance

	if (delta == 0.0f) //This is a gray, no chroma...
	{
		*h = 0.0f; // Hue
		*s = 0.0f; // Saturation
	}
	else //Chromatic data...
	{
		if (*l < 0.5f)
			*s = delta / (fmax + fmin); // Saturation
		else
			*s = delta / (2.0f - fmax - fmin); // Saturation

		float deltaR = (((fmax - r) / 6.0f) + (delta / 2.0f)) / delta;
		float deltaG = (((fmax - g) / 6.0f) + (delta / 2.0f)) / delta;
		float deltaB = (((fmax - b) / 6.0f) + (delta / 2.0f)) / delta;

		if (r == fmax)
			*h = deltaB - deltaG; // Hue
		else if (g == fmax)
			*h = (1.0f / 3.0f) + deltaR - deltaB; // Hue
		else if (b == fmax)
			*h = (2.0f / 3.0f) + deltaG - deltaR; // Hue

		if (*h < 0.0f)
			*h += 1.0f; // Hue
		else if (*h > 1.0f)
			*h -= 1.0f; // Hue
	}
}

//==========================================================================================================================
float HueToRGB(float f1, float f2, float hue)
{//==========================================================================================================================
	if (hue < 0.0f)
		hue += 1.0f;
	else if (hue > 1.0f)
		hue -= 1.0f;
	float res;
	if ((6.0f * hue) < 1.0f)
		res = f1 + (f2 - f1) * 6.0f * hue;
	else if ((2.0f * hue) < 1.0f)
		res = f2;
	else if ((3.0f * hue) < 2.0f)
		res = f1 + (f2 - f1) * ((2.0f / 3.0f) - hue) * 6.0f;
	else
		res = f1;
	return res;
}

//==========================================================================================================================
void HSLToRGB(float h, float s, float l, float* r, float* g, float* b)
{//==========================================================================================================================


	if (s == 0.0f)
	{
		*r = l;
		*g = l;
		*b = l;
	}
	else
	{
		float f2;

		if (l < 0.5f)
			f2 = l * (1.0f + s);
		else
			f2 = (l + s) - (s * l);

		float f1 = 2.0f * l - f2;

		*r = HueToRGB(f1, f2, h + (1.0f / 3.0f));
		*g = HueToRGB(f1, f2, h);
		*b = HueToRGB(f1, f2, h - (1.0f / 3.0f));
	}
}

//float adjust_gamma = 1.0f;
//float adjust_brightness = 1.0f;
//float adjust_lightness = 1.0f;

//==========================================================================================================================
void adjust_color(int* pr, int* pg, int* pb)
{//==========================================================================================================================

	int r, g, b;
	r = *pr;
	g = *pg;
	b = *pb;

	//if its not black
	if (r != b || r != g || (r == b && r == g && r > 16))
	{
		float fr, fg, fb, fh, fs, fl;
		fr = (float)((float)r / 256.0f);
		fg = (float)((float)g / 256.0f);
		fb = (float)((float)b / 256.0f);


		//gamma
		//fr = pow(fr,0.8f);
		//fg = pow(fg,0.8f);
		//fb = pow(fb,0.8f);

		//increase blue hue unless color is gray
		if (r != b || r != g)
			fb = fb + (5.0f / 256.0f);

		//increase lightness
		RGBToHSL(fr, fg, fb, &fh, &fs, &fl);
		fl += (10.0f / 256.0f);
		fs += (5.0f / 256.0f);
		if (fl > 1.0f)fl = 1.0f;
		if (fs > 1.0f)fs = 1.0f;
		HSLToRGB(fh, fs, fl, &fr, &fg, &fb);

		//brighten
		//fr*=1.1f;
		//fg*=1.1f;
		//fb*=1.1f;


		r = (int)(fr * 256.0f);
		g = (int)(fg * 256.0f);
		b = (int)(fb * 256.0f);

		if (r > 255)r = 255;
		if (g > 255)g = 255;
		if (b > 255)b = 255;
	}

	*pr = r;
	*pb = b;
	*pg = g;

	/*
	vec3 hslcolor = RGBToHSL(color);
	//hslcolor.x+=(3.0f/255.0f);
	hslcolor.z+=(5.0f/255.0f);
	color = HSLToRGB(hslcolor);


	color = ContrastSaturationBrightness(color,1.0,1.0,1.1);

	*/
}


//==========================================================================================================================
void HARDWARE_create_brightened_palette(int* pal, int* newpal, int bright)//HARDWARE_CreatePalBright
{//==========================================================================================================================

	int x = 0;
	for (x = 0; x < 256; x++)
	{
		//bgr->rgb->hsl->lighten->rgb->bgr
		/*

		int bgr=pal[x];

		//bgr to r g b

		int r=((((bgr%32))*8));
		int g=((((bgr/32)%32))*8);
		int b=(((bgr/1024))*8);


		//r g b to h s l

		float hue, saturation, brightness;

		int cmax = (r > g) ? r : g;
		if (b > cmax) cmax = b;
		int cmin = (r < g) ? r : g;
		if (b < cmin) cmin = b;

		brightness = ((float) cmax) / 255.0f;
		if (cmax != 0)
		saturation = ((float) (cmax - cmin)) / ((float) cmax);
		else
		saturation = 0;
		if (saturation == 0)
		hue = 0;
		else {
		float redc = ((float) (cmax - r)) / ((float) (cmax - cmin));
		float greenc = ((float) (cmax - g)) / ((float) (cmax - cmin));
		float bluec = ((float) (cmax - b)) / ((float) (cmax - cmin));
		if (r == cmax)
		hue = bluec - greenc;
		else if (g == cmax)
		hue = 2.0f + redc - bluec;
		else
		hue = 4.0f + greenc - redc;
		hue = hue / 6.0f;
		if (hue < 0)
		hue = hue + 1.0f;
		}


		//h s l lighten

		brightness=brightness*((((float)bright)+31.0f)/31.0f);
		if(brightness<0.0f)brightness=0.0f;
		//if(brightness>1.0f)brightness=1.0f;

		//h s l to r g b



		if (saturation == 0)
		{
		r = g = b = (int) (brightness * 255.0f + 0.5f);
		}
		else
		{
		float h = (hue - (float)floor(hue)) * 6.0f;
		float f = h - (float)floor(h);
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));
		switch ((int) h)
		{
		case 0:
		r = (int) (brightness * 255.0f + 0.5f);
		g = (int) (t * 255.0f + 0.5f);
		b = (int) (p * 255.0f + 0.5f);
		break;
		case 1:
		r = (int) (q * 255.0f + 0.5f);
		g = (int) (brightness * 255.0f + 0.5f);
		b = (int) (p * 255.0f + 0.5f);
		break;
		case 2:
		r = (int) (p * 255.0f + 0.5f);
		g = (int) (brightness * 255.0f + 0.5f);
		b = (int) (t * 255.0f + 0.5f);
		break;
		case 3:
		r = (int) (p * 255.0f + 0.5f);
		g = (int) (q * 255.0f + 0.5f);
		b = (int) (brightness * 255.0f + 0.5f);
		break;
		case 4:
		r = (int) (t * 255.0f + 0.5f);
		g = (int) (p * 255.0f + 0.5f);
		b = (int) (brightness * 255.0f + 0.5f);
		break;
		case 5:
		r = (int) (brightness * 255.0f + 0.5f);
		g = (int) (p * 255.0f + 0.5f);
		b = (int) (q * 255.0f + 0.5f);
		break;
		}
		}

		//r g b to bgr
		if(r>255)r=255;
		if(g>255)g=255;
		if(b>255)b=255;

		int newbgr =((b/8)*1024)+((g/8)*32)+((r/8));
		*/

		//plain old rgb lightening

		int r, g, b;

		r = pal[x] & 31;
		r += bright;
		if (r < 0) r = 0;
		if (r > 31) r = 31;
		g = (pal[x] >> 5) & 31;
		g += bright;
		if (g < 0) g = 0;
		if (g > 31) g = 31;
		b = (pal[x] >> 10) & 31;
		b += bright;
		if (b < 0) b = 0;
		if (b > 31) b = 31;
		newpal[x] = HARDWARE_RGB(r, g, b);
	}
}


//=========================================================================================================================
void BobColor::initPresetColors()
{//=========================================================================================================================
	if (colorsInitialized)return;

	colorsInitialized = true;
	BobColor c;

	lightCyan->lighter();
	lighterCyan->lighter();
	lighterCyan->lighter();
	darkCyan->darker();
	darkerCyan->darker();
	darkerCyan->darker();


	lightMagenta->lighter();
	lighterMagenta->lighter();
	lighterMagenta->lighter();
	darkMagenta->darker();
	darkerMagenta->darker();
	darkerMagenta->darker();


	lightYellow->lighter();
	lighterYellow->lighter();
	lighterYellow->lighter();
	darkYellow->darker();
	darkerYellow->darker();
	darkerYellow->darker();


	lightOrange->lighter();
	darkOrange->darker();
	darkerOrange->darker();
	darkerOrange->darker();


	lightRed->lighter();
	lighterRed->lighter();
	lighterRed->lighter();
	darkRed->darker();
	darkerRed->darker();
	darkerRed->darker();


	lightPink->lighter();
	lighterPink->lighter();
	lighterPink->lighter();
	darkPink->darker();
	darkerPink->darker();
	darkerPink->darker();


	lightPurple->lighter();
	lighterPurple->lighter();
	lighterPurple->lighter();
	darkPurple->darker();
	darkerPurple->darker();
	darkerPurple->darker();


	lightBlue->lighter();
	lighterBlue->lighter();
	lighterBlue->lighter();
	darkBlue->darker();
	darkerBlue->darker();
	darkerBlue->darker();


	lighterGreen->lighter();
	lighterGreen->lighter();
	lightGreen->lighter();
	darkGreen->darker();
	darkerGreen->darker();
	darkerGreen->darker();


	lighterAqua->lighter();
	lighterAqua->lighter();
	lightAqua->lighter();
	darkAqua->darker();
	darkerAqua->darker();
	darkerAqua->darker();


	lighterTurquoise->lighter();
	lighterTurquoise->lighter();
	lightTurquoise->lighter();
	darkTurquoise->darker();
	darkerTurquoise->darker();
	darkerTurquoise->darker();

	lighterOlive->lighter();
	lighterOlive->lighter();
	lightOlive->lighter();
	darkOlive->darker();
	darkerOlive->darker();
	darkerOlive->darker();

	lighterBurgandy->lighter();
	lighterBurgandy->lighter();
	lightBurgandy->lighter();
	darkBurgandy->darker();
	darkerBurgandy->darker();
	darkerBurgandy->darker();

	clear->name="clear";
	black->name="black";
	darkerGray->name="darkerGray";
	darkGray->name="darkGray";
	gray->name="gray";
	lightGray->name="lightGray";
	lighterGray->name="lighterGray";
	white->name="white";

	cyan->name="cyan";
	lightCyan->name="lightCyan";
	lighterCyan->name="lighterCyan";
	darkCyan->name="darkCyan";
	darkerCyan->name="darkerCyan";

	magenta->name="magenta";
	lightMagenta->name="lightMagenta";
	lighterMagenta->name="lighterMagenta";
	darkMagenta->name="darkMagenta";
	darkerMagenta->name="darkerMagenta";

	yellow->name="yellow";
	lightYellow->name="lightYellow";
	lighterYellow->name="lighterYellow";
	darkYellow->name="darkYellow";
	darkerYellow->name="darkerYellow";

	orange->name="orange";
	lightOrange->name="lightOrange";
	lighterOrange->name="lighterOrange";
	darkOrange->name="darkOrange";
	darkerOrange->name="darkerOrange";

	red->name="red";
	lightRed->name="lightRed";
	lighterRed->name="lighterRed";
	darkRed->name="darkRed";
	darkerRed->name="darkerRed";

	pink->name="pink";
	lightPink->name="lightPink";
	lighterPink->name="lighterPink";
	darkPink->name="darkPink";
	darkerPink->name="darkerPink";

	purple->name="purple";
	lightPurple->name="lightPurple";
	lighterPurple->name="lighterPurple";
	darkPurple->name="darkPurple";
	darkerPurple->name="darkerPurple";


	blue->name="blue";
	lighterBlue->name="lighterBlue";
	lightBlue->name="lightBlue";
	darkBlue->name="darkBlue";
	darkerBlue->name="darkerBlue";

	green->name="green";
	lighterGreen->name="lighterGreen";
	lightGreen->name="lightGreen";
	darkGreen->name="darkGreen";
	darkerGreen->name="darkerGreen";

	aqua->name="aqua";
	lighterAqua->name="lighterAqua";
	lightAqua->name="lightAqua";
	darkAqua->name="darkAqua";
	darkerAqua->name="darkerAqua";

	turquoise->name="turquoise";
	lighterTurquoise->name="lighterTurquoise";
	lightTurquoise->name="lightTurquoise";
	darkTurquoise->name="darkTurquoise";
	darkerTurquoise->name="darkerTurquoise";

	olive->name="olive";
	lighterOlive->name = "lighterOlive";
	lightOlive->name = "lightOlive";
	darkOlive->name = "darkOlive";
	darkerOlive->name = "darkerOlive";

	burgandy->name="burgandy";
	lighterBurgandy->name = "lighterBurgandy";
	lightBurgandy->name = "lightBurgandy";
	darkBurgandy->name = "darkBurgandy";
	darkerBurgandy->name = "darkerBurgandy";

	wine->name="wine";


	colors.add(clear);
	colors.add(transparent);
	colors.add(black);
	colors.add(darkerGray);
	colors.add(darkGray);
	colors.add(gray);
	colors.add(lightGray);
	colors.add(lighterGray);
	colors.add(white);
	colors.add(cyan);
	colors.add(lightCyan);
	colors.add(lighterCyan);
	colors.add(darkCyan);
	colors.add(darkerCyan);
	colors.add(magenta);
	colors.add(lightMagenta);
	colors.add(lighterMagenta);
	colors.add(darkMagenta);
	colors.add(darkerMagenta);
	colors.add(yellow);
	colors.add(lightYellow);
	colors.add(lighterYellow);
	colors.add(darkYellow);
	colors.add(darkerYellow);
	colors.add(orange);
	colors.add(lightOrange);
	colors.add(lighterOrange);
	colors.add(darkOrange);
	colors.add(darkerOrange);
	colors.add(red);
	colors.add(lightRed);
	colors.add(lighterRed);
	colors.add(darkRed);
	colors.add(darkerRed);
	colors.add(pink);
	colors.add(lightPink);
	colors.add(lighterPink);
	colors.add(darkPink);
	colors.add(darkerPink);
	colors.add(purple);
	colors.add(darkPurple);
	colors.add(darkerPurple);
	colors.add(lightPurple);
	colors.add(lighterPurple);
	colors.add(blue);
	colors.add(lightBlue);
	colors.add(lighterBlue);
	colors.add(darkBlue);
	colors.add(darkerBlue);
	colors.add(green);
	colors.add(lighterGreen);
	colors.add(lightGreen);
	colors.add(darkGreen);
	colors.add(darkerGreen);
	colors.add(aqua);
	colors.add(lighterAqua);
	colors.add(lightAqua);
	colors.add(darkAqua);
	colors.add(darkerAqua);
	colors.add(turquoise);
	colors.add(lighterTurquoise);
	colors.add(lightTurquoise);
	colors.add(darkTurquoise);
	colors.add(darkerTurquoise);
	colors.add(olive);
	colors.add(lighterOlive);
	colors.add(lightOlive);
	colors.add(darkOlive);
	colors.add(darkerOlive);
	colors.add(burgandy);
	colors.add(lighterBurgandy);
	colors.add(lightBurgandy);
	colors.add(darkBurgandy);
	colors.add(darkerBurgandy);
	colors.add(wine);

}


//==========================================================================================================================
BobColor* BobColor::getColorByName(string name)
{//==========================================================================================================================

	if (name == "" || name == "empty")return nullptr;
	for(int i=0;i<colors.size();i++)
	{
		BobColor *c = colors.get(i);

		if (c->name == name)return c;

	}
	return nullptr;


}


//=========================================================================================================================
BobColor::BobColor()
{//=========================================================================================================================
	name = "empty";

//	boost::uuids::random_generator generator;
//	uuid = to_string(generator());

}
////=========================================================================================================================
//BobColor::BobColor(BobColor* c)
//{//=========================================================================================================================
//	if (c != nullptr)
//	{
//		name = c->name;
//		r = c->ri();
//		g = c->gi();
//		b = c->bi();
//		a = c->ai();
//	}
//	else
//		log.error("Color c was null!");
//}
//
////=========================================================================================================================
//BobColor::BobColor(const BobColor &c)
//{//=========================================================================================================================
//
////	boost::uuids::random_generator generator;
////	uuid = to_string(generator());
//
//		name = c.name;
//		r = c.r;
//		g = c.g;
//		b = c.b;
//		a = c.a;
//
//}
//=========================================================================================================================
BobColor::BobColor(BobColor c, int ai)
{//=========================================================================================================================
//
//	boost::uuids::random_generator generator;
//	uuid = to_string(generator());

	name = c.name;
	r = c.ri();
	g = c.gi();
	b = c.bi();
	a = ai;

}


//=========================================================================================================================
BobColor::BobColor(BobColor c, float af)
{//=========================================================================================================================
//
//	boost::uuids::random_generator generator;
//	uuid = to_string(generator());

	name = c.name;
	r = c.ri();
	g = c.gi();
	b = c.bi();
	a = (int)(af * 255.0f);

}
//
////=========================================================================================================================
//BobColor::BobColor(BobColor c, float af)
//{//=========================================================================================================================
//	if (c != nullptr)
//	{
//		name = c.name;
//		r = c.ri();
//		g = c.gi();
//		b = c.bi();
//		a = (int)(af * 255.0f);
//	}
//	else
//		log.error("Color c was null!");
//}
//=========================================================================================================================
BobColor::BobColor(float rf, float gf, float bf)
{//=========================================================================================================================

//	boost::uuids::random_generator generator;
//	uuid = to_string(generator());

	r = (int)(rf * 255.0f);
	g = (int)(gf * 255.0f);
	b = (int)(bf * 255.0f);
	a = 255;
}


//=========================================================================================================================
BobColor::BobColor(float rf, float gf, float bf, float af)
{//=========================================================================================================================

//	boost::uuids::random_generator generator;
//	uuid = to_string(generator());

	r = (int)(rf * 255.0f);
	g = (int)(gf * 255.0f);
	b = (int)(bf * 255.0f);
	a = (int)(af * 255.0f);
}


//=========================================================================================================================
BobColor::BobColor(int ri, int gi, int bi)
{//=========================================================================================================================

//	boost::uuids::random_generator generator;
//	uuid = to_string(generator());

	r = ri;
	g = gi;
	b = bi;
	a = 255;
}


//=========================================================================================================================
BobColor::BobColor(int ri, int gi, int bi, int ai)
{//=========================================================================================================================
//
//	boost::uuids::random_generator generator;
//	uuid = to_string(generator());

	r = ri;
	g = gi;
	b = bi;
	a = ai;
}


//=========================================================================================================================
BobColor::BobColor(int rgb)
{//=========================================================================================================================

//	boost::uuids::random_generator generator;
//	uuid = to_string(generator());


	int ri = (rgb >> 16) & 0xFF;
	int gi = (rgb >> 8) & 0xFF;
	int bi = (rgb >> 0) & 0xFF;

	r = ri;
	g = gi;
	b = bi;
	a = 255;
}


//=========================================================================================================================
BobColor::BobColor(float hf, float sf, float bf, float af, bool hsbOverload)
{//=========================================================================================================================

//	boost::uuids::random_generator generator;
//	uuid = to_string(generator());

	int rgb = HSBtoRGB(hf, sf, bf);
	int ri = (rgb >> 16) & 0xFF;
	int gi = (rgb >> 8) & 0xFF;
	int bi = (rgb >> 0) & 0xFF;
	int ai = (int)(af * 255.0f);

	r = ri;
	g = gi;
	b = bi;
	a = ai;
}


//=========================================================================================================================
float BobColor::rf()
{//=========================================================================================================================
	return (float)(r / 255.0f);
}


//=========================================================================================================================
float BobColor::gf()
{//=========================================================================================================================
	return (float)(g / 255.0f);
}


//=========================================================================================================================
float BobColor::bf()
{//=========================================================================================================================
	return (float)(b / 255.0f);
}


//=========================================================================================================================
float BobColor::af()
{//=========================================================================================================================
	return (float)(a / 255.0f);
}


//=========================================================================================================================
int BobColor::ri()
{//=========================================================================================================================
	return r;
}


//=========================================================================================================================
int BobColor::gi()
{//=========================================================================================================================
	return g;
}


//=========================================================================================================================
int BobColor::bi()
{//=========================================================================================================================
	return b;
}


//=========================================================================================================================
int BobColor::ai()
{//=========================================================================================================================
	return a;
}


//=========================================================================================================================
float* BobColor::RGBtoHSB(int r, int g, int b)
{//=========================================================================================================================
	float hue, saturation, brightness;


	int cmax = (r > g) ? r : g;
	if (b > cmax)
	{
		cmax = b;
	}
	int cmin = (r < g) ? r : g;
	if (b < cmin)
	{
		cmin = b;
	}

	brightness = ((float)(cmax)) / 255.0f;
	if (cmax != 0)
	{
		saturation = ((float)(cmax - cmin)) / ((float)(cmax));
	}
	else
	{
		saturation = 0;
	}
	if (saturation == 0)
	{
		hue = 0;
	}
	else
	{
		float redc = ((float)(cmax - r)) / ((float)(cmax - cmin));
		float greenc = ((float)(cmax - g)) / ((float)(cmax - cmin));
		float bluec = ((float)(cmax - b)) / ((float)(cmax - cmin));
		if (r == cmax)
		{
			hue = bluec - greenc;
		}
		else if (g == cmax)
		{
			hue = 2.0f + redc - bluec;
		}
		else
		{
			hue = 4.0f + greenc - redc;
		}
		hue = hue / 6.0f;
		if (hue < 0)
		{
			hue = hue + 1.0f;
		}
	}

	float* hsbvals = new float[3];
	hsbvals[0] = hue;
	hsbvals[1] = saturation;
	hsbvals[2] = brightness;
	return hsbvals;
}


//=========================================================================================================================
int BobColor::HSBtoRGB(float hue, float saturation, float brightness)
{//=========================================================================================================================
	int r = 0, g = 0, b = 0;
	if (saturation == 0)
	{
		r = g = b = (int)(brightness * 255.0f + 0.5f);
	}
	else
	{
		float h = (hue - (float)(floor(hue))) * 6.0f;
		float f = h - (float)(floor(h));
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));
		switch ((int)(h))
		{
		case 0:
			r = (int)(brightness * 255.0f + 0.5f);
			g = (int)(t * 255.0f + 0.5f);
			b = (int)(p * 255.0f + 0.5f);
			break;
		case 1:
			r = (int)(q * 255.0f + 0.5f);
			g = (int)(brightness * 255.0f + 0.5f);
			b = (int)(p * 255.0f + 0.5f);
			break;
		case 2:
			r = (int)(p * 255.0f + 0.5f);
			g = (int)(brightness * 255.0f + 0.5f);
			b = (int)(t * 255.0f + 0.5f);
			break;
		case 3:
			r = (int)(p * 255.0f + 0.5f);
			g = (int)(q * 255.0f + 0.5f);
			b = (int)(brightness * 255.0f + 0.5f);
			break;
		case 4:
			r = (int)(t * 255.0f + 0.5f);
			g = (int)(p * 255.0f + 0.5f);
			b = (int)(brightness * 255.0f + 0.5f);
			break;
		case 5:
			r = (int)(brightness * 255.0f + 0.5f);
			g = (int)(p * 255.0f + 0.5f);
			b = (int)(q * 255.0f + 0.5f);
			break;
		}
	}

	unsigned int rs = static_cast<unsigned int>(r << 16);
	unsigned int gs = static_cast<unsigned int>(g << 8);
	unsigned int bs = static_cast<unsigned int>(b << 0);

	return (int)(0xff000000 | rs | gs | bs);
}


//=========================================================================================================================
void BobColor::darker()
{//=========================================================================================================================
	darker(0.4f);
}


//=========================================================================================================================
void BobColor::darker(float scale)
{//=========================================================================================================================
	scale = 1 - scale;

	float* hsbvals = RGBtoHSB(ri(), gi(), bi());


	//if already darkest increase saturation
	if (hsbvals[2] == 0.0f)
	{
		hsbvals[1] *= 1.0f / scale;
		if (hsbvals[1] > 1.0f)
		{
			hsbvals[1] = 1.0f;
		}
	}

	hsbvals[2] *= scale;
	if (hsbvals[2] < 0.0f)
	{
		hsbvals[2] = 0.0f;
	}

	int rgb = HSBtoRGB(hsbvals[0], hsbvals[1], hsbvals[2]);
	int ri = (rgb >> 16) & 0xFF;
	int gi = (rgb >> 8) & 0xFF;
	int bi = (rgb >> 0) & 0xFF;

	r = ri;
	g = gi;
	b = bi;
}


//=========================================================================================================================
void BobColor::lighter()
{//=========================================================================================================================

	//if(lighter!=null)return lighter;

	lighter(0.4f);
}


//=========================================================================================================================
void BobColor::lighter(float scale)
{//=========================================================================================================================

	if (scale < 1.0f)
	{
		scale += 1.0f;
	}


	float* hsbvals = RGBtoHSB(ri(), gi(), bi());

	//if already lightest, decrease saturation instead
	if (hsbvals[2] == 1.0f)
	{
		hsbvals[1] *= 1.0f / scale;
		if (hsbvals[1] < 0.0f)
		{
			hsbvals[1] = 0.0f;
		}
	}

	hsbvals[2] *= scale;
	if (hsbvals[2] > 1.0f)
	{
		hsbvals[2] = 1.0f;
	}

	int rgb = HSBtoRGB(hsbvals[0], hsbvals[1], hsbvals[2]);
	int ri = (rgb >> 16) & 0xFF;
	int gi = (rgb >> 8) & 0xFF;
	int bi = (rgb >> 0) & 0xFF;

	r = ri;
	g = gi;
	b = bi;
}

/*
void Color::multiply(Color *c)
{
   return new Color(rf() * c->rf(), gf() * c->gf(), bf() * c->bf(), af() * c->af());
}

void Color::addToCopy(Color *c)
{
   return new Color(rf() + c->rf(), gf() + c->gf(), bf() + c->bf(), af() + c->af());
}

void Color::scaleCopy(float value)
{
   return new Color(rf() * value, gf() * value, bf() * value, af() * value);
}
*/


int BobColor::rgbatoABGRInt(char r, char g, char b, char a)
{ //==========================================================================================================================
	return ((a << 15) + ((b) << 10) + ((g) << 5) + (r));
}

//int Color::HexToDec(const string &hexst)
//{ //===============================================================================================
//   return int::valueOf(hexst, 16);
//}

int BobColor::DecToRed(int dec)
{ //===============================================================================================
	return (dec % 32) * 8;
}

int BobColor::DecToGreen(int dec)
{ //===============================================================================================
	return ((dec / 32) % 32) * 8;
}

int BobColor::DecToBlue(int dec)
{ //===============================================================================================
	return (dec / 1024) * 8;
}

//==========================================================================================================================
int BobColor::getRGB()
{//==========================================================================================================================
	return ((1 << 15) + (ri()) + ((gi()) << 5) + ((bi()) << 10));
}
