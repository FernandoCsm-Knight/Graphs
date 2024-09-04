#include <iostream>
#include <cstdlib> 

#include "lib/datastructs/IndexedPriorityQueue.hpp"
#include "lib/helpers/Arithmatic.hpp"
#include "lib/helpers/StopWatch.hpp"
#include "lib/helpers/Path.hpp"
#include "lib/Graph.hpp"

using std::string;

int main() {
    int order = 6;
    Graph<int> graph(GraphTypes::COMPLETE, order);
    size_t number = 0;

    for(int i = 1; i <= graph.size(); ++i) {
        auto comb = graph.combinations(i);
        std::cout << "Comb: " << comb.size() << std::endl;

        for(auto c : comb) {
            std::cout << c << std::endl;

            Set<Edge<int>> edges;
            for(int idx = 0; idx < c.size(); ++idx) {
                for(int jdx = idx + 1; jdx < c.size(); ++jdx) {
                    edges.add(Edge<int>(c[idx], c[jdx]));
                }
            }

            size_t n = edges.size(); 
            size_t powerSetSize = 1 << n;

            for (size_t k = 0; k < powerSetSize; ++k) {
                std::cout << "{ ";
                for (size_t j = 0; j < n; ++j) {
                    if (k & (1 << j)) {
                        std::cout << edges[j] << " ";
                    }
                }
                std::cout << "}" << std::endl;
            }
        }

        number += comb.size() * (1 << ((i * (i - 1)) / 2));
    }

    std::cout << "Number of Sub-Graphs: " << number << std::endl;
    std::cout << graph << std::endl;

    std::cout << "Proof: ";
    size_t aux = 0;
    for(int i = 1; i <= order; ++i) {
        aux += art::combinations(order, i) * (1 << ((i * (i - 1)) / 2));
        std::cout << art::combinations(order, i) << " * " << (1 << ((i * (i - 1)) / 2));
        if(i < order) {
            std::cout << " + ";
        }
    }
    std::cout << std::endl << "Expected Number of Sub-Graphs: " << aux << std::endl;
}
