#include "Banks/SetBank8.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Math.h"
#include "Sound.h"
#include "hud.h"
const UINT8 spitter_anim[] = {15, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0};
struct SpitterCustomData
{
    BOOLEAN canShoot;
    INT8 counter;
};


extern INT16 player_x;
extern BOOLEAN gameOver;

void SpitterShoot(struct SpitterCustomData *data)
{
    if (data->canShoot == TRUE)
    {
        PlayFx(CHANNEL_4, 8, 0x24, 0xa2, 0x70, 0x80);
        struct Sprite *sprite_ebullet1 = SpriteManagerAdd(SpriteEnemyBullet, THIS->x, THIS->y);
        sprite_ebullet1->flags = THIS->flags;
        sprite_ebullet1->unique_id = 4;
        data->canShoot = FALSE;
    }
}
void Start_SpriteSpitter()
{
    struct SpitterCustomData *data = (struct SpitterCustomData *)THIS->custom_data;
    SetSpriteAnim(THIS, spitter_anim, 15);
    THIS->coll_x = 4;
    THIS->coll_y = 4;
    THIS->coll_w = 7;
    THIS->coll_h = 14;
    data->canShoot = TRUE;
}
void Update_SpriteSpitter()
{
    struct SpitterCustomData *data = (struct SpitterCustomData *)THIS->custom_data;
    UINT8 i;
    struct Sprite *spr;
    if (gameOver == TRUE)
    {
        SPRITE_SET_CGB_PALETTE(THIS, 0);
        SPRITE_SET_DMG_PALETTE(THIS, 0);
    }

    if (THIS->x < player_x)
    {
        SPRITE_UNSET_VMIRROR(THIS);
    }
    else if (THIS->x > player_x)
    {
        SPRITE_SET_VMIRROR(THIS);
        THIS->x - 2;
    }

    if (THIS->anim_frame == 6)
    {
        SpitterShoot(data);
    }
    if (THIS->anim_frame == 0)
    {
        data->canShoot = TRUE;
    }

    SPRITEMANAGER_ITERATE(i, spr)
    {
        if (spr->type == SpriteChain || spr->type == SpriteBumerang || spr->type == SpriteGuadana)
        {
            if (CheckCollision(THIS, spr))
            {

                //SkelDeathSound();
                SpriteManagerRemove(THIS_IDX);
                if (spr->type == SpriteChain)
                {
                    
                }
                
                SpriteManagerAdd(SpriteExplosion, THIS->x, THIS->y);
            }
        }
    }
}
void Destroy_SpriteSpitter()
{
}
