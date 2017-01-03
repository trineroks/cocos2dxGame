#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "Ship.hpp"
#include <vector>
#include <stdlib.h>
#include <random>
#include "cocos2d.h"
#include "Asteroid.hpp"

class GameScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GameScene);
    
    Point touchOffset;
    
private:
    const float _offDistance = 30.0f;
    const float _maxSpeed = 80.0f;
    const float _minSpeed = 20.0f;
    float _timeToNextAsteroid;
    float _holdTime;
    
    void SpawnAsteroid(int health, Vec2 startPosition, Vec2 moveVector, bool isSplitAsteroid);
    void SplitAsteroid();
    
    void createAsteroidLeft();
    void createAsteroidTop();
    void createAsteroidRight();
    
    float getSideDistanceVariation();
    float getTopDistanceVariation();
    
    bool checkAsteroidTapped(cocos2d::Touch *touch);
    
    void update(float delta);
    bool isColliding(Rect target, Rect collider);
    bool ShipIsOutOfBounds();
    bool checkCollision();
    void AsteroidIsOutOfBounds();
    void cleanUpAsteroids();
    
    void manageAsteroidSpawns(float delta);
    void splitAsteroidProperties();
    
    Point touchToPoint(cocos2d::Touch* touch);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    
    Ship* _ship;
    std::vector<Asteroid *> _asteroids;
    
    unsigned int _score;
    cocos2d::Label* _scoreLabel;

};

#endif // __HELLOWORLD_SCENE_H__
