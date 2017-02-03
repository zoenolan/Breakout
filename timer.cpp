/*****************************************************************************
 timer class

 NAME:timer.h
 DATE:24/2/1997
 AUTHOR: Z.A. Nolan

*****************************************************************************/

#include "timer.h"

TTimer::TTimer()
{
 _Started=-1 ;
}

TTimer::Start()
{
  // get the start time
 gettimeofday(&_Start, (struct timezone*)0);

 // set the valid flag
 _Started=1 ;
}

TTimer::End()
{
  // get the end time
 gettimeofday(&_End, (struct timezone*)0);

 // set the valid flag
 if (_Started==1)
   {
    _Started=0 ;
   }
 else
   {
    _Started=-1 ;
   }
}

float TTimer::TimeTaken()
{
 float TimeTaken ;


 if (_Started==0)
   {
    TimeTaken = (_End.tv_sec - _Start.tv_sec) +
                (_End.tv_usec - _Start.tv_usec)/1000000.0;
   }
 else
   {
    TimeTaken=-1 ;
   }

 return TimeTaken ;
}
