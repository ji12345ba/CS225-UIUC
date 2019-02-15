/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <iostream>
using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if(first[curDim] < second[curDim]){
       return true;
     }
     else if(first[curDim] > second[curDim]){
       return false;
     }
     else{  //there is a tie
       return first < second;
     }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double current_squared_distance = 0.0;
     double potential_squared_distance = 0.0;

     for(int i = 0; i < Dim; i++){
       current_squared_distance += (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
     }
     for(int i = 0; i < Dim; i++){
       potential_squared_distance += (target[i] - potential[i]) * (target[i] - potential[i]);
     }

     if(potential_squared_distance < current_squared_distance){
       return true;
     }
     else if(potential_squared_distance > current_squared_distance){
       return false;
     }
     else{  //there is a tie
       return potential < currentBest;
     }
}
















template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

     //handle the case that the vector has no Point in it.
     if(newPoints.empty()){
       root = NULL;
       size = 0;
     }
     else{
       //copying the input list of points into a points vector
       vector<Point<Dim>> points = newPoints;
       size = 0;
       constructKD(points, 0, points.size() - 1, 0, root);
     }

}


template <int Dim>
void KDTree<Dim>::constructKD(vector<Point<Dim>>& newPoints, int left, int right,
                              int dimension, KDTreeNode*& subroot)
                              //subroot must be passed by reference!!
                              //subroot must be passed by reference!!
                              //subroot must be passed by reference!!
//You would want to pass a pointer by reference
//if you have a need to modify the pointer
//rather than the object that the pointer is pointing to.
{
  if(left > right){ //base case
    return;
  }
  size_t median = (left + right) / 2;

  Point<Dim> temp = select(newPoints, left, right, median, dimension);
  subroot = new KDTreeNode(temp);
  size++;
  if(subroot == NULL){cout << "subroot is null\n"<< endl;}
  constructKD(newPoints, left, median - 1, (dimension + 1) % Dim, subroot->left);
  constructKD(newPoints, median + 1, right, (dimension + 1) % Dim, subroot->right);
}


//group a list (ranging from indices left to right) into two parts:
//those less than a certain element, and those greater than or equal to the element.
template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& list, int left, int right, size_t pivotIndex, int dimension){
  Point<Dim> pivotValue = list[pivotIndex];
  swap(list[pivotIndex], list[right]);  // Move pivot to end
  size_t storeIndex = left;
  for(int i = left; i < right; i++){
    if(smallerDimVal(list[i], pivotValue, dimension)){
      swap(list[storeIndex], list[i]);
      storeIndex++;
    }
  }
  swap(list[right], list[storeIndex]);  // Move pivot to its final place
  return storeIndex;
}


// Returns the k-th smallest element of list within left..right inclusive
template <int Dim>
Point<Dim> KDTree<Dim>::select(vector<Point<Dim>>& list, int left, int right, size_t k, int dimension){
  if(left == right){     // If the list contains only one element,
    return list[left];  // return that element
  }
  size_t pivotIndex = (left + right) / 2;    // select a pivotIndex between left and right
  pivotIndex = partition(list, left, right, pivotIndex, dimension);
  // The pivot is in its final sorted position
  if (k == pivotIndex){
    return list[k];
  }
  else if(k < pivotIndex){
    return select(list, left, pivotIndex - 1, k, dimension);
  }
  else{
    return select(list, pivotIndex + 1, right, k, dimension);
  }
}














template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   _copy(root, other->root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  _delete(root);
  _copy(root, rhs->root);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   _delete(root);
}

template <int Dim>
void KDTree<Dim>::_copy(KDTreeNode*& curr_node, KDTreeNode*& other){
  if(other == NULL){
    return;
  }
  curr_node = new KDTreeNode(other->point);
  _copy(curr_node->left, other->left);
  _copy(curr_node->right, other->right);
}

template <int Dim>
void KDTree<Dim>::_delete(KDTreeNode*& subroot){
  if(subroot == NULL){
    return;
  }
  _delete(subroot->left);
  _delete(subroot->right);
  delete subroot;
}



























template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> currentBest = root->point;
    Point<Dim> temp = query;  //To prevent error
    findNN(root, currentBest, temp, 0);
    return currentBest;
}
//helper function for findNearestNeighbor
template <int Dim>
void KDTree<Dim>::findNN(KDTreeNode* curr_node, Point<Dim> &currentBest,
                         Point<Dim> &query, int dimension) const{

    if(curr_node == NULL){
      return;
    }
    KDTreeNode* next_node;
    KDTreeNode* other_node;
    if(smallerDimVal(curr_node->point, query, dimension)){
      next_node = curr_node->right;
      other_node = curr_node->left;
    }
    else{
      next_node = curr_node->left;
      other_node = curr_node->right;
    }
    findNN(next_node, currentBest, query, (dimension + 1) % Dim);


    if(shouldReplace(query, currentBest, curr_node->point)){
      currentBest = curr_node->point;
    }


    double radius = 0.0;
    for(int i = 0; i < Dim; i++){
      radius += (currentBest[i] - query[i]) * (currentBest[i] - query[i]);
    }
    double distance =  (curr_node->point[dimension] - query[dimension])
                        * (curr_node->point[dimension] - query[dimension]);
    if(radius >= distance){
      findNN(other_node, currentBest, query, (dimension + 1) % Dim);
    }
}
