#pragma once
#include "wxCommon.h"
#include "LangScript.h"
#include "Lang.h"
class Logics:public LangScript{

};

#define theXLang Script::getMe<Logics>()


class wxLangShow:public LangShow{
public:
	void show(CodeNode * show,int x,int y)
	{
		dc.SetFont( wxFont(12, wxMODERN, wxNORMAL, wxNORMAL, true) );
		std::string info = toInfo(show);

		dc.SetPen(*wxLIGHT_GREY_PEN);
		dc.SetBrush(*wxLIGHT_GREY_BRUSH);
        dc.DrawRectangle(x-3, y-5, info.size() * 15, 25);
		//dc.SetTextForeground(*wxBLACK);
		dc.DrawText(info.c_str(), x, y);
	}
	std::string toInfo(CodeNode *show)
	{
		std::string info;
		if (show->parent && (show->parent->nodeName=="or" || show->parent->nodeName=="and") )
		{
			if (*show->parent->childs.begin() == show)
			{
				info = "如果 ";
			}
			else
				info = "否则 ";
		}
		if (show->nodeName == "or")
			info += "选择(好) ";//+ show->getDescInfo();
		else if (show->nodeName == "and")
			info += "选择(坏) ";//+ show->getDescInfo();
		else if (show->nodeName == "calc")
			info += "计算 " + show->getDescInfo();
		else if (show->nodeName == "block")
			info += "执行 ";
		else if (show->nodeName == "code")
			info += "代码 " + show->getDescInfo();
		else	
			info += show->nodeName+show->getDescInfo();
		return info;
	}
	void showRelation(CodeNode *parent,CodeNode *first,CodeNode *second)
	{
		if (first && second)
		{
			if (parent->nodeName == "or" && parent != first)
				dc.SetPen(*wxRED_PEN);
			else if (parent->nodeName == "and" && parent != first)
				dc.SetPen(*wxYELLOW_PEN);
			else if (parent == first)
			{
				dc.SetPen(*wxLIGHT_GREY_PEN);
			}
			else
				dc.SetPen(*wxGREEN_PEN);
			dc.DrawLine(first->thisx - 3, first->thisy - 5 + 25, second->thisx-3, second->thisy);
		}
	}
	bool check(CodeNode *show,int x,int y)
	{
		std::string info = toInfo(show);
		int startx = show->thisx-3;int starty = show->thisy-5;
		int w = info.size() * 15; int h =  25;
		if (x >= startx && y >= starty && x <= startx + w && y <= starty + h)
		{
			return true;
		}
		return false;
	}
	wxDC &dc;
	wxLangShow(wxDC &dc):dc(dc){
	
	}
};

class ShowLang{
public:
	std::string name;
	wxDC * dc;
	ShowLang(wxDC *dc):dc(dc){}
	ShowLang(){dc = NULL;}
	void show()
	{
		wxLangShow s(*dc);
		if (name != "")
		{
			theXLang.showAll(&s);
		}
	}
	CodeNode* pick(int x,int y)
	{
		wxLangShow s(*dc);
		if (name != "")
		{
			theXLang.showAll(&s);
			return theXLang.pick(&s,x,y);
		}
		return NULL;
	}
	void set(const char * name)
	{
		this->name = name;
		theXLang.readFromFile(this->name.c_str());
	}
	std::string toString()
	{
		return theXLang.toString();
	}
};