#include "PersonMgr.h"
#include "../BaseCSV.h"

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

void PersonMgr::init()
{
    BaseCSV infoAction;
    
    infoAction.load("res/csv/actioninfo.csv");
    
    for (int y = 0; y < infoAction.getHeight(); ++y) {
        std::pair<int, StaticPersonInfo> spi;
        
        spi.first = spi.second.m_gameObjID = infoAction.getAsInt("gameobjid", y);
        
        spi.second.m_strImg[0] = infoAction.get("img0", y);
        spi.second.m_strImg[1] = infoAction.get("img1", y);
        
        spi.second.m_resname = infoAction.get("resname", y);
        
        for (int i = 0; i < _PERSON_ACTION_NUMS; ++i) {
            char str[128];
            
            sprintf(str, "bindex%d", i);
            spi.second.m_ActionInfos[i].bindex = infoAction.getAsInt(str, y);
            
            sprintf(str, "eindex%d", i);
            spi.second.m_ActionInfos[i].eindex = infoAction.getAsInt(str, y);
            
            sprintf(str, "time%d", i);
            spi.second.m_ActionInfos[i].times = infoAction.getAsInt(str, y);
            
            spi.second.m_ActionInfos[i].nums = spi.second.m_ActionInfos[i].eindex - spi.second.m_ActionInfos[i].bindex;
        }
        
        m_mapStaticPersonInfo.insert(spi);
    }
}
