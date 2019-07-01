#ifndef SURFACE_H
#define SURFACE_H

#include "ssas.h"
#include "projectitem.h"

#include <list>
#include <map>

class Edge;
class Element;
class Node;

class Surface
    : public ProjectItem
{
public:
  SSAS_LIB_DECL Surface();
  SSAS_LIB_DECL Surface(const QString & name);
  SSAS_LIB_DECL Surface(const QString & id, const QString & name);

public:
  SSAS_LIB_DECL void addElement(std::unique_ptr<Element> element);
  SSAS_LIB_DECL void addNode(std::unique_ptr<Node> node);
  SSAS_LIB_DECL Edge * edge(std::size_t index);
  SSAS_LIB_DECL const Edge * edge(std::size_t index) const;
  SSAS_LIB_DECL Element * element(std::size_t index);
  SSAS_LIB_DECL const Element * element(std::size_t index) const;
  SSAS_LIB_DECL Node * node(std::size_t index);
  SSAS_LIB_DECL const Node * node(std::size_t index) const;
  SSAS_LIB_DECL void readGeomFile(const QString & fileName);
  SSAS_LIB_DECL std::size_t totalEdges() const;
  SSAS_LIB_DECL std::size_t totalElements() const;
  SSAS_LIB_DECL std::size_t totalNodes() const;

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
