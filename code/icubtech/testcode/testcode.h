
/*
 * Copyright (C) 2024 iCub Tech - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
*/

// - include guard ----------------------------------------------------------------------------------------------------

#ifndef __TESTCODE_H_
#define __TESTCODE_H_

// keeps C interfaces so that we can call them from a C module

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


// macros used to change the test

#define DUMMY 100
#define TEST1 1
#define TEST2 2
#define TEST3 3
    
#define TESTcode TEST3   

void testcode_init();

void testcode_tick();

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif  // include-guard


// - end-of-file (leave a blank line after)----------------------------------------------------------------------------
