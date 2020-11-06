#include "hud.h"
#include "Banks/SetBank6.h"
#include "print.h"
#include "SpriteManager.h"
#include "ZGBMain.h"

extern const UINT8 max_life;
extern INT8 current_life;



void RefreshWeapon(INT8 weapon){
    const UINT8 W1_1 = 116;
    const UINT8 W1_2 = 117;
    const UINT8 W1_3 = 118;
    const UINT8 W1_4 = 119;

    const UINT8 W2_1 = 112;
    const UINT8 W2_2 = 113;
    const UINT8 W2_3 = 114;
    const UINT8 W2_4 = 115;

    const UINT8 W3_1 = 108;
    const UINT8 W3_2 = 109;
    const UINT8 W3_3 = 110;
    const UINT8 W3_4 = 111;

    switch(weapon){
        case 0:
            set_win_tiles(9, 0, 1, 1, &W1_1);
            set_win_tiles(9, 1, 1, 1, &W1_2);
            set_win_tiles(10, 0, 1, 1, &W1_3);
            set_win_tiles(10, 1, 1, 1, &W1_4);
        break;
            
        case 1:
            set_win_tiles(9, 0, 1, 1, &W2_1);
            set_win_tiles(9, 1, 1, 1, &W2_2);
            set_win_tiles(10, 0, 1, 1, &W2_3);
            set_win_tiles(10, 1, 1, 1, &W2_4);
        break;
        case 2:
            set_win_tiles(9, 0, 1, 1, &W3_1);
            set_win_tiles(9, 1, 1, 1, &W3_2);
            set_win_tiles(10, 0, 1, 1, &W3_3);
            set_win_tiles(10, 1, 1, 1, &W3_4);
        break;
    }
   /* if(weapon == FALSE){
        set_win_tiles(9, 0, 1, 1, &W1_1);
        set_win_tiles(9, 1, 1, 1, &W1_2);
        set_win_tiles(10, 0, 1, 1, &W1_3);
        set_win_tiles(10, 1, 1, 1, &W1_4);
    }else{
        set_win_tiles(9, 0, 1, 1, &W2_1);
        set_win_tiles(9, 1, 1, 1, &W2_2);
        set_win_tiles(10, 0, 1, 1, &W2_3);
        set_win_tiles(10, 1, 1, 1, &W2_4);
    }
    */
}



void RefreshLife() {
	const UINT8 HEART_TILE = 122;
    const UINT8 HEART_TILE2 = 98;
    const UINT8 EMPTY_HEART_TILE = 121;
    UINT8 i;
    UINT8 last_tile;
    
    if(current_life !=0 ){
        DPRINT(2, 0, "LIFE");
        last_tile = (current_life+1) / 2 ;
        for(i=0; i != (max_life / 2); ++i) {
		    set_win_tiles(1 + i, 1, 1, 1, &EMPTY_HEART_TILE);
	    }
        if(current_life% 2 == 0){
	        for(i = 0; i != (current_life / 2) ; ++i) {
                set_win_tiles(1 + i, 1, 1, 1, &HEART_TILE);
            }
            for(; i != (max_life / 2); ++i) {
		        set_win_tiles(1 + i, 1, 1, 1, &EMPTY_HEART_TILE);
	        }
        }else{
            for(i = 0; i != ((current_life - 1) / 2) ; ++i) {
                set_win_tiles(1 + i, 1, 1, 1, &HEART_TILE);
	        }
            if(i == ((current_life-1)/2)){
                set_win_tiles(1 + i, 1, 1, 1, &HEART_TILE2);
            }
        
        }
    }
}