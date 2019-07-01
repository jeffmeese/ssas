#include "viewmodel.h"

#include "project.h"
#include "surface.h"
#include "surfaceviewitem.h"

ViewModel::ViewModel()
{
}

void ViewModel::handleAddProjectItem(ProjectItem *projectItem)
{
  Surface * surface = dynamic_cast<Surface*>(projectItem);
  SurfaceViewItem * viewItem = new SurfaceViewItem(surface);
  invisibleRootItem()->appendRow(viewItem);
  emit itemAdded(viewItem);
}

void ViewModel::setProject(Project *project)
{
  mProject = project;
  if (mProject != nullptr) {
    connect(mProject, SIGNAL(itemAdded(ProjectItem*)), SLOT(handleAddProjectItem(ProjectItem*)));
  }
}
