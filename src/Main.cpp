#include <iostream>
#include <cstdlib> 

#include "lib/datastructs/IndexedPriorityQueue.hpp"
#include "lib/helpers/Arithmatic.hpp"
#include "lib/helpers/StopWatch.hpp"
#include "lib/helpers/Path.hpp"
#include "lib/Graph.hpp"

using std::string;

int main() {
    Graph<int> graph;
    graph.import("graph.json");
    graph.plot();
}
