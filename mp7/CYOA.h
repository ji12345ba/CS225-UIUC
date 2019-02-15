#pragma once

#include "Graph.h"
#include "DirectedEdge.h"
#include "dirent.h"

class CYOA {
public:
  Graph<Vertex, DirectedEdge> load(std::string path);

private:
  class GraphFile {
    public:
      std::string key;
      std::string content;
      std::unordered_map<std::string, std::string> edges;
  };

  GraphFile _processFile(std::string file, std::string key);


  // String ops:
  // @see https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
  // trim from start (in place)
  static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
      return !std::isspace(ch);
    }));
  }

  // trim from end (in place)
  static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
      return !std::isspace(ch);
    }).base(), s.end());
  }

  // trim from both ends (in place)
  static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
  }



};