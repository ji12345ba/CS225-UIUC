#include <cmath>
#include <iterator>
#include <iostream>
#include <list>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
using namespace std;
/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  currentPoint = Point(-1, -1);
}

//constructor
ImageTraversal::Iterator::Iterator(ImageTraversal* traversal_, Point point_){
  traversal = traversal_;
  currentPoint = point_;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
    currentPoint = traversal->pop();
    //right pixel
    if(currentPoint.x + 1 < traversal->png_.width()){ //check not out of bounds
      if(traversal->visited[currentPoint.x + 1][currentPoint.y] == false){ //check not visited
        if(calculateDelta(traversal->png_.getPixel(currentPoint.x + 1, currentPoint.y), traversal->png_.getPixel(traversal->start_.x, traversal->start_.y)) <= traversal->tolerance_){ //check within tolerance
          Point right(currentPoint.x + 1, currentPoint.y);
          traversal->add(right);
        }
      }
    }

    //below pixel
    if(currentPoint.y + 1 < traversal->png_.height()){ //check not out of bounds
      if(traversal->visited[currentPoint.x][currentPoint.y + 1] == false){ //check not visited
        if(calculateDelta(traversal->png_.getPixel(currentPoint.x, currentPoint.y + 1), traversal->png_.getPixel(traversal->start_.x, traversal->start_.y)) <= traversal->tolerance_){ //check within tolerance
          Point below(currentPoint.x, currentPoint.y + 1);
          traversal->add(below);
        }
      }
    }

    //left pixel
    if(currentPoint.x > 0){ //check not out of bounds
      if(traversal->visited[currentPoint.x - 1][currentPoint.y] == false){ //check not visited
        if(calculateDelta(traversal->png_.getPixel(currentPoint.x - 1, currentPoint.y), traversal->png_.getPixel(traversal->start_.x, traversal->start_.y)) <= traversal->tolerance_){ //check within tolerance
          Point left(currentPoint.x - 1, currentPoint.y);
          traversal->add(left);
        }
      }
    }

    //above pixel
    if(currentPoint.y > 0){ //check not out of bounds
      if(traversal->visited[currentPoint.x][currentPoint.y - 1] == false){ //check not visited
        if(calculateDelta(traversal->png_.getPixel(currentPoint.x, currentPoint.y - 1), traversal->png_.getPixel(traversal->start_.x, traversal->start_.y)) <= traversal->tolerance_){ //check within tolerance
          Point above(currentPoint.x, currentPoint.y - 1);
          traversal->add(above);
        }
      }
    }

    traversal->visited[currentPoint.x][currentPoint.y] = true;

    currentPoint = traversal->peek(); //becomes next point in traversal list. (-1, -1) if empty

    while(!traversal->point_list.empty()){  //the if below with cause segfault if currentPoint = -1, -1
      if(traversal->visited[currentPoint.x][currentPoint.y] == true){
        currentPoint = traversal->pop();
        currentPoint = traversal->peek();
      }
      else{break;}
    }   //passed 7*4 test with while loop

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return this->currentPoint;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return !(this->currentPoint == other.currentPoint);
}
