#include "abstractsyntaxtree.h"

AbstractSyntaxTree::AbstractSyntaxTree(typename BinaryTree<std::string>::Node* node) 
    : BinaryTree<std::string>(node)
{ /* nothing */
}
