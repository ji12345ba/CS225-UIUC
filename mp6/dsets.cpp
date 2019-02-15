/* Your code here! */
#include "dsets.h"
using namespace std;

//Creates n unconnected root nodes at the end of the vector.
void DisjointSets::addelements(int num){
  for(int i = 1; i <= num; i++){
    elements.push_back(-1);
  }
  return;
}

//return the index of the root of the up-tree in which the parameter element resides.
//COMPRESS PATHS:
//update the parent as we unwinds the recursion
int DisjointSets::find(int elem){
  if(elements[elem] < 0){
    return elem;
  }
  else{
    elements[elem] = find(elements[elem]);
    return elements[elem];
  }
}

void DisjointSets::setunion(int a, int b){
  int rootA = find(a);
  int rootB = find(b);
  //if they are already in union
  //without this line it passes catch tests but ./testdsets will segfault
  if(rootA == rootB){
    return;
  }

  if(rootA < rootB){  //if B is a smaller set than A
    elements[rootA] = elements[rootA] + elements[rootB];
    elements[rootB] = rootA;
  }
  else{
    elements[rootB] = elements[rootA] + elements[rootB];
    elements[rootA] = rootB;
  }

}

int DisjointSets::size(int elem){
  return -1 * elements[find(elem)];
}
