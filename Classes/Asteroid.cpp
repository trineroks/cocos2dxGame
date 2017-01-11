#include "Asteroid.hpp"

Asteroid::Asteroid(int health, Vec2 position, Vec2 moveVector, Sprite *sprite, bool isSplitAsteroid)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    _position.x = position.x;
    _position.y = position.y;
    _health = health;
    _sprite = sprite;
    
    _toRemove = false;
    _toSplit = false;
    
    _timeOffScreen = 0.0f;
    
    _isSplitAsteroid = isSplitAsteroid;
    
    if (!_isSplitAsteroid)
    {
        _hasEnteredScene = false;
        if (_position.x >= visibleSize.width + origin.x)
        {
            _rightStarting = true;
            _moveVector.x = moveVector.x*(-1.0f);
        }
        else
        {
            _moveVector.x = moveVector.x;
            _rightStarting = false;
        }
    }
    else {
        _moveVector.x = moveVector.x;
        _hasEnteredScene = true;
    }
    
    _moveVector.y = moveVector.y;
}

Asteroid::~Asteroid()
{
    _sprite = NULL;
}

bool Asteroid::isTouchingSprite(cocos2d::Touch *touch)
{
    Point _touch = Director::getInstance()->convertToGL(touch->getLocationInView());
    //_touch = _sprite->convertToNodeSpace(_touch);
    //Rect *_rect = getHitBox();
    //return _rect->containsPoint(_touch);
    return (_sprite->getPosition().getDistance(_touch) < getSpriteRect().size.width);
}

const Rect& Asteroid::getSpriteRect()
{
    return _sprite->getTextureRect();
}

void Asteroid::setPosition(const Vec2 &position)
{
    _position.x = position.x;
    _position.y = position.y;
}

bool Asteroid::isRightStarting()
{
    return _rightStarting;
}

void Asteroid::incrementPosition(float delta)
{
    _position.x += _moveVector.x * delta;
    _position.y -= _moveVector.y * delta;
    updatePosition();
}

void Asteroid::updatePosition()
{
    _sprite->setPosition(_position);
}

Vec2& Asteroid::getPosition()
{
    return _position;
}

Rect Asteroid::getHitBox()
{
    return _sprite->getBoundingBox();
}

cocos2d::Sprite* Asteroid::getSprite() {
    return _sprite;
}
