/** This file is part of something blah blag
 *  see LICENSE
 */

#pragma once

#include "geometry/Circle2D.h"

class Planet {

public:
  /** x coord
   *  y coor
   *  radius
   *  (surprise!)
   */
  Planet(double x, double y, double r) : circ(x, y, r) {
    
  }


  const emp::Circle & GetCircle() const { return circ;}


protected:
  emp::Circle circ; 

};
