
#pragma once

#include "base/vector.h"
#include "base/assert.h"
#include "tools/functions.h"
#include <set> 

// TODO: if this is header only, nuke the following & fix the fallout
class Planet;


class Agent {
public:

  Agent() = delete;

  /** Construct an agent
   * \param n the name of this agent
   */
  Agent (std::string n, int id = -1) : name(n), ID(id) {
  }

  /** Get the name of the agent
   *
   */
  std::string GetName() const { return name; }

  /** Get the planet currently selected by this agent
   *
   */
  const Planet * GetSelected() const { return selected; }

  /** set the planet we have selected
   *
   */
  void SetSelected (const Planet * sel) { 
    selected = sel;
  }
 
  /** Add a planet to this agent's owned collection
   * 
   * \param p pointer to the planet to own
   */
  void AddOwnedPlanet (Planet * p) {
    planets.insert(p);
  }

  /** Get the ID of this agent
   * \returns the id of this agent
   */
  int GetID() { return ID; }

  /** Set the ID of this agent
   *  \param i the new id of this agent
   */
  void SetID(int i) { ID = i;}

protected:
  /// vector of pointers to planets owned by this agent
  std::set<Planet *> planets;

  /// the planet selected, currently
  const Planet * selected = nullptr;

  /// Name of this agent
  std::string name = "unassigned";

  /// The ID of this agent
  int ID = -1;
};
