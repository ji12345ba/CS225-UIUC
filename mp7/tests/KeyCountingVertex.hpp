#pragma once

#include "../Vertex.h"

#include <string>

class KeyCountingVertex : public Vertex {
  public:
    KeyCountingVertex(const std::string key = "") : Vertex(key) {
        keyAccess_ct_ = 0;
    };

    string key() const {
      keyAccess_ct_++;
      return Vertex::key();
    }

    bool operator==(const KeyCountingVertex & other) const {
      return key() == other.key();
    }

    unsigned int keyAccesses() {
      return keyAccess_ct_;
    }

    void resetAccessCount() {
      keyAccess_ct_ = 0;
    }

  private:
    mutable unsigned int keyAccess_ct_;
};


// Inject std::hash<KeyCountingVertex> to allow Vertex to be used as a key to a hash table:
namespace std {
  template<> 
  struct hash<KeyCountingVertex> {
    std::size_t operator()(const KeyCountingVertex & v) const noexcept {
      std::hash<std::string> hf;
      return hf(v.key());
    }
  };
}