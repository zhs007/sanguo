#include "LayerCtrl.h"
#include "ui/UIWidget.h"

USING_NS_CC;

const float _ADDMAXSCALE		=	0.2f;		//! 超出最大放大大小的比例
const float _ADDMINSCALE		=	0.05f;		//! 超出最小放大大小的比例

const float _MAXRESUME_SPEED	=	0.6f;		//! 超出最大恢复比例的速度（每秒）
const float _MINRESUME_SPEED	=	0.4f;		//! 超出最小恢复比例的速度（每秒）

LayerCtrl* LayerCtrl::create()
{
    LayerCtrl* ret = new LayerCtrl();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

LayerCtrl::LayerCtrl()
	: m_fMaxScale(1.0f)
	, m_fMinScale(0.0f)
	, m_bTouch(false)
	, m_bUseSlide(true)
	, m_bSlide(false)
	, m_fScaleTime(0.0f)
	, m_fChgScale(0.0f)
	, m_fScaleX(0.0f)
	, m_fScaleY(0.0f)
{
	setMaxRebound(_ADDMAXSCALE, _MAXRESUME_SPEED);
	setMinRebound(_ADDMINSCALE, _MINRESUME_SPEED);
}

LayerCtrl::~LayerCtrl()
{
}

bool LayerCtrl::init()
{
    if(Layer::init())
    {
		auto mouseListener = EventListenerMouse::create();
		mouseListener->onMouseScroll = CC_CALLBACK_1(LayerCtrl::_onMouseScroll, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

		auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(false);
		touchListener->onTouchBegan = CC_CALLBACK_2(LayerCtrl::_onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(LayerCtrl::_onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(LayerCtrl::_onTouchEnded, this);
		touchListener->onTouchCancelled = CC_CALLBACK_2(LayerCtrl::_onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

		auto touchesListener = EventListenerTouchAllAtOnce::create();
		touchesListener->onTouchesBegan = CC_CALLBACK_2(LayerCtrl::_onTouchesBegan, this);
		touchesListener->onTouchesMoved = CC_CALLBACK_2(LayerCtrl::_onTouchesMoved, this);
		touchesListener->onTouchesEnded = CC_CALLBACK_2(LayerCtrl::_onTouchesEnded, this);
		touchesListener->onTouchesCancelled = CC_CALLBACK_2(LayerCtrl::_onTouchesEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchesListener, this);

		schedule(schedule_selector(LayerCtrl::onIdle));

		Size visibleSize = Director::getInstance()->getVisibleSize();

		m_fLayerWidth = visibleSize.width;
		m_fLayerHeight = visibleSize.height;

        return true;
    }

    return false;
}

//! 设置图层的大小
void LayerCtrl::setLayerSize(float width, float height)
{
	m_fLayerWidth = width;
	m_fLayerHeight = height;
}

//! 设置场景的矩形
void LayerCtrl::SetLayerRect(Rect rect)
{
	m_LayerRect = rect;

	//setAnchorPoint(rect.origin);
	setAnchorPoint(Vec2(0, 0));
	setContentSize(rect.size);

	//scaleTo(0.1f, 10.0f, 2000.0f, 1300.0f);

	if(m_LayerRect.size.width != 0.0f && m_LayerRect.size.height != 0.0f)
	{
		//Size visibleSize = Director::getInstance()->getVisibleSize();

		if(m_LayerRect.size.width * m_fMaxScale < m_fLayerWidth)
			m_fMaxScale = m_fLayerWidth / m_LayerRect.size.width;

		if(m_LayerRect.size.height * m_fMaxScale < m_fLayerHeight)
			m_fMaxScale = m_fLayerHeight / m_LayerRect.size.height;
	}

	if(m_LayerRect.size.width != 0.0f && m_LayerRect.size.height != 0.0f)
	{
		//Size visibleSize = Director::getInstance()->getVisibleSize();

		if(m_LayerRect.size.width * m_fMinScale < m_fLayerWidth)
			m_fMinScale = m_fLayerWidth / m_LayerRect.size.width;

		if(m_LayerRect.size.height * m_fMinScale < m_fLayerHeight)
			m_fMinScale = m_fLayerHeight / m_LayerRect.size.height;
	}
}

//! 设置最大的放大比例（默认为1.0f）
void LayerCtrl::setMaxScale(float scale)
{
	if(m_LayerRect.size.width != 0.0f && m_LayerRect.size.height != 0.0f)
	{
		//Size visibleSize = Director::getInstance()->getVisibleSize();

		if(m_LayerRect.size.width * scale < m_fLayerWidth)
			scale = m_fLayerWidth / m_LayerRect.size.width;

		if(m_LayerRect.size.height * scale < m_fLayerHeight)
			scale = m_fLayerHeight / m_LayerRect.size.height;
	}

	m_fMaxScale = scale;
}

//! 设置最小的缩小比例（如果不设置或者小于场景宽高，则根据场景宽高自行决定）
void LayerCtrl::setMinScale(float scale)
{
	if(m_LayerRect.size.width != 0.0f && m_LayerRect.size.height != 0.0f)
	{
		//Size visibleSize = Director::getInstance()->getVisibleSize();

		if(m_LayerRect.size.width * scale < m_fLayerWidth)
			scale = m_fLayerWidth / m_LayerRect.size.width;

		if(m_LayerRect.size.height * scale < m_fLayerHeight)
			scale = m_fLayerHeight / m_LayerRect.size.height;
	}

	m_fMinScale = scale;
}

//! 设置超过最大的回弹数据，exceed为允许超出的值，speed为超出后每秒恢复的值
void LayerCtrl::setMaxRebound(float exceed, float speed)
{
	m_fExceedMax = exceed;
	m_fResumeMax = speed;
}

//! 设置超过最小的回弹数据，exceed为允许超出的值，speed为超出后每秒恢复的值
void LayerCtrl::setMinRebound(float exceed, float speed)
{
	m_fExceedMin = exceed;
	m_fResumeMin = speed;
}

//! 设置是否使用滑动效果
void LayerCtrl::setUseSlide(bool slide)
{
	m_bUseSlide = slide;
}

//! 获取当前是否是按下状态（单点有效，如果鼠标按下但是移动超过一定范围，则不再视为鼠标按下）
bool LayerCtrl::isTouch()
{
	return m_bTouch;
}

//! 缩放到特定大小
void LayerCtrl::scaleTo(float scale, float time, float cx, float cy)
{
	//cx = 0;
	//cy = 0;

	float cscale = getScale();

	//if(scale == cscale)
	//	return ;

	if(time <= 0.0f || cscale == 0.0f)
		return ;

	m_fScaleTime = time;
	m_fChgScale = (scale - cscale) / time;

	//! 当前屏幕的中心位置
	//Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 pos = getPosition();

	m_fChgBeginX = (m_fLayerWidth / 2 - pos.x) / cscale;
	m_fChgBeginY = (m_fLayerHeight / 2 - pos.y) / cscale;

	m_fChgX = (cx - m_fChgBeginX) / time;
	m_fChgY = (cy - m_fChgBeginY) / time;
}

void LayerCtrl::setPosition(const Vec2 &position)
{
	Layer::setPosition(position);
	fixPosition();

	//CCLog("LayerCtrl::setPosition position.x = %f, position.y = %f, x = %f, y = %f", position.x, position.y, getPositionX(), getPositionY());
}

void LayerCtrl::setScale(float scale)
{
	if(scale > m_fMaxScale + m_fExceedMax)
		scale = m_fMaxScale + m_fExceedMax;

	if(m_fMinScale != 0.0f)
	{
		if(scale < m_fMinScale - m_fExceedMin)
			scale = m_fMinScale - m_fExceedMin;
	}

	if(m_LayerRect.size.width != 0.0f && m_LayerRect.size.height != 0.0f)
	{
		//Size visibleSize = Director::getInstance()->getVisibleSize();

		if(m_LayerRect.size.width * scale < m_fLayerWidth)
			scale = m_fLayerWidth / m_LayerRect.size.width;

		if(m_LayerRect.size.height * scale < m_fLayerHeight)
			scale = m_fLayerHeight / m_LayerRect.size.height;
	}

	Layer::setScale(scale);
	fixPosition();
}

//! 要求允许多点触摸（目前仅解决Widget禁止多点触摸的问题）
void LayerCtrl::setTouchesEnable(bool enabled)
{
//	Node* parent = getParent();
//
//	while(parent != NULL)
//	{
//		Layer* pLayer = dynamic_cast<Layer*>(parent);
//
//        if(pLayer != NULL) {
//            pLayer->setTouchEnabled(enabled);
//            
//            pLayer->setSwallowsTouches(<#bool swallowsTouches#>)
//        }
//
//		parent = parent->getParent();
//	}
}

//! 鼠标
void LayerCtrl::_onMouseScroll(Event *event)
{
	auto mouseEvent = static_cast<EventMouse*>(event);

	float sy = mouseEvent->getScrollY() * 0.1f;
	scaleLayer(sy, mouseEvent->getCursorX(), mouseEvent->getCursorY());
}

//! 触摸
bool LayerCtrl::_onTouchBegan(Touch* touch, Event* event)
{
	m_bSlide = false;
	m_vecMoveDis.x = 0.0f;
	m_vecMoveDis.y = 0.0f;

	m_bTouch = true;
	m_fTouchX = touch->getLocation().x;
	m_fTouchY = touch->getLocation().y;

	return true;
}

void LayerCtrl::_onTouchMoved(Touch* touch, Event* event)
{
	float cx = touch->getLocation().x;
	float cy = touch->getLocation().y;

	float sx = touch->getPreviousLocation().x;
	float sy = touch->getPreviousLocation().y;

	if(abs(m_fTouchX - cx) > 10 || abs(m_fTouchY - cy) > 10)
		m_bTouch = false;

	float mx = cx - sx;
	float my = cy - sy;

	Vec2 pos = getPosition();

	pos.x += mx;
	pos.y += my;

	setPosition(pos);

	m_vecMoveDis.x = cx - sx;
	m_vecMoveDis.y = cy - sy;
}

void LayerCtrl::_onTouchEnded(Touch* touch, Event* event)
{
	if(!m_bTouch)
		m_bSlide = true;

	m_bTouch = false;
}

void LayerCtrl::_onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
	m_bSlide = false;
	m_vecMoveDis.x = 0.0f;
	m_vecMoveDis.y = 0.0f;
}

void LayerCtrl::_onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
	if(touches.size() == 2)
	{
		float sx[2];
		float sy[2];

		sx[0] = touches[0]->getPreviousLocation().x;
		sy[0] = touches[0]->getPreviousLocation().y;
		sx[1] = touches[1]->getPreviousLocation().x;
		sy[1] = touches[1]->getPreviousLocation().y;

		float cx[2];
		float cy[2];

		cx[0] = touches[0]->getLocation().x;
		cy[0] = touches[0]->getLocation().y;
		cx[1] = touches[1]->getLocation().x;
		cy[1] = touches[1]->getLocation().y;

		float x = (sx[0] + sx[1]) / 2.0f;
		float y = (sy[0] + sy[1]) / 2.0f;

		float sdis = sqrt((sx[0] - sx[1]) * (sx[0] - sx[1]) + (sy[0] - sy[1]) * (sy[0] - sy[1]));
		float cdis = sqrt((cx[0] - cx[1]) * (cx[0] - cx[1]) + (cy[0] - cy[1]) * (cy[0] - cy[1]));

		if(sdis <= 0.0f)
			return ;

		scaleLayer((cdis - sdis) / sdis, x, y);
	}
}

void LayerCtrl::_onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
}

//! 计时
void LayerCtrl::onIdle(float dt)
{
	//! 缩放动画
	if(m_fScaleTime > 0.0f)
	{
		float mt = dt;

		if(m_fScaleTime < dt)
		{
			mt = m_fScaleTime;
			m_fScaleTime = 0.0f;
		}
		else
		{
			m_fScaleTime -= dt;
		}

		float cscale = getScale();

		cscale += m_fChgScale * mt;
		setScale(cscale);

		cscale = getScale();

		m_fChgBeginX += m_fChgX * mt;
		m_fChgBeginY += m_fChgY * mt;

		//Size visibleSize = Director::getInstance()->getVisibleSize();

		float cx = m_fLayerWidth / 2 - m_fChgBeginX * cscale;
		float cy = m_fLayerHeight / 2 - m_fChgBeginY * cscale;

		setPosition(Vec2(cx, cy));

		return ;
	}

	float cscale = getScale();

	if(cscale > m_fMaxScale)
	{
		float chgs = m_fResumeMax * dt;

		if(chgs > cscale - m_fMaxScale)
			chgs = cscale - m_fMaxScale;

		scaleLayer(-chgs, m_fScaleX, m_fScaleY);
	}
	else if(m_fMinScale != 0.0f && cscale < m_fMinScale)
	{
		float chgs = m_fResumeMin * dt;

		if(chgs > m_fMinScale - cscale)
			chgs = m_fMinScale - cscale;

		scaleLayer(chgs, m_fScaleX, m_fScaleY);
	}

	if(m_bUseSlide && m_bSlide)
	{
		Vec2 pos = getPosition();

		setPosition(Vec2(pos.x + m_vecMoveDis.x, pos.y + m_vecMoveDis.y));

		m_vecMoveDis = ccpMult(m_vecMoveDis, 0.85f);

		if((fabsf(m_vecMoveDis.x) <= 1.0f && fabsf(m_vecMoveDis.y) <= 1.0f) || pos.x == getPosition().x || pos.y == getPosition().y)
			m_bSlide = false;
	}
}

//! 修正位置
void LayerCtrl::fixPosition()
{
	//return ;

	if(m_LayerRect.size.width == 0.0f || m_LayerRect.size.height == 0.0f)
		return ;

	//Size visibleSize = Director::getInstance()->getVisibleSize();
	float cscale = getScale();

	Vec2 pos = getPosition();

	float minx = m_LayerRect.origin.x * cscale;
	float miny = m_LayerRect.origin.y * cscale;
	float maxx = minx + m_LayerRect.size.width * cscale;
	float maxy = miny + m_LayerRect.size.height * cscale;

	if(pos.x + minx > 0)
		pos.x = -minx;

	if(pos.y + miny > 0)
		pos.y = -miny;

	if(maxx + pos.x < m_fLayerWidth)
		pos.x =  m_fLayerWidth - maxx;

	if(maxy + pos.y < m_fLayerHeight)
		pos.y = m_fLayerHeight - maxy;

	Layer::setPosition(pos);
}

//! 根据中心位置缩放
void LayerCtrl::scaleLayer(float chgs, float cx, float cy)
{
	float cscale = getScale();

	if(cscale == 0.0f)
		return ;

	//! 屏幕坐标转换成场景坐标
	Vec2 pos = getPosition();
	float sx = (cx - pos.x) / cscale;
	float sy = (cy - pos.y) / cscale;

	cscale += chgs;
	setScale(cscale);
	//return ;

	cscale = getScale();

	float ncx = sx * cscale + pos.x;
	float ncy = sy * cscale + pos.y;

	pos.x -= ncx - cx;
	pos.y -= ncy - cy;

	setPosition(pos);

	m_fScaleX = cx;
	m_fScaleY = cy;
}