#include "MarisolmostafacollaborationApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template<>
InputParameters validParams<MarisolmostafacollaborationApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_output_syntax") = false;

  return params;
}

MarisolmostafacollaborationApp::MarisolmostafacollaborationApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  MarisolmostafacollaborationApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  MarisolmostafacollaborationApp::associateSyntax(_syntax, _action_factory);
}

MarisolmostafacollaborationApp::~MarisolmostafacollaborationApp()
{
}

// External entry point for dynamic application loading
extern "C" void MarisolmostafacollaborationApp__registerApps() { MarisolmostafacollaborationApp::registerApps(); }
void
MarisolmostafacollaborationApp::registerApps()
{
  registerApp(MarisolmostafacollaborationApp);
}

// External entry point for dynamic object registration
extern "C" void MarisolmostafacollaborationApp__registerObjects(Factory & factory) { MarisolmostafacollaborationApp::registerObjects(factory); }
void
MarisolmostafacollaborationApp::registerObjects(Factory & factory)
{
}

// External entry point for dynamic syntax association
extern "C" void MarisolmostafacollaborationApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { MarisolmostafacollaborationApp::associateSyntax(syntax, action_factory); }
void
MarisolmostafacollaborationApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
