#ifndef ship_hpp
#define ship_hpp

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class Ship : public cocos2d::Node
{
public:
    Ship();
    ~Ship();
    int shieldStatus();
    Sprite* getSprite();
    Sprite** getShieldSprites();
    void showShieldSprite();
    
    void decrementShield();
    void incrementShield();
    
    bool isTouchingSprite(cocos2d::Touch* touch);
    void preSetPosition(const Vec2 &position);
    Vec2& getPreSetPosition();
    Vec2& getPreviousSetPosition();
    
    const Rect& getSpriteRect();
    Rect getHitbox();
    
    void updatePosition();
    void revertPosition();
    void turnOffShield();
private:
    bool _shieldUp;
    Sprite* _sprite;
    Sprite* _shield[3];
    int _shieldStatus;
    Vec2 _position;
    Vec2 _prevposition;
};

#endif /* ship_hpp */
