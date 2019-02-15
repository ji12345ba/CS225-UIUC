#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>



void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG * original = new PNG();
  original->readFromFile(inputFile);
  unsigned int width = original->width();
  unsigned int height = original->height();
  PNG * output = new PNG(width, height);
  for(unsigned int x = 0; x < width; x++){
    for(unsigned int y = 0; y < height; y++){
      HSLAPixel & prev = original->getPixel(x, y);
      HSLAPixel & curr = output->getPixel(width - x - 1, height - y - 1);
      curr = prev;
    }
  }
  output->writeToFile(outputFile);
  delete original;
  delete output;
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // TODO: Part 3

  for(unsigned int x = 0; x < width; x++){
    for(unsigned int y = 0; y < height; y++){
      HSLAPixel & p = png.getPixel(x, y);
      p.s = 1;
      p.l = 0.5;
      p.h = 160;
      p.a = (double)y / (double)height;
    }
  }
  for(unsigned int x = 0; x < width; x++){
    for(unsigned int y = 0; y < ((double)height / 2.0); y++){
      HSLAPixel & p = png.getPixel(x, y);
      p.s = 1;
      p.l = 0.5;
      p.h = 215;
      p.a = 1 - (    (double)y    /   (double)height    );
    }
  }
  for(unsigned int x = (width / 4); x < ((double)width / 4 * 3); x++){
    for(unsigned int y = (height / 4); y < ((double)height /2); y++){
      HSLAPixel & p = png.getPixel(x, y);
      p.l = p.l + 0.2;
      p.h = 270;
    }
  }
  for(unsigned int x = (width / 4); x < ((double)width / 4 * 3); x++){
    for(unsigned int y = (height / 2); y < ((double)height / 4 * 3); y++){
      HSLAPixel & p = png.getPixel(x, y);
      p.l = p.l + 0.2;
      p.h = 23;
    }
  }
  int counter = 0;
  for(unsigned int x = 0; x < width; x++){
    for(unsigned int y = 0; y < height; y++){
      HSLAPixel & p = png.getPixel(x, y);
      if(counter % 36 == 0){
        p.l = 0.05;
      }
      counter++;
    }
  }


  return png;
}
