#ifndef __SPI_INTERFACE__
#define __SPI_INTERFACE__

#include "Std_Types.h"


#define SPI_MASTER_MODE 1
#define SPI_SLAVE_MODE 0


#define SPI_LSB     1
#define SPI_MSB     0

#define SPI_CLK_Falling_Rising    1
#define SPI_CLK_Rising_Falling    0

#define SPI_CLK_Setup_Sample    1
#define SPI_CLK_Sample_Setup    0

typedef enum
{
    SPI_F_osc_div_by4 = 0,
    SPI_F_osc_div_by16 = 1,
    SPI_F_osc_div_by64 = 2,
    SPI_F_osc_div_by128 = 3,
    SPI_F_osc_div_by2 = 4,
    SPI_F_osc_div_by8 = 5,
    SPI_F_osc_div_by32 = 6,
    SPI_F_osc_div_by64D = 7
} SPI_FREQ_t;

void SPI_voidInit(u8 copy_u8MasterSalveMode,
                  SPI_FREQ_t copy_enumSPI_FREQ);
void SPI_voidSendRecv(u8 copy_u8SendData, u8 *copy_pu8RecvData);

#endif
