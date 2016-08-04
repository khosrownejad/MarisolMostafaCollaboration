#ifndef STRESS_DIVERGENCE_TENSOR_WITH_DAMAGE_H
#define STRESS_DIVERGENCE_TENSOR_WITH_DAMAGE_H

#include "StressDivergenceTensors.h"

class StressDivergenceTensorsWithDamage : public StressDivergenceTensors
{
public:
  StressDivergenceTensorsWithDamage(const InputParameters & parameters);

protected:
	virtual Real computeQpResidual();
	virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  virtual void computeJacobian();
  virtual void computeOffDiagJacobian(unsigned int jvar);

  const VariableValue & _damage;
	const Real _residualStiffness;

};

#endif
