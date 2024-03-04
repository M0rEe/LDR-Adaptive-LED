#ifndef __KEYPAD_CONFIG__
#define __KEYPAD_CONFIG__

#include "DIO_interface.h"


#define HIGH            DIO_PIN_HIGH
#define LOW             DIO_PIN_LOW

#define MAX_ROW_SIZE    4
#define MAX_COL_SIZE    4

//TODO support MORE OR LESS PINS 
//depends on pins are pulled high or low 
#define ACTIVATOR       LOW
#define NOT_ACTIVATOR   HIGH

/* Rows*/
#define ROW1_PORT   DIO_PORTC
#define ROW2_PORT   DIO_PORTC
#define ROW3_PORT   DIO_PORTC
#define ROW4_PORT   DIO_PORTC

#define ROW1_PIN    DIO_PIN5
#define ROW2_PIN    DIO_PIN4
#define ROW3_PIN    DIO_PIN3
#define ROW4_PIN    DIO_PIN2
/* Columns*/
#define COL1_PORT   DIO_PORTD
#define COL2_PORT   DIO_PORTD
#define COL3_PORT   DIO_PORTD
#define COL4_PORT   DIO_PORTD

#define COL1_PIN    DIO_PIN7
#define COL2_PIN    DIO_PIN6
#define COL3_PIN    DIO_PIN5
#define COL4_PIN    DIO_PIN3

#endif

// If size of rows or cols changes array must be //!UPDATED  


