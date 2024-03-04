#ifndef __INT_INTERFACE__
#define __INT_INTERFACE__
#include "Std_Types.h"
#include "BitMath.h"
#include "INT_private.h"
#include "INT_config.h"

typedef enum
{
    INT0_ = 0,
    INT1_,
    INT2_
} EXTINT_Source_t;

typedef enum
{
    RISING_EDGE = 0,
    FALLING_EDGE,
    LOW_LEVEL,
    ANY_CHANGE

} EXTINT_Sens_Ctrl_t;
void EXINT_voidEnable(EXTINT_Source_t copy_enumInterruptSrc, EXTINT_Sens_Ctrl_t copy_enumSenseCtrl);
void EXINT_voidSetCallBackINT1(void (*copy_pFunc)(void));
void EXINT_voidDisable(EXTINT_Source_t copy_enumInterruptSrc);

#endif