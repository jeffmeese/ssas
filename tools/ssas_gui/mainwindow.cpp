#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "application.h"
#include "project.h"
#include "node.h"
#include "surface.h"
#include "triangle.h"
#include "viewmodel.h"
#include "workspacemodel.h"

#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(Application & application, QWidget *parent)
  : QMainWindow(parent)
  , mUi(new Ui::MainWindow)
  , mView(new View)
  , mWorkspaceModel(new WorkspaceModel)
  , mApplication(application)
{
  mUi->setupUi(this);
  initActions();
  newProject();
  resetModels();
  updateWindowTitle();
}

MainWindow::~MainWindow()
{
}

void MainWindow::handleAddSurface()
{
  QString fileName("D:\\work\\gdais\\projects\\models\\carlos\\ddart\\ddart-small\\model\\ddart.geom");

  Project * project = mApplication.project();
  std::unique_ptr<Surface> surface(new Surface);
  surface->setName("ddart");
  surface->readGeomFile(fileName);
  project->addItem(std::move(surface));
  project->setModified();
  updateWindowTitle();
}

void MainWindow::handleAddTreatment()
{
  Project * project = mApplication.project();
  project->setModified();
  updateWindowTitle();
}

void MainWindow::handleHelpContents()
{

}

void MainWindow::handleHelpIndex()
{

}

void MainWindow::handleHelpAbout()
{

}

void MainWindow::handleHelpAboutQt()
{
  QApplication::aboutQt();
}

void MainWindow::handleExit()
{
  if (!promptSave())
    return;

  QApplication::quit();
}

void MainWindow::handleNewProject()
{
  if (!promptSave())
    return;

  newProject();
  resetModels();
  updateWindowTitle();
}

void MainWindow::handleOpenProject()
{
  if (!promptSave())
    return;

  QString caption("Choose file name");
  QString filter("SSAS files (*.ssas);;Xml files(*.xml)");
  QString dirName(QDir::currentPath());
  QString fileName = QFileDialog::getOpenFileName(this, caption, dirName, filter);
  if (fileName.isEmpty())
    return;

  openProject(fileName);
  resetModels();
  updateWindowTitle();
}

void MainWindow::handleSaveProject()
{
  QString fileName(mApplication.project()->fileName());
  if (fileName.isEmpty()) {
    handleSaveProjectAs();
    updateWindowTitle();
    return;
  }

  mApplication.saveProject(fileName);
  updateWindowTitle();
}

void MainWindow::handleSaveProjectAs()
{
  QString fileName = promptSaveFileName();
  if (fileName.isEmpty())
    return;

  saveProject(fileName);
  updateWindowTitle();
}

void MainWindow::initActions()
{
  // Program actions
  connect(mUi->actionExit, SIGNAL(triggered()), SLOT(handleExit()));
  connect(mUi->actionNew_Project, SIGNAL(triggered()), SLOT(handleNewProject()));
  connect(mUi->actionOpen_Project, SIGNAL(triggered()), SLOT(handleOpenProject()));
  connect(mUi->actionSave_Project, SIGNAL(triggered()), SLOT(handleSaveProject()));
  connect(mUi->actionSave_Project_As, SIGNAL(triggered()), SLOT(handleSaveProjectAs()));

  // Project actions
  connect(mUi->actionAdd_Surface, SIGNAL(triggered()), SLOT(handleAddSurface()));
  connect(mUi->actionAdd_Treatment, SIGNAL(triggered()), SLOT(handleAddTreatment()));

  // Help actions
  connect(mUi->actionContents, SIGNAL(triggered()), SLOT(handleHelpContents()));
  connect(mUi->actionIndex, SIGNAL(triggered()), SLOT(handleHelpIndex()));
  connect(mUi->actionAbout, SIGNAL(triggered()), SLOT(handleHelpAbout()));
  connect(mUi->actionAbout_Qt, SIGNAL(triggered()), SLOT(handleHelpAboutQt()));
}

void MainWindow::newProject()
{
  mApplication.newProject();
}

void MainWindow::openProject(const QString &fileName)
{
  mApplication.openProject(fileName);
}

bool MainWindow::promptSave()
{
  Project * project = mApplication.project();
  if (!project->modified())
    return true;

  QString title("Save Project?");
  QString message("Do you want to save the current project?");
  QMessageBox::StandardButtons buttons = QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel;
  QMessageBox::StandardButton response = QMessageBox::question(this, title, message, buttons);

  if (response == QMessageBox::No)
    return true;

  if (response == QMessageBox::Cancel)
    return false;

  if (response == QMessageBox::Yes) {
    QString fileName;
    if (project->fileName().isEmpty()) {
      fileName = promptSaveFileName();
      if (fileName.isEmpty()) {
        return false;
      }
    }
    saveProject(fileName);
  }

  return true;
}

QString MainWindow::promptSaveFileName()
{
  QString caption("Choose file name");
  QString filter("SSAS files (*.ssas);;Xml files(*.xml)");
  QString dirName(QDir::currentPath());
  QString fileName = QFileDialog::getSaveFileName(this, caption, dirName, filter);
  return fileName;
}

void MainWindow::resetModels()
{
  mWorkspaceModel.reset(new WorkspaceModel);
  mWorkspaceModel->setProject(mApplication.project());
  mUi->cWorkspaceView->setModel(mWorkspaceModel.get());

  mViewModel.reset(new ViewModel);
  mViewModel->setProject(mApplication.project());
  mUi->cModelView->setModel(mViewModel.get());
  mUi->cModelView->reset();

  mApplication.project()->setModified(false);
}

void MainWindow::saveProject(const QString &fileName)
{
  mApplication.saveProject(fileName);
}

void MainWindow::updateWindowTitle()
{
  QString windowTitle("SSAS");
  QString fileTitle("Untitled");
  QString fileName(mApplication.project()->fileName());
  if (!fileName.isEmpty()) {
    fileTitle = fileName;
  }

  windowTitle += " - " + fileTitle;
  if (mApplication.project()->modified()) {
    windowTitle += "*";
  }

  setWindowTitle(windowTitle);
}
