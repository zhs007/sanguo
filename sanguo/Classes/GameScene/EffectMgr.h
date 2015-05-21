#ifndef __GAMESCENE_EFFECTMGR_H__
#define __GAMESCENE_EFFECTMGR_H__

#include "cocos2d.h"
#include "BaseDef.h"

USING_NS_CC;

class EffectMgr
{
public:
    static EffectMgr& getSingleton();

	void init(Node* personode);
	void release();

	//! 计时
	void onIdle(int ot);

	//! 添加一根箭
	void addArrow(float bx, float by, float ex, float ey, int movetime, int delay);
	//! 释放所有的箭
	void releaseAllArrow();

protected:
	struct _ArrowData{
		Sprite*			sprite;
		int				delay;		//! 延迟时间

		float			bx;			//! 起点位置
		float			by;
		float			ex;			//! 终点位置
		float			ey;
		float			px1;		//! 控制点1
		float			py1;
		float			px2;		//! 控制点2
		float			py2;

		int				curtime;	//! 经过的时间
		int				alltime;	//! 总时间

		//! 动画计时，如果动画播放完成返回true
		bool onIdle(int ot);
		//! 释放
		void release();

		//! 计算角度
		float getRotate(float px, float py, float x, float y);
	};

	EffectMgr();
    virtual ~EffectMgr();

	//! 计时相关
	//! 弓箭计时
	void onIlde_Arrow(int ot);

protected:
	Node*			m_pPersonNode;		//! 人物节点


	std::list<_ArrowData>		m_lstArrow;			//! 弓箭效果
};

#endif	// __GAMESCENE_EFFECTMGR_H__