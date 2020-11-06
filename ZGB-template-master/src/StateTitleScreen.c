#include "Banks/SetBank7.h"
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
#include "..\res\src\titleScreen.h"
#include "..\res\src\titleScreenTiles.h"
#include "..\res\src\titleFace.h"
#include "../res/src/font.h"
const UINT16 bp_titlescreen[] = {PALETTE_FROM_HEADER(titleScreenTiles)};
const UINT16 s_titleScreen[] = {PALETTE_FROM_HEADER(titleFace)};
extern INT8 current_life;
extern const UINT8 max_life;
extern UINT8 etapa;
extern UINT8 last_state;
extern UINT8 subweaponCounter;
INT8 titlecounter;
void Start_StateTitleScreen() {
    
    SPRITES_8x16;
    titlecounter = 0;
    SHOW_SPRITES;
    etapa = 0;
    
	
    INIT_FONT(font, PRINT_BKG);
    SpriteManagerLoad(25);
    InitScroll(&titleScreen, 0,0);
    SHOW_BKG;
    SetPalette(SPRITES_PALETTE, 0, 8, s_titleScreen, bank_StateTitleScreen);
    SetPalette(BG_PALETTE, 0, 8, bp_titlescreen, bank_StateTitleScreen);
    //MoveScroll(50, 0);
}

void Update_StateTitleScreen() {
    //PRINT(3, 17, "BLUEBLOOD 2020");
	if(KEY_TICKED(J_START)) {
		current_life = max_life;
        subweaponCounter = 0;
        last_state = current_state;
		SetState(StateSplashScreen);
	}
    if(titlecounter <= 60){
        titlecounter++;
        if(titlecounter <= 30){
            PRINT(2, 9, "PRESS");
            PRINT(4, 10, "START");
        }else{
            PRINT(2, 9, "     ");
            PRINT(4, 10, "     ");
        }
    }else{
        titlecounter = 0;
    }
}