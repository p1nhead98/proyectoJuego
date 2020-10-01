#include "Banks/SetBank5.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"
#include "Scroll.h"
#include "hud.h"
extern INT16 player_x;
extern INT16 player_y;
extern BOOLEAN gameOver;
const UINT8 stoneman_0[] = {6, 7,7,7,7,3,3};
const UINT8 stoneman_1[] = {4, 1,3,1,5};
const UINT8 stoneman_2[] = {1, 1};
extern UINT16 energy;
struct StoneManCustomData
{
    BOOLEAN canHurt;
    BOOLEAN canwalk;
    INT8 state;
    BOOLEAN canShoot;
    UINT8 lives;
    INT8 counter;
};



void StoneManMove(){

    if(SPRITE_GET_VMIRROR(THIS)) {
    	        if(TranslateSprite(THIS, -5 << delta_time, 0)) {
			        SPRITE_UNSET_VMIRROR(THIS);
		        } else	if(!scroll_collisions[GetScrollTile(((THIS->x + THIS->coll_x) >> 3), (THIS->y >> 3) + 2u)]) {
			        SPRITE_UNSET_VMIRROR(THIS);
		        }
	        }else {
		        if(TranslateSprite(THIS, +5 << delta_time, 0)) {
			        SPRITE_SET_VMIRROR(THIS);
		        }else if(!scroll_collisions[GetScrollTile(((THIS->x + THIS->coll_x + THIS->coll_w) >> 3), (THIS->y >> 3) + 2u)]) {
			        SPRITE_SET_VMIRROR(THIS);
		        }
	        }
}

void StoneManShoot(struct StoneManCustomData* data){
    if(data->canShoot == TRUE){
        struct Sprite* sprite_stone = SpriteManagerAdd(SpriteStone,THIS->x,THIS->y - 29);
        sprite_stone->flags = THIS->flags;
        data->canShoot = FALSE;
    }

}
void Start_SpriteStoneMan(){
    struct StoneManCustomData* data = (struct StoneManCustomData*)THIS->custom_data;
    data->canwalk = FALSE;
    THIS->coll_x = 3;
    THIS->coll_y = -16;
    THIS->coll_w = 11;
    THIS->coll_h = 32;
    data->lives = 8;
    if(THIS->x > player_x){
        SPRITE_SET_VMIRROR(THIS);
    }else{
        SPRITE_UNSET_VMIRROR(THIS);
    }
    data->state = 0;
    data->canShoot = TRUE;
    data->counter = 0;
    data->canHurt = FALSE;
}
void Update_SpriteStoneMan(){
    struct StoneManCustomData* data = (struct StoneManCustomData*)THIS->custom_data;
    UINT8 i;
	struct Sprite* spr;
    DrawFrame(FRAME_16x16, THIS->frame - 3 , THIS->x - scroll_x , THIS->y - scroll_y - 16, THIS->flags);
    
    if(gameOver == TRUE){
        SPRITE_SET_CGB_PALETTE(THIS, 0);
        SPRITE_SET_DMG_PALETTE(THIS,0);
    }
    
    switch(data->state){
        case 0: 
        SetSpriteAnim(THIS, stoneman_0, 8);
        StoneManShoot(data);
        if(THIS->anim_frame == 5){
            data->state = 1;
        }
        break;
    
        
        case 1:
            SPRITE_SET_CGB_PALETTE(THIS, 3);
            SPRITE_SET_DMG_PALETTE(THIS, 0);
            SetSpriteAnim(THIS,stoneman_1,7);
            if(THIS->anim_frame == 1 || THIS->anim_frame == 3){
                    if(data->canwalk == TRUE){
                        data->canwalk = FALSE;
                        StoneManMove();
                    }
            }else{
                data->canwalk = TRUE;
            }
            break;

        case 2:
            if(data->counter <= 18){
                    data->counter++;
                    SPRITE_SET_CGB_PALETTE(THIS, 7);
                    SPRITE_SET_DMG_PALETTE(THIS, 1);
                    if(data->counter == 18){
                        data->state = 1;
                        data->counter = 0;
                        data->canHurt = FALSE;
                        
                    }
                }
            break;
    }


    SPRITEMANAGER_ITERATE(i, spr) {
			if(spr->type == SpriteChain || spr->type == SpriteGuadana || spr->type == SpriteBumerang) {
				if(CheckCollision(THIS, spr)) {
                    
                        if(data->lives >0 && data->canHurt == FALSE){
                            data->canHurt = TRUE;
                            if(spr->type == SpriteChain){
                                data->lives = data->lives - 2;
                            }else if(spr->type == SpriteGuadana || spr->type == SpriteBumerang){
                                data->lives = data->lives - 1;
                            }
                            data->state = 2;
                            
                            
                            
                            
                        }else if(data->lives < 1){
                            //FSkelDeathSound();
                            if(spr->type == SpriteChain){
                                if(energy<=17){
                                    energy = energy + 3;
                                }else if(energy == 18){
                                    energy = energy + 2;
                                }else if(energy == 19){
                                    energy = energy + 1;
                                }
                            }
                            refreshEnergy(energy);
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
void Destroy_SpriteStoneMan(){

}