#include <iostream>
#include <cstdlib> 

#include "lib/datastructs/IndexedPriorityQueue.hpp"
#include "lib/datastructs/MaxHeap.hpp"
#include "lib/helpers/Arithmatic.hpp"
#include "lib/helpers/Stopwatch.hpp"
#include "lib/helpers/Path.hpp"
#include "lib/Graph.hpp"

#include "lib/datastructs/PriorityQueue.hpp"

using std::string;

int main() {
    Graph<int> graph(true);

    graph.addEdge(0, 1, 3.0);
    graph.addEdge(0, 2, 5.0);
    graph.addEdge(0, 3, 4.0);
    graph.addEdge(1, 4, 7.0);
    graph.addEdge(1, 5, 5.0);
    graph.addEdge(1, 2, 1.0);
    graph.addEdge(2, 4, 2.0);
    graph.addEdge(3, 2, 2.0);
    graph.addEdge(5, 4, 8.0);

    std::cout << graph << std::endl;

    std::cout << "Shortest path weights: " << std::endl;
    std::cout << graph.shortestPath(0) << std::endl;

    std::cout << "Widest path weights: " << std::endl;
    std::cout << graph.widestPath(0) << std::endl;

    std::cout << "Narrrowest path weights: " << std::endl;
    std::cout << graph.narrrowestPath(0) << std::endl;
    return 0;
}
