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
    population = 0;
    population_cap = r*r;
  }

  /** Set the owner of this planet
   * 
   * \param agent pointer to the agent that will own this planet
   */
  void SetOwner(Agent * agent) { owner = agent;}

  /** Get the circle corresponding to this planet
   *
   * \return a circle object */
  const emp::Circle & GetCircle() const { return circ;}

  /** Set the location and radius of this circle
   *
   * \param x the new x location for this planet
   * \param y the new y location for this planet
   * \param r the new radius value for this planet
   *
   */
  void Reset(double x, double y, double r){
      circ.Set(x,y,r);
      population_cap = r*r;
  }

  /** Set the population of this planet
   *  Asserts that the population is less than the cap
   *
   *  This should probably be changed to just assume you meant the cap
   *  Though, "errors should never pass silently" and that
   *
   */
  void SetPopulation (double pop) { 
    emp_assert(pop <= population_cap);

    population = pop;
  }

  /** Grow the population of this planet
   *
   *  Correctly bounds based off of the population cap
   *
   *  TODO: make this have the correct growth rate instead of being exponential
   *
   *  \returns the population after being grown
   */
  double GrowPopulation () {
    population *= growth_rate;
    if (population > population_cap) {
      population = population_cap;
    }
    return population;
  }

  /// Get the population of this planet
  double GetPopulation() const { return population; }

  /** Get a pointer to the owner of this planet
   *
   * \return pointer to the owner of this planet */
  Agent * GetOwner() const { return owner;}


  /// Get the X of the center of this planet
  double GetX() const { return circ.GetCenterX(); }
  /// Get the Y of the center of this planet
  double GetY() const { return circ.GetCenterY(); }
  /// Get the radius of this planet
  double GetRadius() const { 
    return circ.GetRadius();
  }

protected:
  /// the circle for this planet
  emp::Circle circ; 

  /// the rate at which the population grows
  double growth_rate = 1.01;

  /// the current population of this planet
  double population = 0;

  /// maximum population
  double population_cap = 0;

  /// pointer to the owner of this planet
  Agent * owner = nullptr;
  /// vector of pointers to the neighbors of this planet
  emp::vector<Planet *> neighbors;

};
