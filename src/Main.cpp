#include <iostream>
#include <cstdlib> 
#include <chrono>

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

    ArrayList<int> set;
    set.add(0);
    set.add(1);
    set.add(2);
    set.add(3);

    std::cout << graph << std::endl;
    std::cout << graph.induce(set) << std::endl;

    Stopwatch sw("Dijkstra's Algorithm", Period::MICROSECONDS);
    sw.start();
    std::cout << "Shortest path weights: " << std::endl;
    std::cout << graph.shortestPath(0) << std::endl;

    std::cout << "Widest path weights: " << std::endl;
    std::cout << graph.widestPath(0) << std::endl;

    std::cout << "Narrrowest path weights: " << std::endl;
    std::cout << graph.narrrowestPath(0) << std::endl;
    std::cout << "Execution time: " << sw.stop() << " mis" << std::endl;
    return 0;
}
