#include "triangle.h"

Triangle::Triangle(int id)
  : Element(id, 3, 3)
{
}

void Triangle::doEdgeNodes(int index, int & node1, int & node2) const
{
  if (index == 1) {
    node1 = 1;
    node2 = 2;
  }
  else if (index == 2) {
    node1 = 2;
    node2 = 3;
  }
  else if (index == 3) {
    node2 = 3;
    node1 = 1;
  }
}

