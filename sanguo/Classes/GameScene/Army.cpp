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

void Army::init(GameObjID oid, int nums, float xx, float yy, float dirx, float diry)
{
    float a = atan(dirx / diry);
    m_quat.set(Vec3(0.0f, 0.0f, 1.0f), a);
    
    for (int i = 0; i < nums; ++i) {
        Person* pPerson = m_scene.newSoldier(m_infoSoldier.idActionInfo, 0);
        
        m_lstPerson.push_back(pPerson);
    }
    
    setPosition(xx, yy);
    
    int index = 0;
    for (std::vector<Person*>::iterator it = m_lstPerson.begin(); it != m_lstPerson.end(); ++it) {
        Vec3 pt;
        
        pt.x = _ARMY_ARRAY[index * 2] * m_infoSoldier.minRadius;
        pt.y = _ARMY_ARRAY[index * 2 + 1] * m_infoSoldier.minRadius + 1000;
        pt.z = 0.0f;
        
        pt = m_quat * pt;
        
        (*it)->moveTo(xx + pt.x, yy + pt.y, 10);
        
        ++index;
    }
}

void Army::setPosition(float xx, float yy)
{
    m_ptPos.x = xx;
    m_ptPos.y = yy;
    
    int index = 0;
    for (std::vector<Person*>::iterator it = m_lstPerson.begin(); it != m_lstPerson.end(); ++it) {
        Vec3 pt;
        
        pt.x = _ARMY_ARRAY[index * 2] * m_infoSoldier.minRadius;
        pt.y = _ARMY_ARRAY[index * 2 + 1] * m_infoSoldier.minRadius;
        pt.z = 0.0f;
        
        pt = m_quat * pt;
        
        (*it)->setPosition(xx + pt.x, yy + pt.y);
        
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