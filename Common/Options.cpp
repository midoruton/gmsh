// $Id: Options.cpp,v 1.1 2001-02-12 17:39:39 geuzaine Exp $

#include "Gmsh.h"
#include "GmshUI.h"
#include "Geo.h"
#include "Mesh.h"
#include "Draw.h"
#include "Context.h"
#include "Options.h"

// action is a combination of GMSH_SET, GMSH_GET, GMSH_GUI

extern Context_T   CTX ;

#ifdef _FLTK
#include "GUI.h"
extern GUI        *WID ;
#endif

#define NOVIEW Msg(WARNING, "View[%d] does not exist", num)

//******************* Strings ***********************************

char * opt_general_display(OPT_ARGS_STR){
  if(action & GMSH_SET) CTX.display = val;
  return CTX.display;
}


char * opt_view_name(OPT_ARGS_STR){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW;  return NULL; }
  if(action & GMSH_SET) 
    strcpy(v->Name, val);
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number)){
    WID->view_input[0]->value(v->Name);
    WID->m_toggle_butt[num]->label(v->Name);
  }
#endif
  return v->Name;
}
char * opt_view_format(OPT_ARGS_STR){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return NULL; }
  if(action & GMSH_SET)
    strcpy(v->Format, val);
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number))
    WID->view_input[1]->value(v->Format);
#endif
  return v->Format;
}
char * opt_view_filename(OPT_ARGS_STR){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return NULL; }
  if(action & GMSH_SET)
    strcpy(v->FileName, val);
  return v->FileName;
}


char * opt_print_font(OPT_ARGS_STR){
  if(action & GMSH_SET) CTX.print.font = val;
  return CTX.print.font;
}


//******************* Numbers ***********************************


double opt_general_viewport0(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.viewport[0] = (int)val;
  return CTX.viewport[0];
}
double opt_general_viewport1(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.viewport[1] = (int)val;
  return CTX.viewport[1];
}
double opt_general_viewport2(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.viewport[2] = (int)val;
  return CTX.viewport[2];
}
double opt_general_viewport3(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.viewport[3] = (int)val;
  return CTX.viewport[3];
}
double opt_general_graphics_position0(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.gl_position[0] = (int)val;
  return CTX.gl_position[0];
}
double opt_general_graphics_position1(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.gl_position[1] = (int)val;
  return CTX.gl_position[1];
}
double opt_general_graphics_fontsize(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.gl_fontsize = (int)val;
  return CTX.gl_fontsize;
}
double opt_general_menu_position0(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.position[0] = (int)val;
  return CTX.position[0];
}
double opt_general_menu_position1(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.position[1] = (int)val;
  return CTX.position[1];
}
double opt_general_menu_fontsize(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.fontsize = (int)val;
  return CTX.fontsize;
}
double opt_general_center_windows(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.center_windows = (int)val;
  return CTX.center_windows;
}
double opt_general_rotation0(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.r[0] = val;
  return CTX.r[0];
}
double opt_general_rotation1(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.r[1] = val;
  return CTX.r[1];
}
double opt_general_rotation2(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.r[2] = val;
  return CTX.r[3];
}
double opt_general_quaternion0(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.quaternion[0] = val;
  return CTX.quaternion[0];
}
double opt_general_quaternion1(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.quaternion[1] = val;
  return CTX.quaternion[1];
}
double opt_general_quaternion2(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.quaternion[2] = val;
  return CTX.quaternion[2];
}
double opt_general_quaternion3(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.quaternion[3] = val;
  return CTX.quaternion[3];
}
double opt_general_translation0(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.t[0] = val;
  return CTX.t[0];
}
double opt_general_translation1(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.t[1] = val;
  return CTX.t[1];
}
double opt_general_translation2(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.t[2] = val;
  return CTX.t[2];
}
double opt_general_scale0(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.s[0] = val;
  return CTX.s[0];
}
double opt_general_scale1(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.s[1] = val;
  return CTX.s[1];
}
double opt_general_scale2(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.s[2] = val;
  return CTX.s[2];
}
double opt_general_shine(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.shine = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->gen_value[1]->value(CTX.shine);
#endif
  return CTX.shine;
}
double opt_general_verbosity(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.verbosity = (int)val;
  return CTX.verbosity;
}
double opt_general_terminal(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.terminal = (int)val;
  return CTX.terminal;
}
double opt_general_orthographic(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.ortho = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI)){
    WID->gen_butt[6]->value(CTX.ortho);
    WID->gen_butt[7]->value(!CTX.ortho);
  }
#endif
  return CTX.ortho;
}
double opt_general_fast_redraw(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.fast = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->gen_butt[2]->value(CTX.fast);
#endif
  return CTX.fast;
}
double opt_general_axes(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.axes = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->gen_butt[0]->value(CTX.axes);
#endif
  return CTX.axes;
}
double opt_general_small_axes(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.small_axes = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->gen_butt[1]->value(CTX.small_axes);
#endif
  return CTX.small_axes;
}
double opt_general_display_lists(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.display_lists = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->gen_butt[3]->value(CTX.display_lists);
#endif
  return CTX.display_lists;
}
double opt_general_alpha_blending(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.alpha = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->gen_butt[4]->value(CTX.alpha);
#endif
  return CTX.alpha;
}
double opt_general_color_scheme(OPT_ARGS_NUM){
  if(action & GMSH_SET){
    CTX.color_scheme = (int)val;
    if(CTX.color_scheme>2) CTX.color_scheme=0;
    Init_Colors(0);
  }
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->gen_value[0]->value(CTX.color_scheme);
#endif
  return CTX.color_scheme;
}
double opt_general_trackball(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.useTrackball = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->gen_butt[5]->value(CTX.useTrackball);
#endif
  return CTX.useTrackball;
}
double opt_general_zoom_factor(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.zoom_factor = val;
  return CTX.zoom_factor;
}
double opt_general_clip0(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip[0] = (int)val;
  return CTX.clip[0];
}
double opt_general_clip0a(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[0][0] = val;
  return CTX.clip_plane[0][0];
}
double opt_general_clip0b(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[0][1] = val;
  return CTX.clip_plane[0][1];
}
double opt_general_clip0c(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[0][2] = val;
  return CTX.clip_plane[0][2];
}
double opt_general_clip0d(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[0][3] = val;
  return CTX.clip_plane[0][3];
}
double opt_general_clip1(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip[1] = (int)val;
  return CTX.clip[1];
}
double opt_general_clip1a(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[1][0] = val;
  return CTX.clip_plane[1][0];
}
double opt_general_clip1b(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[1][1] = val;
  return CTX.clip_plane[1][1];
}
double opt_general_clip1c(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[1][2] = val;
  return CTX.clip_plane[1][2];
}
double opt_general_clip1d(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[1][3] = val;
  return CTX.clip_plane[1][3];
}
double opt_general_clip2(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip[2] = (int)val;
  return CTX.clip[2];
}
double opt_general_clip2a(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[2][0] = val;
  return CTX.clip_plane[2][0];
}
double opt_general_clip2b(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[2][1] = val;
  return CTX.clip_plane[2][1];
}
double opt_general_clip2c(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[2][2] = val;
  return CTX.clip_plane[2][2];
}
double opt_general_clip2d(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[2][3] = val;
  return CTX.clip_plane[2][3];
}
double opt_general_clip3(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip[3] = (int)val;
  return CTX.clip[3];
}
double opt_general_clip3a(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[3][0] = val;
  return CTX.clip_plane[3][0];
}
double opt_general_clip3b(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[3][1] = val;
  return CTX.clip_plane[3][1];
}
double opt_general_clip3c(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[3][2] = val;
  return CTX.clip_plane[3][2];
}
double opt_general_clip3d(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[3][3] = val;
  return CTX.clip_plane[3][3];
}
double opt_general_clip4(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip[4] = (int)val;
  return CTX.clip[4];
}
double opt_general_clip4a(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[4][0] = val;
  return CTX.clip_plane[4][0];
}
double opt_general_clip4b(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[4][1] = val;
  return CTX.clip_plane[4][1];
}
double opt_general_clip4c(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[4][2] = val;
  return CTX.clip_plane[4][2];
}
double opt_general_clip4d(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[4][3] = val;
  return CTX.clip_plane[4][3];
}
double opt_general_clip5(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip[5] = (int)val;
  return CTX.clip[5];
}
double opt_general_clip5a(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[5][0] = val;
  return CTX.clip_plane[5][0];
}
double opt_general_clip5b(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[5][1] = val;
  return CTX.clip_plane[5][1];
}
double opt_general_clip5c(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[5][2] = val;
  return CTX.clip_plane[5][2];
}
double opt_general_clip5d(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.clip_plane[5][3] = val;
  return CTX.clip_plane[5][3];
}
double opt_general_light0(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light[0] = (int)val;
  return CTX.light[0];
}
double opt_general_light00(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light_position[0][0] = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->gen_value[2]->value(CTX.light_position[0][0]);
#endif
  return CTX.light_position[0][0];
}
double opt_general_light01(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light_position[0][1] = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->gen_value[3]->value(CTX.light_position[0][1]);
#endif
  return CTX.light_position[0][1];
}
double opt_general_light02(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light_position[0][2] = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->gen_value[4]->value(CTX.light_position[0][2]);
#endif
  return CTX.light_position[0][2];
}
double opt_general_light1(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light[1] = (int)val;
  return CTX.light[1];
}
double opt_general_light10(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light_position[1][0] = val;
  return CTX.light_position[1][0];
}
double opt_general_light11(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light_position[1][1] = val;
  return CTX.light_position[1][1];
}
double opt_general_light12(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light_position[1][2] = val;
  return CTX.light_position[1][2];
}
double opt_general_light2(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light[2] = (int)val;
  return CTX.light[2];
}
double opt_general_light20(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light_position[2][0] = val;
  return CTX.light_position[2][0];
}
double opt_general_light21(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light_position[2][1] = val;
  return CTX.light_position[2][1];
}
double opt_general_light22(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light_position[2][2] = val;
  return CTX.light_position[2][2];
}
double opt_general_light3(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light[3] = (int)val;
  return CTX.light[3];
}
double opt_general_light30(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light_position[3][0] = val;
  return CTX.light_position[3][0];
}
double opt_general_light31(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light_position[3][1] = val;
  return CTX.light_position[3][1];
}
double opt_general_light32(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light_position[3][2] = val;
  return CTX.light_position[3][2];
}
double opt_general_light4(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light[4] = (int)val;
  return CTX.light[4];
}
double opt_general_light40(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light_position[4][0] = val;
  return CTX.light_position[4][0];
}
double opt_general_light41(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light_position[4][1] = val;
  return CTX.light_position[4][1];
}
double opt_general_light42(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light_position[4][2] = val;
  return CTX.light_position[4][2];
}
double opt_general_light5(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light[5] = (int)val;
  return CTX.light[5];
}
double opt_general_light50(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light_position[5][0] = val;
  return CTX.light_position[5][0];
}
double opt_general_light51(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light_position[5][1] = val;
  return CTX.light_position[5][1];
}
double opt_general_light52(OPT_ARGS_NUM){
  if(action & GMSH_SET) CTX.light_position[5][2] = val;
  return CTX.light_position[5][2];
}



double opt_geometry_normals(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.geom.normals = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->geo_value[0]->value(CTX.geom.normals);
#endif
  return CTX.geom.normals;
}
double opt_geometry_tangents(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.geom.tangents = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->geo_value[1]->value(CTX.geom.tangents);
#endif
  return CTX.geom.tangents;
}
double opt_geometry_points(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.geom.points = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->geo_butt[0]->value(CTX.geom.points);
#endif
  return CTX.geom.points;
}
double opt_geometry_lines(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.geom.lines = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->geo_butt[1]->value(CTX.geom.lines);
#endif
  return CTX.geom.lines;
}
double opt_geometry_surfaces(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.geom.surfaces = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->geo_butt[2]->value(CTX.geom.surfaces);
#endif
  return CTX.geom.surfaces;
}
double opt_geometry_volumes(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.geom.volumes = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->geo_butt[3]->value(CTX.geom.volumes);
#endif
  return CTX.geom.volumes;
}
double opt_geometry_points_num(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.geom.points_num = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->geo_butt[4]->value(CTX.geom.points_num);
#endif
  return CTX.geom.points_num;
}
double opt_geometry_lines_num(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.geom.lines_num = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->geo_butt[5]->value(CTX.geom.lines_num);
#endif
  return CTX.geom.lines_num;
}
double opt_geometry_surfaces_num(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.geom.surfaces_num = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->geo_butt[6]->value(CTX.geom.surfaces_num);
#endif
  return CTX.geom.surfaces_num;
}
double opt_geometry_volumes_num(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.geom.volumes_num = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->geo_butt[7]->value(CTX.geom.volumes_num);
#endif
  return CTX.geom.volumes_num;
}
double opt_geometry_hidden(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.geom.hidden = (int)val;
  return CTX.geom.hidden;
}
double opt_geometry_shade(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.geom.shade = (int)val;
  return CTX.geom.shade;
}
double opt_geometry_highlight(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.geom.highlight = (int)val;
  return CTX.geom.highlight;
}
double opt_geometry_old_circle(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.geom.old_circle = (int)val;
  return CTX.geom.old_circle;
}
double opt_geometry_scaling_factor(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.geom.scaling_factor = (int)val;
  return CTX.geom.scaling_factor;
}


double opt_mesh_quality(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.quality = val;
  return CTX.mesh.quality;
}
double opt_mesh_normals(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.normals = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_value[5]->value(CTX.mesh.normals);
#endif
  return CTX.mesh.normals;
}
double opt_mesh_tangents(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.tangents = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_value[1]->value(CTX.mesh.tangents);
#endif
  return CTX.mesh.tangents;
}
double opt_mesh_explode(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.explode = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_value[6]->value(CTX.mesh.explode);
#endif
  return CTX.mesh.explode;
}
double opt_mesh_scaling_factor(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.scaling_factor = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_value[1]->value(CTX.mesh.scaling_factor);
#endif
  return CTX.mesh.scaling_factor;
}
double opt_mesh_lc_factor(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.lc_factor = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_value[2]->value(CTX.mesh.lc_factor);
#endif
  return CTX.mesh.lc_factor;
}
double opt_mesh_rand_factor(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.rand_factor = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_value[3]->value(CTX.mesh.rand_factor);
#endif
  return CTX.mesh.rand_factor;
}
double opt_mesh_limit_gamma(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.limit_gamma = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_value[4]->value(CTX.mesh.limit_gamma);
#endif
  return CTX.mesh.limit_gamma;
}
double opt_mesh_limit_eta(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.limit_eta = val;
  return CTX.mesh.limit_eta;
}
double opt_mesh_limit_rho(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.limit_rho = val;
  return CTX.mesh.limit_rho;
}
double opt_mesh_points(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.points = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_butt[3]->value(CTX.mesh.points);
#endif
  return CTX.mesh.points;
}
double opt_mesh_lines(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.lines = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_butt[4]->value(CTX.mesh.lines);
#endif
  return CTX.mesh.lines;
}
double opt_mesh_surfaces(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.surfaces = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_butt[5]->value(CTX.mesh.surfaces);
#endif
  return CTX.mesh.surfaces;
}
double opt_mesh_volumes(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.volumes = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_butt[6]->value(CTX.mesh.volumes);
#endif
  return CTX.mesh.volumes;
}
double opt_mesh_points_num(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.points_num = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_butt[7]->value(CTX.mesh.points_num);
#endif
  return CTX.mesh.points_num;
}
double opt_mesh_lines_num(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.lines_num = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_butt[8]->value(CTX.mesh.lines_num);
#endif
  return CTX.mesh.lines_num;
}
double opt_mesh_surfaces_num(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.surfaces_num = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_butt[9]->value(CTX.mesh.surfaces_num);
#endif
  return CTX.mesh.surfaces_num;
}
double opt_mesh_volumes_num(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.volumes_num = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_butt[10]->value(CTX.mesh.volumes_num);
#endif
  return CTX.mesh.volumes_num;
}
double opt_mesh_hidden(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.hidden = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_butt[11]->value(!CTX.mesh.hidden);
#endif
  return CTX.mesh.hidden;
}
double opt_mesh_shade(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.shade = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_butt[13]->value(CTX.mesh.shade);
#endif
  return CTX.mesh.shade;
}
double opt_mesh_format(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.format = (int)val;
  return CTX.mesh.format;
}
double opt_mesh_nb_smoothing(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.nb_smoothing = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_value[0]->value(CTX.mesh.nb_smoothing);
#endif
  return CTX.mesh.nb_smoothing;
}
double opt_mesh_algo(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.algo = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_butt[2]->value(CTX.mesh.algo==DELAUNAY_NEWALGO);
#endif
  return CTX.mesh.algo;
}
double opt_mesh_point_insertion(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.point_insertion = (int)val;
  return CTX.mesh.point_insertion;
}
double opt_mesh_speed_max(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.speed_max = (int)val;
  return CTX.mesh.speed_max;
}
double opt_mesh_min_circ_points(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.min_circ_points = (int)val;
  return CTX.mesh.min_circ_points;
}
double opt_mesh_degree(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.degree = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_butt[0]->value(CTX.mesh.degree==2);
#endif
  return CTX.mesh.degree;
}
double opt_mesh_dual(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.dual = (int)val;
  return CTX.mesh.dual;
}
double opt_mesh_interactive(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.interactive = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->mesh_butt[1]->value(CTX.mesh.interactive);
#endif
  return CTX.mesh.interactive;
}
double opt_mesh_use_cut_plane(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.use_cut_plane = (int)val;
  return CTX.mesh.use_cut_plane;
}
double opt_mesh_cut_planea(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.cut_planea = val;
  return CTX.mesh.cut_planea;
}
double opt_mesh_cut_planeb(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.cut_planeb = val;
  return CTX.mesh.cut_planeb;
}
double opt_mesh_cut_planec(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.cut_planec = val;
  return CTX.mesh.cut_planec;
}
double opt_mesh_cut_planed(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.mesh.cut_planed = val;
  return CTX.mesh.cut_planed;
}



double opt_post_scales(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.post.scales = (int)val;
  return CTX.post.scales;
}
double opt_post_link(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.post.link = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI)){
    WID->post_butt[0]->value(CTX.post.link==0);
    WID->post_butt[1]->value(CTX.post.link==1);
    WID->post_butt[2]->value(CTX.post.link==2);
  }
#endif
  return CTX.post.link;
}
double opt_post_smooth(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.post.smooth = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->post_butt[3]->value(CTX.post.smooth);
#endif
  return CTX.post.smooth;
}
double opt_post_anim_delay(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.post.anim_delay = (val>=0.)? val : 0. ;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI))
    WID->post_value[0]->value(CTX.post.anim_delay);
#endif
  return CTX.post.anim_delay;
}
double opt_post_nb_views(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.post.nb_views = (int)val;
  return CTX.post.nb_views;
}



double opt_view_nb_timestep(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->NbTimeStep = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number))
    WID->view_value[9]->maximum(v->NbTimeStep-1);
#endif
  return v->NbTimeStep;
}
double opt_view_timestep(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->TimeStep = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number))
    WID->view_value[9]->value(v->TimeStep);
#endif
  return v->TimeStep;
}
double opt_view_min(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->Min = val;
  return v->Min;
}
double opt_view_max(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->Max = val;
  return v->Max;
}
double opt_view_custom_min(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->CustomMin = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number)){
    WID->view_value[0]->value(v->CustomMin);
  }
#endif
  return v->CustomMin;
}
double opt_view_custom_max(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->CustomMax = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number))
    WID->view_value[1]->value(v->CustomMax);
#endif
  return v->CustomMax;
}
double opt_view_offset0(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->Offset[0] = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number))
    WID->view_value[3]->value(v->Offset[0]);
#endif
  return v->Offset[0];
}
double opt_view_offset1(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->Offset[1] = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number))
    WID->view_value[4]->value(v->Offset[1]);
#endif
  return v->Offset[1];
}
double opt_view_offset2(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->Offset[2] = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number))
    WID->view_value[5]->value(v->Offset[2]);
#endif
  return v->Offset[2];
}
double opt_view_raise0(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->Raise[0] = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number))
    WID->view_value[6]->value(v->Raise[0]);
#endif
  return v->Raise[0];
}
double opt_view_raise1(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->Raise[1] = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number))
    WID->view_value[7]->value(v->Raise[1]);
#endif
  return v->Raise[1];
}
double opt_view_raise2(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->Raise[2] = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number))
    WID->view_value[8]->value(v->Raise[2]);
#endif
  return v->Raise[2];
}
double opt_view_arrow_scale(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->ArrowScale = val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number))
    WID->view_value[10]->value(v->ArrowScale);
#endif
  return v->ArrowScale;
}
double opt_view_visible(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->Visible = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number))
    WID->m_toggle_butt[num]->value(v->Visible);
#endif
  return v->Visible;
}
double opt_view_intervals_type(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->IntervalsType = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number)){
    WID->view_butt[6]->value(v->IntervalsType==DRAW_POST_ISO);
    WID->view_butt[7]->value(v->IntervalsType==DRAW_POST_DISCRETE);
    WID->view_butt[8]->value(v->IntervalsType==DRAW_POST_CONTINUOUS);
    WID->view_butt[9]->value(v->IntervalsType==DRAW_POST_NUMERIC);
  }
#endif
  return v->IntervalsType;
}
double opt_view_nb_iso(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->NbIso = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number))
    WID->view_value[2]->value(v->NbIso);
#endif
  return v->NbIso;
}
double opt_view_light(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->Light = (int)val;
  return v->Light;
}
double opt_view_show_element(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->ShowElement = (int)val;
  return v->ShowElement;
}
double opt_view_show_time(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->ShowTime = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number))
    WID->view_butt[1]->value(v->ShowTime);
#endif
  return v->ShowTime;
}
double opt_view_show_scale(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->ShowScale = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number))
    WID->view_butt[0]->value(v->ShowScale);
#endif
  return v->ShowScale;
}
double opt_view_transparent_scale(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->TransparentScale = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number))
    WID->view_butt[2]->value(v->TransparentScale);
#endif
  return v->TransparentScale;
}
double opt_view_scale_type(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->ScaleType = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number)){
    WID->view_butt[4]->value(v->ScaleType==DRAW_POST_LINEAR);
    WID->view_butt[5]->value(v->ScaleType==DRAW_POST_LOGARITHMIC);
  }
#endif
  return v->ScaleType;
}
double opt_view_range_type(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->RangeType = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number))
    WID->view_butt[3]->value(v->RangeType==DRAW_POST_CUSTOM);
#endif
  return v->RangeType;
}
double opt_view_arrow_type(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->ArrowType = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number)){
    WID->view_butt[10]->value(v->ArrowType==DRAW_POST_SEGMENT);
    WID->view_butt[11]->value(v->ArrowType==DRAW_POST_ARROW);
    WID->view_butt[12]->value(v->ArrowType==DRAW_POST_CONE);
    WID->view_butt[13]->value(v->ArrowType==DRAW_POST_DISPLACEMENT);
  }
#endif
  return v->ArrowType;
}
double opt_view_arrow_location(OPT_ARGS_NUM){
  Post_View *v = (Post_View*)List_Pointer_Test(Post_ViewList, num);
  if(!v){ NOVIEW; return 0.; }
  if(action & GMSH_SET) 
    v->ArrowLocation = (int)val;
#ifdef _FLTK
  if(WID && (action & GMSH_GUI) && (num == WID->view_number)){
    WID->view_butt[14]->value(v->ArrowLocation==DRAW_POST_LOCATE_COG);
    WID->view_butt[15]->value(v->ArrowLocation==DRAW_POST_LOCATE_VERTEX);
  }
#endif
  return v->ArrowLocation;
}


double opt_print_format(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.print.format = (int)val;
  return CTX.print.format;
}
double opt_print_eps_quality(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.print.eps_quality = (int)val;
  return CTX.print.eps_quality;
}
double opt_print_jpeg_quality(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.print.jpeg_quality = (int)val;
  return CTX.print.jpeg_quality;
}
double opt_print_gif_dither(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.print.gif_dither = (int)val;
  return CTX.print.gif_dither;
}
double opt_print_gif_sort(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.print.gif_sort = (int)val;
  return CTX.print.gif_sort;
}
double opt_print_gif_interlace(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.print.gif_interlace = (int)val;
  return CTX.print.gif_interlace;
}
double opt_print_gif_transparent(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.print.gif_transparent = (int)val;
  return CTX.print.gif_transparent;
}
double opt_print_font_size(OPT_ARGS_NUM){
  if(action & GMSH_SET) 
    CTX.print.font_size = (int)val;
  return CTX.print.font_size;
}


//******************* Colors ***********************************


unsigned int opt_general_color_background(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.bg = val;
  return CTX.color.bg;
}
unsigned int opt_general_color_foreground(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.fg = val;
  return CTX.color.fg;
}
unsigned int opt_general_color_text(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.text = val;
  return CTX.color.text;
}
unsigned int opt_general_color_axes(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.axes = val;
  return CTX.color.axes;
}
unsigned int opt_general_color_small_axes(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.small_axes = val;
  return CTX.color.small_axes;
}
unsigned int opt_geometry_color_points(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.geom.point = val;
  return CTX.color.geom.point;
} 
unsigned int opt_geometry_color_lines(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.geom.line = val;
  return CTX.color.geom.line;
}
unsigned int opt_geometry_color_surfaces(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.geom.surface = val;
  return CTX.color.geom.surface;
}
unsigned int opt_geometry_color_volumes(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.geom.volume = val;
  return CTX.color.geom.volume;
}
unsigned int opt_geometry_color_points_select(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.geom.point_sel = val;
  return CTX.color.geom.point_sel;
}
unsigned int opt_geometry_color_lines_select(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.geom.line_sel = val;
  return CTX.color.geom.line_sel;
}
unsigned int opt_geometry_color_surfaces_select(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.geom.surface_sel = val;
  return CTX.color.geom.surface_sel;
}
unsigned int opt_geometry_color_volumes_select(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.geom.volume_sel = val;
  return CTX.color.geom.volume_sel;
}
unsigned int opt_geometry_color_points_highlight(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.geom.point_hlt = val;
  return CTX.color.geom.point_hlt;
}
unsigned int opt_geometry_color_lines_highlight(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.geom.line_hlt = val;
  return CTX.color.geom.line_hlt;
}
unsigned int opt_geometry_color_surfaces_highlight(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.geom.surface_hlt = val;
  return CTX.color.geom.surface_hlt;
}
unsigned int opt_geometry_color_volumes_highlight(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.geom.volume_hlt = val;
  return CTX.color.geom.volume_hlt;
}
unsigned int opt_geometry_color_tangents(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.geom.tangents = val;
  return CTX.color.geom.tangents;
}
unsigned int opt_geometry_color_normals(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.geom.normals = val;
  return CTX.color.geom.normals;
}
unsigned int opt_mesh_color_points(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.vertex = val;
  return CTX.color.mesh.vertex;
} 
unsigned int opt_mesh_color_points_supp(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.vertex_supp = val;
  return CTX.color.mesh.vertex_supp;
} 
unsigned int opt_mesh_color_lines(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.line = val;
  return CTX.color.mesh.line;
} 
unsigned int opt_mesh_color_triangles(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.triangle = val;
  return CTX.color.mesh.triangle;
}
unsigned int opt_mesh_color_quadrangles(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.quadrangle = val;
  return CTX.color.mesh.quadrangle;
}
unsigned int opt_mesh_color_tetrahedra(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.tetrahedron = val;
  return CTX.color.mesh.tetrahedron;
}
unsigned int opt_mesh_color_hexahedra(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.hexahedron = val;
  return CTX.color.mesh.hexahedron;
}
unsigned int opt_mesh_color_prisms(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.prism = val;
  return CTX.color.mesh.prism;
}
unsigned int opt_mesh_color_pyramid(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.pyramid = val;
  return CTX.color.mesh.pyramid;
}
unsigned int opt_mesh_color_tangents(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.tangents = val;
  return CTX.color.mesh.tangents;
}
unsigned int opt_mesh_color_normals(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.normals = val;
  return CTX.color.mesh.normals;
}
unsigned int opt_mesh_color_1(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.carousel[0] = val;
  return CTX.color.mesh.carousel[0];
}
unsigned int opt_mesh_color_2(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.carousel[1] = val;
  return CTX.color.mesh.carousel[1];
}
unsigned int opt_mesh_color_3(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.carousel[2] = val;
  return CTX.color.mesh.carousel[2];
}
unsigned int opt_mesh_color_4(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.carousel[3] = val;
  return CTX.color.mesh.carousel[3];
}
unsigned int opt_mesh_color_5(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.carousel[4] = val;
  return CTX.color.mesh.carousel[4];
}
unsigned int opt_mesh_color_6(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.carousel[5] = val;
  return CTX.color.mesh.carousel[5];
}
unsigned int opt_mesh_color_7(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.carousel[6] = val;
  return CTX.color.mesh.carousel[6];
}
unsigned int opt_mesh_color_8(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.carousel[7] = val;
  return CTX.color.mesh.carousel[7];
}
unsigned int opt_mesh_color_9(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.carousel[8] = val;
  return CTX.color.mesh.carousel[8];
}
unsigned int opt_mesh_color_10(OPT_ARGS_COL){
  if(action & GMSH_SET) 
    CTX.color.mesh.carousel[9] = val;
  return CTX.color.mesh.carousel[9];
}
