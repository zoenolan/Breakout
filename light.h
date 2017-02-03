#ifndef plight_h
#define plight_h

/*****************************************************************************
 Point Light Class

 NAME:plight.h
 DATE:5/11/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

#include "vector.h"
#include "line.h"
#include "object.h"

class TLight :public TObject
{
 private:


 public:
   // Constructors
   TPointLight () ;
   TPointLight (const TColour &Colour) ;

   double Intensity() const ;

   double Intersection(TVector &Point,TVector &Normal,const TLine Line) const;
   TColour Shade() ;

   // streaming operators
   friend istream &operator>>(istream &In, TPointLight &Light);
   friend ostream &operator<<(ostream &Out,const TPointLight &Light) ;
} ;

#endif
