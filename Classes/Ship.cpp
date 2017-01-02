#include "Ship.hpp"

Ship::Ship()
{
    _sprite = Sprite::createWithSpriteFrameName("playerShip1_blue.png");
    
    _shield[0] = Sprite::createWithSpriteFrameName("shield1.png");
    _shield[1] = Sprite::createWithSpriteFrameName("shield2.png");
    _shield[2] = Sprite::createWithSpriteFrameName("shield3.png");
    
    _shield[0]->setOpacity(0);
    _shield[1]->setOpacity(0);
    _shield[2]->setOpacity(0);
    
    _shieldStatus = 3;
    _position = Vec2(0,0);
    _prevposition = Vec2(0,0);
    _shieldUp = false;
}

Ship::~Ship()
{
    _sprite = NULL;
    _shield[0] = NULL;
    _shield[1] = NULL;
    _shield[2] = NULL;
}

void Ship::decrementShield()
{
    _shieldStatus -= 1;
    if (_shieldStatus <= 0)
        _shieldStatus = 0;
}

void Ship::incrementShield()
{
    _shieldStatus += 1;
    if (_shieldStatus >= 3)
        _shieldStatus = 3;
}

int Ship::shieldStatus()
{
    return _shieldStatus;
}

void Ship::showShieldSprite()
{
    if (_shieldUp)
    {
        if (_shieldStatus >= 1)
            _shield[_shieldStatus-1]->setOpacity(255);
    }
    else {
        _shield[0]->setOpacity(0);
        _shield[1]->setOpacity(0);
        _shield[2]->setOpacity(0);
    }
}

Sprite **Ship::getShieldSprites()
{
    return _shield;
}

Sprite* Ship::getSprite()
{
    return _sprite;
}

bool Ship::isTouchingSprite(cocos2d::Touch* touch)
{
    Point _touch = Director::getInstance()->convertToGL(touch->getLocationInView());
    //_touch = _sprite->convertToNodeSpace(_touch);
    //Rect _rect = getHitbox();
    //if(_rect.containsPoint(_touch))
    if(_sprite->getPosition().getDistance(_touch) < getSpriteRect().size.width)
    {
        _shieldUp = true;
        return true;
    }
    return false;
}

void Ship::turnOffShield()
{
    _shieldUp = false;
}

void Ship::preSetPosition(const Vec2 &position)
{
    _position.x = position.x;
    _position.y = position.y;
}

Vec2& Ship::getPreSetPosition()
{
    return _position;
}

Rect Ship::getHitbox()
{
    return _sprite->getBoundingBox();
}

const Rect& Ship::getSpriteRect()
{
    return _sprite->getTextureRect();
}

void Ship::revertPosition()
{
    preSetPosition(_prevposition);
}

void Ship::updatePosition() {
    
    _sprite->setPosition(_position);
    _shield[0]->setPosition(_position);
    _shield[1]->setPosition(_position);
    _shield[2]->setPosition(_position);
    
    _prevposition.x = _position.x;
    _prevposition.y = _position.y;
}
