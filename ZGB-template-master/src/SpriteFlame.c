#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"

const UINT8 fire1[] = {47, 0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,1,5};
void Start_SpriteFlame(){
    SetSpriteAnim(THIS, fire1,30);
}
void Update_SpriteFlame(){
    if(THIS->anim_frame == 46){
        SpriteManagerRemove(THIS_IDX);
    }
}
void Destroy_SpriteFlame(){

}