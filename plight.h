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

class TPointLight :public TObject
{
 private:
   TVector _Position ;
   double  _Intensity ;

   // read and write functions
   istream &Read (istream &In) ;
   ostream &Write (ostream &Out) const ;

 public:
   // Constructors
   TPointLight () ;
   TPointLight (const TVector &Position , double Intensity ,
                const TColour &Colour) ;


   TVector Position() const ;
   double Intersection(TVector &Point,TVector &Normal,const TLine &Line) const;
   TColour Shade (const TVector &Normal,const TVector &Point,
                  const TVector &RayStart,const TObject *Object) const ;

   // streaming operators
   friend istream &operator>>(istream &In, TPointLight &Light);
   friend ostream &operator<<(ostream &Out,const TPointLight &Light) ;
} ;

#endif
