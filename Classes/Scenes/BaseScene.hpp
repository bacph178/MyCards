//
//  BaseScene.hpp
//  TienLenMienNam2
//
//  Created by Black3rry on 4/8/16.
//
//

#ifndef BaseScene_hpp
#define BaseScene_hpp

#include "cocos2d.h"
USING_NS_CC;

class BaseScene : public Layer
{
public:
    virtual bool init();
    virtual void onExit();
    
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) { };
    virtual void onKeyRelease(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) { };
    
    CREATE_FUNC(BaseScene);
    
protected:
    Vec2   MVec2(float x, float y);
    
    Size visibleSize;
    float   width;
    float   height;
    float   originX;
    float   originY;
};

#endif /* BaseScene_hpp */
