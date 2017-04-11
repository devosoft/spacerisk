#pragma once

// Empirical library includes
#include "tools/vector.h"
#include "tools/Random.h"

// local includes
#include "planet.h"
#include "agent.h"

const size_t MAX_RANDOMIZE_TRIES = 1000000;
const double MIN_RAD = 5.0;
const double MAX_RAD = 20.0;

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


  /** This function will update the state of the galaxy before it is displayed
   *
   *  Ostensibly, this should take a double that's the amount of time since the last
   *  update, since framerates are not a reliable way to judge time
   *
   *  but that's probably more complex than we need for this
   */
  void Update() {

    for (auto & p : planets) {
      p.GrowPopulation();
    }
  }

  /** This randomize only reorders planets, but also removes owners
   */
  void Randomize() {
    size_t counter = 0; 
    
    for (size_t i=0; i<planets.size(); i++){
      // note, 5 & 20 are arbitrary
      double radius = random.GetDouble(MIN_RAD,MAX_RAD);
      double y = random.GetDouble(radius, height-radius); //make sure noting goes off screen
      double x = random.GetDouble(radius, width-radius);
      planets[i].Reset(x,y,radius);
      planets[i].SetOwner(nullptr);

      if (counter > MAX_RANDOMIZE_TRIES) continue; //if overlaps, just give up :) 

      for(size_t j =0; j<i; j++){
          if (planets[i].GetCircle().HasOverlap(planets[j].GetCircle())){
              i--; 
              counter++;
              break;

          }
      }
    }

  }
  
  /** Function to randomize the starting configuration (location, size) of all the planets, while
   *  attempting to prevent them from overlapping.
   *
   *  \param reference to vector containing agents
   *  Will give up after a while if it can't place them without overlaps.
   */
  void Randomize(emp::vector<Agent *> & agents){
    Randomize();

    // grant each player a planet
    for (auto & agent : agents)
    {
      size_t randomChoice;
      // get a random choice of planet until the choice is unowned
      do {
        randomChoice = random.GetInt(planets.size());
      } while (planets[randomChoice].GetOwner());

      planets[randomChoice].SetOwner(agent);
      planets[randomChoice].SetPopulation(1);

    }
  }

   /** Add a planet to the galaxy
   * \param x the x coord of the planet to add
   * \param y the y coord of the planet to add
   * \param r the radius of the planet to add
   */
  void AddPlanet(double x, double y, double r){
      planets.emplace_back(x,y,r);
  }

  /** TODO: figure out a way to process displaying planets without actually handing the entire
   * planets vector outside of this object
   */
  emp::vector<Planet> GetPlanets() const { return planets;}

protected:
  /// random thingy
  emp::Random random;
  /// vector of planet objects in this galaxy
  emp::vector<Planet> planets;
  
  double width;
  double height; 
};
