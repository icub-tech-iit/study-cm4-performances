
/*
 * Copyright (C) 2012 iCub Facility - Istituto Italiano di Tecnologia
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
#ifndef _EVENTVIEWER_H_
#define _EVENTVIEWER_H_

#ifdef __cplusplus
extern "C" {
#endif

// - doxy begin -------------------------------------------------------------------------------------------------------

/** @file       eventviewer.h
    @brief      This header file implements public interface to the hal trace module.
    @author     marco.accame@iit.it
    @date       09/09/2011
**/

/** @defgroup eventviewer Event Viewer

    The event viewer is used on CM3 and CM4 MPU to communicate to UV4 by Keil changes of the executing code, so that
    the timing of some code can be mesured in runtime.
    
    To view the timing it is required to connect the target with the ULINKpro by and run the project with some
    options being set. The execution timing is seen on the relevant window of UV4.
    
    The options to set are: (1) use of a proper .ini file in the Options/Debug window of UV4, (2) proper initialisation
    of the Option/Debug/Settings/Trace window, (3) sue of RTX kernel in teh Options/Target/Operating System window.
    
    After the launch of the debug the window is displayed with menu Debug/OS Support/Event Viewer.
    
    The content of window depends on the used calls of this SW package. 
    
    @{        
 **/


// - external dependencies --------------------------------------------------------------------------------------------

#include "stdint.h"



// - public #define  --------------------------------------------------------------------------------------------------
// empty-section
  

// - declaration of public user-defined types ------------------------------------------------------------------------- 

/** @typedef    typedef enum evResult_t
    @brief      contains the result of the functions.
 **/
typedef enum
{
    ev_res_OK               = 0,
    ev_res_NOK_generic      = -1
} evResult_t;


/** @typedef    typedef enum ev_IDs_t
    @brief      contains the basic IDs to be used.
 **/
typedef enum
{
    ev_ID_idle              = 1,        /**< the idle ID: use this as initial ID and when there is no relevant activity */
    ev_ID_first_ostask      = 2,        /**< use this and successive 93 IDs for os tasks */
    ev_ID_first_usrdef      = 96,       /**< use this and successive 31 IDs for for user-defined activities */
    ev_ID_pendsv            = 128,      /**< use this for pendsv */
    ev_ID_systick           = 129,      /**< use this for systick */
    ev_ID_svc               = 130,      /**< use this for svc */
    ev_ID_first_isr         = 131       /**< use this and successive for ISRs */
} ev_IDs_t;


/** @typedef    typedef uint8_t evEntityId_t
    @brief      contains the extended IDs derived from the @e ev_IDs_t values. For instance, a user-defined ID can be 
                a evEntityId_t variable equal to ev_ID_first_usrdef+1.               
 **/
typedef uint8_t evEntityId_t;


/** @typedef    typedef void (*evEntityName_t)(void)
    @brief      the type used for the name to be displayed on uv4.               
 **/
typedef void (*evEntityName_t)(void); 
 
// - declaration of extern public variables, ... but better using use _get/_set instead -------------------------------
// empty-section





// - declaration of extern public functions ---------------------------------------------------------------------------


/** @fn         extern evResult_t eventviewer_init(void)
    @brief      Initialises the trace peripheral for use with the event viewer of uv4.
    @return     ev_res_OK upon success
    @warning    The function requires a proper .ini file for the toolchain.
 **/
extern evResult_t eventviewer_init(void);


/** @fn         extern void eventviewer_load(evEntityId_t id, evEntityName_t name)
    @brief      loads a given entity name with a given id. if not yet initted it attempt an init.
    @param      id          the ID to load
    @param      name        the name displayed on uv4
 **/
extern void eventviewer_load(evEntityId_t id, evEntityName_t name);


/** @fn         extern void eventviewer_unload(evEntityId_t id, evEntityName_t name)
    @brief      unloads a given entity name with a given id. if not yet initted it attempt an init.
    @param      id          the ID to unload
    @param      name        the name displayed on uv4
 **/
extern void eventviewer_unload(evEntityId_t id, evEntityName_t name);


/** @fn         extern evEntityId_t eventviewer_switch_to(evEntityId_t id)
    @brief      loads into uv4 the given id. if not yet initted it does nothing.
    @param      id          the ID to switch to
    @return     the previous ID 
 **/
extern evEntityId_t eventviewer_switch_to(evEntityId_t id);
 
 
 
 /** @}            
    end of group eventviewer  
 **/
 
#ifdef __cplusplus
}       // closing brace for extern "C"
#endif 

#endif  // include-guard


// - end-of-file (leave a blank line after)----------------------------------------------------------------------------



