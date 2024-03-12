#include <util/delay.h>
#include "DIO_interface.h"
#include "7SEGMENT_interface.h"
#include "LCD_interface.h"
#include "GLOBAL_INT.h"
#include "INT_interface.h"
#include "KEYPAD_interface.h"
#include "ADC_interface.h"
#include "SPI_interface.h"

/* Keypad Matrix */
u8 KeypadMatrix[4][4] = {
    {'7', '8', '9', 'A'},
    {'4', '5', '6', 'B'},
    {'1', '2', '3', 'C'},
    {'*', '0', '#', 'D'}};

/***
 * @return Value withen new range
 * @param X value to be mapped
 * @param in_min input range minimumm
 * @param in_max input range maximum
 * @param out_min output range minimum
 * @param out_max output range maximum
 *
 */
u16 map(u16 x, u16 in_min, u16 in_max, u16 out_min, u16 out_max)
{
  return (u32)(x - in_min) * (u32)(out_max - out_min) / (u32)(in_max - in_min) + out_min;
}

int main(void)
{
  /* Initialization seciton */
  DIO_voidInitPins();
  LCD_4_bit_voidInit();
  ADC_voidInit(ADC_AVCC, ADC_RIGHT_ADJUST, ADC0_IDX, ADC_AUTO_TRIGGER_OFF, ADC_preScaler_DIV_BY_128, ADC_INT_DISABLE);
  /* Local Variable */
  u8 KeyPressed = 0;
  u16 Threshold = 50;
  u16 buffer = 0;

  LCD_4_bit_voidWriteStringAt((u8 *)"Threshold(50)", 1, 0);

  while (1)
  {
    u16 adcRead = ADC_u16Read_Channel(ADC0_IDX, ADC_AVCC, ADC_preScaler_DIV_BY_128);

    u16 mappedValue = map(adcRead, 0, 1023, 0, 100);

    LCD_4_bit_voidWriteStringAt((u8 *)"adc val :", 0, 0);
    LCD_4_bit_voidWriteStringAt((u8 *)"       ", 0, 10);
    LCD_4_bit_voidSetCursor(0, 10);
    LCD_4_bit_voidWriteInt(mappedValue);

    KEYPAD_voidGetCharBLOCKING(&KeyPressed, (u8 *)KeypadMatrix);
    //TODO: input validation upon 0 to 99 range only 
    
    if (KeyPressed >= '0' && KeyPressed <= '9') // validatie numbers only 
    {
      buffer = (buffer * 10) + (KeyPressed - '0');
      LCD_4_bit_voidWriteStringAt((u8 *)"current :", 1, 0);
      LCD_4_bit_voidWriteStringAt((u8 *)"    ", 1, 9);
      LCD_4_bit_voidSetCursor(1, 9);
      LCD_4_bit_voidWriteInt(buffer);
    }
    else if (KeyPressed == '#')
    {
      // apply threshold to program and write  it on lcd
      Threshold = buffer;
      buffer = 0;
      LCD_4_bit_voidWriteStringAt((u8 *)"    ", 1, 9);
      LCD_4_bit_voidWriteStringAt((u8 *)"ThresholdValue:", 2, 0);
      LCD_4_bit_voidWriteStringAt((u8 *)"    ", 3, 0);
      LCD_4_bit_voidSetCursor(3, 0);
      LCD_4_bit_voidWriteInt(Threshold);
    }
    else if (KeyPressed == '*') //clear last input number 
    {
      buffer /= 10;
      LCD_4_bit_voidWriteStringAt((u8 *)"current :", 1, 0);
      LCD_4_bit_voidWriteStringAt((u8 *)"    ", 1, 9);
      LCD_4_bit_voidSetCursor(1, 9);
      LCD_4_bit_voidWriteInt(buffer);
    }
    if ((mappedValue > Threshold))
    {
      // TODO: PWM light adaptation
      DIO_voidTogglePinValue(DIO_PORTC, DIO_PIN0);
    }

    // invalidate Key after
    KeyPressed = 0;

    _delay_ms(100);
  }

  return 0;
}

//! MANDATORY to stop compiler from optimizing isr and
//! save this function address into the vector table
// void __vector_2(void) __attribute__((signal));
