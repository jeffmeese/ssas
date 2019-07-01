#ifndef NODE_H
#define NODE_H

#include "ssas.h"

class Node
{
public:
  SSAS_LIB_DECL Node(int id);

public:
  SSAS_LIB_DECL int id() const;
  SSAS_LIB_DECL double x() const;
  SSAS_LIB_DECL double y() const;
  SSAS_LIB_DECL double z() const;
  SSAS_LIB_DECL void set(double x, double y, double z);
  SSAS_LIB_DECL void setX(double value);
  SSAS_LIB_DECL void setY(double value);
  SSAS_LIB_DECL void setZ(double value);

private:
  int mId;
  double mX;
  double mY;
  double mZ;
};

#endif // NODE_H
