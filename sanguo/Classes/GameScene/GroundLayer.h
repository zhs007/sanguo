#ifndef __GAMESCENE_GROUNDLAYER_H__
#define __GAMESCENE_GROUNDLAYER_H__

#include "cocos2d.h"
#include "BaseDef.h"

USING_NS_CC;

class GroundLayer : public cocos2d::Node
{
public:
    // implement the "static create()" method manually
    CREATE_FUNC(GroundLayer);
public:
	//! 计时
	void onIdle(int ot);
    
    float getWidth();
    
    float getHeight();
    
    void initTile();
protected:
	GroundLayer();
    virtual ~GroundLayer();
    
    bool init();
protected:
    Sprite*                     m_pBack;
    
    SpriteBatchNode*			m_sbnGround;		//! 地面节点
    SpriteBatchNode*			m_sbnTile;          //! tile节点
};

#endif	// __GAMESCENE_GROUNDLAYER_H__
