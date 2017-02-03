#ifndef zerotest_h
#define zerotest_h

/******************************************************************************
 Free function to test if a double is zero

 NAME:zerotest.h
 DATE:7/11/1996
 AUTHOR: Z.A. Nolan

******************************************************************************/

#include <math.h>

#define EPSILON 1e-10    // max value to treat as zero

// function to test if a double is zero
template <class T> inline int IsZero (const T Number)
{
 if ((Number>-EPSILON)&&(Number<EPSILON))
   {
    return (1) ;
   }
 else
   {
    return (0) ;
   }

}

// function to test if a double is less than zero
template <class T> inline int LessThanZero (const T Number)
{
 if (Number<EPSILON)
   {
    return (1) ;
   }
 else
   {
    return (0) ;
   }
}

// function to test if a double is greater than zero
template <class T> inline int GreaterThanZero (const T Number)
{
 if (Number>EPSILON)
   {
    return (1) ;
   }
 else
   {
    return (0) ;
   }

}

#endif
