// $Id: PostSimplex.cpp,v 1.24 2001-08-03 19:23:38 geuzaine Exp $

#include "Gmsh.h"
#include "GmshUI.h"
#include "Geo.h"
#include "Mesh.h"
#include "Draw.h"
#include "Iso.h"
#include "IsoSimplex.h"
#include "Context.h"

extern Context_T   CTX;

void Draw_Simplex(int dim, double *X, double *Y, double *Z,
		  double *Offset, double Raise[3][5]){
  int k;
  double xx[4], yy[4], zz[4];

  glColor4ubv((GLubyte*)&CTX.color.fg);
  switch(dim){
  case 0 :
    Draw_Point(X,Y,Z,Offset,Raise);
    break;
  case 1 :
    Draw_Line(X,Y,Z,Offset,Raise);
    break;
  case 2 :
    glBegin(GL_LINE_LOOP);
    for(k=0 ; k<3 ; k++) 
      glVertex3d(X[k]+Offset[0]+Raise[0][k],
		 Y[k]+Offset[1]+Raise[1][k],
		 Z[k]+Offset[2]+Raise[2][k]);
    glEnd();
    break;
  case 3 :
    for(k=0 ; k<4 ; k++){
      xx[k] = X[k]+Offset[0]+Raise[0][k] ;
      yy[k] = Y[k]+Offset[1]+Raise[1][k] ;
      zz[k] = Z[k]+Offset[2]+Raise[2][k] ;
    }
    glBegin(GL_LINES);
    glVertex3d(xx[0], yy[0], zz[0]); glVertex3d(xx[1], yy[1], zz[1]);
    glVertex3d(xx[0], yy[0], zz[0]); glVertex3d(xx[2], yy[2], zz[2]);
    glVertex3d(xx[0], yy[0], zz[0]); glVertex3d(xx[3], yy[3], zz[3]);
    glVertex3d(xx[1], yy[1], zz[1]); glVertex3d(xx[2], yy[2], zz[2]);
    glVertex3d(xx[1], yy[1], zz[1]); glVertex3d(xx[3], yy[3], zz[3]);
    glVertex3d(xx[2], yy[2], zz[2]); glVertex3d(xx[3], yy[3], zz[3]);
    glEnd();
    break;
  }
}


/* ------------------------------------------------------------------------ */
/*  Scalar Simplices                                                        */
/* ------------------------------------------------------------------------ */

void Draw_ScalarPoint(Post_View *View, 
		      double ValMin, double ValMax, double Raise[3][5],
		      double *X, double *Y, double *Z, double *V){
  double   d;
  char Num[100];

  if(View->Boundary > 0) return;

  d = V[View->TimeStep];

  if(View->SaturateValues){
    if(d > ValMax) d = ValMax;
    else if(d < ValMin) d = ValMin;
  }

  RaiseFill(0, d, ValMin, Raise);

  if(View->ShowElement) Draw_Simplex(0,X,Y,Z,View->Offset,Raise);

  if(d>=ValMin && d<=ValMax){      
    Palette2(View,ValMin,ValMax,d);
    if(View->IntervalsType == DRAW_POST_NUMERIC){
      glRasterPos3d(X[0]+Raise[0][0]+View->Offset[0],
		    Y[0]+Raise[1][0]+View->Offset[1],
		    Z[0]+Raise[2][0]+View->Offset[2]);
      sprintf(Num, View->Format, d);
      Draw_String(Num);
    }
    else
      Draw_Point(X,Y,Z,View->Offset,Raise);
  }
}

void Draw_ScalarLine(Post_View *View, 
		     double ValMin, double ValMax, double Raise[3][5],
		     double *X, double *Y, double *Z, double *V){

  int     i,k,nb=0;
  double  d;
  double  Xp[5],Yp[5],Zp[5],Val[5],value[5],thev;
  char    Num[100] ;

  if(View->Boundary > 0){
    View->Boundary--;
    Draw_ScalarPoint(View, ValMin, ValMax, Raise, &X[0], &Y[0], &Z[0], &V[0]);//0
    Draw_ScalarPoint(View, ValMin, ValMax, Raise, &X[1], &Y[1], &Z[1], &V[1]);//1
    View->Boundary++;
    return;
  }

  double *vv = &V[2*View->TimeStep];
  if(View->SaturateValues){
    for(i=0;i<2;i++){
      if(vv[i] > ValMax) Val[i] = ValMax;
      else if(vv[i] < ValMin) Val[i] = ValMin;
      else Val[i] = vv[i];
    }
  }
  else{
    for(i=0;i<2;i++){	      
      Val[i] = vv[i];
    }
  }

  for(k=0 ; k<2 ; k++)
    RaiseFill(k, Val[k], ValMin, Raise);

  if(View->ShowElement) Draw_Simplex(1,X,Y,Z,View->Offset,Raise);

  if(View->IntervalsType == DRAW_POST_NUMERIC){

    d = (Val[0]+Val[1]) / 2.;

    if(d >= ValMin && d <= ValMax){
      Palette2(View,ValMin,ValMax,d);
      sprintf(Num, View->Format, d);
      glRasterPos3d((X[0]+Raise[0][0] + X[1]+Raise[0][1])/2. + View->Offset[0],
		    (Y[0]+Raise[1][0] + Y[1]+Raise[1][1])/2. + View->Offset[1],
		    (Z[0]+Raise[2][0] + Z[1]+Raise[2][1])/2. + View->Offset[2]);
      Draw_String(Num);
    }

  }
  else{

    if(View->IntervalsType==DRAW_POST_CONTINUOUS){

      if(Val[0] >= ValMin && Val[0] <= ValMax &&
         Val[1] >= ValMin && Val[1] <= ValMax){
	glBegin(GL_LINES);
	Palette2(View,ValMin,ValMax,Val[0]);
	glVertex3d(X[0]+View->Offset[0]+Raise[0][0],
		   Y[0]+View->Offset[1]+Raise[1][0],
		   Z[0]+View->Offset[2]+Raise[2][0]);
	Palette2(View,ValMin,ValMax,Val[1]);
	glVertex3d(X[1]+View->Offset[0]+Raise[0][1],
		   Y[1]+View->Offset[1]+Raise[1][1],
		   Z[1]+View->Offset[2]+Raise[2][1]);
	glEnd();
      }
      else{
	//todo
      }

    }
    else{
      for(k=0 ; k<View->NbIso ; k++){
	Palette(View,View->NbIso,k);
	if(View->IntervalsType==DRAW_POST_DISCRETE){
	  CutLine1D(X,Y,Z,&Val[0],
		    View->GVFI(ValMin,ValMax,View->NbIso+1,k),
		    View->GVFI(ValMin,ValMax,View->NbIso+1,k+1),
		    ValMin,ValMax,Xp,Yp,Zp,&nb,value);    
	  if(nb == 2){
	    for(i=0;i<2;i++) RaiseFill(i,value[i],ValMin,Raise);    
	    Draw_Line(Xp,Yp,Zp,View->Offset,Raise);  
	  }
	}
	else{
	  thev = View->GVFI(ValMin,ValMax,View->NbIso,k);
	  CutLine0D(X,Y,Z,&Val[0],
		    thev, ValMin,ValMax,Xp,Yp,Zp,&nb);    
	  if(nb){
	    RaiseFill(0,thev,ValMin,Raise);
	    Draw_Point(Xp,Yp,Zp,View->Offset,Raise);    
	  }
	}
      }
    }

  }

}

void Draw_ScalarTriangle(Post_View *View, int preproNormals,
			 double ValMin, double ValMax, double Raise[3][5],
			 double *X, double *Y, double *Z, double *V){

  int     i, k, nb=0;
  double  d;
  double  x1x0, y1y0, z1z0, x2x0, y2y0, z2z0, nn[3], norms[9];
  double  Xp[5],Yp[5],Zp[5],Val[3],value[5],thev;
  char    Num[100] ;

  if(!preproNormals && View->Boundary > 0){
    View->Boundary--;
    Draw_ScalarLine(View, ValMin, ValMax, Raise, &X[0], &Y[0], &Z[0], &V[0]);//01
    Draw_ScalarLine(View, ValMin, ValMax, Raise, &X[1], &Y[1], &Z[1], &V[1]);//12
    Xp[0] = X[0]; Yp[0] = Y[0]; Zp[0] = Z[0]; Val[0] = V[0];
    Xp[1] = X[2]; Yp[1] = Y[2]; Zp[1] = Z[2]; Val[1] = V[2];
    Draw_ScalarLine(View, ValMin, ValMax, Raise, Xp, Yp, Zp, Val);//02
    View->Boundary++;
    return;
  }

  double *vv = &V[3*View->TimeStep];
  if(View->SaturateValues){
    for(i=0;i<3;i++){
      if(vv[i] > ValMax) Val[i] = ValMax;
      else if(vv[i] < ValMin) Val[i] = ValMin;
      else Val[i] = vv[i];
    }
  }
  else{
    for(i=0;i<3;i++){	      
      Val[i] = vv[i];
    }
  }

  for(k=0 ; k<3 ; k++)
    RaiseFill(k, Val[k], ValMin, Raise);

  if(View->Light){

    x1x0 = (X[1]+Raise[0][1]) - (X[0]+Raise[0][0]); 
    y1y0 = (Y[1]+Raise[1][1]) - (Y[0]+Raise[1][0]);
    z1z0 = (Z[1]+Raise[2][1]) - (Z[0]+Raise[2][0]); 
    x2x0 = (X[2]+Raise[0][2]) - (X[0]+Raise[0][0]);
    y2y0 = (Y[2]+Raise[1][2]) - (Y[0]+Raise[1][0]); 
    z2z0 = (Z[2]+Raise[2][2]) - (Z[0]+Raise[2][0]);
    nn[0]  = y1y0 * z2z0 - z1z0 * y2y0 ;
    nn[1]  = z1z0 * x2x0 - x1x0 * z2z0 ;
    nn[2]  = x1x0 * y2y0 - y1y0 * x2x0 ;

    if(View->SmoothNormals){
      if(preproNormals){
	for(i=0;i<3;i++){
	  View->add_normal(X[i]+Raise[0][i],Y[i]+Raise[1][i],Z[i]+Raise[2][i],
			   nn[0],nn[1],nn[2]);
	}
	return;
      }
      else{
	for(i=0;i<3;i++){
	  if(!View->get_normal(X[i]+Raise[0][i],Y[i]+Raise[1][i],Z[i]+Raise[2][i],
			       norms[3*i],norms[3*i+1],norms[3*i+2])){
	    //Msg(WARNING, "Oups, did not find smoothed normal");
	    norms[3*i] = nn[0];
	    norms[3*i+1] = nn[1];
	    norms[3*i+2] = nn[2];
	  }
	}
      }
    }
    else{
      for(i=0;i<3;i++){
	norms[3*i] = nn[0];
	norms[3*i+1] = nn[1];
	norms[3*i+2] = nn[2];
      }
    }
    glNormal3dv(nn);
  }

  if(preproNormals) return;

  if(View->ShowElement) Draw_Simplex(2,X,Y,Z,View->Offset,Raise);

  if(View->IntervalsType == DRAW_POST_NUMERIC){

    d = (Val[0]+Val[1]+Val[2]) / 3.;
    if(d >= ValMin && d <= ValMax){
      Palette2(View,ValMin,ValMax,d);
      sprintf(Num, View->Format, d);
      glRasterPos3d( (X[0]+Raise[0][0] + X[1]+Raise[0][1] + X[2]+Raise[0][2])/3. + 
		     View->Offset[0],
		     (Y[0]+Raise[1][0] + Y[1]+Raise[1][1] + Y[2]+Raise[1][2])/3. +
		     View->Offset[1],
		     (Z[0]+Raise[2][0] + Z[1]+Raise[2][1] + Z[2]+Raise[2][2])/3. + 
		     View->Offset[2] );
      Draw_String(Num);
    }

  }
  else{
    
    if(View->IntervalsType == DRAW_POST_CONTINUOUS){
      if(Val[0] >= ValMin && Val[0] <= ValMax &&
         Val[1] >= ValMin && Val[1] <= ValMax &&
         Val[2] >= ValMin && Val[2] <= ValMax){
        glBegin(GL_TRIANGLES);
	Palette2(View,ValMin,ValMax,Val[0]);
	glNormal3dv(&norms[0]);
        glVertex3d(X[0]+View->Offset[0]+Raise[0][0],
                   Y[0]+View->Offset[1]+Raise[1][0],
                   Z[0]+View->Offset[2]+Raise[2][0]);
	Palette2(View,ValMin,ValMax,Val[1]);
	glNormal3dv(&norms[3]);
        glVertex3d(X[1]+View->Offset[0]+Raise[0][1],
                   Y[1]+View->Offset[1]+Raise[1][1],
                   Z[1]+View->Offset[2]+Raise[2][1]);
	Palette2(View,ValMin,ValMax,Val[2]);
	glNormal3dv(&norms[6]);
        glVertex3d(X[2]+View->Offset[0]+Raise[0][2],
                   Y[2]+View->Offset[1]+Raise[1][2],
                   Z[2]+View->Offset[2]+Raise[2][2]);
        glEnd();
      }
      else{
        CutTriangle2D(X,Y,Z,Val,
                      ValMin,ValMax,ValMin,ValMax,
                      Xp,Yp,Zp,&nb,value);
        if(nb >= 3){      
          glBegin(GL_POLYGON);
          for(i=0 ; i<nb ; i++){
	    Palette2(View,ValMin,ValMax,value[i]);
            RaiseFill(i,value[i],ValMin,Raise);
            glVertex3d(Xp[i]+View->Offset[0]+Raise[0][i],
                       Yp[i]+View->Offset[1]+Raise[1][i],
                       Zp[i]+View->Offset[2]+Raise[2][i]);
          }
          glEnd();
        }
      }
    }
    else{
      for(k=0 ; k<View->NbIso ; k++){
        if(View->IntervalsType == DRAW_POST_DISCRETE){
          Palette(View,View->NbIso,k);
          CutTriangle2D(X,Y,Z,Val,
                        View->GVFI(ValMin,ValMax,View->NbIso+1,k),
                        View->GVFI(ValMin,ValMax,View->NbIso+1,k+1),
                        ValMin,ValMax,
                        Xp,Yp,Zp,&nb,value);      
          if(nb >= 3){
            for(i=0 ; i<nb ; i++) RaiseFill(i,value[i],ValMin,Raise);    
            Draw_Polygon(nb,Xp,Yp,Zp,View->Offset,Raise);  
          }
        }
        else{
          Palette(View,View->NbIso,k);
          thev = View->GVFI(ValMin,ValMax,View->NbIso,k);
          CutTriangle1D(X,Y,Z,Val,
                        thev, ValMin,ValMax,Xp,Yp,Zp,&nb);        
          if(nb == 2){
            for(i=0 ; i<2 ; i++) RaiseFill(i,thev,ValMin,Raise);
            Draw_Line(Xp,Yp,Zp,View->Offset,Raise);    
          }
        }
      }
    }

  }
    
}

void Draw_ScalarTetrahedron(Post_View *View, int preproNormals,
			    double ValMin, double ValMax, double Raise[3][5],
			    double *X, double *Y, double *Z, double *V){

  int     k,i;
  double  d, xx[4], yy[4], zz[4];
  char Num[100];
  double Val[4];

  if(!preproNormals && View->Boundary > 0){
    View->Boundary--;
    Draw_ScalarTriangle(View, 0, ValMin, ValMax, Raise, &X[0], &Y[0], &Z[0], &V[0]);//012
    Draw_ScalarTriangle(View, 0, ValMin, ValMax, Raise, &X[1], &Y[1], &Z[1], &V[1]);//123
    xx[0] = X[0]; yy[0] = Y[0]; zz[0] = Z[0]; Val[0] = V[0];
    xx[1] = X[1]; yy[1] = Y[1]; zz[1] = Z[1]; Val[1] = V[1];
    xx[2] = X[3]; yy[2] = Y[3]; zz[2] = Z[3]; Val[2] = V[3];
    Draw_ScalarTriangle(View, 0, ValMin, ValMax, Raise, xx, yy, zz, Val);//013
    xx[1] = X[2]; yy[1] = Y[2]; zz[1] = Z[2]; Val[1] = V[2];
    Draw_ScalarTriangle(View, 0, ValMin, ValMax, Raise, xx, yy, zz, Val);//023
    View->Boundary++;
    return;
  }

  double *vv = &V[4*View->TimeStep];
  if(View->SaturateValues){
    for(i=0;i<4;i++){
      if(vv[i] > ValMax) Val[i] = ValMax;
      else if(vv[i] < ValMin) Val[i] = ValMin;
      else Val[i] = vv[i];
    }
  }
  else{
    for(i=0;i<4;i++){	      
      Val[i] = vv[i];
    }
  }

  for(k=0 ; k<4 ; k++)
    RaiseFill(k, Val[k], ValMin, Raise);

  if(!preproNormals && View->ShowElement) Draw_Simplex(3,X,Y,Z,View->Offset,Raise);

  if(!preproNormals && View->IntervalsType == DRAW_POST_NUMERIC){

    d = 0.25 * (Val[0]  +Val[1]+Val[2] + Val[3]);
    if(d >= ValMin && d <= ValMax){
      Palette2(View,ValMin,ValMax,d);
      sprintf(Num, View->Format, d);
      glRasterPos3d(0.25 * (X[0]+Raise[0][0] + X[1]+Raise[0][1] + 
			    X[2]+Raise[0][2] + X[3]+Raise[0][3]) + View->Offset[0],
		    0.25 * (Y[0]+Raise[1][0] + Y[1]+Raise[1][1] + 
			    Y[2]+Raise[1][2] + Y[3]+Raise[1][3]) + View->Offset[1],
		    0.25 * (Z[0]+Raise[2][0] + Z[1]+Raise[2][1] + 
			    Z[2]+Raise[2][2] + Z[3]+Raise[2][3]) + View->Offset[2]);
      Draw_String(Num);
    }

  }
  else{
    for(k=0 ; k<View->NbIso ; k++){
      if(!preproNormals) Palette(View,View->NbIso,k);
      IsoSimplex(View, preproNormals, X, Y, Z, Val,
		 View->GVFI(ValMin,ValMax,View->NbIso,k), 
		 ValMin, ValMax, View->Offset, Raise);
    }

  }

}

/* ------------------------------------------------------------------------ */
/*  Vector Simplices                                                        */
/* ------------------------------------------------------------------------ */

void Draw_VectorSimplex(int nbnod, Post_View *View, 
			double ValMin, double ValMax, double Raise[3][5],
			double *X, double *Y, double *Z, double *V){
  int    j, k ;
  double fact, xx[4], yy[4], zz[4],  xc=0., yc=0., zc=0., Val[4][3], d[4];
  double dx=0., dy=0., dz=0., dd;
  char   Num[100];

  for(k=0 ; k<nbnod ; k++){
    Val[k][0] = V[3*nbnod*View->TimeStep+3*k] ;
    Val[k][1] = V[3*nbnod*View->TimeStep+3*k+1] ;
    Val[k][2] = V[3*nbnod*View->TimeStep+3*k+2] ;              
    d[k] = sqrt(Val[k][0]*Val[k][0]+Val[k][1]*Val[k][1]+Val[k][2]*Val[k][2]);            
    RaiseFill(k, d[k], ValMin, Raise);
  }

  if(View->ArrowType == DRAW_POST_DISPLACEMENT){

    fact = View->ArrowScale/50. ;
    for(k=0 ; k<nbnod ; k++){
      xx[k] = X[k] + fact * Val[k][0] + Raise[0][k] + View->Offset[0];
      yy[k] = Y[k] + fact * Val[k][1] + Raise[1][k] + View->Offset[1];
      zz[k] = Z[k] + fact * Val[k][2] + Raise[2][k] + View->Offset[2];
    }

    switch(nbnod){
    case 1:
      Palette2(View,ValMin,ValMax,d[0]);
      glBegin(GL_POINTS);
      glVertex3d(xx[0],yy[0],zz[0]);
      glEnd();
      if(View->TimeStep){//draw trajectory
	glBegin(GL_LINE_STRIP);
	for(j=0 ; j<View->TimeStep+1 ; j++){
	  dx = V[3*(View->TimeStep-j)]  ;
	  dy = V[3*(View->TimeStep-j)+1];
	  dz = V[3*(View->TimeStep-j)+2];
	  dd = sqrt(dx*dx+dy*dy+dz*dz);
	  Palette2(View,ValMin,ValMax,dd);
	  glVertex3d(X[0] + fact*dx + Raise[0][0] + View->Offset[0],
		     Y[0] + fact*dy + Raise[1][0] + View->Offset[1],
		     Z[0] + fact*dz + Raise[2][0] + View->Offset[2]);
	}
	glEnd();
      }
      break;
    case 2: Draw_ScalarLine(View, ValMin, ValMax, Raise, xx, yy, zz, d); break;
    case 3: Draw_ScalarTriangle(View, 0, ValMin, ValMax, Raise, xx, yy, zz, d); break;
    case 4: Draw_ScalarTetrahedron(View, 0, ValMin, ValMax, Raise, xx, yy, zz, d); break;
    }
    return;
  }

  if(View->ShowElement) Draw_Simplex(nbnod-1,X,Y,Z,View->Offset,Raise);

  if(View->ArrowLocation == DRAW_POST_LOCATE_COG ||
     View->IntervalsType == DRAW_POST_NUMERIC){
    for(k = 0 ; k<nbnod ; k++){
      dx += Val[k][0]; xc += X[k] + Raise[0][k];
      dy += Val[k][1]; yc += Y[k] + Raise[1][k];
      dz += Val[k][2]; zc += Z[k] + Raise[2][k];
    }
    dx /= (double)nbnod; xc /= (double)nbnod;
    dy /= (double)nbnod; yc /= (double)nbnod;
    dz /= (double)nbnod; zc /= (double)nbnod;
    dd = sqrt(dx*dx+dy*dy+dz*dz);
    if(dd!=0.0 && dd>=ValMin && dd<=ValMax){             
      Palette(View,View->NbIso,View->GIFV(ValMin,ValMax,View->NbIso,dd));            
      if(View->IntervalsType == DRAW_POST_NUMERIC){
	glRasterPos3d(xc + View->Offset[0],
		      yc + View->Offset[1],
		      zc + View->Offset[2]);
	sprintf(Num, View->Format, dd);
	Draw_String(Num);
      }
      else{
	fact = CTX.pixel_equiv_x/CTX.s[0] * View->ArrowScale/ValMax ;
	if(View->ScaleType == DRAW_POST_LOGARITHMIC && ValMin>0){
	  dx /= dd ; dy /= dd ; dz /= dd ;
	  dd = log10(dd/ValMin) ; 
	  dx *= dd ; dy *= dd ; dz *= dd ;
	}
	RaiseFill(0, dd, ValMin, Raise);         
	Draw_Vector(View->ArrowType, View->IntervalsType!=DRAW_POST_ISO,
		    xc, yc, zc, fact*dd, fact*dx, fact*dy, fact*dz,
		    View->Offset, Raise);
      }
    }
  }
  else{
    for(k=0 ; k<nbnod ; k++){
      if(d[k]!=0.0 && d[k]>=ValMin && d[k]<=ValMax){           
	Palette(View,View->NbIso,View->GIFV(ValMin,ValMax,View->NbIso,d[k]));
	fact = CTX.pixel_equiv_x/CTX.s[0] * View->ArrowScale/ValMax ;
	if(View->ScaleType == DRAW_POST_LOGARITHMIC && ValMin>0){
	  Val[k][0] /= d[k] ; Val[k][1] /= d[k] ; Val[k][2] /= d[k] ;
	  d[k] = log10(d[k]/ValMin) ;
	  Val[k][0] *= d[k] ; Val[k][1] *= d[k] ; Val[k][2] *= d[k] ;
	}
	RaiseFill(0, d[k], ValMin, Raise);         
	Draw_Vector(View->ArrowType, View->IntervalsType!=DRAW_POST_ISO,
		    X[k], Y[k], Z[k],
		    fact*d[k], fact*Val[k][0], fact*Val[k][1], fact*Val[k][2],
		    View->Offset, Raise);
      }               
    }       
  }

}

void Draw_VectorPoint(Post_View *View, 
		      double ValMin, double ValMax, double Raise[3][5],
		      double *X, double *Y, double *Z, double *V){
  Draw_VectorSimplex(1, View, ValMin, ValMax, Raise, X, Y, Z, V);
}

void Draw_VectorLine(Post_View *View, 
		     double ValMin, double ValMax, double Raise[3][5],
		     double *X, double *Y, double *Z, double *V){
  Draw_VectorSimplex(2, View, ValMin, ValMax, Raise, X, Y, Z, V);
}

void Draw_VectorTriangle(Post_View *View, 
			 double ValMin, double ValMax, double Raise[3][5],
			 double *X, double *Y, double *Z, double *V){
  Draw_VectorSimplex(3, View, ValMin, ValMax, Raise, X, Y, Z, V);
}

void Draw_VectorTetrahedron(Post_View *View, 
			    double ValMin, double ValMax, double Raise[3][5],
			    double *X, double *Y, double *Z, double *V){
  Draw_VectorSimplex(4, View, ValMin, ValMax, Raise, X, Y, Z, V);
}


/* ------------------------------------------------------------------------ */
/*  Tensor Simplices                                                        */
/* ------------------------------------------------------------------------ */

static int TensorError = 0 ;

void Draw_TensorSimplex(int nbnod, Post_View *View, 
			double ValMin, double ValMax, double Raise[3][5],
			double *X, double *Y, double *Z, double *V){
  if(!TensorError){
    TensorError = 1;
    Msg(GERROR, "Tensor field visualization is not implemented");
    Msg(GERROR, "We *need* some ideas on how to implement this!");
    Msg(GERROR, "Send your ideas to <gmsh@geuz.org>!");
  }
}


void Draw_TensorPoint(Post_View *View, 
		      double ValMin, double ValMax, double Raise[3][5],
		      double *X, double *Y, double *Z, double *V){
  Draw_TensorSimplex(1, View, ValMin, ValMax, Raise, X, Y, Z, V);
}

void Draw_TensorLine(Post_View *View, 
		     double ValMin, double ValMax, double Raise[3][5],
		     double *X, double *Y, double *Z, double *V){
  Draw_TensorSimplex(2, View, ValMin, ValMax, Raise, X, Y, Z, V);
}

void Draw_TensorTriangle(Post_View *View, 
			 double ValMin, double ValMax, double Raise[3][5],
			 double *X, double *Y, double *Z, double *V){
  Draw_TensorSimplex(3, View, ValMin, ValMax, Raise, X, Y, Z, V);
}

void Draw_TensorTetrahedron(Post_View *View, 
			    double ValMin, double ValMax, double Raise[3][5],
			    double *X, double *Y, double *Z, double *V){
  Draw_TensorSimplex(4, View, ValMin, ValMax, Raise, X, Y, Z, V);
}

