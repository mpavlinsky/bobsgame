//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;





#include "notification/Notification.h"


class NotificationManager : public EnginePart
{
public:

	static Logger log;


	ArrayList<Notification*>* notificationList = new ArrayList<Notification*>();

	static BobTexture* loadingBarTexture;
	static BobTexture* loadingBarBackgroundTexture;


	NotificationManager(BGClientEngine* g);


	virtual void init();


	virtual void update();


	virtual void render(int layer);


	virtual void add(Notification* n);


	virtual void remove(Notification* n);
};

