#ifndef DAMAGE_IRREVESIBILITY_PENALTY_H
#define DAMAGE_IRREVESIBILITY_PENALTY_H

#include "Kernel.h"

class DamageIrreversibilityPenalty;

template<>
InputParameters validParams<DamageIrreversibilityPenalty>();

class DamageIrreversibilityPenalty : public Kernel
{
public:
  DamageIrreversibilityPenalty(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);
  const Real _penalty_eta;
  const int _penalty_n;
};
#endif
