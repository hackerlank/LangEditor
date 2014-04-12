/**********************************************************************************
 * Author jijinlong Date 2014/3/30
 * email:jjl_2009_hi@163.com
 */
#pragma once

#include "Code.h"
#include "wxCommon.h"
class Script{
public:
	std::map<std::string,Code *> codes;
	typedef std::map<std::string,Code *>::iterator CODES_ITER;
	void clearCodes()
	{
		for (CODES_ITER iter = codes.begin(); iter != codes.end();++iter)
		{
			if (iter->second) delete iter->second;
		}
		codes.clear();
	}
	virtual void readFromFile(const std::string & fileName){}
	Code * findCode(const char *name)
	{
		CODES_ITER iter = codes.find(name);
		if (iter != codes.end()) return iter->second;
		return NULL;
	}
	template<typename CLASS>
	static CLASS & getMe(){
		static CLASS me;
		return me;
	}
	void exec(const char *name,Args*args)
	{
		Code * code = findCode(name);
		if (code)
		{
			code->exec(args);
		}
	}
	std::map<std::string,Code *> libs;
	Code * generate(const char *name)
	{
		if (!name ) return NULL;
		CODES_ITER iter = libs.find(name);
		if (iter != libs.end())
		{
			return iter->second->clone();
		}
		return NULL;
	}
	void addLib(const std::string &name,Code *code)
	{
		libs[name] = code;
	}
	virtual ~Script()
	{
		for (CODES_ITER iter = libs.begin(); iter != libs.end();++iter)
		{
			if (iter->second) delete iter->second;
		}
		for (CODES_ITER iter = codes.begin(); iter != codes.end();++iter)
		{
			if (iter->second) delete iter->second;
		}
		libs.clear();
		codes.clear();
	}
#if 1
	void showAll(LangShow *showL)
	{
		int y = 10;
		int x = 20;
		for (CODES_ITER iter = codes.begin(); iter != codes.end();++iter)
		{
			if (iter->second) 
				y = iter->second->code->show(showL,x,y);
			y += 30;
		}
	}
	CodeNode * pick(LangShow *showL,int x,int y)
	{
		for (CODES_ITER iter = codes.begin(); iter != codes.end();++iter)
		{
			if (iter->second)
			{
				CodeNode * node = iter->second->code->pick(showL,x,y);
				if (node) return node;
			}
		}
		return NULL;
	}
	std::string toString()
	{
		std::stringstream codeASS;
		for (CODES_ITER iter = codes.begin(); iter != codes.end();++iter)
		{
			if (iter->second)
			{
				CodeNode * node = iter->second->code;
				if (node) codeASS << node->toString();
			}
		}
		return codeASS.str();
	}
#endif
};

