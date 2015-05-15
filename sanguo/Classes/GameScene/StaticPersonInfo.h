#ifndef __GAMESCENE_STATICPERSONINFO_H__
#define __GAMESCENE_STATICPERSONINFO_H__

#include "cocos2d.h"
#include "BaseDef.h"

USING_NS_CC;

class StaticPersonInfo
{
public:
    //! 角色动作信息（静态）
    struct _ActionInfo{
        int		bindex;		//! 起始帧
        int		eindex;		//! 结束帧
        int		nums;		//! 帧总数，如果为0表示没有该动作
        int		times;		//! 帧间的时间
        //bool	loop;		//! 是否循环
        
        _ActionInfo() : bindex(0), eindex(0), nums(0), times(0) {}
    };
public:
    StaticPersonInfo();
    ~StaticPersonInfo();
public:
    _ActionInfo			m_ActionInfos[_PERSON_ACTION_NUMS];		//! 动作信息
};

#endif // __GAMESCENE_STATICPERSONINFO_H__