#ifndef __GAMESCENE_GAMESCENE_H__
#define __GAMESCENE_GAMESCENE_H__

#include "cocos2d.h"
#include "BaseObj.h"
#include "LayerCtrl.h"

USING_NS_CC;

class Person;

class GameScene
{
public:
	GameScene();
    virtual ~GameScene();
public:
    void init(Node* pRoot);
    
    void release();

	//! 测试
	void onIdle(int ot);
public:
    Node* getRoot() { return m_pLayer; }
protected:
    Node*       m_pRoot;
    LayerCtrl*  m_pLayer;

	//! 测试
	std::vector<Person*>		m_lstPerson;
};

#endif // __GAMESCENE_GAMESCENE_H__