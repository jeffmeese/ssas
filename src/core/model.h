#ifndef MODEL_H
#define MODEL_H

#include "ssas.h"

#include "projectitem.h"

#include <memory>
#include <vector>

class Surface;
class Treatment;

class Model
    : public ProjectItem
{
  Q_OBJECT

public:
  SSAS_LIB_DECL Model();
  SSAS_LIB_DECL virtual ~Model() override;

public:
  SSAS_LIB_DECL void addSurface(std::unique_ptr<Surface> surface);
  SSAS_LIB_DECL void addTreatment(std::unique_ptr<Treatment> treatment);

signals:
  SSAS_LIB_DECL void surfaceAdded(Surface * surface);
  SSAS_LIB_DECL void treatmentAdded(Treatment * treatment);

protected:
  bool loadAttributes(QXmlStreamReader & reader) override;
  bool saveAttributes(QXmlStreamWriter & writer) const override;

private:
  typedef std::unique_ptr<Surface> SurfacePtr;
  typedef std::unique_ptr<Treatment> TreatmentPtr;

private:
  std::vector<SurfacePtr> mSurfaces;
  std::vector<TreatmentPtr> mTreatments;
};

#endif // MODEL_H
