#include "surface.h"

#include "edge.h"
#include "node.h"
#include "triangle.h"

#include <sstream>

static const QString type("Surface");

Surface::Surface()
  : ProjectItem(type)
{
}

Surface::Surface(const QString & name)
  : ProjectItem(type, name)
{
}

Surface::Surface(const QString & id, const QString & name)
  : ProjectItem(type, id, name)
{
}

void Surface::addElement(std::unique_ptr<Element> element)
{
  createEdges(element.get());
  mElements.push_back(std::move(element));
}

void Surface::addNode(std::unique_ptr<Node> node)
{
  mNodes.push_back(std::move(node));
}

void Surface::createEdges(Element *element)
{
  for (int i = 0; i < element->totalEdges(); i++) {
    int index1, index2;
    element->edgeNodes(i+1, index1, index2);

    int node1 = element->node(index1);
    int node2 = element->node(index2);
    int edgeNumber = -1;

    EdgeNodeList & list1 = mEdgeTable[node1];
    for (EdgeNodeList::iterator itr = list1.begin(); itr != list1.end(); ++itr) {
      if (itr->first == node2) {
        edgeNumber = itr->second;
      }
    }

    EdgeNodeList & list2 = mEdgeTable[node2];
    for (EdgeNodeList::iterator itr = list2.begin(); itr != list2.end(); ++itr) {
      if (itr->first == node1) {
        edgeNumber = itr->second;
      }
    }

    if (edgeNumber < 0) {
      edgeNumber = static_cast<int>(mEdges.size()+1);

      std::unique_ptr<Edge> edge(new Edge(edgeNumber));
      edge->setNode1(node1);
      edge->setNode2(node2);
      mEdgeTable[node1].push_back(NodePair(node2, edgeNumber));
      mEdgeTable[node2].push_back(NodePair(node1, edgeNumber));
      mEdges.push_back(std::move(edge));
    }

    element->setEdge(i+1, edgeNumber);
  }
}

Edge * Surface::edge(std::size_t index)
{
  return mEdges[index-1].get();
}

const Edge * Surface::edge(std::size_t index) const
{
  return mEdges[index-1].get();
}

Element * Surface::element(std::size_t index)
{
  return mElements[index-1].get();
}

const Element * Surface::element(std::size_t index) const
{
  return mElements[index-1].get();
}

bool Surface::loadAttributes(QXmlStreamReader & reader)
{
  return !reader.hasError();
}

Node * Surface::node(std::size_t index)
{
  return mNodes[index-1].get();
}

const Node * Surface::node(std::size_t index) const
{
  return mNodes[index-1].get();
}

void Surface::readGeomFile(const QString &fileName)
{
  mNodes.clear();
  mElements.clear();
  mEdges.clear();
  mEdgeTable.clear();

  QFile file(fileName);
  if (!file.open(QFile::ReadOnly)) {
    std::ostringstream oss;
    oss << "Could not open file " << fileName.toStdString() << "\n";
    throw std::invalid_argument(oss.str());
  }

  QTextStream inputStream(&file);
  QString inputLine = inputStream.readLine();
  QStringList lineData = inputLine.split(" ");
  int totalNodes = lineData.at(0).toInt();
  for (int i = 0; i < totalNodes; i++) {
    QString inputLine = inputStream.readLine();
    QStringList lineData = inputLine.split(" ");
    double x = lineData.at(0).toDouble();
    double y = lineData.at(1).toDouble();
    double z = lineData.at(2).toDouble();

    std::unique_ptr<Node> node(new Node(i+1));
    node->set(x, y, z);
    addNode(std::move(node));
  }

  inputLine = inputStream.readLine();
  lineData = inputLine.split(" ");
  int totalElements = lineData.at(0).toInt();
  for (int i = 0; i < totalElements; i++) {
    QString inputLine = inputStream.readLine();
    QStringList lineData = inputLine.split(" ");
    int node1 = lineData.at(0).toInt();
    int node2 = lineData.at(1).toInt();
    int node3 = lineData.at(2).toInt();

    std::unique_ptr<Triangle> triangle(new Triangle(i+1));
    triangle->setNode(1, node1);
    triangle->setNode(2, node2);
    triangle->setNode(3, node3);

    addElement(std::move(triangle));
  }
}

bool Surface::saveAttributes(QXmlStreamWriter & writer) const
{
  return !writer.hasError();
}

std::size_t Surface::totalEdges() const
{
  return mEdges.size();
}

std::size_t Surface::totalElements() const
{
  return mElements.size();
}

std::size_t Surface::totalNodes() const
{
  return mNodes.size();
}
