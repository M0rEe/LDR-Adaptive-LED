#ifndef __INT_INTERFACE__
#define __INT_INTERFACE__
#include "Std_Types.h"
#include "BitMath.h"
#include "INT_private.h"
#include "INT_config.h"
/**
 * @brief : Interrupt Source enum E.G. INT0 ..etc.
 */
typedef enum
{
    INT2_ = 5,
    INT0_,
    INT1_
} EXTINT_Source_t;


/**
 * @brief : Interrupt Source Activation enum E.G. Rigising edge,Falling edge ..etc.
 */
typedef enum
{
    LOW_LEVEL = 0,
    ANY_CHANGE,
    FALLING_EDGE,
    RISING_EDGE
} EXTINT_Sens_Ctrl_t;


/**
 * @return void
 * @param : copy_enumInterruptSrc     Interrupt Source
 * @param : copy_enumSenseCtrl        Interrupt Activation State
 * @brief : Configure Given Interrut To be activated upon given state
 */
void EXINT_voidEnable(EXTINT_Source_t copy_enumInterruptSrc, EXTINT_Sens_Ctrl_t copy_enumSenseCtrl);

/**
 * @return void
 * @param : copy_pFunc     Pointer to Call-Back function
 * @brief : Configure Given Interrut To perform  given Function From higher level
 */
void EXINT_voidSetCallBackINT0(void (*copy_pFunc)(void));
/**
 * @return void
 * @param : copy_pFunc     Pointer to Call-Back function
 * @brief : Configure Given Interrut To perform  given Function From higher level
 */
void EXINT_voidSetCallBackINT1(void (*copy_pFunc)(void));
/**
 * @return void
 * @param : copy_pFunc     Pointer to Call-Back function
 * @brief : Configure Given Interrut To perform  given Function From higher level
 */
void EXINT_voidSetCallBackINT2(void (*copy_pFunc)(void));
/**
 * @return void
 * @param : copy_enumInterruptSrc     Interrupt Source
 * @brief : Disable Given Interrut
 */
void EXINT_voidDisable(EXTINT_Source_t copy_enumInterruptSrc);

#endif