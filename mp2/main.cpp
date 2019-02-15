#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image alma, sticker1, sticker2, sticker3, output;
  alma.readFromFile("alma.png");
  sticker1.readFromFile("thug.resized.png");
  sticker2.readFromFile("corn.resized.png");
  sticker3.readFromFile("i.resized.png");

  StickerSheet mp2pic(alma, 4);
  mp2pic.addSticker(sticker1, 415, 35);
  mp2pic.addSticker(sticker2, 295, 60);
  mp2pic.addSticker(sticker2, 550, 60);
  mp2pic.addSticker(sticker3, 400, 140);
  output = mp2pic.render();
  output.writeToFile("myImage.png");

  return 0;
}
