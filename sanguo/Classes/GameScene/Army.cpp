#include "Army.h"
#include "Person.h"
#include "PersonMgr.h"
#include "GameScene.h"

USING_NS_CC;

Army::Army(GameScene& scene, SoldierInfo& si)
    : m_scene(scene)
    , m_infoSoldier(si)
{
}

Army::~Army()
{
}

void Army::init(GameObjID oid, int nums, float xx, float yy)
{
//    SoldierInfo* pSI = PersonMgr::getSingleton().getSoldierInfo(oid);
//    if (pSI == NULL)
//        return ;
    
    for (int i = 0; i < nums; ++i) {
        Person* pPerson = m_scene.newSoldier(m_infoSoldier.idActionInfo, 0);
        
        m_lstPerson.push_back(pPerson);
    }
    
    setPosition(xx, yy);
}

void Army::setPosition(float xx, float yy)
{
    m_ptPos.x = xx;
    m_ptPos.y = yy;
    
    int index = 0;
    for (std::vector<Person*>::iterator it = m_lstPerson.begin(); it != m_lstPerson.end(); ++it) {
        float ox = _ARMY_ARRAY[index * 2] * m_infoSoldier.minRadius;
        float oy = _ARMY_ARRAY[index * 2 + 1] * m_infoSoldier.minRadius;
        
        (*it)->setPosition(xx + ox, yy + oy);
        
        ++index;
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