#include <tchar.h>

#include "habra_line.h"

int _tmain(int argc, _TCHAR* argv[])
{
  // Enable extended debug for HabraLine library
	debugger::EnableExtendedDebug();
  
  HabraLine line(HabraPoint(0,0), HabraPoint(2000, 2000));

  HabraLine* pLine = new HabraLine(HabraPoint(0,0), HabraPoint(2000, 2000));

  // do something with line
  // ...

  line.modify(HabraPoint(-5000,-5000), HabraPoint(-1000, -1000));

  return 0;
}

