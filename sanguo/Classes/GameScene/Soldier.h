#ifndef __GAMESCENE_SOLDIER_H__
#define __GAMESCENE_SOLDIER_H__

#include "cocos2d.h"
#include "BaseObj.h"
#include "GameScene.h"
#include "BaseDef.h"

USING_NS_CC;

class Person;

class Soldier : public BaseObj
{
    friend class GameScene;
public:
    void init(GameObjID oid, int nums, float xx, float yy, float dirx, float diry);
public:
    virtual void setPosition(float xx, float yy);
    
    virtual float getPositionX() { return m_ptPos.x; }
    virtual float getPositionY() { return m_ptPos.y; }
    
    virtual void onIdle(int ot);
    
    virtual void release();
protected:
    Soldier(GameScene& scene, SoldierInfo& si);
    virtual ~Soldier();
protected:
    GameScene&              m_scene;
    SoldierInfo&            m_infoSoldier;
    
    Person*                 m_pPerson;
    
    cocos2d::Vec2           m_ptPos;
    
    Quaternion              m_quat;
};


#endif
