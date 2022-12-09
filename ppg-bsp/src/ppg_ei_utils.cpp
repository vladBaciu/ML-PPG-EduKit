/**
 *   @file    ppg_ei_utils.c
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
#include "ppg_ei_utils.h"
#include "ppg_oled_driver.h"
#include "ppg_mtb_adc.h"
#include "ppg_led_driver.h"
#include "ppg_max30102.h"
#include "ppg_config.h"
#include "ppg_milliseconds.h"
#include "ppg_oled_driver.h"

#include "edge-impulse-sdk/porting/ei_classifier_porting.h"
#include "edge-impulse-sdk/classifier/ei_run_classifier.h"

#include "cyhal.h"
/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 *  ==============================================================================================*/


/*==================================================================================================
 *                                       LOCAL MACROS
 *  ==============================================================================================*/
#define PPG_GREEN_WAVELENGTH   (0U)
#define PPG_RED_WAVELENGTH     (1U)
#define PPG_IR_WAVELENGTH      (2U)

#define PPG_INTERVAL_MS      (1000U / ((PPG_STREAM_DATA_FREQUENCY * 3U) + 1))
#define PPG_ACTIVE_TIME      ((PPG_LED_DUTY_CYCLE * PPG_INTERVAL_MS)/100U)


/*==================================================================================================
 *                                      LOCAL CONSTANTS
 *  ==============================================================================================*/

// Raw features copied from test sample
static const float raw_signal[] = {
    377, 273, 667, 380, 276, 667, 380, 275, 663, 379, 268, 663, 373, 263, 658, 370,
    261, 656, 368, 261, 657, 366, 260, 654, 369, 258, 654, 367, 257, 650, 365, 252,
    649, 361, 250, 649, 359, 250, 645, 358, 246, 644, 354, 244, 643, 360, 251, 650,
    371, 266, 662, 377, 276, 665, 382, 276, 667, 379, 272, 660, 375, 265, 656, 369,
    258, 654, 364, 258, 650, 368, 258, 652, 363, 254, 649, 362, 254, 647, 360, 250,
    647, 356, 247, 645, 356, 245, 643, 352, 243, 641, 350, 241, 638, 351, 241, 641,
    360, 256, 654, 374, 270, 662, 377, 276, 666, 377, 275, 664, 376, 268, 662, 372,
    265, 655, 368, 256, 652, 366, 257, 651, 362, 257, 649, 364, 255, 650, 362, 254,
    648, 360, 249, 646, 359, 245, 644, 356, 248, 642, 355, 244, 642, 353, 242, 638,
    352, 243, 639, 359, 253, 652, 369, 269, 661, 379, 274, 665, 378, 272, 661, 376,
    269, 658, 372, 263, 656, 366, 259, 652, 364, 255, 651, 360, 255, 650, 360, 255,
    645, 362, 251, 648, 359, 251, 646, 358, 247, 644, 354, 245, 643, 350, 243, 640,
    352, 238, 638, 351, 242, 641, 358, 252, 650, 367, 263, 659, 372, 269, 659, 375,
    265, 660, 371, 262, 650, 367, 255, 650
};

static uint32_t ppg_signal[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE] = {0U};
/*==================================================================================================
 *                                      LOCAL VARIABLES
 *  ==============================================================================================*/


/*==================================================================================================
 *                                      GLOBAL CONSTANTS
 *  ==============================================================================================*/
#if (MAIN_APP == PPG_APP_EI_STREAM_DATA)
const uint8_t ppgStreamingText[] = "Streaming data to Edge Impulse ...";
const uint8_t ppgConnectionText[] = "Connection: serial";
#endif
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

static void PPG_ReadChannel(uint8_t index, uint32_t *buf)
{
    switch(index)
    {
        case PPG_GREEN_WAVELENGTH:
        TLC5925_enableGreen();
        break;
        case PPG_RED_WAVELENGTH:
        TLC5925_enableRed();
        break;
        case PPG_IR_WAVELENGTH:
        TLC5925_enableIR();
        break;
    }
    CyDelay(PPG_ACTIVE_TIME);
    *buf = PpgGetResult(PPG_ADC_SAR_CHANNEL);
    CyDelay(PPG_ACTIVE_TIME);
    TLC5925_disableAll();
    
}

static void PPG_ReadChannels(uint32_t *buf)
{
    PPG_ReadChannel(PPG_GREEN_WAVELENGTH, buf++);
    PPG_ReadChannel(PPG_RED_WAVELENGTH, buf++);
    PPG_ReadChannel(PPG_IR_WAVELENGTH, buf);
}

// Callback: fill a section of the out_ptr buffer when requested
static int get_signal_data(size_t offset, size_t length, float *out_ptr) {
    for (size_t i = 0; i < length; i++) {
        out_ptr[i] = (ppg_signal + offset)[i];
    }

    return EIDSP_OK;
}


/***************************************************************************
 * Function: PPG_UtilsDisplayStringArray
 *
 * Description: Display text on OLED LCD
 **************************************************************************/
static void PPG_UtilsDisplayStringArray(const uint8_t *pStringBuffer, uint16_t buffLen, uint8_t textSize, uint32_t coords, bool clearDisplay)
{
    if(TRUE == clearDisplay)
    {
        display_clear();
    }

    gfx_setTextColor(WHITE);
    gfx_setTextSize(textSize);
    gfx_setCursor((coords >> 16U) & 0xFF, coords & 0xFF);
    for(uint8_t i = 0 ; i < buffLen ; i++){
            gfx_write(*(pStringBuffer + i));
      }

    display_update();
}

/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
 *  ==============================================================================================*/




#if (MAIN_APP == PPG_APP_EI_STREAM_DATA)
void PPG_UtilsAppStreamingData(void)
{
    uint32_t channelBuffer[3U] = {0UL};
    uint32_t lastMsValue = 0UL;
    uint8_t channelIndex = 0U;
    
    display_clear(); 
    display_update();
    CyDelay(500UL);

    PPG_UtilsDisplayStringArray(ppgStreamingText,  sizeof(ppgStreamingText)  - 1U, 1U, ((15UL << 16) | 10UL), FALSE);
    PPG_UtilsDisplayStringArray(ppgConnectionText, sizeof(ppgConnectionText) - 1U, 1U, ((10UL << 16) | 50UL), FALSE);

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
            ei_printf("%lu,%lu,%lu\n", channelBuffer[0U], channelBuffer[1U], channelBuffer[2U]);
            channelIndex=0U;
        }
    }
}
#endif

#if (MAIN_APP == PPG_APP_EI_INFERENCE_ACQUIRED_DATA)
void PPG_EI_UtilsAppLiveInference(void)
{
    signal_t signal;            // Wrapper for raw input buffer
    ei_impulse_result_t result; // Used to store inference output
    EI_IMPULSE_ERROR res;       // Return code from inference

    uint32_t lastMsValue = 0UL;
    uint8_t channelIndex = 0U;
    uint32_t samples = 0UL;

    // Assign callback function to fill buffer used for preprocessing/inference
    signal.total_length = EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE;
    signal.get_data = &get_signal_data;

    for(;;)
    {
        while(signal.total_length != samples)
        {
            if(MILLIS_GetValue() > lastMsValue + PPG_INTERVAL_MS)
            {
                lastMsValue = MILLIS_GetValue();
                PPG_ReadChannel(channelIndex, &ppg_signal[samples++]);
                channelIndex = ++channelIndex % 3U;
            }
        }

        // Perform DSP pre-processing and inference
        res = run_classifier(&signal, &result, false);

        // Print return code and how long it took to perform inference
        ei_printf("run_classifier returned: %d\r\n", res);
        ei_printf("Timing: DSP %d ms, inference %d ms, anomaly %d ms\r\n",
                result.timing.dsp,
                result.timing.classification,
                result.timing.anomaly);

        ei_printf("Predictions:\r\n");
        for (uint16_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
            ei_printf("  %s: ", ei_classifier_inferencing_categories[i]);
            ei_printf("%.5f\r\n", result.classification[i].value);
        }

        channelIndex = 0U;
        samples = 0UL;
    }
}
#endif


#if (MAIN_APP == PPG_APP_EI_INFERENCE_HARDCODED_DATA)
void PPG_EI_UtilsAppStaticInference(void)
{
    signal_t signal;            // Wrapper for raw input buffer
    ei_impulse_result_t result; // Used to store inference output
    EI_IMPULSE_ERROR res;       // Return code from inference
    // Calculate the length of the buffer

    size_t buf_len = sizeof(raw_signal) / sizeof(raw_signal[0]);

    // Make sure that the length of the buffer matches expected input length
    if (buf_len != EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE) {
        ei_printf("ERROR: The size of the input buffer is not correct.\r\n");
        ei_printf("Expected %d items, but got %d\r\n",
                EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE,
                (int)buf_len);
    }

    // Assign callback function to fill buffer used for preprocessing/inference
    signal.total_length = EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE;
    signal.get_data = &get_signal_data;

    // Perform DSP pre-processing and inference
    res = run_classifier(&signal, &result, false);

    // Print return code and how long it took to perform inference
    ei_printf("run_classifier returned: %d\r\n", res);
    ei_printf("Timing: DSP %d ms, inference %d ms, anomaly %d ms\r\n",
            result.timing.dsp,
            result.timing.classification,
            result.timing.anomaly);

    ei_printf("Predictions:\r\n");
    for (uint16_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
        ei_printf("  %s: ", ei_classifier_inferencing_categories[i]);
        ei_printf("%.5f\r\n", result.classification[i].value);
    }
}
#endif /* (MAIN_APP == PPG_APP_EI_INFERENCE_HARDCODED_DATA) */

