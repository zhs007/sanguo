#include "GameScene.h"
#include "PersonMgr.h"
#include "Army.h"

USING_NS_CC;

GameScene::GameScene()
{
    
}

GameScene::~GameScene()
{
    
}

bool GameScene::init()
{
    if(!LayerCtrl::init())
        return false;
    
    //m_pRoot = pRoot;
    
    initMap();
    
    m_pLayerSoldier = SoldierLayer::create();
    m_pLayerEffect = EffectLayer::create();
    
    addChild(m_pLayerSoldier);
    addChild(m_pLayerEffect);
    
//    m_pLayer = LayerCtrl::create();
//    m_pLayer->setTouchesEnable(true);
//    m_pRoot->addChild(m_pLayer);
//    
//    Sprite* pSprite = Sprite::create("res/worldmap.jpg");
//    pSprite->setAnchorPoint(Vec2(0, 0));
//    pSprite->setPosition(Vec2(0, 0));
//    pSprite->setScale(2);
//    m_pLayer->addChild(pSprite);
//    
//    //pLayer->setLayerSize(pSprite->getContentSize().width, pSprite->getContentSize().height);
//    
//    Rect rect;
//    rect.origin.set(0, 0);
//    rect.size.setSize(pSprite->getContentSize().width * 2, pSprite->getContentSize().height * 2);
//    m_pLayer->SetLayerRect(rect);

	//PersonMgr::getSingleton().init(this);

	for(int i = 0; i < 10; ++i)
	{
//		Person* pPerson = PersonMgr::getSingleton().newPerson(0, 10000001 + i);
//
//		if(pPerson != NULL)
//			pPerson->setPosition(100 + i * 100, 100 + i * 100);
        
        addArmy(10000001 + i, 100 + i * 100, 100 + i * 100);
	}
    
    //Person* pPerson = PersonMgr::getSingleton().newPerson(0);
    //pPerson->init(0, *this);
    //pPerson->setPosition(1000, 1000);
    
    schedule(schedule_selector(GameScene::onIdle));
    
    return true;
}

void GameScene::initMap()
{
    m_pLayerGround = GroundLayer::create();
    addChild(m_pLayerGround);
    
    Rect rect;
    rect.origin.set(0, 0);
    rect.size.setSize(m_pLayerGround->getWidth(), m_pLayerGround->getHeight());
    SetLayerRect(rect);
}

void GameScene::onIdle(float dt)
{
    int ot = dt * 1000;
    
    for (std::vector<Army*>::iterator it = m_lstArmy.begin(); it != m_lstArmy.end(); ++it) {
        (*it)->onIdle(ot);
    }
}

void GameScene::release()
{
    for (std::vector<Army*>::iterator it = m_lstArmy.begin(); it != m_lstArmy.end(); ++it) {
        Army* pArmy = *it;
        
        pArmy->release();
        
        delete pArmy;
    }
    
    m_lstArmy.clear();
}

void GameScene::addArmy(int gameObjID, float xx, float yy)
{
    Army* pArmy = new Army(*this);
    pArmy->init(gameObjID, xx, yy);
    
    m_lstArmy.push_back(pArmy);
}

//! 新建一个士兵实例出来
//! 注：一般来说，add这样开头的接口，表示生成的对象会被管理起来，而new这样的接口表示生成的对象需要自己来管理
Person* GameScene::newSoldier(GameObjID oid, int camp)
{
    return m_pLayerSoldier->newSoldier(*this, oid, camp);
}

//! 释放一个士兵实例
void GameScene::deleteSoldier(Person* pPerson)
{
    m_pLayerSoldier->deleteSoldier(pPerson);
}

//! 添加一根箭
void GameScene::addArrow(float bx, float by, float ex, float ey, int movetime, int delay)
{
    m_pLayerEffect->addArrow(bx, by, ex, ey, movetime, delay);
}
