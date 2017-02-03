#ifndef line_h
#define line_h

/*****************************************************************************
 3D Line class

 NAME:line.h
 DATE:5/11/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

// include input output
#include <iostream.h>

// include the vector class
#include "vector.h"

class TLine
{
 private:
   TVector _StartPoint ;  // Start point of the line
   TVector _EndPoint ;    // end point of the line

 public:
   // Constructors
   TLine () {}

   // A line between two points
   TLine (const TVector &StartPoint,const TVector &EndPoint) ;

   // Selectors

   //  get the start point
   TVector StartPoint() const ;

   // get the end point
   TVector EndPoint() const ;

   // Modifiers

   // get the distance to a point
   double  Distance (const TVector &Point) const ;

   // get the distance to a line
   double  Distance (const TLine &Line) const ;

   // invert a line
   TLine operator-() const ;

   // output
   friend ostream &operator<<(ostream &Out,const TLine &Line) ;
   friend istream &operator>>(istream &In,TLine &Line) ;

} ;

#endif
