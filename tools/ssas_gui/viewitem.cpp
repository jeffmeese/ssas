#include "viewitem.h"

ViewItem::ViewItem()
{
}

void ViewItem::attachToRenderer(vtkRenderer *renderer)
{
  doAttachToRenderer(renderer);
}
