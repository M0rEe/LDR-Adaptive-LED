#ifndef __SPI_INTERFACE__
#define __SPI_INTERFACE__

#include "Std_Types.h"
#define SELECTED 1
#define DISABLE  0


#define SPI_MASTER_MODE SELECTED
#define SPI_SLAVE_MODE DISABLE

#define SPI_LSB SELECTED
#define SPI_MSB DISABLE

#define SPI_CLK_Falling_Rising SELECTED
#define SPI_CLK_Rising_Falling DISABLE

#define SPI_CLK_Setup_Sample SELECTED
#define SPI_CLK_Sample_Setup DISABLE


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

/*
 * @return : void
 * @param  : copy_u8MasterSalveMode      MCU Master/Slave Mode
 * @param  : copy_enumSPI_FREQ           Enum of SPI_Frequency/CLK
 * @brief  : Initialize SPI Module With Predefined Configurations and post build touch-ups
 **/
void SPI_voidInit(u8 copy_u8MasterSalveMode,
                  SPI_FREQ_t copy_enumSPI_FREQ);

/*
 * @return : void
 * @param  : copy_u8SendData            Data to be sent either Master/slave
 * @param  : copy_pu8RecvData           Data to be received
 * @brief  : BLOCKING function to SEND/RECEIVE simultaneously
 **/
void SPI_voidSendRecv(u8 copy_u8SendData, u8 *copy_pu8RecvData);

/*
 * @return : void
 * @param  : copy_u8SendData            Data to be sent either Master/slave
 * @param  : copy_pu8RecvData           Data to be received
 * @brief  : NON-BLOCKING function to Put Data to be sent on request for next available sent frame
  !@warning: MUST ENABLE GLOBAL INTERRUPT BEFORE THE USAGE OF THIS FUNCTION 
 **/
void SPI_voidSendNoNBlocking(u8 copy_u8SendData, void (*copy_pfCallback)(u8 copy_pu8RecvData));

#endif
