/**********************************************************************************
 * Author jijinlong Date 2014/3/30
 * email:jjl_2009_hi@163.com
 */
#pragma once

#include "LangCode.h"

#include "Script.h"
class LangScript:public Script{
public:
	void readFromFile(const std::string & fileName,bool clear = true)
	{
		if (clear)
			clearCodes();
		lang::NodeFile doc;
		lang::LNode * rootd = doc.read(fileName.c_str());
		parseLNode(rootd);
	}
	 CodeNode* readFromString(const std::string &info)
	{
		lang::NodeFile doc;
		lang::LNode * rootd = doc.readFromString(info);
		if (rootd)
		{
			lang::LNode* root = rootd->FirstChild();
			if(root)
			{
				LangCode * code = (LangCode*)generate("NPCLIB");
				CodeNode node;
				CodeNode*p = &node;
				p = code->parseNode(root,p);
				CodeNode * t = new CodeNode;
				*t = *p;
				return t;
			}
			delete rootd;
		}
		return NULL;
	}
	void parseLNode(lang::LNode *rootd)
	{
		if (rootd)
		{
			lang::LNode* root = rootd->FirstChild();
			while(root)
			{
				if (root->name == "code")
				{
					LangCode * code = (LangCode*)generate("NPCLIB");
					if (!code)
					{
						delete rootd;
							return;
					}
					CodeNode * node = code->traceNode(root);
					code->code = node;
					codes[root->get("name")] = code;
				}
				else if (root->name == "import")
				{
					readFromFile(dir + root->get("name"),false);	
				}
				root = root->Next();
			}
			delete rootd;
		}
	}
	std::string dir;
	virtual ~LangScript(){}
};


#define LANG_SCRIPT(CLASS)\
class CLASS:public LangCode{\
public:\
    CLASS(){\
		init();\
	};\
	LangCode * clone()\
	{\
		LangCode * code = new CLASS();\
		*code = *this;\
		return code;\
	}\
	void init();\
};\
AutoRunLang<CLASS> auto##CLASS(#CLASS);\
void CLASS::init()


#define LANG_SCRIPT_NAME(CLASS,NAME)\
class CLASS:public LangCode{\
public:\
    CLASS(){\
		init();\
	};\
	LangCode * clone()\
	{\
		LangCode * code = new CLASS();\
		*code = *this;\
		return code;\
	}\
	void init();\
};\
AutoRunLang<CLASS> auto##CLASS(NAME);\
void CLASS::init()

#define theLang Script::getMe<LangScript>()
template<typename CLASS>
class AutoRunLang{
public:
	AutoRunLang(const char *name)
	{
		theLang.addLib(name,new CLASS());
	}
};


#define LANG_SCRIPT_NEW(CLASS,MAN)\
class CLASS:public LangCode{\
public:\
    CLASS(){\
		init();\
	};\
	LangCode * clone()\
	{\
		LangCode * code = new CLASS();\
		*code = *this;\
		return code;\
	}\
	void init();\
};\
AutoRunLangNew<CLASS,MAN> auto##CLASS(#CLASS);\
void CLASS::init()

template<typename CLASS,typename MAN>
class AutoRunLangNew{
public:
	AutoRunLangNew(const char *name)
	{
		Script::getMe<MAN>().addLib(name,new CLASS());
	}
};
