#ifndef __7SEGMENT_INTERFACE__
#define __7SEGMENT_INTERFACE__

#include "Std_Types.h"


/**
 * @return void
 * @brief : Initialize 7Segment
 */
void SSD_voidInit(void);

/**
 * @return void
 * @param : copy_u8SSDindex            Index of 7segment display
 * @param : copy_u8Number              Number to be written
 * @brief : Wirite given number on 7segment
 */
void SSD_voidWriteNumber(u8 copy_u8SSDindex, u8 copy_u8Number);



/**
 * @return void
 * @param : copy_u8SSDindex            Index of 7segment display
 * @param : copy_u8Number              Number to be written
 * @brief : Wirite given number on 7segment
 */
void SSD_voidWriteMultipleNumbers(u8 copy_u8num1, u8 copy_u8num2, u8 copy_u8num3, u8 copy_u8num4, u16 copy_u16SecondsDelay);


#endif //__7SEGMENT_INTERFACE__