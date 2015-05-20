#include "Person.h"
#include "PersonMgr.h"

USING_NS_CC;

Person::Person()
    : m_pSpr(NULL)
	, m_pRoot(NULL)
	, m_pActionInfo(NULL)
	, m_iAction(_PERSON_ACTION_WAIT)
	, m_iFrame(0)
	, m_iDir(0)
	, m_iActTime(0)
	, m_bFlip(false)
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
	
	return true;
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

	m_pSpr->setSpriteFrame(m_lstActionFrames[m_iDir][m_iAction][m_iFrame]);

	if(m_bFlip)
		m_pSpr->setScaleX(-1);
	else
		m_pSpr->setScaleX(1);
}

void Person::setPosition(float xx, float yy)
{
	if(m_pRoot == NULL)
		return ;

    m_pSpr->setPosition(xx, yy);
}