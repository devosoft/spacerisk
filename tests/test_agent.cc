/** file: test-agent.cc
 *  author: Jake Fenton
 *
 * Contains tests for the agent.h
 *
 */

#define CATCH_CONFIG_MAIN
#undef NDEBUG

#include "../third-party/catch/single_include/catch.hpp"

#include "../source/agent.h"
#include "../source/galaxy.h"

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
  Galaxy milky(5, 100, 100);

  milky.AddAgent("Smith");

  auto ags = milky.GetAgents();
  
  // only one agent, means we can cheat
  for (auto a : ags) {
    REQUIRE(a.GetName() == "Smith");
    REQUIRE(a.GetColor() == "green");
  }
}


