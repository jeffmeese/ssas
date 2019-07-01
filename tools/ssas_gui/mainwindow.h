#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

class Application;
class View;
class WorkspaceModel;
class ViewModel;
namespace Ui {
  class MainWindow;
}

class MainWindow
    : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(Application & application, QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void handleAddSurface();
  void handleAddTreatment();
  void handleHelpContents();
  void handleHelpIndex();
  void handleHelpAbout();
  void handleHelpAboutQt();
  void handleExit();
  void handleNewProject();
  void handleOpenProject();
  void handleSaveProject();
  void handleSaveProjectAs();

private:
  bool promptSave();
  QString promptSaveFileName();
  void initActions();
  void newProject();
  void openProject(const QString & fileName);
  void resetModels();
  void saveProject(const QString & fileName);
  void updateWindowTitle();

private:
  std::unique_ptr<Ui::MainWindow> mUi;
  std::unique_ptr<View> mView;
  std::unique_ptr<WorkspaceModel> mWorkspaceModel;
  std::unique_ptr<ViewModel> mViewModel;
  Application & mApplication;
};

#endif // MAINWINDOW_H
