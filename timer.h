#ifndef timer_h
#define timer_h

/*****************************************************************************
 timer class

 NAME:timer.h
 DATE:24/2/1997
 AUTHOR: Z.A. Nolan

*****************************************************************************/

#include <time.h>
#include <sys/time.h>

class TTimer
{
 private:
   struct timeval _Start, _End;    // members to store the start and end times
   int  _Started;                  // boolean for testing if the timing has
				   // begun.

 public:
   TTimer() ;

   Start() ;                       // start timer
   End() ;                         // end timer

   float TimeTaken() ;             // get the result

} ;

#endif
