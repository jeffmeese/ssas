#ifndef ELEMENT_H
#define ELEMENT_H

#include "ssas.h"

#include <QVector>

class Element
{
public:
  virtual ~Element();

public:
  SSAS_LIB_DECL int edge(int index) const;
  SSAS_LIB_DECL int node(int index) const;
  SSAS_LIB_DECL void setEdge(int index, int value);
  SSAS_LIB_DECL void setNode(int index, int value);
  SSAS_LIB_DECL int totalEdges() const;
  SSAS_LIB_DECL int totalNodes() const;

public:
  SSAS_LIB_DECL void edgeNodes(int index, int & node1, int & node2) const;

protected:
  virtual void doEdgeNodes(int index, int & node1, int & node2) const = 0;

protected:
  Element(int id, int nodes, int edges);

private:
  int mId;
  QVector<int> mEdges;
  QVector<int> mNodes;
};

#endif // ELEMENT_H
