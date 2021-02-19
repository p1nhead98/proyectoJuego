#include "ZGBMain.h"
#include "Math.h"

UINT8 next_state = StateTitleScreen;
extern UINT8 current_level;

UINT8 GetTileReplacement(UINT8* tile_ptr, UINT8* tile) {
	if(current_state == StateGame) {
		switch(current_level){
			case 0: *tile = 2;	break;
			case 1: *tile = 0; break;
			case 2: *tile = 2; break;
			case 3: *tile = 0; break;
			case 6: *tile = 18; break;
			default: *tile = 0; break;
		}
		
		switch (*tile_ptr){
		case 254: return SpriteGhost; break;
		case 253: return SpriteWoodSpider; break;
		case 252: return SpriteViper; break;
		case 251: return SpriteWizzard; break;
		case 250: return SpriteTinyDevil; break;
		case 249: return SpriteSkeleton; break;
		case 248: return SpriteFlyingMen; break;
		case 247: return SpriteFireSkel; break;
		case 246: return SpriteShooter; break;
		case 245: return SpriteEye; break;
		case 244: return SpriteLand; break;
		case 243: return SpriteStoneMan; break;
		case 242: return SpriteSkelBoss; break;
		case 241: return SpriteTitleFace; break;
		case 240: return SpriteForestBossH; break;
		case 239: return SpriteFallenLog; break;
		case 238: return SpriteSpitter; break;
		case 237: return SpriteSwingingLog; break;
		case 236: return SpriteMidBoss1; break;
		}

		*tile = *tile_ptr;
	}else if (current_state == StateTitleScreen){
			*tile = 90 ; 


			switch (*tile_ptr){
		
		case 254: return SpriteTitleFace; break;
		}
		*tile = *tile_ptr;
	}

	return 255u;
}