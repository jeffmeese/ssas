#include "surfaceitem.h"

#include "surface.h"

SurfaceItem::SurfaceItem(Surface * surface)
  : mSurface(surface)
{
  setText(surface->name());
}
