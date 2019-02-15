#include "abstractsyntaxtree.h"
using namespace std;
/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    return eval(root);
}
double AbstractSyntaxTree::eval(Node* subRoot)const {
  if(subRoot == NULL){
    return -1;
  }
  else if(subRoot->elem == "+"){
    return eval(subRoot->left) + eval(subRoot->right);
  }
  else if(subRoot->elem == "-"){
    return eval(subRoot->left) - eval(subRoot->right);
  }
  else if(subRoot->elem == "*"){
    return eval(subRoot->left) * eval(subRoot->right);
  }
  else if(subRoot->elem == "/"){
    return eval(subRoot->left) / eval(subRoot->right);
  }
  else{
    return std::stod(subRoot->elem);
  }
}
