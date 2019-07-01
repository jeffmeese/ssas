#include "view.h"

#include "viewitem.h"
#include "viewmodel.h"

#include <vtkCaptionActor2D.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkTextProperty.h>

#include <QDebug>

View::View(QWidget * parentWidget, Qt::WindowFlags flags)
  : QVTKOpenGLNativeWidget (parentWidget, flags)
  , mModel(nullptr)
  , mAxesActor(vtkAxesActor::New())
  , mRenderer(vtkRenderer::New())
  , mRubberBandZoom(vtkInteractorStyleRubberBandZoom::New())
  , mTrackballCamera(vtkInteractorStyleTrackballCamera::New())
{
  mRenderer->SetBackground(0.9, 0.9, 0.9);
  mTrackballCamera->SetDefaultRenderer(mRenderer);
  mRenderer->ResetCamera();

  GetRenderWindow()->AddRenderer(mRenderer);
  GetRenderWindow()->GetInteractor()->SetInteractorStyle(mTrackballCamera);
  buildAxes();
}

void View::buildAxes()
{
	mAxesActor->AxisLabelsOn();
	mAxesActor->SetShaftTypeToLine();
	mAxesActor->SetTipTypeToCone();
	mAxesActor->GetXAxisCaptionActor2D()->GetProperty()->SetColor(0.0,0.0,0.0);
	mAxesActor->GetYAxisCaptionActor2D()->GetProperty()->SetColor(0.0,0.0,0.0);
	mAxesActor->GetZAxisCaptionActor2D()->GetProperty()->SetColor(0.0,0.0,0.0);
	mAxesActor->GetXAxisCaptionActor2D()->GetCaptionTextProperty()->ShadowOff();
	mAxesActor->GetYAxisCaptionActor2D()->GetCaptionTextProperty()->ShadowOff();
	mAxesActor->GetZAxisCaptionActor2D()->GetCaptionTextProperty()->ShadowOff();
	mRenderer->AddActor(mAxesActor);
}

void View::paintGL()
{
  QVTKOpenGLNativeWidget::paintGL();

  mRenderer->GetRenderWindow()->Render();
}

void View::handleItemAdded(ViewItem *viewItem)
{
  viewItem->attachToRenderer(mRenderer);
  update();
}

void View::reset()
{
  mRenderer->ResetCamera();
  mRenderer->GetRenderWindow()->Render();
}

void View::setModel(ViewModel * viewModel)
{
  mModel = viewModel;
  if (viewModel != nullptr) {
    connect(viewModel, SIGNAL(itemAdded(ViewItem*)), SLOT(handleItemAdded(ViewItem*)));
  }
}
