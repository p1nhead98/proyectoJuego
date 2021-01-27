#include "Banks/SetBank12.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Math.h"
#include "Sound.h"
extern INT16 player_x;
extern INT16 player_y;
const UINT8 fhead1[] = {1, 0};
const UINT8 fhead2[] = {6, 1,1,1,1,1,1};
extern BOOLEAN hide;

struct flyingHeadCustomData
{
    INT16 target_x;
    INT16 target_y;
    INT8 counter;
    INT8 state;
};

extern BOOLEAN gameOver;
void Start_SpriteForestBossH(){
    struct flyingHeadCustomData* data = (struct flyingHeadCustomData*)THIS->custom_data;
    THIS->flags = 128;
    data->state = 0;
    data->counter = 0;
}
void Update_SpriteForestBossH(){
    struct flyingHeadCustomData* data = (struct flyingHeadCustomData*)THIS->custom_data;
    UINT8 i;
    struct Sprite* spr;

    switch(data->state){
        case 0:
            SetSpriteAnim(THIS, fhead2, 15);
            if(THIS->anim_frame == 5){
                data->state = 1;
                data->target_x = player_x;
                data->target_y = player_y;
            }
        break;
        case 1:
            if(hide == FALSE){
            SetSpriteAnim(THIS, fhead1, 15);
            if(THIS->x < data->target_x){
                THIS->x++;
            }else if(THIS->x > data->target_x){
                THIS->x--;
            }
            if(THIS->y < data->target_y){
                THIS->y++;
            }else if (THIS->y > data->target_y){
                THIS->y--;
            }
            if(THIS->x == data->target_x && THIS->y == data->target_y){
                data->state = 0;
                
            }
            }
        break;
    }
  
   
    SPRITEMANAGER_ITERATE(i, spr) {
		
	}
}
void Destroy_SpriteForestBossH(){

}


