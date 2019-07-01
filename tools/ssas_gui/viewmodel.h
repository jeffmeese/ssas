#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QStandardItemModel>

class Project;
class ProjectItem;
class ViewItem;

class ViewModel
    : public QStandardItemModel
{
  Q_OBJECT

public:
  ViewModel();

public:
  void setProject(Project * project);

signals:
  void itemAdded(ViewItem * viewItem);

private slots:
  void handleAddProjectItem(ProjectItem * projectItem);

private:
  Project * mProject;
};

#endif // VIEWMODEL_H
