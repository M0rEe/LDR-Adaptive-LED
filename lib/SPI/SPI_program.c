#include "SPI_interface.h"
#include "SPI_private.h"
#include "DIO_interface.h"

#define SPI_INTERRUPT_ENABLE() (Set_Bit(SPCR, SPIE))
#define SPI_INTERRUPT_DISABLE() (Clr_Bit(SPCR, SPIE))

#define SPI_ENABLE_MODULE() (Set_Bit(SPCR, SPE))
#define SPI_DISABLE_MODULE() (Clr_Bit(SPCR, SPE))

#define SPI_GET_INTERRUPT_FLAG() (Get_Bit(SPSR, SPIF))
#define SPI_GET_COLLISION_FLAG() (Get_Bit(SPSR, WCOL))

void SPI_voidInit(u8 copy_u8MasterSalveMode, SPI_FREQ_t copy_enumSPI_FREQ)
{
    // Disable SPI interrupt
    Clr_Bit(SPCR, SPIE);
#if SPI_LSB == 1
    Set_Bit(SPCR, DORD);
#else
    Clr_Bit(SPCR, DORD);
#endif
    Set_Bit(SPCR, MSTR);

#if SPI_CLK_Falling_Rising == 1
    Set_Bit(SPCR, CPOL);
#else
    Clr_Bit(SPCR, CPOL);
#endif

#if SPI_CLK_Setup_Sample == 1
    Set_Bit(SPCR, CPHA);
#else
    Clr_Bit(SPCR, CPHA);
#endif
    if (copy_u8MasterSalveMode == SPI_MASTER_MODE)
    {

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
        // select Salve Mode
        Clr_Bit(SPCR, MSTR);
    }
    // Enable SPI
    Set_Bit(SPCR, SPE);
}

void SPI_voidSendRecv(u8 copy_u8SendData, u8 *copy_pu8RecvData)
{
    // Select Slave
    DIO_voidSetPinValue(DIO_PORTB, DIO_PIN4, DIO_PIN_LOW);
    // wait for collison
    // while (!SPI_GET_COLLISION_FLAG());
    SPDR = copy_u8SendData;
    // wait for data to be written
    while (!SPI_GET_INTERRUPT_FLAG());
    // read data
    *copy_pu8RecvData = SPDR;

}