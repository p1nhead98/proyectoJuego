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
    UINT8 counter;
};

void grenadeJump(struct BoleadoraCustomData* data){
    data->accel_y = -50;
}

void boldirection(struct BoleadoraCustomData* data){
    
        if(SPRITE_GET_VMIRROR(THIS)){
            data->accel_x = -2;
        }else{
            data->accel_x = 2;
        }
      
}
void explosions(struct BoleadoraCustomData* data){
  
                SpriteManagerAdd(SpriteExplosion,THIS->x ,THIS->y);
                SpriteManagerAdd(SpriteExplosion,THIS->x -12,THIS->y);
                SpriteManagerAdd(SpriteExplosion,THIS->x + 17,THIS->y);
                SpriteManagerAdd(SpriteExplosion,THIS->x ,THIS->y -9);
                SpriteManagerAdd(SpriteExplosion,THIS->x ,THIS->y+17);
                ScreenShake();
            SpriteManagerRemove(THIS_IDX);
           
}


void Start_SpriteBoleadora(){
    struct BoleadoraCustomData* data = (struct BoleadoraCustomData*)THIS->custom_data;
    data->accel_y = 0;
    data->counter = 0;
    data->start = TRUE;
    grenadeJump(data);
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
       
        
        

        
        
        if(data->accel_y < 60){
            data->accel_y +=4;
        }
        if(TranslateSprite(THIS, (data->accel_x ), data->accel_y >> 4 )){
            explosions(data);
            
            
        }
            
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