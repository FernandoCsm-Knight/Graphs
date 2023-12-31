#ifndef GRAPH_DIJKSTRA_TEST_HPP
#define GRAPH_DIJKSTRA_TEST_HPP

#include <iostream>
#include <fstream>

#include "Test.hpp"
#include "../Graph.hpp"

class GraphDijkstraTest : public Test {
    private:
        Graph<std::string> digraph;
        Graph<std::string> graph;
    
    public:

        GraphDijkstraTest(std::string path = "test.log", std::string name = "", std::string description = "") : Test(path, name, description) {
            graph = Graph<std::string>(false);

            graph.addEdge("A", "B", 1);
            graph.addEdge("A", "E", 2);
            graph.addEdge("B", "F", 3);
            graph.addEdge("B", "G", 3);
            graph.addEdge("B", "C", 1);
            graph.addEdge("C", "D", 1);
            graph.addEdge("C", "G", 1);
            graph.addEdge("D", "C", 2);
            graph.addEdge("E", "I", 1);
            graph.addEdge("F", "A", 2);
            graph.addEdge("F", "J", 1);
            graph.addEdge("F", "G", 1);
            graph.addEdge("G", "K", 4);
            graph.addEdge("H", "G", 1);
            graph.addEdge("I", "J", 1);
            graph.addEdge("J", "E", 2);
            graph.addEdge("J", "K", 5);
            graph.addEdge("K", "L", 1);
            graph.addEdge("K", "H", 1);
            graph.addEdge("L", "H", 1);

            graph.addVertex("M");

            digraph = Graph<std::string>(true);

            digraph.addEdge("A", "B", 1);
            digraph.addEdge("A", "E", 2);
            digraph.addEdge("B", "F", 3);
            digraph.addEdge("B", "G", 3);
            digraph.addEdge("B", "C", 1);
            digraph.addEdge("C", "D", 1);
            digraph.addEdge("C", "G", 1);
            digraph.addEdge("D", "C", 2);
            digraph.addEdge("E", "I", 1);
            digraph.addEdge("F", "A", 2);
            digraph.addEdge("F", "J", 1);
            digraph.addEdge("F", "G", 1);
            digraph.addEdge("G", "K", 4);
            digraph.addEdge("H", "G", 1);
            digraph.addEdge("I", "J", 1);
            digraph.addEdge("J", "E", 2);
            digraph.addEdge("J", "K", 5);
            digraph.addEdge("K", "L", 1);
            digraph.addEdge("K", "H", 1);
            digraph.addEdge("L", "H", 1);

            digraph.addVertex("M");
        }

        bool shortestPathTest(bool directed = false) {
            if(directed)
                return digraph.shortestPath("A", "H").getWeight() == 8;
            else
                return graph.shortestPath("A", "H").getWeight() == 4;
        }

        bool distanceTest(bool directed = false) {
            if(directed)
                return digraph.distance("A", "H") == 4;
            else
                return graph.distance("A", "H") == 3;
        }

        bool run() {
            std::ofstream file(path, std::ios::app);
            
            file << (this->name.length() > 0 ? this->name : "Graph Dijkstra Test:") << std::endl;
            file << (this->description.length() > 0 ? this->description : "\tTest for the Dijkstra algorithm.") << std::endl;

            file << "\t\tShortest Path Test (Digraph): " << (this->shortestPathTest() ? "Passed" : "Failed") << std::endl;
            file << "\t\tShortest Path Test (Graph): " << (this->shortestPathTest(true) ? "Passed" : "Failed") << std::endl;
            file << "\t\tDistance Test (Digraph): " << (this->distanceTest() ? "Passed" : "Failed") << std::endl;
            file << "\t\tDistance Test (Graph): " << (this->distanceTest(true) ? "Passed" : "Failed") << std::endl;

            file << std::endl;
            file.close();
            return true;
        }
};

#endif