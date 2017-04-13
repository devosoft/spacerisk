//  This file is part of Project Name
//  Copyright (C) Michigan State University, 2017.
//  Released under the MIT Software license; see doc/LICENSE

// Empirical library
#include "web/web.h"
#include "web/Animate.h"

// local
#include "../galaxy.h"
#include "../PlayerAgent.h"
#include "../Game.h"

namespace UI = emp::web;

static const std::string PlayerColors[] = { "green", "red", "blue", "purple", "orange", "brown"};

// TODO: @CAO, plz to not make animate need the canvas at constructor time
class WebInterface : public UI::Animate {
public:

  /** Draw a frame of the animation
   *
   */
  void DoFrame () {

      game.Update();
      canvas.Clear("black"); 
      auto const & planets = game.GetPlanets();

      canvas.Font("10px Arial");

      for (auto & planet : planets){
          std::string currColor = "grey";

          if (planet.GetOwner() != nullptr)
          {
            currColor = PlayerColors[planet.GetOwner()->GetID()];

            if (&planet == currSelected) {
              currColor = "yellow";
            }
          }
          
          canvas.Draw(planet.GetCircle(), currColor);
          canvas.CenterText(planet.GetX(),
                            planet.GetY(),
                            emp::to_string((int)planet.GetPopulation()),
                            "white");
      }

  }

  /** Actual constructor
   *
   * \param numPlanets the number of planets to construct with this interface
   */
  WebInterface(uint64_t numPlanets, double width, double height) : game(numPlanets, width, height),
                                                                   doc("emp_base"), 
                                                                   canvas(doc.AddCanvas(width, height, "map")),
                                                                   player("Player") {
     // help, I'm trapped in a canvas factory

     doc.AddButton([this](){game.Randomize();}, "Randomize", "random_button");
     doc << "<h1>Hello, World!</h1>" ; 

     game.AddAgent("Steven");
     game.AddAgent("Tess");
     game.AddAgent("Sponge");
     canvas.On("click", [this](UI::MouseEvent event){ MouseClick(event);});

     game.AddAgent(&player);

     Start(); //start animation DoFrame() will be run repeatedly
  }


  WebInterface() = delete; //< disabled default constructor

  WebInterface(const WebInterface & ) = delete; //< disable copy constructor
  WebInterface operator= (const WebInterface &) = delete; //< disable assignment
  
  WebInterface( WebInterface && ) = delete; //< disable move constructor
  WebInterface operator= (WebInterface &&) = delete; //< disable move assign

private:
  Game game;

  UI::Document doc; ////// make a doc
  UI::Canvas canvas; //< canvas!

  /* the player for this interface
   * 
   * TODO: it's actually possible to not have a player, and to just be observing the AIs
   * Need to account for that
   *
   */
  PlayerAgent player;

  // TODO: we don't want this to be const (since we'll be modifying the planets by 
  // interacting with them), but we have the planet refs below as consts, so....
  // yeah.
  // need to fix that.
  const Planet * currSelected;

  void MouseClick(UI::MouseEvent & event){
      int x = event.clientX - canvas.GetXPos();
      int y = event.clientY - canvas.GetYPos();
   
      std::cout << "click" << std::endl;

      for (auto const & planet : game.GetPlanets()) {
        if(planet.GetCircle().Contains(x, y)) {
          if (currSelected == &planet) {
            currSelected = nullptr;
          }
          else {
            if (planet.GetOwner() == &player) {
              currSelected = &planet;
              std::cout << "Clicked on something we own." << std::endl;
            }
          }
        }
        
      }
  }

};



/*
 * Just think of these as 'persistent', not 'globals'
 */
WebInterface interface(50, 600, 400);


/**
 * REMEMBER: THIS FUNCTION DIES
 */
int main()
{

}
