#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) { //24 & 240 orange and blue
  /* @todo [Part 3] */
  double hue;
  unsigned very_random_number = x*x + y*y;


  hue = 50 - (very_random_number % 100);

  HSLAPixel pixel(hue, 1, 0.5);
  return pixel;
}
