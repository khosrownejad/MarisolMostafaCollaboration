#include "DamageIrreversibilityPenalty.h"
#include "MooseMesh.h"

template<>
InputParameters validParams<DamageIrreversibilityPenalty>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Contribution from the irreversibility penalty term ");
	params.addRequiredParam<Real>("PenaltyEta", "Coefficient of the penalty function");
	params.addRequiredParam<int>("PenaltyN", "Exponent of the penalty function");
  return params;
}

DamageIrreversibilityPenalty::DamageIrreversibilityPenalty(const InputParameters & parameters) :
    Kernel(parameters),
		_penalty_eta(getParam<Real>("PenaltyEta")),
		_penalty_n(getParam<int>("PenaltyN"))
{
}
Real
DamageIrreversibilityPenalty::computeQpResidual()
{
  Real f_udot = 0.0;
  f_udot = (_u_dot[_qp]<0.0) ? -_u_dot[_qp] : 0.0;

  return _penalty_eta/_dt/_penalty_n * std::pow(f_udot,_penalty_n) * _test[_i][_qp];
}

Real
DamageIrreversibilityPenalty::computeQpJacobian()
{
  return 0.0;

}

Real
DamageIrreversibilityPenalty::computeQpOffDiagJacobian(unsigned int jvar)
{
  return 0.0;
}
