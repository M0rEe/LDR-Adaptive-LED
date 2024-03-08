#include <util/delay.h>
#include "DIO_interface.h"
#include "7SEGMENT_interface.h"
#include "LCD_interface.h"
#include "GLOBAL_INT.h"
#include "INT_interface.h"
#include "KEYPAD_interface.h"
#include "ADC_interface.h"
#include "SPI_interface.h"

void ReadData(u8 Data)
{
  if (Data == 35)
  {
    DIO_voidTogglePinValue(DIO_PORTA, DIO_PIN5);
  }
  else
  {
  }
}

int main(void)
{
  DIO_voidInitPins();
  // Initialize Master
  SPI_voidInit(SPI_MASTER_MODE,
               SPI_F_osc_div_by128);
  SET_GLOBAL_INTERRUPT();

  u8 Recv = 0;
  while (1)
  {
    // Master Code
    // SPI_voidSendRecv(55, &Recv);
    SPI_voidSendNoNBlocking(55, ReadData);
    // if (Recv == 35)
    //{
    DIO_voidTogglePinValue(DIO_PORTD, DIO_PIN5);
    //}

    _delay_ms(250);
  }

  return 0;
}

//! MANDATORY to stop compiler from optimizing isr and
//! save this function address into the vector table
// void __vector_2(void) __attribute__((signal));
