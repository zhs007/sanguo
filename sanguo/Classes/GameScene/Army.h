#ifndef __GAMESCENE_ARMY_H__
#define __GAMESCENE_ARMY_H__

#include "cocos2d.h"
#include "BaseObj.h"
#include "GameScene.h"
#include "BaseDef.h"

USING_NS_CC;

class Person;

class Army : public BaseObj
{
    friend class GameScene;
public:
    void init(int personid, float xx, float yy, GameScene& scene);
public:
    virtual void setPosition(float xx, float yy);
    
    virtual void onIdel(float dt);
    
    virtual void release();
protected:
	Army();
    virtual ~Army();
protected:
    std::vector<Person*>  m_lstPerson;
};

#endif // __GAMESCENE_ARMY_H__