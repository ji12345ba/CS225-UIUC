#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <list>

/**
* @return The edges of the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::edges() const {
  return edgeList.size();
}


/**
* Removes the Vertex which the given key
* @param key The key of the Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const V & v) {
  return removeVertex(v.key());
}


/**
* Inserts an Edge into the Graph
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const std::string key1, const std::string key2) {
  return insertEdge( vertexMap.at(key1), vertexMap.at(key2) );
}


/**
* Removes an Edge from the adjacency list.
* Hint: Maybe we can use our iterator removeEdge?
* @param v1 The source Vertex
* @param v2 The destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const V & v1, const V & v2) {
  removeEdge( v1.key(), v2.key() );
}


/**
* Removes the given Edge from the Graph.
* Hint: Use std::find
* @param e The Edge you want to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const Edge & e) {
  edgeListIter it = std::find(edgeList.begin(), edgeList.end(), e);
  removeEdge(it);
}


/**
* @param v The Vertex that you would like to find the incident edges for
* @return The list edges (by reference) that are adjacent to the given v
(The incoming edges).
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const V & v) const {
  return incidentEdges( v.key() );
}


/**
 * Return whether the two vertices are adjacent to one another
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const V & v1, const V & v2) const {
  return isAdjacent( v1.key(), v2.key() );
}
