#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Sound.h"

const UINT8 p_anim_walk[] = {4,1,2,1,3};
const UINT8 p_anim_idle[] = {1,0};
const UINT8 p_anim_slide[] = {1,4};
const UINT8 p_anim_jump[] = {1,5};
const UINT8 p_anim_attack[] = {4,6,6,7,7};
const UINT8 p_anim_ladders[] = {1,8};

BOOLEAN canfall;
INT16 player_accel_y;
struct Sprite* sprite_player = 0;
struct Sprite* player_parent = 0;
UINT8 tile_collision;
INT8 player_state;
INT8 SlideCount;
INT16 player_x,player_y;
INT8 mirrorCount1 = 0;
BOOLEAN fall;
BOOLEAN canEnter;

extern UINT8 current_level;
extern UINT8 last_level;

void playerCollisions(){
        if(player_state == 4){
            THIS->coll_x = 3;
            THIS->coll_y = 8;
            THIS->coll_w = 10;
            THIS->coll_h = 8;
        }else{
            THIS->coll_x = 3;
            THIS->coll_y = 1;
            THIS->coll_w = 10;
            THIS->coll_h = 15;
        }
        
}

void CheckCollisionTile() {
	switch(tile_collision) {
		case 25u:
			// SET_BIT(stage_completion, current_stage);
			//SetState(STATE_VICTORY);
			break;
	}
}

void mirrorPlayer1(){
      
    if(KEY_PRESSED(J_UP) || KEY_PRESSED(J_DOWN)){
    if(mirrorCount1 <=30){
        mirrorCount1++;
        switch(mirrorCount1){
            case 1: SPRITE_SET_VMIRROR(THIS); break;
            case 15: SPRITE_UNSET_VMIRROR(THIS);  break;
            case 30: mirrorCount1 = 0; break;

        }
    }
    }
}

void colisiones(){
    UINT8 colision = GetScrollTile((THIS->x + THIS->coll_x) >> 3, (THIS ->y + 15u) >> 3);
    switch(colision){
        case 125u:
            if(THIS->x > 150){
                THIS->x = 8;
            }else{
                THIS->x = 184;
            }
            break;
        case 123u: 
            if(canEnter == FALSE){
                canEnter = TRUE;
                SpriteManagerAdd(SpriteUp, THIS->x, THIS->y-8);
            } 
            break;
        case 124u:
            fall =TRUE;
            break;
    }
    if(colision != 123u && canEnter == TRUE){
        canEnter = FALSE;
    }
}

void jump(){
    if(player_state == 0 || player_state == 5){
        player_accel_y = -60;
        player_state = 3;
        player_parent = 0;
    }
}

void slide(){
    playerCollisions();
    if(SlideCount <= 15 && player_state == 4){
        SetSpriteAnim(THIS, p_anim_slide, 15);
        if(SPRITE_GET_VMIRROR(THIS)){
            TranslateSprite(THIS,-2,0);
        }else{
            TranslateSprite(THIS,2,0);
        }
        SlideCount++;
        if(SlideCount == 15){
            player_state = 0;
            SlideCount = 0;
            playerCollisions();
        }
    }
        
    
}

void attack(){
    struct Sprite* sprite_chain = SpriteManagerAdd(SpriteChain,THIS->x,THIS->y);
    sprite_chain->flags = THIS->flags;
}

void PlayerMovement(){
   
    if(KEY_PRESSED(J_RIGHT)){
        TranslateSprite(THIS,1,0);
        if(player_state != 2){
        SPRITE_UNSET_VMIRROR(THIS);
        }
    }
    if(KEY_PRESSED(J_LEFT)){
        TranslateSprite(THIS,-1,0);
        if(player_state != 2){
        SPRITE_SET_VMIRROR(THIS);
        }
    }
 
}

void ladders(){
if(KEY_PRESSED(J_UP)) {
		UINT8 tile = GetScrollTile((THIS->x + THIS->coll_x) >> 3, (THIS ->y + 15u) >> 3);
		if(tile == 126u )
		{
			THIS->x = ((THIS->x + THIS->coll_x)>> 3) << 3;
			player_accel_y = 0;
			player_state = 5;
		}
	}
	if(KEY_PRESSED(J_DOWN)) {
		UINT8 tile = GetScrollTile((THIS->x + THIS->coll_x) >> 3, (THIS ->y + 16u) >> 3);
		if(tile == 126u )
		{
			THIS->x = ((THIS->x + THIS->coll_x)>> 3) << 3;
			THIS->y = THIS->y + 1u;
			player_accel_y = 0;
			player_state = 5;
		}
	}
}

void Start_SpritePlayer() {
    SlideCount = 0;
    canfall = FALSE;
    player_accel_y = 0;
    player_state = 3;
    mirrorCount1 = 0;
    sprite_player = THIS;
    fall = FALSE;
    playerCollisions();
    canEnter = FALSE;
}

void Update_SpritePlayer() {
    UINT8 i;
    colisiones();
    if(fall == TRUE && player_state != 5){
        THIS->y+=player_accel_y;
        SetSpriteAnim(THIS, p_anim_jump, 15);
    }
    
  


    if(canEnter == TRUE && KEY_TICKED(J_UP)){
        switch(current_level){
            case 0:
                last_level = current_level;
                current_level++;
                SetState(current_state);
                break;
            case 1:
                last_level = current_level;
                if(THIS->y < 150){
                    current_level++;
                }else{
                    current_level--;
                }
                SetState(current_state);
                break;

        }    
    }


    switch(player_state){
        case 0://Idle

            PlayerMovement();
            ladders();
            
        
            if(KEY_PRESSED(J_LEFT) || KEY_PRESSED(J_RIGHT)){
                SetSpriteAnim(THIS,p_anim_walk,9);
            }else{
                SetSpriteAnim(THIS,p_anim_idle,15);
            }
            
            if(KEY_TICKED(J_A) && !KEY_PRESSED(J_DOWN)){
                PlayFx(CHANNEL_1 , 10, 0x66, 0x80, 0xf1, 0x74,0x86);
                jump();
            }
            if(KEY_PRESSED(J_DOWN) && KEY_TICKED(J_A) ){
                player_state = 4;
            }
            if(KEY_TICKED(J_B) && !KEY_TICKED(J_A)){
                PlayFx(CHANNEL_4, 10, 0x3a, 0xa1, 0x00, 0xc0);
                player_state = 1;
                attack();
                //SpriteManagerAdd(SpriteChain,THIS->x,THIS->y);
            }
            
            if(KEY_TICKED(J_B) && KEY_TICKED(J_A)){
                PlayFx(CHANNEL_4, 10, 0x3a, 0xa1, 0x00, 0xc0);
                player_state = 2;
                attack();
            }
            
            break;
        
        case 1:
            SetSpriteAnim(THIS,p_anim_attack,15);
                if(THIS->anim_frame == 3){
                    if(player_state == 2){
                    player_state = 3;
                }else if(player_state == 1){
                    player_state = 0;
                    }   
                }
            break;
        case 2:
             SetSpriteAnim(THIS,p_anim_attack,15);
                if(THIS->anim_frame == 3){
                    if(player_state == 2){
                    player_state = 3;
                }   
                }
              
                    PlayerMovement();        
                
            
            break;

        case 3://Jumping
            SetSpriteAnim(THIS, p_anim_jump, 15);
            if(player_accel_y < 0 && !KEY_PRESSED(J_A)){
                player_accel_y = 0;
            }
            if(KEY_TICKED(J_B)){
                PlayFx(CHANNEL_4, 10, 0x3a, 0xa1, 0x00, 0xc0);
                attack();
                player_state = 2;
            }
            PlayerMovement();
            ladders();
            break;
        case 4: //Sliding
            slide();
            break;

        case 5://ladders
            i = 126;
            SetSpriteAnim(THIS,p_anim_ladders,1);
			if(KEY_PRESSED(J_UP)) {
                mirrorPlayer1();
				tile_collision = TranslateSprite(THIS, 0, -1 << delta_time);
				CheckCollisionTile();
				i = GetScrollTile((THIS->x + THIS->coll_x) >> 3, (THIS->y + 15u) >> 3);
			} else if(KEY_PRESSED(J_DOWN)) {
                mirrorPlayer1();
				tile_collision = TranslateSprite(THIS, 0, 1 << delta_time);
				CheckCollisionTile();
				i = GetScrollTile((THIS->x + THIS->coll_x) >> 3, (THIS->y + 16u) >> 3);
			} else {
				SetSpriteAnim(THIS,p_anim_ladders,1);
			}
			/* if(KEY_PRESSED(J_RIGHT)) {
				SPRITE_UNSET_VMIRROR(THIS);
			} else if(KEY_PRESSED(J_LEFT)) {
				SPRITE_SET_VMIRROR(THIS);
			} */

			//Check the end of the ladder
			if(i != 126u && i != 1u && i != 2u)
			{
				//TranslateSprite(THIS, 0, 1 << delta_time);
				player_state = 3;
			}

			//Check jumping
			if(KEY_TICKED(J_A)) {
                PlayFx(CHANNEL_1, 10, 0x66, 0x80, 0xf1, 0x74,86);
				jump();
			}
            break;
        
    }




        if(player_parent == 0 && player_state != 5){
		if(player_accel_y < 60  ) {
			player_accel_y += 4;
            //SetSpriteAnim(THIS, p_anim_jump,15);
           
		}
		tile_collision = TranslateSprite(THIS, 0, (player_accel_y >> (4 << delta_time)));
		if(!tile_collision && delta_time != 0 && player_accel_y < 40 && player_state != 5 ) { //Do another iteration if there is no collision
			player_accel_y += 4 >> delta_time;
            
			tile_collision = TranslateSprite(THIS, 0, (player_accel_y >> 4));
		}
		if(tile_collision && !TranslateSprite(THIS,0,(player_accel_y >> (-4 << delta_time)))) {
              
			
				player_accel_y = 0;
               
                  if( player_state == 3 || player_state == 2){
                        player_state = 0;
                  }
                    
                
			
			

			 CheckCollisionTile();
		}
        if(player_state == 0 && player_accel_y == 20){
            player_state = 3;
        }
        }
        if(player_parent && player_state == 3 ){
                        player_accel_y = 0;
                        player_state = 0;
                  }

    player_x = THIS->x;
    player_y = THIS->y;
    
}

void Destroy_SpritePlayer() {
    sprite_player = 0 ;
    SetState(current_state);
}