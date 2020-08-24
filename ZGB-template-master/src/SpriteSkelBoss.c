#include "Banks/SetBank6.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"
#include "Scroll.h"


extern INT16 player_x;
extern INT16 player_y;

const UINT8 skullHead1[] = {1,0};
const UINT8 skullHead2[] = {1,1};


BOOLEAN armAttack;
BOOLEAN sparkAttack;
INT16 boss1Counter;

struct SkelBossCustomData
{
    BOOLEAN canHurt;
    INT8 state;
    UINT8 live;
    INT8 counter;
    
};



void Start_SpriteSkelBoss(){
    struct SkelBossCustomData* data = (struct SkelBossCustomData*)THIS->custom_data;
    struct Sprite* arm1 = SpriteManagerAdd(SpriteBoss1Arm,THIS->x-34,THIS->y+40);
    struct Sprite* arm2 = SpriteManagerAdd(SpriteBoss1Arm,THIS->x+50,THIS->y+40);
    arm2->flags = 32;
    armAttack = TRUE;
    sparkAttack = FALSE;
    boss1Counter = 0;
    data->canHurt = FALSE;
    data->counter = 0;
    data->live = 17;
    
}
void Update_SpriteSkelBoss(){
    struct SkelBossCustomData* data = (struct SkelBossCustomData*)THIS->custom_data;
    UINT8 i;
	struct Sprite* spr;
    switch(data->state){
        case 0:
            SPRITE_SET_CGB_PALETTE(THIS, 3);
            SPRITE_SET_DMG_PALETTE(THIS, 0);
            if(armAttack){
                SPRITE_UNSET_VMIRROR(THIS);
                SetSpriteAnim(THIS, skullHead1, 0);
            }else{
                if((THIS->x - 10) > player_x){
                    SPRITE_UNSET_VMIRROR(THIS);
                    SetSpriteAnim(THIS, skullHead2, 0);
            
                }else if((THIS->x + 10) < player_x){
                    SPRITE_SET_VMIRROR(THIS);
                    SetSpriteAnim(THIS, skullHead2, 0);
                }else{
                    SPRITE_UNSET_VMIRROR(THIS);
                    SetSpriteAnim(THIS, skullHead1, 0);
            
                }
            }
        break;
        case 1:
            if(data->counter <= 14){
                data->counter++;
                SPRITE_SET_CGB_PALETTE(THIS, 7);
                SPRITE_SET_DMG_PALETTE(THIS, 1);
                
            }else{
                data->state = 0;
                data->counter = 0;
                data->canHurt = FALSE;
            }
        break;
    }

    if(sparkAttack){
        if(boss1Counter<=250){
            boss1Counter++;
        }else{
            SpriteManagerAdd(SpriteSparkBall,THIS->x+16,THIS->y+36);
            sparkAttack = FALSE;
            boss1Counter = 0;
        }
    }

    SPRITEMANAGER_ITERATE(i, spr) {
			if(spr->type == SpriteChain || spr->type == SpriteSword) {
				if(CheckCollision(THIS, spr)) {
                    
                        if(data->live >0 && data->canHurt == FALSE){
                            data->canHurt = TRUE;
                            data->live = data->live - 1;
                            
                            data->state = 1;
                            
                            
                            
                            
                        }else if(data->live == 0){
                            //FSkelDeathSound();
					        SpriteManagerRemove(THIS_IDX);
                            SpriteManagerAdd(SpriteExplosion, THIS->x, THIS->y);
                            SpriteManagerAdd(SpriteExplosion, THIS->x, THIS->y - 16);
                            /*if(energy<=19){
                                energy = energy+3;
                            }
                            refreshEnergy(energy);
                            */
                        }
                    
                }
			}
    }
}
void Destroy_SpriteSkelBoss(){

}