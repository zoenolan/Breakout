#ifndef ball_h
#define ball_h

/*****************************************************************************
 Ball Class

 NAME:ball.h
 DATE:8/3/1997
 AUTHOR: Z.A. Nolan

*****************************************************************************/

// include vector class
#include "vector.h"

// and the colour class
#include "colour.h"

// and the line class
#include "line.h"

// and include the object class
#include "object.h"

class TBall :public TObject
{
 private:
   TVector _Acceleration ; // Acceleration of the ball
   TVector _Velocity ;   // Speed of the ball
   TVector _Position ; // position of the ball
   double  _Radius ;   // radius of the ball
   double  _Friction ; // friction
   double  _Elasticity ; // Elasticity of ball

public:
   // Constructors
   TBall () ;
   TBall (TVector Acceleration,TVector Velocity,TVector Position,
          double Radius,double Friction,double Elasticity,
          const TSurfaceProperties SurfaceProperties) ;

   // get the corner data
   TVector Acceleration() const;
   TVector Velocity() const;
   TVector Position() const;
   double  Radius() const;

   void Move(const double &TimeStep) ;
   void Rebound (const TVector &Normal) ;

   // intersection
   double Intersection(TVector &Normal,const TBall &Ball) const ;
   void Draw() ;

} ;
#endif
