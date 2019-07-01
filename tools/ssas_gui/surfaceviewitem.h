#ifndef SURFACEVIEWITEM_H
#define SURFACEVIEWITEM_H

#include "viewitem.h"

#include <list>
#include <map>

#include <vtkActor.h>
#include <vtkCell.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkPolyData.h>
#include <vtkPolygon.h>
#include <vtkPolyDataMapper.h>
#include <vtkPoints.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkUnsignedCharArray.h>

class Element;
class Surface;
class View;

class SurfaceViewItem
    : public ViewItem
{
public:
  SurfaceViewItem(Surface * surface);

protected:
  void doDraw(View * view);
  void doAttachToRenderer(vtkRenderer * renderer) override;

private:
  void createElements();
  void createNodes();

private:
	typedef std::pair<vtkIdType, Element*> ElementPair;
	typedef std::list<ElementPair> ElementList;

private:
  Surface * mSurface;
  vtkSmartPointer<vtkActor> mActor;
  vtkSmartPointer<vtkCellArray> mActorElements;
  vtkSmartPointer<vtkPolyDataMapper> mElementMapper;
  vtkSmartPointer<vtkPolyData> mElementPolyData;
  vtkSmartPointer<vtkUnsignedCharArray> mSurfaceColors;
  vtkSmartPointer<vtkPoints> mSurfaceNodes;
  ElementList mElementList;
  std::list<vtkCell*> mCellList;
  std::map<Element*, vtkIdType> mElementIds;
};

#endif // SURFACEVIEWITEM_H
