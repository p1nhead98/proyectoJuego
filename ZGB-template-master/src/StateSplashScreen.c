#include "Banks/SetBank4.h"
#include "main.h"

#include "Scroll.h"
#include "Frame.h"
#include "Print.h"
#include "Sprite.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "Math.h"
#include "gbt_player.h"
#include "ZGBMain.h"
#include "Palette.h"
#include "../res/src/prologuemap.h"
#include "../res/src/prologuetiles.h"
#include "../res/src/font.h"

const UINT16 prologue[] = {PALETTE_FROM_HEADER(prologuetiles)};


extern UINT8 etapa;
extern UINT8 last_state;
INT8 splashScreenCounter;
void Start_StateSplashScreen() {
    
    SPRITES_8x16;
   splashScreenCounter = 0;
    SHOW_SPRITES;
    
    
	
    INIT_FONT(font, PRINT_BKG);
    switch(etapa){
        case 0:
            InitScroll(&prologuemap, 0,0);
            SetPalette(BG_PALETTE, 0, 8, prologue, bank_StateSplashScreen);
            PRINT(6, 3, "PROLOGUE");
            
        break;
    }
    
    SHOW_BKG;
   
    //MoveScroll(50, 0);
}

void Update_StateSplashScreen() {
    //PRINT(3, 17, "BLUEBLOOD 2020");
	
    if(splashScreenCounter <= 120){
        splashScreenCounter++;
        
    }else{
        splashScreenCounter = 0;
        switch(etapa){
            case 0:
                SetState(StateGame); 
            break;
        }
    }
}