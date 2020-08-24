#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"
#include "Scroll.h"

const UINT8 bole_anim2[] = {4,0,0,0,0};
extern INT16 player_x;
extern INT16 player_y;


struct BoleadoraCustomData
{
    INT16 b_accel_x;
    BOOLEAN start;
    
};

void boldirection(struct BoleadoraCustomData* data){
    
        if(SPRITE_GET_VMIRROR(THIS)){
            data->b_accel_x = -3;
        }else{
            data->b_accel_x = 3;
        }
      
}

void Start_SpriteBoleadora(){
    struct BoleadoraCustomData* data = (struct BoleadoraCustomData*)THIS->custom_data;

    data->start = TRUE;
    
}
void Update_SpriteBoleadora(){
    struct BoleadoraCustomData* data = (struct BoleadoraCustomData*)THIS->custom_data;
    UINT8 i;
	struct Sprite* spr;
    SPRITE_SET_CGB_PALETTE(THIS, 3);
    SPRITE_SET_DMG_PALETTE(THIS, 0);

       
            SetSpriteAnim(THIS,bole_anim2,15);
            if(data->start){
                boldirection(data);
                data->start=FALSE;
            }
        
        
        
       
            THIS->x = THIS->x + (data->b_accel_x );
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
void Destroy_SpriteBoleadora(){

}