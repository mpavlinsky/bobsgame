//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;





#include "MenuPanel.h"


class GameChallengeNotificationPanel : public MenuPanel
{
public:
	static Logger log;


	//DialogLayout* notificationPanel;

	//Button* yesButton;
	//Button* noButton;

	FriendCharacter* friendCharacter = nullptr;
	string gameName = "";

	long long notificationCreatedTime = 0;

	//Label* timeLeftLabel = nullptr;


	GameChallengeNotificationPanel(FriendCharacter* friend_in, const string& gameName);


	virtual void update() override;


	virtual void onScrolledUp() override;


	virtual void scrollUp() override;


	virtual void scrollDown() override;


protected:
	virtual void layout() override;


public:
	virtual void setButtonsVisible(bool b);


	virtual void doNo();


	virtual void doYes();


	virtual void renderBefore() override;


	virtual void render() override;
};

