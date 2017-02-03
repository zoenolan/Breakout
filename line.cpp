/****************************************************************************
 3D Line class

 NAME: line.cpp
 DATE: 24/10/96
 AUTHOR: Z.A. Nolan

****************************************************************************/

// include the maths library
#include <math.h>

// include the line header
#include "line.h"

// include the zero test function
#include "zerotest.h"

// constructor
TLine::TLine (const TVector &StartPoint,const TVector &EndPoint)
{
 _StartPoint=StartPoint ;
 _EndPoint=EndPoint ;
}

// get the starting point
TVector TLine::StartPoint() const
{
 // return the starting point
 return (_StartPoint) ;
}

// get the end point
TVector TLine::EndPoint() const
{
 // return the End point
 return (_EndPoint) ;
}

// find the distance to a point from a line
double TLine::Distance (const TVector &Point) const
{
 TVector AP ; // vector from start of line to the point
 TVector U ;  // unit direction vector of the line
 double Result ; // the distance

 // work out AP
 AP=Point-_StartPoint ;

 // work out U
 U=(_EndPoint-_StartPoint).Unit() ;

 // work out the result
 Result=(AP*U).Magnitude() ;
 Result=fabs (Result) ;

 // return the result
 return (Result) ;
}

// find the distance between two lines
double TLine::Distance (const TLine &Line) const
{
 TVector m,n ; // unit direction vectors of each line
 TVector MN ; // m cross nover mod m cross n
 double Result ; // the Result
 double ZeroTest ; // part result that needs testing for zero

 // work out m
 m=(_EndPoint-_StartPoint).Unit() ;

 // work out n
 n=(Line._EndPoint-Line._StartPoint).Unit() ;

 // work MN
 ZeroTest=(m*n).Magnitude() ;

 if (IsZero(ZeroTest))
   {
    // the lines are parallel
    // so the distance between them is the distance between two points
    Result=(_StartPoint-Line._StartPoint).Magnitude() ;
   }
 else
   {
    // the lines are not parallel
    MN=(m*n)*(1/(ZeroTest)) ;

    // work out the distance
    Result=(_StartPoint-Line._StartPoint).Dot(MN) ;
   }

 Result=fabs(Result) ;

 // return the result
 return (Result) ;
}

// invert the line
TLine TLine::operator -() const
{
 TLine Result(_EndPoint,_StartPoint) ; // the inverted line

 return (Result) ;
}

// output a line
ostream &operator<<(ostream &Out,const TLine &Line)
{
 // write to the stream
 Out<<Line._StartPoint<<'-'<<Line._EndPoint ;

 // return the stream
 return Out ;
}

// input a line
istream &operator>>(istream &In,TLine &Line)
{
 char Dash ; // dummy char to read the dash into

 // Read from the stream
 In>>Line._StartPoint>>Dash>>Line._EndPoint ;

 // return the stream
 return In ;
}
