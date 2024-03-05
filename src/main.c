#include <util/delay.h>
#include "DIO_interface.h"
#include "7SEGMENT_interface.h"
#include "LCD_interface.h"
#include "GLOBAL_INT.h"
#include "INT_interface.h"
#include "KEYPAD_interface.h"
#include "ADC_interface.h"
#include <stdio.h>

u8 keypadMatrix[4][4] = {

    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'C', '0', '=', '+'}};

u8 keyPressed = 0;

u8 celsius[] = { // celsius sympol
    0B11100,
    0B10100,
    0B11100,
    0B00000,
    0B00000,
    0B00000,
    0B00000,
    0B00000};

int main(void)
{
  DIO_voidInitPins();
  LCD_4_bit_voidInit();
  ADC_voidInit(ADC_INTERNAL2_56, ADC_RIGHT_ADJUST, ADC0_IDX, AUTO_TRIG_DISABLE,
               ADC_preScaler_DIV_BY_128, ADC_INT_DISABLE);

  LCD_4_bit_voidCreateCustomChar(celsius, 0);
  LCD_4_bit_voidWriteStringAt((u8 *)"KeyPressed: ", 0, 0);
  LCD_4_bit_voidWriteInt(156);
  while (1)
  {
    if (KEYPAD_u8GetChar(&keyPressed, (u8 *)keypadMatrix) != 0)
    {
      LCD_4_bit_voidSetCursor(1, 0);
      LCD_4_bit_voidWriteChar(keyPressed);
    }
    else
    {
      u16 Digital = ADC_u16Read_Channel(ADC1_IDX, ADC_AVCC, ADC_preScaler_DIV_BY_128);

      u16 Analog = (Digital * 5000UL) / 1024;
      LCD_4_bit_voidWriteStringAt((u8 *)"Temprature Value: ", 2, 0);
      LCD_4_bit_voidWriteStringAt((u8 *)"     ", 3, 0);
      LCD_4_bit_voidSetCursor(3, 0);
      LCD_4_bit_voidWriteInt(Analog / 10);
      LCD_4_bit_voidWriteCustomChar(3, 4, 0);
      LCD_4_bit_voidWriteStringAt((u8 *)"C", 3, 5);
    }
    _delay_ms(200);
  }

  return 0;
}

//! MANDATORY to stop compiler from optimizing isr and
//! save this function address into the vector table
// void __vector_2(void) __attribute__((signal));
