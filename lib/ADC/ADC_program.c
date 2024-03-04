#include "ADC_interface.h"
#include "ADC_private.h"

#define ADC_MODULE_ENABLE() (Set_Bit(ADCSRA, ADEN))
#define ADC_MODULE_DISABLE() (Clr_Bit(ADCSRA, ADEN))

#define ADC_START_CONVERSION() (Set_Bit(ADCSRA, ADSC))
#define ADC_READ_INTERRUPT_FLAG() (Get_Bit(ADCSRA, ADIF))

#define ADC_INTERRUPT_ENABLE() (Set_Bit(ADCSRA, ADIE))
#define ADC_INTERRUPT_DISABLE() (Clr_Bit(ADCSRA, ADIE))

#define ADCHL_VALUE (*(volatile u16 *)0x24);

void ADC_voidInit(ADC_VRef_t copyVref_enum,
                  u8 copy_u8LftAdjust, ADC_Channels_t copy_ADC_Channels_enm_Index,
                  ADC_Auto_Trigger_Src_t copy_ADC_Autotrig_enum_state,
                  ADC_Prescaller_t copy_Prescaler_enum_Index,
                  u8 copy_u8Intterrupt_state)
{
    ADC_MODULE_DISABLE();
    ADMUX |= (copyVref_enum << REFS0);
    ADMUX |= (copy_u8LftAdjust << ADLAR);
    ADMUX |= (copy_ADC_Channels_enm_Index << MUX0);
    (copy_u8Intterrupt_state == ADC_INT_DISABLE) ? Clr_Bit(ADCSRA, ADIE) : Set_Bit(ADCSRA, ADIE);
    if (copy_ADC_Autotrig_enum_state == AUTO_TRIG_DISABLE)
    {
        Clr_Bit(ADCSRA, ADATE);
    }
    else
    {
        Set_Bit(ADCSRA, ADATE);
        SFIOR |= (copy_ADC_Autotrig_enum_state << ADTS0);
    }
    ADCSRA |= (copy_Prescaler_enum_Index << ADPS0);
    ADC_MODULE_ENABLE();
}

// Blocking
u16 ADC_u16Read_Channel(ADC_Channels_t copy_ADC_Channels_enum_Index,
                        ADC_VRef_t copyVref_enum,
                        ADC_Prescaller_t copy_Prescaler_enum_Index)
{
    ADC_MODULE_DISABLE();
    ADMUX |= (copyVref_enum << REFS0);
    ADMUX |= (copy_ADC_Channels_enum_Index << MUX0);
    ADC_MODULE_ENABLE();
    ADC_START_CONVERSION();
    while (!ADC_READ_INTERRUPT_FLAG())
        ;
    return ADCHL_VALUE;
}