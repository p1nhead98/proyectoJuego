#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateGame)\
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpritePlayer,player)\
_SPRITE_DMG(SpriteChain,chain)\
_SPRITE_DMG(SpriteSkeleton,skeleton)\
_SPRITE_DMG(SpriteGhost,ghost)\
_SPRITE_DMG(SpriteExplosion,explosion)\
_SPRITE_DMG(SpriteWoodSpider,woodspider)\
_SPRITE_DMG(SpriteViper,viper)\
_SPRITE_DMG(SpriteEnemyBullet,enemybullet)\
_SPRITE_DMG(SpriteWizzard,wizard)\
_SPRITE_DMG(SpriteTinyDevil,tinyDevil)\
_SPRITE_DMG(SpriteFlyingMen, flyingmen)\
_SPRITE_DMG(SpriteFireSkel, fireskel)\
_SPRITE_DMG(SpriteFlame, flame)\
_SPRITE_DMG(SpriteUp, up)\
_SPRITE_DMG(SpriteBumerang, bumerang)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif