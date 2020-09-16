#include "Banks/SetBank4.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Math.h"
#include "Sound.h"

const UINT8 bullet_1[] ={2, 0,1};
extern BOOLEAN gameOver;
void Start_SpriteEnemyBullet(){
    SetSpriteAnim(THIS, bullet_1, 15);
    THIS->coll_x = 2;
    THIS->coll_y = 6;
    THIS->coll_w = 4;
    THIS->coll_h = 4;
}
void Update_SpriteEnemyBullet(){
    UINT8 i;
    struct Sprite* spr;

    if(gameOver == TRUE){
        SPRITE_SET_CGB_PALETTE(THIS, 0);
        SPRITE_SET_DMG_PALETTE(THIS,0);
    }
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
                THIS->x = THIS->x - 3;
            }else{
                THIS->x = THIS->x + 3;
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
   
    SPRITEMANAGER_ITERATE(i, spr) {
		
	}
}
void Destroy_SpriteEnemyBullet(){

}




