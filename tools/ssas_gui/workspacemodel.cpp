#include "workspacemodel.h"

#include "project.h"
#include "surface.h"
#include "surfaceitem.h"

#include <QDebug>

WorkspaceModel::WorkspaceModel()
  : mProject(nullptr)
  , mModelItem(nullptr)
  , mGeometryItem(nullptr)
  , mRegionItem(nullptr)
  , mTreatmentItem(nullptr)
{
  createTopLevelItems();
}

void WorkspaceModel::createTopLevelItems()
{
  mModelItem = new QStandardItem("Model");
  mGeometryItem = new QStandardItem("Geometry");
  mRegionItem = new QStandardItem("Regions");
  mTreatmentItem = new QStandardItem("Treatments");

  invisibleRootItem()->appendRow(mModelItem);
  mModelItem->appendRow(mGeometryItem);
  mModelItem->appendRow(mRegionItem);
  mModelItem->appendRow(mTreatmentItem);
}

void WorkspaceModel::handleAddProjectItem(ProjectItem *projectItem)
{
  qDebug() << QObject::tr(__FUNCTION__);

  // TODO: Eventually replace this with a factory
  Surface * surface = dynamic_cast<Surface*>(projectItem);
  if (surface != nullptr) {
    SurfaceItem * surfaceItem = new SurfaceItem(surface);
    mGeometryItem->appendRow(surfaceItem);
  }
}

void WorkspaceModel::populateModel()
{
}

void WorkspaceModel::setProject(Project *project)
{
  mProject = project;

  removeRows(0, rowCount());
  createTopLevelItems();
  populateModel();

  if (mProject != nullptr) {
    connect(mProject, SIGNAL(itemAdded(ProjectItem*)), SLOT(handleAddProjectItem(ProjectItem*)));
  }
}


