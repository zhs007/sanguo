#ifndef __GAMESCENE_GAMESCENE_H__
#define __GAMESCENE_GAMESCENE_H__

#include "cocos2d.h"
#include "BaseObj.h"
#include "LayerCtrl.h"

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
protected:
    GameScene();
    virtual ~GameScene();
    
    virtual bool init();
protected:
//    Node*               m_pRoot;
//    LayerCtrl*          m_pLayer;
    
    std::vector<Army*>  m_lstArmy;
};

#endif // __GAMESCENE_GAMESCENE_H__