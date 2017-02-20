#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger DebugInfoPanel::log = Logger("DebugInfoPanel");


//ArrayList<de::matthiasmann::twl::Label*> DebugInfoPanel::label = nullptr;
//de::matthiasmann::twl::DialogLayout::Group* DebugInfoPanel::horizontalGroup = nullptr;
//de::matthiasmann::twl::DialogLayout::Group* DebugInfoPanel::verticalGroup = nullptr;

DebugInfoPanel::DebugInfoPanel()
{ //=========================================================================================================================


	SubPanel();

	//   horizontalGroup = insideLayout->createParallelGroup();
	//   verticalGroup = insideLayout->createSequentialGroup();
	//
	//   //updateStatusPanel();
	//
	//   insideLayout->setHorizontalGroup(horizontalGroup);
	//
	//   insideLayout->setVerticalGroup(verticalGroup);
}

void DebugInfoPanel::update()
{ //=========================================================================================================================

	updateTicks += (int)Engine::realWorldTicksPassed();
	if (updateTicks > 200) //every 200 ticks
	{
		updateTicks = 0;

		//
		//      int size = Console::consoleTextList->size();
		//
		//      if (label->empty() || size != label->size())
		//      {
		//         label = ArrayList<Label*>(size);
		//
		//         for (int i = 0; i < size; i++)
		//         {
		//            label[i] = new Label(Console::consoleTextList[i]->getText);
		//         }
		//
		//         insideLayout->removeAllChildren();
		//
		//         horizontalGroup = insideLayout->createParallelGroup(label);
		//         verticalGroup = insideLayout->createSequentialGroup(label);
		//
		//         insideLayout->setHorizontalGroup(horizontalGroup);
		//
		//         insideLayout->setVerticalGroup(verticalGroup);
		//      }
		//      else
		//      {
		//         for (int i = 0; i < size; i++)
		//         {
		//            label[i]->setText(Console::consoleTextList[i]->getText);
		//         }
	}
}

