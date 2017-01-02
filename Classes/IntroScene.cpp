#include "IntroScene.hpp"
#include "GameScene.hpp"
#include "Constants.h"

USING_NS_CC;

Scene* IntroScene::createScene()
{
    auto scene = Scene::create();
    auto layer = IntroScene::create();
    scene->addChild(layer);
    return scene;
}

bool IntroScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto title = Label::createWithTTF("Ship Control", "fonts/arial.ttf", 24);
    
    title->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height - title->getContentSize().height));
    this->addChild(title);

    auto startButton = Label::createWithTTF("Play", "fonts/arial.ttf", 24);
    auto startGameItem = MenuItemLabel::create(startButton, CC_CALLBACK_1(IntroScene::GoToGameScene, this));
    startGameItem->setPosition(Point (visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    
    auto menu = Menu::create(startGameItem, NULL);
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);
    
    return true;
    
}

void IntroScene::GoToGameScene(cocos2d::Ref *sender)
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene( TransitionFade::create(TRANSITION_TIME, scene));
}
