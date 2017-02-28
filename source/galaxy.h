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

  void Randomize(){
      int counter = 0; 
      for (size_t i=0; i<planets.size(); i++){

          // note, 5 & 20 are arbitrary
          double radius = random.GetDouble(5,20); 
          double y = random.GetDouble(radius, height-radius); //make sure noting goes off screen
          double x = random.GetDouble(radius, width-radius); 
          planets[i].Reset(x,y,radius); 

          if (counter > 1000000) continue; //if overlaps, just give up :) 

          for(size_t j =0; j<i; j++){
              if (planets[i].GetCircle().HasOverlap(planets[j].GetCircle())){
                  i--; 
                  counter++;
                  break;

              }
          }
      }
  }

  void AddPlanet(double x, double y, double r){
      planets.emplace_back(x,y,r);
  }

  const emp::vector<Planet>& getPlanets() const { return planets;} 
  const emp::vector<Agent>& getAgents() const { return agents;} 


protected:
  /// random thingy
  emp::Random random;
  /// vector of planet objects in this galaxy
  emp::vector<Planet> planets;
  /// vector of agent objects for this galaxy ( slash universe, thanks spjps)
  emp::vector<Agent> agents;  
  double width; double height; 
};
