/******************************************************************************
 Breakout Main file

 NAME:main.c
 DATE:11/11/1996
 AUTHOR: Z.A. Nolan

******************************************************************************/

#define XBLOCKS 10
#define YBLOCKS 6

#include "vector.h"
#include "cube.h"
#include "ball.h"
#include "timer.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include "aux.h"

#include <iostream.h>
#include "zerotest.h"
#include <math.h>

TCube Walls;
TBall Ball ;
TTimer Timer ;
TCube Bat ;

TCube Blocks [XBLOCKS*YBLOCKS];

void CollisionTests()
{
 double Time,NewTime ;
 double TimeStep ;
 TVector Normal,NewNormal ;
 int Hits ;
 int BlockCounter ;
 int BlockHit ;

    float mat[4];

 Timer.End() ;
 TimeStep=Timer.TimeTaken() ;
 Timer.Start() ;

 Hits=1 ;
 BlockHit=-1 ;

 // check for collisions
 do
   {
     // check if ball hits walls
    Time=Walls.Intersection(Normal,Ball) ;

    // check if ball hits bat
    NewTime=Bat.Intersection(NewNormal,Ball) ;
    if ((NewTime<Time)&&(GreaterThanZero(NewTime))||(LessThanZero(Time)))
      {
       Time=NewTime ;
       Normal=NewNormal ;
      }

    // check if ball hits bricks
    for (BlockCounter=0;BlockCounter<(XBLOCKS*YBLOCKS);BlockCounter++)
      {
       NewTime=Blocks[BlockCounter].Intersection(NewNormal,Ball) ;
       if (IsZero(NewTime-Time))
         {
          Normal=(Normal+NewNormal).Unit() ;
          BlockHit=BlockCounter ;
         }
       if ((NewTime<Time)&&(GreaterThanZero(NewTime))||(LessThanZero(Time)))
         {
          Time=NewTime ;
          Normal=NewNormal ;
          BlockHit=BlockCounter;
         }
      }

    if ((Time<=TimeStep)&&(!LessThanZero(Time)))
      {
       Ball.Move(Time) ;
       Ball.Rebound(Normal) ;
       TimeStep=TimeStep-Time ;

       if (BlockHit!=-1)
         {
          Blocks[BlockHit].Hit() ;
         }
      }
    else
      {
       // no collisions so move the ball over the whole timestep
       Ball.Move(TimeStep) ;
       Hits=0 ;
      }
   }
 while (Hits) ;
}

void display(void)
{
 int BlockCounter ;

  // Test for collision
  CollisionTests() ;

 // Draw all the graphics

 // Clear the screen
 glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

 // Draw the Walls
 Walls.Draw() ;
 Bat.Draw() ;
 // Draw the balls
 Ball.Draw() ;
 // Draw Bricks
 for (BlockCounter=0;BlockCounter<(YBLOCKS*XBLOCKS);BlockCounter++)
   {
    Blocks[BlockCounter].Draw() ;
   }

 // flush the pipeline and swap the buffers
 glFlush ();
 glXSwapBuffers(auxXDisplay(),auxXWindow());

}

void myReshape(int w, int h)
{
 float XScale,YScale,ZScale ;

 // set the viewport to full window
 glViewport(0, 0, w, h);

 // do the perspective
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(60.0,1.0,1.0,11.0);	/*  transformation  */

 // set up the model transforms
 glMatrixMode(GL_MODELVIEW);

 glLoadIdentity();

 // translate so -1,-1,-1 is the orgin
 glTranslatef(-1,-1,-0.8) ;

 // scale to right size
 glScalef(2,2,2) ;

 // scale the zaxis to right size right
 glScalef(1,1,1.5) ;

 // translate to orgin
 glTranslatef(-Walls.BottomCorner().X(),
              -Walls.BottomCorner().Y(),
              -Walls.BottomCorner().Z()) ;

 // scale world to unit cube
 XScale=1.0/( Walls.TopCorner().X()-Walls.BottomCorner().X() ) ;
 YScale=1.0/( Walls.TopCorner().Y()-Walls.BottomCorner().Y() ) ;
 ZScale=1.0/( Walls.TopCorner().Z()-Walls.BottomCorner().Z() ) ;

 if (ZScale<0.0)
   {
    ZScale=-ZScale ;
   }
 glScalef(XScale,YScale,ZScale) ;

}

void MoveBatLeft()
{
 if (Bat.BottomCorner().X()>Walls.BottomCorner().X())
   {
    Bat=TCube(TVector(Bat.BottomCorner().X()-2.5,
                Bat.BottomCorner().Y(),
                Bat.BottomCorner().Z()),
        TVector(Bat.TopCorner().X()-2.5,
                Bat.TopCorner().Y(),
                Bat.TopCorner().Z()),
        TSurfaceProperties(TColour(0.0,0.0,1.0),0.7,0.7,0.3,10),
        1,-1) ;
   }
}

void MoveBatRight()
{
 if (Bat.TopCorner().X()<Walls.TopCorner().X())
   {
    Bat=TCube(TVector(Bat.BottomCorner().X()+2.5,
                Bat.BottomCorner().Y(),
                Bat.BottomCorner().Z()),
        TVector(Bat.TopCorner().X()+2.5,
                Bat.TopCorner().Y(),
                Bat.TopCorner().Z()),
        TSurfaceProperties(TColour(0.0,0.0,1.0),0.7,0.7,0.3,10),
        1,-1) ;
   }
}

void main()
{
 GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
 GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
 GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
 GLfloat position[] = {1.0, 1.0, -4.1, 1.0 };

 GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
 GLfloat local_view[] = { 0.0 };
 int X,Y ; // counters
 int ColourFlag=0 ;
 TColour BlockColour ;

 // create the ball
 Ball=TBall(TVector(0.0,-9.81,0.0),TVector(5.0,30.0,0.0),TVector(50,80,-50)
            ,2,0.001,0.9999999,
          TSurfaceProperties(TColour(1.0,0.0,0.0),0.7,0.7,0.3,10)) ;

 // create the walls
 Walls=TCube(TVector(0.0,0.0,0.0),TVector(100.0,100.0,-100.0),
             TSurfaceProperties(TColour(1.0,1.0,1.0),0.7,0.7,0.3,10),
             0,-1) ;

 // create the bat
 Bat=TCube(TVector(40.0,5.0,-45.0),TVector(60.0,7.5,-55.0),
             TSurfaceProperties(TColour(0.0,0.0,1.0),0.7,0.7,0.3,10),
             1,-1) ;

 // create the blocks
 for (Y=0;Y<YBLOCKS;Y++)
   {
    for (X=0;X<XBLOCKS;X++)
      {
       if (ColourFlag==0)
         {
          ColourFlag=1 ;
          BlockColour=TColour(1.0,0.0,0.0) ;
         }
       else
         {
          ColourFlag=0 ;
          BlockColour=TColour(0.0,1.0,0.0) ;
         }

       Blocks[Y*XBLOCKS+X]=TCube(TVector(0.0+(X*10.0),95.0-(Y*5),-45.0),
                                 TVector(10.0+(X*10.0),100.0-(Y*5),-55.0),
                           TSurfaceProperties(BlockColour,0.7,0.7,0.3,10),
                                 1,1) ;

      }
    if (ColourFlag==0)
      {
       ColourFlag=1 ;
      }
    else
      {
       ColourFlag=0 ;
      }
   }

 // open window
 auxInitDisplayMode (AUX_DOUBLE | AUX_RGB);
 auxInitPosition (0, 0, 480, 480);
 auxInitWindow ("Breakout");

 // set up light source
 glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
 glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
 glLightfv(GL_LIGHT0, GL_POSITION, position);
 glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
 glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

 // enable lighting and shading
 glEnable(GL_LIGHTING);
 glEnable(GL_LIGHT0);
 glEnable(GL_AUTO_NORMAL);
 glEnable(GL_NORMALIZE);
 glEnable(GL_DEPTH_TEST);
 glDepthFunc(GL_LESS);
 glShadeModel (GL_SMOOTH);

 // set the timer going
 Timer.Start() ;

 // set the keys for moving the bat
 auxKeyFunc(AUX_LEFT,MoveBatLeft) ;
 auxKeyFunc(AUX_RIGHT,MoveBatRight) ;

 // set the reshape, Idle and main loop functions
 auxReshapeFunc (myReshape);
 auxIdleFunc (display) ;
 auxMainLoop (display);

}
