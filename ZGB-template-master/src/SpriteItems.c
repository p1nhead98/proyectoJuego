#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"
#include "Scroll.h"
#include "Trig.h"
#include "hud.h"
#include "print.h"

const UINT8 item1[] = {2, 0,0};
const UINT8 item2[] = {2, 1,1};
const UINT8 item3[] = {2, 2,2};
const UINT8 item4[] = {2, 3,3};
const UINT8 item5[] = {2, 4,4};
//const UINT8 bole_anim2[] = {4,0,0,0,0};
extern INT16 player_x;
extern INT16 player_y;
extern UINT16 subweaponCounter;
extern UINT8 currentSubWeapon;
extern UINT8 lastSubWeapon;

struct ItemsCustomData
{
    INT16 accel_x;
    INT16 accel_y;
    UINT8 type;
    UINT8 counter;
    
};

void dropItems(struct ItemsCustomData* data){
  
    switch(subweaponCounter){
        case 5:
            data->type = 1;
            SetSpriteAnim(THIS, item1, 15);
        break;
        case 10:
            data->type = 1;
            SetSpriteAnim(THIS, item1, 15);
        break;
        case 15:
            data->type = 1;
            SetSpriteAnim(THIS, item1, 15);            
        break;
        case 20:
            data->type = 1;
            SetSpriteAnim(THIS, item1, 15);
        break;
        case 25:
            data->type = 1;
            SetSpriteAnim(THIS, item1, 15);
        break;
        case 7:
            data->type = 2;
            SetSpriteAnim(THIS, item2, 15);
        break;
        case 13:
            data->type = 2;
            SetSpriteAnim(THIS, item2, 15);
        break;
        case 19:
            data->type = 2;
            SetSpriteAnim(THIS, item2, 15);
        break;
        case 26:
            data->type = 2;
            SetSpriteAnim(THIS, item2, 15);
        break;
        case 14:
            data->type = 3;
            SetSpriteAnim(THIS, item3, 15);
        break;
        case 23:
            data->type = 3;
            SetSpriteAnim(THIS, item3, 15);
        break;
        case 29:
            data->type = 3;
            SetSpriteAnim(THIS, item3, 15);
        break;
        default:
            if(subweaponCounter % 2 == 0 && subweaponCounter > 20){
                data->type = 4;
                SetSpriteAnim(THIS, item4,15);
            }else if(subweaponCounter % 2 !=0 && subweaponCounter > 5){
                data->type = 5;
                SetSpriteAnim(THIS, item5,15);
            }else{
                data->type = 0;
            }
        break;
    }
    
}

void itemJump(struct ItemsCustomData* data){
    data->accel_y = -30;
}

void Start_SpriteItems(){
    struct ItemsCustomData* data = (struct ItemsCustomData*)THIS->custom_data;
    data->accel_y = 0;
    data->counter = 0;
    if(subweaponCounter >= 30){
        subweaponCounter = 0;
    }
    dropItems(data);
    itemJump(data);
    THIS->coll_x = 3;
    THIS->coll_y = 3;
    THIS->coll_w = 10;
    THIS->coll_h = 10;
}

void Update_SpriteItems(){
    struct ItemsCustomData* data = (struct ItemsCustomData*)THIS->custom_data;
    UINT8 i;
	struct Sprite* spr;
    if(data->type == 0 ){
        SpriteManagerRemove(THIS_IDX);
    }
    
   
    if(THIS->anim_frame == 1){
        SPRITE_SET_CGB_PALETTE(THIS,7);
        SPRITE_SET_DMG_PALETTE(THIS, 1);
    }else{
        SPRITE_SET_CGB_PALETTE(THIS, 3);
        SPRITE_SET_DMG_PALETTE(THIS, 0);
    }

                       /*if(SPRITE_GET_VMIRROR(THIS)){
                DrawFrame(FRAME_8x16, THIS->first_tile , THIS->x - scroll_x - 8 , THIS->y - scroll_y , THIS->flags);
            }else{
                DrawFrame(FRAME_8x16, THIS->first_tile , THIS->x - scroll_x + 8 , THIS->y - scroll_y , THIS->flags);
            }*/
    
    if(data->accel_y < 24){
            data->accel_y +=4;
    }
    TranslateSprite(THIS, 0, data->accel_y >> 4 );
    
    if(data->counter < 250){
        data->counter++;
    }else{
        SpriteManagerRemove(THIS_IDX);
    }

     SPRITEMANAGER_ITERATE(i, spr) {
			if(spr->type == SpritePlayer) {
				if(CheckCollision(THIS, spr)) {
                    SpriteManagerRemove(THIS_IDX);
                    lastSubWeapon = currentSubWeapon;
                    switch(data->type){
                        case 1:
                            currentSubWeapon = 1;
                        break;
                        case 2:
                            currentSubWeapon = 0;
                        break;
                        case 3:
                            currentSubWeapon = 2;                        
                        break;
                        case 4:
                        break;
                        case 5:
                        break;
                    }
                    RefreshWeapon(currentSubWeapon);
                            PRINT_POS(17, 0);
                            Printf(":%d", (UINT16)(currentSubWeapon));

                    

                }
			}
        }

}
void Destroy_SpriteItems(){

}