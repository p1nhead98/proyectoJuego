#include "Banks/SetBank5.h"
#include "main.h"
#include "../res/src/player.h"

#include "..\res\src\towntilesgb.h"
#include "..\res\src\housetiles.h"
#include "..\res\src\boss1.h"
#include "../res/src/font.h"
#include "../res/src/window.h"
#include "../res/src/gobpalette.h"
#include "../res/src/gospalette.h"
#include "../res/src/skelboss.h"

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

UINT8 col_tiles_town[] = {3,4,5,6,7,8,9,10,11,12,13,14,31,32,78,79,80,81,82,83,84,0};
UINT8 col_down_town[] = {126,127,0};
const UINT16 bp_town1[] = {PALETTE_FROM_HEADER(towntilesgb)};

UINT8 col_tiles_house[] = {1,19,20,27,28,23,24,25,26,33,34,4,5,0};
UINT8 col_down_house[] = {126,127,0};
const UINT16 bp_house1[] = {PALETTE_FROM_HEADER(housetiles)};

const UINT16 bp_gameover[] = {PALETTE_FROM_HEADER(gobpalette)};
const UINT16 s_gameover[] = {PALETTE_FROM_HEADER(gospalette)};

const UINT16 s_boss1[] = {PALETTE_FROM_HEADER(skelboss)};

extern UINT8* tema3_mod_Data[];

UINT8 col_tiles_town2[] = {3,4,5,6,0};

extern UINT8* gameover_mod_Data[];
extern INT8 current_life;

extern UINT16 lives;

UINT8 water;
BOOLEAN gameOver;
const UINT16 s_palette_1[] = {PALETTE_FROM_HEADER(player)};

INT8 x = 0;
INT8 x2 = 0;
UINT8 count = 1;
//extern UINT8* forest_mod_Data[];
extern UINT8 current_level;
extern UINT8 last_level;
extern const UINT8 num_levels;
extern const struct MapInfo* levels[];
extern struct TilesInfo anim;
extern INT16 player_x;
extern INT16 player_y;
extern INT8 player_state;
UINT16 ny;



void Start_StateGame() {
	UINT8 i;
	const struct MapInfo* level = levels[current_level];
	gameOver = FALSE;
	SPRITES_8x16;
	/*
0: player
1: chain
2: skeleton
3 :ghost
4 :explosion
5: woodspider
6: viper
7: enemybullet
8: wizzard
9: tinydevil
10: flyngmen
11: fireskel
12: flame
13: up
14: bumerang
15: shooter
16: eye
17: land
18 :stoneman
19: stone
20: sword
21: knife
22: SkelBoss
23: boss1arm
24: sparkball
*/
	
	SHOW_SPRITES;

	//scroll_target = SpriteManagerAdd(SpritePlayer, 24, 72);
	
	BGP_REG = PAL_DEF(0,1,2,3);
	
	INIT_FONT(font, PRINT_WIN);
	WX_REG = 7;
	WY_REG = (144 - (2 << 3));
	scroll_h_border = 2 << 3;
	InitWindow(0, 0, &window);
	SHOW_WIN;
	x=0,x2=0;
	SpriteManagerLoad(0);
	SpriteManagerLoad(1);
	SpriteManagerLoad(4);
	SpriteManagerLoad(13);
	SpriteManagerLoad(14);
	SpriteManagerLoad(20);
	SpriteManagerLoad(21);
	SpriteManagerLoad(26);
	
	switch(current_level){
	
		case 0:
			
			SpriteManagerLoad(2);
			
			if(last_level == 0){
				PlayMusic(tema3_mod_Data, 1, 1);
				
				scroll_target = SpriteManagerAdd(SpritePlayer, 16, 95);
    		
			}else if(last_level == 1){
				scroll_target = SpriteManagerAdd(SpritePlayer, 624, 95);
			}
			SetPalette(SPRITES_PALETTE, 0, 8, s_palette_1, bank_StateGame);
			SetPalette(BG_PALETTE, 0, 8, bp_town1, bank_StateGame);
			
			InitScroll(level, col_tiles_town, col_down_town);
			//PlayMusic(gameover_mod_Data, 5, 0);
		break;

		case 1:
			SpriteManagerLoad(2);
			SpriteManagerLoad(7);
			SpriteManagerLoad(15);
			SpriteManagerLoad(16);
			if(last_level == 0){
				scroll_target = SpriteManagerAdd(SpritePlayer, 26, 224);
			}else{
				scroll_target = SpriteManagerAdd(SpritePlayer,128,56);
			}
			SetPalette(SPRITES_PALETTE, 0, 8, s_palette_1, bank_StateGame);
			SetPalette(BG_PALETTE, 0, 8, bp_house1, bank_StateGame);
			InitScroll(level, col_tiles_house, col_down_house);
		break;

		case 2:
			SpriteManagerLoad(7);
			SpriteManagerLoad(9);
			SpriteManagerLoad(15);
			SpriteManagerLoad(17);
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
			
	
			
			SpriteManagerLoad(6);
			SpriteManagerLoad(7);
	
		
			SpriteManagerLoad(15);
			SpriteManagerLoad(16); 
		
			SpriteManagerLoad(18);
			SpriteManagerLoad(19);
	
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
			SpriteManagerLoad(2);
			SpriteManagerLoad(17);
			SpriteManagerLoad(18);
			SpriteManagerLoad(19);
			if(last_level == 3){
				scroll_target = SpriteManagerAdd(SpritePlayer, 32, 56);
			}else{
				scroll_target = SpriteManagerAdd(SpritePlayer, 448, 56);
			}
			SetPalette(SPRITES_PALETTE, 0, 8, s_palette_1, bank_StateGame);
			SetPalette(BG_PALETTE, 0, 8, bp_house1, bank_StateGame);
			InitScroll(level, col_tiles_house, col_down_house);
		break;
		case 5:
			SpriteManagerLoad(2);
			SpriteManagerLoad(6);
			SpriteManagerLoad(7);
			SpriteManagerLoad(18);
			SpriteManagerLoad(19);
			if(last_level == 4){
				scroll_target = SpriteManagerAdd(SpritePlayer, 40, 40);
			}
			SetPalette(SPRITES_PALETTE, 0, 8, s_palette_1, bank_StateGame);
			SetPalette(BG_PALETTE, 0, 8, bp_town1, bank_StateGame);
			InitScroll(level, col_tiles_town, col_down_town);
		break;
		case 6:
			
			SpriteManagerLoad(22);
			SpriteManagerLoad(23);
			SpriteManagerLoad(24);
			if(last_level == 4){
				scroll_target = SpriteManagerAdd(SpritePlayer, 9, 128);
			}
			SetPalette(SPRITES_PALETTE, 0, 8, s_boss1, bank_StateGame);
			SetPalette(BG_PALETTE, 0, 8, bp_town1, bank_StateGame);
			InitScroll(level, col_tiles_town2, col_down_town);
		break;
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
	

	if(current_level == 0){
		if (--count == 0) {	
			count = 4;	
			x-- ;
			x2++;
			AnimateTiles_stage1();
		}
	}else if(current_level == 2 ||  current_level ==5){
		if (--count == 0) {	
			count = 7;	
			x-- ;
			AnimateTiles_stage1();
		}	
	}


	if(KEY_TICKED(J_START)){
		current_level++;	
		SetState(current_state);
	}
	

	if(gameOver == TRUE){
		HIDE_WIN;
		BGP_REG = PAL_DEF(3,3,3,3);
		OBP0_REG = PAL_DEF(0,0,0,0);
		SetPalette(SPRITES_PALETTE, 0, 8, s_gameover, bank_StateGame);
		SetPalette(BG_PALETTE, 0, 8, bp_gameover, bank_StateGame);
	}
}