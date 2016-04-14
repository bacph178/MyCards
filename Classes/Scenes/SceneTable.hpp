//
//  SceneTable.hpp
//  MyCards
//
//  Created by hungle on 4/13/16.
//
//


#ifndef __TABLE_SCENE_H__
#define __TABLE_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "UI/MSprite.hpp"
#include "BaseScene.hpp"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class SceneTable : public BaseScene {
public :
    
    static cocos2d::Scene* createScene(bool enableDisplayRoomList);
    
    void menuCallBack(Ref *sender,ui::Widget::TouchEventType type);
    void phongCallBack(Ref *sender,ui::Widget::TouchEventType type);
    void tableCallBack(Ref *sender,ui::Widget::TouchEventType type);
    void lTableCallBack(Ref *pSender, ui::ListView::EventType type);
    void rTableCallBack(Ref *pSender, ui::ListView::EventType type);
    void rScrollTableCallBack(Ref *pSender, ui::ScrollView::EventType type);
    
    virtual bool init() override;
    virtual void onExit() override;
    
    CREATE_FUNC(SceneTable);
    
    //void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    
public:
    void initMenu(Size size,Vec2 origin);
    void initTable(Size size,Vec2 origin);
    
protected:
    
    MSprite * btn_phong;
    
    ui::ListView* lvRight;
    ui::ListView* lvLeft;
    
    bool scroll_bottom;
    
};
#endif // __TABLE_SCENE_H__