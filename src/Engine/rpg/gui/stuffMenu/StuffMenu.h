//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class FriendsPanel;
class DebugInfoPanel;
class StatusPanel;
class MessagesPanel;
class ItemsPanel;
class LogsPanel;
class ControlsPanel;
class SettingsPanel;


class StuffMenu : public MenuPanel
{
public:

	static Logger log;


	FriendsPanel* friendsPanel;
	DebugInfoPanel* debugInfoPanel;
	StatusPanel* statusPanel;
	MessagesPanel* messagesPanel;
	ItemsPanel* itemsPanel;
	LogsPanel* logsPanel;
	ControlsPanel* controlsPanel;
	SettingsPanel* settingsPanel;


	//ArrayList<ToggleButton*> stuffMenuTabs;


	float subPanelScreenWidthPercent = 0.80f;
	float subPanelScreenHeightPercent = 0.86f;


	StuffMenu();


	virtual void setActivated(bool b) override;


	virtual void setAllInvisible();


	virtual void openSubMenu();// SubPanel* subPanel);


	virtual void init();


	virtual void update() override;


	virtual void render() override;


protected:
	virtual void layout() override;
};

