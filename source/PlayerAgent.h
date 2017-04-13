#pragma once

#include "agent.h"

/** This class implements a (probably) human player, with its associated interface
 *
 * This class may be used by an AI playing with the human interface
 *
 */
class PlayerAgent : public Agent {
public:
  PlayerAgent(std::string name, int id=-1) : Agent(name, id) {};
};
