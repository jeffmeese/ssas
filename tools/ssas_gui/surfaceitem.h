#ifndef SURFACEITEM_H
#define SURFACEITEM_H

#include "workspacemodelitem.h"

class Surface;

class SurfaceItem
    : public WorkspaceModelItem
{
public:
  SurfaceItem(Surface * surface);

private:
  Surface * mSurface;
};

#endif // SURFACEITEM_H
