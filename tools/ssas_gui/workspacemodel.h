#ifndef WORKSPACEMODEL_H
#define WORKSPACEMODEL_H

#include <QStandardItemModel>

class Project;
class ProjectItem;

class WorkspaceModel
    : public QStandardItemModel
{
  Q_OBJECT

public:
  WorkspaceModel();

public:
  Project * project();
  void setProject(Project * project);

private slots:
  void handleAddProjectItem(ProjectItem * projectItem);

private:
  void createTopLevelItems();
  void populateModel();

private:
  Project * mProject;
  QStandardItem * mModelItem;
  QStandardItem * mGeometryItem;
  QStandardItem * mRegionItem;
  QStandardItem * mTreatmentItem;
};

inline Project * WorkspaceModel::project()
{
  return mProject;
}

#endif // WORKSPACEMODEL_H
