#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"
#include "Scroll.h"


extern INT16 player_x;
extern INT16 player_y;


struct BoleadoraCustomData
{
    INT16 accel_y;
    INT16 accel_x;
    BOOLEAN start;
    BOOLEAN dir;
};

void boldirection(struct BoleadoraCustomData* data){
    
        if(SPRITE_GET_VMIRROR(THIS)){
            data->dir = TRUE;
        }else{
            data->dir = FALSE;
        }
      
}

void Start_SpriteBoleadora(){
    struct BoleadoraCustomData* data = (struct BoleadoraCustomData*)THIS->custom_data;
    data->accel_y = 0;
    data->accel_x = 0;
    data->start = TRUE;
    
}
void Update_SpriteBoleadora(){
    struct BoleadoraCustomData* data = (struct BoleadoraCustomData*)THIS->custom_data;
    UINT8 i;
	struct Sprite* spr;
    SPRITE_SET_CGB_PALETTE(THIS, 3);
    SPRITE_SET_DMG_PALETTE(THIS, 0);

       
            
            if(data->start){
                boldirection(data);
                data->start=FALSE;
            }
       
        
        
            if(data->accel_x > -6){
                data->accel_x -=1;
            }
        
        
        if(data->accel_x == -6){
            if(data->accel_y < 5 ){
                data->accel_y++;
            }
        }
        TranslateSprite(THIS, (data->accel_x >> 4), (data->accel_y >> 4));
            
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