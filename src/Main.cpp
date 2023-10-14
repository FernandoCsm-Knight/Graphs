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

    graph.addEdge("A", "B");
    graph.addEdge("A", "C");
    graph.addEdge("B", "D");
    graph.addEdge("C", "E");
    graph.addEdge("D", "E");
    
    graph.toJsonFile();
    std::cout << graph.describe() << std::endl;
}
