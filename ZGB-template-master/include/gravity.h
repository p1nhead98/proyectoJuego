#ifndef GRAVITY_H
#define GRAVITY_H

#include "Print.h"


void gravity(struct Sprite* parent, UINT8 tile_colision){
    if(parent == 0 ){
		if(data->accel_y < 60  ) {
			data->accel_y += 4;
           }
	    tile_colision = TranslateSprite(THIS, 0, (data->accel_y >> (4 << delta_time)));
	    if(!tile_colision && delta_time != 0 && data->accel_y < 40  ) { //Do another iteration if there is no collision
		    data->accel_y += 4 >> delta_time;
            tile_colision = TranslateSprite(THIS, 0, (data->accel_y >> 4));
	    }
	    if(tile_colision && !TranslateSprite(THIS,0,(data->accel_y >> (-4 << delta_time)))) {
            data->accel_y = 0;
            if(data->state == 1 ){
                data->state = 0;
            }else if(data->state == 2){
                if(THIS->x < player_x){
                    SPRITE_UNSET_VMIRROR(THIS);
                }else{
                    SPRITE_SET_VMIRROR(THIS);
                }
                data->state = 3;
            } 
	    }
    }
}
#endif