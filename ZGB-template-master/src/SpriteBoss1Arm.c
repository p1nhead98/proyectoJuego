#include "Banks/SetBank6.h"
#include <gb\gb.h>
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"
#include "Scroll.h"

const UINT8 arm0[] = {5,2,2,2,2,2};
const UINT8 arm1[] = {1,2};
const UINT8 arm2[] = {1,3};
const UINT8 arm3[] = {15,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
const UINT8 arm4[] = {1,4};

extern INT16 player_x;
extern INT16 player_y;

extern BOOLEAN armAttack;
extern BOOLEAN sparkAttack;
BOOLEAN boss1death;
struct Boss1ArmCustomData
{
    INT8 state;
    INT8 state2;
    INT8 counter;
    INT8 counter2;
    INT16 start_x;
    INT16 start_y;   
};
void SpriteShake(){
    UINT8 i = 0;
    if(i < 31){
        i++;
        if(i % 2 == 0){
            THIS->x = THIS-> x + 2;
        }else{
            THIS->x = THIS-> x - 2;
        }
        if(i == 31){
            i = 0;
        }
    }
}
void ScreenShake(){
    UINT8 i = 0;
   
    if(i <= 31){
        i++;
        if(i % 2 == 0){
            scroll_x = scroll_x+4;
        }else{
            scroll_x = scroll_x-4;
        }
        
    }
}

void Start_SpriteBoss1Arm(){
    struct Boss1ArmCustomData* data = (struct Boss1ArmCustomData*)THIS->custom_data;
    
    THIS->coll_x = 3;
    THIS->coll_y = 0;
    THIS->coll_w = 10;
    THIS->coll_h = 10;

    data->state = 0;
    
    data->state2 = 0; 
    data->counter = 0;
    data->counter2 = 0;
    data->start_x = THIS->x;
    data->start_y = THIS->y;
    boss1death = FALSE;
}

void Update_SpriteBoss1Arm(){
    struct Boss1ArmCustomData* data = (struct Boss1ArmCustomData*)THIS->custom_data;
    UINT8 i;
	struct Sprite* spr;
    
  if(boss1death == FALSE){  
    switch(data->state){
        case 0:
            DrawFrame(FRAME_16x16, THIS->first_tile, THIS->x - scroll_x  , THIS->y - scroll_y - 16,  THIS->flags);
            SetSpriteAnim(THIS, arm0, 3);
            if(THIS->anim_frame == 4){
                data->state = 1;
            }
        break; 
        case 1:
            DrawFrame(FRAME_16x16, THIS->first_tile, THIS->x - scroll_x  , THIS->y - scroll_y - 16,  THIS->flags);
            SetSpriteAnim(THIS, arm1, 0);
            if(data->counter < 31){
                data->counter++;
                if(data->counter % 2 == 0){
                    THIS->x = THIS-> x + 2;
                }else{
                    THIS->x = THIS-> x - 2;
                }
                if(data->counter == 31){
                    data->state = 2;
                    data->counter = 0;
                }
            }
            
                    
                    
        break;

        case 2:
            SetSpriteAnim(THIS, arm2, 1);
            switch(data->counter){
                case 0:
                    
                    if(SPRITE_GET_VMIRROR(THIS)){
                        DrawFrame(FRAME_16x16, THIS->first_tile, THIS->x - scroll_x - 4 , THIS->y - scroll_y - 16,  THIS->flags);
                        if(THIS->x < (data->start_x +20)){
                            TranslateSprite(THIS, 2,0);
                        }
                    }else{
                        DrawFrame(FRAME_16x16, THIS->first_tile, THIS->x - scroll_x + 4 , THIS->y - scroll_y - 16,  THIS->flags);
                        if(THIS->x > (data->start_x -20)){
                            TranslateSprite(THIS, -2,0);
                        }
                    }
                break;

                case 1:
                     DrawFrame(FRAME_16x16, THIS->first_tile + 4, THIS->x - scroll_x  , THIS->y - scroll_y - 12,  THIS->flags);
                    if(SPRITE_GET_VMIRROR(THIS)){
                        
                        if(THIS->x > (data->start_x - 10)){
                            TranslateSprite(THIS, -2,0);
                        }
                    }else{
                        
                        if(THIS->x < (data->start_x + 10 )){
                            TranslateSprite(THIS, 2,0);
                        }
                    }
                break;

                case 2:
                   
                    if(SPRITE_GET_VMIRROR(THIS)){
                        DrawFrame(FRAME_16x16, THIS->first_tile, THIS->x - scroll_x + 4  , THIS->y - scroll_y - 16,  0);
                        if(THIS->x > (data->start_x - 30)){
                            TranslateSprite(THIS, -2,0);
                        }
                    }else{
                        DrawFrame(FRAME_16x16, THIS->first_tile, THIS->x - scroll_x - 4 , THIS->y - scroll_y - 16,  32);
                        if(THIS->x < (data->start_x + 30 )){
                            TranslateSprite(THIS, 2,0);
                        }
                    }
                break;
                
                
            }
            if(TranslateSprite(THIS,0,3)){
                if(data->state == 2){
                    data->state = 3;
                    ScreenShake();
                    data->counter++;
                    
                }
            }
        break;

        case 3:

            switch(data->counter - 1){
                case 0:
                    if(SPRITE_GET_VMIRROR(THIS)){
                        DrawFrame(FRAME_16x16, THIS->first_tile, THIS->x - scroll_x - 4 , THIS->y - scroll_y - 16,  THIS->flags);
                    }else{
                        DrawFrame(FRAME_16x16, THIS->first_tile, THIS->x - scroll_x + 4 , THIS->y - scroll_y - 16,  THIS->flags);
                    }
                break;
                case 1:
                    DrawFrame(FRAME_16x16, THIS->first_tile + 4, THIS->x - scroll_x  , THIS->y - scroll_y - 12,  THIS->flags);
                break;
                case 2:
                    if(SPRITE_GET_VMIRROR(THIS)){
                        DrawFrame(FRAME_16x16, THIS->first_tile, THIS->x - scroll_x + 4  , THIS->y - scroll_y - 16,  0);
                    }else{
                        DrawFrame(FRAME_16x16, THIS->first_tile, THIS->x - scroll_x - 4 , THIS->y - scroll_y - 16,  32);
                    }
                break;
            }
            if(data->counter !=3){
                if(data->counter2 <= 15){
                    data->counter2++;
                
                }else{
                    data->state = 4;
                    data->counter2 = 0;
                }
            }else{
                if(data->counter2 <= 25){
                    data->counter2++;
                
                }else{
                    data->state = 4;
                    data->counter2 = 0;
                }
            }
        break;

        case 4:
            DrawFrame(FRAME_16x16, THIS->first_tile + 4, THIS->x - scroll_x  , THIS->y - scroll_y - 16,  THIS->flags);
            
            SetSpriteAnim(THIS, arm1, 1);

            if(THIS->x < data->start_x ){
                TranslateSprite(THIS, 1, 0);
            }else if(THIS->x > data->start_x){
                TranslateSprite(THIS, -1, 0);
            }
            if(THIS->y >= data->start_y){
                TranslateSprite(THIS, 0, -1);
            }


            if(THIS->x == data->start_x && THIS->y == data->start_y){
                if(data->counter == 3){
                    data->state = 5;
                    data->counter = 0;
                }else{
                    data->state = 2;
                }
            }
        break;

        case 5:
            DrawFrame(FRAME_16x16, THIS->first_tile, THIS->x - scroll_x  , THIS->y - scroll_y - 16,  THIS->flags);
                armAttack = FALSE;
                if(sparkAttack == FALSE){
                    sparkAttack = TRUE;
                }
                
                data->state  = 6;
            
        break;
        case 6:
            DrawFrame(FRAME_16x16, THIS->first_tile, THIS->x - scroll_x  , THIS->y - scroll_y - 16,  THIS->flags);
            if(armAttack == TRUE && sparkAttack == FALSE ){
                data->state = 0;
            }
        break;
    }

    


  }else{
      switch(data->state2){
            case 0:
            DrawFrame(FRAME_16x16, THIS->first_tile, THIS->x - scroll_x  , THIS->y - scroll_y - 16,  THIS->flags);
            SetSpriteAnim(THIS, arm3, 13);
            if(data->counter < 31){
                data->counter++;
                if(data->counter % 2 == 0){
                    THIS->x = THIS-> x + 2;
                }else{
                    THIS->x = THIS-> x - 2;
                }
                if(data->counter == 31){
                    data->counter = 0;
                }
            }
            if(THIS->anim_frame == 14){
                data->state2 = 1;
                data->counter = 0;
            }
            break;
            
            case 1:
                SetSpriteAnim(THIS, arm2, 1);
               
                if(SPRITE_GET_VMIRROR(THIS)){       
                    if(THIS->x > (data->start_x - 10)){
                        TranslateSprite(THIS, -2,0);
                    }
                }else{     
                    if(THIS->x < (data->start_x + 10 )){
                        TranslateSprite(THIS, 2,0);
                    }
                }

                if(SPRITE_GET_VMIRROR(THIS)){
                    DrawFrame(FRAME_16x16, THIS->first_tile, THIS->x - scroll_x + 4  , THIS->y - scroll_y - 16,  0);
                }else{
                    DrawFrame(FRAME_16x16, THIS->first_tile, THIS->x - scroll_x - 4 , THIS->y - scroll_y - 16,  32);
                }

                if(TranslateSprite(THIS,0,3)){
                    ScreenShake();
                    if(data->counter <= 1){
                        data->state2 = 2;
                        data->counter++;
                    }else{
                        data->state2 = 3;
                    }
                }
            break;
            case 2:
                SetSpriteAnim(THIS, arm2, 1);
                
                
                if(THIS->y >= data->start_y){
                    TranslateSprite(THIS, 0, -3);
                }

                if(SPRITE_GET_VMIRROR(THIS)){
                    DrawFrame(FRAME_16x16, THIS->first_tile, THIS->x - scroll_x + 4  , THIS->y - scroll_y - 16,  0);
                }else{
                    DrawFrame(FRAME_16x16, THIS->first_tile, THIS->x - scroll_x - 4 , THIS->y - scroll_y - 16,  32);
                }

                if( THIS->y <= data->start_y){
                    
                        data->state2 = 1;
                     
                }
            break;
            
            case 3:
                SetSpriteAnim(THIS, arm2, 1);
                DrawFrame(FRAME_16x16, THIS->first_tile + 4, THIS->x - scroll_x  , THIS->y - scroll_y - 12,  THIS->flags);
            break;
      }
  }
/*
     SPRITEMANAGER_ITERATE(i, spr) {
			if(spr->type == SpritePlayer) {
				if(CheckCollision(THIS, spr)) {
                    if(data->canDest == TRUE){
                        SpriteManagerRemove(THIS_IDX);
                    }
                    }
				}

                
			} */
}
void Destroy_SpriteBoss1Arm(){

}