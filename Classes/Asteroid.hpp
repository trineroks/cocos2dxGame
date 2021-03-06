#pragma once

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class Asteroid : public cocos2d::Node
{
public:
    const float _timeToRemoveWhenOffscreen = 5.0f;
    
    Asteroid(int health, Vec2 position, Vec2 moveVector, Sprite *sprite, bool isSplitAsteroid);
    ~Asteroid();
    bool isTouchingSprite(Touch* touch);
    bool isRightStarting();
    
    void setPosition(const Vec2 &position);
    void incrementPosition(float delta);
    Vec2& getPosition();
    void updatePosition();
    
    float getTimeOffScreen() {
        return _timeOffScreen;
    };
    
    void incrementTimeOffScreen(float delta) {
        _timeOffScreen += delta;
    };
    
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
    };
    
    bool getHasEnteredScene() {
        return _hasEnteredScene;
    };
    
    void hasEnteredScene() {
        _hasEnteredScene = true;
    };
    
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
    bool _hasEnteredScene;
    float _timeOffScreen;
    Vec2 _position;
    Vec2 _moveVector;
    int _health;
    cocos2d::Sprite* _sprite;
    
};
