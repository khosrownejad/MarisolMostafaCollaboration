#ifndef DAMAGE_GRADIENT_ENERGY_H
#define DAMAGE_GRADIENT_ENERGY_H

#include "Kernel.h"

class DamageGradientEnergy;

template<>
InputParameters validParams<DamageGradientEnergy>();

class DamageGradientEnergy : public Kernel
{
public:
  DamageGradientEnergy(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);
  const Real _Gc, _l0;
};
#endif
