#include "PersonMgr.h"
#include "Army.h"
#include "../BaseCSV.h"
#include "EffectMgr.h"

USING_NS_CC;

PersonMgr::PersonMgr()
	: m_sbnPerson(NULL)
{
    initActionInfo("actioninfo.csv", false);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/soldier.plist", "res/soldier.pvr.ccz");
}

PersonMgr::~PersonMgr()
{
    
}

PersonMgr& PersonMgr::getSingleton()
{
    static PersonMgr s_mgr;
    
    return s_mgr;
}

//! 初始化
void PersonMgr::init(Node* root)
{
	//! 初始化人物的批量渲染资源
	if(m_sbnPerson != NULL)
	{
		if(m_sbnPerson->getParent() != NULL)
		{
			if(m_sbnPerson->getParent() != root)
			{
				m_sbnPerson->getParent()->removeChild(m_sbnPerson);
				m_sbnPerson = NULL;
			}
		}
		else
		{
			m_sbnPerson = NULL;
		}
	}

	if(m_sbnPerson == NULL)
	{
		Texture2D* persontex = Director::getInstance()->getTextureCache()->addImage("res/soldier.pvr.ccz");
		m_sbnPerson = SpriteBatchNode::createWithTexture(persontex);

		m_sbnPerson->setPosition(0, 0);
		root->addChild(m_sbnPerson);
	}

	EffectMgr::getSingleton().init(m_sbnPerson);
}

void PersonMgr::release()
{
	EffectMgr::getSingleton().release();

	if(m_sbnPerson != NULL)
	{
		if(m_sbnPerson->getParent() != NULL)
			m_sbnPerson->getParent()->removeChild(m_sbnPerson);

		m_sbnPerson = NULL;
	}
}

Person* PersonMgr::newPerson(int personid)
{
    Person* pPerson = new Person;
    
    return pPerson;
}

void PersonMgr::deletePerson(Person* pPerson)
{
    delete pPerson;
}

//! 创建一个人物 camp阵营 id士兵ID
Person* PersonMgr::newPerson(int camp, int id)
{
	Person* pPerson = new Person;
	
	if(pPerson->init(camp, id, m_sbnPerson))
		return pPerson;

	return NULL;
}

//! 初始化动作信息表
void PersonMgr::initActionInfo(const char* filename, bool refresh)
{
	if(!m_mapActionInfo.empty() && !refresh)
		return ;

	BaseCSV csvdata;
	csvdata.load(filename);

	m_mapActionInfo.clear();

	//! 第一行是表头
	for(int i = 1; i < csvdata.m_iHeight; ++i)
	{
		std::pair<int, _ActionInfo> p;

		p.first = csvdata.getAsInt("gameobjid", i);

		p.second.id = p.first;
		p.second.img0 = csvdata.get("img0", i);
		p.second.img1 = csvdata.get("img1", i);
		p.second.resname = csvdata.get("resname", i);
		p.second.stype = csvdata.getAsInt("stype", i);

		char tmp[32];

		for(int j = 0; j < _PERSON_ACTION_NUMS; ++j)
		{
			sprintf(tmp, "bindex%d", j);
			p.second.bindex[j] = csvdata.getAsInt(tmp, i);

			sprintf(tmp, "eindex%d", j);
			p.second.eindex[j] = csvdata.getAsInt(tmp, i);

			sprintf(tmp, "time%d", j);
			p.second.atime[j] = csvdata.getAsInt(tmp, i);
		}

		m_mapActionInfo.insert(p);
	}
}

//! 取动作信息
_ActionInfo* PersonMgr::getActionInfo(int id)
{
	std::map<int, _ActionInfo>::iterator it = m_mapActionInfo.find(id);

	if(it != m_mapActionInfo.end())
		return &(it->second);

	return NULL;
}