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
    void init(GameObjID oid, float xx, float yy);
public:
    virtual void setPosition(float xx, float yy);

	virtual float getPositionX() { return 0.0f; }
	virtual float getPositionY() { return 0.0f; }
    
    virtual void onIdle(int ot);
    
    virtual void release();
protected:
	Army(GameScene& scene);
    virtual ~Army();
protected:
    GameScene&              m_scene;
    std::vector<Person*>    m_lstPerson;
};

#endif // __GAMESCENE_ARMY_H__