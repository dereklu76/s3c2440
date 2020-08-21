#include "button.h"

void button_init(void)
{
	*pGPGCON &= GPGCON_KEY_MSK;
	*pGPGCON |= GPGCON_KEY_SET;
}

