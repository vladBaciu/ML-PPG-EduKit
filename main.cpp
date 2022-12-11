
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

#include "ppg_config.h"
#include "ppg_mtb_adc.h"
#include "ppg_milliseconds.h"
#include "ppg_oled_driver.h"
#include "ppg_digi_pot.h"
#include "ppg_led_driver.h"
#include "ppg_utils.h"
#include "ppg_ei_utils.h"


int main(int argc, char **argv) {

	cy_rslt_t result_init;

    /* Initialize the device and board peripherals */
    result_init = cybsp_init();

    /* Board init failed. Stop program execution */
    if (result_init != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Enable global interrupts */
    __enable_irq();

    /* Initialize retarget-io to use the debug UART port */
    result_init = cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX,
                                 CY_RETARGET_IO_BAUDRATE);

    /* retarget-io init failed. Stop program execution */
    if (result_init != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Assign millis IRQ */
    MILLIS_AssignISR();
    /* Init I2C bus - wrapper in digi pot library. 
       Oled init also does this if I2C is not initialized. */
    AD5273_Init();
    
    /* Init SAR ADC and configure HSIOM for analog pins */
    PpgAdcInit();

    /* Set desired led driver value. 
       Value set using the digital potentiometer. */
    TLC5925_SetCurrent_mA(PPG_LED_CURRENT_MA);

    /* Init and start millis timer */
    MILLIS_InitAndStartTimer();
    
    display_init();
    CyDelay(1000UL);


#if(MAIN_APP == PPG_APP_EI_INFERENCE_HARDCODED_DATA)
    PPG_EI_UtilsAppStaticInference();
#endif /* (MAIN_APP == PPG_APP_EI_INFERENCE_HARDCODED_DATA) */

#if(MAIN_APP == PPG_APP_EI_INFERENCE_ACQUIRED_DATA)
    PPG_EI_UtilsAppLiveInference();
#endif /* (MAIN_APP == PPG_APP_EI_INFERENCE_ACQUIRED_DATA) */

#if (MAIN_APP == PPG_APP_EI_STREAM_DATA)
    PPG_UtilsAppStreamingData();
#endif /* (MAIN_APP == PPG_APP_EI_INFERENCE_ACQUIRED_DATA) */

    return 0;
}