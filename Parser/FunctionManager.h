#ifndef _FUNCTION_MANAGER_H_
#define _FUNCTION_MANAGER_H_

class mystack;
class mymap;
#include <stdio.h>
/*
  Singleton, one function manager for 
  all parsers. 
*/

class FunctionManager
{
    mymap *functions;
    mystack *calls;  
    FunctionManager ();
    static FunctionManager *instance;
  public :
    static FunctionManager* Instance();
    bool enterFunction (char *name, FILE **f) const;
    bool createFunction  (char *name, FILE *f);
    bool leaveFunction (FILE **f);
};

#endif
