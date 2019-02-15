#include "../cs225/catch/catch.hpp"

#include "../graph.h"
#include "../edge.h"
#include "../NetworkFlow.h"

#include <iostream>


TEST_CASE("Graph a - 10 -> b  has flow of 10.", "[valgrind][weight=1]") {
  Graph g = Graph(true,true);

  g.insertEdge("a","b");
  g.setEdgeWeight("a","b",10);

  NetworkFlow n(g,"a","b");

  Graph f = n.calculateFlow();

  REQUIRE( n.getMaxFlow() == 10 );
}

TEST_CASE("Testing flow through two pipes", "[valgrind][weight=1]") {
  Graph g = Graph(true,true);

  g.insertEdge("a","b");
  g.setEdgeWeight("a","b",10);
  g.insertEdge("b","c");
  g.setEdgeWeight("b","c",5);
  g.insertEdge("a","c");
  g.setEdgeWeight("a","c",3);

  NetworkFlow n(g,"a","c");

  Graph f = n.calculateFlow();

  REQUIRE( n.getMaxFlow() == 8 );
}

TEST_CASE("Testing simple backflow", "[valgrind][weight=1]") {
  Graph g = Graph(true,true);

  g.insertEdge("a","b");
  g.setEdgeWeight("a","b",10);
  g.insertEdge("a","c");
  g.setEdgeWeight("a","c",10);
  g.insertEdge("b","c");
  g.setEdgeWeight("b","c",5);
  g.insertEdge("b","d");
  g.setEdgeWeight("b","d",10);
  g.insertEdge("c","d");
  g.setEdgeWeight("c","d",10);

  NetworkFlow n(g,"a","d");

  Graph f = n.calculateFlow();

  REQUIRE( n.getMaxFlow() == 20 );
}

TEST_CASE("Testing full pipe usage", "[valgrind][weight=1]") {
  Graph g = Graph(true,true);

  g.insertEdge("a","b");
  g.setEdgeWeight("a","b",9);
  g.insertEdge("a","d");
  g.setEdgeWeight("a","d",4);
  g.insertEdge("b","c");
  g.setEdgeWeight("b","c",8);
  g.insertEdge("c","d");
  g.setEdgeWeight("c","d",5);
  g.insertEdge("d","e");
  g.setEdgeWeight("d","e",7);
  g.insertEdge("c","f");
  g.setEdgeWeight("c","f",3);
  g.insertEdge("e","f");
  g.setEdgeWeight("e","f",8);

  NetworkFlow n(g,"a","f");

  Graph f = n.calculateFlow();

  REQUIRE( n.getMaxFlow() == 10 );
}

TEST_CASE("Testing 3 x 3 plumbing", "[valgrind][weight=1]") {
  Graph g = Graph(true,true);

  g.insertEdge("a","b");
  g.setEdgeWeight("a","b",4);
  g.insertEdge("b","c");
  g.setEdgeWeight("b","c",5);

  g.insertEdge("d","e");
  g.setEdgeWeight("d","e",3);
  g.insertEdge("e","f");
  g.setEdgeWeight("e","f",5);

  g.insertEdge("g","h");
  g.setEdgeWeight("g","h",1);
  g.insertEdge("h","i");
  g.setEdgeWeight("h","i",5);

  g.insertEdge("a","d");
  g.setEdgeWeight("a","d",8);
  g.insertEdge("b","e");
  g.setEdgeWeight("b","e",5);
  g.insertEdge("c","f");
  g.setEdgeWeight("c","f",3);

  g.insertEdge("d","g");
  g.setEdgeWeight("d","g",4);
  g.insertEdge("e","h");
  g.setEdgeWeight("e","h",11);
  g.insertEdge("f","i");
  g.setEdgeWeight("f","i",7);

  NetworkFlow n(g,"a","i");

  Graph f = n.calculateFlow();

  REQUIRE( n.getMaxFlow() == 8 );
}
