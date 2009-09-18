#ifndef _AESADDON_H
#define _AESADDON_H

#include <Application.h>
#include <StorageKit.h>
#include <TrackerAddOn.h>

class AESAddOn
	: public BApplication
{
public:
	AESAddOn();
	virtual void RefsReceived(BMessage *message);
	virtual void ReadyToRun();
	int32 ref_num;

private:
	PAppWindow * prefsWindow;
};

#endif
