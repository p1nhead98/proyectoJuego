#include "Banks/SetBank9.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Sound.h"
#include "Print.h"
#include "Palette.h"
#include "hud.h"

const UINT8 swinging_log[] = {10, 0,0,2,4,6,8,8,6,4,2};

void Start_SpriteSwingingLog()
{
    THIS->size = FRAME_32x16;
    SetSpriteAnim(THIS,swinging_log,7);
}

void Update_SpriteSwingingLog()
{
}

void Destroy_SpriteSwingingLog()
{
}