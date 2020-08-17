#include "Banks/SetBank3.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Math.h"
#include "Sound.h"
#include "hud.h"

extern INT16 player_x;
extern INT16 player_y;
const UINT8 fskel_1[] = {4, 0,1,2,1};
const UINT8 fskel_2[] = {1, 1};
extern UINT16 energy;
struct FSkeletonCustomData
{
    UINT8 skel_state;
    INT8 counter;
    INT8 counter2;
    UINT8 lives;
    BOOLEAN canHurt;
    BOOLEAN canAttack;
};
void FSkelDeathSound(){
    PlayFx(CHANNEL_4, 20, 0x3b, 0xd1, 0x79, 0x80);
}
void FSkeletonMove(){
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
void FSkelAttack(struct FSkeletonCustomData* data){
    
    SpriteManagerAdd(SpriteFlame, THIS->x, THIS->y);
    data->canAttack = FALSE;
    
}
void Start_SpriteFireSkel(){
	struct FSkeletonCustomData* data = (struct FSkeletonCustomData*)THIS->custom_data;
    data->skel_state = 0;
    data->counter = 0;
    data->counter2 = 0;
    data->lives = 7;
    data->canHurt = FALSE;
    data->canAttack = TRUE;
    THIS->coll_x = 5;
    THIS->coll_y = 3;
    THIS->coll_w = 5;
    THIS->coll_h = 13;
    SetSpriteAnim(THIS,fskel_1,9);
}

void Update_SpriteFireSkel(){
    struct FSkeletonCustomData* data = (struct FSkeletonCustomData*)THIS->custom_data;
    UINT8 i;
	struct Sprite* spr;
    switch(data->skel_state){
        

        case 0:
            
            if(data->counter <= 3){
                data->counter++;
                if(data->counter == 3){
                    FSkeletonMove();
                    data->counter = 0;
                    data->counter2 ++;
                    
                }
            }
            break;
            case 1:
                
                if(data->counter <= 15){
                    data->counter++;
                    if(data->counter == 15){
                        data->skel_state = 0;
                        data->counter = 0;
                        data->canHurt = FALSE;
                        SetSpriteAnim(THIS,fskel_1,9);
                    }
                }
                break;
      

    }

 
    if(data->counter2 == 31){
        data->counter2 = 0;
        data->canAttack = TRUE;
        
    }
    if(data->counter2 == 30 && data->canAttack == TRUE){
        
            FSkelAttack(data);
            data->canAttack = FALSE;
        
    }

    SPRITEMANAGER_ITERATE(i, spr) {
			if(spr->type == SpriteChain) {
				if(CheckCollision(THIS, spr)) {
                    if(spr->anim_frame >=1){
                        if(data->lives >0 && data->canHurt == FALSE){
                            data->canHurt = TRUE;
                            data->lives--;
                            
                            data->skel_state = 1;
                            SetSpriteAnim(THIS,fskel_2,1);
                        }else if(data->lives < 1){
                            FSkelDeathSound();
					        SpriteManagerRemove(THIS_IDX);
                            SpriteManagerAdd(SpriteExplosion, THIS->x, THIS->y);
                            if(energy<=19){
                                energy = energy+3;
                            }
                            refreshEnergy(energy);
                        }
                    }
                }
			}
            if(spr->type == SpriteBumerang) {
				if(CheckCollision(THIS, spr)) {
                    if(spr->anim_frame >=1){
                        if(data->lives >0 && data->canHurt == FALSE){
                            data->canHurt = TRUE;
                            data->lives--;
                            data->skel_state = 1;
                            SetSpriteAnim(THIS,fskel_2,1);
                        }else if(data->lives < 1){
                            FSkelDeathSound();
					        SpriteManagerRemove(THIS_IDX);
                            SpriteManagerAdd(SpriteExplosion, THIS->x, THIS->y);
                        }
                    }
                }
			}
		}
}

void Destroy_SpriteFireSkel(){

}