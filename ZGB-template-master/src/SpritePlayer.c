#include "Banks/SetBank6.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Sound.h"
#include "Print.h"
#include "Palette.h"
#include "hud.h"




const UINT8 p_anim_idle[] = {5,0,0,0,0,1};
const UINT8 p_anim_walk[] = {4,4,5,6,5};
const UINT8 p_anim_slide[] = {2,7,7};
const UINT8 p_anim_jump[] = {1,2};
const UINT8 p_anim_attack[] = {4,8,8,9,9}; // chain attack anim
const UINT8 p_anim_death[] = {4,12,13,13,13}; // death anim
const UINT8 p_anim_attack3[] = {3,8,9,9};// boleadora attack anim
const UINT8 p_anim_ladders[] = {2,10,10};
const UINT8 p_anim_hit[] = {4,11,11,11,11};
const UINT8 p_anim_fall[] = {1,3};

INT16 player_accel_y;
struct Sprite* sprite_player = 0;
struct Sprite* player_parent = 0;

UINT8 tile_collision;
INT8 player_state;

INT16 player_x,player_y;

BOOLEAN inmu;
UINT16 goCounter;
BOOLEAN canEnter;
BOOLEAN hit_dir; 
INT16 inmunity = 0;
extern UINT8 currentSubWeapon;
extern const UINT8 max_life;
INT8 current_life;

extern UINT8 energy;
extern UINT16 lives;
extern UINT8 current_level;
extern UINT8 last_level;
extern BOOLEAN gameOver;






void pHit(){
    if(inmunity == 0) {
			if(current_life <= 0) {
                if(lives>=1){
                    player_state = 9;
                    
                }else{
                    gameOver = TRUE;
                }
			} else {
                RefreshLife();
				SPRITE_SET_PALETTE(THIS, 1);
				inmunity = 100;
                inmu=TRUE;
			}
	}
}

void hit(BOOLEAN dir){
    SetSpriteAnim(THIS, p_anim_hit, 20);
    if(dir == FALSE){
        if(THIS->x > 0 ){
            TranslateSprite(THIS, -1, 0);
        }
        SPRITE_UNSET_VMIRROR(THIS);
    }else{
        if(THIS->x < (scroll_w-15)){
            TranslateSprite(THIS, 1, 0);
        }
        SPRITE_SET_VMIRROR(THIS);
    }
    if(THIS->anim_frame==3){
        player_state = 0;
		pHit();
    }
}

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

void colisiones(){
    UINT8 colision = GetScrollTile(((THIS->x + THIS->coll_x) + 4 ) >> 3, (THIS ->y + 15u) >> 3);
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
            if(lives>=1){
                SetState(current_state);
                lives--;
                current_life = max_life;
            }else{
                gameOver = TRUE;
            }
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
    UINT8 colision = GetScrollTile(((THIS->x + THIS->coll_x) + 4 ) >> 3, (THIS ->y - 15u) >> 3);
    playerCollisions();
    if(player_state == 4){
        SetSpriteAnim(THIS, p_anim_slide, 7);
        if(THIS->x > 1 && THIS->x < (scroll_w-15))
        if(SPRITE_GET_VMIRROR(THIS)){
            TranslateSprite(THIS,-2,0);
        }else{
            TranslateSprite(THIS,2,0);
        }        
        if(THIS->anim_frame == 1){
            player_state = 3;
            playerCollisions();
        }
    }
}

void attack(){
    
        struct Sprite* sprite_chain = SpriteManagerAdd(SpriteChain,THIS->x,THIS->y);
        sprite_chain->flags = THIS->flags;
    
}

void attack1(){
    struct Sprite* sprite_bumerang;
    switch(currentSubWeapon){
        case 3:
            sprite_bumerang = SpriteManagerAdd(SpriteShield,THIS->x ,THIS->y - 9);
        break;
        case 0:
             sprite_bumerang = SpriteManagerAdd(SpriteBoleadora,THIS->x,THIS->y);
        break;
        case 1:
             sprite_bumerang = SpriteManagerAdd(SpriteGuadana,THIS->x,THIS->y);
        break;
    }
    if(SPRITE_GET_VMIRROR(THIS)){
        sprite_bumerang->flags = 32;
    }else{
        sprite_bumerang->flags = 0;
    }
}

void PlayerMovement(){
    if(KEY_PRESSED(J_RIGHT) && THIS->x < (scroll_w-15)){
        TranslateSprite(THIS,1,0);
        if(player_state != 2){
            SPRITE_UNSET_VMIRROR(THIS);
        }
    }
    if(KEY_PRESSED(J_LEFT) && THIS->x > 0){
        TranslateSprite(THIS,-1,0);
        if(player_state != 2){
            SPRITE_SET_VMIRROR(THIS);
        }
    }
}

void ladders(){
    if(KEY_PRESSED(J_UP)) {
		UINT8 tile = GetScrollTile((THIS->x + THIS->coll_x) >> 3, (THIS ->y + 15u) >> 3);
	    if(tile == 126u ){
			THIS->x = ((THIS->x + THIS->coll_x)>> 3) << 3;
			player_accel_y = 0;
			player_state = 5;
		}
	}
	if(KEY_PRESSED(J_DOWN)) {
		UINT8 tile = GetScrollTile((THIS->x + THIS->coll_x) >> 3, (THIS ->y + 16u) >> 3);
		if(tile == 126u ){
			THIS->x = ((THIS->x + THIS->coll_x)>> 3) << 3;
			THIS->y = THIS->y + 1u;
			player_accel_y = 0;
			player_state = 5;
		}
	}
}

void Start_SpritePlayer() {
    OBP0_REG = PAL_DEF(2,0,1,3);
	OBP1_REG = PAL_DEF(0,0,0,0);
    inmu = FALSE;
    player_accel_y = 0;
    player_state = 3;
    sprite_player = THIS;
    playerCollisions();
    RefreshLife();
    refreshLives(lives);
    //RefreshWeapon1(weapon1);
    refreshEnergy(energy);
    canEnter = FALSE;
    inmunity = 0;
    goCounter = 0;
    
}

void Update_SpritePlayer() {
    UINT8 i;
    struct Sprite* spr;

    if(gameOver == FALSE){
        colisiones();
        /*
        if(KEY_TICKED(J_SELECT) && weapon1 == FALSE && player_state != 1 && player_state != 2){
            weapon1 = TRUE;
            RefreshWeapon1(weapon1);
            
        }else if(KEY_TICKED(J_SELECT) && weapon1 == TRUE  && player_state != 1 && player_state != 2){
            weapon1 = FALSE;
            RefreshWeapon1(weapon1);
        
        }
        */
    
       if(KEY_TICKED(J_SELECT) && currentSubWeapon == 0){
            
            currentSubWeapon++;
            PRINT_POS(17, 0);
            Printf(":%d", (UINT16)(currentSubWeapon));
            RefreshWeapon(currentSubWeapon);
       }else if(KEY_TICKED(J_SELECT) && currentSubWeapon == 1){
            
            currentSubWeapon = 0;
            PRINT_POS(17, 0);
            Printf(":%d", (UINT16)(currentSubWeapon));
            RefreshWeapon(currentSubWeapon);
       }
    
        // Chequea si esta sobre una puerta y se presiona "up", asi asignar el valor del level a cual se ira
        if(canEnter == TRUE && KEY_TICKED(J_UP)){
            if(current_level == 0){
                last_level = current_level;
                SetState(current_state); 
                current_level++;
                
            }else{
                last_level = current_level;
                SetState(current_state);
                if(THIS->x < 100){
                    current_level--;
                }else{
                    current_level++;
                }
                
            }
        }   

        if(current_level == 5 && THIS->x == scroll_w-15){
            current_level++;
            SetState(current_state);
        }
       
        //Estados del player
        switch(player_state){
            case 0://Quieto
                PlayerMovement();
                ladders();

                if(KEY_PRESSED(J_LEFT) || KEY_PRESSED(J_RIGHT)){  // Asigna la animacion de correr
                    SetSpriteAnim(THIS,p_anim_walk,9);

                }else{
                    SetSpriteAnim(THIS,p_anim_idle,4);
                }
            
                if(KEY_TICKED(J_A) && !KEY_PRESSED(J_DOWN)){ //salto
                    PlayFx(CHANNEL_1 , 10, 0x66, 0x80, 0xf1, 0x74,0x86);
                    jump();
                }
                if(KEY_PRESSED(J_DOWN) && KEY_TICKED(J_A) ){ //slide
                    player_state = 4;
                }
                if(KEY_TICKED(J_B) && !KEY_TICKED(J_A) && !KEY_PRESSED(J_UP)){ // main weapon attack idle
                    PlayFx(CHANNEL_4, 10, 0x3a, 0xa1, 0x00, 0xc0);
                    player_state = 1;
                    attack();
                    //SpriteManagerAdd(SpriteChain,THIS->x,THIS->y);
                }   
            
                if(KEY_TICKED(J_B) && KEY_TICKED(J_A) && !KEY_PRESSED(J_UP)){ // main weapon attack jumping
                    PlayFx(CHANNEL_4, 10, 0x3a, 0xa1, 0x00, 0xc0);
                    player_state = 2;
                    attack();
                }

                if(KEY_PRESSED(J_UP) && KEY_TICKED(J_B) && !KEY_TICKED(J_A)){ // sub weapon idle attack
                    if(energy != 0){
                        attack1();
                        energy--;
                        refreshEnergy(energy);
                        player_state = 7;
                    }
                }

                if(KEY_PRESSED(J_UP) && KEY_TICKED(J_B) && KEY_TICKED(J_A)){ // sub weapon idle attack
                    if(energy != 0){
                        attack1();
                        energy--;
                        refreshEnergy(energy);
                        player_state = 8;
                    }
                }
            
            break;
        
            case 1: // Ataque quieto del arma principal
                
                    SetSpriteAnim(THIS,p_anim_attack,15);
                
                    /* if(THIS->anim_frame >= 2){
                        player_accel_y = 0;
                        if(SPRITE_GET_VMIRROR(THIS)){
                            TranslateSprite(THIS,-2,0);
                        }else{
                            TranslateSprite(THIS,2,0);
                        }
                    } */
                
            
                if(THIS->anim_frame == 3){
                    if(player_state == 2){
                        player_state = 3;
                    }else if(player_state == 1){
                        player_state = 0;
                    }   
                }
            break;

            case 2: // Ataque saltando del arma principal
               
                    SetSpriteAnim(THIS,p_anim_attack,15);
                

                PlayerMovement();        
                if(THIS->anim_frame == 3){
                    if(player_state == 2){
                        player_state = 3;  
                    }   
                }
            
            break;

            case 3: // Saltando
                if(player_accel_y < 1){ // comprueba el momento en que desciende en el salto y le da su animacion
                    SetSpriteAnim(THIS, p_anim_jump, 15);
                }else{
                    SetSpriteAnim(THIS, p_anim_fall, 15);
                }
                if(player_accel_y < 0 && !KEY_PRESSED(J_A)){ //Si no se mantiene "A" se deja de saltar
                    player_accel_y = 0;
                }
                if(KEY_TICKED(J_B) && !KEY_PRESSED(J_UP)){ //Ataque de arma primaria saltando
                    PlayFx(CHANNEL_4, 10, 0x3a, 0xa1, 0x00, 0xc0);
                    attack();
                    player_state = 2;
                }
                if(KEY_PRESSED(J_UP) && KEY_TICKED(J_B)){ // Ataque de arma secundaria saltando
                    if(energy != 0){
                        attack1();
                        energy--;
                        refreshEnergy(energy);
                        player_state = 8;
                    }
                }
                PlayerMovement();// Permite el movimiento en el aire
                ladders();//permite el subir escaleras estando en el aire
            break;

            case 4: //Sliding
                slide();
            break;

            case 5://Subiendo/bajando escaleras
                i = 126;
                SetSpriteAnim(THIS,p_anim_ladders,12);
			    if(KEY_PRESSED(J_UP)) {
                    if(THIS->anim_frame == 1){
                        SPRITE_SET_VMIRROR(THIS);
                    }else{
                        SPRITE_UNSET_VMIRROR(THIS);
                    }
                
				    tile_collision = TranslateSprite(THIS, 0, -1 << delta_time);
			        CheckCollisionTile();
				    i = GetScrollTile((THIS->x + THIS->coll_x) >> 3, (THIS->y + 15u) >> 3);
			    } else if(KEY_PRESSED(J_DOWN)) {
                    if(THIS->anim_frame == 1){
                        SPRITE_SET_VMIRROR(THIS);
                    }else{
                        SPRITE_UNSET_VMIRROR(THIS);
                    }
              
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
                    //PlayFx(CHANNEL_1, 10, 0x66, 0x80, 0xf1, 0x74,86);
				    jump();
			    }
            break;


            case 6://Una vez se recibe un golpe 
                hit(hit_dir);
            break;
        

            case 7: //Subarma quieto
                SetSpriteAnim(THIS, p_anim_attack3, 15);
                if(THIS->anim_frame == 2){
                    if(player_state == 7){
                        player_state = 3;
                    }else if(player_state == 7){
                        player_state = 0;
                    }   
                }
            break;
            
            case 8: // Subarma Saltando
            SetSpriteAnim(THIS, p_anim_attack3, 15);
            PlayerMovement();        
                if(THIS->anim_frame == 2){
                    if(player_state == 8){
                        player_state = 3;  
                    }   
                }
            break;

            case 9: // death
            SetSpriteAnim(THIS, p_anim_death, 5);
            if(THIS->anim_frame == 3 ){
                SetState(current_state);
                current_life = max_life;
                lives--;
                

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

        SPRITEMANAGER_ITERATE(i, spr) {
        
		    if(spr->type != SpriteChain && spr->type != SpriteGuadana && spr->type != SpriteLand && spr->type != SpriteExplosion && spr->type != SpriteBumerang && 
            spr->type != SpriteBoleadora && spr->type != SpritePlayer && spr->type != SpriteUp && spr->type != SpriteBoss1Arm && spr->type != SpriteShield) {
			    if(CheckCollision(THIS, spr)) {
                    if(player_state != 6 && player_state != 9 && inmu == FALSE){
                        if(THIS->x < spr->x){
                            hit_dir = FALSE;
                        }else{
                            hit_dir = TRUE;
                        }
                        if(spr->type == SpriteStoneMan){
                            current_life = current_life - 2;
                        }else{
                            current_life--;
                        }
                        player_state = 6;
                    }
                }
		    }
            if(spr->type == SpriteBoss1Arm ){
                if(CheckCollision(THIS,spr)  && THIS->y > spr->y ){
                    if(player_state != 6 && player_state != 9 && inmu == FALSE){
                        if(THIS->x < spr->x){
                            hit_dir = FALSE;
                        }else{
                            hit_dir = TRUE;
                        }
                        current_life = current_life - 2;
                        player_state = 6;
                    }
                }else if(CheckCollision(THIS,spr) && player_accel_y > 15 ){         
                    if(THIS->y + 4 < spr->y){
                        THIS->y = spr->y-15;
                        player_accel_y = 15;
                        if(player_state == 3){
                            player_state= 0;
                        }   
                    }
                }
            }
            if(spr->type == SpriteLand ){
                if(CheckCollision(THIS,spr) && player_accel_y > 15 ){         
                    if(THIS->y + 4 < spr->y){
                        THIS->y = spr->y-15;
                        player_accel_y = 15;
                        if(player_state == 3){
                            player_state= 0;
                        }   
                    }
                }
            }
	    }



        if(inmunity != 0) {
		    inmunity -= (1 << delta_time);
            if((inmunity % 2 == 0)){
                SPRITE_SET_DMG_PALETTE(THIS, 1);
                SPRITE_SET_CGB_PALETTE(THIS, 7);
            }else{
                SPRITE_SET_CGB_PALETTE(THIS, 0);
                SPRITE_SET_DMG_PALETTE(THIS, 0);
            }      
		    if(inmunity < 1) {
			    inmunity = 0;
                inmu = FALSE;
                SPRITE_SET_CGB_PALETTE(THIS, 0);
			    SPRITE_SET_DMG_PALETTE(THIS, 0);
			
		    }
	    }
    }else{
        SetSpriteAnim(THIS, p_anim_hit, 15);
        
        if(goCounter <= 111){
            goCounter++;
            
            switch(goCounter){
                case 0:
                    
                    SPRITE_SET_CGB_PALETTE(THIS, 0);
                    
                break;
                case 50:
                    OBP1_REG = PAL_DEF(1,1,1,1);
                    SPRITE_SET_CGB_PALETTE(THIS, 1);
                    
                break;
                case 75:
                    OBP1_REG = PAL_DEF(2,2,2,2);
                    SPRITE_SET_CGB_PALETTE(THIS, 2);
                    
                break;
                case 100:
                    OBP1_REG = PAL_DEF(3,3,3,3);
                    SPRITE_SET_CGB_PALETTE(THIS, 3);
                    
                break;
                case 110:
                    SetState(StateGameOver);
                break;
            }
        }   
    }



}

void Destroy_SpritePlayer() {
    
}