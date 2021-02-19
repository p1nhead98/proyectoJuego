#include "Banks/SetBank3.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"

const UINT8 land_1[] = {1,0};
const UINT8 land_2[] = {4,0,1,2,3};
const UINT8 land_3[] = {1,3};
const UINT8 land_4[] = {4,3,2,1,0};
struct landCustomData
{
    INT16 count;
    INT16 accel_y;
    INT8 state;
    BOOLEAN fall;
    
};
extern INT16 player_y;
extern INT8 player_state;


void Start_SpriteLand(){
    struct landCustomData* data = (struct landCustomData*)THIS->custom_data;
    data->count = 0;
    data->state = 0;
    data->accel_y = 0;
    data->fall = FALSE;
    THIS->coll_x = 1;
    THIS->coll_y = 0;
    THIS->coll_w = 13;
    THIS->coll_h = 9;
}

void Update_SpriteLand(){
    struct landCustomData* data = (struct landCustomData*)THIS->custom_data;
    UINT8 i;
    struct Sprite* spr;

    switch(data->state){
        case 0:
            data->count = 0;
            SetSpriteAnim(THIS, land_1, 0);
            break;
        case 1:
            if(data->count < 21){
                data->count++;
                if(data->count % 2 == 0){
                    THIS->x = THIS-> x + 2;
                }else{
                    THIS->x = THIS-> x - 2;
                }
                if(data->count == 20){
                    data->count = 0;
                    data->state = 2;
                }
            }
            break;

        case 2:
            SetSpriteAnim(THIS, land_2, 30);
            THIS->coll_x = 0;
            THIS->coll_y = 0;
            THIS->coll_w = 0;
            THIS->coll_h = 0;
            if(THIS->anim_frame == 3){
                data->state = 3;
            }
            break;
        case 3:
            SetSpriteAnim(THIS, land_3, 0);
            if(data->count < 60){
                data->count++;
                if(data->count == 60 ){
                data->state = 4;
                }
            }
            break;
        case 4:
            SetSpriteAnim(THIS, land_4, 30);
            if(THIS->anim_frame == 3){
                data->state = 0;
            }
            break;
    }


   SPRITEMANAGER_ITERATE(i, spr) {
			if(spr->type == SpritePlayer) {
				if(CheckCollision(THIS, spr) && THIS->y > player_y && player_state == 0) {
                    if(data->state == 0){
                        data->state = 1;
                    }
                }
			}
		}
}
void Destroy_SpriteLand(){

}