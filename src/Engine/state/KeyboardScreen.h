//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class KeyboardScreen : public MenuPanel
{
public:
	static Logger log;


	//DialogLayout* keyboardPanel;


	//Button* okButton;


	KeyboardScreen();

private:
	class WidgetAnonymousInnerClassHelper// : public Widget
	{
	private:
		KeyboardScreen* outerInstance;

	public:
		WidgetAnonymousInnerClassHelper(KeyboardScreen* outerInstance);

		virtual void layout();
	};

public:
	bool _clickedOK = false;

	//The following method was originally marked 'synchronized':
	virtual bool getClickedOK_S();

	//The following method was originally marked 'synchronized':
	virtual void setClickedOK_S(bool b);


	virtual void update() override;


	virtual void onScrolledUp() override;


	virtual void scrollDown() override;


protected:
	virtual void layout() override;


public:
	virtual void setButtonsVisible(bool b);


	virtual void doOK();


	virtual void renderBefore() override;


	virtual void render() override;
};

