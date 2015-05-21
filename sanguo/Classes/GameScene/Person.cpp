#include "Person.h"
#include "PersonMgr.h"
#include "EffectMgr.h"

USING_NS_CC;

const int _PERSON_BASESPEED		=	100;		//! 基准速度（该速度下动画正常播放）
const int _ARROW_SPEED			=	100;		//! 箭飞行的速度

Person::Person()
    : m_pSpr(NULL)
	, m_pRoot(NULL)
	, m_pActionInfo(NULL)
	, m_iAction(_PERSON_ACTION_WAIT)
	, m_iFrame(0)
	, m_iDir(0)
	, m_iActTime(0)
	, m_bFlip(false)
	, m_iMoveTime(0)
{
    
}

Person::~Person()
{
    
}

bool Person::init(int camp, int personid, Node* root)
{
	_ActionInfo* ainfo = PersonMgr::getSingleton().getActionInfo(personid);

	if(ainfo == NULL)
		return false;

	m_pRoot = root;
	m_iCamp = camp;
	m_iID = personid;
	m_pActionInfo = ainfo;

	initRes();
	refreshDisplay();

	setPosition(0, 0);
	
	return true;
}

void Person::release()
{
	if(m_pSpr != NULL)
	{
		if(m_pSpr->getParent() != NULL)
		{
			m_pSpr->getParent()->removeChild(m_pSpr);
		}

		m_pSpr->release();
		m_pSpr = NULL;
	}

	for(int i = 0; i < _PERSON_DIR_NUMS; ++i)
	{
		for(int j = 0; j < _PERSON_ACTION_NUMS; ++j)
		{
			for(std::vector<SpriteFrame*>::iterator it = m_lstActionFrames[i][j].begin(); it != m_lstActionFrames[i][j].end(); ++it)
			{
				(*it)->release();
			}
		}
	}
}

void Person::setPosition(float xx, float yy)
{
	m_fX = xx;
	m_fY = yy;

	if(m_pRoot == NULL || m_pSpr == NULL)
		return ;

    m_pSpr->setPosition(xx, yy);
	m_pSpr->setLocalZOrder(_GAMESCENE_Z_PERSON - m_fY);
}

//! 朝向
void Person::dirTo(float xx, float yy)
{
	float sx = xx - m_fX;
	float sy = yy - m_fY;

	if(sx == 0 && sy == 0)
		return ;

	double degree = 0;

	if(sy == 0 && sx > 0)
		degree = 90;
	else if(sy == 0 && sx < 0)
		degree = 270;
	else if(sx == 0 && sy > 0)
		degree = 0;
	else if(sx == 0 && sy < 0)
		degree = 180;
	else
	{
		double radians = atanf(sx / sy);
		degree = CC_RADIANS_TO_DEGREES(radians);

		if(sx < 0 && sy < 0)
			degree += 180;
		else if(sx > 0 && sy < 0)
			degree += 180;
	}

	if(degree < 0)
		degree += 360;

	if(degree >= 360)
		degree -= 360;

	if(degree >= 0 && degree <= 180)
	{
		m_bFlip = false;

		m_iDir = (int)degree / (180 / _PERSON_DIR_NUMS);

		if(m_iDir < 0)
			m_iDir = 0;

		if(m_iDir >= _PERSON_DIR_NUMS)
			m_iDir = _PERSON_DIR_NUMS - 1;
	}
	else
	{
		m_bFlip = true;

		int tdeg = 360 - degree;

		m_iDir = tdeg / (180 / _PERSON_DIR_NUMS);

		if(m_iDir < 0)
			m_iDir = 0;

		if(m_iDir >= _PERSON_DIR_NUMS)
			m_iDir = _PERSON_DIR_NUMS - 1;
	}

	refreshDisplay();
}

//! 移动到 speed每秒钟移动的距离
void Person::moveTo(float ex, float ey, int speed)
{
	m_fEX = ex;
	m_fEY = ey;

	chgAction(_PERSON_ACTION_RUN);
	dirTo(ex, ey);
	chgSpeed(speed);
}

//! 停止
void Person::stop()
{
	m_fEX = m_fX;
	m_fEY = m_fY;
	m_iMoveTime = 0;

	chgAction(_PERSON_ACTION_WAIT);
}

//! 改变移动速度
void Person::chgSpeed(int speed)
{
	if(speed <= 0)
		stop();

	m_iMoveSpeed = speed;

	float dis = sqrt((m_fX - m_fEX) * (m_fX - m_fEX) + (m_fY - m_fEY) * (m_fY - m_fEY));

	m_iMoveTime = dis * 1000 / m_iMoveSpeed;

	//! 已经到达终点
	if(m_iMoveTime <= 0)
	{
		setPosition(m_fEX, m_fEY);
		stop();
		return ;
	}

	m_fMX = (m_fEX - m_fX) / m_iMoveTime;
	m_fMY = (m_fEY - m_fY) / m_iMoveTime;

	m_iRunActionTime = m_pActionInfo->atime[_PERSON_ACTION_RUN] * _PERSON_BASESPEED / m_iMoveSpeed;

	if(m_iRunActionTime < 1)
		m_iRunActionTime = 1;
}

//! 攻击
void Person::attack(BaseObj* dest)
{
	float dx = m_fX;
	float dy = m_fY;

	if(dest != NULL)
	{
		dx = dest->getPositionX();
		dy = dest->getPositionY();
	}

	attack(dx, dy);
}

void Person::attack(float dx, float dy)
{
	stop();
	dirTo(dx, dy);
	chgAction(_PERSON_ACTION_ATTACK);

	//! 如果是弓箭手则发射箭
	if(m_pActionInfo->stype == 1)
	{
		float dis = sqrt((m_fX - dx) * (m_fX - dx) + (m_fY - dy) * (m_fY - dy));
		int movetime = dis * 1000 / _ARROW_SPEED;

		if(movetime <= 0)
			movetime = 100;

		EffectMgr::getSingleton().addArrow(m_fX, m_fY, dx, dy, movetime, 200);
	}
}

//! 死亡
void Person::dead()
{
	stop();
	chgAction(_PERSON_ACTION_DEAD);
}

//! 计时
void Person::onIdle(int ot)
{
	onIdle_Move(ot);
	onIdle_Action(ot);
}

//! 初始化资源
void Person::initRes()
{
	if(m_pRoot == NULL)
		return ;

	if(m_pActionInfo == NULL)
		return ;

	char tmp[32];

	//! 初始化动作数据
	for(int i = 0; i < _PERSON_DIR_NUMS; ++i)
	{
		for(int j = 0; j < _PERSON_ACTION_NUMS; ++j)
		{
			int nums = m_pActionInfo->eindex[j] - m_pActionInfo->bindex[j] + 1;

			if(nums <= 0)
				continue ;

			for(int k = m_pActionInfo->bindex[j]; k <= m_pActionInfo->eindex[j]; ++k)
			{
				sprintf(tmp, "%s_%d_%d.png", m_pActionInfo->resname.c_str(), i, k);

				SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(tmp);

				if(frame != NULL)
				{
					frame->retain();
					m_lstActionFrames[i][j].push_back(frame);
				}
			}
		}
	}

	m_pSpr = Sprite::create();

	if(m_pSpr == NULL)
		return ;

	m_pSpr->retain();
	m_pSpr->setSpriteFrame(m_lstActionFrames[0][0][0]);

	m_pRoot->addChild(m_pSpr);
}

//! 刷新显示
void Person::refreshDisplay()
{
	if(m_pRoot == NULL)
		return ;

	if(m_lstActionFrames[m_iDir][m_iAction].size() <= 0)
		return ;

	if(m_iFrame < 0 || m_iFrame >= m_lstActionFrames[m_iDir][m_iAction].size())
		return ;

	if(m_pSpr == NULL)
		return ;

	m_pSpr->setSpriteFrame(m_lstActionFrames[m_iDir][m_iAction][m_iFrame]);

	if(m_bFlip)
		m_pSpr->setScaleX(-1);
	else
		m_pSpr->setScaleX(1);
}

//! 改变动作
void Person::chgAction(int action, bool refresh)
{
	if(action < 0 || action >= _PERSON_ACTION_NUMS)
		return ;

	if(!refresh && action == m_iAction)
		return ;

	//! 动作不存在
	if(m_lstActionFrames[m_iDir][action].size() <= 0)
		return ;

	m_iAction = action;
	m_iFrame = 0;
	m_iActTime = 0;

	refreshDisplay();
}

//! 移动计时
void Person::onIdle_Move(int ot)
{
	if(m_iMoveTime == 0)
		return ;

	//! 已经到达目的地
	if(ot >= m_iMoveTime)
	{
		setPosition(m_fEX, m_fEY);
		stop();
		return ;
	}

	m_iMoveTime -= ot;
	m_fX += m_fMX * ot;
	m_fY += m_fMY * ot;

	setPosition(m_fX, m_fY);
}

//! 动作计时
void Person::onIdle_Action(int ot)
{
	m_iActTime += ot;

	//! 确定帧间
	int frametime = m_pActionInfo->atime[m_iAction];

	////! 移动的帧间特殊确定
	//if(m_iAction == _PERSON_ACTION_RUN)
	//	frametime = m_iRunActionTime;

	if(m_iActTime < frametime)
		return ;

	int fadd = m_iActTime / frametime;
	m_iActTime = m_iActTime % frametime;

	m_iFrame += fadd;

	if(m_iFrame >= m_lstActionFrames[m_iDir][m_iAction].size())
	{
		//! 不循环的动作切换到待机
		if(!_PERSON_ACTION_LOOP[m_iAction])
		{
			if(m_iAction != _PERSON_ACTION_DEAD)
			{
				chgAction(_PERSON_ACTION_WAIT);
				return ;
			}
			else
			{
				m_iFrame = m_lstActionFrames[m_iDir][m_iAction].size() - 1;
			}
		}
		else
		{
			m_iFrame = m_iFrame % m_lstActionFrames[m_iDir][m_iAction].size();
		}
	}

	refreshDisplay();
}