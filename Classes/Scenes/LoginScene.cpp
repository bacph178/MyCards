#include "LoginScene.h"
#include "RegisterScene.h"
#include "ShowGame.h"

#include "UI/MButton.hpp"
#include "UI/MLabel.hpp"
#include "UI/MSprite.hpp"
#include "UI/MEditBox.hpp"
#include "UI/MLabel.hpp"
#include "UI/MText.hpp"

#include "Utils/NetworkManager.h"

#include "Utils/TLMNConfig.hpp"

#include <protobufObject/login.pb.h>
#include <thread>

#include <iostream>

#if WIN32
#pragma comment(lib, "libprotobuf.lib")
#endif



#include <string>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include "zlib.h"

#define MOD_GZIP_ZLIB_WINDOWSIZE 15
#define MOD_GZIP_ZLIB_CFACTOR    9
#define MOD_GZIP_ZLIB_BSIZE      8096
#define MAX_SIZE 1024 * 1024



#define TAG_BTN_FACEBOOK 1
#define TAG_BTN_LOGIN 2
#define TAG_BTN_REGISTER 3
#define TAG_BTN_PLAYNOW 4
#define TAG_BTN_FOGOTPASSWORD 5
#define TAG_EDITBOX_MATKHAU 6
#define TAG_EDITBOX_TAIKHOAN 7

using namespace cocos2d::ui;

Scene* LoginScene::createScene() {
    
    auto scene = Scene::create();
   
    auto layer = LoginScene::create();

    scene->addChild(layer);

    return scene;
}

bool LoginScene::init() {
    
    if ( !BaseScene::init() ) {
        return false;
    }
    
    
    
    auto bkg = MSprite::create(BKG_LOGIN,visibleSize);
    bkg->setPosition(MVec2(0, 0));
    
    
    //hotline
    auto hotline_txt = MLabel::create("Hotline : 19001755",25);
    hotline_txt->setPosition(MVec2(15,height-15-hotline_txt->getHeight()));
    
    
    //version
    auto version_txt = MLabel::create("Ver 1.0",25);
    version_txt->setPosition(MVec2(width-version_txt->getWidth()-15,
                                  height-15-version_txt->getHeight()));
    
    
    //girl
    auto girl = MSprite::create(SPRITE_GIRL_LOGIN);
    girl->setPosition(originX + width / 8, originY);
    
    
    //========================= buttons
    
    
    //loginfacebook Button
    auto btn_login_facebook = MButton::create(BTN_LOGIN_FACEBOOK,"Đăng nhập facebook",30,TAG_BTN_FACEBOOK);
    btn_login_facebook->setPosition(MVec2(width*0.95f-btn_login_facebook->getWidth(),height/3.0f));
    btn_login_facebook->setZoomScale(0.01f);
    btn_login_facebook->addTouchEventListener( CC_CALLBACK_2(LoginScene::menuCallBack,this));
    
    
    //đăng nhập
    auto btn_login = MButton::create(BTN_LOGIN,"Đăng nhập",30,TAG_BTN_LOGIN);
    btn_login->setPosition(Vec2(btn_login_facebook->getPosition().x,
                                btn_login_facebook->getPosition().y+btn_login_facebook->getHeight()-5));
    btn_login->addTouchEventListener( CC_CALLBACK_2(LoginScene::menuCallBack,this));
    
    
    //đăng ký
    auto btn_register = MButton::create(BTN_LOGIN,"Đăng ký",30,TAG_BTN_REGISTER);
    btn_register->setPosition(Vec2(btn_login_facebook->getPosition().x+btn_login_facebook->getWidth()/2
                                   -btn_register->getWidth()/2,
                                   btn_login->getPosition().y));
    btn_register->addTouchEventListener( CC_CALLBACK_2(LoginScene::menuCallBack,this));
    
    
    //choi ngay
    auto btn_playnow = MButton::create(BTN_LOGIN,"Chơi ngay",30,TAG_BTN_PLAYNOW);
    btn_playnow->setPosition(Vec2(btn_login_facebook->getPosition().x+btn_login_facebook->getWidth()
                                  -btn_playnow->getWidth(),
                                  btn_login->getPosition().y));
    btn_playnow->addTouchEventListener( CC_CALLBACK_2(LoginScene::menuCallBack,this));
    
    
    //quen mk
    auto fogotPassword = MButton::create("Quên mật khẩu?",25,TAG_BTN_FOGOTPASSWORD);
    fogotPassword->setPosition(Vec2(btn_login_facebook->getPosition().x+btn_login_facebook->getWidth()
                                    -fogotPassword->getWidth()-5,
                                btn_playnow->getPosition().y+btn_playnow->getHeight()+10));
    fogotPassword->addTouchEventListener( CC_CALLBACK_2(LoginScene::menuCallBack,this));
    
    
    //underline
    auto under_line = MText::create("______________",25);
    under_line->setPosition(Vec2(fogotPassword->getPosition().x,fogotPassword->getPosition().y));
    
    //========================= Text Field
    
    // Textfield mat khau
    auto background_matkhau = MSprite::create(BKG_INPUT_LOGIN);
    
    auto edit_matkhau = MEditBox::create(background_matkhau->getContentSize(),BKG_INPUT_LOGIN);
    edit_matkhau->setPosition(Vec2(btn_login_facebook->getPosition().x+10,
                                   fogotPassword->getPosition().y+fogotPassword->getHeight()+10));
    edit_matkhau->setPlaceHolder("  Nhập mật khẩu");
    edit_matkhau->setMaxLength(12);
    edit_matkhau->setTag(TAG_EDITBOX_MATKHAU);
    edit_matkhau->setInputFlag(EditBox::InputFlag::PASSWORD);
    edit_matkhau->setDelegate(this);
    
    
    // Textfield tai khoan
    
    auto edit_user = MEditBox::create(background_matkhau->getContentSize(),BKG_INPUT_LOGIN);
    edit_user->setPosition(Vec2(edit_matkhau->getPosition().x,
                                edit_matkhau->getPosition().y+background_matkhau->getHeight()+10));
    edit_user->setPlaceHolder("  Nhập tên");
    edit_user->setTag(TAG_EDITBOX_TAIKHOAN);
    edit_user->setMaxLength(12);
    edit_user->setDelegate(this);
    
    
    this->addChild(bkg);
    this->addChild(hotline_txt);
    this->addChild(version_txt);
    this->addChild(girl);
    
    
    this->addChild(btn_login_facebook);
    this->addChild(btn_login);
    this->addChild(btn_register);
    this->addChild(btn_playnow);
    this->addChild(fogotPassword);
    this->addChild(under_line);
    
    this->addChild(edit_matkhau);
    this->addChild(edit_user);
    
    //edit_matkhau->touchDownAction(NULL, cocos2d::ui::Widget::TouchEventType::ENDED);
    
    
    sprite = Sprite::create("bgr_textview.png");
    sprite->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMidY());
    this->addChild(sprite, 0);
    
    this->scheduleUpdate();
    
    
    
    return true;
}


bool loginSuccess = false;


std::mutex mtx;

void LoginScene::update(float delta){
    auto position = sprite->getPosition();
    position.x -= 250 * delta;
    if (position.x  < 0 - (sprite->getBoundingBox().size.width / 2))
        position.x = this->getBoundingBox().getMaxX() + sprite->getBoundingBox().size.width/2;
    sprite->setPosition(position);
    int k = -1;
    mtx.lock();
    pair<google::protobuf::Message*, int> loginResult;
    for (int i=0; i<NetworkManager::listEvent.size(); i++) {
        if(NetworkManager::listEvent[i][0].second == NetworkManager::LOGIN){
            loginResult = NetworkManager::listEvent[i][0];
            loginSuccess = ((BINLoginResponse *) loginResult.first)->responsecode();
            k = i;
            break;
        }
    }
    
    if(k != -1)
        NetworkManager::listEvent.erase(NetworkManager::listEvent.begin() + k);
    
    mtx.unlock();
    
    
    
    if(k != -1) {
        if(loginSuccess){
            auto showgame = RegisterScene::createScene();
            Director::getInstance()->replaceScene(TransitionCrossFade::create(0.1f,showgame));
            loginSuccess = false;
        } else {
            cocos2d::MessageBox(((BINLoginResponse *) loginResult.first)->message().c_str(), "xxx");
        }
    }
}



std::string user_id_str;
std::string password_str;

struct membuf : std::streambuf
{
    membuf(char* begin, char* end) {
        this->setg(begin, begin, end);
    }
};


//======================

std::string compress_gzip(const std::string& str,
                          int compressionlevel = Z_BEST_COMPRESSION)
{
    z_stream zs;                        // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));
    
    if (deflateInit2(&zs,
                     compressionlevel,
                     Z_DEFLATED,
                     MOD_GZIP_ZLIB_WINDOWSIZE + 16,
                     MOD_GZIP_ZLIB_CFACTOR,
                     Z_DEFAULT_STRATEGY) != Z_OK
        ) {
        throw(std::runtime_error("deflateInit2 failed while compressing."));
    }
    
    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();           // set the z_stream's input
    
    int ret;
    char outbuffer[32768];
    std::string outstring;
    
    // retrieve the compressed bytes blockwise
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);
        
        ret = deflate(&zs, Z_FINISH);
        
        if (outstring.size() < zs.total_out) {
            // append the block to the output string
            outstring.append(outbuffer,
                             zs.total_out - outstring.size());
        }
    } while (ret == Z_OK);
    
    deflateEnd(&zs);
    
    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib compression: (" << ret << ") " << zs.msg;
        throw(std::runtime_error(oss.str()));
    }
    
    return outstring;
}

// Found this one here: http://panthema.net/2007/0328-ZLibString.html, author is Timo Bingmann
/** Compress a STL string using zlib with given compression level and return
 * the binary data. */
std::string compress_deflate(const std::string& str,
                             int compressionlevel = Z_BEST_COMPRESSION)
{
    z_stream zs;                        // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));
    
    if (deflateInit(&zs, compressionlevel) != Z_OK)
        throw(std::runtime_error("deflateInit failed while compressing."));
    
    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();           // set the z_stream's input
    
    int ret;
    char outbuffer[32768];
    std::string outstring;
    
    // retrieve the compressed bytes blockwise
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);
        
        ret = deflate(&zs, Z_FINISH);
        
        if (outstring.size() < zs.total_out) {
            // append the block to the output string
            outstring.append(outbuffer,
                             zs.total_out - outstring.size());
        }
    } while (ret == Z_OK);
    
    deflateEnd(&zs);
    
    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib compression: (" << ret << ") " << zs.msg;
        throw(std::runtime_error(oss.str()));
    }
    
    return outstring;
}

/** Decompress an STL string using zlib and return the original data. */
std::string decompress_deflate(const std::string& str)
{
    z_stream zs;                        // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));
    
    if (inflateInit(&zs) != Z_OK)
        throw(std::runtime_error("inflateInit failed while decompressing."));
    
    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();
    
    int ret;
    char outbuffer[32768];
    std::string outstring;
    
    // get the decompressed bytes blockwise using repeated calls to inflate
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);
        
        ret = inflate(&zs, 0);
        
        if (outstring.size() < zs.total_out) {
            outstring.append(outbuffer,
                             zs.total_out - outstring.size());
        }
        
    } while (ret == Z_OK);
    
    inflateEnd(&zs);
    
    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib decompression: (" << ret << ") "
        << zs.msg;
        throw(std::runtime_error(oss.str()));
    }
    
    return outstring;
}
vector<char> LoginScene::decompress_gzip2(const char* byte_arr, uLong length) {
    
    vector<char> result;
    vector<char> nil_vector;
    if (length == 0) return nil_vector;
    bool done = false;
    z_stream zs;
    memset(&zs, 0, sizeof(zs));
    
    zs.next_in = (Bytef*) byte_arr;
    zs.avail_in = length;
    zs.total_out = 0;
    zs.zalloc = Z_NULL;
    zs.zfree = Z_NULL;
    
    if (inflateInit2(&zs, MOD_GZIP_ZLIB_WINDOWSIZE + 16) != Z_OK)  return nil_vector;
    
    int ret;
    
    char outbuffer[32768];
    
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);
        
        ret = inflate(&zs, Z_SYNC_FLUSH);
        
        if (result.size() < zs.total_out) {
            int size = result.size();
            for (int i = 0; i < zs.total_out - size; i++)
                result.push_back(outbuffer[i]);
        }
        
    } while (ret == Z_OK);
    
    inflateEnd(&zs);
    
    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib decompression: (" << ret << ") "
        << zs.msg;
        return nil_vector;
    }
    return result;
}

std::string decompress_gzip(const std::string &str)
{
    z_stream zs;                        // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));
    
    if (inflateInit2(&zs, MOD_GZIP_ZLIB_WINDOWSIZE + 16) != Z_OK)
        throw(std::runtime_error("inflateInit failed while decompressing."));
    
    
    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();
    
    
    int ret;
    char outbuffer[32768];
    std::string outstring;
    
    
    
    // get the decompressed bytes blockwise using repeated calls to inflate
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);
        
        ret = inflate(&zs, 0);
        
        
        if (outstring.size() < zs.total_out) {
            outstring.append(outbuffer,
                             zs.total_out - outstring.size());
        }
        
    } while (ret == Z_OK);
    
    inflateEnd(&zs);
    
    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib decompression: (" << ret << ") "
        << zs.msg;
        throw(std::runtime_error(oss.str()));
    }
    
    return outstring;
}


void LoginScene::menuCallBack(Ref *pSender, Widget::TouchEventType eventType){
    if(eventType == Widget::TouchEventType::ENDED){
        MButton *button = (MButton*) pSender;
        int tag = button->getTag();
        switch (tag) {
            case TAG_BTN_FACEBOOK:
                CCLOG("%s","Login with facebook!");
                break;
            case TAG_BTN_LOGIN:
                CCLOG("%s","Login with esxit!");
                NetworkManager::getInstance()->getLoginMessageFromServer(user_id_str, password_str);
                
                break;
            case TAG_BTN_REGISTER:
                {
                    auto registerscene = RegisterScene::createScene();
                    Director::getInstance()->replaceScene(TransitionMoveInR::create(0.25f, registerscene));
                    
                }
                break;
            case TAG_BTN_PLAYNOW:
                {
                    auto select = ShowGame::createScene();
                   Director::getInstance()->replaceScene(TransitionCrossFade::create(0.15f, select));
                }
                break;
            case TAG_BTN_FOGOTPASSWORD:
                CCLOG("%s","Forgot_Password!");
                break;
            default:
                break;
        }
    }

}

#pragma mark - EditBoxDelegate

void LoginScene::editBoxEditingDidBegin(EditBox *editBox) {
    CCLOG("%s","edit begin!");
}

void LoginScene::editBoxEditingDidEnd(EditBox *editBox) {
    
    CCLOG("%s","edit end!");
}

void LoginScene::editBoxTextChanged(EditBox *editBox, const std::string& text) {
    CCLOG("%s","edit changed!");
}

void LoginScene::editBoxReturn(EditBox *editBox) {
    switch (editBox->getTag()) {
        case TAG_EDITBOX_MATKHAU:
            password_str = editBox->getText();
            CCLOG("%s",password_str.c_str());
            break;
        case TAG_EDITBOX_TAIKHOAN:
            user_id_str = editBox->getText();
            CCLOG("%s",user_id_str.c_str());
            break;
        default:
            break;
    }
}

void LoginScene::onExit() {
    BaseScene::onExit();
}


