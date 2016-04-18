//
//  CardSprite.cpp

#include "CardSprite.hpp"
#include "Utils/TLMNConfig.hpp"

using namespace cocos2d;
using namespace std;

CardSprite* CardSprite::create(Card card, PositionIndex PositionIndex) {
    
    CardSprite* cardSprite = CardSprite::create();
    cardSprite->setCard(card);
    cardSprite->setPositionIndex(PositionIndex);
    cardSprite->setSpriteFrame(card.ToString());
    cardSprite->addEvents();
    return cardSprite;
}

bool CardSprite::init() {
    
    if (!Sprite::init()) {
        return false;
    }
    
    this->isBack = false;
    this->cardState = Idle;
    this->isFirstTimeClick = false;
    this->origionPostion = Vec2(0,0);
    
    return true;
}

string CardSprite::getName(){
    return getFileName();
}

void CardSprite::onEnter() {
    Sprite::onEnter();
}

void CardSprite::addEvents(){
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&](Touch* touch, Event* event) {
        Vec2 p = touch->getLocation();
        Rect rect = this->getBoundingBox();
        
        if(rect.containsPoint(p))
        {
            return true; // to indicate that we have consumed it.
        }
        
        return false; // we did not consume this event, pass thru.
    };
    
    listener->onTouchEnded = [=](Touch* touch, Event* event) {
        
        CardSprite::touchEvent(touch);
        if(cardState == Idle){
            if(!isFirstTimeClick){
                origionPostion = this->getPosition();
                isFirstTimeClick = true;
            }
            cardState = OnHand;
            auto moveBy = MoveBy::create(0.15f, Vec2(0,25));
            this->runAction(moveBy);
            
        }else if(cardState == OnHand){
            cardState = Idle;
            isFirstTimeClick = false;
            auto moveBy = MoveBy::create(0.15f, Vec2(0,-25));
            this->runAction(moveBy);
        }
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

// MOVE

void CardSprite::setMove(float x, float y, float time){
    this->runAction(MoveTo::create(time, Vec2(x,y)));
}

void CardSprite::setMove(float x, float y){
    this->runAction(MoveTo::create(0.15f, Vec2(x,y)));
}

// GET & SET

string CardSprite::getValue(){
    return to_string(cardValue % 10);
}

string CardSprite::getSuit(){
    return to_string(cardValue / 10);
}

void CardSprite::setIsBack(bool isBack){
    this->isBack = isBack;
}

bool CardSprite::getIsBack(){
    return this->isBack;
}

void CardSprite::setState(CardState state){
    this->cardState = state;
}

CardState CardSprite::getState(){
    return this->cardState;
}

void CardSprite::setCardValue(int cardValue){
    this->cardValue = cardValue;
}

int CardSprite::getCardValue(){
    return this->cardValue;
}

int CardSprite::getNumberValue(){
    return this->cardValue / 10;
}

int CardSprite::getNumberSuit(){
    return this->cardValue % 10;
}

void CardSprite::setIndex(int index){
    this->index = index;
}

int CardSprite::getIndex(){
    return this->index;
}


void CardSprite::update(){
    switch(cardState)
    {
        case Idle:
        {
            break;
        }
        case OnHand:
        {
            break;
        }
        case Putted:
        {
            break;
        }
        case Fold:
        {
            break;
        }
        case Destroy:
        {
            
            break;
        }
        default:
        {
            break;
        }
    }
}

// Touch Event!

void CardSprite::touchEvent(Touch* touch)
{
    CCLOG("touched : %s",getName().c_str());
}

string CardSprite::getFileName()
{
    std::string filename;
    int type = this->cardValue % 10;
    int number = this->cardValue / 10;
    
    switch (type) {
        case 3: {
            filename = filename = StringUtils::format("%02dro.png", number);
            break;
        }
        case 4: {
            filename = filename = StringUtils::format("%02dco.png", number);
            break;
        }
        case 2: {
            filename = filename = StringUtils::format("%02dtep.png", number);
            break;
        }
        case 1: {
            filename = filename = StringUtils::format("%02dbich.png", number);
            break;
        }
            
            
        default: {
            filename = StringUtils::format("nullx.png");
            break;
        }
    }
    
    return filename;
}