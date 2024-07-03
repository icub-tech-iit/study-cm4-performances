
/*
 * Copyright (C) 2017 iCub Facility - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
 * website: www.robotcub.org
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

// - include guard ----------------------------------------------------------------------------------------------------

#ifndef _EMBOT_HW_SYS_H_
#define _EMBOT_HW_SYS_H_

#include "embot_core.h"

#include <string>


namespace embot::hw::sys {
       

    
    // forces the cpu to exec instructions to reach a given delay
    void delay(embot::core::relTime t);    
    
        
    
} // namespace embot::hw ::sys {



#endif  // include-guard


// - end-of-file (leave a blank line after)----------------------------------------------------------------------------


