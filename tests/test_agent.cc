/** file: test-agent.cc
 *  author: Jake Fenton
 *
 * Contains tests for the agent.h
 *
 */

#define CATCH_CONFIG_MAIN
#undef NDEBUG

#include "../third-party/catch/single_include/catch.hpp"

#include <iostream>

#include "../source/agent.h"
#include "../source/galaxy.h"
#include "../source/planet.h"
#include "../source/Game.h"


TEST_CASE("construct agent", "[unit]") {
  Agent smith("smith", 1);

  REQUIRE(smith.GetName() == "smith");
  REQUIRE(smith.GetColor() == "red");
}

TEST_CASE("construct galaxy", "[unit]") {
  Galaxy milky(5, 100, 100);
  REQUIRE(milky.GetPlanets().size() == 5);
}

TEST_CASE("add agent to galaxy", "[unit]") {
  Game game(5, 100, 100);
  game.AddAgent("Smith");
  
  const emp::vector<Agent> & agents = game.GetAgents();

  // only one agent, means we can cheat
  for (const Agent & a : agents) {
    REQUIRE(a.GetName() == "Smith");
    REQUIRE(a.GetColor() == "green");
  }
}

TEST_CASE("planet construct", "[unit]"){
 Planet Eros(0, 0, 1); 
}

TEST_CASE("planet add owner", "[unit]") {
  Planet Eros(0, 0, 1);
  Agent Smith("Smith", 0);

  Eros.SetOwner(&Smith);
  REQUIRE(Eros.GetOwner() == &Smith);
  REQUIRE(Eros.GetOwner()->GetName() == "Smith");
  REQUIRE(Eros.GetOwner()->GetColor() == "green");
}

TEST_CASE("galaxy random agent assign", "[unit]") {
  Game game(1, 100, 100);
  game.AddAgent("Smith");
  game.Randomize(); // will make game assign Smith to the one planet

  REQUIRE(game.GetAgents()[0].GetName() == "Smith");

  std::cout << &(game.GetAgents()[0]) << std::endl;
  std::cout << game.GetPlanets()[0].GetOwner() << std::endl;

  for (auto a : game.GetPlanets())
  {
    REQUIRE(a.GetOwner()->GetName() == "Smith");
    REQUIRE(a.GetOwner()->GetColor() == "green");
  }

}


TEST_CASE("planet x y setter/getter", "[unit]") {
  Planet Eros(5, 10, 15);

  REQUIRE(Eros.GetX() == 5);
  REQUIRE(Eros.GetY() == 10);
  REQUIRE(Eros.GetRadius() == 15);

}
