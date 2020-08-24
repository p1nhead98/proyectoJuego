#ifndef ENERGY_H
#define ENERGY_H


#include <gb/gb.h>
#include "print.h"
void refreshEnergy(UINT8 energy){
    
    PRINT_POS(14, 1);
    Printf("%d", (UINT16)(energy));
    if(energy < 10){
        DPRINT(15,1," ");
    }
}

void refreshLives(UINT16 lives){
    const UINT8 LIVE_TILE = 99;
    set_win_tiles(16, 0, 1, 1, &LIVE_TILE);
    PRINT_POS(17, 0);
    Printf(":%d", (UINT16)(lives));
    if(lives < 10){
        DPRINT(19,1," ");
    }
}
void RefreshWeapon1(BOOLEAN weapon);


#endif