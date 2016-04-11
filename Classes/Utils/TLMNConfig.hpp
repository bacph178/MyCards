//
//  TLMNConfig.hpp
//  MyCards
//
//  Created by Black3rry on 4/9/16.
//
//

#ifndef __TLMNCONFIG_H__
#define __TLMNCONFIG_H__

extern const int		SCREEN_WIDTH;
extern const int		SCREEN_HEIGHT;

extern const char* SERVER_NAME;
extern const int SERVER_PORT;

enum
{
    Z_BACKGROUND = 0,
    Z_POPUP,
    Z_POPUP_BACKGROUND,
    Z_GAMEBOARD,
    
    Z_SIDEBAR,
};

enum {
    kCardLayer1 = 1,
    kCardLayer2 = 1,
    kCardLayer3 = 3,
    kCardLayer4 = 4,
    kCardLayer5 = 5,
    kCardlayer6 = 6
};

enum {
    kGameIntro,
    kGamePlay,
    kGameOver
};

enum CardState {
    Idle,
    OnHand,
    Putted,
    Fold,
    Destroy
};

enum PlayerState{
    Idle_Player,
    Play,
    Pass,
    Win,
    Lose,
    Pre
};

enum CardType {
    Hearts = 0,
    Diamonds,
    Clubs,
    Spade,
    OTHER
};

extern const char*		SPR_BACKGROUND_MAINMENU;
extern const char*		SPR_GAME_TITLE;
extern const char*		SPR_GAMEPLAY_BOARD_BACKGROUND;

extern const char*		SPR_GAMEPLAY_SCORE_BACKGROUND;
extern const char*		SPR_GAMEPLAY_SCORE_BACKGROUND_LIGHTMAP;

extern const char*		SPR_SIDEBAR;

//== Login screen
extern const char* BTN_LOGIN_FACEBOOK ;
extern const char* BTN_LOGIN ;
extern const char* BTN_REGISTER ;
extern const char* BTN_PLAY_NOW ;
extern const char* BKG_INPUT_LOGIN ;

extern const char* SPRITE_GIRL_LOGIN ;
extern const char* BKG_LOGIN ;

//== Register screen
extern const char* BTN_REGISTER_REGISTER ;
extern const char* BKG_INPUT_SDT ;
extern const char* BKG_INPUT_PASSWORD ;
extern const char* BKG_INPUT_REPASSWORD ;
extern const char* SPRITE_BIGKEN_ONLINE ;
extern const char* SPRITE_GIRL_REGISTER ;
extern const char* BKG_REGISTER ;

//== List Game Screen
extern const char* BTN_ITEM_GAME ;
extern const char* BTN_BACK ;
extern const char* BTN_MENU ;
extern const char* BTN_SETTING;
extern const char* BTN_HELPER ;
extern const char* BTN_CENTS ;
extern const char* BTN_DOI_THUONG ;
extern const char* BKG_AVATAR ;
extern const char* SPRITE_COINS ;
extern const char* SPRITE_KENS ;
extern const char* SPRITE_LIST_GAME ;
extern const char* BKF_LIST_GAME ;

// TLMN
extern const char* BTN_MESSAGE ;
extern const char* BTN_SOUND_ON ;
extern const char* BTN_SOUND_OFF ;
extern const char* BTN_PURCHASE ;
extern const char* BTN_BUTTON ;
extern const char* BKG_CHAT_BOX ;
extern const char* BKG_TABLE ;

#endif
