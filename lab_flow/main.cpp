#include "NetworkFlow.h"
#include <vector>
#include <iostream>
#include "edge.h"

int main() {

  Graph g1 = Graph(true,true);

  g1.insertEdge("a","b");
  g1.setEdgeWeight("a","b",10);

  std::cout << "Input graph:" << std::endl;
  g1.print();

  NetworkFlow n1(g1,"a","b");

  Graph f = n1.calculateFlow();

  std::cout << "Flow for graph is " << n1.getMaxFlow() << std::endl;

  std::cout << "Flow graph is " << std::endl;

  n1.getFlowGraph().print();

  Graph g2 = Graph(true,true);

  g2.insertEdge("a","b");
  g2.insertEdge("b","c");
  g2.insertEdge("b","d");
  g2.insertEdge("a","c");
  g2.insertEdge("c","d");
  g2.setEdgeWeight("a","b",10);
  g2.setEdgeWeight("b","d",10);
  g2.setEdgeWeight("a","c",10);
  g2.setEdgeWeight("c","d",10);
  g2.setEdgeWeight("b","c",5);

  std::cout << "Input graph:" << std::endl;
  g2.print();

  NetworkFlow n2(g2,"a","d");

  f = n2.calculateFlow();

  std::cout << "Flow for graph is " << n2.getMaxFlow() << std::endl;

  std::cout << "Flow graph is " << std::endl;

  n2.getFlowGraph().print();

  return 0;
}
