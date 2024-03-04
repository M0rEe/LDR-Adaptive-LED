#include "INT_interface.h"


void EXINT_voidEnable(EXTINT_Source_t copy_enumInterruptSrc, EXTINT_Sens_Ctrl_t copy_enumSenseCtrl)
{

    switch (copy_enumInterruptSrc)
    {
    case INT0_:
        switch (copy_enumSenseCtrl)
        {
        case FALLING_EDGE:
            Set_Bit(MCUCR, ISC01);
            Clr_Bit(MCUCR, ISC00);
            break;

        case RISING_EDGE:
            Set_Bit(MCUCR, ISC01);
            Set_Bit(MCUCR, ISC00);
            break;

        case ANY_CHANGE:
            Clr_Bit(MCUCR, ISC01);
            Set_Bit(MCUCR, ISC00);
            break;

        case LOW_LEVEL:
            Clr_Bit(MCUCR, ISC01);
            Clr_Bit(MCUCR, ISC00);
            break;

        default:
            break;
        }
        Set_Bit(GICR, INT0);
        break;

    case INT1_:
        switch (copy_enumSenseCtrl)
        {
        case FALLING_EDGE:
            Clr_Bit(MCUCR, ISC10);
            Set_Bit(MCUCR, ISC11);
            break;

        case RISING_EDGE:
            Set_Bit(MCUCR, ISC10);
            Set_Bit(MCUCR, ISC11);
            break;

        case ANY_CHANGE:
            Set_Bit(MCUCR, ISC10);
            Clr_Bit(MCUCR, ISC11);
            break;

        case LOW_LEVEL:
            Clr_Bit(MCUCR, ISC10);
            Clr_Bit(MCUCR, ISC11);
            break;
        }
        Set_Bit(GICR, INT1);
        break;

    case INT2_:
        switch (copy_enumSenseCtrl)
        {
        case FALLING_EDGE:
            Clr_Bit(MCUCSR, ISC2);
            break;

        case RISING_EDGE:
            Set_Bit(MCUCSR, ISC2);
            break;
        default:
            break;
        }
        Set_Bit(GICR, INT2);
        break;
    }
}

void EXINT_voidDisable(EXTINT_Source_t copy_enumInterruptSrc)
{
    switch (copy_enumInterruptSrc)
    {
    case INT0_:
        Clr_Bit(GICR, INT0);
        break;

    case INT1_:
        Clr_Bit(GICR, INT1);
        break;

    case INT2_:
        Clr_Bit(GICR, INT2);
        break;
    }
}
static void (*PRV_pCallBack_INT1)(void)  = NULL;
void EXINT_voidSetCallBackINT1(void (*copy_pFunc)(void))
{
    if (copy_pFunc)
    {
        PRV_pCallBack_INT1 = copy_pFunc;
    }
    else
    {
        // Error
    }
}

ISR(INT1_vect)
{
    PRV_pCallBack_INT1();
}