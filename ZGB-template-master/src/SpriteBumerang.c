#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"
const UINT8 bum_anim[] = {2,0,1};

extern INT16 player_x;
extern INT16 player_y;


struct bumerangCustomData
{
    INT16 b_accel_x;
    INT16 b_accel_y;
    BOOLEAN canDest;
    BOOLEAN start;
};

void bdirection(struct bumerangCustomData* data){
    
        if(SPRITE_GET_VMIRROR(THIS)){
            data->b_accel_x = -64;
        }else{
            data->b_accel_x = +80;
        }
      
}

void Start_SpriteBumerang(){
    struct bumerangCustomData* data = (struct bumerangCustomData*)THIS->custom_data;
    data->canDest=FALSE;
    data->b_accel_y = 0;
    SetSpriteAnim(THIS, bum_anim,30);
    data->start=TRUE;
    THIS->coll_x = 3;
    THIS->coll_y = 3;
    THIS->coll_w = 10;
    THIS->coll_h = 10;
    
}
void Update_SpriteBumerang(){
    struct bumerangCustomData* data = (struct bumerangCustomData*)THIS->custom_data;
    UINT8 i;
	struct Sprite* spr;
    SPRITE_SET_PALETTE(THIS, 0);
    if(data->start){
        bdirection(data);
        data->start=FALSE;
    }
        if(data->b_accel_x == 0){
            data->canDest=TRUE;
        }
        if(THIS->x < player_x){
            if(data->b_accel_x < 50){
                data->b_accel_x +=2;
            }
        }else {
             if(data->b_accel_x > -50){
                data->b_accel_x -=2;
             }
        }
        if(data->canDest == TRUE){
            if(THIS->y < player_y){
                
                    data->b_accel_y+=1;
                
            }else{
               
                    data->b_accel_y-=1;
                
            }
        }
        THIS->x = THIS->x + (data->b_accel_x >> 4);
        THIS->y = THIS->y + (data->b_accel_y >> 4);


     SPRITEMANAGER_ITERATE(i, spr) {
			if(spr->type == SpritePlayer) {
				if(CheckCollision(THIS, spr)) {
                    if(data->canDest == TRUE){
                        SpriteManagerRemove(THIS_IDX);
                    }
                    }
				}
			}

}
void Destroy_SpriteBumerang(){

}