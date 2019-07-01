#include "node.h"

Node::Node(int id)
  : mId(id)
{
  mX = mY = mZ = 0.0;
}

int Node::id() const
{
  return mId;
}

double Node::x() const
{
  return mX;
}

double Node::y() const
{
  return mY;
}

double Node::z() const
{
  return mZ;
}

void Node::set(double x, double y, double z)
{
  mX = x;
  mY = y;
  mZ = z;
}

void Node::setX(double value)
{
  mX = value;
}

void Node::setY(double value)
{
  mY = value;
}

void Node::setZ(double value)
{
  mZ = value;
}
