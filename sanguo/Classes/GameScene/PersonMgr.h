#ifndef __GAMESCENE_PERSONMGR_H__
#define __GAMESCENE_PERSONMGR_H__

#include "cocos2d.h"
#include "BaseObj.h"
#include "Person.h"

USING_NS_CC;

class PersonMgr
{
public:
    static PersonMgr& getSingleton();
public:
	void release();
public:
	//! 初始化动作信息表
	void initActionInfo(const char* filename, bool refresh);
	//! 取动作信息
	PersonActionInfo* getActionInfo(GameObjID oid);

protected:
	PersonMgr();
    virtual ~PersonMgr();
protected:
	std::map<int, PersonActionInfo>	m_mapActionInfo;	//! 动作信息
};

#endif // __GAMESCENE_PERSONMGR_H__