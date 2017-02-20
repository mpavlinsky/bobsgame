//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class StatusPanel : public SubPanel
{
public:
	static Logger log;

	/*
	
	   public int userID=-1;
	   public String emailAddress = "";
	   public String passwordHash = "";
	   public int accountVerified = 0;
	   public String verificationHash = "";
	   public long lastPasswordResetTime = 0;
	   public long accountCreatedTime = 0;
	   public long accountVerifiedTime = 0;
	   public long firstLoginTime = 0;
	   public long lastLoginTime = 0;
	   public long lastLoginTime = 0;
	   public int timesLoggedIn = 0;
	   public String firstIP = "";
	   public String lastIP = "";
	   public String realName = "";
	   public long birthdayTime = 0;
	   public String facebookID = "";
	   public String facebookAccessToken = "";
	   public String facebookEmail = "";
	   public String facebookBirthday = "";
	   public String facebookFirstName = "";
	   public String facebookLastName = "";
	   public String facebookGender = "";
	   public String facebookLocale = "";
	   public Float facebookTimeZone = 0.0f;
	   public String facebookUsername = "";
	   public String facebookWebsite = "";
	
	   public String googlePlusID = "";
	   public String postalCode = "";
	   public String countryName = "";
	   public String isoCountryCode = "";
	   public String placeName = "";
	   public String stateName = "";
	   public float lat = 0;
	   public float lon = 0;
	   public int timeZone = 0;
	   public String notes = "";
	   public String warnings = "";
	   public String avatarIcon = "";
	   public String lastKnownRoom = "";
	   public int lastKnownX = 0;
	   public int lastKnownY = 0;
	   public String startingRoom = "";
	   public long timePlayed = 0;
	   public long pixelsWalked = 0;
	   public int money = 0;
	   public int moneyPurchased = 0;
	   public int realWorldTransactions = 0;
	   public int inGameTransactions = 0;
	   public int timesTalkedToNPCs = 0;
	   public int timesTalkedToOtherPlayers = 0;
	   public String characterAppearance = "";
	   public String characterName = "";
	   public String itemsHeld = "";
	   public String itemsTotalCollected = "";
	   public String itemsPurchased = "";
	*/
	//
	//   Button* editCharacterButton = nullptr;
	//
	//
	//   Label* moneyDescriptionLabel = nullptr;
	//   Label* moneyLabel = nullptr;
	//   Button* addMoneyButton = nullptr;
	//   Label* addMoneyButtonQuestionMark = nullptr;
	//
	//   Label* accountTypeDescriptionLabel = nullptr;
	//   Label* accountTypeLabel = nullptr;
	//   Button* goPremiumButton = nullptr;
	//   Label* goPremiumButtonQuestionMark = nullptr;
	//
	//
	//   //public String characterName = "";
	//   Label* characterNameDescriptionLabel = nullptr;
	//   Label* characterNameLabel = nullptr;
	//
	//
	//   DialogLayout* accountDialogLayout;
	//   Label* accountPanelLabel;
	//
	//
	//   //public String emailAddress = "";
	//   Label* emailAddressDescriptionLabel = nullptr;
	//   Label* emailAddressLabel = nullptr;
	//
	//
	//   //public long accountCreatedTime = 0;
	//   Label* accountCreatedTimeDescriptionLabel = nullptr;
	//   Label* accountCreatedTimeLabel = nullptr;
	//
	//
	//   //public long lastLoginTime = 0;
	//   Label* lastLoginTimeDescriptionLabel = nullptr;
	//   Label* lastLoginTimeLabel = nullptr;
	//
	//
	//   //public int timesLoggedIn = 0;
	//   Label* timesLoggedInDescriptionLabel = nullptr;
	//   Label* timesLoggedInLabel = nullptr;
	//
	//
	//   //public String lastIP = "";
	//   Label* lastIPDescriptionLabel = nullptr;
	//   Label* lastIPLabel = nullptr;
	//
	//
	//   //public String realName = "";
	//   //Label realNameDescriptionLabel = null;
	//   //Label realNameLabel = null;
	//
	//
	//   //public long birthdayTime = 0;
	//   //Label birthdayTimeDescriptionLabel = null;
	//   //Label birthdayTimeLabel = null;
	//
	//
	//   DialogLayout* facebookDialogLayout;
	//   Label* facebookPanelLabel;
	//
	//   //public String facebookEmail = "";
	//   Label* facebookEmailDescriptionLabel = nullptr;
	//   Label* facebookEmailLabel = nullptr;
	//
	//
	//   //public String facebookBirthday = "";
	//   Label* facebookBirthdayDescriptionLabel = nullptr;
	//   Label* facebookBirthdayLabel = nullptr;
	//
	//
	//   //public String facebookFirstName = "";
	//   Label* facebookFirstNameDescriptionLabel = nullptr;
	//   Label* facebookFirstNameLabel = nullptr;
	//
	//
	//   //public String facebookLastName = "";
	//   Label* facebookLastNameDescriptionLabel = nullptr;
	//   Label* facebookLastNameLabel = nullptr;
	//
	//
	//   //public String facebookGender = "";
	//   Label* facebookGenderDescriptionLabel = nullptr;
	//   Label* facebookGenderLabel = nullptr;
	//
	//
	//   //public String facebookLocale = "";
	//   Label* facebookLocaleDescriptionLabel = nullptr;
	//   Label* facebookLocaleLabel = nullptr;
	//
	//
	//   //public Float facebookTimeZone = 0.0f;
	//   Label* facebookTimeZoneDescriptionLabel = nullptr;
	//   Label* facebookTimeZoneLabel = nullptr;
	//
	//
	//   //public String facebookUsername = "";
	//   Label* facebookUsernameDescriptionLabel = nullptr;
	//   Label* facebookUsernameLabel = nullptr;
	//
	//
	//   //public String facebookWebsite = "";
	//   Label* facebookWebsiteDescriptionLabel = nullptr;
	//   Label* facebookWebsiteLabel = nullptr;
	//
	//
	//   DialogLayout* locationDialogLayout;
	//   Label* locationPanelLabel;
	//
	//   //public String postalCode = "";
	//   Label* postalCodeDescriptionLabel = nullptr;
	//   Label* postalCodeLabel = nullptr;
	//
	//   //public String countryName = "";
	//   Label* countryNameDescriptionLabel = nullptr;
	//   Label* countryNameLabel = nullptr;
	//
	//   //public String isoCountryCode = "";
	//   Label* isoCountryCodeDescriptionLabel = nullptr;
	//   Label* isoCountryCodeLabel = nullptr;
	//
	//   //public String placeName = "";
	//   Label* placeNameDescriptionLabel = nullptr;
	//   Label* placeNameLabel = nullptr;
	//
	//
	//   //public String stateName = "";
	//   Label* stateNameDescriptionLabel = nullptr;
	//   Label* stateNameLabel = nullptr;
	//
	//
	//   //public float lat = 0;
	//   Label* latDescriptionLabel = nullptr;
	//   Label* latLabel = nullptr;
	//
	//   //public float lon = 0;
	//   Label* lonDescriptionLabel = nullptr;
	//   Label* lonLabel = nullptr;
	//
	//   //public int timeZone = 0;
	//   Label* timeZoneDescriptionLabel = nullptr;
	//   Label* timeZoneLabel = nullptr;
	//
	//
	//   //Label playerFacebookNameDescriptionLabel = null;
	//   //Label playerFacebookNameLabel = null;
	//
	//   //Label playerGooglePlusNameDescriptionLabel = null;
	//   //Label playerGooglePlusNameLabel = null;
	//
	//   //Label playerTwitterNameDescriptionLabel = null;
	//   //Label playerTwitterNameLabel = null;
	//
	//
	//   //Label totalTimePlayedDescriptionLabel = null;
	//   //Label totalTimePlayedLabel = null;
	//
	//   //Label sessionTimePlayedDescriptionLabel = null;
	//   //Label sessionTimePlayedLabel = null;
	//
	//   //Label averageTimePlayedDescriptionLabel = null;
	//   //Label averageTimePlayedLabel = null;
	//
	//   //Label gamesPurchasedDescriptionLabel = null;
	//   //Label gamesPurchasedLabel = null;
	//
	//   //Label gamesSoldDescriptionLabel = null;
	//   //Label gamesSoldLabel = null;
	//
	//   //Label friendsInGameDescriptionLabel = null;
	//   //Label friendsInGameLabel = null;
	//
	//   //Label totalGamesPlayedDescriptionLabel = null;
	//   //Label totalGamesPlayedLabel = null;
	//
	//   //Label timesChallengedDescriptionLabel = null;
	//   //Label timesChallengedLabel = null;
	//
	//   //Label timesChallengerDescriptionLabel = null;
	//   //Label timesChallengerLabel = null;
	//
	//   //Label timesWonDescriptionLabel = null;
	//   //Label timesWonLabel = null;
	//
	//   //Label timesLostDescriptionLabel = null;
	//   //Label timesLostLabel = null;
	//
	//   //Label betsWonDescriptionLabel = null;
	//   //Label betsWonLabel= null;
	//
	//   //Label betsLostDescriptionLabel = null;
	//   //Label betsLostLabel = null;
	//
	//   //Label pointsEarnedDescriptionLabel = null;
	//   //Label pointsEarnedLabel = null;
	//
	//   //Label globalRankingDescriptionLabel = null;
	//   //Label globalRankingLabel = null;
	//
	//   //Label regionalRankingDescriptionLabel = null;
	//   //Label regionalRankingLabel = null;
	//
	//   //Label stepsWalkedDescriptionLabel = null;
	//   //Label stepsWalkedLabel= null;
	//
	//   //Label buttonsPushedDescriptionLabel = null;
	//   //Label buttonsPushedLabel = null;


	StatusPanel();


protected:
	virtual void doGoPremiumButton();


	virtual void doAddMoneyButton();


	virtual void doEditCharacterButton();


public:
	virtual void init() override;


	virtual void layout() override;


	virtual void setVisible(bool b) override;
};

