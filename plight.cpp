/*****************************************************************************
 Point Light Class

 NAME:plight.cpp
 DATE:5/11/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

#include <math.h>
#include "plight.h"
#include "zerotest.h"

// Constructor
TPointLight::TPointLight ()
:TObject()
{
 _Position=TVector(0.0,0.0,0.0) ;
 _Intensity=0.0 ;
}

// Constructor
TPointLight::TPointLight(const TVector &Position,
                         double Intensity,const TColour &Colour)
:TObject(TSurfaceProperties(Colour,0.0,0.0,0.0,0))
{
 _Position=Position ;
 _Intensity=Intensity ;
}

// intersection with a ray
double TPointLight::Intersection
                       (TVector &Point,TVector &Normal,const TLine &Line)const
{
 double LightDistance ;

 // work out distance to light source
 LightDistance=(Point-_Position).Magnitude() ;

 return LightDistance ;
}

TVector TPointLight::Position() const
{
 return _Position ;
}

// function to input a sphere
istream &TPointLight::Read (istream &In)
{
 char Comma ; // delimter for the items
 char Bracket ; // delimiter for vector and colour parts
 TVector Position ;
 TColour Colour ;
 double  Intensity ;

 // read in the point light
 In>>Bracket>>Position>>Bracket>>Comma>>Intensity>>Comma
   >>Bracket>>Colour>>Bracket ;

 // copy to the object
 (*this)=TPointLight(Position,Intensity,Colour) ;

 // return the stream
 return In ;
}

// function to output a sphere
ostream &TPointLight::Write (ostream &Out) const
{
 // write out the colour
 Out<<'('<<(*this).Position()<<')'<<','<<_Intensity<<','
    <<'('<<(*this).Colour()<<')' ;

 // return the stream
 return Out ;
}

// function to read in a plane
istream &operator>>(istream &In,TPointLight &Light)
{
 // input a plane
 return Light.Read(In) ;
}

ostream &operator<<(ostream &Out,const TPointLight &Light)
{
 // output the colour
 return Light.Write(Out) ;

}

TColour TPointLight::Shade (const TVector &Normal,const TVector &Point,
                            const TVector &RayStart,
                            const TObject *Object) const
{
 TColour Colour ;
 double DiffuseValue ;
 double SpecularValue ;
 TVector R ;
 TVector Eye ;
 TVector LightDirection ;

 LightDirection=(_Position-Point).Unit() ;

 // do the diffuse reflection
 DiffuseValue=Normal.Dot(LightDirection) ;

 if (LessThanZero(DiffuseValue))
   {
    DiffuseValue=0.0 ;
   }

 Colour=Colour+((Object->Colour())*DiffuseValue*(Object->Diffuse())) ;

 // do the specular reflection
 Eye=(Point-RayStart).Unit() ;

 R=(Eye-(Normal*((Normal.Dot(Eye))*2))).Unit() ;

 SpecularValue=R.Dot(LightDirection) ;

 if (LessThanZero(SpecularValue))
   {
    SpecularValue=0.0 ;
   }

 Colour=Colour+
     (((*this).Colour()*_Intensity)*(Object->Specular())*
     (Object->Shine())*pow(SpecularValue,(Object->Roughness()))) ;

 // return the colour
 return Colour ;
}
