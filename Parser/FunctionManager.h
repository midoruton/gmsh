// Gmsh - Copyright (C) 1997-2013 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to the public mailing list <gmsh@geuz.org>.

#ifndef _FUNCTION_MANAGER_H_
#define _FUNCTION_MANAGER_H_

class mystack;
class mymap;

#include <string>
#include <stdio.h>

// Singleton, one function manager for all parsers. 

class FunctionManager
{
  mymap *functions;
  mystack *calls;  
  FunctionManager ();
  static FunctionManager *instance;
 public :
  static FunctionManager* Instance();
  int createFunction(char *name, FILE *f, std::string &filename, int lineno);
  int enterFunction(char *name, FILE **f, std::string &filename, int &lineno) const;
  int leaveFunction(FILE **f, std::string &filename, int &lineno);
};

#endif
