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


// --------------------------------------------------------------------------------------------------------------------
// - public interface
// --------------------------------------------------------------------------------------------------------------------

#include "embot_tools.h"




// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------



// --------------------------------------------------------------------------------------------------------------------
// - pimpl: private implementation (see scott meyers: item 22 of effective modern c++, item 31 of effective c++
// --------------------------------------------------------------------------------------------------------------------

struct embot::tools::Histogram::Impl
{  

    struct Status
    {
        Config                      config;  
        std::uint32_t               numofbins;        
        Values                      values; 
        Status() { numofbins = 0; values.total = values.below = values.beyond = 0; values.inside.clear(); } 
    }; 
    
    Status status;    

    Impl() 
    { 
         
    }
    
    bool init(const Config &config)
    {
        if(false == config.isvalid())
        {
            return false;
        }
        
        status.config = config;
        
        status.numofbins = status.config.nsteps();    
        
        status.values.inside.reserve(status.config.nsteps());                
        status.values.inside.resize(status.config.nsteps(), 0); 
        
        status.values.total = status.values.below = status.values.beyond = 0;

        return true;        
    }
    

   
    bool add(std::uint64_t val)
    {
        if(false == status.config.isvalid())
        {   // not yet initted
            return false;
        }
        
        if(val < status.config.min)
        {
            status.values.below ++;
            status.values.total ++;         
        }
        else if(val < status.config.max)
        {
            std::uint64_t index = (val - status.config.min) / status.config.step;
            if(index < status.numofbins)
            {
                status.values.inside[index] ++;
                status.values.total ++;
            }
            else
            {
                return false;
            }
        }
        else //if(val >= status.config.max) 
        {  
            status.values.beyond ++;
            status.values.total ++;  
        }
        
        return true;
    }
    
    
    bool reset()
    {
        std::fill(status.values.inside.begin(), status.values.inside.end(), 0);
        status.values.below = status.values.beyond = status.values.total = 0;
        return true;
    }
                      
};





struct embot::tools::PeriodValidator::Impl
{ 
    embot::core::Time previous {0};
    embot::core::Time delta {0};
    embot::core::Time prevreport {0};
    bool enabledReport {false};
    bool enabledAlert {false};
    bool usehisto {false};
    
    Config configuration {};
    
    embot::tools::Histogram histo {};


    Impl() = default;

    
    bool init(const Config &config)
    {
        if(false == config.isvalid())
        {
            return false;
        }
        
        configuration = config;
        
        // ok, now i load the 
        
        if(true == configuration.histoconfig.isvalid())
        {
            usehisto = true;
            histo.init(configuration.histoconfig);
        }

        return true;        
    }
    

   
    bool tick(embot::core::Time currtime_usec, embot::core::Time &deltatime_usec)
    {        
        if(0 == previous)
        {
            previous = currtime_usec;
            delta = 0;
            prevreport = currtime_usec;
            deltatime_usec = delta;
            return true;
        }
        else if(currtime_usec < previous)
        {        
            return false;
        }
        
        delta = currtime_usec - previous;
        previous = currtime_usec;
        
        if(true == usehisto)
        {
            histo.add(delta);
        }
        
        enabledAlert = false;
        enabledReport = false;
        
        // now i check ... should i alert?
        if(delta >= configuration.alertvalue)
        {
            enabledAlert = true;
        }
               

        if((true == usehisto) && ((currtime_usec - prevreport) > configuration.reportinterval))
        {
            prevreport = currtime_usec;
            enabledReport = (configuration.reportinterval > 0) ? true : false;            
        }
        
        deltatime_usec = delta;        
        return true;        
    }
    
    
    bool reset()
    {
        previous = 0;
        delta = 0; 
        prevreport = 0; 
        enabledReport = false;
        enabledAlert = false;  
    
        histo.reset(); 

        return true;                
    }
    
    
    bool alert(embot::core::Time &deltatime_usec) const
    {
        deltatime_usec = delta;          
        return enabledAlert;
    }
    
    
    bool report() const
    {       
        return enabledReport;
    }
                   
};




// --------------------------------------------------------------------------------------------------------------------
// - all the rest
// --------------------------------------------------------------------------------------------------------------------



embot::tools::Histogram::Histogram() 
: pImpl(new Impl)
{   

}

embot::tools::Histogram::~Histogram()
{   
    delete pImpl;
}


bool embot::tools::Histogram::init(const Config &config) 
{   
    return pImpl->init(config);
}


bool embot::tools::Histogram::reset()
{
    return pImpl->reset();
}


bool embot::tools::Histogram::add(std::uint64_t value)
{
    return pImpl->add(value);
}

const embot::tools::Histogram::Config * embot::tools::Histogram::getconfig() const
{
    return &pImpl->status.config;
}

const embot::tools::Histogram::Values * embot::tools::Histogram::getvalues() const
{
    return &pImpl->status.values;
}

//bool embot::tools::Histogram::probabilitydensityfunction(std::vector<std::uint32_t> &values, const std::uint32_t scale, const bool underflowisONE) const
//{
//    if(0 == pImpl->status.values.total)
//    {
//        values.clear();
//        return false;
//    }
//    
//    values.resize(pImpl->status.values.inside.size() + 2);
//    
//    std::uint32_t *ref = &values[0];
//    std::uint64_t v64 = pImpl->status.values.below;
//    
//    if(0 == v64)
//    {
//        *ref = 0;
//    }
//    else
//    {
//        *ref = static_cast<std::uint32_t>(scale * v64 / pImpl->status.values.total);
//        if((0 == *ref) && (true == underflowisONE))
//        {
//            *ref = 1;
//        }
//    }
//    
//    for(int i=0; i<pImpl->status.values.inside.size(); i++)
//    {
//        ref = &values[i+1];
//        v64 = pImpl->status.values.inside[i];
//        if(0 == v64)
//        {
//            *ref = 0;
//        }
//        else
//        {
//            *ref = static_cast<std::uint32_t>(scale * v64 / pImpl->status.values.total);
//            if((0 == *ref) && (true == underflowisONE))
//            {
//                *ref = 1;
//            }
//        }          
//    }
//    
//    ref = &values[values.size()-1];
//    v64 = pImpl->status.values.beyond;
//    
//    if(0 == v64)
//    {
//        *ref = 0;
//    }
//    else
//    {
//        *ref = static_cast<std::uint32_t>(scale * v64 / pImpl->status.values.total);
//        if((0 == *ref) && (true == underflowisONE))
//        {
//            *ref = 1;
//        }
//    } 
//    
//    return true;
//    
//}

bool embot::tools::Histogram::probabilitydensityfunction(std::vector<double> &values) const
{
    if(0 == pImpl->status.values.total)
    {
        values.clear();
        return false;
    }
    
    values.resize(pImpl->status.values.inside.size() + 2);
  
    values[0] = static_cast<double>(pImpl->status.values.below) / static_cast<double>(pImpl->status.values.total);
    
    for(int i=0; i<pImpl->status.values.inside.size(); i++)
    {
        values[i+1] = static_cast<double>(pImpl->status.values.inside[i]) / static_cast<double>(pImpl->status.values.total);
    }
    
    values[values.size()-1] = static_cast<double>(pImpl->status.values.beyond) / static_cast<double>(pImpl->status.values.total);
    
    return true;   
}

bool embot::tools::Histogram::probabilitydensityfunction(std::vector<std::uint32_t> &values, const std::uint32_t scale) const
{
    if(0 == pImpl->status.values.total)
    {
        values.clear();
        return false;
    }
    
    values.resize(pImpl->status.values.inside.size() + 2);
    
    values[0] = static_cast<std::uint32_t>(scale * pImpl->status.values.below / pImpl->status.values.total);
    
    for(int i=0; i<pImpl->status.values.inside.size(); i++)
    {
        values[i+1] = static_cast<std::uint32_t>(scale * pImpl->status.values.inside[i] / pImpl->status.values.total);        
    }
    
    values[values.size()-1] = static_cast<std::uint32_t>(scale * pImpl->status.values.beyond / pImpl->status.values.total);
    
    return true;    
}


embot::tools::PeriodValidator::PeriodValidator() 
: pImpl(new Impl)
{   

}

embot::tools::PeriodValidator::~PeriodValidator()
{   
    delete pImpl;
}


bool embot::tools::PeriodValidator::init(const Config &config) 
{   
    return pImpl->init(config);
}


bool embot::tools::PeriodValidator::tick(embot::core::Time currtime, embot::core::Time &deltatime)
{
    return pImpl->tick(currtime, deltatime);
}


bool embot::tools::PeriodValidator::reset()
{
    return pImpl->reset();
}


bool embot::tools::PeriodValidator::alert(embot::core::Time &deltatime) const
{
    return pImpl->alert(deltatime);
}

bool embot::tools::PeriodValidator::report() const
{
    return pImpl->report();
}


const embot::tools::Histogram * embot::tools::PeriodValidator::histogram() const
{
    return &pImpl->histo;
}


// - end-of-file (leave a blank line after)----------------------------------------------------------------------------

