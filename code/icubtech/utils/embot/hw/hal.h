
/*
 * Copyright (C) 2024 iCub Tech - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
*/

// - include guard ----------------------------------------------------------------------------------------------------

#ifndef __HAL_H_
#define __HAL_H_

// to see HAL 
#if defined(STM32HAL_STM32G4)
#include "stm32g4xx_hal.h"
#elif defined(STM32HAL_STM32H7)
#include "stm32h7xx_hal.h"
#else
#error pls define either STM32HAL_STM32G4 or STM32HAL_STM32H7
#endif


#endif  // include-guard


// - end-of-file (leave a blank line after)----------------------------------------------------------------------------
