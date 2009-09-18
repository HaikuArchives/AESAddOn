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
#include "constants.h"

#include "PAppWindow.h"

PAppWindow::PAppWindow(entry_ref ref, BMessage *msg)
	: BWindow(BRect(64,64,400,240), "DropAES", B_TITLED_WINDOW,B_NOT_RESIZABLE|B_NOT_ZOOMABLE|B_NOT_MINIMIZABLE)
{

	BView * MainView;
	MainView = new BView(Bounds(),"view",B_FOLLOW_ALL, 0);
	MainView->SetViewColor(ui_color (B_PANEL_BACKGROUND_COLOR));
	AddChild(MainView);

	BRadioButton *radio;
	radio = new BRadioButton(BRect(20, 20, 80, 40), NULL, "128Bit", new BMessage(STRENGTH128));
	radio->SetValue(true);
	MainView->AddChild(radio);
	
	radio = new BRadioButton(BRect(100, 20, 160, 40), NULL, "192Bit", new BMessage(STRENGTH192));
	MainView->AddChild(radio);
	
	radio = new BRadioButton(BRect(180, 20, 240, 40), NULL, "256Bit", new BMessage(STRENGTH256));
	MainView->AddChild(radio);

	keyField = new BTextControl(BRect(20, 50, 245, 90), NULL, "Key:", NULL, new BMessage(KEY));
	keyField->SetDivider(60);
	keyField->TextView()->HideTyping(true);
	MainView->AddChild(keyField);

	retypeField = new BTextControl(BRect(20, 90, 245, 90), NULL, "Retype:", NULL, new BMessage(KEY));
	retypeField->SetDivider(60);
	retypeField->TextView()->HideTyping(true);
	MainView->AddChild(retypeField);


	encryptButton = new BButton(BRect(20,140,100,160), "enb", "Encrypt", new BMessage(ENCRYPT), B_FOLLOW_LEFT | B_FOLLOW_TOP);
	MainView->AddChild(encryptButton);

	decryptButton = new BButton(BRect(120,140,200,160), "decb", "Decrypt", new BMessage(DECRYPT), B_FOLLOW_LEFT | B_FOLLOW_TOP);
	MainView->AddChild(decryptButton);

	cancelbutton = new BButton(BRect(240,140,320,160), "canbtn", "Cancel", new BMessage(BTN_CANCEL), B_FOLLOW_LEFT | B_FOLLOW_TOP);
	MainView->AddChild(cancelbutton);

	// set default encryption strength	
	strength = "128";
	
	Show();


		BMessage *message;
		message = msg;

		entry_ref fref;	
		BFile file;
		
	for(int32 count = 0 ; message->FindRef("refs", count, &fref) == B_OK ; count++) 
		{
			BEntry entry(&fref, true);
			BPath path;
			entry.GetPath(&path);
			fpath = path.Path();
		}
}

void PAppWindow::MessageReceived(BMessage *message) {
	switch(message->what) {
		case STRENGTH128:
			{
			strength = "128";
			break;
			}
		case STRENGTH192:
			{
			strength = "192";			
			break;
			}
		case STRENGTH256:
			{
			strength = "256";			
			break;
			}
		case BTN_CANCEL:
			Quit();
			break;
		case ENCRYPT:
			{
			if((strcmp(keyField->Text(), retypeField->Text()) != 0) || (strlen(keyField->Text()) < 1))
				{
					(new BAlert(NULL , "The keys do not match, or the fields are empty." , "Ok"))->Go();
				} else {
				key = keyField->Text();
				crypt = "-e";
				Aes();			
				}
			break;
			}
		case DECRYPT:
			{
			if((strcmp(keyField->Text(), retypeField->Text()) != 0) || (strlen(keyField->Text()) < 1))
				{
					(new BAlert(NULL , "The keys do not match, or the fields are empty." , "Ok"))->Go();
				} else {
				key = keyField->Text();
				crypt = "-d";
				Aes();			
				}
			break;
			}

		default:
			BWindow::MessageReceived(message);
			break;
	}
}





void PAppWindow::Aes()
{
	BString com = "rawaes ";
	com << crypt.String();
	com << strength.String();
	com << " ";
	com << key.String();
	com << " \"";
	com << fpath.String();
	com << "\"";
	com << " \"";
	com << fpath.String();
	com << "\"";
	
	system(com.String());
	Quit();
}
