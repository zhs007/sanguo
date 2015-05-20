#ifndef __GAMESCENE_PERSON_H__
#define __GAMESCENE_PERSON_H__

#include "cocos2d.h"
#include "BaseObj.h"
#include "GameScene.h"
#include "BaseDef.h"

USING_NS_CC;

class Person : public BaseObj
{
    friend class PersonMgr;
public:
    bool init(int camp, int personid, Node* root);
public:
    virtual void setPosition(float xx, float yy);
protected:
	Person();
    virtual ~Person();

	//! 初始化资源
	void initRes();
	//! 刷新显示
	void refreshDisplay();
protected:
    Sprite*                     m_pSpr;
    std::vector<SpriteFrame*>	m_lstActionFrames[_PERSON_DIR_NUMS][_PERSON_ACTION_NUMS];	//! 动画数据

	Node*						m_pRoot;
	int							m_iCamp;		//! 阵营
	int							m_iID;
	_ActionInfo*				m_pActionInfo;	//! 动作信息

	//! 动作相关
	int							m_iAction;		//! 当前使用的动作
	int							m_iFrame;		//! 当前帧
	int							m_iDir;			//! 当前的方向 0-4
	int							m_iActTime;		//! 当前帧经过的时间
	bool						m_bFlip;		//! 是否翻转
};

#endif // __GAMESCENE_PERSON_H__