#include "ZGBMain.h"
#include "Math.h"

UINT8 next_state = StateGame;
extern UINT8 current_level;

UINT8 GetTileReplacement(UINT8* tile_ptr, UINT8* tile) {
	if(current_state == StateGame) {
		switch(current_level){
			case 0: *tile = 2;	break;
			case 1: *tile = 0; break;
			case 2: *tile = 2; break;
			case 3: *tile = 0; break;
			case 6: *tile = 1; break;
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
		}

		*tile = *tile_ptr;
	}

	return 255u;
}