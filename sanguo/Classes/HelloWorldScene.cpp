#include "HelloWorldScene.h"
#include "LayerCtrl.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_scene.init(this);

	schedule(schedule_selector(HelloWorld::onIdle));
    
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
//    LayerCtrl* pLayer = LayerCtrl::create();
//    pLayer->setTouchesEnable(true);
//    this->addChild(pLayer);
//    
//    Sprite* pSprite = Sprite::create("res/worldmap.jpg");
//    pSprite->setAnchorPoint(Vec2(0, 0));
//    pSprite->setPosition(Vec2(0, 0));
//    pLayer->addChild(pSprite);
//    
//    //pLayer->setLayerSize(pSprite->getContentSize().width, pSprite->getContentSize().height);
//    
//    Rect rect;
//    rect.origin.set(0, 0);
//    rect.size.setSize(pSprite->getContentSize().width, pSprite->getContentSize().height);
//    pLayer->SetLayerRect(rect);
    //pLayer->setLayerSize(pSprite->getContentSize().width, pSprite->getContentSize().height);

//    /////////////////////////////
//    // 2. add a menu item with "X" image, which is clicked to quit the program
//    //    you may modify it.
//
//    // add a "close" icon to exit the progress. it's an autorelease object
//    auto closeItem = MenuItemImage::create(
//                                           "CloseNormal.png",
//                                           "CloseSelected.png",
//                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
//    
//	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
//                                origin.y + closeItem->getContentSize().height/2));
//
//    // create menu, it's an autorelease object
//    auto menu = Menu::create(closeItem, NULL);
//    menu->setPosition(Vec2::ZERO);
//    this->addChild(menu, 1);
//
//    /////////////////////////////
//    // 3. add your codes below...
//
//    // add a label shows "Hello World"
//    // create and initialize a label
//    
//    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
//    
//    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//
//    // add the label as a child to this layer
//    this->addChild(label, 1);
//
//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//! ≤‚ ‘
void HelloWorld::onIdle(float dt)
{
	m_scene.onIdle(dt * 1000);
}