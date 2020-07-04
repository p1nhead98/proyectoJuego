#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"

extern BOOLEAN canEnter;
extern INT16 player_x;
extern INT16 player_y;

void Start_SpriteUp(){
    
}
void Update_SpriteUp(){
    THIS->x = player_x +4;
    THIS->y = player_y - 13;
    if(canEnter == FALSE){
        SpriteManagerRemove(THIS_IDX);
    }
}
void Destroy_SpriteUp(){

}