#include "LCD_interface.h"
#include "DIO_interface.h"
#include "util/delay.h"

#if LCD_4BIT == ENABLED

static inline void LCD_4_BIT_Shift(u8);
static inline void LCD_4_BIT_Pulse();
static void LCD_4BIT_INTIT_PINS();

static inline void LCD_4_BIT_Pulse(void)
{
    DIO_voidSetPinValue(LCD_4_BIT_EN_PORT, LCD_4_BIT_EN_PIN, DIO_PIN_HIGH); // Pulse Enable pin
    _delay_us(5);
    DIO_voidSetPinValue(LCD_4_BIT_EN_PORT, LCD_4_BIT_EN_PIN, DIO_PIN_LOW); // Pulse Enable pin
}

static void LCD_4BIT_INTIT_PINS()
{
    DIO_voidSetPinDirection(LCD_4_BIT_D4_PORT, LCD_4_BIT_D4_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_4_BIT_D5_PORT, LCD_4_BIT_D5_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_4_BIT_D6_PORT, LCD_4_BIT_D6_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_4_BIT_D7_PORT, LCD_4_BIT_D7_PIN, DIO_PIN_OUTPUT);

    DIO_voidSetPinDirection(LCD_4_BIT_RS_PORT, LCD_4_BIT_RS_PIN, DIO_PIN_OUTPUT); // rs
    DIO_voidSetPinDirection(LCD_4_BIT_RW_PORT, LCD_4_BIT_RW_PIN, DIO_PIN_OUTPUT); // rw

    DIO_voidSetPinDirection(LCD_4_BIT_EN_PORT, LCD_4_BIT_EN_PIN, DIO_PIN_OUTPUT); // en
}

static inline void LCD_4_BIT_Shift(u8 data)
{
    DIO_voidSetPinValue(LCD_4_BIT_D4_PORT, LCD_4_BIT_D4_PIN, ((data >> 0) & 0x01));
    DIO_voidSetPinValue(LCD_4_BIT_D5_PORT, LCD_4_BIT_D5_PIN, ((data >> 1) & 0x01));
    DIO_voidSetPinValue(LCD_4_BIT_D6_PORT, LCD_4_BIT_D6_PIN, ((data >> 2) & 0x01));
    DIO_voidSetPinValue(LCD_4_BIT_D7_PORT, LCD_4_BIT_D7_PIN, ((data >> 3) & 0x01));
}

void LCD_4_bit_send_command(u8 cmd)
{
    LCD_4_BIT_Shift(cmd >> 4);                                             // write command to data pins
    DIO_voidSetPinValue(LCD_4_BIT_RW_PORT, LCD_4_BIT_RW_PIN, DIO_PIN_LOW); // select write operation
    DIO_voidSetPinValue(LCD_4_BIT_RS_PORT, LCD_4_BIT_RS_PIN, DIO_PIN_LOW); // Select Instruction Regsiter
    LCD_4_BIT_Pulse();

    LCD_4_BIT_Shift(cmd);                                                  // write command to data pins
    DIO_voidSetPinValue(LCD_4_BIT_RW_PORT, LCD_4_BIT_RW_PIN, DIO_PIN_LOW); // select write operation
    DIO_voidSetPinValue(LCD_4_BIT_RS_PORT, LCD_4_BIT_RS_PIN, DIO_PIN_LOW); // Select Instruction Regsiter
    LCD_4_BIT_Pulse();
}

static void LCD_4_BIT_Send_DATA(u8 data)
{

    LCD_4_BIT_Shift(data >> 4);                                             // write command to data pins
    DIO_voidSetPinValue(LCD_4_BIT_RW_PORT, LCD_4_BIT_RW_PIN, DIO_PIN_LOW);  // select write operation
    DIO_voidSetPinValue(LCD_4_BIT_RS_PORT, LCD_4_BIT_RS_PIN, DIO_PIN_HIGH); // Select data Regsiter
    LCD_4_BIT_Pulse();

    LCD_4_BIT_Shift(data);                                                  // write command to data pins
    DIO_voidSetPinValue(LCD_4_BIT_RW_PORT, LCD_4_BIT_RW_PIN, DIO_PIN_LOW);  // select write operation
    DIO_voidSetPinValue(LCD_4_BIT_RS_PORT, LCD_4_BIT_RS_PIN, DIO_PIN_HIGH); // Select Instruction Regsiter
    LCD_4_BIT_Pulse();
}

void LCD_4_bit_INIT(void)
{
    LCD_4BIT_INTIT_PINS();
    // * pins already initialized
    _delay_ms(100);
    LCD_4_bit_send_command(_LCD_8BIT_MODE_2_LINE);
    _delay_ms(5);

    LCD_4_bit_send_command(_LCD_8BIT_MODE_2_LINE);
    _delay_us(150);

    LCD_4_bit_send_command(_LCD_8BIT_MODE_2_LINE);
    _delay_us(150);

    LCD_4_bit_send_command(_LCD_CLEAR);
    _delay_us(150);

    LCD_4_bit_send_command(_LCD_RETURN_HOME);
    _delay_us(150);

    LCD_4_bit_send_command(_LCD_ENTRY_MODE_INC_SHIFT_OFF);
    _delay_us(150);

    LCD_4_bit_send_command(_LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON);
    _delay_us(150);
    LCD_4_bit_send_command(_LCD_CLEAR);
    LCD_4_bit_Set_Cursor(1, 0);
}

void LCD_4_bit_Write_Char(u8 ch)
{
    LCD_4_BIT_Send_DATA(ch);
}

void LCD_4_bit_Write_String_At(u8 *ptr, u8 line, u8 col)
{
    u8 *tempPtr = ptr;
    u8 offsetX = 0, offsetY = 0;
    while (*tempPtr != '\0')
    {
        LCD_4_bit_Set_Cursor((line + offsetX), (col + offsetY));
        LCD_4_bit_Write_Char(*tempPtr);
        tempPtr++;
        if (offsetY == 19)
        {
            offsetX = (offsetX + 1) % 5;
        }
        else
        {
        }
        offsetY = (offsetY + 1) % 20;
    }
}

void LCD_4_bit_Set_Cursor(u8 line, u8 col)
{
    switch (line)
    {
    case 1:
        LCD_4_bit_send_command((LINE1 + col));
        break;

    case 2:
        LCD_4_bit_send_command((LINE2 + col));
        break;

    case 3:
        LCD_4_bit_send_command((LINE3 + col));
        break;

    case 4:
        LCD_4_bit_send_command((LINE4 + col));
        break;

    default:
        break;
    }
}

void LCD_4_bit_Write_Custom_Char(u8 line, u8 col, u8 mempos)
{
    LCD_4_bit_send_command((_LCD_CGRAM_START + (mempos * 8)));
    LCD_4_bit_Set_Cursor(line, col);
    LCD_4_bit_Write_Char(mempos);
}

void LCD_4_bit_Create_Custom_Char(u8 *dataArr, u8 mempos)
{
    LCD_4_bit_send_command((_LCD_CGRAM_START + (mempos * 8)));
    for (u8 i = 0; i < 8; i++)
    {
        LCD_4_BIT_Send_DATA(dataArr[i]);
    }
    LCD_4_bit_send_command(_LCD_DDRAM_START);
}

void LCD_4_bit_Write_int(u16 num)
{
    u16 arrTemp [6];
    while (num != 0 )
    {
         u8 temp = num%10;
         LCD_4_bit_Write_Char(('0'+temp));
         num /= 10;
    }
    
}
#endif

#if LCD_8BIT == ENABLED
static void LCD_8_BIT_Send_CMD(u8);
static void LCD_8BIT_INTIT_PINS();

static void LCD_8_BIT_Send_CMD(u8 cmd)
{
    DIO_voidSetPinValue(LCD_8_BIT_EN_PORT, LCD_8_BIT_EN_PIN, DIO_PIN_HIGH); // Pulse Enable pin
    _delay_us(10);
    DIO_voidSetPinValue(LCD_8_BIT_D0_PORT, LCD_8_BIT_D0_PIN, ((cmd >> 0) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D1_PORT, LCD_8_BIT_D1_PIN, ((cmd >> 1) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D2_PORT, LCD_8_BIT_D2_PIN, ((cmd >> 2) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D3_PORT, LCD_8_BIT_D3_PIN, ((cmd >> 3) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D4_PORT, LCD_8_BIT_D4_PIN, ((cmd >> 4) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D5_PORT, LCD_8_BIT_D5_PIN, ((cmd >> 5) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D6_PORT, LCD_8_BIT_D6_PIN, ((cmd >> 6) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D7_PORT, LCD_8_BIT_D7_PIN, ((cmd >> 7) & 0x01));
    // write command onto data pins
    DIO_voidSetPinValue(LCD_8_BIT_RW_PORT, LCD_8_BIT_RW_PIN, DIO_PIN_LOW); // select write operation
    DIO_voidSetPinValue(LCD_8_BIT_RS_PORT, LCD_8_BIT_RS_PIN, DIO_PIN_LOW); // Select Instruction Regsiter

    DIO_voidSetPinValue(LCD_8_BIT_EN_PORT, LCD_8_BIT_EN_PIN, DIO_PIN_LOW); // Pulse Enable pin
}

static void LCD_8_BIT_Send_DATA(u8 data)
{
    DIO_voidSetPinValue(LCD_8_BIT_EN_PORT, LCD_8_BIT_EN_PIN, DIO_PIN_HIGH); // Pulse Enable pin
    _delay_us(10);
    DIO_voidSetPinValue(LCD_8_BIT_D0_PORT, LCD_8_BIT_D0_PIN, ((data >> 0) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D1_PORT, LCD_8_BIT_D1_PIN, ((data >> 1) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D2_PORT, LCD_8_BIT_D2_PIN, ((data >> 2) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D3_PORT, LCD_8_BIT_D3_PIN, ((data >> 3) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D4_PORT, LCD_8_BIT_D4_PIN, ((data >> 4) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D5_PORT, LCD_8_BIT_D5_PIN, ((data >> 5) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D6_PORT, LCD_8_BIT_D6_PIN, ((data >> 6) & 0x01));
    DIO_voidSetPinValue(LCD_8_BIT_D7_PORT, LCD_8_BIT_D7_PIN, ((data >> 7) & 0x01));
    // write Data onto data pins
    DIO_voidSetPinValue(LCD_8_BIT_RW_PORT, LCD_8_BIT_RW_PIN, DIO_PIN_LOW);  // select write operation
    DIO_voidSetPinValue(LCD_8_BIT_RS_PORT, LCD_8_BIT_RS_PIN, DIO_PIN_HIGH); // Select data Regsiter

    DIO_voidSetPinValue(LCD_8_BIT_EN_PORT, LCD_8_BIT_EN_PIN, DIO_PIN_LOW); // Pulse Enable pin
}

static void LCD_8BIT_INTIT_PINS()
{
    DIO_voidSetPinDirection(LCD_8_BIT_D0_PORT, LCD_8_BIT_D0_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_8_BIT_D1_PORT, LCD_8_BIT_D1_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_8_BIT_D2_PORT, LCD_8_BIT_D2_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_8_BIT_D3_PORT, LCD_8_BIT_D3_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_8_BIT_D4_PORT, LCD_8_BIT_D4_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_8_BIT_D5_PORT, LCD_8_BIT_D5_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_8_BIT_D6_PORT, LCD_8_BIT_D6_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_8_BIT_D7_PORT, LCD_8_BIT_D7_PIN, DIO_PIN_OUTPUT);

    DIO_voidSetPinDirection(LCD_8_BIT_RS_PORT, LCD_8_BIT_RS_PIN, DIO_PIN_OUTPUT); // rs
    DIO_voidSetPinDirection(LCD_8_BIT_RW_PORT, LCD_8_BIT_RW_PIN, DIO_PIN_OUTPUT); // rw

    DIO_voidSetPinDirection(LCD_8_BIT_EN_PORT, LCD_8_BIT_EN_PIN, DIO_PIN_OUTPUT); // en
}

void LCD_8_bit_INIT(void)
{
    LCD_8BIT_INTIT_PINS();
    // * pins already initialized
    _delay_ms(30);
    LCD_8_BIT_Send_CMD(_LCD_8BIT_MODE_2_LINE);
    _delay_ms(5);

    LCD_8_BIT_Send_CMD(_LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON);
    _delay_us(150);

    LCD_8_BIT_Send_CMD(_LCD_CLEAR);
    _delay_us(150);

    LCD_8_BIT_Send_CMD(_LCD_ENTRY_MODE_INC_SHIFT_OFF);
    _delay_us(150);

    // LCD_8_BIT_Send_CMD(_LCD_4BIT_MODE_2_LINE);

    LCD_8_BIT_Send_CMD(_LCD_DDRAM_START);
    LCD_8_bit_Set_Cursor(1, 0);
}

void LCD_8_bit_Write_Char(u8 ch)
{
    LCD_8_BIT_Send_DATA(ch);
}

void LCD_8_bit_Write_String_At(u8 *ptr, u8 line, u8 col)
{
    u8 *tempPtr = ptr;
    u8 offsetX = 0, offsetY = 0;
    while (*tempPtr != '\0')
    {
        LCD_8_bit_Set_Cursor((line + offsetX), (col + offsetY));
        LCD_8_bit_Write_Char(*tempPtr);
        tempPtr++;
        if (offsetY == 19)
        {
            offsetX = (offsetX + 1) % 5;
        }
        else
        {
        }
        offsetY = (offsetY + 1) % 20;
    }
}

void LCD_8_bit_Set_Cursor(u8 line, u8 col)
{
    switch (line)
    {
    case 1:
        LCD_8_BIT_Send_CMD((LINE1 + col));
        break;

    case 2:
        LCD_8_BIT_Send_CMD((LINE2 + col));
        break;

    case 3:
        LCD_8_BIT_Send_CMD((LINE3 + col));
        break;

    case 4:
        LCD_8_BIT_Send_CMD((LINE4 + col));
        break;

    default:
        break;
    }
}

void LCD_8_bit_Write_Custom_Char(u8 line, u8 col, u8 mempos)
{
    LCD_8_BIT_Send_CMD((_LCD_CGRAM_START + (mempos * 8)));
    LCD_8_bit_Set_Cursor(line, col);
    LCD_8_bit_Write_Char(mempos);
}
void LCD_8_bit_Create_Custom_Char(u8 *dataArr, u8 mempos)
{
    LCD_8_BIT_Send_CMD((_LCD_CGRAM_START + (mempos * 8)));
    for (u8 i = 0; i < 8; i++)
    {
        LCD_8_BIT_Send_DATA(dataArr[i]);
    }
}
#endif