#include "Banks/SetBank7.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"
#include "Scroll.h"

void faceTiles(){
    DrawFrame(FRAME_8x16, THIS->first_tile, THIS->x - scroll_x , THIS->y - scroll_y , THIS->flags); 
    DrawFrame(FRAME_8x16, THIS->first_tile +2 , THIS->x - scroll_x + 8 , THIS->y - scroll_y , THIS->flags);  
    DrawFrame(FRAME_8x16, THIS->first_tile +4 , THIS->x - scroll_x + 16 , THIS->y - scroll_y + 8 , THIS->flags);
    DrawFrame(FRAME_8x16, THIS->first_tile +6 , THIS->x - scroll_x + 24 , THIS->y - scroll_y  , THIS->flags);
    DrawFrame(FRAME_8x16, THIS->first_tile +8 , THIS->x - scroll_x + 32 , THIS->y - scroll_y  , THIS->flags);
    DrawFrame(FRAME_8x16, THIS->first_tile +10 , THIS->x - scroll_x + 40 , THIS->y - scroll_y  , THIS->flags);
    DrawFrame(FRAME_8x16, THIS->first_tile +12 , THIS->x - scroll_x  , THIS->y - scroll_y + 16 , THIS->flags);
    DrawFrame(FRAME_8x16, THIS->first_tile +14 , THIS->x - scroll_x + 8 , THIS->y - scroll_y + 16 , THIS->flags);
    DrawFrame(FRAME_8x16, THIS->first_tile +16 , THIS->x - scroll_x + 24 , THIS->y - scroll_y + 16 , THIS->flags);
    DrawFrame(FRAME_8x16, THIS->first_tile +18 , THIS->x - scroll_x + 32 , THIS->y - scroll_y + 16 , THIS->flags);
    DrawFrame(FRAME_8x16, THIS->first_tile +20 , THIS->x - scroll_x   , THIS->y - scroll_y + 8 , 17);
    DrawFrame(FRAME_8x16, THIS->first_tile +22 , THIS->x - scroll_x + 8 , THIS->y - scroll_y + 8, 17);
    DrawFrame(FRAME_8x16, THIS->first_tile +24 , THIS->x - scroll_x + 24 , THIS->y - scroll_y + 8, 17);
    DrawFrame(FRAME_8x16, THIS->first_tile +26 , THIS->x - scroll_x + 32 , THIS->y - scroll_y + 8, 17);
    DrawFrame(FRAME_8x16, THIS->first_tile +28 , THIS->x - scroll_x  , THIS->y - scroll_y + 24 , 18);
    DrawFrame(FRAME_8x16, THIS->first_tile +30 , THIS->x - scroll_x +32 , THIS->y - scroll_y + 24 , 18);
    
}


void Start_SpriteTitleFace(){
   
    faceTiles();

}

void Update_SpriteTitleFace(){
  
    faceTiles();
           
}

void Destroy_SpriteTitleFace(){

}