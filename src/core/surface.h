#ifndef SURFACE_H
#define SURFACE_H

#include "ssas.h"
#include "projectitem.h"

#include <list>
#include <map>

class Edge;
class Element;
class Node;

class SSAS_LIB_DECL Surface
    : public ProjectItem
{
public:
  Surface();
  Surface(const QString & name);
  Surface(const QString & id, const QString & name);

public:
  void addElement(std::unique_ptr<Element> element);
  void addNode(std::unique_ptr<Node> node);
  Edge * edge(std::size_t index);
  const Edge * edge(std::size_t index) const;
  Element * element(std::size_t index);
  const Element * element(std::size_t index) const;
  Node * node(std::size_t index);
  const Node * node(std::size_t index) const;
  void readGeomFile(const QString & fileName);
  std::size_t totalEdges() const;
  std::size_t totalElements() const;
  std::size_t totalNodes() const;

protected:
  bool loadAttributes(QXmlStreamReader & reader) override;
  bool saveAttributes(QXmlStreamWriter & writer) const override;

private:
  void createEdges(Element * element);

private:
  typedef std::unique_ptr<Node> NodePtr;
  typedef std::unique_ptr<Edge> EdgePtr;
  typedef std::unique_ptr<Element> ElementPtr;
  typedef std::pair<int, int> NodePair;
  typedef std::list<NodePair> EdgeNodeList;
  typedef std::map<int, EdgeNodeList> EdgeTable;

private:
  std::vector<EdgePtr> mEdges;
  std::vector<ElementPtr> mElements;
  std::vector<NodePtr> mNodes;
  EdgeTable mEdgeTable;
};

#endif // SURFACE_H
