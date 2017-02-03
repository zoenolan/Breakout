#ifndef plane_h
#define plane_h

/*****************************************************************************
 Plane Class

 NAME:plane.h
 DATE:5/11/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

// include vector class
#include "vector.h"

// and the colour class
#include "colour.h"

// and the line class
#include "line.h"

// and include the object class
#include "object.h"

class TPlane :public TObject
{
 private:
   TVector _Normal ;   // Normal to the plane
   double  _Constant ; // Plane constant

   // read and write functions
   istream &Read (istream &In) ;
   ostream &Write (ostream &Out) const ;

public:
   // Constructors
   TPlane () ;
   TPlane (TVector Normal,double D,
           const TSurfaceProperties) ;

   // selectors
   TVector Normal() const;
   double  D() const;

   // Intersection of a line and a plane
   double Intersection(TVector &Point,TVector &Normal,const TLine &Line) const;

   // streaming operators
   friend istream &operator>>(istream &In, TPlane &Plane);
   friend ostream &operator<<(ostream &Out,const TPlane &Plane) ;
} ;
#endif
