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
const UINT8 skullHead3[] = {15,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};


BOOLEAN armAttack;
BOOLEAN sparkAttack;
INT16 boss1Counter;
extern BOOLEAN boss1death;
extern void ScreenShake();


struct SkelBossCustomData
{
    BOOLEAN canHurt;
    INT8 state;
    UINT8 live;
    INT8 counter;
    UINT16 counter2;
    BOOLEAN death;
    INT8 accel_y;
    
};

void bossSkelJump(struct SkelBossCustomData* data){
    data->accel_y = -60;
}

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
    data->counter2 = 0;
    data->live = 17;
    data->death = FALSE;
    data->state = 0;
  
    data->accel_y = 0;
}
void Update_SpriteSkelBoss(){
    struct SkelBossCustomData* data = (struct SkelBossCustomData*)THIS->custom_data;
    UINT8 i;
	struct Sprite* spr;
    
    


    if(data->death == FALSE){
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
        if(boss1Counter<=230){
            boss1Counter++;
        }else{
            SpriteManagerAdd(SpriteSparkBall,THIS->x + 8,THIS->y+36);
            sparkAttack = FALSE;
            boss1Counter = 0;
        }
    }
    
    SPRITEMANAGER_ITERATE(i, spr) {
			if(spr->type == SpriteChain || spr->type == SpriteGuadana) {
				if(CheckCollision(THIS, spr)) {
                    
                        if(data->live >0 && data->canHurt == FALSE){
                            data->canHurt = TRUE;
                            data->live = data->live - 1;
                            
                            data->state = 1;
                            
                        }else if(data->live == 0){
                            if(data->death == FALSE){
                                data->counter2 = 0;
                                data->death = TRUE;
                                boss1death = TRUE;
                                data->state = 0;
                            }
                    }
			}
    }
}
    

    }else{
        //TranslateSprite(THIS, 0, 1);
        SPRITE_SET_CGB_PALETTE(THIS, 3);
        SPRITE_SET_DMG_PALETTE(THIS, 0);
        if(data->counter <= 20){
            data->counter++;
            if(data->counter == 10){
                SpriteManagerAdd(SpriteExplosion,THIS->x + 15,THIS->y+15);
                SpriteManagerAdd(SpriteExplosion,THIS->x -9,THIS->y+29);
                SpriteManagerAdd(SpriteExplosion,THIS->x + 22,THIS->y+20);
                SpriteManagerAdd(SpriteExplosion,THIS->x + 5,THIS->y+10);
            }
        }else{
            data->counter = 0;
            SpriteManagerAdd(SpriteExplosion,THIS->x + 4,THIS->y+32);
            SpriteManagerAdd(SpriteExplosion,THIS->x -10,THIS->y+11);
            SpriteManagerAdd(SpriteExplosion,THIS->x ,THIS->y+7);
            SpriteManagerAdd(SpriteExplosion,THIS->x + 26,THIS->y+29);
        }
        if(data->accel_y < 80){
            data->accel_y +=4;
        }
        switch(data->state){
            case 0:
                SetSpriteAnim(THIS, skullHead3, 13);
                if(THIS->anim_frame % 2 != 0){
                    
                    if(SPRITE_GET_VMIRROR(THIS)){
                        SPRITE_UNSET_VMIRROR(THIS);
                    }else{
                        SPRITE_SET_VMIRROR(THIS);
                    }
                }
                if(THIS->anim_frame == 14){
                    data->state = 1;
                    data->counter2 = 0;
                }
            break;

            case 1:
                SetSpriteAnim(THIS, skullHead1, 0);
                if(data->counter2 < 101){
                    data->counter2++;
                if(data->counter2 % 2 == 0){
                    THIS->x = THIS-> x + 2;
                }else{
                    THIS->x = THIS-> x - 2;
                }
                if(data->counter2 == 101){
                    data->state = 2;
                    data->counter2 = 0;
                }
                }
            break;

            case 2:
            
                if(TranslateSprite(THIS, 0, (data->accel_y >> 4))){
                    
                    data->state = 3;
                    bossSkelJump(data);
                    ScreenShake();
                }
            break;

            case 3:
                THIS->y = THIS->y + (data->accel_y >> 4);
            break;
        }


    }
}
void Destroy_SpriteSkelBoss(){

}