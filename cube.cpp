/*****************************************************************************
 Cube Class

 NAME:cube.cpp
 DATE:17/12/1996
 AUTHOR: Z.A. Nolan

*****************************************************************************/

// include the cube header
#include "cube.h"
#include "ball.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include "aux.h"
#include "zerotest.h"

// Constructor
TCube::TCube ()
:TObject()
{
 _TopCorner=TVector(0,0,0) ;
 _BottomCorner=TVector(0,0,0) ;
 _Hits=0 ;

 _LeftNormal=TVector(0,0,0) ;
 _RightNormal=TVector(0,0,0) ;
 _FrontNormal=TVector(0,0,0) ;
 _BackNormal=TVector(0,0,0) ;
 _TopNormal=TVector(0,0,0) ;
 _BottomNormal=TVector(0,0,0) ;
}

// Constructor
TCube::TCube (TVector BottomCorner,TVector TopCorner,
              const TSurfaceProperties SurfaceProperties,int Position,int Hits)
:TObject(SurfaceProperties)
{
 _TopCorner=TopCorner;
 _BottomCorner=BottomCorner ;

 // Construct Normals
 _LeftNormal=TVector(1,0,0) ;
 _RightNormal=TVector(-1,0,0) ;
 _FrontNormal=TVector(0,0,-1) ;
 _BackNormal=TVector(0,0,1) ;
 _TopNormal=TVector(0,-1,0) ;
 _BottomNormal=TVector(0,1,0) ;

 // set the number of Hits
 _Hits=Hits ;

 // check to see if the position is inside or outside the cube
 if (Hits==0)
   {
    // Position inside cube
    _LeftNormal=TVector(1,0,0) ;
    _RightNormal=TVector(-1,0,0) ;
    _FrontNormal=TVector(0,0,-1) ;
    _BackNormal=TVector(0,0,1) ;
    _TopNormal=TVector(0,-1,0) ;
    _BottomNormal=TVector(0,1,0) ;
   }
 else
   {
    // Position outside cube
    _LeftNormal=TVector(-1,0,0) ;
    _RightNormal=TVector(1,0,0) ;
    _FrontNormal=TVector(0,0,1) ;
    _BackNormal=TVector(0,0,-1) ;
    _TopNormal=TVector(0,1,0) ;
    _BottomNormal=TVector(0,-1,0) ;
   }

}

// return the top corner of the cube
TVector TCube::TopCorner()
{
 return _TopCorner ;
}

// return the bottom corner of the cube
TVector TCube::BottomCorner()
{
 return _BottomCorner ;
}

// free function to do all the work for one plane test in the collision
double CollisionTest  (const double &Position,const double &Velocity,
                       const double &Acceleration, const double &Height)
{
 double Root1,Root2 ;
 double Time;
 double CommonPart ;

 // test for Collision of ball and plane

 if (IsZero(Acceleration)==0)
   {

    // Ball has acceleration
    CommonPart=
      ((Velocity*Velocity)-(Acceleration*0.5*(Position-Height ) ) );
    // check for negative before we square root it
    if (LessThanZero(CommonPart))
      {
       // set time to negative
       Time=-100 ;
      }
    else
      {
       CommonPart=sqrt(CommonPart) ;

       Root1=(-Velocity+CommonPart)/Acceleration ;
       Root2=(-Velocity-CommonPart)/Acceleration ;

       if (Root1<Root2)
         {
          if (LessThanZero(Root1))
            {
             Time=Root2 ;
            }
          else
            {
             Time=Root1 ;
            }
         }
       else
         {
          if (LessThanZero(Root2))
            {
             Time=Root1 ;
            }
          else
            {
             Time=Root2 ;
            }
         }
      }
   }
 else
   {
    if (IsZero(Velocity)==0)
      {
       // no acceleration
       Time=(Height-Position)/Velocity ;
      }
    else
      {
       // ball can't hit plane
       Time=-1000 ;
      }
   }

 // return the time till the collision
 return (Time) ;
}

// Find the intersection of a cube and a ball
double TCube::Intersection (TVector &Normal,
                            const TBall &Ball) const
{
 double Root1,Root2 ;
 double Time,NewTime;
 int HitPlane ;
 TBall Temp ;

 TVector CubeNormal ;

 if (_Hits!=0)
   {

    // test the floor
    Time=CollisionTest (Ball.Position().Y(),Ball.Velocity().Y(),
                    Ball.Acceleration().Y(),_BottomCorner.Y()+Ball.Radius()) ;
    CubeNormal=_BottomNormal ;
    HitPlane=0 ;

    // test the roof
    NewTime=CollisionTest (Ball.Position().Y(),Ball.Velocity().Y(),
                        Ball.Acceleration().Y(),
                        _TopCorner.Y()-Ball.Radius()) ;

    if ((NewTime<Time)&&(GreaterThanZero(NewTime))||(LessThanZero(Time)))
      {
       Time=NewTime ;
       CubeNormal=_TopNormal ;
      }

    // test the left
    NewTime=CollisionTest (Ball.Position().X(),Ball.Velocity().X(),
                        Ball.Acceleration().X(),
                        _BottomCorner.X()+Ball.Radius()) ;

    if (IsZero(NewTime-Time))
      {
       // Corner hit
       CubeNormal=(CubeNormal+_LeftNormal).Unit() ;
       HitPlane=1 ;
      }

    else if ((NewTime<Time)&&(GreaterThanZero(NewTime))||(LessThanZero(Time)))
      {
       // normal hit
       Time=NewTime ;
       CubeNormal=_LeftNormal ;
       HitPlane=1 ;
      }

    // test the right wall
    NewTime=CollisionTest (Ball.Position().X(),Ball.Velocity().X(),
                      Ball.Acceleration().X(),_TopCorner.X()-Ball.Radius()) ;

    if (IsZero(NewTime-Time))
      {
       // Corner hit
       CubeNormal=(CubeNormal+_RightNormal).Unit() ;
       HitPlane=1 ;
      }

    else if ((NewTime<Time)&&(GreaterThanZero(NewTime))||(LessThanZero(Time)))
      {
       Time=NewTime ;
       CubeNormal=_RightNormal ;
       HitPlane=1 ;
      }

    // check that the hit is within the limits of the cube

    //calculate the new position of the ball
    Temp=Ball ;
    Temp.Move(Time) ;

    // do the test
    if (HitPlane==0)
      {
       // test the left/right planes
       if ((Temp.Position().X()<_BottomCorner.X())||
           (Temp.Position().X()>_TopCorner.X()))
         {
          Time=-1000 ;
         }
      }
    else
      {
       // test the top/bottom planes
       if ((Temp.Position().Y()<_BottomCorner.Y())||
        (Temp.Position().Y()>_TopCorner.Y()))
         {
          Time=-1000 ;
         }
      }

    // set the normal
    Normal=CubeNormal ;
   }
 else
   {
    Time=-1000 ;
   }

 // return the time taken to hit the cube
 return (Time) ;
}

void DrawWall(TVector A,TVector B,TVector C,TVector D)
{
 glBegin (GL_QUADS);
   // draw the Wall
   glVertex3f (A.X(),A.Y(),A.Z());
   glVertex3f (B.X(),B.Y(),B.Z());
   glVertex3f (C.X(),C.Y(),C.Z());
   glVertex3f (D.X(),D.Y(),D.Z());
 glEnd ();
}

void TCube::Draw()
{
 TVector A,B,C,D,E,F,G,H ;
 if (_Hits!=0)
   {
    // set the material
    (*this).SurfaceProperties().Set() ;

    // draw the cube

    // work out the corner vectors for each of the walls
    A=(*this).BottomCorner() ;
    B=TVector((*this).BottomCorner().X(),
              (*this).TopCorner().Y(),
              (*this).BottomCorner().Z()) ;
    C=TVector((*this).TopCorner().X(),
              (*this).TopCorner().Y(),
              (*this).BottomCorner().Z()) ;
    D=TVector((*this).TopCorner().X(),
              (*this).BottomCorner().Y(),
              (*this).BottomCorner().Z()) ;

    E=TVector((*this).BottomCorner().X(),
              (*this).BottomCorner().Y(),
              (*this).TopCorner().Z()) ;
    F=TVector((*this).BottomCorner().X(),
              (*this).TopCorner().Y(),
              (*this).TopCorner().Z()) ;
    G=(*this).TopCorner() ;
    H=TVector((*this).TopCorner().X(),
              (*this).BottomCorner().Y(),
              (*this).TopCorner().Z()) ;

    // draw four main walls
    DrawWall(A,B,F,E) ;
    DrawWall(B,F,G,C) ;
    DrawWall(C,D,H,G) ;
    DrawWall(A,E,H,D) ;

    // back wall
    DrawWall(E,F,G,H) ;

    // front wall
    DrawWall(A,B,C,D) ;
   }
}

void TCube::Hit()
{
 if ((_Hits!=-1)||(_Hits!=0))
   {
    // block is breakable
    _Hits=_Hits-1 ;
   }
}
