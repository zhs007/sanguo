#ifndef __GAMESCENE_BASEDEF_H__
#define __GAMESCENE_BASEDEF_H__

// 命名习惯
// 1、Mgr类，都是singleton的，一般来说，只有全局唯一的而且不依赖任何其他类生存的类才是Mgr类
// 对其他类有依赖关系的，特别是对其他非singleton类有依赖关系的，都不应该是Mgr类
// 一般，纯静态类才会是Mgr类
// 2、生成对象的几种常用接口，new、add
// new表示仅仅产生对象，但并不会管理对象，需要自己手动管理对象
// add表示产生对象并关系对象，外部不需要过多的维护对象的生存周期

// GameObjID
// 在游戏里，所有的游戏对象都是有一个唯一静态ID，是对象唯一静态标示
// 简单起见，这个ID一定是8位数
//
// 首位为1表示这是一个内部对象
// 前4位为1000，表示这是一个角色资源，也就是PersonActionInfo里面的ID标示
// 前4位为1001，表示这是一个士兵

typedef int GameObjID;

//! 游戏场景Z轴划分
const int _GAMESCENE_Z_PERSONBOT	=	10000;	//! 人物脚下层（该值 - y）
const int _GAMESCENE_Z_PERSON		=	20000;	//! 人物层（该值 - y）
const int _GAMESCENE_Z_PERSONEFF	=	30000;	//! 人物效果层（该值 - y）

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
struct PersonActionInfo{
	GameObjID		oid;
    
	std::string		img0;		//! 使用的图片
	std::string		img1;
	std::string		resname;	//! 资源名称
	int				stype;		//! 士兵类型 0普通 1弓箭

	int				bindex[_PERSON_ACTION_NUMS];	//! 动作起始帧
	int				eindex[_PERSON_ACTION_NUMS];	//! 动作结束帧
	int				atime[_PERSON_ACTION_NUMS];		//! 动作帧间间隔
};

//! 士兵静态数据
struct SoldierInfo{
    GameObjID       oid;
    
    GameObjID       idActionInfo;       //! 对应的动画数据，由于可能多个士兵公用一套动画，所以这样设计
    
    int             minRadius;          //! 最小半径，进攻队列下，军团会挤到一起，这个是士兵的最小间距，像素单位
    int             maxRadius;          //! 最大半径，行军队列下，军团会被拉开，这个是士兵的最大间距，像素单位
    int             speed;              //! 行军速度，每秒位移多少像素
};

#endif // __GAMESCENE_BASEDEF_H__