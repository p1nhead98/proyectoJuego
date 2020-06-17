#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Math.h"
#include "Sound.h"

extern INT16 player_x;
extern INT16 player_y;
const UINT8 wizzard_1[] = {24, 0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,4,4,5,5};


struct WizzardCustomData
{
    BOOLEAN canShoot;
    INT8 counter;
};
void WizDeathSound(){
    PlayFx(CHANNEL_4, 20, 0x3b, 0xd1, 0x79, 0x80);
}

void WizzardMove(){
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

void WShoot(struct WizzardCustomData* data){
    
    struct Sprite* sprite_ebullet1 = SpriteManagerAdd(SpriteEnemyBullet,THIS->x,THIS->y);
    struct Sprite* sprite_ebullet2 = SpriteManagerAdd(SpriteEnemyBullet,THIS->x,THIS->y);

    sprite_ebullet1->flags = THIS->flags;
    sprite_ebullet2->flags = THIS->flags;
    sprite_ebullet1->unique_id = 4;
    sprite_ebullet2->unique_id = 5;
    data->canShoot = TRUE;
  
}

void Start_SpriteWizzard(){
	struct WizzardCustomData* data = (struct WizzardCustomData*)THIS->custom_data;
    data->canShoot = FALSE;
    data->counter = 0;
    SetSpriteAnim(THIS,wizzard_1,15);
}

void Update_SpriteWizzard(){
    struct WizzardCustomData* data = (struct WizzardCustomData*)THIS->custom_data;
    UINT8 i;
	struct Sprite* spr;
    
        if(THIS->anim_frame <= 20){
            if(data->canShoot == TRUE){
                data->canShoot = FALSE;
            }
            if(data->counter <= 3){
                data->counter++;
                if(data->counter == 3){
                    WizzardMove();
                    data->counter = 0;
                }
            }
        }else if (THIS->anim_frame == 23){
            if(THIS->x < player_x){
                SPRITE_UNSET_VMIRROR(THIS);
            }else{
                SPRITE_SET_VMIRROR(THIS);
            }
            if(data->canShoot == FALSE){
                WShoot(data);
            }
        }


    SPRITEMANAGER_ITERATE(i, spr) {
			if(spr->type == SpriteChain) {
				if(CheckCollision(THIS, spr)) {
                    SpriteManagerRemove(THIS_IDX);
					SpriteManagerAdd(SpriteExplosion, THIS->x, THIS->y);
				}
			}
		}
}

void Destroy_SpriteWizzard(){

}