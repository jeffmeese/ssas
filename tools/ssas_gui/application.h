#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <memory>

class Project;

class Application
    : public QApplication
{
public:
  Application(int & argc, char ** argv);
  ~Application();

public:
  Project * project();
  const Project * project() const;

public:
  void newProject();
  void openProject(const QString & fileName);
  void saveProject(const QString & fileName) const;

private:
  std::unique_ptr<Project> mProject;
};

inline Project * Application::project()
{
  return mProject.get();
}

inline const Project * Application::project() const
{
  return mProject.get();
}

#endif // APPLICATION_H
