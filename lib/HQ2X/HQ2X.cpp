#include "stdafx.h"



#include "HQ2X.h"

//#pragma once
#include "../../src/main.h"

unsigned char* HQ2X::LUT16to32;
unsigned char* HQ2X::RGBtoYUV;

bool HQ2X::lutsOk = false;

int HQ2X::Interp1(int c1, int c2)
{
	return ((c1 * 3 + c2) >> 2) | 0xFF000000;
}

int HQ2X::Interp2(int c1, int c2, int c3)
{
	return ((c1 * 2 + c2 + c3) >> 2) | 0xFF000000;
}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("unused") private int Interp5(int c1, int c2)
int HQ2X::Interp5(int c1, int c2)
{
	return ((c1 + c2) >> 1) | 0xFF000000;
}

int HQ2X::Interp6(int c1, int c2, int c3)
{
	return (((((c1 & 0x00FF00) * 5 + (c2 & 0x00FF00) * 2 + (c3 & 0x00FF00)) & 0x0007F800) + (((c1 & 0xFF00FF) * 5 + (c2 & 0xFF00FF) * 2 + (c3 & 0xFF00FF)) & 0x07F807F8)) >> 3) | 0xFF000000;
}

int HQ2X::Interp7(int c1, int c2, int c3)
{
	return (((((c1 & 0x00FF00) * 6 + (c2 & 0x00FF00) + (c3 & 0x00FF00)) & 0x0007F800) + (((c1 & 0xFF00FF) * 6 + (c2 & 0xFF00FF) + (c3 & 0xFF00FF)) & 0x07F807F8)) >> 3) | 0xFF000000;
}

int HQ2X::Interp9(int c1, int c2, int c3)
{
	return (((((c1 & 0x00FF00) * 2 + ((c2 & 0x00FF00) + (c3 & 0x00FF00)) * 3) & 0x0007F800) + (((c1 & 0xFF00FF) * 2 + ((c2 & 0xFF00FF) + (c3 & 0xFF00FF)) * 3) & 0x07F807F8)) >> 3) | 0xFF000000;
}

int HQ2X::Interp10(int c1, int c2, int c3)
{
	return (((((c1 & 0x00FF00) * 14 + (c2 & 0x00FF00) + (c3 & 0x00FF00)) & 0x000FF000) + (((c1 & 0xFF00FF) * 14 + (c2 & 0xFF00FF) + (c3 & 0xFF00FF)) & 0x0FF00FF0)) >> 4) | 0xFF000000;
}

bool HQ2X::Diff(int w1, int w2)
{
	YUV1 = RGBtoYUV[w1];
	YUV2 = RGBtoYUV[w2];
	return ((abs((YUV1 & Ymask) - (YUV2 & Ymask)) > trY) || (abs((YUV1 & Umask) - (YUV2 & Umask)) > trU) || (abs((YUV1 & Vmask) - (YUV2 & Vmask)) > trV));
}

void HQ2X::hq2x_32(unsigned char* in, unsigned char* out, int Xres, int Yres)
{
	int i, j, k;
	int outX = 0;
	int outY = 0;
	int prevline, nextline;
	int* w = new int[(10)];
	int* c = new int[(10)];

	//   +----+----+----+
	//   |    |    |    |
	//   | w1 | w2 | w3 |
	//   +----+----+----+
	//   |    |    |    |
	//   | w4 | w5 | w6 |
	//   +----+----+----+
	//   |    |    |    |
	//   | w7 | w8 | w9 |
	//   +----+----+----+

	for (j = 0; j < Yres; j++)
	{
		if (j > 0)
		{
			prevline = -1;
		}
		else
		{
			prevline = 0;
		}
		if (j < Yres - 1)
		{
			nextline = 1;
		}
		else
		{
			nextline = 0;
		}

		outX = 0;

		for (i = 0; i < Xres; i++)
		{
			w[2] = RGB8888toRGB565(in[i + (j + prevline) * Xres]);
			w[5] = RGB8888toRGB565(in[i + j * Xres]);
			w[8] = RGB8888toRGB565(in[i + (j + nextline) * Xres]);

			if (i > 0)
			{
				w[1] = RGB8888toRGB565(in[i - 1 + (j + prevline) * Xres]);
				w[4] = RGB8888toRGB565(in[i - 1 + j * Xres]);
				w[7] = RGB8888toRGB565(in[i - 1 + (j + nextline) * Xres]);
			}
			else
			{
				w[1] = w[2];
				w[4] = w[5];
				w[7] = w[8];
			}

			if (i < Xres - 1)
			{
				w[3] = RGB8888toRGB565(in[i + 1 + (j + prevline) * Xres]);
				w[6] = RGB8888toRGB565(in[i + 1 + j * Xres]);
				w[9] = RGB8888toRGB565(in[i + 1 + (j + nextline) * Xres]);
			}
			else
			{
				w[3] = w[2];
				w[6] = w[5];
				w[9] = w[8];
			}

			int pattern = 0;
			int flag = 1;

			YUV1 = RGBtoYUV[w[5]];

			for (k = 1; k <= 9; k++)
			{
				if (k == 5)
				{
					continue;
				}

				if (w[k] != w[5])
				{
					YUV2 = RGBtoYUV[w[k]];
					if ((abs((YUV1 & Ymask) - (YUV2 & Ymask)) > trY) || (abs((YUV1 & Umask) - (YUV2 & Umask)) > trU) || (abs((YUV1 & Vmask) - (YUV2 & Vmask)) > trV))
					{
						pattern |= flag;
					}
				}
				flag <<= 1;
			}

			for (k = 1; k <= 9; k++)
			{
				c[k] = LUT16to32[w[k]];
			}

			switch (pattern)
			{
			case 0:
			case 1:
			case 4:
			case 32:
			case 128:
			case 5:
			case 132:
			case 160:
			case 33:
			case 129:
			case 36:
			case 133:
			case 164:
			case 161:
			case 37:
			case 165:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					break;
				}
			case 2:
			case 34:
			case 130:
			case 162:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					break;
				}
			case 16:
			case 17:
			case 48:
			case 49:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 64:
			case 65:
			case 68:
			case 69:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 8:
			case 12:
			case 136:
			case 140:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					break;
				}
			case 3:
			case 35:
			case 131:
			case 163:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					break;
				}
			case 6:
			case 38:
			case 134:
			case 166:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					break;
				}
			case 20:
			case 21:
			case 52:
			case 53:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 144:
			case 145:
			case 176:
			case 177:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 192:
			case 193:
			case 196:
			case 197:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 96:
			case 97:
			case 100:
			case 101:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 40:
			case 44:
			case 168:
			case 172:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					break;
				}
			case 9:
			case 13:
			case 137:
			case 141:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					break;
				}
			case 18:
			case 50:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 80:
			case 81:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					}
					break;
				}
			case 72:
			case 76:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 10:
			case 138:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					break;
				}
			case 66:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 24:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 7:
			case 39:
			case 135:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					break;
				}
			case 148:
			case 149:
			case 180:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 224:
			case 228:
			case 225:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 41:
			case 169:
			case 45:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					break;
				}
			case 22:
			case 54:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 208:
			case 209:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					}
					break;
				}
			case 104:
			case 108:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 11:
			case 139:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					break;
				}
			case 19:
			case 51:
				{
					if (Diff(w[2], w[6]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp6(c[5], c[2], c[4]);
						out[outX + 1 + outY * Xres * 2] = Interp9(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 146:
			case 178:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp9(c[5], c[2], c[6]);
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp6(c[5], c[6], c[8]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					break;
				}
			case 84:
			case 85:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp6(c[5], c[6], c[2]);
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp9(c[5], c[6], c[8]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					break;
				}
			case 112:
			case 113:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					if (Diff(w[6], w[8]))
					{
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp6(c[5], c[8], c[4]);
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp9(c[5], c[6], c[8]);
					}
					break;
				}
			case 200:
			case 204:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp9(c[5], c[8], c[4]);
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp6(c[5], c[8], c[6]);
					}
					break;
				}
			case 73:
			case 77:
				{
					if (Diff(w[8], w[4]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp6(c[5], c[4], c[2]);
						out[outX + (outY + 1) * Xres * 2] = Interp9(c[5], c[8], c[4]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 42:
			case 170:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp9(c[5], c[4], c[2]);
						out[outX + (outY + 1) * Xres * 2] = Interp6(c[5], c[4], c[8]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					break;
				}
			case 14:
			case 142:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp9(c[5], c[4], c[2]);
						out[outX + 1 + outY * Xres * 2] = Interp6(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					break;
				}
			case 67:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 70:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 28:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 152:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 194:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 98:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 56:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 25:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 26:
			case 31:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					}
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 82:
			case 214:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					}
					break;
				}
			case 88:
			case 248:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					}
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					}
					break;
				}
			case 74:
			case 107:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 27:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 86:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					break;
				}
			case 216:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					}
					break;
				}
			case 106:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 30:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 210:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					}
					break;
				}
			case 120:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					break;
				}
			case 75:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 29:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 198:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 184:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 99:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 57:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 71:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 156:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 226:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 60:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 195:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 102:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 153:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 58:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp7(c[5], c[4], c[2]);
					}
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp7(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 83:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp7(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp7(c[5], c[6], c[8]);
					}
					break;
				}
			case 92:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp7(c[5], c[8], c[4]);
					}
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp7(c[5], c[6], c[8]);
					}
					break;
				}
			case 202:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp7(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp7(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 78:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp7(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp7(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 154:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp7(c[5], c[4], c[2]);
					}
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp7(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 114:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp7(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp7(c[5], c[6], c[8]);
					}
					break;
				}
			case 89:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp7(c[5], c[8], c[4]);
					}
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp7(c[5], c[6], c[8]);
					}
					break;
				}
			case 90:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp7(c[5], c[4], c[2]);
					}
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp7(c[5], c[2], c[6]);
					}
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp7(c[5], c[8], c[4]);
					}
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp7(c[5], c[6], c[8]);
					}
					break;
				}
			case 55:
			case 23:
				{
					if (Diff(w[2], w[6]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp6(c[5], c[2], c[4]);
						out[outX + 1 + outY * Xres * 2] = Interp9(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 182:
			case 150:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp9(c[5], c[2], c[6]);
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp6(c[5], c[6], c[8]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					break;
				}
			case 213:
			case 212:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp6(c[5], c[6], c[2]);
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp9(c[5], c[6], c[8]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					break;
				}
			case 241:
			case 240:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					if (Diff(w[6], w[8]))
					{
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp6(c[5], c[8], c[4]);
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp9(c[5], c[6], c[8]);
					}
					break;
				}
			case 236:
			case 232:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp9(c[5], c[8], c[4]);
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp6(c[5], c[8], c[6]);
					}
					break;
				}
			case 109:
			case 105:
				{
					if (Diff(w[8], w[4]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp6(c[5], c[4], c[2]);
						out[outX + (outY + 1) * Xres * 2] = Interp9(c[5], c[8], c[4]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 171:
			case 43:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp9(c[5], c[4], c[2]);
						out[outX + (outY + 1) * Xres * 2] = Interp6(c[5], c[4], c[8]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					break;
				}
			case 143:
			case 15:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp9(c[5], c[4], c[2]);
						out[outX + 1 + outY * Xres * 2] = Interp6(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					break;
				}
			case 124:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					break;
				}
			case 203:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 62:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 211:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					}
					break;
				}
			case 118:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					break;
				}
			case 217:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					}
					break;
				}
			case 110:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 155:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 188:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 185:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 61:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 157:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 103:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 227:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 230:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 199:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 220:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp7(c[5], c[8], c[4]);
					}
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					}
					break;
				}
			case 158:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp7(c[5], c[4], c[2]);
					}
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 234:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp7(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 242:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp7(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					}
					break;
				}
			case 59:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					}
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp7(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 121:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					}
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp7(c[5], c[6], c[8]);
					}
					break;
				}
			case 87:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp7(c[5], c[6], c[8]);
					}
					break;
				}
			case 79:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp7(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 122:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp7(c[5], c[4], c[2]);
					}
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp7(c[5], c[2], c[6]);
					}
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					}
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp7(c[5], c[6], c[8]);
					}
					break;
				}
			case 94:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp7(c[5], c[4], c[2]);
					}
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					}
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp7(c[5], c[8], c[4]);
					}
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp7(c[5], c[6], c[8]);
					}
					break;
				}
			case 218:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp7(c[5], c[4], c[2]);
					}
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp7(c[5], c[2], c[6]);
					}
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp7(c[5], c[8], c[4]);
					}
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					}
					break;
				}
			case 91:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					}
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp7(c[5], c[2], c[6]);
					}
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp7(c[5], c[8], c[4]);
					}
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp7(c[5], c[6], c[8]);
					}
					break;
				}
			case 229:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 167:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					break;
				}
			case 173:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					break;
				}
			case 181:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 186:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp7(c[5], c[4], c[2]);
					}
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp7(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 115:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp7(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp7(c[5], c[6], c[8]);
					}
					break;
				}
			case 93:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp7(c[5], c[8], c[4]);
					}
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp7(c[5], c[6], c[8]);
					}
					break;
				}
			case 206:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp7(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp7(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 205:
			case 201:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp7(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 174:
			case 46:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp7(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					break;
				}
			case 179:
			case 147:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp7(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 117:
			case 116:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp7(c[5], c[6], c[8]);
					}
					break;
				}
			case 189:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 231:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 126:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					}
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					break;
				}
			case 219:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					}
					break;
				}
			case 125:
				{
					if (Diff(w[8], w[4]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp6(c[5], c[4], c[2]);
						out[outX + (outY + 1) * Xres * 2] = Interp9(c[5], c[8], c[4]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					break;
				}
			case 221:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp6(c[5], c[6], c[2]);
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp9(c[5], c[6], c[8]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					break;
				}
			case 207:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
						out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp9(c[5], c[4], c[2]);
						out[outX + 1 + outY * Xres * 2] = Interp6(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 238:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp9(c[5], c[8], c[4]);
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp6(c[5], c[8], c[6]);
					}
					break;
				}
			case 190:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp9(c[5], c[2], c[6]);
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp6(c[5], c[6], c[8]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 187:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp9(c[5], c[4], c[2]);
						out[outX + (outY + 1) * Xres * 2] = Interp6(c[5], c[4], c[8]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 243:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					if (Diff(w[6], w[8]))
					{
						out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp6(c[5], c[8], c[4]);
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp9(c[5], c[6], c[8]);
					}
					break;
				}
			case 119:
				{
					if (Diff(w[2], w[6]))
					{
						out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp6(c[5], c[2], c[4]);
						out[outX + 1 + outY * Xres * 2] = Interp9(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					break;
				}
			case 237:
			case 233:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp10(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 175:
			case 47:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp10(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					break;
				}
			case 183:
			case 151:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp10(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 245:
			case 244:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp10(c[5], c[6], c[8]);
					}
					break;
				}
			case 250:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					}
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					}
					break;
				}
			case 123:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					break;
				}
			case 95:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					}
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					break;
				}
			case 222:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					}
					break;
				}
			case 252:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					}
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp10(c[5], c[6], c[8]);
					}
					break;
				}
			case 249:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[2]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp10(c[5], c[8], c[4]);
					}
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					}
					break;
				}
			case 235:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[3], c[6]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp10(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 111:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp10(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[6]);
					break;
				}
			case 63:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp10(c[5], c[4], c[2]);
					}
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[9], c[8]);
					break;
				}
			case 159:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					}
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp10(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 215:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp10(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[7], c[4]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					}
					break;
				}
			case 246:
				{
					out[outX + outY * Xres * 2] = Interp2(c[5], c[1], c[4]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp10(c[5], c[6], c[8]);
					}
					break;
				}
			case 254:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[1]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					}
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					}
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp10(c[5], c[6], c[8]);
					}
					break;
				}
			case 253:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[2]);
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[2]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp10(c[5], c[8], c[4]);
					}
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp10(c[5], c[6], c[8]);
					}
					break;
				}
			case 251:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[3]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp10(c[5], c[8], c[4]);
					}
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					}
					break;
				}
			case 239:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp10(c[5], c[4], c[2]);
					}
					out[outX + 1 + outY * Xres * 2] = Interp1(c[5], c[6]);
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp10(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[6]);
					break;
				}
			case 127:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp10(c[5], c[4], c[2]);
					}
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp2(c[5], c[2], c[6]);
					}
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp2(c[5], c[8], c[4]);
					}
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[9]);
					break;
				}
			case 191:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp10(c[5], c[4], c[2]);
					}
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp10(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					out[outX + 1 + (outY + 1) * Xres * 2] = Interp1(c[5], c[8]);
					break;
				}
			case 223:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp2(c[5], c[4], c[2]);
					}
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp10(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[7]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp2(c[5], c[6], c[8]);
					}
					break;
				}
			case 247:
				{
					out[outX + outY * Xres * 2] = Interp1(c[5], c[4]);
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp10(c[5], c[2], c[6]);
					}
					out[outX + (outY + 1) * Xres * 2] = Interp1(c[5], c[4]);
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp10(c[5], c[6], c[8]);
					}
					break;
				}
			case 255:
				{
					if (Diff(w[4], w[2]))
					{
						out[outX + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + outY * Xres * 2] = Interp10(c[5], c[4], c[2]);
					}
					if (Diff(w[2], w[6]))
					{
						out[outX + 1 + outY * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + outY * Xres * 2] = Interp10(c[5], c[2], c[6]);
					}
					if (Diff(w[8], w[4]))
					{
						out[outX + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + (outY + 1) * Xres * 2] = Interp10(c[5], c[8], c[4]);
					}
					if (Diff(w[6], w[8]))
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = c[5] | 0xFF000000;
					}
					else
					{
						out[outX + 1 + (outY + 1) * Xres * 2] = Interp10(c[5], c[6], c[8]);
					}
					break;
				}
			}
			outX += 2;
		}
		outY += 2;
	}
}

void HQ2X::InitLUTs()
{
	int i, j, k, r, g, b, Y, u, v;

	for (i = 0; i < 65536; i++)
	{
		LUT16to32[i] = ((i & 0xF800) << 8) + ((i & 0x07E0) << 5) + ((i & 0x001F) << 3);
	}

	for (i = 0; i < 32; i++)
	{
		for (j = 0; j < 64; j++)
		{
			for (k = 0; k < 32; k++)
			{
				r = i << 3;
				g = j << 2;
				b = k << 3;
				Y = (r + g + b) >> 2;
				u = 128 + ((r - b) >> 2);
				v = 128 + ((-r + 2 * g - b) >> 3);
				RGBtoYUV[(i << 11) + (j << 5) + k] = (Y << 16) + (u << 8) + v;
			}
		}
	}
	lutsOk = true;
}

int HQ2X::RGB8888toRGB565(int rgb)
{
	return ((rgb & 0x00F80000) >> 8) | ((rgb & 0x0000FC00) >> 5) | ((rgb & 0x000000F8) >> 3);
}

BufferedImage* HQ2X::hq2x(BufferedImage* image)// unsigned char* inArr, int w, int h)
{
	unsigned char* inArr = image->getData();
	int w = image->getWidth();
	int h = image->getHeight();


	//in = removeAlpha(in);

	//		int w = in->getWidth();
	//		int h = in->getHeight();

	//int x = w * 2;
	//int y = h * 2;
	//unsigned char * inArr = new unsigned char[(w*h)];
	unsigned char* outArr = new unsigned char[((w * 2) * (h * 2)) * 4];

	//in->getRGB(0, 0, w, h, inArr, 0, w);

	if (!lutsOk)
	{
		LUT16to32 = new unsigned char[(65536)];
		RGBtoYUV = new unsigned char[(65536)];
		InitLUTs();
	}

	hq2x_32(inArr, outArr, w, h);

	//inArr->clear();

	//System.runFinalization();
	//System.gc();

	//unsigned char *out = new unsigned char[((w * 2) * (h * 2)) * 4];// (w * 2, h * 2, BufferedImage::TYPE_INT_ARGB);
	//out->setRGB(0, 0, x, y, outArr, 0, x);

	// out = addAlpha(out);

	return new BufferedImage(outArr, w, h);
}

//	vector<int> HQ2X::hq2x(vector<int> &rgbIntArray, int w, int h)
//	{
//
//		//in = removeAlpha(in);
//
//
//		//int x = w*2;
//		//int y = h*2;
//
//		vector<int> outArr(w*h*4);
//
//
//
//		if (!lutsOk)
//		{
//			LUT16to32 = vector<int>(65536);
//			RGBtoYUV = vector<int>(65536);
//			InitLUTs();
//		}
//
//		hq2x_32(rgbIntArray, outArr, w, h);
//
//		//inArr=null;
//
//		//System.runFinalization();
//		//System.gc();
//
//		//BufferedImage out = new BufferedImage(w*2, h*2, BufferedImage.TYPE_INT_ARGB);
//		//out.setRGB(0, 0, x, y, outArr, 0, x);
//
//		//out = addAlpha(out);
//
//		return outArr;
//	}
//


