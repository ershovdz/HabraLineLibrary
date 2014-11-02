#include "vs_debug_helper.h"

static bool isVisualDebuggerEnabled = false;

DLL_FUNC (bool) debugger::ExtendedDebugEnabled()
{
  return isVisualDebuggerEnabled;
}

DLL_FUNC (void) debugger::EnableExtendedDebug()
{
  isVisualDebuggerEnabled = true;
}

DLL_FUNC (void) debugger::DisableExtendedDebug()
{
  isVisualDebuggerEnabled = false;
}