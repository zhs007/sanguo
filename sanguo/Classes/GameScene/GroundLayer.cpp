#include "GroundLayer.h"

USING_NS_CC;

//////////////////////////////////////////////////////////////////////////
//! GroundLayer

GroundLayer::GroundLayer()
    : m_pBack(NULL)
    , m_sbnGround(NULL)
{	
}

GroundLayer::~GroundLayer()
{
}

bool GroundLayer::init()
{
    if (!cocos2d::Node::init())
        return false;
    
    m_pBack = Sprite::create("res/worldmap.jpg");
    m_pBack->setAnchorPoint(Vec2(0, 0));
    m_pBack->setPosition(Vec2(0, 0));
    m_pBack->setScale(2);
    addChild(m_pBack);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/soldier.plist", "res/soldier.pvr.ccz");
    
    //! 初始化特效的批量渲染资源
    Texture2D* persontex = Director::getInstance()->getTextureCache()->addImage("res/soldier.pvr.ccz");
    m_sbnGround = SpriteBatchNode::createWithTexture(persontex);
    
    m_sbnGround->setPosition(0, 0);
    addChild(m_sbnGround);
    
    return true;
}

//! 计时
void GroundLayer::onIdle(int ot)
{
}

float GroundLayer::getWidth()
{
    if (m_pBack != NULL) {
        return m_pBack->getContentSize().width * 2;
    }
    
    return 0;
}

float GroundLayer::getHeight()
{
    if (m_pBack != NULL) {
        return m_pBack->getContentSize().height * 2;
    }
    
    return 0;
}
