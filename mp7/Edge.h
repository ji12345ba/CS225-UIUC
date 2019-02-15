#pragma once

#include "Vertex.h"
#include <iostream>

class Edge {
  public:
    Edge(const Vertex & source, const Vertex & dest, double weight = 1) :
      source_(source), dest_(dest), weight_(weight) { }
    virtual ~Edge() { }

    /**
     * Returns the source Vertex of the Edge.
     */
    const Vertex & source() const { return source_; }

    /**
     * Returns the destination Vertex of the Edge.
     */
    const Vertex & dest() const { return dest_; }

    /**
     * Returns the weight of the Edge.
     */
    double weight() const { return weight_; }

    /**
     * Returns `true` if the Edge is directed; otherwise `false`.
     */
    virtual bool directed() const { return false; }

    /**
     * Returns `true` if the Edge connects the same vertex endpoints
     * as the `other` Edge.  In an undirected graph, this function
     * returns `true` when the endpoints are swapped.
     */
    bool operator==(const Edge & other) const {
      if (directed() == true) {
        return (source_ == other.source_) && (dest_ == other.dest_);
      } else {
        return (
          ((source_ == other.source_) && (dest_ == other.dest_)) ||
          ((source_ == other.dest_) && (dest_ == other.source_))
        );
      }
    }

    /**
     * Add, modify, or read a key/value propoerty of the Edge.
     */
    string & operator[](const string & value) {
      return properties_[value];
    }

    /**
     * Prints out the Edge in a human-readable format to `out`
     */
    friend std::ostream & operator<<(std::ostream & out, const Edge & edge) {
      out << "Edge(" << edge.source().key();
      if (edge.directed()) { out << " -> "; }
      else                 { out << " <-> "; }
      out << edge.dest().key()  << ")";

      if (edge.properties_.size() > 0) {
        out << " {";
        for (auto & pair : edge.properties_) {
          out << pair.first << "=\"" << pair.second << "\"";
        }
        out << "}";
      }

      return out;      
    }

  private:
    const Vertex & source_;
    const Vertex & dest_;
    double weight_;
    std::unordered_map<string, string> properties_;
};

// Inject std::hash<Edge> to allow Edge to be used as a key to a hash table:
namespace std {
  template<> 
  struct hash<Edge> {
    std::size_t operator()(const Edge & e) const noexcept {
      std::hash<std::string> hf;

      if (e.directed()) {
        return hf( e.source().key() + "->" + e.dest().key() );
      } else {
        // Ensure lower key is first to ensure that if e1 == e2, then hf(e1) == hf(e2):
        if (e.source().key() < e.dest().key()) {
          return hf( e.source().key() + "->" + e.dest().key() );
        } else {
          return hf( e.dest().key() + "->" + e.source().key() );
        }
      }
    }
  };
}