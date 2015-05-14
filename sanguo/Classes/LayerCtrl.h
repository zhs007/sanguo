#ifndef __LAYERCTRL_H__
#define __LAYERCTRL_H__

#include "cocos2d.h"

USING_NS_CC;

class LayerCtrl : public cocos2d::Layer
{
public:
    static LayerCtrl* create();

	//! 设置图层的大小
	void setLayerSize(float width, float height);

	//! 设置场景的矩形
	void SetLayerRect(Rect rect);
	//! 设置最大的放大比例（默认为1.0f）
	void setMaxScale(float scale);
	//! 设置最小的缩小比例（如果不设置或者小于场景宽高，则根据场景宽高自行决定）
	void setMinScale(float scale);

	//! 缩放回弹相关
	//! 设置超过最大的回弹数据，exceed为允许超出的值，speed为超出后每秒恢复的值
	void setMaxRebound(float exceed, float speed);
	//! 设置超过最小的回弹数据，exceed为允许超出的值，speed为超出后每秒恢复的值
	void setMinRebound(float exceed, float speed);

	//! 设置是否使用滑动效果
	void setUseSlide(bool slide);

	//! 获取当前是否是按下状态（单点有效，如果鼠标按下但是移动超过一定范围，则不再视为鼠标按下）
	bool isTouch();

	//! 缩放到特定大小
	void scaleTo(float scale, float time, float cx, float cy);

	virtual void setPosition(const Vec2 &position);
	virtual void setScale(float scale);

	//! 要求允许多点触摸（目前仅解决Widget禁止多点触摸的问题）
	void setTouchesEnable(bool enabled);

protected:
	LayerCtrl();
    virtual ~LayerCtrl();
    
    virtual bool init();

	//! 鼠标
	void _onMouseScroll(Event *event);

	//! 触摸
	bool _onTouchBegan(Touch* touch, Event* event);
    void _onTouchMoved(Touch* touch, Event* event);
    void _onTouchEnded(Touch* touch, Event* event);

	void _onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
    void _onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
    void _onTouchesEnded(const std::vector<Touch*>& touches, Event* event);

	//! 计时
	void onIdle(float dt);

	//! 修正位置
	void fixPosition();
	//! 根据中心位置缩放
	void scaleLayer(float chgs, float cx, float cy);

protected:
	Rect		m_LayerRect;		//! 场景的矩形
	float		m_fMaxScale;		//! 最大的缩放比例
	float		m_fMinScale;		//! 最小的缩放比例

	bool		m_bTouch;			//! 是否是点击状态
	float		m_fTouchX;			//! 点击的位置
	float		m_fTouchY;

	float		m_fScaleX;			//! 缩放的位置
	float		m_fScaleY;

	//! 缩放回弹相关
	float		m_fExceedMax;		//! 允许超出最大的值
	float		m_fExceedMin;		//! 允许超出最小的值
	float		m_fResumeMax;		//! 超出最大的恢复速度
	float		m_fResumeMin;		//! 超出最大的恢复速度

	//! 滑动相关
	bool		m_bUseSlide;		//! 是否使用滑动效果
	Vec2		m_vecMoveDis;		//! 移动距离
	bool		m_bSlide;			//! 是否是滑动状态

	//! 缩放动画相关
	float		m_fScaleTime;		//! 缩放经历的时间
	float		m_fChgScale;		//! 每秒变化的大小
	float		m_fChgX;			//! 每秒位置的变化
	float		m_fChgY;
	float		m_fChgBeginX;		//! 变化初始的位置
	float		m_fChgBeginY;

	//! 图层相关
	float		m_fLayerWidth;		//! 图层大小
	float		m_fLayerHeight;
};

#endif // __LAYERCTRL_H__