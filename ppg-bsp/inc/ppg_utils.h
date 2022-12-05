/**
 *   @file    ppg_utils.h
 *   @author  Vlad-Eusebiu Baciu
 *   @brief   Export utils definitions and functions.
 *   @details Export common APIs, macros used in custom libs.
 *
 */

/*==================================================================================================
 *
 * Copyright Vrije Universiteit Brussel, 2021-2022
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 *  ==============================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef UTILS_H
#define UTILS_H

/*==================================================================================================
 *                                        INCLUDE FILES
 *  ==============================================================================================*/

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
    
/*==================================================================================================
 *                                          CONSTANTS
 *  ==============================================================================================*/


/*==================================================================================================
 *                                      DEFINES AND MACROS
 *  ==============================================================================================*/

/* @brief Just a redefinition */
#define TRUE                      true
#define FALSE                     false

/* @brief Data transfer status values */
#define TRANSFER_CMPLT        (0x00UL)
#define TRANSFER_ERROR        (0xFFUL)
    
/* @brief MIN and MAX functions */
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
    
/*==================================================================================================
 *                                             ENUMS
 *  ==============================================================================================*/



/*==================================================================================================
 *                                STRUCTURES AND OTHER TYPEDEFS
 *  ==============================================================================================*/



/*==================================================================================================
 *                                GLOBAL VARIABLE DECLARATIONS
 *  ==============================================================================================*/


/*==================================================================================================
 *                                    FUNCTION PROTOTYPES
 *  ==============================================================================================*/

void PPG_AppStreamingData(void);
void displayStringArray(uint8_t *pStringBuffer, uint16_t buffLen, uint8_t textSize, uint32_t coords);
void HandleError(void);


#endif /* UTILS_H */

#ifdef __cplusplus
}
#endif
