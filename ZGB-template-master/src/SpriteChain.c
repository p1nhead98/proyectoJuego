#include "Banks/SetBank2.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Sound.h"
const UINT8 chain_anim[] = {4,0,0,1,1};

extern INT16 player_x;
extern INT16 player_y;
extern INT8 player_state;
void WhipSound(){

    if(THIS->anim_frame == 3){
        PlayFx(CHANNEL_4, 10, 0x3d, 0xa1, 0x02, 0x80);
    
    }
}
void chainCollisionChange(){
    if(THIS->anim_frame>=2){
        THIS->coll_x = 7;
        THIS->coll_y = 7;
        THIS->coll_w = 3;
        THIS->coll_h = 3;
    }else{
        THIS->coll_x = 0;
        THIS->coll_y = 6;
        THIS->coll_w = 16;
        THIS->coll_h = 2;
    }
}

void Start_SpriteChain(){
    SetSpriteAnim(THIS, chain_anim, 15);
}

void Update_SpriteChain(){
    
    WhipSound();
    if(SPRITE_GET_VMIRROR(THIS)){
       if(THIS->anim_frame >=2){
             THIS->coll_x = 7;
            THIS->coll_y = 7;
            THIS->coll_w = 3;
            THIS->coll_h = 3;
            THIS->y = player_y+4;
            THIS->x = player_x -14;
        }else{
                    THIS->coll_x = 0;
            THIS->coll_y = 6;
            THIS->coll_w = 16;
            THIS->coll_h = 2;
            THIS->y = player_y - 5;
            THIS->x = player_x +10;
            
        }

    }else{
        
        if(THIS->anim_frame >=2){
            THIS->coll_x = 7;
            THIS->coll_y = 7;
            THIS->coll_w = 3;
            THIS->coll_h = 3;
            THIS->y = player_y+4;
            THIS->x = player_x +14;
        }else{
            
                    THIS->coll_x = 0;
            THIS->coll_y = 6;
            THIS->coll_w = 16;
            THIS->coll_h = 2;
            THIS->y = player_y - 5;
            THIS->x = player_x -10;
            
        }
    }
  
    if(THIS->anim_frame == 4 || player_state == 3 || player_state == 0 || player_state == 5){
        SpriteManagerRemove(THIS_IDX);
    }
    
}

void Destroy_SpriteChain(){

}