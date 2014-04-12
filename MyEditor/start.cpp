#include "wxCommon.h"
#include "Frames.h"

class EditApp : public wxApp
{
public:
    virtual bool OnInit()
	{
		if ( !wxApp::OnInit() )
			return false;

		EditFrame *frame = new EditFrame(wxT("Lang±à¼­Æ÷"),
									 wxDefaultPosition, wxSize(550, 840));
		frame->Show(true);

		return true;
	}

    virtual int OnExit()
	{
		return 1;
	}
};


IMPLEMENT_APP(EditApp)