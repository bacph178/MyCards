#include "ShowGame.h"
#include "LoginScene.h"
#include "TLMienNam.h"
#include "SceneTable.hpp"

#include "UI/MButton.hpp"
#include "UI/MSprite.hpp"
#include "Utils/TLMNConfig.hpp"
#include "Utils/NetworkManager.h"
#include "Utils/Common.h"
#include "protobufObject/enter_zone.pb.h"



#define TAG_BTN_BACK 1
#define TAG_BTN_MENU 2
#define TAG_BTN_NAPXU 3
#define TAG_BTN_TROGIUP 4
#define TAG_BTN_CAIDAT 5

#define TAG_GAME_XITO 6
#define TAG_GAME_PHOM 7
#define TAG_GAME_TLMB 8
#define TAG_GAME_TLMN 9
#define TAG_GAME_BACAY 10
#define TAG_GAME_POCKER 11
#define TAG_GAME_XOCDIA 12

using namespace cocos2d::ui;

Scene* ShowGame::createScene() {
    
    auto scene = Scene::create();
    
    auto layer = ShowGame::create();

    scene->addChild(layer);

    return scene;
}

bool ShowGame::init() {
    
    if ( !BaseScene::init() ) {
        return false;
    }
    
    auto bkg = MSprite::create("bgr_listgame.jpg",visibleSize);
    bkg->setPosition(MVec2(0,0));
    this->addChild(bkg);
    
    auto girl = MSprite::create("girl2.png");
    girl->setPosition(MVec2(width/2-girl->getWidth()/2,0));
    this->addChild(girl);
    
    //====================================  buttons
    
    {
        
        auto btn_back = MButton::create(BTN_BACK,TAG_BTN_BACK);
        btn_back->setPosition(MVec2(10,height-10- btn_back->getHeight()));
        btn_back->addTouchEventListener( CC_CALLBACK_2(ShowGame::menuCallBack, this) );
        this->addChild(btn_back);
        
        //btn Menu
        auto btn_mennu = MButton::create(BTN_MENU,TAG_BTN_MENU);
        btn_mennu->setPosition(MVec2(width-10-btn_mennu->getWidth(),
                                    height-10- btn_mennu->getHeight()));
        btn_mennu->addTouchEventListener( CC_CALLBACK_2(ShowGame::menuCallBack, this) );
        this->addChild(btn_mennu);
    }
    
    //====================================  navigation bar
    
    {
        
        auto bkg_navigationbar = MSprite::create("ic_navigationbar.png");
        bkg_navigationbar->setScale(width/bkg_navigationbar->getWidth(),1);
        bkg_navigationbar->setPosition(MVec2(0,0));
        this->addChild(bkg_navigationbar);
        
        // nap xu
        auto btn_napxu = MButton::createExtends("ic_charge.png","Nạp xu",30,TAG_BTN_NAPXU);
        btn_napxu->setPosition(MVec2(width*1.3f/5,
                                    bkg_navigationbar->getHeight()/2 - btn_napxu->getHeight()/2));
        btn_napxu->addTouchEventListener( CC_CALLBACK_2(ShowGame::menuCallBack, this) );
        this->addChild(btn_napxu);
        
        // tro giup
        auto btn_trogiup = MButton::createExtends(BTN_HELPER,"Trợ giúp",30,TAG_BTN_TROGIUP);
        btn_trogiup->setPosition(Vec2(originX + width*3.3f/5,btn_napxu->getPosition().y));
        btn_trogiup->addTouchEventListener( CC_CALLBACK_2(ShowGame::menuCallBack, this) );
        this->addChild(btn_trogiup);
        
        // cai dat
        auto btn_caidat = MButton::createExtends("ic_setting.png","Cài đặt",30,TAG_BTN_CAIDAT);
        btn_caidat->setPosition(Vec2(originX + width*4.3f/5,btn_napxu->getPosition().y));
        btn_caidat->addTouchEventListener( CC_CALLBACK_2(ShowGame::menuCallBack, this) );
        this->addChild(btn_caidat);
    }
    
    //==================================== scroll view - game button
    
    // add scroll view
    auto game_button = MSprite::create("game_xocdia.png");
    
    Size scollFrameSize = Size(width,game_button->getHeight()*1.2f);
    auto scrollView = ScrollView::create();
    scrollView->setContentSize(scollFrameSize);
   
    scrollView->setPosition(MVec2(0,height*1/6));
    scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
    scrollView->setScrollBarEnabled(false);
    scrollView->setBounceEnabled(true);
    scrollView->setInertiaScrollEnabled(true);
    scrollView->setTouchEnabled(true);
    
    auto containerSize = Size(game_button->getWidth()*7*1.2f, scollFrameSize.height);
    scrollView->setInnerContainerSize(containerSize);
    this->addChild(scrollView);
    
    {   // Game buttons
        
        auto game_xocdia = MButton::createItem("game_xocdia.png",TAG_GAME_XOCDIA);
        game_xocdia->setPosition(Vec2(containerSize.width*1-game_xocdia->getWidth()*1.2f/2,
                                      containerSize.height/2));
        game_xocdia->addTouchEventListener( CC_CALLBACK_2(ShowGame::gameItemCallBack, this) );
        scrollView->addChild(game_xocdia);
        
        auto game_xito = MButton::createItem("game_xito.png",TAG_GAME_XITO);
        game_xito->setPosition(Vec2(containerSize.width*6/7-game_xocdia->getWidth()*1.2f/2,
                                    containerSize.height/2));
        game_xito->addTouchEventListener( CC_CALLBACK_2(ShowGame::gameItemCallBack, this) );
        scrollView->addChild(game_xito);
        
        auto game_tlmn = MButton::createItem("game_tlmn.png",TAG_GAME_TLMN);
        game_tlmn->setPosition(Vec2(containerSize.width*5/7-game_xocdia->getWidth()*1.2f/2,
                                    containerSize.height/2));
        game_tlmn->addTouchEventListener( CC_CALLBACK_2(ShowGame::gameItemCallBack, this) );
        scrollView->addChild(game_tlmn);
        
        auto game_tlmb = MButton::createItem("game_tlmb.png",TAG_GAME_TLMB);
        game_tlmb->setPosition(Vec2(containerSize.width*4/7-game_xocdia->getWidth()*1.2f/2,
                                    containerSize.height/2));
        game_tlmb->addTouchEventListener( CC_CALLBACK_2(ShowGame::gameItemCallBack, this) );
        scrollView->addChild(game_tlmb);
        
        auto game_poker = MButton::createItem("game_poker.png",TAG_GAME_POCKER);
        game_poker->setPosition(Vec2(containerSize.width*3/7-game_xocdia->getWidth()*1.2f/2,
                                     containerSize.height/2));
        game_poker->addTouchEventListener( CC_CALLBACK_2(ShowGame::gameItemCallBack, this) );
        scrollView->addChild(game_poker);
        
        auto game_phom = MButton::createItem("game_phom.png",TAG_GAME_PHOM);
        game_phom->setPosition(Vec2(containerSize.width*2/7-game_xocdia->getWidth()*1.2f/2,
                                    containerSize.height/2));
        game_phom->addTouchEventListener( CC_CALLBACK_2(ShowGame::gameItemCallBack, this) );
        scrollView->addChild(game_phom);
        
        auto game_bacay = MButton::createItem("game_bacay.png",TAG_GAME_BACAY);
        game_bacay->setPosition(Vec2(containerSize.width*1/7-game_xocdia->getWidth()*1.2f/2,
                                     containerSize.height/2));
        game_bacay->addTouchEventListener( CC_CALLBACK_2(ShowGame::gameItemCallBack, this) );
        scrollView->addChild(game_bacay);
    }
    
    
     // POPUP SETTING
    m_popupSetting = PopupSetting::create();
    m_popupSetting->retain();
    
    addChild(m_popupSetting);
    
    CCLOG("ShowGame-created");
    
	this->scheduleUpdate();

    return true;
}


void ShowGame::menuCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if(type == Widget::TouchEventType::ENDED) {
        MButton *button = (MButton*) sender;
        int tag = button->getTag();
        switch (tag) {
            case TAG_BTN_BACK:
                CCLOG("%s","btn_back");
                {
                    auto registerscene = LoginScene::createScene();
                    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.25f, registerscene));
                }
                break;
            case TAG_BTN_CAIDAT:
                CCLOG("%s","btn_catdat");
                {
                    m_popupSetting->appear();
                }
                break;
            case TAG_BTN_MENU:
                CCLOG("%s","btn_menu");
                break;
            case TAG_BTN_NAPXU:
                CCLOG("%s","btn_napxu");
                break;
            case TAG_BTN_TROGIUP:
                CCLOG("%s","btn_trogiup");
                break;
            default:
                break;
        }
    }
    
}

void ShowGame::gameItemCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if(type == Widget::TouchEventType::ENDED){
        MButton *button = (MButton*) sender;
        int tag = button->getTag();
        switch (tag) {
            case TAG_GAME_XOCDIA:
                CCLOG("%s","game : xocdia");
                break;
            case TAG_GAME_XITO:
                CCLOG("%s","game : xito");
                break;
            case TAG_GAME_TLMN:
                CCLOG("%s","game : tlmn");
                {
					NetworkManager::getInstance()->getEnterZoneMessageFromServer(
						Common::getInstance()->getZoneId(tag));
                }
                break;
            case TAG_GAME_TLMB:
                CCLOG("%s","game : tlmb");
                break;
            case TAG_GAME_POCKER:
                CCLOG("%s","game : pocker");
                break;
            case TAG_GAME_PHOM:
                CCLOG("%s","game : phom");
                break;
            case TAG_GAME_BACAY:
                CCLOG("%s","game : bacay");
                break;
            default:
                break;
        }
    }
    
}

void ShowGame::update(float dt) {
	std::mutex mtx;
	bool isSuccess = false;
	int k = -1;
	mtx.lock();
	//handle login
	pair<google::protobuf::Message*, int> result;
	for (int i = 0; i<NetworkManager::listEvent.size(); i++) {
		if (NetworkManager::listEvent[i][0].second == NetworkManager::ENTER_ZONE){
			result = NetworkManager::listEvent[i][0];
			isSuccess = ((BINEnterZoneResponse *)result.first)->responsecode();
			k = i;
			break;
		}
	}

	if (k != -1)
		NetworkManager::listEvent.erase(NetworkManager::listEvent.begin() + k);

	mtx.unlock();

	if (k != -1) { //found
		if (isSuccess) {
			auto scene = SceneTable::createScene(true);
			Director::getInstance()->replaceScene(TransitionCrossFade::create(0.25f, scene));
			isSuccess = false;
		}
		else {
			cocos2d::MessageBox(((BINEnterZoneResponse *)result.first)->message().c_str(), "XXX");
		
		}
	}

}



void ShowGame::gotoMenuDialog(){
    //Setting dialog
    
    //auto settingdialog = SettingDialog::create();
    //settingdialog->setPosition(Vec2(0,settingdialog->getContentSize().height));
    //this->addChild(settingdialog);
    //auto moveTo = MoveTo::create(0.25f, Vec2(0,0));
    //settingdialog->runAction(moveTo);
   
}

void ShowGame::onExit() {
    BaseScene::onExit();
}



