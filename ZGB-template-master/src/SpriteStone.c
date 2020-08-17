#include "Banks/SetBank4.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"


extern INT16 player_x;
extern INT16 player_y;
extern BOOLEAN gameOver;

const UINT8 stone_0[] = {6, 0,0,0,0,0,0};
const UINT8 stone_1[] = {3, 0,1,2};
struct Sprite* stone_parent = 0;
UINT8 tile_collisionstone;




struct StoneCustomData
{
    BOOLEAN canJump;
    INT8 state;
    INT8 counter;
    INT16 accel_y;
};

void Rebote(struct StoneCustomData* data){
    
        if(data->counter== 0 || data->counter == 1){
            data->accel_y = -60;
        }else if(data->counter == 2 || data->counter == 3){
            data->accel_y = -50;
        }else if(data->counter == 4){
            data->accel_y = -40;
        }
        data->counter++;
   
    
}

void Start_SpriteStone(){
    struct StoneCustomData* data = (struct StoneCustomData*)THIS->custom_data;
    data->state = 0;
    data->counter = 0;
    data->accel_y = 0;
    THIS->coll_x = 4;
    THIS->coll_y = 4;
    THIS->coll_w = 10;
    THIS->coll_h = 10;
}
void Update_SpriteStone(){
    struct StoneCustomData* data = (struct StoneCustomData*)THIS->custom_data;

    if(gameOver == TRUE){
        SPRITE_SET_CGB_PALETTE(THIS, 0);
        SPRITE_SET_DMG_PALETTE(THIS,0);
    }

    if(data->counter == 5){
        SpriteManagerRemove(THIS_IDX);
        SpriteManagerAdd(SpriteExplosion, THIS->x, THIS->y);
    }
    switch(data->state){
        case 0:
            SetSpriteAnim(THIS, stone_0, 8);
            if(THIS->anim_frame == 4){
            data->state = 1;
            }
            break;
        
        case 1:
            SetSpriteAnim(THIS, stone_1, 10);
            if(SPRITE_GET_VMIRROR(THIS)){
                TranslateSprite(THIS, -1, 0);
            }else{
                TranslateSprite(THIS, 1, 0);
            }


            if(stone_parent == 0 ){
		        if(data->accel_y < 60  ) {
			        data->accel_y += 4;
           
		        }
	        tile_collisionstone = TranslateSprite(THIS, 0, (data->accel_y >> (4 << delta_time)));
	        if(!tile_collisionstone && delta_time != 0 && data->accel_y < 40  ) { //Do another iteration if there is no collision
		        data->accel_y += 4 >> delta_time;
            
		        tile_collisionstone = TranslateSprite(THIS, 0, (data->accel_y >> 4));
	        }
	            if(tile_collisionstone && !TranslateSprite(THIS,0,(data->accel_y >> (-4 << delta_time)))) {
              
			
	            data->accel_y = 0;
                
                Rebote(data);
		        //CheckCollisionTile();
	            }
                }
            break;
    }



}
void Destroy_SpriteStone(){

}