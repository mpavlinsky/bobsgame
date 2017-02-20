


#include "stdafx.h"
#include "CaptionManager.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------






Logger CaptionManager::log = Logger("CaptionManager");


//=========================================================================================================================
CaptionManager::CaptionManager(Engine* g)
{//=========================================================================================================================
	this->e = g;
}



//=========================================================================================================================
void CaptionManager::update()
{//=========================================================================================================================

	int ticksPassed = 0;
	if (e != nullptr)
	{
		ticksPassed = e->engineTicksPassed();
	}
	else
	{
		ticksPassed = State::realWorldTicksPassed();
	}
	


	//-----------------------------
	//update time
	//-----------------------------
	for (int n = 0; n < captionList->size(); n++)
	{
		Caption* c = captionList->get(n);
		if (c->ticksToRemain > 0)
		{
			c->ticksToRemain -= ticksPassed;
			if (c->ticksToRemain < 0)
			{
				c->ticksToRemain = 0;
			}
		}
	}


	for (int n = 0; n < captionList->size(); n++)
	{
		Caption* c = captionList->get(n);
		c->update();

		if(c->deleteMe)
		{
			captionList->remove(c);
			if(c->texture!=nullptr)
			{
				log.debug("Caption texture was not null on delete, should not happen.");
				c->texture->release();
				c->texture = nullptr;
			}
			delete c;
			n--;
		}

	}
}


//=========================================================================================================================
void CaptionManager::render(RenderOrder layer)
{//=========================================================================================================================


	//go through linked list backwards, because new captions are appended on the end.
	//in the case of the clock, we want to draw the older time over the new time so it fades nicely


	for (int n = captionList->size() - 1; n >= 0; n--)
	{
		Caption* c = captionList->get(n);
		if (c->layer == layer)
		{
			c->render();
		}
	}


	//   for (int n = captionList->size() - 1; n >= 0; n--)
	//   {
	//      Caption* c = captionList->get(n);
	//      if (c->drawAbove == false)
	//      {
	//         c->render();
	//      }
	//   }
	//
	//   for (int n = captionList->size() - 1; n >= 0; n--)
	//   {
	//      Caption* c = captionList->get(n);
	//      if (c->drawAbove == true)
	//      {
	//         c->render();
	//      }
	//   }
}


//=========================================================================================================================
Caption* CaptionManager::newManagedCaption(int x, int y, int ticks, const string& text, BobFont* font, BobColor* textColor, BobColor* textAAColor, BobColor* textBGColor, RenderOrder r, float scale, int width, Entity* entity, Area* area, bool fadeLetterColorTowardsTop, bool centerTextOnMultipleLines)
{//=========================================================================================================================

	if (ticks >= 0 && ticks < 100)
	{
		log.log(string("Caption was made with ticks: ") + to_string(ticks) + string(". Text: ") + text);
	}

	Caption* c = new Caption(this->e, (float)x, (float)y, ticks, text, font, textColor, textAAColor, textBGColor, r, scale, width, entity, area, fadeLetterColorTowardsTop, centerTextOnMultipleLines);
	captionList->add(c);
	return c;
}

//=========================================================================================================================
Caption* CaptionManager::newManagedCaption(int x, int y, int ticks, const string& text, TTF_Font* ttfFont, BobColor* textColor, BobColor* textBGColor, RenderOrder r, float scale, Entity* entity, Area* area)
{//=========================================================================================================================

	if (ticks >= 0 && ticks < 100)
	{
		log.log(string("TTF Caption was made with ticks: ") + to_string(ticks) + string(". Text: ") + text);
	}

	Caption* c = new Caption(this->e, (float)x, (float)y, ticks, text, ttfFont, textColor, textBGColor, r, scale, entity, area);
	captionList->add(c);
	return c;
}

//	//=========================================================================================================================
//	/**
//	 * MUST USE THE RETURN VALUE
//	 */
//	public Caption fadeOutDelete_MUST_USE_RETURN(Caption c)
//	{//=========================================================================================================================
//
//		//TODO: take an array in with the external getCaption so it can be set to null?
//
//
//		c.getToAlpha=0.0f;
//
//		return null;
//
//
//	}
//
//	//=========================================================================================================================
//	/**
//	 * MUST USE THE RETURN VALUE
//	 */
//	public Caption delete_MUST_USE_RETURN(Caption c)
//	{//=========================================================================================================================
//
//		//TODO: take an array in with the external getCaption so it can be set to null?
//
//		c.delete=true;
//
//		return null;
//	}

//
//	//=========================================================================================================================
//	public void CAPTION_delete_all_captions()
//	{//=========================================================================================================================
//
//		/*
//		while(first_CAPTION!=null)
//		{
//			CAPTION* current_caption=first_CAPTION;
//			while(current_caption.next!=null)current_caption=(CAPTION*)current_caption.next;
//			CAPTION_delete_caption(current_caption);
//		}
//		*/
//
//	}
//	//=========================================================================================================================
//	public void CAPTION_pause()
//	{//=========================================================================================================================
//			//delete all sprites but keep captions
//			//set pause_CAPTION to first_CAPTION
//			//set first_CAPTION to null
//
//		/*
//		pause_CAPTION= first_CAPTION;
//		first_CAPTION=null;
//
//		if(pause_CAPTION!=null)
//		{
//			Caption current_caption = pause_CAPTION;
//			bool stop=0;
//			while(stop==0)
//			{
//				u8 c=0;
//			for(c=0;c<current_caption.chunks;c++)
//			{
//				if(current_caption.sprite[c]!=null)
//					{
//						HARDWARE_delete_sprite(current_caption.sprite[c]);
//						current_caption.sprite[c]=null;
//					}
//				}
//				if(current_caption.next!=null)current_caption=(CAPTION*)current_caption.next;else stop=1;
//			}
//		}
//		*/
//	}
//
//	//=========================================================================================================================
//	public void CAPTION_unpause()
//	{//=========================================================================================================================
//		//delete all captions from first_CAPTION on
//		//set first_CAPTION back to pause_CAPTION
//		//set pause_CAPTION to null
//		//redraw all getCaption sprites
//
//		//CAPTION_delete_all_captions();
//
//		first_CAPTION= pause_CAPTION;
//		pause_CAPTION=null;
//
//		//u8 caption_chunks_onscreen[2]={0,0};
//
//
//		/*
//		if(first_CAPTION!=null)
//		{
//			CAPTION* current_caption = first_CAPTION;
//			bool stop=0;
//			while(stop==0)
//			{
//				u8 c=0;
//			for(c=0;c<current_caption.chunks;c++)
//			{
//				if(current_caption.sprite[c]==null)
//					{
//						//current_caption.PLAYER_id[c]=FIRST_SPRITE_ID+caption_chunks_onscreen[current_caption.screen];
//
//						current_caption.sprite[c]=HARDWARE_create_sprite(current_caption.gfx[c],0,current_caption.layer,current_caption.getScale,current_caption.screen_x+64*c,current_caption.screen_y,255);
//
//						//HARDWARE_create_sprite(current_caption.screen,current_caption.PLAYER_id[c],current_caption.gfx_slot[c],64,32,1,0,0,0,0,0,current_caption.prio,current_caption.getScale,current_caption.screen_x+64*c,current_caption.screen_y);
//						//caption_chunks_onscreen[current_caption.screen]++;
//					}
//				}
//				if(current_caption.next!=null)current_caption=(CAPTION*)current_caption.next;else stop=1;
//			}
//		}*/
//
//	}
//
//


