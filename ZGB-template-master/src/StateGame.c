#include "Banks/SetBank2.h"
#include "main.h"
#include "../res/src/player.h"

#include "..\res\src\towntilesgb.h"
#include "..\res\src\housetiles.h"
#include "../res/src/font.h"
#include "../res/src/window.h"

#include <gb/gb.h> 
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

UINT8 col_tiles_forest[] = {1,2,3,4,20,21,26,27,28,29,30,31,40,41,42,43,44,45,50,52,53,54,57,58,59,60,61,62,65,83,84,85,86,89,90,91,92,0};
UINT8 col_down_forest[] = {32,34,35,36,38,39,55,93,95,96,98,126,127,0};

UINT8 col_tiles_town[] = {3,4,5,6,7,8,9,10,11,12,13,14,31,32,71,73,77,0};
UINT8 col_down_town[] = {126,127,0};
const UINT16 bp_town1[] = {PALETTE_FROM_HEADER(towntilesgb)};

UINT8 col_tiles_house[] = {1,2,3,27,28,23,24,25,26,4,5,0};
UINT8 col_down_house[] = {126,127,0};
const UINT16 bp_house1[] = {PALETTE_FROM_HEADER(housetiles)};

extern UINT8* gameover_mod_Data[];
extern UINT8 current_life;

const UINT16 s_palette_1[] = {PALETTE_FROM_HEADER(player)};



//extern UINT8* forest_mod_Data[];
extern UINT8 current_level;
extern UINT8 last_level;
extern const UINT8 num_levels;
extern const struct MapInfo* levels[];

extern INT16 player_x;
extern INT16 player_y;
UINT16 ny;


void Start_StateGame() {
	UINT8 i;
	const struct MapInfo* level = levels[current_level];
	SPRITES_8x16;
	SpriteManagerLoad(0);
	SpriteManagerLoad(1);
	SpriteManagerLoad(2);
	SpriteManagerLoad(4);
	SpriteManagerLoad(6);
	SpriteManagerLoad(7);
	SpriteManagerLoad(9);
	SpriteManagerLoad(10);
	
	SpriteManagerLoad(13);
	SpriteManagerLoad(14);
	SpriteManagerLoad(15);
	SpriteManagerLoad(16);
	SpriteManagerLoad(17);
	SHOW_SPRITES;

	//scroll_target = SpriteManagerAdd(SpritePlayer, 24, 72);
	OBP0_REG = PAL_DEF(2,0,1,3);
	OBP1_REG = PAL_DEF(0,0,0,0);
	BGP_REG = PAL_DEF(0,1,2,3);
	
	INIT_FONT(font, PRINT_WIN);
	WX_REG = 7;
	WY_REG = (144 - (2 << 3));
	scroll_h_border = 2 << 3;
	InitWindow(0, 0, &window);
	SHOW_WIN;
	

	switch(current_level){
	
	case 0:
		
		if(last_level == 0){
			current_life = 4;
			scroll_target = SpriteManagerAdd(SpritePlayer, 16, 80);
    		
		}else if(last_level == 1){
			scroll_target = SpriteManagerAdd(SpritePlayer, 584, 80);
		}
		SetPalette(SPRITES_PALETTE, 0, 8, s_palette_1, bank_StateGame);
		SetPalette(BG_PALETTE, 0, 8, bp_town1, bank_StateGame);
		InitScroll(level, col_tiles_town, col_down_town);
		PlayMusic(gameover_mod_Data, 5, 0);
		break;
	case 1:
		if(last_level == 0){
			scroll_target = SpriteManagerAdd(SpritePlayer, 32, 224);
		}else{
			scroll_target = SpriteManagerAdd(SpritePlayer,128,56);
		}
		SetPalette(SPRITES_PALETTE, 0, 8, s_palette_1, bank_StateGame);
		SetPalette(BG_PALETTE, 0, 8, bp_house1, bank_StateGame);
		InitScroll(level, col_tiles_house, col_down_house);
		break;

	case 2:
		if(last_level == 1){
			scroll_target = SpriteManagerAdd(SpritePlayer, 56, 96);
		}else{
			scroll_target = SpriteManagerAdd(SpritePlayer, 616, 56);
		}
		SetPalette(SPRITES_PALETTE, 0, 8, s_palette_1, bank_StateGame);
		SetPalette(BG_PALETTE, 0, 8, bp_town1, bank_StateGame);
		InitScroll(level, col_tiles_town, col_down_town);
		break;

	case 3:
		if(last_level == 2){
			scroll_target = SpriteManagerAdd(SpritePlayer, 48, 56);
		}else{
			scroll_target = SpriteManagerAdd(SpritePlayer, 448, 56);
		}
		SetPalette(SPRITES_PALETTE, 0, 8, s_palette_1, bank_StateGame);
		SetPalette(BG_PALETTE, 0, 8, bp_house1, bank_StateGame);
		InitScroll(level, col_tiles_house, col_down_house);
		break;

	case 4:
		if(last_level == 3){
			scroll_target = SpriteManagerAdd(SpritePlayer, 32, 56);
		}else{
			scroll_target = SpriteManagerAdd(SpritePlayer, 448, 56);
		}
		SetPalette(SPRITES_PALETTE, 0, 8, s_palette_1, bank_StateGame);
		SetPalette(BG_PALETTE, 0, 8, bp_house1, bank_StateGame);
		InitScroll(level, col_tiles_house, col_down_house);
		break;

/*	case 2:
		MoveScroll(20, 568);
		scroll_target = SpriteManagerAdd(SpritePlayer, 100, 616);
		SetPalette(SPRITES_PALETTE, 0, 8, s_palette_1, bank_StateGame);
		SetPalette(BG_PALETTE, 0, 8, bp_forest1, bank_StateGame);
		InitScroll(level, col_tiles_1, col_down);
		break;
	*/
	
	}
	SHOW_BKG;
	
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0x77; //Max volume
	//PlayMusic(forest_mod_Data,5,1);
}

void Update_StateGame() {
/*	if(scroll_target && (current_level == 0 || current_level == 2)){
		scroll_target = 0;
		ny = player_y;
	}
	if(scroll_target == 0 && (current_level == 0 || current_level == 2)) {
		
		if(U_LESS_THAN(scroll_bottom_movement_limit, player_y - scroll_y)) {
			ny = player_y - scroll_bottom_movement_limit;
		} else if(U_LESS_THAN(player_y - scroll_y, scroll_top_movement_limit)) {
			ny = player_y - scroll_top_movement_limit;
		}

		MoveScroll(20, ny);
	}

	*/
	if(KEY_TICKED(J_SELECT)){
		current_level++;	
		SetState(current_state);
	}
	if(KEY_TICKED(J_START)){
		
	}
}