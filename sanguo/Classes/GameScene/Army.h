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
    void init(GameObjID oid, int nums, float xx, float yy);
public:
    virtual void setPosition(float xx, float yy);

	virtual float getPositionX() { return m_ptPos.x; }
	virtual float getPositionY() { return m_ptPos.y; }
    
    virtual void onIdle(int ot);
    
    virtual void release();
protected:
	Army(GameScene& scene, SoldierInfo& si);
    virtual ~Army();
protected:
    GameScene&              m_scene;
    SoldierInfo&            m_infoSoldier;
    
    std::vector<Person*>    m_lstPerson;
    
    cocos2d::Vec2           m_ptPos;
};

#endif // __GAMESCENE_ARMY_H__