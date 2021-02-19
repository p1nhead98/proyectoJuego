#include "Banks/SetBank8.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Math.h"
#include "Sound.h"
#include "hud.h"
#include "effects.h"

const UINT8 mBoss_start[] = {2, 10, 10};
const UINT8 mBoss_start2[] = {3, 11, 11, 11};
const UINT8 mBoss_stand[] = {2, 0, 0};
const UINT8 mBoss_charging[] = {20, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
const UINT8 mBoss_attacking[] = {1, 4};
const UINT8 mBoss_jumping[] = {2, 6, 6};
const UINT8 mBoss_stomp[] = {1, 8};
const UINT8 mBoss_charging2[] = {20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

extern INT16 player_x;
extern INT16 player_y;

struct Sprite *mb1_parent = 0;
UINT8 tile_collisionmb1;

struct mBoss1CustomData
{
  INT16 count;
  INT16 accel_y;
  INT16 accel_x;
  INT8 state;
  BOOLEAN fall;
};

void mirrorMb()
{
  if (THIS->x < player_x)
  {
    SPRITE_UNSET_VMIRROR(THIS);
  }
  else
  {
    SPRITE_SET_VMIRROR(THIS);
  }
}

void mb1Jump(struct mBoss1CustomData *data, INT16 accelY, INT8 state)
{
  data->accel_y = -accelY;
  data->state = state;
}

void Start_SpriteMidBoss1()
{
  struct mBoss1CustomData *data = (struct mBoss1CustomData *)THIS->custom_data;
  THIS->size = FRAME_16x16;
  SetSpriteAnim(THIS, mBoss_start, 2);
  data->state = 0;
  data->accel_y = 0;
  THIS->y = THIS->y + 1;
  
}
void Update_SpriteMidBoss1()
{
  struct mBoss1CustomData *data = (struct mBoss1CustomData *)THIS->custom_data;
  switch (data->state)
  {
  case 0:
  if (THIS->x < player_x)
  {
    SPRITE_UNSET_VMIRROR(THIS);
  }
  else
  {
    SPRITE_SET_VMIRROR(THIS);
  }
    data->accel_y = 0;
    if (THIS->anim_frame == 1)
    {
      mb1Jump(data, 90, 1);
    }
    break;
  case 1:
    SetSpriteAnim(THIS, mBoss_start2, 2);
    if (!(data->accel_y < 1))
    {

      data->state = 2;
    }
    break;
  case 2:
    THIS->size = FRAME_32x16;
    SPRITE_SET_CGB_PALETTE(THIS, 2);
    data->accel_y = 0;
    SetSpriteAnim(THIS, mBoss_start2, 1);
    if (THIS->anim_frame == 2)
    {
      data->state = 7;
    }
    break;
  case 3:
    SetSpriteAnim(THIS, mBoss_stand, 2);
    data->accel_y = 0;

    if (THIS->x < player_x)
    {
      SPRITE_UNSET_VMIRROR(THIS);
    }
    else
    {
      SPRITE_SET_VMIRROR(THIS);
    }
    if (THIS->anim_frame == 1)
    {
      data->state = 4;
    }
    break;
  case 4:
    SetSpriteAnim(THIS, mBoss_charging, 18);
    data->accel_y = 0;
    if (THIS->anim_frame % 2 == 0)
    {
      SPRITE_SET_DMG_PALETTE(THIS, 1);
      SPRITE_SET_CGB_PALETTE(THIS, 7);
    }
    else
    {
      SPRITE_SET_DMG_PALETTE(THIS, 0);
      SPRITE_SET_CGB_PALETTE(THIS, 2);
    }
    if (THIS->anim_frame == 9)
    {
      mb1Jump(data, 120, 5);
    }
    break;
  case 5:
    SetSpriteAnim(THIS, mBoss_jumping, 2);
    if (!(data->accel_y < 1))
    {
      data->state = 6;
    }
    break;
  case 6:
    SetSpriteAnim(THIS, mBoss_jumping, 2);
    data->accel_y = 0;
    THIS->x = player_x;
    if (THIS->anim_frame == 1)
    {
      data->state = 7;
    }
    break;
  case 7:

    SetSpriteAnim(THIS, mBoss_stomp, 1);
    if (TranslateSprite(THIS, 0, (data->accel_y >> 4)))
    {
      data->state = 8;
    }
    break;
  case 8:
    SetSpriteAnim(THIS, mBoss_charging, 15);

    if (THIS->anim_frame == 9)
    {
      data->state = 9;
    }
    break;
  case 9:
    SetSpriteAnim(THIS, mBoss_stand, 2);
    if (THIS->x < player_x)
    {
      SPRITE_UNSET_VMIRROR(THIS);
    }
    else
    {
      SPRITE_SET_VMIRROR(THIS);
    }
    if (THIS->anim_frame == 1)
    {
      data->state = 10;
    }
    break;
  case 10:
    SetSpriteAnim(THIS, mBoss_charging2, 18);
    data->accel_x = 0;
    if (THIS->anim_frame % 2 == 0)
    {
      SPRITE_SET_DMG_PALETTE(THIS, 1);
      SPRITE_SET_CGB_PALETTE(THIS, 7);
    }
    else
    {
      SPRITE_SET_DMG_PALETTE(THIS, 0);
      SPRITE_SET_CGB_PALETTE(THIS, 2);
    }
    if (THIS->anim_frame == 9)
    {
      data->state = 11;
    }
    break;
  case 11:
    SetSpriteAnim(THIS, mBoss_attacking, 1);
    if (SPRITE_GET_VMIRROR(THIS))
    {
      if (data->accel_x > -93)
      {
        data->accel_x = data->accel_x - 3;
      }

      if (THIS->x > 6)
      {
        TranslateSprite(THIS, (data->accel_x >> 4), 0);
      }
      else
      {
        ScreenShake(6);
        data->state = 3;
      }
    }
    else
    {
      if (data->accel_x < 93)
      {
        data->accel_x = data->accel_x + 3;
      }
      if (TranslateSprite(THIS, (data->accel_x >> 4), 0))
      {
        ScreenShake(6);
        data->state = 3;
      }
      else if (!scroll_collisions[GetScrollTile(((THIS->x + THIS->coll_x + THIS->coll_w) >> 3), (THIS->y >> 3) + 2u)] && !scroll_collisions_down[GetScrollTile(((THIS->x + THIS->coll_x + THIS->coll_w) >> 3), (THIS->y >> 3) + 2u)])
      {
        ScreenShake(6);
        data->state = 3;
      }
    }

    break;
  }

  if (mb1_parent == 0)
  {
    if (data->accel_y < 60)
    {
      data->accel_y += 4;
    }
    tile_collisionmb1 = TranslateSprite(THIS, 0, (data->accel_y >> (4 << delta_time)));
    if (!tile_collisionmb1 && delta_time != 0 && data->accel_y < 40)
    { //Do another iteration if there is no collision
      data->accel_y += 4 >> delta_time;

      tile_collisionmb1 = TranslateSprite(THIS, 0, (data->accel_y >> 4));
    }
    if (tile_collisionmb1 && !TranslateSprite(THIS, 0, (data->accel_y >> (-4 << delta_time))))
    {

      data->accel_y = 0;

      if (data->state == 5)
      {
        data->state = 3;
      }
      if (data->state == 7)
      {
        ScreenShake(6);

        data->state = 8;
      }

      //CheckCollisionTile();
    }
  }
}
void Destroy_SpriteMidBoss1()
{
}