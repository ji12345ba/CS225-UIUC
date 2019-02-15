#include "../cs225/catch/catch.hpp"

#include "../Graph.h"
#include "../DirectedEdge.h"
#include "../Vertex.h"

Graph<Vertex, Edge> createTestGraph_shortestPath() {
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

TEST_CASE("Graph::shortestPath finds a shortest path with two vertices", "[weight=2]") {
  Graph<Vertex, Edge> g = createTestGraph_shortestPath();

  std::list<std::string> path = g.shortestPath("d", "e");
  
  REQUIRE( path.size() == 2 );
  REQUIRE( path.front() == "d" );
  REQUIRE( path.back() == "e" );
}

TEST_CASE("Graph::shortestPath finds a shortest path with three vertices", "[weight=2]") {
  Graph<Vertex, Edge> g = createTestGraph_shortestPath();

  std::list<std::string> path = g.shortestPath("d", "b");  
  REQUIRE( path.size() == 3 );
}

TEST_CASE("Graph::shortestPath finds a shortest path with four vertices", "[weight=2]") {
  Graph<Vertex, Edge> g = createTestGraph_shortestPath();

  std::list<std::string> path = g.shortestPath("a", "g");
  // a -> c -> h -> g
  REQUIRE( path.size() == 4 );
}

TEST_CASE("Graph::shortestPath finds a shortest path with four vertices (reverse)", "[weight=2]") {
  Graph<Vertex, Edge> g = createTestGraph_shortestPath();

  std::list<std::string> path = g.shortestPath("g", "a");
  // g -> h -> c -> a
  REQUIRE( path.size() == 4 );
}

TEST_CASE("Graph::shortestPath finds a shortest path with five vertices", "[weight=2]") {
  Graph<Vertex, Edge> g = createTestGraph_shortestPath();

  std::list<std::string> path = g.shortestPath("f", "a");
  // f -> g -> h -> c -> a
  REQUIRE( path.size() == 5 );
}

TEST_CASE("Graph::shortestPath finds a shortest path with six vertices", "[weight=2]") {
  Graph<Vertex, Edge> g = createTestGraph_shortestPath();

  std::list<std::string> path = g.shortestPath("f", "d");
  // f -> g -> h -> c -> [a/e] -> b
  REQUIRE( path.size() == 6 );
}
