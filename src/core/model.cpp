#include "model.h"

#include "element.h"
#include "node.h"
#include "surface.h"
#include "treatment.h"
#include "triangle.h"

Model::Model()
  : ProjectItem("Model")
{
}

Model::~Model()
{
}

void Model::addSurface(std::unique_ptr<Surface> surface)
{
  mSurfaces.push_back(std::move(surface));
  emit surfaceAdded(mSurfaces.back().get());
}

void Model::addTreatment(std::unique_ptr<Treatment> treatment)
{
  mTreatments.push_back(std::move(treatment));
  emit treatmentAdded(mTreatments.back().get());
}

bool Model::loadAttributes(QXmlStreamReader & reader)
{
  return !reader.hasError();
}

bool Model::saveAttributes(QXmlStreamWriter & writer) const
{
  return !writer.hasError();
}
