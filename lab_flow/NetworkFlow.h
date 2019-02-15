/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#pragma once

#include <vector>
#include <algorithm>

#include "graph.h"
#include "edge.h"

/**
 * Represents a algorithm to determine the maximum network flow of a graph.
 */
class NetworkFlow {
public:
  /**
   * Constructor to create a flow analyzer.
   *
   * @param startingGraph  The initial graph.
   * @param source  The source vertex.
   * @param sink    The sink vertex.
   */

  NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink);

  /**
   * Create an initial residual graph.
   *
   */

  /**
   * Find an augmenting path from the source to the sink.
   *
   * @returns A vector of the vertices from source to sink with greater than zero flow.
   *          Returns an empty vector if no such path exists.
   */

  bool findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path, std::set<Vertex> &visited);
  bool findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path);

  int pathCapacity(const std::vector<Vertex> & path) const;

  const Graph & calculateFlow();
  /**
   * Returns a constant reference to the state space graph.
   *
   * @returns A constant reference to the state space graph.
   */

  const Graph & getGraph() const;
  const Graph & getFlowGraph() const;
  const Graph & getResidualGraph() const;

  int getMaxFlow() const;

private:
  Graph & g_;
  Graph residual_;
  Graph flow_;

  Vertex source_;
  Vertex sink_;

  int maxFlow_;
};
