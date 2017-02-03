/*****************************************************************************
 Ball Class

 NAME:ball.cpp
 DATE:8/3/1997
 AUTHOR: Z.A. Nolan

*****************************************************************************/

// include the plane header
#include "ball.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include "aux.h"
#include "zerotest.h"

#define BIGNUMBER 1000000

// Constructor
TBall::TBall ()
:TObject()
{
 _Acceleration=TVector(0,0,0);
 _Velocity=TVector(0,0,0) ;
 _Position=TVector(0,0,0) ;
 _Radius=0 ;
}

// Constructor
TBall::TBall (TVector Acceleration,TVector Velocity,TVector Position,
              double Radius,double Friction,double Elasticity,
              const TSurfaceProperties SurfaceProperties)
:TObject(SurfaceProperties)
{
 _Acceleration=Acceleration ;
 _Velocity=Velocity;
 _Position=Position ;
 _Radius=Radius ;
 _Friction=Friction ;
 _Elasticity=Elasticity ;
}

// return the top corner of the cube
TVector TBall::Position() const
{
 return _Position ;
}

// return the bottom corner of the cube
TVector TBall::Acceleration() const
{
 return _Acceleration ;
}


// return the bottom corner of the cube
TVector TBall::Velocity() const
{
 return _Velocity ;
}

// return the bottom corner of the cube
double TBall::Radius() const
{
 return _Radius ;
}

// The Intersection of a sphere and a line
double TBall::Intersection(TVector &Normal,const TBall &Ball) const
{
  //dummy at the moment
   return (-1) ;
}

// Move the ball by the right amount for the time step
void TBall::Move(const double &TimeStep)
{
 TVector OldVelocity ;

 OldVelocity=_Velocity ;

 _Velocity=_Velocity+(_Acceleration*TimeStep) ;

 _Position=_Position+((OldVelocity+_Velocity)*TimeStep*0.5) ;
}

// Work out the new velocity of the ball
void TBall::Rebound(const TVector &Normal)
{
 // reflect the ball
 _Velocity=_Velocity-(Normal*2.0*(_Velocity.Dot(Normal))) ;

 // add friction and Elasticity
 _Velocity=TVector((1-_Friction)*_Velocity.X(),
                   _Elasticity*_Velocity.Y(),
                   _Velocity.Z()) ;
}

void TBall::Draw()
{
  // set the material
 (*this).SurfaceProperties().Set() ;

 // Draw the ball
 glTranslatef ((*this).Position().X(),
               (*this).Position().Y(),
               (*this).Position().Z()) ;

 auxSolidSphere((*this).Radius()) ;
 glTranslatef (-(*this).Position().X(),
               -(*this).Position().Y(),
               -(*this).Position().Z());
}
