#ifndef EDGE_H
#define EDGE_H

#include "ssas.h"

#include <vector>

class SSAS_LIB_DECL Edge
{
public:
  Edge(int id);

public:
  int node1() const;
  int node2() const;
  void setNode1(int value);
  void setNode2(int value);

private:
  int mId;
  int mNode1;
  int mNode2;
};

#endif // EDGE_H
