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

int main() {
    MatrixGraph<std::string> graph(true);

    graph.addEdge("A", "B");
    graph.addEdge("B", "C");
    graph.addEdge("C", "A");

    std::cout << graph.tarjan() << std::endl;
    return 0;
}
