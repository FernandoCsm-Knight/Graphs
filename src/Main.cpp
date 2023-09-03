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

int main() {
    MatrixGraph<std::string> graph(true);    

    graph.addEdge("A", "B");
    graph.addEdge("A", "C");
    graph.addEdge("E", "A");
    graph.addEdge("B", "C");
    graph.addEdge("B", "D");
    graph.addEdge("D", "F");
    graph.addEdge("F", "C");
    graph.addEdge("E", "F");

    std::cout << graph.dist("A", "F") << std::endl;
}