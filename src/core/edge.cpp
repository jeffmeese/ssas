#include "edge.h"

Edge::Edge(int id)
  : mId(id)
{
  mNode1 = mNode2 = -1;
}

int Edge::node1() const
{
  return mNode1;
}

int Edge::node2() const
{
  return mNode2;
}

void Edge::setNode1(int value)
{
  mNode1 = value;
}

void Edge::setNode2(int value)
{
  mNode2 = value;
}
