#include <iostream>
#include <cstdlib> 

#include "lib/datastructs/IndexedPriorityQueue.hpp"
#include "lib/helpers/Arithmatic.hpp"
#include "lib/helpers/Stopwatch.hpp"
#include "lib/helpers/Path.hpp"
#include "lib/Graph.hpp"

using std::string;

int main() {
    Graph<string> graph;
    graph.addEdge("A", "B");
    graph.addEdge("A", "C");
    graph.addEdge("C", "B");
    graph.addEdge("C", "D");
    graph.addEdge("D", "E");
    graph.addEdge("D", "J");
    graph.addEdge("J", "I");
    graph.addEdge("I", "H");
    graph.addEdge("H", "G");
    graph.addEdge("H", "F");

    std::cout << graph.depthFirstSearch("A") << std::endl;
    std::cout << graph.times("A") << std::endl;
}
