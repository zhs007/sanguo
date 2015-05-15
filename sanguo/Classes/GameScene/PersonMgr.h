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
    Person* newPerson(int personid);
protected:
	PersonMgr();
    virtual ~PersonMgr();
protected:
};

#endif // __GAMESCENE_PERSONMGR_H__