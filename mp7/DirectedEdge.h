#pragma once

#include "Vertex.h"
#include "Edge.h"

class DirectedEdge : public Edge {
  public:
    DirectedEdge(const Vertex & source, const Vertex & dest, double weight = 1) :
      Edge(source, dest, weight) { };

    bool directed() const { return true; }
};