/**
 *   @file    ppg_utils.c
 *   @author  Vlad-Eusebiu Baciu
 *   @brief   Utils library
 *   @details Includes common functions, macros for all the
 *            custom libraries.
 *            
 */

/*==================================================================================================
 *
 * Copyright Vrije Universiteit Brussel, 2021-2022
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 *  ==============================================================================================*/


/*==================================================================================================
 *                                        INCLUDE FILES
 * 1) system and project includes
 * 2) needed interfaces from external units
 * 3) internal and external interfaces from this unit
 *  ==============================================================================================*/
#include "ppg_utils.h"

#include <cmsis_gcc.h>
#include <stdint.h>
#include "cyhal.h"

#include "ppg_oled_driver.h"
#include "ppg_mtb_adc.h"
#include "ppg_led_driver.h"
#include "ppg_max30102.h"
#include "ppg_config.h"
#include "ppg_milliseconds.h"

/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 *  ==============================================================================================*/


/*==================================================================================================
 *                                       LOCAL MACROS
 *  ==============================================================================================*/

#if (MAIN_APP == PPG_APP_EI_STREAM_DATA)
#define PPG_INTERVAL_MS      (1000U / ((PPG_STREAM_DATA_FREQUENCY * 3U) + 1))
#define PPG_ACTIVE_TIME      ((PPG_LED_DUTY_CYCLE * PPG_INTERVAL_MS)/100U)
#endif
/*==================================================================================================
 *                                      LOCAL CONSTANTS
 *  ==============================================================================================*/


/*==================================================================================================
 *                                      LOCAL VARIABLES
 *  ==============================================================================================*/



/*==================================================================================================
 *                                      GLOBAL CONSTANTS
 *  ==============================================================================================*/

/*==================================================================================================
 *                                      GLOBAL VARIABLES
 *  ==============================================================================================*/

/*==================================================================================================
 *                                   LOCAL FUNCTION PROTOTYPES
 *  ==============================================================================================*/

/*==================================================================================================
 *                                   GLOBAL FUNCTION PROTOTYPES
 *  ==============================================================================================*/

/*==================================================================================================
 *                                       LOCAL FUNCTIONS
 *  ==============================================================================================*/
#if (MAIN_APP == PPG_APP_EI_STREAM_DATA)
static PPG_ReadChannel(uint8_t index, uint32_t *buf)
{
    switch(index)
    {
        case RED_CHANNEL:
        TLC5925_enableRed();
        break;
        case GREEN_CHANNEL:
        TLC5925_enableGreen();
        break;
        case IR_CHANNEL:
        TLC5925_enableIR();
        break;
    }
    CyDelay(PPG_ACTIVE_TIME);
    *buf = PpgGetResult(PPG_ADC_SAR_CHANNEL);
    CyDelay(PPG_ACTIVE_TIME);
    TLC5925_disableAll();
    
}

static PPG_ReadChannels(uint32_t *buf)
{
    PPG_ReadChannel(GREEN_CHANNEL, buf++);
    PPG_ReadChannel(RED_CHANNEL, buf++);
    PPG_ReadChannel(IR_CHANNEL, buf);
}

#endif

/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
 *  ==============================================================================================*/

#if (MAIN_APP == PPG_APP_EI_STREAM_DATA)
void PPG_AppStreamingData(void)
{
    uint32_t channelBuffer[3U] = {0UL};
    uint32_t lastMsValue = 0UL;
    uint8_t channelIndex = 0U;

    MILLIS_AssignISR();

    AD5273_Init();
    
    PpgAdcInit();

    TLC5925_SetCurrent_mA(PPG_LED_CURRENT_MA);
    /* Enable red LED */
    TLC5925_enableRed();

    MILLIS_InitAndStartTimer();

    for(;;)
    {
        if(MILLIS_GetValue() > lastMsValue + PPG_INTERVAL_MS)
        {
            lastMsValue = MILLIS_GetValue();
            PPG_ReadChannel(channelIndex, &channelBuffer[channelIndex]);
            channelIndex++;
        }
        if(3U == channelIndex)
        {
            printf("%lu,%lu,%lu\n", channelBuffer[0U], channelBuffer[1U], channelBuffer[2U]);
            channelIndex=0U;
        }
    }
}
#endif

/***************************************************************************
 * Function: displayStringArray
 *
 * Description: Display text on OLED LCD
 **************************************************************************/
void displayStringArray(uint8_t *pStringBuffer, uint16_t buffLen, uint8_t textSize, uint32_t coords)
{
    display_clear();
    gfx_setTextColor(WHITE);
    gfx_setTextSize(textSize);
    gfx_setCursor((coords >> 16U) & 0xFF, coords & 0xFF);
    for(uint8_t i = 0 ; i < buffLen ; i++){
            gfx_write(*(pStringBuffer + i));
      }

    display_update();
    CyDelay(800);
    display_clear();
}

/***************************************************************************
 * Function: HandleError    
 *
 * Description: Disable IRQ and enter an infinite loop.
 **************************************************************************/
void HandleError(void)
{   
     /* Disable all interrupts. */
	__ASM volatile ("cpsid i" : : : "memory");
    
    /* Infinite loop. */
    while(1u) {}
}
