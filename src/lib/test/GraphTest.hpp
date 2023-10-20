#ifndef GRAPH_TEST_HPP
#define GRAPH_TEST_HPP

#include <iostream>
#include <fstream>

#include "Test.hpp"
#include "../Graph.hpp"

class GraphTest : public Test {
    private:
        Graph<std::string> graph;

    public:
        GraphTest(std::string path = "test.log", std::string name = "", std::string description = "") : Test(path, name, description) {
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
        }

        bool weightTest() {
            return graph.weight("J", "K") == 5;
        }

        bool verticesTest() {
            return graph.getVertices().size() == 13;
        }

        bool edgesTest() {
            return graph.getEdges().size() == 19;
        }

        bool degreeTest() {
            return graph.degree("A").first() == 3;
        }

        bool neighborsTest() {
            return graph.getNeighbors("A").size() == 3;
        }

        bool addVertexTest() {
            Graph<std::string> tmp(graph);
            tmp.addVertex("N");
            return tmp.contains("N");
        }

        bool addEdgeTest() {
            Graph<std::string> tmp(graph);
            tmp.addEdge("A", "M", 1);
            return true;
        }

        bool removeVertexTest() {
            Graph<std::string> tmp(graph);
            tmp.removeVertex("M");
            return !tmp.contains("M");
        }

        bool removeEdgeTest() {
            Graph<std::string> tmp(graph);
            tmp.removeEdge("A", "B");
            return !tmp.contains("A", "B");
        }

        bool run() {
            std::ofstream file(path, std::ios::app);

            file << (this->name.length() > 0 ? this->name : "Graph Test:") << std::endl;
            file << (this->description.length() > 0 ? this->description : "\tTest for the graph datastruct.") << std::endl;

            file << "\t\tWeight Test: " << (weightTest() ? "Passed" : "Failed") << std::endl;
            file << "\t\tVertices Test: " << (verticesTest() ? "Passed" : "Failed") << std::endl;
            file << "\t\tEdges Test: " << (edgesTest() ? "Passed" : "Failed") << std::endl;
            file << "\t\tDegree Test: " << (degreeTest() ? "Passed" : "Failed") << std::endl;
            file << "\t\tNeighbors Test: " << (neighborsTest() ? "Passed" : "Failed") << std::endl;
            file << "\t\tAdd Vertex Test: " << (addVertexTest() ? "Passed" : "Failed") << std::endl;
            file << "\t\tAdd Edge Test: " << (addEdgeTest() ? "Passed" : "Failed") << std::endl;
            file << "\t\tRemove Vertex Test: " << (removeVertexTest() ? "Passed" : "Failed") << std::endl;
            file << "\t\tRemove Edge Test: " << (removeEdgeTest() ? "Passed" : "Failed") << std::endl;

            file << std::endl;
            file.close();
            return true;
        }
};

#endif