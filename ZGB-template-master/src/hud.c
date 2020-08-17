#include "hud.h"
#include "Banks/SetBank6.h"
#include "print.h"




void RefreshWeapon1(BOOLEAN weapon){
    const UINT8 W1_1 = 100;
    const UINT8 W1_2 = 101;
    const UINT8 W1_3 = 102;
    const UINT8 W1_4 = 103;

    const UINT8 W2_1 = 104;
    const UINT8 W2_2 = 105;
    const UINT8 W2_3 = 106;
    const UINT8 W2_4 = 107;
    if(weapon == FALSE){
        set_win_tiles(9, 0, 1, 1, &W1_1);
        set_win_tiles(9, 1, 1, 1, &W1_2);
        set_win_tiles(10, 0, 1, 1, &W1_3);
        set_win_tiles(10, 1, 1, 1, &W1_4);
    }else{
        set_win_tiles(9, 0, 1, 1, &W2_1);
        set_win_tiles(9, 1, 1, 1, &W2_2);
        set_win_tiles(10, 0, 1, 1, &W2_3);
        set_win_tiles(10, 1, 1, 1, &W2_4);
    }
}