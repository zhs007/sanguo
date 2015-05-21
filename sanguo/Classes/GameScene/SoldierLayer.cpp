#include "SoldierLayer.h"
#include "Person.h"
#include "GameScene.h"

USING_NS_CC;

SoldierLayer::SoldierLayer()
	: m_sbnPerson(NULL)
{
}

SoldierLayer::~SoldierLayer()
{
    
}

//! 初始化
bool SoldierLayer::init()
{
    if (!cocos2d::Layer::init())
        return false;
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/soldier.plist", "res/soldier.pvr.ccz");
    
    //! 初始化人物的批量渲染资源
    Texture2D* persontex = Director::getInstance()->getTextureCache()->addImage("res/soldier.pvr.ccz");
    m_sbnPerson = SpriteBatchNode::createWithTexture(persontex);
    
    m_sbnPerson->setPosition(0, 0);
    addChild(m_sbnPerson);
    
    return true;
}

void SoldierLayer::releaseAllSoldier()
{
	if(m_sbnPerson != NULL)
	{
        removeChild(m_sbnPerson);

		m_sbnPerson = NULL;
	}
}

//! 创建一个人物 oid士兵ID camp阵营
Person* SoldierLayer::newSoldier(GameScene& scene, GameObjID oid, int camp)
{
	Person* pPerson = new Person(scene);
	
	if(pPerson->init(camp, oid, m_sbnPerson))
		return pPerson;

	return NULL;
}

//! 释放一个士兵
void SoldierLayer::deleteSoldier(Person* pPerson)
{
    if (pPerson != NULL)
        delete pPerson;
}
