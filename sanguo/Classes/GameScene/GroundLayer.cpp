#include "GroundLayer.h"

USING_NS_CC;

//////////////////////////////////////////////////////////////////////////
//! GroundLayer

GroundLayer::GroundLayer()
    : m_pBack(NULL)
    , m_sbnGround(NULL)
    , m_sbnTile(NULL)
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
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/tile.plist", "res/tile.pvr.ccz");
    
    //! 初始化特效的批量渲染资源
    Texture2D* persontex = Director::getInstance()->getTextureCache()->addImage("res/soldier.pvr.ccz");
    m_sbnGround = SpriteBatchNode::createWithTexture(persontex);
    
    m_sbnGround->setPosition(0, 0);
    addChild(m_sbnGround);
    
    Texture2D* tileex = Director::getInstance()->getTextureCache()->addImage("res/tile.pvr.ccz");
    m_sbnTile = SpriteBatchNode::createWithTexture(tileex);
    
    m_sbnTile->setPosition(0, 0);
    addChild(m_sbnTile);
    
    return true;
}

void GroundLayer::initTile()
{
    SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("tile001.png");
    
    for (int y = 0; y < 100; ++y) {
        for (int x = 0; x < 100; ++x) {
            Sprite* pTile = Sprite::createWithSpriteFrame(frame);
            pTile->setAnchorPoint(Vec2(0, 0));
            pTile->setPosition(Vec2(16 * x, 16 * y));

            m_sbnTile->addChild(pTile);
        }
    }
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
