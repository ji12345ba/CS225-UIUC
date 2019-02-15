#include "StickerSheet.h"
#include "Image.h"


StickerSheet::StickerSheet(const Image &picture, unsigned max){
  max_ = max;
  base_image = picture;
  Scene = new Image* [max];
  x_array = new unsigned[max];
  y_array = new unsigned[max];
  for(unsigned i = 0; i < max; i++){  //initialize every pointer in the array
    Scene[i] = NULL;
  }
  num_stickers = 0;
}


StickerSheet::~StickerSheet(){
  clear();
}


void StickerSheet::clear(){
  for(unsigned i = 0; i < num_stickers; i++){
    delete Scene[i];
    Scene[i] = NULL;
  }
  delete[] Scene;
  Scene = NULL;
  delete[] x_array;
  x_array = NULL;
  delete[] y_array;
  y_array = NULL;
}


StickerSheet::StickerSheet(const StickerSheet &other){
  copy(other);
}


void StickerSheet::copy(const StickerSheet & other){
  max_ = other.max_;
  base_image = other.base_image;
  num_stickers = other.num_stickers;
  x_array = new unsigned[max_];
  y_array = new unsigned[max_];
  Scene = new Image* [max_];
  for (unsigned i = 0; i < max_; i++){
    Scene[i] = NULL;
  }

  for (unsigned i = 0; i < num_stickers; i++){
      Scene[i] = new Image();
      *Scene[i] = *other.Scene[i];
      x_array[i] = other.x_array[i];
      y_array[i] = other.y_array[i];
  }
}


const StickerSheet & StickerSheet::operator=(const StickerSheet &other){
  clear();
  copy(other);
  return *this;
}


void StickerSheet::changeMaxStickers(unsigned new_max){
  if(new_max == num_stickers){
    return;
  }
  Image** newScene = new Image*[new_max];
  for(unsigned i = 0; i < new_max; i++){
    newScene[i] = NULL;
  }
  unsigned* new_x_array = new unsigned[new_max];
  unsigned* new_y_array = new unsigned[new_max];

  if(num_stickers < new_max){
    for (unsigned i = 0; i < num_stickers; i++){
      newScene[i] = new Image();
      *newScene[i] = *Scene[i];
      new_x_array[i] = x_array[i];
      new_y_array[i] = y_array[i];
    }
  }
  else{ //num_stickers > new_max, some stickers are lost
    for (unsigned i = 0; i < new_max; i++){
      newScene[i] = new Image();
      *newScene[i] = *Scene[i];
      new_x_array[i] = x_array[i];
      new_y_array[i] = y_array[i];
    }
    num_stickers = new_max;
  }

  clear();
  Scene = newScene;
  newScene = NULL;
  x_array = new_x_array;
  new_x_array = NULL;
  y_array = new_y_array;
  new_y_array = NULL;

  max_ = new_max;
}


int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
  if(num_stickers < max_){
    if(Scene[num_stickers] == NULL){
      Scene[num_stickers] = new Image();
    }
    *Scene[num_stickers] = sticker;
    x_array[num_stickers] = x;
    y_array[num_stickers] = y;
    num_stickers ++;
    return (num_stickers - 1);
  }
  return -1;
}


bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if(index >= num_stickers){
    return false;
  }
  else{
    x_array[index] = x;
    y_array[index] = y;
    return true;
  }
}


void StickerSheet::removeSticker(unsigned index){
  if(index < num_stickers){
    for(unsigned i = index; i < (num_stickers - 1); i++){
      *Scene[i] =  *Scene[i + 1];      //push every sticker after the removed one to the left
      x_array[i] = x_array[i + 1];
      y_array[i] = y_array[i + 1];
    }
    delete Scene[num_stickers - 1];  //delete the last one
    Scene[num_stickers] = NULL;
    num_stickers --;
  }
}


Image * StickerSheet::getSticker(unsigned index) const{
  if (index < num_stickers){
    return Scene[index];
  }
  return NULL;
}

Image StickerSheet::render() const{
  Image new_image;
  unsigned max_width = base_image.width();
  unsigned max_height = base_image.height();

  for (unsigned i = 0; i < num_stickers; i++){
    if(Scene[i] != NULL){
      if(x_array[i] + Scene[i]->width() > max_width){
        max_width = x_array[i] + Scene[i]->width();
      }
      if(y_array[i] + Scene[i]->height() > max_height){
        max_height = y_array[i] + Scene[i]->height();
      }
    }
  }
  new_image = base_image;
  new_image.resize(max_width, max_height);

  for(unsigned i = 0; i < num_stickers; i++){
    if(Scene[i] != NULL){
      for(unsigned w = x_array[i]; w < (x_array[i] + Scene[i]->width()); w++){
        for(unsigned h = y_array[i]; h < (y_array[i] + Scene[i]->height()); h++){
          if(Scene[i]->getPixel((w - x_array[i]), (h - y_array[i])).a != 0){
            new_image.getPixel(w, h) = Scene[i]->getPixel((w - x_array[i]), (h - y_array[i]));
          }
        }
      }
    }
  }
  return new_image;
}
