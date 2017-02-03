/*****************************************************************************
 Base class for all object in the raycaster/raytracer

 NAME:object.cpp
 DATE:10/11/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

// include the header file
#include "object.h"

// constructor
TObject::TObject ()
{
 _SurfaceProperties=TSurfaceProperties() ;
}

TObject::TObject (const TSurfaceProperties SurfaceProperties)

{
 _SurfaceProperties=SurfaceProperties ;
}

// return the colour of the object
TSurfaceProperties TObject::SurfaceProperties() const
{
 return _SurfaceProperties  ;
}
