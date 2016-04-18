#include "RegisterScene.h"
#include "LoginScene.h"
#include "ShowGame.h"

#include "UI/MSprite.hpp"
#include "UI/MLabel.hpp"
#include "UI/MButton.hpp"
#include "UI/MEditBox.hpp"

#include "Utils/TLMNConfig.hpp"
#include "Utils/NetworkManager.h"

#include <protobufObject/register.pb.h>
#include <thread>

#include <iostream>


#define TAG_BTN_REGISTER 1
#define TAG_BTN_BACK 2

#define TAG_EDITBOX_NHAP_MATKHAU 3
#define TAG_EDITBOX_NHAPLAI_MATKHAU 4
#define TAG_EDITBOX_NHAP_SDT 5

using namespace cocos2d::ui;

Scene* RegisterScene::createScene() {
    
    auto scene = Scene::create();
    
    auto layer = RegisterScene::create();

    scene->addChild(layer);

    return scene;
}

bool RegisterScene::init() {
    
    if (!BaseScene::init()) {
        return false;
    }
    
    auto bkg = MSprite::create("bgr_register.jpg",visibleSize);
    bkg->setPosition(MVec2(0,0));
    this->addChild(bkg);
    
    this->initMenu();
    
    this->scheduleUpdate();

    return true;
}

void RegisterScene::initMenu(){
    
    auto bigken = MSprite::create("bigken_logo.png");
    bigken->setPosition(MVec2(20, visibleHeight - bigken->getHeight() - 20));
    this->addChild(bigken);
    
    auto girl = MSprite::create("girl2.png");
    girl->setPosition(MVec2(visibleWidth / 6,0));
    this->addChild(girl);
    
    
    //==================================== Buttons
    
    //register Button
    auto btn_register = MButton::create("ic_button_register.png",TAG_BTN_REGISTER);
    btn_register->setPosition(MVec2(visibleWidth - 50 - btn_register->getWidth(), visibleHeight / 3));
    btn_register->setZoomScale(0.01f);
    btn_register->addTouchEventListener(CC_CALLBACK_2(RegisterScene::menuCallBack, this));
    this->addChild(btn_register);
    
    // item nhap lai mat khau
    auto item_nhaplai_matkhau = MSprite::create("ic_button_password.png");
    item_nhaplai_matkhau->setPosition(Vec2(btn_register->getPosition().x,
                                        btn_register->getPosition().y+btn_register->getHeight()+20));
    this->addChild(item_nhaplai_matkhau);
    
    // item nhap mat khau
    auto item_nhap_matkhau = MSprite::create("ic_button_password.png");
    item_nhap_matkhau->setPosition(Vec2(btn_register->getPosition().x,
                                        item_nhaplai_matkhau->getPosition().y+item_nhaplai_matkhau->getHeight()+20));
    this->addChild(item_nhap_matkhau);
    
    // item nhap sdt
    auto item_nhap_sdt = MSprite::create("ic_button_isdn.png");
    item_nhap_sdt->setPosition(Vec2(btn_register->getPosition().x,
                                    item_nhap_matkhau->getPosition().y+item_nhap_matkhau->getHeight()+20));
    this->addChild(item_nhap_sdt);
    
    auto background_nhap_register = MSprite::create("ic_editbox_register.png");
    
    
    // btn back
    auto btn_back = MButton::create(BTN_BACK,TAG_BTN_BACK);
    btn_back->setPosition(Vec2(visibleWidth - 10 - btn_back->getWidth(), 10));
    btn_back->addTouchEventListener(CC_CALLBACK_2(RegisterScene::menuCallBack, this));
    this->addChild(btn_back);
    
    //==================================== Text Field
    
    auto nhaplai_matkhau = MEditBox::create(background_nhap_register->getContentSize(),"ic_editbox_register.png");
    nhaplai_matkhau->setPosition(Vec2(item_nhaplai_matkhau->getPosition().x+item_nhaplai_matkhau->getWidth(),
                                      item_nhaplai_matkhau->getPosition().y));
    nhaplai_matkhau->setPlaceHolder("Nhập lại mật khẩu");
    nhaplai_matkhau->setMaxLength(12);
    nhaplai_matkhau->setTag(TAG_EDITBOX_NHAPLAI_MATKHAU);
    nhaplai_matkhau->setInputFlag(EditBox::InputFlag::PASSWORD);
    nhaplai_matkhau->setDelegate(this);
    this->addChild(nhaplai_matkhau);
    
    // editbox nhap mat khau

    auto nhap_matkhau = MEditBox::create(background_nhap_register->getContentSize(),"ic_editbox_register.png");
    nhap_matkhau->setPosition(Vec2(item_nhap_matkhau->getPosition().x + item_nhap_matkhau->getWidth(),
                                   item_nhap_matkhau->getPosition().y));
    nhap_matkhau->setPlaceHolder("Nhập mật khẩu");
    nhap_matkhau->setMaxLength(12);
    nhap_matkhau->setTag(TAG_EDITBOX_NHAP_MATKHAU);
    nhap_matkhau->setInputFlag(EditBox::InputFlag::PASSWORD);
    nhap_matkhau->setDelegate(this);
    this->addChild(nhap_matkhau);
    
    
    // editbox nhap sdt
    
    auto nhap_sdt = MEditBox::create(background_nhap_register->getContentSize(),"ic_editbox_register.png");
    nhap_sdt->setPosition(Vec2(item_nhap_sdt->getPosition().x+item_nhap_sdt->getWidth(),
                               item_nhap_sdt->getPosition().y));
    nhap_sdt->setPlaceHolder("Nhập số điện thoại");
    nhap_sdt->setMaxLength(12);
    nhap_sdt->setTag(TAG_EDITBOX_NHAP_SDT);
    nhap_sdt->setInputMode(EditBox::InputMode::NUMERIC);
    nhap_sdt->setDelegate(this);
    this->addChild(nhap_sdt);
    
}

bool registerSuccess = false;

std::mutex mtx_register;

void RegisterScene::update(float delta){
   
    int k = -1;
    
    mtx_register.lock();
    pair<google::protobuf::Message*, int> registerResult;
    for (int i=0; i<NetworkManager::listEvent.size(); i++) {
        if(NetworkManager::listEvent[i][0].second == NetworkManager::REGISTER){
            registerResult = NetworkManager::listEvent[i][0];
            registerSuccess = ((BINRegisterResponse *) registerResult.first)->responsecode();
            k = i;
            break;
        }
    }
    
    if(k != -1)
        NetworkManager::listEvent.erase(NetworkManager::listEvent.begin() + k);
    mtx_register.unlock();
    
    if(k != -1) {
        if(registerSuccess){
            auto showgame = ShowGame::createScene();
            Director::getInstance()->replaceScene(TransitionCrossFade::create(0.1f,showgame));
            registerSuccess = false;
        } else {
            cocos2d::MessageBox(((BINRegisterResponse *) registerResult.first)->message().c_str(), "xxx");
        }
    }
}

std::string user_id_str_register;
std::string password_str_register;
std::string re_password_str_register;

void RegisterScene::menuCallBack(Ref *sender,Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED){
        MButton * button = (MButton*) sender;
        int tag = button->getTag();
        switch (tag) {
            case TAG_BTN_REGISTER:
            {
                if(user_id_str_register.empty() || password_str_register.empty()
                   || re_password_str_register.empty()){
                    
                    cocos2d::MessageBox("Vui lòng nhập vào ô còn trống!",
                                        "Đăng ký");
                    
                    return;
                }
                if(password_str_register == re_password_str_register){
                    NetworkManager::getInstance()->getRegisterMessageFromServer(
                                                                                user_id_str_register,password_str_register, "");
                }else{
                    cocos2d::MessageBox("Mật khẩu xác nhận không chính xác!",
                                        "Đăng ký");
                }
            }
                break;
            case TAG_BTN_BACK:
                {
                    auto registerscene = LoginScene::createScene();
                    
                    Director::getInstance()->replaceScene(TransitionMoveInL::create(0.25f, registerscene));
                    //Director::getInstance()->popScene();
                }
                break;
            default:
                break;
        }
        
    }
}

void RegisterScene::editBoxEditingDidBegin(EditBox *editBox) {
    CCLOG("%s","edit begin!");
}

void RegisterScene::editBoxEditingDidEnd(EditBox *editBox) {
    switch (editBox->getTag()) {
        case TAG_EDITBOX_NHAP_MATKHAU:
            password_str_register = editBox->getText();
            CCLOG("%s",this->nhap_matkhau_str.c_str());
            break;
        case TAG_EDITBOX_NHAPLAI_MATKHAU:
            re_password_str_register = editBox->getText();
            CCLOG("%s",this->nhaplai_matkhau_str.c_str());
            break;
        case TAG_EDITBOX_NHAP_SDT:
            user_id_str_register = editBox->getText();
            CCLOG("%s",this->nhap_sdt_str.c_str());
            break;
        default:
            break;
    }
    CCLOG("%s","edit end!");
}

void RegisterScene::editBoxTextChanged(EditBox *editBox, std::string &text) {
    CCLOG("%s","edit changed!");
}

void RegisterScene::editBoxReturn(EditBox *editBox) {
   
}

void RegisterScene::onExit() {
    BaseScene::onExit();
}
