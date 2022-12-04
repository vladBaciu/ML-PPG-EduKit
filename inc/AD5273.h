/**
 *   @file    AD5273BRJZ1.h
 *   @author  Vlad-Eusebiu Baciu
 *   @brief   Library for the AD5273BRJZ1 digital pot.
 *   @details Initialize the digital pot, set resistance, read status. 
 *            
 */

/*==================================================================================================
 *
 * Copyright Vrije Universiteit Brussel, 2021
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 *  ==============================================================================================*/

#ifndef AD5273_H_
#define AD5273_H_

/*==================================================================================================
 *                                        INCLUDE FILES
 * 1) system and project includes
 * 2) needed interfaces from external units
 * 3) internal and external interfaces from this unit
 *  ==============================================================================================*/

#include "utils.h"

    
/*==================================================================================================
 *                                          CONSTANTS
 *  ==============================================================================================*/


/*==================================================================================================
 *                                      DEFINES AND MACROS
 *  ==============================================================================================*/

    
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
    
void AD5273_Init(void);
void AD5273_SetWiper(uint32_t resVal);
uint8_t AD5273_ReadData(void);
uint8_t AD5273_WriteData(uint8_t val);


#endif /* AD5273_H_ */
/* [] END OF FILE */
