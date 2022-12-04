/**
 *   @file    ppg_milliseconds.c
 *   @author  Vlad-Eusebiu Baciu
 *   @brief   MILLS library
 *   @details Library used for time measurement
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

#include "cycfg_peripherals.h"

/* @brief Include custom libraries for PPG EduKit */
#include "ppg_milliseconds.h"

/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 *  ==============================================================================================*/


/*==================================================================================================
 *                                       LOCAL MACROS
 *  ==============================================================================================*/

/* @brief Timer period in nanoseconds */
#define TIMER_PERIOD_NSEC               1000UL
/* @brief Timer instance */
/*==================================================================================================
 *                                      LOCAL CONSTANTS
 *  ==============================================================================================*/


/*==================================================================================================
 *                                      LOCAL VARIABLES
 *  ==============================================================================================*/



/*==================================================================================================
 *                                      GLOBAL CONSTANTS
 *  ==============================================================================================*/
const cy_stc_sysint_t isrConfig =
{
		.intrPriority = 7U,
		.intrSrc = TIMER_1MS_IRQ
};

/*==================================================================================================
 *                                      GLOBAL VARIABLES
 *  ==============================================================================================*/

/* @brief Global variable that keeps track of the time */
volatile uint32 gMilliseconds;

/*==================================================================================================
 *                                   LOCAL FUNCTION PROTOTYPES
 *  ==============================================================================================*/

/*==================================================================================================
 *                                   GLOBAL FUNCTION PROTOTYPES
 *  ==============================================================================================*/

/*==================================================================================================
 *                                       LOCAL FUNCTIONS
 *  ==============================================================================================*/


/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
 *  ==============================================================================================*/

/***************************************************************************
 * Function: MILLIS_InterruptHandler    
 *
 * Description: Timer interrupt handler. Increment gMilliseconds variable
 **************************************************************************/
void MILLIS_InterruptHandler(void)
{
    /* Clear the terminal count interrupt */
    Cy_TCPWM_ClearInterrupt(TIMER_1MS_HW, TIMER_1MS_NUM, CY_TCPWM_INT_ON_TC);
    
    gMilliseconds++;
   
}

/***************************************************************************
 * Function: MILLIS_AssignISR    
 *
 * Description: Assign ISR to Timer ovf
 **************************************************************************/
void MILLIS_AssignISR(void)
{
    Cy_SysInt_Init(&isrConfig, MILLIS_InterruptHandler);
    NVIC_ClearPendingIRQ(TIMER_1MS_IRQ);/* Clears the interrupt */
    NVIC_EnableIRQ(TIMER_1MS_IRQ); /* Enable the core interrupt */
}

/***************************************************************************
 * Function: MILLIS_InitAndStartTimer    
 *
 * Description: Init and start Timer
 **************************************************************************/
void MILLIS_InitAndStartTimer(void)
{
     /* Start the TCPWM component in timer/counter mode. The return value of the
     * function indicates whether the arguments are valid or not. It is not used
     * here for simplicity. */
    (void)Cy_TCPWM_Counter_Init(TIMER_1MS_HW, TIMER_1MS_NUM, &TIMER_1MS_config);
    Cy_TCPWM_Enable_Multiple(TIMER_1MS_HW, TIMER_1MS_MASK); /* Enable the counter instance */
    
    /* Set the timer period in milliseconds. To count N cycles, period should be
     * set to N-1. */
    Cy_TCPWM_Counter_SetPeriod(TIMER_1MS_HW, TIMER_1MS_NUM, TIMER_PERIOD_NSEC - 1);
    
    /* Trigger a software reload on the counter instance. This is required when 
     * no other hardware input signal is connected to the component to act as
     * a trigger source. */
    Cy_TCPWM_TriggerReloadOrIndex(TIMER_1MS_HW, TIMER_1MS_MASK);
}

/***************************************************************************
 * Function: MILLIS_DisableTimer    
 *
 * Description: Disable Timer
 **************************************************************************/
void MILLIS_DisableTimer(void)
{
    Cy_TCPWM_Disable_Multiple(TIMER_1MS_HW, TIMER_1MS_MASK);
}

/***************************************************************************
 * Function: MILLIS_GetValue    
 *
 * Description: Read time value
 **************************************************************************/
uint32_t MILLIS_GetValue(void)
{
    return gMilliseconds;
}
/* [] END OF FILE */
