#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger LegalScreen::log = Logger("LegalScreen");


LegalScreen::LegalScreen()
{ //=========================================================================================================================

	//MenuPanel();

	//
	//   legalPanel = new DialogLayout();
	//   legalPanel->setTheme("legalpanel");
	//
	//
	//   Label* legalPanelLabel = new Label("LEGAL");
	//   legalPanelLabel->setCanAcceptKeyboardFocus(false);
	//   legalPanelLabel->setTheme("bigLabel");
	//
	//

	//
	//
	//   okButton = new Button("I Agree");
	//   okButton->setCanAcceptKeyboardFocus(false);
	//   okButton->addCallback([&] ()
	//      {
	//         doAgree();
	//      }
	//   );
	//
	//
	//   noButton = new Button("I Disagree");
	//   noButton->setCanAcceptKeyboardFocus(false);
	//   noButton->addCallback([&] ()
	//      {
	//         doDisagree();
	//      }
	//   );
	//
	//
	//   legalPanel->setHorizontalGroup(legalPanel->createParallelGroup(legalPanel->createParallelGroup().addMinGap(400), legalPanel->createSequentialGroup(legalPanel->createParallelGroup().addMinGap(50), legalPanel->createParallelGroup(legalPanel->createSequentialGroup().addGap().addWidget(legalPanelLabel).addGap(), legalPanel->createSequentialGroup().addGap().addWidget(legalTextLabel).addGap(), legalPanel->createSequentialGroup().addGap().addWidget(noButton).addGap().addWidget(okButton).addGap()), legalPanel->createParallelGroup().addMinGap(50))));
	//
	//
	//   legalPanel->setVerticalGroup(legalPanel->createSequentialGroup(legalPanel->createSequentialGroup().addMinGap(20), legalPanel->createParallelGroup(legalPanelLabel), legalPanel->createSequentialGroup().addMinGap(20), legalPanel->createParallelGroup(legalTextLabel), legalPanel->createSequentialGroup().addMinGap(20), legalPanel->createParallelGroup(okButton, noButton), legalPanel->createSequentialGroup().addMinGap(50)));
	//
	//
	//   //---------------------------------------------------------
	//   //layout
	//   //---------------------------------------------------------
	//
	//   insideScrollPaneLayout->setHorizontalGroup(insideScrollPaneLayout->createParallelGroup(insideScrollPaneLayout->createSequentialGroup().addGap().addWidget(legalPanel).addGap()));
	//
	//   insideScrollPaneLayout->setVerticalGroup(insideScrollPaneLayout->createSequentialGroup(insideScrollPaneLayout->createSequentialGroup().addGap(), insideScrollPaneLayout->createParallelGroup().addWidget(legalPanel), insideScrollPaneLayout->createSequentialGroup().addGap()));
	//
	//
	//   //---------------------
	//   //scrollpane
	//   //----------------------
	//
	//   scrollPane = new ScrollPane(insideScrollPaneLayout);
	//
	//   scrollPane->setTheme(GUIManager::scrollPaneTheme);
	//   scrollPane->setCanAcceptKeyboardFocus(false);
	//   scrollPane->setExpandContentSize(true);
	//
	//
	//   //---------------------
	//   //add scrollpane to outside panel
	//   //----------------------
	//
	//   //mainPanelLayout.add(scrollPane);
	//
	//
	//   mainPanelLayout->setCanAcceptKeyboardFocus(false);
	//   mainPanelLayout->setHorizontalGroup(mainPanelLayout->createParallelGroup(scrollPane));
	//
	//   mainPanelLayout->setVerticalGroup(mainPanelLayout->createSequentialGroup(scrollPane));
	//
	//
	//   add(mainPanelLayout);
	//
	//
	//   legalPanel->adjustSize();


	setActivated(true);
}

//The following method was originally marked 'synchronized':
bool LegalScreen::getClickedOK_S()
{
	return _clickedOK;
}

//The following method was originally marked 'synchronized':
bool LegalScreen::getClickedCancel_S()
{
	return _clickedCancel;
}

//The following method was originally marked 'synchronized':
void LegalScreen::setClickedOK_S(bool b)
{
	_clickedOK = b;
}

//The following method was originally marked 'synchronized':
void LegalScreen::setClickedCancel_S(bool b)
{
	_clickedCancel = b;
}

void LegalScreen::update()
{ //=========================================================================================================================
	if (isActivated == true)
	{
		if (isScrollingDown == false)
		{
			ticksSinceTurnedOff = 0;
			ticksSinceTurnedOn += 32;

			scrollUp();
		}
		else
		{
			if (isScrollingDown == true)
			{
				ticksSinceTurnedOn = 0;
				ticksSinceTurnedOff += 32;

				scrollDown();
			}
		}
	}
}

void LegalScreen::onScrolledUp()
{ //=========================================================================================================================

	//getGUI().setTooltipDelay(1);
}

void LegalScreen::layout()
{ //=========================================================================================================================

	//   //login panel is centered
	//
	//   legalPanel->adjustSize();
	//   legalPanel->setPosition(insideScrollPaneLayout->getInnerX() + (insideScrollPaneLayout->getInnerWidth() - legalPanel->getWidth()) / 2, insideScrollPaneLayout->getInnerY() + (insideScrollPaneLayout->getInnerHeight() - legalPanel->getHeight()) / 2);

	MenuPanel::layout();
}

void LegalScreen::setButtonsVisible(bool b)
{ //=========================================================================================================================

	//
	//   noButton->setVisible(b);
	//   okButton->setVisible(b);
}

void LegalScreen::scrollDown()
{ //=========================================================================================================================
	if (ticksSinceTurnedOff <= fadeOutTime)
	{
		screenY = (float)(Easing::easeOutCubic(ticksSinceTurnedOff, 0, GLUtils::getViewportHeight(), fadeOutTime));
		layout();
	}
	else
	{
		isActivated = false;
		isScrollingDown = false;
		//MenuPanel::setVisible(false);
	}
}

void LegalScreen::doDisagree()
{ //=========================================================================================================================
	//   GUI* gui = getGUI();
	//   if (gui != nullptr)
	//   {
	//      setButtonsVisible(false);
	//
	//      //create thread, this needs to be a thread because Button.doCallback(Runnable) only calls Runnable.run() which does NOT create a thread.
	//      new Thread([&] ()
	//         {
	//            try
	//            {
	//               Thread::currentThread().setName("Legal_doDisagree");
	//            }
	//            catch (SecurityException e)
	//            {
	//               e->printStackTrace();
	//            }
	//
	//            setActivated(false);
	//
	//            while (getIsScrollingDown())
	//            {
	//               try
	//               {
	//                  delay(500);
	//               }
	//               catch (exception& e)
	//               {
	//               }
	//            }
	//
	//            setClickedCancel_S(true);
	//         }
	//      )
	//      .
	//      start();
	//   }
}

void LegalScreen::doAgree()
{ //=========================================================================================================================

	//   GUI* gui = getGUI();
	//   if (gui != nullptr)
	//   {
	//      setButtonsVisible(false);
	//
	//      //create thread, this needs to be a thread because Button.doCallback(Runnable) only calls Runnable.run() which does NOT create a thread.
	//      new Thread([&] ()
	//         {
	//            try
	//            {
	//               Thread::currentThread().setName("Legal_doOK");
	//            }
	//            catch (SecurityException e)
	//            {
	//               e->printStackTrace();
	//            }
	//
	//            setActivated(false);
	//
	//            while (getIsScrollingDown())
	//            {
	//               try
	//               {
	//                  delay(500);
	//               }
	//               catch (exception& e)
	//               {
	//               }
	//            }
	//
	//            setClickedOK_S(true);
	//         }
	//      )
	//      .
	//      start();
	//   }
}

void LegalScreen::renderBefore()
{ //=========================================================================================================================


	if (getIsScrollingDown() == true)
	{
		return;
	}
	if (getIsActivated() == false)
	{
		return;
	}
	//additional rendering calls go here (after gui is drawn)
}

void LegalScreen::render()
{ //=========================================================================================================================


	if (getIsScrollingDown() == true)
	{
		return;
	}
	if (getIsActivated() == false)
	{
		return;
	}

	//additional rendering calls go here (after gui is drawn)
}

