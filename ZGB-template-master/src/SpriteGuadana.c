#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"
#include "Scroll.h"

const UINT8 guad_anim[] = {4,0,1,0,1};
extern INT16 player_x;
extern INT16 player_y;


struct GuadanaCustomData
{
    INT16 accel_x;
    INT16 accel_y;
    BOOLEAN start;
    
};

void GuadUp(struct GuadanaCustomData* data){
    data->accel_y = -85;
}

void GuadanaDirection(struct GuadanaCustomData* data){
    
        if(SPRITE_GET_VMIRROR(THIS)){
            data->accel_x = -1;
        }else{
            data->accel_x = 1;
        }
      
}

void Start_SpriteGuadana(){
    struct GuadanaCustomData* data = (struct GuadanaCustomData*)THIS->custom_data;
    GuadUp(data);
    data->start = TRUE;
    
}
void Update_SpriteGuadana(){
    struct GuadanaCustomData* data = (struct GuadanaCustomData*)THIS->custom_data;
    UINT8 i;
	struct Sprite* spr;
    SPRITE_SET_CGB_PALETTE(THIS, 3);
    SPRITE_SET_DMG_PALETTE(THIS, 0);

    SetSpriteAnim(THIS,guad_anim,15);
    if(data->start){
        GuadanaDirection(data);
        data->start=FALSE;
    }

    switch(THIS->anim_frame){
        case 0:
            if(data->accel_x == -1){
                THIS->flags = 32;
            }else{
                THIS->flags = 0;
            }
            
        break;

        case 1:
            if(data->accel_x == -1){
                THIS->flags = 32;
            }else{
                THIS->flags = 0;
            }
        break;

        case 2:
            if(data->accel_x == -1){
                THIS->flags = 64;
            }else{
                THIS->flags = 96;
            }
        break;

        case 3:
            if(data->accel_x == -1){
                THIS->flags = 64;
            }else{
                THIS->flags = 96;
            } 
        break;
    }
            
        
        
        
       
            THIS->x = THIS->x + (data->accel_x );
    if(data->accel_y < 80){
        data->accel_y +=4;
    }
    THIS->y = THIS->y + (data->accel_y >> 4);
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
void Destroy_SpriteGuadana(){

}