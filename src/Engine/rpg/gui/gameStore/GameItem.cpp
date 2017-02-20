#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger GameItem::log = Logger("GameItem");


GameItem::GameItem()
{ //=========================================================================================================================


	//   setTheme("gameContainerDialogLayout");
	//
	//   thisDialogLayout = this;
	//
	//
	//   gameTitleLabel = new Label("Tetrid");
	//   gameTitleLabel->setCanAcceptKeyboardFocus(false);
	//   gameTitleLabel->setTheme("gameLabel");
	//
	//   textAreaModel = new SimpleTextAreaModel();
	//
	//   textArea = new TextArea(textAreaModel);
	//   textArea->setCanAcceptKeyboardFocus(false);
	//   textArea->setTheme("gameTextArea");
	//
	//
	//   textArea->setBorderSize(0, 0);
	//
	//
	//   buyButton = new Button("Buy now!");
	//   buyButton->setCanAcceptKeyboardFocus(false);
	//   buyButton->setTheme("oppositeThemeButton");
	//
	//   priceLabel = new Label("$0.99");
	//   priceLabel->setCanAcceptKeyboardFocus(false);
	//   priceLabel->setTheme("priceLabel");
	//
	//
	//   //TODO: need to figure out how to alter the texture this points to. if i use the same size texture for all games it should work fine!
	//
	//
	//   iconWidget = new WidgetAnonymousInnerClassHelper(this);
	//
	//   iconWidget->setCanAcceptKeyboardFocus(false);
	//   iconWidget->setTheme("widget");
	//
	//
	//   setCanAcceptKeyboardFocus(false);
	//   setHorizontalGroup(createParallelGroup(createParallelGroup(gameTitleLabel), createSequentialGroup().addWidget(iconWidget).addGap(10).addWidget(textArea), createSequentialGroup().addGap().addWidget(priceLabel).addGap(20).addWidget(buyButton)));
	//
	//   setVerticalGroup(createSequentialGroup(createParallelGroup(gameTitleLabel), createParallelGroup(iconWidget, textArea), createSequentialGroup().addGap(), createParallelGroup(priceLabel, buyButton)));
}


//void GameItem::WidgetAnonymousInnerClassHelper::paint(GUI* gui)
//{
//   outerInstance->super->paint(gui);
//
//   //this was how i figured out how to force it to animate
//   //gamePreview.draw(getAnimationState(),getInnerX(),getInnerY(),128,128);
//}
//
//void GameItem::WidgetAnonymousInnerClassHelper::layout()
//{
//   outerInstance->gamePreview = static_cast<AnimatedImage*>(GLUtils::TWLthemeManager->getImage("gamePreviewAnimation"));
//
//   //if i set the background image in layout it works, if not it doesn't.
//   setBackground(outerInstance->gamePreview);
//
//   setMinSize(200, 200);
//   setMaxSize(200, 200);
//   adjustSize();
//
//   //force getText area to fit the rest of the width without creating a horizontal scrollbar
//   int w = outerInstance->thisDialogLayout->getWidth() - 128 - 165;
//   if (w < 0)
//   {
//      w = 128;
//   }
//   outerInstance->textArea->setMinSize(w, 0);
//}
//
//void GameItem::setText(const string& getText)
//{
//   textAreaModel->setText(getText, false);
//}


