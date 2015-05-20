#ifndef __GAMESCENE_BASEDEF_H__
#define __GAMESCENE_BASEDEF_H__

// GameObjID
// 在游戏里，所有的游戏对象都是有一个唯一静态ID，是对象唯一静态标示
// 简单起见，这个ID一定是8位数
//
// 首位为1表示这是一个内部对象
// 前4位为1000，表示这是一个角色资源，也就是PersonActionInfo里面的ID标示

const int _PERSON_DIR_NUMS              =	5;		//! 人物朝向

//! 人物动作类型
const int _PERSON_ACTION_WAIT			=	0;		//! 待机
const int _PERSON_ACTION_RUN			=	1;		//! 跑动
const int _PERSON_ACTION_WIN			=	2;		//! 胜利
const int _PERSON_ACTION_DEAD			=	3;		//! 死亡
const int _PERSON_ACTION_ATTACK			=	4;		//! 攻击
const int _PERSON_ACTION_CAST			=	5;		//! 施法
const int _PERSON_ACTION_HIT			=	6;		//! 受击
const int _PERSON_ACTION_FELL			=	7;		//! 击倒
const int _PERSON_ACTION_ASSAULT		=	8;		//! 冲锋
const int _PERSON_ACTION_ATTACK2		=	9;		//! 攻击2
const int _PERSON_ACTION_CHARGE			=	10;		//! 蓄力
const int _PERSON_ACTION_CHARGECAST		=	11;		//! 蓄力施法
const int _PERSON_ACTION_CAST2			=	12;		//! 施法2

const int _PERSON_ACTION_NUMS           =	13;		//! 动作数量

//! 动作是否循环
const bool _PERSON_ACTION_LOOP[] = {
    true,
    true,
    true,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    true
};

//! 英雄动作信息
struct _ActionInfo{
	int				id;
	std::string		img0;		//! 使用的图片
	std::string		img1;
	std::string		resname;	//! 资源名称
	int				stype;		//! 士兵类型 0普通 1弓箭

	int				bindex[_PERSON_ACTION_NUMS];	//! 动作起始帧
	int				eindex[_PERSON_ACTION_NUMS];	//! 动作结束帧
	int				atime[_PERSON_ACTION_NUMS];		//! 动作帧间间隔
};

#endif // __GAMESCENE_BASEDEF_H__