#ifndef NODE_H
#define NODE_H

#include "ssas.h"

class SSAS_LIB_DECL Node
{
public:
  Node(int id);

public:
  int id() const;
  double x() const;
  double y() const;
  double z() const;
  void set(double x, double y, double z);
  void setX(double value);
  void setY(double value);
  void setZ(double value);

private:
  int mId;
  double mX;
  double mY;
  double mZ;
};

#endif // NODE_H
