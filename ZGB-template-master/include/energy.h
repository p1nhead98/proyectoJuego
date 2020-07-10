#ifndef ENERGY_H
#define ENERGY_H

#include "Print.h"

void refreshEnergy(UINT8 energy){
    
    PRINT_POS(15, 1);
    Printf("P:%d", (UINT16)(energy));
    if(energy < 10){
        DPRINT(18,1," ");
    }
}



#endif