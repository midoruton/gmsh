// Gmsh - Copyright (C) 1997-2008 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to <gmsh@geuz.org>.

#ifndef _GAUSS_H_
#define _GAUSS_H_

#include "Numeric.h"

int GaussLegendreTri(int n1, int n2, IntPt *pts);
int GaussLegendreTet(int n1, int n2, int n3, IntPt *pts); 
int GaussLegendreHex(int n1, int n2, int n3, IntPt *pts);

int getNGQTPts(int order);
IntPt *getGQTPts (int order);

int getNGQQPts(int order);
IntPt *getGQQPts(int order);

int getNGQTetPts(int order);
IntPt *getGQTetPts(int order);

int getNGQHPts(int order);
IntPt *getGQHPts(int order);

#endif
