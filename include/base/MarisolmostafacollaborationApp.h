#ifndef MARISOLMOSTAFACOLLABORATIONAPP_H
#define MARISOLMOSTAFACOLLABORATIONAPP_H

#include "MooseApp.h"

class MarisolmostafacollaborationApp;

template<>
InputParameters validParams<MarisolmostafacollaborationApp>();

class MarisolmostafacollaborationApp : public MooseApp
{
public:
  MarisolmostafacollaborationApp(InputParameters parameters);
  virtual ~MarisolmostafacollaborationApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* MARISOLMOSTAFACOLLABORATIONAPP_H */
