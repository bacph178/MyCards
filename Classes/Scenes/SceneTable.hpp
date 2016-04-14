//
//  SceneTable.hpp
//  MyCards
//
//  Created by hungle on 4/13/16.
//
//


#ifndef __SCENE_TABLE_HPP__
#define __SCENE_TABLE_HPP__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "UI/MSprite.hpp"
#include "BaseScene.hpp"
#include "ui/CocosGUI.h"
#include "UI/MLabel.hpp"
#include "UI/M9Path.hpp"
#include "protobufObject/filter_room.pb.h"

using namespace cocos2d;

class SceneTable : public BaseScene {
public:

	static cocos2d::Scene* createScene(bool enableDisplayRoomList);

	void menuCallBack(Ref *sender, ui::Widget::TouchEventType type);
	void phongCallBack(Ref *sender, ui::Widget::TouchEventType type);
	void tableCallBack(Ref *sender, ui::Widget::TouchEventType type);
	void lTableCallBack(Ref *pSender, ui::ListView::EventType type);
	void rTableCallBack(Ref *pSender, ui::ListView::EventType type);
	void rScrollTableCallBack(Ref *pSender, ui::ScrollView::EventType type);
	virtual bool init() override;
	virtual void onExit() override;

	void update(float) override;

	CREATE_FUNC(SceneTable);

	//void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

public:
	void initMenu(Size size, Vec2 origin);
	void initTable(Size size, Vec2 origin, std::vector<BINRoomPlay> listRoomPlay);
	void addLayoutRight(M9Path *backgroundLeft, MLabel *hoatdong, Size visibleSize, Vec2 origin, std::vector<BINRoomPlay> listRoom);

protected:

	MSprite * btn_phong;

	ui::ListView* lvRight;
	ui::ListView* lvLeft;

	bool scroll_bottom;
	std::vector<BINRoomPlay> listRoomPlay;
    
};
#endif // __SCENE_TABLE_HPP__