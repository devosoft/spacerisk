/** This file is part of something blah blag
 *  see LICENSE
 */

#pragma once

#include "geometry/Circle2D.h"
#include "agent.h"

// emp libary includes
#include "tools/vector.h"


class Planet {

public:
  /** x coord
   *  y coor
   *  \param radius, $(whatever fricken' unit galaxy is measured in)
   *
   */
  Planet(double x, double y, double r=10.0) : circ(x, y, r) {
   
  }

  /** Set the owner of this planet
   * 
   * \param agent pointer to the agent that will own this planet
   */
  void SetOwner(Agent * agent) { owner = agent;}

  const emp::Circle & GetCircle() const { return circ;}


protected:
  /// the circle for this planet
  emp::Circle circ; 
  /// the current population of this planet
  uint64_t population;
  /// pointer to the owner of this planet
  Agent * owner;
  /// vector of pointers to the neighbors of this planet
  emp::vector<Planet *> neighbors;

};
