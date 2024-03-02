#ifndef __7SEGMENT_INTERFACE__
#define __7SEGMENT_INTERFACE__

#include "Std_Types.h"

void SSD_Init(void);
void SSD_Write_Number(u8 SSD_IDX, u8 Number);
void SSD_Write_Multiple_numbers(u8 num1, u8 num2, u8 num3, u8 num4, u16 uS_delay);

#endif //__7SEGMENT_INTERFACE__