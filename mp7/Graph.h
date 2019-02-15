#pragma once

#include <list>
#include <unordered_map>
#include <string>
#include <algorithm>

#include "Edge.h"
#include "Vertex.h"

#include <iostream>

template <class V = Vertex, class E = Edge>
class Graph {
  typedef std::reference_wrapper<E> E_byRef;
  typedef std::reference_wrapper<V> V_byRef;
  typedef typename std::list<E_byRef>::iterator edgeListIter;

  public:
    // Graph properties:
    unsigned int size() const;
    unsigned int edges() const;
    unsigned int degree(const V & v) const;

    // Vertex modification:
    V & insertVertex(std::string key);

    void removeVertex(const std::string & key);
    void removeVertex(const V & v);

    // Edge modification:
    E & insertEdge(const std::string key1, const std::string key2);
    E & insertEdge(const V & v1, const V & v2);

    void removeEdge(const std::string key1, const std::string key2);
    void removeEdge(const V & v1, const V & v2);
    void removeEdge(const Edge & e);
    void removeEdge(const edgeListIter & it);

    // Graph structure:
    const std::list<E_byRef> incidentEdges(const std::string key) const;
    const std::list<E_byRef> incidentEdges(const V & v) const;

    bool isAdjacent(const std::string key1, const std::string key2) const;
    bool isAdjacent(const V & v1, const V & v2) const;

    // Graph algorithm:
    std::list<std::string> shortestPath(const std::string start, const std::string end);

    // stream<< printer
    friend std::ostream & operator<<(std::ostream & out, const Graph<V,E> & g) {
      out << "Graph(|V|=" << g.size() << ", |E|=" << g.edges() << "):" << std::endl;

      for (const std::pair<std::string, std::list<edgeListIter>> & pair : g.adjList) {
        const std::string & key = pair.first;
        const std::list<edgeListIter> & edges = pair.second;
        const V & v = g.vertexMap.at(key);

        out << "  " << v << std::endl;
        for (const edgeListIter & it : edges) {
          const E & e = *it;
          out << "    " << *it << std::endl;
        }
      }

      return out;
    }

  private:
    std::list<E_byRef> edgeList;
    std::unordered_map<std::string, V &> vertexMap;
    std::unordered_map<std::string, std::list<edgeListIter>> adjList;
};

#include "Graph-given.hpp"
#include "Graph.hpp"
#include "Graph2.hpp"
