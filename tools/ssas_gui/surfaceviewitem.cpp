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
  , mSurfaceColors(vtkUnsignedCharArray::New())
  , mSurfaceNodes(vtkPoints::New())
  , mElementPolyData(vtkPolyData::New())
  , mElementMapper(vtkPolyDataMapper::New())
  , mActorElements(vtkCellArray::New())
{
  createNodes();
  createElements();
}

vtkCell * SurfaceViewItem::createCell(Element * surfaceElement)
{
	qDebug() << QObject::tr(__FUNCTION__);

	vtkCell * elementCell = nullptr;
	if (surfaceElement->totalNodes() == 3)
			elementCell = vtkTriangle::New();
	else if (surfaceElement->totalNodes() == 4)
			elementCell = vtkQuad::New();

	if (elementCell == nullptr)
		return nullptr;

	for (int i = 0; i < surfaceElement->totalNodes(); i++)
		elementCell->GetPointIds()->SetId(i, surfaceElement->edge(i+1)-1);

	return elementCell;
}

void SurfaceViewItem::createElements()
{
	qDebug() << QObject::tr(__FUNCTION__);

	mActorElements->Delete();
	mActorElements = mActorElements->New();
	mSurfaceColors->Delete();
	mSurfaceColors = mSurfaceColors->New();

	mSurfaceColors->SetNumberOfComponents(3);
	mSurfaceColors->SetName("Colors");

	// Set up the surface actor
	for (std::size_t i = 0; i < mSurface->totalElements(); i++) {
		Element * element = mSurface->element(i+1);

		//Color color(mAssociatedSurface->GetColor());
		vtkCell * elementCell = createCell(element);
		if (elementCell) {
			vtkIdType idElement = mActorElements->InsertNextCell(elementCell);
			mElementIds.insert(std::make_pair(element, idElement));
			mElementList.push_back(std::make_pair(idElement, element));
			//mSurfaceColors->InsertNextTuple3(color.Red()*255, color.Green()*255, color.Blue()*255);
		}
	}

	// Set up the elements poly data
	mElementPolyData->SetPolys(mActorElements);
	mElementPolyData->GetCellData()->SetScalars(mSurfaceColors);

	//mElementMapper->SetInput(mElementPolyData);
	mElementMapper->SetResolveCoincidentTopologyToPolygonOffset();

	mActor->SetMapper(mElementMapper);
}

void SurfaceViewItem::createNodes()
{
	qDebug() << QObject::tr(__FUNCTION__);

	mSurfaceNodes->Delete();
	mSurfaceNodes = mSurfaceNodes->New();

	for (std::size_t i = 0; i < mSurface->totalNodes(); i++) {
		Node * node = mSurface->node(i+1);

		double xPos = node->x();
		double yPos = node->y();
		double zPos = node->z();

		// Apply scaling
		//xPos *= node->ScalingX();
		//yPos *= node->ScalingY();
		//zPos *= node->ScalingZ();

		// Apply translation
		//xPos += node->TranslationX();
		//yPos += node->TranslationY();
		//zPos += node->TranslationZ();

		mSurfaceNodes->InsertNextPoint(xPos, yPos, zPos);
	}

	mElementPolyData->SetPoints(mSurfaceNodes);
}

void SurfaceViewItem::doDraw(View *view)
{
}

void SurfaceViewItem::doAttachToRenderer(vtkRenderer *renderer)
{
	renderer->AddActor(mActor);
}
