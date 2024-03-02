#ifndef __LCD_PRIVATE__
#define __LCD_PRIVATE__

#include "LCD_config.h"

#define _LCD_CLEAR                                  0X01
#define _LCD_RETURN_HOME                            0x02

#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF               0x04
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON                0x05

#define _LCD_ENTRY_MODE_INC_SHIFT_OFF               0x06
#define _LCD_ENTRY_MODE_INC_SHIFT_ON                0x07

#define _LCD_CURSOR_MOVE_SHIFT_LEFT                 0x10
#define _LCD_CURSOR_MOVE_SHIFT_RIGHT                0x14

#define _LCD_DISPLAY_SHIFT_LEFT                     0x18
#define _LCD_DISPLAY_SHIFT_RIGHT                    0x1C

#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF    0x0C

#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON     0x0D

#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF     0x0E

#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON      0x0F

#define _LCD_DISPLAY_OFF_CURSOR_OFF                 0x08

#define _LCD_8BIT_MODE_2_LINE                       0x38
#define _LCD_4BIT_MODE_2_LINE                       0x28

#define _LCD_CGRAM_START                            0x40
#define _LCD_DDRAM_START                            0x80

#define LINE1                                       0x80
#define LINE2                                       0xc0
#define LINE3                                       0x94
#define LINE4                                       0xd4

#if LCD_4BIT == ENABLED

void LCD_4_bit_INIT(void);
void LCD_4_bit_Write_Char(u8);
void LCD_4_bit_send_command(u8);
void LCD_4_bit_Write_String_At(u8 *ptr,u8 line ,u8 col);
void LCD_4_bit_Set_Cursor(u8 x , u8 y);
void LCD_4_bit_Write_Custom_Char(u8 line,u8 col,u8 mempos);
void LCD_4_bit_Create_Custom_Char(u8 *dataArr, u8 mempos);
void LCD_4_bit_Write_int(u16);

#endif

#if LCD_8BIT == ENABLED

void LCD_8_bit_INIT(void);
void LCD_8_bit_Write_Char(u8);
void LCD_8_bit_Write_String_At(u8 *ptr,u8 line ,u8 col);
void LCD_8_bit_Set_Cursor(u8 x , u8 y);
void LCD_8_bit_Write_Custom_Char(u8 line,u8 col,u8 mempos);
void LCD_8_bit_Create_Custom_Char(u8 *dataArr, u8 mempos);

#endif

#endif //__LCD_PRIVATE__