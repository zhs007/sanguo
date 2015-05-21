#include "Army.h"
#include "Person.h"
#include "PersonMgr.h"
#include "GameScene.h"

USING_NS_CC;

Army::Army(GameScene& scene)
    : m_scene(scene)
{
}

Army::~Army()
{
}

void Army::init(GameObjID oid, float xx, float yy)
{
    Person* pPerson = m_scene.newSoldier(oid, 0);
    
    if(pPerson != NULL)
        pPerson->setPosition(xx, yy);
    
    pPerson->moveTo(xx + 100, yy + 200, 10);
    
    m_lstPerson.push_back(pPerson);
}

void Army::setPosition(float xx, float yy)
{
    m_ptPos.x = xx;
    m_ptPos.y = yy;
    
    for (std::vector<Person*>::iterator it = m_lstPerson.begin(); it != m_lstPerson.end(); ++it) {
        (*it)->setPosition(xx, yy);
    }
}

void Army::onIdle(int ot)
{
    for (std::vector<Person*>::iterator it = m_lstPerson.begin(); it != m_lstPerson.end(); ++it) {
        (*it)->onIdle(ot);
    }
}

void Army::release()
{
    for (std::vector<Person*>::iterator it = m_lstPerson.begin(); it != m_lstPerson.end(); ++it) {
        Person* pPerson = *it;
        
        pPerson->release();
        
        m_scene.deleteSoldier(pPerson);
    }
    
    m_lstPerson.clear();
}