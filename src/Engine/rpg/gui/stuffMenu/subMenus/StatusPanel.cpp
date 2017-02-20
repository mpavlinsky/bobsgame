#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger StatusPanel::log = Logger("StatusPanel");


StatusPanel::StatusPanel()
{ //=========================================================================================================================

	SubPanel();


	//
	//   Label* statusPanelLabel = new Label("Status");
	//   statusPanelLabel->setCanAcceptKeyboardFocus(false);
	//   statusPanelLabel->setTheme("bigLabel");
	//
	//
	//   //final BGClientEngine game = (BGClientEngine) g;
	//
	//
	//   string moneyToolTip = "";
	//   //				"Support \"bob\" ( That's me! ) by adding BobCoin$ to your account to buy more nD minigames and other stuff! (Coming Soon!)\n" +
	//   //				"\n"+
	//   //				"The games you buy can be played by your friends, even if they don't own them!\n" +
	//   //				"Plus, they're really cheap, and you can use them for bonuses in various places in the game.\n" +
	//   //				"\n"+
	//   //				"Have no money? ( That's OK, me too! ) Don't worry, you don't have to buy anything!!\n" +
	//   //				"You can compete in minigame bets and earn money through various tasks.\n"+
	//   //				"\n"+
	//   //				"Hate \"bob?\" and REFUSE to give him a SINGLE RED BOBCOIN?! ( That's OK, me too! )\n"+
	//   //				"The best revenge is to keep playing and tell everyone how terrible the game is so they come and play too!\n"+
	//   //				"All that grinding will swamp my servers and cost me tons of money, leaving me destitute and homeless- just like I always wanted!\n" +
	//   //				"It's win-win all around!"
	//   //				;
	//
	//   moneyDescriptionLabel = new Label("BobCoin$: ");
	//   moneyDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   moneyDescriptionLabel->setTheme("descriptionLabel");
	//   moneyLabel = new Label(" ");
	//   moneyLabel->setCanAcceptKeyboardFocus(false);
	//   moneyLabel->setTheme("valueLabel");
	//
	//   addMoneyButton = new Button("Support \"bob!\" - Add BobCoin$");
	//   addMoneyButton->setCanAcceptKeyboardFocus(false);
	//   addMoneyButton->setTheme("smallButton");
	//   //addMoneyButton.setTooltipContent(moneyToolTip);
	//   addMoneyButton->addCallback([&] ()
	//      {
	//         doAddMoneyButton();
	//      }
	//   );
	//
	//
	//   addMoneyButtonQuestionMark = new Label("?!");
	//   addMoneyButtonQuestionMark->setCanAcceptKeyboardFocus(false);
	//   addMoneyButtonQuestionMark->setTheme("bigLabel");
	//   addMoneyButtonQuestionMark->setTooltipContent(moneyToolTip);
	//   //--------
	//
	//
	//   string accountToolTip = string("Support \"bob\" with a BobPass for a one-time price of $12 a year.\n") + string("\n") + string("   - Avatar Vanity Plate* (Make everyone else jealous- the spice of life!)\n") + string("   - More Friends* - (Make my servers explode!)\n") + string("   - Forum Membership* - (Come and spew hatred where I could read it and ruin my day!)\n") + string("   - Bug Reports* - (See how much crap I have to fix! Pay to do work for me!)\n") + string("   - Beta Minigames* - (Play em' before they work!)\n") + string("   - Make A Custom Avatar - Coming Soon!\n") + string("   - Design And Script Your House - Coming Soon!\n") + string("   - Whatever else I come up with!\n") + string("\n") + string("Plus, I'll think you're really cool, and my intense psychic energy will \n") + string("resonate in the collective subconscious, improving your life telepathically!**\n") + string("\n") + string("\n") + string("*Features will be rolled out shortly!\n") + string("**Results may vary.");
	//   //"   - Bonus BobCoin$ Added To Your Account (Why the heck not!)\n" +
	//   accountTypeDescriptionLabel = new Label("Account Type: ");
	//   accountTypeDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   accountTypeDescriptionLabel->setTheme("descriptionLabel");
	//   accountTypeLabel = new Label(" ");
	//   accountTypeLabel->setCanAcceptKeyboardFocus(false);
	//   accountTypeLabel->setTheme("valueLabel");
	//
	//   goPremiumButton = new Button("Support \"bob!\" - Buy A BobPass");
	//   goPremiumButton->setCanAcceptKeyboardFocus(false);
	//   goPremiumButton->setTheme("smallButton");
	//   //goPremiumButton.setTooltipContent(accountToolTip);
	//   goPremiumButton->addCallback([&] ()
	//      {
	//         doGoPremiumButton();
	//      }
	//   );
	//
	//   goPremiumButtonQuestionMark = new Label("?!");
	//   goPremiumButtonQuestionMark->setCanAcceptKeyboardFocus(false);
	//   goPremiumButtonQuestionMark->setTheme("bigLabel");
	//   goPremiumButtonQuestionMark->setTooltipContent(accountToolTip);
	//   //---------
	//
	//
	//   //public String characterName = "";
	//
	//   characterNameDescriptionLabel = new Label("Character Name: ");
	//   characterNameDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   characterNameDescriptionLabel->setTheme("descriptionLabel");
	//   characterNameLabel = new Label(" ");
	//   characterNameLabel->setCanAcceptKeyboardFocus(false);
	//   characterNameLabel->setTheme("valueLabel");
	//
	//
	//   editCharacterButton = new Button("Edit Character");
	//   editCharacterButton->setCanAcceptKeyboardFocus(false);
	//   editCharacterButton->setTheme("smallButton");
	//   editCharacterButton->addCallback([&] ()
	//      {
	//         doEditCharacterButton();
	//      }
	//   );
	//
	//
	//   //public String emailAddress = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete emailAddressDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete emailAddressLabel;
	//   emailAddressDescriptionLabel = new Label("Email Address: ");
	//   emailAddressDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   emailAddressDescriptionLabel->setTheme("descriptionLabel");
	//   emailAddressLabel = new Label(" ");
	//   emailAddressLabel->setCanAcceptKeyboardFocus(false);
	//   emailAddressLabel->setTheme("valueLabel");
	//
	//
	//   //public long accountCreatedTime = 0;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete accountCreatedTimeDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete accountCreatedTimeLabel;
	//   accountCreatedTimeDescriptionLabel = new Label("Account Created Time: ");
	//   accountCreatedTimeDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   accountCreatedTimeDescriptionLabel->setTheme("descriptionLabel");
	//   accountCreatedTimeLabel = new Label(" ");
	//   accountCreatedTimeLabel->setCanAcceptKeyboardFocus(false);
	//   accountCreatedTimeLabel->setTheme("valueLabel");
	//
	//
	//   //public long lastLoginTime = 0;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete lastLoginTimeDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete lastLoginTimeLabel;
	//   lastLoginTimeDescriptionLabel = new Label("Last Login Time: ");
	//   lastLoginTimeDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   lastLoginTimeDescriptionLabel->setTheme("descriptionLabel");
	//   lastLoginTimeLabel = new Label(" ");
	//   lastLoginTimeLabel->setCanAcceptKeyboardFocus(false);
	//   lastLoginTimeLabel->setTheme("valueLabel");
	//
	//
	//   //public int timesLoggedIn = 0;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete timesLoggedInDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete timesLoggedInLabel;
	//   timesLoggedInDescriptionLabel = new Label("Times Logged In: ");
	//   timesLoggedInDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   timesLoggedInDescriptionLabel->setTheme("descriptionLabel");
	//   timesLoggedInLabel = new Label(" ");
	//   timesLoggedInLabel->setCanAcceptKeyboardFocus(false);
	//   timesLoggedInLabel->setTheme("valueLabel");
	//
	//
	//   //public String lastIP = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete lastIPDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete lastIPLabel;
	//   lastIPDescriptionLabel = new Label("Last IP Address: ");
	//   lastIPDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   lastIPDescriptionLabel->setTheme("descriptionLabel");
	//   lastIPLabel = new Label(" ");
	//   lastIPLabel->setCanAcceptKeyboardFocus(false);
	//   lastIPLabel->setTheme("valueLabel");
	//
	//
	//   accountPanelLabel = new Label("Account Stuff");
	//   accountPanelLabel->setCanAcceptKeyboardFocus(false);
	//   accountPanelLabel->setTheme("bigLabel");
	//
	//   //---------------------------------------------------------
	//   //account box
	//   //---------------------------------------------------------
	//
	//   accountDialogLayout = new DialogLayout();
	//   accountDialogLayout->setCanAcceptKeyboardFocus(false);
	//
	//   accountDialogLayout->setHorizontalGroup(accountDialogLayout->createParallelGroup(accountDialogLayout->createSequentialGroup().addGap().addWidget(accountPanelLabel).addGap(), accountDialogLayout->createSequentialGroup(accountDialogLayout->createParallelGroup(emailAddressDescriptionLabel, accountCreatedTimeDescriptionLabel, lastLoginTimeDescriptionLabel, timesLoggedInDescriptionLabel, lastIPDescriptionLabel), accountDialogLayout->createParallelGroup(emailAddressLabel, accountCreatedTimeLabel, lastLoginTimeLabel, timesLoggedInLabel, lastIPLabel))));
	//
	//   accountDialogLayout->setVerticalGroup(accountDialogLayout->createSequentialGroup(accountDialogLayout->createParallelGroup().addWidgets(accountPanelLabel), accountDialogLayout->createParallelGroup().addWidgets(emailAddressDescriptionLabel, emailAddressLabel), accountDialogLayout->createParallelGroup().addWidgets(accountCreatedTimeDescriptionLabel, accountCreatedTimeLabel), accountDialogLayout->createParallelGroup().addWidgets(lastLoginTimeDescriptionLabel, lastLoginTimeLabel), accountDialogLayout->createParallelGroup().addWidgets(timesLoggedInDescriptionLabel, timesLoggedInLabel), accountDialogLayout->createParallelGroup().addWidgets(lastIPDescriptionLabel, lastIPLabel)));
	//
	//
	//   //		//public String realName = "";
	//   //		realNameDescriptionLabel = null;
	//   //		realNameLabel = null;
	//   //		realNameDescriptionLabel = new Label("Real Name: ");
	//   //		realNameDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		realNameDescriptionLabel.setTheme("descriptionLabel");
	//   //		realNameLabel = new Label(" ");
	//   //		realNameLabel.setCanAcceptKeyboardFocus(false);
	//   //		realNameLabel.setTheme("valueLabel");
	//
	//
	//   //public long birthdayTime = 0;
	//   //		birthdayTimeDescriptionLabel = null;
	//   //		birthdayTimeLabel = null;
	//   //		birthdayTimeDescriptionLabel = new Label("Birthday Time: ");
	//   //		birthdayTimeDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		birthdayTimeDescriptionLabel.setTheme("descriptionLabel");
	//   //		birthdayTimeLabel = new Label(" ");
	//   //		birthdayTimeLabel.setCanAcceptKeyboardFocus(false);
	//   //		birthdayTimeLabel.setTheme("valueLabel");
	//
	//
	//   //public String postalCode = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete postalCodeDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete postalCodeLabel;
	//   postalCodeDescriptionLabel = new Label("Postal/Zip Code: ");
	//   postalCodeDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   postalCodeDescriptionLabel->setTheme("descriptionLabel");
	//   postalCodeLabel = new Label(" ");
	//   postalCodeLabel->setCanAcceptKeyboardFocus(false);
	//   postalCodeLabel->setTheme("valueLabel");
	//
	//   //public String countryName = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete countryNameDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete countryNameLabel;
	//   countryNameDescriptionLabel = new Label("Country Name: ");
	//   countryNameDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   countryNameDescriptionLabel->setTheme("descriptionLabel");
	//   countryNameLabel = new Label(" ");
	//   countryNameLabel->setCanAcceptKeyboardFocus(false);
	//   countryNameLabel->setTheme("valueLabel");
	//
	//   //public String isoCountryCode = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete isoCountryCodeDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete isoCountryCodeLabel;
	//   isoCountryCodeDescriptionLabel = new Label("Country Code: ");
	//   isoCountryCodeDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   isoCountryCodeDescriptionLabel->setTheme("descriptionLabel");
	//   isoCountryCodeLabel = new Label(" ");
	//   isoCountryCodeLabel->setCanAcceptKeyboardFocus(false);
	//   isoCountryCodeLabel->setTheme("valueLabel");
	//
	//   //public String placeName = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete placeNameDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete placeNameLabel;
	//   placeNameDescriptionLabel = new Label("Place Name: ");
	//   placeNameDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   placeNameDescriptionLabel->setTheme("descriptionLabel");
	//   placeNameLabel = new Label(" ");
	//   placeNameLabel->setCanAcceptKeyboardFocus(false);
	//   placeNameLabel->setTheme("valueLabel");
	//
	//
	//   //public String stateName = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete stateNameDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete stateNameLabel;
	//   stateNameDescriptionLabel = new Label("State Name: ");
	//   stateNameDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   stateNameDescriptionLabel->setTheme("descriptionLabel");
	//   stateNameLabel = new Label(" ");
	//   stateNameLabel->setCanAcceptKeyboardFocus(false);
	//   stateNameLabel->setTheme("valueLabel");
	//
	//
	//   //public float lat = 0;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete latDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete latLabel;
	//   latDescriptionLabel = new Label("Latitude: ");
	//   latDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   latDescriptionLabel->setTheme("descriptionLabel");
	//   latLabel = new Label(" ");
	//   latLabel->setCanAcceptKeyboardFocus(false);
	//   latLabel->setTheme("valueLabel");
	//
	//   //public float lon = 0;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete lonDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete lonLabel;
	//   lonDescriptionLabel = new Label("Longitude: ");
	//   lonDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   lonDescriptionLabel->setTheme("descriptionLabel");
	//   lonLabel = new Label(" ");
	//   lonLabel->setCanAcceptKeyboardFocus(false);
	//   lonLabel->setTheme("valueLabel");
	//
	//   //public int timeZone = 0;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete timeZoneDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete timeZoneLabel;
	//   timeZoneDescriptionLabel = new Label("Time Zone: ");
	//   timeZoneDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   timeZoneDescriptionLabel->setTheme("descriptionLabel");
	//   timeZoneLabel = new Label(" ");
	//   timeZoneLabel->setCanAcceptKeyboardFocus(false);
	//   timeZoneLabel->setTheme("valueLabel");
	//
	//
	//   locationPanelLabel = new Label("Location Stuff");
	//   locationPanelLabel->setCanAcceptKeyboardFocus(false);
	//   locationPanelLabel->setTheme("bigLabel");
	//
	//   //---------------------------------------------------------
	//   //location box
	//   //---------------------------------------------------------
	//
	//   locationDialogLayout = new DialogLayout();
	//   locationDialogLayout->setCanAcceptKeyboardFocus(false);
	//
	//   locationDialogLayout->setHorizontalGroup(locationDialogLayout->createParallelGroup(locationDialogLayout->createSequentialGroup().addGap().addWidget(locationPanelLabel).addGap(), locationDialogLayout->createSequentialGroup(locationDialogLayout->createParallelGroup(postalCodeDescriptionLabel, countryNameDescriptionLabel, isoCountryCodeDescriptionLabel, placeNameDescriptionLabel, stateNameDescriptionLabel, latDescriptionLabel, lonDescriptionLabel, timeZoneDescriptionLabel), locationDialogLayout->createParallelGroup(postalCodeLabel, countryNameLabel, isoCountryCodeLabel, placeNameLabel, stateNameLabel, latLabel, lonLabel, timeZoneLabel))));
	//
	//   locationDialogLayout->setVerticalGroup(locationDialogLayout->createSequentialGroup(locationDialogLayout->createParallelGroup().addWidgets(locationPanelLabel), locationDialogLayout->createParallelGroup().addWidgets(postalCodeDescriptionLabel, postalCodeLabel), locationDialogLayout->createParallelGroup().addWidgets(countryNameDescriptionLabel, countryNameLabel), locationDialogLayout->createParallelGroup().addWidgets(isoCountryCodeDescriptionLabel, isoCountryCodeLabel), locationDialogLayout->createParallelGroup().addWidgets(placeNameDescriptionLabel, placeNameLabel), locationDialogLayout->createParallelGroup().addWidgets(stateNameDescriptionLabel, stateNameLabel), locationDialogLayout->createParallelGroup().addWidgets(latDescriptionLabel, latLabel), locationDialogLayout->createParallelGroup().addWidgets(lonDescriptionLabel, lonLabel), locationDialogLayout->createParallelGroup().addWidgets(timeZoneDescriptionLabel, timeZoneLabel)));
	//
	//
	//   //public String facebookEmail = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookEmailDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookEmailLabel;
	//   facebookEmailDescriptionLabel = new Label("Facebook Email: ");
	//   facebookEmailDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   facebookEmailDescriptionLabel->setTheme("descriptionLabel");
	//   facebookEmailLabel = new Label(" ");
	//   facebookEmailLabel->setCanAcceptKeyboardFocus(false);
	//   facebookEmailLabel->setTheme("valueLabel");
	//
	//
	//   //public String facebookBirthday = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookBirthdayDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookBirthdayLabel;
	//   facebookBirthdayDescriptionLabel = new Label("Facebook Birthday: ");
	//   facebookBirthdayDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   facebookBirthdayDescriptionLabel->setTheme("descriptionLabel");
	//   facebookBirthdayLabel = new Label(" ");
	//   facebookBirthdayLabel->setCanAcceptKeyboardFocus(false);
	//   facebookBirthdayLabel->setTheme("valueLabel");
	//
	//
	//   //public String facebookFirstName = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookFirstNameDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookFirstNameLabel;
	//   facebookFirstNameDescriptionLabel = new Label("Facebook First Name: ");
	//   facebookFirstNameDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   facebookFirstNameDescriptionLabel->setTheme("descriptionLabel");
	//   facebookFirstNameLabel = new Label(" ");
	//   facebookFirstNameLabel->setCanAcceptKeyboardFocus(false);
	//   facebookFirstNameLabel->setTheme("valueLabel");
	//
	//
	//   //public String facebookLastName = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookLastNameDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookLastNameLabel;
	//   facebookLastNameDescriptionLabel = new Label("Facebook Last Name: ");
	//   facebookLastNameDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   facebookLastNameDescriptionLabel->setTheme("descriptionLabel");
	//   facebookLastNameLabel = new Label(" ");
	//   facebookLastNameLabel->setCanAcceptKeyboardFocus(false);
	//   facebookLastNameLabel->setTheme("valueLabel");
	//
	//
	//   //public String facebookGender = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookGenderDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookGenderLabel;
	//   facebookGenderDescriptionLabel = new Label("Facebook Gender: ");
	//   facebookGenderDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   facebookGenderDescriptionLabel->setTheme("descriptionLabel");
	//   facebookGenderLabel = new Label(" ");
	//   facebookGenderLabel->setCanAcceptKeyboardFocus(false);
	//   facebookGenderLabel->setTheme("valueLabel");
	//
	//
	//   //public String facebookLocale = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookLocaleDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookLocaleLabel;
	//   facebookLocaleDescriptionLabel = new Label("Facebook Locale: ");
	//   facebookLocaleDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   facebookLocaleDescriptionLabel->setTheme("descriptionLabel");
	//   facebookLocaleLabel = new Label(" ");
	//   facebookLocaleLabel->setCanAcceptKeyboardFocus(false);
	//   facebookLocaleLabel->setTheme("valueLabel");
	//
	//
	//   //public Float facebookTimeZone = 0.0f;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookTimeZoneDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookTimeZoneLabel;
	//   facebookTimeZoneDescriptionLabel = new Label("Facebook Time Zone: ");
	//   facebookTimeZoneDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   facebookTimeZoneDescriptionLabel->setTheme("descriptionLabel");
	//   facebookTimeZoneLabel = new Label(" ");
	//   facebookTimeZoneLabel->setCanAcceptKeyboardFocus(false);
	//   facebookTimeZoneLabel->setTheme("valueLabel");
	//
	//
	//   //public String facebookUsername = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookUsernameDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookUsernameLabel;
	//   facebookUsernameDescriptionLabel = new Label("Facebook Username: ");
	//   facebookUsernameDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   facebookUsernameDescriptionLabel->setTheme("descriptionLabel");
	//   facebookUsernameLabel = new Label(" ");
	//   facebookUsernameLabel->setCanAcceptKeyboardFocus(false);
	//   facebookUsernameLabel->setTheme("valueLabel");
	//
	//
	//   //public String facebookWebsite = "";
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookWebsiteDescriptionLabel;
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete facebookWebsiteLabel;
	//   facebookWebsiteDescriptionLabel = new Label("Facebook Website: ");
	//   facebookWebsiteDescriptionLabel->setCanAcceptKeyboardFocus(false);
	//   facebookWebsiteDescriptionLabel->setTheme("descriptionLabel");
	//   facebookWebsiteLabel = new Label(" ");
	//   facebookWebsiteLabel->setCanAcceptKeyboardFocus(false);
	//   facebookWebsiteLabel->setTheme("valueLabel");
	//
	//
	//   facebookPanelLabel = new Label("Facebook Stuff");
	//   facebookPanelLabel->setCanAcceptKeyboardFocus(false);
	//   facebookPanelLabel->setTheme("bigLabel");
	//
	//   //---------------------------------------------------------
	//   //facebook box
	//   //---------------------------------------------------------
	//
	//   facebookDialogLayout = new DialogLayout();
	//   facebookDialogLayout->setCanAcceptKeyboardFocus(false);
	//
	//   facebookDialogLayout->setHorizontalGroup(facebookDialogLayout->createParallelGroup(facebookDialogLayout->createSequentialGroup().addGap().addWidget(facebookPanelLabel).addGap(), facebookDialogLayout->createSequentialGroup(facebookDialogLayout->createParallelGroup(facebookEmailDescriptionLabel, facebookBirthdayDescriptionLabel, facebookFirstNameDescriptionLabel, facebookLastNameDescriptionLabel, facebookGenderDescriptionLabel, facebookLocaleDescriptionLabel, facebookTimeZoneDescriptionLabel, facebookUsernameDescriptionLabel, facebookWebsiteDescriptionLabel), facebookDialogLayout->createParallelGroup(facebookEmailLabel, facebookBirthdayLabel, facebookFirstNameLabel, facebookLastNameLabel, facebookGenderLabel, facebookLocaleLabel, facebookTimeZoneLabel, facebookUsernameLabel, facebookWebsiteLabel))));
	//
	//   facebookDialogLayout->setVerticalGroup(facebookDialogLayout->createSequentialGroup(facebookDialogLayout->createParallelGroup().addWidgets(facebookPanelLabel), facebookDialogLayout->createParallelGroup().addWidgets(facebookEmailDescriptionLabel, facebookEmailLabel), facebookDialogLayout->createParallelGroup().addWidgets(facebookBirthdayDescriptionLabel, facebookBirthdayLabel), facebookDialogLayout->createParallelGroup().addWidgets(facebookFirstNameDescriptionLabel, facebookFirstNameLabel), facebookDialogLayout->createParallelGroup().addWidgets(facebookLastNameDescriptionLabel, facebookLastNameLabel), facebookDialogLayout->createParallelGroup().addWidgets(facebookGenderDescriptionLabel, facebookGenderLabel), facebookDialogLayout->createParallelGroup().addWidgets(facebookLocaleDescriptionLabel, facebookLocaleLabel), facebookDialogLayout->createParallelGroup().addWidgets(facebookTimeZoneDescriptionLabel, facebookTimeZoneLabel), facebookDialogLayout->createParallelGroup().addWidgets(facebookUsernameDescriptionLabel, facebookUsernameLabel), facebookDialogLayout->createParallelGroup().addWidgets(facebookWebsiteDescriptionLabel, facebookWebsiteLabel)));
	//
	//
	//   //		playerGooglePlusNameDescriptionLabel = new Label("Google+ Name: ");
	//   //		playerGooglePlusNameDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		playerGooglePlusNameDescriptionLabel.setTheme("descriptionLabel");
	//   //		playerGooglePlusNameLabel = new Label("bobsgame");
	//   //		playerGooglePlusNameLabel.setCanAcceptKeyboardFocus(false);
	//   //		playerGooglePlusNameLabel.setTheme("valueLabel");
	//   //
	//   //		playerTwitterNameDescriptionLabel = new Label("Twitter Name: ");
	//   //		playerTwitterNameDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		playerTwitterNameDescriptionLabel.setTheme("descriptionLabel");
	//   //		playerTwitterNameLabel = new Label("bobsgame");
	//   //		playerTwitterNameLabel.setCanAcceptKeyboardFocus(false);
	//   //		playerTwitterNameLabel.setTheme("valueLabel");
	//   //
	//   //
	//   //		totalTimePlayedDescriptionLabel = new Label("Total Time Played: ");
	//   //		totalTimePlayedDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		totalTimePlayedDescriptionLabel.setTheme("descriptionLabel");
	//   //		totalTimePlayedLabel = new Label("20000:00");
	//   //		totalTimePlayedLabel.setCanAcceptKeyboardFocus(false);
	//   //		totalTimePlayedLabel.setTheme("valueLabel");
	//   //
	//   //		sessionTimePlayedDescriptionLabel = new Label("Time Played This Session: ");
	//   //		sessionTimePlayedDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		sessionTimePlayedDescriptionLabel.setTheme("descriptionLabel");
	//   //		sessionTimePlayedLabel = new Label("0:00");
	//   //		sessionTimePlayedLabel.setCanAcceptKeyboardFocus(false);
	//   //		sessionTimePlayedLabel.setTheme("valueLabel");
	//   //
	//   //		averageTimePlayedDescriptionLabel = new Label("Average Session Time: ");
	//   //		averageTimePlayedDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		averageTimePlayedDescriptionLabel.setTheme("descriptionLabel");
	//   //		averageTimePlayedLabel = new Label("0:02");
	//   //		averageTimePlayedLabel.setCanAcceptKeyboardFocus(false);
	//   //		averageTimePlayedLabel.setTheme("valueLabel");
	//   //
	//   //		gamesPurchasedDescriptionLabel = new Label("Games Purchased: ");
	//   //		gamesPurchasedDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		gamesPurchasedDescriptionLabel.setTheme("descriptionLabel");
	//   //		gamesPurchasedLabel = new Label("15");
	//   //		gamesPurchasedLabel.setCanAcceptKeyboardFocus(false);
	//   //		gamesPurchasedLabel.setTheme("valueLabel");
	//   //
	//   //		gamesSoldDescriptionLabel = new Label("Games Sold: ");
	//   //		gamesSoldDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		gamesSoldDescriptionLabel.setTheme("descriptionLabel");
	//   //		gamesSoldLabel = new Label("0");
	//   //		gamesSoldLabel.setCanAcceptKeyboardFocus(false);
	//   //		gamesSoldLabel.setTheme("valueLabel");
	//   //
	//   //		friendsInGameDescriptionLabel = new Label("Friends In Game: ");
	//   //		friendsInGameDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		friendsInGameDescriptionLabel.setTheme("descriptionLabel");
	//   //		friendsInGameLabel = new Label("1");
	//   //		friendsInGameLabel.setCanAcceptKeyboardFocus(false);
	//   //		friendsInGameLabel.setTheme("valueLabel");
	//   //
	//   //		totalGamesPlayedDescriptionLabel = new Label("Total Games Played: ");
	//   //		totalGamesPlayedDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		totalGamesPlayedDescriptionLabel.setTheme("descriptionLabel");
	//   //		totalGamesPlayedLabel = new Label("0");
	//   //		totalGamesPlayedLabel.setCanAcceptKeyboardFocus(false);
	//   //		totalGamesPlayedLabel.setTheme("valueLabel");
	//   //
	//   //		timesChallengedDescriptionLabel = new Label("Times Challenged By Others: ");
	//   //		timesChallengedDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		timesChallengedDescriptionLabel.setTheme("descriptionLabel");
	//   //		timesChallengedLabel = new Label("0");
	//   //		timesChallengedLabel.setCanAcceptKeyboardFocus(false);
	//   //		timesChallengedLabel.setTheme("valueLabel");
	//   //
	//   //		timesChallengerDescriptionLabel = new Label("Times Challenged Others: ");
	//   //		timesChallengerDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		timesChallengerDescriptionLabel.setTheme("descriptionLabel");
	//   //		timesChallengerLabel = new Label("0");
	//   //		timesChallengerLabel.setCanAcceptKeyboardFocus(false);
	//   //		timesChallengerLabel.setTheme("valueLabel");
	//   //
	//   //		timesWonDescriptionLabel = new Label("Times You Won: ");
	//   //		timesWonDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		timesWonDescriptionLabel.setTheme("descriptionLabel");
	//   //		timesWonLabel = new Label("99999");
	//   //		timesWonLabel.setCanAcceptKeyboardFocus(false);
	//   //		timesWonLabel.setTheme("valueLabel");
	//   //
	//   //		timesLostDescriptionLabel = new Label("Times You Lost: ");
	//   //		timesLostDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		timesLostDescriptionLabel.setTheme("descriptionLabel");
	//   //		timesLostLabel = new Label("0");
	//   //		timesLostLabel.setCanAcceptKeyboardFocus(false);
	//   //		timesLostLabel.setTheme("valueLabel");
	//   //
	//   //		betsWonDescriptionLabel = new Label("Bets Won: ");
	//   //		betsWonDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		betsWonDescriptionLabel.setTheme("descriptionLabel");
	//   //		betsWonLabel = new Label("99999");
	//   //		betsWonLabel.setCanAcceptKeyboardFocus(false);
	//   //		betsWonLabel.setTheme("valueLabel");
	//   //
	//   //		betsLostDescriptionLabel = new Label("Bets Lost: ");
	//   //		betsLostDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		betsLostDescriptionLabel.setTheme("descriptionLabel");
	//   //		betsLostLabel = new Label("0");
	//   //		betsLostLabel.setCanAcceptKeyboardFocus(false);
	//   //		betsLostLabel.setTheme("valueLabel");
	//   //
	//   //		pointsEarnedDescriptionLabel = new Label("Total Points Earned: ");
	//   //		pointsEarnedDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		pointsEarnedDescriptionLabel.setTheme("descriptionLabel");
	//   //		pointsEarnedLabel = new Label("99999999");
	//   //		pointsEarnedLabel.setCanAcceptKeyboardFocus(false);
	//   //		pointsEarnedLabel.setTheme("valueLabel");
	//   //
	//   //		globalRankingDescriptionLabel = new Label("Global Ranking: ");
	//   //		globalRankingDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		globalRankingDescriptionLabel.setTheme("descriptionLabel");
	//   //		globalRankingLabel = new Label("1st Place");
	//   //		globalRankingLabel.setCanAcceptKeyboardFocus(false);
	//   //		globalRankingLabel.setTheme("valueLabel");
	//   //
	//   //		regionalRankingDescriptionLabel = new Label("Regional Ranking: ");
	//   //		regionalRankingDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		regionalRankingDescriptionLabel.setTheme("descriptionLabel");
	//   //		regionalRankingLabel = new Label("1st Place");
	//   //		regionalRankingLabel.setCanAcceptKeyboardFocus(false);
	//   //		regionalRankingLabel.setTheme("valueLabel");
	//   //
	//   //		stepsWalkedDescriptionLabel = new Label("Total Steps Walked: ");
	//   //		stepsWalkedDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		stepsWalkedDescriptionLabel.setTheme("descriptionLabel");
	//   //		stepsWalkedLabel = new Label("2452757542");
	//   //		stepsWalkedLabel.setCanAcceptKeyboardFocus(false);
	//   //		stepsWalkedLabel.setTheme("valueLabel");
	//   //
	//   //		buttonsPushedDescriptionLabel = new Label("Total Buttons Pushed: ");
	//   //		buttonsPushedDescriptionLabel.setCanAcceptKeyboardFocus(false);
	//   //		buttonsPushedDescriptionLabel.setTheme("descriptionLabel");
	//   //		buttonsPushedLabel = new Label("32652357");
	//   //		buttonsPushedLabel.setCanAcceptKeyboardFocus(false);
	//   //		buttonsPushedLabel.setTheme("valueLabel");
	//
	//
	//   insideLayout->setHorizontalGroup(insideLayout->createParallelGroup(insideLayout->createSequentialGroup(insideLayout->createSequentialGroup().addGap(), insideLayout->createParallelGroup(insideLayout->createSequentialGroup().addGap().addWidget(statusPanelLabel).addGap(), insideLayout->createSequentialGroup(insideLayout->createSequentialGroup(insideLayout->createParallelGroup(characterNameDescriptionLabel, accountTypeDescriptionLabel), insideLayout->createParallelGroup(insideLayout->createSequentialGroup(characterNameLabel), insideLayout->createSequentialGroup(accountTypeLabel)), insideLayout->createParallelGroup(insideLayout->createSequentialGroup(editCharacterButton).addGap(), insideLayout->createSequentialGroup(goPremiumButton, goPremiumButtonQuestionMark).addGap()))), insideLayout->createSequentialGroup(accountDialogLayout), insideLayout->createSequentialGroup(locationDialogLayout), insideLayout->createSequentialGroup(facebookDialogLayout)), insideLayout->createSequentialGroup().addGap())));
	//   //,moneyDescriptionLabel
	//   //realNameDescriptionLabel,
	//   //birthdayTimeDescriptionLabel,
	//   //
	//   //																		playerFacebookNameDescriptionLabel,
	//   //																		playerGooglePlusNameDescriptionLabel,
	//   //																		playerTwitterNameDescriptionLabel,
	//   //																		totalTimePlayedDescriptionLabel,
	//   //																		sessionTimePlayedDescriptionLabel,
	//   //																		averageTimePlayedDescriptionLabel,
	//   //																		stepsWalkedDescriptionLabel,
	//   //																		buttonsPushedDescriptionLabel,
	//   //																		globalRankingDescriptionLabel,
	//   //																		regionalRankingDescriptionLabel,
	//   //																		pointsEarnedDescriptionLabel,
	//   //																		gamesPurchasedDescriptionLabel,
	//   //																		gamesSoldDescriptionLabel,
	//   //																		friendsInGameDescriptionLabel,
	//   //																		totalGamesPlayedDescriptionLabel,
	//   //																		timesChallengedDescriptionLabel,
	//   //																		timesChallengerDescriptionLabel,
	//   //																		timesWonDescriptionLabel,
	//   //																		timesLostDescriptionLabel,
	//   //																		betsWonDescriptionLabel,
	//   //																		betsLostDescriptionLabel
	//   //,insideLayout.createSequentialGroup(moneyLabel)
	//   //realNameLabel,
	//   //birthdayTimeLabel,
	//   //
	//   //																		playerFacebookNameLabel,
	//   //																		playerGooglePlusNameLabel,
	//   //																		playerTwitterNameLabel,
	//   //																		totalTimePlayedLabel,
	//   //																		sessionTimePlayedLabel,
	//   //																		averageTimePlayedLabel,
	//   //																		stepsWalkedLabel,
	//   //																		buttonsPushedLabel,
	//   //																		globalRankingLabel,
	//   //																		regionalRankingLabel,
	//   //																		pointsEarnedLabel,
	//   //																		gamesPurchasedLabel,
	//   //																		gamesSoldLabel,
	//   //																		friendsInGameLabel,
	//   //																		totalGamesPlayedLabel,
	//   //																		timesChallengedLabel,
	//   //																		timesChallengerLabel,
	//   //																		timesWonLabel,
	//   //																		timesLostLabel,
	//   //																		betsWonLabel,
	//   //																		betsLostLabel
	//   //insideLayout.createSequentialGroup(addMoneyButton,addMoneyButtonQuestionMark).addGap(),
	//
	//   insideLayout->setVerticalGroup(insideLayout->createSequentialGroup(insideLayout->createParallelGroup(insideLayout->createSequentialGroup(), insideLayout->createSequentialGroup(insideLayout->createSequentialGroup(statusPanelLabel), insideLayout->createSequentialGroup().addGap(), insideLayout->createParallelGroup(characterNameDescriptionLabel, characterNameLabel, editCharacterButton), insideLayout->createSequentialGroup().addGap(), insideLayout->createParallelGroup(accountTypeDescriptionLabel, accountTypeLabel, goPremiumButton, goPremiumButtonQuestionMark), insideLayout->createSequentialGroup().addGap(), insideLayout->createSequentialGroup().addGap(), insideLayout->createSequentialGroup(accountDialogLayout), insideLayout->createSequentialGroup().addGap(), insideLayout->createSequentialGroup(locationDialogLayout), insideLayout->createSequentialGroup().addGap(), insideLayout->createSequentialGroup(facebookDialogLayout)))));
	//   //insideLayout.createParallelGroup(editCharacterButton)
	//   //,
	//   //insideLayout.createSequentialGroup().addGap()
	//   //insideLayout.createParallelGroup(moneyDescriptionLabel,moneyLabel,addMoneyButton,addMoneyButtonQuestionMark),
	//   //insideLayout.createParallelGroup(realNameDescriptionLabel,            realNameLabel                ),
	//   //insideLayout.createParallelGroup(birthdayTimeDescriptionLabel,        birthdayTimeLabel            ),
	//   //								insideLayout.createParallelGroup(playerFacebookNameDescriptionLabel,		playerFacebookNameLabel),
	//   //								insideLayout.createParallelGroup(playerGooglePlusNameDescriptionLabel,		playerGooglePlusNameLabel),
	//   //								insideLayout.createParallelGroup(playerTwitterNameDescriptionLabel,		playerTwitterNameLabel),
	//   //								insideLayout.createParallelGroup(totalTimePlayedDescriptionLabel,		totalTimePlayedLabel),
	//   //								insideLayout.createParallelGroup(sessionTimePlayedDescriptionLabel,		sessionTimePlayedLabel),
	//   //								insideLayout.createParallelGroup(averageTimePlayedDescriptionLabel,		averageTimePlayedLabel),
	//   //								insideLayout.createParallelGroup(stepsWalkedDescriptionLabel,			stepsWalkedLabel),
	//   //								insideLayout.createParallelGroup(buttonsPushedDescriptionLabel,			buttonsPushedLabel),
	//   //								insideLayout.createParallelGroup(globalRankingDescriptionLabel,			globalRankingLabel),
	//   //								insideLayout.createParallelGroup(regionalRankingDescriptionLabel,		regionalRankingLabel),
	//   //								insideLayout.createParallelGroup(pointsEarnedDescriptionLabel,			pointsEarnedLabel),
	//   //								insideLayout.createParallelGroup(gamesPurchasedDescriptionLabel,		gamesPurchasedLabel),
	//   //								insideLayout.createParallelGroup(gamesSoldDescriptionLabel,				gamesSoldLabel),
	//   //								insideLayout.createParallelGroup(friendsInGameDescriptionLabel,			friendsInGameLabel),
	//   //								insideLayout.createParallelGroup(totalGamesPlayedDescriptionLabel,		totalGamesPlayedLabel),
	//   //								insideLayout.createParallelGroup(timesChallengedDescriptionLabel,		timesChallengedLabel),
	//   //								insideLayout.createParallelGroup(timesChallengerDescriptionLabel,		timesChallengerLabel),
	//   //								insideLayout.createParallelGroup(timesWonDescriptionLabel,				timesWonLabel),
	//   //								insideLayout.createParallelGroup(timesLostDescriptionLabel,				timesLostLabel),
	//   //								insideLayout.createParallelGroup(betsWonDescriptionLabel,				betsWonLabel),
	//   //								insideLayout.createParallelGroup(betsLostDescriptionLabel,				betsLostLabel)
}

void StatusPanel::doGoPremiumButton()
{ //=========================================================================================================================
	//
	//   if (Main::isApplet == true)
	//   {
	//      //open with javascript
	//
	//      URL* url = nullptr;
	//      try
	//      {
	//         url = new URL(string("http://www.bobsgame.com/buyBobPass.php?u=") + getGameSave()->userID);
	//      }
	//      catch (MalformedURLException e)
	//      {
	//         e->printStackTrace();
	//      }
	//
	//      Main::mainObject->getAppletContext().showDocument(url, "_blank");
	//   }
	//   else
	//   {
	//      try
	//      {
	//         //open browser window, we can't get it with JS as a desktop client so we need to redirect to PHP or something which stores it in SQL
	//         string url = string("http://www.bobsgame.com/buyBobPass.php?u=") + getGameSave()->userID;
	//
	//         java::awt::Desktop::getDesktop().browse(java::net::URI::create(url));
	//      }
	//      catch (java::io::IOException e)
	//      {
	//         log.error(string("Could not open browser: ") + e->getMessage());
	//      }
	//   }
}

void StatusPanel::doAddMoneyButton()
{ //=========================================================================================================================

	//
	//   if (Main::isApplet == true)
	//   {
	//      //open with javascript
	//
	//      URL* url = nullptr;
	//      try
	//      {
	//         url = new URL(string("http://www.bobsgame.com/buyBobCoins.php?u=") + getGameSave()->userID);
	//      }
	//      catch (MalformedURLException e)
	//      {
	//         e->printStackTrace();
	//      }
	//
	//      Main::mainObject->getAppletContext().showDocument(url, "_blank");
	//   }
	//   else
	//   {
	//      try
	//      {
	//         //open browser window, we can't get it with JS as a desktop client so we need to redirect to PHP or something which stores it in SQL
	//         string url = string("http://www.bobsgame.com/buyBobCoins.php?u=") + getGameSave()->userID;
	//
	//         java::awt::Desktop::getDesktop().browse(java::net::URI::create(url));
	//      }
	//      catch (java::io::IOException e)
	//      {
	//         log.error(string("Could not open browser: ") + e->getMessage());
	//      }
	//   }
}

void StatusPanel::doEditCharacterButton()
{ //=========================================================================================================================
	getStuffMenu()->setActivated(false);

	getPlayerEditMenu()->setActivated(true);
}

void StatusPanel::init()
{ //=========================================================================================================================
	SubPanel::init();
	//getGUI().setTooltipDelay(1);
}

void StatusPanel::layout()
{ //=========================================================================================================================

	//
	//   //Login panel is centered
	//
	//   //panel.adjustSize();
	//   //panel.setPosition(
	//   //insideScrollPaneLayout.getInnerX() + (insideScrollPaneLayout.getInnerWidth() - panel.getWidth()) / 2,
	//   //insideScrollPaneLayout.getInnerY() + (insideScrollPaneLayout.getInnerHeight() - panel.getHeight()) / 2);
	//
	//   if (facebookDialogLayout->isVisible() == true)
	//   {
	//      facebookDialogLayout->adjustSize();
	//   }
	//   else
	//   {
	//      facebookDialogLayout->setSize(0, 0);
	//   }

	SubPanel::layout();
}

void StatusPanel::setVisible(bool b)
{ //=========================================================================================================================
	SubPanel::setVisible(b);


	//
	//   if (b == true)
	//   {
	//      //String birthdayString = "?";
	//      //if(getGameSave()->birthdayTime>0)birthdayString = new SimpleDateFormat("yyyy-MM-dd").format(new Date(getGameSave()->birthdayTime));
	//
	//      string accountCreatedTimeString = "?";
	//      if (getGameSave()->accountCreatedTime > 0)
	//      {
	//         accountCreatedTimeString = (new SimpleDateFormat("yyyy-MM-dd-HH:mm"))->format(new Date(getGameSave()->accountCreatedTime));
	//      }
	//
	//      string lastLoginTimeString = "?";
	//      if (getGameSave()->lastLoginTime > 0)
	//      {
	//         lastLoginTimeString = (new SimpleDateFormat("yyyy-MM-dd-HH:mm"))->format(new Date(getGameSave()->lastLoginTime));
	//      }
	//
	//      string accountTypeString = ClientEngine()->getAccountTypeString(getGameSave()->accountType);
	//
	//
	//      string moneyString = string::format("%1$,.2f", getGameSave()->money);
	//
	//
	//      //update labels
	//      moneyLabel->setText(string("") + moneyString);
	//      accountTypeLabel->setText(string("") + accountTypeString);
	//
	//      characterNameLabel->setText(string("") + getGameSave()->characterName);
	//      emailAddressLabel->setText(string("") + getGameSave()->emailAddress);
	//
	//      accountCreatedTimeLabel->setText(string("") + accountCreatedTimeString);
	//      lastLoginTimeLabel->setText(string("") + lastLoginTimeString);
	//      timesLoggedInLabel->setText(string("") + getGameSave()->timesLoggedIn);
	//      lastIPLabel->setText(string("") + getGameSave()->lastIP);
	//      //realNameLabel.setText(""+getGameSave()->realName);
	//      //birthdayTimeLabel.setText(""+birthdayString);
	//      postalCodeLabel->setText(string("") + getGameSave()->postalCode);
	//      countryNameLabel->setText(string("") + getGameSave()->countryName);
	//      isoCountryCodeLabel->setText(string("") + getGameSave()->isoCountryCode);
	//      placeNameLabel->setText(string("") + getGameSave()->placeName);
	//      stateNameLabel->setText(string("") + getGameSave()->stateName);
	//      latLabel->setText(string("") + getGameSave()->lat);
	//      lonLabel->setText(string("") + getGameSave()->lon);
	//      timeZoneLabel->setText(string("") + to_string(Main::mainObject->timeZoneGMTOffset));
	//
	//      postalCodeLabel->setText(string("") + getGameSave()->postalCode);
	//      stateNameLabel->setText(string("") + getGameSave()->stateName);
	//      countryNameLabel->setText(string("") + getGameSave()->countryName);
	//
	//
	//      if (getGameSave()->facebookID.length() > 0)
	//      {
	//         facebookDialogLayout->setVisible(true);
	//
	//         facebookEmailLabel->setText(string("") + getGameSave()->facebookEmail);
	//         facebookBirthdayLabel->setText(string("") + getGameSave()->facebookBirthday);
	//         facebookFirstNameLabel->setText(string("") + getGameSave()->facebookFirstName);
	//         facebookLastNameLabel->setText(string("") + getGameSave()->facebookLastName);
	//         facebookGenderLabel->setText(string("") + getGameSave()->facebookGender);
	//         facebookLocaleLabel->setText(string("") + getGameSave()->facebookLocale);
	//         facebookTimeZoneLabel->setText(string("") + getGameSave()->facebookTimeZone);
	//         facebookUsernameLabel->setText(string("") + getGameSave()->facebookUsername);
	//         facebookWebsiteLabel->setText(string("") + getGameSave()->facebookWebsite);
	//      }
	//      else
	//      {
	//         facebookDialogLayout->setVisible(false);
	//      }
}

