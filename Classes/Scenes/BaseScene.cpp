//
//  BaseScene.cpp
//  TienLenMienNam2
//
//  Created by Black3rry on 4/8/16.
//
//

#include "BaseScene.hpp"
#include "Utils/NetworkManager.h"
#include "Utils/TLMNConfig.hpp"

bool BaseScene::init()
{
    if(!Layer::init())
    {
        return false;
    }

    Size _visibleSize = Director::getInstance()->getVisibleSize();
    visibleSize = _visibleSize;
    width = _visibleSize.width;
    height = _visibleSize.height;
    
    Vec2 _origin = Director::getInstance()->getVisibleOrigin();
    originX = _origin.x;
    originY = _origin.y;
    
    return true;
}

Vec2 BaseScene::MVec2(float x, float y) {
    return Vec2(originX + x, originY + y);
}

void BaseScene::onExit() {
    Layer::onExit();
}