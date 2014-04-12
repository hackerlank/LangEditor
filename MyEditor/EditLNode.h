#pragma once

#include "wxCommon.h"
#include "Lang.h"
class MyEditLangDialog : public wxDialog
{
public:
    MyEditLangDialog(wxWindow *parent,CodeNode*node);

    void OnAddFirst(wxCommandEvent& event);
	void OnAddNext(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
private:
    DECLARE_EVENT_TABLE()
	CodeNode *_nowNode;
	std::map<std::string,wxTextCtrl*> texts;
	wxRadioBox * m_icons;
	typedef std::map<std::string,wxTextCtrl*>::iterator TEXTS_ITER;

	wxTextCtrl *m_textMsg;
};