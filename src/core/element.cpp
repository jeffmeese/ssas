#include "element.h"

Element::Element(int id, int nodes, int edges)
  : mId(id)
{
  mEdges.resize(edges);
  mNodes.resize(nodes);
  for (int i = 0; i < edges; i++) {
    mEdges[i] = -1;
  }
  for (int i = 0; i < nodes; i++) {
    mNodes[i] = -1;
  }
}

Element::~Element()
{

}

int Element::edge(int index) const
{
  return mEdges[index-1];
}

void Element::edgeNodes(int index, int &node1, int &node2) const
{
  doEdgeNodes(index, node1, node2);
}

int Element::node(int index) const
{
  return mNodes[index-1];
}

void Element::setEdge(int index, int value)
{
  mEdges[index-1] = value;
}

void Element::setNode(int index, int value)
{
  mNodes[index-1] = value;
}

int Element::totalEdges() const
{
  return mEdges.size();
}

int Element::totalNodes() const
{
  return mNodes.size();
}

