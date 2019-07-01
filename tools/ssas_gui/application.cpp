#include "application.h"

#include "project.h"

Application::Application(int & argc, char ** argv)
  : QApplication(argc, argv)
{
  newProject();
}

Application::~Application()
{

}

void Application::newProject()
{
  mProject.reset(new Project);
}

void Application::openProject(const QString & fileName)
{
  mProject->load(fileName);
}

void Application::saveProject(const QString & fileName) const
{
  mProject->save(fileName);
}
