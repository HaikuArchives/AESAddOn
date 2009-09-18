#include <StorageKit.h>
#include <TrackerAddOn.h>

#include "PAppWindow.h"

void process_refs(entry_ref ref, BMessage *msg, void *reserved)
{
	PAppWindow * prefsWindow = new PAppWindow(ref, msg);
	
	thread_id thread = prefsWindow->Thread();
	//wait for the window thread to return
	status_t win_status = B_OK;
	wait_for_thread(thread, &win_status);
}

int
main(int /*argc*/, char **/*argv*/)
{
	fprintf(stderr, "This can only be used as a Tracker add-on.\n");
	return -1; 
}
