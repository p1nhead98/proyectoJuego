#include "Banks/SetBank5.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Sound.h"
#include "Scroll.h"
const UINT8 sword_anim1[] = {2,9,9};
const UINT8 sword_anim2[] = {4,0,4,8,8};
extern INT16 player_x;
extern INT16 player_y;
extern INT8 player_state;
UINT8 sword_state;


void Start_SpriteSword(){
    
    sword_state = 0;
    
    
    
}

void Update_SpriteSword(){
    SPRITE_SET_CGB_PALETTE(THIS, 3);
    SPRITE_SET_DMG_PALETTE(THIS, 0);
    switch(sword_state){
        case 0:
            SetSpriteAnim(THIS, sword_anim1, 22);
            if(SPRITE_GET_VMIRROR(THIS)){
                THIS->y = player_y + 4;
                THIS->x = player_x +10;
            }else{
                THIS->y = player_y + 4;
                THIS->x = player_x -4;
            }
            if(THIS->anim_frame == 1){
                sword_state = 1;
            }
            break;

        case 1:
            SetSpriteAnim(THIS, sword_anim2, 24);
            
            if(SPRITE_GET_VMIRROR(THIS)){
                THIS->y = player_y-1;
                THIS->x = player_x -6;
            }else{
                THIS->y = player_y-1;
                THIS->x = player_x +14;
            }
            if(THIS->anim_frame < 2){
                if(SPRITE_GET_VMIRROR(THIS)){
                    DrawFrame(FRAME_8x16, THIS->frame + 2, THIS->x - scroll_x - 8 , THIS->y - scroll_y  , THIS->flags);
                    DrawFrame(FRAME_8x16, THIS->frame + 4, THIS->x - scroll_x  , THIS->y - scroll_y +16  , THIS->flags);
                    DrawFrame(FRAME_8x16, THIS->frame + 6, THIS->x - scroll_x - 8  , THIS->y - scroll_y +16  , THIS->flags);
                }else{
                    DrawFrame(FRAME_8x16, THIS->frame + 2, THIS->x - scroll_x + 8 , THIS->y - scroll_y , THIS->flags);
                    DrawFrame(FRAME_8x16, THIS->frame + 4, THIS->x - scroll_x  , THIS->y - scroll_y +16  , THIS->flags);
                    DrawFrame(FRAME_8x16, THIS->frame + 6, THIS->x - scroll_x + 8  , THIS->y - scroll_y +16  , THIS->flags);
                }
                
            }
            if(THIS->anim_frame == 3  || player_state == 3 || player_state == 0 || player_state == 5 || player_state == 6){
                SpriteManagerRemove(THIS_IDX);
            }
            break;

    }












  
    
    
}

void Destroy_SpriteSword(){

}