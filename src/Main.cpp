#include <iostream>
#include <cstdlib> 

#include "lib/datastructs/IndexedPriorityQueue.hpp"
#include "lib/helpers/Arithmatic.hpp"
#include "lib/helpers/StopWatch.hpp"
#include "lib/helpers/Path.hpp"
#include "lib/Graph.hpp"

using std::string;

int main() {
    Graph<int> graph(GraphTypes::EULERIAN, 20);

    graph.plot();

    std::cout << graph.describe() << std::endl;

    std::cout << graph.connectedComponents() << std::endl;

    // std::cout << graph.cycles(CycleDetectionType::WALK, false).size() << std::endl;

    // Arithmetic ar;

    // unsigned long long sum = 0;
    // for(int i = 3; i <= 5; ++i) {
    //     sum += ar.arrangements(5, i);
    // }

    // std::cout << "Sum: " << sum << std::endl;
}
