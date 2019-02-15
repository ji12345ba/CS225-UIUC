#include "Image.h"
using namespace cs225;

void Image::lighten(){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & p = this->getPixel(i, j);
      if (p.l + 0.1 >= 1){
        p.l = 1;
      }
      else{
        p.l += 0.1;
      }
    }
  }
}

void Image::lighten(double amount){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & p = this->getPixel(i, j);
      if (p.l + amount >= 1){
        p.l = 1;
      }
      else{
        p.l += amount;
      }
    }
  }
}

void Image::darken(){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & p = this->getPixel(i, j);
      if (p.l - 0.1 <= 0){
        p.l = 0;
      }
      else{
        p.l -= 0.1;
      }
    }
  }
}

void Image::darken(double amount){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & p = this->getPixel(i, j);
      if (p.l - amount <= 0){
        p.l = 0;
      }
      else{
        p.l -= amount;
      }
    }
  }
}

void Image::saturate(){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & p = this->getPixel(i, j);
      if (p.s + 0.1 >= 1){
        p.s = 1;
      }
      else{
        p.s += 0.1;
      }
    }
  }
}

void Image::saturate(double amount){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & p = this->getPixel(i, j);
      if (p.s + amount >= 1){
        p.s = 1;
      }
      else{
        p.s += amount;
      }
    }
  }
}

void Image::desaturate(){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & p = this->getPixel(i, j);
      if (p.s - 0.1 <= 0){
        p.s = 0;
      }
      else{
        p.s -= 0.1;
      }
    }
  }
}

void Image::desaturate(double amount){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & p = this->getPixel(i, j);
      if (p.s - amount <= 0){
        p.s = 0;
      }
      else{
        p.s -= amount;
      }
    }
  }
}

void Image::grayscale(){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & p = this->getPixel(i, j);
      p.s = 0;
    }
  }
}

void Image::rotateColor(double degrees){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & p = this->getPixel(i, j);
      double final_h = p.h;
      final_h += degrees;
      //check if it's out of bounds
      if (final_h < 0){
        final_h += 360;
      }
      if (final_h > 360){
        final_h -= 360;
      }
      p.h = final_h;
    }
  }
}

void Image::illinify(){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & p = this->getPixel(i, j);
      if(p.h >= 113.5 && p.h <= 293.5){
        p.h = 216;
      }
      else{
        p.h = 11;
      }
    }
  }
}

void Image::scale(double factor){
  unsigned int w = (unsigned int)(this->width() * factor);
  unsigned int h = (unsigned int)(this->height() * factor);
  PNG* scaled = new PNG(w, h);
  //for every pixel in the new image
  for (unsigned int i = 0; i < w; i++){
    for (unsigned int j = 0; j < h; j++){
      HSLAPixel & p = scaled->getPixel(i, j);
      //change it to pixels in similar position of the original image
      unsigned int matched_i = (unsigned int) (this->width() * i / w + 0.5); //round double to unsigned int
      unsigned int matched_j = (unsigned int) (this->height() * j / h + 0.5);
      p = this->getPixel(matched_i, matched_j);
    }
  }
  //copy the new image to the original
  this->resize(w, h);
  for (unsigned int i = 0; i < w; i++){
    for (unsigned int j = 0; j < h; j++){
      HSLAPixel & p = scaled->getPixel(i, j);
      HSLAPixel & p_ = this->getPixel(i, j);
      p_ = p;
    }
  }
  delete scaled;  //delete the new image to prevent memory leak
}

void Image::scale(unsigned w, unsigned h){
  PNG* scaled = new PNG(w, h);
  //for every pixel in the new image
  for (unsigned int i = 0; i < w; i++){
    for (unsigned int j = 0; j < h; j++){
      HSLAPixel & p = scaled->getPixel(i, j);
      //change it to pixels in similar position of the original image
      unsigned int matched_i = (unsigned int) (this->width() * i / w + 0.5); //round double to unsigned int
      unsigned int matched_j = (unsigned int) (this->height() * j / h + 0.5);
      p = this->getPixel(matched_i, matched_j);
    }
  }
  //copy the new image to the original
  this->resize(w, h);
  for (unsigned int i = 0; i < w; i++){
    for (unsigned int j = 0; j < h; j++){
      HSLAPixel & p = scaled->getPixel(i, j);
      HSLAPixel & p_ = this->getPixel(i, j);
      p_ = p;
    }
  }
  delete scaled;  //delete the new image to prevent memory leak

}
