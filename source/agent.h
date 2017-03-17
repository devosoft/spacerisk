
#pragma once

#include "base/vector.h"
#include "base/assert.h"
#include "tools/functions.h"
#include <set> 

// TODO: if this is header only, nuke the following & fix the fallout
class Planet;

static const std::string PlayerColors[] = { "green", "red", "blue", "yellow", "purple", "orange", "brown"};

class Agent {
public:

  Agent() = delete;

  /** Construct an agent
   * \param n the name of this agent
   */
  Agent (std::string n, int id) : name(n), ID(id) {
    emp_assert(id < emp::GetSize(PlayerColors));
    emp_assert(id >= 0);
    color = PlayerColors[ID];
  }

  /** Get the color of this agent
   *
   * \return the color of this agent */
  std::string GetColor() const { return color; }

  /** Get the name of the agent
   *
   */
  std::string GetName() const { return name; }

protected:
  /// vector of pointers to planets owned by this agent
  std::set<Planet *> planets;

  /// Name of this agent
  std::string name = "unassigned";

  /// Color of this agent
  std::string color = "no color";

  /// The ID of this agent
  int ID = -1;
};
