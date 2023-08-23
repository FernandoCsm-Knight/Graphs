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

int main() {
    MatrixGraph<std::string> graph;

    graph.addEdge("A", "B");
    graph.addEdge("A", "C");
    graph.addEdge("A", "D");
    graph.addEdge("B", "C");
    graph.addEdge("B", "D");
    graph.addEdge("C", "D");

    std::cout << graph << std::endl;
    std::cout << (isRegular(graph) ? "Yes":  "No") << std::endl;

    return 0;
}
