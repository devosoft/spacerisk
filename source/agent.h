
#pragma once

#include "tools/vector.h"

// TODO: if this is header only, nuke the following & fix the fallout
class Planet;

class Agent {


protected:
  /// vector of pointers to planets owned by this agent
  emp::set<Planet *> planets;
};
