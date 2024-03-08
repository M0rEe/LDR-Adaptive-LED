#include "SPI_interface.h"
#include "SPI_private.h"
#include "DIO_interface.h"

#define SPI_INTERRUPT_ENABLE() (Set_Bit(SPCR, SPIE))
#define SPI_INTERRUPT_DISABLE() (Clr_Bit(SPCR, SPIE))

#define SPI_ENABLE_MODULE() (Set_Bit(SPCR, SPE))
#define SPI_DISABLE_MODULE() (Clr_Bit(SPCR, SPE))

#define SPI_GET_INTERRUPT_FLAG() (Get_Bit(SPSR, SPIF))
#define SPI_GET_COLLISION_FLAG() (Get_Bit(SPSR, WCOL))

/*
 * @return : void
 * @param  : copy_u8MasterSalveMode      MCU Master/Slave Mode
 * @param  : copy_enumSPI_FREQ           Enum of SPI_Frequency/CLK
 * @brief  : Initialize SPI Module With Predefined Configurations and post build touch-ups
 **/
void SPI_voidInit(u8 copy_u8MasterSalveMode, SPI_FREQ_t copy_enumSPI_FREQ)
{
    // Disable SPI interrupt
    Clr_Bit(SPCR, SPIE);
#if SPI_LSB == SELECTED
    Set_Bit(SPCR, DORD);
#else
    Clr_Bit(SPCR, DORD);
#endif

#if SPI_CLK_Falling_Rising == SELECTED
    Set_Bit(SPCR, CPOL);
#else
    Clr_Bit(SPCR, CPOL);
#endif

#if SPI_CLK_Setup_Sample == SELECTED
    Set_Bit(SPCR, CPHA);
#else
    Clr_Bit(SPCR, CPHA);
#endif
    if (copy_u8MasterSalveMode == SPI_MASTER_MODE)
    {
        // Master Mode
        Set_Bit(SPCR, MSTR);
        SPCR &= 0xFC; // clear first 2 bits
        SPCR |= (copy_enumSPI_FREQ & 0x03);
        if ((copy_enumSPI_FREQ & 0x04) == 0)
        {
            Clr_Bit(SPSR, SPI2X);
        }
        else
        {
            Set_Bit(SPSR, SPI2X);
        }
    }
    else
    {
        // Salve Mode
        Clr_Bit(SPCR, MSTR);
    }
    // Enable SPI
    Set_Bit(SPCR, SPE);
}

/*
 * @return : void
 * @param  : copy_u8SendData            Data to be sent either Master/slave
 * @param  : copy_pu8RecvData           Data to be received
 * @brief  : BLOCKING function to SEND/RECEIVE simultaneously
 **/
void SPI_voidSendRecv(u8 copy_u8SendData, u8 *copy_pu8RecvData)
{
    // Select Slave
    DIO_voidSetPinValue(DIO_PORTB, DIO_PIN4, DIO_PIN_LOW);
    // wait for collison
    // while (!SPI_GET_COLLISION_FLAG());
    SPDR = copy_u8SendData;
    // wait for data to be written
    while (!SPI_GET_INTERRUPT_FLAG())
        ;
    // read data
    *copy_pu8RecvData = SPDR;
}

static void (*PRV_callBackHandler)(u8 copy_pu8RecvData) = NULL;
/*
 * @return : void
 * @param  : copy_u8SendData            Data to be sent either Master/slave
 * @param  : copy_pu8RecvData           Data to be received
 * @brief  : NON-BLOCKING function to Put Data to be sent on request for next available sent frame
  !@warning: MUST ENABLE GLOBAL INTERRUPT BEFORE THE USAGE OF THIS FUNCTION 
 **/
void SPI_voidSendNoNBlocking(u8 copy_u8SendData, void (*copy_pfCallback)(u8 copy_pu8RecvData))
{
    if (Get_Bit(SPCR, MSTR) == SPI_MASTER_MODE)
    {
        // Select Slave
        DIO_voidSetPinValue(DIO_PORTB, DIO_PIN4, DIO_PIN_LOW);
    }
    else
    {
        // Slave Mode
    }
    // Enable Interrupt
    SPI_INTERRUPT_ENABLE();
    // Set callBack Function
    PRV_callBackHandler = copy_pfCallback;
    // Check Collision
    // Start Transmission
    SPDR = copy_u8SendData;
}
// Serial Transmition Complete
ISR(SPI_STC_vect)
{
    if (PRV_callBackHandler)
        PRV_callBackHandler(SPDR);
}