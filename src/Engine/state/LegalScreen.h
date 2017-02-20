//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class LegalScreen : public MenuPanel
{
public:
	static Logger log;


	//   DialogLayout* legalPanel;
	//
	//   Button* noButton;
	//   Button* okButton;


	LegalScreen();

	bool _clickedOK = false;
	bool _clickedCancel = false;

	//The following method was originally marked 'synchronized':
	virtual bool getClickedOK_S();
	//The following method was originally marked 'synchronized':
	virtual bool getClickedCancel_S();

	//The following method was originally marked 'synchronized':
	virtual void setClickedOK_S(bool b);
	//The following method was originally marked 'synchronized':
	virtual void setClickedCancel_S(bool b);


	virtual void update() override;


	virtual void onScrolledUp() override;


protected:
	virtual void layout() override;


public:
	virtual void setButtonsVisible(bool b);


	virtual void scrollDown() override;


	virtual void doDisagree();


	virtual void doAgree();


	virtual void renderBefore() override;


	virtual void render() override;
};

