#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Math.h"
#include "Sound.h"

extern INT16 player_x;
extern INT16 player_y;
const UINT8 ghost_1[] = {2, 0,1};
const UINT8 ghost_2[] = {13,1,1,1,1,1,1,1,1,2,3,4,5,6};
const UINT8 ghost_3[] = {2, 6,7};
struct GhostCustomData
{
    UINT8 ghost_state;
    INT8 counter;
    BOOLEAN direction;
    UINT8 lives;
    INT16 accel_y;
    INT16 accel_x;
};
void GhostDeathSound(){
    PlayFx(CHANNEL_4, 20, 0x3b, 0xd1, 0x79, 0x80);
}
void GhostMove(){
     if(SPRITE_GET_VMIRROR(THIS)) {
    	        if(TranslateSprite(THIS, -1, 0)) {
			        SPRITE_UNSET_VMIRROR(THIS);
		        } else	if(!scroll_collisions[GetScrollTile(((THIS->x + THIS->coll_x) >> 3), (THIS->y >> 3) + 2u)]) {
			        SPRITE_UNSET_VMIRROR(THIS);
		        }
	        }else {
		        if(TranslateSprite(THIS, +1, 0)) {
			        SPRITE_SET_VMIRROR(THIS);
		        }else if(!scroll_collisions[GetScrollTile(((THIS->x + THIS->coll_x + THIS->coll_w) >> 3), (THIS->y >> 3) + 2u)]) {
			        SPRITE_SET_VMIRROR(THIS);
		        }
	        }

}

void maskMove( struct GhostCustomData* data){
                  
                       
                            if(THIS->x < player_x){
                                data->accel_x+=1;
                                SPRITE_UNSET_VMIRROR(THIS);
                            }else if(THIS->x > player_x){
                                data->accel_x-=1;
                                SPRITE_SET_VMIRROR(THIS);
                            }
                            if(THIS->y < player_y){
                                data->accel_y += 1;
                
                            }else if(THIS->y > player_y){
                                data->accel_y -= 1;
                            }
                           
                      
                    
}
void colisionesGhost(){
    UINT8 colision = GetScrollTile((THIS->x + THIS->coll_x) >> 3, (THIS ->y + 15u) >> 3);
    switch(colision){
        case 94u:
            if(THIS->x > 150){
                THIS->x = 8;
            }else{
                THIS->x = 184;
            }
            break;
    }
}
void Start_SpriteGhost(){
	struct GhostCustomData* data = (struct GhostCustomData*)THIS->custom_data;
    data->ghost_state = 0;
    data->counter = 0;
    data->direction = FALSE;
   
    SetSpriteAnim(THIS,ghost_1,9);
}

void Update_SpriteGhost(){
    struct GhostCustomData* data = (struct GhostCustomData*)THIS->custom_data;
    UINT8 i;
	struct Sprite* spr;
    colisionesGhost();
    switch(data->ghost_state){
   
    

        case 0:
           
            if(data->counter <= 2){
                data->counter++;
                if(data->counter == 2){
                    GhostMove();
                    data->counter = 0;
                }
            }
            break;
        
        case 1:
            SetSpriteAnim(THIS, ghost_2, 15);

            if(!data->direction && THIS->anim_frame <= 8 ){
                THIS->x--;
                
                SPRITE_UNSET_VMIRROR(THIS);
            }else if(data->direction && THIS->anim_frame <= 8){
                THIS->x++;
                
                SPRITE_SET_VMIRROR(THIS);
            }
            if(THIS->anim_frame > 8){
                THIS->y--;
            }
            if(THIS->anim_frame == 12){
                data->counter = 0;
                data->ghost_state = 2;
            }
            break;
        case 2:
            SetSpriteAnim(THIS, ghost_3,15);
              

             
                    
                    maskMove(data);
                    THIS->y = THIS->y + (data->accel_y >> 2);
                    THIS->x = THIS->x + (data->accel_x >> 2);
                    
                  
                    
                
            
            break;
        
        

    }

    SPRITEMANAGER_ITERATE(i, spr) {
			if(spr->type == SpriteChain) {
				if(CheckCollision(THIS, spr)) {
                    if(data->ghost_state == 0){
					data->ghost_state = 1;
                    if(spr->x > THIS->x){
                        data->direction = FALSE;
                    }else{
                        data->direction =  TRUE;
                    }
                    }else if(data->ghost_state == 2){

                            SpriteManagerRemove(THIS_IDX);
                            SpriteManagerAdd(SpriteExplosion, THIS->x, THIS->y);
                            
                        }
                    }
				}
			}
		
}

void Destroy_SpriteGhost(){

}