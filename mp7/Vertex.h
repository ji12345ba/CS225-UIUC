#pragma once

#include <string>
#include <unordered_map>
#include <iostream>
using std::string;

class Vertex {
  public:
    Vertex(string key) : key_(key) { }

    /**
     * Returns the `key` of the Vertex.  Every Vertex must have a unique key.
     */
    string key() const {
      return key_;
    }

    /**
     * Returns `true` if the Vertex has the same `key` as `other`.
     */
    bool operator==(const Vertex & other) const {
      return key_ == other.key_;
    }

    /**
     * Add, modify, or read a key/value propoerty of the Vertex.
     */
    string & operator[](const string & value) {
      return properties_[value];
    }

    /**
     * Prints out the Vertex in a human-readable format to `out`
     */
    friend std::ostream & operator<<(std::ostream & out, const Vertex & v) {
      out << "Vertex(" << v.key() << ")";

      if (v.properties_.size() > 0) {
        out << " {";
        for (auto & pair : v.properties_) {
          out << pair.first << "=\"" << pair.second << "\"";
        }
        out << "}";
      }

      return out;
    }

  private:
    string key_;
    std::unordered_map<string, string> properties_;
};

// Inject std::hash<Vertex> to allow Vertex to be used as a key to a hash table:
namespace std {
  template<> 
  struct hash<Vertex> {
    std::size_t operator()(const Vertex & v) const noexcept {
      std::hash<std::string> hf;
      return hf(v.key());
    }
  };

  template<> 
  struct hash<const Vertex> {
    std::size_t operator()(const Vertex & v) const noexcept {
      std::hash<std::string> hf;
      return hf(v.key());
    }
  };
}
