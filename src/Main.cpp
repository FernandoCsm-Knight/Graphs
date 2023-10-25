#include <iostream>
#include <cstdlib> 

#include "lib/datastructs/IndexedPriorityQueue.hpp"
#include "lib/helpers/Path.hpp"
#include "lib/Graph.hpp"

#include "lib/test/TestBuilder.hpp"

using std::string;

int main() {
    Graph<string> graph(true);

    graph.addEdge("A", "B", 1);
    graph.addEdge("A", "C", 2);
    graph.addEdge("B", "E", 3);
    graph.addEdge("C", "D", 4);
    graph.addEdge("E", "F", 5);
    graph.addEdge("G", "H", 6);
    graph.addVertex("M");

    graph.toJsonFile();
    std::cout << graph.clasp("A", '-') << std::endl;

    // TestBuilder test;
    // test.addTest(TestType::graph_t);
    // test.addTest(TestType::digraph_t);
    // test.addTest(TestType::dijkstra_t);
    // test.addTest(TestType::mst_t);
    // test.run();
    return 0;
}
