#include "DIO_interface.h"
#include "7SEGMENT_interface.h"
#include "LCD_interface.h"
#include <util/delay.h>

u8 customChar[] = {
    0x03,
    0x04,
    0x08,
    0x08,
    0x0C,
    0x0A,
    0x09,
    0x00};

int main(void)
{
  DIO_INTI();
  /*LCD*/
  LCD_4_bit_INIT();
  /* Switch 1   --> UP*/
  // DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN7, DIO_PIN_INPUT);
  // DIO_voidActivePinInPullUpResistance(DIO_PORTD, DIO_PIN7);

  /* Swithc 2   -->  DOWN */
  // DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN6, DIO_PIN_INPUT);
  // DIO_voidActivePinInPullUpResistance(DIO_PORTD, DIO_PIN6);

  u8 UPval = 1;
  u8 DOWNval = 1;

  u8 str[] = "-+Hello World+-";

  LCD_4_bit_Create_Custom_Char(customChar, 0);

  LCD_4_bit_Write_Char(1);
  LCD_4_bit_Write_String_At(str, 0, 0);
  LCD_4_bit_Write_String_At(str, 1, 0);
  LCD_4_bit_Write_String_At(str, 2, 0);
  LCD_4_bit_Write_String_At(str, 3, 0);
  LCD_4_bit_Write_Custom_Char(3,8,0);

  while (1)
  {

    DIO_voidGetPinValue(DIO_PORTD, DIO_PIN7, &UPval);   // getting up keypress
    DIO_voidGetPinValue(DIO_PORTD, DIO_PIN6, &DOWNval); // getting down keypress

    if (DIO_PIN_LOW == UPval)
    {
      LCD_4_bit_Write_Char('U');
      LCD_4_bit_Write_Char(0);
    }
    else
    {
    }

    if (DIO_PIN_LOW == DOWNval)
    {
      LCD_4_bit_Write_Char('D');
    }
    else
    {
    }
    _delay_ms(200);
  }

  return 0;
}