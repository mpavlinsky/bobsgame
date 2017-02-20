#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------





Logger BobFont::log = Logger("BobFont");


TTF_Font* BobFont::ttf_bobsgame_8 = nullptr;
TTF_Font* BobFont::ttf_bobsgame_16 = nullptr;
TTF_Font* BobFont::ttf_oswald_8 = nullptr;
TTF_Font* BobFont::ttf_oswald_10 = nullptr;
TTF_Font* BobFont::ttf_oswald_12 = nullptr;
TTF_Font* BobFont::ttf_oswald_16 = nullptr;
TTF_Font* BobFont::ttf_oswald_24 = nullptr;
TTF_Font* BobFont::ttf_oswald_32 = nullptr;
TTF_Font* BobFont::ttf_oswald_48 = nullptr;
TTF_Font* BobFont::ttf_oswald_64 = nullptr;



BobFont* BobFont::font_32 = nullptr;
BobFont* BobFont::font_bob_16 = nullptr;
BobFont* BobFont::font_bob_16_shadow2 = nullptr;
BobFont* BobFont::font_bob_8 = nullptr;
BobFont* BobFont::font_bob_8_shadow1 = nullptr;
BobFont* BobFont::font_normal_11 = nullptr;
BobFont* BobFont::font_normal_11_outlined = nullptr;
BobFont* BobFont::font_normal_11_shadow1 = nullptr;
BobFont* BobFont::font_normal_16 = nullptr;
BobFont* BobFont::font_normal_16_outlined_smooth = nullptr;
BobFont* BobFont::font_normal_16_outlined_blocky = nullptr;
BobFont* BobFont::font_normal_16_outlined_blocky_shadow1 = nullptr;
BobFont* BobFont::font_normal_16_shadow1 = nullptr;
BobFont* BobFont::font_normal_8 = nullptr;
BobFont* BobFont::font_normal_8_outlined = nullptr;
BobFont* BobFont::font_normal_8_outlined_shadow1 = nullptr;
BobFont* BobFont::font_normal_8_outlined_shadow2 = nullptr;
BobFont* BobFont::font_normal_8_shadow1 = nullptr;
BobFont* BobFont::font_normal_8_shadow3 = nullptr;
BobFont* BobFont::font_small_16 = nullptr;
BobFont* BobFont::font_small_16_shadow3 = nullptr;
BobFont* BobFont::font_small_16_outlined_smooth = nullptr;
BobFont* BobFont::font_small_16_outlined_smooth_shadow = nullptr;
BobFont* BobFont::font_small_16_outlined_blocky = nullptr;
BobFont* BobFont::font_small_8 = nullptr;
BobFont* BobFont::font_small_8_outlined = nullptr;
BobFont* BobFont::font_small_8_shadow1 = nullptr;

//=========================================================================================================================
BobFont::BobFont(const string& filename, int maxCharHeight, int blockHeight, bool outlined)
{//=========================================================================================================================


	this->filename = filename;
	this->maxCharHeight = maxCharHeight;
	this->blockHeight = blockHeight;
	this->outlined = outlined;
	//this.blockWidth = blockWidth;

	byteArray = FileUtils::loadByteFileFromExePath(filename);
}


//=========================================================================================================================
void BobFont::initFonts()
{//=========================================================================================================================


 //-----------------------------
 //init TTF
 //-----------------------------
	TTF_Init();
	string path = Main::getPath();
	ttf_bobsgame_8 = TTF_OpenFont(string(path+"data/fonts/bobsgame.ttf").c_str(), 8);
	ttf_bobsgame_16 = TTF_OpenFont(string(path + "data/fonts/bobsgame.ttf").c_str(), 16);
	ttf_oswald_8 = TTF_OpenFont(string(path + "data/fonts/OpenSans-Bold.ttf").c_str(), 8);
	ttf_oswald_10 = TTF_OpenFont(string(path + "data/fonts/OpenSans-Bold.ttf").c_str(), 10);
	ttf_oswald_12 = TTF_OpenFont(string(path+"data/fonts/OpenSans-Bold.ttf").c_str(), 12);
	ttf_oswald_16 = TTF_OpenFont(string(path+"data/fonts/OpenSans-Bold.ttf").c_str(), 16);
	ttf_oswald_24 = TTF_OpenFont(string(path+"data/fonts/OpenSans-Bold.ttf").c_str(), 24);
	ttf_oswald_32 = TTF_OpenFont(string(path+"data/fonts/OpenSans-Bold.ttf").c_str(), 32);
	ttf_oswald_48 = TTF_OpenFont(string(path+"data/fonts/OpenSans-Bold.ttf").c_str(), 48);
	ttf_oswald_64 = TTF_OpenFont(string(path+"data/fonts/OpenSans-Bold.ttf").c_str(), 64);


	

	//FreeTypeFontGenerator *generator = new FreeTypeFontGenerator(Gdx::files::internal("fonts/OpenSans-Regular.ttf"));
	//BitmapFont *font12 = generator->generateFont(12); // font size 12 pixels
	//BitmapFont *font25 = generator->generateFont(25); // font size 25 pixels
	//generator->dispose(); // don't forget to dispose to avoid memory leaks!


	//font12.draw(batch,str,x,y);


	font_Palette_ByteArray = FileUtils::loadByteFileFromExePath("data/fonts/text.pal");// "assets/fonts/getText.pal");


	//fontTinyByteArray = FileUtils::HARDWARE_load_file("assets/fonts/font_tiny.bin");
	//fontHugeByteArray = FileUtils::HARDWARE_load_file("assets/fonts/font_huge.bin");


	font_32 = new BobFont("data/fonts/font_32.bin", 32, 64, false);
	font_32->blockWidth = 64;

	font_bob_16 = new BobFont("data/fonts/font_bob_16_hq2x.bin", 36, 32, false); //fix height
	font_bob_16_shadow2 = new BobFont("data/fonts/font_bob_16_hq2x_shadow2.bin", 38, 32, false); //fix height

	font_bob_8 = new BobFont("data/fonts/font_bob_8.bin", 20, 16, false); //fix height
	font_bob_8_shadow1 = new BobFont("data/fonts/font_bob_8_shadow1.bin", 22, 16, false); //fix height

	font_normal_11 = new BobFont("data/fonts/font_normal_11.bin", 15, 24, false);
	font_normal_11_outlined = new BobFont("data/fonts/font_normal_11_outlined.bin", 17, 24, true);
	font_normal_11_shadow1 = new BobFont("data/fonts/font_normal_11_shadow1.bin", 16, 24, false);

	font_normal_16 = new BobFont("data/fonts/font_normal_16_hq2x.bin", 20, 32, false);
	font_normal_16_outlined_smooth = new BobFont("data/fonts/font_normal_16_hq2x_outlined.bin", 22, 32, true);
	font_normal_16_outlined_blocky = new BobFont("data/fonts/font_normal_16_nearest2x_outlined.bin", 22, 32, true);
	font_normal_16_outlined_blocky_shadow1 = new BobFont("data/fonts/font_normal_16_nearest2x_outlined_shadow1.bin", 23, 32, true);
	font_normal_16_shadow1 = new BobFont("data/fonts/font_normal_16_hq2x_shadow.bin", 22, 32, false);

	font_normal_8 = new BobFont("data/fonts/font_normal_8.bin", 10, 16, false);
	font_normal_8_outlined = new BobFont("data/fonts/font_normal_8_outlined.bin", 12, 16, true);
	font_normal_8_outlined_shadow1 = new BobFont("data/fonts/font_normal_8_outlined_shadow1.bin", 13, 16, true);
	font_normal_8_outlined_shadow2 = new BobFont("data/fonts/font_normal_8_outlined_shadow2.bin", 14, 16, true);
	font_normal_8_shadow1 = new BobFont("data/fonts/font_normal_8_shadow1.bin", 11, 16, false);
	font_normal_8_shadow3 = new BobFont("data/fonts/font_normal_8_shadow3.bin", 13, 16, false);

	font_small_16 = new BobFont("data/fonts/font_small_16_hq2x.bin", 18, 32, false);
	font_small_16_shadow3 = new BobFont("data/fonts/font_small_16_hq2x_shadow3.bin", 20, 32, false);
	font_small_16_outlined_smooth = new BobFont("data/fonts/font_small_16_hq2x_outlined.bin", 20, 32, true);
	font_small_16_outlined_smooth_shadow = new BobFont("data/fonts/font_small_16_hq2x_outlined_shadow2.bin", 20, 32, true);
	font_small_16_outlined_blocky = new BobFont("data/fonts/font_small_16_nearest2x_outlined.bin", 20, 32, true);

	font_small_8 = new BobFont("data/fonts/font_small_8.bin", 9, 16, false);
	font_small_8_outlined = new BobFont("data/fonts/font_small_8_outlined.bin", 11, 16, true);
	font_small_8_shadow1 = new BobFont("data/fonts/font_small_8_shadow1.bin", 10, 16, false);
}


//=========================================================================================================================
void BobFont::cleanup()
{//=========================================================================================================================

	TTF_CloseFont(ttf_bobsgame_8);
	TTF_CloseFont(ttf_bobsgame_16);


}




//=========================================================================================================================
void BobFont::change_font()
{//=========================================================================================================================
}


//=========================================================================================================================
bool BobFont::is_a_vowel(char c)
{//=========================================================================================================================

	switch (c)
	{
	case 'a':
	case 'e':
	case 'i':
	case 'o':
	case 'u':
	case 'y':
	case 'A':
	case 'E':
	case 'I':
	case 'O':
	case 'U':
	case 'Y':
		return true;
	default:
		return false;
	}
}


//=========================================================================================================================
int BobFont::getFontIndexForChar(char c)
{//=========================================================================================================================
	int i = -1;
	switch (c)
	{
	case 'A':
		{
			i = CHAR_A;
			break;
		}
	case 'B':
		{
			i = CHAR_B;
			break;
		}
	case 'C':
		{
			i = CHAR_C;
			break;
		}
	case 'D':
		{
			i = CHAR_D;
			break;
		}
	case 'E':
		{
			i = CHAR_E;
			break;
		}
	case 'F':
		{
			i = CHAR_F;
			break;
		}
	case 'G':
		{
			i = CHAR_G;
			break;
		}
	case 'H':
		{
			i = CHAR_H;
			break;
		}
	case 'I':
		{
			i = CHAR_I;
			break;
		}
	case 'J':
		{
			i = CHAR_J;
			break;
		}
	case 'K':
		{
			i = CHAR_K;
			break;
		}
	case 'L':
		{
			i = CHAR_L;
			break;
		}
	case 'M':
		{
			i = CHAR_M;
			break;
		}
	case 'N':
		{
			i = CHAR_N;
			break;
		}
	case 'O':
		{
			i = CHAR_O;
			break;
		}
	case 'P':
		{
			i = CHAR_P;
			break;
		}
	case 'Q':
		{
			i = CHAR_Q;
			break;
		}
	case 'R':
		{
			i = CHAR_R;
			break;
		}
	case 'S':
		{
			i = CHAR_S;
			break;
		}
	case 'T':
		{
			i = CHAR_T;
			break;
		}
	case 'U':
		{
			i = CHAR_U;
			break;
		}
	case 'V':
		{
			i = CHAR_V;
			break;
		}
	case 'W':
		{
			i = CHAR_W;
			break;
		}
	case 'X':
		{
			i = CHAR_X;
			break;
		}
	case 'Y':
		{
			i = CHAR_Y;
			break;
		}
	case 'Z':
		{
			i = CHAR_Z;
			break;
		}
	case 'a':
		{
			i = CHAR_a;
			break;
		}
	case 'b':
		{
			i = CHAR_b;
			break;
		}
	case 'c':
		{
			i = CHAR_c;
			break;
		}
	case 'd':
		{
			i = CHAR_d;
			break;
		}
	case 'e':
		{
			i = CHAR_e;
			break;
		}
	case 'f':
		{
			i = CHAR_f;
			break;
		}
	case 'g':
		{
			i = CHAR_g;
			break;
		}
	case 'h':
		{
			i = CHAR_h;
			break;
		}
	case 'i':
		{
			i = CHAR_i;
			break;
		}
	case 'j':
		{
			i = CHAR_j;
			break;
		}
	case 'k':
		{
			i = CHAR_k;
			break;
		}
	case 'l':
		{
			i = CHAR_l;
			break;
		}
	case 'm':
		{
			i = CHAR_m;
			break;
		}
	case 'n':
		{
			i = CHAR_n;
			break;
		}
	case 'o':
		{
			i = CHAR_o;
			break;
		}
	case 'p':
		{
			i = CHAR_p;
			break;
		}
	case 'q':
		{
			i = CHAR_q;
			break;
		}
	case 'r':
		{
			i = CHAR_r;
			break;
		}
	case 's':
		{
			i = CHAR_s;
			break;
		}
	case 't':
		{
			i = CHAR_t;
			break;
		}
	case 'u':
		{
			i = CHAR_u;
			break;
		}
	case 'v':
		{
			i = CHAR_v;
			break;
		}
	case 'w':
		{
			i = CHAR_w;
			break;
		}
	case 'x':
		{
			i = CHAR_x;
			break;
		}
	case 'y':
		{
			i = CHAR_y;
			break;
		}
	case 'z':
		{
			i = CHAR_z;
			break;
		}
	case '.':
		{
			i = CHAR_PERIOD;
			break;
		}
	case ',':
		{
			i = CHAR_COMMA;
			break;
		}
	case '\'':
		{
			i = CHAR_QUOTE;
			break;
		} // /'
		//   case '�':
		//      {
		//         i = CHAR_QUOTE;
		//         break;
		//      } // /'
	case '!':
		{
			i = CHAR_EXCLAMATION;
			break;
		}


		/*
		case '?':
		{
		   i = CHAR_QUESTIONMARK;
		   break;
		}
		*/


	case '=':
		{
			i = CHAR_EQUALS;
			break;
		}
	case '\\':
		{
			i = CHAR_BACKSLASH;
			break;
		}
	case '/':
		{
			i = CHAR_FRONTSLASH;
			break;
		}
	case '^':
		{
			i = CHAR_CARET;
			break;
		}
	case '_':
		{
			i = CHAR_UNDERSCORE;
			break;
		}
	case '&':
		{
			i = CHAR_AMPERSAND;
			break;
		}
	case '+':
		{
			i = CHAR_PLUS;
			break;
		}
	case '#':
		{
			i = CHAR_POUND;
			break;
		}
	case '$':
		{
			i = CHAR_DOLLAR;
			break;
		}
	case '%':
		{
			i = CHAR_PERCENT;
			break;
		}
	case '(':
		{
			i = CHAR_OPENPARENTHESIS;
			break;
		}
	case ')':
		{
			i = CHAR_CLOSEPARENTHESIS;
			break;
		}
	case '"':
		{
			i = CHAR_DOUBLEQUOTE;
			break;
		}
	case '*':
		{
			i = CHAR_ASTERISK;
			break;
		}
	case '-':
		{
			i = CHAR_MINUS;
			break;
		}
	case ':':
		{
			i = CHAR_COLON;
			break;
		}
	case ';':
		{
			i = CHAR_SEMICOLON;
			break;
		}
	case '|':
		{
			i = CHAR_PIPE;
			break;
		}
	case '`':
		{
			i = CHAR_BACKQUOTE;
			break;
		}
	case '~':
		{
			i = CHAR_TILDE;
			break;
		}
	case '@':
		{
			i = CHAR_AT;
			break;
		}
	case '{':
		{
			i = CHAR_OPENCURLYBRACKET;
			break;
		}
	case '}':
		{
			i = CHAR_CLOSECURLYBRACKET;
			break;
		}
	case '[':
		{
			i = CHAR_OPENSQUAREBRACKET;
			break;
		}
	case ']':
		{
			i = CHAR_CLOSESQUAREBRACKET;
			break;
		}
	case '0':
		{
			i = CHAR_0;
			break;
		}
	case '1':
		{
			i = CHAR_1;
			break;
		}
	case '2':
		{
			i = CHAR_2;
			break;
		}
	case '3':
		{
			i = CHAR_3;
			break;
		}
	case '4':
		{
			i = CHAR_4;
			break;
		}
	case '5':
		{
			i = CHAR_5;
			break;
		}
	case '6':
		{
			i = CHAR_6;
			break;
		}
	case '7':
		{
			i = CHAR_7;
			break;
		}
	case '8':
		{
			i = CHAR_8;
			break;
		}
	case '9':
		{
			i = CHAR_9;
			break;
		}
		/*
		case '�':
		{
		   i = CHAR_dN;
		   break;
		}
		case '�':
		{
		   i = CHAR_aa;
		   break;
		}
		case '�':
		{
		   i = CHAR_ae;
		   break;
		}
		case '�':
		{
		   i = CHAR_ai;
		   break;
		}
		case '�':
		{
		   i = CHAR_ao;
		   break;
		}
		case '�':
		{
		   i = CHAR_au;
		   break;
		}
		case '�':
		{
		   i = CHAR_dn;
		   break;
		}
		case '�':
		{
		   i = CHAR_iE;
		   break;
		}
		case '�':
		{
		   i = CHAR_iQ;
		   break;
		}
		case '�':
		{
		   i = CHAR_aE;
		   break;
		}
		case '�':
		{
		   i = CHAR_aI;
		   break;
		}
		case '�':
		{
		   i = CHAR_aA;
		   break;
		}
  
		case '�':
		{
		   i = CHAR_RR;
		   break;
		}
		case '�':
		{
		   i = CHAR_LL;
		   break;
		}
		case '�':
		{
		   i = CHAR_ca;
		   break;
		}
		case '�':
		{
		   i = CHAR_ce;
		   break;
		}
		case '�':
		{
		   i = CHAR_ci;
		   break;
		}
		case '�':
		{
		   i = CHAR_co;
		   break;
		}
		case '�':
		{
		   i = CHAR_cu;
		   break;
		}
		case '�':
		{
		   i = CHAR_ga;
		   break;
		}
		case '�':
		{
		   i = CHAR_ge;
		   break;
		}
		case '�':
		{
		   i = CHAR_de;
		   break;
		}
		case '�':
		{
		   i = CHAR_cc;
		   break;
		}
		case '�':
		{
		   i = CHAR_lo;
		   break;
		}
  
		case '�':
		{
		   i = CHAR_aO;
		   break;
		}
		case '�':
		{
		   i = CHAR_gu;
		   break;
		}
  
		case '�':
		{
		   i = CHAR_dI;
		   break;
		}
		case '�':
		{
		   i = CHAR_dA;
		   break;
		}
		case '�':
		{
		   i = CHAR_dO;
		   break;
		}
		case '�':
		{
		   i = CHAR_dU;
		   break;
		}
		case '�':
		{
		   i = CHAR_da;
		   break;
		}
		case '�':
		{
		   i = CHAR_do;
		   break;
		}
		case '�':
		{
		   i = CHAR_du;
		   break;
		}
		case '�':
		{
		   i = CHAR_dB;
		   break;
		}
		*/

	case ' ':
		{
			i = CHAR_SPACE;
			break;
		}

	case '\n':
		{
			i = -1;
			break;
		}

	case '<':
		{
			string e = "Parsed a '<'.";

			log.error(e);

			i = -1;
			break;
		}
	case '>':
		{
			string e = "Parsed a '>'.";

			log.error(e);

			i = -1;
			break;
		}

	default:
		{
			i = CHAR_BLOCK;
			break;
		}
	}

	return i;
}


//=========================================================================================================================
int BobFont::getNextWordLength(const string& text, int in_position, BobFont* font)
{//=========================================================================================================================

	int next_word_length = 0;

	int length = (int)text.length();

	int temp_position = in_position;

	while (temp_position < length && (text[temp_position] != ' ' || temp_position == in_position) && isCurrentPositionANewline(text, temp_position) == false)
	//we should be starting on a space or the beginning of the test. include the starting space, up to the next space
	//&&
	//getText.charAt(temp_position)!='<'
	{
		//skip over tags
		if (temp_position < length && text[temp_position] == '<')
		{
			int x = 0;
			while (temp_position + x < length && text[temp_position + x] != '>')
			{
				x++;
			}
			temp_position += x;
			temp_position++; //for the '>'

			continue;
		}

		if (temp_position < length)
		{
			next_word_length += getCharWidth(BobFont::getFontIndexForChar(text[temp_position]), font);
			//add a space between letters for all fonts but outlined
			//if(font_id!=BobFont.FONT_OUTLINED_ID)
			next_word_length++;

			temp_position++;
		}
	}


	return next_word_length;
}


//=========================================================================================================================
bool BobFont::isCurrentPositionANewline(const string& t, int position)
{//=========================================================================================================================
	if ((t[position] == '\n') || (position < (int)t.length() - 1 && t[position] == '<' && t[position + 1] == '.') || (position < (int)t.length() - 2 && t[position] == '<' && t[position + 1] == 'N' && t[position + 2] == 'E')) //newline - or its a newline
	{
		return true;
	}
	else
	{
		return false;
	}
}


//=========================================================================================================================
int BobFont::getFontPixelValueAtIndex(int index, BobFont* font)
{//=========================================================================================================================

	if(font==nullptr || font == NULL)
	{
		log.error("BobFont::getFontPixelValueAtIndex font is null");
		return 0;
	}

//	int size = 0;
//	if (font != nullptr && font->byteArray != nullptr)size = (int)GOOGLE_ARRAYSIZE(font->byteArray);
//
//
//	if (index >= size)
//	{
//		log.error("BobFont::getFontPixelValueAtIndex index >=size should never happen!");
//		return -1;
//	}
	return font->byteArray[index];
}


//=========================================================================================================================
int BobFont::getCharWidth(int letter_index, BobFont* font)
{//=========================================================================================================================

	if (letter_index == -1)
	{
		return 0;
	}

	int x = 0;
	int y = 0;
	int w = 0;
	int blockWidth = 0;
	int blockHeight = 0;
	int maxCharHeight = 0;

	if (font != nullptr)blockWidth = font->blockWidth;
	if (font != nullptr)blockHeight = font->blockHeight;
	if (font != nullptr)maxCharHeight = font->maxCharHeight;

	for (x = blockWidth - 1; x >= 0; x--)
	{
		for (y = 0; y < maxCharHeight; y++)
		{
			if (BobFont::getFontPixelValueAtIndex((letter_index * blockWidth * blockHeight) + (y * blockWidth) + x, font) != 0)
			{
				w = x + 1;
				x = -1;
				y = maxCharHeight;
				break;
			}
		}
	}

	if (letter_index == BobFont::getFontIndexForChar(' '))
	{
		w = 3;

		if (maxCharHeight > 10)
		{
			w = 5;
		}

		//WIDTH OF SPACE IS DETERMINED HERE //was 3?
	}

	return w;
}

int BobFont::CHAR_A = 0;
int BobFont::CHAR_B = 1;
int BobFont::CHAR_C = 2;
int BobFont::CHAR_D = 3;
int BobFont::CHAR_E = 4;
int BobFont::CHAR_F = 5;
int BobFont::CHAR_G = 6;
int BobFont::CHAR_H = 7;
int BobFont::CHAR_I = 8;
int BobFont::CHAR_J = 9;
int BobFont::CHAR_K = 10;
int BobFont::CHAR_L = 11;
int BobFont::CHAR_M = 12;
int BobFont::CHAR_N = 13;
int BobFont::CHAR_O = 14;
int BobFont::CHAR_P = 15;
int BobFont::CHAR_Q = 16;
int BobFont::CHAR_R = 17;
int BobFont::CHAR_S = 18;
int BobFont::CHAR_T = 19;
int BobFont::CHAR_U = 20;
int BobFont::CHAR_V = 21;
int BobFont::CHAR_W = 22;
int BobFont::CHAR_X = 23;
int BobFont::CHAR_Y = 24;
int BobFont::CHAR_Z = 25;
int BobFont::CHAR_a = 26;
int BobFont::CHAR_b = 27;
int BobFont::CHAR_c = 28;
int BobFont::CHAR_d = 29;
int BobFont::CHAR_e = 30;
int BobFont::CHAR_f = 31;
int BobFont::CHAR_g = 32;
int BobFont::CHAR_h = 33;
int BobFont::CHAR_i = 34;
int BobFont::CHAR_j = 35;
int BobFont::CHAR_k = 36;
int BobFont::CHAR_l = 37;
int BobFont::CHAR_m = 38;
int BobFont::CHAR_n = 39;
int BobFont::CHAR_o = 40;
int BobFont::CHAR_p = 41;
int BobFont::CHAR_q = 42;
int BobFont::CHAR_r = 43;
int BobFont::CHAR_s = 44;
int BobFont::CHAR_t = 45;
int BobFont::CHAR_u = 46;
int BobFont::CHAR_v = 47;
int BobFont::CHAR_w = 48;
int BobFont::CHAR_x = 49;
int BobFont::CHAR_y = 50;
int BobFont::CHAR_z = 51;
int BobFont::CHAR_0 = 52;
int BobFont::CHAR_1 = 53;
int BobFont::CHAR_2 = 54;
int BobFont::CHAR_3 = 55;
int BobFont::CHAR_4 = 56;
int BobFont::CHAR_5 = 57;
int BobFont::CHAR_6 = 58;
int BobFont::CHAR_7 = 59;
int BobFont::CHAR_8 = 60;
int BobFont::CHAR_9 = 61;
int BobFont::CHAR_EXCLAMATION = 62;
int BobFont::CHAR_QUESTIONMARK = 63;
int BobFont::CHAR_PERIOD = 64;
int BobFont::CHAR_COMMA = 65;
int BobFont::CHAR_QUOTE = 66;
int BobFont::CHAR_DOUBLEQUOTE = 67;
int BobFont::CHAR_COLON = 68;
int BobFont::CHAR_SEMICOLON = 69;
int BobFont::CHAR_FRONTSLASH = 70;
int BobFont::CHAR_BACKSLASH = 71;
int BobFont::CHAR_ASTERISK = 72;
int BobFont::CHAR_PLUS = 73;
int BobFont::CHAR_MINUS = 74;
int BobFont::CHAR_EQUALS = 75;
int BobFont::CHAR_UNDERSCORE = 76;
int BobFont::CHAR_CARET = 77;
int BobFont::CHAR_BACKQUOTE = 78;
int BobFont::CHAR_TILDE = 79;
int BobFont::CHAR_OPENPARENTHESIS = 80;
int BobFont::CHAR_CLOSEPARENTHESIS = 81;
int BobFont::CHAR_OPENANGLEBRACKET = 82;
int BobFont::CHAR_CLOSEANGLEBRACKET = 83;
int BobFont::CHAR_OPENCURLYBRACKET = 84;
int BobFont::CHAR_CLOSECURLYBRACKET = 85;
int BobFont::CHAR_OPENSQUAREBRACKET = 86;
int BobFont::CHAR_CLOSESQUAREBRACKET = 87;
int BobFont::CHAR_PIPE = 88;
int BobFont::CHAR_AT = 89;
int BobFont::CHAR_POUND = 90;
int BobFont::CHAR_DOLLAR = 91;
int BobFont::CHAR_PERCENT = 92;
int BobFont::CHAR_AMPERSAND = 93;
int BobFont::CHAR_BLOCK = 94;
int BobFont::CHAR_SPACE = 95;
int BobFont::CHAR_dN = 96;
int BobFont::CHAR_aa = 97;
int BobFont::CHAR_ae = 98;
int BobFont::CHAR_ai = 99;
int BobFont::CHAR_ao = 100;
int BobFont::CHAR_au = 101;
int BobFont::CHAR_dn = 102;
int BobFont::CHAR_iE = 103;
int BobFont::CHAR_iQ = 104;
int BobFont::CHAR_aE = 105;
int BobFont::CHAR_aI = 106;
int BobFont::CHAR_aA = 107;
int BobFont::CHAR_RR = 108;
int BobFont::CHAR_LL = 109;
int BobFont::CHAR_ca = 110;
int BobFont::CHAR_ce = 111;
int BobFont::CHAR_ci = 112;
int BobFont::CHAR_co = 113;
int BobFont::CHAR_cu = 114;
int BobFont::CHAR_ga = 115;
int BobFont::CHAR_ge = 116;
int BobFont::CHAR_de = 117;
int BobFont::CHAR_cc = 118;
int BobFont::CHAR_lo = 119;
int BobFont::CHAR_aO = 120;
int BobFont::CHAR_gu = 121;
int BobFont::CHAR_dI = 122;
int BobFont::CHAR_dA = 123;
int BobFont::CHAR_dO = 124;
int BobFont::CHAR_dU = 125;
int BobFont::CHAR_da = 126;
int BobFont::CHAR_do = 127;
int BobFont::CHAR_du = 128;
int BobFont::CHAR_dB = 129;

