[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 80
  ny = 80
  xmin = 0
  xmax = 1
  ymin = 0
  ymax = 1
  elem_type = QUAD4
[]

[Variables]
  [./disp_x]
    order = FIRST
    family = LAGRANGE
    #initial_condition = 0
  [../]
  [./disp_y]
    order = FIRST
    family = LAGRANGE
    #initial_condition = 0
  [../]
  [./damage]
    order = FIRST
    family = LAGRANGE
    #initial_condition = 0
  [../]
[]

[ICs]
  [./dispXzero]
    variable = disp_x
    type = ConstantIC
    value = 0
  [../]
  [./dispXzero]
    variable = disp_y
    type = ConstantIC
    value = 0
  [../]
  [./damageICBoundingBox]
    variable = damage
    type = BoundingBoxIC
    x1 = 0.46
    y1 = 0.6
    x2 = 0.54
    y2 = 1.0
    inside = 1.0
    outside = 0.0
  [../]
[]


[Kernels]

 active = 'disp_x disp_y damageGradient damageSurfaceStrain'

# MECHANICAL EQUILIBRIUM
  [./disp_x]
  type = StressDivergenceTensorsWithDamage
  displacements = 'disp_x disp_y'
  variable = disp_x
  damage = damage
  residualStiffness = 0.1
  component = 0
  [../]
  [./disp_y]
  type = StressDivergenceTensorsWithDamage
  displacements = 'disp_x disp_y'
  variable = disp_y
  damage = damage
  residualStiffness = 0.1
  component = 1
  [../]

# DAMAGE
  [./damageGradient]
  type = DamageGradientEnergy
  variable = damage
  Gc = 5.0
  l0 = 0.1
  [../]
  [./damageSurfaceStrain]
  type = SurfaceAndStrainEnergyContributionToDamage
  variable = damage
  Gc = 5.0
  l0 = 0.1
  [../]
  [./damageIrrevPenalty]
  type = DamageIrreversibilityPenalty
  variable = damage
  PenaltyEta = 10.0
  PenaltyN = 2.0
  [../]

[]

[AuxVariables]

  #active = 'stress11 stress22'

  [./stress11]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./stress22]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./stress12]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]

  #active = 'matl_e11 matl_e22'

  [./matl_e11]
    type = RankTwoAux
    rank_two_tensor = stress
    index_i = 0
    index_j = 0
    variable = stress11
  [../]
  [./matl_e22]
    type = RankTwoAux
    rank_two_tensor = stress
    index_i = 1
    index_j = 1
    variable = stress22
  [../]
  [./matl_e12]
    type = RankTwoAux
    rank_two_tensor = stress
    index_i = 0
    index_j = 1
    variable = stress12
  [../]
[]

[Materials]

  [./elasticity_tensor]
    type = ComputeIsotropicElasticityTensor
    block = 0
    youngs_modulus = 20000.0
    poissons_ratio = 0.3
  [../]
  [./strain]
    type = ComputeSmallStrain
    block = 0
    displacements = 'disp_x disp_y'
  [../]
  [./stress]
    type = ComputeLinearElasticStress
    block = 0
  [../]

[]

[BCs]

  active = 'top_y bottom_y left_x right_x'

  [./top_y]
  type = DirichletBC
  variable = 'disp_y'
  boundary = 'top'
  value = 0
  [../]
  [./bottom_y]
  type = DirichletBC
  variable = 'disp_y'
  boundary = 'bottom'
  value = 0
  [../]
  [./left_x]
  type = DirichletBC
  variable = 'disp_x'
  boundary = 'left'
  value = 0
  [../]
  [./right_x]
  type = FunctionDirichletBC
  variable = 'disp_x'
  boundary = 'right'
  function = '0.001*t'
  [../]

[]

[Preconditioning]
  # active = ' '
  [./SMP]
    type = FDP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  scheme = explicit-euler

  solve_type = 'PJFNK'
  petsc_options_iname = '-pc_type -ksp_grmres_restart -sub_ksp_type -sub_pc_type -pc_asm_overlap'
  petsc_options_value = 'asm         101   preonly   lu      1'

  l_max_its = 30
  nl_max_its = 10
  l_tol = 1.0e-4
  nl_rel_tol = 1.0e-5
  #nl_abs_tol = 1.0e-6
  start_time = 0.0
  #num_steps = 20
  end_time = 0.4

  [./TimeStepper]
    #type = ConstantDT
    type = SolutionTimeAdaptiveDT
    dt = 0.01
  [../]
[]

[Outputs]
    file_base = elasticityWithDamage
  [./exodus]
    type = Exodus
    execute_on = 'initial timestep_end'
  [../]
  [./csv]
    type = CSV
    execute_on = 'timestep_end'
  [../]
  [./console]
    type = Console
    execute_on = 'linear nonlinear timestep_end'
  [../]
[]
