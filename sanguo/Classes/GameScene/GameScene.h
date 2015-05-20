#ifndef __GAMESCENE_GAMESCENE_H__
#define __GAMESCENE_GAMESCENE_H__

#include "cocos2d.h"
#include "BaseObj.h"
#include "LayerCtrl.h"

USING_NS_CC;

class Army;

class GameScene
{
public:
	GameScene();
    virtual ~GameScene();
public:
    void init(Node* pRoot);
    
    void initMap();
    
    void onIdle(float dt);
    
    void release();
public:
    void addArmy(int gameObjID, float xx, float yy);
public:
    Node* getRoot() { return m_pLayer; }
protected:
    Node*               m_pRoot;
    LayerCtrl*          m_pLayer;
    
    std::vector<Army*>  m_lstArmy;
};

#endif // __GAMESCENE_GAMESCENE_H__