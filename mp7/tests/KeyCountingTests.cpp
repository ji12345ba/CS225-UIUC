#include "../cs225/catch/catch.hpp"

#include "../Graph.h"
#include "../Edge.h"
#include "../Vertex.h"
#include "KeyCountingVertex.hpp"

#include <vector>

TEST_CASE("Graph::isAdjacent runs in min(deg(v1), deg(v2))", "[weight=5]") {
  Graph<KeyCountingVertex, Edge> g;
  std::vector<KeyCountingVertex> aX;

  //    a <-> [a{0-100}]
  KeyCountingVertex a = g.insertVertex("a");
  for (int i = 0; i < 100; i++) {
    KeyCountingVertex v = g.insertVertex("a" + std::to_string(i));
    g.insertEdge(a, v);
    aX.push_back(v);
  }

  // Must have used a hash table to insert Vertex a:
  REQUIRE( a.keyAccesses() > 0 );
  a.resetAccessCount();

  // Find other verticies:
  KeyCountingVertex a0 = aX[0];
  KeyCountingVertex a40 = aX[40];
  KeyCountingVertex a80 = aX[80];

  // [Lower Degree], [Higher Degree]
  g.isAdjacent(a, a0);
  REQUIRE( a.keyAccesses() > 0 );  // Must have an access.
  REQUIRE( a.keyAccesses() < 3 );  // No more than 3 accesses /degree==1
  a.resetAccessCount();

  g.isAdjacent(a, a40);
  REQUIRE( a.keyAccesses() < 3 );
  a.resetAccessCount();

  // [Higher Degree], [Lower Degree]
  g.isAdjacent(a40, a);
  REQUIRE( a.keyAccesses() < 3 );
  a.resetAccessCount();

  g.isAdjacent(a80, a);
  REQUIRE( a.keyAccesses() < 3 );
  a.resetAccessCount();
}