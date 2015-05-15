#ifndef __GAMESCENE_BASEDEF_H__
#define __GAMESCENE_BASEDEF_H__

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

#endif // __GAMESCENE_BASEDEF_H__