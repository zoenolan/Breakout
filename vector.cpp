/****************************************************************************
 3D Vector class

 NAME: vector.cpp
 DATE: 23/10/96
 AUTHOR: Z.A. Nolan

****************************************************************************/

// include the streams library
#include <iostream.h>

// and the maths library
#include <math.h>

// and the double zero test
#include "zerotest.h"

// and the 3D Vectors
#include "vector.h"

// Default constructor
TVector::TVector ()
{
 _X=0 ;
 _Y=0 ;
 _Z=0 ;
}

// Constructor for doubles
TVector::TVector(double X,double Y,double Z)
{
 _X=X ;
 _Y=Y ;
 _Z=Z ;
}

// Constructor for int
TVector::TVector(int X,int Y,int Z)
{
 _X=(double)X ;
 _Y=(double)Y ;
 _Z=(double)Z ;
}


// selector for the X value
double TVector::X() const
{
 return (_X) ;
}

// selector for the Y value
double TVector::Y() const
{
 return (_Y) ;
}

// selector for the Z value
double TVector::Z() const
{
 return (_Z) ;
}

// + operator
TVector TVector::operator+ (const TVector &Vector) const
{
 TVector Result ; // Result Vector

 // do the addition
 Result._X=_X+Vector._X ;
 Result._Y=_Y+Vector._Y ;
 Result._Z=_Z+Vector._Z ;

 // return the result
 return (Result) ;
}

// - operator
TVector TVector::operator -(const TVector &Vector) const
{
 TVector Result ; // Result Vector

 // do the addition
 Result._X=_X-Vector._X ;
 Result._Y=_Y-Vector._Y ;
 Result._Z=_Z-Vector._Z ;

 // return the result
 return (Result) ;
}

// += operator
TVector &TVector::operator +=(const TVector &Vector)
{
 // do the addition
 _X+=Vector._X ;
 _Y+=Vector._Y ;
 _Z+=Vector._Z ;

}

// -= operator
TVector &TVector::operator -=(const TVector &Vector)
{
 // do the addition
 _X-=Vector._X ;
 _Y-=Vector._Y ;
 _Z-=Vector._Z ;
}

// cross product
TVector TVector::operator* (const TVector &Vector) const
{
 TVector Result ; // Result vector

 // work out the cross product
 Result._X=(_Y*Vector._Z)-(_Z*Vector._Y) ;
 Result._Y=-((_X*Vector._Z)-(_Z*Vector._X)) ;
 Result._Z=(_X*Vector._Y)-(_Y*Vector._X) ;

 return (Result) ;
}

// cross product
TVector &TVector::operator *= (const TVector &Vector)
{
 TVector Result ; // Result vector

 // work out the cross product
 Result._X=(_Y*Vector._Z)-(_Z*Vector._Y) ;
 Result._Y=-((_X*Vector._Z)-(_Z*Vector._X)) ;
 Result._Z=(_X*Vector._Y)-(_Y*Vector._X) ;

 // copy the result back to the right object
 *this=Result ;

 return *this ;
}

// dot product
double TVector::Dot (const TVector &Vector) const
{
 double Result ; // the result

 // calculate dot product
 Result=(_X*Vector._X)+(_Y*Vector._Y)+(_Z*Vector._Z) ;

 // return the result
 return (Result) ;

}

// * by a scalar
TVector TVector::operator * (double Scalar) const
{
 TVector Result ; //

 // do the *
 Result._X=_X*Scalar ;
 Result._Y=_Y*Scalar ;
 Result._Z=_Z*Scalar ;

 // return the result
 return (Result) ;

}

// *= by a scalar
TVector &TVector::operator *= (double Scalar)
{
 // do the *
 _X*=Scalar ;
 _Y*=Scalar ;
 _Z*=Scalar ;
}

double TVector::Distance (const TVector &Vector) const
{
 double Result ; // the result

 // do the maths
 Result=sqrt( (pow((_X-Vector._X),2))+
              (pow((_Y-Vector._Y),2))+
              (pow((_Z-Vector._Z),2)) ) ;

 // return the result
 return (Result) ;
}

// get the length of a vector
double TVector::Magnitude () const
{
 double Result ; // the result

 // find out the length of the vector
 Result=sqrt((_X*_X)+(_Y*_Y)+(_Z*_Z)) ;

 // return the result
 return (Result) ;
}

// make a unit vector
TVector TVector::Unit() const
{
 TVector Result ; // the resulting unit vector
 double  Length ; // the length of the vector

 Length=(*this).Magnitude() ;

 if (IsZero(Length)==0)
   {
    // make the vector unit
    Result._X=_X/Length ;
    Result._Y=_Y/Length ;
    Result._Z=_Z/Length ;
   }

 // return the result
 return (Result) ;
}

// make a vector negative
TVector TVector::operator-() const
{
 TVector Result ; // The result

 // make the vector negative
 Result._X=-_X ;
 Result._Y=-_Y ;
 Result._Z=-_Z ;

 // return the result
 return (Result) ;
}

// function to input a vector
istream &TVector::Read (istream &In)
{
 char Comma ; // delimter for the vector items

 // read in the vector
 In>>_X>>Comma>>_Y>>Comma>>_Z ;

 // return the stream
 return In ;
}

// function to output a vector
ostream &TVector::Write (ostream &Out) const
{
 // write out the vector
 Out<<_X<<','<<_Y<<','<<_Z ;

 // return the stream
 return Out ;
}

// function to read in a vector
istream &operator>>(istream &In,TVector &Vector)
{
 // input a vector
 return Vector.Read(In) ;
}

ostream &operator<<(ostream &Out,const TVector &Vector)
{
 // output the vector
 return Vector.Write(Out) ;
}
