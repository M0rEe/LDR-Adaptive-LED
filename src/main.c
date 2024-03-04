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
u8 celsius[] = {
  0B11100,
  0B10100,
  0B11100,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};
int main(void)
{
  DIO_INTI();
  LCD_4_bit_INIT();
  ADC_voidInit(ADC_AVCC, ADC_RIGHT_ADJUST, ADC0_IDX, AUTO_TRIG_DISABLE,
               ADC_preScaler_DIV_BY_128, ADC_INT_DISABLE);
  DIO_voidSetPinDirection(DIO_PORTD, PIN3, DIO_PIN_INPUT);
  DIO_voidSetPinDirection(DIO_PORTA, PIN4, DIO_PIN_OUTPUT);
  LCD_4_bit_Create_Custom_Char(celsius,0);
  LCD_4_bit_Write_String_At((u8 *)"KeyPressed: ", 0, 0);

  while (1)
  {
    if (KEYPAD_u8GetChar(&keyPressed, (u8 *)keypadMatrix) != 0)
    {
      LCD_4_bit_Set_Cursor(1, 0);
      LCD_4_bit_Write_Char(keyPressed);
    }
    else
    {
      u8 tempArr[6];
      u16 Digital = ADC_u16Read_Channel(ADC1_IDX, ADC_AVCC, ADC_preScaler_DIV_BY_128);
      
      u16 Analog = (Digital * 5000UL) / 1024;
      sprintf((char *)tempArr, "%i", (Analog/10));

      LCD_4_bit_Write_String_At((u8 *)"Temprature Value: ", 2, 0);
      LCD_4_bit_Write_String_At(tempArr, 3, 0);
      LCD_4_bit_Write_Custom_Char(3,4,0);
      LCD_4_bit_Write_String_At((u8*)"C", 3, 5);

    }
    _delay_ms(200);
  }

  return 0;
}

//! MANDATORY to stop compiler from optimizing isr and
//! save this function address into the vector table
// void __vector_2(void) __attribute__((signal));
