#include "7SEGMENT_interface.h"
#include "7SEGMENT_config.h"
#include <util/delay.h>

void SSD_Init(void)
{

#if BCD == ENABLED
    DIO_voidSetPinDirection(SSD_PIN0_PORT, SSD_PIN0, DIO_PIN_OUTPUT); // A
    DIO_voidSetPinDirection(SSD_PIN1_PORT, SSD_PIN1, DIO_PIN_OUTPUT); // B
    DIO_voidSetPinDirection(SSD_PIN2_PORT, SSD_PIN2, DIO_PIN_OUTPUT); // C
    DIO_voidSetPinDirection(SSD_PIN3_PORT, SSD_PIN3, DIO_PIN_OUTPUT); // D
#else
    DIO_voidSetPinDirection(SSD_PIN0_PORT, SSD_PIN0, DIO_PIN_OUTPUT); // A
    DIO_voidSetPinDirection(SSD_PIN1_PORT, SSD_PIN1, DIO_PIN_OUTPUT); // B
    DIO_voidSetPinDirection(SSD_PIN2_PORT, SSD_PIN2, DIO_PIN_OUTPUT); // C
    DIO_voidSetPinDirection(SSD_PIN3_PORT, SSD_PIN3, DIO_PIN_OUTPUT); // D
    DIO_voidSetPinDirection(SSD_PIN3_PORT, SSD_PIN4, DIO_PIN_OUTPUT); // E
    DIO_voidSetPinDirection(SSD_PIN4_PORT, SSD_PIN5, DIO_PIN_OUTPUT); // F
    DIO_voidSetPinDirection(SSD_PIN5_PORT, SSD_PIN6, DIO_PIN_OUTPUT); // G

#endif
    DIO_voidSetPinDirection(SSD_ENABLE0_PORT, SSD_ENABLE0_PIN, DIO_PIN_OUTPUT); // Enable
    DIO_voidSetPinDirection(SSD_ENABLE1_PORT, SSD_ENABLE1_PIN, DIO_PIN_OUTPUT); // Enable
    DIO_voidSetPinDirection(SSD_ENABLE2_PORT, SSD_ENABLE2_PIN, DIO_PIN_OUTPUT); // Enable
    DIO_voidSetPinDirection(SSD_ENABLE3_PORT, SSD_ENABLE3_PIN, DIO_PIN_OUTPUT); // Enable
}

void SSD_Write_Number(u8 SSD_IDX, u8 Number)
{
    switch (SSD_IDX)
    {
    case 1:
#if COMMON_ANODE == ENABLED
        DIO_voidSetPinValue(SSD_ENABLE0_PORT, SSD_ENABLE0_PIN, DIO_PIN_LOW); // Enable level for ANODE
#elif COMMON_CATHODE == ENABLED
        DIO_voidSetPinValue(SSD_ENABLE0_PORT, SSD_ENABLE0_PIN, DIO_PIN_HIGH); // Enable level for CATHODE
#endif
        break;

    case 2:
#if COMMON_ANODE == ENABLED
        DIO_voidSetPinValue(SSD_ENABLE1_PORT, SSD_ENABLE1_PIN, DIO_PIN_LOW); // Enable level for ANODE
#elif COMMON_CATHODE == ENABLED
        DIO_voidSetPinValue(SSD_ENABLE1_PORT, SSD_ENABLE1_PIN, DIO_PIN_HIGH); // Enable level for CATHODE
#endif
        break;

    case 3:
#if COMMON_ANODE == ENABLED
        DIO_voidSetPinValue(SSD_ENABLE2_PORT, SSD_ENABLE2_PIN, DIO_PIN_LOW); // Enable level for ANODE
#elif COMMON_CATHODE == ENABLED
        DIO_voidSetPinValue(SSD_ENABLE2_PORT, SSD_ENABLE2_PIN, DIO_PIN_HIGH); // Enable level for CATHODE
#endif
        break;

    case 4:
#if COMMON_ANODE == ENABLED
        DIO_voidSetPinValue(SSD_ENABLE3_PORT, SSD_ENABLE3_PIN, DIO_PIN_LOW); // Enable level for ANODE
#elif COMMON_CATHODE == ENABLED
        DIO_voidSetPinValue(SSD_ENABLE3_PORT, SSD_ENABLE3_PIN, DIO_PIN_HIGH); // Enable level for CATHODE
#endif
        break;

    default:
        break;
    }
#if BCD == ENABLED

    DIO_voidSetPinValue(SSD_PIN0_PORT, SSD_PIN0, ((Number >> 0) & 0x01)); // A
    DIO_voidSetPinValue(SSD_PIN1_PORT, SSD_PIN1, ((Number >> 1) & 0x01)); // B
    DIO_voidSetPinValue(SSD_PIN2_PORT, SSD_PIN2, ((Number >> 2) & 0x01)); // C
    DIO_voidSetPinValue(SSD_PIN3_PORT, SSD_PIN3, ((Number >> 3) & 0x01)); // D

#else
    DIO_voidSetPinValue(SSD_PIN0_PORT, SSD_PIN0, ((number >> 0) & 0x01)); // A
    DIO_voidSetPinValue(SSD_PIN1_PORT, SSD_PIN1, ((number >> 1) & 0x01)); // B
    DIO_voidSetPinValue(SSD_PIN2_PORT, SSD_PIN2, ((number >> 2) & 0x01)); // C
    DIO_voidSetPinValue(SSD_PIN3_PORT, SSD_PIN3, ((number >> 3) & 0x01)); // D
    DIO_voidSetPinValue(SSD_PIN0_PORT, SSD_PIN4, ((number >> 4) & 0x01)); // E
    DIO_voidSetPinValue(SSD_PIN1_PORT, SSD_PIN5, ((number >> 5) & 0x01)); // F
    DIO_voidSetPinValue(SSD_PIN2_PORT, SSD_PIN6, ((number >> 6) & 0x01)); // G

#endif
}

void SSD_Write_Multiple_numbers(u8 num1, u8 num2, u8 num3, u8 num4, u16 uS_delay)
{

    SSD_Write_Number(1, num1);
    _delay_us(uS_delay);
    DIO_voidSetPinValue(SSD_ENABLE0_PORT, SSD_ENABLE0_PIN, DIO_PIN_HIGH); // Disable
                                                                          /*************************/
    SSD_Write_Number(2, num2);
    _delay_us(uS_delay);
    DIO_voidSetPinValue(SSD_ENABLE1_PORT, SSD_ENABLE1_PIN, DIO_PIN_HIGH); // Disable
                                                                          /*************************/
    SSD_Write_Number(3, num3);
    _delay_us(uS_delay);
    DIO_voidSetPinValue(SSD_ENABLE2_PORT, SSD_ENABLE2_PIN, DIO_PIN_HIGH); // Disable
                                                                          /*************************/
    SSD_Write_Number(4, num4);
    _delay_us(uS_delay);
    DIO_voidSetPinValue(SSD_ENABLE3_PORT, SSD_ENABLE3_PIN, DIO_PIN_HIGH); // Disable
}