#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "ssas.h"
#include "element.h"

#include <vector>

class Triangle
    : public Element
{
public:
  SSAS_LIB_DECL Triangle(int id);

protected:
  void doEdgeNodes(int index, int & node1, int & node2) const override;
};

#endif // TRIANGLE_H
