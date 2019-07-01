#include "treatment.h"

static const QString type("Treatment");

Treatment::Treatment()
  : ProjectItem(type)
{
}

Treatment::Treatment(const QString & name)
  : ProjectItem(type, name)
{
}

Treatment::Treatment(const QString & id, const QString & name)
  : ProjectItem(type, id, name)
{
}

bool Treatment::loadAttributes(QXmlStreamReader & reader)
{
  return !reader.hasError();
}

bool Treatment::saveAttributes(QXmlStreamWriter & writer) const
{
  return !writer.hasError();
}
