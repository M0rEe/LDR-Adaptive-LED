#ifndef __KEYPAD_INTERFACE__
#define __KEYPAD_INTERFACE__

#include "KEYPAD_private.h"
#include "KEYPAD_config.h"


u8 KEYPAD_u8GetChar(u8 *copy_pu8CharPressed, u8 *copy_pu8KeypadMatrix);

#endif