#include "Banks/SetBank3.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"

const UINT8 fire1[] = {47, 0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,1,5};
void Start_SpriteFlame(){
    SetSpriteAnim(THIS, fire1,30);
    THIS->coll_x = 2;
    THIS->coll_y = 6;
    THIS->coll_w = 6;
    THIS->coll_h = 10;
}
void Update_SpriteFlame(){
    if(THIS->anim_frame == 46){
        SpriteManagerRemove(THIS_IDX);
    }
}
void Destroy_SpriteFlame(){

}