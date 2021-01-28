#include "Banks/SetBank2.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Sound.h"
const UINT8 chain_anim1[] = {3, 0, 0, 0};
const UINT8 chain_anim2[] = {3, 1, 1, 1};
const UINT8 fireBall_anim[] = {2, 2, 3};
extern INT16 player_x;
extern INT16 player_y;
extern BOOLEAN canTransform;
extern INT8 player_state;
void WhipSound()
{

    if (THIS->anim_frame == 2)
    {
        PlayFx(CHANNEL_4, 10, 0x3d, 0xa1, 0x02, 0x80);
    }
}

struct chainCustomData
{
    INT16 accel_y;
    INT16 accel_x;
    BOOLEAN start;
    BOOLEAN dir;
    UINT8 counter;
    INT8 state;
};

void FireBallDirection(struct chainCustomData *data)
{

    if (SPRITE_GET_VMIRROR(THIS))
    {
        data->accel_x = -3;
    }
    else
    {
        data->accel_x = 3;
    }
}

void chainCollisionChange()
{
    if (THIS->anim_frame >= 2)
    {
        THIS->coll_x = 7;
        THIS->coll_y = 7;
        THIS->coll_w = 3;
        THIS->coll_h = 3;
    }
    else
    {
        THIS->coll_x = 0;
        THIS->coll_y = 6;
        THIS->coll_w = 16;
        THIS->coll_h = 2;
    }
}

void Start_SpriteChain()
{
    struct chainCustomData *data = (struct chainCustomData *)THIS->custom_data;
    data->start = TRUE;
    data->state = 0;
}

void Update_SpriteChain()
{
    struct chainCustomData *data = (struct chainCustomData *)THIS->custom_data;
    UINT8 i;
    struct Sprite *spr;
    SPRITE_SET_PALETTE(THIS, 0);
    
        WhipSound();
        if (SPRITE_GET_VMIRROR(THIS))
        {
            switch (data->state)
            {
            case 0:
                SetSpriteAnim(THIS, chain_anim1, 17);
                THIS->coll_x = 7;
                THIS->coll_y = 7;
                THIS->coll_w = 3;
                THIS->coll_h = 3;
                THIS->y = player_y - 5;
                THIS->x = player_x + 10;
                if (THIS->anim_frame == 2)
                {
                    data->state = 1;
                }

                break;
            case 1:
                SetSpriteAnim(THIS, chain_anim2, 17);
                THIS->coll_x = 0;
                THIS->coll_y = 6;
                THIS->coll_w = 16;
                THIS->coll_h = 2;
                THIS->y = player_y + 4;
                THIS->x = player_x - 13;
                break;
            }
        }
        else
        {
            switch (data->state)
            {
            case 0:
                SetSpriteAnim(THIS, chain_anim1, 17);
                THIS->coll_x = 7;
                THIS->coll_y = 7;
                THIS->coll_w = 3;
                THIS->coll_h = 3;
                THIS->y = player_y - 5;
                THIS->x = player_x - 10;
                if (THIS->anim_frame == 2)
                {
                    data->state = 1;
                }

                break;
            case 1:
                SetSpriteAnim(THIS, chain_anim2, 17);
                THIS->coll_x = 0;
                THIS->coll_y = 6;
                THIS->coll_w = 16;
                THIS->coll_h = 2;
                THIS->y = player_y + 4;
                THIS->x = player_x + 13;
                break;
            }
        }

        if ((data->state == 1 && THIS->anim_frame == 3) || player_state == 3 || player_state == 0 || player_state == 5 || player_state == 6)
        {
            SpriteManagerRemove(THIS_IDX);
        }
    
    
}

void Destroy_SpriteChain()
{
}