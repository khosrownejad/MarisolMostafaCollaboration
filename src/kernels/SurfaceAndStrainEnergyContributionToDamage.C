#include "SurfaceAndStrainEnergyContributionToDamage.h"

template<>
InputParameters validParams<SurfaceAndStrainEnergyContributionToDamage>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Contribution from the gradient term ");
  params.addRequiredParam<Real>("Gc", "fracture energy Gc ");
  params.addRequiredParam<Real>("l0", "fracture lengthscale l0");
  return params;
}

SurfaceAndStrainEnergyContributionToDamage::SurfaceAndStrainEnergyContributionToDamage(const InputParameters & parameters) :
    Kernel(parameters),
    _Gc(getParam<Real>("Gc")),
    _l0(getParam<Real>("l0")),
    _elasticityTensor(getMaterialPropertyByName<RankFourTensor>("elasticity_tensor")),
    _elasticStrain(getMaterialPropertyByName<RankTwoTensor>("total_strain"))
{
}

Real
SurfaceAndStrainEnergyContributionToDamage::computeQpResidual()
{
  Real strainEnergyDensity = 0.5*(_elasticStrain[_qp].doubleContraction(_elasticityTensor[_qp]*_elasticStrain[_qp]));

  Real residual = 0;
  residual += ((_Gc/_l0 + 2*strainEnergyDensity)* _u[_qp] - 2*strainEnergyDensity) * _test[_i][_qp] ;

  return residual;
}

Real
SurfaceAndStrainEnergyContributionToDamage::computeQpJacobian()
{
  return 0.0;
}

Real
SurfaceAndStrainEnergyContributionToDamage::computeQpOffDiagJacobian(unsigned int jvar)
{
  return 0.0;
}
