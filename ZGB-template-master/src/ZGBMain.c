#include "ZGBMain.h"
#include "Math.h"

UINT8 next_state = StateGame;

UINT8 GetTileReplacement(UINT8* tile_ptr, UINT8* tile) {
	if(current_state == StateGame) {
		*tile = 0;
		switch (*tile_ptr){
		case 255: return SpriteSkeleton; break;
		case 254: return SpriteGhost; break;
		case 253: return SpriteWoodSpider; break;
		case 252: return SpriteViper; break;
		case 251: return SpriteWizzard; break;
		case 250: return SpriteTinyDevil; break;
		}

		*tile = *tile_ptr;
	}

	return 255u;
}