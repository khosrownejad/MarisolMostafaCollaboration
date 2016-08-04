#ifndef SURFACE_AND_STRAIN_ENERGY_CONTRIBUTION_TO_DAMAGE_H
#define SURFACE_AND_STRAIN_ENERGY_CONTRIBUTION_TO_DAMAGE_H

#include "Kernel.h"
#include "RankTwoTensor.h"
#include "RankFourTensor.h"

class SurfaceAndStrainEnergyContributionToDamage;

template<>
InputParameters validParams<SurfaceAndStrainEnergyContributionToDamage>();

class SurfaceAndStrainEnergyContributionToDamage : public Kernel
{
public:
  SurfaceAndStrainEnergyContributionToDamage(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const Real _Gc, _l0;
  const MaterialProperty<RankFourTensor> & _elasticityTensor;
  const MaterialProperty<RankTwoTensor> & _elasticStrain;

};
#endif
