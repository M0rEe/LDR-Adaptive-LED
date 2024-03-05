#include "INT_interface.h"


/**
 * @return void
 * @param : copy_enumInterruptSrc     Interrupt Source
 * @param : copy_enumSenseCtrl        Interrupt Activation State
 * @brief : Configure Given Interrut To be activated upon given state
 */
void EXINT_voidEnable(EXTINT_Source_t copy_enumInterruptSrc, EXTINT_Sens_Ctrl_t copy_enumSenseCtrl)
{

    switch (copy_enumInterruptSrc)
    {
    case INT0_:
        //* Configure Interrupt Activate State
        /*
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
            insted of switch it's better to use
            2 line of code setting 2 bits to zeros then apply its value
        */

        MCUCR &= 0xFC; // clearing first 2 bits
        MCUCR |= copy_enumSenseCtrl;
        //* Enable Interrupt
        Set_Bit(GICR, INT0);
        break;

    case INT1_:
        //* Configure Interrupt Activate State
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
        //* Enable Interrupt

        Set_Bit(GICR, INT1);
        break;

    case INT2_:
        //*Configure Interrupt Activate State
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
        //* Enable Interrupt
        Set_Bit(GICR, INT2);
        break;
    }
}


/**
 * @return void
 * @param : copy_enumInterruptSrc     Interrupt Source
 * @brief : Disable Given Interrut 
 */
void EXINT_voidDisable(EXTINT_Source_t copy_enumInterruptSrc)
{
    switch (copy_enumInterruptSrc)
    {
    case INT0_:
        //* Disable Interrupt
        Clr_Bit(GICR, INT0);
        break;

    case INT1_:
        //* Disable Interrupt
        Clr_Bit(GICR, INT1);
        break;

    case INT2_:
        //* Disable Interrupt
        Clr_Bit(GICR, INT2);
        break;
    }
}

static void (*PRV_pCallBack_INT1)(void) = NULL;

/**
 * @return void
 * @param : copy_pFunc     Pointer to Call-Back function 
 * @brief : Configure Given Interrut To perform  given Function From higher level
 */
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

static void (*PRV_pCallBack_INT0)(void) = NULL;

/**
 * @return void
 * @param : copy_pFunc     Pointer to Call-Back function 
 * @brief : Configure Given Interrut To perform  given Function From higher level
 */
void EXINT_voidSetCallBackINT0(void (*copy_pFunc)(void))
{
    if (copy_pFunc)
    {
        PRV_pCallBack_INT0 = copy_pFunc;
    }
    else
    {
        // Error
    }
}

static void (*PRV_pCallBack_INT2)(void) = NULL;

/**
 * @return void
 * @param : copy_pFunc     Pointer to Call-Back function 
 * @brief : Configure Given Interrut To perform  given Function From higher level
 */
void EXINT_voidSetCallBackINT2(void (*copy_pFunc)(void))
{
    if (copy_pFunc)
    {
        PRV_pCallBack_INT2 = copy_pFunc;
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

ISR(INT0_vect)
{
    PRV_pCallBack_INT0();
}

ISR(INT2_vect)
{
    PRV_pCallBack_INT2();
}