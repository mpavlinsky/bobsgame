
#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------





BobTexture* BobMenu::rectangleCursorTexture = nullptr;
BobTexture* BobMenu::cursorTexture = nullptr;
BobTexture* BobMenu::upCursorTexture = nullptr;
BobTexture* BobMenu::downCursorTexture = nullptr;
long long BobMenu::cursorInOutToggleTicks = 0;
bool BobMenu::cursorInOutToggle = false;

BobColor* BobMenu::menuColor = nullptr;
BobColor* BobMenu::disabledMenuColor = nullptr;
BobColor* BobMenu::warningMenuColor = nullptr;
BobColor* BobMenu::clearColor = nullptr;
BobColor* BobMenu::infoColor = nullptr;
BobColor* BobMenu::statusColor = nullptr;
BobColor* BobMenu::errorColor = nullptr;
BobColor* BobMenu::bgColor = nullptr;

ArrayList<BobMenu*> BobMenu::activeMenus;

//=========================================================================================================================
BobMenu::MenuItem::~MenuItem()
{//=========================================================================================================================
	if (caption != nullptr)
	{
		caption->setToBeDeletedImmediately();
	}

	//if (subMenu != nullptr)delete subMenu;
}

//=========================================================================================================================
void BobMenu::MenuItem::setYesNo(bool yesNo)
{//=========================================================================================================================
	yesNoValue = yesNo;
	if (isYesNoType)
	{
		//string value = "";
		//if (yesNo)value = "Yes";
		//else value = "   ";
		//if (caption != nullptr)caption->replaceText("(" + value + ") " + captionText);
		if (yesNo == false) {setColor(disabledMenuColor);}
		else {setColor(menuColor);}
		
	}
}

//=========================================================================================================================
void BobMenu::MenuItem::toggle()
{//=========================================================================================================================
	setYesNo(!yesNoValue);
}

//=========================================================================================================================
void BobMenu::MenuItem::setColor(BobColor* color)
{//=========================================================================================================================
	caption->setTextColor(color);
	this->color = color;

}

//=========================================================================================================================
void BobMenu::MenuItem::setText(string s)
{//=========================================================================================================================
	caption->setText(s);
}


//BobSubMenu* BobMenu::addSubMenu(string caption, string id, BobsGame *b, void(*f) (BobsGame*, string))
//{
//	MenuItem *m = new MenuItem();
//	m->caption = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, 0, -1, caption, font, menuColor, BobColor::clear, RenderOrder::OVER_GUI);
//	m->subMenu = new BobSubMenu(e);
//	m->subMenu->parentMenu = this;
//	m->subMenu->bobsGame = b;
//	m->subMenu->callBack = f;
//
//	if (id == "")id = caption;
//	std::transform(id.begin(), id.end(), id.begin(), ::tolower);
//	m->id = id;
//	menuItems.add(m);
//
//	return m->subMenu;
//}


//=========================================================================================================================
BobMenu::BobMenu(Engine *g, string title)
{//=========================================================================================================================
	this->e = g;
	if (rectangleCursorTexture == nullptr)rectangleCursorTexture = GLUtils::getTextureFromPNG("data/textbox/rectangleCursor.png");
	if (cursorTexture == nullptr)cursorTexture = GLUtils::getTextureFromPNG("data/textbox/outlinedCursor.png");
	if (upCursorTexture == nullptr)upCursorTexture = GLUtils::getTextureFromPNG("data/textbox/upCursor.png");
	if (downCursorTexture == nullptr)downCursorTexture = GLUtils::getTextureFromPNG("data/textbox/downCursor.png");

	cursorInOutToggleTicks = 0;
	cursorInOutToggle = false;

	if (menuColor == nullptr)menuColor = BobColor::darkGray;
	if (disabledMenuColor == nullptr)disabledMenuColor = BobColor::lightGray;
	if (warningMenuColor == nullptr)warningMenuColor = BobColor::lightRed;
	if (clearColor == nullptr)clearColor = BobColor::clear;
	if (infoColor == nullptr)infoColor = BobColor::gray;
	if (statusColor == nullptr)statusColor = BobColor::lightGreen;
	if (errorColor == nullptr)errorColor = BobColor::lightRed;
	if (bgColor == nullptr)bgColor = BobColor::white;

	if (title != "")
	{
		titleCaption = new Caption(e,Caption::CENTERED_X, 0, -1, title, BobFont::ttf_oswald_32, menuColor, BobColor::clear, RenderOrder::OVER_GUI);
	}

	activeMenus.add(this);
}
//=========================================================================================================================
BobMenu::~BobMenu()
{//=========================================================================================================================
	if (titleCaption != nullptr)titleCaption->setToBeDeletedImmediately();
	menuItems.deleteAll();
	
	activeMenus.remove(this);
}


int graphicWidth = 0;
int graphicYStartPosition = 0;
//=========================================================================================================================
void BobMenu::setGraphic(BobTexture* t, int graphicWidth, int graphicYStartPosition)
{//=========================================================================================================================
	this->graphic = t;
	this->graphicWidth = graphicWidth;
	this->graphicYStartPosition = graphicYStartPosition;

}


//=========================================================================================================================
void BobMenu::clear()
{//=========================================================================================================================

	menuItems.deleteAll();
}
//=========================================================================================================================
void BobMenu::setAllCaptionsToFullAlpha()
{//=========================================================================================================================
	for (int i = 0; i < menuItems.size(); i++)
	{
		MenuItem *m = menuItems.get(i);
		if(m->caption!=nullptr)m->caption->setAlphaImmediately(1.0f);
	}
}

//=========================================================================================================================
void BobMenu::update(int ticksPassed)
{//=========================================================================================================================
	cursorInOutToggleTicks += ticksPassed;
	if (cursorInOutToggleTicks > 300)
	{
		cursorInOutToggleTicks = 0;
		cursorInOutToggle = !cursorInOutToggle;
	}

	for(int i = 0; i < activeMenus.size(); i++)
	{
		BobMenu *m = activeMenus.get(i);

		for(int n = 0; n < m->menuItems.size(); n++)
		{
			MenuItem *mi = m->menuItems.get(n);

			if (mi->info)continue;
			if (mi->hidden)continue;

			int mx = getControlsManager()->getMouseX();
			int my = getControlsManager()->getMouseY();

			Caption *c = mi->caption;
			if (c->visible == false)continue;

			int x0 = c->screenX + (c->getWidth() * 0.05);
			int x1 = c->screenX + c->getWidth() - (c->getWidth() * 0.05);
			int y0 = c->screenY + (c->getHeight() * 0.05);
			int y1 = c->screenY + c->getHeight() - (c->getHeight() * 0.05);

			if (x0 < mx && x1 > mx && y0 < my && y1 > my)
			{
				m->cursorPosition = n;
			}
		}
	}

}


//=========================================================================================================================
bool BobMenu::areAllMenusDisabled()
{//=========================================================================================================================
	bool allDisabled = true;
	for (int i = 0; i < menuItems.size(); i++)
	{
		MenuItem *m = menuItems.get(i);
		if (m->hidden == false && m->info == false)
		{
			allDisabled = false;
		}
	}
	if (allDisabled)return true;
	return false;
}


//=========================================================================================================================
void BobMenu::up(bool noSound)
{//=========================================================================================================================
	if (areAllMenusDisabled())return;
	do
	{
		cursorPosition--;
		if (cursorPosition < 0)cursorPosition = menuItems.size() - 1;
	} while (getSelectedMenuItem()->hidden == true || getSelectedMenuItem()->info == true);
	rectangleCursorMovementLastTime = System::currentHighResTimer();
	if(noSound==false)getAudioManager()->playSound("tick", 0.5f, 1.0f);

}


//=========================================================================================================================
void BobMenu::down(bool noSound)
{//=========================================================================================================================
	if (areAllMenusDisabled())return;
	do
	{
		cursorPosition++;
		if (cursorPosition > menuItems.size() - 1)cursorPosition = 0;
	} while (getSelectedMenuItem()->hidden == true || getSelectedMenuItem()->info == true);
	rectangleCursorMovementLastTime = System::currentHighResTimer();
	if (noSound == false)getAudioManager()->playSound("tick", 0.5f, 1.0f);
}


//=========================================================================================================================
BobMenu::MenuItem* BobMenu::addInfo(string caption, string id, BobColor *color)
{//=========================================================================================================================
	MenuItem *m = new MenuItem();
	m->caption = new Caption(e, Caption::CENTERED_X, 0, -1, caption, font, color, BobColor::clear, RenderOrder::OVER_GUI);
	m->captionText = caption;
	m->color = color;
	m->id = id;
	m->hidden = false;
	m->info = true;

	if (id == "")id = caption;
	std::transform(id.begin(), id.end(), id.begin(), ::tolower);
	m->id = id;
	menuItems.add(m);
	return m;
}


//=========================================================================================================================
BobMenu::MenuItem* BobMenu::add(string caption, string id, BobColor *color)
{//=========================================================================================================================
	MenuItem *m = new MenuItem();
	m->caption = new Caption(e, Caption::CENTERED_X, 0, -1, caption, font, color, BobColor::clear, RenderOrder::OVER_GUI);
	m->captionText = caption;
	m->color = color;
	if (id == "")id = caption;
	std::transform(id.begin(), id.end(), id.begin(), ::tolower);
	m->id = id;
	menuItems.add(m);
	return m;
}


//=========================================================================================================================
BobMenu::MenuItem* BobMenu::addYesNo(string caption, bool yesNo)
{//=========================================================================================================================
	//string value = "";
	//if (yesNo==false)value = " - (No)";
	//else value = "   ";
	//MenuItem *m = add(caption + value, caption);
	MenuItem *m = add(caption, caption);
	m->captionText = caption;
	
	m->isYesNoType = true;
	m->yesNoValue = yesNo;
	if (yesNo == false)m->setColor(disabledMenuColor);
	else m->setColor(menuColor);
	return m;
}


//=========================================================================================================================
void BobMenu::setHidden(string id, bool b)
{//=========================================================================================================================
	std::transform(id.begin(), id.end(), id.begin(), ::tolower);
	for (int i = 0; i<menuItems.size(); i++)
	{
		MenuItem *m = menuItems.get(i);
		if (m->id == id)
		{
			m->hidden = b;
		}
	}
}


//=========================================================================================================================
void BobMenu::setAllInvisible()
{//=========================================================================================================================
	for (int i = 0; i < menuItems.size(); i++)
	{
		MenuItem *m = menuItems.get(i);
		if (m->caption != nullptr)m->caption->visible = false;
	}
}


//=========================================================================================================================
void BobMenu::setAllVisible()
{//=========================================================================================================================
	for (int i = 0; i < menuItems.size(); i++)
	{
		MenuItem *m = menuItems.get(i);
		if (m->caption != nullptr)m->caption->visible = true;
	}
}


//=========================================================================================================================
bool BobMenu::isSelectedID(string id, bool clicked, int mx, int my)
{//=========================================================================================================================

	std::transform(id.begin(), id.end(), id.begin(), ::tolower);

	if(clicked)
	{
		for(int i=0;i<menuItems.size();i++)
		{
			MenuItem *m = menuItems.get(i);
			if (m->id != id)continue;

			Caption *c = m->caption;
			if (c->visible == false)continue;

			int x0 = c->screenX + (c->getWidth()*0.05);
			int x1 = c->screenX + c->getWidth() - (c->getWidth()*0.05);
			int y0 = c->screenY + (c->getHeight()*0.05);
			int y1 = c->screenY + c->getHeight() - (c->getHeight()*0.05);

			if(x0 < mx && x1 > mx && y0 < my && y1 > my)
			{
				cursorPosition = i;
				getAudioManager()->playSound("touchblock", 0.5f, 1.0f);
				return true;
			}
		}
		return false;
	}
	else
	{
		if(menuItems.get(cursorPosition)->id == id)
		{
			//getAudioManager()->playSound("touchblock", 0.5f,1.0f);
			return true;
		}
		else return false;
	}


	
}


//=========================================================================================================================
void BobMenu::setSelectedID(string id)
{//=========================================================================================================================
	std::transform(id.begin(), id.end(), id.begin(), ::tolower);
	for (int i = 0; i < menuItems.size(); i++)
	{
		MenuItem *m = menuItems.get(i);
		if (m->id == id)
		{
			cursorPosition = i;
		}
	}
}
//=========================================================================================================================
Caption* BobMenu::getCaptionByID(string id)
{//=========================================================================================================================
	std::transform(id.begin(), id.end(), id.begin(), ::tolower);

	for (int i = 0; i<menuItems.size(); i++)
	{
		MenuItem *m = menuItems.get(i);
		if (m->id == id)
		{
			return m->caption;
		}
	}
	return nullptr;
}


//=========================================================================================================================
BobMenu::MenuItem* BobMenu::getMenuItemByID(string id)
{//=========================================================================================================================
	std::transform(id.begin(), id.end(), id.begin(), ::tolower);

	for (int i = 0; i<menuItems.size(); i++)
	{
		MenuItem *m = menuItems.get(i);
		if (m->id == id)
		{
			return m;
		}
	}
	return nullptr;
}


//=========================================================================================================================
BobMenu::MenuItem* BobMenu::getSelectedMenuItem()
{//=========================================================================================================================
	if (cursorPosition >= menuItems.size())return nullptr;
	return menuItems.get(cursorPosition);
}

int BobMenu::getAmountOfMenuItems()
{
	return menuItems.size();
}

//=========================================================================================================================
//returns bottom of graphic y position
void BobMenu::render(int y, int x, int endY, bool drawCursor, int* returnBottomOfGraphic, int* returnBottomOfCaptions, bool renderBackgroundAndBorder, int* returnLeftX, int* returnRightX)
{//=========================================================================================================================

	if (y == 0 && titleCaption != nullptr)y = titleCaption->getHeight() + 8;


	float leftX = (float)GLUtils::getViewportWidth();
	float rightX = 0;
	float topY = 0;
	float bottomY = 0;

	if (graphic != nullptr)
	{
		float tx0 = 0;
		float tx1 = (float)(graphic->getImageWidth()) / (float)(graphic->getTextureWidth());
		float ty0 = 0;
		float ty1 = (float)((float)(graphic->getImageHeight()) / (float)(graphic->getTextureHeight()));

		float ratio = (float)(graphicWidth) / (float)(graphic->getImageWidth());

		float sx0 = (float)((int)((getEngine()->getWidth() - graphicWidth) / 2));
		float sx1 = (float)((int)(sx0 + graphicWidth));

		float sy0 = (float)graphicYStartPosition;
		float sy1 = (float)((int)(sy0 + (float)(graphic->getImageHeight() * ratio)));

		y = (int)(sy1 + 40);


		GLUtils::drawTexture(graphic, tx0, tx1, ty0, ty1, sx0, sx1, sy0, sy1, 1.0f, GLUtils::FILTER_NEAREST);
	}

	if (returnBottomOfGraphic != nullptr)*returnBottomOfGraphic = y;

	topY = (float)y;

	if (menuItems.size() == 0)return;

	//if selected disabled, move down
	if (areAllMenusDisabled()==false && (getSelectedMenuItem() == nullptr || getSelectedMenuItem()->hidden == true || getSelectedMenuItem()->info == true))down(true);

	int bottomOfCaptions = 0;

	ArrayList<MenuItem*> visibleMenuItems;

	
	{

		int menuItemsToShow = 0;
		int lowestHeight = y;
		for (int i = 0; i < menuItems.size(); i++)
		{
			MenuItem *m = menuItems.get(i);
			Caption *c = m->caption;

			if (c != nullptr)
			{
				if (m->hidden)
				{
					c->visible = false;
					continue;
				}
				else
				{
					visibleMenuItems.add(m);
					lowestHeight += (int)(c->getHeight()*spacing);

					//figure out how many can fit in the space
					//if less than totalVisible can fit
					if (lowestHeight >= endY && menuItemsToShow == 0)
					{
						menuItemsToShow = visibleMenuItems.size() - 3;
					}
				}
			}
		}

		if (menuItemsToShow == 0)menuItemsToShow = visibleMenuItems.size();

		//set them all invisible so i can only enable the ones to fit on the screen
		for (int i = 0; i < visibleMenuItems.size(); i++)
		{
			MenuItem *m = visibleMenuItems.get(i);
			Caption *c = m->caption;

			if (c != nullptr)
			{
				c->visible = false;
			}
		}

		
		MenuItem* selectedMenuItem = getSelectedMenuItem();

		int numVisibleMenuItemsBeforeCursor = visibleMenuItems.size();
		if (selectedMenuItem != nullptr)
		{
			//figure out visible menu items before cursor
			for (int i = 0; i < visibleMenuItems.size(); i++)
			{
				if (visibleMenuItems.get(i) == selectedMenuItem)
				{
					numVisibleMenuItemsBeforeCursor = i;
				}
			}
		}

		int numDrawn = 0;
		float firstCaptionX = 0;

		bool drawUpArrow = false;
		float upArrowY = 0;
		bool drawDownArrow = false;
		float downArrowY = 0;

		for (int i = 0; i < visibleMenuItems.size() && numDrawn <= menuItemsToShow; i++)
		{

			//figure out first caption to show
			//scroll down until the rest of the menus show on the screen
			if (numDrawn == 0)
			{
				if (numVisibleMenuItemsBeforeCursor > menuItemsToShow / 2 && menuItemsToShow < visibleMenuItems.size())
				{
					//if cursor > menuItemsToShow / 2, draw up arrow, start on cursor position - menuItemsToShow/2 - 1
					//draw up arrow
					drawUpArrow = true;
					upArrowY = (float)(y - 16);

					//jump i to numVisibleMenuItemsBeforeCursor - menuItemsToShow/2 -
					i = numVisibleMenuItemsBeforeCursor - (menuItemsToShow / 2);

					if (visibleMenuItems.size() - numVisibleMenuItemsBeforeCursor < menuItemsToShow)
					{
						i = (visibleMenuItems.size() - menuItemsToShow) - 1;
					}
				}
			}
			if (i < 0)i = 0;

			MenuItem *m = visibleMenuItems.get(i);
			Caption *c = m->caption;

			if (c != nullptr)
			{
				c->updateScreenXY();

				if (numDrawn == 0)
				{
					firstCaptionX = c->screenX;
				}
				

				c->visible = true;

				c->screenY = (float)(y + numDrawn * c->getHeight()*spacing);
				bottomOfCaptions = (int)(y + (numDrawn + 1) * c->getHeight()*spacing);

				if (x != 0)
				{
					c->fixedPosition = 0;
					if (center)c->screenX = (float)(x - c->getWidth() / 2);
					else c->screenX = (float)(x);
				}
				else
				{
					if (center == false)
					{
						c->fixedPosition = 0;
						c->screenX = (float)(firstCaptionX);
					}
				}

				if (c->screenX < leftX)leftX = c->screenX;
				if (c->screenX + c->getWidth() > rightX)rightX = c->screenX + c->getWidth();

				numDrawn++;
			}
		}
		if (visibleMenuItems.size() - numVisibleMenuItemsBeforeCursor > menuItemsToShow)
		{
			drawDownArrow = true;
			downArrowY = (float)bottomOfCaptions;
			bottomOfCaptions += 16;
		}


		if (returnBottomOfCaptions != nullptr)*returnBottomOfCaptions = bottomOfCaptions;

		bottomY = (float)bottomOfCaptions;

		if (returnLeftX != nullptr)*returnLeftX = leftX;
		if (returnRightX != nullptr)*returnRightX = rightX;

		if (renderBackgroundAndBorder)
		{
			GLUtils::drawFilledRect(0, 0, 0, leftX - 24, rightX + 24, topY - 16, bottomY + 16, 1);
			GLUtils::drawFilledRect(255, 255, 255, leftX - 22, rightX + 22, topY - 14, bottomY + 14, 1);
		}

		//draw transparent cursor rectangle
		//interpolate cursor rectangle location
		//pulse fade
		//menuItems.get(cursorPosition)->caption->setTextColor(BobColor::white);


		if (areAllMenusDisabled() == false && drawCursor)
		{

			long long currentTime = System::currentHighResTimer();
			long long startTime = rectangleCursorPulseLastTime;
			int pulseTicks = (int)(System::getTicksBetweenTimes(startTime, currentTime));
			if (pulseTicks > rectangleCursorPulsePeriodTicks)
			{
				rectangleCursorPulseLastTime = currentTime;
				rectangleCursorPulseInOut = !rectangleCursorPulseInOut;
			}
			else
			{
				float whereInPeriod = (float)pulseTicks / (float)rectangleCursorPulsePeriodTicks;
				float alphaChange = rectangleCursorPulseToAlpha - rectangleCursorPulseFromAlpha;
				if (rectangleCursorPulseInOut)
				{
					rectangleCursorPulseCurrentAlpha = rectangleCursorPulseFromAlpha + ((1.0f - whereInPeriod) * alphaChange);
				}
				else
				{
					rectangleCursorPulseCurrentAlpha = rectangleCursorPulseFromAlpha + (whereInPeriod * alphaChange);
				}
			}

			rectangleCursorToY = menuItems.get(cursorPosition)->caption->screenY - 2;

			if (rectangleCursorFromY < y || rectangleCursorCurrentY < y)
			{
				rectangleCursorFromY = rectangleCursorToY;
				rectangleCursorCurrentY = rectangleCursorToY;
			}

			if (rectangleCursorMovementLastTime == 0)rectangleCursorMovementLastTime = currentTime;

			startTime = rectangleCursorMovementLastTime;
			int moveTicks = (int)(System::getTicksBetweenTimes(startTime, currentTime));
			if (moveTicks > rectangleCursorMovementPeriodTicks)
			{
				rectangleCursorMovementLastTime = currentTime;
				rectangleCursorCurrentY = rectangleCursorToY;
				rectangleCursorFromY = rectangleCursorToY;
			}
			else
			{
				float whereInPeriod = (float)moveTicks / (float)rectangleCursorMovementPeriodTicks;
				float moveChange = rectangleCursorToY - rectangleCursorFromY;

				rectangleCursorCurrentY = rectangleCursorFromY + (whereInPeriod * moveChange);

				if (rectangleCursorCurrentY == rectangleCursorToY)rectangleCursorFromY = rectangleCursorToY;
			}





			BobTexture *cursor = rectangleCursorTexture;

			if (cursor != nullptr && menuItems.size() > 0)
			{
				
				float sx0 = leftX - 24;
				float sx1 = rightX + 24;

				float sy0 = rectangleCursorCurrentY;
				float sy1 = sy0 + menuItems.get(cursorPosition)->caption->getHeight() + 4;

				GLUtils::drawTexture(cursor, sx0, sx1, sy0, sy1, rectangleCursorPulseCurrentAlpha, GLUtils::FILTER_NEAREST);
			}
		}

		//getCaptionManager()->render(RenderOrder::OVER_GUI);
		for (int i = 0; i < menuItems.size(); i++)
		{
			MenuItem *m = menuItems.get(i);
			//if (i != cursorPosition)m->setColor(m->color);
			Caption *c = m->caption;
			c->update();
			c->render();
		}
		if (titleCaption != nullptr)
		{
			titleCaption->update();
			titleCaption->render();
		}

		//			if (areAllMenusDisabled() == false && drawCursor)
		//			{
		//
		//				BobTexture *cursor = cursorTexture;
		//
		//				if (cursor != nullptr && menuItems != nullptr && menuItems.size() > 0)
		//				{
		//
		//					float sx0 = menuItems.get(cursorPosition)->caption->screenX - 18;
		//					if (cursorInOutToggle)sx0 += 2;
		//					float sx1 = sx0 + 16;
		//
		//					float sy0 = menuItems.get(cursorPosition)->caption->screenY + 4;
		//					float sy1 = sy0 + 16;
		//
		//					GLUtils::drawTexture(cursor, 0, 1, 0, 1, sx0, sx1, sy0, sy1, 1.0f, GLUtils::FILTER_NEAREST);
		//				}
		//			}

		if (drawUpArrow)
		{
			BobTexture *t = upCursorTexture;
			if (t != nullptr)
			{
				float sx0 = (float)(GLUtils::getViewportWidth() / 2 - 4);
				if (x != 0) sx0 = (float)x;
				float sx1 = sx0 + 16;

				float sy0 = upArrowY;
				float sy1 = sy0 + 16;

				GLUtils::drawTexture(t, 0, 1, 0, 1, sx0, sx1, sy0, sy1, 1.0f, GLUtils::FILTER_NEAREST);
			}
		}

		if (drawDownArrow)
		{
			BobTexture *t = downCursorTexture;
			if (t != nullptr)
			{
				float sx0 = (float)(GLUtils::getViewportWidth() / 2 - 4);
				if (x != 0) sx0 = (float)x;
				float sx1 = sx0 + 16;

				float sy0 = downArrowY;
				float sy1 = sy0 + 16;

				GLUtils::drawTexture(t, 0, 1, 0, 1, sx0, sx1, sy0, sy1, 1.0f, GLUtils::FILTER_NEAREST);
			}
		}
	}

}


