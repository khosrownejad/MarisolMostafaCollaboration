#include "StressDivergenceTensorsWithDamage.h"
#include "MooseMesh.h"

// Based on http://solidmechanics.org/Text/Chapter8_5/Chapter8_5.php

template<>
InputParameters validParams<StressDivergenceTensorsWithDamage>()
{
  InputParameters params = validParams<StressDivergenceTensors>();
  params.addClassDescription("Stress divergence with coupling to concentration");
  params.addRequiredCoupledVar("damage", "damage variable");
	params.addRequiredParam<Real>("residualStiffness", "residual stiffness when damage is 1");
  return params;
}

StressDivergenceTensorsWithDamage::StressDivergenceTensorsWithDamage(const InputParameters & parameters) :
    StressDivergenceTensors(parameters),
    _damage(coupledValue("damage")),
		_residualStiffness(getParam<Real>("residualStiffness"))
{
}

Real
StressDivergenceTensorsWithDamage::computeQpResidual()
{
  return ((1-_damage[_qp])*(1-_damage[_qp])+ _residualStiffness)*StressDivergenceTensors::computeQpResidual();
}

Real
StressDivergenceTensorsWithDamage::computeQpJacobian()
{
  return StressDivergenceTensors::computeQpJacobian();
}

void
StressDivergenceTensorsWithDamage::computeJacobian()
{
	StressDivergenceTensors::computeJacobian();
}

void
StressDivergenceTensorsWithDamage::computeOffDiagJacobian(unsigned int jvar)
{
	StressDivergenceTensors::computeOffDiagJacobian(jvar);
}

Real
StressDivergenceTensorsWithDamage::computeQpOffDiagJacobian(unsigned int jvar)
{
		return StressDivergenceTensors::computeQpOffDiagJacobian(jvar);

}
