#ifndef _GMSH_DEFINES_H_
#define _GMSH_DEFINES_H_

// Copyright (C) 1997-2008 C. Geuzaine, J.-F. Remacle
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 // USA.
// 
// Please report all bugs and problems to <gmsh@geuz.org>.

// IO file formats
#define FORMAT_MSH           1
#define FORMAT_UNV           2
#define FORMAT_GREF          3
#define FORMAT_XPM           4
#define FORMAT_PS            5
#define FORMAT_BMP           6
#define FORMAT_GIF           7
#define FORMAT_GEO           8
#define FORMAT_JPEG          9
#define FORMAT_AUTO          10
#define FORMAT_PPM           11
#define FORMAT_YUV           12
#define FORMAT_DMG           13
#define FORMAT_SMS           14
#define FORMAT_OPT           15
#define FORMAT_VTK           16
#define FORMAT_TEX           18
#define FORMAT_VRML          19
#define FORMAT_EPS           20
#define FORMAT_PNG           22
#define FORMAT_PDF           24
#define FORMAT_POS           26
#define FORMAT_STL           27
#define FORMAT_P3D           28
#define FORMAT_SVG           29
#define FORMAT_MESH          30
#define FORMAT_BDF           31
#define FORMAT_CGNS          32
#define FORMAT_MED           33

// Element types in .msh file format
#define MSH_LIN_2  1
#define MSH_TRI_3  2
#define MSH_QUA_4  3
#define MSH_TET_4  4
#define MSH_HEX_8  5
#define MSH_PRI_6  6
#define MSH_PYR_5  7
#define MSH_LIN_3  8
#define MSH_TRI_6  9
#define MSH_QUA_9  10
#define MSH_TET_10 11
#define MSH_HEX_27 12
#define MSH_PRI_18 13
#define MSH_PYR_14 14
#define MSH_PNT    15
#define MSH_QUA_8  16
#define MSH_HEX_20 17
#define MSH_PRI_15 18
#define MSH_PYR_13 19
#define MSH_TRI_9  20
#define MSH_TRI_10 21
#define MSH_TRI_12 22
#define MSH_TRI_15 23
#define MSH_TRI_15I 24
#define MSH_TRI_21 25
#define MSH_LIN_4  26
#define MSH_LIN_5  27
#define MSH_LIN_6  28

// Geometric entities
#define ENT_NONE     0
#define ENT_POINT    (1<<0)
#define ENT_LINE     (1<<1)
#define ENT_SURFACE  (1<<2)
#define ENT_VOLUME   (1<<3)
#define ENT_ALL      (ENT_POINT | ENT_LINE | ENT_SURFACE | ENT_VOLUME)

// 2D mesh algorithms
#define ALGO_2D_MESHADAPT_DELAUNAY  1
#define ALGO_2D_ANISOTROPIC         2 // unused
#define ALGO_2D_TRIANGLE            3 // unused
#define ALGO_2D_MESHADAPT           4
#define ALGO_2D_DELAUNAY            5

// 3D mesh algorithms
#define ALGO_3D_TETGEN_DELAUNAY    1
#define ALGO_3D_NETGEN             4
#define ALGO_3D_TETGEN             5 // unused

#define TRANSFINI 1
#define LIBRE     2

#endif
