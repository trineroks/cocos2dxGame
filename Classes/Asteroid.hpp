#pragma once

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class Asteroid : public cocos2d::Node
{
public:
    Asteroid(int health, Vec2 position, Vec2 moveVector, Sprite *sprite, bool isSplitAsteroid);
    ~Asteroid();
    bool isTouchingSprite(Touch* touch);
    bool isRightStarting();
    int health();
    void bindSprite(Sprite* sprite);
    
    void setPosition(const Vec2 &position);
    void incrementPosition(float delta);
    Vec2& getPosition();
    void updatePosition();
    
    Vec2& getMoveVector() {
        return _moveVector;
    };
    
    void setToRemove() {
        _toRemove = true;
    };
    
    bool getToRemove() {
        return _toRemove;
    };
    
    void setToSplit() {
        _toSplit = true;
    };
    
    bool getToSplit() {
        return _toSplit;
    };
    
    void decrementHP() {
        --_health;
    };
    
    bool getSplitAsteroid() {
        return _isSplitAsteroid;
    }
    
    int getHP() {
        return _health;
    };
    
    const Rect& getSpriteRect();
    Rect getHitBox();
    Sprite* getSprite();
private:
    bool _rightStarting;
    bool _toRemove;
    bool _toSplit;
    bool _isSplitAsteroid;
    Vec2 _position;
    Vec2 _moveVector;
    int _health;
    cocos2d::Sprite* _sprite;
    
};
