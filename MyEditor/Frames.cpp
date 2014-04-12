#include "Frames.h"
#include "Canvas.h"
#include "iostream"
#include <fstream>
BEGIN_EVENT_TABLE(EditFrame, wxFrame)
  EVT_MENU(100, EditFrame::OnTest)
  EVT_MENU(101, EditFrame::OnSave)
END_EVENT_TABLE()

EditFrame::EditFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
  : wxFrame((wxFrame *)NULL, wxID_ANY, title, pos, size,
             wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE)
 {
	SetIcon(wxICON(sample));

	wxMenu *file_menu = new wxMenu;

	file_menu->Append(100, wxT("&Open\tF1"));
	file_menu->Append(101, wxT("&Save\tF2"));
	wxMenuBar *menu_bar = new wxMenuBar;

	menu_bar->Append(file_menu, wxT("&File"));
	m_canvas = new EditCanvas(this);
	SetMenuBar(menu_bar);
 }

void EditFrame::OnTest(wxCommandEvent& WXUNUSED(event) )
{
    wxFileDialog dialog(this);

    if (dialog.ShowModal() == wxID_OK)
    {
		m_canvas->lang.set(dialog.GetPath().c_str());
		m_canvas->Refresh();
    }
}

void EditFrame::OnSave(wxCommandEvent& WXUNUSED(event) )
{
	 wxFileDialog dialog(this,
                        wxT("±£´æ"),
                        wxEmptyString,
                        wxT("new.ai"),
                        wxT("Text files (*.ai)|*.ai"),
                        wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    dialog.SetFilterIndex(1);

    if (dialog.ShowModal() == wxID_OK)
    {
		std::string info = m_canvas->lang.toString();
		FILE *hp = fopen((const char*)dialog.GetPath().c_str(),"w");
		if (hp)
		{
			fwrite(info.c_str(),info.size(),1,hp);
			fclose(hp);
		}
	}
}