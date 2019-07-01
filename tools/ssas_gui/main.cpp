#include <iostream>

#include "application.h"
#include "mainwindow.h"

#include <QSurfaceFormat>
#include <QVTKOpenGLWidget.h>

int main(int argc, char ** argv)
{
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());

  Application application(argc, argv);
  MainWindow mainWindow(application, nullptr);
  mainWindow.show();

  return application.exec();
}
