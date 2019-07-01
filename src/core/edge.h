#ifndef EDGE_H
#define EDGE_H

#include "ssas.h"

#include <vector>

class Edge
{
public:
  SSAS_LIB_DECL Edge(int id);

public:
  SSAS_LIB_DECL int node1() const;
  SSAS_LIB_DECL int node2() const;
  SSAS_LIB_DECL void setNode1(int value);
  SSAS_LIB_DECL void setNode2(int value);

private:
  int mId;
  int mNode1;
  int mNode2;
};

#endif // EDGE_H
