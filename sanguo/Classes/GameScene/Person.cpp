#include "Person.h"

USING_NS_CC;

Person::Person()
    : m_pSpr(NULL)
{
    
}

Person::~Person()
{
    
}

void Person::init(int personid, GameScene& scene)
{
    m_pSpr = Sprite::create("res/bsoldier0_0_0.png");
    m_pSpr->setScale(0.5);
    
    scene.getRoot()->addChild(m_pSpr);
}

void Person::setPosition(float xx, float yy)
{
    m_pSpr->setPosition(xx, yy);
}