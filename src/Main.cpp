#include <iostream>
#include <cstdlib> 

#include "lib/datastructs/ArrayList.hpp"
#include "lib/helpers/Pair.hpp"
#include "lib/datastructs/LinkedList.hpp"
#include "lib/datastructs/Map.hpp"
#include "lib/datastructs/RBTree.hpp"
#include "lib/helpers/Edge.hpp"
#include "lib/helpers/Vertex.hpp"
#include "lib/MatrixGraph.hpp"
#include "lib/datastructs/Set.hpp"
#include "lib/Tarjan.hpp"
#include "lib/datastructs/MinHeap.hpp"
#include "lib/datastructs/PriorityQueue.hpp"

using std::string;

int main() {
    Graph<string> graph;

    graph.addEdge("A", "B", 1.0);
    graph.addEdge("A", "C", 5.0);
    graph.addEdge("A", "F", 3.0);
    graph.addEdge("B", "F", 1.0);
    graph.addEdge("C", "F", 1.0);
    graph.addEdge("F", "D", 4.0); // 4
    graph.addEdge("C", "E", 1.0);
    graph.addEdge("E", "D", 1.0);
    graph.addEdge("D", "G", 1.0);

    graph.toJsonFile();
    std::cout << graph.shortestPaht("A", "G") << std::endl;
}
