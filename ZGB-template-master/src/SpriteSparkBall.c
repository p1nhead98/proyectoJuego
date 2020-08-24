#include "Banks/SetBank6.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"
#include "Scroll.h"

const UINT8 sparkball1[] = {10,0,1,0,1,0,1,0,1,0,1};
const UINT8 sparkball2[] = {2,0,1};
extern INT16 player_x;
extern INT16 player_y;
extern BOOLEAN armAttack;

struct SparkBallCustomData
{
    INT16 target_x;
    INT16 target_y;
    INT8 counter;
    INT8 state;
};



void Start_SpriteSparkBall(){
    struct SparkBallCustomData* data = (struct SparkBallCustomData*)THIS->custom_data;
    data->state = 0;
    data->counter = 0;
    
}
void Update_SpriteSparkBall(){
    struct SparkBallCustomData* data = (struct SparkBallCustomData*)THIS->custom_data;
    UINT8 i;
	struct Sprite* spr;
    
    switch(data->state){
        case 0:
            SetSpriteAnim(THIS, sparkball1, 15);
            if(THIS->anim_frame == 9){
                data->state = 1;
                data->target_x = player_x;
                data->target_y = player_y;
            }
        break;
        case 1:
            SetSpriteAnim(THIS, sparkball2, 15);
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
                data->counter++;
            }
        break;
    }
    if(data->counter == 3){
            SpriteManagerRemove(THIS_IDX);
            armAttack = TRUE;
        }
    DrawFrame(FRAME_8x16, THIS->frame, THIS->x - scroll_x + 8 , THIS->y - scroll_y ,  32);

     SPRITEMANAGER_ITERATE(i, spr) {
		/*	if(spr->type == SpritePlayer) {
				if(CheckCollision(THIS, spr)) {
                    if(data->canDest == TRUE){
                        SpriteManagerRemove(THIS_IDX);
                    }
                    }
				}

                */
			}

}
void Destroy_SpriteSparkBall(){

}