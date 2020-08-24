#include "Banks/SetBank2.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"
#include "Scroll.h"
#include "Sound.h"

const UINT8 tdevil_1[] = {2, 0,1};
const UINT8 tdevil_2[] = {1, 2};
const UINT8 tdevil_3[] = {1, 3};
const UINT8 tdevil_4[] = {6, 4,5,4,5,4,5};
extern INT16 player_x;
extern INT16 player_y;

struct tDevilCustomData
{
    UINT8 state;
    INT8 counter;
    BOOLEAN direction;
    UINT8 lives;
    INT16 accel_y;
    INT16 accel_x;
};

void tdevilMovement(){
     if(SPRITE_GET_VMIRROR(THIS)) {
    	        if(TranslateSprite(THIS, -1 << delta_time, 0)) {
			        SPRITE_UNSET_VMIRROR(THIS);
		        } else	if( !scroll_collisions[GetScrollTile(((THIS->x + THIS->coll_x) >> 3), (THIS->y >> 3) + 2u)]  && !scroll_collisions_down[GetScrollTile(((THIS->x + THIS->coll_x) >> 3), (THIS->y >> 3) + 2u)]) {
			        SPRITE_UNSET_VMIRROR(THIS);
		        }
	        }else {
		        if(TranslateSprite(THIS, +1 << delta_time, 0)) {
			        SPRITE_SET_VMIRROR(THIS);
		        }else if(  !scroll_collisions[GetScrollTile(((THIS->x + THIS->coll_x + THIS->coll_w) >> 3), (THIS->y >> 3) + 2u)] && !scroll_collisions_down[GetScrollTile(((THIS->x + THIS->coll_x + THIS->coll_w) >> 3), (THIS->y >> 3) + 2u)] ) {
			        SPRITE_SET_VMIRROR(THIS);
		        }
	        }
}

void tdevilJump(struct tDevilCustomData* data){
    data->accel_y = -70;
}

struct Sprite* tdevil_parent = 0;
UINT8 tile_collisiontd;

void Start_SpriteTinyDevil(){
    struct tDevilCustomData* data = (struct tDevilCustomData*)THIS->custom_data;
    SetSpriteAnim(THIS, tdevil_1,9);
    data->state = 3;
    data->accel_y = 0;
    THIS->coll_x = 4;
    THIS->coll_y = 3;
    THIS->coll_w = 9;
    THIS->coll_h = 13;
}
void Update_SpriteTinyDevil(){
  	struct tDevilCustomData* data = (struct tDevilCustomData*)THIS->custom_data;
    UINT8 i;
	struct Sprite* spr;
    switch (data->state){
        case 0: 
            SetSpriteAnim(THIS, tdevil_1,9);
            if(data->counter <= 2){
                data->counter++;
                if(data->counter == 2){
                    tdevilMovement();
                    data->counter = 0;
                }
            }
            if(DISTANCE(THIS->x, player_x) < 27){
                PlayFx(CHANNEL_1 , 10, 0x76, 0xd3, 0x54, 0x73,0x86);
                tdevilJump(data);
                if(THIS->x < player_x){
                    data->direction = TRUE;
                }else{
                    data->direction = FALSE;
                }
                data->state = 1;
            }
            break;
        
        case 1:
            SetSpriteAnim(THIS, tdevil_2, 0);
            if(DISTANCE(THIS->x, player_x) < 2){
                data->state = 2;
            }
            if(data->direction){
                SPRITE_UNSET_VMIRROR(THIS);
                TranslateSprite(THIS,1,0);
            }else{
                SPRITE_SET_VMIRROR(THIS);
                TranslateSprite(THIS,-1,0);
            }
            
            break;
        
        case 2:
            SetSpriteAnim(THIS, tdevil_3, 0);
            TranslateSprite(THIS,0,1);
            break;
        
        case 3:
            SetSpriteAnim(THIS, tdevil_4, 7);
            if(THIS->anim_frame == 5){
                data->state = 0;
            }
            break;
    }

    if(tdevil_parent == 0 ){
		if(data->accel_y < 60  ) {
			data->accel_y += 4;
           
		}
	    tile_collisiontd = TranslateSprite(THIS, 0, (data->accel_y >> (4 << delta_time)));
	    if(!tile_collisiontd && delta_time != 0 && data->accel_y < 40  ) { //Do another iteration if there is no collision
		    data->accel_y += 4 >> delta_time;
            
		    tile_collisiontd = TranslateSprite(THIS, 0, (data->accel_y >> 4));
	    }
	    if(tile_collisiontd && !TranslateSprite(THIS,0,(data->accel_y >> (-4 << delta_time)))) {
              
			
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
                    
                
			
			

		    //CheckCollisionTile();
	    }
    }


    SPRITEMANAGER_ITERATE(i, spr) {
			if(spr->type == SpriteChain || spr->type == SpriteSword) {
				if(CheckCollision(THIS, spr)) {
                    
					SpriteManagerRemove(THIS_IDX);
                    SpriteManagerAdd(SpriteExplosion, THIS->x, THIS->y);
                    PlayFx(CHANNEL_4, 20, 0x3b, 0xd1, 0x79, 0x80);
                    
                }
			}
		}

}
void Destroy_SpriteTinyDevil(){

}