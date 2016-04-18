#ifndef __TLMIENNAM_SCENE_H__
#define __TLMIENNAM_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Objects/CardSprite.hpp"
#include "BaseScene.hpp"

class SettingDialog;

using namespace cocos2d;
using namespace std;

class TLMienNam : public BaseScene
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    virtual void onExit() override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(TLMienNam);
    
    void update(float) override;

protected:
    vector<Card> _cards;
    vector<Card> _cards_left;
    vector<Card> _cards_right;
    vector<Card> _cards_top;
    
    vector<CardSprite*> card_tag;
    
    void initMenu(Size size,Vec2 origin);
    void initCards();
    Card getCard();
    void createCards(PositionIndex index,int tag);
    void createOtherCards(PositionIndex index,int tag,float marginX,float marginY,float rotage);
    void showInitCard();
    void initGame();
    double cardScale();
    
    void menuCallBack(Ref *pSender, ui::Widget::TouchEventType eventType);
    void playCallBack(Ref *pSender, ui::Widget::TouchEventType eventType);
    void cardCallBack(Ref *pSender, ui::Widget::TouchEventType eventType);
    
private:
    
    Sprite * sprite;
    int cardTag;
    //CardSprite *cardSprite;
    
    
   
};


#endif // __TLMIENNAM_SCENE_H__
