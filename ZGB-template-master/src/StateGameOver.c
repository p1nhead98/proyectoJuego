#include "Banks/SetBank4.h"
#include "main.h"

#include <gb/gb.h>
#include "ZGBMain.h"
#include "Scroll.h"

#include "Keys.h"
#include "Palette.h"
#include "Frame.h"
#include "Print.h"
#include "..\res\src\housetiles.h"
#include "../res/src/gameoverscreen.h"
#include "../res/src/font.h"
const UINT16 bp_gameoverscreen[] = {PALETTE_FROM_HEADER(housetiles)};

extern INT8 current_life;
extern const UINT8 max_life;
void Start_StateGameOver() {
	InitScroll(&gameoverscreen, 0, 0);
	SHOW_BKG;
    SetPalette(BG_PALETTE, 0, 8, bp_gameoverscreen, bank_StateGameOver);
    INIT_FONT(font, PRINT_BKG);
	PRINT(6, 8, "GAME OVER");

}

void Update_StateGameOver() {
	if(KEY_TICKED(J_START) ) {
		current_life = max_life;
		SetState(StateGame);
	}
}