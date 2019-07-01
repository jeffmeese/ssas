#ifndef ELEMENT_H
#define ELEMENT_H

#include "ssas.h"

#include <QVector>

class SSAS_LIB_DECL Element
{
public:
  virtual ~Element();

public:
  int edge(int index) const;
  int node(int index) const;
  void setEdge(int index, int value);
  void setNode(int index, int value);
  int totalEdges() const;
  int totalNodes() const;

public:
  void edgeNodes(int index, int & node1, int & node2) const;

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
