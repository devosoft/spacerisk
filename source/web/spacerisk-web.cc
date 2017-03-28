//  This file is part of Project Name
//  Copyright (C) Michigan State University, 2017.
//  Released under the MIT Software license; see doc/LICENSE

#include "web/web.h"
#include "../galaxy.h"
#include "web/Animate.h"


namespace UI = emp::web;

// TODO: @CAO, plz to not make animate need the canvas at constructor time
class WebInterface : public UI::Animate {
public:

  /** Draw a frame of the animation
   *
   */
  void DoFrame () {
      
      canvas.Clear("black"); 
      auto & planets = galaxy.GetPlanets();
      std::cout << "Animating frame now." << std::endl;

      canvas.Font("10px Arial");

      for (auto & planet : planets){
          std::string currColor = "grey";

          if (planet.GetOwner() != nullptr)
          {
            currColor = planet.GetOwner()->GetColor();

            if (planet.GetOwner()->GetSelected() != nullptr) {
              emp::Alert("Found planet!");
            }

            if (&planet == planet.GetOwner()->GetSelected()) {
              currColor = "yellow";
            }
          }
          
          canvas.Draw(planet.GetCircle(), currColor);
          canvas.CenterText(planet.GetCircle().GetCenterX(),
                            planet.GetCircle().GetCenterY(),
                            emp::to_string((int)planet.GetPopulation()),
                            "white");
          planet.GrowPopulation();
      }

  }

  /** Actual constructor
   *
   * \param numPlanets the number of planets to construct with this interface
   */
  WebInterface(uint64_t numPlanets, double width, double height) : galaxy(numPlanets, width, height), doc("emp_base"), canvas(doc.AddCanvas(width, height, "map")) {
     // help, I'm trapped in a canvas factory

     doc.AddButton([this](){galaxy.Randomize();}, "Randomize", "random_button");
     doc << "<h1>Hello, World!</h1>" ; 

     galaxy.AddAgent("Steven");
     galaxy.AddAgent("Tess");
     galaxy.AddAgent("Sponge");
     canvas.On("click", [this](UI::MouseEvent event){ MouseClick(event);}); 

     Start(); //start animation DoFrame() will be run repeatedly
  }


  WebInterface() = delete; //< disabled default constructor

  WebInterface(const WebInterface & ) = delete; //< disable copy constructor
  WebInterface operator= (const WebInterface &) = delete; //< disable assignment
  
  WebInterface( WebInterface && ) = delete; //< disable move constructor
  WebInterface operator= (WebInterface &&) = delete; //< disable move assign

private:
  /// the galaxy this interface displays
  Galaxy galaxy;

  // Is this how I use doxygen //< <> >> 
  //< looks good
  UI::Document doc; ////// make a doc
  UI::Canvas canvas; //< canvas!

  void MouseClick(UI::MouseEvent & event){
      int x = event.clientX - canvas.GetXPos();
      int y = event.clientY - canvas.GetYPos();
      
      for (auto planet : galaxy.GetPlanets()) {
        if(planet.GetCircle().Contains(x, y)) {
          planet.GetOwner()->SetSelected(&planet);
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
