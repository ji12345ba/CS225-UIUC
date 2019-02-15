#include "../cs225/catch/catch.hpp"

#include "../Graph.h"
#include "../Edge.h"
#include "../Vertex.h"


Graph<Vertex, Edge> createTestGraph() {
  /*
         _ b   /--------- h
        /  | _/           |
      a -- c -- e    f -- g
        \_   _/
           d
  */

  Graph<Vertex, Edge> g;
  g.insertVertex("a");
  g.insertVertex("b");
  g.insertVertex("c");
  g.insertVertex("d");
  g.insertVertex("e");
  g.insertVertex("f");
  g.insertVertex("g");
  g.insertVertex("h");

  // Edges on `a`:
  g.insertEdge("a", "b");
  g.insertEdge("a", "c");
  g.insertEdge("a", "d");

  // Additional edges on `b`:
  g.insertEdge("b", "c");

  // Additional edges on `c`:
  g.insertEdge("c", "e");
  g.insertEdge("c", "h");

  // Additional edges on `d`:
  g.insertEdge("d", "e");

  // Additional edges on `e`: (none)

  // Additional edges on `f`:
  g.insertEdge("f", "g");

  // Additional edges on `g`:
  g.insertEdge("g", "h");

  // Additional edges on `h`: (none)

  return g;
}



TEST_CASE("Graph::size returns the vertex count", "[weight=1]") {
  Graph<Vertex, Edge> g;

  g.insertVertex("a");
  g.insertVertex("b");
  REQUIRE( g.size() == 2 );

  g.insertVertex("c");
  g.insertVertex("d");
  g.insertVertex("e");
  REQUIRE( g.size() == 5 );

}

TEST_CASE("Graph::edges::size returns the edge count", "[weight=1]") {
  Graph<Vertex, Edge> g;

  g.insertVertex("a");
  g.insertVertex("b");
  g.insertVertex("c");
  g.insertVertex("d");
  g.insertVertex("e");

  REQUIRE( g.edges() == 0 );

  g.insertEdge("a", "c");
  g.insertEdge("b", "d");
  g.insertEdge("a", "e");

  REQUIRE( g.edges() == 3 );

  //modified
  g.removeEdge("a", "c");
  REQUIRE(g.edges() == 2);
  g.removeVertex("d");
  REQUIRE(g.size() == 4);
}

TEST_CASE("Eight-vertex test graph has correct properties", "[weight=1]") {
  Graph<Vertex, Edge> g = createTestGraph();
  REQUIRE( g.size() == 8 );
  REQUIRE( g.edges() == 9 );
}

TEST_CASE("Graph::incidentEdges contains incident edges (origin-only test)", "[weight=1]") {
  Graph<Vertex, Edge> g = createTestGraph();
  REQUIRE( g.incidentEdges("a").size() == 3 );
}

TEST_CASE("Graph::incidentEdges contains incident edges (dest-only test)", "[weight=1]") {
  Graph<Vertex, Edge> g = createTestGraph();
  REQUIRE( g.incidentEdges("h").size() == 2 );
}

TEST_CASE("Graph::incidentEdges contains incident edges (hybrid test)", "[weight=1]") {
  Graph<Vertex, Edge> g = createTestGraph();
  REQUIRE( g.incidentEdges("d").size() == 2 );
}

TEST_CASE("Graph::isAdjacent is correct (same-order test)", "[weight=1]") {
  Graph<Vertex, Edge> g = createTestGraph();
  REQUIRE( g.isAdjacent("a", "d") == true );
}

TEST_CASE("Graph::isAdjacent is correct (opposite-order test)", "[weight=1]") {
  Graph<Vertex, Edge> g = createTestGraph();
  REQUIRE( g.isAdjacent("a", "d") == true );
}
