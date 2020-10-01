#ifndef ENERGY_H
#define ENERGY_H


#include <gb/gb.h>
#include "print.h"
void refreshEnergy(UINT8 energy){
    
    PRINT_POS(11, 1);
    Printf("%d", (UINT16)(energy));
    if(energy < 10){
        DPRINT(12,1," ");
    }
}

void refreshLives(UINT16 lives){
    const UINT8 LIVE_TILE = 99;
    set_win_tiles(16, 1, 1, 1, &LIVE_TILE);
    
    PRINT_POS(17, 1);
    Printf(":%d", (UINT16)(lives));
    if(lives < 10){
        DPRINT(19,2," ");
    }
}
void RefreshWeapon(INT8 weapon);


#endif