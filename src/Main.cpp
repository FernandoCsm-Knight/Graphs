#include <iostream>
#include <cstdlib> 

#include "lib/datastructs/IndexedPriorityQueue.hpp"
#include "lib/helpers/Path.hpp"
#include "lib/Graph.hpp"

#include "lib/test/TestBuilder.hpp"

using std::string;

int main() {
    TestBuilder test;
    test.addTest(TestType::graph_t);
    test.addTest(TestType::digraph_t);
    test.addTest(TestType::dijkstra_t);
    test.addTest(TestType::mst_t);
    test.run();
    return 0;
}
