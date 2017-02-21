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

  /** Actual constructor
   *
   * \param numPlanets the number of planets to construct with this interface
   */
  WebInterface(uint64_t numPlanets, UI::Canvas & canvas) : UI::Animate(canvas), galaxy(numPlanets) {
     
  }

  WebInterface() = delete; //< disabled default constructor

  WebInterface(const WebInterface & ) = delete; //< disable copy constructor
  WebInterface operator= (const WebInterface &) = delete; //< disable assignment
  
  WebInterface( WebInterface && ) = delete; //< disable move constructor
  WebInterface operator= (WebInterface &&) = delete; //< disable move assign

private:
  /// the galaxy this interface displays
  Galaxy galaxy;
  
};



/*
 * Just think of these as 'persistent', not 'globals'
 */
UI::Document doc("emp_base");
WebInterface interface(5);


/**
 * REMEMBER: THIS FUNCTION DIES
 */
int main()
{
  doc << "<h1>Hello, world!</h1>";
}
