#include "GameScene.h"

USING_NS_CC;

GameScene::GameScene()
    : m_pRoot(NULL)
    //, m_pLayer(NULL)
{
    
}

GameScene::~GameScene()
{
    
}

void GameScene::init(Node* pRoot)
{
    m_pRoot = pRoot;
    
    LayerCtrl* pLayer = LayerCtrl::create();
    pLayer->setTouchesEnable(true);
    m_pRoot->addChild(pLayer);
    
    Sprite* pSprite = Sprite::create("res/worldmap.jpg");
    pSprite->setAnchorPoint(Vec2(0, 0));
    pSprite->setPosition(Vec2(0, 0));
    pLayer->addChild(pSprite);
    
    //pLayer->setLayerSize(pSprite->getContentSize().width, pSprite->getContentSize().height);
    
    Rect rect;
    rect.origin.set(0, 0);
    rect.size.setSize(pSprite->getContentSize().width, pSprite->getContentSize().height);
    pLayer->SetLayerRect(rect);
}

void GameScene::release()
{
    
}