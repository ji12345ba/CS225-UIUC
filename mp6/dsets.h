/* Your code here! */
#pragma once

#include <vector>
using namespace std;
class DisjointSets{
  //the default compiler-supplied Big Three will work flawlessly
public:
  void addelements(int num);
  int find(int elem);
  void setunion(int a, int b);
  int size(int elem);

  vector<int> elements;
};
