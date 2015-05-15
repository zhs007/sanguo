#include "PersonMgr.h"

USING_NS_CC;

PersonMgr::PersonMgr()
{
    
}

PersonMgr::~PersonMgr()
{
    
}

PersonMgr& PersonMgr::getSingleton()
{
    static PersonMgr s_mgr;
    
    return s_mgr;
}

Person* PersonMgr::newPerson(int personid)
{
    Person* pPerson = new Person;
    
    return pPerson;
}