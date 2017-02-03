
/*****************************************************************************
 Base class for all object surface properties in the raycaster/raytracer

 NAME:surface.cpp
 DATE:17/11/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

// include the header file
#include "surface.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include "aux.h"

// constructor
TSurfaceProperties::TSurfaceProperties ()
{
 _Colour=TColour(0.0,0.0,0.0) ;
}

TSurfaceProperties::TSurfaceProperties
                 (const TColour &Colour,const double Diffuse,
                  const double Specular,const double Shine,
                  const int Roughness)
{
 _Colour=Colour ;
 _Diffuse=Diffuse ;
 _Specular=Specular ;
 _Shine=Shine ;
 _Roughness=Roughness ;
}

// return the colour of the object
TColour TSurfaceProperties::Colour() const
{
 return _Colour ;
}

// return the diffuse value of the object of the object
double TSurfaceProperties::Diffuse() const
{
 return _Diffuse ;
}

// return the specular value of the object
double TSurfaceProperties::Specular() const
{
 return _Specular ;
}

// return the roughness of the object
int TSurfaceProperties::Roughness() const
{
 return _Roughness ;
}

// return the shine of the object
double TSurfaceProperties::Shine() const
{
 return _Shine ;
}

// copy
TSurfaceProperties::Copy(TSurfaceProperties &Surface)
{
 _Colour=Surface.Colour() ;
 _Diffuse=Surface.Diffuse() ;
 _Specular=Surface.Specular() ;
 _Shine=Surface.Shine() ;
 _Roughness=Surface.Roughness() ;
}

void  TSurfaceProperties::Set()
{
 float mat[4] ;

 // set the ambient
 mat[0] = _Colour.Red();
 mat[1] = _Colour.Green();
 mat[2] = _Colour.Blue();
 mat[3] = 1.0;

 glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, mat);

 // set the diffuse
 mat[0] = _Colour.Red()*_Diffuse ;
 mat[1] = _Colour.Green()*_Diffuse ;
 mat[2] = _Colour.Blue()*_Diffuse ;
 glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, mat);

 // set the specular
 mat[0] = _Colour.Red()*_Specular*_Shine ;
 mat[1] = _Colour.Green()*_Specular*_Shine ;
 mat[2] = _Colour.Blue()*_Specular*_Shine  ;
 glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, mat);
 glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, (float)_Roughness);

}
