#pragma bank 2
#include <gb/gb.h>
#include "MapInfo.h"
#include "..\res\src\town1_1.h"
#include "..\res\src\town1_2.h"
#include "..\res\src\town1_3.h"
#include "..\res\src\town1_4.h"
#include "..\res\src\town1_5.h"
#include "..\res\src\house1_1.h"
#include "..\res\src\house1_2.h"
#include "..\res\src\house1_3.h"
#include "..\res\src\forest1_1.h"
#include "..\res\src\forest1_2.h"
#include "..\res\src\forest1_3.h"
const struct MapInfo* levels[] = {
    &town1_1,
    &house1_1,
    &town1_2,
    &house1_2,
    &house1_3,
    &town1_3,
    &town1_5,
    &town1_4,
};

// const struct MapInfo* ForestLevels[] = {
//     &forest1_1,
//     &forest1_2,
//     &forest1_3,
// };

UINT8 current_level = 0;
UINT8 last_level = 0;
const UINT8 num_levels = 4;
UINT8 last_state;
UINT8 etapa = 0;
BOOLEAN gameOver;