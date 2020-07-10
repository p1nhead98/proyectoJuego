#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Math.h"
#include "Sound.h"
#include "energy.h"
extern INT16 player_x;
extern INT16 player_y;
const UINT8 skel_1[] = {1, 0};
const UINT8 skel_2[] = {6, 0,1,2,3,4,4};
const UINT8 skel_3[] = {4, 4,5,4,6};
const UINT8 skel_4[] = {4, 7,8,9,9};
extern UINT8 energy;
struct SkeletonCustomData
{
    UINT8 skel_state;
    INT8 counter;
};
void SkelDeathSound(){
    PlayFx(CHANNEL_4, 20, 0x3b, 0xd1, 0x79, 0x80);
}
void SkeletonMove(){
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
void Start_SpriteSkeleton(){
	struct SkeletonCustomData* data = (struct SkeletonCustomData*)THIS->custom_data;
    data->skel_state = 0;
    data->counter = 0;
    SetSpriteAnim(THIS,skel_1,1);
    if(THIS->x < player_x){
        SPRITE_UNSET_VMIRROR(THIS);
    }else{
        SPRITE_SET_VMIRROR(THIS);
    }

    THIS->coll_x = 5;
    THIS->coll_y = 3;
    THIS->coll_w = 5;
    THIS->coll_h = 13;
}

void Update_SpriteSkeleton(){
    struct SkeletonCustomData* data = (struct SkeletonCustomData*)THIS->custom_data;
    UINT8 i;
	struct Sprite* spr;
    switch(data->skel_state){
        case 0:
            SetSpriteAnim(THIS,skel_1,1);
            if(DISTANCE(THIS->x, player_x) < 100){
                data->skel_state = 1;
            }
            break;
        case 1:
            SetSpriteAnim(THIS,skel_2,9);
            if(THIS->anim_frame == 4){
                data->skel_state = 2;
            }

            break;

        case 2:
            SetSpriteAnim(THIS,skel_3,9);
            if(data->counter <= 3){
                data->counter++;
                if(data->counter == 3){
                    SkeletonMove();
                    data->counter = 0;
                }
            }
            break;
      

    }

    SPRITEMANAGER_ITERATE(i, spr) {
			if(spr->type == SpriteChain ) {
				if(CheckCollision(THIS, spr)) {
                    if(spr->anim_frame >=1){
                        SkelDeathSound();
					    SpriteManagerRemove(THIS_IDX);
                        if(energy<=19){
                            energy++;
                        }
                        refreshEnergy(energy);
                        SpriteManagerAdd(SpriteExplosion, THIS->x, THIS->y);
                    }
                }
			}else if(spr->type == SpriteBumerang ) {
				if(CheckCollision(THIS, spr)) {
                    if(spr->anim_frame >=1){
                        SkelDeathSound();
					    SpriteManagerRemove(THIS_IDX);
                        SpriteManagerAdd(SpriteExplosion, THIS->x, THIS->y);
                    }
                }
			}
		}
}

void Destroy_SpriteSkeleton(){

}