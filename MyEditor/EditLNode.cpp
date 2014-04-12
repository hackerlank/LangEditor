#include "EditLNode.h"
#include "ShowLang.h"
void MyEditLangDialog::OnAddFirst(wxCommandEvent& WXUNUSED(event))
{
	if (m_textMsg)
	{
		CodeNode * node = theXLang.readFromString((const char*)m_textMsg->GetValue());
		if (node)
		_nowNode->addFirstChild(node);
	}
	Destroy();
}
void MyEditLangDialog::OnAddNext(wxCommandEvent& WXUNUSED(event))
{
	if (m_textMsg)
	{
		CodeNode * node = theXLang.readFromString((const char*)m_textMsg->GetValue());
		if (node)
		_nowNode->addNext(node);
	}
	Destroy();
}
void MyEditLangDialog::OnClose(wxCloseEvent& event)
{
	switch (m_icons->GetSelection())
	{
		case 0:
		{
			// 删除
			_nowNode->remove();
			delete _nowNode;
		}break;
		case 1:
		{
			for (TEXTS_ITER iter = texts.begin(); iter != texts.end();++iter)
			{
				_nowNode->propies.propies[iter->first] = iter->second->GetValue();
			}
		}break; // 编辑
	}
	
	EndModal(wxID_CANCEL);
	Destroy();
}
MyEditLangDialog::MyEditLangDialog(wxWindow *parent,CodeNode*node)
                : wxDialog(parent, wxID_ANY, wxString(wxT("编辑器")))
{
	wxBoxSizer *sizerTop = new wxBoxSizer(wxVERTICAL);
	_nowNode = node;
	sizerTop->Add(new wxStaticText(this, wxID_ANY, node->nodeName.c_str()),1,wxEXPAND | wxALL, 5);
	wxSizer * const sizerBtnsBox = new wxStaticBoxSizer(wxVERTICAL, this, "&属性列表");
	wxBoxSizer *sizerV = new wxBoxSizer(wxVERTICAL);
	for (std::map<std::string,std::string>::iterator it = node->propies.propies.begin(); it != node->propies.propies.end();++it)
	{
		wxBoxSizer *sizerTop = new wxBoxSizer(wxHORIZONTAL);
		if (it->second != "")
		{
			wxTextCtrl *text = new wxTextCtrl(this, wxID_ANY, it->second.c_str());
			texts[it->first] = text;
			sizerTop->Add(new wxStaticText(this, wxID_ANY, it->first.c_str()),1,wxEXPAND | wxALL, 5);
			sizerTop->Add(text,1,wxEXPAND | wxALL, 5);
		}
		else
		{
			wxTextCtrl *text = new wxTextCtrl(this, wxID_ANY, it->first.c_str());
			texts["VV"] = text;
			sizerTop->Add(text,1,wxEXPAND | wxALL, 5);
		}
		sizerV->Add(sizerTop, wxSizerFlags(1).Expand());

		sizerBtnsBox->Add(sizerV);//, wxSizerFlags(1).Expand());
	}
	{
		wxBoxSizer *sizerTop = new wxBoxSizer(wxHORIZONTAL);
		const wxString icons[] =
		{
			"&删除",
			"&编辑",
			"&增加",
		};

		m_icons = new wxRadioBox(this, wxID_ANY, "&编辑选项",
								 wxDefaultPosition, wxDefaultSize,
								 WXSIZEOF(icons), icons,
								 2, wxRA_SPECIFY_ROWS);
		m_icons->SetSelection(2);
		sizerTop->Add(m_icons, wxSizerFlags().Expand().Border());

		sizerBtnsBox->Add(sizerTop);
		sizerBtnsBox->SetMinSize(500,100);
	}
	wxSizer * const AddBtns = new wxStaticBoxSizer(wxVERTICAL, this, "&增加");
	if (AddBtns)
	{
		wxBoxSizer *sizerTop = new wxBoxSizer(wxVERTICAL);

		m_textMsg = new wxTextCtrl(this, wxID_ANY, "",
                               wxDefaultPosition, wxSize(400,200),
                               wxTE_MULTILINE);

		sizerTop->Add(m_textMsg,wxSizerFlags().Centre());
		wxBoxSizer *sizerTop1 = new wxBoxSizer(wxHORIZONTAL);
		sizerTop1->Add(new wxButton(this, 122, "&首子"),
                   wxSizerFlags().Centre());
		sizerTop1->Add(new wxButton(this, 123, "&下任"),
                   wxSizerFlags().Centre());
		sizerTop->Add(sizerTop1);
		AddBtns->Add(sizerTop);
		sizerTop->SetMinSize(500,210);
	}
	sizerTop->Add(sizerBtnsBox);
	sizerTop->Add(AddBtns);
	SetSizerAndFit(sizerTop,false);
	this->SetSize(300,600);
}
BEGIN_EVENT_TABLE(MyEditLangDialog, wxDialog)
    EVT_BUTTON(122, MyEditLangDialog::OnAddFirst)
	EVT_BUTTON(123, MyEditLangDialog::OnAddNext)
	EVT_CLOSE(MyEditLangDialog::OnClose)
END_EVENT_TABLE()