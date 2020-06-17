#include "Banks/SetBank2.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Sound.h"
#include "Math.h"

const UINT8 wspider_1[] = {1, 0};
const UINT8 wspider_2[] = {5, 0,1,2,3,4};
const UINT8 wspider_3[] = {5,4,4,4,4,4};
const UINT8 wspider_4[] = {3,5,5,5};
const UINT8 wspider_5[] = {1,6};
struct wspiderCustomData
{
    UINT8 wspider_state;
    INT8 counter;
    BOOLEAN direction;
    UINT8 lives;
    INT16 accel_y;
    INT16 accel_x;
};

struct Sprite* wspider_parent = 0;
extern INT16 player_x;
extern INT16 player_y;
UINT8 tile_collisionws;

void Start_SpriteWoodSpider(){
    struct wspiderCustomData* data = (struct wspiderCustomData*)THIS->custom_data;
   
    data->wspider_state = 0;
}
void Update_SpriteWoodSpider(){
    struct wspiderCustomData* data = (struct wspiderCustomData*)THIS->custom_data;



    switch(data->wspider_state){
        case 0:
            SetSpriteAnim(THIS, wspider_1, 0);
            if(DISTANCE(THIS->x, player_x ) < 20 && DISTANCE(THIS->y, player_y) < 16 ){
                data->wspider_state = 1;
            }
            break;
        case 1:
            SetSpriteAnim(THIS, wspider_2,15);
            if(THIS->anim_frame == 4){
                data->wspider_state = 2;
            }
            break;

        case 2:
            SetSpriteAnim(THIS, wspider_3,15);
            if(THIS->anim_frame == 4){
                data->wspider_state = 3;
            }
            break;
        
        case 3:
            SetSpriteAnim(THIS, wspider_4, 15);
            if(THIS->anim_frame == 2){
                if(THIS->x < player_x){
                    data->direction = TRUE;
                }else if (THIS->x > player_x){
                    data->direction = FALSE;
                }
                data->wspider_state = 4;
                data->accel_y  = -50;
            }
            break;
        case 4:
            SetSpriteAnim(THIS, wspider_5, 15);
            if(data->direction){
                TranslateSprite(THIS, 1, 0);
            }else {
                TranslateSprite(THIS, -1, 0);
            }
            wspider_parent = 0;
            break;
    }


    if(wspider_parent == 0 ){
		if(data->accel_y < 60  ) {
			data->accel_y += 4;
           
		}
	tile_collisionws = TranslateSprite(THIS, 0, (data->accel_y >> (4 << delta_time)));
	if(!tile_collisionws && delta_time != 0 && data->accel_y < 40  ) { //Do another iteration if there is no collision
		data->accel_y += 4 >> delta_time;
            
		tile_collisionws = TranslateSprite(THIS, 0, (data->accel_y >> 4));
	}
	if(tile_collisionws && !TranslateSprite(THIS,0,(data->accel_y >> (-4 << delta_time)))) {
              
			
	    data->accel_y = 0;
               
        if(data->wspider_state == 4){
            data->wspider_state = 2;
        } 
                    
                
			
			

		//CheckCollisionTile();
	}
    }
}

void Destroy_SpriteWoodSpider(){

}