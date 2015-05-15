#ifndef __GAMESCENE_PERSON_H__
#define __GAMESCENE_PERSON_H__

#include "cocos2d.h"
#include "BaseObj.h"
#include "GameScene.h"

USING_NS_CC;

class Person : public BaseObj
{
    friend class PersonMgr;
public:
    void init(int personid, GameScene& scene);
public:
    virtual void setPosition(float xx, float yy);
protected:
	Person();
    virtual ~Person();
protected:
    Sprite*     m_pSpr;
};

#endif // __GAMESCENE_PERSON_H__