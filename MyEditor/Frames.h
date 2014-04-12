#pragma once
#include "wxCommon.h"
class EditCanvas;
class EditFrame:public wxFrame
{
public:
	EditFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	void OnTest(wxCommandEvent& WXUNUSED(event) );
	void OnSave(wxCommandEvent& WXUNUSED(event) );
private:
    DECLARE_EVENT_TABLE()
	EditCanvas * m_canvas;
	wxPanel *m_panel;
};