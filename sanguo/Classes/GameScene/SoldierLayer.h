#ifndef __GAMESCENE_SOLDIERLAYER_H__
#define __GAMESCENE_SOLDIERLAYER_H__

#include "cocos2d.h"
#include "BaseDef.h"
#include "BaseObj.h"

USING_NS_CC;

class Person;
class GameScene;

class SoldierLayer : public cocos2d::Node
{
public:
    // implement the "static create()" method manually
    CREATE_FUNC(SoldierLayer);
public:
	void releaseAllSoldier();

	//! 创建一个士兵 oid士兵ID camp阵营
	Person* newSoldier(GameScene& scene, GameObjID oid, int camp);
    //! 释放一个士兵
    void deleteSoldier(Person* pPerson);
protected:
	SoldierLayer();
    virtual ~SoldierLayer();
    
    //! create时会自动调用初始化
    bool init();
protected:
	SpriteBatchNode*			m_sbnPerson;		//! 人物节点
};

#endif // __GAMESCENE_SOLDIERLAYER_H__