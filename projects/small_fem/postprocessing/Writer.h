#ifndef _WRITER_H_
#define _WRITER_H_

#include "fullMatrix.h"
#include <string>
#include <vector>

class Writer{
 protected:
  bool hasValue;
  bool isScalar;

  std::vector<double>*              nodalScalarValue;
  std::vector<fullVector<double> >* nodalVectorValue;

 public:
  Writer(void);

  virtual ~Writer(void);

  virtual void write(const std::string name) const = 0;

  void setValues(std::vector<double>& value);
  void setValues(std::vector<fullVector<double> >& value);
};

#endif