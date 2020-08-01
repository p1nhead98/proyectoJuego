#include "Banks/SetBank3.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Math.h"
#include "Sound.h"
#include "energy.h"
const UINT8 shooter_anim[] = {15,0,0,0,0,0,0,0,1,2,3,4,5,4,5,0};

struct ShooterCustomData
{
    BOOLEAN canShoot;
    INT8 counter;
};
extern UINT8 energy;
extern INT16 player_x;

void SShoot(struct ShooterCustomData* data){
    if(data->canShoot == TRUE){
        struct Sprite* sprite_ebullet1 = SpriteManagerAdd(SpriteEnemyBullet,THIS->x,THIS->y);
        sprite_ebullet1->flags = THIS->flags;
        sprite_ebullet1->unique_id = 4;
        data->canShoot = FALSE;
    }

}
void Start_SpriteShooter(){
    struct ShooterCustomData* data = (struct ShooterCustomData*)THIS->custom_data;
    SetSpriteAnim(THIS, shooter_anim, 15);
    THIS->coll_x = 4;
    THIS->coll_y = 4;
    THIS->coll_w = 7;
    THIS->coll_h = 14;
    data->canShoot = TRUE;
}
void Update_SpriteShooter(){
  struct ShooterCustomData* data = (struct ShooterCustomData*)THIS->custom_data;
   UINT8 i;
   struct Sprite* spr;

    if(THIS->x < player_x){    
        SPRITE_UNSET_VMIRROR(THIS);
    }else if (THIS->x > player_x){
        SPRITE_SET_VMIRROR(THIS);
        THIS->x  -2;
    }
	
    if(THIS->anim_frame==6){
        SShoot(data);
    }
    if(THIS->anim_frame == 0){
        data->canShoot = TRUE;
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
void Destroy_SpriteShooter(){

}



