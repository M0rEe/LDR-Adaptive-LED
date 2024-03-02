#include "DIO_interface.h"
#include "7SEGMENT_interface.h"
#include "LCD_interface.h"
#include <util/delay.h>

int main(void)
{
  /* Switch */
  DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN7, DIO_PIN_INPUT);
  DIO_voidActivePinInPullUpResistance(DIO_PORTD, DIO_PIN7);
  DIO_INTI();
  /*LCD*/
  /*
  DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN0, DIO_PIN_OUTPUT); // d0
  DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN1, DIO_PIN_OUTPUT); // d1
  DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN2, DIO_PIN_OUTPUT); // d2
  DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN3, DIO_PIN_OUTPUT); // d3
  DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN4, DIO_PIN_OUTPUT); // d4
  DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN5, DIO_PIN_OUTPUT); // d5
  DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN6, DIO_PIN_OUTPUT); // d6
  DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN7, DIO_PIN_OUTPUT); // d7

  DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN4, DIO_PIN_OUTPUT); // rs
  DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN5, DIO_PIN_OUTPUT); // rw

  DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN6, DIO_PIN_OUTPUT); // en
  */
  LCD_4_bit_INIT();

  u16 counter = 0; //, tempCounter;
  u8 val = 1;

  u8 ptr[] = {
      0B00000,
      0B11100,
      0B00100,
      0B00100,
      0B00100,
      0B00100,
      0B11100,
      0B00000};
  // SSD_Init();
  // int ones = 0, tens = 0, hundreds = 0, thouthands = 0;
  u8 str[] = "---Hello World---";
  u8 str2[] = "--First Line---";

  while (1)
  {
    DIO_voidGetPinValue(DIO_PORTD, DIO_PIN7, &val);

    // LCD_4_bit_Write_String_At(str, 4, 0);

    // LCD_4_bit_Write_Custom_Char(2, 0, 0);
    if (DIO_PIN_LOW == val)
    {
      counter++;
      // LCD_4_bit_Create_Custom_Char(ptr, 0);
      LCD_4_bit_Create_Custom_Char(ptr, 1);
      LCD_4_bit_Write_Custom_Char(3,5,1);
      LCD_4_bit_Write_String_At(str, 4, 0);
      LCD_4_bit_Write_String_At(str2, 1, 2);
      LCD_4_bit_Set_Cursor(2,0);
      LCD_4_bit_Write_int(256);
    }
    else
    {
    }
    _delay_ms(100);
    /*
    tempCounter = counter;

    ones = tempCounter % 10;
    tempCounter /= 10;

    tens = tempCounter % 10;
    tempCounter /= 10;

    hundreds = tempCounter % 10;
    tempCounter /= 10;

    thouthands = tempCounter % 10;
    tempCounter /= 10;

    SSD_Write_Multiple_numbers(ones, tens, hundreds, thouthands, 500);
    */
  }

  return 0;
}