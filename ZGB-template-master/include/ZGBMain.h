#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateGame)\
_STATE(StateGameOver)\
_STATE(StateTitleScreen)\
_STATE(StateSplashScreen)\
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
_SPRITE_DMG(SpriteShooter, shooter)\
_SPRITE_DMG(SpriteEye, eye)\
_SPRITE_DMG(SpriteLand, land)\
_SPRITE_DMG(SpriteStoneMan, stoneman)\
_SPRITE_DMG(SpriteStone, stone)\
_SPRITE_DMG(SpriteGuadana, guadana)\
_SPRITE_DMG(SpriteBoleadora, grenade)\
_SPRITE_DMG(SpriteSkelBoss, skelboss)\
_SPRITE_DMG(SpriteBoss1Arm, boss1arm)\
_SPRITE_DMG(SpriteSparkBall, sparkball)\
_SPRITE_DMG(SpriteTitleFace, titleFace)\
_SPRITE_DMG(SpriteItems, items)\
_SPRITE_DMG(SpriteForestBossH, flyingHead)\
_SPRITE_DMG(SpriteTinyEye, eye2)\
_SPRITE_DMG(SpriteFallenLog, fallinLog)\
_SPRITE_DMG(SpriteSpitter, spitter)\
_SPRITE_DMG(SpriteSwingingLog, swingingLog)\
_SPRITE_DMG(SpriteMidBoss1, midBoss1)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif