#include "..\res\src\sky1.h"
#include "..\res\src\sky2.h"
#include "..\res\src\wateranim.h"
#include "..\res\src\player.h"
#include "..\res\src\player2.h"
#include "..\res\src\transform.h"
#include <string.h>
#include "effects.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Keys.h"
#include "SpriteManager.h"
#include <BankManager.h>

void AnimateTiles_stage1();

void SetAnimTilesInt()
{

	disable_interrupts();
	add_VBL(AnimateTiles_stage1);
	enable_interrupts();
}

void AnimateTiles_stage1()
{
	extern UINT8 x;
	extern UINT8 x2;
	unsigned char tileData[16];

	PUSH_BANK(sky1.bank);

	memcpy(tileData, &sky1.data->data[16 * (x % 16)], 16);
	set_bkg_data(21, 1, tileData);
	POP_BANK;

	PUSH_BANK(sky2.bank);
	memcpy(tileData, &sky2.data->data[16 * (x % 16)], 16);
	set_bkg_data(27, 1, tileData);
	POP_BANK;

	PUSH_BANK(wateranim.bank);
	memcpy(tileData, &wateranim.data->data[16 * (x2 % 8)], 16);
	set_bkg_data(37, 1, tileData);
	POP_BANK;
}

void ScreenShake(INT8 x)
{
	scroll_x = scroll_x + x;
}

void TransformPlayer()
{
	extern BOOLEAN canTransform;
	if (canTransform == TRUE)
	{
		PUSH_BANK(player2.bank)
		set_sprite_data(0, 48, &player2.data->data[0]);
		POP_BANK;
	}
	else if (canTransform == FALSE)
	{
		PUSH_BANK(player.bank)
		set_sprite_data(0, 48, &player.data->data[0]);
		POP_BANK;
	}
}

void Transforming()
{
	PUSH_BANK(transform.bank);
	set_sprite_data(0, 16, &transform.data->data[0]);
	POP_BANK;
}