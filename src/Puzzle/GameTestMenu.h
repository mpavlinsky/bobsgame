
#include "bobtypes.h"

#include "Gwen/Platform.h"
#include <Gwen/Controls/Base.h>
#include <Gwen/Controls/DockBase.h>
#include "Gwen/Controls/Label.h"
#include "Gwen/Controls/TabControl.h"
#include "Gwen/Controls/HorizontalSplitter.h"
#include "Gwen/Controls/ListBox.h"
#include "Gwen/Controls/HorizontalSlider.h"
#include "Gwen/Controls/StatusBar.h"
#include <Gwen/Controls/Button.h>
#include <Gwen/Controls/ImagePanel.h>
#include <Gwen/Controls/Rectangle.h>
#include "Gwen/Controls/DockedTabControl.h"
#include "Gwen/Controls/WindowControl.h"
#include "Gwen/Controls/CollapsibleList.h"
#include "Gwen/Controls/Layout/Position.h"

#include <Gwen/Controls/WindowControl.h>
#include <Gwen/Controls/ListBox.h>
#include <Gwen/Controls/Base.h>
#include <Gwen/Controls/Property/BaseProperty.h>
#include <Gwen/Controls/Property/ColorSelector.h>
#include <Gwen/Controls/Property/ComboBox.h>
#include <Gwen/Controls/Property/Checkbox.h>
#include <Gwen/Controls/Property/TextWithButton.h>
#include <Gwen/Controls/Property/Listbox.h>
#include <Gwen/Controls/Properties.h>
#include <Gwen/Controls/PropertyTree.h>
#include <Gwen/Controls/CheckBox.h>
#include <Gwen/Controls/ColorPicker.h>
#include <Gwen/Controls/ComboBox.h>
#include <map>


//=========================================================================================================================
class GameTestPreviewRectangle : public Gwen::Controls::Rectangle
{//=========================================================================================================================
public:

	//GWEN_CONTROL(PreviewRectangle, Rectangle);
	//typedef PreviewRectangle ThisClass;
	//typedef Rectangle BaseClass;
	static const char* GetIdentifier()
	{
		static const char* ident = "Rectangle" ":" "PreviewRectangle";
		return ident;
	};
	virtual Gwen::Controls::Base* DynamicCast(const char* Variable)
	{
		if (GetIdentifier() == Variable)
			return this;

		return Gwen::Controls::Rectangle::DynamicCast(Variable);
	}
	virtual const char* GetTypeName() { return "PreviewRectangle"; }
	virtual const char* GetBaseTypeName() { return Gwen::Controls::Rectangle::GetTypeName(); }
	//GWEN_CONTROL_CONSTRUCTOR(PreviewRectangle)
	GameTestPreviewRectangle(Gwen::Controls::Base* pParent, const Gwen::String& pName, BobsGame* b) : Gwen::Controls::Rectangle(pParent, pName)
	{
		bobsGame = b;
		m_Color = Gwen::Color(255, 255, 0, 255);
	}

	virtual void Render(Gwen::Skin::Base* skin);

	BobsGame *bobsGame = nullptr;
};


//=========================================================================================================================
class GameTestMenuControl : public Gwen::Controls::Base
{//=========================================================================================================================
public:
	//GWEN_CONTROL(GameTestMenuControl, Gwen::Controls::Base);
	//typedef GameTestMenuControl ThisClass;
	//typedef Gwen::Controls::Base BaseClass;
	static const char* GetIdentifier()
	{
		static const char* ident = "Base" ":" "GameTestMenuControl";
		return ident;
	};
	virtual Gwen::Controls::Base* DynamicCast(const char* Variable)
	{
		if (GetIdentifier() == Variable)
			return this;

		return Gwen::Controls::Base::DynamicCast(Variable);
	}
	virtual const char* GetTypeName() { return "GameTestMenuControl"; }
	virtual const char* GetBaseTypeName() { return Gwen::Controls::Base::GetTypeName(); }
	GameTestMenuControl(Gwen::Controls::Base* pParent, const Gwen::String& pName = "", BobsGame *b = nullptr);



	void onExitButton(Gwen::Controls::Base* control);
	void onUpVoteButton(Gwen::Controls::Base* control);
	void onDownVoteButton(Gwen::Controls::Base* control);
	void vote(bool upDown);


	void onGameSequencesListSelect(Gwen::Controls::Base* control);
	void onGameTypesListSelect(Gwen::Controls::Base* control);


	void checkResize();
	void doResize();
	void populateGameTypesListBox();
	void populateGameSequencesListBox();


	void initPreviewGame();
	void onPreviewButton(Gwen::Controls::Base* control);
	void onChangeDifficulty(Gwen::Controls::Base* control);
	void onChangeHideVotedGames(Gwen::Controls::Base* control);



private:
	Gwen::Controls::Base* previewBase;
public:
	GameTestPreviewRectangle* darkRectangle = nullptr;
	Gwen::Controls::Button* previewButton = nullptr;
	Gwen::Controls::ComboBox* difficultyCombo = nullptr;

	Gwen::Controls::Label* selectedGameLabel = nullptr;

	Gwen::Controls::Base* leftBase = nullptr;
	Gwen::Controls::Base* rightBase = nullptr;
	Gwen::Controls::HorizontalSplitter *mainWindowSplitter = nullptr;


	Gwen::Controls::Base* gameTypesListBoxBase = nullptr;
	Gwen::Controls::ListBox* gameTypesListBox = nullptr;

	Gwen::Controls::Base* gameSequencesListBoxBase = nullptr;
	Gwen::Controls::ListBox* gameSequencesListBox = nullptr;



private:

	Gwen::Controls::Base* applyButtonsBase = nullptr;
	Gwen::Controls::Button* exitButton = nullptr;
	Gwen::Controls::Button* upVoteButton = nullptr;
	Gwen::Controls::Button* downVoteButton = nullptr;

	Gwen::Controls::Base* gameTypesWindow = nullptr;
	Gwen::Controls::Base* gameSequencesWindow = nullptr;
	Gwen::Controls::TabControl* leftBaseTabControl = nullptr;
	Gwen::Controls::TabButton* gameTypesTab = nullptr;
	Gwen::Controls::Base* gameTypesPage = nullptr;

	Gwen::Controls::TabButton* gameSequencesTab = nullptr;
	Gwen::Controls::Base* gameSequencesPage = nullptr;

	Gwen::Controls::CheckBox *hideVotedGames = nullptr;

public:
	bool exit = false;
private:

	GameSequence *currentGameSequence = nullptr;


public:
	bool windowOpen = false;
	BobsGame* bobsGame = nullptr;


	int fontHeight = 20;
	int lastW = 0;
	int lastH = 0;
};

