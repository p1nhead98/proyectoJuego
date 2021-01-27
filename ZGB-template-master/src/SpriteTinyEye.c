#include "Banks/SetBank8.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Sound.h"
#include "Math.h"
#include "hud.h"

const UINT8 teye_1[] = {5, 1,1,0,0,0};
const UINT8 teye_2[] = {5, 0,0,0,0,0};
const UINT8 teye_3[] = {3,0,0,1};
const UINT8 teye_4[] = {1,2};
extern BOOLEAN gameOver;

struct teyeCustomData
{
    UINT8 state;
    INT8 counter;
    BOOLEAN direction;
    UINT8 lives;
    INT16 accel_y;
    INT16 accel_x;
};

struct Sprite* teye_parent = 0;
extern INT16 player_x;
extern INT16 player_y;
UINT8 tile_collisionts;

void Start_SpriteTinyEye(){
    struct teyeCustomData* data = (struct teyeCustomData*)THIS->custom_data;
    THIS->coll_x = 2;
    THIS->coll_y = 2;
    THIS->coll_w = 12;
    THIS->coll_h = 13;
    data->state = 1;
    data->accel_y = 0;
}
void Update_SpriteTinyEye(){
    struct teyeCustomData* data = (struct teyeCustomData*)THIS->custom_data;
    UINT8 i;
    struct Sprite* spr;
    if(gameOver == TRUE){
        SPRITE_SET_CGB_PALETTE(THIS, 0);
        SPRITE_SET_DMG_PALETTE(THIS,7);
    }


    switch(data->state){
        
        case 1:
            SetSpriteAnim(THIS, teye_1,15);
            if(THIS->anim_frame == 4){
                data->state = 2;
            }
            break;

        case 2:
            SetSpriteAnim(THIS, teye_2,15);
            if(THIS->x < player_x){    
                SPRITE_UNSET_VMIRROR(THIS);
            }else if (THIS->x > player_x){
                SPRITE_SET_VMIRROR(THIS);
            }
            if(THIS->anim_frame == 4){
                data->state = 3;
            }
            break;
        
        case 3:
            SetSpriteAnim(THIS, teye_3, 15);
           
            if(THIS->anim_frame == 2){
                if(THIS->x < player_x){
                    data->direction = TRUE;
                    SPRITE_UNSET_VMIRROR(THIS);
                }else if (THIS->x > player_x){
                    data->direction = FALSE;
                    SPRITE_SET_VMIRROR(THIS);
                }
                data->state = 4;
                data->accel_y  = -50;
            }else{
                if(THIS->x < player_x){
                    SPRITE_UNSET_VMIRROR(THIS);
                }else if (THIS->x > player_x){
                    SPRITE_SET_VMIRROR(THIS);
                }
            }
            break;
        case 4:
            SetSpriteAnim(THIS, teye_4, 15);
            if(data->direction){
                TranslateSprite(THIS, 1, 0);
            }else {
                TranslateSprite(THIS, -1, 0);
            }
            teye_parent = 0;
            break;
    }


    if(teye_parent == 0 ){
		if(data->accel_y < 60  ) {
			data->accel_y += 4;
           
		}
	tile_collisionts = TranslateSprite(THIS, 0, (data->accel_y >> (4 << delta_time)));
	if(!tile_collisionts && delta_time != 0 && data->accel_y < 40  ) { //Do another iteration if there is no collision
		data->accel_y += 4 >> delta_time;
            
		tile_collisionts = TranslateSprite(THIS, 0, (data->accel_y >> 4));
	}
	if(tile_collisionts && !TranslateSprite(THIS,0,(data->accel_y >> (-4 << delta_time)))) {
              
			
	    data->accel_y = 0;
               
        if(data->state == 4){
            data->state = 1;
        } 
                    
                
			
			

		//CheckCollisionTile();
	}
    }

     SPRITEMANAGER_ITERATE(i, spr) {
			// if(spr->type == SpriteChain ) {
			// 	if(CheckCollision(THIS, spr)) {
            //         if(spr->anim_frame >=1){
            //             //SkelDeathSound();
			// 		    SpriteManagerRemove(THIS_IDX);
            //             // if(energy<=19){
            //             //     energy++;
            //             // }
            //             // refreshEnergy();
            //             SpriteManagerAdd(SpriteExplosion, THIS->x, THIS->y);
            //         }
            //     }
			// }else if(spr->type == SpriteBumerang || spr->type == SpriteGuadana) {
				// if(CheckCollision(THIS, spr)) {
                //     if(spr->anim_frame >=1){
                //         //SkelDeathSound();
				// 	    SpriteManagerRemove(THIS_IDX);
                //         SpriteManagerAdd(SpriteExplosion, THIS->x, THIS->y);
                //     }
                // }
			}
		}



void Destroy_SpriteTinyEye(){

}