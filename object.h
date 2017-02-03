#ifndef object_h
#define object_h

/*****************************************************************************
 Base class for all object in the raycaster/raytracer

 NAME:object.h
 DATE:10/11/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

// include the colour class
#include "surface.h"

// Dummy class
class TBall ;

class TObject
{
 private:
   TSurfaceProperties _SurfaceProperties ;

 public:
   // constuctor
   TObject () ;
   TObject (const TSurfaceProperties SurfaceProperties) ;

   virtual ~TObject() {}

   // return the colour
   TSurfaceProperties SurfaceProperties() const;

   // intersection
   virtual double Intersection(TVector &Normal,
                               const TBall &Ball) const =0 ;
   virtual void Draw()=0 ;

} ;

#endif
