#pragma once

class CodeNode;
class LangShow{
public:
	virtual void show(CodeNode * showL,int x,int y) = 0;
	virtual bool check(CodeNode *showL,int x,int y) = 0;
	virtual void showRelation(CodeNode *parent,CodeNode *first,CodeNode *second) = 0;
};

