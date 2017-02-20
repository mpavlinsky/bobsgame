
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger Console::log = Logger("Console");


bool error_console_on = 1;
string error_messages[128];


DEBUG_overlay_STRUCT* DEBUG_overlays[128];

CaptionManager* Console::captionManager = nullptr;


//===========================================================================================================================
void ERROR_init_error_console()
{//===========================================================================================================================

	//int x = 0;
	//for (x = 0; x < 128; x++)error_messages[x] = "";

	//for (x = 0; x < 128; x++)DEBUG_overlays[x] = NULL;
}

//===========================================================================================================================
void ERROR_set_error(string error_string)
{//===========================================================================================================================


	Console::log.error(error_string);

	//copy the new error string into a stored string
	//char* new_error = (char*)malloc((strlen(error_string) + 2) * sizeof(char));
	//sprintf(new_error, "%s\n", error_string);
	//string new_error = error_string + "\n";

	//add this string to the error message array
	//int slot = -1;
	//int x = 0;
	//for (x = 0; x < 128; x++)
	//	if (error_messages[x] == "")
	//	{
	//		slot = x;
	//		x = 128;
	//		break;
	//	}
	//
	//if (slot == -1)
	//{
	//	//too many errors, could recycle the array, could use linked list, could delete errors as they get bumped off screen.
	//	return;
	//}
	//
	//error_messages[slot] = new_error;

	
}


//===========================================================================================================================
void ERROR_draw_error_console()
{//===========================================================================================================================
	//go through error_messages
	//find non-NULL value

	int amount_of_errors = 0;

	int x = 0;
	for (x = 0; x < 128; x++)
		if (error_messages[x] != "")amount_of_errors++;


	//start at top of screen
	//fill values

	int line_height = 12;

	int max_lines;
	max_lines = (int)GLUtils::getViewportHeight() / line_height;

	//if height of screen is greater than lines that can fit, start at the last error - amount

	int start_error = 0;
	if (amount_of_errors > max_lines)start_error = amount_of_errors - max_lines;


	SDL_Surface* error_SURFACE = NULL;
	BobTexture* error_TEXTURE = NULL;
	SDL_Color green_COLOR = {0,255,0,255};
	SDL_Color white_COLOR = {255,255,255,255};
	SDL_Color black_COLOR = {0,0,0,255};

	int line = 0;
	//draw font to screen
	for (x = amount_of_errors - 1; x >= start_error; x--)
	{
		line++;

		if (x == amount_of_errors - 1)error_SURFACE = TTF_RenderText_Shaded(BobFont::ttf_bobsgame_8, error_messages[x].c_str(), green_COLOR, black_COLOR);
		else error_SURFACE = TTF_RenderText_Shaded(BobFont::ttf_bobsgame_8, error_messages[x].c_str(), white_COLOR, black_COLOR);

		error_TEXTURE = GLUtils::loadTextureFromSurface(string(error_messages[x]),error_SURFACE);

		GLUtils::drawTexture(error_TEXTURE, (float)0, (float)(GLUtils::getViewportHeight()) - (line_height * line), GLUtils::FILTER_NEAREST);

		if (error_SURFACE != NULL)
		{
			SDL_FreeSurface(error_SURFACE);
			error_SURFACE = NULL;
		}
		if (error_TEXTURE != NULL)
		{
			error_TEXTURE->release();
			error_TEXTURE = NULL;
		}
	}
}



//===========================================================================================================================
DEBUG_overlay_STRUCT* DEBUG_make_overlay(string text, float hardware_screen_x, float hardware_screen_y)
{//===========================================================================================================================


	//this uses actual hardware screen x and y because it does not render as a game sprite like most other objects like captions, so it isnt affected by ZOOM


	//copy the new error string into a stored string
	DEBUG_overlay_STRUCT* overlay = (DEBUG_overlay_STRUCT*)malloc(sizeof(DEBUG_overlay_STRUCT));

	//add this string to the error message array
	int slot = -1;
	int x = 0;
	for (x = 0; x < 128; x++)
		if (DEBUG_overlays[x] == NULL)
		{
			slot = x;
			x = 128;
			break;
		}

	if (slot == -1)
	{
		//too many errors, could recycle the array, could use linked list, could delete errors as they get bumped off screen.
		return NULL;
	}

	DEBUG_overlays[slot] = overlay;

	//sprintf((char*)(overlay->text), text);
	overlay->text = text;
	overlay->x = hardware_screen_x;
	overlay->y = hardware_screen_y;
	overlay->width = 0;


	return overlay;
}

//===========================================================================================================================
void DEBUG_update_overlay(DEBUG_overlay_STRUCT* overlay, string text, float hardware_screen_x, float hardware_screen_y)
{//===========================================================================================================================

	//sprintf((char*)(overlay->text), text);
	overlay->text = text;
	overlay->x = hardware_screen_x;
	overlay->y = hardware_screen_y;
}

//===========================================================================================================================
void DEBUG_delete_overlay(DEBUG_overlay_STRUCT* overlay)
{//===========================================================================================================================

	if (overlay == NULL)return;

	int x = 0;
	for (x = 0; x < 128; x++)
		if (DEBUG_overlays[x] == overlay)
		{
			DEBUG_overlays[x] = NULL;
			x = 128;
			break;
		}

	free(overlay);
}

//===========================================================================================================================
void DEBUG_draw_overlays()
{//===========================================================================================================================


	SDL_Surface* error_SURFACE = NULL;
	BobTexture* error_TEXTURE = NULL;
	SDL_Color white_COLOR = {255,255,255,255};
	SDL_Color black_COLOR = {0,0,0,255};

	int x = 0;
	for (x = 0; x < 128; x++)
	{
		if (DEBUG_overlays[x] != NULL)
		{
			error_SURFACE = TTF_RenderText_Shaded(BobFont::ttf_bobsgame_8, DEBUG_overlays[x]->text.c_str(), white_COLOR, black_COLOR);
			error_TEXTURE = GLUtils::loadTextureFromSurface(string(DEBUG_overlays[x]->text), error_SURFACE);

			GLUtils::drawTexture(error_TEXTURE, (float)DEBUG_overlays[x]->x, (float)DEBUG_overlays[x]->y, GLUtils::FILTER_NEAREST);

			DEBUG_overlays[x]->width = error_TEXTURE->getImageWidth();

			if (error_SURFACE != NULL)
			{
				SDL_FreeSurface(error_SURFACE);
				error_SURFACE = NULL;
			}
			if (error_TEXTURE != NULL)
			{
				error_TEXTURE->release();
				error_TEXTURE = NULL;
			}
		}
	}
}

//===========================================================================================================================
void DEBUG_draw_text(float screenX0, float screenY0, string text, BobColor* color)
{//===========================================================================================================================


	SDL_Surface* error_SURFACE = NULL;
	BobTexture* error_TEXTURE = NULL;
	SDL_Color white_COLOR = { (u8)color->ri(),(u8)color->gi(),(u8)color->bi(),255 };
	SDL_Color black_COLOR = { 0,0,0,255 };


	error_SURFACE = TTF_RenderText_Shaded(BobFont::ttf_bobsgame_8, text.c_str(), white_COLOR, black_COLOR);
	error_TEXTURE = GLUtils::loadTextureFromSurface(text.c_str(),error_SURFACE);

	GLUtils::drawTexture(error_TEXTURE, screenX0, screenY0, GLUtils::FILTER_NEAREST);


	if (error_SURFACE != NULL)
	{
		SDL_FreeSurface(error_SURFACE);
		error_SURFACE = NULL;
	}
	if (error_TEXTURE != NULL)
	{
		error_TEXTURE->release();
		error_TEXTURE = NULL;
	}
		
	
}


ArrayList<ConsoleText*>* Console::consoleTextList = new ArrayList<ConsoleText*>();
mutex Console::_consoleTextList_Mutex;

Console::Console()
{ //=========================================================================================================================
	captionManager = new CaptionManager(nullptr);

}

void Console::update()
{ //=========================================================================================================================

	captionManager->update();

	for (int i = 0; i < consoleTextList->size(); i++)
	{
		ConsoleText* d = consoleTextList->get(i);

		int cx = d->x;
		int cy = d->y;
		if (cx == -1)cx = 0;
		if (cy == -1)cy = 0;//-1 is a magic num for captions, dont use it
		if (d->caption == nullptr)d->caption = Console::captionManager->newManagedCaption(cx, cy, -1, d->text, BobFont::ttf_bobsgame_8, d->color, BobColor::clear, RenderOrder::CONSOLE);

		if (d->caption->text != d->text)d->caption->setText(d->text, false);
		if (d->caption->getTextColor() != d->color)d->caption->setTextColor(d->color, nullptr, BobColor::clear);

		if (d->ticks != -1)
		{
			d->ticks -= (int)State::realWorldTicksPassed();

			if (d->ticks <= 0)
			{
				d->caption->setToBeDeletedImmediately();
				consoleTextList->removeAt(i);
				i--;
			}
		}
	}
}

ConsoleText* Console::error(const string& s)
{ //=========================================================================================================================

	return add(s, BobColor::red, -1, -1, -1, true);
}

ConsoleText* Console::error(const string& s, int ticks)
{ //=========================================================================================================================

	return add(s, BobColor::red, -1, -1, ticks, true);
}

ConsoleText* Console::error(const string& s, BobColor* c)
{ //=========================================================================================================================

	return add(s, c, -1, -1, -1, true);
}

ConsoleText* Console::error(const string& s, BobColor* c, int ticks)
{ //=========================================================================================================================

	return add(s, c, -1, -1, ticks, true);
}

ConsoleText* Console::error(const string& s, int x, int y)
{ //=========================================================================================================================

	return add(s, BobColor::red, x, y, -1, true);
}

ConsoleText* Console::error(const string& s, BobColor* c, int x, int y)
{ //=========================================================================================================================

	return add(s, c, x, y, -1, true);
}

ConsoleText* Console::debug(const string& s)
{ //=========================================================================================================================

	ConsoleText* d = add(s, nullptr, -1, -1, -1, true);

	return d;
}

ConsoleText* Console::debug(const string& s, int ticks)
{ //=========================================================================================================================

	ConsoleText* d = add(s, nullptr, -1, -1, ticks, true);

	return d;
}

ConsoleText* Console::debug(const string& s, BobColor* c)
{ //=========================================================================================================================

	ConsoleText* d = add(s, c, -1, -1, -1, true);

	return d;
}

ConsoleText* Console::debug(const string& s, BobColor* c, int ticks)
{ //=========================================================================================================================

	ConsoleText* d = add(s, c, -1, -1, ticks, true);

	return d;
}

ConsoleText* Console::debug(const string& s, int x, int y)
{ //=========================================================================================================================

	ConsoleText* d = add(s, nullptr, x, y, -1, true);

	return d;
}

ConsoleText* Console::debug(const string& s, BobColor* c, int x, int y)
{ //=========================================================================================================================

	ConsoleText* d = add(s, c, x, y, -1, true);

	return d;
}

ConsoleText* Console::add(const string& s)
{ //=========================================================================================================================

	return add(s, nullptr, -1, -1, -1, false);
}

ConsoleText* Console::add(const string& s, int ticks)
{ //=========================================================================================================================

	return add(s, nullptr, -1, -1, ticks, false);
}

ConsoleText* Console::add(const string& s, BobColor* c)
{ //=========================================================================================================================

	return add(s, c, -1, -1, -1, false);
}

ConsoleText* Console::add(const string& s, BobColor* c, int ticks)
{ //=========================================================================================================================

	return add(s, c, -1, -1, ticks, false);
}

ConsoleText* Console::add(const string& s, int x, int y)
{ //=========================================================================================================================

	return add(s, nullptr, x, y, -1, false);
}

ConsoleText* Console::add(const string& s, int x, int y, int ticks)
{ //=========================================================================================================================

	return add(s, nullptr, x, y, ticks, false);
}

ConsoleText* Console::add(const string& s, BobColor* c, int x, int y)
{ //=========================================================================================================================

	return add(s, c, x, y, -1, false);
}

ConsoleText* Console::add(const string& s, BobColor* c, int x, int y, int ticks)
{ //=========================================================================================================================

	return add(s, c, x, y, ticks, false);
}

ConsoleText* Console::add(const string& s, BobColor* c, int x, int y, int ticks, bool isDebug)
{ //=========================================================================================================================

	ConsoleText* dt = new ConsoleText(s, c, x, y, ticks, isDebug);
	lock_guard<mutex> lock(_consoleTextList_Mutex);
	consoleTextList->add(dt);
	return dt;
}

#ifdef _DEBUG
bool debugConsoleOff = false;
#else
bool debugConsoleOff = true;
#endif

void Console::render()
{ //=========================================================================================================================



		int numStrings = consoleTextList->size();

		int messagesCounter = 0;

		for (int n = numStrings; n > 0; n--)
		{
			ConsoleText* dt = consoleTextList->get(n - 1);

			if (dt->caption == nullptr)continue;

			if (debugConsoleOff == true && dt->isDebug == true)
			{
				dt->caption->visible = false;
				continue;
			}


			if (dt->x != -1 || dt->y != -1)
			{
				int x = dt->x;
				int y = dt->y;

				if (x == -1)
				{
					//x=GLUtils.getViewportWidth()/2;// make this get width of string to center it
					x = GLUtils::getRealWindowWidth() / 2 - ((GLUtils::getOutlinedTextWidth(dt->text) + 3) / 2);
				}


				if (y == -1)
				{
					y = GLUtils::getRealWindowHeight() / 2;
				}


				//GLUtils::drawOutlinedString((float)x, (float)y, dt->text, dt->color);
				//DEBUG_draw_text((float)x, (float)y, dt->text, dt->color);
				dt->caption->screenX = (float)x;
				dt->caption->screenY = (float)y;
			}
			else
			{
				messagesCounter++;
				//GLUtils::drawOutlinedString((float)8, (float)GLUtils::getViewportHeight() - (12 * messagesCounter), dt->text, dt->color);
				//DEBUG_draw_text((float)8, (float)GLUtils::getRealWindowHeight() - (12 * messagesCounter), dt->text, dt->color);

				float x = 8;
				float y = (float)GLUtils::getRealWindowHeight() - (12 * messagesCounter);
				dt->caption->screenX = x;
				dt->caption->screenY = y;
			}
		}

		captionManager->render(RenderOrder::CONSOLE);

}

