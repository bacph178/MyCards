#include "IntroScene.h"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "LoginScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "NativeUtility.h"
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#endif

#include "Utils/NetworkManager.h"
#include "Utils/TLMNConfig.hpp"

Scene* IntroScene::createScene() {
    
    auto scene = Scene::create();
    
    auto layer = IntroScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool IntroScene::init() {
    
    if ( !BaseScene::init() ) {
        return false;
    }

    
    NetworkManager::getInstance()->connectServer(SERVER_NAME, SERVER_PORT);
    NetworkManager::getInstance()->getInitializeMessageFromServer("0", "1", "vn"
        ,"vi", "00000000", "Samsung galaxy S2", "192.168.1.47");
    NetworkManager::getInstance()->listenData();
    
    
	auto background = MSprite::create("bg.png",visibleSize);
	background->setPosition(MVec2(0, 0)); 
    background->setColor(Color3B::BLACK);
	this->addChild(background);
    
    auto label = MLabel::create("BigKen Online", 65);
    label->setPosition(MVec2(width/2 - label->getWidth()/2,height/2 - label->getHeight()/2));
    this->addChild(label);
    
    
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CCLOG("id iphone : %s",NativeUtility::objectiveC_call().c_str());
    #endif
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    
    #endif
    
	this->scheduleOnce(schedule_selector(IntroScene::gotoStartScene), 2.0f);
    
    return true;
}

void IntroScene::gotoStartScene(float dt) {
	auto startscene = LoginScene::createScene();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.25f, startscene));
}

void IntroScene::onExit() {
    BaseScene::onExit();
}
