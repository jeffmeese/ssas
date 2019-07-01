#ifndef MODEL_H
#define MODEL_H

#include "ssas.h"

#include "projectitem.h"

#include <memory>
#include <vector>

class Surface;
class Treatment;

class SSAS_LIB_DECL Model
    : public ProjectItem
{
  Q_OBJECT

public:
  Model();
  virtual ~Model() override;

public:
  void addSurface(std::unique_ptr<Surface> surface);
  void addTreatment(std::unique_ptr<Treatment> treatment);

signals:
  void surfaceAdded(Surface * surface);
  void treatmentAdded(Treatment * treatment);

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
