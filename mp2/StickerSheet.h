#include "Image.h"

#pragma once

 class StickerSheet{
 public:

   Image** Scene;
   unsigned* x_array;
   unsigned* y_array;
   unsigned max_;
   unsigned num_stickers;
   Image base_image;

   StickerSheet(const Image &picture, unsigned max);
   ~StickerSheet();
   StickerSheet(const StickerSheet &other); //copy constructor
   const StickerSheet & operator=(const StickerSheet &other);
   void changeMaxStickers(unsigned max);
   int addSticker(Image &sticker, unsigned x, unsigned y);
   bool translate(unsigned index, unsigned x, unsigned y);
   void removeSticker(unsigned index);
   Image *getSticker(unsigned index) const;
   Image render() const;
   void copy(const StickerSheet & other);
   void clear();
 };
