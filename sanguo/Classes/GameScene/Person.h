#ifndef __GAMESCENE_PERSON_H__
#define __GAMESCENE_PERSON_H__

#include "cocos2d.h"
#include "BaseObj.h"
#include "GameScene.h"
#include "BaseDef.h"

USING_NS_CC;

class Person : public BaseObj
{
    friend class SoldierLayer;
public:
    bool init(int camp, int personid, Node* root);

	virtual void release();
    
    //! 计时
    virtual void onIdle(int ot);
public:
    virtual void setPosition(float xx, float yy);

	virtual float getPositionX() { return m_fX; }
	virtual float getPositionY() { return m_fY; }

	//! 取当前的动作
	int getAction() { return m_iAction; }

	//! 朝向
	void dirTo(float xx, float yy);

	//! 移动相关
	//! 移动到 speed每秒钟移动的距离
	void moveTo(float ex, float ey, int speed);
	//! 停止
	void stop();
	//! 改变移动速度
	void chgSpeed(int speed);

	//! 攻击相关
	//! 攻击
	void attack(BaseObj* dest);
	void attack(float dx, float dy);

	//! 死亡
	void dead();
protected:
	Person(GameScene& scene);
    virtual ~Person();

	//! 初始化资源
	void initRes();
	//! 刷新显示
	void refreshDisplay();
	//! 改变动作
	void chgAction(int action, bool refresh = false);

	//! 计时相关
	//! 移动计时
	void onIdle_Move(int ot);
	//! 动作计时
	void onIdle_Action(int ot);
protected:
    GameScene&                  m_scene;
    
    Sprite*                     m_pSpr;
    std::vector<SpriteFrame*>	m_lstActionFrames[_PERSON_DIR_NUMS][_PERSON_ACTION_NUMS];	//! 动画数据

	Node*						m_pRoot;
	int							m_iCamp;		//! 阵营
	int							m_iID;
	PersonActionInfo*			m_pActionInfo;	//! 动作信息

	float						m_fX;			//! 坐标
	float						m_fY;

	//! 动作相关
	int							m_iAction;		//! 当前使用的动作
	int							m_iFrame;		//! 当前帧
	int							m_iDir;			//! 当前的方向 0-4
	int							m_iActTime;		//! 当前帧经过的时间
	bool						m_bFlip;		//! 是否翻转

	//! 移动相关
	float						m_fEX;				//! 终点坐标
	float						m_fEY;
	int							m_iMoveTime;		//! 移动时间（毫秒）
	int							m_iMoveSpeed;		//! 移动速度（每秒移动的距离）
	float						m_fMX;				//! 每毫秒移动的距离
	float						m_fMY;
	int							m_iRunActionTime;	//! 移动的帧间（随速度变化）
};

#endif // __GAMESCENE_PERSON_H__