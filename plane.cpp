
/*****************************************************************************
 Plane Class

 NAME:plane.cpp
 DATE:5/11/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

// include the plane header
#include "plane.h"

// Constructor
TPlane::TPlane ()
:TObject()
{
 _Normal=TVector(0,0,0) ;
 _Constant=0 ;
}

// Constructor
TPlane::TPlane (TVector Normal,double D,
                const TSurfaceProperties SurfaceProperties)
:TObject(SurfaceProperties)
{
 _Normal=Normal.Unit() ;
 _Constant=D ;
}

// get the normal
TVector TPlane::Normal() const
{
 return _Normal ;
}

// get D
double TPlane::D() const
{
 return _Constant ;
}

// Find the intersection of a plane and a line
double TPlane::Intersection (TVector &Point,TVector &Normal,
                             const TLine &Line) const
{
 TVector LineDirection ;
 double  Distance ;
 TVector Direction ;
 double  ZeroCheck ;

 LineDirection=(Line.EndPoint()-Line.StartPoint()).Unit() ;

 ZeroCheck=_Normal.Dot(LineDirection) ;

 // check for divide by zero
 if (ZeroCheck!=0.0)
   {
    Distance=(_Constant-(_Normal.Dot(Line.StartPoint())))/(ZeroCheck) ;
   }
 else
   {
    // no intersection so set to a negative value
    Distance=-10 ;
   }

 Direction=LineDirection*Distance ;
 Point=Line.StartPoint()+Direction ;

 Normal=_Normal ;

 return Distance ;
}

// function to input a plane
istream &TPlane::Read (istream &In)
{
 char Comma ; // delimter for the items
 char Bracket ; // delimiter for vector and colour parts
 TVector Normal ;
 TColour Colour;
 double  Constant ;
 double  Diffuse ;
 double  Specular ;
 double  Shine ;
 int     Roughness ;

 // read in the colour
 In>>Bracket>>Normal>>Bracket>>Comma>>Constant>>Comma>>
     Bracket>>Colour>>Bracket ;

 // copy to the object
 (*this)=TPlane(Normal,Constant,
         TSurfaceProperties(Colour)) ;

 // return the stream
 return In ;
}

// function to output a colour
ostream &TPlane::Write (ostream &Out) const
{
 // write out the colour
 Out<<'('<<(*this).Normal()<<')'<<','<<(*this).D()<<','
    <<'('<<(*this).Colour()<<')' ;

 // return the stream
 return Out ;
}

// function to read in a plane
istream &operator>>(istream &In,TPlane &Plane)
{
 // input a plane
 return Plane.Read(In) ;
}

ostream &operator<<(ostream &Out,const TPlane &Plane)
{
 // output the colour
 return Plane.Write(Out) ;
}
