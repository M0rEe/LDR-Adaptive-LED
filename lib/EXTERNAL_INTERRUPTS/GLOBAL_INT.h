#ifndef __INT_GLOBAL__
#define __INT_GLOBAL__
#include "BitMath.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define SET_GLOBAL_INTERRUPT()          sei()
#define RESET_GLOBAL_INTERRUPT()        cli()

#endif