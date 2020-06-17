#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Math.h"
#include "Sound.h"

const UINT8 bullet_1[] ={2, 0,1};

void Start_SpriteEnemyBullet(){
    SetSpriteAnim(THIS, bullet_1, 15);
}
void Update_SpriteEnemyBullet(){
    switch(THIS->unique_id){
        case 1:
            THIS->y++;
            break;
        
        case 2:
            THIS->y++;
            THIS->x++;
            break;

        case 3:
            THIS->y++;
            THIS->x--;
            break;

        case 4:
            if(SPRITE_GET_VMIRROR(THIS)){
                THIS->x--;
            }else{
                THIS->x++;
            }
            break;
        
        case 5:
            if(SPRITE_GET_VMIRROR(THIS)){
                THIS->x--;
            }else{
                THIS->x++;
            }
            THIS->y--;
            break;
        
        
    }
   

}
void Destroy_SpriteEnemyBullet(){

}