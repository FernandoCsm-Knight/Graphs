#include <iostream>
#include <cstdlib> 

#include "lib/datastructs/IndexedPriorityQueue.hpp"
#include "lib/helpers/Arithmatic.hpp"
#include "lib/helpers/StopWatch.hpp"
#include "lib/helpers/Path.hpp"
#include "lib/Graph.hpp"

using std::string;

int main() {
    Graph<int> graph(true);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);
    graph.addEdge(1, 4);
    graph.addEdge(4, 3);
    graph.addEdge(0, 4);
    graph.addEdge(5, 0);
    graph.addEdge(5, 4);
    std::cout << graph.depthFirstSearch(0) << std::endl;
}
