#ifndef TREATMENT_H
#define TREATMENT_H

#include "ssas.h"
#include "projectitem.h"

class SSAS_LIB_DECL Treatment
    : public ProjectItem
{
public:
  Treatment();
  Treatment(const QString & name);
  Treatment(const QString & id, const QString & name);

protected:
  bool loadAttributes(QXmlStreamReader & reader) override;
  bool saveAttributes(QXmlStreamWriter & writer) const override;
};

#endif // TREATMENT_H
