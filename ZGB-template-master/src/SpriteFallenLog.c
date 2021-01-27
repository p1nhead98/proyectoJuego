#include "Banks/SetBank9.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
struct fallenLogCustomData
{
    INT16 count;
    INT16 accel_y;
    INT8 state;
    BOOLEAN fall;
    
};
extern INT16 player_y;
extern INT8 player_state;


void Start_SpriteFallenLog(){
    struct fallenLogCustomData* data = (struct fallenLogCustomData*)THIS->custom_data;
    data->count = 0;
    data->state = 0;
    data->accel_y = 0;
    data->fall = FALSE;
    THIS->coll_x = 1;
    THIS->coll_y = 0;
    THIS->coll_w = 31;
    THIS->coll_h = 9;
}

void Update_SpriteFallenLog(){
    struct fallenLogCustomData* data = (struct fallenLogCustomData*)THIS->custom_data;
    UINT8 i;
    struct Sprite* spr;
     DrawFrame(FRAME_16x16, THIS->frame + 4 , THIS->x - scroll_x +16, THIS->y - scroll_y , THIS->flags);
    switch(data->state){
        case 1:
            if(data->count < 21){
                data->count++;
                if(data->count % 2 == 0){
                    THIS->x = THIS-> x + 2;
                }else{
                    THIS->x = THIS-> x - 2;
                }
                if(data->count == 20){
                    data->state = 2;
                }
            }
            break;

        case 2:
            if(data->accel_y <= 9){
                data->accel_y += 2;
            }
            break;
    }

    THIS->y = THIS->y + (data->accel_y >> 2);

   SPRITEMANAGER_ITERATE(i, spr) {
			if(spr->type == SpritePlayer) {
				if(CheckCollision(THIS, spr) && THIS->y > player_y && player_state == 0) {
                    if(data->fall == FALSE){
                    data->fall = TRUE;
                    data->state = 1;
                    }
                }
			}
		}
}
void Destroy_SpriteFallenLog(){

}