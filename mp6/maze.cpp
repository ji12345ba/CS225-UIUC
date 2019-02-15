/* Your code here! */
#include "maze.h"
#include <sys/time.h>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

SquareMaze::SquareMaze(){
  //No-parameter constructor
  //Creates an empty maze
}

void SquareMaze::makeMaze(int width, int height){
  width_ = width;
  height_ = height;
  int mazeSize = width * height;
  mazeSets.addelements(mazeSize);
  for(int i = 0; i < mazeSize; i++){
    rightWalls.push_back(true);
    downWalls.push_back(true);
  }
  //select random walls to delete without creating a cycle
  int x, y;
  struct timeval tv;
  gettimeofday(&tv,NULL);
  srand(tv.tv_usec);
  while(mazeSets.size(0) < mazeSize){  //delete until there's only one set

    x = rand() % width_;
    y = rand() % height_;

    if(rand() % 2 == 1){
      if(x != width_ - 1){
        if(mazeSets.find(y * width_ + x) != mazeSets.find(y * width_ + x + 1)){
          rightWalls[y * width_ + x] = false;  //or use setWall
          mazeSets.setunion(y * width_ + x, y * width_ + x + 1);
        }
      }
    }
    else{
      if(y != height_ - 1){
        if(mazeSets.find(y * width_ + x) != mazeSets.find(y * width_ + x + width_)){
          setWall(x, y, 1, false);
          mazeSets.setunion(y * width_ + x, y * width_ + x + width_);
        }
      }
    }
  }

}

bool SquareMaze::canTravel(int x, int y, int dir) const{

  switch(dir){
    case 0: //right
      return rightWalls[y * width_ + x] == false;
    case 1: //down
      return downWalls[y * width_ + x] == false;
    case 2: //left
      return (x != 0) && (rightWalls[y * width_ + x - 1] == false);
    case 3: //up
      return (y != 0) && (downWalls[y * width_ + x - width_] == false);
  }
  return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
  if(dir == 0){
    rightWalls[y * width_ + x] = exists;
  }
  else if(dir == 1){
    downWalls[y * width_ + x] = exists;
  }
}



vector<int> SquareMaze::solveMaze(){
    int x, y, curr_idx;
    vector<int> prev_cell;  //stores the path of bfs
    vector<int> distance;  //stores the distance of every cell from entrance
    prev_cell.push_back(0); //entrance is visited
    distance.push_back(0);
    for(int i = 1; i < width_ * height_; i++){
      prev_cell.push_back(-1); //-1 = not visited
      distance.push_back(0);
    }
    queue<int> bfs;
    bfs.push(0);
    while(!bfs.empty()){
      curr_idx = bfs.front();
      x = curr_idx % width_;
      y = curr_idx / width_;
      bfs.pop();

      if(canTravel(x, y, 0)){
        if(prev_cell[curr_idx + 1] == -1){
          bfs.push(curr_idx + 1);
          prev_cell[curr_idx + 1] = curr_idx;
          distance[curr_idx + 1] = distance[curr_idx] + 1;
        }
      }
      if(canTravel(x, y, 1)){
        if(prev_cell[curr_idx + width_] == -1){
          bfs.push(curr_idx + width_);
          prev_cell[curr_idx + width_] = curr_idx;
          distance[curr_idx + width_] = distance[curr_idx] + 1;
        }
      }
      if(canTravel(x, y, 2)){
        if(prev_cell[curr_idx - 1] == -1){
          bfs.push(curr_idx - 1);
          prev_cell[curr_idx - 1] = curr_idx;
          distance[curr_idx - 1] = distance[curr_idx] + 1;
        }
      }
      if(canTravel(x, y, 3)){
        if(prev_cell[curr_idx - width_] == -1){
          bfs.push(curr_idx - width_);
          prev_cell[curr_idx - width_] = curr_idx;
          distance[curr_idx - width_] = distance[curr_idx] + 1;
        }
      }
    }
    int longest_path = width_ * (height_ - 1);
    for(int k = 0; k < width_; k++){
      if(distance[width_ * (height_ - 1) + k] > distance[longest_path]){
        longest_path = width_ * (height_ - 1) + k;
      }
    }
    destination = longest_path;
    vector<int> solution;
    curr_idx = destination; //uses curr_idx again
    while(curr_idx != 0){
      if(prev_cell[curr_idx] == curr_idx - 1){
        solution.push_back(0);
      }
      if(prev_cell[curr_idx] == curr_idx - width_){
        solution.push_back(1);
      }
      if(prev_cell[curr_idx] == curr_idx + 1){
        solution.push_back(2);
      }
      if(prev_cell[curr_idx] == curr_idx + width_){
        solution.push_back(3);
      }
      curr_idx = prev_cell[curr_idx];
    }
    reverse(solution.begin(), solution.end());

  return solution;
}



PNG* SquareMaze::drawMaze() const{
  int canvas_width = width_ * 10 + 1;
  int canvas_height = height_ * 10 + 1;
  PNG* canvas = new PNG(canvas_width, canvas_height);
  //Blacken the entire topmost row and leftmost column of pixels
  for(int y = 0; y < canvas_height; y++){
    HSLAPixel& p = canvas->getPixel(0, y);
    p.l = 0;  //Blacken
  }
  for(int x = 10; x < canvas_width; x++){
    HSLAPixel& p = canvas->getPixel(x, 0);
    p.l = 0;  //Blacken
  }

  for(int x = 0; x < width_; x++){
    for(int y = 0; y < height_; y++){
      if(rightWalls[y * width_ + x]){
        //blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = canvas->getPixel((x + 1) * 10, y * 10 + k);
          p.l = 0;  //Blacken
        }
      }
      if(downWalls[y * width_ + x]){
        //blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = canvas->getPixel(x * 10 + k, (y + 1) * 10);
          p.l = 0;  //Blacken
        }
      }
    }
  }
  return canvas;
}


PNG* SquareMaze::drawMazeWithSolution(){
  PNG* canvas = drawMaze();
  vector<int> solution = solveMaze();
  int x = 5;
  int y = 5;

  //whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
  int destinationX = destination % width_;
  int destinationY = destination / height_;
  for(int k = 1; k <= 9; k++){
    HSLAPixel& p = canvas->getPixel(destinationX * 10 + k, (destinationY + 1) * 10);
    p.l = 1;
  }
  for(size_t i = 0; i < solution.size(); i++){
    switch (solution[i]) {
      case 0:
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = canvas->getPixel(x + k, y);
          p.h = 0;
          p.s = 1;
          p.l = 0.5;
          p.a = 1;
        }
        x += 10;
        break;

      case 1:
      for(int k = 0; k <= 10; k++){
        HSLAPixel& p = canvas->getPixel(x, y + k);
        p.h = 0;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
        y += 10;
        break;

      case 2:
      for(int k = 0; k <= 10; k++){
        HSLAPixel& p = canvas->getPixel(x - k, y);
        p.h = 0;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
        x -= 10;
        break;

      case 3:
      for(int k = 0; k <= 10; k++){
        HSLAPixel& p = canvas->getPixel(x, y - k);
        p.h = 0;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
        y -= 10;
        break;
    }
  }
  return canvas;
}

PNG* SquareMaze::drawCreativeMaze(){
  int canvas_width = width_ * 10 + 1;
  int canvas_height = height_ * 10 + 1;
  PNG* canvas = new PNG(canvas_width, canvas_height);
  for(int y = 0; y < int(canvas_height / 4); y++){
    HSLAPixel& p = canvas->getPixel(0, y);
    p.l = 0;  //Blacken
  }
  for(int y = 3 * int(canvas_height / 4); y < canvas_height; y++){
    HSLAPixel& p = canvas->getPixel(0, y);
    p.l = 0;  //Blacken
  }
  for(int x = 10; x < canvas_width; x++){
    HSLAPixel& p = canvas->getPixel(x, 0);
    p.l = 0;  //Blacken
  }


  for(int x = 0; x < width_; x++){
    for(int y = 0; y < int(height_ / 4); y++){
          if(rightWalls[y * width_ + x]){
            //blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10
            for(int k = 0; k <= 10; k++){
              HSLAPixel& p = canvas->getPixel((x + 1) * 10, y * 10 + k);
              p.h = 240;
              p.s = 1;
              p.l = 0.5;  //Blue
              p.a = 1;
            }
          }
          if(downWalls[y * width_ + x]){
            //blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10
            for(int k = 0; k <= 10; k++){
              HSLAPixel& p = canvas->getPixel(x * 10 + k, (y + 1) * 10);
              p.h = 15;
              p.s = 1;
              p.l = 0.5;  //Orange
              p.a = 1;
            }
          }
    }
    for(int y = 3 * int(height_ / 4); y < height_; y++){
          if(rightWalls[y * width_ + x]){
            //blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10
            for(int k = 0; k <= 10; k++){
              HSLAPixel& p = canvas->getPixel((x + 1) * 10, y * 10 + k);
              p.h = 15;
              p.s = 1;
              p.l = 0.5;  //Orange
              p.a = 1;
            }
          }
          if(downWalls[y * width_ + x]){
            //blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10
            for(int k = 0; k <= 10; k++){
              HSLAPixel& p = canvas->getPixel(x * 10 + k, (y + 1) * 10);
              p.h = 240;
              p.s = 1;
              p.l = 0.5;  //Blue
              p.a = 1;
            }
          }
    }
  }





  for(int x = int(width_ / 3); x < 2 * int(width_ / 3); x++){
    for(int y = int(height_ / 4); y < 3 * int(height_ / 4); y++){
      if(rightWalls[y * width_ + x]){
        //blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = canvas->getPixel((x + 1) * 10, y * 10 + k);
          p.h = 15;
          p.s = 1;
          p.l = 0.5;  //Orange
          p.a = 1;
        }
      }
      if(downWalls[y * width_ + x]){
        //blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = canvas->getPixel(x * 10 + k, (y + 1) * 10);
          p.h = 240;
          p.s = 1;
          p.l = 0.5;  //Blue
          p.a = 1;
        }
      }
    }
  }


  return canvas;
}
