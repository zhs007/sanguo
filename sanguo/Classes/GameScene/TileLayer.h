#ifndef __GAMESCENE_TILELAYER_H__
#define __GAMESCENE_TILELAYER_H__

#include "cocos2d.h"
#include "BaseDef.h"

USING_NS_CC;

class TileLayer : public cocos2d::Node
{
public:
    // implement the "static create()" method manually
    CREATE_FUNC(TileLayer);
public:
    //! 计时
    void onIdle(int ot);
    
    float getWidth();
    
    float getHeight();
protected:
    TileLayer();
    virtual ~TileLayer();
    
    bool init();
protected:
    //Sprite*                     m_pBack;
    
    SpriteBatchNode*			m_sbnTile;		//! 地面节点
};

#endif	// __GAMESCENE_TILELAYER_H__
