//
// C++ Interface: MSubElement
//
// Description:
//
//
// Authors:  <Frederic Duboeuf>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef _MSUBELEMENT_H_
#define _MSUBELEMENT_H_

#include "GmshMessage.h"
#include "MElement.h"
#include "MTetrahedron.h"
#include "MTriangle.h"
#include "MLine.h"
#include "MPoint.h"


class MSubTetrahedron : public MTetrahedron
{
 protected:
  bool _owner;
  MElement* _orig;
  std::vector<MElement*> _parents;
  IntPt *_intpt;
 public:
  MSubTetrahedron(MVertex *v0, MVertex *v1, MVertex *v2, MVertex *v3, int num=0, int part=0, bool owner=false, MElement* orig=NULL)
    : MTetrahedron(v0, v1, v2, v3, num, part), _owner(owner), _orig(orig), _intpt(0) {}
  MSubTetrahedron(std::vector<MVertex*> v, int num=0, int part=0, bool owner=false, MElement* orig=NULL)
    : MTetrahedron(v, num, part), _owner(owner), _orig(orig), _intpt(0) {}
  ~MSubTetrahedron();
  virtual int getTypeForMSH() const { return MSH_TET_SUB; }
  virtual const polynomialBasis* getFunctionSpace(int order=-1) const;
  virtual const JacobianBasis* getJacobianFuncSpace(int order=-1) const;
  virtual void getShapeFunctions(double u, double v, double w, double s[], int o);
  virtual void getGradShapeFunctions(double u, double v, double w, double s[][3], int o);
  virtual void getHessShapeFunctions(double u, double v, double w, double s[][3][3], int o);
  // the parametric coordinates of the LineChildren are
  // the coordinates in the local parent element.
  virtual bool isInside(double u, double v, double w);
  virtual void getIntegrationPoints(int pOrder, int *npts, IntPt **pts);
  virtual MElement *getParent() const { return _orig; }
  virtual void setParent(MElement *p, bool owner = false) { _orig = p; _owner = owner; }
  virtual bool ownsParent() const { return _owner; }
  virtual std::vector<MElement*> getMultiParents() const { return _parents; }
  virtual void setMultiParent(std::vector<MElement*> &parents, bool owner = false) { _parents = parents; _orig = _parents[0]; _owner = owner; }
};

class MSubTriangle : public MTriangle
{
 protected:
  bool _owner;
  MElement* _orig;
  std::vector<MElement*> _parents;
  IntPt *_intpt;
 public:
  MSubTriangle(MVertex *v0, MVertex *v1, MVertex *v2, int num=0, int part=0, bool owner=false, MElement* orig=NULL)
    : MTriangle(v0, v1, v2, num, part), _owner(owner), _orig(orig), _intpt(0) {}
  MSubTriangle(std::vector<MVertex*> v, int num=0, int part=0, bool owner=false, MElement* orig=NULL)
    : MTriangle(v, num, part), _owner(owner), _orig(orig), _intpt(0) {}
  ~MSubTriangle();
  virtual int getTypeForMSH() const { return MSH_TRI_SUB; }
  virtual const polynomialBasis* getFunctionSpace(int order=-1) const;
  virtual const JacobianBasis* getJacobianFuncSpace(int order=-1) const;
  virtual void getShapeFunctions(double u, double v, double w, double s[], int o);
  virtual void getGradShapeFunctions(double u, double v, double w, double s[][3], int o);
  virtual void getHessShapeFunctions(double u, double v, double w, double s[][3][3], int o);
  // the parametric coordinates of the LineChildren are
  // the coordinates in the local parent element.
  virtual bool isInside(double u, double v, double w);
  virtual void getIntegrationPoints(int pOrder, int *npts, IntPt **pts);
  virtual MElement *getParent() const { return _orig; }
  virtual void setParent(MElement *p, bool owner = false) { _orig = p; _owner = owner; }
  virtual bool ownsParent() const { return _owner; }
  virtual std::vector<MElement*> getMultiParents() const { return _parents; }
  virtual void setMultiParent(std::vector<MElement*> &parents, bool owner = false) { _parents = parents; _orig = _parents[0]; _owner = owner; }
};

class MSubLine : public MLine
{
 protected:
  bool _owner;
  MElement* _orig;
  std::vector<MElement*> _parents;
  IntPt *_intpt;
 public:
  MSubLine(MVertex *v0, MVertex *v1, int num=0, int part=0, bool owner=false, MElement* orig=NULL)
    : MLine(v0, v1, num, part), _owner(owner), _orig(orig), _intpt(0) {}
  MSubLine(std::vector<MVertex*> v, int num=0, int part=0, bool owner=false, MElement* orig=NULL)
    : MLine(v, num, part), _owner(owner), _orig(orig), _intpt(0) {}
  ~MSubLine();
  virtual int getTypeForMSH() const { return MSH_LIN_SUB; }
  virtual const polynomialBasis* getFunctionSpace(int order=-1) const;
  virtual const JacobianBasis* getJacobianFuncSpace(int order=-1) const;
  virtual void getShapeFunctions(double u, double v, double w, double s[], int o);
  virtual void getGradShapeFunctions(double u, double v, double w, double s[][3], int o);
  virtual void getHessShapeFunctions(double u, double v, double w, double s[][3][3], int o);
  // the parametric coordinates of the LineChildren are
  // the coordinates in the local parent element.
  virtual bool isInside(double u, double v, double w);
  virtual void getIntegrationPoints(int pOrder, int *npts, IntPt **pts);
  virtual MElement *getParent() const { return _orig; }
  virtual void setParent(MElement *p, bool owner = false) { _orig = p; _owner = owner; }
  virtual bool ownsParent() const { return _owner; }
  virtual std::vector<MElement*> getMultiParents() const { return _parents; }
  virtual void setMultiParent(std::vector<MElement*> &parents, bool owner = false) { _parents = parents; _orig = _parents[0]; _owner = owner; }
};

class MSubPoint : public MPoint
{
 protected:
  bool _owner;
  MElement* _orig;
  std::vector<MElement*> _parents;
  IntPt *_intpt;
 public:
  MSubPoint(MVertex *v0, int num=0, int part=0, bool owner=false, MElement* orig=NULL)
    : MPoint(v0, num, part), _owner(owner), _orig(orig), _intpt(0) {}
  MSubPoint(std::vector<MVertex*> v, int num=0, int part=0, bool owner=false, MElement* orig=NULL)
    : MPoint(v, num, part), _owner(owner), _orig(orig), _intpt(0) {}
  ~MSubPoint();
  virtual int getTypeForMSH() const { return MSH_PNT_SUB; }
  virtual const polynomialBasis* getFunctionSpace(int order=-1) const;
  virtual const JacobianBasis* getJacobianFuncSpace(int order=-1) const;
  virtual void getShapeFunctions(double u, double v, double w, double s[], int o);
  virtual void getGradShapeFunctions(double u, double v, double w, double s[][3], int o);
  virtual void getHessShapeFunctions(double u, double v, double w, double s[][3][3], int o);
  // the parametric coordinates of the PointChildren are
  // the coordinates in the local parent element.
  virtual bool isInside(double u, double v, double w);
  virtual void getIntegrationPoints(int pOrder, int *npts, IntPt **pts);
  virtual MElement *getParent() const { return _orig; }
  virtual void setParent(MElement *p, bool owner = false) { _orig = p; _owner = owner; }
  virtual bool ownsParent() const { return _owner; }
  virtual std::vector<MElement*> getMultiParents() const { return _parents; }
  virtual void setMultiParent(std::vector<MElement*> &parents, bool owner = false) { _parents = parents; _orig = _parents[0]; _owner = owner; }
};

#endif // _MSUBELEMENT_H_