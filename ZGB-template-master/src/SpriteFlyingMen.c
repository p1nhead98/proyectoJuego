#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"
extern INT16 player_x;
const UINT8 f_men[] = {3, 0,1,2};

struct fmenCustomData
{

    INT8 counter;
    
};

void Start_SpriteFlyingMen(){
    struct fmenCustomData* data = (struct fmenCustomData*)THIS->custom_data;
    SetSpriteAnim(THIS, f_men, 17);
    data->counter = 0;
     
}

void Update_SpriteFlyingMen(){
    struct fmenCustomData* data = (struct fmenCustomData*)THIS->custom_data;

    if(THIS->x > player_x){
        SPRITE_SET_VMIRROR(THIS);
    }else{
        SPRITE_UNSET_VMIRROR(THIS);
    }
    if(data->counter <= 120){
        data->counter++;
        if(data->counter <=60){
            THIS->y--;
        }else{
            THIS->y++;
        }
        if(data->counter == 120){
            data->counter = 0;
        }
    }
}

void Destroy_SpriteFlyingMen(){

}