#pragma bank 2
#include <gb/gb.h>
#include "MapInfo.h"
#include "..\res\src\town1_1.h"
#include "..\res\src\house1_1.h"

const struct MapInfo* levels[] = {
    &town1_1,
    &house1_1,
    
};

UINT8 current_level = 0;
UINT8 last_level = 0;
const UINT8 num_levels = 3;