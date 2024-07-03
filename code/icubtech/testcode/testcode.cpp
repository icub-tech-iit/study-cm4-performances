
/*
 * Copyright (C) 2024 iCub Tech - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
*/


// --------------------------------------------------------------------------------------------------------------------
// - public interface
// --------------------------------------------------------------------------------------------------------------------

#include "testcode.h"


// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------

// to see HAL 
#include "hal.h"

// to see the scope
#include "embot_app_scope.h"

#include "embot_hw_sys.h"

#include <array>

using namespace std;

// --------------------------------------------------------------------------------------------------------------------
// - implementation
// --------------------------------------------------------------------------------------------------------------------


#if 0

    description
    
    we want to execute some testcode() full of some math operations and measure its duration
    to measure the time we use a dedicated object called scope that sends an itm stimulus
    that is detected by the eventviewer of MDK Keil.
    we can also use something that toggles a pin.


#endif

namespace measure {
    
    void init();
    void start();
    void stop();
}

namespace test {
    
    void init();
    void execute();
}


// the C functions

void testcode_init()
{
    measure::init();
    test::init();
}

void testcode_tick()
{
    measure::start();
    test::execute();
    measure::stop();    
}


// the C++ implementation




namespace measure {
    
    void DURATION() {}
    embot::app::scope::SignalEViewer *sev {nullptr};
    embot::app::scope::SignalEViewer::Config evc {DURATION, embot::app::scope::SignalEViewer::Config::LABEL::one};
    
    void init()
    {
        sev = new embot::app::scope::SignalEViewer(evc);        
    }
    
    void start()
    {
        __disable_irq();
        sev->on();
    }
    
    void stop()
    {
        sev->off(); 
        __enable_irq();        
    }
}


namespace test {
     
       
    
    void dummy()
    {
        constexpr embot::core::Time usec2wait {100*embot::core::time1microsec};
        embot::hw::sys::delay(usec2wait);      
    }    
    
    constexpr size_t bufferSize {64};
    volatile float buffer1[bufferSize] = {0};
    volatile float buffer2[bufferSize] = {0};
    volatile float buffer3[bufferSize] = {0};
    
    void test1()
    {
        constexpr size_t num {100};
        for(size_t n=0; n<num; n++)
        {
            for(size_t i=0; i<bufferSize; i++)
            {
                buffer1[i] = buffer2[i] = 1.0 + static_cast<float>(i); // never zero
            }
            for(size_t i=0; i<bufferSize; i++)
            {
                buffer3[i] = buffer1[i] * buffer2[i] + buffer2[i] / static_cast<float>(1.0f + buffer1[i]);
            }            
        }
              
    }

    void test2()
    {
        constexpr size_t num {100};
        for(size_t n=0; n<num; n++)
        {
            for(size_t i=0; i<bufferSize; i++)
            {
                buffer1[i] = buffer2[i] = 1.0 + static_cast<float>(i); // never zero
            }
            for(size_t i=0; i<bufferSize; i++)
            {
                size_t pos1 = (i + 3) % bufferSize;
                size_t pos1a = (i + 8) % bufferSize;
                size_t pos2 = (i + 20) % bufferSize;
                size_t pos2a = (i + 15) % bufferSize;
                size_t pos3 = (i + 35) % bufferSize;
                buffer3[pos3] = buffer1[pos1] * buffer2[pos2] + buffer2[pos2a] / static_cast<float>(1.0f + buffer1[pos1a]);
            }            
        }
              
    }
    
    float jjj(float i)
    {
        if(i>3.0)
        {
            return std::cos(i);
        }
        
        return std::sin(i+1);
    }
 
    float iii(float i)
    {
        if(i>2.0)
        {
            return std::sin(i);
        }
        
        return std::cos(i+1);
    }
    
    void test3()
    {
        constexpr size_t num {1};
        for(size_t n=0; n<num; n++)
        {
            for(size_t i=0; i<bufferSize; i++)
            {
                buffer1[i] = buffer2[i] = 1.0 + static_cast<float>(i); // never zero
            }
            for(size_t i=0; i<bufferSize; i++)
            {
                size_t pos1 = (i + 3) % bufferSize;
                size_t pos1a = (i + 8) % bufferSize;
                size_t pos2 = (i + 20) % bufferSize;
                size_t pos2a = (i + 15) % bufferSize;
                size_t pos3 = (i + 35) % bufferSize;
                buffer3[pos3] = buffer1[pos1] * buffer2[pos2] + buffer2[pos2a] / static_cast<float>(1.0f + buffer1[pos1a]);
                uint8_t val {0};
                if(buffer3[pos3] > 1000.0f)
                {
                    val = 0;
                }
                else if(buffer3[pos3] > 100.0f)
                {
                    val = 1;
                }  
                else if(buffer3[pos3] > 10.0f)
                {
                    val = 2;
                } 
                else if(buffer3[pos3] > 1.0f)
                {
                    val = 3;
                }  
                else
                {
                    val = 4;
                }      
                switch(val)
                {
                    case 0:
                    {
                        buffer1[pos1] = std::cos(buffer2[pos2a]);
                        buffer2[pos1] = std::sin(buffer2[pos2]);
                    } break;
                    case 1:
                    {
                        buffer2[pos1] = std::sin(buffer2[pos2a]);
                        buffer3[pos1] = std::atan(buffer1[pos2]);
                    } break;
                    case 3:
                    {
                        buffer2[pos1] = jjj(buffer2[pos2a]);
                        buffer3[pos1] = iii(buffer1[pos2]);
                    } break;
                    case 4:
                    default:
                    {
                        buffer1[pos1] = iii(buffer2[pos2a]);
                        buffer2[pos1] = jjj(buffer1[pos2]);
                    } break;
                }                    
            }            
        }
              
    }


    // and now the test
    
    void init() {}
        
    void execute()
    {        
#if !defined(TESTcode) 
    #error you must define TESTcode to be one of {DUMMY, TEST1, TEST2, TEST3}
#elif   (TESTcode == DUMMY)
        dummy();
#elif   (TESTcode == TEST1)       
        test1();
#elif   (TESTcode == TEST2)      
        test2();
#elif   (TESTcode == TEST3)      
        test3();        
#else
    #error you must define TESTcode to be one of {DUMMY, TEST1, TEST2, TEST3}
#endif  

    }
    
}


// - end-of-file (leave a blank line after)----------------------------------------------------------------------------

