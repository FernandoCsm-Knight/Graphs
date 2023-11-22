#include <iostream>
#include <cstdlib> 

#include "lib/datastructs/IndexedPriorityQueue.hpp"
#include "lib/helpers/Path.hpp"
#include "lib/Graph.hpp"

#include "lib/test/TestBuilder.hpp"

using std::string;

int main() {
    Graph<int> graph(true);

    graph.addEdge(0, 1, 1.0);
    graph.addEdge(0, 2, 20.0);
    graph.addEdge(0, 3, 30.0);
    graph.addEdge(1, 2, 2.0);
    graph.addEdge(2, 1, 2.0);
    graph.addEdge(1, 3, 3.0);
    graph.addEdge(3, 1, 3.0);
    graph.addEdge(2, 3, 1.0);
    graph.addEdge(3, 2, 3.0);

    graph.chuLiuEdmonds(0).toJsonFile();
    return 0;
}
