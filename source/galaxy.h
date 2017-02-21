


#pragma once

#include "tools/vector.h"
#include "tools/Random.h"
#include "planet.h"
#include "agent.h"


/** Class to represent a galaxy, with planets and other goodies
 *
 *  does NOT handle drawing anything--that's for the interface classes in the driver files
 */
class Galaxy {

public:
  
  /** Construct a galaxy 
   * 
   * \param numPlanets the number of planets to construct this galaxy with
   * \param width, in magic
   * \param height, also in magic
   */
  Galaxy (uint64_t numPlanets, double width, double height) {
    for (size_t i = 0; i < numPlanets; i++) {
      // note, 5 & 20 are arbitrary
      planets.emplace_back(random.GetDouble(width), random.GetDouble(height), random.GetDouble(5, 20));
    }
  };


protected:
  /// random thingy
  emp::Random random;
  /// vector of planet objects in this galaxy
  emp::vector<Planet> planets;
  /// vector of agent objects for this galaxy ( slash universe, thanks spjps)
  emp::vector<Agent> agents;  
};
