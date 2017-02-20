#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger ItemsPanel::log = Logger("ItemsPanel");


ItemsPanel::ItemsPanel()
{ //=========================================================================================================================

	SubPanel();


	//   horizontalGroup = insideLayout->createParallelGroup();
	//   verticalGroup = insideLayout->createSequentialGroup();
	//
	//
	//   //for each item in ItemManager.itemList, make a dialogLayout, fill it with name and description
	//
	//   //if there are no items, make one that says no items.
	//
	//
	//   insideLayout->setHorizontalGroup(horizontalGroup);
	//
	//   insideLayout->setVerticalGroup(verticalGroup);
}

void ItemsPanel::updateItems()
{ //=========================================================================================================================


	ArrayList<Item*>* items = new ArrayList<Item*>();

	for (int i = 0; i < (int)getEventManager()->itemList.size(); i++)
	{
		if (getEventManager()->itemList.get(i)->getHaveItemValue_S() == true)
		{
			items->add(getEventManager()->itemList.get(i));
		}
	}
	//
	//
	//   itemDialogLayout = ArrayList<DialogLayout*>(items->size());
	//
	//   for (int n = 0; n < items->size(); n++)
	//   {
	//      itemDialogLayout[n] = new DialogLayout();
	//      itemDialogLayout[n]->setCanAcceptKeyboardFocus(false);
	//      itemDialogLayout[n]->setTheme("itemBox");
	//
	//
	//      Item* i = items[n];
	//      Label* nameLabel = new Label(i->name());
	//      nameLabel->setCanAcceptKeyboardFocus(false);
	//      nameLabel->setTheme("itemLabel");
	//
	//
	//      //Label descriptionLabel = new Label(i.description);
	//      //descriptionLabel.setCanAcceptKeyboardFocus(false);
	//      //descriptionLabel.setTheme("");
	//
	//
	//      SimpleTextAreaModel* textAreaModel = new SimpleTextAreaModel();
	//
	//
	//      TextArea* textArea = new TextArea(textAreaModel);
	//      textArea->setTheme("textarea");
	//
	//      textArea->setBorderSize(0, 0);
	//      textArea->setCanAcceptKeyboardFocus(false);
	//
	//      textAreaModel->setText(i->description(), false);
	//
	//
	//      itemDialogLayout[n]->setHorizontalGroup(itemDialogLayout[n]->createParallelGroup(nameLabel, textArea));
	//
	//      itemDialogLayout[n]->setVerticalGroup(itemDialogLayout[n]->createSequentialGroup(nameLabel, textArea));
	//   }
	//
	//
	//   insideLayout->removeAllChildren();
	//
	//   horizontalGroup = insideLayout->createParallelGroup(itemDialogLayout);
	//   verticalGroup = insideLayout->createSequentialGroup(itemDialogLayout).addGap();
	//
	//   insideLayout->setHorizontalGroup(horizontalGroup);
	//
	//   insideLayout->setVerticalGroup(verticalGroup);
}

void ItemsPanel::layout()
{ //=========================================================================================================================


	//   if (itemDialogLayout->empty())
	//   {
	//      updateItems();
	//   }
	//
	//   for (int i = 0; i < itemDialogLayout->size(); i++)
	//   {
	//      itemDialogLayout[i]->setMaxSize((int)((GLUtils::getViewportWidth() * getStuffMenu()->subPanelScreenWidthPercent) * 0.80f), 500);
	//   }


	SubPanel::layout();
}

void ItemsPanel::setVisible(bool b)
{ //=========================================================================================================================

	if (b == true)
	{
		updateItems();
	}
	SubPanel::setVisible(b);
}

