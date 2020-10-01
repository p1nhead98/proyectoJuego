#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"
#include "Scroll.h"
#include "Trig.h"


//const UINT8 bole_anim2[] = {4,0,0,0,0};
extern INT16 player_x;
extern INT16 player_y;


struct ShieldCustomData
{
    INT16 accel_x;
    INT16 accel_y;
    BOOLEAN ver;
    BOOLEAN hor;
    UINT8 radius;
};


void Start_SpriteShield(){
    struct ShieldCustomData* data = (struct ShieldCustomData*)THIS->custom_data;

    data->accel_x = 40;
    data->ver = TRUE;
    data->hor = TRUE;
}
void Update_SpriteShield(){
    struct ShieldCustomData* data = (struct ShieldCustomData*)THIS->custom_data;
    UINT8 i;
	struct Sprite* spr;
    SPRITE_SET_CGB_PALETTE(THIS, 3);
    SPRITE_SET_DMG_PALETTE(THIS, 0);
   
        if(THIS->x < player_x){
            if(data->accel_x < 50){
                data->accel_x +=3;
            }
        }else {
             if(data->accel_x > -50){
                data->accel_x -=3;
             }
        }
        
        if(THIS->y < (player_y - 4)){
            THIS->y= THIS->y + 3;
        }else if(THIS->y > (player_y + 20)){
            THIS->y = THIS->y -3;
        }
        
        
    THIS->x = THIS->x + (data->accel_x >> 4);    
  

                       /*if(SPRITE_GET_VMIRROR(THIS)){
                DrawFrame(FRAME_8x16, THIS->first_tile , THIS->x - scroll_x - 8 , THIS->y - scroll_y , THIS->flags);
            }else{
                DrawFrame(FRAME_8x16, THIS->first_tile , THIS->x - scroll_x + 8 , THIS->y - scroll_y , THIS->flags);
            }*/
    


     SPRITEMANAGER_ITERATE(i, spr) {
		/*	if(spr->type == SpritePlayer) {
				if(CheckCollision(THIS, spr)) {
                    if(data->canDest == TRUE){
                        SpriteManagerRemove(THIS_IDX);
                    }
                    }
				}

                */
			}

}
void Destroy_SpriteShield(){

}