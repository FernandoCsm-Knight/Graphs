#include <iostream>
#include <cstdlib> 

#include "lib/datastructs/IndexedPriorityQueue.hpp"
#include "lib/helpers/Path.hpp"
#include "lib/Graph.hpp"

#include "lib/test/TestBuilder.hpp"

using std::string;

int main() {
    ArrayList<int> comp;

    comp.addInOrder(1);
    comp.addInOrder(2);
    comp.addInOrder(3);
    comp.addInOrder(4);
    comp.addInOrder(5);
    comp.addInOrder(5);
    comp.addInOrder(5);
    comp.addInOrder(6);
    comp.addInOrder(7);

    std::cout << comp << std::endl;
    std::cout << comp.lastIndexOf(1, true) << std::endl;

    // TestBuilder test;
    // test.addTest(TestType::graph_t);
    // test.addTest(TestType::digraph_t);
    // test.addTest(TestType::dijkstra_t);
    // test.addTest(TestType::mst_t);
    // test.run();
    return 0;
}
