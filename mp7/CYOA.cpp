#include "CYOA.h"
#include "Graph.h"
#include "DirectedEdge.h"
#include "dirent.h"

#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
#include <unordered_map>
#include <vector>

CYOA::GraphFile CYOA::_processFile(std::string file, std::string key) {
  CYOA::GraphFile gf;
  gf.key = key;

  std::string edgeName = "";
  std::string content = "";

  // Read the file contents:
  // @see https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
  std::ifstream input(file);
  for (std::string line; getline( input, line ); ) {
    // Skip empty lines:
    trim(line);
    if (line.length() == 0) { continue; }

    // Found an edge marker:
    if (line.at(0) == '#') {
      // New edge found:
      if (edgeName == "") { gf.content = string(content); }
      else                { gf.edges[edgeName] = string(content); }

      // Update data:
      edgeName = line.substr(1);
      trim(edgeName);
      content = "";
    } else {
      // Otherwise, add to content:
      content += " " + line;
    }
  }

  // Last edge:
  if (edgeName == "") { gf.content = string(content); }
  else                { gf.edges[edgeName] = string(content); }

  return gf;
}


Graph<Vertex, DirectedEdge> CYOA::load(std::string path) {
  //
  // Part 1: Read the graph files
  //
  std::vector<GraphFile> gfs;

  // Grab every file in the `path`:
  // @see https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir(path.c_str())) != NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir(dir)) != NULL) {
      std::string fileName(ent->d_name);
      if (fileName == "." || fileName == "..") { continue; }

      std::string fullPath = path + fileName;
      GraphFile gf = _processFile(fullPath, fileName.substr(0, fileName.length() - 3));
      gfs.push_back(gf);
    }
    closedir(dir);
  } else {
    /* could not open directory */
    std::cerr << "Unable to open " << path << std::endl;
  }


  //
  // Part 2: Construct the graph
  //
  Graph<Vertex, DirectedEdge> g;

  // Add every vertex:
  for (const GraphFile & gf : gfs) {
    Vertex & v = g.insertVertex(gf.key);
    v["content"] = gf.content;
  }

  // Add edges:
  for (const GraphFile & gf : gfs) {
    for (auto & it : gf.edges) {
      std::string edgeKey = it.first;
      std::string edgeContent = it.second;

      Edge & e = g.insertEdge( gf.key, edgeKey );
      e["content"] = edgeContent;
    }
  }

  return g;
};