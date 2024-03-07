#include <util/delay.h>
#include "DIO_interface.h"
#include "7SEGMENT_interface.h"
#include "LCD_interface.h"
#include "GLOBAL_INT.h"
#include "INT_interface.h"
#include "KEYPAD_interface.h"
#include "ADC_interface.h"
#include "SPI_interface.h"

#define SPI_GET_INTERRUPT_FLAG() (Get_Bit(SPSR, SPIF))
#define SPI_GET_COLLISION_FLAG() (Get_Bit(SPSR, WCOL))

int main(void)
{
  DIO_voidInitPins();

  SPI_voidInit(SPI_MASTER_MODE,
               SPI_F_osc_div_by64);

  u8 Recv = 55;
  DIO_voidSetPinValue(DIO_PORTB, DIO_PIN4, DIO_PIN_LOW);
  while (1)
  {
    // master
    SPI_voidSendRecv(55, &Recv);
    if (Recv == 35)
    {
      DIO_voidTogglePinValue(DIO_PORTA, DIO_PIN5);
    }
    _delay_ms(250);
  }

  return 0;
}

//! MANDATORY to stop compiler from optimizing isr and
//! save this function address into the vector table
// void __vector_2(void) __attribute__((signal));
