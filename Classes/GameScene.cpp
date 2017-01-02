#include "GameScene.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(ccc4(0,0,0,0)) )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    _ship = new Ship();
    _ship->preSetPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(_ship->getSprite(), 1);
    this->addChild(_ship->getShieldSprites()[0], 2);
    this->addChild(_ship->getShieldSprites()[1], 2);
    this->addChild(_ship->getShieldSprites()[2], 2);
    
    _timeToNextAsteroid = 0;
    
    SpawnAsteroid(3, Vec2(visibleSize.width + origin.x + 40.0f, visibleSize.height + origin.y), Vec2(50.0f, 20.0f), false);
    
    this->scheduleUpdate();
    
    CCLOG("GameScene::init");
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

Point GameScene::touchToPoint(cocos2d::Touch *touch)
{
    return Director::getInstance()->convertToGL(touch->getLocationInView());
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    this->touchOffset = Point::ZERO;
    if (touch)
    {
        if (checkAsteroidTapped(touch))
            return true;
        else if (_ship->isTouchingSprite(touch)) {
            this->touchOffset = this->_ship->getSprite()->getPosition() - this->touchToPoint(touch);
        }
    }
    //CCLOG("onTouchBegan");
    return true;
}
void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (touch && touchOffset.x && touchOffset.y)
        this->_ship->preSetPosition(this->touchToPoint(touch) + this->touchOffset);
    //CCLOG("onTouchMoved");
}
void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (touch && touchOffset.x && touchOffset.y)
    {
        this->_ship->preSetPosition(this->touchToPoint(touch) + this->touchOffset);
        this->_ship->turnOffShield();
        //this->_ship->getSprite()->stopAllActions();
    }
    //CCLOG("onTouchEnded");
}

bool GameScene::checkAsteroidTapped(cocos2d::Touch *touch)
{
    for (std::vector<Asteroid*>::iterator j = _asteroids.begin(); j != _asteroids.end(); j++)
    {
        if ((*j)->isTouchingSprite(touch)) {
            (*j)->setToSplit();
            return true;
        }
    }
    return false;
}

bool GameScene::isColliding(Rect target, Rect collider)
{
    return collider.intersectsRect(target);
}

bool GameScene::ShipIsOutOfBounds()
{
    Size _visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 _origin = Director::getInstance()->getVisibleOrigin();
    
    if (_ship->getPreSetPosition().x - (_ship->getSpriteRect().size.width / 2) < _origin.x ||
        _ship->getPreSetPosition().y - (_ship->getSpriteRect().size.height / 2) < _origin.y ||
        _ship->getPreSetPosition().x + (_ship->getSpriteRect().size.width / 2) > _origin.x + _visibleSize.width ||
        _ship->getPreSetPosition().y + (_ship->getSpriteRect().size.height / 2) > _origin.y + _visibleSize.height)
    {
        _ship->revertPosition();
        return true;
    }
    return false;
}

void GameScene::AsteroidIsOutOfBounds()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    for (std::vector<Asteroid*>::iterator j = _asteroids.begin(); j != _asteroids.end(); j++)
    {
        if ((*j)->getPosition().y <= origin.y - _offDistance)
        {
            (*j)->setToRemove();
        }
        else if ((*j)->getSplitAsteroid())
        {
            if ((*j)->getPosition().x <= origin.x - _offDistance ||
                (*j)->getPosition().x >= origin.x + visibleSize.width + _offDistance)
                (*j)->setToRemove();
        }
        else
        {
            if ((*j)->isRightStarting() && (*j)->getPosition().x <= origin.x - _offDistance)
            {
                (*j)->setToRemove();
            }
            else if (!(*j)->isRightStarting() && (*j)->getPosition().x >= origin.x + visibleSize.width + _offDistance)
            {
                (*j)->setToRemove();
            }
        }
    }
}

void GameScene::cleanUpAsteroids()
{
    for (std::vector<Asteroid*>::iterator j = _asteroids.begin(); j != _asteroids.end();)
    {
        if ((*j)->getToRemove())
        {
            this->removeChild((*j)->getSprite());
            delete *j;
            j = _asteroids.erase(j);
            CCLOG("Asteroid removed");
        }
        else
            ++j;
    }
}

bool GameScene::checkCollision()
{
    for (std::vector<Asteroid*>::iterator j = _asteroids.begin(); j != _asteroids.end(); j++)
    {
        if (isColliding(_ship->getHitbox(), (*j)->getHitBox()))
        {
            (*j)->setToRemove();
            //CCLOG("Collision");
            return true;
        }
    }
    //CCLOG("No Collision");
    return false;
}

void GameScene::SpawnAsteroid(int health, Vec2 startPosition, Vec2 moveVector, bool isSplitAsteroid)
{
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//    
//    Vec2 moveVector = Vec2(80.0f, 50.0f);
//    Vec2 startPosition = Vec2(visibleSize.width + origin.x + 40.0f, visibleSize.height + origin.y);
    
    Sprite *sprite = NULL;
    
    switch(health) {
        case 1:
            sprite = Sprite::createWithSpriteFrameName("meteorBrown_small1.png");
            break;
        case 2:
            sprite = Sprite::createWithSpriteFrameName("meteorBrown_med1.png");
            break;
        case 3:
            sprite = Sprite::createWithSpriteFrameName("meteorBrown_big1.png");
            break;
        default:
            sprite = Sprite::createWithSpriteFrameName("meteorBrown_big4.png");
            break;
    }
    
    Asteroid *asteroid = new Asteroid(health, startPosition, moveVector, sprite, isSplitAsteroid);
    
    _asteroids.push_back(asteroid);
    
    this->addChild(asteroid->getSprite());
}

void GameScene::manageAsteroidSpawns(float delta)
{
    
}

void GameScene::SplitAsteroid()
{
    //NOTE TO FUTURE SELF: WHEN YOU ADD TO THIS VECTOR THE POINTER THE ITERATOR POINTS TO IS NOT GUARANTEED
    //TO BE THE SAME OBJECT. PROBABLY DUE TO SHIFTING IN MEMORY OR SOMETHING
    for (std::vector<Asteroid*>::iterator j = _asteroids.begin(); j != _asteroids.end(); j++)
    {
        if((*j)->getToSplit())
        {
            (*j)->decrementHP();
            (*j)->setToRemove();
            int HP = (*j)->getHP();
            Vec2 startPosition = Vec2((*j)->getPosition().x, (*j)->getPosition().y);
            Vec2 moveVector1 = Vec2((*j)->getMoveVector().x, (*j)->getMoveVector().y);
            Vec2 moveVector2 = Vec2((*j)->getMoveVector().x*(-1.0f), (*j)->getMoveVector().y);
            if (HP >= 1)
            {
                SpawnAsteroid(HP, startPosition, moveVector1, true);
                SpawnAsteroid(HP, startPosition, moveVector2, true);
            }
            return;
        }
    }
}

void GameScene::update(float delta)
{
    ShipIsOutOfBounds();
    _ship->showShieldSprite();
    _ship->updatePosition();
    for (std::vector<Asteroid*>::iterator j = _asteroids.begin(); j != _asteroids.end(); j++)
        (*j)->incrementPosition(delta);
    checkCollision();
    SplitAsteroid();
    AsteroidIsOutOfBounds();
    cleanUpAsteroids();
}
