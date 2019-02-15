#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <unordered_map>
#include <iostream>
/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  std::list<std::string> path;
  std::queue<string> bfs;
  std::unordered_map<string, string> predecessor;
  std::unordered_map<string, bool> visited;
  for(auto it = vertexMap.begin(); it != vertexMap.end(); it++){
    predecessor[it->first] = "none";
  }
  bfs.push(start);
  predecessor[start] = "start";

  while(!bfs.empty()){
    string temp = bfs.front();
    bfs.pop();
    //add temp's neighbor
    for(auto it = vertexMap.begin(); it != vertexMap.end(); it++){
      //write a new isNeighbor function that works slightly different from isAdjacent
      bool isNeighbor = false;
      for(edgeListIter edgeit : adjList.at(temp)){
        if((*edgeit).get().source().key() == it->first ||
           (*edgeit).get().dest().key() == it->first){
          isNeighbor = true;
        }
      }

      if(isNeighbor && predecessor[it->first] == "none"){
        bfs.push(it->first);
        predecessor[it->first] = temp;
      }
    }
  }

  string temp2 = end;
  path.push_back(end);
  while(temp2 != start){
    path.push_back(predecessor[temp2]);
    temp2 = predecessor[temp2];
  }
  std::reverse(path.begin(),path.end());
  
  return path;
}
