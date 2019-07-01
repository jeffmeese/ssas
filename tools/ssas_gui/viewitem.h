#ifndef VIEWITEM_H
#define VIEWITEM_H

#include <QString>
#include <QStandardItem>

#include <vtkRenderer.h>

class View;

class ViewItem
    : public QStandardItem
{
public:
  void attachToRenderer(vtkRenderer * renderer);

protected:
  ViewItem();

protected:
  virtual void doAttachToRenderer(vtkRenderer * renderer) = 0;
};

#endif // VIEWITEM_H
