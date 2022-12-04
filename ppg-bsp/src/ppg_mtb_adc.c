/*
 * PPG_Adc.c
 *
 *  Created on: Nov 12, 2022
 *      Author: baciu
 */
#include "cycfg_routing.h"
#include "cy_sysclk.h"
#include "cycfg_peripherals.h"
#if defined (CY_USING_HAL)
    #include "cyhal_hwmgr.h"

#endif //defined (CY_USING_HAL)
#define CYREG_HSIOM_AMUX_SPLIT_CTL1 0x40312004u
#define CYREG_HSIOM_AMUX_SPLIT_CTL2 0x40312008u
#define CYREG_HSIOM_AMUX_SPLIT_CTL3 0x4031200cu
#define CYREG_HSIOM_AMUX_SPLIT_CTL4 0x40312010u
#define CYREG_HSIOM_AMUX_SPLIT_CTL5 0x40312014u
#define CYREG_HSIOM_AMUX_SPLIT_CTL6 0x40312018u
#define CYREG_HSIOM_AMUX_SPLIT_CTL7 0x4031201cu
#define CYREG_HSIOM_AMUX_SPLIT_CTL8 0x40312020u
#define CYREG_SAR_CTRL 0x411d0000u
#define CYREG_SAR_MUX_SWITCH0 0x411d0300u
#define CYREG_PASS_AREF_AREF_CTRL 0x411f0e00u

extern const cy_stc_sar_config_t ADC_SAR_config;

static void ADC_StartConvert(void)
{
    if (SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk == (ADC_SAR_HW->SAMPLE_CTRL & SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk))
    {
        Cy_SAR_StartConvert(ADC_SAR_HW, CY_SAR_START_CONVERT_CONTINUOUS);
    }
    else
    {
        Cy_SAR_StartConvert(ADC_SAR_HW, CY_SAR_START_CONVERT_SINGLE_SHOT);
    }
}

static uint32_t ADC_IsEndConversion(cy_en_sar_return_mode_t retMode)
{
    uint32 endOfConversion = 0u;
    cy_en_sar_status_t result;

    result = Cy_SAR_IsEndConversion(ADC_SAR_HW, retMode);

    if (result == CY_SAR_SUCCESS)
    {
        endOfConversion = 1u;
    }

    return endOfConversion;
}


void PpgAdcInit(void)
{
	CY_SET_REG32(CYREG_HSIOM_AMUX_SPLIT_CTL4, 0x00000030u);
	CY_SET_REG32(CYREG_HSIOM_AMUX_SPLIT_CTL5, 0x00000030u);
	CY_SET_REG32(CYREG_SAR_CTRL, 0x80000000u);
	CY_SET_REG32(CYREG_SAR_MUX_SWITCH0, 0x00080000u);
	CY_SET_REG32(CYREG_PASS_AREF_AREF_CTRL, 0x80110001u);



	(void)Cy_SAR_DeInit(ADC_SAR_HW, false);
	(void)Cy_SAR_Init(ADC_SAR_HW, &ADC_SAR_config);

	Cy_SAR_Enable(ADC_SAR_HW);
}

uint32_t PpgGetResult(uint8_t channel)
{
	ADC_StartConvert();

	while(ADC_IsEndConversion(CY_SAR_RETURN_STATUS) != 0);

	return Cy_SAR_GetResult32(ADC_SAR_HW, channel);
}
