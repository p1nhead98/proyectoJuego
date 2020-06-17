#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"

const UINT8 explosion1[] = {3, 0,1,2};
void Start_SpriteExplosion(){
    SetSpriteAnim(THIS, explosion1,30);
}
void Update_SpriteExplosion(){
    if(THIS->anim_frame == 2){
        SpriteManagerRemove(THIS_IDX);
    }
}
void Destroy_SpriteExplosion(){

}