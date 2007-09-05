#include "GUI_Classifier.h"
#include "Geo.h"
#include "Gmsh.h"
#include "Draw.h"
#include "Options.h"
#include "Context.h"
#include "SelectBuffer.h"
#include "GUI_Projection.h"
#include "GUI_Extras.h"
#include "Message.h"
#include "meshGFaceDelaunayInsertion.h"
#include "meshGFaceOptimize.h"
#include "gmshEdge.h"
#include "gmshFace.h"

extern Mesh *THEM;
extern Context_T CTX;

void buildListOfEdgeAngle ( e2t_cont adj,std::vector<edge_angle> &edges_detected,std::vector<edge_angle> &edges_lonly);

int maxEdgeNum ()
{
  GModel::eiter it =  GModel::current()->firstEdge();
  GModel::eiter ite = GModel::current()->lastEdge();
  int MAXX = 0;
  while (it != ite)
    {
      MAXX = std::max (MAXX, (*it)->tag());
      ++it;
    }
  return MAXX;
}

int maxFaceNum ()
{
  GModel::fiter it =  GModel::current()->firstFace();
  GModel::fiter ite = GModel::current()->lastFace();
  int MAXX = 0;
  while (it != ite)
    {
      MAXX = std::max (MAXX, (*it)->tag());
      ++it;
    }
  return MAXX;
}


struct compareMLinePtr 
{
  bool operator () ( MLine *l1 , MLine *l2) const
  {
    static Less_Edge le;
    return le(l1->getEdge(0),l2->getEdge(0)); 
  }
};

 
void recurClassify ( MTri3 *t , 
		     std::vector<MTriangle *> &triangles,
		     std::map<MLine*, GEdge*, compareMLinePtr> &lines,
		     std::set<GEdge*> &closure)
{
  if (!t->isDeleted())
    {
      triangles.push_back(t->tri());
      t->setDeleted ( true );
      
      for (int i=0;i<3;i++)
	{
	  MTri3 *tn = t->getNeigh(i);
	  if (tn)
	    {
	      edgeXface exf ( t, i);
	      MLine ml (exf.v[0],exf.v[1]);	  
	      std::map<MLine*, GEdge*, compareMLinePtr>::iterator it = lines.find(&ml);
	      if (it==lines.end())
		recurClassify (tn, triangles,lines, closure);
	      else
		closure.insert(it->second);
	    }
	}  
    }
}



void class_color_cb(Fl_Widget* w, void* data)
{
  classificationEditor *e = (classificationEditor*)data;
  std::map<MLine*, GEdge*, compareMLinePtr> lines;
  {
    GModel::eiter it =  GModel::current()->firstEdge();
    GModel::eiter ite = GModel::current()->lastEdge();
    for( ;it!=ite;++it)
      {
	for (int i=0;i<(*it)->lines.size();i++)lines[(*it)->lines[i] ] = *it;
      }
  }


  std::list<MTri3*> tris;
  {
    std::set<GFace*>::iterator it = e->_faces.begin();
    while (it != e->_faces.end())
      {
	GFace *gf = *it;
	for (int i=0;i<gf->triangles.size();i++)
	  {
	    tris.push_back (new MTri3 ( gf->triangles [i] , 0 ) );
	  }
	gf->triangles.clear();
	++it;
      }
  }


  connectTriangles (tris);

  {
    std::list<MTri3*> ::iterator it = tris.begin();
    while (it != tris.end())
      {
	if (!(*it)->isDeleted())
	  {
	    std::set<GEdge*> closure;
	    std::vector<MTriangle*> triangles;
	    gmshFace *temporary = new gmshFace ( GModel::current(), maxFaceNum() + 1);
	    recurClassify ( *it , temporary->triangles,lines, closure); 
	    GModel::current()->add (temporary);
	    e->tempFaces.push_back(temporary);	    	    
	  }
	++it;
      }

    it = tris.begin();
    while (it != tris.end())
      {
	delete *it;
	++it;
      }
  }

  CTX.mesh.changed = ENT_ALL;
  Draw();  
  Msg(ONSCREEN, "");

}

void updateedges_cb(Fl_Widget* w, void* data)
{
  classificationEditor *e = (classificationEditor*)data;
 
  //  printf("%d edges detected\n",e->edges_detected.size());

  for (int i=0;i<e->temporary->lines.size();i++)
    {
      delete e->temporary->lines[i];
    }
  e->temporary->lines.clear();

  for ( int i=0 ; i<e->edges_detected.size();i++)
    {
      edge_angle ea =  e->edges_detected[i];
      //      printf("angle = %g\n",ea.angle);
      if ( ea.angle  <= e -> _inputs[CLASSVALUE_ANGLE] ->value() / 180 * M_PI) 
	break;
      e->temporary->lines.push_back(new MLine(ea.v1, ea.v2));            
    } 

  if (e->_togbuttons[CLASSTOGBUTTON_CLOS]->value())
    {
      for ( int i=0 ; i<e->edges_lonly.size();i++)
	{
	  edge_angle ea =  e->edges_lonly[i];
	  e->temporary->lines.push_back(new MLine(ea.v1, ea.v2));            
	} 
    }
  

  CTX.mesh.changed = ENT_ALL;
  Draw();   
}

edge_angle::  edge_angle ( MVertex *_v1, MVertex *_v2, MTriangle *t1, MTriangle *t2)
  : v1(_v1), v2(_v2)
{
  if (!t2) angle = 0;
  else
    {
      double c1[3];
      double c2[3];
      double c3[3];
      {
	MVertex *p1 = t1->getVertex(0);
	MVertex *p2 = t1->getVertex(1);
	MVertex *p3 = t1->getVertex(2);
	double a[3] = { p1->x() - p2->x(), p1->y() - p2->y(), p1->z() - p2->z() };
	double b[3] = { p1->x() - p3->x(), p1->y() - p3->y(), p1->z() - p3->z() };
	c1[2] = a[0] * b[1] - a[1] * b[0];
	c1[1] = -a[0] * b[2] + a[2] * b[0];
	c1[0] = a[1] * b[2] - a[2] * b[1];
      }
      {
	MVertex *p1 = t2->getVertex(0);
	MVertex *p2 = t2->getVertex(1);
	MVertex *p3 = t2->getVertex(2);
	double a[3] = { p1->x() - p2->x(), p1->y() - p2->y(), p1->z() - p2->z() };
	double b[3] = { p1->x() - p3->x(), p1->y() - p3->y(), p1->z() - p3->z() };
	c2[2] = a[0] * b[1] - a[1] * b[0];
	c2[1] = -a[0] * b[2] + a[2] * b[0];
	c2[0] = a[1] * b[2] - a[2] * b[1];
      }
      norme(c1);
      norme(c2);
      prodve(c1,c2,c3);
      double cosa ; prosca(c1,c2,&cosa);
      double sina = norme (c3);
      angle = atan2(sina,cosa);
    }
  
}
void buildListOfEdgeAngle ( e2t_cont adj,std::vector<edge_angle> &edges_detected,std::vector<edge_angle> &edges_lonly)
{
  e2t_cont::iterator it = adj.begin();
  for ( ; it!=adj.end();++it )
    {
      if ( it->second.second ) edges_detected.push_back ( edge_angle ( it->first.getVertex (0) ,it->first.getVertex (1) , 
								       it->second.first,it->second.second) );
      else edges_lonly.push_back ( edge_angle ( it->first.getVertex (0) ,it->first.getVertex (1) , 
						it->second.first,it->second.second) );	
    }
  std::sort ( edges_detected .begin() ,  edges_detected .end() );
}


classificationEditor::classificationEditor() 
{

  // construct GUI in terms of standard sizes
  const int BH = 2 * GetFontSize() + 1, BB = 12 * GetFontSize(), WB = 7;
  const int width = (int)(3.5 * BB), height = 10 * BH;

  _window = new Dialog_Window(width, height, "Classify");
  
  Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
  {
    Fl_Group *o = new Fl_Group(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Edge Detection");
    //    o->hide();
    // create all widgets (we construct this once, we never deallocate!)
    
    _buttons[CLASSBUTTON_SELECT] = 
      new Fl_Button       (2*WB, 2*WB+1*BH, BB, BH, "Select Elements");
    _buttons[CLASSBUTTON_SELECT]->callback(class_select_cb, this);
    
    _togbuttons[CLASSTOGBUTTON_HIDE] = 
      new Fl_Toggle_Button(3*WB+BB, 2*WB+1*BH, BB, BH, "Hide Unselected");
    _togbuttons[CLASSTOGBUTTON_HIDE]->callback(class_hide_cb,this);

    _togbuttons[CLASSTOGBUTTON_CLOS] = 
      new Fl_Toggle_Button(4*WB+2*BB, 2*WB+1*BH, BB, BH, "Include Closure");
    _togbuttons[CLASSTOGBUTTON_CLOS]->callback(updateedges_cb,this);
    
    _inputs[CLASSVALUE_ANGLE] = 
      new Fl_Value_Input(2*WB, 3*WB+2*BH, BB, BH, "Treshold Angle");
    _inputs[CLASSVALUE_ANGLE]->value(40);
    _inputs [CLASSVALUE_ANGLE]->maximum(90);
    _inputs[CLASSVALUE_ANGLE]->minimum(0);
    _inputs[CLASSVALUE_ANGLE]->align(FL_ALIGN_RIGHT);
    _inputs[CLASSVALUE_ANGLE]->step(1);
    _inputs[CLASSVALUE_ANGLE]->when(FL_WHEN_RELEASE);  
    _inputs[CLASSVALUE_ANGLE]->callback(updateedges_cb,this);

    _buttons[CLASSBUTTON_DEL] = 
      new Fl_Button       (2*WB, 5*WB+4*BH, BB, BH, "Delete Edge");
    _buttons[CLASSBUTTON_DEL]->callback(class_deleteedge_cb, this);    
    _buttons[CLASSBUTTON_ADD] = 
      new Fl_Button       (2*WB, 6*WB+5*BH, BB, BH, "Save Selection");
    _buttons[CLASSBUTTON_ADD]->callback(class_save_cb, this);    
    _buttons[CLASSBUTTON_CLEAR] = 
      new Fl_Button       (2*WB, 7*WB+6*BH, BB, BH, "Clear All");
    _buttons[CLASSBUTTON_CLEAR]->callback(class_clear_cb, this);    
    o->end();
  }
  {
    Fl_Group *o = new Fl_Group(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Face Colouring");
    o->hide();
    _buttons[CLASSBUTTON_SELFAC] = 
      new Fl_Button       (2*WB, 2*WB+1*BH, BB, BH, "Select Model Face");
    _buttons[CLASSBUTTON_SELFAC]->callback(class_selectgface_cb, this);
    _buttons[CLASSBUTTON_COLOR] = 
      new Fl_Button       (2*WB, 3*WB+2*BH, BB, BH, "Classify Mesh Faces");
    _buttons[CLASSBUTTON_COLOR]->callback(class_color_cb, this);
    o->end();
  }

  // allocate detected edges
  // temporary for the selection
  // saved for the ones that have been saved by the user
  // and that will be used for next step

  temporary = new gmshEdge ( GModel::current(), maxEdgeNum() + 1 );
  GModel::current()->add (temporary);
  saved = new gmshEdge ( GModel::current(), maxEdgeNum() + 1 );
  GModel::current()->add (saved);
  
  _window->end();
  _window->hotspot(_window);
  _window->size_range(width, (int)(0.85 * height));    
}


void class_hide_cb(Fl_Widget *w, void *data)
{
  CTX.hide_unselected = !CTX.hide_unselected;
  CTX.mesh.changed = ENT_ALL;
  Draw();
}

void class_select_cb(Fl_Widget *w, void *data)
{
  classificationEditor *e = (classificationEditor*)data;
  std::vector<GVertex*> vertices;
  std::vector<GEdge*> edges;
  std::vector<GFace*> faces;
  std::vector<GRegion*> regions;
  std::vector<MElement*> elements;
  std::vector<MTriangle*> &ele(e->getElements());

  CTX.pick_elements = 1;

  while(1) {
    CTX.mesh.changed = ENT_ALL;
    Draw();

    Msg(ONSCREEN, "Select Elements\n"
	"[Press 'e' to end selection or 'q' to abort]");
    
    char ib = SelectEntity(ENT_ALL, vertices, edges, faces, regions, elements);
    if(ib == 'l') {
      if(CTX.pick_elements){
	for(unsigned int i = 0; i < elements.size(); i++){
	  if(elements[i]->getNumEdges() == 3 && elements[i]->getVisibility() != 2){
	    elements[i]->setVisibility(2); ele.push_back((MTriangle*)elements[i]);
	  }
	}
      }
    }
    if(ib == 'r') {
      for(unsigned int i = 0; i < elements.size(); i++)
	elements[i]->setVisibility(1);
    }
    // ok, we compute edges !
    if(ib == 'e') {
      ZeroHighlight();
      e2t_cont adj;
      buildEdgeToTriangle (ele , adj );      
      buildListOfEdgeAngle ( adj,e->edges_detected,e->edges_lonly);
      break;
    }
    // do nothing
    if(ib == 'q') {
      ZeroHighlight();
      ele.clear();
      break;
    }
  }
  
  updateedges_cb(0, data);

  CTX.mesh.changed = ENT_ALL;
  CTX.pick_elements = 0;
  Draw();  
  Msg(ONSCREEN, "");
}


void class_selectgface_cb(Fl_Widget *w, void *data)
{
  classificationEditor *e = (classificationEditor*)data;
  std::vector<GVertex*> vertices;
  std::vector<GEdge*> edges;
  std::vector<GFace*> faces;
  std::vector<GFace*> temp;
  std::vector<GRegion*> regions;
  std::vector<MElement*> elements;

  opt_geometry_surfaces(0, GMSH_SET | GMSH_GUI, 1);

  while(1) {
    CTX.mesh.changed = ENT_ALL;
    Draw();

    Msg(ONSCREEN, "Select Model Face\n"
	"[Press 'e' to end selection or 'q' to abort]");
    
    char ib = SelectEntity(ENT_SURFACE, vertices, edges, faces, regions, elements);
    if(ib == 'l') {
      for(unsigned int i = 0; i < faces.size(); i++){
	HighlightEntity(faces[i]);	
	temp.push_back(faces[i]);
      }
    }
    // ok store the list of gfaces !
    if(ib == 'e') {
      ZeroHighlight();
      for(unsigned int i = 0; i < temp.size(); i++){
	e->_faces.insert (temp[i]);
      }
      break;
    }
    // do nothing
    if(ib == 'q') {
      ZeroHighlight();
      break;
    }
  } 
  CTX.mesh.changed = ENT_ALL;
  Draw();  
  Msg(ONSCREEN, "");
}


void class_deleteedge_cb(Fl_Widget *w, void *data)
{
  classificationEditor *e = (classificationEditor*)data;
  std::vector<GVertex*> vertices;
  std::vector<GEdge*> edges;
  std::vector<GFace*> faces;
  std::vector<GRegion*> regions;
  std::vector<MElement*> elements;
  std::vector<MLine*> ele;
  
  CTX.pick_elements = 1;
  
  while(1) {
    CTX.mesh.changed = ENT_ALL;
    Draw();

    Msg(ONSCREEN, "Select Elements\n"
	"[Press 'e' to end selection or 'q' to abort]");
    
    char ib = SelectEntity(ENT_ALL, vertices, edges, faces, regions, elements);
    if(ib == 'l') {
      if(CTX.pick_elements){
	for(unsigned int i = 0; i < elements.size(); i++){
	  if(elements[i]->getNumEdges() == 1 && elements[i]->getVisibility() != 2){
	    elements[i]->setVisibility(2); ele.push_back((MLine*)elements[i]);
	  }
	}
      }
    }
    if(ib == 'r') {
      for(unsigned int i = 0; i < elements.size(); i++)
	elements[i]->setVisibility(1);
    }
    // ok, we compute edges !
    if(ib == 'e') {
      ZeroHighlight();      
      break;
    }
    // do nothing
    if(ib == 'q') {
      ZeroHighlight();
      ele.clear();
      break;
    }
  }


  std::sort (ele.begin(),ele.end());
  //  look in all temporary edges if a deleted one is present and delete it !
  std::vector<MLine*> temp = e->temporary->lines;
  e->temporary->lines.clear();
       
  for(int i=0;i<temp.size();i++)
    {      
      std::vector<MLine*>::iterator it = std::find (ele.begin(),ele.end(),temp[i]);
      if (it != ele.end())
	{
	  delete temp[i];
	}
      else e->temporary->lines.push_back(temp[i]);
    }
  
  CTX.mesh.changed = ENT_ALL;
  CTX.pick_elements = 0;
  Draw();  
  Msg(ONSCREEN, "");
}


void class_save_cb(Fl_Widget *w, void *data)
{
  classificationEditor *e = (classificationEditor*)data;

  e->saved->lines.insert (e->saved->lines.end(), e->temporary->lines.begin(), e->temporary->lines.end());
  e->temporary->lines.clear();
  e->_elements.clear();
  e->edges_detected.clear();

  CTX.mesh.changed = ENT_ALL;
  CTX.pick_elements = 0;
  Draw();  
  Msg(ONSCREEN, "");
}

void class_clear_cb(Fl_Widget *w, void *data)
{
  classificationEditor *e = (classificationEditor*)data;

  for (int i=0;i<e->temporary->lines.size();i++)
    {      
      delete e->temporary->lines[i];
    }
  e->temporary->lines.clear();

  for (int i=0;i<e->saved->lines.size();i++)
    {      
      delete e->saved->lines[i];
    }
  e->saved->lines.clear();

  CTX.mesh.changed = ENT_ALL;
  CTX.pick_elements = 0;
  Draw();  
  Msg(ONSCREEN, "");
}



void mesh_classify_cb(Fl_Widget* w, void* data)
{
  // create the (static) editor
  static classificationEditor *editor = 0;
  if(!editor){
    editor = new classificationEditor();
  }
  editor->show();
}


