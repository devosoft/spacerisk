
#pragma once

#include "base/vector.h"
#include <set> 

// TODO: if this is header only, nuke the following & fix the fallout
class Planet;

class Agent {


protected:
  /// vector of pointers to planets owned by this agent
  std::set<Planet *> planets;
};
