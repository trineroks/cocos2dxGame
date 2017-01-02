#ifndef IntroScene_hpp
#define IntroScene_hpp

#include "cocos2d.h"

class IntroScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(IntroScene);
    
private:
    void GoToGameScene(cocos2d::Ref* sender);
};
#endif /* IntroScene_hpp */
