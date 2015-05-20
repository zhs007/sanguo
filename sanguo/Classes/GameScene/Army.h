#ifndef __GAMESCENE_ARMY_H__
#define __GAMESCENE_ARMY_H__

#include "cocos2d.h"
#include "BaseObj.h"
#include "GameScene.h"
#include "BaseDef.h"

USING_NS_CC;

class Army : public BaseObj
{
public:
    void init(int personid, GameScene& scene);
public:
    virtual void setPosition(float xx, float yy);
protected:
	Army();
    virtual ~Army();
protected:
};

#endif // __GAMESCENE_ARMY_H__