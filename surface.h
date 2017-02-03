#ifndef surface_h
#define surface_h

/*****************************************************************************
 Base class for all object surface properties in the raycaster/raytracer

 NAME:surface.h
 DATE:17/11/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

// include the colour class
#include "colour.h"

class TSurfaceProperties
{
 private:
   TColour _Colour ;
   double  _Diffuse ;
   double  _Specular ;
   double  _Shine ;
   int     _Roughness ;

 public:
   // constuctor
   TSurfaceProperties () ;
   TSurfaceProperties (const TColour &Colour,const double Diffuse,
            const double Specular,const double Shine,const int Roughness);

   // return the colour
   TColour Colour() const;
   double  Diffuse() const ;
   double  Specular() const ;
   double  Shine() const ;
   int     Roughness() const ;
           Copy(TSurfaceProperties &Surface) ;

   void  Set() ;
} ;

#endif
