#ifndef __GAMESCENE_PERSONMGR_H__
#define __GAMESCENE_PERSONMGR_H__

#include "cocos2d.h"
#include "BaseObj.h"
#include "Person.h"

USING_NS_CC;

class PersonMgr
{
public:
    static PersonMgr& getSingleton();
public:
	void init(Node* root);
	void release();

    Person* newPerson(int personid);
    
    void deletePerson(Person* pPerson);

	//! 创建一个人物 camp阵营 id士兵ID
	Person* newPerson(int camp, int id);

	//! 初始化动作信息表
	void initActionInfo(const char* filename, bool refresh);
	//! 取动作信息
	_ActionInfo* getActionInfo(int id);

protected:
	PersonMgr();
    virtual ~PersonMgr();

protected:
	std::map<int, _ActionInfo>	m_mapActionInfo;	//! 动作信息
	SpriteBatchNode*			m_sbnPerson;		//! 人物节点
};

#endif // __GAMESCENE_PERSONMGR_H__