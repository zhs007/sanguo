#include "GameScene.h"
#include "PersonMgr.h"

USING_NS_CC;

GameScene::GameScene()
    : m_pRoot(NULL)
    , m_pLayer(NULL)
{
    
}

GameScene::~GameScene()
{
    
}

void GameScene::init(Node* pRoot)
{
    m_pRoot = pRoot;
    
    m_pLayer = LayerCtrl::create();
    m_pLayer->setTouchesEnable(true);
    m_pRoot->addChild(m_pLayer);
    
    Sprite* pSprite = Sprite::create("res/worldmap.jpg");
    pSprite->setAnchorPoint(Vec2(0, 0));
    pSprite->setPosition(Vec2(0, 0));
    pSprite->setScale(2);
    m_pLayer->addChild(pSprite);
    
    //pLayer->setLayerSize(pSprite->getContentSize().width, pSprite->getContentSize().height);
    
    Rect rect;
    rect.origin.set(0, 0);
    rect.size.setSize(pSprite->getContentSize().width * 2, pSprite->getContentSize().height * 2);
    m_pLayer->SetLayerRect(rect);
    
    Person* pPerson = PersonMgr::getSingleton().newPerson(0);
    pPerson->init(0, *this);
    pPerson->setPosition(1000, 1000);
}

void GameScene::release()
{
    
}