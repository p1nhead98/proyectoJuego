#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Math.h"
#include "Sound.h"

const UINT8 viper_1[] ={4, 0,1,2,1};
extern INT16 player_x;
extern INT16 player_y;

struct ViperCustomData
{

    INT8 counter;
    
};



void Shoot(){
    SpriteManagerAdd(SpriteExplosion,THIS->x, THIS->y);
    struct Sprite* sprite_ebullet1 = SpriteManagerAdd(SpriteEnemyBullet,THIS->x,THIS->y);
    struct Sprite* sprite_ebullet2 = SpriteManagerAdd(SpriteEnemyBullet,THIS->x,THIS->y);
    struct Sprite* sprite_ebullet3 = SpriteManagerAdd(SpriteEnemyBullet,THIS->x,THIS->y);

    sprite_ebullet1->unique_id = 1;
    sprite_ebullet2->unique_id = 2;
    sprite_ebullet3->unique_id = 3;
}

void Start_SpriteViper(){
    struct ViperCustomData* data = (struct ViperCustomData*)THIS->custom_data;
    SetSpriteAnim(THIS, viper_1, 15);
    data->counter = 0;
    THIS->coll_x = 3;
    THIS->coll_y = 4;
    THIS->coll_w = 11;
    THIS->coll_h = 9;
}
void Update_SpriteViper(){
    struct ViperCustomData* data = (struct ViperCustomData*)THIS->custom_data;
    UINT8 i;
	struct Sprite* spr;
    if(DISTANCE(THIS->x, player_x) < 10 ){
                PlayFx(CHANNEL_4, 20, 0x3b, 0xd1, 0x79, 0x80);
                SpriteManagerRemove(THIS_IDX);
                Shoot();
    }
   

    if(data->counter <= 3){

        data->counter++;
       
        if(data->counter == 3){
             THIS->x--;
            data->counter = 0;
        }
    }
     
         SPRITEMANAGER_ITERATE(i, spr) {
			if(spr->type == SpriteChain) {
				if(CheckCollision(THIS, spr)) {
                    
					SpriteManagerRemove(THIS_IDX);
                    SpriteManagerAdd(SpriteExplosion, THIS->x, THIS->y);
                    PlayFx(CHANNEL_4, 20, 0x3b, 0xd1, 0x79, 0x80);
                    
                }
			}
		}
}
void Destroy_SpriteViper(){
    
}