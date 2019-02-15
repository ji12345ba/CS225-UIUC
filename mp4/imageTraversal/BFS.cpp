#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"
using namespace std;
using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  png_ = png;
  start_ = start;
  tolerance_ = tolerance;
  //set up 2D boolean array visited
  visited = new bool*[png_.width()];
  for(unsigned i = 0; i < png_.width(); i++){
    visited[i] = new bool[png_.height()];
  }
  for(unsigned i = 0; i < png_.width(); i++){
    for(unsigned j = 0; j < png_.height(); j++){
      visited[i][j] = false;
    }
  }
  point_list.push_back(start_);
  //visited[start_.x][start_.y] = true;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal* dfs = new BFS(png_, start_, tolerance_);
  ImageTraversal::Iterator it(dfs, start_);
  return it;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  point_list.push_back(point);
  return;
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  if(point_list.empty()){
    return Point(-1, -1);
  }
  Point temp = point_list.front();
  point_list.pop_front();
  return temp;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  if(point_list.empty()){
    return Point(-1, -1);
  }
  return point_list.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return point_list.empty();
}


/*
//right pixel
if(point.x + 1 < png_.width()){ //check not out of bounds
  if(visited[point.x + 1][point.y] == false){ //check not visited
    if(calculateDelta(png_.getPixel(point.x, point.y), png_.getPixel(point.x + 1, point.y)) <= tolerance_){ //check within tolerance
      Point right(point.x + 1, point.y);
      point_list.push_back(right);
      visited[right.x][right.y] = true;
    }
  }
}

//below pixel
if(point.y + 1 < png_.height()){ //check not out of bounds
  if(visited[point.x][point.y + 1] == false){ //check not visited
    if(calculateDelta(png_.getPixel(point.x, point.y), png_.getPixel(point.x, point.y + 1)) <= tolerance_){ //check within tolerance
      Point below(point.x, point.y + 1);
      point_list.push_back(below);
      visited[below.x][below.y] = true;
    }
  }
}

//left pixel
if(point.x > 0){ //check not out of bounds
  if(visited[point.x - 1][point.y] == false){ //check not visited
    if(calculateDelta(png_.getPixel(point.x, point.y), png_.getPixel(point.x - 1, point.y)) <= tolerance_){ //check within tolerance
      Point left(point.x - 1, point.y);
      point_list.push_back(left);
      visited[left.x][left.y] = true;
    }
  }
}

//above pixel
if(point.y > 0){ //check not out of bounds
  if(visited[point.x][point.y - 1] == false){ //check not visited
    if(calculateDelta(png_.getPixel(point.x, point.y), png_.getPixel(point.x, point.y - 1)) <= tolerance_){ //check within tolerance
      Point above(point.x, point.y - 1);
      point_list.push_back(above);
      visited[above.x][above.y] = true;
    }
  }
}
*/
