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
  Galaxy (uint64_t numPlanets, double w, double h): width(w), height(h) {
    for (size_t i = 0; i < numPlanets; i++) {
      planets.emplace_back(0,0,0); 
    }
    Randomize(); 
  };

  /** Function to randomize the starting configuration (location, size) of all the planets, while
   *  attempting to prevent them from overlapping.
   *
   *  Will give up after a while if it can't place them without overlaps.
   */
  void Randomize(){
      int counter = 0; 
      for (size_t i=0; i<planets.size(); i++){

          // note, 5 & 20 are arbitrary
          double radius = random.GetDouble(5,20);
          double y = random.GetDouble(radius, height-radius); //make sure noting goes off screen
          double x = random.GetDouble(radius, width-radius);
          planets[i].Reset(x,y,radius);
          planets[i].SetOwner(nullptr);

          if (counter > 1000000) continue; //if overlaps, just give up :) 

          for(size_t j =0; j<i; j++){
              if (planets[i].GetCircle().HasOverlap(planets[j].GetCircle())){
                  i--; 
                  counter++;
                  break;

              }
          }
      }

      // grant each player a planet
      for (auto agent : agents)
      {
        size_t randomChoice;
        // get a random choice of planet until the choice is unowned
        do {
          randomChoice = random.GetInt(planets.size());
        } while (planets[randomChoice].GetOwner());

        planets[randomChoice].SetOwner(&agent);
      }
  }

  /** Add a player to the galaxy
   *  
   * \param name the name of the agent to add
   */
  void AddAgent(std::string name)
  {
    agents.emplace_back(name, agents.size());
  }

  /** Add a planet to the galaxy
   * \param x the x coord of the planet to add
   * \param y the y coord of the planet to add
   * \param r the radius of the planet to add
   */
  void AddPlanet(double x, double y, double r){
      planets.emplace_back(x,y,r);
  }

  // buwhai?
  const emp::vector<Planet>& GetPlanets() const { return planets;}
  const emp::vector<Agent>& GetAgents() const { return agents;}


protected:
  /// random thingy
  emp::Random random;
  /// vector of planet objects in this galaxy
  emp::vector<Planet> planets;
  /// vector of agent objects for this galaxy ( slash universe, thanks spjps)
  emp::vector<Agent> agents;  
  
  double width;
  double height; 
};
