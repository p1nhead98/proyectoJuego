#include "Banks/SetBank2.h"
#include "main.h"
#include "../res/src/player.h"
#include "..\res\src\tiles.h"
#include "..\res\src\ilusionforestiles.h"

#include "..\res\src\forest1_2.h"

#include "Scroll.h"
#include "Frame.h"
#include "Sprite.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "Math.h"
#include "gbt_player.h"
#include "ZGBMain.h"
#include "Palette.h"

UINT8 col_tiles_1[] = {1,2,3,4,20,21,26,27,28,29,30,31,40,41,42,43,44,45,50,52,53,54,57,58,59,60,61,62,65,83,84,85,86,89,90,91,92,0};
UINT8 col_down[] = {32,34,35,36,38,39,55,93,95,96,98,126,127,0};
const UINT16 s_palette_1[] = {PALETTE_FROM_HEADER(player)};
const UINT16 bp_forest1[] = {PALETTE_FROM_HEADER(ilusionforestiles)};

extern UINT8* forest_mod_Data[];

extern INT16 player_x;
extern INT16 player_y;
UINT16 ny;


void Start_StateGame() {
	UINT8 i;

	SPRITES_8x16;
	for(i = 0; i != N_SPRITE_TYPES; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

	scroll_target = SpriteManagerAdd(SpritePlayer, 24, 72);
	OBP0_REG = PAL_DEF(3,0,1,2);
	SetPalette(SPRITES_PALETTE, 0, 8, s_palette_1, bank_StateGame);
	SetPalette(BG_PALETTE, 0, 8, bp_forest1, bank_StateGame);
	InitScroll(&forest1_2, col_tiles_1, col_down);
	SHOW_BKG;
	//SpriteManagerAdd(SpriteSkeleton,144,552);
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0x77; //Max volume
	PlayMusic(forest_mod_Data,5,1);
}

void Update_StateGame() {
	/*

	if(scroll_target){
		scroll_target = 0;
		ny = player_y;
	}
	if(scroll_target == 0) {
		
		if(U_LESS_THAN(scroll_bottom_movement_limit, player_y - scroll_y)) {
			ny = player_y - scroll_bottom_movement_limit;
		} else if(U_LESS_THAN(player_y - scroll_y, scroll_top_movement_limit)) {
			ny = player_y - scroll_top_movement_limit;
		}

		MoveScroll(24, ny);
	}

	*/
}