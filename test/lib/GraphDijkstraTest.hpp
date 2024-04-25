#ifndef GRAPH_DIJKSTRA_TEST_HPP
#define GRAPH_DIJKSTRA_TEST_HPP

#include <iostream>
#include <fstream>

#include "Test.hpp"
#include "../../src/lib/Graph.hpp"

class GraphDijkstraTest : public Test {
private:
    Graph<std::string> digraph;
    Graph<std::string> graph;

protected:
    void onTestStart(const std::string& testName) override {
        std::cout << "Starting test: " << testName << std::endl;
    }

    void onTestEnd(const std::string& testName, long long elapsed) override {
        std::cout << "Finished test: " << testName << " in " << elapsed << " ms" << std::endl;
    }

    void customTest(const std::string& testName) override {
        if (testName == "Shortest Path Test (Digraph)") {
            shortestPathTest(true);
        } else if (testName == "Shortest Path Test (Graph)") {
            shortestPathTest(false);
        } else if (testName == "Distance Test (Digraph)") {
            distanceTest(true);
        } else if (testName == "Distance Test (Graph)") {
            distanceTest(false);
        }
    }

public:
    GraphDijkstraTest(const std::string& logFolderName = "test/logs") : Test(logFolderName) {
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

    void shortestPathTest(bool directed) {
        bool passed;
        if (directed) {
            passed = digraph.shortestPath("A", "H").getWeight() == 8;
        } else {
            passed = graph.shortestPath("A", "H").getWeight() == 4;
        }
        logResult("Shortest Path Test (" + std::string(directed ? "Digraph" : "Graph") + ")", passed);
    }

    void distanceTest(bool directed) {
        bool passed;
        if (directed) {
            passed = digraph.distance("A", "H") == 4;
        } else {
            passed = graph.distance("A", "H") == 3;
        }
        logResult("Distance Test (" + std::string(directed ? "Digraph" : "Graph") + ")", passed);
    }

private:
    void logResult(const std::string& testName, bool passed) {
        std::ofstream file(logFolder + "/" + STD_LOG_FILE, std::ios::app);
        file << "\t\t" << testName << ": " << (passed ? "Passed" : "Failed") << std::endl;
        file.close();
    }
};

#endif