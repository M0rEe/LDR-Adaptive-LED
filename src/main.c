#include <util/delay.h>
#include "DIO_interface.h"
#include "7SEGMENT_interface.h"
#include "LCD_interface.h"
#include "GLOBAL_INT.h"
#include "INT_interface.h"
#include "KEYPAD_interface.h"
#include "ADC_interface.h"
#include <stdio.h>

/*
u8 customChar[] = {
    0B11100,
    0B10100,
    0B10100,
    0B11100,
    0B00000,
    0B00000,
    0B00000,
    0B00000};
*/
/*
void func(void)
{
  DIO_voidTogglePinValue(DIO_PORTA, PIN4);
}
*/

u8 keypadMatrix[4][4] = {

    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'C', '0', '=', '+'}};

u8 keyPressed = 0;

int main(void)
{
  DIO_INTI();
  LCD_4_bit_INIT();
  ADC_voidInit(ADC_AVCC, ADC_RIGHT_ADJUST, ADC0_IDX, AUTO_TRIG_DISABLE,
               ADC_preScaler_DIV_BY_128, ADC_INT_DISABLE);
  DIO_voidSetPinDirection(DIO_PORTD, PIN3, DIO_PIN_INPUT);
  DIO_voidSetPinDirection(DIO_PORTA, PIN4, DIO_PIN_OUTPUT);
  u8 UPval = 1;
  u8 DOWNval = 1;

  u8 str[] = "KeyPressed: ";
  LCD_4_bit_Write_String_At(str, 0, 0);

  /*
    u8 str[] = "-+Hello World+-";
    LCD_4_bit_Create_Custom_Char(customChar, 0);
    LCD_4_bit_Write_Char(0);
    LCD_4_bit_Write_String_At(str, 1, 0);
    LCD_4_bit_Write_String_At(str, 2, 0);
    LCD_4_bit_Write_String_At(str, 3, 0);
    LCD_4_bit_Write_Custom_Char(3, 8, 0);
  */

  // SET_GLOBAL_INTERRUPT();
  // EXINT_voidSetCallBackINT1(func);
  // EXINT_voidEnable(INT1_, FALLING_EDGE);
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
      u16 Value = ADC_u16Read_Channel(ADC0_IDX,ADC_INTERNAL2_56,ADC_preScaler_DIV_BY_128);
      sprintf((char*)tempArr,"%i",Value);
      LCD_4_bit_Write_String_At((u8*)"LDR Value: ",2,0);
      LCD_4_bit_Write_String_At(tempArr,3,0);
    }

    if (DIO_PIN_LOW == UPval)
    {
    }
    else
    {
    }

    if (DIO_PIN_LOW == DOWNval)
    {
    }
    else
    {
    }
    _delay_ms(200);
  }

  return 0;
}

//! MANDATORY to stop compiler from optimizing isr and
//! save this function address into the vector table
// void __vector_2(void) __attribute__((signal));
