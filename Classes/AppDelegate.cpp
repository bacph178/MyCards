#include "AppDelegate.h"
#ifdef SDKBOX_ENABLED
#include "PluginFacebook/PluginFacebook.h"
#endif
#include "Scenes/IntroScene.h"
#include "Utils/TLMNConfig.hpp"
#include "Scenes/TLMienNam.h"
#include "Scenes/SceneTable.hpp"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(SCREEN_WIDTH, SCREEN_HEIGHT);
static cocos2d::Size smallResolutionSize = cocos2d::Size(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.25f);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
static cocos2d::Size largeResolutionSize = cocos2d::Size(SCREEN_WIDTH, SCREEN_HEIGHT);

AppDelegate::AppDelegate(){
    
}

AppDelegate::~AppDelegate(){
    
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    
    GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages(){
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
#ifdef SDKBOX_ENABLED
    sdkbox::PluginFacebook::init();
#endif
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("My Cards", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
        glview->setFrameSize(designResolutionSize.width * 0.5f, designResolutionSize.height * 0.5f);
#else
        glview = GLViewImpl::create("My Cards");
#endif
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);
    
    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    
    // create a scene. it's an autorelease object
    auto scene = SceneTable::createScene();
    
    // run
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
