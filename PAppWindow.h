#ifndef _PAPPW_H
#define _PAPPW_H

#include <Window.h>
#include <String.h>
#include <Application.h>
#include <Button.h>
#include <Slider.h>
#include <File.h>
#include <Roster.h>
#include <Entry.h>
#include <stdlib.h>
#include <Path.h>
#include <File.h>
#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include <StringView.h>
#include <Alert.h>
#include <View.h>
#include <RadioButton.h>
#include <InterfaceDefs.h>
#include <TextControl.h>
#include <Message.h>

class PAppWindow
	: public BWindow
{
public:
	PAppWindow(entry_ref ref, BMessage *msg);
	virtual void Aes();
	virtual void MessageReceived(BMessage *message);

private:
	BTextControl *keyField;
	BTextControl *retypeField;
	
	BButton * encryptButton;
	BButton * decryptButton;
	BButton * cancelbutton;	
	
	BString fpath;
	BString strength;
	BString key;
	BString crypt;
};

#endif
