#ifndef vector_h
#define vector_h

/*****************************************************************************
 3D Vector Class

 NAME:vector.h
 DATE:5/11/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

#include <iostream.h>    // include the streams library

// Dummy Class
class TLine ;

class TVector
{
 private:
   double _X ;
   double _Y ;
   double _Z ;

   // Streaming
   istream &Read (istream &In) ;
   ostream &Write (ostream &Out) const ;

 public:
   // Constructors
   TVector () ;
   TVector (double X,double Y, double Z) ;
   TVector (int X,int Y,int Z) ;

   // Selectors
   double X() const ;
   double Y() const ;
   double Z() const ;

   // Modifiers
   TVector operator+(const TVector &Vector) const ;
   TVector operator-(const TVector &Vector) const ;
   TVector & operator+= (const TVector &Vector) ;
   TVector & operator-= (const TVector &Vector) ;

   // Cross product
   TVector operator* (const TVector &Vector) const;
   TVector &operator*= (const TVector &Vector) ;

   // Dot Product
   double Dot (const TVector &Vector) const ;

   // * by Scalar
   TVector operator* (double Scalar) const ;
   TVector &operator*= (double Scalar) ;

   // Distance between two vectors
   double Distance (const TVector &Vector) const ;

   // The Length of a vector
   double Magnitude () const;

   // Make a vector unit length
   TVector Unit() const ;

   // make a Vector negative
   TVector operator-() const ;

   // these just call the real functions
   friend istream &operator>>(istream &In, TVector &Vector);
   friend ostream &operator<<(ostream &Out,const TVector &Vector) ;
} ;

#endif
