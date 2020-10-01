#include "..\res\src\sky1.h"
#include "..\res\src\sky2.h"
#include "..\res\src\wateranim.h"
#include <string.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Keys.h"
#include "SpriteManager.h"
#include <BankManager.h>


void AnimateTiles_stage1();

void SetAnimTilesInt() {
    
	disable_interrupts();
	add_VBL(AnimateTiles_stage1);
	enable_interrupts();
}

void AnimateTiles_stage1() {
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