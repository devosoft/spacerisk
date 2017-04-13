/**
 * \file Game.h
 * \author Jake Fenton
 *
 * This file contains the Game object and its implementaiton
 *
 * The game will be responsible for co-ordinating the communication between all the interfaces,
 * galaxy and players
 *
 */

#include "tools/vector.h"

#include <utility>

#include "agent.h"
#include "galaxy.h"

class Game {

public:

  Game(size_t numPlanets, double width, double height) : galaxy(numPlanets, width, height) {}

  /** Add a player to the game
  *  
  * \param name the name of the agent to add
  */
  Agent & AddAgent(std::string name)
  {
    agents.push_back(std::make_pair(new Agent(name, agents.size()), true));
    return *(agents.back().first);
  }

  Agent & AddAgent(Agent * a) {
    a->SetID(agents.size());
    agents.push_back(std::make_pair(a, false));
    return *(agents.back().first);
  }

  /** Update the game
   *
   * TODO: make this a signal, consult @CAO
   */
  void Update() {
    galaxy.Update();
  }

  /* Get the planets vector (ew ew ew) from the galazy and return it
   *
   * THIS IS BAD WE SHOULD FIND A BETTER WAY
   *
   * \returns const vector of planets
   */
  auto GetPlanets () const { return galaxy.GetPlanets(); }


  /** Effectively a reset for the game
   *  This should also be some kind of signal
   *  TODO: Signalz
   */
  void Randomize() {
    galaxy.Randomize(agents);
  }

protected:
  Galaxy galaxy;
  emp::vector<std::pair<Agent* , bool>> agents;
};
