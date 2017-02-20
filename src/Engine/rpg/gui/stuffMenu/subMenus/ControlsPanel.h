//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class ControlsPanel : public SubPanel
{
public:

	static Logger log;


	//ArrayList<Label*> buttonValueLabel;


	ControlsPanel();

private:
	class WidgetAnonymousInnerClassHelper// : public Widget
	{
	private:
		ControlsPanel* outerInstance;

	public:
		WidgetAnonymousInnerClassHelper(ControlsPanel* outerInstance);

		virtual void layout();
	};


public:
	virtual void setButton(int index, int value);
};

