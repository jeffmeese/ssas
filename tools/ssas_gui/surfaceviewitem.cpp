#include "surfaceviewitem.h"

#include "edge.h"
#include "element.h"
#include "node.h"
#include "surface.h"
#include "view.h"

#include <vtkQuad.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkTriangle.h>

#include <QDebug>

SurfaceViewItem::SurfaceViewItem(Surface * surface)
  : mSurface(surface)
  , mActor(vtkActor::New())
  , mActorElements(vtkCellArray::New())
  , mElementMapper(vtkPolyDataMapper::New())
  , mElementPolyData(vtkPolyData::New())
  , mSurfaceColors(vtkUnsignedCharArray::New())
  , mSurfaceNodes(vtkPoints::New())
{
  createNodes();
  createElements();
}

void SurfaceViewItem::createElements()
{
	qDebug() << QObject::tr(__FUNCTION__);

  for (std::size_t i = 0; i < mSurface->totalElements(); i++) {
    auto element = mSurface->element(i+1);
    auto polygon = vtkSmartPointer<vtkPolygon>::New();
    polygon->GetPointIds()->SetNumberOfIds(element->totalNodes());
    for (int j = 0; j < element->totalNodes(); j++) {
      polygon->GetPointIds()->SetId(j, element->node(j+1)-1);
    }
    mActorElements->InsertNextCell(polygon);
  }
  mElementPolyData->SetPoints(mSurfaceNodes);
  mElementPolyData->SetPolys(mActorElements);
  mElementMapper->SetInputData(mElementPolyData);
  mActor->SetMapper(mElementMapper);
}

void SurfaceViewItem::createNodes()
{
	qDebug() << QObject::tr(__FUNCTION__);

  for (std::size_t i = 0; i < mSurface->totalNodes(); i++) {
    auto node = mSurface->node(i+1);
    double xPos = node->x();
    double yPos = node->y();
    double zPos = node->z();
    mSurfaceNodes->InsertNextPoint(xPos, yPos, zPos);
  }
}

void SurfaceViewItem::doDraw(View *view)
{
}

void SurfaceViewItem::doAttachToRenderer(vtkRenderer *renderer)
{
	renderer->AddActor(mActor);
}
