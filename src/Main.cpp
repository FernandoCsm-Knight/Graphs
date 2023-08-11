#include <iostream>

#include "lib/ArrayList.hpp"
#include "lib/helpers/KeyValue.hpp"
#include "lib/LinkedList.hpp"
#include "lib/Map.hpp"
#include "lib/RBTree.hpp"
#include "lib/helpers/Edge.hpp"
#include "lib/helpers/Vertex.hpp"
#include "lib/Graph.hpp"

int main() {
    Graph<std::string> graph;

    graph.addEdge("A", "B");
    graph.addEdge("A", "C");
    graph.addEdge("B", "C");
    graph.addEdge("B", "D");
    graph.addEdge("D", "C");
    graph.addVertex("E");
    graph.addVertex("F");
    graph.addVertex("G");
    graph.addVertex("H");
    graph.removeEdge("D", "C");
    graph.removeVertex("E");

    Map<Vertex<std::string>, LinkedList<Vertex<std::string>>> adj = graph.adjacentList();
    
    std::cout << adj << std::endl;
    std::cout << graph << std::endl;
    return 0;
}
