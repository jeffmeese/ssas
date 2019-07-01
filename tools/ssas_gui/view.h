#ifndef VIEW_H
#define VIEW_H

#include <QVTKOpenGLNativeWidget.h>

#include <vtkAxesActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkInteractorStyleRubberBandZoom.h>
#include <vtkInteractorStyleTrackballCamera.h>

class ViewModel;
class ViewItem;

class View
    : public QVTKOpenGLNativeWidget
{
  Q_OBJECT

public:
  View(QWidget * parentWidget = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

public:
  void reset();
  void setModel(ViewModel * viewModel);

protected:
  void paintGL() override;

private slots:
  void handleItemAdded(ViewItem * viewItem);

private:
  void buildAxes();

private:
  ViewModel * mModel;
  vtkSmartPointer<vtkAxesActor> mAxesActor;
  vtkSmartPointer<vtkRenderer> mRenderer;
  vtkSmartPointer<vtkRenderWindow> mRenderWindow;
  vtkSmartPointer<vtkInteractorStyleRubberBandZoom> mRubberBandZoom;
  vtkSmartPointer<vtkInteractorStyleTrackballCamera> mTrackballCamera;
};

#endif // VIEW_H
