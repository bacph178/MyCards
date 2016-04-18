#include "SceneTable.hpp"
#include "TLMienNam.h"
#include "UI/MButton.hpp"
#include "UI/MText.hpp"
#include "UI/M9Path.hpp"
#include "UI/MLabel.hpp"
#include "Utils/TLMNConfig.hpp"
#include "Utils/NetworkManager.h"
#include "Utils/Common.h"
#include "ShowGame.h"


#define TAG_BTN_BACK 1
#define TAG_BTN_PLAYNOW 2
#define TAG_BTN_CREATE 3
#define TAG_BTN_GOTO 4
#define TAG_BTN_REFRESH 5
#define TAG_BTN_PHONGVIP 6
#define TAG_BTN_PHONGFREE 7

using namespace cocos2d::ui;

bool enableDisplayRoomList;

Scene* SceneTable::createScene(bool tempEnableDisplayRoomList) {
    
    enableDisplayRoomList = tempEnableDisplayRoomList;
    
    auto scene = Scene::create();
    
    auto layer = SceneTable::create();
    
    scene->addChild(layer);
    
    return scene;
    
}

bool SceneTable::init() {
    
    if ( !BaseScene::init() ) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto background_screen = MSprite::create("bgr_select_table.jpg",visibleSize);
    background_screen->setPosition(Vec2(origin.x,origin.y));
    this->addChild(background_screen);
    
    if(enableDisplayRoomList){
        CCLOG("XXXX: true");
    }else{
        CCLOG("XXXX: false");
    }
    

	
    this->initTable(visibleSize, origin, listRoomPlay);
    
    this->initMenu(visibleSize, origin);
	NetworkManager::getInstance()->getFilterRoomMessageFromServer(
		Common::getInstance()->getZoneId(0), true, -1, -1);
	this->scheduleUpdate(); 
    return true;
    
}

bool isChangedStatus = false;

google::protobuf::Message* checkEvent(int message_id) {
	std::mutex mtx;
//	bool isSuccess = false;
	int k = -1;
	mtx.lock();
	//handle login
	pair<google::protobuf::Message*, int> result;
	for (int i = 0; i<NetworkManager::listEvent.size(); i++) {
		if (NetworkManager::listEvent[i][0].second == message_id){
			result = NetworkManager::listEvent[i][0];
			k = i;
			break;
		}
	}

	if (k != -1)
		NetworkManager::listEvent.erase(NetworkManager::listEvent.begin() + k);

	mtx.unlock();

	if (k != -1) { //found
		return result.first;
	}
	return 0;
}



void SceneTable::update(float delta) {
	BaseScene::update(delta);
	//handle filter room response
	BINFilterRoomResponse* response = (BINFilterRoomResponse*)checkEvent(NetworkManager::FILTER_ROOM);
	if (response != 0){
		if (response->responsecode()) {
			for (int i = 0; i < response->roomplays_size(); i++) {
				listRoomPlay.push_back(response->roomplays(i));
				// listRoomPlay.insert();
			}	
			setItemorListView(listRoomPlay); 
		}
		else {
			//
		}
	}

	//handle enter room response

	BINEnterRoomResponse *enterroomresponse = (BINEnterRoomResponse *)checkEvent(NetworkManager::ENTER_ROOM);

	if (enterroomresponse != 0) {
		if (enterroomresponse->responsecode()) {
			auto tlmiennam = TLMienNam::createScene();
			Director::getInstance()->replaceScene(TransitionCrossFade::create(0.25f, tlmiennam));
		}
		else {
			cocos2d::MessageBox(enterroomresponse->message().c_str(), "xxx");
		}
	}
}

void SceneTable::initMenu(Size visibleSize,Vec2 origin) {
    
    auto btn_back = MButton::create(BTN_BACK,TAG_BTN_BACK);
    btn_back->setPosition(Vec2(origin.x+10,origin.y+visibleSize.height-btn_back->getHeight()-10));
    btn_back->addTouchEventListener(CC_CALLBACK_2(SceneTable::menuCallBack, this));
    
    auto txt_game_name = MLabel::create("TL Miền Nam",35);
    txt_game_name->setPosition(Vec2(btn_back->getPosition().x+btn_back->getWidth()+10,
                                    btn_back->getPosition().y));
    
    auto btn_play_now = MButton::create("ic_button_second.png","Chơi ngay",30,Color3B(151,28,28),TAG_BTN_PLAYNOW);
    btn_play_now->setPosition(Vec2(origin.x+visibleSize.width-btn_play_now->getWidth()-10,
                                   origin.y+visibleSize.height-btn_play_now->getHeight()-10));
    btn_play_now->addTouchEventListener(CC_CALLBACK_2(SceneTable::menuCallBack, this));
    
    auto btn_create_table = MButton::create(BTN_BUTTON,"Tạo bàn",30,TAG_BTN_CREATE);
    btn_create_table->setPosition(Vec2(btn_play_now->getPosition().x-btn_create_table->getWidth()-10,
                                       btn_play_now->getPosition().y));
    btn_create_table->addTouchEventListener(CC_CALLBACK_2(SceneTable::menuCallBack, this));
    
    auto btn_goto_table = MButton::create(BTN_BUTTON,"Đến bàn",30,TAG_BTN_GOTO);
    btn_goto_table->setPosition(Vec2(btn_create_table->getPosition().x-btn_goto_table->getWidth()-10,
                                     btn_create_table->getPosition().y));
    btn_goto_table->addTouchEventListener(CC_CALLBACK_2(SceneTable::menuCallBack, this));
    
    auto btn_refresh = MButton::create("ic_button_refresh.png",TAG_BTN_REFRESH);
    btn_refresh->setPosition(Vec2(btn_goto_table->getPosition().x-btn_refresh->getWidth()-10,
                                  btn_goto_table->getPosition().y));
    btn_refresh->addTouchEventListener(CC_CALLBACK_2(SceneTable::menuCallBack, this));
    
    //==bottom bar under
    
    auto bar = MSprite::create("bgr_bottom_bar.png",Size(visibleSize.width,visibleSize.height*0.125f));
    bar->setPosition(origin.x,origin.y);
    
    btn_phong = MSprite::createExtendsUp("bgr_table_selected.png",Size(visibleSize.width*0.4f,visibleSize.height*0.125f));
    btn_phong->setPosition(Vec2(origin.x+visibleSize.width*0.2f,origin.y));
    
    //    auto btn_phong_vip = MSprite::createExtends("null_bkg.png","Phòng Vip",Size(visibleSize.width*0.4f,visibleSize.height*0.125f));
    //    btn_phong_vip->setPosition(Vec2(origin.x+visibleSize.width*0.2f,origin.y));
    //    btn_phong_vip->setTag(BTN_PHONGVIP);
    
    auto btn_phong_vip = MButton::create("null_bkg.png","Phòng Vip",30,TAG_BTN_PHONGVIP);
    btn_phong_vip->setPosition(Vec2(origin.x+visibleSize.width*0.4f-btn_phong_vip->getWidth()/2,
                                    origin.y+visibleSize.height*0.125f*0.5f-btn_phong_vip->getHeight()/2));
    btn_phong_vip->addTouchEventListener(CC_CALLBACK_2(SceneTable::phongCallBack, this));
    
    
    auto btn_phong_free = MButton::create("null_bkg.png","Phòng Free",30,TAG_BTN_PHONGFREE);
    btn_phong_free->setPosition(Vec2(origin.x+visibleSize.width*0.8f-btn_phong_free->getWidth()/2,
                                     origin.y+visibleSize.height*0.125f*0.5f-btn_phong_free->getHeight()/2));
    btn_phong_free->addTouchEventListener(CC_CALLBACK_2(SceneTable::phongCallBack, this));
    
    this->addChild(btn_back);
    this->addChild(txt_game_name);
    this->addChild(btn_play_now);
    this->addChild(btn_create_table);
    this->addChild(btn_goto_table);
    this->addChild(btn_refresh);
    
    this->addChild(bar);
    this->addChild(btn_phong);
    this->addChild(btn_phong_vip);
    this->addChild(btn_phong_free);
}

void SceneTable::addLayoutRight(M9Path *backgroundLeft, MLabel *hoatdong, Size visibleSize, Vec2 origin, std::vector<BINRoomPlay> listRoom) {
	auto backgroundRight = M9Path::create("tab_two.9.png", Size(visibleSize.width*0.8f, visibleSize.height*0.75f));
	backgroundRight->setPosition(origin.x + visibleSize.width*0.2f,
		origin.y + visibleSize.height / 2 - backgroundRight->getHeight() / 2);
	this->addChild(backgroundRight);

	auto ban_so = MLabel::create("Bàn số ▿", 32);
	ban_so->setPosition(Vec2(origin.x - ban_so->getWidth() / 2 + visibleSize.width*0.32f,
		hoatdong->getPosition().y));
	this->addChild(ban_so);

	auto tien_cuoc = MLabel::create("Tiền cược ▿", 32);
	tien_cuoc->setPosition(Vec2(origin.x - tien_cuoc->getWidth() / 2 + visibleSize.width*0.55f,
		hoatdong->getPosition().y));
	this->addChild(tien_cuoc);

	auto trang_thai = MLabel::create("Trạng thái ▿", 32);
	trang_thai->setPosition(Vec2(origin.x - trang_thai->getWidth() / 2 + visibleSize.width*0.76f,
		hoatdong->getPosition().y));
	this->addChild(trang_thai);

	auto khoa = MLabel::create("Khóa ▿", 32);
	khoa->setPosition(Vec2(origin.x - khoa->getWidth() / 2 + visibleSize.width*0.945f,
		hoatdong->getPosition().y));
	this->addChild(khoa);

	Layout* layoutRight = Layout::create();
	layoutRight->setContentSize(Size(backgroundRight->getWidth() - 30, backgroundRight->getHeight() * 5 / 6));
	layoutRight->setPosition(Vec2(origin.x + 15 + backgroundLeft->getWidth(), origin.y + visibleSize.height*0.125f));
	this->addChild(layoutRight);

	lvRight = ListView::create();
	for (int i = 0; i<listRoom.size(); i++)
	{
		auto bkg_item = Sprite::create("bgr_list_item.png");

		auto number_table = MLabel::create(listRoom[i].roomname(), 30);
		auto money = MLabel::create(listRoom[i].minbet() + " xu", 30);
		auto status = MLabel::create(listRoom[i].enteringplayer() + "/" + listRoom[i].roomcapacity(), 30);


		auto lock = Sprite::create("ic_lock.png");

		auto custom_item = Layout::create();

		custom_item->setContentSize(Size(layoutRight->getContentSize().width, lock->getContentSize().height * 2));

		bkg_item->setScale(layoutRight->getContentSize().width / bkg_item->getContentSize().width,
			lock->getContentSize().height * 2 / bkg_item->getContentSize().height);
		bkg_item->setPosition(layoutRight->getContentSize().width / 2, custom_item->getContentSize().height / 2);

		number_table->setPosition(Vec2(number_table->getContentSize().width / 2 + backgroundRight->getContentSize().width / 8,
			custom_item->getContentSize().height / 2.0f - number_table->getContentSize().height / 2));
		money->setPosition(Vec2(money->getContentSize().width / 2 + backgroundRight->getContentSize().width*2.5f / 8,
			custom_item->getContentSize().height / 2.0f - money->getContentSize().height / 2));
		status->setPosition(Vec2(status->getContentSize().width / 2 + backgroundRight->getContentSize().width * 5 / 8,
			custom_item->getContentSize().height / 2.0f - status->getContentSize().height / 2));
		lock->setPosition(Vec2(lock->getContentSize().width / 2 + backgroundRight->getContentSize().width * 7 / 8,
			custom_item->getContentSize().height / 2.0f));

		custom_item->addChild(bkg_item);
		custom_item->addChild(number_table);
		custom_item->addChild(money);
		custom_item->addChild(status);
		custom_item->addChild(lock);
		lock->setVisible(listRoom[i].passwordrequired());
		custom_item->setTouchEnabled(true);
		lvRight->pushBackCustomItem(custom_item);
	}
	lvRight->setItemsMargin(15);	
	/*lvRight->addEventListener([this](Ref* sender, ui::ListView::EventType type){
	CCLOG("123");
	});

	[this](Ref* sender, ui::ListView::EventType type) {
	if (type == ui::ListView::EventType::ON_SELECTED_ITEM_END){
	CCLOG("scrolViewCallback %s", "CLicked!");
	}
	}*/

	lvRight->setBounceEnabled(true);
	lvRight->setGravity(ListView::Gravity::LEFT);
	lvRight->setContentSize(layoutRight->getContentSize());
	lvRight->setTouchEnabled(true);
	lvRight->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(SceneTable::rTableCallBack, this));
	lvRight->addEventListener((ui::ScrollView::ccScrollViewCallback)CC_CALLBACK_2(SceneTable::rScrollTableCallBack, this));
	layoutRight->addChild(lvRight);
}

void SceneTable::initTable(Size visibleSize,Vec2 origin, vector<BINRoomPlay> listRoom){
    //layout left
    auto backgroundLeft = M9Path::create("tab_one.9.png",Size(visibleSize.width*0.2f,visibleSize.height*0.75f));
    backgroundLeft->setPosition(origin.x,origin.y+ visibleSize.height/2-backgroundLeft->getContentSize().height/2);
    this->addChild(backgroundLeft);
    
    auto hoatdong = MLabel::create("Hoạt động",32);
    hoatdong->setPosition(Vec2(origin.x+backgroundLeft->getContentSize().width/2-hoatdong->getContentSize().width/2,
                               backgroundLeft->getPosition().y+backgroundLeft->getContentSize().height
                               -1.8f*hoatdong->getContentSize().height));
    this->addChild(hoatdong);
    
    Layout* layoutLeft = Layout::create();
    layoutLeft->setContentSize(Size(backgroundLeft->getWidth()-30,backgroundLeft->getHeight()*5/6));
    layoutLeft->setPosition(Vec2(origin.x+15,origin.y+visibleSize.height*0.125f));
    this->addChild(layoutLeft);
    
    lvLeft = ListView::create();
    //auto testxxx = MText::create("This is a notification xxxxxx!",15);
    //lv1->setItemModel(testxxx);
    for(int i=0;i<20;i++){
        auto testxxx = MText::create("This is a notification xxxxxx!,nothing.don't look at me!please!",15);
        testxxx->ignoreContentAdaptWithSize(false);
        testxxx->setContentSize(Size(layoutLeft->getContentSize().width,testxxx->getHeight()*2));
        lvLeft->pushBackCustomItem(testxxx);
    }
    
    lvLeft->setItemsMargin(10);
    lvLeft->setGravity(ListView::Gravity::LEFT);
    lvLeft->setContentSize(layoutLeft->getContentSize());
    lvLeft->setScrollBarEnabled(false);
    layoutLeft->addChild(lvLeft);
    
    //==========================Layout Right
    
    
    auto backgroundRight = M9Path::create("tab_two.9.png",Size(visibleSize.width*0.8f,visibleSize.height*0.75f));
    backgroundRight->setPosition(origin.x+visibleSize.width*0.2f,
                                 origin.y+visibleSize.height/2-backgroundRight->getHeight()/2);
    this->addChild(backgroundRight);
    
    auto ban_so = MLabel::create("Bàn số ▿",32);
    ban_so->setPosition(Vec2(origin.x-ban_so->getWidth()/2 + visibleSize.width*0.32f,
                             hoatdong->getPosition().y));
    this->addChild(ban_so);
    
    auto tien_cuoc = MLabel::create("Tiền cược ▿",32);
    tien_cuoc->setPosition(Vec2(origin.x-tien_cuoc->getWidth()/2 + visibleSize.width*0.55f,
                                hoatdong->getPosition().y));
    this->addChild(tien_cuoc);
    
    auto trang_thai = MLabel::create("Trạng thái ▿",32);
    trang_thai->setPosition(Vec2(origin.x-trang_thai->getWidth()/2 + visibleSize.width*0.76f,
                                 hoatdong->getPosition().y));
    this->addChild(trang_thai);
    
    auto khoa = MLabel::create("Khóa ▿",32);
    khoa->setPosition(Vec2(origin.x-khoa->getWidth()/2 + visibleSize.width*0.945f,
                           hoatdong->getPosition().y));
    this->addChild(khoa);
    
    
    Layout* layoutRight = Layout::create();
    layoutRight->setContentSize(Size(visibleWidth * 0.8f - 30, visibleHeight * 0.75f * 5 / 6));
    layoutRight->setPosition(MVec2(15 + visibleWidth * 0.2f, visibleHeight * 0.125f));
    this->addChild(layoutRight);
    
    lvRight = ListView::create();
    lvRight->setItemsMargin(15);
	
    //setItemorListView(listRoomPlay);

    lvRight->setBounceEnabled(true);
    lvRight->setGravity(ListView::Gravity::LEFT);
    lvRight->setContentSize(layoutRight->getContentSize());
    lvRight->setTouchEnabled(true);
    lvRight->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(SceneTable::rTableCallBack, this));
    lvRight->addEventListener((ui::ScrollView::ccScrollViewCallback)CC_CALLBACK_2(SceneTable::rScrollTableCallBack, this));
    
    layoutRight->addChild(lvRight);
    //======

}

void SceneTable::setItemorListView(vector<BINRoomPlay> listRoom){
    
	lvRight->removeAllChildren();
	for (int i = 0; i<listRoom.size(); i++) {
        
        auto bkg_item = Sprite::create("bgr_list_item.png");
        char buffer[50];
        sprintf(buffer, "%d", listRoom[i].roomindex());
		auto number_table = MLabel::create(buffer, 30);
        sprintf(buffer, "%d xu", listRoom[i].minbet());
		auto money = MLabel::create(buffer, 30);
        sprintf(buffer, "%d/%d", listRoom[i].enteringplayer(), listRoom[i].roomcapacity());
		auto status = MLabel::create(buffer, 30);
        
        auto lock = Sprite::create("ic_lock.png");
        auto custom_item = Layout::create();
        
        Size size = Size(visibleWidth * 0.8f - 30, visibleHeight * 0.75f * 5 / 6);
        
        custom_item->setContentSize(Size(size.width,bkg_item->getContentSize().height));
        
        bkg_item->setScaleX(size.width/bkg_item->getContentSize().width);
        bkg_item->setPosition(size.width/2,custom_item->getContentSize().height/2);
        
        number_table->setPosition(Vec2(number_table->getContentSize().width/2+size.width/8,
                                       custom_item->getContentSize().height / 2.0f-number_table->getContentSize().height/2));
        money->setPosition(Vec2(money->getContentSize().width/2+size.width*2.5f/8,
                                custom_item->getContentSize().height / 2.0f-money->getContentSize().height/2));
        status->setPosition(Vec2(status->getContentSize().width/2+size.width*5/8,
                                 custom_item->getContentSize().height / 2.0f-status->getContentSize().height/2));
        lock->setPosition(Vec2(lock->getContentSize().width/2+size.width*7/8,
                               custom_item->getContentSize().height / 2.0f));
        
        custom_item->addChild(bkg_item);
        custom_item->addChild(number_table);
        custom_item->addChild(money);
        custom_item->addChild(status);
        custom_item->addChild(lock);
		lock->setVisible(listRoom[i].passwordrequired());
        custom_item->setTouchEnabled(true);
        lvRight->pushBackCustomItem(custom_item);
    }
}


void SceneTable::rTableCallBack(cocos2d::Ref *pSender, ui::ListView::EventType type){
    if(type == ui::ListView::EventType::ON_SELECTED_ITEM_END){
        
        ListView* listView = (ListView*) pSender;
        int index = listView->getCurSelectedIndex();
		
		CCLOG("index: %d", index);
		NetworkManager::getInstance()->getEnterRoomMessageFromServer(
			listRoomPlay[index].roomindex(), "");
    }
}

void SceneTable::rScrollTableCallBack(cocos2d::Ref *pSender, ui::ScrollView::EventType type){
    if(!scroll_bottom && type == ui::ScrollView::EventType::SCROLL_TO_BOTTOM){
        CCLOG("BOTTOM!");
        // setItemorListView(listRoomPlay);
        scroll_bottom = true;
    }
}

void SceneTable::tableCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if(type == Widget::TouchEventType::ENDED){
        //xxxxx
    }
}

void SceneTable::menuCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if(type == Widget::TouchEventType::ENDED){
        MButton *button = (MButton*) sender;
        int tag = button->getTag();
        switch (tag) {
            case TAG_BTN_BACK:
                CCLOG("%s","Button Back");
            {
                auto select = ShowGame::createScene();
                Director::getInstance()->replaceScene(TransitionCrossFade::create(0.15f, select));
            }
                break;
            case TAG_BTN_CREATE:
                CCLOG("%s","Button create");
                break;
            case TAG_BTN_GOTO:
                CCLOG("%s","Button GoTo");
                break;
            case TAG_BTN_PLAYNOW:
                CCLOG("%s","Button Play Now");
            {
                auto select = TLMienNam::createScene();
                Director::getInstance()->replaceScene(TransitionCrossFade::create(0.15f, select));
            }
                break;
            case TAG_BTN_REFRESH:
                CCLOG("%s","Button Refresh");
                break;
            default:
                break;
        }
    }
    
}

void SceneTable::phongCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if(type == Widget::TouchEventType::ENDED){
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        MButton *button = (MButton*) sender;
        int tag = button->getTag();
        switch (tag) {
            case TAG_BTN_PHONGVIP:
                CCLOG("%s","Phong Vip");
                btn_phong->runAction(MoveTo::create(0.1f, Vec2(origin.x+visibleSize.width*0.2f,origin.y)));
				//clear list and call network
				listRoomPlay.clear();
				NetworkManager::getInstance()->getFilterRoomMessageFromServer(
					Common::getInstance()->getZoneId(tag), true, -1, -1);
                break;
            case TAG_BTN_PHONGFREE:
                CCLOG("%s","Phong Free");
                btn_phong->runAction(MoveTo::create(0.1f, Vec2(origin.x+visibleSize.width*0.6f,origin.y)));
				//clear list and call network
				listRoomPlay.clear();
				NetworkManager::getInstance()->getFilterRoomMessageFromServer(
					Common::getInstance()->getZoneId(tag), false, -1, -1);
                break;
            default:
                break;
        }
    }
}

void SceneTable::onExit() {
    BaseScene::onExit();
};