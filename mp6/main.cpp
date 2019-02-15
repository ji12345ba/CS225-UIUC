#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze s;
    s.makeMaze(100, 100);
    PNG* canvas = s.drawCreativeMaze();
    canvas->writeToFile("creative.png");
    cout << "creative maze created" << endl;
    return 0;
}
