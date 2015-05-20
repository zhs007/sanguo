#include "Army.h"
#include "Person.h"
#include "PersonMgr.h"

USING_NS_CC;

Army::Army()
{
}

Army::~Army()
{
}

void Army::init(int personid, float xx, float yy, GameScene& scene)
{
    Person* pPerson = PersonMgr::getSingleton().newPerson(0, personid);
    
    if(pPerson != NULL)
        pPerson->setPosition(xx, yy);
    
    m_lstPerson.push_back(pPerson);
}

void Army::setPosition(float xx, float yy)
{
    for (std::vector<Person*>::iterator it = m_lstPerson.begin(); it != m_lstPerson.end(); ++it) {
        (*it)->setPosition(xx, yy);
    }
}

void Army::onIdel(float dt)
{
    for (std::vector<Person*>::iterator it = m_lstPerson.begin(); it != m_lstPerson.end(); ++it) {
        (*it)->onIdel(dt);
    }
}

void Army::release()
{
    for (std::vector<Person*>::iterator it = m_lstPerson.begin(); it != m_lstPerson.end(); ++it) {
        Person* pPerson = *it;
        
        pPerson->release();
        
        PersonMgr::getSingleton().deletePerson(pPerson);
    }
    
    m_lstPerson.clear();
}