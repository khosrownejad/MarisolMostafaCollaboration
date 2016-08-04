#include "DamageGradientEnergy.h"

template<>
InputParameters validParams<DamageGradientEnergy>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Contribution from the gradient term ");
	params.addRequiredParam<Real>("Gc", "fracture energy Gc ");
	params.addRequiredParam<Real>("l0", "fracture lengthscale l0");
  return params;
}

DamageGradientEnergy::DamageGradientEnergy(const InputParameters & parameters) :
    Kernel(parameters),
		_Gc(getParam<Real>("Gc")),
		_l0(getParam<Real>("l0"))
{
}

Real
DamageGradientEnergy::computeQpResidual()
{
  return -_Gc*_l0 * _grad_u[_qp] * _grad_test[_i][_qp];
}

Real
DamageGradientEnergy::computeQpJacobian()
{
  return -_Gc * _l0 * _grad_phi[_j][_qp] * _grad_test[_i][_qp];

}

Real
DamageGradientEnergy::computeQpOffDiagJacobian(unsigned int jvar)
{
  return 0.0;
}


