#include "../cs225/catch/catch.hpp"

#include "../Graph.h"
#include "../DirectedEdge.h"
#include "../Vertex.h"

TEST_CASE("Graphs with `DirectedEdge`s have directed edges", "[weight=1]") {
  Graph<Vertex, DirectedEdge> g;
  g.insertVertex("a");
  g.insertVertex("b");
  g.insertEdge("a", "b");
  
  REQUIRE( g.incidentEdges("a").front().get().directed() == true );
}

TEST_CASE("Graphs::isAdjacent with `DirectedEdge`s finds the directed edge", "[weight=1]") {
  Graph<Vertex, DirectedEdge> g;
  Vertex a = g.insertVertex("a");
  Vertex b = g.insertVertex("b");
  g.insertEdge("a", "b");
  
  REQUIRE( g.isAdjacent(a, b) == true );
}

TEST_CASE("Graphs::isAdjacent with `DirectedEdge`s does not find the directed edge", "[weight=1]") {
  Graph<Vertex, DirectedEdge> g;
  Vertex a = g.insertVertex("a");
  Vertex b = g.insertVertex("b");
  g.insertEdge("a", "b");
  
  REQUIRE( g.isAdjacent(b, a) == false );
}
