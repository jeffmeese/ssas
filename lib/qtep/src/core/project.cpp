#include "project.h"
#include "projectitem.h"

#include <QFile>
#include <QDebug>

class Project::Impl
{
  friend class Project;

public:
  Impl();

public:
  QString fileName() const;
  bool modified() const;
  QString name() const;
  void setModified(bool modified = true);
  void setName(const QString & name);

public:
  void addItem(std::unique_ptr<ProjectItem> item);
  ProjectItem * findItem(const QString & itemId);
  const ProjectItem * findItem(const QString & itemId) const;
  QList<ProjectItem*> findItems(const QString & name) const;
  ProjectItem * itemAt(std::size_t index);
  const ProjectItem * itemAt(std::size_t index) const;
  bool load(const QString & fileName);
  bool loadXml(QXmlStreamReader & reader);
  void newProject();
  bool removeItem(const QString & itemId);
  bool save(const QString & fileName);
  bool saveXml(QXmlStreamWriter & writer) const;
  std::size_t totalItems() const;

private:
  typedef std::unique_ptr<ProjectItem> ProjectItemPtr;

private:
  bool mModified;
  QString mFileName;
  QString mName;
  std::vector<ProjectItemPtr> mItems;
  Project * mProject;
};

Project::Project()
  : mImpl(new Impl)
{
  mImpl->mProject = this;
}

Project::~Project()
{

}

QString Project::fileName() const
{
  return mImpl->mFileName;
}

bool Project::modified() const
{
  return mImpl->mModified;
}

QString Project::name() const
{
  return mImpl->mName;
}

void Project::addItem(std::unique_ptr<ProjectItem> item)
{
  mImpl->addItem(std::move(item));
}

ProjectItem * Project::findItem(const QString & itemId)
{
  return mImpl->findItem(itemId);
}

const ProjectItem * Project::findItem(const QString & itemId) const
{
  return mImpl->findItem(itemId);
}

QList<ProjectItem*> Project::findItems(const QString & name) const
{
  return mImpl->findItems(name);
}

ProjectItem * Project::itemAt(std::size_t index)
{
  return mImpl->itemAt(index);
}

const ProjectItem * Project::itemAt(std::size_t index) const
{
  return mImpl->itemAt(index);
}

bool Project::load(const QString & fileName)
{
  return mImpl->load(fileName);
}

bool Project::loadXml(QXmlStreamReader & reader)
{
  return mImpl->loadXml(reader);
}

void Project::newProject()
{
  mImpl->newProject();
}

bool Project::removeItem(const QString & itemId)
{
  return mImpl->removeItem(itemId);
}

bool Project::save(const QString & fileName)
{
  return mImpl->save(fileName);
}

bool Project::saveXml(QXmlStreamWriter & writer) const
{
  return mImpl->saveXml(writer);
}

void Project::setModified(bool modified)
{
  mImpl->setModified(modified);
}

void Project::setName(const QString & name)
{
  mImpl->setName(name);
}

std::size_t Project::totalItems() const
{
  return mImpl->totalItems();
}

// Private Implementation
Project::Impl::Impl()
  : mModified(false)
  , mName("Project")
{
}

void Project::Impl::addItem(std::unique_ptr<ProjectItem> projectItem)
{
  projectItem->setProject(mProject);
  mItems.push_back(std::move(projectItem));
  emit mProject->itemAdded(mItems.back().get());
  setModified();
}

ProjectItem * Project::Impl::findItem(const QString & itemId)
{
  for (std::vector<ProjectItemPtr>::iterator itr = mItems.begin(); itr != mItems.end(); ++itr) {
    if (itr->get()->id() == itemId) {
      return itr->get();
    }
  }
  return nullptr;
}

const ProjectItem * Project::Impl::findItem(const QString & itemId) const
{
  for (std::vector<ProjectItemPtr>::const_iterator itr = mItems.begin(); itr != mItems.end(); ++itr) {
    if (itr->get()->id() == itemId) {
      return itr->get();
    }
  }
  return nullptr;
}

QList<ProjectItem*> Project::Impl::findItems(const QString & name) const
{
  QList<ProjectItem*> items;
  for (std::vector<ProjectItemPtr>::const_iterator itr = mItems.begin(); itr != mItems.end(); ++itr) {
    if (itr->get()->name() == name) {
      items.append(itr->get());
    }
  }
  return items;
}

ProjectItem * Project::Impl::itemAt(std::size_t index)
{
  return mItems.at(index).get();
}

const ProjectItem * Project::Impl::itemAt(std::size_t index) const
{
  return mItems.at(index).get();
}

bool Project::Impl::load(const QString & fileName)
{
  mFileName = QString();

  QFile file(fileName);
  if (!file.open(QFile::ReadOnly)) {
    return false;
  }

  QXmlStreamReader reader(&file);
  if (!loadXml(reader)) {
    return false;
  }

  mFileName = fileName;
  setModified(false);
  return true;
}

bool Project::Impl::loadXml(QXmlStreamReader & reader)
{
  return !reader.hasError();
}

void Project::Impl::newProject()
{
  mName = QString();
  mFileName = QString();
  mItems.clear();
  setModified(false);
}

bool Project::Impl::removeItem(const QString & itemId)
{
  for (std::vector<ProjectItemPtr>::iterator itr = mItems.begin(); itr != mItems.end(); ++itr) {
    if (itr->get()->id() == itemId) {
      emit mProject->itemAboutToBeRemoved(itr->get());
      mItems.erase(itr);
      emit mProject->itemRemoved();
      setModified();
      return true;
    }
  }
  return false;
}

bool Project::Impl::save(const QString & fileName)
{
  mFileName = QString();

  QFile file(fileName);
  if (!file.open(QFile::WriteOnly)) {
    return false;
  }

  QXmlStreamWriter writer(&file);
  writer.setAutoFormatting(true);
  writer.setAutoFormattingIndent(2);
  writer.writeStartDocument();
  if (!saveXml(writer)) {
    return false;
  }
  writer.writeEndDocument();

  mFileName = fileName;
  setModified(false);
  return true;
}

bool Project::Impl::saveXml(QXmlStreamWriter & writer) const
{
  writer.writeStartElement("Project");
  for (std::size_t i = 0; i < mItems.size(); i++) {
    ProjectItem * item = mItems.at(i).get();
    item->saveXml(writer);
  }
  writer.writeEndElement();
  return !writer.hasError();
}

void Project::Impl::setModified(bool value)
{
  mModified = value;
  emit mProject->modified(value);
}

void Project::Impl::setName(const QString & name)
{
  mName = name;
  emit mProject->nameChanged(name);
  setModified();
}

std::size_t Project::Impl::totalItems() const
{
  return mItems.size();
}
