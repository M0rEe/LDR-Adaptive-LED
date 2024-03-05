#ifndef __7SEGMENT_CONFIG__
#define __7SEGMENT_CONFIG__

#include "DIO_interface.h"


#define ENABLED 1
#define DISABLED 0

#define NUMBER_OF_SSDS  4

#define BCD ENABLED

#define SSD_ENABLE0_PIN  DIO_PIN3
#define SSD_ENABLE0_PORT DIO_PORTA

#define SSD_ENABLE1_PIN  DIO_PIN2
#define SSD_ENABLE1_PORT DIO_PORTA

#define SSD_ENABLE2_PIN  DIO_PIN5
#define SSD_ENABLE2_PORT DIO_PORTB

#define SSD_ENABLE3_PIN  DIO_PIN6
#define SSD_ENABLE3_PORT DIO_PORTB

#define COMMON_ANODE    ENABLED
#define COMMON_CATHODE  DISABLED


#if BCD == ENABLED

#define SSD_PIN0        DIO_PIN0
#define SSD_PIN0_PORT   DIO_PORTB

#define SSD_PIN1        DIO_PIN1
#define SSD_PIN1_PORT   DIO_PORTB

#define SSD_PIN2        DIO_PIN2
#define SSD_PIN2_PORT   DIO_PORTB

#define SSD_PIN3        DIO_PIN4
#define SSD_PIN3_PORT   DIO_PORTB

#else

#define SSD_PIN0        DIO_PIN0
#define SSD_PIN0_PORT   DIO_PORTB

#define SSD_PIN1        DIO_PIN1
#define SSD_PIN1_PORT   DIO_PORTB

#define SSD_PIN2        DIO_PIN2
#define SSD_PIN2_PORT   DIO_PORTB

#define SSD_PIN3        DIO_PIN4
#define SSD_PIN3_PORT   DIO_PORTB

#define SSD_PIN4        DIO_PIN0
#define SSD_PIN4_PORT   DIO_PORTB

#define SSD_PIN5        DIO_PIN1
#define SSD_PIN5_PORT   DIO_PORTB

#define SSD_PIN6        DIO_PIN1
#define SSD_PIN6_PORT   DIO_PORTB



#endif

#endif //__7SEGMENT_CONFIG__