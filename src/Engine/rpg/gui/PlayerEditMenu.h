//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class PlayerEditMenu : public MenuPanel
{
public:
	static Logger log;


	//   DialogLayout* editPanel;
	//   DialogLayout* animPanel;
	//
	//   Label* playerEditPanelLabel;
	//
	//   Label* errorLabel;
	//   Label* statusLabel;
	//
	//
	//   Label* nameLabel;
	//   EditField* nameEditField;
	//
	//   Label* zipCodeLabel;
	//   EditField* zipCodeEditField;
	//
	//
	//   Label* addSocialAccountsLabel;
	//   Label* facebookAccountLabel;
	//   Button* addFacebookAccountButton;
	//
	//   Label* googlePlusAccountLabel;
	//   //Button addGooglePlusAccountButton;
	//
	//   Label* genderLabel;
	//   ArrayList<Label*> genderButtonLabels;
	//   SimpleIntegerModel* genderOptionModel;
	//   ArrayList<ToggleButton*> genderButtons;
	//
	//   Label* countryLabel;
	//   SimpleChangableListModel<string>* countryStrings;
	//   ComboBox<string>* countryComboBox;
	//
	//   Label* archetypeLabel;
	//   SimpleChangableListModel<string>* archetypeStrings;
	//   ComboBox<string>* archetypeComboBox;
	//
	//   Label* hairColorLabel;
	//   SimpleChangableListModel<string>* hairColorStrings;
	//   ComboBox<string>* hairColorComboBox;
	//
	//   Label* skinColorLabel;
	//   SimpleChangableListModel<string>* skinColorStrings;
	//   ComboBox<string>* skinColorComboBox;
	//
	//   Label* eyeColorLabel;
	//   SimpleChangableListModel<string>* eyeColorStrings;
	//   ComboBox<string>* eyeColorComboBox;
	//
	//   Label* shirtColorLabel;
	//   SimpleChangableListModel<string>* shirtColorStrings;
	//   ComboBox<string>* shirtColorComboBox;
	//
	//   Label* pantsColorLabel;
	//   SimpleChangableListModel<string>* pantsColorStrings;
	//   ComboBox<string>* pantsColorComboBox;
	//
	//   Label* shoeColorLabel;
	//   SimpleChangableListModel<string>* shoeColorStrings;
	//   ComboBox<string>* shoeColorComboBox;
	//
	//   Button* randomButton;
	//   Button* okButton;


	string nameString = "";

	int genderIndex = 0;

	int archetypeIndex = 0;
	int hairColorIndex = 0;
	int skinColorIndex = 0;
	int eyeColorIndex = 0;
	int shirtColorIndex = 0;
	int pantsColorIndex = 0;
	int shoeColorIndex = 0;


	Caption* playerNameCaption = nullptr;


	bool initRandom = false;


	long long lastTime = 0;
	int frame = 0;

	int direction = 0;
	int loopCount = 0;


	PlayerEditMenu();

private:
	class CallbackAnonymousInnerClassHelper// : public EditField::Callback
	{
	private:
		PlayerEditMenu* outerInstance;

	public:
		CallbackAnonymousInnerClassHelper(PlayerEditMenu* outerInstance);

		virtual void callback(int key);// override;
	};

private:
	class CallbackAnonymousInnerClassHelper2// : public EditField::Callback
	{
	private:
		PlayerEditMenu* outerInstance;

	public:
		CallbackAnonymousInnerClassHelper2(PlayerEditMenu* outerInstance);

		virtual void callback(int key);// override;
	};


public:
	virtual void init();


	virtual void setButtonsVisible(bool b);


public:
	class AddressInfo
	{
	private:
		PlayerEditMenu* outerInstance;

	public:
		AddressInfo(PlayerEditMenu* outerInstance);

		string postalCode = "";
		string stateName = "";
		string placeName = "";

		float lat = 0.0f;
		float lon = 0.0f;
		float timeZone = 0.0f;
	};


public:
	virtual AddressInfo* queryYahooGeocodingAPI(const string& address);


	virtual AddressInfo* queryGoogleGeocodingAPI(const string& address);


	virtual void doOKButton();


	virtual void linkFacebookAccount();


	virtual void redrawPlayer();


	virtual void setRandomOptions();


protected:
	virtual void layout() override;


public:
	virtual void setActivated(bool b) override;


	virtual void update() override;

	virtual void render() override;
};

