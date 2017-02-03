#ifndef cube_h
#define cube_h

/*****************************************************************************
 Plane Class

 NAME:cube.h
 DATE:17/12/1996
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

class TCube :public TObject
{
 private:
   TVector _TopCorner ;   // Top corner of the cube
   TVector _BottomCorner ; // Bottom corner of the cube
   int     _Hits ;  // number of hits needed to kill the block

   TVector _LeftNormal ; // Normals
   TVector _RightNormal ;
   TVector _FrontNormal ;
   TVector _BackNormal ;
   TVector _TopNormal ;
   TVector _BottomNormal ;

public:
   // Constructors
   TCube () ;
   TCube (TVector BottomCorner,TVector TopCorner,
                  const TSurfaceProperties,int Position,int Hits) ;

   // get the corner data
   TVector TopCorner() ;
   TVector BottomCorner() ;

   // Intersection of a line and a plane
   double Intersection(TVector &Normal,const TBall &Ball) const;

   void Draw() ;
   void Hit() ;

} ;
#endif
