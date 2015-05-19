#ifndef __GAMESCENE_PERSONMGR_H__
#define __GAMESCENE_PERSONMGR_H__

#include "cocos2d.h"
#include "BaseObj.h"
#include "Person.h"
#include "StaticPersonInfo.h"
#include <unordered_map>

USING_NS_CC;

class PersonMgr
{
public:
    static PersonMgr& getSingleton();
public:
    Person* newPerson(int personid);
protected:
	PersonMgr();
    virtual ~PersonMgr();
protected:
    std::unordered_map<int, StaticPersonInfo>   m_mapStaticPersonInfo;
};

#endif // __GAMESCENE_PERSONMGR_H__