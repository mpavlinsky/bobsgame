//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class CreateNewAccount : public MenuPanel
{
	//EditField nameEditField;
public:

	static Logger log;


	//   EditField* emailEditField;
	//
	//   EditField* passwordEditField;
	//   EditField* confirmPasswordEditField;
	//
	//
	//   Button* okButton;
	//   Button* cancelButton;
	//
	//   string nameString = "";
	//
	//
	//   DialogLayout* panel;
	//   DialogLayout* emailDialogLayout;
	//   DialogLayout* passwordDialogLayout;
	//   DialogLayout* socialDialogLayout;
	//
	//   Label* errorLabel;
	//   Label* statusLabel;
	//
	//
	//   Label* emailLabel;
	//   Label* passwordLabel;
	//   Label* confirmPasswordLabel;
	//
	//
	CreateNewAccount();
	//
	//private:
	//   class CallbackAnonymousInnerClassHelper : public EditField::Callback
	//   {
	//   private:
	//      CreateNewAccount* outerInstance;
	//
	//   public:
	//      CallbackAnonymousInnerClassHelper(CreateNewAccount* outerInstance);
	//
	//      virtual void callback(int key) override;
	//   };
	//
	//private:
	//   class CallbackAnonymousInnerClassHelper2 : public EditField::Callback
	//   {
	//   private:
	//      CreateNewAccount* outerInstance;
	//
	//   public:
	//      CallbackAnonymousInnerClassHelper2(CreateNewAccount* outerInstance);
	//
	//      virtual void callback(int key);
	//   };
	//
	//private:
	//   class CallbackAnonymousInnerClassHelper3 : public EditField::Callback
	//   {
	//   private:
	//      CreateNewAccount* outerInstance;
	//
	//   public:
	//      CallbackAnonymousInnerClassHelper3(CreateNewAccount* outerInstance);
	//
	//      virtual void callback(int key);
	//   };


public:
	virtual void init();


	virtual void setButtonsVisible(bool b);


	virtual void onScrolledUp() override;


	virtual void doCancel();


	virtual void doCreateAccount();


protected:
	virtual void layout() override;


public:
	virtual void update() override;


	virtual void setActivated(bool b) override;


	virtual void renderBefore() override;


	virtual void render() override;
};

