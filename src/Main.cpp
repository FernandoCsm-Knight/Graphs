#include <iostream>

#include "lib/ArrayList.hpp"
#include "lib/helpers/Pair.hpp"
#include "lib/LinkedList.hpp"
#include "lib/Map.hpp"
#include "lib/RBTree.hpp"
#include "lib/helpers/Edge.hpp"
#include "lib/helpers/Vertex.hpp"
#include "lib/MatrixGraph.hpp"
#include "lib/Set.hpp"
#include "lib/Tarjan.hpp"
#include "lib/MinHeap.hpp"
#include "lib/PriorityQueue.hpp"

using std::string;

int main() {
    Graph<string> graph;

    graph.addEdge("A", "B");
    graph.addEdge("A", "C");
    graph.addEdge("A", "D");
    graph.addEdge("B", "C");
    graph.addEdge("C", "D");
    graph.addEdge("D", "E");
    graph.addEdge("E", "F");

    graph.removeVertex("A");

    std::cout << graph << std::endl;
}