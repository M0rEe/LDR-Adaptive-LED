#ifndef __ADC_INTERFACE__
#define __ADC_INTERFACE__
#include "Std_Types.h"
typedef enum
{
    ADC_preScaler_DIV_BY_2 = 1,
    ADC_preScaler_DIV_BY_4,
    ADC_preScaler_DIV_BY_8,
    ADC_preScaler_DIV_BY_16,
    ADC_preScaler_DIV_BY_32,
    ADC_preScaler_DIV_BY_64,
    ADC_preScaler_DIV_BY_128
} ADC_Channels_t;

typedef enum
{
    ADC0_IDX = 0,
    ADC1_IDX,
    ADC2_IDX,
    ADC3_IDX,
    ADC4_IDX,
    ADC5_IDX,
    ADC6_IDX,
    ADC7_IDX
} ADC_Prescaller_t; // TODO COMPLETE DIFFERENTIAL CHANNELS

typedef enum
{
    ADC_AREF = 0,
    ADC_AVCC,
    ADC_INTERNAL2_56 = 4
} ADC_VRef_t;

typedef enum
{
    FREE_RUNNING_MODE = 0,
    ANALOG_COMPARATOR,
    EXINT_REQUEST0,
    TIMER_COUNTER0_CMP_MATCH,
    TIMER_COUNTER0_OVRFLW,
    TIMER_COUNTER1_CMP_MATCHB,
    TIMER_COUNTER1_OVRFLW,
    TIMER_COUNTER_CAP_EVENT,
    AUTO_TRIG_DISABLE
} ADC_Auto_Trigger_Src_t;

#define ADC_RIGHT_ADJUST 0
#define ADC_LEFT_ADJUST 1

#define ADC_ENABLE 1
#define ADC_DISABLE 0

#define ADC_AUTO_TRIGGER_ON 1
#define ADC_AUTO_TRIGGER_OFF 0

#define ADC_INT_ENABLE 1
#define ADC_INT_DISABLE 0


/**
 * @return void
 * @param : copyVref_enum                       voltage Referrence
 * @param : copy_u8LftAdjust                    Left Adjust
 * @param : copy_ADC_Channels_enm_Index         Index Of channel
 * @param : copy_ADC_Autotrig_enum_state        ADC Auto Trigger
 * @param : copy_Prescaler_enum_Index           Pre-Scaller value
 * @param : copy_u8Intterrupt_state             Interrupt Enable/Disable
 * @brief : Initialize ADC module with given arguments
 */
void ADC_voidInit(ADC_VRef_t copyVref_enum,
                  u8 copy_u8LftAdjust, ADC_Channels_t copy_ADC_Channels_enm_Index,
                  ADC_Auto_Trigger_Src_t copy_ADC_Autotrig_enum_state,
                  ADC_Prescaller_t copy_Prescaler_enum_Index,
                  u8 copy_u8Intterrupt_state);

// Blocking
/**
 * @return u16
 * @param : copyVref_enum                       voltage Referrence
 * @param : copy_ADC_Channels_enum_Index         Index Of channel
 * @param : copy_Prescaler_enum_Index           Pre-Scaller value
 * @brief : Modify ADC Module then Reading Given Channel  
 */
u16 ADC_u16Read_Channel(ADC_Channels_t copy_ADC_Channels_enum_Index,
                        ADC_VRef_t copyVref_enum,
                        ADC_Prescaller_t copy_Prescaler_enum_Index);
#endif