#ifndef __GAMESCENE_GAMESCENE_H__
#define __GAMESCENE_GAMESCENE_H__

#include "cocos2d.h"
#include "BaseObj.h"
#include "LayerCtrl.h"
#include "EffectLayer.h"
#include "SoldierLayer.h"
#include "GroundLayer.h"

USING_NS_CC;

class Army;

class GameScene : public LayerCtrl
{
public:
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
public:
    void initMap();
    
    void onIdle(float dt);
    
    void release();
public:
    void addArmy(int gameObjID, float xx, float yy);
    
    //! 新建一个士兵实例出来
    //! 注：一般来说，add这样开头的接口，表示生成的对象会被管理起来，而new这样的接口表示生成的对象需要自己来管理
    Person* newSoldier(GameObjID oid, int camp);
    //! 释放一个士兵实例
    void deleteSoldier(Person* pPerson);
    
    //! 添加一根箭
    void addArrow(float bx, float by, float ex, float ey, int movetime, int delay);
protected:
    GameScene();
    virtual ~GameScene();
    
    virtual bool init();
protected:
//    Node*               m_pRoot;
//    LayerCtrl*          m_pLayer;
    
    GroundLayer*        m_pLayerGround;
    EffectLayer*        m_pLayerEffect;
    SoldierLayer*       m_pLayerSoldier;
    
    std::vector<Army*>  m_lstArmy;
};

#endif // __GAMESCENE_GAMESCENE_H__