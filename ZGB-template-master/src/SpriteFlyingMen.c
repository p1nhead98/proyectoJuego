#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"
#include "hud.h"
extern INT16 player_x;
const UINT8 f_men[] = {3, 0,1,2};
extern UINT16 energy;
struct fmenCustomData
{

    INT8 counter;
    
};

void Start_SpriteFlyingMen(){
    struct fmenCustomData* data = (struct fmenCustomData*)THIS->custom_data;
    SetSpriteAnim(THIS, f_men, 17);
    data->counter = 0;
     
}

void Update_SpriteFlyingMen(){
    struct fmenCustomData* data = (struct fmenCustomData*)THIS->custom_data;
       UINT8 i;
   struct Sprite* spr;

    if(THIS->x > player_x){
        SPRITE_SET_VMIRROR(THIS);
    }else{
        SPRITE_UNSET_VMIRROR(THIS);
    }
    if(data->counter <= 120){
        data->counter++;
        if(data->counter <=60){
            THIS->y--;
        }else{
            THIS->y++;
        }
        if(data->counter == 120){
            data->counter = 0;
        }
    }

       SPRITEMANAGER_ITERATE(i, spr) {
			if(spr->type == SpriteChain ) {
				if(CheckCollision(THIS, spr)) {
                    if(spr->anim_frame >=1){
                        //SkelDeathSound();
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
                        //SkelDeathSound();
					    SpriteManagerRemove(THIS_IDX);
                        SpriteManagerAdd(SpriteExplosion, THIS->x, THIS->y);
                    }
                }
			}
		}
}

void Destroy_SpriteFlyingMen(){

}